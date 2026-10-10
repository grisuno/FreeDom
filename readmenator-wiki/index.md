# Second Brain

*Last synthesized: 2026-10-10 | 262 files | 11 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `browser_ui.c`, `css.h`, `tab.c`. Architecturally it is 6 layers, dominant utility (154 files) across 11 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between src, include: browser_ui, include: css: 20 extracted cross-community imports and 0 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (10% file coverage), 0 security findings, 4 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 262 |
| Symbols | 6260 |
| Resolved imports | 507 |
| Languages | c, h, py, sh |
| Communities | 11 |
| Doc coverage | 10% (27/262 files) |
| Security findings | 0 |
| Estimated read cost | ~182391 tokens (chars/4, offline so $0) |
| Large files (>256KB, maybe generated) | 4: `browser_ui.c`, `css.c`, `page_view.c`, `test_css.c` |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target freedom-0.0.3
```

## Concept Wiki

- [src (59 files, cohesion 0.75)](./community_0_src.md)
- [include: browser_ui (47 files, cohesion 0.53)](./community_1_include_browser_ui.md)
- [include: css (40 files, cohesion 0.73)](./community_2_include_css.md)
- [include: page_view (31 files, cohesion 0.50)](./community_3_include_page_view.md)
- [include: text_shape (20 files, cohesion 0.55)](./community_4_include_text_shape.md)
- [include: local_store (16 files, cohesion 0.83)](./community_5_include_local_store.md)
- [gui (15 files, cohesion 0.50)](./community_6_gui.md)
- [include: secure_fetch (10 files, cohesion 0.62)](./community_7_include_secure_fetch.md)
- [include: download (8 files, cohesion 0.78)](./community_8_include_download.md)
- [include: import_map (4 files, cohesion 0.75)](./community_9_include_import_map.md)
- [orphans (12 files, cohesion 0.00)](./community_10_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `gui/browser_ui.c` | 141.1 (large, maybe generated) |
| `include/css.h` | 81.1 |
| `src/tab.c` | 56.0 |
| `src/freedom.c` | 52.6 |
| `src/css.c` | 51.1 (large, maybe generated) |

## Strongest Connections

- 3 -> 0: depends_on (strength 0.9, EXTRACTED)
- 6 -> 0: depends_on (strength 0.9, EXTRACTED)
- 6 -> 3: depends_on (strength 0.9, EXTRACTED)
- 1 -> 3: depends_on (strength 0.9, EXTRACTED)
- 1 -> 2: depends_on (strength 0.9, EXTRACTED)
- 1 -> 6: depends_on (strength 0.9, EXTRACTED)
- 1 -> 4: depends_on (strength 0.9, EXTRACTED)
- 1 -> 8: depends_on (strength 0.9, EXTRACTED)
- 1 -> 0: depends_on (strength 0.9, EXTRACTED)
- 1 -> 5: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
