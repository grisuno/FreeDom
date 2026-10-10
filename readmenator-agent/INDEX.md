# Index

| File | Purpose | Subsystem | Symbols | Used by |
|------|---------|-----------|---------|---------|
| `app.py` | Author: Gris Iscomeback Email: grisun0[at]proton[dot]me Creation Date: 06/18/2026 License: GPL... | root | 3 | 0 |
| `docker-entrypoint.sh` | - | root | 0 | 0 |
| `docker_run.sh` | Thin wrapper. | root | 0 | 0 |
| `fuzz.sh` | Thin wrapper. | root | 0 | 0 |
| `fuzz/fuzz_css.c` | fuzz_root_match: Root matcher for the attribute-scoped custom-property path: a fixed <html... | fuzz | 2 | 0 |
| `fuzz/fuzz_data_url.c` | - | fuzz | 1 | 0 |
| `fuzz/fuzz_dom.c` | - | fuzz | 2 | 0 |
| `fuzz/fuzz_dom_debug.c` | - | fuzz | 1 | 0 |
| `fuzz/fuzz_download.c` | - | fuzz | 1 | 0 |
| `fuzz/fuzz_freebug.c` | - | fuzz | 1 | 0 |
| `fuzz/fuzz_html_parse.c` | - | fuzz | 0 | 0 |
| `fuzz/fuzz_image_decode.c` | poke_and_free: Touch every claimed pixel corner so the sanitizer flags an out-of-bounds extent... | fuzz | 2 | 0 |
| `fuzz/fuzz_import_map.c` | - | fuzz | 2 | 0 |
| `fuzz/fuzz_js_dom.c` | - | fuzz | 3 | 0 |
| `fuzz/fuzz_js_geom.c` | fz_parent_of: trigger UB, and a decoded table must re-encode to a table that decodes again. | fuzz | 3 | 0 |
| `fuzz/fuzz_js_sandbox.c` | fz_mod: Module host for the fuzzer: every "./" specifier resolves, and "./self.js" loads the... | fuzz | 5 | 0 |
| `fuzz/fuzz_page_view.c` | - | fuzz | 0 | 0 |
| `fuzz/fuzz_pdf_export.c` | - | fuzz | 1 | 0 |
| `fuzz/fuzz_prefetch.c` | libFuzzer harness for the prefetch lookahead scanner (Hito 29). | fuzz | 1 | 0 |
| `fuzz/fuzz_prefs.c` | - | fuzz | 1 | 0 |
| `fuzz/fuzz_svg_render.c` | - | fuzz | 1 | 0 |
| `fuzz/fuzz_text_shape.c` | - | fuzz | 2 | 0 |
| `fuzz/fuzz_tls_impersonate.c` | - | fuzz | 0 | 0 |
| `fuzz/fuzz_url.c` | - | fuzz | 2 | 0 |
| `fuzz/fuzz_web_storage.c` | - | fuzz | 0 | 0 |
| `fuzz/fuzz_webfont.c` | libFuzzer harness for the webfont lookahead scanner (spec/webfont.md). | fuzz | 1 | 0 |
| `gui/browser_ui.c` | ui_input_state: Live editable state for one form text control, aliasing a block of the current... | gui | 531 | 0 |
| `gui/browser_ui_internal.h` | ui_theme_mode: ui_rgb button_text; ui_rgb menu_bg; ui_rgb menu_border; ui_rgb menu_text; ui_rgb... | gui | 10 | 2 |
| `gui/bui_theme.c` | ui_theme_default: bui_theme — presentation palettes for the Wayland/Cairo GUI. | gui | 6 | 0 |
| `gui/freedom_view.c` | - | gui | 2 | 0 |
| `gui/svg_paint.c` | svg_paint — Cairo back end for the shapes svg_render extracted. | gui | 5 | 0 |
| `gui/ui_render.c` | sanitize_utf8_inplace: Rewrites s in place to well-formed UTF-8, replacing any byte that is not... | gui | 29 | 0 |
| `include/anti_fp.h` | fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define... | include | 35 | 6 |
| `include/block_flow.h` | block_flow (bf_) -- vertical margin collapsing for block-level boxes. | include | 4 | 3 |
| `include/box_style.h` | bx_edges: anything longer fails closed instead of truncating into a wrong match. #define... | include | 25 | 11 |
| `include/box_tree.h` | bt_positioned: Stage 2: one positioned box in the final paint order. | include | 32 | 5 |
| `include/browser.h` | browser_free: Zero-initialise or reset a state. | include | 19 | 3 |
| `include/compositor.h` | cx_style: A box's resolved style, in the SAME value-spaces as css.h: position uses css_position... | include | 9 | 4 |
| `include/css.h` | css_style: A resolved presentation. | include | 131 | 33 |
| `include/css_atrule.h` | car_ops: The questions @supports asks the caller's own engine. prop is lowercased and * both... | include | 10 | 3 |
| `include/css_box.h` | - | include | 25 | 4 |
| `include/css_chain.h` | cch_element_matches: Nonzero iff the parsed selector *sel matches element `el`, built against... | include | 8 | 3 |
| `include/css_color.h` | cc_pack: Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for... | include | 7 | 13 |
| `include/css_decl.h` | Bound for the ::before/::after content string pool (and the grid-template | include | 12 | 10 |
| `include/css_gradient.h` | - | include | 3 | 3 |
| `include/css_length.h` | cl_ctx: The state a <length> is measured against. | include | 20 | 9 |
| `include/css_mq.h` | cmq_matches: 1 iff the media query list s[0,len) matches env; malformed/unknown parts fail * closed. | include | 6 | 3 |
| `include/css_select.h` | css_attr_match: Sub-selector for :not()/:is()/:where(): a simple compound with only... | include | 34 | 14 |
| `include/css_text.h` | - | include | 17 | 3 |
| `include/css_values.h` | Single owner of CSS value interpretation for colors and backgrounds. | include | 6 | 6 |
| `include/css_vars.h` | cvr_table: Zero-initialise ({0}) before first use. | include | 19 | 5 |
| `include/data_url.h` | du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/... | include | 6 | 9 |
| `include/disk_store.h` | ds_free: Reads and decrypts path. | include | 3 | 3 |
| `include/dom.h` | dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all four: *... | include | 28 | 18 |
| `include/dom_debug.h` | dd_format: Formats doc into out[0..cap) as a NUL-terminated, line-oriented dump (see the spec... | include | 4 | 4 |
| `include/download.h` | dl_should_download: 1 if the response should be saved (attachment, or a non-renderable media... | include | 9 | 4 |
| `include/flex_layout.h` | fx_item: Upper bound on items per flex line / grid columns. | include | 35 | 9 |
| `include/form.h` | fm_field: One named control. value == NULL is treated as the empty value; name == NULL is *... | include | 12 | 3 |
| `include/frame_clock.h` | active: frame_clock (fc_) — pure animation frame scheduler. | include | 7 | 3 |
| `include/freebug.h` | fb_entry: One captured console message. text and file are owned by the buffer (NUL-terminated).... | include | 18 | 12 |
| `include/freedom_config.h` | - | include | 13 | 6 |
| `include/hls.h` | hls_segment: or variant info. | include | 8 | 4 |
| `include/hostblock.h` | hb_new: } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted... | include | 10 | 4 |
| `include/hostedit.h` | he_text_has_host: Returns 1 if text (the body of a hosts-format file) already lists host as a... | include | 5 | 3 |
| `include/html_parse.h` | hp_script: One executable <script>. | include | 24 | 23 |
| `include/image_decode.h` | img_pixels: A decoded bitmap that owns its pixel buffer. | include | 13 | 6 |
| `include/import_map.h` | im_resolve: Resolves specifier as imported from base (the importing module's URL). | include | 10 | 4 |
| `include/interp.h` | ip_ease: Compute eased t for normalized t ∈ [0,1]. | include | 22 | 3 |
| `include/js_dom.h` | jd_iframe_track: Tracks iframes already processed by jd_process_iframes, to avoid re-fetching... | include | 17 | 12 |
| `include/js_env.h` | - | include | 3 | 3 |
| `include/js_geom.h` | jg_init: typedef struct jg_rect { dom_node_id node; int32_t     x, y, w, h;       /* document... | include | 19 | 8 |
| `include/js_location.h` | jd_take_history: Drains the history operations page JS performed since the last call: an owned... | include | 6 | 1 |
| `include/js_policy.h` | jsp_trusted: Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its... | include | 7 | 5 |
| `include/js_sandbox.h` | js_limits: Per-evaluation resource limits. | include | 24 | 16 |
| `include/js_trusted.h` | jt_take_opens: Installs window.open for a TRUSTED host (allow.conf AND js.conf) only (plan B4c).... | include | 16 | 4 |
| `include/link_nav.h` | ln_block_reason: Why a reference was blocked, for a precise user-facing notice and for *... | include | 11 | 6 |
| `include/local_store.h` | ls_free: Passphrase variant: generates a random salt, derives the key with Argon2id, * and... | include | 11 | 6 |
| `include/media_decoder.h` | md_cmd: Communicates with the parent over two pipes: out_fd: decoder → parent (frames, stream... | include | 12 | 4 |
| `include/net_realm.h` | nr_realm_allows_http: 1 iff plain http:// is acceptable for this realm. | include | 10 | 4 |
| `include/os_sandbox.h` | os_violation: function (os_policy_allows) that mirrors the installed BPF program. | include | 12 | 4 |
| `include/page_view.h` | pv_run: One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt... | include | 72 | 13 |
| `include/pdf_export.h` | pe_paginate: Deterministic pagination: lays the rows (document-space tops + heights, in order)... | include | 10 | 5 |
| `include/perf_trace.h` | pt_init: #define PT_MAX_SAMPLES 256 typedef struct pt_stage_stats { uint64_t... | include | 17 | 3 |
| `include/prefetch.h` | pf_ref: One scanned reference. url is the RAW attribute value (the policy-gated fetcher *... | include | 21 | 5 |
| `include/prefs.h` | prefs_init: Safe defaults (a virgin session: everything private/off, zoom 100%, *... | include | 18 | 6 |
| `include/profile.h` | profile_close: Loads and decrypts prefs.bin over an out ALREADY initialised (prefs_init). | include | 9 | 3 |
| `include/psl_data.h` | - | include | 7 | 1 |
| `include/render_doc.h` | rd_block: One paint-ready block in document order. text is owned, NUL-terminated and valid... | include | 26 | 7 |
| `include/render_policy.h` | rdp_caps: Render capabilities for a page. | include | 9 | 9 |
| `include/renderer.h` | rd_result_free: Renders untrusted HTML out-of-process and returns an inert title + text. html ==... | include | 7 | 2 |
| `include/request_policy.h` | rp_host_of: Lowercased host of an absolute URL into out. | include | 5 | 6 |
| `include/secure_fetch.h` | sf_chain_info: Minimal view of the verified certificate chain, used by sf_check_chain_policy. *... | include | 38 | 6 |
| `include/svg_paint.h` | svp_draw: Paints `img` into the rect [x, y, w, h] of `cr`, scaled uniformly and centred... | include | 2 | 2 |
| `include/svg_render.h` | sv_shape: One paintable shape, already resolved: presentation attributes inherited from the <g>... | include | 19 | 6 |
| `include/tab.h` | tab_hist_op: One history operation the page's JS performed (spec/js_dom.md 7e): pushState... | include | 41 | 4 |
| `include/text_shape.h` | tsh_font: Font selector: a css_font_family bucket (CSS_FF_*) plus weight/slant flags. | include | 13 | 7 |
| `include/textfield.h` | tf_init: typedef struct tf_field { char   buf[TF_CAP]; /* content, always NUL-terminated at... | include | 15 | 3 |
| `include/tls_impersonate.h` | ti_req: Request: parent -> helper. | include | 23 | 5 |
| `include/ui.h` | ui_line: A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no... | include | 17 | 6 |
| `include/url.h` | url_parts: Components of a validated absolute https URL, sliced for a JS location object. | include | 14 | 17 |
| `include/util.h` | — shared pure helpers (no I/O except where noted). | include | 6 | 10 |
| `include/web_storage.h` | wst_new: web_storage — in-MEMORY localStorage for trusted hosts (owner decision: nothing... | include | 13 | 10 |
| `include/webcaps.h` | wc_caps: Full capability table for one page. | include | 5 | 4 |
| `include/webfont.h` | wf_name_hash: FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names. | include | 17 | 12 |
| `include/webfont_load.h` | wf_sheet: One collected stylesheet: text plus the URL it was fetched from (the * resolution base... | include | 7 | 4 |
| `include/ws_hub.h` | wh_new: #define WH_MAX 8   /* == JD_WS_MAX: sockets per page /* Event kinds delivered to the... | include | 15 | 3 |
| `include/zoom.h` | zm_clamp: stops (50..300) so Ctrl + / Ctrl - land on predictable values, like a mainstream browser. | include | 10 | 5 |
| `install.sh` | Exit immediately if a command exits with a non-zero status, | root | 0 | 0 |
| `run_freedom.sh` | Thin wrapper. | root | 0 | 0 |
| `src/anti_fp.c` | - | src | 23 | 0 |
| `src/block_flow.c` | block_flow (bf_) -- vertical margin collapsing. | src | 4 | 0 |
| `src/box_style.c` | tag_row: One row of the user-agent sheet. | src | 41 | 0 |
| `src/box_tree.c` | layout_block: Block container: stack non-none children vertically, collapsing each child's top *... | src | 22 | 0 |
| `src/browser.c` | clear_status: #include <stdlib.h> #include <string.h> static void free_page(browser_state *bs) {... | src | 41 | 0 |
| `src/compositor.c` | eff_z: Not a stacking context: a positioned box with z:auto still paints in the *... | src | 5 | 0 |
| `src/css.c` | css_match: if (!(inherited_px > 0.0)) inherited_px = CL_INITIAL_FONT_SIZE; if (o->font_scale ==... | src | 231 | 0 |
| `src/css_atrule.c` | keyword_at: Scratch size for one declaration or selector handed to the caller. | src | 11 | 0 |
| `src/css_box.c` | calc_val: `pct` is the percentage component, carried through the arithmetic exactly like `em`... | src | 49 | 0 |
| `src/css_chain.c` | cch_node: One element's selector inputs (tag/id/classes) plus its css_element view, with *... | src | 17 | 0 |
| `src/css_color.c` | normalize: Trims surrounding ASCII spaces and lowercases into out (CC_TOKEN_MAX bytes). *... | src | 27 | 0 |
| `src/css_gradient.c` | find_gradient_call: Locates a gradient function call `fn` (e.g. "linear-gradient(") in v... | src | 14 | 0 |
| `src/css_length.c` | cl_unit_eq: ASCII case-insensitive compare of a possibly-unterminated unit slice against a... | src | 18 | 0 |
| `src/css_mq.c` | read_word: static int is_space(char c) { return c == ' ' \|\| c == '\t' \|\| c == '\n' \|\| c == '\r'... | src | 34 | 0 |
| `src/css_select.c` | csel_hex_val: CSS Syntax 4.3.7 escape consumption (moved from css.c; shared by quoted content... | src | 29 | 0 |
| `src/css_text.c` | --- text-presentation extensions (Hito 23b-6) --- | src | 17 | 0 |
| `src/css_values.c` | - | src | 6 | 0 |
| `src/css_vars.c` | find_slot: Index into t->slot where name lives, or the empty slot where it would go. * Requires... | src | 16 | 0 |
| `src/data_url.c` | b64_val: 0-63 for a base64 alphabet character, -1 otherwise. | src | 10 | 0 |
| `src/disk_store.c` | fsync_dir: Best-effort fsync of the directory holding path, for crash durability of the * rename. | src | 6 | 0 |
| `src/dom.c` | to_lower_buf: #include <stdint.h> #include <stdlib.h> #include <string.h> #include... | src | 72 | 0 |
| `src/dom_debug.c` | dd_cursor: Bounded write cursor: `pos` bytes are committed to `out` (always leaving room for the... | src | 24 | 0 |
| `src/download.c` | lc: download — pure helpers for "save this resource to disk". | src | 12 | 0 |
| `src/flex_layout.c` | nn: No I/O, no global state, no dynamic allocation: fixed-size stack scratch buffers bounded by... | src | 24 | 0 |
| `src/form.c` | put_char: No I/O, no global state. | src | 8 | 0 |
| `src/frame_clock.c` | - | src | 4 | 0 |
| `src/freebug.c` | - | src | 9 | 0 |
| `src/freedom.c` | is_overlay_http: fprintf(fp, "  --dump-video-url: headless, print the first detected video... | src | 46 | 0 |
| `src/hls.c` | last_char: Finds the last occurrence of character `c` in `s` (length `n`). * Returns NULL if not... | src | 10 | 0 |
| `src/hostblock.c` | table_probe: Finds the slot for key (length klen) in t, which must have a free slot. | src | 18 | 0 |
| `src/hostedit.c` | valid_host: #include "hostedit.h" #include <string.h> static char he_lower(char c) { return (c... | src | 13 | 0 |
| `src/html_parse.c` | node_next: }; /* --- helpers --- static char *dup_bytes(const lxb_char_t *src, size_t len) { if... | src | 29 | 0 |
| `src/image_decode.c` | jpeg_err_ctx: libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG *... | src | 27 | 0 |
| `src/import_map.c` | str: A JSON string into an owned UTF-8 buffer (escapes decoded; a lone surrogate or a * raw... | src | 22 | 0 |
| `src/interp.c` | solve_bezier_t: } static double sample_bezier_dx(double t, double cx1, double cx2) { return 3.0... | src | 19 | 0 |
| `src/js_dom.c` | jd_handle: Coerces a JS argument to a node handle. | src | 56 | 0 |
| `src/js_dom_ext.c` | - | src | 3 | 0 |
| `src/js_dom_ext.h` | Private to js_dom.c / js_dom_ext.c: installs the DOM Standard extras (tree | src | 2 | 2 |
| `src/js_dom_internal.h` | Private to the js_dom family (js_dom.c, js_fetch.c, js_events.c, js_embed.c): the context... | src | 4 | 4 |
| `src/js_embed.c` | try_create_iframe_from_script: Scans an inline script body for `video[N]` or `video_data`... | src | 6 | 0 |
| `src/js_env.c` | m_perf_now: performance.now: coarsened elapsed since the origin bound at install time, so * it... | src | 29 | 0 |
| `src/js_events.c` | jd_eval_default_action: Runs one engine event-dispatch expression and maps its result to the C... | src | 10 | 0 |
| `src/js_fetch.c` | jd_pack_ptr: Carry the host fetch fn + its ctx as a function's closure data, each split into... | src | 7 | 0 |
| `src/js_geom.c` | unite: Bounding box of a and b into a; returns 1 if a changed. | src | 21 | 0 |
| `src/js_location.c` | jd_lp_set: Defines a string property on the __locParts data object from a (ptr,len) span. * The... | src | 6 | 0 |
| `src/js_location_internal.h` | Private to js_dom.c / js_location.c: the dom.histTarget native lives with the | src | 2 | 2 |
| `src/js_policy.c` | eq_ci: js_policy — implementation: pure per-host JavaScript policy decision. | src | 6 | 0 |
| `src/js_sandbox.c` | js_mem_state: We enforce the heap cap ourselves (not via JS_SetMemoryLimit, whose check runs... | src | 41 | 0 |
| `src/js_trusted.c` | ws_payload: } void jt_ws_ops_free(jt_ws_op *ops, size_t n) { if (ops == NULL) return; for... | src | 14 | 0 |
| `src/link_nav.c` | clean_href: Removes tab/newline/CR anywhere and trims leading/trailing spaces, in place * into out. | src | 10 | 0 |
| `src/local_store.c` | - | src | 271 | 0 |
| `src/media_decoder.c` | decoder_close: AVFrame         *frame;  /* decoded frame (YUV) AVFrame         *rgb;    /*... | src | 15 | 0 |
| `src/net_realm.c` | ends_with_realm: True if the lowercased host (length n) ends with ".suffix" AND has at least one... | src | 10 | 0 |
| `src/os_sandbox.c` | os_prot_allowed: W^X mirror: mmap/mprotect keep their membership but lose any request that asks... | src | 31 | 0 |
| `src/page_view.c` | pv_cont_info: Nearest-container info attached to a run, plus the flex per-item values (Stage 3)... | src | 222 | 0 |
| `src/pdf_export.c` | - | src | 4 | 0 |
| `src/perf_trace.c` | - | src | 12 | 0 |
| `src/prefetch.c` | ci_starts: static int is_ws(char c) { return c == ' ' \|\| c == '\t' \|\| c == '\n' \|\| c == '\r' \|\|... | src | 17 | 0 |
| `src/prefs.c` | url_valid: A representable URL: 1..PREFS_MAX_URL-1 bytes, no control bytes, no DEL. * Space is... | src | 26 | 0 |
| `src/profile.c` | keyfile_create: #include <unistd.h> #include <openssl/crypto.h> #include <openssl/rand.h>... | src | 9 | 0 |
| `src/render_doc.c` | rd_push: Appends one block, taking owned copies of text (required) and href (optional). *... | src | 20 | 0 |
| `src/render_policy.c` | - | src | 5 | 0 |
| `src/renderer.c` | - | src | 6 | 0 |
| `src/request_policy.c` | public_suffix_labels: Number of labels of the public suffix (eTLD) of a lowercased host... | src | 11 | 0 |
| `src/secure_fetch.c` | tls_capture: Snapshot of the negotiated TLS state. curl exposes the live SSL* only while a... | src | 61 | 0 |
| `src/svg_render.c` | svg_render — inline <svg> markup -> a bounded list of geometric shapes. | src | 33 | 0 |
| `src/tab.c` | write_field: Writes one length-prefixed string field (the write mirror of read_field): a size_t... | src | 120 | 0 |
| `src/text_shape.c` | web_magic_ok: True for font programs FreeType parses without new decoders: wOFF/TrueType/... | src | 26 | 0 |
| `src/textfield.c` | - | src | 12 | 0 |
| `src/tls_impersonate.c` | get_bytes: \| ((uint32_t)r->p[r->off + 3] << 24); r->off += 4; return v; } static uint64_t... | src | 20 | 0 |
| `src/ui_layout.c` | - | src | 4 | 0 |
| `src/url.c` | ci_prefix: produced; every assembly is bounded and reports overflow rather than truncate.... | src | 29 | 0 |
| `src/web_storage.c` | utf8_ok: Well-formed UTF-8, allowing encoded surrogates (WTF-8): a JS string may hold a lone... | src | 17 | 0 |
| `src/webcaps.c` | - | src | 4 | 0 |
| `src/webfont.c` | ci_eq_span: #include <stdint.h> #include <stdlib.h> #include <string.h> static int is_ws(char c)... | src | 15 | 0 |
| `src/webfont_load.c` | wf_key: size_t k = 0; while (PREF[i][k] != '\0') ++k; size_t j = 0; for (; j < k; ++j) { char a... | src | 11 | 0 |
| `src/ws_hub.c` | wh_job: One open, owned by its thread until handed over through the pipe. | src | 27 | 0 |
| `src/zoom.c` | - | src | 7 | 0 |
| `tests/itest_secure_fetch.c` | - | tests | 2 | 0 |
| `tests/test_anti_fp.c` | test_origin_key_unlinks_readback: The property that actually matters: the same canvas buffer... | tests | 15 | 0 |
| `tests/test_block_flow.c` | test_two_positive_collapse_to_max: Two positive margins collapse to the LARGER, never to their... | tests | 8 | 0 |
| `tests/test_box_style.c` | dbl_eq: the display-name helper.  #include <setjmp.h> #include <stdarg.h> #include <stddef.h>... | tests | 42 | 0 |
| `tests/test_box_tree.c` | test_flex_auto_margin_pushes_item: Flexbox 8.1: an item's auto margin takes the free space... | tests | 57 | 0 |
| `tests/test_browser.c` | test_url_bar_selection: Omnibar selection model: extend builds a selection, ops replace/delete... | tests | 17 | 0 |
| `tests/test_compositor.c` | test_sort_matches_zindex_only_ordering: The positioned subset the painter already orders by... | tests | 21 | 0 |
| `tests/test_css.c` | test_inline_font_size_absolute_flag: 2026-07-31: a font-size carries whether its percent is OF... | tests | 333 | 0 |
| `tests/test_css_atrule.c` | test_css_atrule -- @supports evaluation and @layer ranks (spec/css_atrule.md). | tests | 10 | 0 |
| `tests/test_css_box.c` | - | tests | 9 | 0 |
| `tests/test_css_color.c` | test_hsl_fractional_hue: A fractional hue is a <number> too (and hsl() takes an <angle>, whose... | tests | 36 | 0 |
| `tests/test_css_drops.c` | Suite for the parser drop log (spec/css_drops.md). | tests | 25 | 0 |
| `tests/test_css_gradient.c` | - | tests | 7 | 0 |
| `tests/test_css_length.c` | test_unitless: static double px_of(const char *value, const cl_ctx *ctx) { double px = -12345.0... | tests | 25 | 0 |
| `tests/test_css_mq.c` | - | tests | 7 | 0 |
| `tests/test_css_text.c` | - | tests | 6 | 0 |
| `tests/test_css_values.c` | - | tests | 7 | 0 |
| `tests/test_css_vars.c` | test_css_vars -- the custom-property table and var() substitution (spec/css_vars.md). | tests | 14 | 0 |
| `tests/test_data_url.c` | - | tests | 26 | 0 |
| `tests/test_disk_store.c` | - | tests | 16 | 0 |
| `tests/test_dom.c` | setup_doc: #include "dom.h" #include "html_parse.h" static const char HTML[] = "<!DOCTYPE... | tests | 41 | 0 |
| `tests/test_dom_debug.c` | build: #include "dom_debug.h" #include "page_view.h" #include "render_doc.h" #include... | tests | 11 | 0 |
| `tests/test_download.c` | - | tests | 21 | 0 |
| `tests/test_flex_layout.c` | test_autofill_count: assert_item(out[0], 0.0, 100.0);  /* no divide-by-zero, behaves like start... | tests | 67 | 0 |
| `tests/test_form.c` | - | tests | 20 | 0 |
| `tests/test_frame_clock.c` | - | tests | 4 | 0 |
| `tests/test_freebug.c` | - | tests | 13 | 0 |
| `tests/test_freedom.c` | run_freedom_raw: Runs the binary with a raw argument string (no implicit --headless), capturing... | tests | 72 | 0 |
| `tests/test_hls.c` | - | tests | 16 | 0 |
| `tests/test_hostblock.c` | - | tests | 22 | 0 |
| `tests/test_hostedit.c` | - | tests | 11 | 0 |
| `tests/test_html_parse.c` | test_extract_script_list_external_semantics: External-script semantics (Hito 24 EXT): a <script... | tests | 24 | 0 |
| `tests/test_image_decode.c` | - | tests | 37 | 0 |
| `tests/test_import_map.c` | tres: Test URL resolver: absolute https passes, "/x" is origin-relative, "./x" and "../x" * are... | tests | 8 | 0 |
| `tests/test_interp.c` | assert_float_equal: ip_ease_fn fns_0to0[] = { { .kind = IP_EASE_LINEAR }, { .kind = IP_EASE_EASE... | tests | 37 | 0 |
| `tests/test_js_dom.c` | fake_net: Object.defineProperty(event, ...) -- it threw "not an object" on openstreetmap), *... | tests | 175 | 0 |
| `tests/test_js_env.c` | test_performance_timing_identity_safe: performance.timing / navigation / getEntries*: present... | tests | 26 | 0 |
| `tests/test_js_geom.c` | test_same_node_unions: assert_int_equal(jg_add(&t, 2, 0, 0, 5, 5), 0)... | tests | 11 | 0 |
| `tests/test_js_policy.c` | test_trusted_requires_both_signals: Hito 28: a host is TRUSTED (full author CSS + images, on top... | tests | 5 | 0 |
| `tests/test_js_sandbox.c` | test_set_time_budget_applies: js_set_time_budget lowers the wall-clock cap armed on subsequent... | tests | 42 | 0 |
| `tests/test_link_nav.c` | test_resolve_long_bundle_target: Modern bundle URLs exceed the old 4096 target cap (google's xjs... | tests | 22 | 0 |
| `tests/test_local_store.c` | - | tests | 18 | 0 |
| `tests/test_media_decoder.c` | test_pacer_paces_by_pts_delta: #include "media_decoder.h" /* First frame anchors the epoch and... | tests | 6 | 0 |
| `tests/test_net_realm.c` | test_classify_host_lookalikes: static void test_classify_host_i2p(void **state) { (void)state... | tests | 13 | 0 |
| `tests/test_os_sandbox.c` | test_policy_denies_io_uring: io_uring is a seccomp-bypass primitive (its IORING_OP_* operations... | tests | 19 | 0 |
| `tests/test_page_view.c` | parse: #include <stdlib.h> #include <setjmp.h> #include <string.h> #include <cmocka.h> #include... | tests | 181 | 0 |
| `tests/test_pdf_export.c` | - | tests | 30 | 0 |
| `tests/test_perf_trace.c` | - | tests | 12 | 0 |
| `tests/test_prefetch.c` | Tests for prefetch (Hito 29): pure lookahead scanner + parallel download pool. | tests | 12 | 0 |
| `tests/test_prefs.c` | - | tests | 15 | 0 |
| `tests/test_profile.c` | dir: include "prefs.h" include "profile.h" | tests | 17 | 0 |
| `tests/test_render_doc.c` | first_kind: #include "flex_layout.h" #include "page_view.h" #include "render_doc.h" #include... | tests | 36 | 0 |
| `tests/test_render_policy.c` | test_image_allow_data_url: A data: URI embeds its bytes inline: no socket opens, so it skips the... | tests | 21 | 0 |
| `tests/test_renderer.c` | test_render_binary_does_not_crash_parent: (void)state; rd_result r... | tests | 8 | 0 |
| `tests/test_request_policy.c` | test_site_of_psl: } static void test_site_of_multi_suffix(void **state) { (void)state; char... | tests | 12 | 0 |
| `tests/test_secure_fetch.c` | test_enforce_allowlisted_insecure: The allowlist override: the user's sovereign per-host escape... | tests | 50 | 0 |
| `tests/test_svg_render.c` | tests/test_svg_render.c — CMocka suite for the pure inline-SVG parser (sv_). | tests | 16 | 0 |
| `tests/test_tab.c` | sink_cap: Served-stylesheet sink (spec/webfont.md b3b): the parent observes each served 2xx CSS... | tests | 120 | 0 |
| `tests/test_text_shape.c` | read_host_font: Reads a host TrueType file when one exists (same philosophy as the shaping *... | tests | 12 | 0 |
| `tests/test_textfield.c` | - | tests | 8 | 0 |
| `tests/test_tls_impersonate.c` | - | tests | 11 | 0 |
| `tests/test_ui.c` | assert_line: Build: make test   ;   ASan: make asan  #include <stdarg.h> #include <stddef.h>... | tests | 12 | 0 |
| `tests/test_url.c` | test_validate_long_bundle_url: Modern bundle URLs exceed 2048 bytes (google.com's xjs script URL... | tests | 49 | 0 |
| `tests/test_web_storage.c` | - | tests | 9 | 0 |
| `tests/test_webcaps.c` | mk: projection, and the headless operator-flag path.  #include <setjmp.h> #include <stdarg.h>... | tests | 11 | 0 |
| `tests/test_webfont.c` | - | tests | 13 | 0 |
| `tests/test_webfont_load.c` | test_b64: if (b == NULL) { fclose(f); return NULL; } if (fread(b, 1, (size_t)sz, f) !=... | tests | 16 | 0 |
| `tests/test_ws_hub.c` | wait_notify: #include <string.h> #include <cmocka.h> #include "ws_hub.h" typedef struct rec {... | tests | 13 | 0 |
| `tests/test_zoom.c` | - | tests | 11 | 0 |
| `tools/ffgeom.py` | ffgeom -- Firefox geometry as TEXT, no image reading. | tools | 12 | 0 |
| `tools/gen_psl.c` | sort_unique: v->cap = v->cap ? v->cap * 2 : 1024; v->items = (char **)realloc(v->items, v->cap *... | tools | 8 | 0 |
| `tools/mutate.py` | mutate -- compile-time mutation testing for the CMocka suites. | tools | 6 | 0 |
| `tools/pngdiff.c` | pd_reader_open: Opens `path` and normalises whatever colour type it carries into 8-bit RGB, so *... | tools | 14 | 0 |
| `tools/pngprof.py` | pngprof -- structural ink-profile dump for page screenshots. | tools | 4 | 0 |
| `tools/snapshot.py` | Freeze a live page into one self-contained HTML file for `make parity`. | tools | 6 | 0 |
