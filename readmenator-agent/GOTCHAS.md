# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `gui/browser_ui.c` (score: 136.50)
- `include/css.h` (score: 79.10)
- `src/tab.c` (score: 55.90)
- `src/page_view.c` (score: 50.20)
- `include/html_parse.h` (score: 48.40)
- `src/css.c` (score: 48.00)
- `src/freedom.c` (score: 45.90)
- `include/dom.h` (score: 40.80)
- `include/page_view.h` (score: 39.20)
- `tests/test_css.c` (score: 36.60)

## Hotspots (complexity + centrality)

- `gui/browser_ui.c` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `src/tab.c` -- complexity: 0.2, centrality: 0.5, combined: 0.4
- `src/page_view.c` -- complexity: 0.4, centrality: 0.3, combined: 0.4
- `src/css.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `tests/test_css.c` -- complexity: 0.6, centrality: 0.1, combined: 0.3
- `src/freedom.c` -- complexity: 0.1, centrality: 0.4, combined: 0.3
- `include/css.h` -- complexity: 0.2, centrality: 0.3, combined: 0.3
- `src/local_store.c` -- complexity: 0.5, centrality: 0.1, combined: 0.3
- `tests/test_js_dom.c` -- complexity: 0.3, centrality: 0.2, combined: 0.3
- `tests/test_page_view.c` -- complexity: 0.3, centrality: 0.2, combined: 0.2

## Dependency Cycles

Circular dependencies. Refactor to break the cycle.

- `include/js_dom.h` -> `include/js_location.h` -> `include/js_dom.h`

## Layer Violations

- `gui/browser_ui.c` (presentation) -> `include/data_url.h` (data_access): presentation must not import data_access
- `gui/browser_ui.c` (presentation) -> `include/form.h` (data_access): presentation must not import data_access
- `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access): presentation must not import data_access
- `src/render_doc.c` (presentation) -> `include/data_url.h` (data_access): presentation must not import data_access
- `src/render_policy.c` (presentation) -> `include/data_url.h` (data_access): presentation must not import data_access
- `tests/test_box_tree.c` (testing) -> `include/page_view.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/flex_layout.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/page_view.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/render_doc.h` (presentation): testing must not import presentation
- `tests/test_dom_debug.c` (testing) -> `include/render_policy.h` (presentation): testing must not import presentation

## Dataflow Issues (INFERRED, review each lead)

- `gui/browser_ui.c:1435` `gui_subresource_fetch` [UNCHECKED_ALLOC] `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- `gui/browser_ui.c:3894` `flow_text` [DEAD_STORE] `space_w`: `space_w` assigned at line 3894 but never read afterwards.
- `gui/browser_ui.c:3896` `flow_text` [DEAD_STORE] `i`: `i` assigned at line 3896 but never read afterwards.
- `gui/browser_ui.c:7066` `layout_float_band` [DEAD_STORE] `base_top`: `base_top` assigned at line 7066 but never read afterwards.
- `gui/browser_ui.c:8556` `button_box_width` [DEAD_STORE] `cx`: `cx` assigned at line 8556 but never read afterwards.
- `gui/browser_ui.c:9595` `paint_box_decoration` [DEAD_STORE] `bt`: `bt` assigned at line 9595 but never read afterwards.
- `gui/browser_ui.c:9596` `paint_box_decoration` [DEAD_STORE] `bb`: `bb` assigned at line 9596 but never read afterwards.
- `gui/browser_ui.c:9755` `layer` [DEAD_STORE] `on`: `on` assigned at line 9755 but never read afterwards.
- `gui/browser_ui.c:9798` `cairo_set_dash` [DEAD_STORE] `on`: `on` assigned at line 9798 but never read afterwards.
- `gui/browser_ui.c:9833` `convention` [DEAD_STORE] `nr`: `nr` assigned at line 9833 but never read afterwards.
