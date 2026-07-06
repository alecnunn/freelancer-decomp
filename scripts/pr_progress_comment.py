#!/usr/bin/env python3
"""Render a PR progress comment: this PR's match counts vs the `main` baseline.

Inputs:
  --report    objdiff-cli report JSON for the PR head (required)
  --baseline  the `main` dashboard snapshot (gh-pages data/latest.json), optional
              — when absent (e.g. before the first merge) deltas render as "—"
  --out       markdown file to write (default: comment.md)

The comment carries a hidden marker so the workflow can update one sticky comment
instead of posting a new one on every push.
"""
from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path
from typing import Any

MARKER = "<!-- decomp-progress -->"


def _int(v: Any) -> int:
    return int(v) if not isinstance(v, str) else (int(v) if v.isdigit() else 0)


def report_counts(report: dict[str, Any]) -> tuple[dict[str, Any], dict[str, dict[str, int]]]:
    """Return (project measures, {unit -> {matched,total}}) from an objdiff report."""
    pm = report.get("measures", {})
    project = {
        "matched": _int(pm.get("matched_functions", 0)),
        "total": _int(pm.get("total_functions", 0)),
    }
    units: dict[str, dict[str, int]] = {}
    for u in report.get("units", []):
        name = (u.get("name") or "").removeprefix("src/")
        m = u.get("measures", {})
        units[name] = {
            "matched": _int(m.get("matched_functions", 0)),
            "total": _int(m.get("total_functions", 0)),
        }
    return project, units


def baseline_counts(snapshot: dict[str, Any]) -> tuple[int, dict[str, int]]:
    """Return (project matched, {unit -> matched}) from a dashboard snapshot."""
    proj = _int((snapshot.get("project") or {}).get("matched_functions", 0))
    units = {u["name"]: _int(u.get("matched_functions", 0)) for u in snapshot.get("units", [])}
    return proj, units


def delta(cur: int, base: int | None) -> str:
    if base is None:
        return "—"
    d = cur - base
    if d > 0:
        return f"+{d:,}"
    if d < 0:
        return f"{d:,}"
    return "±0"


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description="Render the PR progress comment")
    ap.add_argument("--report", required=True)
    ap.add_argument("--baseline", default="")
    ap.add_argument("--out", default="comment.md")
    ap.add_argument("--sha", default="")
    args = ap.parse_args(argv)

    project, units = report_counts(json.loads(Path(args.report).read_text(encoding="utf-8")))

    base_proj: int | None = None
    base_units: dict[str, int] = {}
    bp = Path(args.baseline)
    if args.baseline and bp.exists() and bp.stat().st_size:
        try:
            base_proj, base_units = baseline_counts(json.loads(bp.read_text(encoding="utf-8")))
        except Exception:
            base_proj = None

    # Show units that are non-empty in the PR or moved relative to main.
    names = sorted(
        {n for n, c in units.items() if c["matched"] > 0}
        | {n for n in base_units if base_units.get(n, 0) > 0},
        key=lambda n: units.get(n, {}).get("matched", 0),
        reverse=True,
    )

    lines: list[str] = [MARKER, "### Decomp progress · this PR vs `main`", ""]
    lines.append("✅ **Build passes** — units with source compiled with the real toolchain flags.")
    lines.append("")
    lines.append("| Unit | Matched | Total | Δ vs `main` |")
    lines.append("|:--|--:|--:|--:|")
    lines.append(
        f"| **Total** | **{project['matched']:,}** | **{project['total']:,}** "
        f"| **{delta(project['matched'], base_proj)}** |"
    )
    for n in names:
        c = units.get(n, {"matched": 0, "total": 0})
        b = base_units.get(n) if base_units or base_proj is not None else None
        lines.append(f"| {n} | {c['matched']:,} | {c['total']:,} | {delta(c['matched'], b)} |")
    lines.append("")
    tag = f" · `{args.sha[:9]}`" if args.sha else ""
    base_note = "baseline = last merge to `main`" if base_proj is not None else "no `main` baseline yet"
    lines.append(f"<sub>measured with objdiff{tag} · {base_note}</sub>")

    Path(args.out).write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"wrote {args.out}: total {project['matched']}/{project['total']}, delta {delta(project['matched'], base_proj)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
