# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `gui/browser_ui.c` (score: 150.60)
- `include/css.h` (score: 65.20)
- `src/freedom.c` (score: 49.10)
- `src/tab.c` (score: 47.90)
- `src/page_view.c` (score: 44.50)
- `include/html_parse.h` (score: 40.50)
- `include/page_view.h` (score: 39.30)
- `src/css.c` (score: 36.70)
- `tests/test_css.c` (score: 30.40)
- `src/local_store.c` (score: 30.00)

## Hotspots (complexity + centrality)

- `gui/browser_ui.c` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `src/tab.c` -- complexity: 0.2, centrality: 0.4, combined: 0.3
- `src/freedom.c` -- complexity: 0.1, centrality: 0.4, combined: 0.3
- `src/page_view.c` -- complexity: 0.3, centrality: 0.3, combined: 0.3
- `src/css.c` -- complexity: 0.4, centrality: 0.1, combined: 0.2
- `include/css.h` -- complexity: 0.2, centrality: 0.3, combined: 0.2
- `tests/test_css.c` -- complexity: 0.4, centrality: 0.1, combined: 0.2
- `src/local_store.c` -- complexity: 0.4, centrality: 0.1, combined: 0.2
- `tests/test_page_view.c` -- complexity: 0.2, centrality: 0.2, combined: 0.2
- `tests/test_js_dom.c` -- complexity: 0.2, centrality: 0.2, combined: 0.2

## Layer Violations

- `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access): presentation must not import data_access
- `gui/browser_ui.c` (presentation) -> `include/form.h` (data_access): presentation must not import data_access
- `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access): presentation must not import data_access
- `src/render_policy.c` (presentation) -> `include/data_url.h` (data_access): presentation must not import data_access
- `tests/test_box_tree.c` (testing) -> `include/page_view.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/flex_layout.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/page_view.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/render_doc.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/render_policy.h` (presentation): testing must not import presentation
- `tests/test_flex_layout.c` (testing) -> `include/flex_layout.h` (presentation): testing must not import presentation
