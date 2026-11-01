# GraphRAG Community Reports

Entities: 8193 | Relationships: 14500 | Communities: 13 | Themes: 4 | Text units: 7723

Query with `readmenator . ask "<question>"` (local: BM25 + Personalized PageRank; global: map-reduce over these reports) or the MCP tool `readmenator.graphrag`.

## Project overview (`root`, root, rating 7.0)

312 files in 13 communities and 4 themes. Highest-impact communities: src: tab (7.0), include: page_view (6.7), src: css (5.5). God nodes: gui/browser_ui.c, include/css.h, src/tab.c, src/freedom.c, src/css.c.

- [src: tab] rating 7.0: `include/html_parse.h` ranks 1 by PageRank, 18 importers, 24 symbols: hp_script: One executable <script>.
- [include: page_view] rating 6.7: `include/css.h` ranks 1 by PageRank, 37 importers, 144 symbols: css_style: A resolved presentation.
- [src: css] rating 5.5: `include/css_color.h` ranks 1 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- [include: browser_ui] rating 4.9: `include/prefs.h` ranks 1 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- [src: text_shape] rating 4.3: `include/js_policy.h` ranks 1 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- [src: http_cache] rating 2.2: `include/local_store.h` ranks 1 by PageRank, 8 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [include: browser] rating 2.1: `include/hostblock.h` ranks 1 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- [include: secure_fetch] rating 1.9: `include/anti_fp.h` ranks 1 by PageRank, 8 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:tests/test_css.c, file:src/page_view.c, file:src/css.c, file:src/css_box.c
- Children: t0, t1, t2, t3
- Root rating = highest community rating.

## src: tab + src: text_shape +3 (`t0`, theme, rating 7.0)

Theme of 5 communities and 109 files: src: tab (51 files, rating 7.0); src: text_shape (42 files, rating 4.3); include: tab (7 files, rating 0.8); include: prefetch (6 files, rating 0.6); include: subreq_batch (3 files, rating 0.3).

- [src: tab] `include/html_parse.h` ranks 1 by PageRank, 18 importers, 24 symbols: hp_script: One executable <script>.
- [src: tab] `include/dom.h` ranks 2 by PageRank, 17 importers, 30 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- [src: text_shape] `include/js_policy.h` ranks 1 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- [src: text_shape] `include/data_url.h` ranks 2 by PageRank, 8 importers, 7 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- [include: tab] `include/frame_broker.h` ranks 1 by PageRank, 3 importers, 17 symbols: fbk_origin_of: Serialized origin ("https://host[:port]", lowercase) or "null" for opaque/non-https/unparseable. * 0 on success, -1 if out does not fit or args are NULL.
- [include: tab] `include/tab.h` ranks 2 by PageRank, 6 importers, 53 symbols: tab_hist_op: One history operation the page's JS performed (spec/js_dom.md 7e): pushState (replace == 0) or replaceState (replace == 1) to url, an absolute same-origin URL * the parent re-validated against the page URL.
- [include: prefetch] `include/import_map.h` ranks 1 by PageRank, 4 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- [include: prefetch] `include/prefetch.h` ranks 2 by PageRank, 4 importers, 28 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:src/text_shape.c, file:src/freedom.c, file:include/tab.h, file:include/frame_broker.h, file:include/prefetch.h, file:src/prefetch.c
- Children: c0, c2, c9, c10, c11
- Theme rating = highest child community rating.

## include: page_view + src: css +1 (`t2`, theme, rating 6.7)

Theme of 3 communities and 91 files: include: page_view (37 files, rating 6.7); src: css (38 files, rating 5.5); include: svg_render (16 files, rating 1.8).

- [include: page_view] `include/css.h` ranks 1 by PageRank, 37 importers, 144 symbols: css_style: A resolved presentation.
- [include: page_view] `include/css_counter.h` ranks 2 by PageRank, 3 importers, 19 symbols: cnt_hash: FNV-1a over `len` bytes of an identifier, ASCII case preserved (identifiers are * case-sensitive).
- [src: css] `include/css_color.h` ranks 1 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- [src: css] `include/css_select.h` ranks 2 by PageRank, 14 importers, 40 symbols: css_attr_match: Sub-selector for :not()/:is()/:where(): a simple compound with only tag/.class/#id/[attr] (no combinators, no pseudo-classes inside * sub-selectors).
- [include: svg_render] `include/image_decode.h` ranks 1 by PageRank, 6 importers, 14 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- [include: svg_render] `include/svg_render.h` ranks 2 by PageRank, 6 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- Key entities: file:tests/test_css.c, file:src/page_view.c, file:src/css.c, file:src/css_box.c, file:tests/test_freedom.c, file:src/svg_render.c
- Children: c4, c3, c6
- Theme rating = highest child community rating.

## include: browser_ui + src: http_cache +2 (`t1`, theme, rating 4.9)

Theme of 4 communities and 94 files: include: browser_ui (46 files, rating 4.9); src: http_cache (16 files, rating 2.2); include: browser (19 files, rating 2.1); include: secure_fetch (13 files, rating 1.9).

- [include: browser_ui] `include/prefs.h` ranks 1 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- [include: browser_ui] `include/zoom.h` ranks 2 by PageRank, 5 importers, 10 symbols: zm_clamp: stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser.
- [src: http_cache] `include/local_store.h` ranks 1 by PageRank, 8 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [src: http_cache] `include/http_cache.h` ranks 2 by PageRank, 3 importers, 19 symbols: hc_parse_http_date: } hc_class; typedef struct hc_meta { char   final_url[HC_URL_MAX]; char   content_type[HC_TYPE_MAX]; char   etag[HC_VAL_MAX]; char   last_modified[HC_VAL_MAX]; char   cache_control[HC_VAL_MAX]; char...
- [include: browser] `include/hostblock.h` ranks 1 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- [include: browser] `include/util.h` ranks 2 by PageRank, 10 importers, 6 symbols: — shared pure helpers (no I/O except where noted).
- [include: secure_fetch] `include/anti_fp.h` ranks 1 by PageRank, 8 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- [include: secure_fetch] `include/secure_fetch.h` ranks 2 by PageRank, 8 importers, 48 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- Key entities: file:gui/browser_ui.c, file:tests/test_interp.c, file:src/http_cache.c, file:src/local_store.c, file:src/browser.c, file:src/os_sandbox.c, file:src/secure_fetch.c, file:tests/test_secure_fetch.c
- Children: c1, c7, c5, c8
- Theme rating = highest child community rating.

## unassigned files (`t3`, theme, rating 1.2)

Theme of 1 communities and 18 files: unassigned files (18 files, rating 1.2).

- [unassigned files] `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- [unassigned files] `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- Key entities: file:tools/pngdiff.c, file:tools/gen_psl.c
- Children: c12
- Theme rating = highest child community rating.

## src: tab (`c0`, community, rating 7.0)

51 files under src (c 33, h 18), mostly utility. Core file include/html_parse.h (PageRank 0.0226, imported by 18 files): hp_script: One executable <script>. Key abstractions: hp_status, hp_config, hp_script, FREEDOM_HTML_PARSE_H, max_bytes, hp_document. Depends on include: page_view (7), include: browser (4), include: secure_fetch (4). Used by include: browser_ui (7), include: page_view (7), src: text_shape (6).

- `include/html_parse.h` ranks 1 by PageRank, 18 importers, 24 symbols: hp_script: One executable <script>.
- `include/dom.h` ranks 2 by PageRank, 17 importers, 30 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- `include/url.h` ranks 3 by PageRank, 16 importers, 14 symbols: url_parts: Components of a validated absolute https URL, sliced for a JS location object.
- Hotspot `src/tab.c`: 189 symbols, 72 connections (score 0.42).
- Hotspot `tests/test_js_dom.c`: 271 symbols, 28 connections (score 0.28).
- Dependency cycle: js_dom.h -> js_location.h -> js_dom.h.
- Dataflow: 2 INFERRED issues (first: UNCHECKED_ALLOC in jd_click_state_new).
- Surprising bridge: frame_broker.c <-> sha2.c (9 hops across communities).
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:tests/test_tab.c, file:src/dom.c, file:src/js_dom.c, file:src/js_sandbox.c, file:tests/test_js_sandbox.c, file:tests/test_url.c
- Rating 7.0/10 = 7 x PageRank share 1.00 + 3 x risk 0.00. Internal imports: 110.

## include: page_view (`c4`, community, rating 6.7)

37 files under include (c 24, h 13), mostly utility. Core file include/css.h (PageRank 0.0501, imported by 37 files): css_style: A resolved presentation. Key abstractions: css_status, css_align, css_display, css_justify, css_font_family, css_text_transform. Depends on src: css (8), src: tab (7), src: text_shape (3). Used by src: css (13), src: text_shape (9), src: tab (7).

- `include/css.h` ranks 1 by PageRank, 37 importers, 144 symbols: css_style: A resolved presentation.
- `include/css_counter.h` ranks 2 by PageRank, 3 importers, 19 symbols: cnt_hash: FNV-1a over `len` bytes of an identifier, ASCII case preserved (identifiers are * case-sensitive).
- `include/page_view.h` ranks 3 by PageRank, 12 importers, 93 symbols: pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for...
- Hotspot `src/page_view.c`: 267 symbols, 40 connections (score 0.33).
- Hotspot `tests/test_css.c`: 366 symbols, 19 connections (score 0.30).
- 15 layer violations, e.g. render_doc.c (presentation) -> data_url.h (data_access).
- Dataflow: 8 INFERRED issues (first: DEAD_STORE in layout_grid).
- Key entities: file:tests/test_css.c, file:src/page_view.c, file:tests/test_page_view.c, file:include/css.h, file:include/page_view.h, file:tests/test_flex_layout.c, file:tests/test_box_tree.c, file:include/flex_layout.h
- Rating 6.7/10 = 7 x PageRank share 0.96 + 3 x risk 0.00. Internal imports: 72.

## src: css (`c3`, community, rating 5.5)

38 files under src (c 25, h 13), mostly utility. Core file include/css_color.h (PageRank 0.0285, imported by 13 files): cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1). Key abstractions: cc_rgb, cc_status, FREEDOM_CSS_COLOR_H, b, cc_pack, CC_COLOR_CURRENT. Depends on include: page_view (13), include: browser_ui (1), src: text_shape (1). Used by include: page_view (8), include: browser_ui (4), include: svg_render (3).

- `include/css_color.h` ranks 1 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- `include/css_select.h` ranks 2 by PageRank, 14 importers, 40 symbols: css_attr_match: Sub-selector for :not()/:is()/:where(): a simple compound with only tag/.class/#id/[attr] (no combinators, no pseudo-classes inside * sub-selectors).
- `include/css_decl.h` ranks 3 by PageRank, 12 importers, 15 symbols: The sheet's two string pools -- background url()s, and the ::before/::after
- Hotspot `src/css.c`: 266 symbols, 40 connections (score 0.33).
- Hotspot `src/css_box.c`: 52 symbols, 17 connections (score 0.10).
- Dataflow: 3 INFERRED issues (first: DEAD_STORE in page_view).
- Key entities: file:src/css.c, file:src/css_box.c, file:include/css_select.h, file:src/css_select.c, file:src/css_gradient.c, file:src/css_color.c, file:src/css_mq.c, file:tests/test_css_color.c
- Rating 5.5/10 = 7 x PageRank share 0.79 + 3 x risk 0.00. Internal imports: 69.

## include: browser_ui (`c1`, community, rating 4.9)

46 files under include (c 30, h 16), mostly utility. Core file include/prefs.h (PageRank 0.0096, imported by 6 files): prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on). Key abstractions: prefs_status, prefs_entry, prefs_state, FREEDOM_PREFS_H, PREFS_VERSION, PREFS_MAX_URL. Depends on src: text_shape (11), src: tab (7), include: page_view (7). Used by src: text_shape (1), src: css (1), include: svg_render (1).

- `include/prefs.h` ranks 1 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `include/zoom.h` ranks 2 by PageRank, 5 importers, 10 symbols: zm_clamp: stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser.
- `include/ui.h` ranks 3 by PageRank, 6 importers, 20 symbols: ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.
- Hotspot `gui/browser_ui.c`: 657 symbols, 143 connections (score 1.00).
- Hotspot `tests/test_profile.c`: 17 symbols, 16 connections (score 0.08).
- 3 layer violations, e.g. browser_ui.c (presentation) -> data_url.h (data_access).
- Dataflow: 34 INFERRED issues (first: UNCHECKED_ALLOC in gui_subresource_fetch).
- Key entities: file:gui/browser_ui.c, file:tests/test_interp.c, file:tests/test_pdf_export.c, file:src/prefs.c, file:include/ui.h, file:include/interp.h, file:include/prefs.h, file:tests/test_download.c
- Rating 4.9/10 = 7 x PageRank share 0.71 + 3 x risk 0.00. Internal imports: 52.

## src: text_shape (`c2`, community, rating 4.3)

42 files under src (c 28, h 14), mostly utility. Core file include/js_policy.h (PageRank 0.0065, imported by 5 files): jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over... Key abstractions: jsp_mode, FREEDOM_JS_POLICY_H, membership, allowlist, jsp_trusted, jsp_present_trusted. Depends on include: page_view (9), src: tab (6), include: browser (3). Used by include: browser_ui (11), src: tab (3), include: page_view (3).

- `include/js_policy.h` ranks 1 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- `include/data_url.h` ranks 2 by PageRank, 8 importers, 7 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- `include/webfont.h` ranks 3 by PageRank, 11 importers, 17 symbols: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- Hotspot `src/freedom.c`: 50 symbols, 64 connections (score 0.30).
- Hotspot `src/text_shape.c`: 68 symbols, 14 connections (score 0.10).
- 1 layer violations, e.g. render_policy.c (presentation) -> data_url.h (data_access).
- Dataflow: 1 INFERRED issues (first: UNCHECKED_ALLOC in headless_fetch).
- Key entities: file:src/text_shape.c, file:src/freedom.c, file:include/text_shape.h, file:tests/test_text_shape.c, file:include/tls_impersonate.h, file:tests/test_data_url.c, file:include/webfont.h, file:tests/test_link_nav.c
- Rating 4.3/10 = 7 x PageRank share 0.62 + 3 x risk 0.00. Internal imports: 50.

## src: http_cache (`c7`, community, rating 2.2)

16 files under src (c 11, h 5), mostly testing. Core file include/local_store.h (PageRank 0.0193, imported by 8 files): ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len... Key abstractions: ls_aead, ls_status, FREEDOM_LOCAL_STORE_H, LS_KEY_LEN, LS_SALT_LEN, LS_NONCE_LEN. Depends on include: browser_ui (1), include: browser (1), include: secure_fetch (1). Used by include: browser_ui (2).

- `include/local_store.h` ranks 1 by PageRank, 8 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- `include/http_cache.h` ranks 2 by PageRank, 3 importers, 19 symbols: hc_parse_http_date: } hc_class; typedef struct hc_meta { char   final_url[HC_URL_MAX]; char   content_type[HC_TYPE_MAX]; char   etag[HC_VAL_MAX]; char   last_modified[HC_VAL_MAX]; char   cache_control[HC_VAL_MAX]; char...
- `include/pq_seal.h` ranks 3 by PageRank, 3 importers, 8 symbols: pqs_buf_free: DER of the PRIVATE key: secret, the caller seals it before it touches disk. *der is owned * (release with pqs_buf_free). pqs_status pqs_export(const pqs_keys *k, uint8_t **der, size_t *len); pqs_status pqs_import(const...
- Hotspot `src/http_cache.c`: 38 symbols, 20 connections (score 0.11).
- Hotspot `tests/test_disk_store.c`: 16 symbols, 16 connections (score 0.08).
- 3 layer violations, e.g. http_cache.h (presentation) -> local_store.h (data_access).
- Surprising bridge: pq_seal.c <-> sha2.c (9 hops across communities).
- Key entities: file:src/http_cache.c, file:src/local_store.c, file:include/http_cache.h, file:tests/test_disk_store.c, file:tests/test_http_cache.c, file:tests/test_local_store.c, file:src/cached_fetch.c, file:include/local_store.h
- Rating 2.2/10 = 7 x PageRank share 0.32 + 3 x risk 0.00. Internal imports: 19.

## include: browser (`c5`, community, rating 2.1)

19 files under include (c 12, h 7), mostly utility. Core file include/hostblock.h (PageRank 0.0078, imported by 5 files): hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or... Key abstractions: hb_list, hb_decision, hb_status, FREEDOM_HOSTBLOCK_H, hb_set, hb_new. Depends on src: tab (1). Used by src: tab (4), include: browser_ui (4), src: text_shape (3).

- `include/hostblock.h` ranks 1 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- `include/util.h` ranks 2 by PageRank, 10 importers, 6 symbols: — shared pure helpers (no I/O except where noted).
- `include/os_sandbox.h` ranks 3 by PageRank, 4 importers, 12 symbols: os_violation: function (os_policy_allows) that mirrors the installed BPF program.
- Hotspot `tests/test_os_sandbox.c`: 19 symbols, 23 connections (score 0.11).
- Hotspot `src/os_sandbox.c`: 31 symbols, 17 connections (score 0.09).
- 1 layer violations, e.g. test_renderer.c (testing) -> renderer.h (presentation).
- Dataflow: 1 INFERRED issues (first: UNCHECKED_ALLOC in hb_new).
- Key entities: file:src/browser.c, file:src/os_sandbox.c, file:tests/test_os_sandbox.c, file:tests/test_hostblock.c, file:src/media_decoder.c, file:include/browser.h, file:src/hostblock.c, file:tests/test_browser.c
- Rating 2.1/10 = 7 x PageRank share 0.31 + 3 x risk 0.00. Internal imports: 18.

## include: secure_fetch (`c8`, community, rating 1.9)

13 files under tests (c 9, h 4), mostly utility. Core file include/anti_fp.h (PageRank 0.0158, imported by 8 files): fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against... Key abstractions: FREEDOM_ANTI_FP_H, FP_TIMER_RESOLUTION_MS, FP_USER_AGENT, FP_ACCEPT_LANGUAGE, FP_ACCEPT_LANGUAGE_HEADER, FP_ACCEPT_HEADER_NAV. Depends on src: tab (1), src: text_shape (1). Used by src: tab (4), include: browser_ui (3), src: text_shape (2).

- `include/anti_fp.h` ranks 1 by PageRank, 8 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- `include/secure_fetch.h` ranks 2 by PageRank, 8 importers, 48 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- `include/ws_hub.h` ranks 3 by PageRank, 3 importers, 15 symbols: wh_new: #define WH_MAX 8   /* == JD_WS_MAX: sockets per page /* Event kinds delivered to the page; values match tab_ws_event_kind. enum { WH_EV_OPEN = 1, WH_EV_TEXT = 2, WH_EV_BINARY = 3, WH_EV_CLOSE = 4, WH_EV_ERROR = 5 }; /* Abnormal...
- Hotspot `src/secure_fetch.c`: 79 symbols, 19 connections (score 0.13).
- Hotspot `include/secure_fetch.h`: 48 symbols, 13 connections (score 0.08).
- Key entities: file:src/secure_fetch.c, file:tests/test_secure_fetch.c, file:include/secure_fetch.h, file:include/anti_fp.h, file:src/ws_hub.c, file:include/identity.h, file:src/identity.c, file:src/anti_fp.c
- Rating 1.9/10 = 7 x PageRank share 0.28 + 3 x risk 0.00. Internal imports: 14.

## include: svg_render (`c6`, community, rating 1.8)

16 files under include (c 10, h 6), mostly utility. Core file include/image_decode.h (PageRank 0.0091, imported by 6 files): img_pixels: A decoded bitmap that owns its pixel buffer. Key abstractions: img_format, img_status, img_pixels, FREEDOM_IMAGE_DECODE_H, guards, width. Depends on src: css (3), include: browser_ui (1), include: page_view (1). Used by include: browser_ui (4), src: tab (3), include: page_view (3).

- `include/image_decode.h` ranks 1 by PageRank, 6 importers, 14 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- `include/svg_render.h` ranks 2 by PageRank, 6 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- `include/freedom_config.h` ranks 3 by PageRank, 5 importers, 15 symbols.
- Hotspot `tests/test_freedom.c`: 111 symbols, 12 connections (score 0.12).
- Hotspot `gui/ui_render.c`: 29 symbols, 13 connections (score 0.07).
- 1 layer violations, e.g. test_svg_render.c (testing) -> svg_render.h (presentation).
- Dataflow: 1 INFERRED issues (first: DEAD_STORE in img_decode_jpeg).
- Key entities: file:tests/test_freedom.c, file:src/svg_render.c, file:tests/test_image_decode.c, file:gui/ui_render.c, file:src/image_decode.c, file:tests/test_svg_render.c, file:include/svg_render.h, file:include/image_decode.h
- Rating 1.8/10 = 7 x PageRank share 0.26 + 3 x risk 0.00. Internal imports: 16.

## unassigned files (`c12`, community, rating 1.2)

18 files under tools (py 12, sh 4, c 2), mostly utility. Core file app.py (PageRank 0.0017, imported by 0 files): Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode. Key abstractions: read_fuzz_stats, list_unique_crashes, run_freedom_headless, load_baseline, load_current, luma.

- `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- `docker_run.sh` ranks 3 by PageRank, 0 importers, 0 symbols: Thin wrapper.
- Hotspot `tools/guitime.py`: 3 symbols, 8 connections (score 0.04).
- Hotspot `tools/fftime.py`: 1 symbols, 8 connections (score 0.03).
- Taint: 6 paths reach this group via subprocess, urllib.request.
- Key entities: file:tools/pngdiff.c, file:tools/gen_psl.c, file:tools/ffgeom.py, file:tools/fbench.py, file:tools/guitime.py, file:tools/mutate.py, file:tools/fftime.py, file:tools/snapshot.py
- Rating 1.2/10 = 7 x PageRank share 0.17 + 3 x risk 0.00. Internal imports: 0.

## include: tab (`c9`, community, rating 0.8)

7 files under include (c 4, h 3), mostly utility. Core file include/frame_broker.h (PageRank 0.0052, imported by 3 files): fbk_origin_of: Serialized origin ("https://host[:port]", lowercase) or "null" for opaque/non-https/unparseable. * 0 on success, -1 if out does not fit or args are NULL. Key abstractions: fbk_rel, fbk_verdict, fbk_frame, fbk_table, FREEDOM_FRAME_BROKER_H, FBK_MAX_FRAMES. Depends on src: tab (2), include: page_view (2). Used by src: tab (2), include: browser_ui (2), src: text_shape (2).

- `include/frame_broker.h` ranks 1 by PageRank, 3 importers, 17 symbols: fbk_origin_of: Serialized origin ("https://host[:port]", lowercase) or "null" for opaque/non-https/unparseable. * 0 on success, -1 if out does not fit or args are NULL.
- `include/tab.h` ranks 2 by PageRank, 6 importers, 53 symbols: tab_hist_op: One history operation the page's JS performed (spec/js_dom.md 7e): pushState (replace == 0) or replaceState (replace == 1) to url, an absolute same-origin URL * the parent re-validated against the page URL.
- `include/frame_host.h` ranks 3 by PageRank, 4 importers, 11 symbols: fh_new: top_url: the trusted top document; fetch/fetch_ctx: the page's policy-gated subresource fetcher (used for the frame document and handed to each frame worker for its own XHR/fetch).
- Hotspot `include/tab.h`: 53 symbols, 15 connections (score 0.10).
- Hotspot `tests/test_frame_host.c`: 9 symbols, 12 connections (score 0.06).
- Surprising bridge: frame_broker.c <-> sha2.c (9 hops across communities).
- Key entities: file:include/tab.h, file:include/frame_broker.h, file:src/frame_host.c, file:include/frame_host.h, file:tests/test_frame_host.c, file:tests/test_frame_broker.c, file:src/frame_broker.c, sym:include/tab.h::replace@54
- Rating 0.8/10 = 7 x PageRank share 0.11 + 3 x risk 0.00. Internal imports: 7.

## include: prefetch (`c10`, community, rating 0.6)

6 files under include (c 4, h 2), mostly utility. Core file include/import_map.h (PageRank 0.0050, imported by 4 files): im_resolve: Resolves specifier as imported from base (the importing module's URL). Key abstractions: FREEDOM_IMPORT_MAP_H, algorithm, IM_MAX_TEXT, IM_MAX_ENTRIES, IM_MAX_SCOPES, im_map. Depends on src: tab (1). Used by src: tab (1), include: browser_ui (1), src: text_shape (1).

- `include/import_map.h` ranks 1 by PageRank, 4 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- `include/prefetch.h` ranks 2 by PageRank, 4 importers, 28 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- `src/import_map.c` ranks 3 by PageRank, 0 importers, 22 symbols: str: A JSON string into an owned UTF-8 buffer (escapes decoded; a lone surrogate or a * raw control character is malformed).
- Hotspot `tests/test_prefetch.c`: 18 symbols, 11 connections (score 0.06).
- Hotspot `src/prefetch.c`: 30 symbols, 9 connections (score 0.06).
- Key entities: file:include/prefetch.h, file:src/prefetch.c, file:tests/test_prefetch.c, file:src/import_map.c, file:include/import_map.h, file:tests/test_import_map.c, sym:src/import_map.c::str@78, sym:src/import_map.c::add@185
- Rating 0.6/10 = 7 x PageRank share 0.09 + 3 x risk 0.00. Internal imports: 5.

## include: subreq_batch (`c11`, community, rating 0.3)

3 files under include (c 2, h 1), mostly utility. Core file include/subreq_batch.h (PageRank 0.0046, imported by 3 files): sqb_res: #ifndef SUBREQ_BATCH_H #define SUBREQ_BATCH_H #include <stddef.h> #define SQB_MAX_JOBS 64 typedef struct sqb_req { const char *method, *url, *body; size_t      body_len; const char *headers;            /* already sanitized by... Key abstractions: sqb_req, sqb_res, SUBREQ_BATCH_H, SQB_MAX_JOBS, ok, sqb. Used by src: tab (1).

- `include/subreq_batch.h` ranks 1 by PageRank, 3 importers, 13 symbols: sqb_res: #ifndef SUBREQ_BATCH_H #define SUBREQ_BATCH_H #include <stddef.h> #define SQB_MAX_JOBS 64 typedef struct sqb_req { const char *method, *url, *body; size_t      body_len; const char *headers;            /* already sanitized by...
- `src/subreq_batch.c` ranks 2 by PageRank, 0 importers, 14 symbols: subreq_batch -- see include/subreq_batch.h and spec/subreq_async.md.
- `tests/test_subreq_batch.c` ranks 3 by PageRank, 0 importers, 9 symbols: subreq_batch (spec/subreq_async.md): parallelism, issue order, refusals, reuse.
- Hotspot `tests/test_subreq_batch.c`: 9 symbols, 11 connections (score 0.05).
- Hotspot `src/subreq_batch.c`: 14 symbols, 7 connections (score 0.04).
- Key entities: file:include/subreq_batch.h, file:src/subreq_batch.c, file:tests/test_subreq_batch.c, sym:src/subreq_batch.c::_GNU_SOURCE@2, sym:src/subreq_batch.c::dup_n@30, sym:src/subreq_batch.c::job_free@44, sym:src/subreq_batch.c::job_main@51, sym:src/subreq_batch.c::res_clear@39
- Rating 0.3/10 = 7 x PageRank share 0.04 + 3 x risk 0.00. Internal imports: 2.
