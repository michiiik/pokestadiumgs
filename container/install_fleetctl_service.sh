#!/bin/bash
# container/install_fleetctl_service.sh [--repo <path>] [--dry-run] [--uninstall]
#
# Installs `fleetctl run` (docs/FLEET_CONTROLLER.md) as a macOS launchd user
# agent, so the container fleet controller survives logout/reboot instead of
# needing a human's terminal session to stay open (docs/FLEET_CONTROLLER.md
# sec 4 already documents the launchd pattern by hand; this script is that
# pattern, scripted).
#
# Install (default, no flags):
#   1. Builds tools/fleetctl from --repo (default: the checkout this script
#      itself lives in) into ~/.local/bin/fleetctl -- `go build -o
#      ~/.local/bin/fleetctl .` run with cwd <repo>/tools/fleetctl (that
#      directory's own go.mod, not a repo-root one, is what makes
#      `go build ./tools/fleetctl` from the repo root fail; this is the
#      same invocation docs/FLEET_CONTROLLER.md's own "Build it once"
#      section documents, `cd tools/fleetctl && go build -o fleetctl .`,
#      just with an absolute -o so it lands straight in ~/.local/bin).
#   2. Writes ~/Library/LaunchAgents/com.gs-decomp.fleetctl.plist running
#        fleetctl run --plan <state-dir>/plan.json --state-dir <state-dir>
#          --runs-dir ~/projects/gs-container-runs --repo <repo>
#          --src-overlay <repo> --max-concurrent 4 --alert-macos
#      with KeepAlive, RunAtLoad, a PATH that includes docker's and gh's
#      directories (resolved from this shell's own PATH at install time,
#      falling back to their Homebrew/system locations if not found), and
#      both stdout/stderr redirected to
#      ~/Library/Logs/gs-decomp/fleetctl.log.
#   3. `launchctl bootstrap gui/$UID <plist>` (bootout first if a prior
#      instance is already loaded, so a reinstall is idempotent).
#
# --plan: fleetctl run's --plan is currently a required flag (see
#   tools/fleetctl/cmd_run.go) -- there is no default plan path fleetctl
#   itself falls back to yet. This script always passes
#   `--plan <state-dir>/plan.json`, so BEFORE installing (or after changing
#   the file set fleetctl should work on), an operator must generate that
#   file once with `fleetctl plan --repo <repo> ... --out <state-dir>/plan.json`
#   (docs/FLEET_CONTROLLER.md sec 1) -- `fleetctl run` only ever reads it to
#   seed state.json and re-loading it on every launchd restart is a no-op
#   for any run id state.json already knows (sec 3), so this is a one-time
#   step per plan, not a per-restart chore.
#
# --src-overlay and --alert-macos: NEITHER FLAG EXISTS ON `fleetctl run` YET
#   as of this writing -- see docs/CONTAINER_AGENT.md's SRC_OVERLAY section
#   and docs/FLEET_CONTROLLER.md's launchd section for the contract they
#   need to implement:
#     --src-overlay <dir>  forwarded as SRC_OVERLAY=<dir> to the
#                           environment of every `container/run.sh` fleetctl
#                           launches (tools/fleetctl/internal/runner),
#                           exactly like a caller exporting it before
#                           invoking container/run.sh by hand.
#     --alert-macos         tools/fleetctl/internal/runner/runner.go already
#                           has a comment naming this flag's one effect: an
#                           `osascript -e 'display notification ...'` call.
#   This script only *invokes* fleetctl with these flags (matching
#   docs/CONTAINER_AGENT.md's rule that fleetctl never touches
#   container/*/disasm/*/​.github/* itself) -- it does not implement them.
#
# --uninstall: `launchctl bootout gui/$UID/com.gs-decomp.fleetctl` (if
#   loaded) then removes the plist. Does NOT stop already-launched
#   containers or fleetctl's own in-progress merges -- run
#   `fleetctl stop --state-dir <state-dir> --all` first if you want that
#   (docs/FLEET_CONTROLLER.md sec 4: unloading the agent alone does not
#   touch already-launched containers).
#
# --dry-run: print the plist body and every command this script would
#   otherwise run (mkdir, go build, launchctl bootout/bootstrap) -- no
#   directory is created, nothing is built, no file is written, launchctl
#   is never invoked. Combine with --uninstall to preview that path too.
set -euo pipefail

usage() {
    echo "usage: $(basename "$0") [--repo <path>] [--dry-run] [--uninstall]" >&2
    exit 1
}

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
default_repo="$(cd "$script_dir/.." && pwd)"

repo="$default_repo"
dry_run=0
do_uninstall=0
while [ "$#" -gt 0 ]; do
    case "$1" in
        --repo)
            [ "$#" -ge 2 ] || usage
            repo="$2"
            shift 2
            ;;
        --repo=*)
            repo="${1#--repo=}"
            shift
            ;;
        --dry-run)
            dry_run=1
            shift
            ;;
        --uninstall)
            do_uninstall=1
            shift
            ;;
        -h|--help)
            usage
            ;;
        *)
            echo "install_fleetctl_service.sh: unknown argument: $1" >&2
            usage
            ;;
    esac
done

case "$repo" in
    /*) : ;;
    *) repo="$(cd "$repo" && pwd)" ;;
esac

label="com.gs-decomp.fleetctl"
uid="$(id -u)"
fleetctl_bin="$HOME/.local/bin/fleetctl"
state_dir="$HOME/projects/gs-container-runs/fleet-state"
runs_dir="$HOME/projects/gs-container-runs"
plan_path="$state_dir/plan.json"
log_dir="$HOME/Library/Logs/gs-decomp"
log_file="$log_dir/fleetctl.log"
plist_dir="$HOME/Library/LaunchAgents"
plist_path="$plist_dir/$label.plist"

run() {
    if [ "$dry_run" -eq 1 ]; then
        printf '[dry-run] %s\n' "$*" >&2
    else
        "$@"
    fi
}

is_loaded() {
    launchctl print "gui/$uid/$label" >/dev/null 2>&1
}

if [ "$do_uninstall" -eq 1 ]; then
    if [ "$dry_run" -eq 1 ]; then
        echo "[dry-run] would check whether gui/$uid/$label is loaded, bootout if so, then remove $plist_path" >&2
        exit 0
    fi
    if is_loaded; then
        echo "install_fleetctl_service.sh: $label is loaded -- booting out" >&2
        launchctl bootout "gui/$uid/$label"
    else
        echo "install_fleetctl_service.sh: $label is not loaded" >&2
    fi
    if [ -f "$plist_path" ]; then
        rm -f "$plist_path"
        echo "install_fleetctl_service.sh: removed $plist_path" >&2
    else
        echo "install_fleetctl_service.sh: $plist_path did not exist" >&2
    fi
    echo "install_fleetctl_service.sh: uninstalled. Already-launched containers were NOT stopped -- run 'fleetctl stop --state-dir $state_dir --all' first next time if you want that too." >&2
    exit 0
fi

if [ ! -d "$repo/tools/fleetctl" ] || [ ! -x "$repo/container/run.sh" ]; then
    echo "install_fleetctl_service.sh: $repo does not look like a repo checkout (no tools/fleetctl or container/run.sh)" >&2
    exit 1
fi

# --- resolve docker's and gh's directories for the plist's PATH ------------
# launchd user agents do not inherit an interactive shell's PATH -- resolve
# both at install time from THIS shell's PATH, falling back to their usual
# Homebrew/system locations if not found on it (e.g. running this script
# under a minimal PATH by hand).
docker_bin="$(command -v docker 2>/dev/null || true)"
docker_dir="${docker_bin:+$(dirname "$docker_bin")}"
docker_dir="${docker_dir:-/usr/local/bin}"
gh_bin="$(command -v gh 2>/dev/null || true)"
gh_dir="${gh_bin:+$(dirname "$gh_bin")}"
gh_dir="${gh_dir:-/opt/homebrew/bin}"

plist_path_dirs=("$HOME/.local/bin" "$docker_dir" "$gh_dir" /usr/local/bin /opt/homebrew/bin /usr/bin /bin /usr/sbin /sbin)
plist_env_path=""
for d in "${plist_path_dirs[@]}"; do
    case ":$plist_env_path:" in
        *":$d:"*) continue ;;
    esac
    plist_env_path="${plist_env_path:+$plist_env_path:}$d"
done

# --- compose the plist ------------------------------------------------------
plist_body="$(cat <<PLIST
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN"
  "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>Label</key><string>$label</string>
  <key>ProgramArguments</key>
  <array>
    <string>$fleetctl_bin</string>
    <string>run</string>
    <string>--plan</string><string>$plan_path</string>
    <string>--state-dir</string><string>$state_dir</string>
    <string>--runs-dir</string><string>$runs_dir</string>
    <string>--repo</string><string>$repo</string>
    <string>--src-overlay</string><string>$repo</string>
    <string>--max-concurrent</string><string>4</string>
    <string>--alert-macos</string>
  </array>
  <key>WorkingDirectory</key><string>$repo</string>
  <key>EnvironmentVariables</key>
  <dict>
    <key>PATH</key><string>$plist_env_path</string>
    <key>HOME</key><string>$HOME</string>
  </dict>
  <key>RunAtLoad</key><true/>
  <key>KeepAlive</key><true/>
  <key>StandardOutPath</key><string>$log_file</string>
  <key>StandardErrorPath</key><string>$log_file</string>
</dict>
</plist>
PLIST
)"

if [ "$dry_run" -eq 1 ]; then
    echo "[dry-run] would run: go build -o $fleetctl_bin .  (in $repo/tools/fleetctl)" >&2
    echo "[dry-run] would create: $(dirname "$fleetctl_bin") $state_dir $runs_dir $log_dir $plist_dir" >&2
    echo "[dry-run] would write $plist_path:" >&2
    printf '%s\n' "$plist_body"
    echo "[dry-run] would run: launchctl bootstrap gui/$uid $plist_path  (bootout first if already loaded)" >&2
    echo "[dry-run] NOTE: --plan requires $plan_path to already exist -- see this script's own --plan comment (generate it once with 'fleetctl plan ... --out $plan_path')." >&2
    exit 0
fi

mkdir -p "$(dirname "$fleetctl_bin")" "$state_dir" "$runs_dir" "$log_dir" "$plist_dir"

echo "install_fleetctl_service.sh: building fleetctl from $repo/tools/fleetctl" >&2
(cd "$repo/tools/fleetctl" && go build -o "$fleetctl_bin" .)

if [ ! -f "$plan_path" ]; then
    echo "install_fleetctl_service.sh: WARNING: $plan_path does not exist yet -- fleetctl run will fail to start until you generate one, e.g.:" >&2
    echo "  fleetctl plan --repo $repo --files N --slots 4 --agent claude:sonnet --out $plan_path" >&2
fi

tmp_plist="$(mktemp -t fleetctl_plist.XXXXXX)"
printf '%s\n' "$plist_body" > "$tmp_plist"
mv "$tmp_plist" "$plist_path"
echo "install_fleetctl_service.sh: wrote $plist_path" >&2

if is_loaded; then
    echo "install_fleetctl_service.sh: $label already loaded -- booting out before reloading" >&2
    launchctl bootout "gui/$uid/$label"
fi

launchctl bootstrap "gui/$uid" "$plist_path"
echo "install_fleetctl_service.sh: bootstrapped $label under gui/$uid. Logs: $log_file" >&2
