# Decompilation progress dashboard

A self-updating dashboard that tracks matching-decomp progress over time. Every
merge to `main` measures the whole project with objdiff and appends one record
to a running history; a static site renders it as burn-up / per-unit charts and
publishes to GitHub Pages.

- **Live site:** `https://<owner>.github.io/<repo>/` (once Pages is enabled)
- **Raw data:** `…/data/history.json` (append-only time series), `…/data/latest.json`

## How it works

```
merge to main
   │
   ▼
[CI] fl bootstrap → fl build → objdiff-cli report generate  (report.json)
   │
   ▼
scripts/decomp_dashboard.py snapshot   → snapshot.json   (one timestamped record)
   │
   ▼
fetch gh-pages:data/history.json  →  publish (append)  →  force-push orphan gh-pages
   │
   ▼
GitHub Pages serves index.html, which fetches data/history.json and charts it
```

- **`main`** holds only source + the tooling (`.github/workflows/decomp-dashboard.yml`,
  `scripts/decomp_dashboard.py`, `scripts/dashboard/index.html`). No generated
  data is ever committed to `main`.
- **`gh-pages`** is an orphan ("bare") branch — unrelated to `main`'s history —
  containing just the published site (`index.html`, `data/*.json`, `.nojekyll`).
  Each run force-pushes a single fresh commit; the *data* history accumulates
  inside `history.json`, not in the branch's git history.

### What's measured

Straight from `objdiff-cli report generate`, at project and per-unit granularity:

| Field | Meaning |
| --- | --- |
| `matched_functions` / `total_functions` | fully byte-identical functions |
| `matched_functions_percent` | the headline burn-up metric |
| `matched_code` / `matched_code_percent` | matched code *bytes* |
| `fuzzy_match_percent` | instruction-level similarity across everything |

The dashboard shows a burn-up of matched functions (toggle to *Remaining* for the
burn-down view, or *Code %*), a stacked per-unit contribution over time, the
current per-unit standing, and a recent-merges table with per-merge deltas.

## One-time setup

1. **Wire up `fl` in the workflow.** The `Install the fl toolchain driver` step
   in `.github/workflows/decomp-dashboard.yml` is a placeholder — replace it with
   however you obtain `fl` in CI, e.g.:
   ```yaml
   - name: Install the fl toolchain driver
     run: cargo install --locked --git https://github.com/<you>/fl fl
   ```
   Everything downstream (`fl bootstrap`/`build`, `objdiff-cli`) is fetched by
   `fl bootstrap`.

2. **Enable GitHub Pages.** Repo → *Settings → Pages* → *Build and deployment* →
   *Source: Deploy from a branch* → **Branch: `gh-pages` / `(root)`**. The branch
   is created automatically by the first successful workflow run.

3. **Push to `main`.** The workflow runs on merge/push to `main` (or trigger it
   manually via *Actions → Decomp Progress Dashboard → Run workflow*).

## Local usage

Regenerate a snapshot from a local build and preview the site without CI:

```sh
# 1. build + measure (needs the fl toolchain set up locally)
objdiff-cli report generate -o report.json
python scripts/decomp_dashboard.py snapshot --report report.json --out snapshot.json

# 2. append to a local copy of the site and serve it
python scripts/decomp_dashboard.py publish --snapshot snapshot.json --pages site
python -m http.server -d site 8000      # → http://localhost:8000
```

`publish` is idempotent per commit: re-running for the same HEAD replaces that
record instead of duplicating it.

### Seeding / backfilling history

To seed the burn-up curve with the project's real history, check out past
milestone commits, rebuild, and snapshot each into the same `site/`:

```sh
for sha in $(git rev-list --reverse --no-merges main); do
  git checkout -q "$sha"
  fl build Common >/dev/null 2>&1 || true
  objdiff-cli report generate -o report.json
  python /path/to/decomp_dashboard.py snapshot --report report.json --out snap.json
  python /path/to/decomp_dashboard.py publish --snapshot snap.json --pages site
done
git checkout -q main
```

(Run the script from a path *outside* the repo so it survives the checkouts.)
Going forward the workflow appends one record per merge automatically.

## Files

| Path | Role |
| --- | --- |
| `.github/workflows/decomp-dashboard.yml` | CI: measure on merge, publish to gh-pages |
| `scripts/decomp_dashboard.py` | `snapshot` (report → record) + `publish` (append + site) |
| `scripts/dashboard/index.html` | the static dashboard (Chart.js, fetches the history) |
