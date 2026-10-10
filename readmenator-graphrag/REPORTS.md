# GraphRAG Community Reports

Entities: 6657 | Relationships: 11671 | Communities: 11 | Themes: 4 | Text units: 6238

Query with `readmenator . ask "<question>"` (local: BM25 + Personalized PageRank; global: map-reduce over these reports) or the MCP tool `readmenator.graphrag`.

## Project overview (`root`, root, rating 7.0)

262 files in 11 communities and 4 themes. Highest-impact communities: src (7.0), include: css (6.1), include: browser_ui (4.2). God nodes: gui/browser_ui.c, include/css.h, src/tab.c, src/freedom.c, src/css.c.

- [src] rating 7.0: `include/html_parse.h` ranks 1 by PageRank, 23 importers, 24 symbols: hp_script: One executable <script>.
- [include: css] rating 6.1: `include/css_color.h` ranks 1 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- [include: browser_ui] rating 4.2: `include/image_decode.h` ranks 1 by PageRank, 6 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- [include: page_view] rating 3.1: `include/render_policy.h` ranks 1 by PageRank, 9 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- [include: text_shape] rating 1.8: `include/data_url.h` ranks 1 by PageRank, 9 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- [include: local_store] rating 1.6: `include/local_store.h` ranks 1 by PageRank, 6 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [gui] rating 1.4: `include/svg_render.h` ranks 1 by PageRank, 6 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- [include: secure_fetch] rating 1.3: `include/anti_fp.h` ranks 1 by PageRank, 6 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:tests/test_css.c, file:src/css.c, file:gui/browser_ui.c, file:tests/test_freedom.c
- Children: t0, t1, t2, t3
- Root rating = highest community rating.

## src + include: secure_fetch +1 (`t1`, theme, rating 7.0)

Theme of 3 communities and 73 files: src (59 files, rating 7.0); include: secure_fetch (10 files, rating 1.3); include: import_map (4 files, rating 0.4).

- [src] `include/html_parse.h` ranks 1 by PageRank, 23 importers, 24 symbols: hp_script: One executable <script>.
- [src] `include/dom.h` ranks 2 by PageRank, 19 importers, 28 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- [include: secure_fetch] `include/anti_fp.h` ranks 1 by PageRank, 6 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- [include: secure_fetch] `include/secure_fetch.h` ranks 2 by PageRank, 6 importers, 38 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- [include: import_map] `include/import_map.h` ranks 1 by PageRank, 4 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- [include: import_map] `fuzz/fuzz_import_map.c` ranks 2 by PageRank, 0 importers, 2 symbols.
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:src/secure_fetch.c, file:tests/test_secure_fetch.c, file:src/import_map.c, file:include/import_map.h
- Children: c0, c7, c9
- Theme rating = highest child community rating.

## include: css + include: page_view +2 (`t0`, theme, rating 6.1)

Theme of 4 communities and 106 files: include: css (40 files, rating 6.1); include: page_view (31 files, rating 3.1); include: text_shape (20 files, rating 1.8); gui (15 files, rating 1.4).

- [include: css] `include/css_color.h` ranks 1 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- [include: css] `include/css.h` ranks 2 by PageRank, 33 importers, 131 symbols: css_style: A resolved presentation.
- [include: page_view] `include/render_policy.h` ranks 1 by PageRank, 9 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- [include: page_view] `include/page_view.h` ranks 2 by PageRank, 13 importers, 72 symbols: pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for...
- [include: text_shape] `include/data_url.h` ranks 1 by PageRank, 9 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- [include: text_shape] `include/webfont.h` ranks 2 by PageRank, 12 importers, 17 symbols: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- [gui] `include/svg_render.h` ranks 1 by PageRank, 6 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- [gui] `include/ui.h` ranks 2 by PageRank, 6 importers, 17 symbols: ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.
- Key entities: file:tests/test_css.c, file:src/css.c, file:src/page_view.c, file:tests/test_page_view.c, file:src/text_shape.c, file:tests/test_data_url.c, file:src/svg_render.c, file:gui/ui_render.c
- Children: c2, c3, c4, c6
- Theme rating = highest child community rating.

## include: browser_ui + include: local_store +1 (`t2`, theme, rating 4.2)

Theme of 3 communities and 71 files: include: browser_ui (47 files, rating 4.2); include: local_store (16 files, rating 1.6); include: download (8 files, rating 0.7).

- [include: browser_ui] `include/image_decode.h` ranks 1 by PageRank, 6 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- [include: browser_ui] `include/prefetch.h` ranks 2 by PageRank, 5 importers, 21 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- [include: local_store] `include/local_store.h` ranks 1 by PageRank, 6 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [include: local_store] `include/prefs.h` ranks 2 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- [include: download] `include/pdf_export.h` ranks 1 by PageRank, 5 importers, 10 symbols: pe_paginate: Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h without ever splitting a row.
- [include: download] `include/download.h` ranks 2 by PageRank, 4 importers, 9 symbols: dl_should_download: 1 if the response should be saved (attachment, or a non-renderable media type), 0 if it should be rendered.
- Key entities: file:gui/browser_ui.c, file:tests/test_freedom.c, file:src/local_store.c, file:src/prefs.c, file:tests/test_pdf_export.c, file:tests/test_download.c
- Children: c1, c5, c8
- Theme rating = highest child community rating.

## unassigned files (`t3`, theme, rating 0.7)

Theme of 1 communities and 12 files: unassigned files (12 files, rating 0.7).

- [unassigned files] `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- [unassigned files] `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- Key entities: file:tools/pngdiff.c, file:tools/ffgeom.py
- Children: c10
- Theme rating = highest child community rating.

## src (`c0`, community, rating 7.0)

59 files under src (c 40, h 19), mostly utility. Core file include/html_parse.h (PageRank 0.0325, imported by 23 files): hp_script: One executable <script>. Key abstractions: hp_status, hp_config, hp_script, FREEDOM_HTML_PARSE_H, max_bytes, hp_document. Depends on include: css (4), include: page_view (3), include: text_shape (2). Used by include: page_view (15), include: browser_ui (9), gui (2).

- `include/html_parse.h` ranks 1 by PageRank, 23 importers, 24 symbols: hp_script: One executable <script>.
- `include/dom.h` ranks 2 by PageRank, 19 importers, 28 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- `include/url.h` ranks 3 by PageRank, 17 importers, 14 symbols: url_parts: Components of a validated absolute https URL, sliced for a JS location object.
- Hotspot `src/tab.c`: 120 symbols, 56 connections (score 0.38).
- Hotspot `tests/test_js_dom.c`: 175 symbols, 24 connections (score 0.26).
- Dependency cycle: js_dom.h -> js_location.h -> js_dom.h.
- 1 layer violations, e.g. test_renderer.c (testing) -> renderer.h (presentation).
- Dataflow: 4 INFERRED issues (first: UNCHECKED_ALLOC in jd_click_state_new).
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:tests/test_tab.c, file:src/dom.c, file:src/js_dom.c, file:tests/test_url.c, file:include/tab.h, file:src/js_sandbox.c
- Rating 7.0/10 = 7 x PageRank share 1.00 + 3 x risk 0.00. Internal imports: 130.

## include: css (`c2`, community, rating 6.1)

40 files under include (c 26, h 14), mostly utility. Core file include/css_color.h (PageRank 0.0482, imported by 13 files): cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1). Key abstractions: cc_rgb, cc_status, FREEDOM_CSS_COLOR_H, b, cc_pack, CC_COLOR_CURRENT. Depends on include: text_shape (2), include: page_view (1). Used by include: page_view (15), src (4), include: browser_ui (3).

- `include/css_color.h` ranks 1 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- `include/css.h` ranks 2 by PageRank, 33 importers, 131 symbols: css_style: A resolved presentation.
- `include/css_select.h` ranks 3 by PageRank, 14 importers, 34 symbols: css_attr_match: Sub-selector for :not()/:is()/:where(): a simple compound with only tag/.class/#id/[attr] (no combinators, no pseudo-classes inside * sub-selectors).
- Hotspot `src/css.c`: 231 symbols, 34 connections (score 0.35).
- Hotspot `tests/test_css.c`: 333 symbols, 16 connections (score 0.33).
- Dataflow: 2 INFERRED issues (first: DEAD_STORE in parse_hex).
- Key entities: file:tests/test_css.c, file:src/css.c, file:include/css.h, file:src/css_box.c, file:include/css_select.h, file:tests/test_css_color.c, file:src/css_mq.c, file:tests/test_css_drops.c
- Rating 6.1/10 = 7 x PageRank share 0.88 + 3 x risk 0.00. Internal imports: 85.

## include: browser_ui (`c1`, community, rating 4.2)

47 files under tests (c 33, h 14), mostly utility. Core file include/image_decode.h (PageRank 0.0090, imported by 6 files): img_pixels: A decoded bitmap that owns its pixel buffer. Key abstractions: img_format, img_status, img_pixels, FREEDOM_IMAGE_DECODE_H, guards, width. Depends on src (9), include: page_view (6), include: text_shape (5). Used by include: page_view (6), src (1).

- `include/image_decode.h` ranks 1 by PageRank, 6 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- `include/prefetch.h` ranks 2 by PageRank, 5 importers, 21 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- `include/tls_impersonate.h` ranks 3 by PageRank, 5 importers, 23 symbols: ti_req: Request: parent -> helper.
- Hotspot `gui/browser_ui.c`: 531 symbols, 115 connections (score 1.00).
- Hotspot `tests/test_freedom.c`: 72 symbols, 12 connections (score 0.12).
- 2 layer violations, e.g. browser_ui.c (presentation) -> data_url.h (data_access).
- Dataflow: 19 INFERRED issues (first: UNCHECKED_ALLOC in gui_subresource_fetch).
- Surprising bridge: block_flow.c <-> test_renderer.c (8 hops across communities).
- Key entities: file:gui/browser_ui.c, file:tests/test_freedom.c, file:src/browser.c, file:tests/test_interp.c, file:tests/test_image_decode.c, file:src/image_decode.c, file:include/tls_impersonate.h, file:include/prefetch.h
- Rating 4.2/10 = 7 x PageRank share 0.60 + 3 x risk 0.00. Internal imports: 46.

## include: page_view (`c3`, community, rating 3.1)

31 files under include (c 21, h 10), mostly utility. Core file include/render_policy.h (PageRank 0.0101, imported by 9 files): rdp_caps: Render capabilities for a page. Key abstractions: rdp_caps, rdp_img_decision, FREEDOM_RENDER_POLICY_H, RDP_TRACKER_MAX_DIM, images, rdp_is_tracking_pixel. Depends on src (15), include: css (15), include: browser_ui (6). Used by include: browser_ui (6), src (3), include: css (1).

- `include/render_policy.h` ranks 1 by PageRank, 9 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- `include/page_view.h` ranks 2 by PageRank, 13 importers, 72 symbols: pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for...
- `include/box_style.h` ranks 3 by PageRank, 11 importers, 25 symbols: bx_edges: anything longer fails closed instead of truncating into a wrong match. #define BX_TAG_NAME_MAX 32u typedef enum bx_display { BX_DISPLAY_BLOCK = 0,     /* stacks vertically, takes the available width BX_DISPLAY_INLINE...
- Hotspot `src/page_view.c`: 222 symbols, 35 connections (score 0.35).
- Hotspot `src/freedom.c`: 46 symbols, 54 connections (score 0.32).
- 14 layer violations, e.g. render_doc.c (presentation) -> data_url.h (data_access).
- Dataflow: 25 INFERRED issues (first: UNINIT_USE in layout_grid).
- Key entities: file:src/page_view.c, file:tests/test_page_view.c, file:include/page_view.h, file:tests/test_flex_layout.c, file:src/freedom.c, file:tests/test_box_tree.c, file:tests/test_box_style.c, file:tests/test_render_doc.c
- Rating 3.1/10 = 7 x PageRank share 0.44 + 3 x risk 0.00. Internal imports: 58.

## include: text_shape (`c4`, community, rating 1.8)

20 files under include (c 14, h 6), mostly utility. Core file include/data_url.h (PageRank 0.0093, imported by 9 files): du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN... Key abstractions: du_status, FREEDOM_DATA_URL_H, allocation, DU_MAX_ENCODED_LEN, du_is_data_url, closed. Depends on include: css (3), src (1), include: page_view (1). Used by include: page_view (6), include: browser_ui (5), src (2).

- `include/data_url.h` ranks 1 by PageRank, 9 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- `include/webfont.h` ranks 2 by PageRank, 12 importers, 17 symbols: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- `include/text_shape.h` ranks 3 by PageRank, 7 importers, 13 symbols: tsh_font: Font selector: a css_font_family bucket (CSS_FF_*) plus weight/slant flags.
- Hotspot `tests/test_webfont_load.c`: 16 symbols, 16 connections (score 0.10).
- Hotspot `src/text_shape.c`: 26 symbols, 13 connections (score 0.09).
- 1 layer violations, e.g. render_policy.c (presentation) -> data_url.h (data_access).
- Key entities: file:src/text_shape.c, file:tests/test_data_url.c, file:include/webfont.h, file:tests/test_webfont_load.c, file:include/text_shape.h, file:src/webfont.c, file:tests/test_text_shape.c, file:src/webfont_load.c
- Rating 1.8/10 = 7 x PageRank share 0.26 + 3 x risk 0.00. Internal imports: 24.

## include: local_store (`c5`, community, rating 1.6)

16 files under include (c 11, h 5), mostly utility. Core file include/local_store.h (PageRank 0.0121, imported by 6 files): ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len... Key abstractions: ls_aead, ls_status, FREEDOM_LOCAL_STORE_H, LS_KEY_LEN, LS_SALT_LEN, LS_NONCE_LEN. Depends on src (1). Used by include: browser_ui (3).

- `include/local_store.h` ranks 1 by PageRank, 6 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- `include/prefs.h` ranks 2 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `include/zoom.h` ranks 3 by PageRank, 5 importers, 10 symbols: zm_clamp: stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser.
- Hotspot `src/local_store.c`: 271 symbols, 10 connections (score 0.26).
- Hotspot `tests/test_profile.c`: 17 symbols, 16 connections (score 0.10).
- Surprising bridge: fuzz_prefs.c <-> test_renderer.c (8 hops across communities).
- Key entities: file:src/local_store.c, file:src/prefs.c, file:include/prefs.h, file:tests/test_profile.c, file:tests/test_disk_store.c, file:tests/test_local_store.c, file:tests/test_prefs.c, file:src/profile.c
- Rating 1.6/10 = 7 x PageRank share 0.23 + 3 x risk 0.00. Internal imports: 20.

## gui (`c6`, community, rating 1.4)

15 files under gui (c 10, h 5), mostly presentation. Core file include/svg_render.h (PageRank 0.0087, imported by 6 files): sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order). Key abstractions: sv_status, sv_shape_kind, sv_verb, sv_seg, sv_shape, sv_image. Depends on include: css (3), src (2), include: page_view (1). Used by include: browser_ui (4), include: page_view (3), src (1).

- `include/svg_render.h` ranks 1 by PageRank, 6 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- `include/ui.h` ranks 2 by PageRank, 6 importers, 17 symbols: ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.
- `include/freedom_config.h` ranks 3 by PageRank, 6 importers, 13 symbols.
- Hotspot `gui/ui_render.c`: 29 symbols, 13 connections (score 0.09).
- Hotspot `tests/test_svg_render.c`: 16 symbols, 11 connections (score 0.07).
- 2 layer violations, e.g. test_svg_render.c (testing) -> svg_render.h (presentation).
- Key entities: file:src/svg_render.c, file:gui/ui_render.c, file:tests/test_svg_render.c, file:include/svg_render.h, file:include/ui.h, file:include/freedom_config.h, file:tests/test_ui.c, file:gui/browser_ui_internal.h
- Rating 1.4/10 = 7 x PageRank share 0.20 + 3 x risk 0.00. Internal imports: 14.

## include: secure_fetch (`c7`, community, rating 1.3)

10 files under tests (c 7, h 3), mostly utility. Core file include/anti_fp.h (PageRank 0.0158, imported by 6 files): fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against... Key abstractions: FREEDOM_ANTI_FP_H, FP_TIMER_RESOLUTION_MS, FP_USER_AGENT, FP_ACCEPT_LANGUAGE, FP_ACCEPT_LANGUAGE_HEADER, FP_ACCEPT_HEADER_NAV. Depends on src (1). Used by src (2), include: browser_ui (2), include: page_view (1).

- `include/anti_fp.h` ranks 1 by PageRank, 6 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- `include/secure_fetch.h` ranks 2 by PageRank, 6 importers, 38 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- `include/ws_hub.h` ranks 3 by PageRank, 3 importers, 15 symbols: wh_new: #define WH_MAX 8   /* == JD_WS_MAX: sockets per page /* Event kinds delivered to the page; values match tab_ws_event_kind. enum { WH_EV_OPEN = 1, WH_EV_TEXT = 2, WH_EV_BINARY = 3, WH_EV_CLOSE = 4, WH_EV_ERROR = 5 }; /* Abnormal...
- Hotspot `src/secure_fetch.c`: 61 symbols, 16 connections (score 0.13).
- Hotspot `tests/test_secure_fetch.c`: 50 symbols, 9 connections (score 0.08).
- Key entities: file:src/secure_fetch.c, file:tests/test_secure_fetch.c, file:include/secure_fetch.h, file:include/anti_fp.h, file:src/ws_hub.c, file:src/anti_fp.c, file:include/ws_hub.h, file:tests/test_ws_hub.c
- Rating 1.3/10 = 7 x PageRank share 0.19 + 3 x risk 0.00. Internal imports: 10.

## unassigned files (`c10`, community, rating 0.7)

12 files under tools (py 5, sh 5, c 2), mostly utility. Core file app.py (PageRank 0.0020, imported by 0 files): Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode. Key abstractions: read_fuzz_stats, list_unique_crashes, run_freedom_headless, load_rows, lum, lum_at.

- `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- `docker_run.sh` ranks 3 by PageRank, 0 importers, 0 symbols: Thin wrapper.
- Hotspot `tools/pngdiff.c`: 14 symbols, 6 connections (score 0.04).
- Hotspot `tools/ffgeom.py`: 12 symbols, 6 connections (score 0.04).
- Taint: 4 paths reach this group via subprocess, urllib.request.
- Key entities: file:tools/pngdiff.c, file:tools/ffgeom.py, file:tools/gen_psl.c, file:tools/mutate.py, file:tools/snapshot.py, file:app.py, file:tools/pngprof.py, sym:tools/mutate.py::main@137
- Rating 0.7/10 = 7 x PageRank share 0.10 + 3 x risk 0.00. Internal imports: 0.

## include: download (`c8`, community, rating 0.7)

8 files under include (c 6, h 2), mostly utility. Core file include/pdf_export.h (PageRank 0.0080, imported by 5 files): pe_paginate: Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h without ever splitting a row. Key abstractions: pe_status, FREEDOM_PDF_EXPORT_H, PE_NAME_MAX, PE_EXT, PE_EXT_PNG, PE_FALLBACK_NAME. Used by include: browser_ui (2).

- `include/pdf_export.h` ranks 1 by PageRank, 5 importers, 10 symbols: pe_paginate: Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h without ever splitting a row.
- `include/download.h` ranks 2 by PageRank, 4 importers, 9 symbols: dl_should_download: 1 if the response should be saved (attachment, or a non-renderable media type), 0 if it should be rendered.
- `fuzz/fuzz_download.c` ranks 3 by PageRank, 0 importers, 1 symbols.
- Hotspot `tests/test_pdf_export.c`: 30 symbols, 8 connections (score 0.06).
- Hotspot `tests/test_download.c`: 21 symbols, 8 connections (score 0.06).
- Surprising bridge: fuzz_download.c <-> test_renderer.c (8 hops across communities).
- Key entities: file:tests/test_pdf_export.c, file:tests/test_download.c, file:src/download.c, file:include/pdf_export.h, file:include/download.h, file:src/pdf_export.c, file:fuzz/fuzz_download.c, file:fuzz/fuzz_pdf_export.c
- Rating 0.7/10 = 7 x PageRank share 0.11 + 3 x risk 0.00. Internal imports: 7.

## include: import_map (`c9`, community, rating 0.4)

4 files under include (c 3, h 1), mostly utility. Core file include/import_map.h (PageRank 0.0072, imported by 4 files): im_resolve: Resolves specifier as imported from base (the importing module's URL). Key abstractions: FREEDOM_IMPORT_MAP_H, algorithm, IM_MAX_TEXT, IM_MAX_ENTRIES, IM_MAX_SCOPES, im_map. Used by src (1).

- `include/import_map.h` ranks 1 by PageRank, 4 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- `fuzz/fuzz_import_map.c` ranks 2 by PageRank, 0 importers, 2 symbols.
- `src/import_map.c` ranks 3 by PageRank, 0 importers, 22 symbols: str: A JSON string into an owned UTF-8 buffer (escapes decoded; a lone surrogate or a * raw control character is malformed).
- Hotspot `tests/test_import_map.c`: 8 symbols, 9 connections (score 0.05).
- Hotspot `src/import_map.c`: 22 symbols, 5 connections (score 0.04).
- Key entities: file:src/import_map.c, file:include/import_map.h, file:tests/test_import_map.c, file:fuzz/fuzz_import_map.c, sym:src/import_map.c::str@78, sym:src/import_map.c::IM_MAX_DEPTH@16, sym:src/import_map.c::IM_URL_MAX@17, sym:src/import_map.c::add@185
- Rating 0.4/10 = 7 x PageRank share 0.05 + 3 x risk 0.00. Internal imports: 3.
