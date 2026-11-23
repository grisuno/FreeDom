# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `gui/browser_ui.c` (score: 203.30)
- `include/css.h` (score: 100.80, imported by 40 files)
- `src/tab.c` (score: 85.20)
- `src/page_view.c` (score: 63.20)
- `src/freedom.c` (score: 63.00)
- `src/css.c` (score: 61.30)
- `include/page_view.h` (score: 42.30, imported by 13 files)
- `include/js_sandbox.h` (score: 41.70, imported by 19 files)

## Blast Radius (change impact)

Editing these files can break the listed number of dependents. Run their tests after any change.

- `include/css_counter.h` -- 3 direct, 55 total dependents
- `include/css_mq.h` -- 4 direct, 55 total dependents
- `include/css.h` -- 40 direct, 52 total dependents
- `include/css_color.h` -- 14 direct, 52 total dependents
- `include/html_parse.h` -- 19 direct, 47 total dependents
- `include/dom.h` -- 17 direct, 43 total dependents
- `include/css_select.h` -- 15 direct, 31 total dependents
- `include/url.h` -- 16 direct, 28 total dependents
- `include/freebug.h` -- 13 direct, 26 total dependents
- `include/js_geom.h` -- 6 direct, 24 total dependents

## Hotspots (complexity + centrality)

- `gui/browser_ui.c` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `src/tab.c` -- complexity: 0.3, centrality: 0.5, combined: 0.4
- `src/page_view.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/css.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/freedom.c` -- complexity: 0.1, centrality: 0.4, combined: 0.3
- `include/css.h` -- complexity: 0.2, centrality: 0.3, combined: 0.3
- `src/js_dom.c` -- complexity: 0.1, centrality: 0.2, combined: 0.1
- `include/page_view.h` -- complexity: 0.1, centrality: 0.1, combined: 0.1
- `src/secure_fetch.c` -- complexity: 0.1, centrality: 0.1, combined: 0.1
- `include/js_dom.h` -- complexity: 0.0, centrality: 0.2, combined: 0.1

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
- `tests/test_chrome_layout.c` (testing) -> `include/chrome_layout.h` (presentation): testing must not import presentation
- `tests/test_css.c` (testing) -> `include/flex_layout.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/flex_layout.h` (presentation): testing must not import presentation

## Dataflow Issues (INFERRED, review each lead)

- `gui/browser_ui.c:1801` `gui_sub_perform` [UNCHECKED_ALLOC] `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- `gui/browser_ui.c:2040` `first` [DEAD_STORE] `dg`: `dg` assigned at line 2040 but never read afterwards.
- `gui/browser_ui.c:4971` `flow_text` [DEAD_STORE] `space_w`: `space_w` assigned at line 4971 but never read afterwards.
- `gui/browser_ui.c:4973` `flow_text` [DEAD_STORE] `i`: `i` assigned at line 4973 but never read afterwards.
- `gui/browser_ui.c:6045` `table` [DEAD_STORE] `parent`: `parent` assigned at line 6045 but never read afterwards.
- `gui/browser_ui.c:6046` `table` [DEAD_STORE] `seen`: `seen` assigned at line 6046 but never read afterwards.
- `gui/browser_ui.c:6048` `table` [DEAD_STORE] `j`: `j` assigned at line 6048 but never read afterwards.
- `gui/browser_ui.c:6221` `measure_item_w_at` [DEAD_STORE] `atom_line_max`: `atom_line_max` assigned at line 6221 but never read afterwards.
- `gui/browser_ui.c:6242` `measure_item_w_at` [DEAD_STORE] `rw`: `rw` assigned at line 6242 but never read afterwards.
- `gui/browser_ui.c:6453` `nested_cont_basis` [DEAD_STORE] `total`: `total` assigned at line 6453 but never read afterwards.
