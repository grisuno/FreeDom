# Second Brain

*Last synthesized: 2026-10-02 | 255 files | 16 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `browser_ui.c`, `css.h`, `tab.c`. Architecturally it is 6 layers, dominant utility (136 files) across 16 import-based communities. Recorded risk surface: 0 security findings and 1 dependency cycles.

Surprising tissue lives between src (community 0), include (community 1), src (community 2): 20 extracted cross-community imports and 0 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (10% file coverage), 0 security findings, 4 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 255 |
| Symbols | 6084 |
| Resolved imports | 484 |
| Languages | c, h, py, sh |
| Communities | 16 |
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
readmenator query "<question>" --target freedom-0.0.3
```

## Concept Wiki

- [src (community 0) (63 files, cohesion 0.74)](./community_0_src.md)
- [include (community 1) (4 files, cohesion 0.43)](./community_1_include.md)
- [src (community 2) (30 files, cohesion 0.64)](./community_2_src.md)
- [include (community 3) (85 files, cohesion 0.64)](./community_3_include.md)
- [include (community 4) (4 files, cohesion 0.60)](./community_4_include.md)
- [tests (5 files, cohesion 0.67)](./community_5_tests.md)
- [include (community 6) (4 files, cohesion 0.75)](./community_6_include.md)
- [gui (5 files, cohesion 0.33)](./community_7_gui.md)
- [include (community 8) (4 files, cohesion 0.60)](./community_8_include.md)
- [include (community 9) (4 files, cohesion 0.60)](./community_9_include.md)
- [src (community 10) (20 files, cohesion 0.42)](./community_10_src.md)
- [include (community 11) (6 files, cohesion 0.70)](./community_11_include.md)
- [include (community 12) (3 files, cohesion 0.67)](./community_12_include.md)
- [include (community 13) (3 files, cohesion 0.50)](./community_13_include.md)
- [include (community 14) (3 files, cohesion 0.67)](./community_14_include.md)
- [orphans (12 files, cohesion 0.00)](./community_15_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `gui/browser_ui.c` | 136.5 (large, maybe generated) |
| `include/css.h` | 79.1 |
| `src/tab.c` | 55.9 |
| `src/page_view.c` | 50.2 (large, maybe generated) |
| `include/html_parse.h` | 48.4 |

## Strongest Connections

- 3 -> 2: depends_on (strength 0.9, EXTRACTED)
- 2 -> 10: depends_on (strength 0.9, EXTRACTED)
- 7 -> 2: depends_on (strength 0.9, EXTRACTED)
- 7 -> 3: depends_on (strength 0.9, EXTRACTED)
- 10 -> 3: depends_on (strength 0.9, EXTRACTED)
- 3 -> 0: depends_on (strength 0.9, EXTRACTED)
- 3 -> 1: depends_on (strength 0.9, EXTRACTED)
- 3 -> 4: depends_on (strength 0.9, EXTRACTED)
- 3 -> 12: depends_on (strength 0.9, EXTRACTED)
- 3 -> 5: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
