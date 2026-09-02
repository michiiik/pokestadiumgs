#!/usr/bin/env python3
"""Generic OpenAI-chat-completions-compatible generator (stdlib only).

Used by container/generators/openai_compat.sh as the fallback for any
provider that speaks the OpenAI /chat/completions wire format (and by
kimi.sh, which is a thin wrapper over this same script -- see kimi.sh for
why). Unlike claude.sh/codex.sh/qwen.sh, a bare HTTP chat model has no file
tools of its own, so this script does the writing: it appends an instruction
to the prompt telling the model to reply with the batch JSON in a fenced
```json block instead of writing a file, then extracts that block (or, if
the whole reply already parses as JSON, uses that) and writes it to $BATCH
itself.

Usage: openai_compat.py <prompt-file> <batch-file>
Env:
  OPENAI_API_KEY   required
  OPENAI_BASE_URL  required, e.g. https://api.openai.com/v1 (no trailing
                   slash; "/chat/completions" is appended)
  GENERATOR_MODEL  required, model id understood by that base URL
"""
from __future__ import annotations

import json
import os
import re
import sys
import urllib.error
import urllib.request

NO_FILE_INSTRUCTION = (
    "\n\nDo not write files; you have no tool access. Reply with the batch "
    "JSON in a single ```json fenced code block and nothing else."
)

FENCE_RE = re.compile(r"```json\s*(.*?)```", re.DOTALL | re.IGNORECASE)


def die(message: str) -> "None":
    print(f"openai_compat.py: {message}", file=sys.stderr)
    sys.exit(1)


def extract_json(content: str) -> str:
    match = FENCE_RE.search(content)
    if match:
        candidate = match.group(1).strip()
    else:
        candidate = content.strip()
    # Validate it parses; raise a clear error if not so the caller (and the
    # wrapper's post-hoc validate_batch check) both fail loudly.
    json.loads(candidate)
    return candidate


def main(argv: list[str]) -> int:
    if len(argv) != 3:
        die(f"usage: {argv[0]} <prompt-file> <batch-file>")

    prompt_path, batch_path = argv[1], argv[2]

    api_key = os.environ.get("OPENAI_API_KEY", "")
    base_url = os.environ.get("OPENAI_BASE_URL", "")
    model = os.environ.get("GENERATOR_MODEL", "")
    if not api_key:
        die("$OPENAI_API_KEY is required")
    if not base_url:
        die("$OPENAI_BASE_URL is required")
    if not model:
        die("$GENERATOR_MODEL is required")

    with open(prompt_path, "r", encoding="utf-8") as f:
        prompt_text = f.read()
    prompt_text += NO_FILE_INSTRUCTION

    payload = json.dumps(
        {
            "model": model,
            "messages": [{"role": "user", "content": prompt_text}],
        }
    ).encode("utf-8")

    url = base_url.rstrip("/") + "/chat/completions"
    request = urllib.request.Request(
        url,
        data=payload,
        method="POST",
        headers={
            "Content-Type": "application/json",
            "Authorization": f"Bearer {api_key}",
        },
    )

    try:
        with urllib.request.urlopen(request, timeout=280) as response:
            response_body = response.read().decode("utf-8")
    except urllib.error.HTTPError as exc:
        detail = exc.read().decode("utf-8", errors="replace")
        die(f"HTTP {exc.code} from {url}: {detail[:2000]}")
    except urllib.error.URLError as exc:
        die(f"request to {url} failed: {exc.reason}")

    try:
        response_json = json.loads(response_body)
        content = response_json["choices"][0]["message"]["content"]
    except (json.JSONDecodeError, KeyError, IndexError, TypeError) as exc:
        die(f"unexpected response shape from {url}: {exc}: {response_body[:2000]}")

    try:
        batch_json_text = extract_json(content)
    except json.JSONDecodeError as exc:
        die(f"reply did not contain a valid JSON batch: {exc}: {content[:2000]}")

    with open(batch_path, "w", encoding="utf-8") as f:
        f.write(batch_json_text)

    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
