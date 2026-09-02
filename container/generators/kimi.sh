#!/usr/bin/env bash
# Generator wrapper: official Kimi Code CLI (agentic -- writes $BATCH itself
# via its Write tool; the prompt file already contains the batch JSON schema
# and the exact output path per tools/container_agent.py's BATCH_CONTRACT).
#
# Usage: kimi.sh <prompt-file> <batch-file>
# Install: the CLI's own installer, pinned to an exact version -- see
#   container/Dockerfile (single ~180MB native binary, no npm/pip):
#   https://moonshotai.github.io/kimi-code/
# Requires: EITHER a subscription login -- a credentials file under
#   ${KIMI_CODE_HOME:-$HOME/.kimi-code}/credentials/ (container/run.sh mounts
#   a throwaway copy of the host's ~/.kimi-code there when AGENT=kimi and no
#   API-key env is set, same pattern as codex.sh/CODEX_HOME) -- OR a bare API
#   key via the CLI's own stateless env-var model definition: KIMI_MODEL_NAME
#   + KIMI_MODEL_API_KEY (KIMI_MODEL_PROVIDER_TYPE defaults to "kimi"). See
#   https://moonshotai.github.io/kimi-code/en/configuration/env-vars.html
#   ("Define a model from environment variables"). This is a different route
#   from kimi_api.sh (AGENT=kimi_api, MOONSHOT_API_KEY through the generic
#   openai_compat.sh path with no CLI installed at all) -- use that one if
#   you just have a Moonshot API key and don't want the CLI's login state.
# Optional: GENERATOR_EFFORT (low|high|max for the default kimi-code/k3 --
#   its config.toml entry declares support_efforts = [low, high, max]) --
#   forwarded via KIMI_MODEL_THINKING_EFFORT, the CLI's own env var for
#   forcing a thinking-effort level on the wire (only takes effect while
#   Thinking is on, which the default profile has enabled).
# Default model: kimi-code/k3 (override with GENERATOR_MODEL; other aliases
#   configured by a subscription login's config.toml include
#   kimi-code/k3-256k, kimi-code/kimi-for-coding, and
#   kimi-code/kimi-for-coding-highspeed -- `kimi --help` / config.toml lists
#   what's actually available for a given login)
#
# Flags verified locally against `kimi --help` and by direct invocation
# (Kimi Code CLI 0.39.1):
#   -p, --prompt <prompt>       run one prompt non-interactively, print the
#                                response, and exit (no TUI)
#   --output-format <format>    "text" | "stream-json"; only valid with -p
#   -m, --model <model>         model alias for this invocation
#   --add-dir <dir>              extra workspace directory for this session
#                                (repeatable) -- $PROMPT/$BATCH live under
#                                the driver's --out mount, not this script's
#                                cwd (the repo root), so both directories are
#                                added defensively in case file tools are
#                                scoped to the workspace
#
# IMPORTANT: `-p` cannot be combined with `--yolo` or `--auto` -- the CLI
# rejects that at startup ("error: Cannot combine --prompt with --auto.",
# confirmed locally) because `-p` mode already runs under auto permission by
# default: "In -p mode, no human approval is requested -- regular tool calls
# are handled under the auto permission policy, while static deny rules
# remain in effect." (https://moonshotai.github.io/kimi-code/en/reference/kimi-command.html#non-interactive-execution)
# So this wrapper passes neither flag.
set -eu
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck source=./_common.sh
. "$SCRIPT_DIR/_common.sh"

PROMPT="$1"
BATCH="$2"

KIMI_HOME="${KIMI_CODE_HOME:-$HOME/.kimi-code}"

if [ ! -f "$KIMI_HOME/credentials/kimi-code.json" ] \
   && { [ -z "${KIMI_MODEL_API_KEY:-}" ] || [ -z "${KIMI_MODEL_NAME:-}" ]; }; then
  echo "container/generators: kimi needs EITHER a subscription login -- a credentials file under \${KIMI_CODE_HOME:-\$HOME/.kimi-code}/credentials/ (container/run.sh mounts the host's copy) -- OR both \$KIMI_MODEL_NAME and \$KIMI_MODEL_API_KEY set (the CLI's stateless API-key model definition)." >&2
  echo "container/generators: for a plain Moonshot API key with no CLI login state at all, use AGENT=kimi_api (\$MOONSHOT_API_KEY) instead." >&2
  exit 1
fi

effort_env=()
if [ -n "${GENERATOR_EFFORT:-}" ]; then
  effort_env=(KIMI_MODEL_THINKING_EFFORT="$GENERATOR_EFFORT")
fi

env "${effort_env[@]}" kimi \
  -p "$(cat "$PROMPT")" \
  -m "${GENERATOR_MODEL:-kimi-code/k3}" \
  --output-format text \
  --add-dir "$(dirname "$PROMPT")" \
  --add-dir "$(dirname "$BATCH")"

validate_batch "$BATCH"
