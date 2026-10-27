# Second Brain

*Last synthesized: 2026-10-26 | 302 files | 12 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `browser_ui.c`, `css.h`, `tab.c`. Architecturally it is 6 layers, dominant utility (176 files) across 12 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between include: css, src: tab, include: browser_ui: 20 extracted cross-community imports and 0 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (14% file coverage), 0 security findings, 6 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 302 |
| Symbols | 7706 |
| Resolved imports | 565 |
| Languages | c, h, py, sh |
| Communities | 12 |
| Doc coverage | 14% (42/302 files) |
| Security findings | 0 |
| Estimated read cost | ~223386 tokens (chars/4, offline so $0) |
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

- [include: css (52 files, cohesion 0.72)](./community_0_include_css.md)
- [src: tab (48 files, cohesion 0.67)](./community_1_src_tab.md)
- [include: browser_ui (44 files, cohesion 0.47)](./community_2_include_browser_ui.md)
- [src: text_shape (42 files, cohesion 0.54)](./community_3_src_text_shape.md)
- [include: local_store (24 files, cohesion 0.81)](./community_4_include_local_store.md)
- [include: page_view (19 files, cohesion 0.45)](./community_5_include_page_view.md)
- [include: browser (19 files, cohesion 0.55)](./community_6_include_browser.md)
- [include: svg_render (14 files, cohesion 0.46)](./community_7_include_svg_render.md)
- [include: secure_fetch (13 files, cohesion 0.54)](./community_8_include_secure_fetch.md)
- [include: prefetch (6 files, cohesion 0.56)](./community_9_include_prefetch.md)
- [include: sha2 (3 files, cohesion 0.67)](./community_10_include_sha2.md)
- [orphans (18 files, cohesion 0.00)](./community_11_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `gui/browser_ui.c` | 180.2 (large, maybe generated) |
| `include/css.h` | 88.0 |
| `src/tab.c` | 68.7 |
| `src/freedom.c` | 60.8 |
| `src/css.c` | 56.7 (large, maybe generated) |

## Strongest Connections

- 2 -> 6: depends_on (strength 0.9, EXTRACTED)
- 2 -> 5: depends_on (strength 0.9, EXTRACTED)
- 2 -> 0: depends_on (strength 0.9, EXTRACTED)
- 2 -> 7: depends_on (strength 0.9, EXTRACTED)
- 2 -> 3: depends_on (strength 0.9, EXTRACTED)
- 2 -> 1: depends_on (strength 0.9, EXTRACTED)
- 2 -> 8: depends_on (strength 0.9, EXTRACTED)
- 2 -> 9: depends_on (strength 0.9, EXTRACTED)
- 2 -> 4: depends_on (strength 0.9, EXTRACTED)
- 7 -> 0: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
