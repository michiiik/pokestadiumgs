#!/usr/bin/env python3
"""Minimal stdio MCP server for isolated pragma candidate probes.

Tools:
  try_pragma_candidates  probe candidates in isolation, gate byte hits through COMPARE=1
  find_owner             which tracked source owns a GLOBAL_ASM pragma
  get_function_asm       the target assembly for a pragma-backed function
  list_targets           rank remaining pragmas by size/family for batching
  draft_candidates       m2c first drafts for a function (hypotheses only)
  permute_candidate      run decomp-permuter on a near-match body for a time budget
"""

import json
import contextlib
import io
import os
import sys
import traceback
from pathlib import Path

import try_pragma_compare as runner
import pragma_targets as targets

ROOT = Path(__file__).resolve().parent.parent

CANDIDATE_ITEMS = {
    "type": "array",
    "items": {
        "type": "object",
        "required": ["function", "code"],
        "properties": {
            "function": {"type": "string"},
            "code": {"type": "string"},
            "label": {"type": "string", "description": "Optional family/source-shape label echoed in the attempt diagnostics."},
        },
    },
    "description": "Ordered candidates; later variants for a solved function are skipped.",
}

COMPANION_EDIT_ITEMS = {
    "type": "array",
    "items": {
        "type": "object",
        "required": ["function", "old", "new"],
        "properties": {
            "function": {"type": "string", "description": "Name of the function whose existing definition/prototype is being edited; it may be the candidate owner when candidate substitution creates its C definition first."},
            "old": {"type": "string", "description": "Exact current text of that function's definition or prototype line(s). Must match exactly once in the file."},
            "new": {"type": "string", "description": "Replacement text."},
        },
    },
    "description": (
        "Paired-change edits to a C body or prototype in the same file (e.g. a caller "
        "that must be re-spelled to keep compiling once a new candidate gets its real "
        "signature). Candidate substitution happens before these edits for both the "
        "isolated probe and the gate, so a stale extern for the candidate owner may be "
        "retyped in the same transaction. Installed together with the candidates only "
        "on a successful gate; on any failure nothing is written. The edit must target "
        "an existing definition/prototype after candidate substitution, and may not add "
        "or remove a #pragma GLOBAL_ASM line."
    ),
}

TOOLS = [
    {
        "name": "try_pragma_candidates",
        "description": "Compile candidates in isolated temporary objects, then sequentially full-compare byte-level hits and keep only exact ROM matches.",
        "inputSchema": {"type": "object", "required": ["candidates"], "properties": {
            "source": {"type": "string", "description": "Source path relative to the repository root. Optional: resolved from the candidates' function names when omitted."},
            "candidates": CANDIDATE_ITEMS,
            "declarations": {"type": "string", "description": "Optional shared extern/prototype block prepended to every candidate probe and installed once ahead of the first accepted replacement."},
            "workers": {"type": "integer", "minimum": 1, "description": "Maximum parallel isolated compile probes (default: PRAGMA_PROBE_WORKERS or 10)."},
            "gate": {"type": "boolean", "default": True, "description": "Run the sequential full COMPARE=1 gate and update source (default true). Set false for isolated probe-only results."},
            "auto_gate": {"type": "boolean", "default": True, "description": "With gate:false, still run the authoritative ROM gate as soon as a candidate comes back link-verified, instead of returning the hit for a second round-trip (AGENTS.md 2.5 step 6). Set false to force a pure probe."},
            "companion_edits": COMPANION_EDIT_ITEMS,
        }},
    },
    {
        "name": "find_owner",
        "description": "Return the tracked source file and .s path that own a GLOBAL_ASM pragma.",
        "inputSchema": {"type": "object", "required": ["function"], "properties": {
            "function": {"type": "string"},
        }},
    },
    {
        "name": "get_function_asm",
        "description": "Return the splat nonmatching assembly for a pragma-backed function together with its owner.",
        "inputSchema": {"type": "object", "required": ["function"], "properties": {
            "function": {"type": "string"},
        }},
    },
    {
        "name": "list_targets",
        "description": "Rank remaining pragma-backed functions by instruction count with the family scanner's classification, for picking small same-shape batches.",
        "inputSchema": {"type": "object", "properties": {
            "source": {"type": "string", "description": "Restrict to one source path (repository-relative or suffix)."},
            "family": {"type": "string", "description": "Restrict to one scanner family, e.g. direct_wrapper, multi_call_wrapper, bounded_lookup, state_field_access, constant_map, jump_table_map."},
            "max_instructions": {"type": "integer", "minimum": 1},
            "min_instructions": {"type": "integer", "minimum": 1},
            "limit": {"type": "integer", "minimum": 1, "default": 50},
        }},
    },
    {
        "name": "draft_candidates",
        "description": "Run m2c over a function's assembly (with a preprocessed context from its owner source) and return first-draft C. Drafts are hypotheses; adapt them and send through try_pragma_candidates.",
        "inputSchema": {"type": "object", "required": ["function"], "properties": {
            "function": {"type": "string"},
            "variants": {"type": "array", "items": {"type": "string", "enum": sorted(targets.DRAFT_VARIANTS)}, "description": "Default: m2c and m2c-no-casts."},
            "context": {"type": "boolean", "default": True},
        }},
    },
    {
        "name": "permute_candidate",
        "description": "Run decomp-permuter on a compiling near-match body for a bounded wall-clock budget and return the best-scoring sources (score 0 = clean instruction diff). Never edits tracked source; a score-0 result still needs try_pragma_candidates.",
        "inputSchema": {"type": "object", "required": ["function", "code"], "properties": {
            "function": {"type": "string"},
            "code": {"type": "string", "description": "C body including its externs, as it would be sent to try_pragma_candidates."},
            "declarations": {"type": "string"},
            "seconds": {"type": "number", "minimum": 5, "default": 60},
            "threads": {"type": "integer", "minimum": 1, "default": 4},
            "stop_on_zero": {"type": "boolean", "default": True},
        }},
    },
]


def reply(request_id, result=None, error=None):
    payload = {"jsonrpc": "2.0", "id": request_id}
    payload["error" if error else "result"] = error or result
    print(json.dumps(payload), flush=True)


class ToolError(Exception):
    """A user-facing tool failure (bad arguments, missing owner, ...)."""


def _resolve_source(args, functions):
    """Return the owner source for a call; all functions must share one owner."""
    source_arg = args.get("source")
    if source_arg:
        source = (ROOT / source_arg).resolve()
        try:
            source.relative_to(ROOT / "disasm")
        except ValueError:
            raise ToolError("source must resolve under the repository disasm directory")
        if not source.is_file():
            raise ToolError(f"source file does not exist: {source}")
        return source
    owners = {}
    for function in functions:
        owner = targets.find_owner(function)
        if owner is None:
            raise ToolError(f"no GLOBAL_ASM pragma owns {function}; pass source explicitly")
        owners[owner.source] = owner
    if len(owners) != 1:
        raise ToolError(
            "candidates span several owner sources: " + ", ".join(sorted(owners))
            + "; send one batch per source"
        )
    return next(iter(owners.values())).source_path


def tool_try_pragma_candidates(args):
    candidates = args.get("candidates") or []
    if not candidates:
        raise ToolError("candidates must not be empty")
    declarations = args.get("declarations")
    if declarations is not None and not isinstance(declarations, str):
        raise ToolError("declarations must be a string when provided")
    companion_edits = args.get("companion_edits")
    if companion_edits is not None:
        if not isinstance(companion_edits, list) or not companion_edits:
            raise ToolError("companion_edits must be a non-empty list when provided")
        for item in companion_edits:
            if not isinstance(item, dict) or not all(
                isinstance(item.get(key), str) for key in ("function", "old", "new")
            ):
                raise ToolError(
                    "each companion_edits item needs string 'function', 'old', and 'new'"
                )
    blocks = [(item["function"], item["code"]) for item in candidates]
    labels = [item.get("label") for item in candidates]
    source = _resolve_source(args, [function for function, _ in blocks])
    preflight_errors = runner.validate_candidate_batch(
        source,
        [function for function, _ in blocks],
        companion_edits,
        blocks,
        declarations,
    )
    if preflight_errors:
        details = "\n".join(f"- {error}" for error in preflight_errors)
        raise ToolError(f"candidate batch preflight failed:\n{details}")
    futility = runner.futility_warnings(blocks, runner._load_prior_attempt_history())
    workers = args.get("workers")
    if workers is not None:
        workers = int(workers)
    result = runner.try_candidates_detailed(
        source,
        blocks,
        probe_workers=workers,
        labels=labels,
        gate=bool(args.get("gate", True)),
        auto_gate=None if args.get("auto_gate") is None else bool(args["auto_gate"]),
        declarations=declarations,
        companion_edits=companion_edits,
    )
    for attempt in result.get("attempts", []):
        index = attempt.get("index")
        if isinstance(index, int) and index < len(labels) and labels[index]:
            attempt["label"] = labels[index]
    result["source"] = source.relative_to(ROOT).as_posix()
    if futility:
        result["futility_warnings"] = futility
    return result, int(result["status"]) not in (0, 1)


def tool_find_owner(args):
    owner = targets.find_owner(args["function"])
    if owner is None:
        raise ToolError(f"no GLOBAL_ASM pragma owns {args['function']}")
    return owner.as_dict(), False


def tool_get_function_asm(args):
    try:
        return targets.function_asm(args["function"]), False
    except KeyError as error:
        raise ToolError(str(error))


def tool_list_targets(args):
    return targets.list_targets(
        source=args.get("source"),
        family=args.get("family"),
        max_instructions=args.get("max_instructions"),
        min_instructions=args.get("min_instructions"),
        limit=int(args.get("limit", 50)),
    ), False


def tool_draft_candidates(args):
    try:
        return targets.draft_candidates(
            args["function"],
            variants=args.get("variants"),
            context=bool(args.get("context", True)),
        ), False
    except (KeyError, FileNotFoundError) as error:
        raise ToolError(str(error))


def tool_permute_candidate(args):
    import permute_candidate

    try:
        result = permute_candidate.permute(
            args["function"],
            args["code"],
            seconds=float(args.get("seconds", 60)),
            threads=int(args.get("threads", 4)),
            declarations=args.get("declarations"),
            stop_on_zero=bool(args.get("stop_on_zero", True)),
        )
    except (KeyError, FileNotFoundError, RuntimeError, ValueError) as error:
        raise ToolError(str(error))
    return result, False


HANDLERS = {
    "try_pragma_candidates": tool_try_pragma_candidates,
    "find_owner": tool_find_owner,
    "get_function_asm": tool_get_function_asm,
    "list_targets": tool_list_targets,
    "draft_candidates": tool_draft_candidates,
    "permute_candidate": tool_permute_candidate,
}


@contextlib.contextmanager
def _silenced_stdout():
    """Keep build logs off the JSON-RPC stream.

    The helpers print build logs to stdout and spawn make/compilers whose
    children inherit the file descriptor, so both the Python-level stream and
    the underlying descriptor are redirected for the duration of a call.
    """
    captured = io.StringIO()
    sys.stdout.flush()
    saved_fd = os.dup(sys.stdout.fileno())
    devnull_fd = os.open(os.devnull, os.O_WRONLY)
    try:
        os.dup2(devnull_fd, sys.stdout.fileno())
        with contextlib.redirect_stdout(captured):
            yield captured
    finally:
        sys.stdout.flush()
        os.dup2(saved_fd, sys.stdout.fileno())
        os.close(devnull_fd)
        os.close(saved_fd)


def call_tool(name, args):
    handler = HANDLERS.get(name)
    if handler is None:
        return {"content": [{"type": "text", "text": f"unknown tool: {name}"}], "isError": True}
    try:
        with _silenced_stdout():
            result, is_error = handler(args)
    except ToolError as error:
        return {"content": [{"type": "text", "text": json.dumps({"error": str(error)})}], "isError": True}
    except Exception:  # pragma: no cover - keep the server alive on unexpected failures
        text = json.dumps({"error": "internal tool failure", "traceback": traceback.format_exc()[-4000:]})
        return {"content": [{"type": "text", "text": text}], "isError": True}
    return {"content": [{"type": "text", "text": json.dumps(result)}], "isError": is_error}


def main():
    for line in sys.stdin:
        if not line.strip():
            continue
        request = json.loads(line)
        method = request.get("method")
        request_id = request.get("id")
        if method == "initialize":
            reply(request_id, {
                "protocolVersion": request["params"].get("protocolVersion", "2024-11-05"),
                "capabilities": {"tools": {}},
                "serverInfo": {"name": "pokemon-stadium-pragma-runner", "version": "1.1"},
            })
        elif method == "notifications/initialized":
            continue
        elif method == "tools/list":
            reply(request_id, {"tools": TOOLS})
        elif method == "tools/call":
            params = request.get("params", {})
            reply(request_id, call_tool(params.get("name"), params.get("arguments", {}) or {}))
        elif request_id is not None:
            reply(request_id, error={"code": -32601, "message": f"Unknown method: {method}"})


if __name__ == "__main__":
    main()
