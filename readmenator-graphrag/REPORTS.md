# GraphRAG Community Reports

Entities: 7035 | Relationships: 12297 | Communities: 11 | Themes: 3 | Text units: 6605

Query with `readmenator . ask "<question>"` (local: BM25 + Personalized PageRank; global: map-reduce over these reports) or the MCP tool `readmenator.graphrag`.

## Project overview (`root`, root, rating 7.0)

275 files in 11 communities and 3 themes. Highest-impact communities: include: css (7.0), src (6.9), include: browser_ui (4.0). God nodes: gui/browser_ui.c, include/css.h, src/tab.c, src/css.c, src/page_view.c.

- [include: css] rating 7.0: `include/css_color.h` ranks 1 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- [src] rating 6.9: `include/html_parse.h` ranks 1 by PageRank, 23 importers, 24 symbols: hp_script: One executable <script>.
- [include: browser_ui] rating 4.0: `include/image_decode.h` ranks 1 by PageRank, 6 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- [include: page_view] rating 3.0: `include/render_policy.h` ranks 1 by PageRank, 9 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- [include: text_shape] rating 1.8: `include/data_url.h` ranks 1 by PageRank, 9 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- [include: local_store] rating 1.6: `include/local_store.h` ranks 1 by PageRank, 6 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [gui] rating 1.3: `include/svg_render.h` ranks 1 by PageRank, 6 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- [include: secure_fetch] rating 1.3: `include/anti_fp.h` ranks 1 by PageRank, 6 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- Key entities: file:tests/test_css.c, file:src/css.c, file:tests/test_js_dom.c, file:src/tab.c, file:gui/browser_ui.c, file:tests/test_freedom.c
- Children: t0, t1, t2
- Root rating = highest community rating.

## include: css + include: page_view +2 (`t1`, theme, rating 7.0)

Theme of 4 communities and 113 files: include: css (47 files, rating 7.0); include: page_view (31 files, rating 3.0); include: text_shape (20 files, rating 1.8); gui (15 files, rating 1.3).

- [include: css] `include/css_color.h` ranks 1 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- [include: css] `include/css.h` ranks 2 by PageRank, 36 importers, 138 symbols: css_style: A resolved presentation.
- [include: page_view] `include/render_policy.h` ranks 1 by PageRank, 9 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- [include: page_view] `include/page_view.h` ranks 2 by PageRank, 13 importers, 86 symbols: pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for...
- [include: text_shape] `include/data_url.h` ranks 1 by PageRank, 9 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- [include: text_shape] `include/webfont.h` ranks 2 by PageRank, 12 importers, 17 symbols: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- [gui] `include/svg_render.h` ranks 1 by PageRank, 6 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- [gui] `include/ui.h` ranks 2 by PageRank, 6 importers, 17 symbols: ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.
- Key entities: file:tests/test_css.c, file:src/css.c, file:src/page_view.c, file:tests/test_page_view.c, file:src/text_shape.c, file:include/text_shape.h, file:src/svg_render.c, file:gui/ui_render.c
- Children: c1, c3, c4, c6
- Theme rating = highest child community rating.

## src + include: browser_ui +4 (`t0`, theme, rating 6.9)

Theme of 6 communities and 147 files: src (59 files, rating 6.9); include: browser_ui (46 files, rating 4.0); include: local_store (16 files, rating 1.6); include: secure_fetch (10 files, rating 1.3); include: download (8 files, rating 0.7); include: prefetch (8 files, rating 0.7).

- [src] `include/html_parse.h` ranks 1 by PageRank, 23 importers, 24 symbols: hp_script: One executable <script>.
- [src] `include/dom.h` ranks 2 by PageRank, 19 importers, 28 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- [include: browser_ui] `include/image_decode.h` ranks 1 by PageRank, 6 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- [include: browser_ui] `include/tls_impersonate.h` ranks 2 by PageRank, 5 importers, 23 symbols: ti_req: Request: parent -> helper.
- [include: local_store] `include/local_store.h` ranks 1 by PageRank, 6 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [include: local_store] `include/prefs.h` ranks 2 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- [include: secure_fetch] `include/anti_fp.h` ranks 1 by PageRank, 6 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- [include: secure_fetch] `include/secure_fetch.h` ranks 2 by PageRank, 6 importers, 38 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:gui/browser_ui.c, file:tests/test_freedom.c, file:src/local_store.c, file:src/prefs.c, file:src/secure_fetch.c, file:tests/test_secure_fetch.c
- Children: c0, c2, c5, c7, c8, c9
- Theme rating = highest child community rating.

## unassigned files (`t2`, theme, rating 0.8)

Theme of 1 communities and 15 files: unassigned files (15 files, rating 0.8).

- [unassigned files] `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- [unassigned files] `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- Key entities: file:tools/pngdiff.c, file:tools/ffgeom.py
- Children: c10
- Theme rating = highest child community rating.

## include: css (`c1`, community, rating 7.0)

47 files under include (c 31, h 16), mostly utility. Core file include/css_color.h (PageRank 0.0506, imported by 13 files): cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1). Key abstractions: cc_rgb, cc_status, FREEDOM_CSS_COLOR_H, b, cc_pack, CC_COLOR_CURRENT. Depends on include: page_view (3), include: text_shape (2). Used by include: page_view (16), src (4), include: browser_ui (4).

- `include/css_color.h` ranks 1 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- `include/css.h` ranks 2 by PageRank, 36 importers, 138 symbols: css_style: A resolved presentation.
- `include/css_select.h` ranks 3 by PageRank, 15 importers, 34 symbols: css_attr_match: Sub-selector for :not()/:is()/:where(): a simple compound with only tag/.class/#id/[attr] (no combinators, no pseudo-classes inside * sub-selectors).
- Hotspot `src/css.c`: 244 symbols, 36 connections (score 0.35).
- Hotspot `tests/test_css.c`: 351 symbols, 18 connections (score 0.34).
- 1 layer violations, e.g. test_css.c (testing) -> flex_layout.h (presentation).
- Dataflow: 3 INFERRED issues (first: DEAD_STORE in page_view).
- Key entities: file:tests/test_css.c, file:src/css.c, file:include/css.h, file:src/css_box.c, file:include/css_select.h, file:tests/test_css_color.c, file:src/css_mq.c, file:tests/test_css_drops.c
- Rating 7.0/10 = 7 x PageRank share 1.00 + 3 x risk 0.00. Internal imports: 95.

## src (`c0`, community, rating 6.9)

59 files under src (c 40, h 19), mostly utility. Core file include/html_parse.h (PageRank 0.0308, imported by 23 files): hp_script: One executable <script>. Key abstractions: hp_status, hp_config, hp_script, FREEDOM_HTML_PARSE_H, max_bytes, hp_document. Depends on include: css (4), include: page_view (4), include: text_shape (2). Used by include: page_view (15), include: browser_ui (9), gui (2).

- `include/html_parse.h` ranks 1 by PageRank, 23 importers, 24 symbols: hp_script: One executable <script>.
- `include/dom.h` ranks 2 by PageRank, 19 importers, 28 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- `include/url.h` ranks 3 by PageRank, 18 importers, 14 symbols: url_parts: Components of a validated absolute https URL, sliced for a JS location object.
- Hotspot `src/tab.c`: 122 symbols, 58 connections (score 0.38).
- Hotspot `tests/test_js_dom.c`: 175 symbols, 24 connections (score 0.24).
- Dependency cycle: js_dom.h -> js_location.h -> js_dom.h.
- 1 layer violations, e.g. test_renderer.c (testing) -> renderer.h (presentation).
- Dataflow: 4 INFERRED issues (first: UNCHECKED_ALLOC in jd_click_state_new).
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:tests/test_tab.c, file:src/dom.c, file:src/js_dom.c, file:tests/test_url.c, file:include/tab.h, file:src/js_sandbox.c
- Rating 6.9/10 = 7 x PageRank share 0.98 + 3 x risk 0.00. Internal imports: 130.

## include: browser_ui (`c2`, community, rating 4.0)

46 files under tests (c 32, h 14), mostly utility. Core file include/image_decode.h (PageRank 0.0085, imported by 6 files): img_pixels: A decoded bitmap that owns its pixel buffer. Key abstractions: img_format, img_status, img_pixels, FREEDOM_IMAGE_DECODE_H, guards, width. Depends on src (9), include: page_view (6), include: text_shape (5). Used by include: page_view (5), src (1).

- `include/image_decode.h` ranks 1 by PageRank, 6 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- `include/tls_impersonate.h` ranks 2 by PageRank, 5 importers, 23 symbols: ti_req: Request: parent -> helper.
- `include/hls.h` ranks 3 by PageRank, 4 importers, 8 symbols: hls_segment: or variant info.
- Hotspot `gui/browser_ui.c`: 574 symbols, 119 connections (score 1.00).
- Hotspot `tests/test_freedom.c`: 88 symbols, 12 connections (score 0.12).
- 2 layer violations, e.g. browser_ui.c (presentation) -> data_url.h (data_access).
- Dataflow: 25 INFERRED issues (first: UNCHECKED_ALLOC in gui_subresource_fetch).
- Surprising bridge: block_flow.c <-> test_renderer.c (8 hops across communities).
- Key entities: file:gui/browser_ui.c, file:tests/test_freedom.c, file:src/browser.c, file:tests/test_interp.c, file:tests/test_image_decode.c, file:src/image_decode.c, file:include/tls_impersonate.h, file:include/interp.h
- Rating 4.0/10 = 7 x PageRank share 0.57 + 3 x risk 0.00. Internal imports: 45.

## include: page_view (`c3`, community, rating 3.0)

31 files under include (c 21, h 10), mostly utility. Core file include/render_policy.h (PageRank 0.0096, imported by 9 files): rdp_caps: Render capabilities for a page. Key abstractions: rdp_caps, rdp_img_decision, FREEDOM_RENDER_POLICY_H, RDP_TRACKER_MAX_DIM, images, rdp_is_tracking_pixel. Depends on include: css (16), src (15), include: text_shape (6). Used by include: browser_ui (6), src (4), include: css (3).

- `include/render_policy.h` ranks 1 by PageRank, 9 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- `include/page_view.h` ranks 2 by PageRank, 13 importers, 86 symbols: pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for...
- `include/flex_layout.h` ranks 3 by PageRank, 12 importers, 43 symbols: fx_item: Upper bound on items per flex line / grid columns.
- Hotspot `src/page_view.c`: 239 symbols, 38 connections (score 0.36).
- Hotspot `src/freedom.c`: 46 symbols, 54 connections (score 0.30).
- 14 layer violations, e.g. render_doc.c (presentation) -> data_url.h (data_access).
- Dataflow: 18 INFERRED issues (first: DEAD_STORE in layout_grid).
- Key entities: file:src/page_view.c, file:tests/test_page_view.c, file:include/page_view.h, file:tests/test_flex_layout.c, file:src/freedom.c, file:tests/test_box_tree.c, file:tests/test_box_style.c, file:include/flex_layout.h
- Rating 3.0/10 = 7 x PageRank share 0.43 + 3 x risk 0.00. Internal imports: 58.

## include: text_shape (`c4`, community, rating 1.8)

20 files under include (c 14, h 6), mostly utility. Core file include/data_url.h (PageRank 0.0089, imported by 9 files): du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN... Key abstractions: du_status, FREEDOM_DATA_URL_H, allocation, DU_MAX_ENCODED_LEN, du_is_data_url, closed. Depends on include: css (3), src (1), include: page_view (1). Used by include: page_view (6), include: browser_ui (5), src (2).

- `include/data_url.h` ranks 1 by PageRank, 9 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- `include/webfont.h` ranks 2 by PageRank, 12 importers, 17 symbols: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- `include/text_shape.h` ranks 3 by PageRank, 7 importers, 24 symbols: tsh_font: Font selector: a css_font_family bucket (CSS_FF_*) plus weight/slant flags.
- Hotspot `src/text_shape.c`: 59 symbols, 13 connections (score 0.11).
- Hotspot `tests/test_webfont_load.c`: 16 symbols, 16 connections (score 0.09).
- 1 layer violations, e.g. render_policy.c (presentation) -> data_url.h (data_access).
- Key entities: file:src/text_shape.c, file:include/text_shape.h, file:tests/test_text_shape.c, file:tests/test_data_url.c, file:include/webfont.h, file:tests/test_webfont_load.c, file:src/webfont.c, file:src/webfont_load.c
- Rating 1.8/10 = 7 x PageRank share 0.25 + 3 x risk 0.00. Internal imports: 24.

## include: local_store (`c5`, community, rating 1.6)

16 files under include (c 11, h 5), mostly utility. Core file include/local_store.h (PageRank 0.0115, imported by 6 files): ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len... Key abstractions: ls_aead, ls_status, FREEDOM_LOCAL_STORE_H, LS_KEY_LEN, LS_SALT_LEN, LS_NONCE_LEN. Depends on src (1). Used by include: browser_ui (3).

- `include/local_store.h` ranks 1 by PageRank, 6 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- `include/prefs.h` ranks 2 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `include/zoom.h` ranks 3 by PageRank, 5 importers, 10 symbols: zm_clamp: stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser.
- Hotspot `src/local_store.c`: 271 symbols, 10 connections (score 0.24).
- Hotspot `tests/test_profile.c`: 17 symbols, 16 connections (score 0.09).
- Surprising bridge: fuzz_prefs.c <-> test_renderer.c (8 hops across communities).
- Key entities: file:src/local_store.c, file:src/prefs.c, file:include/prefs.h, file:tests/test_profile.c, file:tests/test_disk_store.c, file:tests/test_local_store.c, file:tests/test_prefs.c, file:src/profile.c
- Rating 1.6/10 = 7 x PageRank share 0.23 + 3 x risk 0.00. Internal imports: 20.

## gui (`c6`, community, rating 1.3)

15 files under gui (c 10, h 5), mostly presentation. Core file include/svg_render.h (PageRank 0.0082, imported by 6 files): sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order). Key abstractions: sv_status, sv_shape_kind, sv_verb, sv_seg, sv_shape, sv_image. Depends on include: css (3), src (2), include: page_view (1). Used by include: browser_ui (4), include: page_view (3), src (1).

- `include/svg_render.h` ranks 1 by PageRank, 6 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- `include/ui.h` ranks 2 by PageRank, 6 importers, 17 symbols: ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.
- `include/freedom_config.h` ranks 3 by PageRank, 6 importers, 13 symbols.
- Hotspot `gui/ui_render.c`: 29 symbols, 13 connections (score 0.09).
- Hotspot `tests/test_svg_render.c`: 16 symbols, 11 connections (score 0.07).
- 2 layer violations, e.g. test_svg_render.c (testing) -> svg_render.h (presentation).
- Key entities: file:src/svg_render.c, file:gui/ui_render.c, file:tests/test_svg_render.c, file:include/svg_render.h, file:include/ui.h, file:include/freedom_config.h, file:tests/test_ui.c, file:gui/browser_ui_internal.h
- Rating 1.3/10 = 7 x PageRank share 0.19 + 3 x risk 0.00. Internal imports: 14.

## include: secure_fetch (`c7`, community, rating 1.3)

10 files under tests (c 7, h 3), mostly utility. Core file include/anti_fp.h (PageRank 0.0150, imported by 6 files): fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against... Key abstractions: FREEDOM_ANTI_FP_H, FP_TIMER_RESOLUTION_MS, FP_USER_AGENT, FP_ACCEPT_LANGUAGE, FP_ACCEPT_LANGUAGE_HEADER, FP_ACCEPT_HEADER_NAV. Depends on src (1). Used by src (2), include: browser_ui (2), include: page_view (1).

- `include/anti_fp.h` ranks 1 by PageRank, 6 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- `include/secure_fetch.h` ranks 2 by PageRank, 6 importers, 38 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- `include/ws_hub.h` ranks 3 by PageRank, 3 importers, 15 symbols: wh_new: #define WH_MAX 8   /* == JD_WS_MAX: sockets per page /* Event kinds delivered to the page; values match tab_ws_event_kind. enum { WH_EV_OPEN = 1, WH_EV_TEXT = 2, WH_EV_BINARY = 3, WH_EV_CLOSE = 4, WH_EV_ERROR = 5 }; /* Abnormal...
- Hotspot `src/secure_fetch.c`: 61 symbols, 16 connections (score 0.12).
- Hotspot `tests/test_secure_fetch.c`: 50 symbols, 9 connections (score 0.08).
- Key entities: file:src/secure_fetch.c, file:tests/test_secure_fetch.c, file:include/secure_fetch.h, file:include/anti_fp.h, file:src/ws_hub.c, file:src/anti_fp.c, file:include/ws_hub.h, file:tests/test_ws_hub.c
- Rating 1.3/10 = 7 x PageRank share 0.18 + 3 x risk 0.00. Internal imports: 10.

## unassigned files (`c10`, community, rating 0.8)

15 files under tools (py 8, sh 5, c 2), mostly utility. Core file app.py (PageRank 0.0019, imported by 0 files): Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode. Key abstractions: read_fuzz_stats, list_unique_crashes, run_freedom_headless, load_rows, lum, lum_at.

- `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- `docker_run.sh` ranks 3 by PageRank, 0 importers, 0 symbols: Thin wrapper.
- Hotspot `tools/pngdiff.c`: 14 symbols, 6 connections (score 0.04).
- Hotspot `tools/ffgeom.py`: 12 symbols, 6 connections (score 0.04).
- Taint: 4 paths reach this group via subprocess, urllib.request.
- Key entities: file:tools/pngdiff.c, file:tools/ffgeom.py, file:tools/gen_psl.c, file:tools/mutate.py, file:tools/snapshot.py, file:tools/ffshot.py, file:tools/ffq.py, file:tools/pngprof.py
- Rating 0.8/10 = 7 x PageRank share 0.12 + 3 x risk 0.00. Internal imports: 0.

## include: download (`c8`, community, rating 0.7)

8 files under include (c 6, h 2), mostly utility. Core file include/pdf_export.h (PageRank 0.0076, imported by 5 files): pe_paginate: Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h without ever splitting a row. Key abstractions: pe_status, FREEDOM_PDF_EXPORT_H, PE_NAME_MAX, PE_EXT, PE_EXT_PNG, PE_FALLBACK_NAME. Used by include: browser_ui (2).

- `include/pdf_export.h` ranks 1 by PageRank, 5 importers, 10 symbols: pe_paginate: Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h without ever splitting a row.
- `include/download.h` ranks 2 by PageRank, 4 importers, 9 symbols: dl_should_download: 1 if the response should be saved (attachment, or a non-renderable media type), 0 if it should be rendered.
- `fuzz/fuzz_download.c` ranks 3 by PageRank, 0 importers, 1 symbols.
- Hotspot `tests/test_pdf_export.c`: 30 symbols, 8 connections (score 0.06).
- Hotspot `tests/test_download.c`: 21 symbols, 8 connections (score 0.06).
- Surprising bridge: fuzz_download.c <-> test_renderer.c (8 hops across communities).
- Key entities: file:tests/test_pdf_export.c, file:tests/test_download.c, file:src/download.c, file:include/pdf_export.h, file:include/download.h, file:src/pdf_export.c, file:fuzz/fuzz_download.c, file:fuzz/fuzz_pdf_export.c
- Rating 0.7/10 = 7 x PageRank share 0.10 + 3 x risk 0.00. Internal imports: 7.

## include: prefetch (`c9`, community, rating 0.7)

8 files under include (c 6, h 2), mostly utility. Core file include/import_map.h (PageRank 0.0074, imported by 5 files): im_resolve: Resolves specifier as imported from base (the importing module's URL). Key abstractions: FREEDOM_IMPORT_MAP_H, algorithm, IM_MAX_TEXT, IM_MAX_ENTRIES, IM_MAX_SCOPES, im_map. Depends on src (1). Used by src (1), include: browser_ui (1), include: page_view (1).

- `include/import_map.h` ranks 1 by PageRank, 5 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- `include/prefetch.h` ranks 2 by PageRank, 5 importers, 28 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- `fuzz/fuzz_import_map.c` ranks 3 by PageRank, 0 importers, 2 symbols.
- Hotspot `tests/test_prefetch.c`: 18 symbols, 11 connections (score 0.07).
- Hotspot `src/prefetch.c`: 30 symbols, 9 connections (score 0.07).
- Key entities: file:include/prefetch.h, file:src/prefetch.c, file:tests/test_prefetch.c, file:src/import_map.c, file:include/import_map.h, file:tests/test_import_map.c, file:fuzz/fuzz_import_map.c, file:fuzz/fuzz_prefetch.c
- Rating 0.7/10 = 7 x PageRank share 0.10 + 3 x risk 0.00. Internal imports: 7.
