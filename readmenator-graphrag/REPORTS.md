# GraphRAG Community Reports

Entities: 7339 | Relationships: 12843 | Communities: 11 | Themes: 4 | Text units: 6899

Query with `readmenator . ask "<question>"` (local: BM25 + Personalized PageRank; global: map-reduce over these reports) or the MCP tool `readmenator.graphrag`.

## Project overview (`root`, root, rating 7.0)

288 files in 11 communities and 4 themes. Highest-impact communities: include: css (7.0), src: tab (6.1), include: browser_ui (3.1). God nodes: gui/browser_ui.c, include/css.h, src/tab.c, src/css.c, src/freedom.c.

- [include: css] rating 7.0: `include/css_color.h` ranks 1 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- [src: tab] rating 6.1: `include/html_parse.h` ranks 1 by PageRank, 23 importers, 24 symbols: hp_script: One executable <script>.
- [include: browser_ui] rating 3.1: `include/image_decode.h` ranks 1 by PageRank, 6 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- [src: freedom] rating 3.0: `include/hostblock.h` ranks 1 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- [include: page_view] rating 1.9: `include/render_policy.h` ranks 1 by PageRank, 9 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- [include: text_shape] rating 1.6: `include/data_url.h` ranks 1 by PageRank, 9 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- [include: local_store] rating 1.6: `include/prefs.h` ranks 1 by PageRank, 7 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- [gui] rating 1.2: `include/svg_render.h` ranks 1 by PageRank, 6 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- Key entities: file:tests/test_css.c, file:src/css.c, file:tests/test_js_dom.c, file:src/tab.c, file:gui/browser_ui.c, file:tests/test_freedom.c
- Children: t0, t1, t2, t3
- Root rating = highest community rating.

## include: css + include: page_view +1 (`t1`, theme, rating 7.0)

Theme of 3 communities and 91 files: include: css (50 files, rating 7.0); include: page_view (21 files, rating 1.9); include: text_shape (20 files, rating 1.6).

- [include: css] `include/css_color.h` ranks 1 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- [include: css] `include/css.h` ranks 2 by PageRank, 37 importers, 140 symbols: css_style: A resolved presentation.
- [include: page_view] `include/render_policy.h` ranks 1 by PageRank, 9 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- [include: page_view] `include/page_view.h` ranks 2 by PageRank, 13 importers, 87 symbols: pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for...
- [include: text_shape] `include/data_url.h` ranks 1 by PageRank, 9 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- [include: text_shape] `include/webfont.h` ranks 2 by PageRank, 12 importers, 17 symbols: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- Key entities: file:tests/test_css.c, file:src/css.c, file:src/page_view.c, file:tests/test_page_view.c, file:src/text_shape.c, file:include/text_shape.h
- Children: c1, c4, c5
- Theme rating = highest child community rating.

## src: tab + include: local_store +1 (`t2`, theme, rating 6.1)

Theme of 3 communities and 88 files: src: tab (57 files, rating 6.1); include: local_store (16 files, rating 1.6); gui (15 files, rating 1.2).

- [src: tab] `include/html_parse.h` ranks 1 by PageRank, 23 importers, 24 symbols: hp_script: One executable <script>.
- [src: tab] `include/dom.h` ranks 2 by PageRank, 19 importers, 28 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- [include: local_store] `include/prefs.h` ranks 1 by PageRank, 7 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- [include: local_store] `include/local_store.h` ranks 2 by PageRank, 6 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [gui] `include/svg_render.h` ranks 1 by PageRank, 6 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- [gui] `include/ui.h` ranks 2 by PageRank, 6 importers, 18 symbols: ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:src/local_store.c, file:src/prefs.c, file:src/svg_render.c, file:gui/ui_render.c
- Children: c0, c6, c7
- Theme rating = highest child community rating.

## include: browser_ui + src: freedom +2 (`t0`, theme, rating 3.1)

Theme of 4 communities and 92 files: include: browser_ui (38 files, rating 3.1); src: freedom (36 files, rating 3.0); include: secure_fetch (10 files, rating 1.2); include: prefetch (8 files, rating 0.7).

- [include: browser_ui] `include/image_decode.h` ranks 1 by PageRank, 6 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- [include: browser_ui] `include/pdf_export.h` ranks 2 by PageRank, 5 importers, 10 symbols: pe_paginate: Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h without ever splitting a row.
- [src: freedom] `include/hostblock.h` ranks 1 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- [src: freedom] `include/js_policy.h` ranks 2 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- [include: secure_fetch] `include/anti_fp.h` ranks 1 by PageRank, 6 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- [include: secure_fetch] `include/secure_fetch.h` ranks 2 by PageRank, 6 importers, 42 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- [include: prefetch] `include/import_map.h` ranks 1 by PageRank, 5 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- [include: prefetch] `include/prefetch.h` ranks 2 by PageRank, 5 importers, 28 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- Key entities: file:gui/browser_ui.c, file:tests/test_freedom.c, file:src/freedom.c, file:include/tls_impersonate.h, file:src/secure_fetch.c, file:tests/test_secure_fetch.c, file:include/prefetch.h, file:src/prefetch.c
- Children: c2, c3, c8, c9
- Theme rating = highest child community rating.

## unassigned files (`t3`, theme, rating 0.9)

Theme of 1 communities and 17 files: unassigned files (17 files, rating 0.9).

- [unassigned files] `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- [unassigned files] `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- Key entities: file:tools/pngdiff.c, file:tools/ffgeom.py
- Children: c10
- Theme rating = highest child community rating.

## include: css (`c1`, community, rating 7.0)

50 files under include (c 33, h 17), mostly utility. Core file include/css_color.h (PageRank 0.0508, imported by 13 files): cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1). Key abstractions: cc_rgb, cc_status, FREEDOM_CSS_COLOR_H, b, cc_pack, CC_COLOR_CURRENT. Depends on include: page_view (3), include: text_shape (2). Used by include: page_view (16), include: browser_ui (7), src: tab (5).

- `include/css_color.h` ranks 1 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- `include/css.h` ranks 2 by PageRank, 37 importers, 140 symbols: css_style: A resolved presentation.
- `include/css_select.h` ranks 3 by PageRank, 15 importers, 34 symbols: css_attr_match: Sub-selector for :not()/:is()/:where(): a simple compound with only tag/.class/#id/[attr] (no combinators, no pseudo-classes inside * sub-selectors).
- Hotspot `src/css.c`: 247 symbols, 38 connections (score 0.34).
- Hotspot `tests/test_css.c`: 354 symbols, 19 connections (score 0.32).
- 1 layer violations, e.g. test_css.c (testing) -> flex_layout.h (presentation).
- Dataflow: 3 INFERRED issues (first: DEAD_STORE in page_view).
- Key entities: file:tests/test_css.c, file:src/css.c, file:include/css.h, file:src/css_box.c, file:include/css_select.h, file:src/css_gradient.c, file:tests/test_css_color.c, file:src/css_mq.c
- Rating 7.0/10 = 7 x PageRank share 1.00 + 3 x risk 0.00. Internal imports: 100.

## src: tab (`c0`, community, rating 6.1)

57 files under src (c 38, h 19), mostly utility. Core file include/html_parse.h (PageRank 0.0290, imported by 23 files): hp_script: One executable <script>. Key abstractions: hp_status, hp_config, hp_script, FREEDOM_HTML_PARSE_H, max_bytes, hp_document. Depends on include: css (5), include: page_view (4), include: text_shape (2). Used by include: page_view (10), src: freedom (8), include: browser_ui (6).

- `include/html_parse.h` ranks 1 by PageRank, 23 importers, 24 symbols: hp_script: One executable <script>.
- `include/dom.h` ranks 2 by PageRank, 19 importers, 28 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- `include/url.h` ranks 3 by PageRank, 18 importers, 14 symbols: url_parts: Components of a validated absolute https URL, sliced for a JS location object.
- Hotspot `src/tab.c`: 124 symbols, 60 connections (score 0.37).
- Hotspot `tests/test_js_dom.c`: 189 symbols, 24 connections (score 0.24).
- Dependency cycle: js_dom.h -> js_location.h -> js_dom.h.
- 1 layer violations, e.g. test_renderer.c (testing) -> renderer.h (presentation).
- Surprising bridge: fuzz_download.c <-> test_renderer.c (8 hops across communities).
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:tests/test_tab.c, file:src/dom.c, file:src/js_dom.c, file:tests/test_url.c, file:include/tab.h, file:src/js_sandbox.c
- Rating 6.1/10 = 7 x PageRank share 0.87 + 3 x risk 0.00. Internal imports: 126.

## include: browser_ui (`c2`, community, rating 3.1)

38 files under tests (c 27, h 11), mostly utility. Core file include/image_decode.h (PageRank 0.0080, imported by 6 files): img_pixels: A decoded bitmap that owns its pixel buffer. Key abstractions: img_format, img_status, img_pixels, FREEDOM_IMAGE_DECODE_H, guards, width. Depends on src: freedom (9), include: css (7), src: tab (6). Used by src: tab (1).

- `include/image_decode.h` ranks 1 by PageRank, 6 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- `include/pdf_export.h` ranks 2 by PageRank, 5 importers, 10 symbols: pe_paginate: Deterministic pagination: lays the rows (document-space tops + heights, in order) onto pages of usable height page_h without ever splitting a row.
- `include/download.h` ranks 3 by PageRank, 4 importers, 9 symbols: dl_should_download: 1 if the response should be saved (attachment, or a non-renderable media type), 0 if it should be rendered.
- Hotspot `gui/browser_ui.c`: 606 symbols, 127 connections (score 1.00).
- Hotspot `tests/test_freedom.c`: 103 symbols, 12 connections (score 0.12).
- 2 layer violations, e.g. browser_ui.c (presentation) -> data_url.h (data_access).
- Dataflow: 38 INFERRED issues (first: UNCHECKED_ALLOC in gui_subresource_fetch).
- Surprising bridge: fuzz_download.c <-> test_renderer.c (8 hops across communities).
- Key entities: file:gui/browser_ui.c, file:tests/test_freedom.c, file:src/browser.c, file:tests/test_interp.c, file:tests/test_image_decode.c, file:tests/test_pdf_export.c, file:src/image_decode.c, file:include/interp.h
- Rating 3.1/10 = 7 x PageRank share 0.44 + 3 x risk 0.00. Internal imports: 38.

## src: freedom (`c3`, community, rating 3.0)

36 files under src (c 25, h 11), mostly utility. Core file include/hostblock.h (PageRank 0.0084, imported by 5 files): hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or... Key abstractions: hb_list, hb_decision, hb_status, FREEDOM_HOSTBLOCK_H, hb_set, hb_new. Depends on src: tab (8), include: page_view (5), include: text_shape (4). Used by include: browser_ui (9), src: tab (1).

- `include/hostblock.h` ranks 1 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- `include/js_policy.h` ranks 2 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- `include/tls_impersonate.h` ranks 3 by PageRank, 5 importers, 23 symbols: ti_req: Request: parent -> helper.
- Hotspot `src/freedom.c`: 47 symbols, 58 connections (score 0.30).
- Hotspot `src/media_decoder.c`: 15 symbols, 16 connections (score 0.09).
- Dataflow: 2 INFERRED issues (first: UNCHECKED_ALLOC in headless_fetch).
- Key entities: file:src/freedom.c, file:include/tls_impersonate.h, file:src/media_decoder.c, file:tests/test_link_nav.c, file:tests/test_hostblock.c, file:include/perf_trace.h, file:src/hostblock.c, file:src/tls_impersonate.c
- Rating 3.0/10 = 7 x PageRank share 0.43 + 3 x risk 0.00. Internal imports: 37.

## include: page_view (`c4`, community, rating 1.9)

21 files under include (c 14, h 7), mostly presentation. Core file include/render_policy.h (PageRank 0.0091, imported by 9 files): rdp_caps: Render capabilities for a page. Key abstractions: rdp_caps, rdp_img_decision, FREEDOM_RENDER_POLICY_H, RDP_TRACKER_MAX_DIM, images, rdp_is_tracking_pixel. Depends on include: css (16), src: tab (10), include: text_shape (2). Used by src: freedom (5), src: tab (4), include: browser_ui (4).

- `include/render_policy.h` ranks 1 by PageRank, 9 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- `include/page_view.h` ranks 2 by PageRank, 13 importers, 87 symbols: pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for...
- `include/flex_layout.h` ranks 3 by PageRank, 12 importers, 43 symbols: fx_item: Upper bound on items per flex line / grid columns.
- Hotspot `src/page_view.c`: 244 symbols, 38 connections (score 0.34).
- Hotspot `tests/test_page_view.c`: 209 symbols, 22 connections (score 0.24).
- 14 layer violations, e.g. render_doc.c (presentation) -> data_url.h (data_access).
- Dataflow: 7 INFERRED issues (first: DEAD_STORE in layout_grid).
- Key entities: file:src/page_view.c, file:tests/test_page_view.c, file:include/page_view.h, file:tests/test_flex_layout.c, file:tests/test_box_tree.c, file:tests/test_box_style.c, file:include/flex_layout.h, file:src/box_style.c
- Rating 1.9/10 = 7 x PageRank share 0.28 + 3 x risk 0.00. Internal imports: 43.

## include: text_shape (`c5`, community, rating 1.6)

20 files under include (c 14, h 6), mostly utility. Core file include/data_url.h (PageRank 0.0084, imported by 9 files): du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN... Key abstractions: du_status, FREEDOM_DATA_URL_H, allocation, DU_MAX_ENCODED_LEN, du_is_data_url, closed. Depends on include: css (3), src: tab (1), include: page_view (1). Used by include: browser_ui (5), src: freedom (4), src: tab (2).

- `include/data_url.h` ranks 1 by PageRank, 9 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- `include/webfont.h` ranks 2 by PageRank, 12 importers, 17 symbols: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- `include/text_shape.h` ranks 3 by PageRank, 7 importers, 24 symbols: tsh_font: Font selector: a css_font_family bucket (CSS_FF_*) plus weight/slant flags.
- Hotspot `src/text_shape.c`: 61 symbols, 13 connections (score 0.10).
- Hotspot `tests/test_webfont_load.c`: 16 symbols, 16 connections (score 0.09).
- 1 layer violations, e.g. render_policy.c (presentation) -> data_url.h (data_access).
- Key entities: file:src/text_shape.c, file:include/text_shape.h, file:tests/test_text_shape.c, file:tests/test_data_url.c, file:include/webfont.h, file:tests/test_webfont_load.c, file:src/webfont.c, file:src/webfont_load.c
- Rating 1.6/10 = 7 x PageRank share 0.23 + 3 x risk 0.00. Internal imports: 24.

## include: local_store (`c6`, community, rating 1.6)

16 files under include (c 11, h 5), mostly utility. Core file include/prefs.h (PageRank 0.0126, imported by 7 files): prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on). Key abstractions: prefs_status, prefs_entry, prefs_state, FREEDOM_PREFS_H, PREFS_VERSION, PREFS_MAX_URL. Depends on src: tab (1). Used by include: browser_ui (3), gui (1).

- `include/prefs.h` ranks 1 by PageRank, 7 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `include/local_store.h` ranks 2 by PageRank, 6 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- `include/zoom.h` ranks 3 by PageRank, 5 importers, 10 symbols: zm_clamp: stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser.
- Hotspot `src/local_store.c`: 299 symbols, 10 connections (score 0.24).
- Hotspot `tests/test_profile.c`: 17 symbols, 16 connections (score 0.09).
- Key entities: file:src/local_store.c, file:src/prefs.c, file:include/prefs.h, file:tests/test_profile.c, file:tests/test_disk_store.c, file:tests/test_local_store.c, file:tests/test_prefs.c, file:src/profile.c
- Rating 1.6/10 = 7 x PageRank share 0.23 + 3 x risk 0.00. Internal imports: 20.

## gui (`c7`, community, rating 1.2)

15 files under gui (c 10, h 5), mostly presentation. Core file include/svg_render.h (PageRank 0.0078, imported by 6 files): sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order). Key abstractions: sv_status, sv_shape_kind, sv_verb, sv_seg, sv_shape, sv_image. Depends on include: css (4), src: tab (2), include: page_view (1). Used by include: browser_ui (4), include: page_view (2), src: tab (1).

- `include/svg_render.h` ranks 1 by PageRank, 6 importers, 19 symbols: sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in Cairo order).
- `include/ui.h` ranks 2 by PageRank, 6 importers, 18 symbols: ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.
- `include/freedom_config.h` ranks 3 by PageRank, 6 importers, 13 symbols.
- Hotspot `gui/ui_render.c`: 29 symbols, 13 connections (score 0.08).
- Hotspot `tests/test_svg_render.c`: 17 symbols, 11 connections (score 0.06).
- 2 layer violations, e.g. test_svg_render.c (testing) -> svg_render.h (presentation).
- Key entities: file:src/svg_render.c, file:gui/ui_render.c, file:include/ui.h, file:tests/test_svg_render.c, file:include/svg_render.h, file:include/freedom_config.h, file:tests/test_ui.c, file:gui/browser_ui_internal.h
- Rating 1.2/10 = 7 x PageRank share 0.17 + 3 x risk 0.00. Internal imports: 14.

## include: secure_fetch (`c8`, community, rating 1.2)

10 files under tests (c 7, h 3), mostly utility. Core file include/anti_fp.h (PageRank 0.0142, imported by 6 files): fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against... Key abstractions: FREEDOM_ANTI_FP_H, FP_TIMER_RESOLUTION_MS, FP_USER_AGENT, FP_ACCEPT_LANGUAGE, FP_ACCEPT_LANGUAGE_HEADER, FP_ACCEPT_HEADER_NAV. Depends on src: tab (1). Used by src: tab (2), include: browser_ui (2), src: freedom (1).

- `include/anti_fp.h` ranks 1 by PageRank, 6 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- `include/secure_fetch.h` ranks 2 by PageRank, 6 importers, 42 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- `include/ws_hub.h` ranks 3 by PageRank, 3 importers, 15 symbols: wh_new: #define WH_MAX 8   /* == JD_WS_MAX: sockets per page /* Event kinds delivered to the page; values match tab_ws_event_kind. enum { WH_EV_OPEN = 1, WH_EV_TEXT = 2, WH_EV_BINARY = 3, WH_EV_CLOSE = 4, WH_EV_ERROR = 5 }; /* Abnormal...
- Hotspot `src/secure_fetch.c`: 74 symbols, 16 connections (score 0.12).
- Hotspot `include/secure_fetch.h`: 42 symbols, 11 connections (score 0.08).
- Key entities: file:src/secure_fetch.c, file:tests/test_secure_fetch.c, file:include/secure_fetch.h, file:include/anti_fp.h, file:src/ws_hub.c, file:src/anti_fp.c, file:include/ws_hub.h, file:tests/test_ws_hub.c
- Rating 1.2/10 = 7 x PageRank share 0.17 + 3 x risk 0.00. Internal imports: 10.

## unassigned files (`c10`, community, rating 0.9)

17 files under tools (py 10, sh 5, c 2), mostly utility. Core file app.py (PageRank 0.0018, imported by 0 files): Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode. Key abstractions: read_fuzz_stats, list_unique_crashes, run_freedom_headless, load_baseline, load_current, luma.

- `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- `docker_run.sh` ranks 3 by PageRank, 0 importers, 0 symbols: Thin wrapper.
- Hotspot `tools/pngdiff.c`: 14 symbols, 6 connections (score 0.04).
- Hotspot `tools/ffgeom.py`: 12 symbols, 6 connections (score 0.04).
- Taint: 4 paths reach this group via subprocess, urllib.request.
- Key entities: file:tools/pngdiff.c, file:tools/ffgeom.py, file:tools/gen_psl.c, file:tools/mutate.py, file:tools/snapshot.py, file:tools/fbench.py, file:tools/ffshot.py, file:tools/ffq.py
- Rating 0.9/10 = 7 x PageRank share 0.12 + 3 x risk 0.00. Internal imports: 0.

## include: prefetch (`c9`, community, rating 0.7)

8 files under include (c 6, h 2), mostly utility. Core file include/import_map.h (PageRank 0.0070, imported by 5 files): im_resolve: Resolves specifier as imported from base (the importing module's URL). Key abstractions: FREEDOM_IMPORT_MAP_H, algorithm, IM_MAX_TEXT, IM_MAX_ENTRIES, IM_MAX_SCOPES, im_map. Depends on src: tab (1). Used by src: tab (1), include: browser_ui (1), src: freedom (1).

- `include/import_map.h` ranks 1 by PageRank, 5 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- `include/prefetch.h` ranks 2 by PageRank, 5 importers, 28 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- `fuzz/fuzz_import_map.c` ranks 3 by PageRank, 0 importers, 2 symbols.
- Hotspot `tests/test_prefetch.c`: 18 symbols, 11 connections (score 0.06).
- Hotspot `src/prefetch.c`: 30 symbols, 9 connections (score 0.06).
- Key entities: file:include/prefetch.h, file:src/prefetch.c, file:tests/test_prefetch.c, file:src/import_map.c, file:include/import_map.h, file:tests/test_import_map.c, file:fuzz/fuzz_import_map.c, file:fuzz/fuzz_prefetch.c
- Rating 0.7/10 = 7 x PageRank share 0.09 + 3 x risk 0.00. Internal imports: 7.
