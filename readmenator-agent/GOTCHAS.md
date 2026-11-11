# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `gui/browser_ui.c` (score: 182.20)
- `include/css.h` (score: 96.40, imported by 39 files)
- `src/tab.c` (score: 81.40)
- `src/freedom.c` (score: 63.00)
- `src/css.c` (score: 60.80)
- `src/page_view.c` (score: 59.10)
- `include/js_sandbox.h` (score: 41.70, imported by 19 files)
- `include/html_parse.h` (score: 40.40, imported by 19 files)

## Blast Radius (change impact)

Editing these files can break the listed number of dependents. Run their tests after any change.

- `include/css_counter.h` -- 3 direct, 53 total dependents
- `include/css.h` -- 39 direct, 50 total dependents
- `include/css_color.h` -- 13 direct, 50 total dependents
- `include/html_parse.h` -- 19 direct, 44 total dependents
- `include/dom.h` -- 17 direct, 40 total dependents
- `include/css_select.h` -- 15 direct, 30 total dependents
- `include/url.h` -- 16 direct, 28 total dependents
- `include/freebug.h` -- 13 direct, 26 total dependents
- `include/js_geom.h` -- 6 direct, 24 total dependents
- `include/js_sandbox.h` -- 19 direct, 24 total dependents

## Hotspots (complexity + centrality)

- `gui/browser_ui.c` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `src/tab.c` -- complexity: 0.3, centrality: 0.5, combined: 0.4
- `src/page_view.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/css.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/freedom.c` -- complexity: 0.1, centrality: 0.4, combined: 0.3
- `include/css.h` -- complexity: 0.2, centrality: 0.3, combined: 0.3
- `src/js_dom.c` -- complexity: 0.1, centrality: 0.2, combined: 0.2
- `src/secure_fetch.c` -- complexity: 0.1, centrality: 0.2, combined: 0.1
- `include/page_view.h` -- complexity: 0.1, centrality: 0.1, combined: 0.1
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
- `tests/test_css.c` (testing) -> `include/flex_layout.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/flex_layout.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/page_view.h` (presentation): testing must not import presentation

## Dataflow Issues (INFERRED, review each lead)

- `gui/browser_ui.c:1691` `gui_subresource_fetch` [UNCHECKED_ALLOC] `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- `gui/browser_ui.c:1857` `first` [DEAD_STORE] `dg`: `dg` assigned at line 1857 but never read afterwards.
- `gui/browser_ui.c:4674` `flow_text` [DEAD_STORE] `space_w`: `space_w` assigned at line 4674 but never read afterwards.
- `gui/browser_ui.c:4676` `flow_text` [DEAD_STORE] `i`: `i` assigned at line 4676 but never read afterwards.
- `gui/browser_ui.c:5713` `table` [DEAD_STORE] `parent`: `parent` assigned at line 5713 but never read afterwards.
- `gui/browser_ui.c:5714` `table` [DEAD_STORE] `seen`: `seen` assigned at line 5714 but never read afterwards.
- `gui/browser_ui.c:5716` `table` [DEAD_STORE] `j`: `j` assigned at line 5716 but never read afterwards.
- `gui/browser_ui.c:5851` `measure_item_w_at` [DEAD_STORE] `repl_max`: `repl_max` assigned at line 5851 but never read afterwards.
- `gui/browser_ui.c:5852` `measure_item_w_at` [DEAD_STORE] `atom_line_max`: `atom_line_max` assigned at line 5852 but never read afterwards.
- `gui/browser_ui.c:5870` `measure_item_w_at` [DEAD_STORE] `rw`: `rw` assigned at line 5870 but never read afterwards.
