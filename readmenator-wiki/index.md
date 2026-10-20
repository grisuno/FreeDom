# Second Brain

*Last synthesized: 2026-10-20 | 288 files | 11 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `browser_ui.c`, `css.h`, `tab.c`. Architecturally it is 6 layers, dominant utility (174 files) across 11 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between src: tab, include: css, include: browser_ui: 20 extracted cross-community imports and 0 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (15% file coverage), 0 security findings, 4 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 288 |
| Symbols | 6844 |
| Resolved imports | 547 |
| Languages | c, h, py, sh |
| Communities | 11 |
| Doc coverage | 15% (42/288 files) |
| Security findings | 0 |
| Estimated read cost | ~200834 tokens (chars/4, offline so $0) |
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

- [src: tab (57 files, cohesion 0.73)](./community_0_src_tab.md)
- [include: css (50 files, cohesion 0.71)](./community_1_include_css.md)
- [include: browser_ui (38 files, cohesion 0.47)](./community_2_include_browser_ui.md)
- [src: freedom (36 files, cohesion 0.55)](./community_3_src_freedom.md)
- [include: page_view (21 files, cohesion 0.47)](./community_4_include_page_view.md)
- [include: text_shape (20 files, cohesion 0.55)](./community_5_include_text_shape.md)
- [include: local_store (16 files, cohesion 0.83)](./community_6_include_local_store.md)
- [gui (15 files, cohesion 0.48)](./community_7_gui.md)
- [include: secure_fetch (10 files, cohesion 0.62)](./community_8_include_secure_fetch.md)
- [include: prefetch (8 files, cohesion 0.64)](./community_9_include_prefetch.md)
- [orphans (17 files, cohesion 0.00)](./community_10_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `gui/browser_ui.c` | 159.5 (large, maybe generated) |
| `include/css.h` | 90.0 |
| `src/tab.c` | 60.3 |
| `src/freedom.c` | 56.7 |
| `src/css.c` | 56.6 (large, maybe generated) |

## Strongest Connections

- 1 -> 4: depends_on (strength 0.9, EXTRACTED)
- 4 -> 0: depends_on (strength 0.9, EXTRACTED)
- 7 -> 0: depends_on (strength 0.9, EXTRACTED)
- 7 -> 4: depends_on (strength 0.9, EXTRACTED)
- 3 -> 0: depends_on (strength 0.9, EXTRACTED)
- 2 -> 4: depends_on (strength 0.9, EXTRACTED)
- 2 -> 1: depends_on (strength 0.9, EXTRACTED)
- 2 -> 7: depends_on (strength 0.9, EXTRACTED)
- 2 -> 5: depends_on (strength 0.9, EXTRACTED)
- 2 -> 0: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
