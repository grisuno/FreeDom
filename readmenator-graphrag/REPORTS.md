# GraphRAG Community Reports

Entities: 7392 | Relationships: 12812 | Communities: 9 | Themes: 3 | Text units: 6969

Query with `readmenator . ask "<question>"` (local: BM25 + Personalized PageRank; global: map-reduce over these reports) or the MCP tool `readmenator.graphrag`.

## Project overview (`root`, root, rating 7.0)

267 files in 9 communities and 3 themes. Highest-impact communities: src: css (7.0), src: tab (4.8), include: browser_ui (4.4). God nodes: gui/browser_ui.c, include/css.h, src/tab.c, src/css.c, src/freedom.c.

- [src: css] rating 7.0: `include/css.h` ranks 1 by PageRank, 36 importers, 140 symbols: css_style: A resolved presentation.
- [src: tab] rating 4.8: `include/html_parse.h` ranks 1 by PageRank, 18 importers, 24 symbols: hp_script: One executable <script>.
- [include: browser_ui] rating 4.4: `include/prefs.h` ranks 1 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- [src: text_shape] rating 3.3: `include/js_policy.h` ranks 1 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- [include: local_store] rating 2.3: `include/local_store.h` ranks 1 by PageRank, 6 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [include: page_view] rating 1.7: `include/render_policy.h` ranks 1 by PageRank, 8 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- [include: secure_fetch] rating 1.2: `include/anti_fp.h` ranks 1 by PageRank, 6 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- [unassigned files] rating 0.8: `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- Key entities: file:tests/test_css.c, file:src/css.c, file:tests/test_js_dom.c, file:src/tab.c, file:gui/browser_ui.c, file:tests/test_freedom.c
- Children: t0, t1, t2
- Root rating = highest community rating.

## src: css + src: text_shape +2 (`t0`, theme, rating 7.0)

Theme of 4 communities and 137 files: src: css (50 files, rating 7.0); src: text_shape (42 files, rating 3.3); include: local_store (26 files, rating 2.3); include: page_view (19 files, rating 1.7).

- [src: css] `include/css.h` ranks 1 by PageRank, 36 importers, 140 symbols: css_style: A resolved presentation.
- [src: css] `include/css_color.h` ranks 2 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- [src: text_shape] `include/js_policy.h` ranks 1 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- [src: text_shape] `include/data_url.h` ranks 2 by PageRank, 8 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- [include: local_store] `include/local_store.h` ranks 1 by PageRank, 6 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- [include: local_store] `include/hostblock.h` ranks 2 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- [include: page_view] `include/render_policy.h` ranks 1 by PageRank, 8 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- [include: page_view] `include/box_style.h` ranks 2 by PageRank, 11 importers, 31 symbols: bx_edges: anything longer fails closed instead of truncating into a wrong match. #define BX_TAG_NAME_MAX 32u typedef enum bx_display { BX_DISPLAY_BLOCK = 0,     /* stacks vertically, takes the available width BX_DISPLAY_INLINE...
- Key entities: file:tests/test_css.c, file:src/css.c, file:src/text_shape.c, file:src/freedom.c, file:src/local_store.c, file:src/browser.c, file:src/page_view.c, file:tests/test_page_view.c
- Children: c1, c3, c4, c5
- Theme rating = highest child community rating.

## src: tab + include: browser_ui +2 (`t1`, theme, rating 4.8)

Theme of 4 communities and 114 files: src: tab (45 files, rating 4.8); include: browser_ui (53 files, rating 4.4); include: secure_fetch (10 files, rating 1.2); include: prefetch (6 files, rating 0.5).

- [src: tab] `include/html_parse.h` ranks 1 by PageRank, 18 importers, 24 symbols: hp_script: One executable <script>.
- [src: tab] `include/dom.h` ranks 2 by PageRank, 17 importers, 29 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- [include: browser_ui] `include/prefs.h` ranks 1 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- [include: browser_ui] `include/image_decode.h` ranks 2 by PageRank, 5 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- [include: secure_fetch] `include/anti_fp.h` ranks 1 by PageRank, 6 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- [include: secure_fetch] `include/secure_fetch.h` ranks 2 by PageRank, 6 importers, 42 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- [include: prefetch] `include/import_map.h` ranks 1 by PageRank, 4 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- [include: prefetch] `include/prefetch.h` ranks 2 by PageRank, 4 importers, 28 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:gui/browser_ui.c, file:tests/test_freedom.c, file:src/secure_fetch.c, file:tests/test_secure_fetch.c, file:include/prefetch.h, file:src/prefetch.c
- Children: c2, c0, c6, c7
- Theme rating = highest child community rating.

## unassigned files (`t2`, theme, rating 0.8)

Theme of 1 communities and 16 files: unassigned files (16 files, rating 0.8).

- [unassigned files] `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- [unassigned files] `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- Key entities: file:tools/pngdiff.c, file:tools/ffgeom.py
- Children: c8
- Theme rating = highest child community rating.

## src: css (`c1`, community, rating 7.0)

50 files under src (c 33, h 17), mostly utility. Core file include/css.h (PageRank 0.0567, imported by 36 files): css_style: A resolved presentation. Key abstractions: css_status, css_align, css_display, css_justify, css_font_family, css_text_transform. Depends on include: page_view (4), src: tab (3), src: text_shape (2). Used by include: page_view (14), include: browser_ui (11), src: tab (4).

- `include/css.h` ranks 1 by PageRank, 36 importers, 140 symbols: css_style: A resolved presentation.
- `include/css_color.h` ranks 2 by PageRank, 13 importers, 7 symbols: cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color" sentinel of -1).
- `include/css_select.h` ranks 3 by PageRank, 14 importers, 34 symbols: css_attr_match: Sub-selector for :not()/:is()/:where(): a simple compound with only tag/.class/#id/[attr] (no combinators, no pseudo-classes inside * sub-selectors).
- Hotspot `src/css.c`: 247 symbols, 38 connections (score 0.34).
- Hotspot `tests/test_css.c`: 354 symbols, 19 connections (score 0.32).
- 1 layer violations, e.g. test_css.c (testing) -> flex_layout.h (presentation).
- Dataflow: 10 INFERRED issues (first: DEAD_STORE in layout_grid).
- Key entities: file:tests/test_css.c, file:src/css.c, file:include/css.h, file:src/dom.c, file:src/css_box.c, file:include/css_select.h, file:src/css_gradient.c, file:tests/test_css_color.c
- Rating 7.0/10 = 7 x PageRank share 1.00 + 3 x risk 0.00. Internal imports: 100.

## src: tab (`c2`, community, rating 4.8)

45 files under src (c 28, h 17), mostly utility. Core file include/html_parse.h (PageRank 0.0249, imported by 18 files): hp_script: One executable <script>. Key abstractions: hp_status, hp_config, hp_script, FREEDOM_HTML_PARSE_H, max_bytes, hp_document. Depends on src: css (4), include: page_view (4), src: text_shape (3). Used by include: page_view (7), include: browser_ui (6), src: text_shape (6).

- `include/html_parse.h` ranks 1 by PageRank, 18 importers, 24 symbols: hp_script: One executable <script>.
- `include/dom.h` ranks 2 by PageRank, 17 importers, 29 symbols: dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node" and "first" cannot be expressed by an element-only reference).
- `include/url.h` ranks 3 by PageRank, 16 importers, 14 symbols: url_parts: Components of a validated absolute https URL, sliced for a JS location object.
- Hotspot `src/tab.c`: 126 symbols, 62 connections (score 0.38).
- Hotspot `tests/test_js_dom.c`: 200 symbols, 24 connections (score 0.25).
- Dependency cycle: js_dom.h -> js_location.h -> js_dom.h.
- Dataflow: 2 INFERRED issues (first: UNCHECKED_ALLOC in jd_click_state_new).
- Key entities: file:tests/test_js_dom.c, file:src/tab.c, file:tests/test_tab.c, file:src/js_dom.c, file:tests/test_url.c, file:include/tab.h, file:src/js_sandbox.c, file:src/css_computed.c
- Rating 4.8/10 = 7 x PageRank share 0.69 + 3 x risk 0.00. Internal imports: 102.

## include: browser_ui (`c0`, community, rating 4.4)

53 files under include (c 35, h 18), mostly utility. Core file include/prefs.h (PageRank 0.0119, imported by 6 files): prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on). Key abstractions: prefs_status, prefs_entry, prefs_state, FREEDOM_PREFS_H, PREFS_VERSION, PREFS_MAX_URL. Depends on src: css (11), src: text_shape (11), src: tab (6). Used by src: tab (2), include: page_view (2), src: text_shape (1).

- `include/prefs.h` ranks 1 by PageRank, 6 importers, 18 symbols: prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on).
- `include/image_decode.h` ranks 2 by PageRank, 5 importers, 13 symbols: img_pixels: A decoded bitmap that owns its pixel buffer.
- `include/ui.h` ranks 3 by PageRank, 6 importers, 18 symbols: ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.
- Hotspot `gui/browser_ui.c`: 606 symbols, 127 connections (score 1.00).
- Hotspot `tests/test_freedom.c`: 106 symbols, 12 connections (score 0.13).
- 4 layer violations, e.g. browser_ui.c (presentation) -> data_url.h (data_access).
- Dataflow: 36 INFERRED issues (first: UNCHECKED_ALLOC in gui_subresource_fetch).
- Surprising bridge: block_flow.c <-> test_renderer.c (8 hops across communities).
- Key entities: file:gui/browser_ui.c, file:tests/test_freedom.c, file:tests/test_interp.c, file:tests/test_image_decode.c, file:src/svg_render.c, file:gui/ui_render.c, file:tests/test_pdf_export.c, file:src/image_decode.c
- Rating 4.4/10 = 7 x PageRank share 0.63 + 3 x risk 0.00. Internal imports: 61.

## src: text_shape (`c3`, community, rating 3.3)

42 files under src (c 28, h 14), mostly utility. Core file include/js_policy.h (PageRank 0.0076, imported by 5 files): jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over... Key abstractions: jsp_mode, FREEDOM_JS_POLICY_H, membership, allowlist, jsp_trusted, jsp_present_trusted. Depends on src: tab (6), include: page_view (6), src: css (3). Used by include: browser_ui (11), src: tab (3), src: css (2).

- `include/js_policy.h` ranks 1 by PageRank, 5 importers, 7 symbols: jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over...
- `include/data_url.h` ranks 2 by PageRank, 8 importers, 6 symbols: du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation before decoding a payload whose size a * remote, hostile document controls. #define DU_MAX_ENCODED_LEN...
- `include/webfont.h` ranks 3 by PageRank, 11 importers, 17 symbols: wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
- Hotspot `src/freedom.c`: 47 symbols, 58 connections (score 0.30).
- Hotspot `src/text_shape.c`: 61 symbols, 13 connections (score 0.10).
- 1 layer violations, e.g. render_policy.c (presentation) -> data_url.h (data_access).
- Dataflow: 1 INFERRED issues (first: UNCHECKED_ALLOC in headless_fetch).
- Key entities: file:src/text_shape.c, file:src/freedom.c, file:include/text_shape.h, file:tests/test_text_shape.c, file:tests/test_data_url.c, file:include/tls_impersonate.h, file:include/webfont.h, file:tests/test_link_nav.c
- Rating 3.3/10 = 7 x PageRank share 0.47 + 3 x risk 0.00. Internal imports: 50.

## include: local_store (`c4`, community, rating 2.3)

26 files under include (c 17, h 9), mostly utility. Core file include/local_store.h (PageRank 0.0117, imported by 6 files): ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len... Key abstractions: ls_aead, ls_status, FREEDOM_LOCAL_STORE_H, LS_KEY_LEN, LS_SALT_LEN, LS_NONCE_LEN. Depends on include: browser_ui (1), src: tab (1). Used by include: browser_ui (5), src: tab (3), src: text_shape (3).

- `include/local_store.h` ranks 1 by PageRank, 6 importers, 11 symbols: ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in the container so ls_open_passphrase can re-derive. ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len...
- `include/hostblock.h` ranks 2 by PageRank, 5 importers, 10 symbols: hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) } hb_decision; typedef enum hb_status { HB_OK = 0, HB_ERR_NULL_ARG,  /* set or...
- `include/util.h` ranks 3 by PageRank, 10 importers, 6 symbols: — shared pure helpers (no I/O except where noted).
- Hotspot `src/local_store.c`: 303 symbols, 10 connections (score 0.25).
- Hotspot `tests/test_os_sandbox.c`: 19 symbols, 23 connections (score 0.12).
- 1 layer violations, e.g. test_renderer.c (testing) -> renderer.h (presentation).
- Dataflow: 1 INFERRED issues (first: UNCHECKED_ALLOC in hb_new).
- Surprising bridge: block_flow.c <-> test_renderer.c (8 hops across communities).
- Key entities: file:src/local_store.c, file:src/browser.c, file:src/os_sandbox.c, file:tests/test_os_sandbox.c, file:src/media_decoder.c, file:include/browser.h, file:tests/test_hostblock.c, file:src/hostblock.c
- Rating 2.3/10 = 7 x PageRank share 0.33 + 3 x risk 0.00. Internal imports: 27.

## include: page_view (`c5`, community, rating 1.7)

19 files under include (c 12, h 7), mostly presentation. Core file include/render_policy.h (PageRank 0.0092, imported by 8 files): rdp_caps: Render capabilities for a page. Key abstractions: rdp_caps, rdp_img_decision, FREEDOM_RENDER_POLICY_H, RDP_TRACKER_MAX_DIM, images, rdp_is_tracking_pixel. Depends on src: css (14), src: tab (7), include: browser_ui (2). Used by src: text_shape (6), include: browser_ui (4), src: css (4).

- `include/render_policy.h` ranks 1 by PageRank, 8 importers, 9 symbols: rdp_caps: Render capabilities for a page.
- `include/box_style.h` ranks 2 by PageRank, 11 importers, 31 symbols: bx_edges: anything longer fails closed instead of truncating into a wrong match. #define BX_TAG_NAME_MAX 32u typedef enum bx_display { BX_DISPLAY_BLOCK = 0,     /* stacks vertically, takes the available width BX_DISPLAY_INLINE...
- `include/flex_layout.h` ranks 3 by PageRank, 11 importers, 43 symbols: fx_item: Upper bound on items per flex line / grid columns.
- Hotspot `src/page_view.c`: 248 symbols, 38 connections (score 0.34).
- Hotspot `tests/test_page_view.c`: 209 symbols, 22 connections (score 0.24).
- 14 layer violations, e.g. render_doc.c (presentation) -> data_url.h (data_access).
- Key entities: file:src/page_view.c, file:tests/test_page_view.c, file:include/page_view.h, file:tests/test_flex_layout.c, file:tests/test_box_tree.c, file:tests/test_box_style.c, file:include/flex_layout.h, file:src/box_style.c
- Rating 1.7/10 = 7 x PageRank share 0.25 + 3 x risk 0.00. Internal imports: 37.

## include: secure_fetch (`c6`, community, rating 1.2)

10 files under tests (c 7, h 3), mostly utility. Core file include/anti_fp.h (PageRank 0.0152, imported by 6 files): fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against... Key abstractions: FREEDOM_ANTI_FP_H, FP_TIMER_RESOLUTION_MS, FP_USER_AGENT, FP_ACCEPT_LANGUAGE, FP_ACCEPT_LANGUAGE_HEADER, FP_ACCEPT_HEADER_NAV. Depends on src: tab (1). Used by include: browser_ui (2), src: tab (2), src: text_shape (1).

- `include/anti_fp.h` ranks 1 by PageRank, 6 importers, 35 symbols: fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- `include/secure_fetch.h` ranks 2 by PageRank, 6 importers, 42 symbols: sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.
- `include/ws_hub.h` ranks 3 by PageRank, 3 importers, 15 symbols: wh_new: #define WH_MAX 8   /* == JD_WS_MAX: sockets per page /* Event kinds delivered to the page; values match tab_ws_event_kind. enum { WH_EV_OPEN = 1, WH_EV_TEXT = 2, WH_EV_BINARY = 3, WH_EV_CLOSE = 4, WH_EV_ERROR = 5 }; /* Abnormal...
- Hotspot `src/secure_fetch.c`: 74 symbols, 16 connections (score 0.12).
- Hotspot `include/secure_fetch.h`: 42 symbols, 11 connections (score 0.08).
- Key entities: file:src/secure_fetch.c, file:tests/test_secure_fetch.c, file:include/secure_fetch.h, file:include/anti_fp.h, file:src/ws_hub.c, file:src/anti_fp.c, file:include/ws_hub.h, file:tests/test_ws_hub.c
- Rating 1.2/10 = 7 x PageRank share 0.16 + 3 x risk 0.00. Internal imports: 10.

## unassigned files (`c8`, community, rating 0.8)

16 files under tools (py 10, sh 4, c 2), mostly utility. Core file app.py (PageRank 0.0019, imported by 0 files): Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode. Key abstractions: read_fuzz_stats, list_unique_crashes, run_freedom_headless, load_baseline, load_current, luma.

- `app.py` ranks 1 by PageRank, 0 importers, 3 symbols: Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL v3  Description: MCP server to monitor AFL++ fuzzing sessions and execute FreeDom in headless mode.
- `docker-entrypoint.sh` ranks 2 by PageRank, 0 importers, 0 symbols.
- `docker_run.sh` ranks 3 by PageRank, 0 importers, 0 symbols: Thin wrapper.
- Hotspot `tools/pngdiff.c`: 14 symbols, 6 connections (score 0.04).
- Hotspot `tools/ffgeom.py`: 12 symbols, 6 connections (score 0.04).
- Taint: 4 paths reach this group via subprocess, urllib.request.
- Key entities: file:tools/pngdiff.c, file:tools/ffgeom.py, file:tools/gen_psl.c, file:tools/mutate.py, file:tools/snapshot.py, file:tools/fbench.py, file:tools/ffshot.py, file:tools/ffq.py
- Rating 0.8/10 = 7 x PageRank share 0.12 + 3 x risk 0.00. Internal imports: 0.

## include: prefetch (`c7`, community, rating 0.5)

6 files under include (c 4, h 2), mostly utility. Core file include/import_map.h (PageRank 0.0059, imported by 4 files): im_resolve: Resolves specifier as imported from base (the importing module's URL). Key abstractions: FREEDOM_IMPORT_MAP_H, algorithm, IM_MAX_TEXT, IM_MAX_ENTRIES, IM_MAX_SCOPES, im_map. Depends on src: tab (1). Used by include: browser_ui (1), src: tab (1), src: text_shape (1).

- `include/import_map.h` ranks 1 by PageRank, 4 importers, 10 symbols: im_resolve: Resolves specifier as imported from base (the importing module's URL).
- `include/prefetch.h` ranks 2 by PageRank, 4 importers, 28 symbols: pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).
- `src/import_map.c` ranks 3 by PageRank, 0 importers, 22 symbols: str: A JSON string into an owned UTF-8 buffer (escapes decoded; a lone surrogate or a * raw control character is malformed).
- Hotspot `tests/test_prefetch.c`: 18 symbols, 11 connections (score 0.06).
- Hotspot `src/prefetch.c`: 30 symbols, 9 connections (score 0.06).
- Key entities: file:include/prefetch.h, file:src/prefetch.c, file:tests/test_prefetch.c, file:src/import_map.c, file:include/import_map.h, file:tests/test_import_map.c, sym:src/import_map.c::str@78, sym:src/import_map.c::add@185
- Rating 0.5/10 = 7 x PageRank share 0.07 + 3 x risk 0.00. Internal imports: 5.
