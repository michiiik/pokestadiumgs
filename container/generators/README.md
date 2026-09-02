# container/generators/

Pluggable candidate generators for `tools/container_agent.py`'s
`--generator-cmd`. See `docs/CONTAINER_AGENT.md` §3 for how the container
selects and runs one of these by default via the `AGENT` env var. Point the
driver at the dispatcher:

```
--generator-cmd "container/generators/run_generator.sh {prompt} {batch}"
```

`{prompt}` and `{batch}` are absolute paths substituted by
`render_generator_command()`; the prompt file already contains the batch
JSON schema and the exact `{batch}` output path (see `BATCH_CONTRACT` in
`tools/container_agent.py`), so every wrapper's only jobs are: run the
model, and make sure `{batch}` ends up on disk as valid JSON.

Select which coding agent generates candidates with the `AGENT` env var
(default `claude`); `run_generator.sh` execs `container/generators/$AGENT.sh
<prompt> <batch>` and fails clearly on an unknown value.

## Agents

| `AGENT=`        | CLI / package                                    | Required env vars                              | Default model (`GENERATOR_MODEL`) |
|------------------|---------------------------------------------------|--------------------------------------------------|------------------------------------|
| `claude`         | `@anthropic-ai/claude-code` (`claude`)            | `ANTHROPIC_API_KEY`                              | `sonnet`                           |
| `codex`          | `@openai/codex` (`codex`)                         | `OPENAI_API_KEY`                                 | `gpt-5.1-codex`                    |
| `qwen`           | `@qwen-code/qwen-code` (`qwen`)                   | `OPENAI_API_KEY` (or `DASHSCOPE_API_KEY`)        | `qwen3-coder-plus`                 |
| `kimi`           | none -- routes to `openai_compat.sh`              | `MOONSHOT_API_KEY`                               | `kimi-k2.7-code`                   |
| `openai_compat`  | none (`python3` stdlib only)                      | `OPENAI_API_KEY`, `OPENAI_BASE_URL`, `GENERATOR_MODEL` | (none -- must be set)        |

Install lines for the Dockerfile (the other agent copies these; not added
here):

```
npm install -g @anthropic-ai/claude-code
npm install -g @openai/codex
npm install -g @qwen-code/qwen-code
# kimi and openai_compat need only python3, already required by the repo's tooling
```

## claude.sh

`claude -p "$(cat "$PROMPT")" --output-format text --model
"${GENERATOR_MODEL:-sonnet}" --allowedTools Read Write Bash`

Agentic: Claude writes `$BATCH` itself via its `Write` tool (auto-approved
by `--allowedTools` in `--print` mode, no interactive confirmation needed).
Flags verified against `claude --help` locally (Claude Code 2.1.258).

## codex.sh

`codex exec --dangerously-bypass-approvals-and-sandbox --skip-git-repo-check
-m "${GENERATOR_MODEL:-gpt-5.1-codex}" - < "$PROMPT"`

Agentic, prompt piped over stdin (`codex exec` reads stdin when `PROMPT` is
omitted or `-`) to avoid argv length limits on large prompts.
`--dangerously-bypass-approvals-and-sandbox` is documented as "Intended
solely for running in environments that are externally sandboxed" -- exactly
this container, so no per-command approval prompts or a second sandbox layer
on top of the container's own. Flags verified against `codex exec --help`
locally (codex-cli 0.152.0). Docs:
[Non-interactive mode](https://developers.openai.com/codex/noninteractive),
[Autofix GitHub Actions cookbook](https://developers.openai.com/cookbook/examples/codex/autofix-github-actions)
(confirms `OPENAI_API_KEY` as the CI/headless auth env var). `gpt-5.1-codex`
is a stable public model id as of this writing; codex accounts vary in which
ids they can reach, so override `GENERATOR_MODEL` if it 404s.

## qwen.sh

`qwen -p "$(cat "$PROMPT")" --output-format text --model
"${GENERATOR_MODEL:-qwen3-coder-plus}"`

Agentic, same shape as claude.sh. Flags verified against `qwen --help`
locally (qwen-code 0.22.3): `-p/--prompt` runs one prompt non-interactively
and exits. Auth env vars per the
[auth docs](https://qwenlm.github.io/qwen-code-docs/en/users/configuration/auth/):
OpenAI-compatible mode uses `OPENAI_API_KEY` (+ optional `OPENAI_BASE_URL`,
`OPENAI_MODEL`/`QWEN_MODEL`); DashScope mode uses `DASHSCOPE_API_KEY`. The
wrapper requires at least one of `OPENAI_API_KEY` / `DASHSCOPE_API_KEY` to be
set and otherwise leaves provider selection to qwen's own config.

## kimi.sh

Thin wrapper over `openai_compat.sh`, not the official `kimi` CLI. That CLI
(`pip install kimi-cli`) does confirm a non-interactive mode
(`-p/--prompt` with `--print` and `--yolo` for auto-approval -- see the
[command reference](https://moonshotai.github.io/kimi-cli/en/reference/kimi-command.html)),
but its auth is wired through `kimi login` or a TOML
[provider config](https://moonshotai.github.io/kimi-cli/en/configuration/providers.html),
with no single documented stateless env var -- a poor fit for a disposable,
non-interactive container. Moonshot's own chat-completions endpoint is a
plain, well-documented OpenAI-compatible HTTP API
([overview](https://platform.kimi.ai/docs/overview),
[models](https://platform.kimi.ai/docs/models)), so `kimi.sh` sets
`OPENAI_API_KEY=$MOONSHOT_API_KEY`, `OPENAI_BASE_URL` (default
`https://api.moonshot.ai/v1`, or set `MOONSHOT_BASE_URL=https://api.moonshot.cn/v1`
for the China region), `GENERATOR_MODEL` (default `kimi-k2.7-code`, Moonshot's
current coding-focused model) and execs `openai_compat.sh`.

## openai_compat.sh

Generic fallback for any OpenAI-`/chat/completions`-compatible provider,
using only `python3` stdlib (`urllib`, no pip deps) -- see
`openai_compat.py`. Since a bare HTTP chat model has no file tools, the
wrapper appends "Do not write files; reply with the batch JSON in a single
` ```json ` fenced code block" to the prompt it sends, then extracts that
fenced block (or, failing that, tries to parse the whole reply as JSON) and
writes it to `$BATCH` itself.

Requires `OPENAI_API_KEY`, `OPENAI_BASE_URL` (no trailing slash;
`/chat/completions` is appended), `GENERATOR_MODEL`.

## Contract every wrapper follows

- Positional args: `$1` = prompt file path, `$2` = batch file path.
- `set -eu`, bash (`_common.sh` uses bash-only `${!name}` indirection, so the
  per-agent wrappers that source it are bash, not POSIX `sh`).
- Exits non-zero unless `$2` exists and parses as JSON afterwards
  (`_common.sh`'s `validate_batch`, which shells out to
  `python3 -c 'import json,sys; json.load(open(sys.argv[1]))'`).
- cwd is the repo root (`tools/container_agent.py` runs the generator command
  with `cwd=repo_dir`); no wrapper needs to `cd`.
