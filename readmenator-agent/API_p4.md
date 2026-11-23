# API (page 4 of 13)
Previous: [API_p3.md](API_p3.md)

## include/box_tree.h
Depends on: `include/box_style.h`, `include/flex_layout.h`, `include/page_view.h`
Imported by: `fuzz/fuzz_box_tree.c`, `gui/browser_ui.c`, `src/box_tree.c`, `src/page_view.c`, `src/tab.c`, `tests/test_box_tree.c`
- `closed` (function) `include/box_tree.h:34` `* fails closed (BT_ERR_RANGE) instead of overflowing the stack. */ #define BT_MAX_DEPTH 64u #define BT_MAX_CHILDREN...`
- `one` (function) `include/box_tree.h:99` `* of forcing them all onto one (flex-wrap);`
- `line` (function) `include/box_tree.h:115` `* its line (already resolved from align-self / the * container's align-items by the caller). */ /* this node as a...`
- `node` (function) `include/box_tree.h:162` `* node (x/y parent-relative, w/h border-box). display:none nodes get a zero rect and * take no space. The caller...`
- `flow` (function) `include/box_tree.h:201` `* position is where the box would have started in flow (CSS 2.2 §10.3.7/§10.6.4);`
- `bottom` (function) `include/box_tree.h:208` `* bottom with auto top still anchors bottom (R8). * `placed` (may be NULL) marks which boxes have an in-flow rect in...`
- `placed` (function) `include/box_tree.h:215` `* box counts as placed (legacy behaviour). * bt_resolve_positioning delegates with NULL arrays (legacy behaviour)....`
- `bt_box_hidden` (function) `include/box_tree.h:233` `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid);` -- Stage 2b visibility gate: 1 when the box at `bid` or any ancestor on the parent_id chain has visibility...
- `bt_in_subtree` (function) `include/box_tree.h:239` `int bt_in_subtree(const pv_box_def *boxes, size_t nbox, size_t root, size_t bid);` -- 1 when box `bid` is `root` or a descendant of it on the parent_id chain, else 0 (ancestors, siblings, out-of-range...
- `bt_oof_anchor` (function) `include/box_tree.h:253` `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid);` -- Stage 2d out-of-flow subtree classification (spec/box_engine.md).
- `bt_oof_root` (function) `include/box_tree.h:254` `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid);`
- `insets` (function) `include/box_tree.h:258` `* minus the two insets (px half + per-mille half of cb), an auto/unset inset * counting 0, never below 0. *both (may...`
- `bt_containing_block` (function) `include/box_tree.h:268` `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i, const double *box_x, const double *box_y...` -- The containing block of box i as the positioning solver resolves it: the viewport for FIXED (and for ABSOLUTE with...
- `bt_defer_roots` (function) `include/box_tree.h:291` `size_t bt_defer_roots(const pv_box_def *boxes, size_t nbox, const bt_positioned *pos, size_t npos, const char...` -- (an absolute backdrop, say) comes EARLIER in the tree than S, S must paint above it -- but the painter draws all...

## include/browser.h
Imported by: `fuzz/fuzz_browser.c`, `gui/browser_ui.c`, `src/browser.c`, `tests/test_browser.c`
- `state` (function) `include/browser.h:76` `* state (frees old history and page buffers). */ browser_status browser_init(browser_state *bs);`
- `browser_free` (function) `include/browser.h:80` `void browser_free(browser_state *bs);` -- Zero-initialise or reset a state.
- `browser_set_page` (function) `include/browser.h:85` `* browser_set_page() with the result. */ browser_status browser_navigate(browser_state *bs, const char *url);`
- `one` (function) `include/browser.h:104` `* A navigate while pending first aborts the pending one (the new one replaces it);`
- `browser_commit_pending` (function) `include/browser.h:107` `void browser_commit_pending(browser_state *bs);` -- Provisional navigation (spec/browser.md 3c). commit: the document (or its error page) landed -- the entry stays and...
- `browser_abort_pending` (function) `include/browser.h:108` `int browser_abort_pending(browser_state *bs);`
- `browser_has_pending` (function) `include/browser.h:109` `int browser_has_pending(const browser_state *bs);`
- `browser_entry_doc` (function) `include/browser.h:112` `int browser_entry_doc(const browser_state *bs, size_t pos);` -- Provisional navigation (spec/browser.md 3c). commit: the document (or its error page) landed -- the entry stays and...
- `browser_doc_index` (function) `include/browser.h:116` `int browser_doc_index(const browser_state *bs);` -- Index of the current entry within its document's contiguous run of entries (0 for * the entry the document was...
- `browser_set_entry_scroll` (function) `include/browser.h:122` `void browser_set_entry_scroll(browser_state *bs, double scroll);` -- Scroll offset of the CURRENT entry (spec/anchor.md 3): set it when leaving an entry, read it when a same-document...
- `browser_entry_scroll` (function) `include/browser.h:123` `double browser_entry_scroll(const browser_state *bs);`
- `browser_can_back` (function) `include/browser.h:126` `int browser_can_back(const browser_state *bs);` -- Scroll offset of the CURRENT entry (spec/anchor.md 3): set it when leaving an entry, read it when a same-document...
- `browser_can_forward` (function) `include/browser.h:127` `int browser_can_forward(const browser_state *bs);`
- `browser_current_url` (function) `include/browser.h:128` `const char *browser_current_url(const browser_state *bs);`
- `browser_is_exception` (function) `include/browser.h:131` `int browser_is_exception(const browser_state *bs, const char *host);` -- Scroll offset of the CURRENT entry (spec/anchor.md 3): set it when leaving an entry, read it when a same-document...
- `browser_url_bar_selection` (function) `include/browser.h:163` `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len);` -- If a selection exists, writes its start offset and length and returns 1; else 0. * Lets the GUI copy/cut the...
- `browser_url_bar_delete_selection` (function) `include/browser.h:167` `int browser_url_bar_delete_selection(browser_state *bs);` -- Removes the selected range (if any), placing the cursor at its start; returns 1 if * something was removed, else 0.
- `copied` (function) `include/browser.h:175` `* copied (truncated to fit) and shown until now_ms reaches the expiry * (now_ms + BROWSER_STATUS_DURATION_MS). A...`
- `browser_status_text` (function) `include/browser.h:182` `const char *browser_status_text(const browser_state *bs, uint64_t now_ms);` -- Transient status line (a toast, e.g. "blocked: insecure http link"). msg is copied (truncated to fit) and shown...
- `browser_closed_pop` (function) `include/browser.h:197` `int browser_closed_pop(browser_closed *c, char *out, size_t cap);` -- Takes the most recently closed URL into out[cap].

## include/cached_fetch.h
Depends on: `include/http_cache.h`, `include/secure_fetch.h`
Imported by: `gui/browser_ui.c`, `src/cached_fetch.c`, `tests/test_cached_fetch.c`
- `cf_set_store` (function) `include/cached_fetch.h:30` `void cf_set_store(hc_store *store);` -- Cache-aware GET.
- `cf_store` (function) `include/cached_fetch.h:31` `hc_store *cf_store(void);`
- `cf_attach_redirect_memory` (function) `include/cached_fetch.h:38` `void cf_attach_redirect_memory(hc_store *store);` -- conditional GET is sent to the stored FINAL url and a 304 serves the stored body. sf_status cf_get_with(hc_store...

## include/chrome_layout.h
Imported by: `fuzz/fuzz_chrome_layout.c`, `gui/browser_ui_internal.h`, `src/chrome_layout.c`, `tests/test_chrome_layout.c`
- `chl_tab_rect` (function) `include/chrome_layout.h:87` `int chl_tab_rect(const chl_layout *l, int i, chl_rect *r);` -- Computes the layout. tab_count >= 1 and 0 <= active < tab_count, else CHL_EINVAL * (out untouched).
- `chl_tab_close_rect` (function) `include/chrome_layout.h:88` `int chl_tab_close_rect(const chl_layout *l, int i, chl_rect *r);`
- `chl_rect_has` (function) `include/chrome_layout.h:91` `int chl_rect_has(chl_rect r, double x, double y);` -- Computes the layout. tab_count >= 1 and 0 <= active < tab_count, else CHL_EINVAL * (out untouched).
- `chl_tab_drop_index` (function) `include/chrome_layout.h:99` `int chl_tab_drop_index(const chl_layout *l, double x);` -- Absolute index of the visible tab slot under x (clamped to the visible tabs): where a * dragged tab dropped at x...
- `chl_move_index` (function) `include/chrome_layout.h:103` `int chl_move_index(int i, int from, int to);` -- Where element i ends up after the element at `from` moves to `to` (the others shift to * close the gap and open the...
- `chl_tab_for_digit` (function) `include/chrome_layout.h:106` `int chl_tab_for_digit(int digit, int tab_count);` -- Where element i ends up after the element at `from` moves to `to` (the others shift to * close the gap and open the...
- `chl_tab_fallback_title` (function) `include/chrome_layout.h:111` `void chl_tab_fallback_title(const char *url, char *out, size_t cap);` -- A tab label for a page without <title> (Firefox): a file's name for file: URLs and local paths, otherwise the URL...
- `chl_identity_label` (function) `include/chrome_layout.h:162` `const char *chl_identity_label(chl_identity id);` -- CHL_ID_CLASSICAL,   /* https, TLS 1.3 classical key exchange CHL_ID_WEAK,        /* https under the per-host...

## include/compositor.h
Imported by: `gui/browser_ui.c`, `src/box_tree.c`, `src/compositor.c`, `tests/test_compositor.c`
- `cx_forms_stacking_context` (function) `include/compositor.h:60` `int cx_forms_stacking_context(const cx_style *s);` -- Does this box establish a stacking context?
- `cx_item_compare` (function) `include/compositor.h:80` `int cx_item_compare(const cx_item *a, const cx_item *b);` -- Total paint order: layer ascending, then z-index ascending (auto == 0), then document order ascending.
- `cx_sort` (function) `include/compositor.h:84` `void cx_sort(cx_item *items, size_t n);` -- Stable in-place sort of `items` into paint order (uses cx_item_compare).
- `cx_ink_reach` (function) `include/compositor.h:91` `double cx_ink_reach(const int (*layers)[6], int n, int outline_w, int outline_offset);` -- How far (px, >= 0) a box's paint may reach beyond its border box (spec/compositor.md, tanda 95): each outset...
- `cx_span_visible` (function) `include/compositor.h:95` `int cx_span_visible(double top, double h, double reach, double view_top, double view_h);` -- 1 when [top - reach, top + h + reach] touches [view_top, view_top + view_h] (edges * included), else 0.

## include/css.h
Depends on: `include/css_color.h`, `include/css_counter.h`, `include/css_mq.h`
Imported by: `fuzz/fuzz_css.c`, `fuzz/fuzz_text_case.c`, `gui/browser_ui.c`, `gui/bui_mask_img.c`, `gui/bui_theme.c`, `include/box_style.h`, `include/css_chain.h`, `include/css_computed.h`, `include/css_decl.h`, `include/css_select.h`, `include/page_view.h`, `include/pres_hints.h`, `include/sheet_cache.h`, `src/box_tree.c`, `src/compositor.c`, `src/css.c`, `src/css_box.c`, `src/css_length.c`, `src/css_text.c`, `src/css_values.c`, `src/dom_debug.c`, `src/js_native.c`, `src/page_view.c`, `src/render_doc.c`, `src/tab.c`, `src/text_case.c`, `src/text_shape.c`, `tests/test_box_tree.c`, `tests/test_compositor.c`, `tests/test_css.c`, `tests/test_css_drops.c`, `tests/test_css_gradient.c`, `tests/test_css_length.c`, `tests/test_css_text.c`, `tests/test_css_values.c`, `tests/test_dom_debug.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`, `tests/test_tab.c`, `tests/test_text_case.c`, `tests/test_text_shape.c`, `tests/test_webfont_load.c`
- `verbatim` (function) `include/css.h:92` `* the quoted row strings verbatim (flex_layout parses them);`
- `POINTER` (function) `include/css.h:235` `* POINTER (shows the hand cursor already used for links) from every other value * (shows the default arrow);`
- `container` (function) `include/css.h:674` `* container (Display 3 section 2);`
- `family` (function) `include/css.h:719` `* LOCAL family (spec/text_shape.md section 7);`
- `translate` (function) `include/css.h:893` `* translate()/translateX()/translateY();`
- `scaleY` (function) `include/css.h:894` `* scaleY() as a PERCENT of identity (100 = scale(1), matching font_scale's * convention);`
- `declared` (function) `include/css.h:898` `* function was not declared (identity: 0 offset / 100% scale / 0deg). * Percentage translate arguments are not...`
- `element` (function) `include/css.h:903` `* so two different rules matching the same element (e.g. one setting * translate, a more specific one setting...`
- `slots` (function) `include/css.h:910` `* parse time into ALL seven slots (singular matrices fail closed);`
- `css_sheet_uses_counters` (function) `include/css.h:1055` `int css_sheet_uses_counters(const css_sheet *sheet);` -- 1 when any rule of the sheet declares counter-reset / counter-increment. page_view * runs its document-order counter...
- `css_sheet_uses_containers` (function) `include/css.h:1059` `int css_sheet_uses_containers(const css_sheet *sheet);` -- 1 when the sheet holds any rule gated by an @container condition: only then does * the engine need to track query...
- `palette` (function) `include/css.h:1076` `* so an inactive theme * palette (a dark palette in a light render) can never clobber the active one. *...`
- `css_free` (function) `include/css.h:1126` `void css_free(css_sheet *s);` -- As css_parse_scoped, plus the drop sink. log == NULL is exactly css_parse_scoped: same path, same sheet, same cost.
- `order` (function) `include/css.h:1129` `* cascade order (specificity, then document order), then the element's own * inline_style (which wins)....`
- `inherited_px` (function) `include/css.h:1246` `* whose PARENT computes to inherited_px (<= 0 = unknown -> the CSS initial). * * Exported because the caller that...`
- `css_ua_heading_em` (function) `include/css.h:1258` `double css_ua_heading_em(int level);` -- The user-agent sheet's font-size of <h1>..<h6> as a multiple of the parent's (HTML Rendering 15.3.6: 2em, 1.5em...
- `name` (function) `include/css.h:1263` `* name (NULL = not a heading). */ double css_computed_font_size_for_tag(const css_style *o, double inherited_px...`
- `css_font_face_count` (function) `include/css.h:1273` `size_t css_font_face_count(const css_sheet *sheet);` -- Web font access: returns the number of @font-face declarations parsed into the sheet, and copies the i-th...
- `css_font_face_at` (function) `include/css.h:1274` `int css_font_face_at(const css_sheet *sheet, size_t i, char *family, size_t fam_cap, char *src_url, size_t url_cap);`
- `css_resolve_anim_keyframes` (function) `include/css.h:1282` `void css_resolve_anim_keyframes(css_style *s, const css_sheet *sheet);` -- Resolve @keyframes: scans sheet->keyframes[] for a name matching s->anim_name (first-char match).

## include/css_atrule.h
Imported by: `src/css.c`, `src/css_atrule.c`, `tests/test_css_atrule.c`
- `car_supports` (function) `include/css_atrule.h:29` `int car_supports(const char *s, size_t a, size_t b, const car_ops *ops);` -- The questions @supports asks the caller's own engine. prop is lowercased and * both strings are trimmed and...
- `car_layer_rank` (function) `include/css_atrule.h:40` `int car_layer_rank(car_layers *L, const char *name, size_t len);` -- Rank (1..CAR_MAX_LAYERS) of the layer whose full dotted name is name[0,len), registering it on first sight. len == 0...
- `car_effective_spec` (function) `include/css_atrule.h:44` `int car_effective_spec(int spec, int layer, int important);` -- Folds layer rank and specificity into one comparable value (layer first). layer * 0 = unlayered.

## include/css_box.h
Depends on: `include/css_decl.h`
Imported by: `src/css.c`, `src/css_box.c`, `src/css_mq.c`, `src/css_text.c`, `tests/test_css_box.c`
- `cb_length_px` (function) `include/css_box.h:15` `int cb_length_px(const char *v, double *px);`
- `block` (function) `include/css_box.h:19` `* For contexts with no element and no containing block (media query values). */ int cb_math_length_px(const char *v...`
- `cb_interp_len` (function) `include/css_box.h:21` `int cb_interp_len(const char *v, int allow_auto, int *out);`
- `cb_emit_len` (function) `include/css_box.h:22` `int cb_emit_len(css_decl *dst, int cap, int slot, const char *val, int allow_auto, int allow_neg);`
- `cb_expand_box4` (function) `include/css_box.h:24` `int cb_expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg, css_decl *dst, int cap);`
- `cb_expand_box2` (function) `include/css_box.h:26` `int cb_expand_box2(const char *val, int slot_start, int slot_end, int allow_auto, int allow_neg, css_decl *dst, int...`
- `cb_interp_lp` (function) `include/css_box.h:28` `int cb_interp_lp(const char *v, int allow_auto, int allow_pct, int *out_px, int *out_pm);`
- `cb_value_em_milli` (function) `include/css_box.h:30` `int cb_value_em_milli(const char *v);`
- `rectangle` (function) `include/css_box.h:32` `* rectangle (top, right, bottom, left): px[i] + pm[i]/1000 of the border box (height for * top/bottom, width for...`
- `cb_lp_can_be_nonneg` (function) `include/css_box.h:36` `int cb_lp_can_be_nonneg(int px_val, int pct_pm);`
- `cb_next_ws_token` (function) `include/css_box.h:37` `int cb_next_ws_token(const char **p, char *tok, size_t cap);`
- `cb_interp_align` (function) `include/css_box.h:38` `int cb_interp_align(const char *v);`
- `cb_interp_fontsize_ex` (function) `include/css_box.h:39` `int cb_interp_fontsize_ex(const char *v, int *abs_out);`
- `cb_interp_lineheight` (function) `include/css_box.h:40` `int cb_interp_lineheight(const char *v);`
- `cb_interp_weight` (function) `include/css_box.h:41` `int cb_interp_weight(const char *v);`
- `cb_interp_style` (function) `include/css_box.h:42` `int cb_interp_style(const char *v);`
- `cb_interp_textdeco` (function) `include/css_box.h:43` `int cb_interp_textdeco(const char *v);`
- `cb_interp_display` (function) `include/css_box.h:44` `int cb_interp_display(const char *v);`
- `cb_interp_gap` (function) `include/css_box.h:45` `int cb_interp_gap(const char *v);`
- `cb_interp_justify` (function) `include/css_box.h:46` `int cb_interp_justify(const char *v);`
- `cb_interp_gridcols` (function) `include/css_box.h:47` `int cb_interp_gridcols(const char *v);`
- `cb_expand_grid_template_cols` (function) `include/css_box.h:48` `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap);`
- `strings` (function) `include/css_box.h:50` `* Quoted area strings (the grid-template shorthand's row half) are skipped. */ int...`

## include/css_chain.h
Depends on: `include/css.h`, `include/css_select.h`
Imported by: `src/css_chain.c`, `src/dom.c`, `src/page_view.c`, `tests/test_page_view.c`
- `cch_path_new` (function) `include/css_chain.h:70` `cch_path *cch_path_new(void);`
- `cch_path_free` (function) `include/css_chain.h:71` `void cch_path_free(cch_path *pa);`
- `cch_element_matches` (function) `include/css_chain.h:82` `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel);` -- Nonzero iff the parsed selector *sel matches element `el`, built against the same bounded ancestor/sibling/attribute...
- `lacks` (function) `include/css_chain.h:86` `* the element lacks (csel's subj_req) is rejected before the ancestor chain is built: on a * query that scans a...`
- `box` (function) `include/css_chain.h:92` `* generated box (css_resolve_pseudo) against the same element context. * font_size is el's own COMPUTED font-size...`

## include/css_color.h
Imported by: `gui/browser_ui.c`, `gui/bui_theme.c`, `include/css.h`, `src/css.c`, `src/css_box.c`, `src/css_color.c`, `src/css_gradient.c`, `src/css_text.c`, `src/css_values.c`, `src/page_view.c`, `src/pres_hints.c`, `src/svg_paint.c`, `src/svg_render.c`, `tests/test_css_color.c`
- `cc_pack` (function) `include/css_color.h:49` `int cc_pack(cc_rgb c);` -- Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport * and for the pipeline's "no color"...

## include/css_computed.h
Depends on: `include/css.h`
Imported by: `src/css_computed.c`, `src/tab.c`, `tests/test_css_computed.c`
- `ccm_get` (function) `include/css_computed.h:29` `size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap);` -- Writes the computed value of the kebab-case property `prop` into out (cap bytes, NUL terminated).
- `ccm_property_count` (function) `include/css_computed.h:32` `size_t ccm_property_count(void);` -- Writes the computed value of the kebab-case property `prop` into out (cap bytes, NUL terminated).
- `ccm_property_name` (function) `include/css_computed.h:33` `const char *ccm_property_name(size_t i);`

## include/css_counter.h
Imported by: `fuzz/fuzz_css_counter.c`, `include/css.h`, `src/css_counter.c`, `tests/test_css_counter.c`
- `cnt_hash` (function) `include/css_counter.h:34` `unsigned cnt_hash(const char *name, size_t len);` -- FNV-1a over `len` bytes of an identifier, ASCII case preserved (identifiers are * case-sensitive).
- `written` (function) `include/css_counter.h:37` `* written (0 for `none`) or -1 when invalid. `dflt` is the value of an entry with no * integer: 0 for reset, 1 for...`
- `cnt_parse_content` (function) `include/css_counter.h:44` `int cnt_parse_content(const char *val, char *out, size_t cap);` -- Parses a `content` value that uses counter()/counters().
- `cnt_is_marker` (function) `include/css_counter.h:45` `int cnt_is_marker(const char *s);`
- `cnt_format` (function) `include/css_counter.h:49` `size_t cnt_format(int style, long value, char *out, size_t cap);` -- Formats `value` in `style` (unknown or unrepresentable falls back to decimal). * Returns the length written; always...
- `cnt_state_new` (function) `include/css_counter.h:52` `cnt_state *cnt_state_new(void);`
- `cnt_state_free` (function) `include/css_counter.h:53` `void cnt_state_free(cnt_state *s);`
- `cnt_reset` (function) `include/css_counter.h:56` `void cnt_reset(cnt_state *s, int depth, const cnt_decl *d, int n);` -- Formats `value` in `style` (unknown or unrepresentable falls back to decimal). * Returns the length written; always...
- `cnt_increment` (function) `include/css_counter.h:57` `void cnt_increment(cnt_state *s, int depth, const cnt_decl *d, int n);`
- `cnt_leave` (function) `include/css_counter.h:60` `void cnt_leave(cnt_state *s, int depth);` -- The children of an element have all been walked: drop what they created * (instances created at depth >= `depth`...
- `cnt_resolve` (function) `include/css_counter.h:67` `size_t cnt_resolve(const cnt_state *s, const char *marker, cnt_attr_fn attr, void *ctx, char *out, size_t cap);` -- Expands a marker against the live state.

## include/css_decl.h
Depends on: `include/css.h`, `include/css_select.h`
Imported by: `include/css_box.h`, `include/css_gradient.h`, `include/css_mask.h`, `include/css_text.h`, `src/css.c`, `src/css_box.c`, `src/css_gradient.c`, `src/css_text.c`, `src/css_values.c`, `src/page_view.c`, `tests/test_css_box.c`, `tests/test_css_text.c`
- `order` (function) `include/css_decl.h:50` `* The four margin slots are contiguous in CSS shorthand order (top,right,bottom, * left);`
- `contiguous` (function) `include/css_decl.h:65` `* contiguous (dx,dy,color) so expand_shadow writes them as a group. */ P_FONTFAMILY, P_TEXTTRANSFORM...`
- `part` (function) `include/css_decl.h:216` `* each P_CLIP_* edge adds to its px part (the other half of a <length-percentage>). */ P_CLIP_TOP_PM...`

## include/css_gradient.h
Depends on: `include/css_decl.h`
Imported by: `gui/browser_ui.c`, `src/css.c`, `src/css_gradient.c`, `src/css_mask.c`, `src/tab.c`, `tests/test_css_gradient.c`
- `cg_first_url` (function) `include/css_gradient.h:13` `int cg_first_url(const char *val, char *out, size_t outcap);` -- The first url(...) token of val, unquoted and trimmed, into out.
- `cg_expand_bg_image` (function) `include/css_gradient.h:15` `int cg_expand_bg_image(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...`
- `cg_expand_background` (function) `include/css_gradient.h:17` `int cg_expand_background(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...`
- `width` (function) `include/css_gradient.h:21` `* width (x, rx) or height (y, ry);`
- `out` (function) `include/css_gradient.h:36` `* Returns 1 and fills *out (defaults first) when seg is a valid prelude, 0 when seg is not * one (it is a colour...`
- `cg_radial_len_px` (function) `include/css_gradient.h:41` `double cg_radial_len_px(int enc, double dim);` -- The first comma segment of a radial-gradient() argument list, when it is a prelude.
- `zero` (function) `include/css_gradient.h:45` `* floored at a hair above zero (the spec paints the last colour for a degenerate size) and * never non-finite. Pure....`
- `cg_parse_linear` (function) `include/css_gradient.h:55` `int cg_parse_linear(const char *fn, int *angle, int *colors, int *positions);` -- Parses one `linear-gradient(...)` function (the whole text, nothing around it) into its angle (CSS degrees), packed...

## include/css_import.h
Imported by: `fuzz/fuzz_css_import.c`, `src/css_import.c`, `src/tab.c`, `tests/test_css_import.c`, `tests/test_tab.c`
- `ci_scan` (function) `include/css_import.h:36` `size_t ci_scan(const char *css, size_t len, ci_import *out, size_t cap);` -- Reads the leading @import rules of css[0,len) into out (at most cap).
- `ci_wrap` (function) `include/css_import.h:41` `int ci_wrap(const ci_import *im, char *open, size_t ocap, char *close, size_t ccap);` -- Builds the wrapper for one import: open = "@layer N {@supports (S) {@media M {" (only the parts present) and close =...
- `ci_balanced` (function) `include/css_import.h:45` `int ci_balanced(const char *css, size_t len);` -- 1 iff every comment and string in css[0,len) terminates and the braces outside * them never go negative and end at...
- `url` (function) `include/css_import.h:55` `* rewritten to url("ABS"), ABS = resolve(base, ref) (spec/css_import.md, "Rebase"). * Fragment-only, schemed, empty...`

## include/css_index.h
Depends on: `include/css_select.h`
Imported by: `src/css.c`, `src/css_index.c`, `tests/test_css_index.c`
- `cix_build` (function) `include/css_index.h:34` `void cix_build(const css_sel *sels, size_t n, cix_index *idx);` -- Builds the index over sels[0,n) into *idx, overwriting it (a built index must be * cix_free'd first).
- `cix_build_ptrs` (function) `include/css_index.h:37` `void cix_build_ptrs(css_sel *const *sels, size_t n, cix_index *idx);` -- Builds the index over sels[0,n) into *idx, overwriting it (a built index must be * cix_free'd first).
- `cix_free` (function) `include/css_index.h:40` `void cix_free(cix_index *idx);` -- Builds the index over sels[0,n) into *idx, overwriting it (a built index must be * cix_free'd first).
- `index` (function) `include/css_index.h:44` `* index (the caller then scans linearly). */ size_t cix_candidates(const cix_index *idx, const css_element *el...`

## include/css_length.h
Imported by: `src/css.c`, `src/css_box.c`, `src/css_gradient.c`, `src/css_length.c`, `src/css_mq.c`, `src/css_text.c`, `src/css_values.c`, `src/page_view.c`, `tests/test_css_length.c`
- `prelude` (function) `include/css_length.h:106` `* correct context for a media query prelude (whose `em` is defined to use the * initial font size, never the...`
- `cl_unit_is_font_relative` (function) `include/css_length.h:164` `* cl_unit_is_font_relative() draws. */ /* * Re-fits a resolved length to a different font-size: * * used = px + em *...`
- `cl_unit_font_ratio` (function) `include/css_length.h:189` `double cl_unit_font_ratio(const char *unit, size_t unit_len);` -- How many px one of `unit` is worth per 1px of font-size -- the per-unit derivative behind cl_lp.em.
- `here` (function) `include/css_length.h:193` `* Every input cl_resolve accepts resolves identically here (with has_pct 0);`
- `length` (function) `include/css_length.h:213` `* * A basis that is not a usable length (negative, zero, non-finite) contributes * nothing, but the absolute...`
- `cl_number` (function) `include/css_length.h:237` `int cl_number(const char *s, double *out, const char **endp);` -- Returns 1 on success, writing *out and pointing *endp at the first unconsumed character; 0 if there is no number there.
- `cl_is_length_unit` (function) `include/css_length.h:253` `int cl_is_length_unit(const char *unit, size_t unit_len);` -- Non-zero when `unit` names a <length> unit at all (any of the three families * plus px).

## include/css_mask.h
Depends on: `include/css_decl.h`
Imported by: `gui/browser_ui.c`, `src/css.c`, `src/css_mask.c`, `tests/test_css_mask.c`
- `cm_is_mask_prop` (function) `include/css_mask.h:28` `int cm_is_mask_prop(const char *prop);` -- One decoded layer. angle is CSS degrees; alpha[] is 0..255; pos[] is per-mille, -1 = evenly * spaced. kind 0 = no...
- `malformed` (function) `include/css_mask.h:31` `* the value is unsupported or malformed (the caller drops the declaration). */ int cm_expand(const char *prop, const...`
- `cm_encode_layer` (function) `include/css_mask.h:35` `void cm_encode_layer(const cm_layer *l, int *meta, int *alphas, int *poss);` -- Expands one mask declaration into cascade slots.
- `cm_decode_layer` (function) `include/css_mask.h:36` `void cm_decode_layer(int meta, int alphas, int poss, cm_layer *out);`

## include/css_mq.h
Imported by: `fuzz/fuzz_css.c`, `include/css.h`, `src/css.c`, `src/css_mq.c`, `tests/test_css_mq.c`
- `cmq_matches` (function) `include/css_mq.h:28` `int cmq_matches(const char *s, size_t len, const cmq_env *env);` -- 1 iff the media query list s[0,len) matches env; malformed/unknown parts fail * closed.
- `cmq_container_surely` (function) `include/css_mq.h:34` `int cmq_container_surely(const char *s, size_t len, int max_width);` -- @container condition s[0,len) (optionally led by a container name) is SURELY true for every container no wider than...
- `cmq_name_hash` (function) `include/css_mq.h:50` `unsigned cmq_name_hash(const char *s, size_t n);` -- Case-sensitive hash of a container name (custom-ident); never 0 for a non-empty * name, 0 for NULL/empty.
- `cmq_container_decl` (function) `include/css_mq.h:63` `int cmq_container_decl(const char *prop, const char *val, int *type, unsigned names[CMQ_CONTAINER_NAMES], int...` -- Interprets a `container-type`, `container-name` or `container` declaration value. *type (CMQ_CT_*) is written when...

## include/css_select.h
Depends on: `include/css.h`
Imported by: `fuzz/fuzz_css.c`, `include/css_chain.h`, `include/css_decl.h`, `include/css_index.h`, `src/css.c`, `src/css_atrule.c`, `src/css_box.c`, `src/css_chain.c`, `src/css_gradient.c`, `src/css_select.c`, `src/css_text.c`, `src/css_values.c`, `src/css_vars.c`, `src/dom.c`, `src/sheet_cache.c`, `tests/test_css.c`
- `csel_compact_size` (function) `include/css_select.h:168` `size_t csel_compact_size(int nparts);` -- Bytes a selector with `nparts` compounds needs: the header plus the compounds it uses.
- `csel_compact_dup` (function) `include/css_select.h:173` `css_sel *csel_compact_dup(const css_sel *sel);` -- Heap copy of *sel holding only the compounds in use (free()d by the caller); NULL on OOM or a selector with nparts...
- `csel_parse` (function) `include/css_select.h:177` `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel);` -- Parses the complex selector s[a,b) into *sel (spec computed; order/rule left to * the caller).
- `csel_matches` (function) `include/css_select.h:186` `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id, int allow_pseudo_el, int...` -- True if *sel matches element *el against its ancestor chain. target_id (optional) is the URL fragment for :target...
- `csel_element_feature_bits` (function) `include/css_select.h:194` `unsigned long long csel_element_feature_bits(const css_element *e);` -- Ancestor filter. csel_element_feature_bits: the bits of one element's tag, id and classes (two bits per feature...
- `csel_anc_reject` (function) `include/css_select.h:195` `static inline int csel_anc_reject(const css_sel *sel, const css_element *el)`
- `conservative` (function) `include/css_select.h:202` `* Pure and conservative (anything unrecognised answers 1). A selector that answers 0 matches * from the element's...`
- `identifier` (function) `include/css_select.h:208` `* A selector identifier (tag, .class, #id) is read with CSS escapes decoded * (`.md\:flex` is the class "md:flex")...`
- `csel_emit_utf8` (function) `include/css_select.h:220` `size_t csel_emit_utf8(unsigned int cp, char *out);`
- `csel_unescape` (function) `include/css_select.h:222` `void csel_unescape(char *dst, size_t cap, const char *src, size_t n);` -- A selector identifier (tag, .class, #id) is read with CSS escapes decoded (`.md\:flex` is the class "md:flex") and...
- `csel_escape_len` (function) `include/css_select.h:224` `size_t csel_escape_len(const char *s, size_t i, size_t b);` -- does not fit is FOLDED: its first CSEL_FOLD_PREFIX bytes, CSEL_FOLD_MARK (a byte no identifier contains) and 16 hex...
- `csel_ident_fold` (function) `include/css_select.h:226` `void csel_ident_fold(const char *src, size_t len, char *dst);` -- csel_ident_eq folds the element's token the same way, so a CSS Modules name such as...
- `csel_ident_eq` (function) `include/css_select.h:228` `int csel_ident_eq(const char *stored, const char *tok, size_t tlen);` -- instead of being truncated and never matching. #define CSEL_FOLD_PREFIX   40u #define CSEL_FOLD_MARK     '\x1f'...
- `csel_read_ident` (function) `include/css_select.h:231` `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower);` -- Reads an identifier at s[*ip] (escapes decoded, non-ASCII kept, lowercased when * lower != 0) into dst (CSS_TOK_MAX).
- `csel_decl_end` (function) `include/css_select.h:236` `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace);` -- Index of the ';' ending the declaration that starts at s[i] (or of a '}' when stop_brace), or b: separators inside...
- `csel_lower_ch` (function) `include/css_select.h:240` `static inline char csel_lower_ch(char c)`
- `csel_ci_eq` (function) `include/css_select.h:244` `static inline int csel_ci_eq(const char *a, const char *b)`
- `csel_ci_starts` (function) `include/css_select.h:253` `static inline int csel_ci_starts(const char *a, const char *p)` -- static inline char csel_lower_ch(char c) { return (c >= 'A' && c <= 'Z') ?
- `csel_span_eq` (function) `include/css_select.h:262` `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)` -- } return *a == '\0' && *b == '\0'; } /* True if a starts with the (lowercase) prefix p, case-insensitively. static...
- `csel_substr` (function) `include/css_select.h:273` `static inline int csel_substr(const char *hay, const char *needle, int ci)` -- Substring test (used both to drop any value carrying url() — always ci — and by * the attribute `*=` operator).
- `csel_ident_ch` (function) `include/css_select.h:281` `static inline int csel_ident_ch(char c)`

## include/css_text.h
Depends on: `include/css_decl.h`
Imported by: `src/css.c`, `src/css_text.c`, `tests/test_css_text.c`
- `ct_interp_fontfamily` (function) `include/css_text.h:10` `int ct_interp_fontfamily(const char *v);`
- `ct_interp_texttransform` (function) `include/css_text.h:11` `int ct_interp_texttransform(const char *v);`
- `ct_interp_opacity` (function) `include/css_text.h:12` `int ct_interp_opacity(const char *v);`
- `ct_interp_valign` (function) `include/css_text.h:13` `int ct_interp_valign(const char *v);`
- `ct_expand_valign` (function) `include/css_text.h:14` `int ct_expand_valign(const char *val, css_decl *dst, int cap);`
- `ct_interp_transition_property` (function) `include/css_text.h:15` `int ct_interp_transition_property(const char *v);`
- `ct_interp_whitespace` (function) `include/css_text.h:16` `int ct_interp_whitespace(const char *v);`
- `ct_interp_tabsize` (function) `include/css_text.h:17` `int ct_interp_tabsize(const char *v);`
- `ct_interp_textdeco_style` (function) `include/css_text.h:18` `int ct_interp_textdeco_style(const char *v);`
- `ct_interp_textdeco_thickness` (function) `include/css_text.h:19` `int ct_interp_textdeco_thickness(const char *v);`
- `ct_interp_aspect_ratio` (function) `include/css_text.h:20` `int ct_interp_aspect_ratio(const char *v, int *num, int *den);`
- `ct_interp_direction` (function) `include/css_text.h:21` `int ct_interp_direction(const char *v);`
- `ct_interp_liststyle` (function) `include/css_text.h:22` `int ct_interp_liststyle(const char *v);`
- `ct_interp_spacing` (function) `include/css_text.h:23` `int ct_interp_spacing(const char *v, int *out);`
- `ct_emit_spacing` (function) `include/css_text.h:24` `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val);`
- `ct_expand_shadow` (function) `include/css_text.h:25` `int ct_expand_shadow(const char *val, css_decl *dst, int cap);`

## include/css_values.h
Imported by: `gui/browser_ui.c`, `src/css.c`, `src/css_box.c`, `src/css_gradient.c`, `src/css_text.c`, `src/css_values.c`, `tests/test_css_values.c`
- `cv_parse_color` (function) `include/css_values.h:12` `int cv_parse_color(const char *v);`
- `cv_interp_color` (function) `include/css_values.h:13` `int cv_interp_color(const char *v);`
- `cv_color_ok` (function) `include/css_values.h:14` `int cv_color_ok(int c);`
- `cv_bg_alpha_of` (function) `include/css_values.h:15` `int cv_bg_alpha_of(const char *v);`
- `cv_filter_scale` (function) `include/css_values.h:20` `double cv_filter_scale(int pct);` -- The multiplier a filter() brightness/contrast/saturate percentage means (150 -> 1.5).
- `cv_parse_color_t7` (function) `include/css_values.h:24` `int cv_parse_color_t7(const char *v);` -- cv_parse_color with the color's alpha as TRANSPARENCY in bits 24..30 (0 opaque, 127 clear): an opaque color is...
- `black` (function) `include/css_values.h:27` `* transparent black (127 << 24) -- text that paints nothing, not an absent * value. CC_COLOR_CURRENT and -1...`
- `cv_interp_bg` (function) `include/css_values.h:30` `int cv_interp_bg(const char *v);`

## include/css_vars.h
Imported by: `src/css.c`, `src/css_vars.c`, `src/page_view.c`, `tests/test_css.c`, `tests/test_css_vars.c`
- `name` (function) `include/css_vars.h:62` `* name (last declaration wins). Returns 1 when stored, 0 when dropped: a name that * is not "--" + at least one...`
- `cvr_get` (function) `include/css_vars.h:69` `const char *cvr_get(const cvr_table *t, const char *name, size_t nlen);` -- The stored value for name[0,nlen), or NULL.
- `cvr_count` (function) `include/css_vars.h:71` `size_t cvr_count(const cvr_table *t);`
- `cvr_reset` (function) `include/css_vars.h:75` `void cvr_reset(cvr_table *t);` -- Frees every stored string and empties the table, keeping its arrays for reuse. * NULL-safe.
- `cvr_free` (function) `include/css_vars.h:78` `void cvr_free(cvr_table *t);` -- Frees every stored string and empties the table, keeping its arrays for reuse. * NULL-safe. void cvr_reset(cvr_table...
- `cvr_collect_decls` (function) `include/css_vars.h:83` `void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b);` -- Scans the declaration span s[a,b) for `--ident : value` pairs and stores each (a trailing !important is stripped).
- `declaration` (function) `include/css_vars.h:91` `* then drops the whole declaration (CSS Variables 1: invalid at computed time). */ int cvr_resolve(const char *val...`
- `cvr_lookup` (function) `include/css_vars.h:96` `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen);` -- The value name[0,nlen) has in scope sc (same lookup order as cvr_resolve), or * NULL.

## include/data_url.h
Imported by: `fuzz/fuzz_data_url.c`, `gui/browser_ui.c`, `src/data_url.c`, `src/render_doc.c`, `src/render_policy.c`, `src/tab.c`, `src/webfont.c`, `src/webfont_load.c`, `tests/test_data_url.c`
- `allocation` (function) `include/data_url.h:21` `* * du_base64_payload does no allocation (it only slices the caller's url string);`
- `du_is_data_url` (function) `include/data_url.h:46` `int du_is_data_url(const char *url);` -- 16 MiB of encoded text (~12 MiB decoded) -- generous for any real inline icon/ logo/image, bounding the allocation...
- `worker` (function) `include/data_url.h:59` `* the confined worker (du_decode). */ du_status du_shape_ok(const char *url);`
- `closed` (function) `include/data_url.h:65` `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/out/out_len == NULL (with b64_len !=...`

## include/disk_store.h
Depends on: `include/local_store.h`
Imported by: `src/disk_store.c`, `src/http_cache.c`, `src/profile.c`, `tests/test_disk_store.c`
- `ds_free` (function) `include/disk_store.h:47` `void ds_free(uint8_t *buf, size_t len);` -- Reads and decrypts path.

## include/doc_title.h
Imported by: `fuzz/fuzz_doc_title.c`, `gui/browser_ui.c`, `src/doc_title.c`, `tests/test_doc_title.c`
- `dt_scan` (function) `include/doc_title.h:20` `int dt_scan(const char *html, size_t len, char *out, size_t cap);` -- Writes the text of the document's first <title> into out (NUL-terminated, valid UTF-8, whitespace collapsed and...

## include/dom.h
Depends on: `include/html_parse.h`
Imported by: `fuzz/fuzz_anchor.c`, `fuzz/fuzz_dom.c`, `fuzz/fuzz_js_dom.c`, `include/anchor.h`, `include/js_dom.h`, `include/js_geom.h`, `include/page_view.h`, `src/dom.c`, `src/html_parse.c`, `src/js_dom.c`, `src/js_dom_internal.h`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/page_view.c`, `src/tab.c`, `tests/test_anchor.c`, `tests/test_dom.c`, `tests/test_js_dom.c`, `tests/test_js_env.c`, `tests/test_js_native.c`, `tests/test_page_view.c`
- `dom_free` (function) `include/dom.h:48` `void dom_free(dom_index *idx);` -- Builds the index over an already-parsed document. doc must outlive *out. doc == NULL / out == NULL =>...
- `dom_node_count` (function) `include/dom.h:51` `size_t dom_node_count(const dom_index *idx);` -- Builds the index over an already-parsed document. doc must outlive *out. doc == NULL / out == NULL =>...
- `tree` (function) `include/dom.h:59` `* tree (the index only grows, so a node a script removed is still registered and must not be * found);`
- `dom_is_connected` (function) `include/dom.h:65` `int dom_is_connected(const dom_index *idx, dom_node_id node);` -- Nonzero iff node is a valid element that is IN the document tree (a node a script * detached stays indexed but is...
- `count` (function) `include/dom.h:68` `* match count (which may exceed cap, so the caller can size a buffer). */ size_t dom_get_by_tag(const dom_index...`
- `dom_get_by_class` (function) `include/dom.h:71` `size_t dom_get_by_class(const dom_index *idx, const char *cls, dom_node_id *out, size_t cap);`
- `dom_matches` (function) `include/dom.h:100` `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector);` -- Writes up to cap matching ids (document order) into out; returns the total * match count (may exceed cap, so the...
- `dom_document_position` (function) `include/dom.h:110` `size_t dom_document_position(const dom_index *idx, dom_node_id node);` -- Nearest element at or above node matching the selector list, or DOM_NODE_NONE * (Element.closest). dom_node_id...
- `dom_precedes` (function) `include/dom.h:113` `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);` -- Nearest element at or above node matching the selector list, or DOM_NODE_NONE * (Element.closest). dom_node_id...
- `dom_tag_name` (function) `include/dom.h:127` `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);` -- int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b); /* Node at the given document-order position...
- `dom_get_attribute` (function) `include/dom.h:130` `const char *dom_get_attribute(const dom_index *idx, dom_node_id node, const char *name, size_t *len);` -- dom_node_id dom_node_at(const dom_index *idx, size_t position); /* --- navigation (element-only; DOM_NODE_NONE at...
- `dom_attribute_names` (function) `include/dom.h:137` `size_t dom_attribute_names(const dom_index *idx, dom_node_id node, const char **names, size_t *lens, size_t cap);` -- Qualified names of node's attributes, in document order, written to names[] (borrowed, valid while idx/doc are...
- `dom_text_content` (function) `include/dom.h:142` `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len);` -- Concatenated text content of node's subtree (borrowed, valid while idx/doc are * alive), or NULL. *len (optional)...
- `dom_document_title` (function) `include/dom.h:145` `const char *dom_document_title(const dom_index *idx, size_t *len);` -- Concatenated text content of node's subtree (borrowed, valid while idx/doc are * alive), or NULL. *len (optional)...
- `valid` (function) `include/dom.h:150` `* detached node stays valid (it just becomes unreachable from the root and is no * longer rendered). These never...`
- `cycle` (function) `include/dom.h:180` `* Rejects a cycle (child being an ancestor of parent). Invalid handle / self / cycle * => DOM_ERR_NULL_ARG. */...`
- `parent` (function) `include/dom.h:207` `* child of parent (for the *_REF places) or an invalid handle => DOM_ERR_NULL_ARG. */ dom_status...`
- `dom_node_kind` (function) `include/dom.h:223` `int dom_node_kind(const dom_index *idx, dom_node_id node);` -- -- text and comment nodes (spec/dom.md 9) --- Character-data nodes get LAZY handles in the same arena: registered...
- `index` (function) `include/dom.h:239` `* stays valid in the index (not freed). Invalid handle / not-a-child => DOM_ERR_NULL_ARG. */ dom_status...`
- `length` (function) `include/dom.h:264` `* length (no children => an owned empty string). Uses a chain of fixed-size * blocks internally so there is no hard...`
- `process` (function) `include/dom.h:271` `* modules in the same process (style resolution). NULL for a bad or non-element * handle. Valid until the next...`
- `sight` (function) `include/dom.h:276` `* first sight (an innerHTML subtree has no handles until something asks). Registration * is not a tree change...`

## include/dom_debug.h
Depends on: `include/render_doc.h`
Imported by: `fuzz/fuzz_dom_debug.c`, `src/dom_debug.c`, `src/freedom.c`, `tests/test_dom_debug.c`
- `dd_format` (function) `include/dom_debug.h:36` `size_t dd_format(const rd_doc *doc, char *out, size_t cap);` -- Formats doc into out[0..cap) as a NUL-terminated, line-oriented dump (see the spec for the stable format).
- `dd_format_css` (function) `include/dom_debug.h:41` `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap);` -- CSS inspector: dumps every block with its FULL resolved css_style fields as a compact property list.

## include/download.h
Imported by: `fuzz/fuzz_download.c`, `gui/browser_ui.c`, `src/download.c`, `tests/test_download.c`
- `dl_should_download` (function) `include/download.h:43` `int dl_should_download(const char *content_type, const char *content_disposition);` -- 1 if the response should be saved (attachment, or a non-renderable media type), 0 if it should be rendered.
- `literal` (function) `include/download.h:47` `* a static string literal (never freed). */ const char *dl_ext_for_type(const char *content_type);`
- `DL_ERR_OVERFLOW` (function) `include/download.h:56` `* DL_ERR_OVERFLOW (out left empty). url/content_disposition NULL => absent. */ dl_status dl_pick_name(const char...`
- `basename` (function) `include/download.h:61` `* sanitized basename (a name still containing '/' is rejected => DL_ERR_OVERFLOW, * so the path can never escape...`

## include/exact_key.h
Imported by: `fuzz/fuzz_exact_key.c`, `gui/browser_ui.c`, `src/exact_key.c`, `tests/test_exact_key.c`
- `ek_init` (function) `include/exact_key.h:24` `void ek_init(ek_key *k);` -- exact_key (ek_) -- a cache key built by OBSERVING every input of what is cached, compared byte for byte...
- `ek_reset` (function) `include/exact_key.h:27` `void ek_reset(ek_key *k);` -- /* Largest key (anti-DoS); a bigger one is marked bad and never equals anything. #define EK_MAX_BYTES ((size_t)1 <<...
- `ek_put` (function) `include/exact_key.h:31` `void ek_put(ek_key *k, const void *p, size_t len);` -- Appends len bytes of p.
- `ek_equal` (function) `include/exact_key.h:34` `int ek_equal(const ek_key *a, const ek_key *b);` -- Appends len bytes of p.
- `ek_swap` (function) `include/exact_key.h:37` `void ek_swap(ek_key *a, ek_key *b);` -- Appends len bytes of p.
- `ek_free` (function) `include/exact_key.h:40` `void ek_free(ek_key *k);` -- Appends len bytes of p.

## include/fb_cmdline.h
Imported by: `fuzz/fuzz_fb_cmdline.c`, `gui/browser_ui.c`, `src/fb_cmdline.c`, `tests/test_fb_cmdline.c`, `tests/test_js_dom.c`
- `fbc_history_init` (function) `include/fb_cmdline.h:27` `void fbc_history_init(fbc_history *h);`
- `fbc_history_free` (function) `include/fb_cmdline.h:28` `void fbc_history_free(fbc_history *h);`
- `fbc_history_push` (function) `include/fb_cmdline.h:31` `int fbc_history_push(fbc_history *h, const char *text, size_t len);` -- #define FBC_BASE_MAX   256    /* bytes of a completion base path #define FBC_LIST_NAMES 40     /* candidates shown...
- `fbc_history_prev` (function) `include/fb_cmdline.h:35` `const char *fbc_history_prev(fbc_history *h, const char *cur, size_t curlen);` -- Older entry (saves cur as the draft when leaving the live line), or NULL when there is none. * The pointer is valid...
- `fbc_history_next` (function) `include/fb_cmdline.h:38` `const char *fbc_history_next(fbc_history *h);` -- Older entry (saves cur as the draft when leaving the live line), or NULL when there is none. * The pointer is valid...
- `fbc_complete_split` (function) `include/fb_cmdline.h:42` `long fbc_complete_split(const char *text, size_t n, char *base, size_t cap, size_t *prefix_off);` -- Splits the trailing property path of text[0,n): base ("a.b" of "a.b.c", "" = global) into base[cap], * *prefix_off =...
- `fbc_names_expr` (function) `include/fb_cmdline.h:46` `size_t fbc_names_expr(const char *base, char *out, size_t cap);` -- JS expression returning the newline-joined property names reachable from the path `base` * (no getter is run).
- `fbc_complete_pick` (function) `include/fb_cmdline.h:51` `size_t fbc_complete_pick(const char *names, const char *prefix, size_t plen, char *ins, size_t ins_cap, char *list...` -- From the newline-separated `names`, those starting with prefix[0,plen): `ins` gets the longest common extension...
- `fbc_filter_passes` (function) `include/fb_cmdline.h:62` `int fbc_filter_passes(int filter, int level);`
- `fbc_filter_next` (function) `include/fb_cmdline.h:63` `int fbc_filter_next(int filter);` -- extension beyond the prefix, `list` the candidates space-separated; *count how many matched.
- `fbc_filter_label` (function) `include/fb_cmdline.h:64` `const char *fbc_filter_label(int filter);` -- the length of the insertion. size_t fbc_complete_pick(const char *names, const char *prefix, size_t plen, char *ins...

## include/fb_panes.h
Imported by: `gui/browser_ui.c`, `src/fb_cmdline.c`, `src/fb_panes.c`, `src/freedom.c`, `tests/test_fb_panes.c`, `tests/test_js_dom.c`
- `fbp_tab_label` (function) `include/fb_panes.h:34` `const char *fbp_tab_label(int tab);` -- FBP_CSS, FBP_SCRIPT, FBP_NET, FBP_PROFILE,   /* where the JS time went (sampling profiler, time-weighted)...
- `fbp_tab_from_name` (function) `include/fb_panes.h:37` `int fbp_tab_from_name(const char *name);` -- FBP_PROFILE,   /* where the JS time went (sampling profiler, time-weighted) FBP_THROWS,    /* every exception...
- `fbp_tab_wrap` (function) `include/fb_panes.h:40` `int fbp_tab_wrap(int tab, int dir);` -- FBP_STORAGE,   /* cookies, localStorage and sessionStorage of the page FBP_COUNT } fbp_tab; #define FBP_SELECTOR_MAX...
- `fbp_tab_span` (function) `include/fb_panes.h:43` `void fbp_tab_span(int tab, double cell_w, double pad_cells, double *x, double *w);` -- #define FBP_SELECTOR_MAX 256   /* bytes of the user's argument (selector / index / filter) #define FBP_EXPR_MAX...
- `fbp_tab_at` (function) `include/fb_panes.h:46` `int fbp_tab_at(double x, double cell_w, double pad_cells);` -- /* Label of a tab; an out-of-range id is the console.
- `fbp_is_pane` (function) `include/fb_panes.h:49` `int fbp_is_pane(int tab);` -- /* Tab named `name` (case-insensitive), or -1 when unknown / NULL. int fbp_tab_from_name(const char *name); /* The...
- `fbp_js_quote` (function) `include/fb_panes.h:53` `size_t fbp_js_quote(const char *s, size_t n, char *out, size_t cap);` -- JS string literal for s[0,n) (double-quoted).
- `fbp_expr` (function) `include/fb_panes.h:57` `size_t fbp_expr(int tab, const char *sel, size_t n, char *out, size_t cap);` -- The expression that fills `tab`'s panel for argument sel[0,n); NUL-terminated in out. * Returns its length, or 0 for...

## include/find_text.h
Imported by: `fuzz/fuzz_find_text.c`, `gui/browser_ui.c`, `src/find_text.c`, `tests/test_find_text.c`
- `find_text` (function) `include/find_text.h:2` `* find_text (ft_) -- find in page over the rendered text (spec/find_text.md). * * Pure: no I/O, no global state...`
- `ft_fold` (function) `include/find_text.h:35` `uint32_t ft_fold(uint32_t cp);` -- One laid-out text piece. gap_before = 1: white space separates it from the previous * piece (another line or block...
- `written` (function) `include/find_text.h:38` `* number of code points written (<= cap, <= FT_QUERY_MAX);`
- `ft_compile` (function) `include/find_text.h:39` `size_t ft_compile(const char *q, size_t qlen, uint32_t *out, size_t cap);` -- Folds the query, trims it and collapses white space to one ' ' (U+0020).
- `exist` (function) `include/find_text.h:42` `* cap matches exist (truncated may be NULL). */ ft_status ft_search(const ft_piece *pieces, size_t n, const uint32_t...`
- `ft_spans` (function) `include/find_text.h:48` `size_t ft_spans(const ft_piece *pieces, size_t n, const ft_match *m, size_t nm, ft_span *out, size_t cap);` -- Splits matches into per-piece spans (one per piece a match touches, empty spans * dropped), in order.
- `ft_step` (function) `include/find_text.h:53` `long ft_step(long cur, size_t n, int dir);` -- Next (dir > 0) or previous (dir < 0) match index with wrap-around; -1 when n == 0. * A cur outside [0, n) starts at...

## include/flex_layout.h
Imported by: `fuzz/fuzz_css.c`, `include/box_tree.h`, `src/css.c`, `src/dom_debug.c`, `src/flex_layout.c`, `src/page_view.c`, `src/tab.c`, `tests/test_css.c`, `tests/test_dom_debug.c`, `tests/test_flex_layout.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`
- `size` (function) `include/flex_layout.h:60` `* content size (px);`
- `out` (function) `include/flex_layout.h:62` `* fx_result to out (caller-owned). n == 0 is a no-op (out may be NULL). */ fx_status fx_flex_line(const fx_item...`
- `fx_grid_cell` (function) `include/flex_layout.h:74` `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col);` -- Row and column of the index-th item placed row-major into ncols columns. * ncols == 0 yields row = col = 0...
- `number` (function) `include/flex_layout.h:106` `* line number (negative counts from the end). */ #define FX_GL_AUTO 0 #define FX_GL_SPAN_BASE (1 << 20) #define...`
- `fx_grid_line_parse` (function) `include/flex_layout.h:117` `int fx_grid_line_parse(const char *v, int *start, int *end);` -- The shorthand `<side> [ / <side> ]` (no slash => end is auto).
- `fx_grid_line_resolve` (function) `include/flex_layout.h:122` `void fx_grid_line_resolve(int start, int end, int ntracks, int *pos0, int *span);` -- Resolves a start/end pair against ntracks explicit tracks: *pos0 = 0-based start track or -1 (auto-place), *span >= 1.
- `fx_autofill_count` (function) `include/flex_layout.h:129` `size_t fx_autofill_count(double avail, double gap, double minw);` -- repeat(auto-fill, minmax(min, max)): how many min-wide tracks fit in avail (CSS Grid 1 7.2.3.2; one gap between tracks).
- `fx_grid_column_count` (function) `include/flex_layout.h:139` `int fx_grid_column_count(int flow, int cols, int rows, size_t items);` -- Column count of a grid container (CSS Grid 1 8.5).
- `fx_grid_area_hash` (function) `include/flex_layout.h:163` `unsigned fx_grid_area_hash(const char *name);` -- FNV-1a of a trimmed, case-sensitive CSS identifier; never returns 0 for a non-empty name (0 is reserved for "unnamed").
- `offset` (function) `include/flex_layout.h:181` `* offset (from the content start, clamped to >= 0) to out_x[n]. The band does NOT wrap * (v1): an item that would...`
- `required` (function) `include/flex_layout.h:194` `* out_row is required (NULL with n > 0 yields FX_ERR_NULL_ARG);`
- `widths` (function) `include/flex_layout.h:204` `* the OUTER widths (width + ml + mr, clamped >= 0, so a negative margin narrows * the slot and a positive one widens...`
- `FX_ERR_NULL_ARG` (function) `include/flex_layout.h:238` `* Returns FX_ERR_NULL_ARG (a required pointer NULL with n > 0), FX_ERR_RANGE * (negative h/avail, or n > FX_MAX_ITEMS);`
- `space` (function) `include/flex_layout.h:244` `* line order: positive free space (avail - sizes - gaps) is split equally among every * auto margin...`
- `fx_auto_min_size` (function) `include/flex_layout.h:275` `double fx_auto_min_size(double min_content, double basis, double author_min, int scroll_container);` -- units as fx_item.basis.
- `fx_justify_name` (function) `include/flex_layout.h:331` `const char *fx_justify_name(fx_justify j);` -- Stable, short English name of a justify mode for structured/agent output.
- `height` (function) `include/flex_layout.h:337` `* used height (h_out);`
- `it` (function) `include/flex_layout.h:354` `* children that claim it (spec/flex_layout.md, tanda 44): proportionally to * grow[i] (x100) when any grows, else...`
- `win` (function) `include/flex_layout.h:362` `* margins win (both = centre, left only = end);`
- `fx_cross_offset` (function) `include/flex_layout.h:364` `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r);` -- Cross-axis (horizontal) offset of a column item of width w in avail px. auto margins win (both = centre, left only =...

## include/frame_broker.h
Imported by: `fuzz/fuzz_frame_broker.c`, `src/frame_broker.c`, `src/frame_host.c`, `tests/test_frame_broker.c`
- `fbk_origin_of` (function) `include/frame_broker.h:42` `int fbk_origin_of(const char *url, char *out, size_t cap);` -- Serialized origin ("https://host[:port]", lowercase) or "null" for opaque/non-https/unparseable. * 0 on success, -1...
- `fbk_init` (function) `include/frame_broker.h:45` `int fbk_init(fbk_table *t, const char *top_url);` -- Serialized origin ("https://host[:port]", lowercase) or "null" for opaque/non-https/unparseable. * 0 on success, -1...
- `fbk_add` (function) `include/frame_broker.h:49` `int fbk_add(fbk_table *t, int parent, const char *url, int *out_id);` -- Adds a child of `parent` for url.
- `fbk_remove` (function) `include/frame_broker.h:52` `void fbk_remove(fbk_table *t, int id);` -- Adds a child of `parent` for url.
- `fbk_origin` (function) `include/frame_broker.h:55` `const char *fbk_origin(const fbk_table *t, int id);` -- Adds a child of `parent` for url.

## include/frame_clock.h
Imported by: `gui/browser_ui.c`, `src/frame_clock.c`, `tests/test_frame_clock.c`
- `fc_init` (function) `include/frame_clock.h:20` `void fc_init(fc_clock *c);`
- `fc_set_active` (function) `include/frame_clock.h:21` `void fc_set_active(fc_clock *c, int active);`
- `fc_needs_tick` (function) `include/frame_clock.h:22` `int fc_needs_tick(const fc_clock *c);`
- `fc_interval_ms` (function) `include/frame_clock.h:23` `int fc_interval_ms(const fc_clock *c);`

## include/frame_host.h
Depends on: `include/page_view.h`, `include/tab.h`
Imported by: `gui/browser_ui.c`, `src/frame_host.c`, `src/freedom.c`, `tests/test_frame_host.c`
- `fh_new` (function) `include/frame_host.h:29` `fh_host *fh_new(const char *top_url, tab_fetch_fn fetch, void *fetch_ctx, fh_top_msg_fn top_msg, void *top_ctx);` -- top_url: the trusted top document; fetch/fetch_ctx: the page's policy-gated subresource fetcher (used for the frame...
- `fh_set_async` (function) `include/frame_host.h:35` `void fh_set_async(fh_host *h, int on);` -- on != 0: each FRAME_OPEN loads its frame on a background thread and fh_tick integrates it (spec/frame_broker.md...
- `fh_free` (function) `include/frame_host.h:39` `void fh_free(fh_host *h);` -- Closes every frame worker and frees the host; a frame still loading is abandoned (its thread * closes its own worker...
- `fh_apply_top` (function) `include/frame_host.h:43` `void fh_apply_top(fh_host *h, const tab_page *page);` -- Processes the frame ops (kinds FRAME_OPEN/CLOSE/POST) among page->ws of the TOP document; other * kinds are ignored.
- `fh_tick` (function) `include/frame_host.h:47` `int fh_tick(fh_host *h, int elapsed_ms);` -- Advances every frame's virtual clock by elapsed_ms and processes what they posted.
- `fh_count` (function) `include/frame_host.h:50` `int fh_count(const fh_host *h);` -- Advances every frame's virtual clock by elapsed_ms and processes what they posted.
- `it` (function) `include/frame_host.h:53` `* confined worker last built it (NULL when no live frame has that URL);`
- `fh_frame_view` (function) `include/frame_host.h:56` `const pv_view *fh_frame_view(const fh_host *h, const char *url, tab **t_out);` -- Painting (spec/frame_broker.md section 5).
- `fh_generation` (function) `include/frame_host.h:59` `unsigned fh_generation(const fh_host *h);` -- Painting (spec/frame_broker.md section 5).

## include/freebug.h
Imported by: `fuzz/fuzz_freebug.c`, `gui/browser_ui.c`, `include/js_dom.h`, `include/tab.h`, `src/fb_cmdline.c`, `src/freebug.c`, `src/freedom.c`, `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`, `src/tab.c`, `tests/test_fb_cmdline.c`, `tests/test_freebug.c`
- `fb_buffer_init` (function) `include/freebug.h:65` `void fb_buffer_init(fb_buffer *b);` -- A stored source name is truncated to this many bytes (NUL excluded).
- `truncated` (function) `include/freebug.h:69` `* A message longer than FB_MAX_ENTRY_BYTES is stored truncated (not dropped). A * dropped push raises b->overflow...`
- `copied` (function) `include/freebug.h:75` `* copied (truncated to FB_MAX_FILE_BYTES);`
- `fb_buffer_push_loc` (function) `include/freebug.h:78` `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len, const char *file, int line, int col);` -- As fb_buffer_push, but also records a source location. file (may be NULL) is copied (truncated to...
- `fb_buffer_reset` (function) `include/freebug.h:83` `void fb_buffer_reset(fb_buffer *b);` -- Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the * entry array allocation for reuse.
- `fb_buffer_free` (function) `include/freebug.h:86` `void fb_buffer_free(fb_buffer *b);` -- Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the * entry array allocation for reuse.
- `fb_buffer_count` (function) `include/freebug.h:89` `size_t fb_buffer_count(const fb_buffer *b);` -- Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the * entry array allocation for reuse.
- `fb_buffer_at` (function) `include/freebug.h:92` `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i);` -- Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the * entry array allocation for reuse.
- `fb_level_name` (function) `include/freebug.h:96` `const char *fb_level_name(int level);` -- A stable lowercase level name ("log"/"info"/"warn"/"error"/"debug"); an * out-of-range level clamps to "log".

## include/freedom_config.h
Imported by: `fuzz/fuzz_page_view.c`, `gui/browser_ui_internal.h`, `gui/ui_render.c`, `src/page_view.c`, `src/sheet_cache.c`, `src/svg_paint.c`, `src/tab.c`, `tests/test_sheet_cache.c`, `tests/test_tab.c`
- `px` (function) `include/freedom_config.h:24` `* it computes 12 px (getComputedStyle, measured on the parity host, tanda 102): the * reference renderer is what we...`

## include/group_index.h
Imported by: `fuzz/fuzz_group_index.c`, `gui/browser_ui.c`, `src/group_index.c`, `tests/test_group_index.c`
- `group_index` (function) `include/group_index.h:9` `* group_index (gi_) -- stable group-by of n items by an integer key, in CSR form, so a * per-group pass visits only...`
- `gi_build` (function) `include/group_index.h:20` `size_t gi_build(const int *keys, size_t n, size_t nkeys, size_t *offs, size_t *items);` -- Groups item i under keys[i] when 0 <= keys[i] < nkeys (other keys are left out).

## include/hls.h
Imported by: `fuzz/fuzz_hls.c`, `gui/browser_ui.c`, `include/video_controls.h`, `src/freedom.c`, `src/hls.c`, `tests/test_hls.c`
- `hls_select_variant` (function) `include/hls.h:65` `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h);` -- Selects the best variant from a multi-variant playlist.
- `resolved` (function) `include/hls.h:68` `* Writes the absolute URL into resolved (bounded by resolved_sz). Returns the * written length, or 0 on failure. */...`
- `hls_playlist_free` (function) `include/hls.h:74` `void hls_playlist_free(hls_playlist *pl);` -- Resolves a (possibly relative) segment URL against the playlist base URL.
- `media` (function) `include/hls.h:77` `* media (non-2xx status, HTML/text error body, empty). Recognises MPEG-TS (also * behind a fake image prefix, probed...`
- `domain` (function) `include/hls.h:87` `* domain (everything after the first label). Writes NUL-terminated into out and * returns the length, or 0 when...`

## include/host_conf.h
Depends on: `include/hostblock.h`
Imported by: `gui/browser_ui.c`, `src/freedom.c`, `src/host_conf.c`, `tests/test_host_conf.c`
- `hcf_search_dirs` (function) `include/host_conf.h:28` `void hcf_search_dirs(const char *env, const char *home, hcf_dirs *out);` -- Pure.
- `hcf_search_dirs_from_env` (function) `include/host_conf.h:31` `void hcf_search_dirs_from_env(hcf_dirs *out);` -- Pure.
- `hcf_load_filter` (function) `include/host_conf.h:35` `hb_set *hcf_load_filter(const hcf_dirs *dirs);` -- block.conf (BLOCK) + allow.conf (ALLOW) from every directory, cumulative.
- `hcf_load_allowlist` (function) `include/host_conf.h:39` `hb_set *hcf_load_allowlist(const hcf_dirs *dirs, const char *fname);` -- One file (js.conf, allow.conf, ...) from every directory as an ALLOW list.

## include/hostblock.h
Imported by: `gui/browser_ui.c`, `include/host_conf.h`, `src/freedom.c`, `src/hostblock.c`, `tests/test_hostblock.c`
- `hb_new` (function) `include/hostblock.h:49` `hb_set *hb_new(void);` -- } hb_list; typedef enum hb_decision { HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on...
- `hb_free` (function) `include/hostblock.h:52` `void hb_free(hb_set *s);` -- HB_ALLOW = 0,  /* the host may be contacted HB_BLOCK       /* the host is on the blocklist (and not re-enabled) }...
- `walked` (function) `include/hostblock.h:65` `* walked (the host, then without its first label, ...): any suffix on the allowlist * => HB_ALLOW (allow wins...`
- `hb_is_allowlisted` (function) `include/hostblock.h:75` `int hb_is_allowlisted(const hb_set *s, const char *host);` -- 1 iff a domain suffix of host is explicitly on the allowlist (covers subdomains), else 0.
- `hb_count` (function) `include/hostblock.h:85` `size_t hb_count(const hb_set *s, hb_list list);` -- Number of unique domains on the given list (for tests/diagnostics).

## include/hostedit.h
Imported by: `fuzz/fuzz_identity.c`, `gui/browser_ui.c`, `src/hostedit.c`, `tests/test_hostedit.c`
- `he_text_has_host` (function) `include/hostedit.h:46` `int he_text_has_host(const char *text, const char *host);` -- Returns 1 if text (the body of a hosts-format file) already lists host as a domain token on a non-comment line...
- `he_suggest` (function) `include/hostedit.h:55` `int he_suggest(const char *text, const char *query, char results[][HE_MAX_HOST + 1], int max);` -- Omnibar autocomplete: treats allow.conf (a hosts-format text) as a favorites list.
- `he_cdn_kind` (function) `include/hostedit.h:62` `he_cdn_kind_t he_cdn_kind(const char *url);`


Next: [API_p5.md](API_p5.md)
