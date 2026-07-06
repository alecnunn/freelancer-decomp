#!/usr/bin/env python3
"""Re-apply per-unit compiler flags that `fl bootstrap` drops from build.ninja.

`fl` (v0.1.x) generates `build.ninja` from `config/<id>/config.json`, but it only
emits the shared ``decomp`` base flags (plus its own ``/D_DLL`` for DLL units) —
each unit's extra ``cflags[<unit>].flags`` (e.g. ``/GX``, ``/G6``) are silently
filtered out. This makes those flags non-reproducible: a fresh bootstrap (CI, or
any clean checkout) builds without them and matches fewer functions.

This script closes that gap. After ``fl bootstrap`` it reads the declared per-unit
flags straight from ``config.json`` and appends any that are missing from that
unit's ``cxxflags`` line in ``build.ninja`` — so ``config.json`` stays the single
source of truth and the flags survive a clean bootstrap.

Idempotent: a flag already present on the line is left alone.
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path
from typing import Any

CONFIG_ID = "052103_release_1149_Ipatch_ver1254"
_STANZA = re.compile(r"/obj/(?P<unit>[^/]+)/src/")


def unit_flags(cflags: dict[str, Any], unit: str) -> list[str]:
    """The extra flags declared for a unit in config.json (empty if none)."""
    node = cflags.get(unit)
    if not isinstance(node, dict):
        return []
    return [f for f in node.get("flags", []) if f]


def main(argv: list[str] | None = None) -> int:
    argv = sys.argv[1:] if argv is None else argv
    repo = Path(argv[0]) if argv else Path(".")
    config = json.loads(
        (repo / "config" / CONFIG_ID / "config.json").read_text(encoding="utf-8")
    )
    cflags = config.get("cflags", {})

    ninja_path = repo / "build.ninja"
    lines = ninja_path.read_text(encoding="utf-8").splitlines()

    out: list[str] = []
    patched: list[str] = []
    i = 0
    while i < len(lines):
        line = lines[i]
        out.append(line)
        m = _STANZA.search(line)
        if m and i + 1 < len(lines) and lines[i + 1].lstrip().startswith("cxxflags"):
            unit = m.group("unit")  # e.g. "Common.dll"
            cxx = lines[i + 1]
            have = set(cxx.split())
            added = [f for f in unit_flags(cflags, unit) if f not in have]
            if added:
                cxx = cxx.rstrip() + " " + " ".join(added)
                patched.append(f"{unit}: +{' '.join(added)}")
            out.append(cxx)
            i += 2
            continue
        i += 1

    ninja_path.write_text("\n".join(out) + "\n", encoding="utf-8")
    if patched:
        print("apply_unit_cflags: " + "; ".join(patched))
    else:
        print("apply_unit_cflags: nothing to add (build.ninja already current)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
