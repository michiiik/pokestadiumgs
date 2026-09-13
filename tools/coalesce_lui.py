#!/usr/bin/env python3
"""Fold redundant ``lui $at`` sequences in IDO's ``.s`` output.

IDO expands a macro-form memory instruction with no explicit base register
(``sw $0, SYM``) into ``lui $at, %hi(SYM); sw $0, %lo(SYM)($at)``. Neither
IDO's own assembler nor GNU ``as`` can share one ``lui`` across two *different*
symbols on the same page, because at assembly time relocation addresses are
unresolved and the assembler cannot prove two distinct symbols share a page.

This ROM is a *matching* decompilation: every data symbol's final address is
already fixed (see ``linker_scripts/us/symbol_addrs*.txt`` and the
linked ``build/pokestadiumgs-us.map``), so a small, strictly opt-in,
post-compile text transform can prove same-page-ness and fold the redundant
``lui`` -- reproducing an assembler artifact that occurs in the ground-truth
ROM but that no C spelling alone can make either compiler emit.

Everything in this module is pure text/dict manipulation with no build-system
side effects, so it is unit-testable in isolation (see
``tools/test_coalesce_lui.py``). The only consumer that actually shells out to
a compiler is ``tools/coalesce_cc.py``.

Safety model
------------
This is deliberately **not** a blanket peephole optimization. Two independent
gates must both agree before any bytes are folded:

1. **Per-function opt-in.** ``find_coalesce_markers`` looks for an explicit
   ``#pragma COALESCE_AT_LUI(function_name)`` immediately before the
   function definition -- the same convention this codebase already uses for
   ``#pragma GLOBAL_ASM(...)`` and ``#pragma C_FUNCTION_PADDING(n)``. Bare
   text outside a function named by that pragma is never touched, even when
   compiled through this same file.
2. **Address proof.** Even inside an opted-in function, ``fold_source`` only
   folds a run of memory ops when *every* operand's address resolves via the
   authoritative address map and all of them land on the same ``%hi`` page.
   A function whose ground truth does not actually have this shape (wrong
   page, an unresolved symbol, an intervening instruction that clobbers
   ``$at``) is left completely alone; the opt-in pragma alone is not
   sufficient to change output.

Not on the build path any more
------------------------------
``coalesce_cc.py`` folds the *compiled object* now
(``coalesce_object.fold_function_in_object``), because this text-level route
had to re-assemble what it folded and that round trip does not preserve
IDO's own ``cc -c`` scheduling -- see ``coalesce_object``'s module docstring
for the measurement. What stays live here is the address map
(``resolve_repo_addresses``/``hi16``/``lo16``) and the pragma parsing
(``find_coalesce_markers``/``find_coalesce_symbol_filters``), all of which
the object fold uses directly. ``fold_source`` and
``prepare_snippet_for_gnu_as`` are retained as the text-level statement of
the fold's semantics -- ``scan_coalesce_sites.py`` defines "contiguous" in
terms of ``fold_source`` -- and remain unit-tested, but nothing compiles
through them.

Assembler quirk this module works around
-----------------------------------------
The naive fold -- repeating ``%lo(OTHER_SYMBOL)($at)`` for every symbol in
the run -- is what a first prototype tried, and it is what a hand-verified,
GNU-``as``-only pipeline used to confirm the *bytes* are right. But this
project's own IDO port (as0/as1) mis-assembles that exact form: it emits a
*second*, spurious relocation for every ``%lo`` after the first whose symbol
does not match the preceding ``%hi``'s symbol, which the linker then applies
on top of the correct one and doubles the low half of the address. Emitting
a **plain hex immediate** (computed from the address map, since these
addresses are fixed) for every operand after the first -- keeping only the
very first operand's ``%hi``/``%lo`` pair symbolic -- sidesteps the bug
entirely and was confirmed byte-for-byte via IDO's own assembler against the
linked ``baserom.z64`` bytes at the target address. See
``docs/regions/fragments/79/fragment79_393CA0.md`` and the PR description for
the full empirical trail.
"""
from __future__ import annotations

import re
from collections.abc import Mapping
from pathlib import Path

# A bare macro-form memory op: no base register, just a symbol. This is what
# IDO emits for `*(&SYM) = value;`-shaped statements before the assembler
# expands it into an explicit lui/op pair. IDO's `-S` output spells a
# floating-point load/store as the pseudo-mnemonic `l.s`/`s.s`/`l.d`/`s.d`
# rather than `lwc1`/`swc1`/`ldc1`/`sdc1` directly; GNU as accepts both
# spellings identically (confirmed: `l.s`/`s.s` assemble to plain
# `lwc1`/`swc1`, `l.d`/`s.d` to `ldc1`/`sdc1`), so the float spellings are
# just as foldable as the integer ones and are included here for the same
# reason `swc1`/`lwc1` already were.
_MACRO_MEM_OP = re.compile(
    r'^\t(?P<op>sw|sh|sb|lw|lh|lhu|lb|lbu|swc1|lwc1|s\.s|l\.s|s\.d|l\.d)\t(?P<reg>\$\w+),\s*'
    r'(?P<sym>[A-Za-z_.$][\w.$]*)\s*$'
)

# Lines that may appear between macro mem-ops in a foldable run without
# breaking it: source line markers, IDO's inline "# n <src>" echo, and its
# live-register-set annotation. None of these carry machine code.
_DIRECTIVE_GAP = re.compile(r'^[ \t]*(\.loc\b|#|\.livereg\b)')

_ENT = re.compile(r'^\s*\.ent\s+([A-Za-z_.$][\w.$]*)')
_END = re.compile(r'^\s*\.end\s+([A-Za-z_.$][\w.$]*)')

_SYMBOL_ADDR_LINE = re.compile(r'^\s*([A-Za-z_.$][\w.$]*)\s*=\s*0x([0-9A-Fa-f]+)\s*;')
# ld's own "map" style is one of many line shapes that start with a hex
# address; only the bare "<addr>  <name>" symbol-definition shape (nothing
# else on the line) is a real symbol -- section/object-file rows always carry
# extra columns (a section name, a size, a path) and must not be matched.
_MAP_SYMBOL_LINE = re.compile(r'^\s{2,}0x([0-9A-Fa-f]{6,16})\s+([A-Za-z_.$][\w.$]*)\s*$')

# ``#pragma COALESCE_AT_LUI(func)`` folds every foldable run in ``func``.
# The optional trailing symbol list -- ``COALESCE_AT_LUI(func, S1, S2, S3)`` --
# narrows that to the named symbols: an op addressing anything else is left
# alone *and* cuts the run there. Ground truth sometimes reuses one ``$at``
# for part of a same-page group and then reloads it (``func_82300A78`` folds
# D_82305EC4/EC6/EC2 but keeps a second ``lui`` for the equally same-page
# D_82305EC8), which a greedy maximal-run fold cannot express.
_COALESCE_PRAGMA = re.compile(
    r'^[ \t]*#pragma\s+COALESCE_AT_LUI\s*\(\s*([A-Za-z_]\w*)\s*'
    r'((?:,\s*[A-Za-z_.$][\w.$]*\s*)*)\)[ \t]*$',
    re.MULTILINE,
)


def hi16(addr: int) -> int:
    """The ``%hi`` page (upper 16 bits, with the usual +0x8000 rounding)."""
    return ((addr + 0x8000) >> 16) & 0xFFFF


def lo16(addr: int) -> int:
    """The raw ``%lo`` 16-bit field, as an unsigned 0-0xFFFF value."""
    return addr & 0xFFFF


def _lo16_immediate_literal(addr: int) -> str:
    """A ``%lo``-equivalent literal for a ``sw``/``lw``-style offset operand.

    MIPS load/store immediates are a *signed* 16-bit field, and GNU as
    parses a bare offset literal by range, not by target field width: for
    any address whose low 16 bits have bit 15 set (roughly half of all
    addresses), the unsigned form (``0x9000``) reads as a value too large
    for a plain signed-immediate encoding, so `as` treats it as needing
    macro expansion -- which then fails outright inside ``.set noat``
    (reproduced directly: ``sw $0, 0x9000($at)`` under ``.set noat`` errors
    with "macro used $at after '.set noat'"). The signed decimal form
    (``-28672`` for that same value) parses as a direct signed-immediate
    encoding and assembles to the identical bits.
    """
    value = lo16(addr)
    if value & 0x8000:
        return str(value - 0x10000)
    return '0x%04x' % value


def parse_symbol_addrs(paths) -> dict[str, int]:
    """Parse ``NAME = 0xHEX;`` entries out of one or more symbol_addrs files.

    First writer wins across the given paths, mirroring how the linker
    scripts are concatenated (earlier files take priority over later
    generated/derived ones).
    """
    addrs: dict[str, int] = {}
    for raw_path in paths:
        path = Path(raw_path)
        try:
            text = path.read_text(encoding="latin1")
        except OSError:
            continue
        for line in text.splitlines():
            match = _SYMBOL_ADDR_LINE.match(line)
            if match:
                addrs.setdefault(match.group(1), int(match.group(2), 16))
    return addrs


def parse_linker_map(path) -> dict[str, int]:
    """Parse bare symbol-definition rows out of a linked GNU ld map file."""
    addrs: dict[str, int] = {}
    try:
        text = Path(path).read_text(encoding="latin1")
    except OSError:
        return addrs
    for line in text.splitlines():
        match = _MAP_SYMBOL_LINE.match(line)
        if match:
            addrs[match.group(2)] = int(match.group(1), 16)
    return addrs


def _primary_worktree_root(repo_root: Path) -> Path | None:
    """Return the primary checkout for a linked Git worktree, if known.

    A small local copy of the same lookup ``tools/try_pragma_compare.py``
    already performs: kept independent (rather than imported across the
    top-level tools boundary) since it is a handful of
    lines with no other dependency.
    """
    git_file = repo_root / ".git"
    try:
        if not git_file.is_file():
            return None
        line = git_file.read_text(encoding="utf-8").strip()
        prefix = "gitdir: "
        if not line.startswith(prefix):
            return None
        git_dir = Path(line[len(prefix):]).resolve()
        if git_dir.parent.name != "worktrees":
            return None
        return git_dir.parent.parent.parent
    except OSError:
        return None


def candidate_map_paths(repo_root: Path):
    """Linked-map locations to consult, most authoritative first.

    A linked worktree's own map only exists after it has completed a full
    build; falling back to a linked primary checkout's map is safe because
    fixed data-segment addresses (what this module resolves) are intrinsic
    to the ROM's segment layout and identical across every worktree of this
    repository -- this mirrors the existing ``_ensure_worktree_oracles``
    precedent of treating the primary checkout's build artifacts as a
    read-only reference for a linked worktree.
    """
    repo_root = Path(repo_root)
    yield repo_root / "build" / "pokestadiumgs-us.map"
    primary = _primary_worktree_root(repo_root)
    if primary is not None:
        yield primary / "build" / "pokestadiumgs-us.map"


def resolve_repo_addresses(repo_root: Path) -> dict[str, int]:
    """Best-effort authoritative ``{symbol: address}`` map for this checkout.

    ``symbol_addrs*.txt`` is preferred (tracked, always available, no build
    required), then the tracked ``undefined_syms*.ld`` scripts -- splat writes
    every symbol it could not attach to a segment there in the very same
    ``NAME = 0xADDR;`` form, and for a data page referenced only from still-
    ``GLOBAL_ASM`` code that file is usually the *only* tracked place the
    address appears (``D_82305EC2``/``D_82305EC6`` in
    ``fragments/19/fragment19_121100`` are the worked example). A linked
    ``.map`` then fills in fixed dlabel-only addresses that neither carries
    (this project's convention keeps most ``dlabel``s out of
    ``symbol_addrs*.txt`` entirely); note it only lists such an alias in ld's
    ``PROVIDE``-assignment shape, which ``parse_linker_map`` deliberately does
    not match, so the ``.ld`` scripts are not redundant with it.
    """
    repo_root = Path(repo_root)
    linker_scripts = repo_root / "linker_scripts"
    addrs = parse_symbol_addrs(
        sorted(linker_scripts.glob("*/symbol_addrs*.txt"))
        + sorted(linker_scripts.glob("*/undefined_syms*.ld"))
        + sorted(linker_scripts.glob("*/auto/undefined_syms*.ld"))
    )
    for map_path in candidate_map_paths(repo_root):
        if not map_path.is_file():
            continue
        for name, addr in parse_linker_map(map_path).items():
            addrs.setdefault(name, addr)
        break
    return addrs


def find_coalesce_markers(source_text: str) -> set[str]:
    """Function names this C source has explicitly opted into lui-coalescing.

    Mirrors the ``#pragma GLOBAL_ASM(...)``/``#pragma C_FUNCTION_PADDING(n)``
    convention already used in this codebase for per-function,
    build-behavior-altering markers: this is opt-in one function at a time,
    and the marker sits textually with the function it applies to.
    """
    return {match[0] for match in _COALESCE_PRAGMA.findall(source_text)}


def find_coalesce_symbol_filters(source_text: str) -> dict:
    """``{function: frozenset(symbols) | None}`` for every opted-in function.

    ``None`` means the bare ``COALESCE_AT_LUI(func)`` form: fold every run
    the address map proves shares a page (the original, and still the common,
    spelling). A frozenset is the narrowed form described on
    ``_COALESCE_PRAGMA``: only ops addressing one of those symbols may fold,
    and one that does not also *ends* the run it appears in, which is how a
    ground-truth partial fold is spelled.

    Repeating the pragma for one function unions the listed symbols; a bare
    marker anywhere for that function wins outright (it is the wider request).
    """
    filters: dict = {}
    for name, symbol_text in _COALESCE_PRAGMA.findall(source_text):
        symbols = [part.strip() for part in symbol_text.split(',') if part.strip()]
        if not symbols:
            filters[name] = None
            continue
        if name in filters:
            if filters[name] is None:
                continue
            symbols.extend(filters[name])
        filters[name] = frozenset(symbols)
    return filters


def functions_defined(asm_text: str) -> set[str]:
    """Function names IDO actually emitted a ``.ent``/``.end`` block for."""
    names: set[str] = set()
    for line in asm_text.splitlines():
        match = _ENT.match(line)
        if match:
            names.add(match.group(1))
    return names


def extract_function_block(asm_text: str, function_name: str) -> str | None:
    """Return the raw ``.ent NAME ... .end NAME`` text for one function.

    ``None`` if IDO never emitted that function (e.g. the marker names a
    typo'd or dead function).
    """
    lines = asm_text.splitlines(keepends=True)
    start = None
    for i, line in enumerate(lines):
        match = _ENT.match(line)
        if match and match.group(1) == function_name:
            start = i
            break
    if start is None:
        return None
    for j in range(start, len(lines)):
        match = _END.match(lines[j])
        if match and match.group(1) == function_name:
            return ''.join(lines[start : j + 1])
    return None


# Directives IDO's own ``-S`` output carries that GNU ``as`` either does not
# recognize standalone or does not need once a snippet is assembled outside
# the context of the whole file it came from (debug line/file tables, IDO's
# own live-register annotation, and function metadata GNU as does not use
# the same way). Mirrors the strip list from the original hand-verified
# prototype (see the PR description for the exact command sequence).
#
# ``.alias``/``.noalias`` are a later addition: IDO emits them around any
# pair of register-valued loads it cannot statically prove don't alias (seen
# on a plain `if (global == a || global == b) { ...write several other
# globals... }` shape, unrelated to lui-coalescing) to hint its own optimizer
# -- register operands only (``.noalias $2,$3``), never a symbol -- so they
# carry no information relevant to the machine bytes GNU as would emit and
# are safe to drop the same way ``.livereg`` already is. Without stripping
# them GNU as rejects the snippet outright with "unknown pseudo-op", which
# made every opted-in function whose body IDO decorates with them
# uncompilable through this mechanism regardless of whether a fold even
# applies to it.
_GNU_AS_INCOMPATIBLE = re.compile(
    r'^\s*(\.loc\b|\.file\b|\.verstamp\b|\.livereg\b|\.option\b|\.ent\b|\.end\b|'
    r'\.frame\b|\.alias\b|\.noalias\b|\s*#)'
)

_EXTERN_LINE = re.compile(r'^\s*\.extern\s+([A-Za-z_.$][\w.$]*)\s+(\d+)')
_BARE_SYMBOL_OPERAND = re.compile(
    r'%(?:hi|lo)\(([A-Za-z_.$][\w.$]*)\)'
    r'|^\t(?:sw|sh|sb|lw|lh|lhu|lb|lbu|swc1|lwc1|s\.s|l\.s|s\.d|l\.d)\t\$\w+,\s*([A-Za-z_.$][\w.$]*)\s*$'
)


def parse_extern_sizes(asm_text: str) -> dict[str, int]:
    """Map symbol name -> declared size from a whole file's ``.extern`` lines."""
    sizes: dict[str, int] = {}
    for line in asm_text.splitlines():
        match = _EXTERN_LINE.match(line)
        if match:
            sizes.setdefault(match.group(1), int(match.group(2)))
    return sizes


def prepare_snippet_for_gnu_as(
    block_text: str, extern_sizes: dict[str, int]
) -> str:
    """Turn one extracted ``.ent``/``.end`` block into a standalone GNU-``as`` input.

    Strips the IDO-only directives GNU as rejects outside a full compile
    (including ``.ent``/``.end`` themselves -- GNU as needs none of this
    project's function metadata to assemble a plain function body), restores
    the ``.text``/``.globl``/label sequence that normally comes from *before*
    the ``.ent`` line in the whole-file ``.s`` (so this snippet is a
    complete, standalone compilation unit on its own), and prepends an
    ``.extern NAME SIZE`` for every bare global symbol the block still
    references so the assembler's own macro expansion (for any memory op the
    fold left untouched) has something to resolve against.
    """
    ent_match = _ENT.match(block_text.splitlines()[0])
    if not ent_match:
        raise ValueError("block_text must start with an .ent line")
    function_name = ent_match.group(1)

    referenced: set[str] = set()
    for line in block_text.splitlines():
        for match in _BARE_SYMBOL_OPERAND.finditer(line):
            name = match.group(1) or match.group(2)
            if name:
                referenced.add(name)

    kept_lines = [
        line for line in block_text.splitlines(keepends=True)
        if not _GNU_AS_INCOMPATIBLE.match(line)
    ]

    externs = [
        '\t.extern\t%s %d\n' % (name, extern_sizes.get(name, 4))
        for name in sorted(referenced)
    ]
    preamble = (
        '\t.text\n'
        '\t.align\t2\n'
        '\t.globl\t%s\n' % function_name
    )
    # GNU as does not infer a symbol's ELF size from IDO-style .ent/.end
    # bookkeeping (already stripped above); an explicit .size is what makes
    # this snippet's function symbol carry a real size for
    # coalesce_splice.py to compare against the outer object's.
    trailer = '\t.size\t%s, . - %s\n' % (function_name, function_name)
    return ''.join(externs) + preamble + ''.join(kept_lines) + trailer


def _symbol_allowed(op_match, symbol_filter) -> bool:
    """Whether a matched macro mem-op may take part in a fold.

    ``symbol_filter`` of ``None`` (the bare pragma) allows everything; a
    frozenset restricts folding to the symbols the pragma named.
    """
    return symbol_filter is None or op_match.group('sym') in symbol_filter


def fold_source(
    text: str, allowed_functions, address_map: dict[str, int]
) -> tuple[str, int]:
    """Fold shared-page ``lui $at`` runs, but only inside opted-in functions.

    Returns ``(new_text, folds_applied)``. A function not named in
    ``allowed_functions`` is passed through byte-for-byte unchanged. Inside
    an opted-in function, a run of two or more consecutive macro-form memory
    ops (directive/comment-only lines between them do not break the run) is
    folded only when every operand's symbol resolves in ``address_map`` and
    all of them share the same ``%hi`` page; otherwise that run, too, is left
    untouched.

    The fold keeps the *first* operand's ``%hi``/``%lo`` fully symbolic (a
    completely ordinary relocated lui/op pair) and expresses every
    subsequent operand as a literal ``%lo``-equivalent hex immediate off the
    same ``$at`` -- seemingly a step backward from a symbolic ``%lo`` on
    every operand, but that repeated-symbolic form is exactly what triggers
    a relocation-duplication bug in this project's IDO port (see the module
    docstring); the literal-immediate form was verified byte-identical
    against the linked ROM with IDO's own assembler.
    """
    if isinstance(allowed_functions, Mapping):
        allowed = dict(allowed_functions)
    else:
        allowed = {name: None for name in allowed_functions}
    lines = text.splitlines(keepends=True)
    out: list[str] = []
    current_function: str | None = None
    total_folds = 0
    i = 0
    n = len(lines)

    while i < n:
        line = lines[i]
        ent_match = _ENT.match(line)
        if ent_match:
            current_function = ent_match.group(1)
        elif _END.match(line):
            current_function = None

        stripped = line.rstrip('\n')
        symbol_filter = allowed.get(current_function) if current_function in allowed else None
        op_match = (
            _MACRO_MEM_OP.match(stripped) if current_function in allowed else None
        )
        if op_match is not None and not _symbol_allowed(op_match, symbol_filter):
            op_match = None
        if op_match is None:
            out.append(line)
            i += 1
            continue

        # Collect a maximal run of macro mem-ops; directive/comment-only
        # lines are kept (in their original order) but do not break the run.
        run: list[tuple[str, object]] = []
        j = i
        while j < n:
            candidate = lines[j].rstrip('\n')
            mm = _MACRO_MEM_OP.match(candidate)
            if mm is not None and not _symbol_allowed(mm, symbol_filter):
                break
            if mm is not None:
                run.append(('op', mm))
                j += 1
            elif _DIRECTIVE_GAP.match(lines[j]):
                run.append(('gap', lines[j]))
                j += 1
            else:
                break

        ops = [entry for kind, entry in run if kind == 'op']
        addrs = [address_map.get(mm.group('sym')) for mm in ops]
        if (
            len(ops) < 2
            or any(addr is None for addr in addrs)
            or len({hi16(addr) for addr in addrs}) != 1
        ):
            out.append(line)
            i += 1
            continue

        base_sym = ops[0].group('sym')
        out.append('\t.set\tnoat\n')
        out.append('\tlui\t$at, %%hi(%s)\n' % base_sym)
        op_position = 0
        for kind, entry in run:
            if kind == 'gap':
                out.append(entry)  # type: ignore[arg-type]
                continue
            mm = entry
            addr = addrs[op_position]
            op_position += 1
            if op_position == 1:
                out.append(
                    '\t%s\t%s, %%lo(%s)($at)\n' % (mm.group('op'), mm.group('reg'), base_sym)
                )
            else:
                out.append(
                    '\t%s\t%s, %s($at)\t# %s\n'
                    % (mm.group('op'), mm.group('reg'), _lo16_immediate_literal(addr), mm.group('sym'))
                )
        out.append('\t.set\tat\n')
        total_folds += len(ops) - 1
        i = j

    return ''.join(out), total_folds
