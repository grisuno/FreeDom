# freedom-0.0.3 API Reference

> Generated offline by readmenator: 316 modules, 4261 documented entities, documentation coverage 45.0% (1899/4223 public items). Deterministic, zero tokens: signatures from source, docs parsed from Google, NumPy, reST, Javadoc/JSDoc/Doxygen, C# XML, and Rustdoc comments.

Navigate: [Interactive architecture and flows](flows.html) | [Architecture and flows (Mermaid)](architecture.md) | [Class hierarchy](classes.md) | [General index](genindex.md) | [Coverage and warnings](COVERAGE.md) | [`api/index.json`](api/index.json) | [HTML browser](index.html)

Languages: c (174), h (123), py (14), sh (5)

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
| [`fuzz/fuzz_anchor.c`](modules/fuzz.fuzz_anchor.c.md) | Fuzzer for anchor (spec/anchor.md) and url_split_location: a hostile document x a | 0 | 1 | 50.0% |
| [`fuzz/fuzz_box_blur.c`](modules/fuzz.fuzz_box_blur.c.md) | libFuzzer harness for box_blur (spec/box_blur.md): a hostile mask, size, stride and sigma | 0 | 1 | 50.0% |
| [`fuzz/fuzz_box_tree.c`](modules/fuzz.fuzz_box_tree.c.md) | Hostile box trees (any parent graph, cycles included) through the positioned paint | 0 | 3 | 50.0% |
| [`fuzz/fuzz_browser.c`](modules/fuzz.fuzz_browser.c.md) |  | 2 | 3 | 33.3% |
| [`fuzz/fuzz_chrome_layout.c`](modules/fuzz.fuzz_chrome_layout.c.md) | libFuzzer harness for chrome_layout (spec/chrome_layout.md): a hostile URL (a page | 0 | 1 | 50.0% |
| [`fuzz/fuzz_css.c`](modules/fuzz.fuzz_css.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_css_counter.c`](modules/fuzz.fuzz_css_counter.c.md) | libFuzzer harness for css_counter (spec/css_counter.md): hostile `content` and counter | 0 | 1 | 50.0% |
| [`fuzz/fuzz_css_import.c`](modules/fuzz.fuzz_css_import.c.md) | fuzz_css_import -- hostile stylesheet text through the @import prelude reader | 1 | 1 | 33.3% |
| [`fuzz/fuzz_data_url.c`](modules/fuzz.fuzz_data_url.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_doc_title.c`](modules/fuzz.fuzz_doc_title.c.md) | Fuzzer for doc_title (spec/doc_title.md): the title is always valid UTF-8, bounded by | 0 | 1 | 50.0% |
| [`fuzz/fuzz_dom.c`](modules/fuzz.fuzz_dom.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_dom_debug.c`](modules/fuzz.fuzz_dom_debug.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_download.c`](modules/fuzz.fuzz_download.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_exact_key.c`](modules/fuzz.fuzz_exact_key.c.md) | libFuzzer harness for exact_key (spec/exact_key.md). | 0 | 1 | 50.0% |
| [`fuzz/fuzz_fb_cmdline.c`](modules/fuzz.fuzz_fb_cmdline.c.md) |  | 0 | 1 | 50.0% |
| [`fuzz/fuzz_find_text.c`](modules/fuzz.fuzz_find_text.c.md) | libFuzzer harness for find_text (spec/find_text.md). | 0 | 2 | 33.3% |
| [`fuzz/fuzz_frame_broker.c`](modules/fuzz.fuzz_frame_broker.c.md) |  | 0 | 0 | 0.0% |
| [`fuzz/fuzz_freebug.c`](modules/fuzz.fuzz_freebug.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_group_index.c`](modules/fuzz.fuzz_group_index.c.md) | libFuzzer harness for group_index (spec/group_index.md): random keys (including out-of-range ones) and key counts, checked against a naive per-key scan. | 0 | 1 | 50.0% |
| [`fuzz/fuzz_hls.c`](modules/fuzz.fuzz_hls.c.md) | libFuzzer harness for hls (spec/hls.md): hostile playlist text, hostile | 0 | 1 | 50.0% |
| [`fuzz/fuzz_html_parse.c`](modules/fuzz.fuzz_html_parse.c.md) |  | 0 | 0 | 0.0% |
| [`fuzz/fuzz_identity.c`](modules/fuzz.fuzz_identity.c.md) | libFuzzer harness for identity (spec/identity.md) and he_cdn_kind (spec/hostedit.md): | 0 | 1 | 50.0% |
| [`fuzz/fuzz_image_decode.c`](modules/fuzz.fuzz_image_decode.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_import_map.c`](modules/fuzz.fuzz_import_map.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_js_dom.c`](modules/fuzz.fuzz_js_dom.c.md) |  | 0 | 2 | 33.3% |
| [`fuzz/fuzz_js_geom.c`](modules/fuzz.fuzz_js_geom.c.md) |  | 1 | 1 | 0.0% |
| [`fuzz/fuzz_js_sandbox.c`](modules/fuzz.fuzz_js_sandbox.c.md) |  | 1 | 2 | 25.0% |
| [`fuzz/fuzz_link_preview.c`](modules/fuzz.fuzz_link_preview.c.md) | Fuzzer for link_preview (spec/link_preview.md): input = base NUL href. | 0 | 1 | 50.0% |
| [`fuzz/fuzz_mask_cache.c`](modules/fuzz.fuzz_mask_cache.c.md) | libFuzzer harness for mask_cache (spec/mask_cache.md). | 0 | 2 | 33.3% |
| [`fuzz/fuzz_nav_token.c`](modules/fuzz.fuzz_nav_token.c.md) | libFuzzer harness for nav_token (spec/nav_token.md): a byte program of new / ref | 0 | 2 | 33.3% |
| [`fuzz/fuzz_net_guard.c`](modules/fuzz.fuzz_net_guard.c.md) | libFuzzer harness for net_guard (spec/net_guard.md): hostile host and address text. | 0 | 1 | 50.0% |
| [`fuzz/fuzz_page_view.c`](modules/fuzz.fuzz_page_view.c.md) |  | 0 | 0 | 0.0% |
| [`fuzz/fuzz_pdf_export.c`](modules/fuzz.fuzz_pdf_export.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_prefetch.c`](modules/fuzz.fuzz_prefetch.c.md) | libFuzzer harness for the prefetch lookahead scanner (Hito 29). | 0 | 1 | 50.0% |
| [`fuzz/fuzz_prefs.c`](modules/fuzz.fuzz_prefs.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_request_headers.c`](modules/fuzz.fuzz_request_headers.c.md) |  | 0 | 0 | 0.0% |
| [`fuzz/fuzz_scroll_req.c`](modules/fuzz.fuzz_scroll_req.c.md) | fuzz_scroll_req -- spec/scroll_req.md: a hostile wire record either decodes to an | 0 | 1 | 50.0% |
| [`fuzz/fuzz_site_panel.c`](modules/fuzz.fuzz_site_panel.c.md) | libFuzzer harness for site_panel (spec/site_panel.md): a hostile URL and KE-group text | 0 | 1 | 50.0% |
| [`fuzz/fuzz_smooth_scroll.c`](modules/fuzz.fuzz_smooth_scroll.c.md) | libFuzzer harness for smooth_scroll (spec/smooth_scroll.md): drives random sequences of | 0 | 1 | 50.0% |
| [`fuzz/fuzz_svg_render.c`](modules/fuzz.fuzz_svg_render.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_table_layout.c`](modules/fuzz.fuzz_table_layout.c.md) | libFuzzer harness for table_layout and pres_hints (spec/table_layout.md, spec/pres_hints.md). | 1 | 1 | 33.3% |
| [`fuzz/fuzz_text_case.c`](modules/fuzz.fuzz_text_case.c.md) | libFuzzer harness for text_case (spec/text_case.md): case mapping and the | 0 | 1 | 50.0% |
| [`fuzz/fuzz_text_shape.c`](modules/fuzz.fuzz_text_shape.c.md) |  | 0 | 4 | 0.0% |
| [`fuzz/fuzz_tls_impersonate.c`](modules/fuzz.fuzz_tls_impersonate.c.md) |  | 0 | 0 | 0.0% |
| [`fuzz/fuzz_url.c`](modules/fuzz.fuzz_url.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_video_controls.c`](modules/fuzz.fuzz_video_controls.c.md) |  | 0 | 1 | 0.0% |
| [`fuzz/fuzz_web_storage.c`](modules/fuzz.fuzz_web_storage.c.md) |  | 0 | 0 | 0.0% |
| [`fuzz/fuzz_webfont.c`](modules/fuzz.fuzz_webfont.c.md) | libFuzzer harness for the webfont lookahead scanner (spec/webfont.md). | 0 | 1 | 50.0% |
| [`fuzz/fuzz_webfont_register.c`](modules/fuzz.fuzz_webfont_register.c.md) |  | 0 | 2 | 0.0% |

### `gui`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`gui/browser_ui.c`](modules/gui.browser_ui.c.md) |  | 52 | 222 | 31.3% |
| [`gui/browser_ui_internal.h`](modules/gui.browser_ui_internal.h.md) |  | 7 | 18 | 57.7% |
| [`gui/bui_chrome.c`](modules/gui.bui_chrome.c.md) |  | 0 | 35 | 52.8% |
| [`gui/bui_mask_img.c`](modules/gui.bui_mask_img.c.md) | bui_mask_img -- paints a mask-image: url() layer into a mask surface. | 0 | 1 | 50.0% |
| [`gui/bui_theme.c`](modules/gui.bui_theme.c.md) |  | 0 | 6 | 85.7% |
| [`gui/freedom_view.c`](modules/gui.freedom_view.c.md) |  | 0 | 2 | 0.0% |
| [`gui/ui_render.c`](modules/gui.ui_render.c.md) |  | 1 | 6 | 37.5% |

### `include`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`include/anchor.h`](modules/include.anchor.h.md) |  | 1 | 7 | 55.6% |
| [`include/anti_fp.h`](modules/include.anti_fp.h.md) |  | 0 | 34 | 60.0% |
| [`include/block_flow.h`](modules/include.block_flow.h.md) | block_flow (bf_) -- vertical margin collapsing for block-level boxes. | 0 | 3 | 50.0% |
| [`include/box_blur.h`](modules/include.box_blur.h.md) | Gaussian blur of an 8-bit alpha mask by three box passes per axis (spec/box_blur.md). | 0 | 4 | 60.0% |
| [`include/box_style.h`](modules/include.box_style.h.md) |  | 12 | 18 | 64.5% |
| [`include/box_tree.h`](modules/include.box_tree.h.md) |  | 5 | 29 | 40.0% |
| [`include/browser.h`](modules/include.browser.h.md) |  | 3 | 24 | 50.0% |
| [`include/cached_fetch.h`](modules/include.cached_fetch.h.md) |  | 0 | 3 | 50.0% |
| [`include/chrome_layout.h`](modules/include.chrome_layout.h.md) |  | 10 | 28 | 53.8% |
| [`include/compositor.h`](modules/include.compositor.h.md) |  | 5 | 5 | 90.9% |
| [`include/css.h`](modules/include.css.h.md) |  | 72 | 75 | 71.6% |
| [`include/css_atrule.h`](modules/include.css_atrule.h.md) |  | 2 | 7 | 70.0% |
| [`include/css_box.h`](modules/include.css_box.h.md) |  | 0 | 27 | 0.0% |
| [`include/css_chain.h`](modules/include.css_chain.h.md) |  | 3 | 9 | 23.1% |
| [`include/css_color.h`](modules/include.css_color.h.md) |  | 3 | 3 | 42.9% |
| [`include/css_computed.h`](modules/include.css_computed.h.md) |  | 1 | 4 | 33.3% |
| [`include/css_counter.h`](modules/include.css_counter.h.md) |  | 4 | 14 | 36.8% |
| [`include/css_decl.h`](modules/include.css_decl.h.md) |  | 2 | 12 | 13.3% |
| [`include/css_gradient.h`](modules/include.css_gradient.h.md) |  | 4 | 9 | 35.7% |
| [`include/css_import.h`](modules/include.css_import.h.md) |  | 2 | 9 | 66.7% |
| [`include/css_index.h`](modules/include.css_index.h.md) |  | 3 | 4 | 50.0% |
| [`include/css_length.h`](modules/include.css_length.h.md) |  | 5 | 14 | 60.0% |
| [`include/css_mask.h`](modules/include.css_mask.h.md) | CSS Masking 1, alpha gradients only (spec/css_mask.md). | 4 | 5 | 50.0% |
| [`include/css_mq.h`](modules/include.css_mq.h.md) |  | 4 | 7 | 75.0% |
| [`include/css_select.h`](modules/include.css_select.h.md) |  | 10 | 29 | 62.5% |
| [`include/css_text.h`](modules/include.css_text.h.md) |  | 0 | 16 | 0.0% |
| [`include/css_values.h`](modules/include.css_values.h.md) | Single owner of CSS value interpretation for colors and backgrounds. | 0 | 8 | 33.3% |
| [`include/css_vars.h`](modules/include.css_vars.h.md) |  | 4 | 14 | 73.7% |
| [`include/data_url.h`](modules/include.data_url.h.md) |  | 1 | 5 | 28.6% |
| [`include/disk_store.h`](modules/include.disk_store.h.md) |  | 1 | 1 | 33.3% |
| [`include/doc_title.h`](modules/include.doc_title.h.md) | doc_title -- the <title> of a received document that has not been laid out yet | 0 | 2 | 100.0% |
| [`include/dom.h`](modules/include.dom.h.md) |  | 4 | 28 | 57.6% |
| [`include/dom_debug.h`](modules/include.dom_debug.h.md) |  | 0 | 3 | 75.0% |
| [`include/download.h`](modules/include.download.h.md) |  | 1 | 7 | 11.1% |
| [`include/exact_key.h`](modules/include.exact_key.h.md) | exact_key (ek_) -- a cache key built by OBSERVING every input of what is cached, compared | 1 | 7 | 88.9% |
| [`include/fb_cmdline.h`](modules/include.fb_cmdline.h.md) |  | 2 | 15 | 61.1% |
| [`include/fb_panes.h`](modules/include.fb_panes.h.md) |  | 1 | 10 | 75.0% |
| [`include/find_text.h`](modules/include.find_text.h.md) |  | 8 | 9 | 44.4% |
| [`include/flex_layout.h`](modules/include.flex_layout.h.md) |  | 10 | 34 | 55.6% |
| [`include/form.h`](modules/include.form.h.md) |  | 7 | 3 | 27.3% |
| [`include/frame_broker.h`](modules/include.frame_broker.h.md) |  | 6 | 10 | 29.4% |
| [`include/frame_clock.h`](modules/include.frame_clock.h.md) |  | 2 | 4 | 14.3% |
| [`include/frame_host.h`](modules/include.frame_host.h.md) |  | 1 | 11 | 76.9% |
| [`include/freebug.h`](modules/include.freebug.h.md) |  | 4 | 13 | 72.2% |
| [`include/freedom_config.h`](modules/include.freedom_config.h.md) |  | 0 | 26 | 85.2% |
| [`include/group_index.h`](modules/include.group_index.h.md) |  | 0 | 2 | 33.3% |
| [`include/hls.h`](modules/include.hls.h.md) |  | 4 | 6 | 54.5% |
| [`include/host_conf.h`](modules/include.host_conf.h.md) |  | 1 | 7 | 55.6% |
| [`include/hostblock.h`](modules/include.hostblock.h.md) |  | 4 | 5 | 50.0% |
| [`include/hostedit.h`](modules/include.hostedit.h.md) |  | 2 | 4 | 57.1% |
| [`include/html_parse.h`](modules/include.html_parse.h.md) |  | 5 | 18 | 50.0% |
| [`include/http_cache.h`](modules/include.http_cache.h.md) |  | 5 | 13 | 21.1% |
| [`include/identity.h`](modules/include.identity.h.md) |  | 3 | 20 | 45.8% |
| [`include/image_decode.h`](modules/include.image_decode.h.md) |  | 4 | 9 | 42.9% |
| [`include/import_map.h`](modules/include.import_map.h.md) |  | 1 | 8 | 30.0% |
| [`include/interp.h`](modules/include.interp.h.md) |  | 10 | 11 | 31.8% |
| [`include/js_dom.h`](modules/include.js_dom.h.md) |  | 5 | 17 | 34.8% |
| [`include/js_env.h`](modules/include.js_env.h.md) |  | 1 | 2 | 25.0% |
| [`include/js_geom.h`](modules/include.js_geom.h.md) |  | 3 | 15 | 78.9% |
| [`include/js_intl.h`](modules/include.js_intl.h.md) |  | 0 | 1 | 50.0% |
| [`include/js_location.h`](modules/include.js_location.h.md) |  | 0 | 8 | 44.4% |
| [`include/js_native.h`](modules/include.js_native.h.md) |  | 0 | 1 | 0.0% |
| [`include/js_policy.h`](modules/include.js_policy.h.md) |  | 1 | 5 | 42.9% |
| [`include/js_sandbox.h`](modules/include.js_sandbox.h.md) |  | 6 | 30 | 54.1% |
| [`include/js_trusted.h`](modules/include.js_trusted.h.md) |  | 4 | 11 | 37.5% |
| [`include/lazy_load.h`](modules/include.lazy_load.h.md) |  | 0 | 0 | 0.0% |
| [`include/link_nav.h`](modules/include.link_nav.h.md) |  | 6 | 4 | 36.4% |
| [`include/link_preview.h`](modules/include.link_preview.h.md) |  | 4 | 1 | 16.7% |
| [`include/local_store.h`](modules/include.local_store.h.md) |  | 2 | 8 | 18.2% |
| [`include/mask_cache.h`](modules/include.mask_cache.h.md) | mask_cache (mkc_) -- 8-bit alpha masks retained across frames (spec/mask_cache.md). | 3 | 7 | 81.8% |
| [`include/media_decoder.h`](modules/include.media_decoder.h.md) |  | 4 | 7 | 75.0% |
| [`include/nav_token.h`](modules/include.nav_token.h.md) |  | 2 | 8 | 9.1% |
| [`include/net_guard.h`](modules/include.net_guard.h.md) |  | 2 | 6 | 55.6% |
| [`include/net_realm.h`](modules/include.net_realm.h.md) |  | 4 | 5 | 20.0% |
| [`include/os_sandbox.h`](modules/include.os_sandbox.h.md) |  | 4 | 7 | 50.0% |
| [`include/page_view.h`](modules/include.page_view.h.md) |  | 17 | 85 | 62.1% |
| [`include/pdf_export.h`](modules/include.pdf_export.h.md) |  | 1 | 8 | 30.0% |
| [`include/perf_trace.h`](modules/include.perf_trace.h.md) |  | 5 | 11 | 52.9% |
| [`include/pq_seal.h`](modules/include.pq_seal.h.md) |  | 2 | 5 | 12.5% |
| [`include/prefetch.h`](modules/include.prefetch.h.md) |  | 11 | 16 | 53.6% |
| [`include/prefs.h`](modules/include.prefs.h.md) |  | 4 | 13 | 38.9% |
| [`include/pres_hints.h`](modules/include.pres_hints.h.md) | pres_hints (ph_) -- HTML presentational attributes as zero-specificity style. | 0 | 9 | 80.0% |
| [`include/profile.h`](modules/include.profile.h.md) |  | 3 | 5 | 22.2% |
| [`include/psl_data.h`](modules/include.psl_data.h.md) |  | 0 | 0 | 0.0% |
| [`include/render_doc.h`](modules/include.render_doc.h.md) |  | 6 | 20 | 48.1% |
| [`include/render_policy.h`](modules/include.render_policy.h.md) |  | 3 | 5 | 77.8% |
| [`include/renderer.h`](modules/include.renderer.h.md) |  | 3 | 3 | 14.3% |
| [`include/request_policy.h`](modules/include.request_policy.h.md) |  | 1 | 9 | 54.5% |
| [`include/scroll_req.h`](modules/include.scroll_req.h.md) |  | 7 | 6 | 35.7% |
| [`include/secure_fetch.h`](modules/include.secure_fetch.h.md) |  | 9 | 38 | 52.1% |
| [`include/sha2.h`](modules/include.sha2.h.md) |  | 1 | 4 | 50.0% |
| [`include/sheet_cache.h`](modules/include.sheet_cache.h.md) |  | 5 | 6 | 66.7% |
| [`include/shm_slots.h`](modules/include.shm_slots.h.md) |  | 2 | 4 | 42.9% |
| [`include/smooth_scroll.h`](modules/include.smooth_scroll.h.md) |  | 2 | 6 | 11.1% |
| [`include/subreq_batch.h`](modules/include.subreq_batch.h.md) |  | 4 | 12 | 64.7% |
| [`include/svg_paint.h`](modules/include.svg_paint.h.md) |  | 0 | 2 | 33.3% |
| [`include/svg_raster.h`](modules/include.svg_raster.h.md) |  | 0 | 4 | 60.0% |
| [`include/svg_render.h`](modules/include.svg_render.h.md) |  | 9 | 8 | 38.9% |
| [`include/tab.h`](modules/include.tab.h.md) |  | 14 | 47 | 50.0% |
| [`include/table_layout.h`](modules/include.table_layout.h.md) | table_layout (tl_) -- used column widths of a table (automatic table layout). | 2 | 5 | 75.0% |
| [`include/text_case.h`](modules/include.text_case.h.md) | Case mapping for text-transform and synthesized small caps (spec/text_case.md). | 1 | 6 | 75.0% |
| [`include/text_shape.h`](modules/include.text_shape.h.md) |  | 5 | 19 | 72.0% |
| [`include/textfield.h`](modules/include.textfield.h.md) |  | 3 | 11 | 53.3% |
| [`include/tls_impersonate.h`](modules/include.tls_impersonate.h.md) |  | 4 | 18 | 30.4% |
| [`include/ui.h`](modules/include.ui.h.md) |  | 8 | 11 | 35.0% |
| [`include/url.h`](modules/include.url.h.md) |  | 3 | 11 | 46.7% |
| [`include/util.h`](modules/include.util.h.md) | util.h — shared pure helpers (no I/O except where noted). | 0 | 5 | 33.3% |
| [`include/video_controls.h`](modules/include.video_controls.h.md) |  | 5 | 14 | 55.0% |
| [`include/video_pick.h`](modules/include.video_pick.h.md) | Which video a click plays (spec/video_pick.md). | 0 | 3 | 100.0% |
| [`include/web_storage.h`](modules/include.web_storage.h.md) |  | 1 | 11 | 61.5% |
| [`include/webcaps.h`](modules/include.webcaps.h.md) |  | 4 | 0 | 80.0% |
| [`include/webfont.h`](modules/include.webfont.h.md) |  | 3 | 13 | 17.6% |
| [`include/webfont_load.h`](modules/include.webfont_load.h.md) |  | 1 | 5 | 14.3% |
| [`include/wl_display.h`](modules/include.wl_display.h.md) |  | 0 | 5 | 33.3% |
| [`include/wl_guard.h`](modules/include.wl_guard.h.md) |  | 2 | 2 | 60.0% |
| [`include/ws_hub.h`](modules/include.ws_hub.h.md) |  | 1 | 13 | 73.3% |
| [`include/zoom.h`](modules/include.zoom.h.md) |  | 0 | 9 | 60.0% |

### `src`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`src/anchor.c`](modules/src.anchor.c.md) | anchor.c — the indicated part of a document and where it sits (spec/anchor.md). | 0 | 6 | 71.4% |
| [`src/anti_fp.c`](modules/src.anti_fp.c.md) |  | 0 | 22 | 73.9% |
| [`src/block_flow.c`](modules/src.block_flow.c.md) | block_flow (bf_) -- vertical margin collapsing. | 0 | 3 | 50.0% |
| [`src/box_blur.c`](modules/src.box_blur.c.md) |  | 0 | 5 | 33.3% |
| [`src/box_style.c`](modules/src.box_style.c.md) |  | 2 | 42 | 31.1% |
| [`src/box_tree.c`](modules/src.box_tree.c.md) |  | 2 | 17 | 45.0% |
| [`src/browser.c`](modules/src.browser.c.md) |  | 0 | 37 | 28.9% |
| [`src/cached_fetch.c`](modules/src.cached_fetch.c.md) |  | 0 | 6 | 28.6% |
| [`src/chrome_layout.c`](modules/src.chrome_layout.c.md) | chrome_layout -- browser chrome geometry + identity badge. spec/chrome_layout.md | 0 | 17 | 72.2% |
| [`src/compositor.c`](modules/src.compositor.c.md) |  | 0 | 6 | 71.4% |
| [`src/css.c`](modules/src.css.c.md) |  | 9 | 78 | 27.3% |
| [`src/css_atrule.c`](modules/src.css_atrule.c.md) |  | 0 | 4 | 80.0% |
| [`src/css_box.c`](modules/src.css_box.c.md) |  | 3 | 30 | 44.1% |
| [`src/css_chain.c`](modules/src.css_chain.c.md) |  | 3 | 17 | 38.1% |
| [`src/css_color.c`](modules/src.css_color.c.md) |  | 4 | 12 | 41.2% |
| [`src/css_computed.c`](modules/src.css_computed.c.md) |  | 1 | 5 | 28.6% |
| [`src/css_counter.c`](modules/src.css_counter.c.md) |  | 3 | 16 | 30.0% |
| [`src/css_gradient.c`](modules/src.css_gradient.c.md) |  | 0 | 17 | 22.2% |
| [`src/css_import.c`](modules/src.css_import.c.md) | css_import -- @import prelude reader (spec/css_import.md). | 0 | 4 | 80.0% |
| [`src/css_index.c`](modules/src.css_index.c.md) | css_index -- see include/css_index.h and spec/css_index.md. | 1 | 4 | 100.0% |
| [`src/css_length.c`](modules/src.css_length.c.md) |  | 0 | 11 | 25.0% |
| [`src/css_mask.c`](modules/src.css_mask.c.md) |  | 0 | 6 | 42.9% |
| [`src/css_mq.c`](modules/src.css_mq.c.md) |  | 3 | 11 | 33.3% |
| [`src/css_select.c`](modules/src.css_select.c.md) |  | 0 | 19 | 65.0% |
| [`src/css_text.c`](modules/src.css_text.c.md) | --- text-presentation extensions (Hito 23b-6) --- | 0 | 13 | 71.4% |
| [`src/css_values.c`](modules/src.css_values.c.md) |  | 0 | 8 | 22.2% |
| [`src/css_vars.c`](modules/src.css_vars.c.md) |  | 0 | 8 | 55.6% |
| [`src/data_url.c`](modules/src.data_url.c.md) |  | 0 | 5 | 16.7% |
| [`src/disk_store.c`](modules/src.disk_store.c.md) |  | 0 | 4 | 20.0% |
| [`src/doc_title.c`](modules/src.doc_title.c.md) | doc_title -- the <title> of a received document that has not been laid out yet. | 1 | 4 | 33.3% |
| [`src/dom.c`](modules/src.dom.c.md) |  | 7 | 46 | 25.9% |
| [`src/dom_debug.c`](modules/src.dom_debug.c.md) |  | 1 | 2 | 75.0% |
| [`src/download.c`](modules/src.download.c.md) |  | 0 | 5 | 16.7% |
| [`src/exact_key.c`](modules/src.exact_key.c.md) |  | 0 | 6 | 85.7% |
| [`src/fb_cmdline.c`](modules/src.fb_cmdline.c.md) |  | 0 | 11 | 66.7% |
| [`src/fb_panes.c`](modules/src.fb_panes.c.md) |  | 0 | 8 | 88.9% |
| [`src/find_text.c`](modules/src.find_text.c.md) | find_text (ft_) -- find in page over the rendered text. spec/find_text.md. | 0 | 6 | 71.4% |
| [`src/flex_layout.c`](modules/src.flex_layout.c.md) |  | 0 | 26 | 37.0% |
| [`src/form.c`](modules/src.form.c.md) |  | 0 | 2 | 0.0% |
| [`src/frame_broker.c`](modules/src.frame_broker.c.md) |  | 0 | 6 | 71.4% |
| [`src/frame_clock.c`](modules/src.frame_clock.c.md) |  | 0 | 4 | 0.0% |
| [`src/frame_host.c`](modules/src.frame_host.c.md) |  | 4 | 9 | 71.4% |
| [`src/freebug.c`](modules/src.freebug.c.md) |  | 0 | 9 | 70.0% |
| [`src/freedom.c`](modules/src.freedom.c.md) |  | 2 | 17 | 20.0% |
| [`src/group_index.c`](modules/src.group_index.c.md) | group_index (gi_) -- spec/group_index.md. | 0 | 1 | 100.0% |
| [`src/hls.c`](modules/src.hls.c.md) |  | 0 | 13 | 14.3% |
| [`src/host_conf.c`](modules/src.host_conf.c.md) |  | 0 | 6 | 57.1% |
| [`src/hostblock.c`](modules/src.hostblock.c.md) |  | 2 | 9 | 41.7% |
| [`src/hostedit.c`](modules/src.hostedit.c.md) |  | 1 | 4 | 33.3% |
| [`src/html_parse.c`](modules/src.html_parse.c.md) |  | 1 | 17 | 47.4% |
| [`src/http_cache.c`](modules/src.http_cache.c.md) |  | 2 | 18 | 14.3% |
| [`src/identity.c`](modules/src.identity.c.md) |  | 0 | 15 | 50.0% |
| [`src/image_decode.c`](modules/src.image_decode.c.md) |  | 3 | 13 | 35.3% |
| [`src/import_map.c`](modules/src.import_map.c.md) |  | 4 | 6 | 45.5% |
| [`src/interp.c`](modules/src.interp.c.md) |  | 0 | 13 | 71.4% |
| [`src/js_custom_elements.c`](modules/src.js_custom_elements.c.md) |  | 0 | 1 | 0.0% |
| [`src/js_custom_elements.h`](modules/src.js_custom_elements.h.md) | Private to js_dom.c: installs Custom Elements v1 (spec/js_custom_elements.md) on top of the document facade. | 0 | 1 | 50.0% |
| [`src/js_dom.c`](modules/src.js_dom.c.md) |  | 1 | 25 | 11.1% |
| [`src/js_dom_ext.c`](modules/src.js_dom_ext.c.md) |  | 0 | 9 | 0.0% |
| [`src/js_dom_ext.h`](modules/src.js_dom_ext.h.md) | Private to js_dom.c / js_dom_ext.c: installs the DOM Standard extras (tree | 0 | 1 | 50.0% |
| [`src/js_dom_internal.h`](modules/src.js_dom_internal.h.md) | Private to the js_dom family (js_dom.c, js_fetch.c, js_events.c, js_embed.c): the context accessors every native needs. | 0 | 3 | 50.0% |
| [`src/js_embed.c`](modules/src.js_embed.c.md) |  | 0 | 4 | 40.0% |
| [`src/js_env.c`](modules/src.js_env.c.md) |  | 0 | 7 | 0.0% |
| [`src/js_events.c`](modules/src.js_events.c.md) |  | 1 | 7 | 22.2% |
| [`src/js_fetch.c`](modules/src.js_fetch.c.md) |  | 0 | 6 | 14.3% |
| [`src/js_geom.c`](modules/src.js_geom.c.md) |  | 0 | 12 | 84.6% |
| [`src/js_intl.c`](modules/src.js_intl.c.md) |  | 0 | 1 | 50.0% |
| [`src/js_location.c`](modules/src.js_location.c.md) |  | 0 | 8 | 33.3% |
| [`src/js_location_internal.h`](modules/src.js_location_internal.h.md) | Private to js_dom.c / js_location.c: the dom.histTarget native lives with the | 0 | 1 | 50.0% |
| [`src/js_native.c`](modules/src.js_native.c.md) |  | 0 | 3 | 25.0% |
| [`src/js_native_internal.h`](modules/src.js_native_internal.h.md) |  | 1 | 1 | 33.3% |
| [`src/js_policy.c`](modules/src.js_policy.c.md) |  | 0 | 5 | 50.0% |
| [`src/js_sandbox.c`](modules/src.js_sandbox.c.md) |  | 3 | 30 | 41.2% |
| [`src/js_trusted.c`](modules/src.js_trusted.c.md) |  | 1 | 14 | 31.2% |
| [`src/link_nav.c`](modules/src.link_nav.c.md) |  | 0 | 2 | 33.3% |
| [`src/link_preview.c`](modules/src.link_preview.c.md) | link_preview -- the status-strip description of a hovered link (spec/link_preview.md). | 1 | 1 | 66.7% |
| [`src/local_store.c`](modules/src.local_store.c.md) |  | 0 | 25 | 19.2% |
| [`src/mask_cache.c`](modules/src.mask_cache.c.md) |  | 3 | 7 | 72.7% |
| [`src/media_decoder.c`](modules/src.media_decoder.c.md) |  | 2 | 7 | 30.0% |
| [`src/nav_token.c`](modules/src.nav_token.c.md) | nav_token -- per-tab navigation identity shared with fetch threads. spec/nav_token.md | 1 | 9 | 9.1% |
| [`src/net_guard.c`](modules/src.net_guard.c.md) | net_guard -- see include/net_guard.h and spec/net_guard.md. | 0 | 9 | 50.0% |
| [`src/net_realm.c`](modules/src.net_realm.c.md) |  | 0 | 7 | 25.0% |
| [`src/os_sandbox.c`](modules/src.os_sandbox.c.md) |  | 0 | 26 | 33.3% |
| [`src/page_view.c`](modules/src.page_view.c.md) |  | 22 | 125 | 43.9% |
| [`src/pdf_export.c`](modules/src.pdf_export.c.md) |  | 0 | 4 | 20.0% |
| [`src/perf_trace.c`](modules/src.perf_trace.c.md) |  | 0 | 11 | 75.0% |
| [`src/pq_seal.c`](modules/src.pq_seal.c.md) |  | 1 | 8 | 10.0% |
| [`src/prefetch.c`](modules/src.prefetch.c.md) |  | 1 | 12 | 42.9% |
| [`src/prefs.c`](modules/src.prefs.c.md) |  | 1 | 11 | 30.8% |
| [`src/pres_hints.c`](modules/src.pres_hints.c.md) | pres_hints (ph_) -- see include/pres_hints.h and spec/pres_hints.md. | 0 | 6 | 85.7% |
| [`src/profile.c`](modules/src.profile.c.md) |  | 0 | 6 | 14.3% |
| [`src/render_doc.c`](modules/src.render_doc.c.md) |  | 0 | 18 | 47.4% |
| [`src/render_policy.c`](modules/src.render_policy.c.md) |  | 0 | 5 | 50.0% |
| [`src/renderer.c`](modules/src.renderer.c.md) |  | 0 | 4 | 20.0% |
| [`src/request_policy.c`](modules/src.request_policy.c.md) |  | 0 | 7 | 62.5% |
| [`src/scroll_req.c`](modules/src.scroll_req.c.md) |  | 0 | 4 | 80.0% |
| [`src/secure_fetch.c`](modules/src.secure_fetch.c.md) |  | 6 | 45 | 28.8% |
| [`src/sha2.c`](modules/src.sha2.c.md) |  | 0 | 6 | 42.9% |
| [`src/sheet_cache.c`](modules/src.sheet_cache.c.md) | sheet_cache -- see include/sheet_cache.h and spec/sheet_cache.md. | 4 | 6 | 81.8% |
| [`src/smooth_scroll.c`](modules/src.smooth_scroll.c.md) | smooth_scroll (sms_) -- spec/smooth_scroll.md. | 0 | 6 | 14.3% |
| [`src/subreq_batch.c`](modules/src.subreq_batch.c.md) |  | 2 | 12 | 66.7% |
| [`src/svg_paint.c`](modules/src.svg_paint.c.md) | svg_paint — Cairo back end for the shapes svg_render extracted. | 0 | 2 | 66.7% |
| [`src/svg_raster.c`](modules/src.svg_raster.c.md) | svg_raster -- SVG served as an image, rasterized inside the confined worker. spec/svg_raster.md. | 0 | 2 | 66.7% |
| [`src/svg_render.c`](modules/src.svg_render.c.md) | svg_render — inline <svg> markup -> a bounded list of geometric shapes. | 3 | 5 | 55.6% |
| [`src/tab.c`](modules/src.tab.c.md) |  | 10 | 104 | 43.5% |
| [`src/table_layout.c`](modules/src.table_layout.c.md) | table_layout (tl_) -- see include/table_layout.h and spec/table_layout.md. | 0 | 2 | 66.7% |
| [`src/text_case.c`](modules/src.text_case.c.md) |  | 0 | 5 | 50.0% |
| [`src/text_shape.c`](modules/src.text_shape.c.md) |  | 12 | 32 | 48.9% |
| [`src/textfield.c`](modules/src.textfield.c.md) |  | 0 | 12 | 46.2% |
| [`src/tls_impersonate.c`](modules/src.tls_impersonate.c.md) |  | 2 | 7 | 10.0% |
| [`src/ui_layout.c`](modules/src.ui_layout.c.md) |  | 0 | 3 | 50.0% |
| [`src/url.c`](modules/src.url.c.md) |  | 0 | 17 | 22.2% |
| [`src/video_controls.c`](modules/src.video_controls.c.md) |  | 0 | 9 | 70.0% |
| [`src/video_pick.c`](modules/src.video_pick.c.md) | Only an absolute http(s) URL names a stream the decoder can fetch; anything else a script stored in src ("[object Object]", blob:, javascript:) is not a video. | 0 | 2 | 100.0% |
| [`src/web_storage.c`](modules/src.web_storage.c.md) |  | 3 | 8 | 50.0% |
| [`src/webcaps.c`](modules/src.webcaps.c.md) |  | 0 | 4 | 0.0% |
| [`src/webfont.c`](modules/src.webfont.c.md) |  | 0 | 6 | 0.0% |
| [`src/webfont_load.c`](modules/src.webfont_load.c.md) |  | 4 | 4 | 55.6% |
| [`src/wl_display.c`](modules/src.wl_display.c.md) |  | 0 | 7 | 25.0% |
| [`src/wl_guard.c`](modules/src.wl_guard.c.md) |  | 1 | 4 | 33.3% |
| [`src/ws_hub.c`](modules/src.ws_hub.c.md) |  | 5 | 14 | 70.0% |
| [`src/zoom.c`](modules/src.zoom.c.md) |  | 0 | 7 | 75.0% |

### `tools`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`tools.fbench`](modules/tools.fbench.py.md) | fbench -- turn the PNG pairs `make parity` leaves behind into something you can act on. | 0 | 11 | 33.3% |
| [`tools.ffgeom`](modules/tools.ffgeom.py.md) | ffgeom -- Firefox geometry as TEXT, no image reading. | 0 | 7 | 25.0% |
| [`tools.ffq`](modules/tools.ffq.py.md) | ffq -- ask Firefox what it computed, as TEXT. | 0 | 1 | 50.0% |
| [`tools.ffshot`](modules/tools.ffshot.py.md) | ffshot -- full-page Firefox screenshot at a FIXED viewport, for `make parity`/`make wpt`. | 0 | 1 | 50.0% |
| [`tools.fftime`](modules/tools.fftime.py.md) | fftime -- Firefox's time from "navigate" to "painted and idle", for `make fbench`. | 0 | 1 | 50.0% |
| [`tools/gen_psl.c`](modules/tools.gen_psl.c.md) |  | 1 | 2 | 0.0% |
| [`tools.guiscroll`](modules/tools.guiscroll.py.md) | guiscroll -- what one frame costs in the REAL Freedom window while the user scrolls. | 0 | 4 | 40.0% |
| [`tools.guishot`](modules/tools.guishot.py.md) | guishot -- a picture of the REAL Freedom window for the README. | 0 | 2 | 33.3% |
| [`tools.guitime`](modules/tools.guitime.py.md) | guitime -- how long the REAL Freedom window takes from "navigate" to "painted and idle". | 0 | 3 | 50.0% |
| [`tools.mutate`](modules/tools.mutate.py.md) | mutate -- compile-time mutation testing for the CMocka suites. | 0 | 6 | 14.3% |
| [`tools/pngdiff.c`](modules/tools.pngdiff.c.md) |  | 3 | 5 | 44.4% |
| [`tools.pngprof`](modules/tools.pngprof.py.md) | pngprof -- structural ink-profile dump for page screenshots. | 0 | 4 | 20.0% |
| [`tools.prune`](modules/tools.prune.py.md) | prune -- cut a corpus page down to ONE subtree, keeping its whole ancestor chain. | 0 | 1 | 50.0% |
| [`tools.snapshot`](modules/tools.snapshot.py.md) | Freeze a live page into one self-contained HTML file for `make parity`. | 0 | 4 | 40.0% |
| [`tools.snapshot_age`](modules/tools.snapshot_age.py.md) | Report parity snapshots older than N days (stamped by tools/snapshot.py). | 0 | 1 | 50.0% |
