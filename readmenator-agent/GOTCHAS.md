# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `gui/browser_ui.c` (score: 129.30)
- `include/css.h` (score: 78.70)
- `src/tab.c` (score: 47.00)
- `src/freedom.c` (score: 45.70)
- `src/page_view.c` (score: 43.10)
- `src/css.c` (score: 41.90)
- `include/html_parse.h` (score: 40.40)
- `include/page_view.h` (score: 38.50)
- `tests/test_css.c` (score: 30.40)
- `src/local_store.c` (score: 29.10)

## Hotspots (complexity + centrality)

- `gui/browser_ui.c` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `src/tab.c` -- complexity: 0.2, centrality: 0.5, combined: 0.4
- `src/page_view.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/css.c` -- complexity: 0.4, centrality: 0.2, combined: 0.3
- `include/css.h` -- complexity: 0.3, centrality: 0.3, combined: 0.3
- `src/freedom.c` -- complexity: 0.1, centrality: 0.4, combined: 0.3
- `tests/test_css.c` -- complexity: 0.5, centrality: 0.1, combined: 0.3
- `src/local_store.c` -- complexity: 0.5, centrality: 0.1, combined: 0.3
- `tests/test_page_view.c` -- complexity: 0.3, centrality: 0.2, combined: 0.2
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

## Dataflow Issues (INFERRED, review each lead)

- `gui/browser_ui.c:1411` `gui_subresource_fetch` [UNCHECKED_ALLOC] `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- `gui/browser_ui.c:3775` `flow_text` [DEAD_STORE] `space_w`: `space_w` assigned at line 3775 but never read afterwards.
- `gui/browser_ui.c:3777` `flow_text` [DEAD_STORE] `i`: `i` assigned at line 3777 but never read afterwards.
- `gui/browser_ui.c:4116` `emit_replaced_row` [DEAD_STORE] `box_w`: `box_w` assigned at line 4116 but never read afterwards.
- `gui/browser_ui.c:4968` `layout_container` [DEAD_STORE] `item_cbox`: `item_cbox` assigned at line 4968 but never read afterwards.
- `gui/browser_ui.c:6698` `layout_float_band` [DEAD_STORE] `base_top`: `base_top` assigned at line 6698 but never read afterwards.
- `gui/browser_ui.c:7939` `button_box_width` [DEAD_STORE] `cx`: `cx` assigned at line 7939 but never read afterwards.
- `gui/browser_ui.c:8957` `paint_box_decoration` [DEAD_STORE] `bt`: `bt` assigned at line 8957 but never read afterwards.
- `gui/browser_ui.c:8958` `paint_box_decoration` [DEAD_STORE] `bb`: `bb` assigned at line 8958 but never read afterwards.
- `gui/browser_ui.c:9112` `layer` [DEAD_STORE] `on`: `on` assigned at line 9112 but never read afterwards.
