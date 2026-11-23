# Second Brain

*Last synthesized: 2026-11-23 | 358 files | 15 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `browser_ui.c`, `css.h`, `tab.c`. Architecturally it is 6 layers, dominant utility (206 files) across 15 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between include: browser_ui, src: css, src: tab: 20 extracted cross-community imports and 0 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (21% file coverage), 0 security findings, 8 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 358 |
| Symbols | 8687 |
| Resolved imports | 664 |
| Languages | c, h, py, sh |
| Communities | 15 |
| Doc coverage | 21% (75/358 files) |
| Security findings | 0 |
| Estimated read cost | ~260133 tokens (chars/4, offline so $0) |
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

- [include: browser_ui (65 files, cohesion 0.58)](./community_0_include_browser_ui.md)
- [src: css (64 files, cohesion 0.70)](./community_1_src_css.md)
- [src: tab (56 files, cohesion 0.70)](./community_2_src_tab.md)
- [src: text_shape (54 files, cohesion 0.58)](./community_3_src_text_shape.md)
- [include: page_view (30 files, cohesion 0.45)](./community_4_include_page_view.md)
- [include: secure_fetch (19 files, cohesion 0.61)](./community_5_include_secure_fetch.md)
- [src: http_cache (13 files, cohesion 0.80)](./community_6_src_http_cache.md)
- [include: svg_render (12 files, cohesion 0.57)](./community_7_include_svg_render.md)
- [include: tab (7 files, cohesion 0.41)](./community_8_include_tab.md)
- [include: prefetch (6 files, cohesion 0.56)](./community_9_include_prefetch.md)
- [include: os_sandbox (6 files, cohesion 0.62)](./community_10_include_os_sandbox.md)
- [include: sha2 (3 files, cohesion 0.67)](./community_11_include_sha2.md)
- [include: subreq_batch (3 files, cohesion 0.67)](./community_12_include_subreq_batch.md)
- [tools (2 files, cohesion 1.00)](./community_13_tools.md)
- [orphans (18 files, cohesion 0.00)](./community_14_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `gui/browser_ui.c` | 203.3 (large, maybe generated) |
| `include/css.h` | 100.8 |
| `src/tab.c` | 85.2 |
| `src/page_view.c` | 63.2 (large, maybe generated) |
| `src/freedom.c` | 63.0 |

## Strongest Connections

- 0 -> 4: depends_on (strength 0.9, EXTRACTED)
- 0 -> 1: depends_on (strength 0.9, EXTRACTED)
- 0 -> 7: depends_on (strength 0.9, EXTRACTED)
- 0 -> 3: depends_on (strength 0.9, EXTRACTED)
- 0 -> 2: depends_on (strength 0.9, EXTRACTED)
- 0 -> 5: depends_on (strength 0.9, EXTRACTED)
- 0 -> 9: depends_on (strength 0.9, EXTRACTED)
- 0 -> 8: depends_on (strength 0.9, EXTRACTED)
- 1 -> 4: depends_on (strength 0.9, EXTRACTED)
- 1 -> 3: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
