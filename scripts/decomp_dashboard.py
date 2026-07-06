#!/usr/bin/env python3
"""Decompilation progress dashboard tooling.

Two subcommands drive the merge-to-main dashboard workflow:

  snapshot  Turn an ``objdiff-cli report`` (plus the current git commit) into a
            single timestamped progress record.
  publish   Append a snapshot to the append-only history that lives on the
            ``gh-pages`` branch and (re)materialise the static dashboard there.

The history is the source of truth for the burn-up / burn-down charts; every
merge to main adds exactly one record. Publishing is idempotent: re-running for
a commit that is already the latest record is a no-op, so re-triggered workflows
never double-count.
"""
from __future__ import annotations

import argparse
import json
import shutil
import subprocess
import sys
from datetime import datetime, timezone
from pathlib import Path
from typing import Any


def _run(cmd: list[str], cwd: Path | None = None) -> str:
    """Run a command and return its stripped stdout (raising on failure)."""
    result = subprocess.run(
        cmd, cwd=cwd, check=True, capture_output=True, text=True
    )
    return result.stdout.strip()


def _measures(node: dict[str, Any]) -> dict[str, Any]:
    """Extract the subset of objdiff measures we chart, coercing string ints."""
    m = node.get("measures", {}) or {}

    def num(key: str) -> float | int:
        v = m.get(key, 0)
        # objdiff emits large byte counts as strings; keep them numeric.
        if isinstance(v, str):
            return int(v) if v.isdigit() else float(v)
        return v

    return {
        "matched_functions": int(num("matched_functions")),
        "total_functions": int(num("total_functions")),
        "matched_functions_percent": round(float(num("matched_functions_percent")), 4),
        "matched_code": int(num("matched_code")),
        "total_code": int(num("total_code")),
        "matched_code_percent": round(float(num("matched_code_percent")), 4),
        "fuzzy_match_percent": round(float(num("fuzzy_match_percent")), 4),
    }


def git_info(repo: Path) -> dict[str, str]:
    """Collect commit identity for the current HEAD (the merge commit in CI)."""
    fmt = {
        "commit": "%H",
        "short": "%h",
        "subject": "%s",
        "author": "%an",
        "date": "%cI",  # committer date, strict ISO-8601
    }
    out: dict[str, str] = {}
    for key, spec in fmt.items():
        try:
            out[key] = _run(["git", "-C", str(repo), "log", "-1", f"--pretty=format:{spec}"])
        except Exception:
            out[key] = ""
    return out


def cmd_snapshot(args: argparse.Namespace) -> None:
    """Build one progress record from a report + git and write it out."""
    report = json.loads(Path(args.report).read_text(encoding="utf-8"))
    repo = Path(args.repo).resolve()
    info = git_info(repo)

    units: list[dict[str, Any]] = []
    for unit in report.get("units", []):
        name = (unit.get("name") or "").removeprefix("src/")
        um = _measures(unit)
        # Skip units with no code at all (unconfigured/empty stubs) unless matched.
        if um["total_functions"] == 0 and um["matched_functions"] == 0:
            continue
        um["name"] = name
        units.append(um)
    units.sort(key=lambda u: u["matched_functions"], reverse=True)

    snapshot: dict[str, Any] = {
        "timestamp": info.get("date") or datetime.now(timezone.utc).isoformat(),
        "commit": info.get("commit", ""),
        "short": info.get("short", ""),
        "subject": info.get("subject", ""),
        "author": info.get("author", ""),
        "project": _measures(report),
        "units": units,
    }
    Path(args.out).write_text(json.dumps(snapshot, indent=2) + "\n", encoding="utf-8")
    p = snapshot["project"]
    print(
        f"snapshot {snapshot['short']}: "
        f"{p['matched_functions']}/{p['total_functions']} functions "
        f"({p['matched_functions_percent']:.3f}%), code {p['matched_code_percent']:.3f}%"
    )


def cmd_publish(args: argparse.Namespace) -> None:
    """Append a snapshot to the gh-pages history and refresh the dashboard."""
    snapshot = json.loads(Path(args.snapshot).read_text(encoding="utf-8"))
    pages = Path(args.pages)
    data = pages / "data"
    data.mkdir(parents=True, exist_ok=True)

    hist_path = data / "history.json"
    history: list[dict[str, Any]] = []
    if hist_path.exists():
        try:
            history = json.loads(hist_path.read_text(encoding="utf-8"))
        except Exception:
            history = []

    # Idempotent: replace-in-place if this exact commit is already the tail,
    # otherwise append. Never duplicate a commit.
    if history and history[-1].get("commit") == snapshot.get("commit"):
        history[-1] = snapshot
        action = "updated"
    elif any(h.get("commit") == snapshot.get("commit") for h in history):
        history = [snapshot if h.get("commit") == snapshot.get("commit") else h for h in history]
        action = "rewrote"
    else:
        history.append(snapshot)
        action = "appended"

    hist_path.write_text(json.dumps(history, indent=1) + "\n", encoding="utf-8")
    (data / "latest.json").write_text(json.dumps(snapshot, indent=2) + "\n", encoding="utf-8")

    # Materialise the static site (template is the source of truth; copying it
    # each publish lets dashboard tweaks land without a manual gh-pages edit).
    template = Path(args.template)
    if template.exists():
        shutil.copyfile(template, pages / "index.html")
    (pages / ".nojekyll").write_text("", encoding="utf-8")

    print(f"{action} history: {len(history)} records -> {hist_path}")


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Decomp progress dashboard tooling")
    sub = parser.add_subparsers(dest="cmd", required=True)

    sp = sub.add_parser("snapshot", help="report.json + git -> one progress record")
    sp.add_argument("--report", required=True, help="objdiff-cli report JSON")
    sp.add_argument("--repo", default=".", help="repo root (for git info)")
    sp.add_argument("--out", default="snapshot.json", help="output record path")
    sp.set_defaults(func=cmd_snapshot)

    pp = sub.add_parser("publish", help="append snapshot to gh-pages history")
    pp.add_argument("--snapshot", required=True, help="snapshot record JSON")
    pp.add_argument("--pages", required=True, help="checked-out gh-pages dir")
    pp.add_argument(
        "--template",
        default=str(Path(__file__).parent / "dashboard" / "index.html"),
        help="dashboard HTML template",
    )
    pp.set_defaults(func=cmd_publish)

    args = parser.parse_args(argv)
    args.func(args)
    return 0


if __name__ == "__main__":
    sys.exit(main())
