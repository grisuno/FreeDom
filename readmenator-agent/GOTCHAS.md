# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `gui/browser_ui.c` (score: 46.00)
- `src/local_store.c` (score: 27.10)
- `tests/test_css.c` (score: 25.10)
- `src/css.c` (score: 22.60)
- `include/util.h` (score: 20.60)
- `src/page_view.c` (score: 19.20)
- `include/css.h` (score: 14.90)
- `tests/test_page_view.c` (score: 14.00)
- `include/page_view.h` (score: 13.20)
- `include/ui.h` (score: 12.50)

## Hotspots (complexity + centrality)

- `gui/browser_ui.c` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `src/local_store.c` -- complexity: 0.6, centrality: 1.0, combined: 0.9
- `src/page_view.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/tab.c` -- complexity: 0.2, centrality: 0.4, combined: 0.3
- `tests/test_css.c` -- complexity: 0.6, centrality: 0.1, combined: 0.3
- `src/css.c` -- complexity: 0.5, centrality: 0.2, combined: 0.3
- `src/freedom.c` -- complexity: 0.1, centrality: 0.4, combined: 0.3
- `tests/test_page_view.c` -- complexity: 0.3, centrality: 0.2, combined: 0.2
- `src/os_sandbox.c` -- complexity: 0.1, centrality: 0.3, combined: 0.2
- `tests/test_os_sandbox.c` -- complexity: 0.0, centrality: 0.3, combined: 0.2

## Layer Violations

- `tests/test_ui.c` (testing) -> `include/ui.h` (presentation): testing must not import presentation
