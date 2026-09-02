#!/usr/bin/env bash
# Shared helpers for container/generators/*.sh wrappers. Not a standalone
# entry point -- sourced by each per-agent wrapper script.
#
# Every wrapper is called as: <agent>.sh <prompt-file> <batch-file>
# and must exit non-zero unless <batch-file> exists and parses as JSON
# afterwards (tools/container_agent.py's BATCH_CONTRACT tells the model to
# write that file itself; the wrapper only has to verify it happened).

# require_env NAME -- fail with a clear message if env var NAME is unset/empty.
require_env() {
  local name="$1"
  if [ -z "${!name:-}" ]; then
    echo "container/generators: \$${name} is required" >&2
    exit 1
  fi
}

# require_any_env NAME1 NAME2 ... -- fail unless at least one is set/non-empty.
require_any_env() {
  local name
  for name in "$@"; do
    if [ -n "${!name:-}" ]; then
      return 0
    fi
  done
  echo "container/generators: one of \$${*} is required" >&2
  exit 1
}

# validate_batch BATCH_PATH -- fail unless the path exists and parses as JSON.
validate_batch() {
  local batch_path="$1"
  if [ ! -f "$batch_path" ]; then
    echo "container/generators: generator did not write a batch file at $batch_path" >&2
    exit 1
  fi
  if ! python3 -c 'import json,sys; json.load(open(sys.argv[1]))' "$batch_path"; then
    echo "container/generators: $batch_path is not valid JSON" >&2
    exit 1
  fi
}
