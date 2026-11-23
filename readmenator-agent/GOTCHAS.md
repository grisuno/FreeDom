# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `gui/browser_ui.c` (score: 214.10)
- `include/css.h` (score: 104.80, imported by 42 files)
- `src/tab.c` (score: 87.40)
- `src/page_view.c` (score: 63.40)
- `src/freedom.c` (score: 63.00)
- `src/css.c` (score: 61.40)
- `include/html_parse.h` (score: 54.40, imported by 26 files)
- `include/dom.h` (score: 49.30, imported by 22 files)
- `include/page_view.h` (score: 48.30, imported by 16 files)

## Blast Radius (change impact)

Editing these files can break the listed number of dependents. Run their tests after any change.

- `include/css.h` -- 42 direct, 55 total dependents
- `include/css_color.h` -- 14 direct, 51 total dependents
- `include/css_counter.h` -- 4 direct, 51 total dependents
- `include/dom.h` -- 22 direct, 51 total dependents
- `include/css_mq.h` -- 5 direct, 50 total dependents
- `include/html_parse.h` -- 26 direct, 50 total dependents
- `include/css_select.h` -- 16 direct, 32 total dependents
- `include/url.h` -- 19 direct, 31 total dependents
- `include/js_geom.h` -- 10 direct, 30 total dependents
- `include/freebug.h` -- 14 direct, 28 total dependents

## Hotspots (complexity + centrality)

- `gui/browser_ui.c` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `src/tab.c` -- complexity: 0.3, centrality: 0.5, combined: 0.4
- `src/page_view.c` -- complexity: 0.4, centrality: 0.3, combined: 0.3
- `src/css.c` -- complexity: 0.4, centrality: 0.2, combined: 0.3
- `src/freedom.c` -- complexity: 0.1, centrality: 0.4, combined: 0.3
- `include/css.h` -- complexity: 0.2, centrality: 0.3, combined: 0.3
- `include/page_view.h` -- complexity: 0.1, centrality: 0.1, combined: 0.1
- `src/js_dom.c` -- complexity: 0.1, centrality: 0.2, combined: 0.1
- `src/secure_fetch.c` -- complexity: 0.1, centrality: 0.1, combined: 0.1
- `include/dom.h` -- complexity: 0.0, centrality: 0.2, combined: 0.1

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

- `fuzz/fuzz_css_import.c:37` `fz_resolve` [UNCHECKED_ALLOC] `o`: Result of allocator stored in `o` is never checked against NULL.
- `fuzz/fuzz_fb_cmdline.c:7` `LLVMFuzzerTestOneInput` [UNCHECKED_ALLOC] `cut`: Result of allocator stored in `cut` is never checked against NULL.
- `fuzz/fuzz_fb_cmdline.c:7` `LLVMFuzzerTestOneInput` [UNCHECKED_ALLOC] `t`: Result of allocator stored in `t` is never checked against NULL.
- `gui/browser_ui.c:1842` `gui_sub_perform` [UNCHECKED_ALLOC] `out_ctype`: Result of allocator stored in `out_ctype` is never checked against NULL.
- `gui/browser_ui.c:2081` `first` [DEAD_STORE] `dg`: `dg` assigned at line 2081 but never read afterwards.
- `gui/browser_ui.c:5045` `flow_text` [DEAD_STORE] `space_w`: `space_w` assigned at line 5045 but never read afterwards.
- `gui/browser_ui.c:5047` `flow_text` [DEAD_STORE] `i`: `i` assigned at line 5047 but never read afterwards.
- `gui/browser_ui.c:6119` `table` [DEAD_STORE] `parent`: `parent` assigned at line 6119 but never read afterwards.
- `gui/browser_ui.c:6120` `table` [DEAD_STORE] `seen`: `seen` assigned at line 6120 but never read afterwards.
- `gui/browser_ui.c:6122` `table` [DEAD_STORE] `j`: `j` assigned at line 6122 but never read afterwards.
