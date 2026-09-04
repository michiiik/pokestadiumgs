"""Tests for tools/fleet_dashboard.py's rendering.

render_dashboard is the only piece worth pinning: a pure function of a
parsed `fleetctl status --json` document and an injected "now" (never the
real clock, so every test is deterministic). The live refresh loop around
it is a thin, hard-to-usefully-unit-test wrapper (subprocess + sleep) --
this is why the formatting logic is split out as its own function at all.
"""

import datetime
import unittest

import fleet_dashboard as dashboard


def _now() -> datetime.datetime:
    return datetime.datetime(2026, 9, 4, 22, 0, 0, tzinfo=datetime.timezone.utc)


class RenderDashboardTests(unittest.TestCase):
    def test_empty_fleet_shows_none_placeholders(self) -> None:
        status = {"runs": [], "cooldowns": {}, "running": 0, "queued": 0, "running_by_agent": {}, "metrics": []}
        out = dashboard.render_dashboard(status, _now())
        self.assertIn("running=0  queued=0  (none)", out)
        self.assertIn("COOLDOWNS (0 active):", out)
        self.assertIn("ACTIVE RUNS (0):", out)

    def test_only_active_statuses_are_listed(self) -> None:
        status = {
            "runs": [
                {"id": "a", "status": "running", "file": "disasm/src/x.c", "agent": "codex", "model": "m", "owners": 5, "matched": 0},
                {"id": "b", "status": "merging", "file": "disasm/src/x.c", "agent": "codex", "model": "m", "owners": 5, "matched": 1},
                {"id": "c", "status": "pr_open", "file": "disasm/src/x.c", "agent": "codex", "model": "m", "owners": 5, "matched": 1},
                {"id": "d", "status": "done", "file": "disasm/src/x.c", "agent": "codex", "model": "m", "owners": 5, "matched": 0},
                {"id": "e", "status": "queued", "file": "disasm/src/x.c", "agent": "codex", "model": "m", "owners": 5, "matched": 0},
                {"id": "f", "status": "requeued", "file": "disasm/src/x.c", "agent": "codex", "model": "m", "owners": 5, "matched": 0},
            ],
            "cooldowns": {}, "running": 1, "queued": 2, "running_by_agent": {"codex": 1}, "metrics": [],
        }
        out = dashboard.render_dashboard(status, _now())
        self.assertIn("ACTIVE RUNS (3):", out)
        self.assertIn(" a ", out)
        self.assertIn(" b ", out)
        self.assertIn(" c ", out)
        self.assertNotIn(" d ", out)
        self.assertNotIn(" e ", out)
        self.assertNotIn(" f ", out)

    def test_expired_cooldown_is_not_shown_as_active(self) -> None:
        status = {
            "runs": [], "running": 0, "queued": 0, "running_by_agent": {}, "metrics": [],
            "cooldowns": {
                "codex:m": "2026-09-04T21:00:00+00:00",  # already in the past relative to _now()
                "gemini:m": "2026-09-04T23:00:00+00:00",  # still an hour out
            },
        }
        out = dashboard.render_dashboard(status, _now())
        self.assertIn("COOLDOWNS (1 active):", out)
        self.assertIn("gemini:m", out)
        self.assertNotIn("codex:m", out)

    def test_cooldowns_are_sorted_soonest_first(self) -> None:
        status = {
            "runs": [], "running": 0, "queued": 0, "running_by_agent": {}, "metrics": [],
            "cooldowns": {
                "far:m": "2026-09-05T02:00:00+00:00",
                "soon:m": "2026-09-04T22:05:00+00:00",
                "mid:m": "2026-09-04T23:00:00+00:00",
            },
        }
        out = dashboard.render_dashboard(status, _now())
        soon_pos = out.index("soon:m")
        mid_pos = out.index("mid:m")
        far_pos = out.index("far:m")
        self.assertLess(soon_pos, mid_pos)
        self.assertLess(mid_pos, far_pos)

    def test_human_remaining_formats_by_magnitude(self) -> None:
        now = _now()
        self.assertEqual(dashboard._human_remaining(now + datetime.timedelta(seconds=45), now), "45s")
        self.assertEqual(dashboard._human_remaining(now + datetime.timedelta(minutes=5, seconds=3), now), "5m03s")
        self.assertEqual(dashboard._human_remaining(now + datetime.timedelta(hours=1, minutes=30), now), "1h30m")
        self.assertEqual(dashboard._human_remaining(now - datetime.timedelta(seconds=1), now), "expired")

    def test_metrics_table_includes_every_agent_row(self) -> None:
        status = {
            "runs": [], "cooldowns": {}, "running": 0, "queued": 0, "running_by_agent": {},
            "metrics": [
                {"agent": "codex", "runs": 10, "iterations": 40, "accepts": 3, "accepts_per_wall_hour": 0.5, "accepts_per_window": 1.2, "on_cooldown": False},
                {"agent": "gemini", "runs": 5, "iterations": 20, "accepts": 0, "accepts_per_wall_hour": 0.0, "accepts_per_window": 0.0, "on_cooldown": True},
            ],
        }
        out = dashboard.render_dashboard(status, _now())
        self.assertIn("codex", out)
        self.assertIn("gemini", out)
        # on_cooldown renders distinctly from a not-on-cooldown agent.
        codex_line = next(line for line in out.splitlines() if line.strip().startswith("codex"))
        gemini_line = next(line for line in out.splitlines() if line.strip().startswith("gemini"))
        self.assertIn("-", codex_line)
        self.assertIn("yes", gemini_line)

    def test_long_note_is_truncated_not_wrapped(self) -> None:
        status = {
            "cooldowns": {}, "running": 1, "queued": 0, "running_by_agent": {"codex": 1}, "metrics": [],
            "runs": [{
                "id": "a", "status": "running", "file": "disasm/src/x.c", "agent": "codex", "model": "m",
                "owners": 1, "matched": 0,
                "note": "x" * 200,
            }],
        }
        out = dashboard.render_dashboard(status, _now())
        # A single, unbroken 200-char note must not blow out the line width
        # unbounded -- _truncate caps it well below that.
        longest_line = max(len(line) for line in out.splitlines())
        self.assertLess(longest_line, 200)


if __name__ == "__main__":
    unittest.main()
