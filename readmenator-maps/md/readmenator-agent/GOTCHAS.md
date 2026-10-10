# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `gui/browser_ui.c` (score: 141.10)
- `include/css.h` (score: 81.10, imported by 33 files)
- `src/tab.c` (score: 56.00)
- `src/freedom.c` (score: 52.60)
- `src/css.c` (score: 51.10)
- `src/page_view.c` (score: 50.20)
- `include/html_parse.h` (score: 48.40, imported by 23 files)
- `include/dom.h` (score: 40.80, imported by 18 files)
- `include/page_view.h` (score: 39.20, imported by 13 files)

## Blast Radius (change impact)

Editing these files can break the listed number of dependents. Run their tests after any change.

- `include/css_color.h` -- 13 direct, 52 total dependents
- `include/css.h` -- 33 direct, 51 total dependents
- `include/html_parse.h` -- 23 direct, 45 total dependents
- `include/dom.h` -- 18 direct, 40 total dependents
- `include/url.h` -- 17 direct, 27 total dependents
- `include/css_select.h` -- 14 direct, 21 total dependents
- `include/freebug.h` -- 12 direct, 21 total dependents
- `include/js_geom.h` -- 8 direct, 21 total dependents
- `include/js_sandbox.h` -- 16 direct, 19 total dependents
- `include/page_view.h` -- 13 direct, 18 total dependents

## Hotspots (complexity + centrality)

- `gui/browser_ui.c` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `src/tab.c` -- complexity: 0.2, centrality: 0.5, combined: 0.4
- `src/css.c` -- complexity: 0.4, centrality: 0.3, combined: 0.4
- `src/page_view.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/freedom.c` -- complexity: 0.1, centrality: 0.5, combined: 0.3
- `include/css.h` -- complexity: 0.2, centrality: 0.3, combined: 0.3
- `src/local_store.c` -- complexity: 0.5, centrality: 0.1, combined: 0.3
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
- `tests/test_dom_debug.c` (testing) -> `include/flex_layout.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/page_view.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/render_doc.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/render_policy.h` (presentation): testing must not import presentation
- `tests/test_flex_layout.c` (testing) -> `include/flex_layout.h` (presentation): testing must not import presentation

## Dataflow Issues (INFERRED, review each lead)

- `gui/browser_ui.c:1459` `gui_subresource_fetch` [UNCHECKED_ALLOC] `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- `gui/browser_ui.c:1624` `first` [DEAD_STORE] `dg`: `dg` assigned at line 1624 but never read afterwards.
- `gui/browser_ui.c:4073` `flow_text` [DEAD_STORE] `space_w`: `space_w` assigned at line 4073 but never read afterwards.
- `gui/browser_ui.c:4075` `flow_text` [DEAD_STORE] `i`: `i` assigned at line 4075 but never read afterwards.
- `gui/browser_ui.c:7278` `layout_float_band` [DEAD_STORE] `base_top`: `base_top` assigned at line 7278 but never read afterwards.
- `gui/browser_ui.c:8776` `button_box_width` [DEAD_STORE] `cx`: `cx` assigned at line 8776 but never read afterwards.
- `gui/browser_ui.c:9829` `paint_box_decoration` [DEAD_STORE] `bt`: `bt` assigned at line 9829 but never read afterwards.
- `gui/browser_ui.c:9830` `paint_box_decoration` [DEAD_STORE] `bb`: `bb` assigned at line 9830 but never read afterwards.
- `gui/browser_ui.c:9989` `layer` [DEAD_STORE] `on`: `on` assigned at line 9989 but never read afterwards.
- `gui/browser_ui.c:10032` `cairo_set_dash` [DEAD_STORE] `on`: `on` assigned at line 10032 but never read afterwards.
