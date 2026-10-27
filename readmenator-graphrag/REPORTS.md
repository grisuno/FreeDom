# GraphRAG Community Reports

Entities: 8156 | Relationships: 14247 | Communities: 12 | Themes: 4 | Text units: 7691

Query with `readmenator . ask "<question>"` (local: BM25 + Personalized PageRank; global: map-reduce over these reports) or the MCP tool `readmenator.graphrag`.

## Project overview (`root`, root, rating 7.0)

302 files in 12 communities and 4 themes. Highest-impact communities: include: css (7.0), src: tab (5.0), include: browser_ui (3.4). God nodes: gui/browser_ui.c, include/css.h, src/tab.c, src/freedom.c, src/css.c.

- [include: css] rating 7.0: `include/css.h` ranks 1 by PageRank, 36 importers, 140 symbols: css_style: A resolved presentation.
- [src: tab] rating 5.0: `include/html_parse.h` ranks 1 by PageRank, 18 importers, 24 symbols: hp_script: One executable <script>.
- [include: browser_ui] rating 3.4: `include/image_decode.h` ranks 1 by PageRank, 5 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- [src: text_shape] rating 3.2: `include/js_policy.h` ranks 1 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- [include: local_store] rating 2.5: `include/local_store.h` ranks 1 by PageRank, 8 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [include: page_view] rating 1.7: `include/render_policy.h` ranks 1 by PageRank, 8 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- [include: browser] rating 1.6: `include/hostblock.h` ranks 1 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- [include: secure_fetch] rating 1.4: `include/anti_fp.h` ranks 1 by PageRank, 8 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- Key entities: file:tests/test_css.c, file:src/css.c, file:tests/test_js_dom.c, file:src/tab.c, file:gui/browser_ui.c, file:tests/test_freedom.c
- Children: t0, t1, t2, t3
- Root rating = highest community rating.

## include: css + src: text_shape +2 (`t0`, theme, rating 7.0)

Theme of 4 communities and 127 files: include: css (52 files, rating 7.0); src: text_shape (42 files, rating 3.2); include: page_view (19 files, rating 1.7); include: svg_render (14 files, rating 1.1).

- [include: css] `include/css.h` ranks 1 by PageRank, 36 importers, 140 symbols: css_style: A resolved presentation.
- [include: css] `include/css_color.h` ranks 2 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- [src: text_shape] `include/js_policy.h` ranks 1 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- [src: text_shape] `include/data_url.h` ranks 2 by PageRank, 8 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- [include: page_view] `include/render_policy.h` ranks 1 by PageRank, 8 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- [include: page_view] `include/page_view.h` ranks 2 by PageRank, 11 importers, 91 symbols: pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for...
- [include: svg_render] `include/svg_render.h` ranks 1 by PageRank, 5 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- [include: svg_render] `include/ui.h` ranks 2 by PageRank, 6 importers, 19 symbols: ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.
- Key entities: file:tests/test_css.c, file:src/css.c, file:src/freedom.c, file:src/text_shape.c, file:src/page_view.c, file:tests/test_page_view.c, file:src/svg_render.c, file:gui/ui_render.c
- Children: c0, c3, c5, c7
- Theme rating = highest child community rating.

## src: tab + include: prefetch +1 (`t2`, theme, rating 5.0)

Theme of 3 communities and 57 files: src: tab (48 files, rating 5.0); include: prefetch (6 files, rating 0.5); include: sha2 (3 files, rating 0.2).

- [src: tab] `include/html_parse.h` ranks 1 by PageRank, 18 importers, 24 symbols: hp_script: One executable <script>.
- [src: tab] `include/dom.h` ranks 2 by PageRank, 17 importers, 30 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- [include: prefetch] `include/import_map.h` ranks 1 by PageRank, 4 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- [include: prefetch] `include/prefetch.h` ranks 2 by PageRank, 4 importers, 28 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- [include: sha2] `include/sha2.h` ranks 1 by PageRank, 3 importers, 6 symbols: sha_digest_len: sha2 -- one-shot SHA-1 / SHA-256 / SHA-384 / SHA-512 (FIPS 180-4), pure and allocation-free.
- [include: sha2] `src/sha2.c` ranks 2 by PageRank, 0 importers, 15 symbols: pad_tail: Pads the tail of a message into at most two blocks of `bs` bytes with a `lenbytes`-byte * big-endian bit length.
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:include/prefetch.h, file:src/prefetch.c, file:src/sha2.c, file:include/sha2.h
- Children: c1, c9, c10
- Theme rating = highest child community rating.

## include: browser_ui + include: local_store +2 (`t1`, theme, rating 3.4)

Theme of 4 communities and 100 files: include: browser_ui (44 files, rating 3.4); include: local_store (24 files, rating 2.5); include: browser (19 files, rating 1.6); include: secure_fetch (13 files, rating 1.4).

- [include: browser_ui] `include/image_decode.h` ranks 1 by PageRank, 5 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- [include: browser_ui] `include/tab.h` ranks 2 by PageRank, 6 importers, 49 symbols: tab_hist_op: One history operation the page's JS performed (spec/js_dom.md 7e): pushState (replace == 0) or replaceState (replace == 1) to url, an absolute same-origin URL * the parent re-validated against the page URL.
- [include: local_store] `include/local_store.h` ranks 1 by PageRank, 8 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [include: local_store] `include/prefs.h` ranks 2 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- [include: browser] `include/hostblock.h` ranks 1 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- [include: browser] `include/util.h` ranks 2 by PageRank, 10 importers, 6 symbols: — shared pure helpers (no I/O except where noted).
- [include: secure_fetch] `include/anti_fp.h` ranks 1 by PageRank, 8 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- [include: secure_fetch] `include/secure_fetch.h` ranks 2 by PageRank, 8 importers, 48 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- Key entities: file:gui/browser_ui.c, file:tests/test_freedom.c, file:src/local_store.c, file:src/http_cache.c, file:src/browser.c, file:src/os_sandbox.c, file:src/secure_fetch.c, file:tests/test_secure_fetch.c
- Children: c2, c4, c6, c8
- Theme rating = highest child community rating.

## unassigned files (`t3`, theme, rating 0.9)

Theme of 1 communities and 18 files: unassigned files (18 files, rating 0.9).

- [unassigned files] `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- [unassigned files] `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- Key entities: file:tools/pngdiff.c, file:tools/gen_psl.c
- Children: c11
- Theme rating = highest child community rating.

## include: css (`c0`, community, rating 7.0)

52 files under include (c 34, h 18), mostly utility. Core file include/css.h (PageRank 0.0505, imported by 36 files): css_style: A resolved presentation. Key abstractions: css_status, css_align, css_display, css_justify, css_font_family, css_text_transform. Depends on include: page_view (4), src: text_shape (2). Used by include: page_view (14), include: browser_ui (7), src: tab (6).

- `include/css.h` ranks 1 by PageRank, 36 importers, 140 symbols: css_style: A resolved presentation.
- `include/css_color.h` ranks 2 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- `include/css_select.h` ranks 3 by PageRank, 14 importers, 37 symbols: css_attr_match: Sub-selector for :not()/:is()/:where(): a simple compound with only tag/.class/#id/[attr] (no combinators, no pseudo-classes inside * sub-selectors).
- Hotspot `src/css.c`: 247 symbols, 38 connections (score 0.31).
- Hotspot `tests/test_css.c`: 354 symbols, 19 connections (score 0.30).
- 1 layer violations, e.g. test_css.c (testing) -> flex_layout.h (presentation).
- Dataflow: 11 INFERRED issues (first: DEAD_STORE in layout_grid).
- Key entities: file:tests/test_css.c, file:src/css.c, file:include/css.h, file:src/css_box.c, file:include/css_select.h, file:src/css_computed.c, file:src/css_select.c, file:src/css_gradient.c
- Rating 7.0/10 = 7 x PageRank share 1.00 + 3 x risk 0.00. Internal imports: 101.

## src: tab (`c1`, community, rating 5.0)

48 files under src (c 31, h 17), mostly utility. Core file include/html_parse.h (PageRank 0.0232, imported by 18 files): hp_script: One executable <script>. Key abstractions: hp_status, hp_config, hp_script, FREEDOM_HTML_PARSE_H, max_bytes, hp_document. Depends on include: css (6), include: browser (4), include: secure_fetch (4). Used by include: browser_ui (8), include: page_view (7), src: text_shape (6).

- `include/html_parse.h` ranks 1 by PageRank, 18 importers, 24 symbols: hp_script: One executable <script>.
- `include/dom.h` ranks 2 by PageRank, 17 importers, 30 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- `include/url.h` ranks 3 by PageRank, 16 importers, 14 symbols: url_parts: Components of a validated absolute https URL, sliced for a JS location object.
- Hotspot `src/tab.c`: 147 symbols, 68 connections (score 0.38).
- Hotspot `tests/test_js_dom.c`: 268 symbols, 28 connections (score 0.28).
- Dependency cycle: js_dom.h -> js_location.h -> js_dom.h.
- Dataflow: 2 INFERRED issues (first: UNCHECKED_ALLOC in jd_click_state_new).
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:tests/test_tab.c, file:src/dom.c, file:src/js_dom.c, file:src/js_sandbox.c, file:tests/test_js_sandbox.c, file:tests/test_url.c
- Rating 5.0/10 = 7 x PageRank share 0.71 + 3 x risk 0.00. Internal imports: 107.

## include: browser_ui (`c2`, community, rating 3.4)

44 files under include (c 29, h 15), mostly utility. Core file include/image_decode.h (PageRank 0.0062, imported by 5 files): img_pixels: A decoded bitmap that owns its pixel buffer. Key abstractions: img_format, img_status, img_pixels, FREEDOM_IMAGE_DECODE_H, guards, width. Depends on src: text_shape (11), src: tab (8), include: css (7). Used by src: tab (3), src: text_shape (1).

- `include/image_decode.h` ranks 1 by PageRank, 5 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- `include/tab.h` ranks 2 by PageRank, 6 importers, 49 symbols: tab_hist_op: One history operation the page's JS performed (spec/js_dom.md 7e): pushState (replace == 0) or replaceState (replace == 1) to url, an absolute same-origin URL * the parent re-validated against the page URL.
- `include/pdf_export.h` ranks 3 by PageRank, 4 importers, 10 symbols: pe_paginate: Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h without ever splitting a row.
- Hotspot `gui/browser_ui.c`: 642 symbols, 143 connections (score 1.00).
- Hotspot `tests/test_freedom.c`: 111 symbols, 12 connections (score 0.12).
- 2 layer violations, e.g. browser_ui.c (presentation) -> data_url.h (data_access).
- Dataflow: 35 INFERRED issues (first: UNCHECKED_ALLOC in gui_subresource_fetch).
- Surprising bridge: frame_broker.c <-> sha2.c (9 hops across communities).
- Key entities: file:gui/browser_ui.c, file:tests/test_freedom.c, file:include/tab.h, file:tests/test_interp.c, file:tests/test_image_decode.c, file:tests/test_pdf_export.c, file:src/image_decode.c, file:include/interp.h
- Rating 3.4/10 = 7 x PageRank share 0.49 + 3 x risk 0.00. Internal imports: 46.

## src: text_shape (`c3`, community, rating 3.2)

42 files under src (c 28, h 14), mostly utility. Core file include/js_policy.h (PageRank 0.0067, imported by 5 files): jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over... Key abstractions: jsp_mode, FREEDOM_JS_POLICY_H, membership, allowlist, jsp_trusted, jsp_present_trusted. Depends on src: tab (6), include: page_view (6), include: css (3). Used by include: browser_ui (11), src: tab (3), include: css (2).

- `include/js_policy.h` ranks 1 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- `include/data_url.h` ranks 2 by PageRank, 8 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- `include/webfont.h` ranks 3 by PageRank, 11 importers, 17 symbols: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- Hotspot `src/freedom.c`: 48 symbols, 62 connections (score 0.29).
- Hotspot `src/text_shape.c`: 61 symbols, 13 connections (score 0.09).
- 1 layer violations, e.g. render_policy.c (presentation) -> data_url.h (data_access).
- Dataflow: 1 INFERRED issues (first: UNCHECKED_ALLOC in headless_fetch).
- Key entities: file:src/freedom.c, file:src/text_shape.c, file:include/text_shape.h, file:tests/test_text_shape.c, file:include/tls_impersonate.h, file:tests/test_data_url.c, file:include/webfont.h, file:tests/test_link_nav.c
- Rating 3.2/10 = 7 x PageRank share 0.46 + 3 x risk 0.00. Internal imports: 50.

## include: local_store (`c4`, community, rating 2.5)

24 files under include (c 16, h 8), mostly testing. Core file include/local_store.h (PageRank 0.0199, imported by 8 files): ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len... Key abstractions: ls_aead, ls_status, FREEDOM_LOCAL_STORE_H, LS_KEY_LEN, LS_SALT_LEN, LS_NONCE_LEN. Depends on include: browser (1), include: secure_fetch (1). Used by include: browser_ui (4), include: svg_render (1).

- `include/local_store.h` ranks 1 by PageRank, 8 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- `include/prefs.h` ranks 2 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `include/zoom.h` ranks 3 by PageRank, 5 importers, 10 symbols: zm_clamp: stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser.
- Hotspot `src/local_store.c`: 335 symbols, 10 connections (score 0.25).
- Hotspot `src/http_cache.c`: 38 symbols, 20 connections (score 0.11).
- 3 layer violations, e.g. http_cache.h (presentation) -> local_store.h (data_access).
- Surprising bridge: pq_seal.c <-> sha2.c (9 hops across communities).
- Key entities: file:src/local_store.c, file:src/http_cache.c, file:src/prefs.c, file:include/prefs.h, file:include/http_cache.h, file:tests/test_profile.c, file:tests/test_disk_store.c, file:tests/test_http_cache.c
- Rating 2.5/10 = 7 x PageRank share 0.35 + 3 x risk 0.00. Internal imports: 30.

## include: page_view (`c5`, community, rating 1.7)

19 files under include (c 12, h 7), mostly presentation. Core file include/render_policy.h (PageRank 0.0081, imported by 8 files): rdp_caps: Render capabilities for a page. Key abstractions: rdp_caps, rdp_img_decision, FREEDOM_RENDER_POLICY_H, RDP_TRACKER_MAX_DIM, images, rdp_is_tracking_pixel. Depends on include: css (14), src: tab (7), src: text_shape (2). Used by src: text_shape (6), include: browser_ui (5), include: css (4).

- `include/render_policy.h` ranks 1 by PageRank, 8 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- `include/page_view.h` ranks 2 by PageRank, 11 importers, 91 symbols: pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for...
- `include/box_style.h` ranks 3 by PageRank, 11 importers, 31 symbols: bx_edges: anything longer fails closed instead of truncating into a wrong match. #define BX_TAG_NAME_MAX 32u typedef enum bx_display { BX_DISPLAY_BLOCK = 0,     /* stacks vertically, takes the available width BX_DISPLAY_INLINE...
- Hotspot `src/page_view.c`: 255 symbols, 39 connections (score 0.32).
- Hotspot `tests/test_page_view.c`: 213 symbols, 22 connections (score 0.23).
- 14 layer violations, e.g. render_doc.c (presentation) -> data_url.h (data_access).
- Key entities: file:src/page_view.c, file:tests/test_page_view.c, file:include/page_view.h, file:tests/test_flex_layout.c, file:tests/test_box_tree.c, file:tests/test_box_style.c, file:include/flex_layout.h, file:src/box_style.c
- Rating 1.7/10 = 7 x PageRank share 0.24 + 3 x risk 0.00. Internal imports: 37.

## include: browser (`c6`, community, rating 1.6)

19 files under include (c 12, h 7), mostly utility. Core file include/hostblock.h (PageRank 0.0080, imported by 5 files): hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or... Key abstractions: hb_list, hb_decision, hb_status, FREEDOM_HOSTBLOCK_H, hb_set, hb_new. Depends on src: tab (1). Used by src: tab (4), include: browser_ui (4), src: text_shape (3).

- `include/hostblock.h` ranks 1 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- `include/util.h` ranks 2 by PageRank, 10 importers, 6 symbols: — shared pure helpers (no I/O except where noted).
- `include/os_sandbox.h` ranks 3 by PageRank, 4 importers, 12 symbols: os_violation: function (os_policy_allows) that mirrors the installed BPF program.
- Hotspot `tests/test_os_sandbox.c`: 19 symbols, 23 connections (score 0.11).
- Hotspot `src/os_sandbox.c`: 31 symbols, 17 connections (score 0.09).
- 1 layer violations, e.g. test_renderer.c (testing) -> renderer.h (presentation).
- Dataflow: 1 INFERRED issues (first: UNCHECKED_ALLOC in hb_new).
- Surprising bridge: frame_broker.c <-> test_renderer.c (9 hops across communities).
- Key entities: file:src/browser.c, file:src/os_sandbox.c, file:tests/test_os_sandbox.c, file:tests/test_hostblock.c, file:src/media_decoder.c, file:include/browser.h, file:src/hostblock.c, file:tests/test_browser.c
- Rating 1.6/10 = 7 x PageRank share 0.23 + 3 x risk 0.00. Internal imports: 18.

## include: secure_fetch (`c8`, community, rating 1.4)

13 files under tests (c 9, h 4), mostly utility. Core file include/anti_fp.h (PageRank 0.0163, imported by 8 files): fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against... Key abstractions: FREEDOM_ANTI_FP_H, FP_TIMER_RESOLUTION_MS, FP_USER_AGENT, FP_ACCEPT_LANGUAGE, FP_ACCEPT_LANGUAGE_HEADER, FP_ACCEPT_HEADER_NAV. Depends on src: tab (1), src: text_shape (1). Used by src: tab (4), include: browser_ui (3), src: text_shape (2).

- `include/anti_fp.h` ranks 1 by PageRank, 8 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- `include/secure_fetch.h` ranks 2 by PageRank, 8 importers, 48 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- `include/ws_hub.h` ranks 3 by PageRank, 3 importers, 15 symbols: wh_new: #define WH_MAX 8   /* == JD_WS_MAX: sockets per page /* Event kinds delivered to the page; values match tab_ws_event_kind. enum { WH_EV_OPEN = 1, WH_EV_TEXT = 2, WH_EV_BINARY = 3, WH_EV_CLOSE = 4, WH_EV_ERROR = 5 }; /* Abnormal...
- Hotspot `src/secure_fetch.c`: 79 symbols, 19 connections (score 0.13).
- Hotspot `include/secure_fetch.h`: 48 symbols, 13 connections (score 0.08).
- Key entities: file:src/secure_fetch.c, file:tests/test_secure_fetch.c, file:include/secure_fetch.h, file:include/anti_fp.h, file:src/ws_hub.c, file:include/identity.h, file:src/identity.c, file:src/anti_fp.c
- Rating 1.4/10 = 7 x PageRank share 0.21 + 3 x risk 0.00. Internal imports: 14.

## include: svg_render (`c7`, community, rating 1.1)

14 files under include (c 8, h 6), mostly presentation. Core file include/svg_render.h (PageRank 0.0059, imported by 5 files): sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order). Key abstractions: sv_status, sv_shape_kind, sv_verb, sv_seg, sv_shape, sv_image. Depends on include: css (4), src: tab (1), include: local_store (1). Used by include: browser_ui (5), include: page_view (2), src: tab (1).

- `include/svg_render.h` ranks 1 by PageRank, 5 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- `include/ui.h` ranks 2 by PageRank, 6 importers, 19 symbols: ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.
- `include/freedom_config.h` ranks 3 by PageRank, 5 importers, 15 symbols.
- Hotspot `gui/ui_render.c`: 29 symbols, 13 connections (score 0.07).
- Hotspot `tests/test_svg_render.c`: 17 symbols, 11 connections (score 0.06).
- 2 layer violations, e.g. test_svg_render.c (testing) -> svg_render.h (presentation).
- Key entities: file:src/svg_render.c, file:gui/ui_render.c, file:include/ui.h, file:tests/test_svg_render.c, file:include/svg_render.h, file:include/freedom_config.h, file:tests/test_ui.c, file:gui/browser_ui_internal.h
- Rating 1.1/10 = 7 x PageRank share 0.15 + 3 x risk 0.00. Internal imports: 13.

## unassigned files (`c11`, community, rating 0.9)

18 files under tools (py 12, sh 4, c 2), mostly utility. Core file app.py (PageRank 0.0017, imported by 0 files): Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode. Key abstractions: read_fuzz_stats, list_unique_crashes, run_freedom_headless, load_baseline, load_current, luma.

- `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- `docker_run.sh` ranks 3 by PageRank, 0 importers, 0 symbols: Thin wrapper.
- Hotspot `tools/guitime.py`: 3 symbols, 8 connections (score 0.04).
- Hotspot `tools/fftime.py`: 1 symbols, 8 connections (score 0.03).
- Taint: 6 paths reach this group via subprocess, urllib.request.
- Key entities: file:tools/pngdiff.c, file:tools/gen_psl.c, file:tools/ffgeom.py, file:tools/fbench.py, file:tools/guitime.py, file:tools/mutate.py, file:tools/fftime.py, file:tools/snapshot.py
- Rating 0.9/10 = 7 x PageRank share 0.13 + 3 x risk 0.00. Internal imports: 0.

## include: prefetch (`c9`, community, rating 0.5)

6 files under include (c 4, h 2), mostly utility. Core file include/import_map.h (PageRank 0.0052, imported by 4 files): im_resolve: Resolves specifier as imported from base (the importing module's URL). Key abstractions: FREEDOM_IMPORT_MAP_H, algorithm, IM_MAX_TEXT, IM_MAX_ENTRIES, IM_MAX_SCOPES, im_map. Depends on src: tab (1). Used by src: tab (1), include: browser_ui (1), src: text_shape (1).

- `include/import_map.h` ranks 1 by PageRank, 4 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- `include/prefetch.h` ranks 2 by PageRank, 4 importers, 28 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- `src/import_map.c` ranks 3 by PageRank, 0 importers, 22 symbols: str: A JSON string into an owned UTF-8 buffer (escapes decoded; a lone surrogate or a * raw control character is malformed).
- Hotspot `tests/test_prefetch.c`: 18 symbols, 11 connections (score 0.06).
- Hotspot `src/prefetch.c`: 30 symbols, 9 connections (score 0.06).
- Key entities: file:include/prefetch.h, file:src/prefetch.c, file:tests/test_prefetch.c, file:src/import_map.c, file:include/import_map.h, file:tests/test_import_map.c, sym:src/import_map.c::str@78, sym:src/import_map.c::add@185
- Rating 0.5/10 = 7 x PageRank share 0.06 + 3 x risk 0.00. Internal imports: 5.

## include: sha2 (`c10`, community, rating 0.2)

3 files under include (c 2, h 1), mostly utility. Core file include/sha2.h (PageRank 0.0050, imported by 3 files): sha_digest_len: sha2 -- one-shot SHA-1 / SHA-256 / SHA-384 / SHA-512 (FIPS 180-4), pure and allocation-free. Key abstractions: sha_alg, FREEDOM_SHA2_H, SHA_MAX_DIGEST, sha_digest_len, sha_alg_from_name, sha_digest. Used by src: tab (1).

- `include/sha2.h` ranks 1 by PageRank, 3 importers, 6 symbols: sha_digest_len: sha2 -- one-shot SHA-1 / SHA-256 / SHA-384 / SHA-512 (FIPS 180-4), pure and allocation-free.
- `src/sha2.c` ranks 2 by PageRank, 0 importers, 15 symbols: pad_tail: Pads the tail of a message into at most two blocks of `bs` bytes with a `lenbytes`-byte * big-endian bit length.
- `tests/test_sha2.c` ranks 3 by PageRank, 0 importers, 7 symbols: test_sha2 -- CMocka suite for the pure SHA-1/256/384/512 (FIPS 180-4 vectors).
- Hotspot `tests/test_sha2.c`: 7 symbols, 10 connections (score 0.05).
- Hotspot `include/sha2.h`: 6 symbols, 5 connections (score 0.02).
- Surprising bridge: frame_broker.c <-> sha2.c (9 hops across communities).
- Key entities: file:src/sha2.c, file:include/sha2.h, file:tests/test_sha2.c, sym:src/sha2.c::ROL32@9, sym:src/sha2.c::ROR32@8, sym:src/sha2.c::ROR64@10, sym:src/sha2.c::be32@40, sym:src/sha2.c::be64@43
- Rating 0.2/10 = 7 x PageRank share 0.03 + 3 x risk 0.00. Internal imports: 2.
