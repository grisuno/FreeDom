# Index

| File | Purpose | Subsystem | Symbols |
|------|---------|-----------|---------|
| `app.py` | _*_ coding: utf8 _*_ | root | 3 |
| `docker-entrypoint.sh` | - | root | 0 |
| `docker_run.sh` | Thin wrapper. The docker build/run lives in the Makefile (single source of truth | root | 0 |
| `fuzz.sh` | Thin wrapper. The fuzz build/run logic now lives in the Makefile (single source  | root | 0 |
| `fuzz/fuzz_css.c` | - | fuzz | 1 |
| `fuzz/fuzz_data_url.c` | - | fuzz | 1 |
| `fuzz/fuzz_dom.c` | - | fuzz | 2 |
| `fuzz/fuzz_dom_debug.c` | - | fuzz | 1 |
| `fuzz/fuzz_download.c` | - | fuzz | 1 |
| `fuzz/fuzz_freebug.c` | - | fuzz | 1 |
| `fuzz/fuzz_html_parse.c` | - | fuzz | 0 |
| `fuzz/fuzz_image_decode.c` | - | fuzz | 2 |
| `fuzz/fuzz_js_sandbox.c` | - | fuzz | 0 |
| `fuzz/fuzz_page_view.c` | - | fuzz | 0 |
| `fuzz/fuzz_pdf_export.c` | - | fuzz | 1 |
| `fuzz/fuzz_prefetch.c` | libFuzzer harness for the prefetch lookahead scanner (Hito 29). The scanned | fuzz | 1 |
| `fuzz/fuzz_prefs.c` | - | fuzz | 1 |
| `fuzz/fuzz_svg_render.c` | - | fuzz | 1 |
| `fuzz/fuzz_text_shape.c` | - | fuzz | 2 |
| `fuzz/fuzz_tls_impersonate.c` | - | fuzz | 0 |
| `fuzz/fuzz_url.c` | - | fuzz | 2 |
| `gui/browser_ui.c` | - | gui | 408 |
| `gui/browser_ui_internal.h` | ifndef FREEDOM_BROWSER_UI_INTERNAL_H define FREEDOM_BROWSER_UI_INTERNAL_H  ifdef | gui | 6 |
| `gui/bui_theme.c` | - | gui | 6 |
| `gui/freedom_view.c` | - | gui | 2 |
| `gui/svg_paint.c` | svg_paint — Cairo back end for the shapes svg_render extracted. | gui | 5 |
| `gui/ui_render.c` | - | gui | 29 |
| `include/anti_fp.h` | ifndef FREEDOM_ANTI_FP_H define FREEDOM_ANTI_FP_H  include <stddef.h> include <s | include | 10 |
| `include/block_flow.h` | block_flow (bf_) -- vertical margin collapsing for block-level boxes. | include | 2 |
| `include/box_style.h` | ifndef FREEDOM_BOX_STYLE_H define FREEDOM_BOX_STYLE_H  ifdef __cplusplus error " | include | 6 |
| `include/box_tree.h` | ifndef FREEDOM_BOX_TREE_H define FREEDOM_BOX_TREE_H  include <stddef.h>  include | include | 15 |
| `include/browser.h` | ifndef FREEDOM_BROWSER_H define FREEDOM_BROWSER_H  include <stddef.h> include <s | include | 5 |
| `include/compositor.h` | ifndef FREEDOM_COMPOSITOR_H define FREEDOM_COMPOSITOR_H  include <stddef.h>  ifd | include | 3 |
| `include/css.h` | ifndef FREEDOM_CSS_H define FREEDOM_CSS_H  include <stddef.h> include "css_color | include | 49 |
| `include/css_chain.h` | ifndef FREEDOM_CSS_CHAIN_H define FREEDOM_CSS_CHAIN_H  include <lexbor/html/html | include | 4 |
| `include/css_color.h` | ifndef FREEDOM_CSS_COLOR_H define FREEDOM_CSS_COLOR_H  ifdef __cplusplus error " | include | 4 |
| `include/css_length.h` | ifndef FREEDOM_CSS_LENGTH_H define FREEDOM_CSS_LENGTH_H  include <stddef.h>  ifd | include | 10 |
| `include/css_select.h` | ifndef FREEDOM_CSS_SELECT_H define FREEDOM_CSS_SELECT_H  include <stddef.h> incl | include | 15 |
| `include/data_url.h` | ifndef FREEDOM_DATA_URL_H define FREEDOM_DATA_URL_H  include <stddef.h> include  | include | 2 |
| `include/disk_store.h` | ifndef FREEDOM_DISK_STORE_H define FREEDOM_DISK_STORE_H  include <stddef.h> incl | include | 1 |
| `include/dom.h` | ifndef FREEDOM_DOM_H define FREEDOM_DOM_H  include <stddef.h> include <stdint.h> | include | 2 |
| `include/dom_debug.h` | ifndef FREEDOM_DOM_DEBUG_H define FREEDOM_DOM_DEBUG_H  include <stddef.h>  inclu | include | 2 |
| `include/download.h` | ifndef FREEDOM_DOWNLOAD_H define FREEDOM_DOWNLOAD_H  include <stddef.h>  ifdef _ | include | 4 |
| `include/flex_layout.h` | ifndef FREEDOM_FLEX_LAYOUT_H define FREEDOM_FLEX_LAYOUT_H  include <stddef.h>  i | include | 12 |
| `include/form.h` | ifndef FREEDOM_FORM_H define FREEDOM_FORM_H  include <stddef.h>  include "url.h" | include | 6 |
| `include/frame_clock.h` | ifndef FREEDOM_FRAME_CLOCK_H define FREEDOM_FRAME_CLOCK_H  ifdef __cplusplus err | include | 2 |
| `include/freebug.h` | ifndef FREEDOM_FREEBUG_H define FREEDOM_FREEBUG_H  include <stddef.h>  ifdef __c | include | 7 |
| `include/freedom_config.h` | - | include | 8 |
| `include/hls.h` | ifndef FREEDOM_HLS_H define FREEDOM_HLS_H  include <stddef.h>  ifdef __cplusplus | include | 4 |
| `include/hostblock.h` | ifndef FREEDOM_HOSTBLOCK_H define FREEDOM_HOSTBLOCK_H  include <stddef.h>  ifdef | include | 1 |
| `include/hostedit.h` | ifndef FREEDOM_HOSTEDIT_H define FREEDOM_HOSTEDIT_H  include <stddef.h>  ifdef _ | include | 2 |
| `include/html_parse.h` | ifndef FREEDOM_HTML_PARSE_H define FREEDOM_HTML_PARSE_H  include <stddef.h> incl | include | 6 |
| `include/image_decode.h` | ifndef FREEDOM_IMAGE_DECODE_H define FREEDOM_IMAGE_DECODE_H  include <stddef.h>  | include | 4 |
| `include/interp.h` | ifndef FREEDOM_INTERP_H define FREEDOM_INTERP_H  include <stdint.h>  ifdef __cpl | include | 6 |
| `include/js_dom.h` | ifndef FREEDOM_JS_DOM_H define FREEDOM_JS_DOM_H  include "dom.h" include "freebu | include | 4 |
| `include/js_env.h` | ifndef FREEDOM_JS_ENV_H define FREEDOM_JS_ENV_H  include "js_sandbox.h"  ifdef _ | include | 1 |
| `include/js_policy.h` | ifndef FREEDOM_JS_POLICY_H define FREEDOM_JS_POLICY_H  include <stdbool.h>  ifde | include | 1 |
| `include/js_sandbox.h` | ifndef FREEDOM_JS_SANDBOX_H define FREEDOM_JS_SANDBOX_H  include <stddef.h> incl | include | 8 |
| `include/link_nav.h` | ifndef FREEDOM_LINK_NAV_H define FREEDOM_LINK_NAV_H  include <stddef.h>  ifdef _ | include | 4 |
| `include/local_store.h` | ifndef FREEDOM_LOCAL_STORE_H define FREEDOM_LOCAL_STORE_H  include <stddef.h> in | include | 8 |
| `include/media_decoder.h` | ifndef FREEDOM_MEDIA_DECODER_H define FREEDOM_MEDIA_DECODER_H  include <stddef.h | include | 7 |
| `include/net_realm.h` | ifndef FREEDOM_NET_REALM_H define FREEDOM_NET_REALM_H  ifdef __cplusplus error " | include | 2 |
| `include/os_sandbox.h` | ifndef FREEDOM_OS_SANDBOX_H define FREEDOM_OS_SANDBOX_H  include <stddef.h>  ifd | include | 2 |
| `include/page_view.h` | ifndef FREEDOM_PAGE_VIEW_H define FREEDOM_PAGE_VIEW_H  include <stddef.h> includ | include | 12 |
| `include/pdf_export.h` | ifndef FREEDOM_PDF_EXPORT_H define FREEDOM_PDF_EXPORT_H  include <stddef.h>  ifd | include | 5 |
| `include/perf_trace.h` | ifndef FREEDOM_PERF_TRACE_H define FREEDOM_PERF_TRACE_H  ifdef __cplusplus error | include | 4 |
| `include/prefetch.h` | ifndef FREEDOM_PREFETCH_H define FREEDOM_PREFETCH_H  ifdef __cplusplus error "Fr | include | 8 |
| `include/prefs.h` | ifndef FREEDOM_PREFS_H define FREEDOM_PREFS_H  include <stddef.h>  ifdef __cplus | include | 10 |
| `include/profile.h` | ifndef FREEDOM_PROFILE_H define FREEDOM_PROFILE_H  include <stddef.h> include <s | include | 4 |
| `include/psl_data.h` | ifndef FREEDOM_PSL_DATA_H define FREEDOM_PSL_DATA_H  include <stddef.h>  ifdef _ | include | 1 |
| `include/render_doc.h` | ifndef FREEDOM_RENDER_DOC_H define FREEDOM_RENDER_DOC_H  include <stddef.h>  inc | include | 3 |
| `include/render_policy.h` | ifndef FREEDOM_RENDER_POLICY_H define FREEDOM_RENDER_POLICY_H  include <stdbool. | include | 3 |
| `include/renderer.h` | ifndef FREEDOM_RENDERER_H define FREEDOM_RENDERER_H  include <stddef.h>  ifdef _ | include | 4 |
| `include/request_policy.h` | ifndef FREEDOM_REQUEST_POLICY_H define FREEDOM_REQUEST_POLICY_H  include <stddef | include | 1 |
| `include/secure_fetch.h` | ifndef FREEDOM_SECURE_FETCH_H define FREEDOM_SECURE_FETCH_H  include <stddef.h>  | include | 15 |
| `include/svg_paint.h` | ifndef FREEDOM_SVG_PAINT_H define FREEDOM_SVG_PAINT_H  include <cairo.h>  includ | include | 1 |
| `include/svg_render.h` | ifndef FREEDOM_SVG_RENDER_H define FREEDOM_SVG_RENDER_H  include <stddef.h>  ifd | include | 12 |
| `include/tab.h` | ifndef FREEDOM_TAB_H define FREEDOM_TAB_H  include <stddef.h> include <stdint.h> | include | 5 |
| `include/text_shape.h` | - | include | 4 |
| `include/textfield.h` | ifndef FREEDOM_TEXTFIELD_H define FREEDOM_TEXTFIELD_H  include <stddef.h>  ifdef | include | 3 |
| `include/tls_impersonate.h` | ifndef FREEDOM_TLS_IMPERSONATE_H define FREEDOM_TLS_IMPERSONATE_H  include <stdd | include | 12 |
| `include/ui.h` | ifndef FREEDOM_UI_H define FREEDOM_UI_H  include <stddef.h>  ifdef __cplusplus e | include | 5 |
| `include/url.h` | ifndef FREEDOM_URL_H define FREEDOM_URL_H  include <stddef.h>  ifdef __cplusplus | include | 4 |
| `include/util.h` | util.h — shared pure helpers (no I/O except where noted). Static inline so each  | include | 6 |
| `include/webcaps.h` | ifndef FREEDOM_WEBCAPS_H define FREEDOM_WEBCAPS_H  include <stdbool.h>  include  | include | 3 |
| `include/zoom.h` | ifndef FREEDOM_ZOOM_H define FREEDOM_ZOOM_H  ifdef __cplusplus error "Freedom is | include | 4 |
| `install.sh` | Exit immediately if a command exits with a non-zero status, if an undefined vari | root | 0 |
| `run_freedom.sh` | Thin wrapper. Launches a nested weston (for boxes without a Wayland session), th | root | 0 |
| `src/anti_fp.c` | - | src | 23 |
| `src/block_flow.c` | block_flow (bf_) -- vertical margin collapsing. See spec/block_flow.md. | src | 4 |
| `src/box_style.c` | - | src | 38 |
| `src/box_tree.c` | - | src | 18 |
| `src/browser.c` | - | src | 37 |
| `src/compositor.c` | - | src | 5 |
| `src/css.c` | - | src | 226 |
| `src/css_chain.c` | - | src | 14 |
| `src/css_color.c` | - | src | 19 |
| `src/css_length.c` | - | src | 18 |
| `src/css_select.c` | - | src | 16 |
| `src/data_url.c` | - | src | 6 |
| `src/disk_store.c` | - | src | 6 |
| `src/dom.c` | - | src | 63 |
| `src/dom_debug.c` | - | src | 24 |
| `src/download.c` | - | src | 12 |
| `src/flex_layout.c` | - | src | 19 |
| `src/form.c` | - | src | 8 |
| `src/frame_clock.c` | - | src | 4 |
| `src/freebug.c` | - | src | 8 |
| `src/freedom.c` | - | src | 33 |
| `src/hls.c` | - | src | 9 |
| `src/hostblock.c` | - | src | 18 |
| `src/hostedit.c` | - | src | 13 |
| `src/html_parse.c` | - | src | 26 |
| `src/image_decode.c` | - | src | 26 |
| `src/interp.c` | - | src | 19 |
| `src/js_dom.c` | - | src | 63 |
| `src/js_env.c` | - | src | 27 |
| `src/js_policy.c` | - | src | 6 |
| `src/js_sandbox.c` | - | src | 27 |
| `src/link_nav.c` | - | src | 10 |
| `src/local_store.c` | include <openssl/kdf.h> ifndef OSSL_KDF_PARAM_ARGON2_LANES define OSSL_KDF_PARAM | src | 271 |
| `src/media_decoder.c` | - | src | 12 |
| `src/net_realm.c` | - | src | 10 |
| `src/os_sandbox.c` | - | src | 28 |
| `src/page_view.c` | - | src | 168 |
| `src/pdf_export.c` | - | src | 4 |
| `src/perf_trace.c` | - | src | 12 |
| `src/prefetch.c` | - | src | 17 |
| `src/prefs.c` | - | src | 26 |
| `src/profile.c` | - | src | 9 |
| `src/render_doc.c` | - | src | 18 |
| `src/render_policy.c` | - | src | 5 |
| `src/renderer.c` | - | src | 5 |
| `src/request_policy.c` | - | src | 11 |
| `src/secure_fetch.c` | - | src | 42 |
| `src/svg_render.c` | svg_render — inline <svg> markup -> a bounded list of geometric shapes. | src | 31 |
| `src/tab.c` | - | src | 73 |
| `src/text_shape.c` | - | src | 14 |
| `src/textfield.c` | - | src | 12 |
| `src/tls_impersonate.c` | - | src | 18 |
| `src/ui_layout.c` | - | src | 4 |
| `src/url.c` | - | src | 27 |
| `src/webcaps.c` | - | src | 4 |
| `src/zoom.c` | - | src | 7 |
| `tests/itest_secure_fetch.c` | - | tests | 2 |
| `tests/test_anti_fp.c` | - | tests | 15 |
| `tests/test_block_flow.c` | - | tests | 8 |
| `tests/test_box_style.c` | - | tests | 39 |
| `tests/test_box_tree.c` | - | tests | 52 |
| `tests/test_browser.c` | - | tests | 15 |
| `tests/test_compositor.c` | - | tests | 21 |
| `tests/test_css.c` | - | tests | 250 |
| `tests/test_css_color.c` | - | tests | 26 |
| `tests/test_css_drops.c` | Suite for the parser drop log (spec/css_drops.md). | tests | 25 |
| `tests/test_css_length.c` | - | tests | 25 |
| `tests/test_data_url.c` | - | tests | 23 |
| `tests/test_disk_store.c` | - | tests | 15 |
| `tests/test_dom.c` | - | tests | 37 |
| `tests/test_dom_debug.c` | - | tests | 11 |
| `tests/test_download.c` | - | tests | 21 |
| `tests/test_flex_layout.c` | - | tests | 56 |
| `tests/test_form.c` | - | tests | 20 |
| `tests/test_frame_clock.c` | - | tests | 4 |
| `tests/test_freebug.c` | - | tests | 13 |
| `tests/test_freedom.c` | - | tests | 50 |
| `tests/test_hls.c` | - | tests | 16 |
| `tests/test_hostblock.c` | - | tests | 22 |
| `tests/test_hostedit.c` | include <setjmp.h> include <stdarg.h> include <stddef.h> include <stdint.h> incl | tests | 11 |
| `tests/test_html_parse.c` | - | tests | 22 |
| `tests/test_image_decode.c` | - | tests | 37 |
| `tests/test_interp.c` | - | tests | 37 |
| `tests/test_js_dom.c` | - | tests | 108 |
| `tests/test_js_env.c` | - | tests | 26 |
| `tests/test_js_policy.c` | - | tests | 5 |
| `tests/test_js_sandbox.c` | - | tests | 30 |
| `tests/test_link_nav.c` | - | tests | 22 |
| `tests/test_local_store.c` | - | tests | 17 |
| `tests/test_media_decoder.c` | - | tests | 6 |
| `tests/test_net_realm.c` | - | tests | 13 |
| `tests/test_os_sandbox.c` | - | tests | 19 |
| `tests/test_page_view.c` | - | tests | 131 |
| `tests/test_pdf_export.c` | - | tests | 30 |
| `tests/test_perf_trace.c` | - | tests | 12 |
| `tests/test_prefetch.c` | Tests for prefetch (Hito 29): pure lookahead scanner + parallel download pool. | tests | 11 |
| `tests/test_prefs.c` | - | tests | 15 |
| `tests/test_profile.c` | - | tests | 16 |
| `tests/test_render_doc.c` | - | tests | 36 |
| `tests/test_render_policy.c` | - | tests | 20 |
| `tests/test_renderer.c` | - | tests | 8 |
| `tests/test_request_policy.c` | - | tests | 12 |
| `tests/test_secure_fetch.c` | - | tests | 48 |
| `tests/test_svg_render.c` | tests/test_svg_render.c — CMocka suite for the pure inline-SVG parser (sv_). | tests | 16 |
| `tests/test_tab.c` | - | tests | 85 |
| `tests/test_text_shape.c` | - | tests | 9 |
| `tests/test_textfield.c` | - | tests | 8 |
| `tests/test_tls_impersonate.c` | - | tests | 11 |
| `tests/test_ui.c` | - | tests | 12 |
| `tests/test_url.c` | - | tests | 45 |
| `tests/test_webcaps.c` | - | tests | 11 |
| `tests/test_zoom.c` | - | tests | 11 |
| `tools/ffgeom.py` | - | tools | 11 |
| `tools/gen_psl.c` | - | tools | 8 |
| `tools/mutate.py` | - | tools | 6 |
| `tools/pngdiff.c` | - | tools | 13 |
| `tools/pngprof.py` | - | tools | 4 |
