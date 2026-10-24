# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `gui/browser_ui.c` (score: 162.70)
- `include/css.h` (score: 88.00, imported by 36 files)
- `src/tab.c` (score: 64.70)
- `src/freedom.c` (score: 58.80)
- `src/css.c` (score: 56.70)
- `src/page_view.c` (score: 54.80)
- `include/html_parse.h` (score: 38.40, imported by 18 files)
- `include/page_view.h` (score: 37.10, imported by 11 files)
- `include/dom.h` (score: 36.90, imported by 16 files)

## Blast Radius (change impact)

Editing these files can break the listed number of dependents. Run their tests after any change.

- `include/css_color.h` -- 13 direct, 52 total dependents
- `include/css.h` -- 36 direct, 51 total dependents
- `include/html_parse.h` -- 18 direct, 40 total dependents
- `include/dom.h` -- 16 direct, 36 total dependents
- `include/css_select.h` -- 14 direct, 28 total dependents
- `include/url.h` -- 16 direct, 27 total dependents
- `include/freebug.h` -- 11 direct, 20 total dependents
- `include/js_geom.h` -- 6 direct, 20 total dependents
- `include/js_sandbox.h` -- 15 direct, 18 total dependents
- `include/css_decl.h` -- 12 direct, 17 total dependents

## Hotspots (complexity + centrality)

- `gui/browser_ui.c` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `src/tab.c` -- complexity: 0.2, centrality: 0.5, combined: 0.4
- `src/page_view.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/css.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/freedom.c` -- complexity: 0.1, centrality: 0.5, combined: 0.3
- `include/css.h` -- complexity: 0.2, centrality: 0.3, combined: 0.3
- `src/local_store.c` -- complexity: 0.5, centrality: 0.1, combined: 0.2
- `src/js_dom.c` -- complexity: 0.1, centrality: 0.2, combined: 0.2
- `include/page_view.h` -- complexity: 0.1, centrality: 0.1, combined: 0.1
- `include/js_dom.h` -- complexity: 0.0, centrality: 0.2, combined: 0.1

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

- `gui/browser_ui.c:1477` `gui_subresource_fetch` [UNCHECKED_ALLOC] `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- `gui/browser_ui.c:1641` `first` [DEAD_STORE] `dg`: `dg` assigned at line 1641 but never read afterwards.
- `gui/browser_ui.c:4321` `flow_text` [DEAD_STORE] `space_w`: `space_w` assigned at line 4321 but never read afterwards.
- `gui/browser_ui.c:4323` `flow_text` [DEAD_STORE] `i`: `i` assigned at line 4323 but never read afterwards.
- `gui/browser_ui.c:5343` `table` [DEAD_STORE] `parent`: `parent` assigned at line 5343 but never read afterwards.
- `gui/browser_ui.c:5344` `table` [DEAD_STORE] `seen`: `seen` assigned at line 5344 but never read afterwards.
- `gui/browser_ui.c:5346` `table` [DEAD_STORE] `j`: `j` assigned at line 5346 but never read afterwards.
- `gui/browser_ui.c:5646` `nested_cont_basis` [DEAD_STORE] `total`: `total` assigned at line 5646 but never read afterwards.
- `gui/browser_ui.c:5647` `nested_cont_basis` [DEAD_STORE] `n_items`: `n_items` assigned at line 5647 but never read afterwards.
- `gui/browser_ui.c:6719` `builds` [DEAD_STORE] `sl`: `sl` assigned at line 6719 but never read afterwards.
