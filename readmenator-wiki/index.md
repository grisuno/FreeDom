# Second Brain

*Last synthesized: 2026-11-27 | 427 files | 15 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `browser_ui.c`, `css.h`, `tab.c`. Architecturally it is 6 layers, dominant utility (262 files) across 15 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between src: tab, include: browser_ui, include: css: 20 extracted cross-community imports and 0 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (26% file coverage), 0 security findings, 10 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 427 |
| Symbols | 9073 |
| Resolved imports | 773 |
| Languages | c, h, py, sh |
| Communities | 15 |
| Doc coverage | 26% (112/427 files) |
| Security findings | 0 |
| Estimated read cost | ~270000 tokens (chars/4, offline so $0) |
| Large files (>256KB, maybe generated) | 5: `browser_ui.c`, `css.c`, `page_view.c`, `test_css.c`, `test_page_view.c` |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target freedom-0.0.3
```

## Concept Wiki

- [src: tab (72 files, cohesion 0.72)](./community_0_src_tab.md)
- [include: browser_ui (69 files, cohesion 0.53)](./community_1_include_browser_ui.md)
- [include: css (58 files, cohesion 0.69)](./community_2_include_css.md)
- [src: text_shape (55 files, cohesion 0.60)](./community_3_src_text_shape.md)
- [include: page_view (30 files, cohesion 0.49)](./community_4_include_page_view.md)
- [include: http_cache (28 files, cohesion 0.77)](./community_5_include_http_cache.md)
- [include: secure_fetch (24 files, cohesion 0.64)](./community_6_include_secure_fetch.md)
- [include: bui_chrome (20 files, cohesion 0.61)](./community_7_include_bui_chrome.md)
- [include: svg_render (14 files, cohesion 0.62)](./community_8_include_svg_render.md)
- [include: fb_cmdline (11 files, cohesion 0.44)](./community_9_include_fb_cmdline.md)
- [include: download (8 files, cohesion 0.78)](./community_10_include_download.md)
- [include: prefetch (8 files, cohesion 0.64)](./community_11_include_prefetch.md)
- [include: pres_hints (7 files, cohesion 0.60)](./community_12_include_pres_hints.md)
- [tools (3 files, cohesion 1.00)](./community_13_tools.md)
- [orphans (20 files, cohesion 0.00)](./community_14_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `gui/browser_ui.c` | 218.0 (large, maybe generated) |
| `include/css.h` | 104.8 |
| `src/tab.c` | 91.9 |
| `src/page_view.c` | 63.4 (large, maybe generated) |
| `src/freedom.c` | 63.0 |

## Strongest Connections

- 2 -> 4: depends_on (strength 0.9, EXTRACTED)
- 4 -> 0: depends_on (strength 0.9, EXTRACTED)
- 7 -> 0: depends_on (strength 0.9, EXTRACTED)
- 1 -> 0: depends_on (strength 0.9, EXTRACTED)
- 1 -> 12: depends_on (strength 0.9, EXTRACTED)
- 1 -> 4: depends_on (strength 0.9, EXTRACTED)
- 1 -> 2: depends_on (strength 0.9, EXTRACTED)
- 1 -> 8: depends_on (strength 0.9, EXTRACTED)
- 1 -> 3: depends_on (strength 0.9, EXTRACTED)
- 1 -> 10: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
