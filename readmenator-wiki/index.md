# Second Brain

*Last synthesized: 2026-10-16 | 265 files | 10 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `browser_ui.c`, `css.h`, `tab.c`. Architecturally it is 6 layers, dominant utility (156 files) across 10 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between src, include: browser_ui, include: css: 20 extracted cross-community imports and 0 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (11% file coverage), 0 security findings, 4 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 265 |
| Symbols | 6457 |
| Resolved imports | 516 |
| Languages | c, h, py, sh |
| Communities | 10 |
| Doc coverage | 11% (29/265 files) |
| Security findings | 0 |
| Estimated read cost | ~188854 tokens (chars/4, offline so $0) |
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

- [src (59 files, cohesion 0.74)](./community_0_src.md)
- [include: browser_ui (51 files, cohesion 0.57)](./community_1_include_browser_ui.md)
- [include: css (44 files, cohesion 0.73)](./community_2_include_css.md)
- [include: page_view (30 files, cohesion 0.48)](./community_3_include_page_view.md)
- [include: text_shape (20 files, cohesion 0.55)](./community_4_include_text_shape.md)
- [include: local_store (16 files, cohesion 0.83)](./community_5_include_local_store.md)
- [gui (15 files, cohesion 0.50)](./community_6_gui.md)
- [include: secure_fetch (10 files, cohesion 0.62)](./community_7_include_secure_fetch.md)
- [include: prefetch (8 files, cohesion 0.64)](./community_8_include_prefetch.md)
- [orphans (12 files, cohesion 0.00)](./community_9_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `gui/browser_ui.c` | 142.8 (large, maybe generated) |
| `include/css.h` | 81.5 |
| `src/tab.c` | 58.2 |
| `src/css.c` | 54.2 (large, maybe generated) |
| `src/freedom.c` | 52.6 |

## Strongest Connections

- 2 -> 3: depends_on (strength 0.9, EXTRACTED)
- 3 -> 0: depends_on (strength 0.9, EXTRACTED)
- 6 -> 0: depends_on (strength 0.9, EXTRACTED)
- 6 -> 3: depends_on (strength 0.9, EXTRACTED)
- 1 -> 3: depends_on (strength 0.9, EXTRACTED)
- 1 -> 2: depends_on (strength 0.9, EXTRACTED)
- 1 -> 6: depends_on (strength 0.9, EXTRACTED)
- 1 -> 4: depends_on (strength 0.9, EXTRACTED)
- 1 -> 0: depends_on (strength 0.9, EXTRACTED)
- 1 -> 8: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
