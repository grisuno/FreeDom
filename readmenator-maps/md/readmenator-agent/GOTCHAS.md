# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `gui/browser_ui.c` (score: 159.30)
- `include/css.h` (score: 90.00, imported by 37 files)
- `src/tab.c` (score: 60.30)
- `src/css.c` (score: 56.60)
- `src/freedom.c` (score: 54.70)
- `src/page_view.c` (score: 54.00)
- `include/html_parse.h` (score: 48.40, imported by 23 files)
- `include/dom.h` (score: 40.80, imported by 18 files)
- `include/page_view.h` (score: 40.70, imported by 13 files)

## Blast Radius (change impact)

Editing these files can break the listed number of dependents. Run their tests after any change.

- `include/css.h` -- 37 direct, 52 total dependents
- `include/css_color.h` -- 13 direct, 52 total dependents
- `include/html_parse.h` -- 23 direct, 45 total dependents
- `include/dom.h` -- 18 direct, 40 total dependents
- `include/css_select.h` -- 15 direct, 29 total dependents
- `include/url.h` -- 18 direct, 28 total dependents
- `include/freebug.h` -- 12 direct, 21 total dependents
- `include/js_geom.h` -- 8 direct, 21 total dependents
- `include/js_sandbox.h` -- 16 direct, 19 total dependents
- `include/page_view.h` -- 13 direct, 18 total dependents

## Hotspots (complexity + centrality)

- `gui/browser_ui.c` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `src/tab.c` -- complexity: 0.2, centrality: 0.5, combined: 0.4
- `src/css.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/page_view.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/freedom.c` -- complexity: 0.1, centrality: 0.4, combined: 0.3
- `include/css.h` -- complexity: 0.2, centrality: 0.3, combined: 0.3
- `src/local_store.c` -- complexity: 0.5, centrality: 0.1, combined: 0.2
- `include/page_view.h` -- complexity: 0.1, centrality: 0.2, combined: 0.2
- `src/js_dom.c` -- complexity: 0.1, centrality: 0.2, combined: 0.2
- `include/html_parse.h` -- complexity: 0.0, centrality: 0.2, combined: 0.1

## Dependency Cycles

Circular dependencies. Refactor to break the cycle.

- `include/js_dom.h` -> `include/js_location.h` -> `include/js_dom.h`

## Layer Violations

- `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access): presentation must not import data_access
- `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access): presentation must not import data_access
- `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access): presentation must not import data_access
- `src/render_policy.c` (presentation) -> `include/data_url.h` (data_access): presentation must not import data_access
- `tests/test_box_tree.c` (testing) -> `include/page_view.h` (presentation): testing must not import presentation
- `tests/test_css.c` (testing) -> `include/flex_layout.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/flex_layout.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/page_view.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/render_doc.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/render_policy.h` (presentation): testing must not import presentation

## Dataflow Issues (INFERRED, review each lead)

- `gui/browser_ui.c:1520` `gui_subresource_fetch` [UNCHECKED_ALLOC] `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- `gui/browser_ui.c:1685` `first` [DEAD_STORE] `dg`: `dg` assigned at line 1685 but never read afterwards.
- `gui/browser_ui.c:4287` `flow_text` [DEAD_STORE] `space_w`: `space_w` assigned at line 4287 but never read afterwards.
- `gui/browser_ui.c:4289` `flow_text` [DEAD_STORE] `i`: `i` assigned at line 4289 but never read afterwards.
- `gui/browser_ui.c:5298` `table` [DEAD_STORE] `parent`: `parent` assigned at line 5298 but never read afterwards.
- `gui/browser_ui.c:5299` `table` [DEAD_STORE] `seen`: `seen` assigned at line 5299 but never read afterwards.
- `gui/browser_ui.c:5301` `table` [DEAD_STORE] `j`: `j` assigned at line 5301 but never read afterwards.
- `gui/browser_ui.c:5601` `nested_cont_basis` [DEAD_STORE] `total`: `total` assigned at line 5601 but never read afterwards.
- `gui/browser_ui.c:5602` `nested_cont_basis` [DEAD_STORE] `n_items`: `n_items` assigned at line 5602 but never read afterwards.
- `gui/browser_ui.c:8166` `defer_flush` [DEAD_STORE] `fw`: `fw` assigned at line 8166 but never read afterwards.
