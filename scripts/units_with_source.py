#!/usr/bin/env python3
"""Print the space-separated units whose unity entrypoint has real source.

A unit's entrypoint (`src/<unit>.cpp`) is scaffolded all-comments by
`fl bootstrap`; it only has content once modules are `#include`d into it. The PR
build gate compiles exactly these units so an empty stub can't fail the check and
a real compile error does. Run from the repo root (reads `objdiff.json`).
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path


def main() -> int:
    units = json.loads(Path("objdiff.json").read_text(encoding="utf-8")).get("units", [])
    out: list[str] = []
    for u in units:
        src = (u.get("metadata") or {}).get("source_path", "")
        p = Path(src)
        if p.exists() and re.search(r"^\s*#include", p.read_text(errors="ignore"), re.M):
            out.append(u["name"].split("/")[-1])
    print(" ".join(out))
    return 0


if __name__ == "__main__":
    sys.exit(main())
