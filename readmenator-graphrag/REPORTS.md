# GraphRAG Community Reports

Entities: 7868 | Relationships: 13721 | Communities: 11 | Themes: 3 | Text units: 7416

Query with `readmenator . ask "<question>"` (local: BM25 + Personalized PageRank; global: map-reduce over these reports) or the MCP tool `readmenator.graphrag`.

## Project overview (`root`, root, rating 7.0)

289 files in 11 communities and 3 themes. Highest-impact communities: src: css (7.0), src: tab (4.6), include: browser_ui (3.6). God nodes: gui/browser_ui.c, include/css.h, src/tab.c, src/freedom.c, src/css.c.

- [src: css] rating 7.0: `include/css.h` ranks 1 by PageRank, 36 importers, 140 symbols: css_style: A resolved presentation.
- [src: tab] rating 4.6: `include/html_parse.h` ranks 1 by PageRank, 18 importers, 24 symbols: hp_script: One executable <script>.
- [include: browser_ui] rating 3.6: `include/prefs.h` ranks 1 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- [src: text_shape] rating 3.2: `include/js_policy.h` ranks 1 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- [include: page_view] rating 1.7: `include/render_policy.h` ranks 1 by PageRank, 8 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- [src: local_store] rating 1.7: `include/local_store.h` ranks 1 by PageRank, 8 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [include: browser] rating 1.6: `include/hostblock.h` ranks 1 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- [include: secure_fetch] rating 1.5: `include/anti_fp.h` ranks 1 by PageRank, 8 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- Key entities: file:tests/test_css.c, file:src/css.c, file:tests/test_js_dom.c, file:src/tab.c, file:gui/browser_ui.c, file:tests/test_freedom.c
- Children: t0, t1, t2
- Root rating = highest community rating.

## src: css + src: tab +4 (`t0`, theme, rating 7.0)

Theme of 6 communities and 191 files: src: css (53 files, rating 7.0); src: tab (45 files, rating 4.6); src: text_shape (42 files, rating 3.2); include: page_view (19 files, rating 1.7); include: browser (19 files, rating 1.6); gui (13 files, rating 1.0).

- [src: css] `include/css.h` ranks 1 by PageRank, 36 importers, 140 symbols: css_style: A resolved presentation.
- [src: css] `include/css_color.h` ranks 2 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- [src: tab] `include/html_parse.h` ranks 1 by PageRank, 18 importers, 24 symbols: hp_script: One executable <script>.
- [src: tab] `include/dom.h` ranks 2 by PageRank, 17 importers, 29 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- [src: text_shape] `include/js_policy.h` ranks 1 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- [src: text_shape] `include/data_url.h` ranks 2 by PageRank, 8 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- [include: page_view] `include/render_policy.h` ranks 1 by PageRank, 8 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- [include: page_view] `include/box_style.h` ranks 2 by PageRank, 11 importers, 31 symbols: bx_edges: anything longer fails closed instead of truncating into a wrong match. #define BX_TAG_NAME_MAX 32u typedef enum bx_display { BX_DISPLAY_BLOCK = 0,     /* stacks vertically, takes the available width BX_DISPLAY_INLINE...
- Key entities: file:tests/test_css.c, file:src/css.c, file:tests/test_js_dom.c, file:src/tab.c, file:src/freedom.c, file:src/text_shape.c, file:src/page_view.c, file:tests/test_page_view.c
- Children: c0, c2, c3, c4, c5, c7
- Theme rating = highest child community rating.

## include: browser_ui + src: local_store +2 (`t1`, theme, rating 3.6)

Theme of 4 communities and 80 files: include: browser_ui (45 files, rating 3.6); src: local_store (16 files, rating 1.7); include: secure_fetch (13 files, rating 1.5); include: prefetch (6 files, rating 0.4).

- [include: browser_ui] `include/prefs.h` ranks 1 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- [include: browser_ui] `include/image_decode.h` ranks 2 by PageRank, 5 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- [src: local_store] `include/local_store.h` ranks 1 by PageRank, 8 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [src: local_store] `include/http_cache.h` ranks 2 by PageRank, 3 importers, 19 symbols: hc_parse_http_date: } hc_class; typedef struct hc_meta { char   final_url[HC_URL_MAX]; char   content_type[HC_TYPE_MAX]; char   etag[HC_VAL_MAX]; char   last_modified[HC_VAL_MAX]; char   cache_control[HC_VAL_MAX]; char...
- [include: secure_fetch] `include/anti_fp.h` ranks 1 by PageRank, 8 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- [include: secure_fetch] `include/secure_fetch.h` ranks 2 by PageRank, 7 importers, 46 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- [include: prefetch] `include/import_map.h` ranks 1 by PageRank, 4 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- [include: prefetch] `include/prefetch.h` ranks 2 by PageRank, 4 importers, 28 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- Key entities: file:gui/browser_ui.c, file:tests/test_freedom.c, file:src/local_store.c, file:src/http_cache.c, file:src/secure_fetch.c, file:tests/test_secure_fetch.c, file:include/prefetch.h, file:src/prefetch.c
- Children: c1, c6, c8, c9
- Theme rating = highest child community rating.

## unassigned files (`t2`, theme, rating 0.9)

Theme of 1 communities and 18 files: unassigned files (18 files, rating 0.9).

- [unassigned files] `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- [unassigned files] `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- Key entities: file:tools/pngdiff.c, file:tools/gen_psl.c
- Children: c10
- Theme rating = highest child community rating.

## src: css (`c0`, community, rating 7.0)

53 files under src (c 35, h 18), mostly utility. Core file include/css.h (PageRank 0.0524, imported by 36 files): css_style: A resolved presentation. Key abstractions: css_status, css_align, css_display, css_justify, css_font_family, css_text_transform. Depends on include: page_view (4), src: tab (3), src: text_shape (2). Used by include: page_view (14), include: browser_ui (7), src: tab (4).

- `include/css.h` ranks 1 by PageRank, 36 importers, 140 symbols: css_style: A resolved presentation.
- `include/css_color.h` ranks 2 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- `include/css_select.h` ranks 3 by PageRank, 14 importers, 37 symbols: css_attr_match: Sub-selector for :not()/:is()/:where(): a simple compound with only tag/.class/#id/[attr] (no combinators, no pseudo-classes inside * sub-selectors).
- Hotspot `src/css.c`: 247 symbols, 38 connections (score 0.32).
- Hotspot `tests/test_css.c`: 354 symbols, 19 connections (score 0.31).
- 1 layer violations, e.g. test_css.c (testing) -> flex_layout.h (presentation).
- Dataflow: 11 INFERRED issues (first: DEAD_STORE in layout_grid).
- Surprising bridge: css_index.c <-> pq_seal.c (8 hops across communities).
- Key entities: file:tests/test_css.c, file:src/css.c, file:include/css.h, file:src/dom.c, file:src/css_box.c, file:include/css_select.h, file:src/css_computed.c, file:src/css_select.c
- Rating 7.0/10 = 7 x PageRank share 1.00 + 3 x risk 0.00. Internal imports: 103.

## src: tab (`c2`, community, rating 4.6)

45 files under src (c 28, h 17), mostly utility. Core file include/html_parse.h (PageRank 0.0229, imported by 18 files): hp_script: One executable <script>. Key abstractions: hp_status, hp_config, hp_script, FREEDOM_HTML_PARSE_H, max_bytes, hp_document. Depends on src: css (4), include: page_view (4), src: text_shape (3). Used by include: page_view (7), include: browser_ui (6), src: text_shape (6).

- `include/html_parse.h` ranks 1 by PageRank, 18 importers, 24 symbols: hp_script: One executable <script>.
- `include/dom.h` ranks 2 by PageRank, 17 importers, 29 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- `include/url.h` ranks 3 by PageRank, 16 importers, 14 symbols: url_parts: Components of a validated absolute https URL, sliced for a JS location object.
- Hotspot `src/tab.c`: 145 symbols, 66 connections (score 0.38).
- Hotspot `tests/test_js_dom.c`: 228 symbols, 26 connections (score 0.26).
- Dependency cycle: js_dom.h -> js_location.h -> js_dom.h.
- Dataflow: 2 INFERRED issues (first: UNCHECKED_ALLOC in jd_click_state_new).
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:tests/test_tab.c, file:src/js_dom.c, file:include/tab.h, file:src/js_sandbox.c, file:tests/test_url.c, file:tests/test_js_sandbox.c
- Rating 4.6/10 = 7 x PageRank share 0.66 + 3 x risk 0.00. Internal imports: 103.

## include: browser_ui (`c1`, community, rating 3.6)

45 files under tests (c 30, h 15), mostly utility. Core file include/prefs.h (PageRank 0.0110, imported by 6 files): prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on). Key abstractions: prefs_status, prefs_entry, prefs_state, FREEDOM_PREFS_H, PREFS_VERSION, PREFS_MAX_URL. Depends on src: text_shape (11), src: css (7), src: tab (6). Used by src: tab (1), src: local_store (1), gui (1).

- `include/prefs.h` ranks 1 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `include/image_decode.h` ranks 2 by PageRank, 5 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- `include/zoom.h` ranks 3 by PageRank, 5 importers, 10 symbols: zm_clamp: stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser.
- Hotspot `gui/browser_ui.c`: 633 symbols, 137 connections (score 1.00).
- Hotspot `tests/test_freedom.c`: 111 symbols, 12 connections (score 0.12).
- 2 layer violations, e.g. browser_ui.c (presentation) -> data_url.h (data_access).
- Dataflow: 35 INFERRED issues (first: UNCHECKED_ALLOC in gui_subresource_fetch).
- Surprising bridge: block_flow.c <-> test_renderer.c (8 hops across communities).
- Key entities: file:gui/browser_ui.c, file:tests/test_freedom.c, file:tests/test_interp.c, file:tests/test_image_decode.c, file:tests/test_pdf_export.c, file:src/image_decode.c, file:src/prefs.c, file:include/interp.h
- Rating 3.6/10 = 7 x PageRank share 0.52 + 3 x risk 0.00. Internal imports: 49.

## src: text_shape (`c3`, community, rating 3.2)

42 files under src (c 28, h 14), mostly utility. Core file include/js_policy.h (PageRank 0.0070, imported by 5 files): jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over... Key abstractions: jsp_mode, FREEDOM_JS_POLICY_H, membership, allowlist, jsp_trusted, jsp_present_trusted. Depends on src: tab (6), include: page_view (6), src: css (3). Used by include: browser_ui (11), src: tab (3), src: css (2).

- `include/js_policy.h` ranks 1 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- `include/data_url.h` ranks 2 by PageRank, 8 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- `include/webfont.h` ranks 3 by PageRank, 11 importers, 17 symbols: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- Hotspot `src/freedom.c`: 48 symbols, 62 connections (score 0.30).
- Hotspot `src/text_shape.c`: 61 symbols, 13 connections (score 0.10).
- 1 layer violations, e.g. render_policy.c (presentation) -> data_url.h (data_access).
- Dataflow: 1 INFERRED issues (first: UNCHECKED_ALLOC in headless_fetch).
- Key entities: file:src/freedom.c, file:src/text_shape.c, file:include/text_shape.h, file:tests/test_text_shape.c, file:tests/test_data_url.c, file:include/tls_impersonate.h, file:include/webfont.h, file:tests/test_webfont_load.c
- Rating 3.2/10 = 7 x PageRank share 0.46 + 3 x risk 0.00. Internal imports: 50.

## include: page_view (`c4`, community, rating 1.7)

19 files under include (c 12, h 7), mostly presentation. Core file include/render_policy.h (PageRank 0.0085, imported by 8 files): rdp_caps: Render capabilities for a page. Key abstractions: rdp_caps, rdp_img_decision, FREEDOM_RENDER_POLICY_H, RDP_TRACKER_MAX_DIM, images, rdp_is_tracking_pixel. Depends on src: css (14), src: tab (7), src: text_shape (2). Used by src: text_shape (6), src: css (4), include: browser_ui (4).

- `include/render_policy.h` ranks 1 by PageRank, 8 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- `include/box_style.h` ranks 2 by PageRank, 11 importers, 31 symbols: bx_edges: anything longer fails closed instead of truncating into a wrong match. #define BX_TAG_NAME_MAX 32u typedef enum bx_display { BX_DISPLAY_BLOCK = 0,     /* stacks vertically, takes the available width BX_DISPLAY_INLINE...
- `include/flex_layout.h` ranks 3 by PageRank, 11 importers, 43 symbols: fx_item: Upper bound on items per flex line / grid columns.
- Hotspot `src/page_view.c`: 253 symbols, 39 connections (score 0.33).
- Hotspot `tests/test_page_view.c`: 212 symbols, 22 connections (score 0.23).
- 14 layer violations, e.g. render_doc.c (presentation) -> data_url.h (data_access).
- Key entities: file:src/page_view.c, file:tests/test_page_view.c, file:include/page_view.h, file:tests/test_flex_layout.c, file:tests/test_box_tree.c, file:tests/test_box_style.c, file:include/flex_layout.h, file:src/box_style.c
- Rating 1.7/10 = 7 x PageRank share 0.24 + 3 x risk 0.00. Internal imports: 37.

## src: local_store (`c6`, community, rating 1.7)

16 files under src (c 11, h 5), mostly testing. Core file include/local_store.h (PageRank 0.0208, imported by 8 files): ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len... Key abstractions: ls_aead, ls_status, FREEDOM_LOCAL_STORE_H, LS_KEY_LEN, LS_SALT_LEN, LS_NONCE_LEN. Depends on include: browser_ui (1), include: browser (1), include: secure_fetch (1). Used by include: browser_ui (2).

- `include/local_store.h` ranks 1 by PageRank, 8 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- `include/http_cache.h` ranks 2 by PageRank, 3 importers, 19 symbols: hc_parse_http_date: } hc_class; typedef struct hc_meta { char   final_url[HC_URL_MAX]; char   content_type[HC_TYPE_MAX]; char   etag[HC_VAL_MAX]; char   last_modified[HC_VAL_MAX]; char   cache_control[HC_VAL_MAX]; char...
- `include/pq_seal.h` ranks 3 by PageRank, 3 importers, 8 symbols: pqs_buf_free: DER of the PRIVATE key: secret, the caller seals it before it touches disk. *der is owned * (release with pqs_buf_free). pqs_status pqs_export(const pqs_keys *k, uint8_t **der, size_t *len); pqs_status pqs_import(const...
- Hotspot `src/local_store.c`: 323 symbols, 10 connections (score 0.25).
- Hotspot `src/http_cache.c`: 38 symbols, 20 connections (score 0.11).
- 3 layer violations, e.g. http_cache.h (presentation) -> local_store.h (data_access).
- Surprising bridge: css_index.c <-> pq_seal.c (8 hops across communities).
- Key entities: file:src/local_store.c, file:src/http_cache.c, file:include/http_cache.h, file:tests/test_disk_store.c, file:tests/test_http_cache.c, file:tests/test_local_store.c, file:src/cached_fetch.c, file:include/local_store.h
- Rating 1.7/10 = 7 x PageRank share 0.24 + 3 x risk 0.00. Internal imports: 19.

## include: browser (`c5`, community, rating 1.6)

19 files under include (c 12, h 7), mostly utility. Core file include/hostblock.h (PageRank 0.0084, imported by 5 files): hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or... Key abstractions: hb_list, hb_decision, hb_status, FREEDOM_HOSTBLOCK_H, hb_set, hb_new. Depends on src: tab (1). Used by include: browser_ui (4), src: tab (3), src: text_shape (3).

- `include/hostblock.h` ranks 1 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- `include/util.h` ranks 2 by PageRank, 10 importers, 6 symbols: — shared pure helpers (no I/O except where noted).
- `include/os_sandbox.h` ranks 3 by PageRank, 4 importers, 12 symbols: os_violation: function (os_policy_allows) that mirrors the installed BPF program.
- Hotspot `tests/test_os_sandbox.c`: 19 symbols, 23 connections (score 0.11).
- Hotspot `src/os_sandbox.c`: 31 symbols, 17 connections (score 0.09).
- 1 layer violations, e.g. test_renderer.c (testing) -> renderer.h (presentation).
- Dataflow: 1 INFERRED issues (first: UNCHECKED_ALLOC in hb_new).
- Surprising bridge: block_flow.c <-> test_renderer.c (8 hops across communities).
- Key entities: file:src/browser.c, file:src/os_sandbox.c, file:tests/test_os_sandbox.c, file:src/media_decoder.c, file:include/browser.h, file:tests/test_hostblock.c, file:src/hostblock.c, file:tests/test_browser.c
- Rating 1.6/10 = 7 x PageRank share 0.23 + 3 x risk 0.00. Internal imports: 18.

## include: secure_fetch (`c8`, community, rating 1.5)

13 files under tests (c 9, h 4), mostly utility. Core file include/anti_fp.h (PageRank 0.0174, imported by 8 files): fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against... Key abstractions: FREEDOM_ANTI_FP_H, FP_TIMER_RESOLUTION_MS, FP_USER_AGENT, FP_ACCEPT_LANGUAGE, FP_ACCEPT_LANGUAGE_HEADER, FP_ACCEPT_HEADER_NAV. Depends on src: tab (1). Used by include: browser_ui (3), src: tab (3), src: text_shape (2).

- `include/anti_fp.h` ranks 1 by PageRank, 8 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- `include/secure_fetch.h` ranks 2 by PageRank, 7 importers, 46 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- `include/ws_hub.h` ranks 3 by PageRank, 3 importers, 15 symbols: wh_new: #define WH_MAX 8   /* == JD_WS_MAX: sockets per page /* Event kinds delivered to the page; values match tab_ws_event_kind. enum { WH_EV_OPEN = 1, WH_EV_TEXT = 2, WH_EV_BINARY = 3, WH_EV_CLOSE = 4, WH_EV_ERROR = 5 }; /* Abnormal...
- Hotspot `src/secure_fetch.c`: 79 symbols, 17 connections (score 0.12).
- Hotspot `include/secure_fetch.h`: 46 symbols, 12 connections (score 0.08).
- Key entities: file:src/secure_fetch.c, file:tests/test_secure_fetch.c, file:include/secure_fetch.h, file:include/anti_fp.h, file:src/ws_hub.c, file:include/identity.h, file:src/identity.c, file:src/anti_fp.c
- Rating 1.5/10 = 7 x PageRank share 0.21 + 3 x risk 0.00. Internal imports: 14.

## gui (`c7`, community, rating 1.0)

13 files under gui (c 8, h 5), mostly presentation. Core file include/ui.h (PageRank 0.0065, imported by 6 files): ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes. Key abstractions: ui_status, ui_line, ui_layout, rd_doc, jg_table, tab. Depends on src: css (4), include: browser_ui (1), src: tab (1). Used by include: browser_ui (4), include: page_view (2), src: tab (1).

- `include/ui.h` ranks 1 by PageRank, 6 importers, 18 symbols: ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.
- `include/svg_render.h` ranks 2 by PageRank, 5 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- `include/freedom_config.h` ranks 3 by PageRank, 5 importers, 15 symbols.
- Hotspot `gui/ui_render.c`: 29 symbols, 13 connections (score 0.08).
- Hotspot `tests/test_svg_render.c`: 17 symbols, 11 connections (score 0.06).
- 2 layer violations, e.g. test_svg_render.c (testing) -> svg_render.h (presentation).
- Key entities: file:src/svg_render.c, file:gui/ui_render.c, file:include/ui.h, file:tests/test_svg_render.c, file:include/svg_render.h, file:include/freedom_config.h, file:tests/test_ui.c, file:gui/browser_ui_internal.h
- Rating 1.0/10 = 7 x PageRank share 0.14 + 3 x risk 0.00. Internal imports: 12.

## unassigned files (`c10`, community, rating 0.9)

18 files under tools (py 12, sh 4, c 2), mostly utility. Core file app.py (PageRank 0.0018, imported by 0 files): Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode. Key abstractions: read_fuzz_stats, list_unique_crashes, run_freedom_headless, load_baseline, load_current, luma.

- `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- `docker_run.sh` ranks 3 by PageRank, 0 importers, 0 symbols: Thin wrapper.
- Hotspot `tools/guitime.py`: 3 symbols, 8 connections (score 0.04).
- Hotspot `tools/fftime.py`: 1 symbols, 8 connections (score 0.04).
- Taint: 6 paths reach this group via subprocess, urllib.request.
- Key entities: file:tools/pngdiff.c, file:tools/gen_psl.c, file:tools/ffgeom.py, file:tools/fbench.py, file:tools/guitime.py, file:tools/mutate.py, file:tools/snapshot.py, file:tools/fftime.py
- Rating 0.9/10 = 7 x PageRank share 0.13 + 3 x risk 0.00. Internal imports: 0.

## include: prefetch (`c9`, community, rating 0.4)

6 files under include (c 4, h 2), mostly utility. Core file include/import_map.h (PageRank 0.0054, imported by 4 files): im_resolve: Resolves specifier as imported from base (the importing module's URL). Key abstractions: FREEDOM_IMPORT_MAP_H, algorithm, IM_MAX_TEXT, IM_MAX_ENTRIES, IM_MAX_SCOPES, im_map. Depends on src: tab (1). Used by include: browser_ui (1), src: tab (1), src: text_shape (1).

- `include/import_map.h` ranks 1 by PageRank, 4 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- `include/prefetch.h` ranks 2 by PageRank, 4 importers, 28 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- `src/import_map.c` ranks 3 by PageRank, 0 importers, 22 symbols: str: A JSON string into an owned UTF-8 buffer (escapes decoded; a lone surrogate or a * raw control character is malformed).
- Hotspot `tests/test_prefetch.c`: 18 symbols, 11 connections (score 0.06).
- Hotspot `src/prefetch.c`: 30 symbols, 9 connections (score 0.06).
- Key entities: file:include/prefetch.h, file:src/prefetch.c, file:tests/test_prefetch.c, file:src/import_map.c, file:include/import_map.h, file:tests/test_import_map.c, sym:src/import_map.c::str@78, sym:src/import_map.c::add@185
- Rating 0.4/10 = 7 x PageRank share 0.06 + 3 x risk 0.00. Internal imports: 5.
