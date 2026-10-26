# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `gui/browser_ui.c` (score: 175.40)
- `include/css.h` (score: 88.00, imported by 36 files)
- `src/tab.c` (score: 68.60)
- `src/freedom.c` (score: 60.80)
- `src/css.c` (score: 56.70)
- `src/page_view.c` (score: 55.50)
- `include/html_parse.h` (score: 38.40, imported by 18 files)
- `include/page_view.h` (score: 37.10, imported by 11 files)

## Blast Radius (change impact)

Editing these files can break the listed number of dependents. Run their tests after any change.

- `include/css.h` -- 36 direct, 52 total dependents
- `include/css_color.h` -- 13 direct, 52 total dependents
- `include/html_parse.h` -- 18 direct, 40 total dependents
- `include/dom.h` -- 16 direct, 36 total dependents
- `include/css_select.h` -- 14 direct, 28 total dependents
- `include/url.h` -- 16 direct, 27 total dependents
- `include/freebug.h` -- 11 direct, 20 total dependents
- `include/js_geom.h` -- 6 direct, 20 total dependents
- `include/anti_fp.h` -- 8 direct, 18 total dependents
- `include/js_sandbox.h` -- 15 direct, 18 total dependents

## Hotspots (complexity + centrality)

- `gui/browser_ui.c` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `src/tab.c` -- complexity: 0.2, centrality: 0.5, combined: 0.4
- `src/page_view.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/css.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/freedom.c` -- complexity: 0.1, centrality: 0.4, combined: 0.3
- `include/css.h` -- complexity: 0.2, centrality: 0.3, combined: 0.3
- `src/local_store.c` -- complexity: 0.5, centrality: 0.1, combined: 0.3
- `src/js_dom.c` -- complexity: 0.1, centrality: 0.2, combined: 0.1
- `include/page_view.h` -- complexity: 0.1, centrality: 0.1, combined: 0.1
- `src/secure_fetch.c` -- complexity: 0.1, centrality: 0.1, combined: 0.1

## Dependency Cycles

Circular dependencies. Refactor to break the cycle.

- `include/js_dom.h` -> `include/js_location.h` -> `include/js_dom.h`

## Layer Violations

- `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access): presentation must not import data_access
- `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access): presentation must not import data_access
- `include/http_cache.h` (presentation) -> `include/local_store.h` (data_access): presentation must not import data_access
- `src/http_cache.c` (presentation) -> `include/disk_store.h` (data_access): presentation must not import data_access
- `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access): presentation must not import data_access
- `src/render_policy.c` (presentation) -> `include/data_url.h` (data_access): presentation must not import data_access
- `tests/test_box_tree.c` (testing) -> `include/page_view.h` (presentation): testing must not import presentation
- `tests/test_css.c` (testing) -> `include/flex_layout.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/flex_layout.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/page_view.h` (presentation): testing must not import presentation

## Dataflow Issues (INFERRED, review each lead)

- `gui/browser_ui.c:1563` `gui_subresource_fetch` [UNCHECKED_ALLOC] `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- `gui/browser_ui.c:1728` `first` [DEAD_STORE] `dg`: `dg` assigned at line 1728 but never read afterwards.
- `gui/browser_ui.c:4429` `flow_text` [DEAD_STORE] `space_w`: `space_w` assigned at line 4429 but never read afterwards.
- `gui/browser_ui.c:4431` `flow_text` [DEAD_STORE] `i`: `i` assigned at line 4431 but never read afterwards.
- `gui/browser_ui.c:5465` `table` [DEAD_STORE] `parent`: `parent` assigned at line 5465 but never read afterwards.
- `gui/browser_ui.c:5466` `table` [DEAD_STORE] `seen`: `seen` assigned at line 5466 but never read afterwards.
- `gui/browser_ui.c:5468` `table` [DEAD_STORE] `j`: `j` assigned at line 5468 but never read afterwards.
- `gui/browser_ui.c:5768` `nested_cont_basis` [DEAD_STORE] `total`: `total` assigned at line 5768 but never read afterwards.
- `gui/browser_ui.c:5769` `nested_cont_basis` [DEAD_STORE] `n_items`: `n_items` assigned at line 5769 but never read afterwards.
- `gui/browser_ui.c:6841` `builds` [DEAD_STORE] `sl`: `sl` assigned at line 6841 but never read afterwards.
