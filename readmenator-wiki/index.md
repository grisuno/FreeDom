# Second Brain

*Last synthesized: 2026-09-19 | 218 files | 11 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `browser_ui.c`, `css.h`, `tab.c`. Architecturally it is 6 layers, dominant utility (112 files) across 11 import-based communities. Recorded risk surface: 0 security findings and 0 dependency cycles.

Surprising tissue lives between include (community 0), include (community 1), include (community 2): 10 extracted cross-community imports and 10 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (9% file coverage), 0 security findings, 3 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 218 |
| Symbols | 5231 |
| Resolved imports | 398 |
| Languages | c, h, py, sh |
| Communities | 11 |
| Doc coverage | 9% (20/218 files) |
| Security findings | 0 |
| Estimated read cost | ~151816 tokens (chars/4, offline so $0) |
| Large files (>256KB, maybe generated) | 2: `browser_ui.c`, `page_view.c` |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target freedom-0.0.3
```

## Concept Wiki

- [include (community 0) (172 files, cohesion 0.96)](./community_0_include.md)
- [include (community 1) (4 files, cohesion 0.60)](./community_1_include.md)
- [include (community 2) (4 files, cohesion 0.60)](./community_2_include.md)
- [include (community 3) (4 files, cohesion 0.60)](./community_3_include.md)
- [include (community 4) (4 files, cohesion 0.50)](./community_4_include.md)
- [include (community 5) (4 files, cohesion 0.60)](./community_5_include.md)
- [include (community 6) (3 files, cohesion 0.67)](./community_6_include.md)
- [include (community 7) (6 files, cohesion 0.70)](./community_7_include.md)
- [include (community 8) (3 files, cohesion 0.67)](./community_8_include.md)
- [include (community 9) (3 files, cohesion 0.67)](./community_9_include.md)
- [orphans (11 files, cohesion 0.00)](./community_10_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `gui/browser_ui.c` | 129.3 (large, maybe generated) |
| `include/css.h` | 78.7 |
| `src/tab.c` | 47.0 |
| `src/freedom.c` | 45.7 |
| `src/page_view.c` | 43.1 (large, maybe generated) |

## Strongest Connections

- 0 -> 6: depends_on (strength 0.9, EXTRACTED)
- 0 -> 1: depends_on (strength 0.9, EXTRACTED)
- 0 -> 8: depends_on (strength 0.9, EXTRACTED)
- 0 -> 2: depends_on (strength 0.9, EXTRACTED)
- 0 -> 3: depends_on (strength 0.9, EXTRACTED)
- 0 -> 4: depends_on (strength 0.9, EXTRACTED)
- 0 -> 9: depends_on (strength 0.9, EXTRACTED)
- 0 -> 5: depends_on (strength 0.9, EXTRACTED)
- 0 -> 7: depends_on (strength 0.9, EXTRACTED)
- 1 -> 2: depends_on (strength 0.9, EXTRACTED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
