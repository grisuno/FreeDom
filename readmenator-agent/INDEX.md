# Index

| File | Purpose | Subsystem | Symbols |
|------|---------|-----------|---------|
| `app.py` | _*_ coding: utf8 _*_ | root | 3 |
| `docker-entrypoint.sh` | - | root | 0 |
| `docker_run.sh` | Thin wrapper. The docker build/run lives in the Makefile (single source of truth | root | 0 |
| `fuzz.sh` | Thin wrapper. The fuzz build/run logic now lives in the Makefile (single source  | root | 0 |
| `fuzz/fuzz_css.c` | - | fuzz | 5 |
| `fuzz/fuzz_data_url.c` | - | fuzz | 4 |
| `fuzz/fuzz_dom.c` | - | fuzz | 3 |
| `fuzz/fuzz_dom_debug.c` | - | fuzz | 5 |
| `fuzz/fuzz_download.c` | - | fuzz | 4 |
| `fuzz/fuzz_freebug.c` | - | fuzz | 7 |
| `fuzz/fuzz_html_parse.c` | - | fuzz | 4 |
| `fuzz/fuzz_image_decode.c` | - | fuzz | 3 |
| `fuzz/fuzz_js_sandbox.c` | - | fuzz | 3 |
| `fuzz/fuzz_page_view.c` | - | fuzz | 2 |
| `fuzz/fuzz_pdf_export.c` | - | fuzz | 4 |
| `fuzz/fuzz_prefetch.c` | libFuzzer harness for the prefetch lookahead scanner (Hito 29). The scanned | fuzz | 2 |
| `fuzz/fuzz_prefs.c` | - | fuzz | 9 |
| `fuzz/fuzz_svg_render.c` | - | fuzz | 3 |
| `fuzz/fuzz_text_shape.c` | - | fuzz | 5 |
| `fuzz/fuzz_tls_impersonate.c` | - | fuzz | 3 |
| `fuzz/fuzz_url.c` | - | fuzz | 6 |
| `gui/browser_ui.c` | - | gui | 706 |
| `gui/browser_ui_internal.h` | ifndef FREEDOM_BROWSER_UI_INTERNAL_H define FREEDOM_BROWSER_UI_INTERNAL_H  ifdef | gui | 15 |
| `gui/bui_theme.c` | - | gui | 7 |
| `gui/freedom_view.c` | - | gui | 8 |
| `gui/svg_paint.c` | svg_paint — Cairo back end for the shapes svg_render extracted. | gui | 31 |
| `gui/ui_render.c` | - | gui | 69 |
| `include/anti_fp.h` | ifndef FREEDOM_ANTI_FP_H define FREEDOM_ANTI_FP_H  include <stddef.h> include <s | include | 35 |
| `include/block_flow.h` | block_flow (bf_) -- vertical margin collapsing for block-level boxes. | include | 4 |
| `include/box_style.h` | ifndef FREEDOM_BOX_STYLE_H define FREEDOM_BOX_STYLE_H  ifdef __cplusplus error " | include | 29 |
| `include/box_tree.h` | ifndef FREEDOM_BOX_TREE_H define FREEDOM_BOX_TREE_H  include <stddef.h>  include | include | 29 |
| `include/browser.h` | ifndef FREEDOM_BROWSER_H define FREEDOM_BROWSER_H  include <stddef.h> include <s | include | 30 |
| `include/compositor.h` | ifndef FREEDOM_COMPOSITOR_H define FREEDOM_COMPOSITOR_H  include <stddef.h>  ifd | include | 10 |
| `include/css.h` | ifndef FREEDOM_CSS_H define FREEDOM_CSS_H  include <stddef.h> include "css_color | include | 132 |
| `include/css_chain.h` | ifndef FREEDOM_CSS_CHAIN_H define FREEDOM_CSS_CHAIN_H  include <lexbor/html/html | include | 7 |
| `include/css_color.h` | ifndef FREEDOM_CSS_COLOR_H define FREEDOM_CSS_COLOR_H  ifdef __cplusplus error " | include | 9 |
| `include/css_length.h` | ifndef FREEDOM_CSS_LENGTH_H define FREEDOM_CSS_LENGTH_H  include <stddef.h>  ifd | include | 23 |
| `include/css_select.h` | ifndef FREEDOM_CSS_SELECT_H define FREEDOM_CSS_SELECT_H  include <stddef.h> incl | include | 22 |
| `include/data_url.h` | ifndef FREEDOM_DATA_URL_H define FREEDOM_DATA_URL_H  include <stddef.h> include  | include | 7 |
| `include/disk_store.h` | ifndef FREEDOM_DISK_STORE_H define FREEDOM_DISK_STORE_H  include <stddef.h> incl | include | 5 |
| `include/dom.h` | ifndef FREEDOM_DOM_H define FREEDOM_DOM_H  include <stddef.h> include <stdint.h> | include | 34 |
| `include/dom_debug.h` | ifndef FREEDOM_DOM_DEBUG_H define FREEDOM_DOM_DEBUG_H  include <stddef.h>  inclu | include | 4 |
| `include/download.h` | ifndef FREEDOM_DOWNLOAD_H define FREEDOM_DOWNLOAD_H  include <stddef.h>  ifdef _ | include | 10 |
| `include/flex_layout.h` | ifndef FREEDOM_FLEX_LAYOUT_H define FREEDOM_FLEX_LAYOUT_H  include <stddef.h>  i | include | 37 |
| `include/form.h` | ifndef FREEDOM_FORM_H define FREEDOM_FORM_H  include <stddef.h>  include "url.h" | include | 14 |
| `include/frame_clock.h` | ifndef FREEDOM_FRAME_CLOCK_H define FREEDOM_FRAME_CLOCK_H  ifdef __cplusplus err | include | 7 |
| `include/freebug.h` | ifndef FREEDOM_FREEBUG_H define FREEDOM_FREEBUG_H  include <stddef.h>  ifdef __c | include | 18 |
| `include/freedom_config.h` | - | include | 8 |
| `include/hls.h` | ifndef FREEDOM_HLS_H define FREEDOM_HLS_H  include <stddef.h>  ifdef __cplusplus | include | 9 |
| `include/hostblock.h` | ifndef FREEDOM_HOSTBLOCK_H define FREEDOM_HOSTBLOCK_H  include <stddef.h>  ifdef | include | 12 |
| `include/hostedit.h` | ifndef FREEDOM_HOSTEDIT_H define FREEDOM_HOSTEDIT_H  include <stddef.h>  ifdef _ | include | 6 |
| `include/html_parse.h` | ifndef FREEDOM_HTML_PARSE_H define FREEDOM_HTML_PARSE_H  include <stddef.h> incl | include | 25 |
| `include/image_decode.h` | ifndef FREEDOM_IMAGE_DECODE_H define FREEDOM_IMAGE_DECODE_H  include <stddef.h>  | include | 18 |
| `include/interp.h` | ifndef FREEDOM_INTERP_H define FREEDOM_INTERP_H  include <stdint.h>  ifdef __cpl | include | 22 |
| `include/js_dom.h` | ifndef FREEDOM_JS_DOM_H define FREEDOM_JS_DOM_H  include "dom.h" include "freebu | include | 24 |
| `include/js_env.h` | ifndef FREEDOM_JS_ENV_H define FREEDOM_JS_ENV_H  include "js_sandbox.h"  ifdef _ | include | 4 |
| `include/js_policy.h` | ifndef FREEDOM_JS_POLICY_H define FREEDOM_JS_POLICY_H  include <stdbool.h>  ifde | include | 8 |
| `include/js_sandbox.h` | ifndef FREEDOM_JS_SANDBOX_H define FREEDOM_JS_SANDBOX_H  include <stddef.h> incl | include | 25 |
| `include/link_nav.h` | ifndef FREEDOM_LINK_NAV_H define FREEDOM_LINK_NAV_H  include <stddef.h>  ifdef _ | include | 12 |
| `include/local_store.h` | ifndef FREEDOM_LOCAL_STORE_H define FREEDOM_LOCAL_STORE_H  include <stddef.h> in | include | 16 |
| `include/media_decoder.h` | ifndef FREEDOM_MEDIA_DECODER_H define FREEDOM_MEDIA_DECODER_H  include <stddef.h | include | 12 |
| `include/net_realm.h` | ifndef FREEDOM_NET_REALM_H define FREEDOM_NET_REALM_H  ifdef __cplusplus error " | include | 12 |
| `include/os_sandbox.h` | ifndef FREEDOM_OS_SANDBOX_H define FREEDOM_OS_SANDBOX_H  include <stddef.h>  ifd | include | 15 |
| `include/page_view.h` | ifndef FREEDOM_PAGE_VIEW_H define FREEDOM_PAGE_VIEW_H  include <stddef.h> includ | include | 73 |
| `include/pdf_export.h` | ifndef FREEDOM_PDF_EXPORT_H define FREEDOM_PDF_EXPORT_H  include <stddef.h>  ifd | include | 12 |
| `include/perf_trace.h` | ifndef FREEDOM_PERF_TRACE_H define FREEDOM_PERF_TRACE_H  ifdef __cplusplus error | include | 17 |
| `include/prefetch.h` | ifndef FREEDOM_PREFETCH_H define FREEDOM_PREFETCH_H  ifdef __cplusplus error "Fr | include | 22 |
| `include/prefs.h` | ifndef FREEDOM_PREFS_H define FREEDOM_PREFS_H  include <stddef.h>  ifdef __cplus | include | 22 |
| `include/profile.h` | ifndef FREEDOM_PROFILE_H define FREEDOM_PROFILE_H  include <stddef.h> include <s | include | 11 |
| `include/psl_data.h` | ifndef FREEDOM_PSL_DATA_H define FREEDOM_PSL_DATA_H  include <stddef.h>  ifdef _ | include | 7 |
| `include/render_doc.h` | ifndef FREEDOM_RENDER_DOC_H define FREEDOM_RENDER_DOC_H  include <stddef.h>  inc | include | 25 |
| `include/render_policy.h` | ifndef FREEDOM_RENDER_POLICY_H define FREEDOM_RENDER_POLICY_H  include <stdbool. | include | 11 |
| `include/renderer.h` | ifndef FREEDOM_RENDERER_H define FREEDOM_RENDERER_H  include <stddef.h>  ifdef _ | include | 8 |
| `include/request_policy.h` | ifndef FREEDOM_REQUEST_POLICY_H define FREEDOM_REQUEST_POLICY_H  include <stddef | include | 6 |
| `include/secure_fetch.h` | ifndef FREEDOM_SECURE_FETCH_H define FREEDOM_SECURE_FETCH_H  include <stddef.h>  | include | 42 |
| `include/svg_paint.h` | ifndef FREEDOM_SVG_PAINT_H define FREEDOM_SVG_PAINT_H  include <cairo.h>  includ | include | 2 |
| `include/svg_render.h` | ifndef FREEDOM_SVG_RENDER_H define FREEDOM_SVG_RENDER_H  include <stddef.h>  ifd | include | 21 |
| `include/tab.h` | ifndef FREEDOM_TAB_H define FREEDOM_TAB_H  include <stddef.h> include <stdint.h> | include | 36 |
| `include/text_shape.h` | - | include | 12 |
| `include/textfield.h` | ifndef FREEDOM_TEXTFIELD_H define FREEDOM_TEXTFIELD_H  include <stddef.h>  ifdef | include | 17 |
| `include/tls_impersonate.h` | ifndef FREEDOM_TLS_IMPERSONATE_H define FREEDOM_TLS_IMPERSONATE_H  include <stdd | include | 22 |
| `include/ui.h` | ifndef FREEDOM_UI_H define FREEDOM_UI_H  include <stddef.h>  ifdef __cplusplus e | include | 21 |
| `include/url.h` | ifndef FREEDOM_URL_H define FREEDOM_URL_H  include <stddef.h>  ifdef __cplusplus | include | 21 |
| `include/util.h` | util.h — shared pure helpers (no I/O except where noted). Static inline so each  | include | 6 |
| `include/webcaps.h` | ifndef FREEDOM_WEBCAPS_H define FREEDOM_WEBCAPS_H  include <stdbool.h>  include  | include | 9 |
| `include/zoom.h` | ifndef FREEDOM_ZOOM_H define FREEDOM_ZOOM_H  ifdef __cplusplus error "Freedom is | include | 10 |
| `install.sh` | Exit immediately if a command exits with a non-zero status, if an undefined vari | root | 0 |
| `run_freedom.sh` | Thin wrapper. Launches a nested weston (for boxes without a Wayland session), th | root | 0 |
| `src/anti_fp.c` | - | src | 23 |
| `src/block_flow.c` | block_flow (bf_) -- vertical margin collapsing. See spec/block_flow.md. | src | 4 |
| `src/box_style.c` | - | src | 41 |
| `src/box_tree.c` | - | src | 22 |
| `src/browser.c` | - | src | 41 |
| `src/compositor.c` | - | src | 5 |
| `src/css.c` | - | src | 277 |
| `src/css_chain.c` | - | src | 19 |
| `src/css_color.c` | - | src | 21 |
| `src/css_length.c` | - | src | 18 |
| `src/css_select.c` | - | src | 22 |
| `src/data_url.c` | - | src | 6 |
| `src/disk_store.c` | - | src | 10 |
| `src/dom.c` | - | src | 77 |
| `src/dom_debug.c` | - | src | 27 |
| `src/download.c` | - | src | 13 |
| `src/flex_layout.c` | - | src | 19 |
| `src/form.c` | - | src | 10 |
| `src/frame_clock.c` | - | src | 4 |
| `src/freebug.c` | - | src | 11 |
| `src/freedom.c` | - | src | 71 |
| `src/hls.c` | - | src | 13 |
| `src/hostblock.c` | - | src | 20 |
| `src/hostedit.c` | - | src | 14 |
| `src/html_parse.c` | - | src | 34 |
| `src/image_decode.c` | - | src | 36 |
| `src/interp.c` | - | src | 19 |
| `src/js_dom.c` | - | src | 90 |
| `src/js_env.c` | - | src | 42 |
| `src/js_policy.c` | - | src | 6 |
| `src/js_sandbox.c` | - | src | 39 |
| `src/link_nav.c` | - | src | 13 |
| `src/local_store.c` | include <openssl/kdf.h> ifndef OSSL_KDF_PARAM_ARGON2_LANES define OSSL_KDF_PARAM | src | 280 |
| `src/media_decoder.c` | - | src | 35 |
| `src/net_realm.c` | - | src | 11 |
| `src/os_sandbox.c` | - | src | 35 |
| `src/page_view.c` | - | src | 205 |
| `src/pdf_export.c` | - | src | 5 |
| `src/perf_trace.c` | - | src | 15 |
| `src/prefetch.c` | - | src | 28 |
| `src/prefs.c` | - | src | 30 |
| `src/profile.c` | - | src | 16 |
| `src/render_doc.c` | - | src | 22 |
| `src/render_policy.c` | - | src | 5 |
| `src/renderer.c` | - | src | 13 |
| `src/request_policy.c` | - | src | 13 |
| `src/secure_fetch.c` | - | src | 65 |
| `src/svg_render.c` | svg_render — inline <svg> markup -> a bounded list of geometric shapes. | src | 35 |
| `src/tab.c` | - | src | 139 |
| `src/text_shape.c` | - | src | 36 |
| `src/textfield.c` | - | src | 15 |
| `src/tls_impersonate.c` | - | src | 23 |
| `src/ui_layout.c` | - | src | 5 |
| `src/url.c` | - | src | 29 |
| `src/webcaps.c` | - | src | 4 |
| `src/zoom.c` | - | src | 7 |
| `tests/itest_secure_fetch.c` | - | tests | 5 |
| `tests/test_anti_fp.c` | - | tests | 27 |
| `tests/test_block_flow.c` | - | tests | 11 |
| `tests/test_box_style.c` | - | tests | 48 |
| `tests/test_box_tree.c` | - | tests | 58 |
| `tests/test_browser.c` | - | tests | 35 |
| `tests/test_compositor.c` | - | tests | 25 |
| `tests/test_css.c` | - | tests | 265 |
| `tests/test_css_color.c` | - | tests | 30 |
| `tests/test_css_drops.c` | Suite for the parser drop log (spec/css_drops.md). | tests | 32 |
| `tests/test_css_length.c` | - | tests | 31 |
| `tests/test_data_url.c` | - | tests | 32 |
| `tests/test_disk_store.c` | - | tests | 30 |
| `tests/test_dom.c` | - | tests | 49 |
| `tests/test_dom_debug.c` | - | tests | 24 |
| `tests/test_download.c` | - | tests | 26 |
| `tests/test_flex_layout.c` | - | tests | 68 |
| `tests/test_form.c` | - | tests | 24 |
| `tests/test_frame_clock.c` | - | tests | 8 |
| `tests/test_freebug.c` | - | tests | 25 |
| `tests/test_freedom.c` | - | tests | 62 |
| `tests/test_hls.c` | - | tests | 26 |
| `tests/test_hostblock.c` | - | tests | 27 |
| `tests/test_hostedit.c` | include <setjmp.h> include <stdarg.h> include <stddef.h> include <stdint.h> incl | tests | 14 |
| `tests/test_html_parse.c` | - | tests | 35 |
| `tests/test_image_decode.c` | - | tests | 47 |
| `tests/test_interp.c` | - | tests | 42 |
| `tests/test_js_dom.c` | - | tests | 124 |
| `tests/test_js_env.c` | - | tests | 39 |
| `tests/test_js_policy.c` | - | tests | 10 |
| `tests/test_js_sandbox.c` | - | tests | 39 |
| `tests/test_link_nav.c` | - | tests | 29 |
| `tests/test_local_store.c` | - | tests | 28 |
| `tests/test_media_decoder.c` | - | tests | 9 |
| `tests/test_net_realm.c` | - | tests | 18 |
| `tests/test_os_sandbox.c` | - | tests | 30 |
| `tests/test_page_view.c` | - | tests | 163 |
| `tests/test_pdf_export.c` | - | tests | 36 |
| `tests/test_perf_trace.c` | - | tests | 21 |
| `tests/test_prefetch.c` | Tests for prefetch (Hito 29): pure lookahead scanner + parallel download pool. | tests | 29 |
| `tests/test_prefs.c` | - | tests | 26 |
| `tests/test_profile.c` | - | tests | 36 |
| `tests/test_render_doc.c` | - | tests | 55 |
| `tests/test_render_policy.c` | - | tests | 28 |
| `tests/test_renderer.c` | - | tests | 15 |
| `tests/test_request_policy.c` | - | tests | 15 |
| `tests/test_secure_fetch.c` | - | tests | 61 |
| `tests/test_svg_render.c` | tests/test_svg_render.c — CMocka suite for the pure inline-SVG parser (sv_). | tests | 26 |
| `tests/test_tab.c` | - | tests | 105 |
| `tests/test_text_shape.c` | - | tests | 16 |
| `tests/test_textfield.c` | - | tests | 19 |
| `tests/test_tls_impersonate.c` | - | tests | 23 |
| `tests/test_ui.c` | - | tests | 17 |
| `tests/test_url.c` | - | tests | 54 |
| `tests/test_webcaps.c` | - | tests | 15 |
| `tests/test_zoom.c` | - | tests | 14 |
| `tools/ffgeom.py` | - | tools | 12 |
| `tools/gen_psl.c` | - | tools | 12 |
| `tools/mutate.py` | - | tools | 6 |
| `tools/pngdiff.c` | - | tools | 23 |
| `tools/pngprof.py` | - | tools | 4 |
