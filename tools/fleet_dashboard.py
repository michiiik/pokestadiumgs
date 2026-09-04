#!/usr/bin/env python3
"""A live, auto-refreshing terminal view of the fleet, on top of `fleetctl
status --json`.

`fleetctl status`'s own table prints every run fleetctl has ever known about
-- hundreds of rows once a fleet-state directory has been running a while,
almost all of them terminal (done/merged/gate_failed) history. That's the
right shape for `fleetctl status`'s own job (a full audit trail, and the
source `--json` alerts embed), but it's too much to make sense of at a
glance. This renders just what a human watching the fleet actually wants to
see -- currently running containers, live cooldowns, and the per-agent
METRICS table -- and redraws it every --interval seconds.

Usage:
    python3 tools/fleet_dashboard.py --state-dir ~/projects/gs-container-runs/fleet-state
    python3 tools/fleet_dashboard.py --state-dir ... --interval 5
    python3 tools/fleet_dashboard.py --state-dir ... --once   # one render, no loop (e.g. for scripting)
"""

from __future__ import annotations

import argparse
import datetime
import json
import shutil
import subprocess
import sys
import time

DEFAULT_INTERVAL = 10.0

# Statuses render_dashboard's RUNNING section shows -- StatusRunning plus the
# two short-lived post-exit states a container can sit in briefly before
# reconcileQueue/pollPRs moves it on, so a container mid-merge or with a PR
# open still shows up as "doing something" rather than disappearing between
# refreshes.
ACTIVE_STATUSES = ("running", "merging", "pr_open")


def _run_fleetctl_status(fleetctl_bin: str, state_dir: str) -> dict:
    result = subprocess.run(
        [fleetctl_bin, "status", "--state-dir", state_dir, "--json"],
        capture_output=True, text=True, timeout=30,
    )
    if result.returncode != 0:
        raise RuntimeError(f"fleetctl status exited {result.returncode}: {result.stderr.strip()[:500]}")
    return json.loads(result.stdout)


def _parse_iso(ts: str) -> datetime.datetime | None:
    if not ts or ts.startswith("0001-01-01"):
        return None
    return datetime.datetime.fromisoformat(ts)


def _human_remaining(until: datetime.datetime, now: datetime.datetime) -> str:
    remaining = (until - now).total_seconds()
    if remaining <= 0:
        return "expired"
    minutes, seconds = divmod(int(remaining), 60)
    hours, minutes = divmod(minutes, 60)
    if hours:
        return f"{hours}h{minutes:02d}m"
    if minutes:
        return f"{minutes}m{seconds:02d}s"
    return f"{seconds}s"


def _truncate(text: str, width: int) -> str:
    if len(text) <= width:
        return text
    return text[: width - 1] + "…"


def render_dashboard(status: dict, now: datetime.datetime) -> str:
    """Pure formatting: status (a parsed `fleetctl status --json` document)
    and now (the render time, injected rather than read from the clock so
    this is deterministic and unit-testable) in, one screen of text out.
    """
    lines: list[str] = []
    lines.append(f"fleet dashboard -- {now.strftime('%Y-%m-%d %H:%M:%S %Z') or now.isoformat()}")
    lines.append("")

    running = status.get("running", 0)
    queued = status.get("queued", 0)
    by_agent = status.get("running_by_agent") or {}
    by_agent_str = ", ".join(f"{agent}={n}" for agent, n in sorted(by_agent.items())) or "none"
    lines.append(f"running={running}  queued={queued}  ({by_agent_str})")
    lines.append("")

    # --- Cooldowns -----------------------------------------------------
    cooldowns = status.get("cooldowns") or {}
    active_cooldowns = []
    for key, ts in cooldowns.items():
        until = _parse_iso(ts)
        if until is not None and until > now:
            active_cooldowns.append((key, until))
    lines.append(f"COOLDOWNS ({len(active_cooldowns)} active):")
    if active_cooldowns:
        active_cooldowns.sort(key=lambda pair: pair[1])
        for key, until in active_cooldowns:
            lines.append(f"  {key:<32} {_human_remaining(until, now)}")
    else:
        lines.append("  (none)")
    lines.append("")

    # --- Currently active runs ------------------------------------------
    runs = [r for r in status.get("runs", []) if r.get("status") in ACTIVE_STATUSES]
    lines.append(f"ACTIVE RUNS ({len(runs)}):")
    if runs:
        header = f"  {'RUN':<32} {'STATUS':<9} {'FILE':<28} {'AGENT':<28} {'OWN':>3} {'ACC':>3} {'NOTE'}"
        lines.append(header)
        for r in sorted(runs, key=lambda r: (r.get("status", ""), r.get("id", ""))):
            agent = r.get("agent", "")
            model = r.get("model", "")
            agent_model = f"{agent}:{model}" if model else agent
            file_name = (r.get("file") or "").rsplit("/", 1)[-1]
            note = _truncate(r.get("note") or "", 40)
            lines.append(
                f"  {_truncate(r.get('id', ''), 32):<32} {r.get('status', ''):<9} "
                f"{_truncate(file_name, 28):<28} {_truncate(agent_model, 28):<28} "
                f"{r.get('owners', 0):>3} {r.get('matched', 0):>3} {note}"
            )
    else:
        lines.append("  (none)")
    lines.append("")

    # --- Per-agent metrics ------------------------------------------------
    metrics = status.get("metrics") or []
    lines.append("METRICS:")
    lines.append(f"  {'AGENT':<10} {'RUNS':>5} {'ITERS':>6} {'ACCEPTS':>7} {'ACC/HR':>7} {'ACC/WIN':>8} {'COOLDOWN':>9}")
    for m in metrics:
        cooldown = "yes" if m.get("on_cooldown") else "-"
        lines.append(
            f"  {m.get('agent', ''):<10} {m.get('runs', 0):>5} {m.get('iterations', 0):>6} "
            f"{m.get('accepts', 0):>7} {m.get('accepts_per_wall_hour', 0):>7.2f} "
            f"{m.get('accepts_per_window', 0):>8.2f} {cooldown:>9}"
        )

    return "\n".join(lines)


def _clear_screen() -> None:
    sys.stdout.write("\033[2J\033[H")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--state-dir", required=True, help="fleetctl --state-dir (holding state.json)")
    parser.add_argument("--fleetctl", default="fleetctl", help="fleetctl binary (default: fleetctl on PATH)")
    parser.add_argument("--interval", type=float, default=DEFAULT_INTERVAL, help=f"seconds between refreshes (default {DEFAULT_INTERVAL})")
    parser.add_argument("--once", action="store_true", help="render one frame and exit, instead of looping (e.g. for scripting)")
    args = parser.parse_args(argv)

    fleetctl_bin = args.fleetctl
    if shutil.which(fleetctl_bin) is None:
        print(f"fleet_dashboard: {fleetctl_bin!r} not found on PATH", file=sys.stderr)
        return 2

    def render_once() -> str:
        status = _run_fleetctl_status(fleetctl_bin, args.state_dir)
        return render_dashboard(status, datetime.datetime.now().astimezone())

    if args.once:
        try:
            print(render_once())
        except Exception as exc:  # noqa: BLE001 -- surface any failure directly in --once mode
            print(f"fleet_dashboard: {exc}", file=sys.stderr)
            return 1
        return 0

    last_good: str | None = None
    try:
        while True:
            try:
                last_good = render_once()
            except Exception as exc:  # noqa: BLE001 -- a transient read (e.g. state.json mid-write) must not kill the dashboard
                error_line = f"(refresh failed: {exc}; showing last successful frame)"
                last_good = f"{last_good}\n\n{error_line}" if last_good else error_line
            _clear_screen()
            print(last_good)
            print(f"\n(refreshing every {args.interval:g}s -- Ctrl+C to exit)")
            time.sleep(args.interval)
    except KeyboardInterrupt:
        return 0


if __name__ == "__main__":
    raise SystemExit(main())
