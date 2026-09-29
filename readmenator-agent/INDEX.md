# Index

| File | Purpose | Subsystem | Symbols |
|------|---------|-----------|---------|
| `app.py` | app.py  Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 0 | root | 3 |
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
| `gui/browser_ui.c` | - | gui | 496 |
| `gui/browser_ui_internal.h` | - | gui | 10 |
| `gui/bui_theme.c` | - | gui | 6 |
| `gui/freedom_view.c` | - | gui | 2 |
| `gui/svg_paint.c` | svg_paint — Cairo back end for the shapes svg_render extracted. | gui | 5 |
| `gui/ui_render.c` | - | gui | 29 |
| `include/anti_fp.h` | - | include | 35 |
| `include/block_flow.h` | block_flow (bf_) -- vertical margin collapsing for block-level boxes. | include | 4 |
| `include/box_style.h` | - | include | 24 |
| `include/box_tree.h` | - | include | 30 |
| `include/browser.h` | - | include | 17 |
| `include/compositor.h` | - | include | 9 |
| `include/css.h` | - | include | 127 |
| `include/css_box.h` | - | include | 25 |
| `include/css_chain.h` | - | include | 5 |
| `include/css_color.h` | - | include | 7 |
| `include/css_decl.h` | Bound for the ::before/::after content string pool (and the grid-template | include | 12 |
| `include/css_gradient.h` | - | include | 3 |
| `include/css_length.h` | - | include | 20 |
| `include/css_select.h` | - | include | 22 |
| `include/css_text.h` | - | include | 17 |
| `include/css_values.h` | Single owner of CSS value interpretation for colors and backgrounds. | include | 6 |
| `include/data_url.h` | - | include | 6 |
| `include/disk_store.h` | - | include | 3 |
| `include/dom.h` | - | include | 20 |
| `include/dom_debug.h` | - | include | 4 |
| `include/download.h` | - | include | 9 |
| `include/flex_layout.h` | - | include | 29 |
| `include/form.h` | - | include | 12 |
| `include/frame_clock.h` | - | include | 7 |
| `include/freebug.h` | - | include | 18 |
| `include/freedom_config.h` | - | include | 10 |
| `include/hls.h` | - | include | 8 |
| `include/hostblock.h` | - | include | 10 |
| `include/hostedit.h` | - | include | 5 |
| `include/html_parse.h` | - | include | 24 |
| `include/image_decode.h` | - | include | 13 |
| `include/interp.h` | - | include | 22 |
| `include/js_dom.h` | - | include | 19 |
| `include/js_env.h` | - | include | 3 |
| `include/js_policy.h` | - | include | 7 |
| `include/js_sandbox.h` | - | include | 19 |
| `include/link_nav.h` | - | include | 11 |
| `include/local_store.h` | - | include | 11 |
| `include/media_decoder.h` | - | include | 12 |
| `include/net_realm.h` | - | include | 10 |
| `include/os_sandbox.h` | - | include | 12 |
| `include/page_view.h` | - | include | 68 |
| `include/pdf_export.h` | - | include | 10 |
| `include/perf_trace.h` | - | include | 17 |
| `include/prefetch.h` | - | include | 21 |
| `include/prefs.h` | - | include | 18 |
| `include/profile.h` | - | include | 9 |
| `include/psl_data.h` | - | include | 7 |
| `include/render_doc.h` | - | include | 25 |
| `include/render_policy.h` | - | include | 9 |
| `include/renderer.h` | - | include | 7 |
| `include/request_policy.h` | - | include | 5 |
| `include/secure_fetch.h` | - | include | 33 |
| `include/svg_paint.h` | - | include | 2 |
| `include/svg_render.h` | - | include | 19 |
| `include/tab.h` | - | include | 28 |
| `include/text_shape.h` | - | include | 11 |
| `include/textfield.h` | - | include | 15 |
| `include/tls_impersonate.h` | - | include | 23 |
| `include/ui.h` | - | include | 15 |
| `include/url.h` | - | include | 14 |
| `include/util.h` | util.h — shared pure helpers (no I/O except where noted). Static inline so each  | include | 6 |
| `include/webcaps.h` | - | include | 5 |
| `include/zoom.h` | - | include | 10 |
| `install.sh` | Exit immediately if a command exits with a non-zero status, | root | 0 |
| `run_freedom.sh` | Thin wrapper. Launches a nested weston (for boxes without a Wayland session), th | root | 0 |
| `src/anti_fp.c` | - | src | 23 |
| `src/block_flow.c` | block_flow (bf_) -- vertical margin collapsing. See spec/block_flow.md. | src | 4 |
| `src/box_style.c` | - | src | 40 |
| `src/box_tree.c` | - | src | 20 |
| `src/browser.c` | - | src | 37 |
| `src/compositor.c` | - | src | 5 |
| `src/css.c` | - | src | 219 |
| `src/css_box.c` | - | src | 47 |
| `src/css_chain.c` | - | src | 15 |
| `src/css_color.c` | - | src | 20 |
| `src/css_gradient.c` | - | src | 13 |
| `src/css_length.c` | - | src | 18 |
| `src/css_select.c` | - | src | 18 |
| `src/css_text.c` | --- text-presentation extensions (Hito 23b-6) --- | src | 17 |
| `src/css_values.c` | - | src | 6 |
| `src/data_url.c` | - | src | 6 |
| `src/disk_store.c` | - | src | 6 |
| `src/dom.c` | - | src | 63 |
| `src/dom_debug.c` | - | src | 24 |
| `src/download.c` | - | src | 12 |
| `src/flex_layout.c` | - | src | 20 |
| `src/form.c` | - | src | 8 |
| `src/frame_clock.c` | - | src | 4 |
| `src/freebug.c` | - | src | 9 |
| `src/freedom.c` | - | src | 38 |
| `src/hls.c` | - | src | 10 |
| `src/hostblock.c` | - | src | 18 |
| `src/hostedit.c` | - | src | 13 |
| `src/html_parse.c` | - | src | 26 |
| `src/image_decode.c` | - | src | 27 |
| `src/interp.c` | - | src | 19 |
| `src/js_dom.c` | - | src | 69 |
| `src/js_env.c` | - | src | 28 |
| `src/js_policy.c` | - | src | 6 |
| `src/js_sandbox.c` | - | src | 29 |
| `src/link_nav.c` | - | src | 10 |
| `src/local_store.c` | - | src | 271 |
| `src/media_decoder.c` | - | src | 15 |
| `src/net_realm.c` | - | src | 10 |
| `src/os_sandbox.c` | - | src | 31 |
| `src/page_view.c` | - | src | 201 |
| `src/pdf_export.c` | - | src | 4 |
| `src/perf_trace.c` | - | src | 12 |
| `src/prefetch.c` | - | src | 17 |
| `src/prefs.c` | - | src | 26 |
| `src/profile.c` | - | src | 9 |
| `src/render_doc.c` | - | src | 19 |
| `src/render_policy.c` | - | src | 5 |
| `src/renderer.c` | - | src | 6 |
| `src/request_policy.c` | - | src | 11 |
| `src/secure_fetch.c` | - | src | 48 |
| `src/svg_render.c` | svg_render — inline <svg> markup -> a bounded list of geometric shapes. | src | 33 |
| `src/tab.c` | - | src | 90 |
| `src/text_shape.c` | - | src | 15 |
| `src/textfield.c` | - | src | 12 |
| `src/tls_impersonate.c` | - | src | 20 |
| `src/ui_layout.c` | - | src | 4 |
| `src/url.c` | - | src | 27 |
| `src/webcaps.c` | - | src | 4 |
| `src/zoom.c` | - | src | 7 |
| `tests/itest_secure_fetch.c` | - | tests | 2 |
| `tests/test_anti_fp.c` | - | tests | 15 |
| `tests/test_block_flow.c` | - | tests | 8 |
| `tests/test_box_style.c` | - | tests | 41 |
| `tests/test_box_tree.c` | - | tests | 56 |
| `tests/test_browser.c` | - | tests | 15 |
| `tests/test_compositor.c` | - | tests | 21 |
| `tests/test_css.c` | - | tests | 266 |
| `tests/test_css_box.c` | - | tests | 9 |
| `tests/test_css_color.c` | - | tests | 29 |
| `tests/test_css_drops.c` | Suite for the parser drop log (spec/css_drops.md). | tests | 25 |
| `tests/test_css_gradient.c` | - | tests | 7 |
| `tests/test_css_length.c` | - | tests | 25 |
| `tests/test_css_text.c` | - | tests | 6 |
| `tests/test_css_values.c` | - | tests | 6 |
| `tests/test_data_url.c` | - | tests | 23 |
| `tests/test_disk_store.c` | - | tests | 16 |
| `tests/test_dom.c` | - | tests | 37 |
| `tests/test_dom_debug.c` | - | tests | 11 |
| `tests/test_download.c` | - | tests | 21 |
| `tests/test_flex_layout.c` | - | tests | 63 |
| `tests/test_form.c` | - | tests | 20 |
| `tests/test_frame_clock.c` | - | tests | 4 |
| `tests/test_freebug.c` | - | tests | 13 |
| `tests/test_freedom.c` | - | tests | 61 |
| `tests/test_hls.c` | - | tests | 16 |
| `tests/test_hostblock.c` | - | tests | 22 |
| `tests/test_hostedit.c` | - | tests | 11 |
| `tests/test_html_parse.c` | - | tests | 23 |
| `tests/test_image_decode.c` | - | tests | 37 |
| `tests/test_interp.c` | - | tests | 37 |
| `tests/test_js_dom.c` | - | tests | 109 |
| `tests/test_js_env.c` | - | tests | 26 |
| `tests/test_js_policy.c` | - | tests | 5 |
| `tests/test_js_sandbox.c` | - | tests | 30 |
| `tests/test_link_nav.c` | - | tests | 22 |
| `tests/test_local_store.c` | - | tests | 18 |
| `tests/test_media_decoder.c` | - | tests | 6 |
| `tests/test_net_realm.c` | - | tests | 13 |
| `tests/test_os_sandbox.c` | - | tests | 19 |
| `tests/test_page_view.c` | - | tests | 162 |
| `tests/test_pdf_export.c` | - | tests | 30 |
| `tests/test_perf_trace.c` | - | tests | 12 |
| `tests/test_prefetch.c` | Tests for prefetch (Hito 29): pure lookahead scanner + parallel download pool. | tests | 12 |
| `tests/test_prefs.c` | - | tests | 15 |
| `tests/test_profile.c` | - | tests | 17 |
| `tests/test_render_doc.c` | - | tests | 36 |
| `tests/test_render_policy.c` | - | tests | 21 |
| `tests/test_renderer.c` | - | tests | 8 |
| `tests/test_request_policy.c` | - | tests | 12 |
| `tests/test_secure_fetch.c` | - | tests | 48 |
| `tests/test_svg_render.c` | tests/test_svg_render.c — CMocka suite for the pure inline-SVG parser (sv_). | tests | 16 |
| `tests/test_tab.c` | - | tests | 86 |
| `tests/test_text_shape.c` | - | tests | 9 |
| `tests/test_textfield.c` | - | tests | 8 |
| `tests/test_tls_impersonate.c` | - | tests | 11 |
| `tests/test_ui.c` | - | tests | 12 |
| `tests/test_url.c` | - | tests | 45 |
| `tests/test_webcaps.c` | - | tests | 11 |
| `tests/test_zoom.c` | - | tests | 11 |
| `tools/ffgeom.py` | ffgeom -- Firefox geometry as TEXT, no image reading.  The `make geom` loop need | tools | 12 |
| `tools/gen_psl.c` | - | tools | 8 |
| `tools/mutate.py` | mutate -- compile-time mutation testing for the CMocka suites.  One mutant = one | tools | 6 |
| `tools/pngdiff.c` | - | tools | 14 |
| `tools/pngprof.py` | pngprof -- structural ink-profile dump for page screenshots.  Build-time tool fo | tools | 4 |
| `tools/snapshot.py` | Freeze a live page into one self-contained HTML file for `make parity`.  Both en | tools | 6 |
