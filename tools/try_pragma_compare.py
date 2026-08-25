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
    return details


def _declaration_prefix(declarations: str | None) -> str:
    """Normalize a shared declarations block into a candidate prefix."""
    if declarations is None:
        return ""
    body = declarations.strip()
    return body + "\n" if body else ""


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
) -> dict[str, object]:
    """Compile one candidate in an isolated temporary source/object pair."""
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
                    "diagnostic": output[-2000:],
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
            return {"status": "probe_match"}
        finally:
            _remove_probe_outputs(object_path)
    finally:
        temporary_directory.cleanup()


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

    if rebuild_source_object(source_path) != 0:
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

    workers = _resolve_probe_workers(workers, len(blocks))
    with ThreadPoolExecutor(max_workers=workers) as executor:
        futures = {
            executor.submit(
                _probe_one, source_path, function, candidate, expected[function]
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


def _resolve_probe_workers(workers: int | None, candidate_count: int) -> int:
    if workers is None:
        try:
            workers = int(os.environ.get("PRAGMA_PROBE_WORKERS", "10"))
        except ValueError:
            workers = 10
    return max(1, min(workers, candidate_count or 1))


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


def _record_probe_stats(
    source_path: Path,
    attempts: list[dict[str, object]],
    labels: list[str | None] | None,
    blocks: list[tuple[str, str]] | None = None,
) -> None:
    """Append JSONL probe outcomes for family-level tuning.

    The default file is ignored build output; set ``PRAGMA_PROBE_STATS`` to
    override it, or to an empty string to disable metrics. The transaction lock
    surrounds this call, making one JSON object append atomic across runners.
    """
    stats_path_value = os.environ.get("PRAGMA_PROBE_STATS")
    if stats_path_value == "":
        return
    if stats_path_value is None:
        stats_path = (
            Path(__file__).resolve().parent.parent
            / "disasm"
            / "build"
            / "probe-stats.jsonl"
        )
    else:
        stats_path = Path(stats_path_value).expanduser()
    try:
        stats_path.parent.mkdir(parents=True, exist_ok=True)
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
                "label": label,
                "status": attempt.get("status"),
                "probe_status": attempt.get("probe_status"),
                "probe_reason": attempt.get("probe_reason"),
                "mismatch_kind": attempt.get("mismatch_kind"),
                "expected_size": attempt.get("expected_size"),
                "actual_size": attempt.get("actual_size"),
                "similarity_score": attempt.get("similarity_score"),
                "exact_similarity_score": attempt.get("exact_similarity_score"),
                "similarity_rank": attempt.get("similarity_rank"),
                "candidate": (
                    blocks[index][1]
                    if blocks is not None and index < len(blocks)
                    else None
                ),
            }
            rows.append(row)
            key = f"{label or 'unlabeled'}:{attempt.get('status', 'unknown')}"
            counts[key] = counts.get(key, 0) + 1
        with stats_path.open("a", encoding="utf-8") as handle:
            handle.write(json.dumps({
                "source": source_path.as_posix(),
                "counts": counts,
                "attempts": rows,
            }, sort_keys=True) + "\n")
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


def try_candidates_detailed(
    source_path: Path,
    blocks: list[tuple[str, str]],
    *,
    probe_workers: int | None = None,
    labels: list[str | None] | None = None,
    gate: bool = True,
    declarations: str | None = None,
) -> dict[str, object]:
    """Run one candidate transaction while excluding other MCP processes.

    ``declarations`` is a block of shared ``extern``/prototype lines that is
    prepended to every candidate for probing and installed once, ahead of the
    first accepted replacement, so variants need not repeat their externs.
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
        _record_probe_stats(
            source_path,
            result.get("attempts", []),
            labels,
            blocks,
        )
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
    if prefix:
        blocks = [(function, prefix + candidate) for function, candidate in blocks]
    accepted: dict[str, str] = {}
    accepted_indices: dict[str, int] = {}
    _cleanup_stale_probe_dirs(repo_root)
    probe_workers = _resolve_probe_workers(probe_workers, len(blocks))
    attempts = probe_candidates(source_path, blocks, workers=probe_workers)
    if labels is not None:
        for index, attempt in enumerate(attempts):
            if index < len(labels) and labels[index]:
                attempt["label"] = labels[index]

    rejection_rankings = _rank_probe_rejections(attempts, blocks)

    if not gate:
        probe_matches = [
            attempt["function"]
            for attempt in attempts
            if attempt.get("status") == "probe_match"
        ]
        return {
            "status": 0 if probe_matches else 1,
            "accepted": [],
            "probe_matches": probe_matches,
            "attempts": attempts,
            "rejected_ranking": rejection_rankings,
            "batch_status": "probe_only",
            "probe_workers": probe_workers,
            "gate": False,
        }

    # Fall back only for the affected function when its baseline bytes cannot
    # be inspected.  A missing symbol in one owner must not send every other
    # function's rejected variants through the expensive full gate.
    eligible = [index for index, attempt in enumerate(attempts) if _full_gate_eligible(attempt)]
    for index in eligible:
        function, candidate = blocks[index]
        attempt = attempts[index]
        if function in accepted:
            print(f"SKIPPED {function}: earlier candidate accepted")
            attempt.update({
                "status": "skipped",
                "reason": "earlier candidate accepted",
            })
            continue
        source_path.write_text(baseline)
        os.utime(source_path, None)
        rebuild_source_object(source_path)
        result, outcome = _try_candidate_detailed(source_path, function, candidate)
        attempt.update({
            "status": outcome,
            "exit_code": result,
            "probe_status": attempt.get("status"),
        })
        if result == 0:
            accepted[function] = candidate
            accepted_indices[function] = index

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

    # No probe hit means no source edit was made and no linker invocation is
    # necessary.  This is the main speedup for large rejected candidate sets.
    fallback_eligible = any(
        attempt.get("status") == "probe_unavailable"
        and attempt.get("probe_reason")
        in {"baseline_object_unavailable", "missing_function_bytes"}
        for attempt in attempts
    )
    if not accepted and not fallback_eligible:
        return {
            "status": 1,
            "accepted": [],
            "attempts": attempts,
            "rejected_ranking": rejection_rankings,
            "batch_status": "no_candidate_accepted",
            "probe_workers": probe_workers,
            "gate": True,
        }

    combined = baseline
    for install_index, (function, candidate) in enumerate(accepted.items()):
        # Shared declarations are installed once, ahead of the first accepted
        # replacement; later winners in the same batch drop the prefix.
        if prefix and install_index and candidate.startswith(prefix):
            candidate = candidate[len(prefix):]
        pragma = re.compile(
            rf'^#pragma GLOBAL_ASM\("asm/us/nonmatchings/[^"]+/{re.escape(function)}\.s"\)$',
            re.MULTILINE,
        )
        combined, count = pragma.subn(candidate.rstrip("\n"), combined, count=1)
        if count != 1:
            source_path.write_text(baseline)
            os.utime(source_path, None)
            rebuild_source_object(source_path)
            return {
                "status": 2,
                "accepted": [],
                "attempts": attempts,
                "rejected_ranking": rejection_rankings,
                "batch_status": "invalid_pragma",
                "probe_workers": probe_workers,
                "gate": True,
            }
    source_path.write_text(combined)
    os.utime(source_path, None)
    if rebuild_source_object(source_path) != 0:
        source_path.write_text(baseline)
        os.utime(source_path, None)
        rebuild_source_object(source_path)
        return {
            "status": 2,
            "accepted": [],
            "attempts": attempts,
            "rejected_ranking": rejection_rankings,
            "batch_status": "combined_compile_failed",
            "probe_workers": probe_workers,
            "gate": True,
        }
    if accepted:
        print(f"checking {len(accepted)} accepted candidate(s) together")
        result = compare_current_tree(repo_root)
        if result != 0:
            source_path.write_text(baseline)
            os.utime(source_path, None)
            rebuild_source_object(source_path)
            print("combined candidate batch rejected: restored baseline")
            return {
                "status": result,
                "accepted": [],
                "attempts": attempts,
                "rejected_ranking": rejection_rankings,
                "batch_status": "combined_compare_rejected",
                "probe_workers": probe_workers,
                "gate": True,
            }
    else:
        source_path.write_text(baseline)
        os.utime(source_path, None)
        rebuild_source_object(source_path)
        compare_current_tree(repo_root)
        print("no candidate accepted")
        return {
            "status": 1,
            "accepted": [],
            "attempts": attempts,
            "rejected_ranking": rejection_rankings,
            "batch_status": "no_candidate_accepted",
            "probe_workers": probe_workers,
            "gate": True,
        }
    return {
        "status": 0,
        "accepted": list(accepted),
        "attempts": attempts,
        "rejected_ranking": rejection_rankings,
        "batch_status": "accepted",
        "probe_workers": probe_workers,
        "gate": True,
    }


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
