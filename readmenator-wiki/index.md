# Second Brain

*Last synthesized: 2026-10-31 | 312 files | 13 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `browser_ui.c`, `css.h`, `tab.c`. Architecturally it is 6 layers, dominant utility (183 files) across 13 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between src: tab, include: browser_ui, src: text_shape: 20 extracted cross-community imports and 0 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (16% file coverage), 0 security findings, 6 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 312 |
| Symbols | 7747 |
| Resolved imports | 584 |
| Languages | c, h, py, sh |
| Communities | 13 |
| Doc coverage | 16% (50/312 files) |
| Security findings | 0 |
| Estimated read cost | ~231968 tokens (chars/4, offline so $0) |
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

- [src: tab (51 files, cohesion 0.68)](./community_0_src_tab.md)
- [include: browser_ui (46 files, cohesion 0.51)](./community_1_include_browser_ui.md)
- [src: text_shape (42 files, cohesion 0.54)](./community_2_src_text_shape.md)
- [src: css (38 files, cohesion 0.68)](./community_3_src_css.md)
- [include: page_view (37 files, cohesion 0.54)](./community_4_include_page_view.md)
- [include: browser (19 files, cohesion 0.55)](./community_5_include_browser.md)
- [include: svg_render (16 files, cohesion 0.52)](./community_6_include_svg_render.md)
- [src: http_cache (16 files, cohesion 0.79)](./community_7_src_http_cache.md)
- [include: secure_fetch (13 files, cohesion 0.54)](./community_8_include_secure_fetch.md)
- [include: tab (7 files, cohesion 0.41)](./community_9_include_tab.md)
- [include: prefetch (6 files, cohesion 0.56)](./community_10_include_prefetch.md)
- [include: subreq_batch (3 files, cohesion 0.67)](./community_11_include_subreq_batch.md)
- [orphans (18 files, cohesion 0.00)](./community_12_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `gui/browser_ui.c` | 182.2 (large, maybe generated) |
| `include/css.h` | 92.4 |
| `src/tab.c` | 76.9 |
| `src/freedom.c` | 63.0 |
| `src/css.c` | 60.8 (large, maybe generated) |

## Strongest Connections

- 1 -> 5: depends_on (strength 0.9, EXTRACTED)
- 1 -> 4: depends_on (strength 0.9, EXTRACTED)
- 1 -> 6: depends_on (strength 0.9, EXTRACTED)
- 1 -> 3: depends_on (strength 0.9, EXTRACTED)
- 1 -> 2: depends_on (strength 0.9, EXTRACTED)
- 1 -> 0: depends_on (strength 0.9, EXTRACTED)
- 1 -> 8: depends_on (strength 0.9, EXTRACTED)
- 1 -> 10: depends_on (strength 0.9, EXTRACTED)
- 1 -> 7: depends_on (strength 0.9, EXTRACTED)
- 1 -> 9: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
