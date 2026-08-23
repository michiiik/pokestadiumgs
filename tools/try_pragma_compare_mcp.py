#!/usr/bin/env python3
"""Minimal stdio MCP server for in-memory pragma candidate attempts."""

import json
import sys
from pathlib import Path

import try_pragma_compare as runner


def reply(request_id, result=None, error=None):
    payload = {"jsonrpc": "2.0", "id": request_id}
    payload["error" if error else "result"] = error or result
    print(json.dumps(payload), flush=True)


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
                "serverInfo": {"name": "pokemon-stadium-pragma-runner", "version": "1.0"},
            })
        elif method == "notifications/initialized":
            continue
        elif method == "tools/list":
            reply(request_id, {"tools": [{
                "name": "try_pragma_candidates",
                "description": "Try in-memory C replacements sequentially and keep only exact ROM matches.",
                "inputSchema": {"type": "object", "required": ["source", "candidates"], "properties": {
                    "source": {"type": "string", "description": "Source path relative to the repository root."},
                    "candidates": {"type": "array", "items": {"type": "object", "required": ["function", "code"], "properties": {
                        "function": {"type": "string"}, "code": {"type": "string"},
                    }}, "description": "Ordered candidates; later variants for a solved function are skipped."},
                }},
            }]})
        elif method == "tools/call" and request.get("params", {}).get("name") == "try_pragma_candidates":
            args = request["params"].get("arguments", {})
            root = Path(__file__).resolve().parent.parent
            source = (root / args["source"]).resolve()
            blocks = [(item["function"], item["code"]) for item in args["candidates"]]
            code, accepted = runner.try_candidates(source, blocks)
            reply(request_id, {"content": [{"type": "text", "text": json.dumps({"status": code, "accepted": accepted})}], "isError": code not in (0, 1)})
        elif request_id is not None:
            reply(request_id, error={"code": -32601, "message": f"Unknown method: {method}"})


if __name__ == "__main__":
    main()
