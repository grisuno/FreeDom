# Second Brain

*Last synthesized: 2026-10-25 | 290 files | 10 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `browser_ui.c`, `css.h`, `tab.c`. Architecturally it is 6 layers, dominant utility (168 files) across 10 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between include: browser_ui, src: css, src: tab: 20 extracted cross-community imports and 0 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (14% file coverage), 0 security findings, 6 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 290 |
| Symbols | 7511 |
| Resolved imports | 547 |
| Languages | c, h, py, sh |
| Communities | 10 |
| Doc coverage | 14% (40/290 files) |
| Security findings | 0 |
| Estimated read cost | ~219183 tokens (chars/4, offline so $0) |
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

- [include: browser_ui (59 files, cohesion 0.58)](./community_0_include_browser_ui.md)
- [src: css (53 files, cohesion 0.72)](./community_1_src_css.md)
- [src: tab (45 files, cohesion 0.69)](./community_2_src_tab.md)
- [src: text_shape (42 files, cohesion 0.55)](./community_3_src_text_shape.md)
- [include: page_view (19 files, cohesion 0.45)](./community_4_include_page_view.md)
- [include: browser (19 files, cohesion 0.55)](./community_5_include_browser.md)
- [src: local_store (16 files, cohesion 0.79)](./community_6_src_local_store.md)
- [include: secure_fetch (13 files, cohesion 0.54)](./community_7_include_secure_fetch.md)
- [include: prefetch (6 files, cohesion 0.56)](./community_8_include_prefetch.md)
- [orphans (18 files, cohesion 0.00)](./community_9_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `gui/browser_ui.c` | 175.4 (large, maybe generated) |
| `include/css.h` | 88.0 |
| `src/tab.c` | 68.6 |
| `src/freedom.c` | 60.8 |
| `src/css.c` | 56.7 (large, maybe generated) |

## Strongest Connections

- 0 -> 5: depends_on (strength 0.9, EXTRACTED)
- 0 -> 4: depends_on (strength 0.9, EXTRACTED)
- 0 -> 1: depends_on (strength 0.9, EXTRACTED)
- 0 -> 3: depends_on (strength 0.9, EXTRACTED)
- 0 -> 2: depends_on (strength 0.9, EXTRACTED)
- 0 -> 7: depends_on (strength 0.9, EXTRACTED)
- 0 -> 8: depends_on (strength 0.9, EXTRACTED)
- 0 -> 6: depends_on (strength 0.9, EXTRACTED)
- 4 -> 1: depends_on (strength 0.9, EXTRACTED)
- 6 -> 7: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
