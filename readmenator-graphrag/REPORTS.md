# GraphRAG Community Reports

Entities: 9654 | Relationships: 17416 | Communities: 15 | Themes: 4 | Text units: 9107

Query with `readmenator . ask "<question>"` (local: BM25 + Personalized PageRank; global: map-reduce over these reports) or the MCP tool `readmenator.graphrag`.

## Project overview (`root`, root, rating 7.0)

427 files in 15 communities and 4 themes. Highest-impact communities: include: css (7.0), src: tab (6.5), include: browser_ui (4.7). God nodes: gui/browser_ui.c, include/css.h, src/tab.c, src/page_view.c, src/freedom.c.

- [include: css] rating 7.0: `include/css.h` ranks 1 by PageRank, 42 importers, 148 symbols: css_style: A resolved presentation.
- [src: tab] rating 6.5: `include/html_parse.h` ranks 1 by PageRank, 26 importers, 24 symbols: hp_script: One executable <script>.
- [include: browser_ui] rating 4.7: `include/scroll_req.h` ranks 1 by PageRank, 6 importers, 14 symbols: srq_encode: Writes r as SRQ_WIRE_N int32: kind, behavior, block, y, margin_top, margin_bottom, n, nsub.
- [src: text_shape] rating 3.9: `include/hls.h` ranks 1 by PageRank, 6 importers, 11 symbols: hls_segment: or variant info.
- [include: page_view] rating 2.4: `include/page_view.h` ranks 1 by PageRank, 16 importers, 103 symbols: pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for...
- [include: http_cache] rating 2.3: `include/local_store.h` ranks 1 by PageRank, 8 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [include: secure_fetch] rating 2.0: `include/anti_fp.h` ranks 1 by PageRank, 8 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- [include: bui_chrome] rating 1.4: `include/video_controls.h` ranks 1 by PageRank, 5 importers, 23 symbols: vcl_layout: Lays out the bar inside the video rect (x,y,w,h).
- Key entities: file:tests/test_css.c, file:src/css.c, file:tests/test_js_dom.c, file:src/tab.c, file:gui/browser_ui.c, file:include/tab.h
- Children: t0, t1, t2, t3
- Root rating = highest community rating.

## include: css + include: browser_ui +5 (`t0`, theme, rating 7.0)

Theme of 7 communities and 206 files: include: css (58 files, rating 7.0); include: browser_ui (69 files, rating 4.7); include: page_view (30 files, rating 2.4); include: bui_chrome (20 files, rating 1.4); include: svg_render (14 files, rating 1.1); include: download (8 files, rating 0.6); include: pres_hints (7 files, rating 0.5).

- [include: css] `include/css.h` ranks 1 by PageRank, 42 importers, 148 symbols: css_style: A resolved presentation.
- [include: css] `include/css_color.h` ranks 2 by PageRank, 14 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- [include: browser_ui] `include/scroll_req.h` ranks 1 by PageRank, 6 importers, 14 symbols: srq_encode: Writes r as SRQ_WIRE_N int32: kind, behavior, block, y, margin_top, margin_bottom, n, nsub.
- [include: browser_ui] `include/frame_broker.h` ranks 2 by PageRank, 4 importers, 17 symbols: fbk_origin_of: Serialized origin ("https://host[:port]", lowercase) or "null" for opaque/non-https/unparseable. * 0 on success, -1 if out does not fit or args are NULL.
- [include: page_view] `include/page_view.h` ranks 1 by PageRank, 16 importers, 103 symbols: pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for...
- [include: page_view] `include/render_policy.h` ranks 2 by PageRank, 9 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- [include: bui_chrome] `include/video_controls.h` ranks 1 by PageRank, 5 importers, 23 symbols: vcl_layout: Lays out the bar inside the video rect (x,y,w,h).
- [include: bui_chrome] `include/chrome_layout.h` ranks 2 by PageRank, 4 importers, 44 symbols: chl_tab_rect: Computes the layout. tab_count >= 1 and 0 <= active < tab_count, else CHL_EINVAL * (out untouched).
- Key entities: file:tests/test_css.c, file:src/css.c, file:gui/browser_ui.c, file:include/tab.h, file:src/page_view.c, file:tests/test_page_view.c, file:gui/bui_chrome.c, file:include/chrome_layout.h
- Children: c2, c1, c4, c7, c8, c10, c12
- Theme rating = highest child community rating.

## src: tab + src: text_shape +4 (`t1`, theme, rating 6.5)

Theme of 6 communities and 198 files: src: tab (72 files, rating 6.5); src: text_shape (55 files, rating 3.9); include: http_cache (28 files, rating 2.3); include: secure_fetch (24 files, rating 2.0); include: fb_cmdline (11 files, rating 0.8); include: prefetch (8 files, rating 0.5).

- [src: tab] `include/html_parse.h` ranks 1 by PageRank, 26 importers, 24 symbols: hp_script: One executable <script>.
- [src: tab] `include/dom.h` ranks 2 by PageRank, 23 importers, 33 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- [src: text_shape] `include/hls.h` ranks 1 by PageRank, 6 importers, 11 symbols: hls_segment: or variant info.
- [src: text_shape] `include/webfont.h` ranks 2 by PageRank, 13 importers, 17 symbols: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- [include: http_cache] `include/local_store.h` ranks 1 by PageRank, 8 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [include: http_cache] `include/prefs.h` ranks 2 by PageRank, 7 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- [include: secure_fetch] `include/anti_fp.h` ranks 1 by PageRank, 8 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- [include: secure_fetch] `include/secure_fetch.h` ranks 2 by PageRank, 8 importers, 48 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:src/text_shape.c, file:src/freedom.c, file:src/http_cache.c, file:gui/ui_render.c, file:src/secure_fetch.c, file:tests/test_secure_fetch.c
- Children: c0, c3, c5, c6, c9, c11
- Theme rating = highest child community rating.

## unassigned files (`t2`, theme, rating 0.8)

Theme of 1 communities and 20 files: unassigned files (20 files, rating 0.8).

- [unassigned files] `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- [unassigned files] `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- Key entities: file:tools/pngdiff.c, file:tests/test_site_panel.c
- Children: c14
- Theme rating = highest child community rating.

## tools (`t3`, theme, rating 0.2)

Theme of 1 communities and 3 files: tools (3 files, rating 0.2).

- [tools] `tools/guitime.py` ranks 1 by PageRank, 2 importers, 3 symbols: guitime -- how long the REAL Freedom window takes from "navigate" to "painted and idle".
- [tools] `tools/guiscroll.py` ranks 2 by PageRank, 0 importers, 4 symbols: guiscroll -- what one frame costs in the REAL Freedom window while the user scrolls.  guitime measures "navigate -> painted and idle"; this measures the frames AFTER that: the page is loaded in a nested weston (Xvfb + weston, pixman...
- Key entities: file:tools/guitime.py, file:tools/guishot.py
- Children: c13
- Theme rating = highest child community rating.

## include: css (`c2`, community, rating 7.0)

58 files under include (c 39, h 19), mostly utility. Core file include/css.h (PageRank 0.0444, imported by 42 files): css_style: A resolved presentation. Key abstractions: css_status, css_align, css_display, css_justify, css_font_family, css_text_transform. Depends on include: page_view (3), src: tab (2), src: text_shape (2). Used by include: page_view (19), src: tab (7), include: browser_ui (7).

- `include/css.h` ranks 1 by PageRank, 42 importers, 148 symbols: css_style: A resolved presentation.
- `include/css_color.h` ranks 2 by PageRank, 14 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- `include/css_counter.h` ranks 3 by PageRank, 4 importers, 19 symbols: cnt_hash: FNV-1a over `len` bytes of an identifier, ASCII case preserved (identifiers are * case-sensitive).
- Hotspot `src/css.c`: 276 symbols, 40 connections (score 0.28).
- Hotspot `tests/test_css.c`: 374 symbols, 19 connections (score 0.26).
- 1 layer violations, e.g. test_css.c (testing) -> flex_layout.h (presentation).
- Key entities: file:tests/test_css.c, file:src/css.c, file:include/css.h, file:src/css_box.c, file:include/css_select.h, file:src/css_computed.c, file:src/css_select.c, file:src/css_mq.c
- Rating 7.0/10 = 7 x PageRank share 1.00 + 3 x risk 0.00. Internal imports: 111.

## src: tab (`c0`, community, rating 6.5)

72 files under src (c 48, h 24), mostly utility. Core file include/html_parse.h (PageRank 0.0249, imported by 26 files): hp_script: One executable <script>. Key abstractions: hp_status, hp_config, hp_script, FREEDOM_HTML_PARSE_H, max_bytes, hp_document. Depends on include: fb_cmdline (8), include: css (7), include: page_view (6). Used by include: page_view (11), include: browser_ui (6), src: text_shape (5).

- `include/html_parse.h` ranks 1 by PageRank, 26 importers, 24 symbols: hp_script: One executable <script>.
- `include/dom.h` ranks 2 by PageRank, 23 importers, 33 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- `include/js_sandbox.h` ranks 3 by PageRank, 21 importers, 37 symbols: js_limits: Per-evaluation resource limits.
- Hotspot `src/tab.c`: 219 symbols, 85 connections (score 0.42).
- Hotspot `tests/test_js_dom.c`: 280 symbols, 30 connections (score 0.25).
- Dependency cycle: js_dom.h -> js_location.h -> js_dom.h.
- 1 layer violations, e.g. test_renderer.c (testing) -> renderer.h (presentation).
- Dataflow: 1 INFERRED issues (first: UNCHECKED_ALLOC in fz_resolve).
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:tests/test_tab.c, file:src/dom.c, file:src/js_dom.c, file:src/js_sandbox.c, file:tests/test_url.c, file:include/js_sandbox.h
- Rating 6.5/10 = 7 x PageRank share 0.92 + 3 x risk 0.00. Internal imports: 163.

## include: browser_ui (`c1`, community, rating 4.7)

69 files under include (c 49, h 20), mostly utility. Core file include/scroll_req.h (PageRank 0.0050, imported by 6 files): srq_encode: Writes r as SRQ_WIRE_N int32: kind, behavior, block, y, margin_top, margin_bottom, n, nsub. Key abstractions: srq_kind, srq_behavior, srq_block, srq_req, srq_view, FREEDOM_SCROLL_REQ_H. Depends on src: text_shape (13), include: css (7), include: page_view (7). Used by src: tab (3), src: text_shape (2), include: css (1).

- `include/scroll_req.h` ranks 1 by PageRank, 6 importers, 14 symbols: srq_encode: Writes r as SRQ_WIRE_N int32: kind, behavior, block, y, margin_top, margin_bottom, n, nsub.
- `include/frame_broker.h` ranks 2 by PageRank, 4 importers, 17 symbols: fbk_origin_of: Serialized origin ("https://host[:port]", lowercase) or "null" for opaque/non-https/unparseable. * 0 on success, -1 if out does not fit or args are NULL.
- `include/box_blur.h` ranks 3 by PageRank, 4 importers, 5 symbols: Gaussian blur of an 8-bit alpha mask by three box passes per axis (spec/box_blur.md).
- Hotspot `gui/browser_ui.c`: 780 symbols, 168 connections (score 1.00).
- Hotspot `include/tab.h`: 62 symbols, 17 connections (score 0.09).
- 2 layer violations, e.g. browser_ui.c (presentation) -> data_url.h (data_access).
- Dataflow: 41 INFERRED issues (first: UNCHECKED_ALLOC in gui_sub_perform).
- Surprising bridge: fuzz_frame_broker.c <-> sha2.c (9 hops across communities).
- Key entities: file:gui/browser_ui.c, file:include/tab.h, file:src/browser.c, file:tests/test_interp.c, file:include/browser.h, file:tests/test_browser.c, file:src/frame_host.c, file:include/interp.h
- Rating 4.7/10 = 7 x PageRank share 0.67 + 3 x risk 0.00. Internal imports: 71.

## src: text_shape (`c3`, community, rating 3.9)

55 files under src (c 39, h 16), mostly utility. Core file include/hls.h (PageRank 0.0075, imported by 6 files): hls_segment: or variant info. Key abstractions: hls_status, hls_segment, hls_variant, hls_playlist, FREEDOM_HLS_H, hls_select_variant. Depends on include: page_view (6), src: tab (5), include: css (3). Used by include: browser_ui (13), src: tab (2), include: css (2).

- `include/hls.h` ranks 1 by PageRank, 6 importers, 11 symbols: hls_segment: or variant info.
- `include/webfont.h` ranks 2 by PageRank, 13 importers, 17 symbols: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- `include/hostblock.h` ranks 3 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- Hotspot `src/freedom.c`: 50 symbols, 64 connections (score 0.25).
- Hotspot `src/text_shape.c`: 75 symbols, 16 connections (score 0.10).
- 1 layer violations, e.g. render_policy.c (presentation) -> data_url.h (data_access).
- Key entities: file:src/text_shape.c, file:src/freedom.c, file:tests/test_text_shape.c, file:include/text_shape.h, file:include/webfont.h, file:include/tls_impersonate.h, file:tests/test_data_url.c, file:tests/test_hls.c
- Rating 3.9/10 = 7 x PageRank share 0.56 + 3 x risk 0.00. Internal imports: 67.

## include: page_view (`c4`, community, rating 2.4)

30 files under include (c 20, h 10), mostly utility. Core file include/page_view.h (PageRank 0.0099, imported by 16 files): pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for... Key abstractions: pv_status, pv_kind, pv_input_type, pv_form_method, pv_run, pv_box_def. Depends on include: css (19), src: tab (11), src: text_shape (2). Used by include: browser_ui (7), src: tab (6), src: text_shape (6).

- `include/page_view.h` ranks 1 by PageRank, 16 importers, 103 symbols: pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for...
- `include/render_policy.h` ranks 2 by PageRank, 9 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- `include/box_style.h` ranks 3 by PageRank, 12 importers, 31 symbols: bx_edges: anything longer fails closed instead of truncating into a wrong match. #define BX_TAG_NAME_MAX 32u typedef enum bx_display { BX_DISPLAY_BLOCK = 0,     /* stacks vertically, takes the available width BX_DISPLAY_INLINE...
- Hotspot `src/page_view.c`: 294 symbols, 44 connections (score 0.31).
- Hotspot `tests/test_page_view.c`: 231 symbols, 26 connections (score 0.21).
- 14 layer violations, e.g. render_doc.c (presentation) -> data_url.h (data_access).
- Dataflow: 6 INFERRED issues (first: DEAD_STORE in layout_grid).
- Key entities: file:src/page_view.c, file:tests/test_page_view.c, file:include/page_view.h, file:tests/test_box_tree.c, file:tests/test_flex_layout.c, file:include/flex_layout.h, file:tests/test_box_style.c, file:src/box_style.c
- Rating 2.4/10 = 7 x PageRank share 0.34 + 3 x risk 0.00. Internal imports: 58.

## include: http_cache (`c5`, community, rating 2.3)

28 files under include (c 19, h 9), mostly utility. Core file include/local_store.h (PageRank 0.0141, imported by 8 files): ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len... Key abstractions: ls_aead, ls_status, FREEDOM_LOCAL_STORE_H, LS_KEY_LEN, LS_SALT_LEN, LS_NONCE_LEN. Depends on src: tab (2), include: page_view (1). Used by include: browser_ui (5), src: text_shape (1), include: secure_fetch (1).

- `include/local_store.h` ranks 1 by PageRank, 8 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- `include/prefs.h` ranks 2 by PageRank, 7 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `include/zoom.h` ranks 3 by PageRank, 5 importers, 10 symbols: zm_clamp: stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser.
- Hotspot `src/http_cache.c`: 38 symbols, 20 connections (score 0.09).
- Hotspot `tests/test_profile.c`: 17 symbols, 16 connections (score 0.07).
- 4 layer violations, e.g. http_cache.h (presentation) -> local_store.h (data_access).
- Surprising bridge: pq_seal.c <-> sha2.c (9 hops across communities).
- Key entities: file:src/http_cache.c, file:gui/ui_render.c, file:src/local_store.c, file:src/prefs.c, file:include/ui.h, file:include/prefs.h, file:include/http_cache.h, file:tests/test_profile.c
- Rating 2.3/10 = 7 x PageRank share 0.34 + 3 x risk 0.00. Internal imports: 34.

## include: secure_fetch (`c6`, community, rating 2.0)

24 files under tests (c 17, h 7), mostly utility. Core file include/anti_fp.h (PageRank 0.0114, imported by 8 files): fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against... Key abstractions: FREEDOM_ANTI_FP_H, FP_TIMER_RESOLUTION_MS, FP_USER_AGENT, FP_ACCEPT_LANGUAGE, FP_ACCEPT_LANGUAGE_HEADER, FP_ACCEPT_HEADER_NAV. Depends on src: tab (1), src: text_shape (1), include: http_cache (1). Used by include: browser_ui (5), src: tab (4), src: text_shape (2).

- `include/anti_fp.h` ranks 1 by PageRank, 8 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- `include/secure_fetch.h` ranks 2 by PageRank, 8 importers, 48 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- `include/net_guard.h` ranks 3 by PageRank, 4 importers, 9 symbols: ng_request: #ifndef __STDC_VERSION__ #error "net_guard requires C11" #endif #ifdef __cplusplus #error "net_guard is C only" #endif typedef enum ng_verdict { NG_ALLOW = 0, NG_DENY = 1 } ng_verdict; #define NG_FAMILY_V4 4 #define...
- Hotspot `src/secure_fetch.c`: 82 symbols, 23 connections (score 0.12).
- Hotspot `include/secure_fetch.h`: 48 symbols, 13 connections (score 0.07).
- Key entities: file:src/secure_fetch.c, file:tests/test_secure_fetch.c, file:include/secure_fetch.h, file:include/anti_fp.h, file:src/ws_hub.c, file:include/identity.h, file:src/identity.c, file:src/anti_fp.c
- Rating 2.0/10 = 7 x PageRank share 0.28 + 3 x risk 0.00. Internal imports: 25.

## include: bui_chrome (`c7`, community, rating 1.4)

20 files under include (c 15, h 5), mostly utility. Core file include/video_controls.h (PageRank 0.0050, imported by 5 files): vcl_layout: Lays out the bar inside the video rect (x,y,w,h). Key abstractions: vcl_rect, vcl_geom, vcl_hit_kind, FREEDOM_VIDEO_CONTROLS_H, VCL_BAR_H, VCL_MIN_W. Depends on include: css (3), src: tab (2), include: page_view (2). Used by include: browser_ui (3), src: tab (1), src: text_shape (1).

- `include/video_controls.h` ranks 1 by PageRank, 5 importers, 23 symbols: vcl_layout: Lays out the bar inside the video rect (x,y,w,h).
- `include/chrome_layout.h` ranks 2 by PageRank, 4 importers, 44 symbols: chl_tab_rect: Computes the layout. tab_count >= 1 and 0 <= active < tab_count, else CHL_EINVAL * (out untouched).
- `include/link_nav.h` ranks 3 by PageRank, 8 importers, 11 symbols: ln_block_reason: Why a reference was blocked, for a precise user-facing notice and for * agent-friendly structured output.
- Hotspot `gui/browser_ui_internal.h`: 26 symbols, 15 connections (score 0.07).
- Hotspot `gui/bui_chrome.c`: 71 symbols, 5 connections (score 0.05).
- 1 layer violations, e.g. test_chrome_layout.c (testing) -> chrome_layout.h (presentation).
- Key entities: file:gui/bui_chrome.c, file:include/chrome_layout.h, file:gui/browser_ui_internal.h, file:include/video_controls.h, file:src/chrome_layout.c, file:tests/test_link_nav.c, file:tests/test_chrome_layout.c, file:include/link_nav.h
- Rating 1.4/10 = 7 x PageRank share 0.19 + 3 x risk 0.00. Internal imports: 20.

## include: svg_render (`c8`, community, rating 1.1)

14 files under include (c 10, h 4), mostly utility. Core file include/image_decode.h (PageRank 0.0075, imported by 7 files): img_pixels: A decoded bitmap that owns its pixel buffer. Key abstractions: img_format, img_status, img_pixels, FREEDOM_IMAGE_DECODE_H, guards, width. Depends on include: css (2), include: page_view (1). Used by include: browser_ui (3), src: tab (2), include: page_view (1).

- `include/image_decode.h` ranks 1 by PageRank, 7 importers, 14 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- `include/svg_render.h` ranks 2 by PageRank, 7 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- `include/svg_raster.h` ranks 3 by PageRank, 4 importers, 5 symbols: sr_sniff: 1 when the first element of the document (after BOM, whitespace, the XML * declaration, comments and a doctype) is <svg; 0 otherwise.
- Hotspot `tests/test_freedom.c`: 121 symbols, 12 connections (score 0.10).
- Hotspot `tests/test_svg_render.c`: 17 symbols, 11 connections (score 0.05).
- 1 layer violations, e.g. test_svg_render.c (testing) -> svg_render.h (presentation).
- Key entities: file:tests/test_freedom.c, file:tests/test_image_decode.c, file:src/svg_render.c, file:src/image_decode.c, file:tests/test_svg_render.c, file:include/svg_render.h, file:include/image_decode.h, file:tests/test_svg_raster.c
- Rating 1.1/10 = 7 x PageRank share 0.15 + 3 x risk 0.00. Internal imports: 15.

## unassigned files (`c14`, community, rating 0.8)

20 files under tools (py 11, sh 5, c 4), mostly utility. Core file app.py (PageRank 0.0012, imported by 0 files): Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode. Key abstractions: read_fuzz_stats, list_unique_crashes, run_freedom_headless, take_double, check_text, check_rect.

- `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- `docker_run.sh` ranks 3 by PageRank, 0 importers, 0 symbols: Thin wrapper.
- Hotspot `tests/test_site_panel.c`: 13 symbols, 7 connections (score 0.03).
- Hotspot `tools/fftime.py`: 1 symbols, 8 connections (score 0.03).
- Taint: 5 paths reach this group via subprocess, urllib.request.
- Key entities: file:tools/pngdiff.c, file:tests/test_site_panel.c, file:tools/gen_psl.c, file:tools/ffgeom.py, file:tools/fbench.py, file:fuzz/fuzz_site_panel.c, file:tools/mutate.py, file:tools/snapshot.py
- Rating 0.8/10 = 7 x PageRank share 0.12 + 3 x risk 0.00. Internal imports: 0.

## include: fb_cmdline (`c9`, community, rating 0.8)

11 files under include (c 8, h 3), mostly utility. Core file include/freebug.h (PageRank 0.0071, imported by 14 files): fb_entry: One captured console message. text and file are owned by the buffer (NUL-terminated). file/line/col are an optional source location (developer aid): file is NULL and line/col 0 when the location is unknown (e.g. a plain *... Key abstractions: fb_level, fb_entry, fb_buffer, FREEDOM_FREEBUG_H, level, FB_MAX_ENTRIES. Used by src: tab (8), include: browser_ui (4), src: text_shape (2).

- `include/freebug.h` ranks 1 by PageRank, 14 importers, 18 symbols: fb_entry: One captured console message. text and file are owned by the buffer (NUL-terminated). file/line/col are an optional source location (developer aid): file is NULL and line/col 0 when the location is unknown (e.g. a plain *...
- `include/fb_panes.h` ranks 2 by PageRank, 6 importers, 12 symbols: fbp_tab_label: FBP_CSS, FBP_SCRIPT, FBP_NET, FBP_PROFILE,   /* where the JS time went (sampling profiler, time-weighted) FBP_THROWS,    /* every exception thrown, caught ones included ("break on throw" log) FBP_DOM,       /* properties...
- `include/fb_cmdline.h` ranks 3 by PageRank, 5 importers, 18 symbols: fbc_history_push: #define FBC_BASE_MAX   256    /* bytes of a completion base path #define FBC_LIST_NAMES 40     /* candidates shown when a completion is ambiguous typedef struct fbc_history { char  *items[FBC_HIST_MAX];  /* oldest...
- Hotspot `include/freebug.h`: 18 symbols, 15 connections (score 0.06).
- Hotspot `tests/test_fb_cmdline.c`: 7 symbols, 10 connections (score 0.04).
- Dataflow: 2 INFERRED issues (first: UNCHECKED_ALLOC in LLVMFuzzerTestOneInput).
- Key entities: file:include/freebug.h, file:include/fb_cmdline.h, file:include/fb_panes.h, file:tests/test_freebug.c, file:tests/test_fb_panes.c, file:src/fb_cmdline.c, file:src/fb_panes.c, file:tests/test_fb_cmdline.c
- Rating 0.8/10 = 7 x PageRank share 0.12 + 3 x risk 0.00. Internal imports: 11.

## include: download (`c10`, community, rating 0.6)

8 files under include (c 6, h 2), mostly utility. Core file include/pdf_export.h (PageRank 0.0048, imported by 5 files): pe_paginate: Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h without ever splitting a row. Key abstractions: pe_status, FREEDOM_PDF_EXPORT_H, PE_NAME_MAX, PE_EXT, PE_EXT_PNG, PE_FALLBACK_NAME. Used by include: browser_ui (2).

- `include/pdf_export.h` ranks 1 by PageRank, 5 importers, 10 symbols: pe_paginate: Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h without ever splitting a row.
- `include/download.h` ranks 2 by PageRank, 4 importers, 9 symbols: dl_should_download: 1 if the response should be saved (attachment, or a non-renderable media type), 0 if it should be rendered.
- `fuzz/fuzz_download.c` ranks 3 by PageRank, 0 importers, 1 symbols.
- Hotspot `tests/test_pdf_export.c`: 30 symbols, 8 connections (score 0.04).
- Hotspot `tests/test_download.c`: 21 symbols, 8 connections (score 0.04).
- Key entities: file:tests/test_pdf_export.c, file:tests/test_download.c, file:src/download.c, file:include/pdf_export.h, file:include/download.h, file:src/pdf_export.c, file:fuzz/fuzz_pdf_export.c, file:fuzz/fuzz_download.c
- Rating 0.6/10 = 7 x PageRank share 0.08 + 3 x risk 0.00. Internal imports: 7.

## include: prefetch (`c11`, community, rating 0.5)

8 files under include (c 6, h 2), mostly utility. Core file include/import_map.h (PageRank 0.0047, imported by 5 files): im_resolve: Resolves specifier as imported from base (the importing module's URL). Key abstractions: FREEDOM_IMPORT_MAP_H, algorithm, IM_MAX_TEXT, IM_MAX_ENTRIES, IM_MAX_SCOPES, im_map. Depends on src: tab (1). Used by src: tab (1), include: browser_ui (1), src: text_shape (1).

- `include/import_map.h` ranks 1 by PageRank, 5 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- `include/prefetch.h` ranks 2 by PageRank, 5 importers, 28 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- `fuzz/fuzz_import_map.c` ranks 3 by PageRank, 0 importers, 2 symbols.
- Hotspot `tests/test_prefetch.c`: 19 symbols, 11 connections (score 0.05).
- Hotspot `src/prefetch.c`: 30 symbols, 9 connections (score 0.05).
- Key entities: file:include/prefetch.h, file:src/prefetch.c, file:tests/test_prefetch.c, file:src/import_map.c, file:include/import_map.h, file:tests/test_import_map.c, file:fuzz/fuzz_import_map.c, file:fuzz/fuzz_prefetch.c
- Rating 0.5/10 = 7 x PageRank share 0.08 + 3 x risk 0.00. Internal imports: 7.

## include: pres_hints (`c12`, community, rating 0.5)

7 files under include (c 5, h 2), mostly presentation. Core file include/table_layout.h (PageRank 0.0038, imported by 4 files): table_layout (tl_) -- used column widths of a table (automatic table layout). Key abstractions: tl_cell, FREEDOM_TABLE_LAYOUT_H, TL_MAX_COLS, TL_WIDTH_MAX, TL_PER_MILLE, col. Depends on include: css (2). Used by include: browser_ui (1), include: page_view (1).

- `include/table_layout.h` ranks 1 by PageRank, 4 importers, 8 symbols: table_layout (tl_) -- used column widths of a table (automatic table layout).
- `include/pres_hints.h` ranks 2 by PageRank, 4 importers, 10 symbols: pres_hints (ph_) -- HTML presentational attributes as zero-specificity style.
- `fuzz/fuzz_table_layout.c` ranks 3 by PageRank, 0 importers, 3 symbols: libFuzzer harness for table_layout and pres_hints (spec/table_layout.md, spec/pres_hints.md).
- Hotspot `tests/test_pres_hints.c`: 14 symbols, 8 connections (score 0.04).
- Hotspot `tests/test_table_layout.c`: 14 symbols, 8 connections (score 0.04).
- 1 layer violations, e.g. test_table_layout.c (testing) -> table_layout.h (presentation).
- Key entities: file:tests/test_table_layout.c, file:include/pres_hints.h, file:tests/test_pres_hints.c, file:src/pres_hints.c, file:include/table_layout.h, file:src/table_layout.c, file:fuzz/fuzz_table_layout.c, sym:src/pres_hints.c::PH_PER_MILLE_MAX@8
- Rating 0.5/10 = 7 x PageRank share 0.07 + 3 x risk 0.00. Internal imports: 6.

## tools (`c13`, community, rating 0.2)

3 files under tools (py 3), mostly utility. Core file tools/guitime.py (PageRank 0.0033, imported by 2 files): guitime -- how long the REAL Freedom window takes from "navigate" to "painted and idle". Key abstractions: start_display, one_run, main, phase_ms, one_page, main.

- `tools/guitime.py` ranks 1 by PageRank, 2 importers, 3 symbols: guitime -- how long the REAL Freedom window takes from "navigate" to "painted and idle".
- `tools/guiscroll.py` ranks 2 by PageRank, 0 importers, 4 symbols: guiscroll -- what one frame costs in the REAL Freedom window while the user scrolls.  guitime measures "navigate -> painted and idle"; this measures the frames AFTER that: the page is loaded in a nested weston (Xvfb + weston, pixman...
- `tools/guishot.py` ranks 3 by PageRank, 0 importers, 2 symbols: guishot -- a picture of the REAL Freedom window for the README.
- Hotspot `tools/guitime.py`: 3 symbols, 10 connections (score 0.04).
- Hotspot `tools/guiscroll.py`: 4 symbols, 9 connections (score 0.03).
- Taint: 5 paths reach this group via subprocess.
- Key entities: file:tools/guitime.py, file:tools/guishot.py, file:tools/guiscroll.py, sym:tools/guiscroll.py::one_page@48, sym:tools/guiscroll.py::main@95, sym:tools/guitime.py::main@96, sym:tools/guiscroll.py::phase_ms@38, sym:tools/guishot.py::main@43
- Rating 0.2/10 = 7 x PageRank share 0.03 + 3 x risk 0.00. Internal imports: 2.
