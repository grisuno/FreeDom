# freedom-0.0.3 API Reference

> Generated offline by readmenator: 213 modules, 3328 documented entities, documentation coverage 39.6% (1310/3306 public items). Deterministic, zero tokens: signatures from source, docs parsed from Google, NumPy, reST, Javadoc/JSDoc/Doxygen, C# XML, and Rustdoc comments.

Navigate: [Interactive architecture and flows](flows.html) | [Architecture and flows (Mermaid)](architecture.md) | [Class hierarchy](classes.md) | [General index](genindex.md) | [Coverage and warnings](COVERAGE.md) | [`api/index.json`](api/index.json) | [HTML browser](index.html)

Languages: c (112), h (86), py (10), sh (5)

## Modules

### `.`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`app`](modules/app.py.md) | app.py | 0 | 3 | 100.0% |
| [`docker-entrypoint.sh`](modules/docker-entrypoint.sh.md) |  | 0 | 0 | 0.0% |
| [`docker_run.sh`](modules/docker_run.sh.md) | Thin wrapper. | 0 | 0 | 100.0% |
| [`fuzz.sh`](modules/fuzz.sh.md) | Thin wrapper. | 0 | 0 | 100.0% |
| [`install.sh`](modules/install.sh.md) | Exit immediately if a command exits with a non-zero status, | 0 | 0 | 100.0% |
| [`run_freedom.sh`](modules/run_freedom.sh.md) | Thin wrapper. | 0 | 0 | 100.0% |

### `fuzz`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`fuzz/fuzz_css.c`](modules/fuzz.fuzz_css.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_data_url.c`](modules/fuzz.fuzz_data_url.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_dom.c`](modules/fuzz.fuzz_dom.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_dom_debug.c`](modules/fuzz.fuzz_dom_debug.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_download.c`](modules/fuzz.fuzz_download.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_freebug.c`](modules/fuzz.fuzz_freebug.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_html_parse.c`](modules/fuzz.fuzz_html_parse.c.md) |  | 0 | 0 | 0.0% |
| [`fuzz/fuzz_image_decode.c`](modules/fuzz.fuzz_image_decode.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_import_map.c`](modules/fuzz.fuzz_import_map.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_js_dom.c`](modules/fuzz.fuzz_js_dom.c.md) |  | 0 | 2 | 33.3% |
| [`fuzz/fuzz_js_geom.c`](modules/fuzz.fuzz_js_geom.c.md) |  | 1 | 1 | 0.0% |
| [`fuzz/fuzz_js_sandbox.c`](modules/fuzz.fuzz_js_sandbox.c.md) |  | 1 | 2 | 25.0% |
| [`fuzz/fuzz_page_view.c`](modules/fuzz.fuzz_page_view.c.md) |  | 0 | 0 | 0.0% |
| [`fuzz/fuzz_pdf_export.c`](modules/fuzz.fuzz_pdf_export.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_prefetch.c`](modules/fuzz.fuzz_prefetch.c.md) | libFuzzer harness for the prefetch lookahead scanner (Hito 29). | 0 | 1 | 50.0% |
| [`fuzz/fuzz_prefs.c`](modules/fuzz.fuzz_prefs.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_svg_render.c`](modules/fuzz.fuzz_svg_render.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_text_case.c`](modules/fuzz.fuzz_text_case.c.md) | libFuzzer harness for text_case (spec/text_case.md): case mapping and the | 0 | 1 | 50.0% |
| [`fuzz/fuzz_text_shape.c`](modules/fuzz.fuzz_text_shape.c.md) |  | 0 | 4 | 0.0% |
| [`fuzz/fuzz_tls_impersonate.c`](modules/fuzz.fuzz_tls_impersonate.c.md) |  | 0 | 0 | 0.0% |
| [`fuzz/fuzz_url.c`](modules/fuzz.fuzz_url.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_web_storage.c`](modules/fuzz.fuzz_web_storage.c.md) |  | 0 | 0 | 0.0% |
| [`fuzz/fuzz_webfont.c`](modules/fuzz.fuzz_webfont.c.md) | libFuzzer harness for the webfont lookahead scanner (spec/webfont.md). | 0 | 1 | 50.0% |

### `gui`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`gui/browser_ui.c`](modules/gui.browser_ui.c.md) |  | 42 | 198 | 32.8% |
| [`gui/browser_ui_internal.h`](modules/gui.browser_ui_internal.h.md) |  | 5 | 4 | 50.0% |
| [`gui/bui_theme.c`](modules/gui.bui_theme.c.md) |  | 0 | 6 | 85.7% |
| [`gui/freedom_view.c`](modules/gui.freedom_view.c.md) |  | 0 | 2 | 0.0% |
| [`gui/svg_paint.c`](modules/gui.svg_paint.c.md) | svg_paint — Cairo back end for the shapes svg_render extracted. | 0 | 1 | 100.0% |
| [`gui/ui_render.c`](modules/gui.ui_render.c.md) |  | 1 | 6 | 37.5% |

### `include`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`include/anti_fp.h`](modules/include.anti_fp.h.md) |  | 0 | 34 | 60.0% |
| [`include/block_flow.h`](modules/include.block_flow.h.md) | block_flow (bf_) -- vertical margin collapsing for block-level boxes. | 0 | 3 | 50.0% |
| [`include/box_blur.h`](modules/include.box_blur.h.md) | Gaussian blur of an 8-bit alpha mask by three box passes per axis (spec/box_blur.md). | 0 | 3 | 100.0% |
| [`include/box_style.h`](modules/include.box_style.h.md) |  | 12 | 18 | 64.5% |
| [`include/box_tree.h`](modules/include.box_tree.h.md) |  | 5 | 27 | 36.4% |
| [`include/browser.h`](modules/include.browser.h.md) |  | 2 | 16 | 47.4% |
| [`include/compositor.h`](modules/include.compositor.h.md) |  | 5 | 3 | 88.9% |
| [`include/css.h`](modules/include.css.h.md) |  | 72 | 67 | 72.9% |
| [`include/css_atrule.h`](modules/include.css_atrule.h.md) |  | 2 | 7 | 70.0% |
| [`include/css_box.h`](modules/include.css_box.h.md) |  | 0 | 25 | 0.0% |
| [`include/css_chain.h`](modules/include.css_chain.h.md) |  | 2 | 5 | 25.0% |
| [`include/css_color.h`](modules/include.css_color.h.md) |  | 3 | 3 | 42.9% |
| [`include/css_decl.h`](modules/include.css_decl.h.md) |  | 2 | 11 | 14.3% |
| [`include/css_gradient.h`](modules/include.css_gradient.h.md) |  | 4 | 8 | 30.8% |
| [`include/css_index.h`](modules/include.css_index.h.md) |  | 3 | 3 | 42.9% |
| [`include/css_length.h`](modules/include.css_length.h.md) |  | 5 | 14 | 55.0% |
| [`include/css_mask.h`](modules/include.css_mask.h.md) | CSS Masking 1, alpha gradients only (spec/css_mask.md). | 4 | 5 | 50.0% |
| [`include/css_mq.h`](modules/include.css_mq.h.md) |  | 2 | 3 | 50.0% |
| [`include/css_select.h`](modules/include.css_select.h.md) |  | 10 | 23 | 61.8% |
| [`include/css_text.h`](modules/include.css_text.h.md) |  | 0 | 16 | 0.0% |
| [`include/css_values.h`](modules/include.css_values.h.md) | Single owner of CSS value interpretation for colors and backgrounds. | 0 | 8 | 33.3% |
| [`include/css_vars.h`](modules/include.css_vars.h.md) |  | 4 | 14 | 73.7% |
| [`include/data_url.h`](modules/include.data_url.h.md) |  | 1 | 4 | 33.3% |
| [`include/disk_store.h`](modules/include.disk_store.h.md) |  | 1 | 1 | 33.3% |
| [`include/dom.h`](modules/include.dom.h.md) |  | 4 | 23 | 64.3% |
| [`include/dom_debug.h`](modules/include.dom_debug.h.md) |  | 0 | 3 | 75.0% |
| [`include/download.h`](modules/include.download.h.md) |  | 1 | 7 | 11.1% |
| [`include/flex_layout.h`](modules/include.flex_layout.h.md) |  | 10 | 32 | 53.5% |
| [`include/form.h`](modules/include.form.h.md) |  | 7 | 3 | 27.3% |
| [`include/frame_clock.h`](modules/include.frame_clock.h.md) |  | 2 | 4 | 14.3% |
| [`include/freebug.h`](modules/include.freebug.h.md) |  | 4 | 13 | 72.2% |
| [`include/freedom_config.h`](modules/include.freedom_config.h.md) |  | 0 | 10 | 90.9% |
| [`include/hls.h`](modules/include.hls.h.md) |  | 4 | 3 | 62.5% |
| [`include/host_conf.h`](modules/include.host_conf.h.md) |  | 1 | 7 | 55.6% |
| [`include/hostblock.h`](modules/include.hostblock.h.md) |  | 4 | 5 | 50.0% |
| [`include/hostedit.h`](modules/include.hostedit.h.md) |  | 1 | 3 | 60.0% |
| [`include/html_parse.h`](modules/include.html_parse.h.md) |  | 5 | 18 | 50.0% |
| [`include/image_decode.h`](modules/include.image_decode.h.md) |  | 4 | 8 | 46.2% |
| [`include/import_map.h`](modules/include.import_map.h.md) |  | 1 | 8 | 30.0% |
| [`include/interp.h`](modules/include.interp.h.md) |  | 10 | 11 | 31.8% |
| [`include/js_dom.h`](modules/include.js_dom.h.md) |  | 5 | 12 | 38.9% |
| [`include/js_env.h`](modules/include.js_env.h.md) |  | 1 | 1 | 0.0% |
| [`include/js_geom.h`](modules/include.js_geom.h.md) |  | 3 | 15 | 78.9% |
| [`include/js_location.h`](modules/include.js_location.h.md) |  | 0 | 5 | 50.0% |
| [`include/js_policy.h`](modules/include.js_policy.h.md) |  | 1 | 5 | 42.9% |
| [`include/js_sandbox.h`](modules/include.js_sandbox.h.md) |  | 6 | 17 | 54.2% |
| [`include/js_trusted.h`](modules/include.js_trusted.h.md) |  | 4 | 11 | 37.5% |
| [`include/link_nav.h`](modules/include.link_nav.h.md) |  | 6 | 4 | 36.4% |
| [`include/local_store.h`](modules/include.local_store.h.md) |  | 2 | 8 | 18.2% |
| [`include/media_decoder.h`](modules/include.media_decoder.h.md) |  | 4 | 7 | 75.0% |
| [`include/net_realm.h`](modules/include.net_realm.h.md) |  | 4 | 5 | 20.0% |
| [`include/os_sandbox.h`](modules/include.os_sandbox.h.md) |  | 4 | 7 | 50.0% |
| [`include/page_view.h`](modules/include.page_view.h.md) |  | 13 | 73 | 59.8% |
| [`include/pdf_export.h`](modules/include.pdf_export.h.md) |  | 1 | 8 | 30.0% |
| [`include/perf_trace.h`](modules/include.perf_trace.h.md) |  | 5 | 11 | 52.9% |
| [`include/prefetch.h`](modules/include.prefetch.h.md) |  | 11 | 16 | 53.6% |
| [`include/prefs.h`](modules/include.prefs.h.md) |  | 4 | 13 | 38.9% |
| [`include/profile.h`](modules/include.profile.h.md) |  | 3 | 5 | 22.2% |
| [`include/psl_data.h`](modules/include.psl_data.h.md) |  | 0 | 0 | 0.0% |
| [`include/render_doc.h`](modules/include.render_doc.h.md) |  | 6 | 20 | 48.1% |
| [`include/render_policy.h`](modules/include.render_policy.h.md) |  | 3 | 5 | 77.8% |
| [`include/renderer.h`](modules/include.renderer.h.md) |  | 3 | 3 | 14.3% |
| [`include/request_policy.h`](modules/include.request_policy.h.md) |  | 1 | 3 | 60.0% |
| [`include/secure_fetch.h`](modules/include.secure_fetch.h.md) |  | 9 | 32 | 50.0% |
| [`include/svg_paint.h`](modules/include.svg_paint.h.md) |  | 0 | 1 | 50.0% |
| [`include/svg_render.h`](modules/include.svg_render.h.md) |  | 9 | 8 | 38.9% |
| [`include/tab.h`](modules/include.tab.h.md) |  | 12 | 29 | 45.2% |
| [`include/text_case.h`](modules/include.text_case.h.md) | Case mapping for text-transform and synthesized small caps (spec/text_case.md). | 1 | 6 | 75.0% |
| [`include/text_shape.h`](modules/include.text_shape.h.md) |  | 5 | 18 | 70.8% |
| [`include/textfield.h`](modules/include.textfield.h.md) |  | 3 | 11 | 53.3% |
| [`include/tls_impersonate.h`](modules/include.tls_impersonate.h.md) |  | 4 | 18 | 30.4% |
| [`include/ui.h`](modules/include.ui.h.md) |  | 7 | 10 | 33.3% |
| [`include/url.h`](modules/include.url.h.md) |  | 3 | 10 | 50.0% |
| [`include/util.h`](modules/include.util.h.md) | util.h — shared pure helpers (no I/O except where noted). | 0 | 5 | 33.3% |
| [`include/web_storage.h`](modules/include.web_storage.h.md) |  | 1 | 11 | 61.5% |
| [`include/webcaps.h`](modules/include.webcaps.h.md) |  | 4 | 0 | 80.0% |
| [`include/webfont.h`](modules/include.webfont.h.md) |  | 3 | 13 | 17.6% |
| [`include/webfont_load.h`](modules/include.webfont_load.h.md) |  | 1 | 5 | 14.3% |
| [`include/wl_display.h`](modules/include.wl_display.h.md) |  | 0 | 5 | 33.3% |
| [`include/ws_hub.h`](modules/include.ws_hub.h.md) |  | 1 | 13 | 73.3% |
| [`include/zoom.h`](modules/include.zoom.h.md) |  | 0 | 9 | 60.0% |

### `src`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`src/anti_fp.c`](modules/src.anti_fp.c.md) |  | 0 | 22 | 73.9% |
| [`src/block_flow.c`](modules/src.block_flow.c.md) | block_flow (bf_) -- vertical margin collapsing. | 0 | 3 | 50.0% |
| [`src/box_blur.c`](modules/src.box_blur.c.md) |  | 0 | 3 | 25.0% |
| [`src/box_style.c`](modules/src.box_style.c.md) |  | 2 | 42 | 31.1% |
| [`src/box_tree.c`](modules/src.box_tree.c.md) |  | 0 | 14 | 33.3% |
| [`src/browser.c`](modules/src.browser.c.md) |  | 0 | 30 | 25.8% |
| [`src/compositor.c`](modules/src.compositor.c.md) |  | 0 | 4 | 60.0% |
| [`src/css.c`](modules/src.css.c.md) |  | 8 | 70 | 24.1% |
| [`src/css_atrule.c`](modules/src.css_atrule.c.md) |  | 0 | 4 | 80.0% |
| [`src/css_box.c`](modules/src.css_box.c.md) |  | 3 | 28 | 46.9% |
| [`src/css_chain.c`](modules/src.css_chain.c.md) |  | 2 | 12 | 46.7% |
| [`src/css_color.c`](modules/src.css_color.c.md) |  | 1 | 11 | 38.5% |
| [`src/css_gradient.c`](modules/src.css_gradient.c.md) |  | 0 | 15 | 18.8% |
| [`src/css_index.c`](modules/src.css_index.c.md) | css_index -- see include/css_index.h and spec/css_index.md. | 0 | 3 | 75.0% |
| [`src/css_length.c`](modules/src.css_length.c.md) |  | 0 | 11 | 25.0% |
| [`src/css_mask.c`](modules/src.css_mask.c.md) |  | 0 | 6 | 28.6% |
| [`src/css_mq.c`](modules/src.css_mq.c.md) |  | 3 | 7 | 18.2% |
| [`src/css_select.c`](modules/src.css_select.c.md) |  | 0 | 13 | 64.3% |
| [`src/css_text.c`](modules/src.css_text.c.md) | --- text-presentation extensions (Hito 23b-6) --- | 0 | 14 | 73.3% |
| [`src/css_values.c`](modules/src.css_values.c.md) |  | 0 | 8 | 22.2% |
| [`src/css_vars.c`](modules/src.css_vars.c.md) |  | 0 | 8 | 55.6% |
| [`src/data_url.c`](modules/src.data_url.c.md) |  | 0 | 4 | 20.0% |
| [`src/disk_store.c`](modules/src.disk_store.c.md) |  | 0 | 4 | 20.0% |
| [`src/dom.c`](modules/src.dom.c.md) |  | 7 | 41 | 26.5% |
| [`src/dom_debug.c`](modules/src.dom_debug.c.md) |  | 1 | 2 | 75.0% |
| [`src/download.c`](modules/src.download.c.md) |  | 0 | 5 | 16.7% |
| [`src/flex_layout.c`](modules/src.flex_layout.c.md) |  | 0 | 25 | 34.6% |
| [`src/form.c`](modules/src.form.c.md) |  | 0 | 2 | 0.0% |
| [`src/frame_clock.c`](modules/src.frame_clock.c.md) |  | 0 | 4 | 0.0% |
| [`src/freebug.c`](modules/src.freebug.c.md) |  | 0 | 9 | 70.0% |
| [`src/freedom.c`](modules/src.freedom.c.md) |  | 1 | 17 | 15.8% |
| [`src/hls.c`](modules/src.hls.c.md) |  | 0 | 7 | 25.0% |
| [`src/host_conf.c`](modules/src.host_conf.c.md) |  | 0 | 6 | 57.1% |
| [`src/hostblock.c`](modules/src.hostblock.c.md) |  | 2 | 8 | 45.5% |
| [`src/hostedit.c`](modules/src.hostedit.c.md) |  | 1 | 3 | 40.0% |
| [`src/html_parse.c`](modules/src.html_parse.c.md) |  | 1 | 17 | 47.4% |
| [`src/image_decode.c`](modules/src.image_decode.c.md) |  | 3 | 13 | 35.3% |
| [`src/import_map.c`](modules/src.import_map.c.md) |  | 4 | 6 | 45.5% |
| [`src/interp.c`](modules/src.interp.c.md) |  | 0 | 13 | 71.4% |
| [`src/js_custom_elements.c`](modules/src.js_custom_elements.c.md) |  | 0 | 1 | 0.0% |
| [`src/js_custom_elements.h`](modules/src.js_custom_elements.h.md) | Private to js_dom.c: installs Custom Elements v1 (spec/js_custom_elements.md) on top of the document facade. | 0 | 1 | 50.0% |
| [`src/js_dom.c`](modules/src.js_dom.c.md) |  | 1 | 21 | 13.0% |
| [`src/js_dom_ext.c`](modules/src.js_dom_ext.c.md) |  | 0 | 2 | 0.0% |
| [`src/js_dom_ext.h`](modules/src.js_dom_ext.h.md) | Private to js_dom.c / js_dom_ext.c: installs the DOM Standard extras (tree | 0 | 1 | 50.0% |
| [`src/js_dom_internal.h`](modules/src.js_dom_internal.h.md) | Private to the js_dom family (js_dom.c, js_fetch.c, js_events.c, js_embed.c): the context accessors every native needs. | 0 | 3 | 50.0% |
| [`src/js_embed.c`](modules/src.js_embed.c.md) |  | 0 | 4 | 40.0% |
| [`src/js_env.c`](modules/src.js_env.c.md) |  | 0 | 7 | 0.0% |
| [`src/js_events.c`](modules/src.js_events.c.md) |  | 1 | 7 | 22.2% |
| [`src/js_fetch.c`](modules/src.js_fetch.c.md) |  | 0 | 4 | 20.0% |
| [`src/js_geom.c`](modules/src.js_geom.c.md) |  | 0 | 12 | 84.6% |
| [`src/js_location.c`](modules/src.js_location.c.md) |  | 0 | 5 | 50.0% |
| [`src/js_location_internal.h`](modules/src.js_location_internal.h.md) | Private to js_dom.c / js_location.c: the dom.histTarget native lives with the | 0 | 1 | 50.0% |
| [`src/js_policy.c`](modules/src.js_policy.c.md) |  | 0 | 5 | 50.0% |
| [`src/js_sandbox.c`](modules/src.js_sandbox.c.md) |  | 3 | 19 | 43.5% |
| [`src/js_trusted.c`](modules/src.js_trusted.c.md) |  | 1 | 10 | 33.3% |
| [`src/link_nav.c`](modules/src.link_nav.c.md) |  | 0 | 2 | 33.3% |
| [`src/local_store.c`](modules/src.local_store.c.md) |  | 0 | 285 | 1.7% |
| [`src/media_decoder.c`](modules/src.media_decoder.c.md) |  | 2 | 7 | 30.0% |
| [`src/net_realm.c`](modules/src.net_realm.c.md) |  | 0 | 7 | 25.0% |
| [`src/os_sandbox.c`](modules/src.os_sandbox.c.md) |  | 0 | 26 | 33.3% |
| [`src/page_view.c`](modules/src.page_view.c.md) |  | 19 | 111 | 44.3% |
| [`src/pdf_export.c`](modules/src.pdf_export.c.md) |  | 0 | 4 | 20.0% |
| [`src/perf_trace.c`](modules/src.perf_trace.c.md) |  | 0 | 11 | 75.0% |
| [`src/prefetch.c`](modules/src.prefetch.c.md) |  | 1 | 12 | 42.9% |
| [`src/prefs.c`](modules/src.prefs.c.md) |  | 1 | 11 | 30.8% |
| [`src/profile.c`](modules/src.profile.c.md) |  | 0 | 6 | 14.3% |
| [`src/render_doc.c`](modules/src.render_doc.c.md) |  | 0 | 17 | 50.0% |
| [`src/render_policy.c`](modules/src.render_policy.c.md) |  | 0 | 5 | 50.0% |
| [`src/renderer.c`](modules/src.renderer.c.md) |  | 0 | 4 | 20.0% |
| [`src/request_policy.c`](modules/src.request_policy.c.md) |  | 0 | 6 | 57.1% |
| [`src/secure_fetch.c`](modules/src.secure_fetch.c.md) |  | 6 | 41 | 25.0% |
| [`src/svg_render.c`](modules/src.svg_render.c.md) | svg_render — inline <svg> markup -> a bounded list of geometric shapes. | 3 | 5 | 55.6% |
| [`src/tab.c`](modules/src.tab.c.md) |  | 2 | 73 | 36.8% |
| [`src/text_case.c`](modules/src.text_case.c.md) |  | 0 | 5 | 50.0% |
| [`src/text_shape.c`](modules/src.text_shape.c.md) |  | 10 | 23 | 47.1% |
| [`src/textfield.c`](modules/src.textfield.c.md) |  | 0 | 12 | 46.2% |
| [`src/tls_impersonate.c`](modules/src.tls_impersonate.c.md) |  | 2 | 7 | 10.0% |
| [`src/ui_layout.c`](modules/src.ui_layout.c.md) |  | 0 | 3 | 50.0% |
| [`src/url.c`](modules/src.url.c.md) |  | 0 | 16 | 23.5% |
| [`src/web_storage.c`](modules/src.web_storage.c.md) |  | 3 | 8 | 50.0% |
| [`src/webcaps.c`](modules/src.webcaps.c.md) |  | 0 | 4 | 0.0% |
| [`src/webfont.c`](modules/src.webfont.c.md) |  | 0 | 6 | 0.0% |
| [`src/webfont_load.c`](modules/src.webfont_load.c.md) |  | 4 | 4 | 55.6% |
| [`src/wl_display.c`](modules/src.wl_display.c.md) |  | 0 | 7 | 25.0% |
| [`src/ws_hub.c`](modules/src.ws_hub.c.md) |  | 5 | 14 | 70.0% |
| [`src/zoom.c`](modules/src.zoom.c.md) |  | 0 | 7 | 75.0% |

### `tools`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`tools.fbench`](modules/tools.fbench.py.md) | fbench -- turn the PNG pairs `make parity` leaves behind into something you can act on. | 0 | 7 | 25.0% |
| [`tools.ffgeom`](modules/tools.ffgeom.py.md) | ffgeom -- Firefox geometry as TEXT, no image reading. | 0 | 7 | 25.0% |
| [`tools.ffq`](modules/tools.ffq.py.md) | ffq -- ask Firefox what it computed, as TEXT. | 0 | 1 | 50.0% |
| [`tools.ffshot`](modules/tools.ffshot.py.md) | ffshot -- full-page Firefox screenshot at a FIXED viewport, for `make parity`/`make wpt`. | 0 | 1 | 50.0% |
| [`tools/gen_psl.c`](modules/tools.gen_psl.c.md) |  | 1 | 2 | 0.0% |
| [`tools.mutate`](modules/tools.mutate.py.md) | mutate -- compile-time mutation testing for the CMocka suites. | 0 | 6 | 14.3% |
| [`tools/pngdiff.c`](modules/tools.pngdiff.c.md) |  | 3 | 5 | 44.4% |
| [`tools.pngprof`](modules/tools.pngprof.py.md) | pngprof -- structural ink-profile dump for page screenshots. | 0 | 4 | 20.0% |
| [`tools.prune`](modules/tools.prune.py.md) | prune -- cut a corpus page down to ONE subtree, keeping its whole ancestor chain. | 0 | 1 | 50.0% |
| [`tools.snapshot`](modules/tools.snapshot.py.md) | Freeze a live page into one self-contained HTML file for `make parity`. | 0 | 4 | 40.0% |
| [`tools.snapshot_age`](modules/tools.snapshot_age.py.md) | Report parity snapshots older than N days (stamped by tools/snapshot.py). | 0 | 1 | 50.0% |
