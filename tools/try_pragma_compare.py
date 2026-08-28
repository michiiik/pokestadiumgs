#!/usr/bin/env python3
"""Try C replacements for GLOBAL_ASM pragmas.

Usage:
    tools/try_pragma_compare.py disasm/src/229E0.c func_80025CBC candidate.c
    tools/try_pragma_compare.py --bundle disasm/src/229E0.c candidates.txt

The single-candidate form replaces exactly one pragma line.  A failed
COMPARE=1 restores the source file byte-for-byte; a successful comparison
keeps it.  The candidate file is deleted after the attempt unless
--keep-candidate is passed.

Bundle files contain blocks of this form, which are tested independently:

    /* candidate: func_80025D44 */
    extern s32 func_80019378(void);
    s32 func_80025D44(void) { return func_80019378(); }
    /* end candidate */

Bundle candidates are compiled first in isolated temporary source/object
paths.  Those probes run in parallel and never edit the live source.  Only
function-byte hits are tested sequentially in the live checkout with the
full linker/ROM comparison.  The first successful candidate for a function
is retained; later variants for that function are skipped.
"""

from __future__ import annotations

import os
import difflib
import hashlib
import json
import re
import shlex
import shutil
import subprocess
import sys
import tempfile
import threading
import time
from contextlib import contextmanager
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

try:
    import fcntl
except ImportError:  # pragma: no cover - the supported host is POSIX/macOS
    fcntl = None

import probe_stats
import variant_policy

# Set by a caller (``sweep_targets.py``) that already knows a per-function
# family mapping (e.g. from a sweep listing) but does not want to thread a
# ``families`` dict through every ``try_candidates_detailed`` call site.
# ``_record_probe_stats`` consults this only for an attempt that does not
# already carry its own ``family`` key.
family_lookup: Callable[[str], str | None] | None = None


MIPS_REGISTERS = (
    "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra",
)
MIPS_FLOAT_REGISTERS = tuple(f"f{index}" for index in range(32))
NORMALISABLE_REGISTERS = MIPS_REGISTERS + ("s8",) + MIPS_FLOAT_REGISTERS


def _mips_instruction_description(word: int) -> str:
    """Return a compact description useful for source-shape debugging.

    This intentionally decodes only the fields needed to distinguish the
    common candidate failure modes (different register allocation, immediate,
    or opcode).  It is diagnostic text, not a replacement for objdump.
    """
    opcode = (word >> 26) & 0x3F
    rs = MIPS_REGISTERS[(word >> 21) & 0x1F]
    rt = MIPS_REGISTERS[(word >> 16) & 0x1F]
    rd = MIPS_REGISTERS[(word >> 11) & 0x1F]
    funct = word & 0x3F
    if opcode == 0:
        names = {
            0x00: "sll", 0x02: "srl", 0x03: "sra", 0x08: "jr",
            0x09: "jalr", 0x21: "addu", 0x23: "subu", 0x24: "and",
            0x25: "or", 0x26: "xor", 0x27: "nor", 0x2A: "slt",
            0x2B: "sltu",
        }
        name = names.get(funct, f"special/{funct:#x}")
        if funct in {0x08, 0x09}:
            return f"{name} ${rs}"
        if funct in {0x00, 0x02, 0x03}:
            return f"{name} ${rd}, ${rt}, {(word >> 6) & 0x1F}"
        return f"{name} ${rd}, ${rs}, ${rt}"
    names = {
        0x04: "beq", 0x05: "bne", 0x06: "blez", 0x07: "bgtz",
        0x08: "addiu", 0x09: "addiu", 0x0A: "slti", 0x0B: "sltiu",
        0x0C: "andi", 0x0D: "ori", 0x0E: "xori", 0x0F: "lui",
        0x20: "lb", 0x21: "lh", 0x23: "lw", 0x24: "lbu",
        0x25: "lhu", 0x28: "sb", 0x29: "sh", 0x2B: "sw",
    }
    name = names.get(opcode, f"op/{opcode:#x}")
    immediate = word & 0xFFFF
    if immediate & 0x8000:
        immediate -= 0x10000
    if opcode == 0x0F:
        return f"{name} ${rt}, 0x{word & 0xFFFF:04x}"
    if opcode in {0x04, 0x05}:
        return f"{name} ${rs}, ${rt}, {immediate}"
    if opcode in {0x06, 0x07}:
        return f"{name} ${rs}, {immediate}"
    return f"{name} ${rt}, ${rs}, {immediate}"


def source_object_path(source_path: Path) -> tuple[Path, Path]:
    repo_root = Path(__file__).resolve().parent.parent
    relative = source_path.resolve().relative_to(repo_root / "disasm")
    return repo_root, repo_root / "disasm" / "build" / relative.with_suffix(".o")


def _binutils_tool(name: str) -> str:
    prefix = os.environ.get(
        "MIPS_BINUTILS_PREFIX", "/Users/michaegg/homebrew/bin/mips-linux-gnu-"
    )
    return f"{prefix}{name}"


def _probe_root(repo_root: Path) -> Path:
    """Return the dedicated source root used by isolated probe candidates."""
    root = repo_root / "disasm" / "probes"
    root.mkdir(parents=True, exist_ok=True)
    return root


def _cleanup_stale_probe_dirs(repo_root: Path) -> None:
    """Remove abandoned probe source trees without touching tracked sources.

    Probe transactions are process-serialized by ``_candidate_transaction_lock``.
    A one-hour age threshold keeps a live/debugging probe safe while cleaning
    directories left behind by an interrupted runner process.
    """
    stale_after = _command_timeout("PRAGMA_PROBE_STALE_SECONDS", 3600.0)
    now = time.time()
    roots = (
        _probe_root(repo_root),
        repo_root / "disasm" / "src",
        repo_root / "disasm" / "build" / "src",
        repo_root / "disasm" / "build" / "probes",
    )
    for root in roots:
        for directory in root.rglob(".pragma_probe_*"):
            try:
                if not directory.is_dir() or now - directory.stat().st_mtime < stale_after:
                    continue
                shutil.rmtree(directory)
            except OSError:
                continue


def _command_timeout(environment_name: str, default: float) -> float:
    """Read a positive subprocess timeout without making it mandatory."""
    value = os.environ.get(environment_name)
    if value is None:
        return default
    try:
        timeout = float(value)
    except ValueError:
        return default
    return timeout if timeout > 0 else default


def _timeout_output(error: subprocess.TimeoutExpired) -> str:
    output = error.stdout if error.stdout is not None else error.output
    if isinstance(output, bytes):
        output = output.decode(errors="replace")
    return str(output or "")


def _object_build_environment() -> dict[str, str]:
    """Environment shared by Makefile object builds and captured probe recipes."""
    return {
        **os.environ,
        "MIPS_BINUTILS_PREFIX": os.environ.get(
            "MIPS_BINUTILS_PREFIX", "/Users/michaegg/homebrew/bin/mips-linux-gnu-"
        ),
        "COMPARE": "0",
        "RUN_CC_CHECK": "0",
        "OBJDUMP_BUILD": "0",
        "COLOR": "0",
    }


# Placeholder paths (relative to ``disasm/``) used to capture the Makefile's
# probe compile recipe once.  Every later probe substitutes its own paths into
# the captured tokens instead of paying the Makefile parse cost again.
_RECIPE_DIRECTORY = "probes/.pragma_probe_recipe/"
_RECIPE_SOURCE = _RECIPE_DIRECTORY + "__pragma_recipe__.c"
_RECIPE_OBJECT = "build/" + _RECIPE_SOURCE[:-2] + ".o"
_RECIPE_CACHE: dict[tuple[object, ...], dict[str, list[str] | None]] = {}
_RECIPE_CACHE_LOCK = threading.Lock()


def _parse_probe_recipe(make_output: str) -> list[str] | None:
    """Extract the compile command for the placeholder probe from ``make -n``.

    The recipe prints an echo line, a (possibly disabled) host compiler check,
    the real asm-processor/IDO compile, and post-processing commands.  The
    compile is the last command that consumes the placeholder source and
    names the placeholder object, so a still-enabled ``cc`` check can never
    be mistaken for it.
    """
    recipe: list[str] | None = None
    for tokens in _recipe_lines(make_output):
        if tokens[-1] == _RECIPE_SOURCE and "-o" in tokens and _RECIPE_OBJECT in tokens:
            recipe = tokens
    return recipe


def _parse_check_recipe(make_output: str) -> list[str] | None:
    """Extract the host ``cc`` syntax-check command for the placeholder probe.

    The check command carries the repository's include paths and defines in a
    form a host compiler understands, which makes it the right base for
    producing preprocessed C for m2c contexts and permuter inputs.
    """
    for tokens in _recipe_lines(make_output):
        if tokens[-1] == _RECIPE_SOURCE and "-fsyntax-only" in tokens:
            return tokens
    return None


def _recipe_lines(make_output: str):
    for line in make_output.splitlines():
        try:
            tokens = shlex.split(line)
        except ValueError:
            continue
        if not tokens or tokens[0] in {":", "printf", "echo"}:
            continue
        yield tokens


def host_preprocess_command(check_recipe: list[str], include_directory: str) -> list[str]:
    """Turn the captured host syntax check into a ``-E -P`` preprocess command.

    ``include_directory`` (relative to ``disasm/``, trailing slash) replaces
    the probe placeholder so ``-I <owner dir>`` resolves sibling headers.  The
    caller appends the input file; output goes to stdout.  ``__attribute__``
    is erased because pycparser-based consumers cannot parse it.
    """
    command: list[str] = []
    skip_next = False
    for token in check_recipe[:-1]:
        if skip_next:
            skip_next = False
            continue
        if token == "-o":
            skip_next = True
            continue
        if token in {"-fsyntax-only", "-MMD", "-MP", "-fdiagnostics-color"}:
            continue
        command.append(token.replace(_RECIPE_DIRECTORY, include_directory))
    command += ["-E", "-P", "-D__attribute__(x)="]
    return command


def _substitute_probe_recipe(recipe: list[str], source_rel: str, object_rel: str) -> list[str]:
    """Rewrite placeholder paths in a captured recipe for one probe.

    The object placeholder embeds the directory placeholder, so it is replaced
    first; the ``-I <probe dir>`` include token is rewritten last.
    """
    directory_rel = source_rel.rsplit("/", 1)[0] + "/"
    return [
        token.replace(_RECIPE_OBJECT, object_rel)
        .replace(_RECIPE_SOURCE, source_rel)
        .replace(_RECIPE_DIRECTORY, directory_rel)
        for token in recipe
    ]


def _probe_recipes(repo_root: Path) -> dict[str, list[str] | None]:
    """Capture the Makefile's probe recipes once per Makefile revision.

    ``make`` spends most of a probe's wall time discovering sources and
    grepping every tracked file for ``GLOBAL_ASM`` before it even starts the
    compiler.  Capturing the recipe with ``make -n`` keeps the Makefile
    authoritative for flags while letting probes invoke asm-processor/IDO
    directly.  The host syntax check is captured in the same pass (with
    ``RUN_CC_CHECK=1``) for preprocessing consumers.
    """
    makefile = repo_root / "disasm" / "Makefile"
    try:
        key: tuple[object, ...] = (
            makefile.stat().st_mtime_ns,
            os.environ.get("MIPS_BINUTILS_PREFIX"),
        )
    except OSError:
        return {"compile": None, "check": None}
    with _RECIPE_CACHE_LOCK:
        cached = _RECIPE_CACHE.get(key)
        if cached is not None:
            return cached
        placeholder = repo_root / "disasm" / _RECIPE_SOURCE
        try:
            placeholder.parent.mkdir(parents=True, exist_ok=True)
            placeholder.write_text("")
            result = subprocess.run(
                ["make", "-C", "disasm", "-n", "PRAGMA_PROBE=1", "RUN_CC_CHECK=1", _RECIPE_OBJECT],
                cwd=repo_root,
                env=_object_build_environment(),
                text=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                timeout=_command_timeout("PRAGMA_COMPILE_TIMEOUT", 120.0),
            )
        except (OSError, subprocess.TimeoutExpired):
            return {"compile": None, "check": None}
        finally:
            shutil.rmtree(placeholder.parent, ignore_errors=True)
        if result.returncode != 0:
            return {"compile": None, "check": None}
        output = result.stdout or ""
        recipes = {
            "compile": _parse_probe_recipe(output),
            "check": _parse_check_recipe(output),
        }
        if recipes["compile"] is not None:
            _RECIPE_CACHE[key] = recipes
        return recipes


def _probe_compile_recipe(repo_root: Path) -> list[str] | None:
    """Return the cached direct compile command for isolated probes (or ``None``)."""
    return _probe_recipes(repo_root)["compile"]


def host_check_recipe(repo_root: Path) -> list[str] | None:
    """Return the cached host ``cc`` syntax-check command for probes (or ``None``)."""
    return _probe_recipes(repo_root)["check"]


def _make_object(source_path: Path, *, capture: bool = False) -> tuple[int, Path, str]:
    """Compile one source file to its build-tree object.

    Tracked sources go through the repository's normal Makefile rule.  Probe
    sources live below ``disasm/probes/`` and use the captured Makefile recipe
    directly, so parallel probes skip the Makefile parse and never contend
    with each other or alter the tracked source.
    """
    repo_root = Path(__file__).resolve().parent.parent
    relative = source_path.resolve().relative_to(repo_root / "disasm")
    object_path = repo_root / "disasm" / "build" / relative.with_suffix(".o")
    object_path.parent.mkdir(parents=True, exist_ok=True)
    object_path.unlink(missing_ok=True)
    object_rel = object_path.relative_to(repo_root / "disasm").as_posix()
    kwargs: dict[str, object] = {
        "cwd": repo_root,
        "env": _object_build_environment(),
        "text": True,
    }
    if capture:
        kwargs["stdout"] = subprocess.PIPE
        kwargs["stderr"] = subprocess.STDOUT
    command = ["make", "-C", "disasm", "PRAGMA_PROBE=1", object_rel]
    if relative.parts and relative.parts[0] == "probes":
        recipe = _probe_compile_recipe(repo_root)
        if recipe is not None:
            command = _substitute_probe_recipe(recipe, relative.as_posix(), object_rel)
            kwargs["cwd"] = repo_root / "disasm"
    try:
        result = subprocess.run(
            command,
            timeout=_command_timeout("PRAGMA_COMPILE_TIMEOUT", 120.0),
            **kwargs,
        )
    except subprocess.TimeoutExpired as error:
        _remove_probe_outputs(object_path)
        return 124, object_path, (
            f"compile timed out after {error.timeout}s\n{_timeout_output(error)}"
        )
    output = result.stdout if capture and isinstance(result.stdout, str) else ""
    return result.returncode, object_path, output


def rebuild_source_object(source_path: Path) -> int:
    result, _, _ = _make_object(source_path)
    return result


def invalidate_link_outputs(repo_root: Path) -> None:
    build = repo_root / "disasm" / "build"
    for name in ("pokestadiumgs-us.elf", "pokestadiumgs-us.z64", "pokestadiumgs-us.map"):
        (build / name).unlink(missing_ok=True)


def try_candidate(source_path: Path, function: str, candidate: str) -> int:
    with _candidate_transaction_lock():
        result, _ = _try_candidate_detailed(source_path, function, candidate)
    return result


def _try_candidate_detailed(source_path: Path, function: str, candidate: str) -> tuple[int, str]:
    """Run one candidate and identify the phase that accepted or rejected it."""
    source = source_path.read_text()
    candidate = candidate.rstrip() + "\n"

    pragma = re.compile(
        rf'^#pragma GLOBAL_ASM\("asm/us/nonmatchings/[^\"]+/{re.escape(function)}\.s"\)$',
        re.MULTILINE,
    )
    source_after, count = pragma.subn(candidate.rstrip("\n"), source, count=1)
    if count != 1:
        print(f"could not find exactly one pragma for {function}", file=sys.stderr)
        return 2, "invalid_pragma"

    accepted = False
    source_path.write_text(source_after)
    try:
        if rebuild_source_object(source_path) != 0:
            return 2, "compile_failed"
        invalidate_link_outputs(Path(__file__).resolve().parent.parent)
        result, output = _run_compare(Path(__file__).resolve().parent.parent)
        print(output, end="")

        if result != 0:
            print(f"REJECTED {function}: restored GLOBAL_ASM")
            return result, "compare_rejected"

        accepted = True
        print(f"ACCEPTED {function}: source replacement kept")
        return result, "accepted"
    finally:
        if not accepted:
            try:
                source_path.write_text(source)
                # Force make to rebuild the restored object instead of reusing
                # the rejected candidate object, regardless of timestamp
                # resolution.
                os.utime(source_path, None)
                rebuild_source_object(source_path)
            except (OSError, RuntimeError):
                # Preserve the original candidate failure; the next guarded
                # transaction will repair the object if the compiler was
                # interrupted while restoring it.
                pass


def _run_compare(repo_root: Path) -> tuple[int, str]:
    """Run the full compare with a bounded lifetime and captured diagnostics."""
    env = os.environ.copy()
    env.setdefault("MIPS_BINUTILS_PREFIX", "/Users/michaegg/homebrew/bin/mips-linux-gnu-")
    # The full gate also runs the Makefile's host-side syntax check (clang,
    # -fsyntax-only) unless the caller opts out with PRAGMA_GATE_CC_CHECK=0.
    # Skipping it used to let byte-matching candidates land that later broke
    # any non-runner ``make`` (a stale object hid them until the file was
    # touched again); the Makefile now keeps IDO-accepted int/pointer
    # conversions as warnings, so the check only rejects real breakage.
    env["RUN_CC_CHECK"] = "0" if os.environ.get("PRAGMA_GATE_CC_CHECK") == "0" else "1"
    try:
        result = subprocess.run(
            ["make", "-C", "disasm", "COMPARE=1", "-j2"],
            cwd=repo_root,
            env=env,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=_command_timeout("PRAGMA_COMPARE_TIMEOUT", 300.0),
        )
    except subprocess.TimeoutExpired as error:
        return 124, (
            f"compare timed out after {error.timeout}s\n{_timeout_output(error)}"
        )
    return result.returncode, result.stdout or ""


def compare_current_tree(repo_root: Path) -> int:
    invalidate_link_outputs(repo_root)
    result, output = _run_compare(repo_root)
    if output:
        print(output, end="")
    return result


def _object_text(object_path: Path) -> bytes | None:
    """Return the raw relocatable .text section from an object file."""
    with tempfile.TemporaryDirectory(prefix=".pragma_text_") as directory:
        output = Path(directory) / "text.bin"
        result = subprocess.run(
            [_binutils_tool("objcopy"), "--dump-section", f".text={output}", str(object_path)],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
        )
        if result.returncode != 0 or not output.exists():
            return None
        return output.read_bytes()


def _object_symbol(object_path: Path, function: str) -> tuple[int, int] | None:
    """Return a function's section offset and size from a relocatable object."""
    result = subprocess.run(
        [_binutils_tool("nm"), "-S", "--defined-only", str(object_path)],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    )
    if result.returncode != 0:
        return None
    for line in result.stdout.splitlines():
        fields = line.split()
        if len(fields) < 4 or fields[-1] != function or fields[-2].upper() == "U":
            continue
        try:
            return int(fields[0], 16), int(fields[1], 16)
        except ValueError:
            return None
    return None


def _function_bytes(
    object_path: Path,
    function: str,
    span: int | None = None,
) -> bytes | None:
    symbol = _object_symbol(object_path, function)
    text = _object_text(object_path) if symbol is not None else None
    if symbol is None or text is None:
        return None
    offset, symbol_size = symbol
    size = symbol_size if span is None else span
    if size <= 0 or offset < 0 or offset + size > len(text):
        return None
    return text[offset : offset + size]


def _function_byte_views(
    object_path: Path,
    function: str,
    span: int,
) -> tuple[int | None, bytes | None, bytes | None]:
    """Return ``(symbol_size, symbol_bytes, span_bytes)`` with one nm/objcopy pass.

    ``symbol_bytes`` covers the compiler's own symbol range and ``span_bytes``
    covers the baseline owner's span (which may include alignment nops).  A
    probe needs both, and running the binutils pair once per view doubled the
    subprocess count of every probe.
    """
    symbol = _object_symbol(object_path, function)
    if symbol is None:
        return None, None, None
    text = _object_text(object_path)
    if text is None:
        return symbol[1], None, None
    offset, symbol_size = symbol

    def view(size: int) -> bytes | None:
        if size <= 0 or offset < 0 or offset + size > len(text):
            return None
        return text[offset : offset + size]

    return symbol_size, view(symbol_size), view(span)


# --- link-shape verification -------------------------------------------------
#
# A ``.text`` byte match proves the instruction stream, but not the linked
# ROM: a C ``switch`` emits a jump table into a new ``.rodata`` section (the
# baseline keeps its tables in separate data segments, so ``jtbl_*`` symbols
# are *undefined* in the owner object), and a candidate may reference a
# different symbol behind identical relocatable bytes.  These helpers compare
# the allocatable section layout and the function's relocations so that a
# verified probe hit can skip the per-function ROM gate.

_LINK_SHAPE_SKIP_SECTION_PREFIXES = (
    ".rel", ".rela", ".mdebug", ".symtab", ".strtab", ".shstrtab", ".options",
    ".reginfo", ".pdr", ".comment", ".gnu", ".MIPS", ".note", ".debug", ".line",
)
_READELF_SECTION_RE = re.compile(
    r"^\s*\[\s*(\d+)\]\s+(\S+)\s+(\S+)\s+([0-9a-fA-F]{8})\s+([0-9a-fA-F]{6})\s+"
    r"([0-9a-fA-F]{6})\s+([0-9a-fA-F]{2})\s*([A-Za-z]*)"
)
_READELF_SYMBOL_RE = re.compile(
    r"^\s*(\d+):\s+([0-9a-fA-F]+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\S+)\s*(.*)$"
)
_READELF_RELOC_SECTION_RE = re.compile(r"^Relocation section '([^']+)'")
_READELF_RELOC_RE = re.compile(r"^([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+(R_\w+)")


def _readelf(object_path: Path, *flags: str) -> str | None:
    try:
        result = subprocess.run(
            [_binutils_tool("readelf"), *flags, "-W", str(object_path)],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            timeout=_command_timeout("PRAGMA_OBJDUMP_TIMEOUT", 5.0),
        )
    except (OSError, subprocess.TimeoutExpired):
        return None
    if result.returncode != 0:
        return None
    return result.stdout


def _parse_readelf_sections(text: str) -> dict[int, dict[str, object]]:
    sections: dict[int, dict[str, object]] = {}
    for line in text.splitlines():
        match = _READELF_SECTION_RE.match(line)
        if not match:
            continue
        sections[int(match.group(1))] = {
            "name": match.group(2),
            "type": match.group(3),
            "size": int(match.group(6), 16),
            "flags": match.group(8),
        }
    return sections


def _parse_readelf_symbols(text: str) -> dict[int, dict[str, object]]:
    symbols: dict[int, dict[str, object]] = {}
    for line in text.splitlines():
        match = _READELF_SYMBOL_RE.match(line)
        if not match:
            continue
        size_text = match.group(3)
        try:
            size = int(size_text, 16) if size_text.lower().startswith("0x") else int(size_text)
        except ValueError:
            size = 0
        symbols[int(match.group(1))] = {
            "value": int(match.group(2), 16),
            "size": size,
            "type": match.group(4),
            "ndx": match.group(7),
            "name": match.group(8).strip(),
        }
    return symbols


def _parse_readelf_relocations(text: str) -> dict[str, list[tuple[int, str, int]]]:
    """Return ``{section: [(offset, type, symbol_index)]}`` from ``readelf -r``."""
    relocations: dict[str, list[tuple[int, str, int]]] = {}
    current: str | None = None
    for line in text.splitlines():
        header = _READELF_RELOC_SECTION_RE.match(line)
        if header:
            current = header.group(1)
            relocations.setdefault(current, [])
            continue
        if current is None:
            continue
        match = _READELF_RELOC_RE.match(line)
        if not match:
            continue
        info = int(match.group(2), 16)
        relocations[current].append((int(match.group(1), 16), match.group(3), info >> 8))
    return relocations


def _object_section_bytes(object_path: Path, section: str) -> bytes | None:
    with tempfile.TemporaryDirectory(prefix=".pragma_section_") as directory:
        output = Path(directory) / "section.bin"
        result = subprocess.run(
            [_binutils_tool("objcopy"), "--dump-section", f"{section}={output}", str(object_path)],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
        )
        if result.returncode != 0 or not output.exists():
            return None
        return output.read_bytes()


def _object_link_shape(object_path: Path) -> dict[str, object] | None:
    """Return the allocatable sections, symbols, and ``.text`` relocations of an object.

    ``None`` means the view could not be read; callers must then treat the
    candidate as *unverified* (eligible for the sequential gate), never as a
    match.
    """
    section_text = _readelf(object_path, "-S")
    symbol_text = _readelf(object_path, "-s")
    relocation_text = _readelf(object_path, "-r")
    if section_text is None or symbol_text is None or relocation_text is None:
        return None
    sections = _parse_readelf_sections(section_text)
    allocatable: dict[str, dict[str, object]] = {}
    for section in sections.values():
        name = str(section["name"])
        if "A" not in str(section["flags"]) or name.startswith(_LINK_SHAPE_SKIP_SECTION_PREFIXES):
            continue
        entry = dict(section)
        if name != ".text" and section["type"] == "PROGBITS" and int(section["size"]) > 0:
            entry["bytes"] = _object_section_bytes(object_path, name)
        allocatable[name] = entry
    text = _object_text(object_path)
    if text is None:
        return None
    return {
        "sections": allocatable,
        "section_names": {index: str(section["name"]) for index, section in sections.items()},
        "symbols": _parse_readelf_symbols(symbol_text),
        "relocations": _parse_readelf_relocations(relocation_text),
        "text": text,
    }


def _sign_extend_16(value: int) -> int:
    value &= 0xFFFF
    return value - 0x10000 if value & 0x8000 else value


def _normalized_function_relocations(
    shape: dict[str, object],
    start: int,
    size: int,
) -> list[tuple[int, str, str, int]]:
    """Return ``(relative_offset, type, target, addend)`` for ``.text`` relocations in a span.

    Targets are resolved to ``section+value`` so a reference through a local
    symbol and one through the section symbol compare equal.  In-place (REL)
    addends are decoded per relocation type; ``HI16`` pairs with the next
    ``LO16`` against the same symbol.  Intra-``.text`` ``PC16`` branches are
    dropped: their bytes are already covered by the function-byte compare.
    """
    text = shape["text"]
    assert isinstance(text, bytes)
    symbols = shape["symbols"]
    section_names = shape["section_names"]
    assert isinstance(symbols, dict) and isinstance(section_names, dict)
    relocations = shape["relocations"]
    assert isinstance(relocations, dict)
    entries = [
        entry for entry in relocations.get(".rel.text", []) + relocations.get(".rela.text", [])
        if start <= entry[0] < start + size
    ]
    entries.sort()

    def word_at(offset: int) -> int:
        if offset + 4 > len(text):
            return 0
        return int.from_bytes(text[offset:offset + 4], "big")

    def target_of(symbol_index: int) -> tuple[str, int]:
        symbol = symbols.get(symbol_index)
        if symbol is None:
            return (f"SYM:{symbol_index}", 0)
        ndx = str(symbol["ndx"])
        value = int(symbol["value"])
        if ndx == "UND":
            return (f"UND:{symbol['name']}", 0)
        if ndx.isdigit():
            return (str(section_names.get(int(ndx), ndx)), value)
        return (ndx, value)

    normalized: list[tuple[int, str, str, int]] = []
    for position, (offset, kind, symbol_index) in enumerate(entries):
        word = word_at(offset)
        if kind == "R_MIPS_26":
            addend = (word & 0x3FFFFFF) << 2
        elif kind == "R_MIPS_32":
            addend = word
        elif kind == "R_MIPS_HI16":
            addend = (word & 0xFFFF) << 16
            for later_offset, later_kind, later_symbol in entries[position + 1:]:
                if later_kind == "R_MIPS_LO16" and later_symbol == symbol_index:
                    addend += _sign_extend_16(word_at(later_offset))
                    break
        elif kind in {"R_MIPS_LO16", "R_MIPS_GPREL16", "R_MIPS_LITERAL"}:
            addend = _sign_extend_16(word)
        elif kind == "R_MIPS_PC16":
            addend = _sign_extend_16(word) << 2
        else:
            addend = 0
        section, value = target_of(symbol_index)
        if kind == "R_MIPS_PC16" and section == ".text":
            continue
        normalized.append((offset - start, kind, section, value + addend))
    return normalized


def _compare_link_shape(
    expected_shape: dict[str, object] | None,
    actual_shape: dict[str, object] | None,
    expected_symbol: tuple[int, int] | None,
    actual_symbol: tuple[int, int] | None,
) -> dict[str, object]:
    """Decide whether a ``.text`` match will also link byte-identically.

    Returns ``link_verified`` (``True``/``False``/``None`` for unknown) with a
    ``link_mismatch`` reason.  ``section_layout_drift`` is *definitive*: an
    added or resized allocatable section changes the ROM regardless of the
    instruction bytes.  ``relocation_drift`` is advisory only, so the caller
    keeps the candidate eligible for the sequential ROM gate.
    """
    if expected_shape is None or actual_shape is None or expected_symbol is None or actual_symbol is None:
        return {"link_verified": None, "link_mismatch": "shape_unavailable"}
    expected_sections = expected_shape["sections"]
    actual_sections = actual_shape["sections"]
    assert isinstance(expected_sections, dict) and isinstance(actual_sections, dict)
    for name in sorted(set(expected_sections) | set(actual_sections)):
        expected = expected_sections.get(name)
        actual = actual_sections.get(name)
        if expected is None or actual is None:
            side = "candidate" if expected is None else "baseline"
            return {
                "link_verified": False,
                "link_mismatch": "section_layout_drift",
                "link_detail": f"section {name} exists only in the {side} object",
            }
        if int(expected["size"]) != int(actual["size"]):
            return {
                "link_verified": False,
                "link_mismatch": "section_layout_drift",
                "link_detail": (
                    f"section {name} size 0x{int(expected['size']):x} -> 0x{int(actual['size']):x}"
                ),
            }
        if name != ".text" and expected.get("bytes") != actual.get("bytes"):
            return {
                "link_verified": False,
                "link_mismatch": "section_content_drift",
                "link_detail": f"section {name} bytes differ",
            }
    expected_relocations = _normalized_function_relocations(expected_shape, *expected_symbol)
    actual_relocations = _normalized_function_relocations(actual_shape, *actual_symbol)
    if expected_relocations != actual_relocations:
        detail = None
        for left, right in zip(expected_relocations, actual_relocations):
            if left != right:
                detail = f"expected {left} candidate {right}"
                break
        if detail is None:
            detail = (
                f"relocation count {len(expected_relocations)} -> {len(actual_relocations)}"
            )
        return {
            "link_verified": False,
            "link_mismatch": "relocation_drift",
            "link_detail": detail,
        }
    return {"link_verified": True, "link_mismatch": None}


def _is_nop(word: int) -> bool:
    return word == 0


def _is_jr_ra(word: int) -> bool:
    return word == 0x03E00008


def _classify_tail_bytes(data: bytes) -> str:
    """Classify post-return words to separate padding from real tail code.

    The first ``jr $ra`` and its delay slot are the normal function return.
    Words after that pair are the useful part of this diagnostic: extra
    ``jr/nop`` pairs usually mean an assembly owner contains a real tail,
    while all-zero words are alignment padding.  This never changes matching
    eligibility; it only makes a size/layout mismatch actionable.
    """
    if len(data) < 4:
        return "none"
    words = [
        int.from_bytes(data[offset:offset + 4], "big")
        for offset in range(0, len(data) - 3, 4)
    ]
    for index, word in enumerate(words):
        if not _is_jr_ra(word):
            continue
        if index + 1 >= len(words):
            return "unterminated_return"
        tail = words[index + 2:]
        if not tail:
            return "normal_return"
        if all(_is_nop(value) for value in tail):
            return "jr_nop_plus_alignment"
        if any(_is_jr_ra(value) for value in tail):
            return "duplicate_jr_nop_tail"
        return "mixed_post_return_tail"
    if all(_is_nop(value) for value in words[-2:]):
        return "nop_only_tail"
    return "no_return_found"


def _disassemble_bytes(data: bytes) -> list[str]:
    """Disassemble raw big-endian MIPS words with the configured binutils."""
    words = len(data) // 4
    if words == 0:
        return []
    data = data[: words * 4]
    with tempfile.TemporaryDirectory(prefix=".pragma_disasm_") as directory:
        binary = Path(directory) / "function.bin"
        binary.write_bytes(data)
        try:
            result = subprocess.run(
                [
                    _binutils_tool("objdump"),
                    "-D",
                    "-EB",
                    "-b",
                    "binary",
                    "-m",
                    # VR4300 is MIPS III: ``mips:isa32`` decodes 64-bit
                    # operations such as ``dsll32``/``ld`` as ``.word`` and
                    # silently corrupts the normalized similarity score.
                    "mips:4300",
                    str(binary),
                ],
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
                timeout=_command_timeout("PRAGMA_OBJDUMP_TIMEOUT", 5.0),
            )
        except (OSError, subprocess.TimeoutExpired):
            return []
    if result.returncode != 0:
        return []
    instruction_re = re.compile(r"^\s*[0-9a-fA-F]+:\s+[0-9a-fA-F]{8}\s+(.+?)\s*$")
    instructions = []
    for line in result.stdout.splitlines():
        match = instruction_re.match(line)
        if match:
            instructions.append(match.group(1))
    return instructions


def _instruction_texts(data: bytes) -> list[str]:
    """Return objdump text, falling back to the local compact decoder."""
    instructions = _disassemble_bytes(data)
    if instructions:
        return instructions
    return [
        _mips_instruction_description(
            int.from_bytes(data[offset:offset + 4], "big")
        )
        for offset in range(0, len(data) - 3, 4)
    ]


def _normalise_instruction_text(text: str, *, immediates: bool = True) -> str:
    """Erase register (and optionally immediate) allocation, keeping opcode shape."""
    registers = "|".join(
        re.escape(register) for register in NORMALISABLE_REGISTERS
    )
    text = re.sub(
        rf"(?<![A-Za-z0-9_])\$?(?:{registers})(?![A-Za-z0-9_])",
        "REG",
        text.lower(),
    )
    if immediates:
        text = re.sub(r"(?<![A-Za-z0-9_])-?(?:0x[0-9a-f]+|[0-9]+)(?![A-Za-z0-9_])", "IMM", text)
    return re.sub(r"\s+", " ", text).strip()


def _function_mismatch_details(
    object_path: Path,
    function: str,
    expected: bytes,
    actual: bytes | None,
    *,
    actual_symbol_size: int | None = None,
) -> dict[str, object]:
    """Summarize a rejected probe without dumping the candidate object.

    ``actual_symbol_size`` lets a caller that already ran ``nm`` skip a second
    symbol lookup; without it the size is read from the object.
    """
    details: dict[str, object] = {
        "expected_size": len(expected),
        "expected_tail_kind": _classify_tail_bytes(expected),
    }
    if actual_symbol_size is None:
        symbol = _object_symbol(object_path, function)
        if symbol is not None:
            actual_symbol_size = symbol[1]
    if actual_symbol_size is not None:
        details["actual_size"] = actual_symbol_size
    if actual is None:
        details["first_diff_offset"] = None
        return details
    details["actual_tail_kind"] = _classify_tail_bytes(actual)
    expected_texts = _instruction_texts(expected)
    actual_texts = _instruction_texts(actual)
    expected_words = [
        int.from_bytes(expected[offset:offset + 4], "big")
        for offset in range(0, len(expected) - 3, 4)
    ]
    actual_words = [
        int.from_bytes(actual[offset:offset + 4], "big")
        for offset in range(0, len(actual) - 3, 4)
    ]
    instruction_count = max(len(expected_texts), len(actual_texts))
    normalized_expected = [_normalise_instruction_text(text) for text in expected_texts]
    normalized_actual = [_normalise_instruction_text(text) for text in actual_texts]
    register_only_expected = [
        _normalise_instruction_text(text, immediates=False) for text in expected_texts
    ]
    register_only_actual = [
        _normalise_instruction_text(text, immediates=False) for text in actual_texts
    ]
    normalized_matcher = difflib.SequenceMatcher(
        None, normalized_expected, normalized_actual, autojunk=False
    )
    register_only_matcher = difflib.SequenceMatcher(
        None, register_only_expected, register_only_actual, autojunk=False
    )
    raw_matcher = difflib.SequenceMatcher(None, expected_words, actual_words, autojunk=False)
    normalized_matches = sum(block.size for block in normalized_matcher.get_matching_blocks())
    register_only_matches = sum(
        block.size for block in register_only_matcher.get_matching_blocks()
    )
    raw_matches = sum(block.size for block in raw_matcher.get_matching_blocks())
    details["expected_instruction_count"] = len(expected_texts)
    details["actual_instruction_count"] = len(actual_texts)
    details["total_instructions"] = instruction_count
    details["matched_instructions"] = normalized_matches
    details["exact_instruction_matches"] = raw_matches
    details["normalized_matched_instructions"] = normalized_matches
    details["raw_similarity_score"] = round(raw_matches / instruction_count, 4) if instruction_count else 1.0
    details["exact_similarity_score"] = details["raw_similarity_score"]
    details["similarity_score"] = round(normalized_matches / instruction_count, 4) if instruction_count else 1.0
    # Registers erased, immediates kept: separates "same code, different
    # register allocation" from "same shape, different offsets/constants".
    details["register_only_similarity_score"] = (
        round(register_only_matches / instruction_count, 4) if instruction_count else 1.0
    )
    assembly_diff: list[dict[str, object]] = []
    for tag, expected_start, expected_end, actual_start, actual_end in raw_matcher.get_opcodes():
        if tag == "equal":
            continue
        width = max(expected_end - expected_start, actual_end - actual_start)
        for delta in range(width):
            expected_index = expected_start + delta
            actual_index = actual_start + delta
            expected_text = (
                expected_texts[expected_index]
                if expected_index < expected_end
                else "<missing>"
            )
            actual_text = (
                actual_texts[actual_index]
                if actual_index < actual_end
                else "<missing>"
            )
            expected_normalized = (
                normalized_expected[expected_index]
                if expected_index < expected_end
                else "<missing>"
            )
            actual_normalized = (
                normalized_actual[actual_index]
                if actual_index < actual_end
                else "<missing>"
            )
            assembly_diff.append({
                "expected_instruction": expected_index,
                "actual_instruction": actual_index,
                "expected_offset": expected_index * 4,
                "actual_offset": actual_index * 4,
                "expected": expected_text,
                "actual": actual_text,
                "expected_normalized": expected_normalized,
                "actual_normalized": actual_normalized,
                "normalized_match": expected_normalized == actual_normalized,
                "exact_match": expected_text == actual_text,
            })
    details["assembly_diff"] = assembly_diff[:32]
    details["assembly_diff_truncated"] = len(assembly_diff) > 32
    diff_offsets = [
        index
        for index, (left, right) in enumerate(zip(expected, actual))
        if left != right
    ]
    first_diff = diff_offsets[0] if diff_offsets else min(len(expected), len(actual))
    details["first_diff_offset"] = first_diff
    details["diff_offsets"] = diff_offsets[:8]
    details["first_diff_instruction"] = first_diff // 4
    if not diff_offsets and len(expected) != len(actual):
        details["mismatch_kind"] = "symbol_size_drift"
    elif first_diff % 4:
        details["mismatch_kind"] = "unaligned_data_drift"
    else:
        details["mismatch_kind"] = "instruction_drift"
    if first_diff < len(expected):
        details["expected_byte"] = f"{expected[first_diff]:02x}"
    if first_diff < len(actual):
        details["actual_byte"] = f"{actual[first_diff]:02x}"
    instruction_start = first_diff - (first_diff % 4)
    if instruction_start + 4 <= len(expected):
        expected_word = int.from_bytes(
            expected[instruction_start:instruction_start + 4], "big"
        )
        details["expected_instruction"] = f"0x{expected_word:08x}"
        details["expected_instruction_text"] = _mips_instruction_description(expected_word)
    if instruction_start + 4 <= len(actual):
        actual_word = int.from_bytes(
            actual[instruction_start:instruction_start + 4], "big"
        )
        details["actual_instruction"] = f"0x{actual_word:08x}"
        details["actual_instruction_text"] = _mips_instruction_description(actual_word)
    if (
        "expected_instruction_text" in details
        and "actual_instruction_text" in details
        and str(details["expected_instruction_text"]).split(" ", 1)[0]
        == str(details["actual_instruction_text"]).split(" ", 1)[0]
    ):
        details["mismatch_kind"] = "operand_or_scheduling_drift"
    # Whole-body classifications beat the first-instruction heuristic: when the
    # entire opcode stream already lines up, the remaining work is a type,
    # declaration-order, or struct-offset change rather than a control-flow one.
    if diff_offsets and len(expected_texts) == len(actual_texts) and instruction_count:
        if register_only_expected == register_only_actual:
            details["mismatch_kind"] = "register_allocation_only"
        elif normalized_expected == normalized_actual:
            details["mismatch_kind"] = "immediate_drift"
    _annotate_normalized_only_match(details)
    return details


def _annotate_normalized_only_match(details: dict[str, object]) -> None:
    """Flag a normalised score that is hiding a real raw-instruction mismatch.

    ``similarity_score`` erases register allocation; ``raw_similarity_score``
    does not.  A candidate can reach a normalised 1.0 (or anything >= 0.99)
    while its raw score sits well below that -- an agent trusted exactly
    such a 1.0 that had ``raw_similarity_score`` 0.63 with values swapped
    between struct fields (AGENTS.md Sec 5).  This sets a boolean
    ``normalized_only_match`` and folds a plain-language warning into
    ``details["diagnostic"]`` so the flag is visible anywhere the diagnostic
    text is rendered, not just to a caller that inspects both score fields.
    """
    similarity_score = details.get("similarity_score")
    raw_similarity_score = details.get("raw_similarity_score")
    normalized_only_match = (
        isinstance(similarity_score, (int, float))
        and isinstance(raw_similarity_score, (int, float))
        and similarity_score >= 0.99
        and raw_similarity_score < 0.9
    )
    details["normalized_only_match"] = normalized_only_match
    summary = (
        f"similarity_score={similarity_score} raw_similarity_score={raw_similarity_score} "
        f"mismatch_kind={details.get('mismatch_kind')}"
    )
    if normalized_only_match:
        summary += (
            "; normalized_only_match: the normalised similarity score is hiding "
            "register/field differences that raw_similarity_score exposes -- do not "
            "treat this as a match without checking assembly_diff"
        )
    details["diagnostic"] = summary


def _declaration_prefix(declarations: str | None) -> str:
    """Normalize a shared declarations block into a candidate prefix."""
    if declarations is None:
        return ""
    body = declarations.strip()
    return body + "\n" if body else ""


_CALL_SYMBOL_RE = re.compile(r"\bfunc_[0-9A-Fa-f]+\b")

# A signature's return-type/qualifier prefix: any number of storage-class or
# base-type keywords, then exactly one base type name, then optional
# pointer stars.  Deliberately excludes ``=``, ``(``, ``return``, and other
# expression tokens, so a mere call site (``result = func_X(arg);``,
# ``if (func_X(arg))``) never gets mistaken for a declaration or definition.
_SIGNATURE_TYPE_PREFIX_RE = re.compile(
    r"^(?:(?:extern|static|const|volatile|unsigned|signed|struct\s+\w+|union\s+\w+)\s+)*"
    r"[A-Za-z_]\w*\s*\**$"
)

# A bare identifier used as a C control-flow keyword is grammatically
# indistinguishable from a bare type name to ``_SIGNATURE_TYPE_PREFIX_RE``
# (both are just one word) -- ``return func_X(arg);`` must not be mistaken
# for a definition whose "return type" is literally named ``return``.
_CONTROL_FLOW_KEYWORDS = frozenset({
    "return", "if", "while", "for", "switch", "case", "else", "do", "goto",
    "break", "continue", "sizeof",
})


def _is_signature_type_prefix(prefix: str) -> bool:
    """Whether ``prefix`` reads as a return-type/qualifier list, not an expression."""
    if not _SIGNATURE_TYPE_PREFIX_RE.match(prefix):
        return False
    tokens = re.findall(r"[A-Za-z_]\w*", prefix)
    return bool(tokens) and tokens[-1] not in _CONTROL_FLOW_KEYWORDS

# The leading-line shape a hand-written or m2c-drafted candidate uses for its
# own forward declarations (see this module's docstring): blank lines,
# ``/* ... */`` comments, ``extern ...;`` lines, and bare ``<type> f(...);``
# prototypes, all before the body opens its first ``{``.
_EXTERN_LINE_RE = re.compile(r"^\s*extern\b.*;\s*$")
_COMMENT_ONLY_LINE_RE = re.compile(r"^\s*/\*.*\*/\s*$")
_BARE_PROTOTYPE_LINE_RE = re.compile(r"^\s*[^={}]*\([^;{}]*\)\s*;\s*$")


def _find_balanced_close_paren(text: str, open_index: int) -> int | None:
    """Return the index of the ``)`` matching ``text[open_index] == '('``."""
    depth = 0
    for index in range(open_index, len(text)):
        char = text[index]
        if char == "(":
            depth += 1
        elif char == ")":
            depth -= 1
            if depth == 0:
                return index
    return None


def _statement_start(text: str, before: int) -> int:
    """Index just past the nearest ``;``/``{``/``}`` before ``before`` (or 0).

    Anchoring on the nearest statement-terminating character -- not the
    start of the source *line* -- is what lets this find a definition that
    shares its line with an earlier statement, e.g. ``extern u8 D_x[]; u8
    func_8005D92C(s32 index) { ... }``: a line-anchored scan stops at the
    ``;`` inside that same line and never sees the real signature after it.
    """
    boundary = max(text.rfind(char, 0, before) for char in ";{}")
    return boundary + 1


def scan_source_for_callee_signature(source_text: str, function: str) -> str | None:
    """Scan a whole C source for an existing declaration/definition of ``function``.

    Returns the exact ``"<return-type-and-quals> function(<params>)"``
    signature as written in ``source_text`` (no trailing ``;``/``{``) --
    from a real definition when one exists, else from a plain
    ``extern``/prototype declaration -- or ``None`` when the source says
    nothing about it anywhere.

    This is deliberately position-independent: it is not limited to
    declarations above some cutoff.  A callee DEFINED LATER IN THE SAME FILE
    than the call site is exactly the case a synthesized fallback prototype
    must defer to instead of guessing (AGENTS.md Sec 5's
    ``func_8005D92C``: a synthesized ``s32 func_8005D92C()`` conflicted with
    the real, later ``u8 func_8005D92C(s32 arg0) { ... }`` and IDO rejected
    the redeclaration).  A real definition always wins over a plain
    prototype when both exist, since it is authoritative.
    """
    name_pattern = re.compile(rf"\b{re.escape(function)}\s*\(")
    best_definition: str | None = None
    best_declaration: str | None = None
    for match in name_pattern.finditer(source_text):
        open_paren = match.end() - 1
        close_paren = _find_balanced_close_paren(source_text, open_paren)
        if close_paren is None:
            continue
        after = source_text[close_paren + 1 : close_paren + 33].lstrip()
        if not after or after[0] not in "{;":
            continue
        terminator = after[0]
        start = _statement_start(source_text, match.start())
        prefix = source_text[start : match.start()].strip()
        if not prefix or not _is_signature_type_prefix(prefix):
            continue
        params = source_text[open_paren + 1 : close_paren].strip()
        signature = re.sub(r"\s+", " ", f"{prefix} {function}({params})").strip()
        if terminator == "{":
            # A real definition is authoritative; stop scanning immediately.
            return signature
        if best_declaration is None:
            best_declaration = signature
    return best_definition or best_declaration


def _as_extern_declaration(signature: str) -> str:
    """Format a scanned signature as a standalone forward declaration."""
    text = re.sub(r"^extern\s+", "", signature.strip())
    return f"extern {text};"


def _candidate_declared_callee_names(candidate: str) -> set[str]:
    """Return callee names the candidate's own leading lines already declare.

    Mirrors the documented candidate convention (a run of blank, comment,
    ``extern ...;``, or bare-prototype lines before the body): a name that
    only appears *inside* the body -- a call, not a declaration -- must not
    count here, or a genuinely missing forward declaration would never get
    synthesized for it.
    """
    names: set[str] = set()
    for line in candidate.splitlines():
        stripped = line.strip()
        if not stripped:
            continue
        if _COMMENT_ONLY_LINE_RE.match(stripped):
            continue
        is_extern = _EXTERN_LINE_RE.match(stripped) is not None
        is_bare_prototype = (
            not is_extern
            and _BARE_PROTOTYPE_LINE_RE.match(stripped) is not None
            and not stripped.startswith("extern")
        )
        if is_extern or is_bare_prototype:
            names.update(_CALL_SYMBOL_RE.findall(stripped))
            continue
        break
    return names


def _missing_callee_declarations(
    function: str,
    candidate: str,
    baseline_source: str,
    already_declared: set[str],
) -> str:
    """Extra ``extern`` lines this one candidate needs beyond ``already_declared``.

    For every ``func_XXXXXXXX`` the candidate calls -- other than
    ``function`` itself, and other than a name ``already_declared`` already
    covers -- scan ``baseline_source`` (the whole owner file, pragma and
    all) for its real signature and reuse it verbatim.  A callee the scan
    finds nothing about is left alone: no default is guessed, so a probe
    against a genuinely undeclared symbol compiles (or fails) exactly as it
    always has (``synthesise only when nothing is found``, AGENTS.md Sec 5).
    A name already covered by ``already_declared`` never gets a second,
    possibly-conflicting declaration layered on top, whether or not that
    existing one agrees with what the scan would have found.
    """
    referenced = {name for name in _CALL_SYMBOL_RE.findall(candidate) if name != function}
    missing = sorted(referenced - already_declared)
    lines: list[str] = []
    for name in missing:
        signature = scan_source_for_callee_signature(baseline_source, name)
        if signature is None:
            continue
        lines.append(_as_extern_declaration(signature))
    return "\n".join(lines)


def _augment_blocks_with_callee_declarations(
    blocks: list[tuple[str, str]], prefix: str, baseline_source: str,
) -> list[tuple[str, str]]:
    """Prepend ``prefix`` and any needed synthesized callee declarations.

    Beyond the historical behaviour (prepend the shared ``declarations``
    block to every candidate, verbatim), this closes the fallback-prototype
    gap described in AGENTS.md Sec 5: for a callee neither the shared
    ``declarations`` block nor the candidate's own leading lines already
    declare, ``baseline_source`` is scanned for a real signature (a
    definition or prototype anywhere in the file, including further down
    than the pragma being replaced) and, when found, that exact signature is
    injected instead of leaving the callee to whatever the compiler's
    implicit-declaration default would otherwise produce.  Nothing changes
    for a callee already declared somewhere, nor for one the scan finds
    nothing about: this only ever adds a declaration it is confident is
    correct.
    """
    shared_declared = set(_CALL_SYMBOL_RE.findall(prefix))
    augmented: list[tuple[str, str]] = []
    for function, candidate in blocks:
        already_declared = (
            shared_declared | {function} | _candidate_declared_callee_names(candidate)
        )
        extra = _missing_callee_declarations(function, candidate, baseline_source, already_declared)
        pieces = [piece for piece in (prefix.rstrip("\n"), extra) if piece]
        new_prefix = "\n".join(pieces)
        if new_prefix:
            augmented.append((function, new_prefix + "\n" + candidate))
        else:
            augmented.append((function, candidate))
    return augmented


def _load_prior_attempt_history() -> dict[str, list[dict[str, object]]]:
    """Group every historical probe-stats attempt by function, oldest first.

    Reads ``variant_policy.default_stats_paths()`` (the active stats file
    plus any legacy file and rotated siblings of either) through
    ``probe_stats.iter_batches`` so each attempt keeps its batch's
    ``timestamp``.  Cheap and silent when no stats exist yet -- a fresh
    worktree has no ``disasm/probe-stats/`` -- since both of those already
    tolerate missing files by returning nothing.  Called once per batch
    (see ``_annotate_prior_attempts``), never per attempt.
    """
    history: dict[str, list[dict[str, object]]] = {}
    try:
        paths = variant_policy.default_stats_paths()
    except OSError:
        return history
    for batch in probe_stats.iter_batches(paths):
        attempts = batch.get("attempts")
        if not isinstance(attempts, list):
            continue
        timestamp = batch.get("timestamp")
        for attempt in attempts:
            if not isinstance(attempt, dict):
                continue
            function = attempt.get("function")
            if not isinstance(function, str) or not function:
                continue
            enriched = dict(attempt)
            enriched.setdefault("timestamp", timestamp)
            history.setdefault(function, []).append(enriched)
    return history


def _best_prior_attempt(prior: list[dict[str, object]]) -> dict[str, object] | None:
    """Return the highest-``similarity_score`` entry from ``prior``, summarized."""
    if not prior:
        return None

    def score_of(attempt: dict[str, object]) -> float:
        score = attempt.get("similarity_score")
        return float(score) if isinstance(score, (int, float)) else -1.0

    best = max(prior, key=score_of)
    return {
        "similarity_score": best.get("similarity_score"),
        # Older stats rows only carry the pre-rename ``exact_similarity_score``
        # field; a newer row's own ``raw_similarity_score`` takes priority.
        "raw_similarity_score": best.get("raw_similarity_score", best.get("exact_similarity_score")),
        "mismatch_kind": best.get("mismatch_kind"),
        "label": best.get("label"),
        "timestamp": best.get("timestamp"),
    }


def _futility_verdict(prior: list[dict[str, object]], best_prior: dict[str, object] | None) -> str | None:
    """Classify a function's prior-attempt history as futile to keep retrying.

    ``register-tie``: at least six prior attempts already sit at
    ``similarity_score >= 0.99`` with ``mismatch_kind ==
    "register_allocation_only"`` -- IDO's own register allocator, not the
    source shape, is the only remaining variable, so another source-shape
    variant will not close it (see the ``§4``/``§5`` register-tie entries in
    AGENTS.md, e.g. ``func_8130B91C``/``func_8130B95C``,
    ``func_8005C0B0``-family).  ``stuck``: at least fifteen prior attempts
    and the best of them is still below 0.9 similarity -- a bigger structural
    rewrite is needed, not another small variant.
    """
    register_tie_count = sum(
        1
        for attempt in prior
        if attempt.get("mismatch_kind") == "register_allocation_only"
        and isinstance(attempt.get("similarity_score"), (int, float))
        and attempt["similarity_score"] >= 0.99
    )
    if register_tie_count >= 6:
        return (
            f"register-tie: {register_tie_count} prior attempts at >=0.99 "
            "register_allocation_only — source-shape variants will not close this"
        )
    if len(prior) >= 15:
        best_score = best_prior.get("similarity_score") if best_prior else None
        if isinstance(best_score, (int, float)) and best_score < 0.9:
            return f"stuck: {len(prior)} attempts, best {best_score}"
    return None


def _annotate_prior_attempts(result: dict[str, object]) -> None:
    """Populate ``prior_attempts``/``best_prior``/``futility`` on every attempt.

    Loads the probe-stats history exactly once for the whole batch (never
    per attempt), then looks up each attempt's function in that one
    dictionary.  Also sets a batch-level ``result["futility_summary"]``
    (``function -> futility string``) for every function in this batch whose
    prior history is futile, so a caller can see the batch's futile
    functions without re-scanning every attempt.  A no-op, cheap either way,
    when the batch has no attempts or no stats history exists.
    """
    attempts = result.get("attempts")
    if not isinstance(attempts, list):
        result.setdefault("futility_summary", {})
        return
    history = _load_prior_attempt_history()
    summary: dict[str, str] = {}
    for attempt in attempts:
        if not isinstance(attempt, dict):
            continue
        function = attempt.get("function")
        if not isinstance(function, str) or not function:
            continue
        prior = history.get(function, [])
        best_prior = _best_prior_attempt(prior)
        futility = _futility_verdict(prior, best_prior)
        attempt["prior_attempts"] = len(prior)
        attempt["best_prior"] = best_prior
        attempt["futility"] = futility
        if futility is not None:
            summary[function] = futility
    result["futility_summary"] = summary


def _replace_candidate_text(source: str, function: str, candidate: str) -> str | None:
    pragma = re.compile(
        rf'^#pragma GLOBAL_ASM\("asm/us/nonmatchings/[^\"]+/{re.escape(function)}\.s"\)$',
        re.MULTILINE,
    )
    replacement, count = pragma.subn(candidate.rstrip("\n"), source, count=1)
    return replacement if count == 1 else None


def _remove_probe_outputs(object_path: Path) -> None:
    """Remove the temporary object and files produced alongside it."""
    for path in (
        object_path,
        object_path.with_suffix(".d"),
        object_path.with_suffix(".asmproc.d"),
        object_path.with_suffix(".s"),
        object_path.with_suffix(".bin"),
    ):
        path.unlink(missing_ok=True)
    # Each probe gets its own hidden build directory.  Remove it when the
    # compiler left no additional artifacts behind; never touch a normal
    # repository build directory.
    if object_path.parent.name.startswith(".pragma_probe_"):
        try:
            object_path.parent.rmdir()
        except OSError:
            pass


def _probe_one(
    source_path: Path,
    function: str,
    candidate: str,
    expected: bytes | None,
    expected_shape: dict[str, object] | None = None,
) -> dict[str, object]:
    """Compile one candidate in an isolated temporary source/object pair.

    ``expected_shape`` is the baseline object's link shape; when given, a
    ``.text`` match is additionally checked for section-layout and relocation
    drift and reports ``link_verified``.  Without it the result carries
    ``link_verified: None`` and stays on the sequential-gate path.
    """
    started = time.monotonic()
    result = _probe_one_uncounted(source_path, function, candidate, expected, expected_shape)
    result["probe_seconds"] = round(time.monotonic() - started, 3)
    return result


def _compile_diagnostic(
    output: str,
    tail_chars: int = 2000,
    focus: str | None = None,
) -> str:
    """Keep the actionable compiler error as well as the output tail.

    IDO often emits hundreds of warnings for the rest of a large fragment
    after a candidate has already failed.  Returning only the tail hides the
    first syntax/type error, which is the part needed to choose the next
    candidate spelling.  Preserve a small context window around every early
    error and append the tail, de-duplicating when they overlap.
    """
    if len(output) <= tail_chars:
        return output
    lines = output.splitlines()
    error_lines: set[int] = set()
    for index, line in enumerate(lines):
        if re.search(
            r"\b(?:error|fatal|undefined reference|failed to compile|syntax error)\b",
            line,
            re.IGNORECASE,
        ):
            error_lines.update(range(max(0, index - 2), min(len(lines), index + 3)))
        if focus and focus in line:
            error_lines.update(range(max(0, index - 3), min(len(lines), index + 4)))
    head = "\n".join(lines[index] for index in sorted(error_lines))
    tail = output[-tail_chars:]
    if not head or head in tail:
        return tail
    return f"{head}\n...\n{tail}"


def _probe_one_uncounted(
    source_path: Path,
    function: str,
    candidate: str,
    expected: bytes | None,
    expected_shape: dict[str, object] | None,
) -> dict[str, object]:
    baseline = source_path.read_text()
    replacement = _replace_candidate_text(baseline, function, candidate)
    if replacement is None:
        return {
            "status": "probe_unavailable",
            "probe_reason": "invalid_pragma",
        }

    repo_root = Path(__file__).resolve().parent.parent
    temporary_directory = tempfile.TemporaryDirectory(
        prefix=".pragma_probe_", dir=_probe_root(repo_root)
    )
    try:
        directory = Path(temporary_directory.name)
        temporary_source = directory / source_path.name
        temporary_source.write_text(replacement)
        result, object_path, output = _make_object(temporary_source, capture=True)
        try:
            if result != 0:
                return {
                    "status": "compile_failed",
                    "exit_code": result,
                    "diagnostic": _compile_diagnostic(output, focus=function),
                }
            # The assembler symbol size can include alignment nops while the
            # compiler's relocatable symbol size often stops at the delay
            # slot. Compare the candidate over the baseline owner's span so
            # alignment padding is validated instead of causing a false
            # probe rejection. The full ROM gate remains authoritative.
            if expected is None:
                return {
                    "status": "probe_unavailable",
                    "probe_reason": "missing_function_bytes",
                }
            actual_symbol_size, actual_symbol, actual = _function_byte_views(
                object_path, function, len(expected)
            )
            if actual_symbol is None:
                return {
                    "status": "probe_unavailable",
                    "probe_reason": "missing_function_bytes",
                }
            comparison_span_complete = actual is not None
            if actual is None:
                actual = actual_symbol
            if not comparison_span_complete or actual != expected:
                diagnostic = {
                    "status": "probe_rejected",
                    "probe_reason": "function_bytes_differ",
                    "comparison_span_size": len(actual),
                    "comparison_span_complete": comparison_span_complete,
                }
                diagnostic.update(
                    _function_mismatch_details(
                        object_path,
                        function,
                        expected,
                        actual_symbol,
                        actual_symbol_size=actual_symbol_size,
                    )
                )
                return diagnostic
            match: dict[str, object] = {"status": "probe_match", "link_verified": None}
            if expected_shape is not None:
                actual_shape = _object_link_shape(object_path)
                expected_span = _shape_symbol(expected_shape, function)
                actual_span = (
                    _shape_symbol(actual_shape, function) if actual_shape is not None else None
                )
                verdict = _compare_link_shape(
                    expected_shape, actual_shape, expected_span, actual_span
                )
                if verdict.get("link_mismatch") == "section_layout_drift":
                    # Definitive: the candidate adds or resizes an allocatable
                    # section, so the linked ROM cannot be byte-identical even
                    # though the instruction bytes are.
                    diagnostic = {
                        "status": "probe_rejected",
                        "probe_reason": "section_layout_drift",
                        "comparison_span_size": len(actual),
                        "comparison_span_complete": comparison_span_complete,
                    }
                    diagnostic.update(
                        _function_mismatch_details(
                            object_path,
                            function,
                            expected,
                            actual_symbol,
                            actual_symbol_size=actual_symbol_size,
                        )
                    )
                    diagnostic["mismatch_kind"] = "section_layout_drift"
                    if isinstance(diagnostic.get("diagnostic"), str):
                        # Keep the human-readable summary's mismatch_kind in sync
                        # with the definitive section_layout_drift override above.
                        diagnostic["diagnostic"] = re.sub(
                            r"mismatch_kind=\S+",
                            "mismatch_kind=section_layout_drift",
                            diagnostic["diagnostic"],
                            count=1,
                        )
                    diagnostic.update(verdict)
                    return diagnostic
                match.update(verdict)
            return match
        finally:
            _remove_probe_outputs(object_path)
    finally:
        temporary_directory.cleanup()


def _shape_symbol(shape: dict[str, object] | None, function: str) -> tuple[int, int] | None:
    """Return ``(offset, size)`` of a defined ``.text`` function from a link shape."""
    if shape is None:
        return None
    symbols = shape["symbols"]
    section_names = shape["section_names"]
    assert isinstance(symbols, dict) and isinstance(section_names, dict)
    for symbol in symbols.values():
        if symbol["name"] != function or symbol["type"] != "FUNC":
            continue
        ndx = str(symbol["ndx"])
        if ndx.isdigit() and section_names.get(int(ndx)) == ".text":
            return int(symbol["value"]), max(int(symbol.get("size") or 0), 4)
    return None


def probe_candidates(
    source_path: Path,
    blocks: list[tuple[str, str]],
    workers: int | None = None,
) -> list[dict[str, object]]:
    """Parallel-filter candidates without modifying the live source.

    This is only a cheap object-level filter.  A ``probe_match`` is still sent
    through the sequential full linker/ROM comparison before it can be kept.
    """
    results: list[dict[str, object]] = [
        {"index": index, "function": function, "status": "probe_unavailable"}
        for index, (function, _) in enumerate(blocks)
    ]
    try:
        _, baseline_object = source_object_path(source_path)
    except ValueError:
        for result in results:
            result["probe_reason"] = "baseline_object_unavailable"
        return results

    if not _ensure_baseline_object(source_path, baseline_object):
        for result in results:
            result["probe_reason"] = "baseline_object_unavailable"
        return results
    expected = {
        function: _function_bytes(baseline_object, function)
        for function in {function for function, _ in blocks}
    }
    for index, (function, _) in enumerate(blocks):
        if expected[function] is None:
            results[index]["probe_reason"] = "missing_function_bytes"
    # Read the baseline link shape once per batch; every probe hit compares
    # against it so verified matches can share one combined ROM gate.
    expected_shape = (
        _object_link_shape(baseline_object)
        if any(value is not None for value in expected.values())
        else None
    )

    workers = _resolve_probe_workers(workers, len(blocks))
    with ThreadPoolExecutor(max_workers=workers) as executor:
        futures = {
            executor.submit(
                _probe_one, source_path, function, candidate, expected[function], expected_shape
            ): index
            for index, (function, candidate) in enumerate(blocks)
            if expected[function] is not None
        }
        for future in as_completed(futures):
            index = futures[future]
            try:
                result = future.result()
            except Exception as error:  # pragma: no cover - defensive worker boundary
                result = {
                    "status": "probe_unavailable",
                    "probe_reason": "probe_error",
                    "diagnostic": str(error),
                }
            results[index].update(result)
            results[index]["index"] = index
            results[index]["function"] = blocks[index][0]
    return results


_BASELINE_OBJECT_STATE: dict[Path, tuple[int, int]] = {}
_BASELINE_OBJECT_LOCK = threading.Lock()


def _ensure_baseline_object(source_path: Path, object_path: Path) -> bool:
    """Rebuild the tracked baseline object unless this process already did so.

    Every probe pass used to pay a full ``make`` for the baseline object even
    when nothing had changed since the previous pass (a sweep runs two probe
    passes per source).  The object is considered fresh only when both the
    source and object mtimes still equal the values recorded after the last
    successful rebuild in this process, so any live-source edit (ours or
    another process's) invalidates the entry.
    """
    key = source_path.resolve()
    try:
        current = (source_path.stat().st_mtime_ns, object_path.stat().st_mtime_ns)
    except OSError:
        current = None
    with _BASELINE_OBJECT_LOCK:
        if current is not None and _BASELINE_OBJECT_STATE.get(key) == current:
            return True
    if rebuild_source_object(source_path) != 0:
        with _BASELINE_OBJECT_LOCK:
            _BASELINE_OBJECT_STATE.pop(key, None)
        return False
    try:
        fresh = (source_path.stat().st_mtime_ns, object_path.stat().st_mtime_ns)
    except OSError:
        return True
    with _BASELINE_OBJECT_LOCK:
        _BASELINE_OBJECT_STATE[key] = fresh
    return True


def _resolve_probe_workers(workers: int | None, candidate_count: int) -> int:
    if workers is None:
        try:
            workers = int(os.environ.get("PRAGMA_PROBE_WORKERS", "10"))
        except ValueError:
            workers = 10
    return max(1, min(workers, candidate_count or 1))


def _print_normalized_only_match_warnings(attempts: list[dict[str, object]]) -> None:
    """Print a console warning for every ``normalized_only_match`` attempt.

    ``similarity_score`` alone can read as a clean match (>= 0.99, even
    1.0) while ``raw_similarity_score`` -- unaffected by register
    normalisation -- says otherwise; this is exactly the class of result an
    agent trusted this week (a 1.0 with ``raw_similarity_score`` 0.63 and
    values swapped between struct fields, AGENTS.md Sec 5).  Both the
    sequential and the combined gate share this one exit path
    (``finish()``), so the warning surfaces regardless of which gate mode a
    batch used.
    """
    for attempt in attempts:
        if not attempt.get("normalized_only_match"):
            continue
        function = attempt.get("function", "<unknown>")
        similarity_score = attempt.get("similarity_score")
        raw_similarity_score = attempt.get("raw_similarity_score")
        print(
            f"WARNING {function}: similarity_score={similarity_score} but "
            f"raw_similarity_score={raw_similarity_score} -- normalised score is "
            "hiding a register/field difference; check assembly_diff before trusting it",
            file=sys.stderr,
        )


def _rank_probe_rejections(
    attempts: list[dict[str, object]],
    blocks: list[tuple[str, str]],
) -> dict[str, list[dict[str, object]]]:
    """Rank rejected variants by normalized instruction similarity.

    Candidate order is preserved in ``attempts`` because it controls which
    probe hit reaches the sequential gate first.  Rankings are an additional
    diagnostic view for hill-climbing difficult functions.
    """
    grouped: dict[str, list[tuple[int, dict[str, object]]]] = {}
    for index, attempt in enumerate(attempts):
        if attempt.get("status") != "probe_rejected":
            continue
        score = attempt.get("similarity_score")
        if not isinstance(score, (int, float)):
            continue
        function = blocks[index][0]
        grouped.setdefault(function, []).append((index, attempt))

    rankings: dict[str, list[dict[str, object]]] = {}
    for function, rows in grouped.items():
        rows.sort(
            key=lambda row: (
                float(row[1].get("similarity_score", 0.0)),
                float(row[1].get("raw_similarity_score", 0.0)),
            ),
            reverse=True,
        )
        ranked: list[dict[str, object]] = []
        for rank, (index, attempt) in enumerate(rows, 1):
            attempt["similarity_rank"] = rank
            attempt["similarity_total"] = len(rows)
            ranked.append({
                "index": index,
                "label": attempt.get("label"),
                "similarity_score": attempt.get("similarity_score"),
                "matched_instructions": attempt.get("matched_instructions"),
                "total_instructions": attempt.get("total_instructions"),
                "raw_similarity_score": attempt.get("raw_similarity_score"),
                "first_diff_instruction": attempt.get("first_diff_instruction"),
                "mismatch_kind": attempt.get("mismatch_kind"),
            })
        rankings[function] = ranked
    return rankings


def _full_gate_eligible(attempt: dict[str, object]) -> bool:
    """Return whether this specific attempt may use the sequential fallback."""
    if attempt.get("status") == "probe_match":
        return True
    return (
        attempt.get("status") == "probe_unavailable"
        and attempt.get("probe_reason")
        in {"baseline_object_unavailable", "missing_function_bytes"}
    )


def _install_incrementally(
    source_path: Path,
    baseline: str,
    prefix: str,
    winners: dict[str, str],
    attempts: list[dict[str, object]],
    winner_indices: dict[str, int],
    timing: dict[str, object],
) -> tuple[dict[str, str], bool]:
    """Install winners cumulatively, dropping any that conflict with an earlier one.

    Each winner is layered on top of the previously *kept* text and the
    object is rebuilt; a winner whose addition breaks the compile (for
    example a duplicate helper prototype two m2c drafts disagree on) is
    dropped and the source is restored to the last good state instead of
    aborting the whole batch.  A dropped winner's attempt is finalized here
    as ``combined_compile_failed`` and is never retried alone by the
    caller: it already compiles in isolation (that is how it became a
    winner), so re-gating it separately would just re-accept and lose it
    again on the next combined install.

    Returns ``(kept, invalid_pragma)``.  ``kept`` preserves ``winners``
    order and always matches what ``source_path`` holds when this
    returns.  ``invalid_pragma`` means a winner's pragma no longer exists
    in the tree -- a structural problem no amount of dropping other
    winners can repair; ``source_path`` is left at the last good state and
    the caller must revert the whole batch.
    """
    combined = baseline
    kept: dict[str, str] = {}
    for install_index, (function, candidate) in enumerate(winners.items()):
        text = candidate
        if prefix and install_index and text.startswith(prefix):
            text = text[len(prefix):]
        pragma = re.compile(
            rf'^#pragma GLOBAL_ASM\("asm/us/nonmatchings/[^"]+/{re.escape(function)}\.s"\)$',
            re.MULTILINE,
        )
        candidate_text, count = pragma.subn(text.rstrip("\n"), combined, count=1)
        if count != 1:
            source_path.write_text(combined)
            os.utime(source_path, None)
            return kept, True
        source_path.write_text(candidate_text)
        os.utime(source_path, None)
        timing["install_compiles"] = int(timing.get("install_compiles", 0)) + 1
        if rebuild_source_object(source_path) == 0:
            combined = candidate_text
            kept[function] = candidate
            continue
        print(f"DROPPED {function}: conflicts with an earlier winner in this batch")
        index = winner_indices.get(function)
        if index is not None:
            attempt = attempts[index]
            attempt.update({
                "probe_status": attempt.get("probe_status", attempt.get("status")),
                "status": "combined_compile_failed",
                "reason": "conflicts with an earlier winner in this batch",
            })
        source_path.write_text(combined)
        os.utime(source_path, None)
    return kept, False


def _record_probe_stats(
    source_path: Path,
    attempts: list[dict[str, object]],
    labels: list[str | None] | None,
    blocks: list[tuple[str, str]] | None = None,
    declarations: str | None = None,
    timing: dict[str, object] | None = None,
    batch_status: str | None = None,
    families: dict[str, str] | None = None,
) -> None:
    """Append one JSONL probe-outcome batch for family-level tuning.

    Delegates the active file's location, rotation, and row shaping to
    ``tools/probe_stats.py``: see ``probe_stats.stats_path`` for the
    ``PRAGMA_PROBE_STATS`` contract (unset -> new default location outside
    ``disasm/build/``, empty string -> disabled) and
    ``probe_stats.shape_attempt_row`` for what is stripped/truncated before a
    row is written. The transaction lock surrounds this call, making one
    batch append atomic across runners. ``families`` (``function -> family``)
    and the module-level ``family_lookup`` callable are both optional,
    best-effort sources for a per-attempt ``family`` when the attempt dict
    does not already carry one -- see ``sweep_targets.py``, which sets
    ``family_lookup`` from the listing it already has.
    """
    try:
        counts: dict[str, int] = {}
        rows: list[dict[str, object]] = []
        for index, attempt in enumerate(attempts):
            label = (
                labels[index]
                if labels is not None and index < len(labels)
                else attempt.get("label")
            )
            row = {
                "index": index,
                "function": attempt.get("function"),
                "family": attempt.get("family"),
                "label": label,
                "status": attempt.get("status"),
                "probe_status": attempt.get("probe_status"),
                "probe_reason": attempt.get("probe_reason"),
                "mismatch_kind": attempt.get("mismatch_kind"),
                "expected_size": attempt.get("expected_size"),
                "actual_size": attempt.get("actual_size"),
                "first_diff_offset": attempt.get("first_diff_offset"),
                "first_diff_instruction": attempt.get("first_diff_instruction"),
                "expected_instruction": attempt.get("expected_instruction"),
                "actual_instruction": attempt.get("actual_instruction"),
                "expected_instruction_text": attempt.get("expected_instruction_text"),
                "actual_instruction_text": attempt.get("actual_instruction_text"),
                "similarity_score": attempt.get("similarity_score"),
                "exact_similarity_score": attempt.get("exact_similarity_score"),
                "raw_similarity_score": attempt.get("raw_similarity_score"),
                "normalized_only_match": attempt.get("normalized_only_match"),
                "similarity_rank": attempt.get("similarity_rank"),
                "assembly_diff": attempt.get("assembly_diff"),
                "assembly_diff_truncated": attempt.get("assembly_diff_truncated"),
                "permute_score": attempt.get("permute_score"),
                "permute_budget_seconds": attempt.get("permute_budget_seconds"),
                "permute_output_count": attempt.get("permute_output_count"),
                "permute_already_matching": attempt.get("permute_already_matching"),
                "permute_error": attempt.get("permute_error"),
                "link_verified": attempt.get("link_verified"),
                "link_mismatch": attempt.get("link_mismatch"),
                "probe_seconds": attempt.get("probe_seconds"),
                "diagnostic": attempt.get("diagnostic"),
                "declarations": declarations,
                "candidate": (
                    blocks[index][1]
                    if blocks is not None and index < len(blocks)
                    else None
                ),
            }
            rows.append(row)
            key = f"{label or 'unlabeled'}:{attempt.get('status', 'unknown')}"
            counts[key] = counts.get(key, 0) + 1
        batch = probe_stats.new_batch_row(
            source_path.as_posix(),
            rows,
            counts=counts,
            timing=timing,
            batch_status=batch_status,
            families=families,
            family_lookup=family_lookup,
        )
        probe_stats.append_batch(batch)
    except OSError:
        # Metrics must never turn a valid source transaction into a failure.
        return


@contextmanager
def _candidate_transaction_lock():
    """Serialize live-source/full-ROM transactions across MCP processes.

    Isolated object probes are still parallel within one request, but the
    source rewrite, link, compare, and restore phases must not overlap with a
    request from another agent.  Without this process-wide lock, one agent can
    restore a rejected candidate while another agent is running its full gate,
    producing a false combined-compare rejection.
    """
    repo_root = Path(__file__).resolve().parent.parent
    repo_key = hashlib.sha256(str(repo_root).encode()).hexdigest()[:16]
    lock_name = f"pokemon_stadium_pragma_runner_{repo_key}.lock"
    lock_path = Path(tempfile.gettempdir()) / lock_name
    with lock_path.open("a+") as handle:
        if fcntl is not None:
            fcntl.flock(handle.fileno(), fcntl.LOCK_EX)
        try:
            yield
        finally:
            if fcntl is not None:
                fcntl.flock(handle.fileno(), fcntl.LOCK_UN)


def _claim_or_refuse(source_path: Path) -> str | None:
    """Claim ``source_path`` for this runner process, or explain a refusal.

    Called once, at the install boundary in ``_try_candidates_detailed_unlocked``
    -- right before a gated batch's first write into the live source tree,
    since a refusal decided after that write would be too late to prevent it.
    A batch that never reaches this point (``gate=False``, i.e. a probe-only
    batch) never claims anything, matching AGENTS.md's "probe-only batches
    do not claim" rule.

    Returns ``None`` when this process now holds (or already held) the
    claim; otherwise a diagnostic string naming the live holder, and the
    caller must refuse the install rather than write anything. The first
    call for a given path in this process claims it; every later call for
    the same path just touches (extends) that claim, per
    ``tools/file_claims.py``.
    """
    import file_claims

    owner = file_claims.current_owner()
    key = file_claims.registry_key(source_path)
    if key in _CLAIMED_SOURCE_PATHS:
        file_claims.touch(source_path, owner=owner)
        return None
    if file_claims.claim(source_path, owner=owner):
        _CLAIMED_SOURCE_PATHS.add(key)
        return None
    existing = file_claims.holder(source_path)
    holder_owner = existing.get("owner") if existing else "unknown"
    return f"{source_path} is claimed by {holder_owner}"


# Paths this process has already claimed via _claim_or_refuse -- later calls
# for the same path touch instead of re-claiming (see its docstring).
_CLAIMED_SOURCE_PATHS: set[str] = set()


def try_candidates_detailed(
    source_path: Path,
    blocks: list[tuple[str, str]],
    *,
    probe_workers: int | None = None,
    labels: list[str | None] | None = None,
    gate: bool = True,
    declarations: str | None = None,
    families: dict[str, str] | None = None,
) -> dict[str, object]:
    """Run one candidate transaction while excluding other MCP processes.

    ``declarations`` is a block of shared ``extern``/prototype lines that is
    prepended to every candidate for probing and installed once, ahead of the
    first accepted replacement, so variants need not repeat their externs.
    ``families`` (``function -> family``) is an optional, best-effort mapping
    forwarded to the stats writer for owners whose attempt dict does not
    already carry a ``family`` key; see ``_record_probe_stats``.
    """
    with _candidate_transaction_lock():
        result = _try_candidates_detailed_unlocked(
            source_path,
            blocks,
            probe_workers=probe_workers,
            labels=labels,
            gate=gate,
            declarations=declarations,
        )
        _annotate_prior_attempts(result)
        batch_status = result.get("batch_status")
        _record_probe_stats(
            source_path,
            result.get("attempts", []),
            labels,
            blocks,
            declarations,
            timing=result.get("timing") if isinstance(result.get("timing"), dict) else None,
            batch_status=batch_status if isinstance(batch_status, str) else None,
            families=families,
        )
        # Opt-in: rename a just-accepted winner immediately if it already has
        # an evidence-backed name and no other pragma owner (tools/name_decompiled.py).
        if os.environ.get("PRAGMA_NAME_ON_ACCEPT") == "1" and result.get("status") == 0 and result.get("accepted"):
            try:
                import name_decompiled
                name_decompiled.name_after_accept(list(result["accepted"]), quiet=False)
            except Exception as exc:
                print(f"PRAGMA_NAME_ON_ACCEPT: name_after_accept failed: {exc}", file=sys.stderr)
        return result


def _try_candidates_detailed_unlocked(
    source_path: Path,
    blocks: list[tuple[str, str]],
    *,
    probe_workers: int | None = None,
    labels: list[str | None] | None = None,
    gate: bool = True,
    declarations: str | None = None,
) -> dict[str, object]:
    """Try candidates and retain the first winner per function.

    Candidates are first compiled in isolated temporary source/object paths.
    Only candidates whose relocatable function bytes equal the baseline are
    sent through the sequential full linker/ROM comparison.  ``accepted`` is
    populated only after that final combined comparison also succeeds.
    """
    repo_root = Path(__file__).resolve().parent.parent
    baseline = source_path.read_text()
    prefix = _declaration_prefix(declarations)
    blocks = _augment_blocks_with_callee_declarations(blocks, prefix, baseline)
    accepted: dict[str, str] = {}
    accepted_indices: dict[str, int] = {}
    _cleanup_stale_probe_dirs(repo_root)
    probe_workers = _resolve_probe_workers(probe_workers, len(blocks))
    started = time.monotonic()
    attempts = probe_candidates(source_path, blocks, workers=probe_workers)
    probe_seconds = time.monotonic() - started
    if labels is not None:
        for index, attempt in enumerate(attempts):
            if index < len(labels) and labels[index]:
                attempt["label"] = labels[index]

    rejection_rankings = _rank_probe_rejections(attempts, blocks)
    timing: dict[str, object] = {
        "probe_seconds": round(probe_seconds, 3),
        "gate_seconds": 0.0,
        "gate_runs": 0,
        "gate_mode": None,
        "install_compiles": 0,
    }

    def finish(payload: dict[str, object]) -> dict[str, object]:
        timing["total_seconds"] = round(time.monotonic() - started, 3)
        payload["timing"] = dict(timing)
        payload.setdefault("rejected_ranking", rejection_rankings)
        payload.setdefault("probe_workers", probe_workers)
        _print_normalized_only_match_warnings(attempts)
        return payload

    if not gate:
        probe_matches = [
            attempt["function"]
            for attempt in attempts
            if attempt.get("status") == "probe_match"
        ]
        return finish({
            "status": 0 if probe_matches else 1,
            "accepted": [],
            "probe_matches": probe_matches,
            "attempts": attempts,
            "batch_status": "probe_only",
            "gate": False,
        })

    claim_refusal = _claim_or_refuse(source_path)
    if claim_refusal is not None:
        return finish({
            "status": 2,
            "accepted": [],
            "attempts": attempts,
            "batch_status": "file_claimed_by_other",
            "claim_diagnostic": claim_refusal,
            "gate": True,
        })

    gate_started = time.monotonic()

    def run_full_gate() -> int:
        timing["gate_runs"] = int(timing["gate_runs"]) + 1
        return compare_current_tree(repo_root)

    def restore_baseline() -> None:
        source_path.write_text(baseline)
        os.utime(source_path, None)
        rebuild_source_object(source_path)

    def sequential_attempt(index: int) -> None:
        """Gate one candidate alone against the baseline tree (historical path)."""
        function, candidate = blocks[index]
        attempt = attempts[index]
        source_path.write_text(baseline)
        os.utime(source_path, None)
        rebuild_source_object(source_path)
        timing["gate_runs"] = int(timing["gate_runs"]) + 1
        result, outcome = _try_candidate_detailed(source_path, function, candidate)
        attempt.update({
            "status": outcome,
            "exit_code": result,
            "probe_status": attempt.get("probe_status", attempt.get("status")),
        })
        if result == 0:
            accepted[function] = candidate
            accepted_indices[function] = index

    # Candidate order still decides the first winner per function.  A
    # link-verified probe hit (identical function bytes, section layout, and
    # relocations) is deferred to one combined ROM gate; an unverified hit or
    # a baseline-unavailable fallback keeps the historical sequential gate.
    # A missing symbol in one owner must not send every other function's
    # rejected variants through the expensive full gate.
    pending: dict[str, int] = {}
    deferred: dict[str, list[int]] = {}
    for index, attempt in enumerate(attempts):
        if not _full_gate_eligible(attempt):
            continue
        function = blocks[index][0]
        if function in accepted:
            print(f"SKIPPED {function}: earlier candidate accepted")
            attempt.update({
                "probe_status": attempt.get("status"),
                "status": "skipped",
                "reason": "earlier candidate accepted",
            })
            continue
        if function in pending:
            # Later eligible variants stay untried until the combined gate
            # has judged the earlier hit; they are only skipped once a
            # winner exists, exactly as in the sequential runner.
            deferred.setdefault(function, []).append(index)
            continue
        if attempt.get("status") == "probe_match" and attempt.get("link_verified") is True:
            pending[function] = index
            continue
        sequential_attempt(index)

    gate_mode = "sequential"
    verified_combined_text: str | None = None
    if pending:
        gate_mode = "combined"
        winners = dict(accepted)
        winners.update({function: blocks[index][1] for function, index in pending.items()})
        winner_indices = dict(accepted_indices)
        winner_indices.update(pending)
        kept, invalid_pragma = _install_incrementally(
            source_path, baseline, prefix, winners, attempts, winner_indices, timing
        )
        if invalid_pragma:
            restore_baseline()
            timing["gate_seconds"] = round(time.monotonic() - gate_started, 3)
            timing["gate_mode"] = gate_mode
            return finish({
                "status": 2,
                "accepted": [],
                "attempts": attempts,
                "batch_status": "invalid_pragma",
                "gate": True,
            })
        kept_pending = {function: index for function, index in pending.items() if function in kept}
        # A sequential winner dropped for a conflict is no longer installed;
        # it must not survive in ``accepted`` or the result would claim it.
        for function in list(accepted):
            if function not in kept:
                accepted.pop(function)
                accepted_indices.pop(function, None)
        if kept:
            print(
                f"checking {len(kept)} candidate(s) together "
                f"({len(kept_pending)} link-verified)"
            )
            result = run_full_gate()
            if result == 0:
                verified_combined_text = source_path.read_text()
                for function, index in kept_pending.items():
                    attempt = attempts[index]
                    attempt.update({
                        "probe_status": attempt.get("probe_status", attempt.get("status")),
                        "status": "accepted",
                        "exit_code": 0,
                    })
                    accepted[function] = blocks[index][1]
                    accepted_indices[function] = index
            else:
                # The combined tree compiled but did not link byte-identically:
                # fall back to the historical per-function gate for the
                # surviving (non-conflicting) verified hits so one bad
                # candidate cannot sink the rest of the batch.  Winners
                # already dropped as ``combined_compile_failed`` above are
                # never retried alone here -- they would just be re-accepted
                # and lost again on the next combined install.
                gate_mode = "combined_then_sequential"
                print("combined candidate batch rejected: gating link-verified hits individually")
                for function, index in list(pending.items()):
                    if function not in kept_pending:
                        continue
                    sequential_attempt(index)
                    for later_index in deferred.get(function, []):
                        if function in accepted:
                            break
                        sequential_attempt(later_index)
        pending.clear()

    # Probes are intentionally parallel, so variants after a winner may have
    # already compiled.  Report them as skipped for the same user-facing
    # semantics as the old sequential runner while retaining their probe
    # outcome in ``probe_status``.
    for index, (function, _) in enumerate(blocks):
        winner_index = accepted_indices.get(function)
        if winner_index is not None and index > winner_index:
            attempt = attempts[index]
            if attempt["status"] != "skipped":
                attempt.update({
                    "probe_status": attempt.get("status"),
                    "status": "skipped",
                    "reason": "earlier candidate accepted",
                })

    timing["gate_mode"] = gate_mode

    def gated_payload(status: int, batch_status: str, names: list[str]) -> dict[str, object]:
        if not names and batch_status in {
            "combined_compile_failed", "combined_compare_rejected", "invalid_pragma",
        }:
            # The batch ends with nothing installed: any attempt still
            # marked ``accepted`` (an individually-gated sequential winner
            # whose replacement was just reverted from the tree) must not
            # keep claiming that status, or the stats would record
            # ``accepted`` for a function that no longer owns a pragma.
            for attempt in attempts:
                if attempt.get("status") == "accepted":
                    attempt["status"] = batch_status
        timing["gate_seconds"] = round(time.monotonic() - gate_started, 3)
        return finish({
            "status": status,
            "accepted": names,
            "attempts": attempts,
            "batch_status": batch_status,
            "gate": True,
        })

    # No probe hit means no source edit was made and no linker invocation is
    # necessary.  This is the main speedup for large rejected candidate sets.
    if not accepted:
        if int(timing["gate_runs"]) > 0:
            # A sequential attempt left the live source at the baseline, but
            # its restore path may have been interrupted; make it explicit.
            restore_baseline()
            print("no candidate accepted")
        return gated_payload(1, "no_candidate_accepted", [])

    if verified_combined_text is not None and source_path.read_text() == verified_combined_text:
        # The combined tree is exactly what the ROM gate just verified.
        return gated_payload(0, "accepted", list(kept))

    final_indices = dict(accepted_indices)
    final_kept, invalid_pragma = _install_incrementally(
        source_path, baseline, prefix, accepted, attempts, final_indices, timing
    )
    if invalid_pragma:
        restore_baseline()
        return gated_payload(2, "invalid_pragma", [])
    if not final_kept:
        restore_baseline()
        return gated_payload(2, "combined_compile_failed", [])
    if len(final_kept) >= 2:
        # Each surviving winner was verified against the baseline alone (or,
        # for a link-verified hit, in the combined gate above); only their
        # union still needs one fresh combined ROM gate.  A single surviving
        # winner was already gated in exactly this source text.
        print(f"checking {len(final_kept)} accepted candidate(s) together")
        result = run_full_gate()
        if result != 0:
            restore_baseline()
            print("combined candidate batch rejected: restored baseline")
            return gated_payload(result, "combined_compare_rejected", [])
    return gated_payload(0, "accepted", list(final_kept))


def try_candidates(source_path: Path, blocks: list[tuple[str, str]]) -> tuple[int, list[str]]:
    """Compatibility wrapper returning the historical two-tuple."""
    result = try_candidates_detailed(source_path, blocks)
    return int(result["status"]), list(result["accepted"])


def main() -> int:
    keep_candidate = "--keep-candidate" in sys.argv
    args = [arg for arg in sys.argv[1:] if arg != "--keep-candidate"]

    if len(args) == 3 and args[0] == "--bundle":
        source_path = Path(args[1])
        bundle_path = Path(args[2])
        bundle = bundle_path.read_text()
        blocks = re.findall(
            r"/\*\s*candidate:\s*([A-Za-z_]\w*)\s*\*/(.*?)/\*\s*end candidate\s*\*/",
            bundle,
            flags=re.DOTALL,
        )
        if not blocks:
            print("candidate bundle contains no candidate blocks", file=sys.stderr)
            return 2
        result, _ = try_candidates(source_path, blocks)
        if not keep_candidate:
            bundle_path.unlink(missing_ok=True)
        return result

    if len(args) == 3:
        source_path = Path(args[0])
        function = args[1]
        candidate_path = Path(args[2])
        result = try_candidate(source_path, function, candidate_path.read_text())
        if not keep_candidate:
            candidate_path.unlink(missing_ok=True)
        return result

    print(__doc__.strip(), file=sys.stderr)
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
