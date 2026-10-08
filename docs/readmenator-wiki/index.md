# Second Brain

*Last synthesized: 2026-10-07 | 255 files | 11 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `browser_ui.c`, `css.h`, `tab.c`. Architecturally it is 6 layers, dominant utility (149 files) across 11 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between src, include: browser_ui, include: css: 20 extracted cross-community imports and 0 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (10% file coverage), 0 security findings, 4 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 255 |
| Symbols | 6084 |
| Resolved imports | 484 |
| Languages | c, h, py, sh |
| Communities | 11 |
| Doc coverage | 10% (26/255 files) |
| Security findings | 0 |
| Estimated read cost | ~176920 tokens (chars/4, offline so $0) |
| Large files (>256KB, maybe generated) | 3: `browser_ui.c`, `css.c`, `page_view.c` |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target readmenator_FreeDom_wx9txdod
```

## Concept Wiki

- [src (59 files, cohesion 0.75)](./community_0_src.md)
- [include: browser_ui (47 files, cohesion 0.54)](./community_1_include_browser_ui.md)
- [include: css (44 files, cohesion 0.77)](./community_2_include_css.md)
- [include: page_view (31 files, cohesion 0.52)](./community_3_include_page_view.md)
- [include: local_store (16 files, cohesion 0.83)](./community_4_include_local_store.md)
- [gui (15 files, cohesion 0.50)](./community_5_gui.md)
- [include: secure_fetch (10 files, cohesion 0.62)](./community_6_include_secure_fetch.md)
- [include: request_policy (9 files, cohesion 0.53)](./community_7_include_request_policy.md)
- [include: download (8 files, cohesion 0.78)](./community_8_include_download.md)
- [include: import_map (4 files, cohesion 0.75)](./community_9_include_import_map.md)
- [orphans (12 files, cohesion 0.00)](./community_10_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `gui/browser_ui.c` | 136.5 (large, maybe generated) |
| `include/css.h` | 79.1 |
| `src/tab.c` | 55.9 |
| `src/page_view.c` | 50.2 (large, maybe generated) |
| `include/html_parse.h` | 48.4 |

## Strongest Connections

- 3 -> 0: depends_on (strength 0.9, EXTRACTED)
- 5 -> 0: depends_on (strength 0.9, EXTRACTED)
- 5 -> 3: depends_on (strength 0.9, EXTRACTED)
- 1 -> 3: depends_on (strength 0.9, EXTRACTED)
- 1 -> 2: depends_on (strength 0.9, EXTRACTED)
- 1 -> 5: depends_on (strength 0.9, EXTRACTED)
- 1 -> 7: depends_on (strength 0.9, EXTRACTED)
- 1 -> 8: depends_on (strength 0.9, EXTRACTED)
- 1 -> 0: depends_on (strength 0.9, EXTRACTED)
- 1 -> 4: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
