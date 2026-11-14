# Second Brain

*Last synthesized: 2026-11-14 | 325 files | 14 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `browser_ui.c`, `css.h`, `tab.c`. Architecturally it is 6 layers, dominant utility (190 files) across 14 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between include: css, src: tab, include: browser_ui: 20 extracted cross-community imports and 0 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (17% file coverage), 0 security findings, 6 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 325 |
| Symbols | 7951 |
| Resolved imports | 623 |
| Languages | c, h, py, sh |
| Communities | 14 |
| Doc coverage | 17% (54/325 files) |
| Security findings | 0 |
| Estimated read cost | ~238736 tokens (chars/4, offline so $0) |
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

- [include: css (56 files, cohesion 0.69)](./community_0_include_css.md)
- [src: tab (51 files, cohesion 0.69)](./community_1_src_tab.md)
- [include: browser_ui (47 files, cohesion 0.52)](./community_2_include_browser_ui.md)
- [src: text_shape (40 files, cohesion 0.52)](./community_3_src_text_shape.md)
- [include: page_view (26 files, cohesion 0.47)](./community_4_include_page_view.md)
- [include: secure_fetch (24 files, cohesion 0.60)](./community_5_include_secure_fetch.md)
- [include: browser (19 files, cohesion 0.55)](./community_6_include_browser.md)
- [src: http_cache (13 files, cohesion 0.80)](./community_7_src_http_cache.md)
- [include: svg_render (12 files, cohesion 0.57)](./community_8_include_svg_render.md)
- [include: tab (7 files, cohesion 0.41)](./community_9_include_tab.md)
- [include: prefetch (6 files, cohesion 0.56)](./community_10_include_prefetch.md)
- [include: sha2 (3 files, cohesion 0.67)](./community_11_include_sha2.md)
- [include: subreq_batch (3 files, cohesion 0.67)](./community_12_include_subreq_batch.md)
- [orphans (18 files, cohesion 0.00)](./community_13_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `gui/browser_ui.c` | 182.4 (large, maybe generated) |
| `include/css.h` | 96.7 |
| `src/tab.c` | 81.4 |
| `src/freedom.c` | 63.0 |
| `src/css.c` | 60.8 (large, maybe generated) |

## Strongest Connections

- 2 -> 6: depends_on (strength 0.9, EXTRACTED)
- 2 -> 4: depends_on (strength 0.9, EXTRACTED)
- 2 -> 0: depends_on (strength 0.9, EXTRACTED)
- 2 -> 8: depends_on (strength 0.9, EXTRACTED)
- 2 -> 3: depends_on (strength 0.9, EXTRACTED)
- 2 -> 1: depends_on (strength 0.9, EXTRACTED)
- 2 -> 5: depends_on (strength 0.9, EXTRACTED)
- 2 -> 10: depends_on (strength 0.9, EXTRACTED)
- 2 -> 9: depends_on (strength 0.9, EXTRACTED)
- 0 -> 4: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
