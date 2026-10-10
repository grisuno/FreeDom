# API (page 5 of 9)
Previous: [API_p4.md](API_p4.md)

## src/box_tree.c
Depends on: `include/box_style.h`, `include/box_tree.h`, `include/compositor.h`, `include/css.h`
- `layout_block` (function) `src/box_tree.c:37` `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,
                   ...` -- Block container: stack non-none children vertically, collapsing each child's top * margin with the previous child's...
- `bt_nn` (function) `src/box_tree.c:58` `static double bt_nn(double v)` -- if (cavail < 0.0) cavail = 0.0; bt_status r = layout_node(c, cavail, depth + 1); if (r != BT_OK) return r; double...
- `wrap_reverse` (function) `src/box_tree.c:79` `*
 * wrap_reverse (node->wrap_reverse): when node->wrap is active and node->wrap_reverse
 * is no...`
- `layout_flex` (function) `src/box_tree.c:97` `static bt_status layout_flex(bt_node *node, bt_node *const *kids, size_t nk,
                    ...`
- `layout_grid` (function) `src/box_tree.c:220` `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,
                    ...` -- Grid: sized columns via flex_layout (fixed px reserved first, the rest split by fr weight; a NULL grid_track keeps...
- `layout_node` (function) `src/box_tree.c:327` `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)`
- `bt_layout` (function) `src/box_tree.c:372` `bt_status bt_layout(bt_node *root, double avail_w)`
- `assign_doc_order` (function) `src/box_tree.c:412` `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,
                  ...` -- Recursive doc_order assignment.
- `find_positioned_ancestor` (function) `src/box_tree.c:429` `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,
                       ...` -- Walk the parent_id chain from `start` to find the nearest ancestor with position != STATIC.
- `resolve_inset` (function) `src/box_tree.c:449` `static double resolve_inset(int v, int pct_pm, double basis)` -- Resolves an inset <length-percentage>: PV_LEN_UNSET or BT_LEN_AUTO with no percentage half → 0 (anchor at the...
- `inset_unset` (function) `src/box_tree.c:458` `static int inset_unset(int v, int pct_pm)` -- Stage 2b: an inset axis the author left undeclared (UNSET) or `auto`.
- `bt_containing_block` (function) `src/box_tree.c:462` `void bt_containing_block(const pv_box_def *boxes, size_t nbox, size_t i,
                        ...`
- `block` (function) `src/box_tree.c:473` `* true block (same flow neighbourhood), strictly better than zeros. NULL
     * placed keeps lega...`
- `bt_resolve_positioning` (function) `src/box_tree.c:492` `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,
                          ...`
- `bt_resolve_positioning_ex` (function) `src/box_tree.c:503` `bt_status bt_resolve_positioning_ex(const pv_box_def *boxes, size_t nbox,
                       ...`
- `oof_walk` (function) `src/box_tree.c:658` `static int oof_walk(const pv_box_def *boxes, size_t nbox, int bid, int nearest)` -- Shared walk for the Stage 2d classifiers: nearest==1 stops at the first * ABSOLUTE/FIXED box, nearest==0 remembers...
- `bt_oof_anchor` (function) `src/box_tree.c:675` `int bt_oof_anchor(const pv_box_def *boxes, size_t nbox, int bid)`
- `bt_oof_root` (function) `src/box_tree.c:679` `int bt_oof_root(const pv_box_def *boxes, size_t nbox, int bid)`
- `bt_box_hidden` (function) `src/box_tree.c:683` `int bt_box_hidden(const pv_box_def *boxes, size_t nbox, size_t bid)`
- `bt_oof_avail` (function) `src/box_tree.c:696` `double bt_oof_avail(int a, int a_pct, int b, int b_pct, double cb, int *both)`

## src/browser.c
Depends on: `include/browser.h`, `include/util.h`
- `free_page` (function) `src/browser.c:15` `static void free_page(browser_state *bs)`
- `clear_status` (function) `src/browser.c:25` `static void clear_status(browser_state *bs)` -- #include <stdlib.h> #include <string.h> static void free_page(browser_state *bs) { if (bs == NULL) return...
- `free_history` (function) `src/browser.c:30` `static void free_history(browser_state *bs)`
- `free_exceptions` (function) `src/browser.c:42` `static void free_exceptions(browser_state *bs)`
- `is_https_url` (function) `src/browser.c:51` `static int is_https_url(const char *s)`
- `is_local_path` (function) `src/browser.c:55` `static int is_local_path(const char *s)`
- `url_is_allowed` (function) `src/browser.c:60` `static int url_is_allowed(const char *url)`
- `xstrdup` (function) `src/browser.c:74` `static char *xstrdup(const char *s)`
- `cp1252_to_ucs` (function) `src/browser.c:88` `static unsigned int cp1252_to_ucs(unsigned char c)` -- Unicode scalar for a Windows-1252 byte (only meaningful for c >= 0x80).
- `utf8_encode` (function) `src/browser.c:102` `static size_t utf8_encode(unsigned int cp, char *out)` -- Encodes a BMP scalar (<= 0xFFFF) as UTF-8 into out (up to 3 bytes); returns the * byte count written.
- `browser_init` (function) `src/browser.c:156` `browser_status browser_init(browser_state *bs)`
- `browser_free` (function) `src/browser.c:167` `void browser_free(browser_state *bs)`
- `browser_set_url_bar` (function) `src/browser.c:178` `browser_status browser_set_url_bar(browser_state *bs, const char *url)`
- `browser_commit_url_bar` (function) `src/browser.c:190` `browser_status browser_commit_url_bar(browser_state *bs)`
- `browser_navigate` (function) `src/browser.c:224` `browser_status browser_navigate(browser_state *bs, const char *url)`
- `browser_push_state` (function) `src/browser.c:236` `browser_status browser_push_state(browser_state *bs, const char *url)`
- `browser_replace_state` (function) `src/browser.c:243` `browser_status browser_replace_state(browser_state *bs, const char *url)`
- `browser_entry_doc` (function) `src/browser.c:255` `int browser_entry_doc(const browser_state *bs, size_t pos)`
- `browser_doc_index` (function) `src/browser.c:260` `int browser_doc_index(const browser_state *bs)`
- `browser_back` (function) `src/browser.c:268` `browser_status browser_back(browser_state *bs)`
- `browser_forward` (function) `src/browser.c:280` `browser_status browser_forward(browser_state *bs)`
- `browser_can_back` (function) `src/browser.c:292` `int browser_can_back(const browser_state *bs)`
- `browser_can_forward` (function) `src/browser.c:296` `int browser_can_forward(const browser_state *bs)`
- `browser_current_url` (function) `src/browser.c:300` `const char *browser_current_url(const browser_state *bs)`
- `browser_url_bar_selection` (function) `src/browser.c:305` `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)`
- `browser_url_bar_delete_selection` (function) `src/browser.c:316` `int browser_url_bar_delete_selection(browser_state *bs)`
- `browser_url_bar_insert` (function) `src/browser.c:326` `browser_status browser_url_bar_insert(browser_state *bs, char c)`
- `browser_url_bar_backspace` (function) `src/browser.c:341` `browser_status browser_url_bar_backspace(browser_state *bs)`
- `browser_url_bar_delete` (function) `src/browser.c:355` `browser_status browser_url_bar_delete(browser_state *bs)`
- `browser_url_bar_move_cursor` (function) `src/browser.c:366` `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)`
- `browser_url_bar_extend_cursor` (function) `src/browser.c:376` `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)`
- `browser_url_bar_set_cursor` (function) `src/browser.c:385` `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)`
- `browser_url_bar_select_all` (function) `src/browser.c:393` `browser_status browser_url_bar_select_all(browser_state *bs)`
- `browser_url_bar_clear` (function) `src/browser.c:400` `browser_status browser_url_bar_clear(browser_state *bs)`
- `browser_set_page` (function) `src/browser.c:409` `browser_status browser_set_page(browser_state *bs, const char *title,
                           ...`
- `browser_set_status` (function) `src/browser.c:431` `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)`
- `browser_status_text` (function) `src/browser.c:445` `const char *browser_status_text(const browser_state *bs, uint64_t now_ms)`
- `host_equal` (function) `src/browser.c:453` `static int host_equal(const char *a, const char *b)`
- `browser_is_exception` (function) `src/browser.c:464` `int browser_is_exception(const browser_state *bs, const char *host)`
- `browser_add_exception` (function) `src/browser.c:472` `browser_status browser_add_exception(browser_state *bs, const char *host)`

## src/compositor.c
Depends on: `include/compositor.h`, `include/css.h`
- `cx_forms_stacking_context` (function) `src/compositor.c:16` `int cx_forms_stacking_context(const cx_style *s)`
- `cx_box_layer` (function) `src/compositor.c:34` `cx_layer cx_box_layer(const cx_style *s)`
- `eff_z` (function) `src/compositor.c:50` `static int eff_z(const cx_item *it)` -- Not a stacking context: a positioned box with z:auto still paints in the * positioned/zero layer (CSS 2.1 App E...
- `cx_item_compare` (function) `src/compositor.c:54` `int cx_item_compare(const cx_item *a, const cx_item *b)`
- `cx_sort` (function) `src/compositor.c:70` `void cx_sort(cx_item *items, size_t n)` -- Stable insertion sort: n is bounded by the caller (BT_MAX_POSITIONED), so O(n^2) is fine, and stability keeps...

## src/css.c
Depends on: `include/css.h`, `include/css_atrule.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_gradient.h`, `include/css_length.h`, `include/css_mq.h`, `include/css_select.h`, `include/css_text.h`, `include/css_values.h`, `include/css_vars.h`, `include/flex_layout.h`, `include/webfont.h`
- `emit` (function) `src/css.c:60` `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand...`
- `css_decl` (function) `src/css.c:87` `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);`
- `parse_num` (function) `src/css.c:164` `static int parse_num(const char *s, double *out, const char **endp)` -- Parses a leading non-negative number (digits + optional fraction).
- `parse_color` (function) `src/css.c:175` `static int parse_color(const char *v)` -- Delegates to the canonical CSS <number> grammar so a number means the same thing here as in a length, a colour...
- `interp_color` (function) `src/css.c:179` `static int interp_color(const char *v)`
- `through` (function) `src/css.c:195` `* at the two SHARED chokepoints every property funnels through (the generic
 * dispatch tail, and...`
- `bg_alpha_of` (function) `src/css.c:215` `static int bg_alpha_of(const char *v)` -- Alpha (4th) component of the first rgba()/hsla() call inside v, as a percent 0..100; CSS_LEN_UNSET when there is none.
- `interp_bg` (function) `src/css.c:219` `static int interp_bg(const char *v)`
- `expand_bg_image` (function) `src/css.c:227` `static int expand_bg_image(const char *val, css_decl *dst, int cap,
                           ch...`
- `expand_background` (function) `src/css.c:232` `static int expand_background(const char *val, css_decl *dst, int cap,
                           ...`
- `text` (function) `src/css.c:244` `* source text (rem_rebase, see below) rather than by threading a context here.
 *
 * Viewport uni...`
- `expand_box4` (function) `src/css.c:264` `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,
            ...`
- `expand_box2` (function) `src/css.c:269` `static int expand_box2(const char *val, int slot_start, int slot_end,
                       int ...`
- `interp_len` (function) `src/css.c:274` `static int interp_len(const char *v, int allow_auto, int *out)`
- `interp_lp` (function) `src/css.c:278` `static int interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_...`
- `lp_can_be_nonneg` (function) `src/css.c:283` `static int lp_can_be_nonneg(int px_val, int pct_pm)`
- `next_ws_token` (function) `src/css.c:287` `static int next_ws_token(const char **p, char *tok, size_t cap)`
- `interp_align` (function) `src/css.c:291` `static int interp_align(const char *v)`
- `interp_fontsize_ex` (function) `src/css.c:295` `static int interp_fontsize_ex(const char *v, int *abs_out)`
- `interp_lineheight` (function) `src/css.c:299` `static int interp_lineheight(const char *v)`
- `interp_weight` (function) `src/css.c:303` `static int interp_weight(const char *v)`
- `interp_style` (function) `src/css.c:307` `static int interp_style(const char *v)`
- `interp_textdeco` (function) `src/css.c:311` `static int interp_textdeco(const char *v)`
- `interp_display` (function) `src/css.c:315` `static int interp_display(const char *v)`
- `interp_gap` (function) `src/css.c:319` `static int interp_gap(const char *v)`
- `interp_justify` (function) `src/css.c:323` `static int interp_justify(const char *v)`
- `interp_gridcols` (function) `src/css.c:327` `static int interp_gridcols(const char *v)`
- `expand_grid_template_cols` (function) `src/css.c:331` `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)`
- `interp_fontfamily` (function) `src/css.c:337` `static int interp_fontfamily(const char *v)` -- Text-presentation family lives in css_text.c (single owner).
- `interp_texttransform` (function) `src/css.c:338` `static int interp_texttransform(const char *v)`
- `interp_opacity` (function) `src/css.c:339` `static int interp_opacity(const char *v)`
- `expand_valign` (function) `src/css.c:340` `static int expand_valign(const char *val, css_decl *dst, int cap)`
- `interp_transition_property` (function) `src/css.c:341` `static int interp_transition_property(const char *v)`
- `interp_whitespace` (function) `src/css.c:342` `static int interp_whitespace(const char *v)`
- `interp_tabsize` (function) `src/css.c:343` `static int interp_tabsize(const char *v)`
- `interp_textdeco_style` (function) `src/css.c:344` `static int interp_textdeco_style(const char *v)`
- `interp_textdeco_thickness` (function) `src/css.c:345` `static int interp_textdeco_thickness(const char *v)`
- `interp_aspect_ratio` (function) `src/css.c:346` `static int interp_aspect_ratio(const char *v, int *num, int *den)`
- `interp_direction` (function) `src/css.c:347` `static int interp_direction(const char *v)`
- `interp_liststyle` (function) `src/css.c:348` `static int interp_liststyle(const char *v)`
- `emit_spacing` (function) `src/css.c:349` `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
- `expand_shadow` (function) `src/css.c:350` `static int expand_shadow(const char *val, css_decl *dst, int cap)`
- `interp_position` (function) `src/css.c:354` `static int interp_position(const char *v)`
- `interp_boxsizing` (function) `src/css.c:363` `static int interp_boxsizing(const char *v)`
- `interp_float` (function) `src/css.c:369` `static int interp_float(const char *v)`
- `interp_clear` (function) `src/css.c:376` `static int interp_clear(const char *v)`
- `interp_visibility` (function) `src/css.c:386` `static int interp_visibility(const char *v)`
- `interp_overflow` (function) `src/css.c:393` `static int interp_overflow(const char *v)`
- `interp_cursor` (function) `src/css.c:425` `static int interp_cursor(const char *v)`
- `interp_text_overflow` (function) `src/css.c:457` `static int interp_text_overflow(const char *v)`
- `interp_word_break` (function) `src/css.c:463` `static int interp_word_break(const char *v)`
- `interp_overflow_wrap` (function) `src/css.c:471` `static int interp_overflow_wrap(const char *v)`
- `interp_border_collapse` (function) `src/css.c:479` `static int interp_border_collapse(const char *v)` -- if (csel_ci_eq(v, "break-all"))  return CSS_WB_BREAK;       /* greedy mid-line break if (csel_ci_eq(v...
- `number` (function) `src/css.c:488` `* number (no unit) as px (common in shorthand context like "10 5"). */
static int interp_border_s...`
- `interp_empty_cells` (function) `src/css.c:513` `static int interp_empty_cells(const char *v)` -- if (interp_len(tok, 0, &px) && px >= 0) { if (px > CSS_BORDER_SPACING_MAX) px = CSS_BORDER_SPACING_MAX; return px; }...
- `interp_caption_side` (function) `src/css.c:520` `static int interp_caption_side(const char *v)` -- px = css_round_clamp(num, 0, CSS_BORDER_SPACING_MAX); return px; } return -1; } /* empty-cells: show/hide. -1...
- `interp_table_layout` (function) `src/css.c:527` `static int interp_table_layout(const char *v)` -- static int interp_empty_cells(const char *v) { if (csel_ci_eq(v, "show")) return CSS_EC_SHOW; if (csel_ci_eq(v...
- `interp_font_variant` (function) `src/css.c:534` `static int interp_font_variant(const char *v)` -- static int interp_caption_side(const char *v) { if (csel_ci_eq(v, "top"))    return CSS_CS_TOP; if (csel_ci_eq(v...
- `interp_hyphens` (function) `src/css.c:542` `static int interp_hyphens(const char *v)` -- if (csel_ci_eq(v, "auto"))  return CSS_TL_AUTO; if (csel_ci_eq(v, "fixed")) return CSS_TL_FIXED; return -1; } /*...
- `interp_user_select` (function) `src/css.c:550` `static int interp_user_select(const char *v)` -- if (csel_ci_eq(v, "small-caps")) return CSS_FV_SMALL_CAPS; /* all-small-caps, petite-caps, etc: out of scope, fail...
- `interp_caret_color` (function) `src/css.c:559` `static int interp_caret_color(const char *v)` -- if (csel_ci_eq(v, "auto"))   return CSS_HY_AUTO; return -1; } /* user-select: none/text/all/auto. -1 unknown. static...
- `interp_appearance` (function) `src/css.c:571` `static int interp_appearance(const char *v)` -- appearance (CSS Basic UI 4 section 6.1).
- `interp_pointer_events` (function) `src/css.c:589` `static int interp_pointer_events(const char *v)` -- pointer-events.
- `interp_bg_repeat` (function) `src/css.c:601` `static int interp_bg_repeat(const char *v)` -- of them means "this element is a target" -- the same answer as `auto`.
- `interp_bg_size` (function) `src/css.c:611` `static int interp_bg_size(const char *v)` -- return -1; } /* background-repeat: repeat/no-repeat/repeat-x/repeat-y/space/round. -1 unknown. static int...
- `interp_bg_clip` (function) `src/css.c:618` `static int interp_bg_clip(const char *v)` -- if (csel_ci_eq(v, "repeat-x"))  return CSS_BGR_REPEAT_X; if (csel_ci_eq(v, "repeat-y"))  return CSS_BGR_REPEAT_Y; if...
- `interp_bg_origin` (function) `src/css.c:626` `static int interp_bg_origin(const char *v)` -- if (csel_ci_eq(v, "auto"))    return CSS_BGS_AUTO; if (csel_ci_eq(v, "cover"))   return CSS_BGS_COVER; if...
- `interp_bg_attachment` (function) `src/css.c:633` `static int interp_bg_attachment(const char *v)` -- if (csel_ci_eq(v, "border-box"))   return CSS_BGC_BORDER_BOX; if (csel_ci_eq(v, "padding-box"))  return...
- `interp_isolation` (function) `src/css.c:640` `static int interp_isolation(const char *v)` -- static int interp_bg_origin(const char *v) { if (csel_ci_eq(v, "padding-box"))  return CSS_BGO_PADDING_BOX; if...
- `interp_contain` (function) `src/css.c:646` `static int interp_contain(const char *v)` -- /* background-attachment: scroll/fixed/local. -1 unknown. static int interp_bg_attachment(const char *v) { if...
- `interp_content_visibility` (function) `src/css.c:667` `static int interp_content_visibility(const char *v)` -- while (*p == ' ' || *p == '\t') ++p; if (*p == '\0') break; char tok[CSS_TOK_MAX]; size_t k = 0; while (*p != '\0'...
- `interp_image_rendering` (function) `src/css.c:674` `static int interp_image_rendering(const char *v)` -- else if (csel_ci_eq(tok, "layout")) mask |= CSS_CONTAIN_LAYOUT; else if (csel_ci_eq(tok, "style"))  mask |=...
- `interp_color_scheme` (function) `src/css.c:681` `static int interp_color_scheme(const char *v)` -- static int interp_content_visibility(const char *v) { if (csel_ci_eq(v, "visible")) return CSS_CV_VISIBLE; if...
- `interp_accent_color` (function) `src/css.c:699` `static int interp_accent_color(const char *v)` -- const char *p = v; while (*p != '\0') { while (*p == ' ' || *p == '\t') ++p; if (*p == '\0') break; char...
- `interp_print_color_adjust` (function) `src/css.c:704` `static int interp_print_color_adjust(const char *v)` -- size_t k = 0; while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++; tok[k] = '\0'; if...
- `interp_forced_color_adjust` (function) `src/css.c:710` `static int interp_forced_color_adjust(const char *v)` -- return -1; } /* accent-color: auto -> CSS_LEN_AUTO; color -> 0xRRGGBB; -1 unknown. static int...
- `interp_mix_blend_mode` (function) `src/css.c:717` `static int interp_mix_blend_mode(const char *v)` -- /* print-color-adjust: economy/exact. -1 unknown. static int interp_print_color_adjust(const char *v) { if...
- `interp_object_fit` (function) `src/css.c:735` `static int interp_object_fit(const char *v)` -- if (csel_ci_eq(v, "overlay"))      return CSS_MB_OVERLAY; if (csel_ci_eq(v, "darken"))       return CSS_MB_DARKEN...
- `interp_list_style_pos` (function) `src/css.c:744` `static int interp_list_style_pos(const char *v)` -- if (csel_ci_eq(v, "color"))        return CSS_MB_COLOR; if (csel_ci_eq(v, "luminosity"))   return CSS_MB_LUMINOSITY...
- `interp_font_kerning` (function) `src/css.c:750` `static int interp_font_kerning(const char *v)` -- if (csel_ci_eq(v, "fill"))        return CSS_OFI_FILL; if (csel_ci_eq(v, "contain"))     return CSS_OFI_CONTAIN; if...
- `interp_text_rendering` (function) `src/css.c:757` `static int interp_text_rendering(const char *v)` -- /* list-style-position: inside/outside. -1 unknown. static int interp_list_style_pos(const char *v) { if...
- `interp_font_stretch` (function) `src/css.c:765` `static int interp_font_stretch(const char *v)` -- if (csel_ci_eq(v, "auto"))   return CSS_FK_AUTO; if (csel_ci_eq(v, "normal")) return CSS_FK_NORMAL; if...
- `interp_resize` (function) `src/css.c:778` `static int interp_resize(const char *v)` -- /* font-stretch: normal/condensed/expanded/etc. -1 unknown. static int interp_font_stretch(const char *v) { if...
- `interp_scroll_behavior` (function) `src/css.c:786` `static int interp_scroll_behavior(const char *v)` -- if (csel_ci_eq(v, "semi-expanded"))      return CSS_FS_SEMI_EXPANDED; if (csel_ci_eq(v, "extra-expanded"))...
- `interp_overscroll_behavior` (function) `src/css.c:808` `static int interp_overscroll_behavior(const char *v)` -- all, so every one of them behaves exactly like the default -- the same answer as `auto`.
- `interp_backface_visibility` (function) `src/css.c:815` `static int interp_backface_visibility(const char *v)` -- if (csel_ci_eq(v, "pan-x") || csel_ci_eq(v, "pan-y") || csel_ci_eq(v, "pan-left") || csel_ci_eq(v, "pan-right") ||...
- `interp_border_style` (function) `src/css.c:838` `static int interp_border_style(const char *v)`
- `interp_bwidth1` (function) `src/css.c:864` `static int interp_bwidth1(const char *v)`
- `interp_time_ms` (function) `src/css.c:873` `static int interp_time_ms(const char *v)` -- Parses a CSS time: "2s" → 2000, "500ms" → 500, "0s" → 0. * Returns -1 on invalid/missing unit.
- `emit_radius_corner` (function) `src/css.c:906` `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)` -- One corner longhand (border-top-left-radius and friends).
- `interp_bw_tok` (function) `src/css.c:914` `static int interp_bw_tok(const char *t, int *o)` -- One corner longhand (border-top-left-radius and friends).
- `interp_bs_tok` (function) `src/css.c:915` `static int interp_bs_tok(const char *t, int *o)`
- `interp_bc_tok` (function) `src/css.c:916` `static int interp_bc_tok(const char *t, int *o)`
- `expand_outline` (function) `src/css.c:981` `static int expand_outline(const char *val, css_decl *dst, int cap)`
- `interp_column_count` (function) `src/css.c:997` `static int interp_column_count(const char *v)` -- `column-count`: a positive <integer>, or `auto`.
- `interp_column_width` (function) `src/css.c:1009` `static int interp_column_width(const char *v)` -- layout, for the same reason CSS_LEN_MAX lives on the emitter: it is an * anti-DoS policy of the box model, not a...
- `expand_columns` (function) `src/css.c:1020` `static int expand_columns(const char *val, css_decl *dst, int cap)` -- `columns` shorthand: <'column-width'> || <'column-count'> in either order, one or two tokens.
- `expand_flex_flow` (function) `src/css.c:1054` `static int expand_flex_flow(const char *val, css_decl *dst, int cap)` -- `flex-flow` shorthand: the direction and the wrap keyword in either order, one or two tokens.
- `expand_column_rule` (function) `src/css.c:1076` `static int expand_column_rule(const char *val, css_decl *dst, int cap)` -- `column-rule` shorthand: same <line-width> || <line-style> || <color> grammar * as `border`/`outline`, so it reuses...
- `interp_filter_pct` (function) `src/css.c:1088` `static int interp_filter_pct(const char *s)` -- Parse a percentage (or 0..1 float) from inside a filter function's parens. * Returns 0..100 (clamped), -1 on error.
- `interp_filter_deg` (function) `src/css.c:1102` `static int interp_filter_deg(const char *s)` -- Parse a degrees value (e.g. "45deg") from inside a filter function's parens.
- `filter_paren_body` (function) `src/css.c:1117` `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)` -- Helper: extract content inside filter(...) parens.
- `item` (function) `src/css.c:1130` `* timing list takes its first item (CSS Animations/Transitions 1: with one
 * transition/animatio...`
- `anim_easing_iv` (function) `src/css.c:1169` `static int anim_easing_iv(const char *tok)` -- Named easing shared by the animation/transition timing parsers (CSS Easing 1: the five keywords...
- `is_anim_ident` (function) `src/css.c:1181` `static int is_anim_ident(const char *tok)` -- True when tok is a CSS <custom-ident> (the shape an animation-name takes): starts with a letter, underscore, hyphen...
- `declaration` (function) `src/css.c:1196` `* declaration (precedent: expand_filter);`
- `expand_animation` (function) `src/css.c:1197` `static int expand_animation(const char *val, css_decl *dst, int cap)` -- animation shorthand (CSS Animations 1 6.2): every longhand in any order in the first top-level comma item.
- `order` (function) `src/css.c:1427` `* Lengths in declaration order (dx, dy, optional blur >= 0);`
- `blur` (function) `src/css.c:1462` `* consumes ONLY blur(Npx);`
- `expand_backdrop_filter` (function) `src/css.c:1465` `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)` -- backdrop-filter / -webkit-backdrop-filter (2026-07-19, glassmorphism v1): same lax space-separated function-list...
- `axis` (function) `src/css.c:1499` `* bare center displaces it to the free axis (`center right` = x:right, y:center).
 * Any other co...`
- `expand_bg_size` (function) `src/css.c:1615` `static int expand_bg_size(const char *val, css_decl *dst, int cap)` -- background-size (CSS Backgrounds 3 section 3.9): either a keyword (cover/contain) or one-to-two...
- `emit_content` (function) `src/css.c:1655` `static int emit_content(css_decl *dst, int cap, const char *str,
                        char (*c...` -- h = (n == 2) ? comp_px[1] : CSS_LEN_AUTO; hp = (n == 2) ? comp_pm[1] : 0; /* The bare keyword keeps its own code; an...
- `cap` (function) `src/css.c:1731` `* string past the cap (emit_content): a conforming declaration must not * count as a discard just because an icon...`
- `expand_content` (function) `src/css.c:1761` `static int expand_content(const char *val, css_decl *dst, int cap,
                          char...` -- R8: content property.
- `empty` (function) `src/css.c:1765` `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and...`
- `expand_grid_areas` (function) `src/css.c:1804` `static int expand_grid_areas(const char *val, css_decl *dst, int cap,
                           ...` -- grid-template-areas (CSS Grid 1 7.3): the value is a list of quoted strings, one per grid row.
- `expand_grid_template` (function) `src/css.c:1871` `static int expand_grid_template(const char *val, css_decl *dst, int cap,
                        ...` -- grid-template: <rows> / <columns>            e.g.
- `expand_box_shadow` (function) `src/css.c:1922` `static int expand_box_shadow(const char *val, css_decl *dst, int cap)` -- box-shadow (single layer): up to four lengths in order dx, dy, blur, spread, an optional color, and an optional...
- `interp_flex_factor` (function) `src/css.c:1950` `static int interp_flex_factor(const char *v)` -- flex-grow / flex-shrink: a non-negative number stored x100 (0.5 -> 50), clamped to * [0, CSS_FLEX_FACTOR_MAX].
- `interp_flex_basis` (function) `src/css.c:1960` `static int interp_flex_basis(const char *v, int *out)` -- flex-basis: `auto`/`content` -> CSS_LEN_AUTO; a non-negative length -> px; a percentage as per-mille encoded...
- `column` (function) `src/css.c:1973` `* column (`flex: 1 1 0%`);`
- `expand_flex` (function) `src/css.c:1994` `static int expand_flex(const char *val, css_decl *dst, int cap)` -- flex shorthand -> the three contiguous P_FLEX_GROW/SHRINK/BASIS slots.
- `interp_align_kw` (function) `src/css.c:2039` `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` -- align-items / align-self / align-content / justify-items keyword. allow_auto is for * align-self; allow_dist...
- `interp_flex_direction` (function) `src/css.c:2052` `static int interp_flex_direction(const char *v)`
- `interp_box_orient` (function) `src/css.c:2070` `static int interp_box_orient(const char *v)` -- 2009 flexbox `box-orient` axis names onto `css_flex_direction`.
- `interp_flex_line_pack` (function) `src/css.c:2097` `static int interp_flex_line_pack(const char *v)` -- `flex-line-pack` (2012 align-content): the `flex-pack` vocabulary plus `stretch`, mapped onto the css_align_kw slots...
- `interp_flex_wrap` (function) `src/css.c:2107` `static int interp_flex_wrap(const char *v)`
- `interp_grid_flow` (function) `src/css.c:2115` `static int interp_grid_flow(const char *v)` -- if (csel_ci_eq(v, "justify")) return CSS_AK_SPACE_BETWEEN; if (csel_ci_eq(v, "distribute")) return...
- `interp_grid_span` (function) `src/css.c:2141` `static int interp_grid_span(const char *v)` -- grid-column / grid-row: only the `span N` form is supported -> N (clamped to * [1, CSS_GRID_SPAN_MAX]).
- `copy_trim` (function) `src/css.c:2160` `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` -- Copies s[a,b) into dst (bounded, NUL-terminated), trimming ASCII whitespace from * both ends.
- `strip_important` (function) `src/css.c:2173` `static int strip_important(char *val)` -- Strips a trailing "!important" (case-insensitive, with optional whitespace before '!' and between '!' and the...
- `var` (function) `src/css.c:2198` `* cvr_resolve then substitutes var() references when a declaration's value is
 * interpreted (par...`
- `selector_matches_root` (function) `src/css.c:2220` `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m)` -- True when the caller's root matcher (css_media.scope_match) says the selector s[a,b) matches the document's <html>...
- `tr_mul` (function) `src/css.c:2344` `static void tr_mul(double out[6], const double l[6], const double r[6])` -- Right-multiply 2D affine matrices: out = l * r (r applies first).
- `matrix` (function) `src/css.c:2357` `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands...`
- `tr_decompose` (function) `src/css.c:2364` `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,
                        in...` -- QR-decompose an affine matrix into whole px/percent/degree slots.
- `parse_matrix6` (function) `src/css.c:2387` `static int parse_matrix6(const char *p, size_t argn, double m6[6])` -- Parse matrix(a,b,c,d,e,f): six comma-separated unitless numbers.
- `split_top_args` (function) `src/css.c:2419` `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,
               ...` -- Split a top-level comma list honouring paren depth.
- `LIST` (function) `src/css.c:2442` `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose...`
- `translate3d` (function) `src/css.c:2449` `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine
 * renders z as nothing,...`
- `translateX` (function) `src/css.c:2712` `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc...`
- `parse_angle_deg` (function) `src/css.c:2716` `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);`
- `expand_transform_list` (function) `src/css.c:2719` `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);`
- `translateZ` (function) `src/css.c:2721` `* translateZ(), rotateX(0) and rotateY(0) emit the identity (with the stacking * context Firefox builds);`
- `function` (function) `src/css.c:2723` `* transform function (perspective/rotate3d/...), or unparseable syntax,
 * rejects the WHOLE decl...`
- `origin_component` (function) `src/css.c:2920` `static int origin_component(const char *tok, int axis, int *out)` -- One transform-origin component: keyword (axis-checked), a percent, or a bare zero. axis: 0 = x (left/right valid), 1...
- `expand_transform_origin` (function) `src/css.c:2946` `static int expand_transform_origin(const char *val, css_decl *dst, int cap)` -- transform-origin (M1.2c): 1-2 values; keywords and percents only (px lengths fail closed -- the parser has no box...
- `expand_gap` (function) `src/css.c:2978` `static int expand_gap(const char *val, css_decl *dst, int cap)` -- gap / grid-gap (2026-07-10): one value keeps the pre-existing semantics (both axes; row-gap stays unset and falls...
- `ignored` (function) `src/css.c:2997` `* engine slot and is ignored (documented simplification, like list-style's
 * ignored tokens). An...`
- `property` (function) `src/css.c:3032` `* error drops the whole property (fail closed). */
static int expand_clip(const char *val, css_de...`
- `font_first_name` (function) `src/css.c:3076` `static int font_first_name(const char *val, char *out, size_t cap)` -- First family name of a font-family/font value: up to the first comma, trimmed, quotes stripped -- the same entry...
- `writing` (function) `src/css.c:3109` `* Wide keywords claim BOTH slots without writing (inheritance then flows, as
 * the tail does for...`
- `shorthand` (function) `src/css.c:3151` `* generic bucket keeps the rest of the shorthand (same net effect as the
 * font-family longhand ...`
- `caller` (function) `src/css.c:3231` `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached...`
- `interpret_prop_dispatch` (function) `src/css.c:3243` `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,
   ...`
- `slots` (function) `src/css.c:3355` `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return...`
- `sentinel` (function) `src/css.c:3467` `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);`
- `wide_claim` (function) `src/css.c:3853` `static int wide_claim(const char *prop, css_decl *dst, int cap,
                      char (*urlt...` -- SHORTHAND it applies to every longhand the shorthand expands to.
- `interpret_prop` (function) `src/css.c:3893` `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,
            ...` -- The two value-level rules that hold for EVERY property, applied once around the dispatch so no per-property branch...
- `drop_copy_text` (function) `src/css.c:3920` `static void drop_copy_text(char *dst, size_t cap, const char *src)` -- Copies hostile CSS text into a fixed report buffer: bounded, NUL-terminated, truncated with a visible "..." marker...
- `drop_record` (function) `src/css.c:3939` `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)` -- Records one dropped declaration, coalescing by (property, cause).
- `raw_add` (function) `src/css.c:3965` `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)` -- Interprets one declaration span s[0,n) into dst (up to cap).
- `interpret_decls` (function) `src/css.c:4078` `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,
               ...` -- Splits a ';'-separated declaration block into dst (up to cap).
- `add_rule` (function) `src/css.c:4122` `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,
                     siz...` -- } else if (c == '"' || c == '\'') { quote = c; } else if (c == '(' || c == '[') { ++depth; } else if (c == ')' || c...
- `skip_at_rule` (function) `src/css.c:4234` `static size_t skip_at_rule(const char *s, size_t i, size_t n)` -- Skips an @-rule starting at s[i] ('@'): to the terminating ';' or past a * brace-balanced block.
- `block_end` (function) `src/css.c:4250` `static size_t block_end(const char *s, size_t open, size_t n)` -- Index just past the '}' that closes the block whose '{' is at s[open]. n if * unbalanced.
- `at_is_media` (function) `src/css.c:4272` `static int at_is_media(const char *s, size_t i, size_t n)` -- A media query list s[a,b), evaluated by the Media Queries 4 module against the render width (the only real datum...
- `at_keyword` (function) `src/css.c:4283` `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)` -- True when s[i] ('@') begins the at-keyword kw (lowercase, without '@') followed * by a delimiter.
- `csel_substr` (function) `src/css.c:4305` `return known && csel_substr(val, "var(", 1);`
- `supports_selector_ok` (function) `src/css.c:4308` `static int supports_selector_ok(void *ctx, const char *sel)`
- `supports_matches` (function) `src/css.c:4317` `static int supports_matches(const char *s, size_t a, size_t b)`
- `layer_register` (function) `src/css.c:4371` `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,
                     ...` -- Registers the layer name s[a,b) (trimmed; empty = anonymous) nested under the sheet's current layer, and returns its...
- `collect_custom_props_scoped` (function) `src/css.c:4414` `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,
                ...` -- Structure-aware custom-property collection (see the block comment above cvr_collect_decls): walks s[start,end) with...
- `parse_block` (function) `src/css.c:4489` `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                 ...` -- Parses rules in s[start,end).
- `rem_ident_ch` (function) `src/css.c:4741` `static int rem_ident_ch(char c)` -- True for a character that continues a CSS identifier, so a `rem` glued to one is * part of a name and not a unit.
- `rem_num_starts_after` (function) `src/css.c:4749` `static int rem_num_starts_after(char prev)` -- True when a number may START at a character preceded by prev -- i.e. prev cannot be part of a longer name or number.
- `rem_emit_px` (function) `src/css.c:4759` `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)` -- Appends the px equivalent of num rem.
- `rem_rebase` (function) `src/css.c:4789` `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)` -- Rewrites every `<number>rem` length in s[0,n) into `<number x rem_px>px`.
- `sheet_rewind` (function) `src/css.c:4856` `static void sheet_rewind(css_sheet *sh)` -- Rewinds a sheet to empty while keeping every allocation, so the text can be * re-parsed in place.
- `sheet_root_font_px` (function) `src/css.c:4899` `static double sheet_root_font_px(const css_sheet *sh)` -- The root element's font-size in px, as the cascade resolves it (16px when the sheet leaves the root alone).
- `strip_comments` (function) `src/css.c:4907` `static char *strip_comments(const char *text, size_t len, size_t *outlen)` -- Removes C-style block comments into a fresh NUL-terminated buffer (each comment * becomes one space).
- `var` (function) `src/css.c:4917` `* collected and forty var() declarations -- font sizes, widths, radii, the
     * whole theme -- ...`
- `css_parse` (function) `src/css.c:4942` `css_status css_parse(const char *text, size_t len, css_sheet **out)`
- `css_parse_media` (function) `src/css.c:4946` `css_status css_parse_media(const char *text, size_t len, const css_media *media,
                ...`
- `css_parse_scoped` (function) `src/css.c:4951` `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,
               ...`
- `css_parse_logged` (function) `src/css.c:4956` `css_status css_parse_logged(const char *text, size_t len, const css_media *media,
               ...`
- `css_free` (function) `src/css.c:5026` `void css_free(css_sheet *s)`
- `content_attr_of` (function) `src/css.c:5045` `static const char *content_attr_of(const css_element *el, const char *name)` -- Looks up an attribute value on the element being styled (names are stored * lowercased by css_chain; the query is...
- `apply_decl` (function) `src/css.c:5054` `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...`
- `page_view` (function) `src/css.c:5061` `* the generated text reaches page_view (which materialises it as a synthetic * run);`
- `parent` (function) `src/css.c:5093` `* property from the parent (`inherit`), and an unset non-inherited one
         * stands at its i...`
- `computed_font_size` (function) `src/css.c:5472` `static double computed_font_size(const css_style *o, const css_element *el)`
- `cand_cmp` (function) `src/css.c:5488` `static int cand_cmp(const void *pa, const void *pb)`
- `apply_var_source` (function) `src/css.c:5553` `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
        ...` -- Re-resolves one var() source ("prop\0value") against the element's scope and * applies what it interprets to...
- `apply_rule` (function) `src/css.c:5580` `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...` -- Applies one matched rule. es == NULL: the page-global meaning of every var() (markers skipped, their spans applied).
- `fold_font_relative` (function) `src/css.c:5618` `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,
                         ...` -- computed font-size.
- `css_resolve_el` (function) `src/css.c:5648` `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         ...`
- `css_resolve_el_ex` (function) `src/css.c:5657` `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,
                      ...`
- `css_resolve_pseudo` (function) `src/css.c:5663` `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)`
- `resolve_core` (function) `src/css.c:5673` `static css_style resolve_core(const css_sheet *sheet, const css_element *el,
                    ...` -- The cascade. want_pseudo 0 resolves the ELEMENT (a ::before/::after rule only hands it `content`)...
- `css_resolve` (function) `src/css.c:5882` `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                  ...`
- `NULL` (function) `src/css.c:5906` `* Sheet can be NULL (inline style, no @keyframes). */
void css_resolve_anim_keyframes(css_style *...`
- `css_font_face_count` (function) `src/css.c:5938` `size_t css_font_face_count(const css_sheet *sheet)`
- `css_font_face_at` (function) `src/css.c:5942` `int css_font_face_at(const css_sheet *sheet, size_t i,
                     char *family, size_t ...`
- `css_parse_inline` (function) `src/css.c:5952` `css_style css_parse_inline(const char *style, size_t len)`

## src/css_atrule.c
Depends on: `include/css_atrule.h`, `include/css_select.h`
- `skip_ws` (function) `src/css_atrule.c:17` `static size_t skip_ws(const char *s, size_t i, size_t b)`
- `keyword_at` (function) `src/css_atrule.c:23` `static int keyword_at(const char *s, size_t i, size_t b, const char *kw)` -- Scratch size for one declaration or selector handed to the caller.
- `close_paren` (function) `src/css_atrule.c:33` `static size_t close_paren(const char *s, size_t open, size_t b)` -- Index of the ')' matching the '(' at s[open], or b when unbalanced.
- `copy_trimmed` (function) `src/css_atrule.c:54` `static int copy_trimmed(const char *s, size_t a, size_t b, char *dst, size_t cap, int lower)` -- Copies s[a,b) trimmed into dst (cap bytes, NUL-terminated); 0 if it does not fit * or is empty. lower != 0...
- `eval_declaration` (function) `src/css_atrule.c:68` `static int eval_declaration(const char *s, size_t a, size_t b, const car_ops *ops, int *ok)` -- True when s[a,b) (inside a pair of parens) is a declaration `prop: value` * rather than a nested condition.
- `eval_in_parens` (function) `src/css_atrule.c:85` `static int eval_in_parens(const char *s, size_t *i, size_t b, const car_ops *ops,
               ...` -- while (i < b && (csel_ident_ch(s[i]) || s[i] == '-')) ++i; if (i == n0) { *ok = 0; return 0; } size_t n1 = i; i =...
- `eval_condition` (function) `src/css_atrule.c:114` `static int eval_condition(const char *s, size_t a, size_t b, const car_ops *ops,
                ...`
- `car_supports` (function) `src/css_atrule.c:141` `int car_supports(const char *s, size_t a, size_t b, const car_ops *ops)`
- `car_layer_rank` (function) `src/css_atrule.c:148` `int car_layer_rank(car_layers *L, const char *name, size_t len)`
- `car_effective_spec` (function) `src/css_atrule.c:171` `int car_effective_spec(int spec, int layer, int important)`

## src/css_box.c
Depends on: `include/css.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`
- `cb_parse_num` (function) `src/css_box.c:13` `static int cb_parse_num(const char *s, double *out, const char **endp)`
- `cb_wide_keyword` (function) `src/css_box.c:18` `static int cb_wide_keyword(const char *v)`
- `cb_copy_trim` (function) `src/css_box.c:25` `static size_t cb_copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)`
- `cb_length_px` (function) `src/css_box.c:49` `int cb_length_px(const char *v, double *px)` -- Resolves a NUL-terminated <length> token to px through the canonical resolver.
- `cb_interp_align` (function) `src/css_box.c:54` `int cb_interp_align(const char *v)`
- `cb_interp_lineheight` (function) `src/css_box.c:116` `int cb_interp_lineheight(const char *v)` -- line-height as a percent of the natural line box.
- `cb_interp_weight` (function) `src/css_box.c:137` `int cb_interp_weight(const char *v)`
- `cb_interp_style` (function) `src/css_box.c:146` `int cb_interp_style(const char *v)`
- `cb_interp_textdeco` (function) `src/css_box.c:156` `int cb_interp_textdeco(const char *v)` -- text-decoration / text-decoration-line: OR of the line keywords underline / overline / line-through found in the...
- `cb_interp_display` (function) `src/css_box.c:176` `int cb_interp_display(const char *v)`
- `cb_interp_gap` (function) `src/css_box.c:251` `int cb_interp_gap(const char *v)` -- One gap length.
- `cb_interp_justify` (function) `src/css_box.c:258` `int cb_interp_justify(const char *v)`
- `repeat` (function) `src/css_box.c:272` `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill|...) /...`
- `cb_starts_with_ci` (function) `src/css_box.c:283` `static int cb_starts_with_ci(const char *s, const char *pre)`
- `count_tracks` (function) `src/css_box.c:289` `static int count_tracks(const char *s, size_t n)`
- `track_size_of` (function) `src/css_box.c:297` `static int track_size_of(const char *tok)` -- Size of ONE track token: `<N>fr` -> -(N*100); a px/em/rem length -> px (> 0); minmax(a,b) -> the size of its max...
- `count_one_repeat` (function) `src/css_box.c:327` `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,
                      ...`
- `walk_tracks` (function) `src/css_box.c:370` `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)`
- `track_min_of` (function) `src/css_box.c:430` `static int track_min_of(const char *tok)` -- Minimum width of ONE track token for repeat(auto-fill): minmax(a,b) takes a's length; a plain track takes itself....
- `expand_auto_fill` (function) `src/css_box.c:468` `static int expand_auto_fill(const char *val, css_decl *dst, int cap)` -- repeat(auto-fill|auto-fit, <single-track pattern>) tried as a whole value: returns 1 and emits grid_cols = -min_px...
- `cb_expand_grid_template_cols` (function) `src/css_box.c:546` `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap)` -- grid-template-columns: track count PLUS the first CSS_GRID_TRACKS_MAX track sizes, emitted in lock-step (P_GRIDCOLS...
- `accepts` (function) `src/css_box.c:573` `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further...`
- `calc_skip_ws` (function) `src/css_box.c:603` `static void calc_skip_ws(calc_parser *p)`
- `calc_match_fn` (function) `src/css_box.c:610` `static int calc_match_fn(calc_parser *p, const char *name)` -- symbolically to bx_lp_px, the one place a percentage becomes pixels.
- `calc_piecewise` (function) `src/css_box.c:637` `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)` -- Shared by BOTH symbolic components: the percentage is piecewise for exactly the same reason the em derivative is...
- `calc_mathfn` (function) `src/css_box.c:652` `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` -- min()/max()/clamp() (2026-07-10): comma-separated full expressions, every argument the same shape (all lengths or...
- `min` (function) `src/css_box.c:671` `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the...`
- `calc_term` (function) `src/css_box.c:773` `static int calc_term(calc_parser *p, calc_val *out, int depth)` -- out->em = 0.0; out->pct = num; out->is_length = 1;   /* a <percentage> is dimensional, like a length ++p->i; return...
- `calc_expr` (function) `src/css_box.c:797` `static int calc_expr(calc_parser *p, calc_val *out, int depth)`
- `calc_eval_full` (function) `src/css_box.c:816` `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,
           ...` -- Evaluates the inside of a calc(...) (v[0,vlen), the "calc(" prefix and matching ")" already stripped by the caller).
- `calc_eval` (function) `src/css_box.c:832` `static int calc_eval(const char *v, size_t vlen, double *out_px)` -- The pure-length entry point: a percentage in the expression makes the result a <length-percentage>, which this...
- `calc_eval_em` (function) `src/css_box.c:839` `static int calc_eval_em(const char *v, size_t vlen, double *out_em)` -- The pure-length entry point: a percentage in the expression makes the result a <length-percentage>, which this...
- `calc_unwrap` (function) `src/css_box.c:847` `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` -- True if s (already trimmed) is a "calc(...)" call spanning the whole string (case-insensitive keyword, balanced...
- `cb_interp_len` (function) `src/css_box.c:865` `int cb_interp_len(const char *v, int allow_auto, int *out)` -- Parses one box-model length.
- `pct_slot_of` (function) `src/css_box.c:910` `static int pct_slot_of(int slot)` -- The css_pct_slot mirroring a px length slot, or -1 when the property does not accept the <length-percentage> type.
- `cb_value_em_milli` (function) `src/css_box.c:960` `int cb_value_em_milli(const char *v)` -- The font-relative derivative of `v`, in thousandths of an em, saturating at CSS_EM_MILLI_MAX.
- `cb_interp_lp` (function) `src/css_box.c:980` `int cb_interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_px, ...`
- `term` (function) `src/css_box.c:987` `* the same expression and failed closed on the percentage term (its property * may not accept one);`
- `interp_len` (function) `src/css_box.c:1156` `* this file that might hand a token to interp_len (transitively: margin/padding/
 * inset, flex-b...`
- `cb_expand_box2` (function) `src/css_box.c:1227` `int cb_expand_box2(const char *val, int slot_start, int slot_end,
                       int allo...` -- Expands a two-slot logical shorthand (margin-inline / padding-block / inset-inline: one value sets both sides, two...

## src/css_chain.c
Depends on: `include/css_chain.h`, `include/css_select.h`
- `fill_css_node` (function) `src/css_chain.c:35` `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)` -- Fills *node with element e's tag/id/class tokens (no style=, no parent link yet). * Over-long tokens are simply...
- `sibling_position` (function) `src/css_chain.c:133` `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)` -- Computes the 1-based index of n among its ELEMENT siblings and the total element-sibling count (both walks bounded...
- `sibling_type_position` (function) `src/css_chain.c:151` `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)` -- Like sibling_position but only counts siblings with the SAME local name as n. * R2: for :nth-of-type() /...
- `count_children` (function) `src/css_chain.c:179` `static int count_children(lxb_dom_node_t *n)` -- Counts ALL child nodes (elements, text, comments) of the DOM element n. * R2: for :empty matching.
- `inputs` (function) `src/css_chain.c:193` `* identical inputs (single source of truth). */
static const css_element *build_chain(lxb_dom_ele...`
- `cch_element_style_vars` (function) `src/css_chain.c:246` `css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,
                 ...`
- `cch_pseudo_style` (function) `src/css_chain.c:273` `css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,
            ...`
- `cch_element_style` (function) `src/css_chain.c:288` `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)`
- `cch_element_matches` (function) `src/css_chain.c:292` `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)`

## src/css_color.c
Depends on: `include/css_color.h`
- `ascii_lower` (function) `src/css_color.c:118` `static int ascii_lower(int c)`
- `hex_val` (function) `src/css_color.c:122` `static int hex_val(int c)`
- `normalize` (function) `src/css_color.c:131` `static int normalize(const char *token, char *out)` -- Trims surrounding ASCII spaces and lowercases into out (CC_TOKEN_MAX bytes). * Returns 0, or -1 if the trimmed token...
- `parse_hex` (function) `src/css_color.c:145` `static int parse_hex(const char *s, cc_rgb *out)` -- static int normalize(const char *token, char *out) { size_t start = 0; while (token[start] == ' ' || token[start] ==...
- `cc_round` (function) `src/css_color.c:215` `static long cc_round(double v)` -- fp += (double)(*b - '0') / scale; ++b; ++frac_digits; if (frac_digits > CC_NUMBER_MAX_DIGITS) return -1; } } if...
- `parse_component` (function) `src/css_color.c:220` `static int parse_component(const char *b, const char *e, int is_alpha, int *out)` -- Parses one rgb() component in [b, e).
- `parse_hsl_comp` (function) `src/css_color.c:253` `static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out)` -- Parses one hsl() component: H is integer 0..360, S/L are 0%..100%. * Returns 0 / -1.
- `span` (function) `src/css_color.c:325` `* span (when a slash is present) into ab/ae, and returns the component count,
 * or -1. Bounded: ...`
- `parse_func` (function) `src/css_color.c:397` `static int parse_func(const char *s, cc_rgb *out)` -- Parses the functional rgb()/rgba()/hsl()/hsla() form (lowercased token).
- `lab_comp` (function) `src/css_color.c:467` `static int lab_comp(const char *b, const char *e, double pct_ref, int is_hue, double *out)` -- One component: a <number>, a <percentage> (scaled so 100% == pct_ref), `none` * (0), or -- when is_hue -- an <angle>...
- `srgb_encode` (function) `src/css_color.c:495` `static unsigned char srgb_encode(double lin)`
- `oklab_to_rgb` (function) `src/css_color.c:502` `static void oklab_to_rgb(double L, double a, double b, cc_rgb *out)`
- `lab_to_rgb` (function) `src/css_color.c:513` `static void lab_to_rgb(double L, double a, double b, cc_rgb *out)` -- return (unsigned char)cc_round(v * 255.0); } static void oklab_to_rgb(double L, double a, double b, cc_rgb *out) {...
- `parse_lab_family` (function) `src/css_color.c:529` `static int parse_lab_family(const char *s, cc_rgb *out)` -- double fy = (L + 16.0) / 116.0, fx = a / 500.0 + fy, fz = fy - b / 200.0; double xr = (fx * fx * fx > e) ? fx * fx *...
- `named_cmp` (function) `src/css_color.c:567` `static int named_cmp(const void *key, const void *element)`
- `parse_named` (function) `src/css_color.c:573` `static int parse_named(const char *s, cc_rgb *out)`
- `cc_parse` (function) `src/css_color.c:583` `cc_status cc_parse(const char *token, cc_rgb *out)`
- `strncmp` (function) `src/css_color.c:598` `strncmp(buf, "oklab(", 6) == 0 || strncmp(buf, "oklch(", 6) == 0)`
- `cc_pack` (function) `src/css_color.c:623` `int cc_pack(cc_rgb c)`
- `cc_unpack` (function) `src/css_color.c:627` `cc_rgb cc_unpack(int packed)`

## src/css_gradient.c
Depends on: `include/css_color.h`, `include/css_decl.h`, `include/css_gradient.h`, `include/css_length.h`, `include/css_select.h`, `include/css_values.h`
- `cg_parse_num` (function) `src/css_gradient.c:12` `static int cg_parse_num(const char *s, double *out, const char **endp)`
- `cg_wide_keyword` (function) `src/css_gradient.c:17` `static int cg_wide_keyword(const char *v)`
- `gradient` (function) `src/css_gradient.c:27` `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,
 * the whole decl...`
- `find_gradient_call` (function) `src/css_gradient.c:76` `static int find_gradient_call(const char *v, const char *fn, size_t *start,
                     ...` -- Locates a gradient function call `fn` (e.g. "linear-gradient(") in v (case-insensitive; an occurrence that is the...
- `conic_prelude` (function) `src/css_gradient.c:110` `static int conic_prelude(const char *seg, int *angle)` -- conic-gradient prelude: `from <int>deg`, optionally followed by `at <pos>` (position accepted and ignored -- always...
- `grad_stop_pos` (function) `src/css_gradient.c:152` `static int grad_stop_pos(const char *pp, int conic, const char **endp)` -- One stop position after a color: `N%` -> 0-1000 (x10); conic also accepts `Ndeg` -> the same 0-1000 turn fraction...
- `CSS_GRAD_STOPS_MAX` (function) `src/css_gradient.c:183` `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when
 * the gradient fai...`
- `emit_gradient` (function) `src/css_gradient.c:290` `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,
                         ...` -- Emits the gradient decl group. nstops == 0 emits only the explicit reset * (P_BG_GRAD_N = 0), which is how a...
- `find_radial_gradient` (function) `src/css_gradient.c:347` `static int find_radial_gradient(const char *v, size_t *start, size_t *end,
                      ...` -- R5c: detects radial-gradient(circle at center, color1, color2).
- `pool` (function) `src/css_gradient.c:388` `* pool (gradient explicitly reset);`
- `downstream` (function) `src/css_gradient.c:392` `* happens downstream (render_doc.c), gated by caps.images like an <img>. */
int cg_expand_bg_imag...`
- `declaration` (function) `src/css_gradient.c:451` `* declaration (fail closed);`
- `bg_layer_tokens_ok` (function) `src/css_gradient.c:458` `static int bg_layer_tokens_ok(const char *s)` -- True iff every token of s (split on whitespace, '/' and ',') is a valid non-colour component of a background layer...
- `cg_expand_background` (function) `src/css_gradient.c:498` `int cg_expand_background(const char *val, css_decl *dst, int cap,
                             ch...`

## src/css_length.c
Depends on: `include/css.h`, `include/css_length.h`
- `know` (function) `src/css_length.c:7` `* this module cannot know (real font metrics, the viewport) arrives through
 * cl_ctx rather than...`
- `cl_unit_eq` (function) `src/css_length.c:30` `static int cl_unit_eq(const char *unit, size_t len, const char *lit)` -- ASCII case-insensitive compare of a possibly-unterminated unit slice against a lowercase literal.
- `cl_font_size` (function) `src/css_length.c:56` `static double cl_font_size(const cl_ctx *ctx)` -- The element's font-size, falling back to the CSS initial value when the caller left it unset.
- `cl_root_font_size` (function) `src/css_length.c:60` `static double cl_root_font_size(const cl_ctx *ctx)`
- `cl_metric_or` (function) `src/css_length.c:67` `static double cl_metric_or(double measured, double ratio, const cl_ctx *ctx)` -- A font metric, or the fallback the spec itself names for when that metric is unavailable -- expressed as a ratio of...
- `cl_viewport_scale` (function) `src/css_length.c:80` `static int cl_viewport_scale(const char *u, size_t len, const cl_ctx *ctx, double *per)` -- Viewport-relative units (section 6.2).
- `cl_ctx_initial` (function) `src/css_length.c:100` `cl_ctx cl_ctx_initial(void)`
- `cl_unit_scale` (function) `src/css_length.c:117` `cl_status cl_unit_scale(const char *unit, size_t unit_len,
                        const cl_ctx *...`
- `cl_is_length_unit` (function) `src/css_length.c:167` `int cl_is_length_unit(const char *unit, size_t unit_len)`
- `cl_unit_is_font_relative` (function) `src/css_length.c:174` `int cl_unit_is_font_relative(const char *unit, size_t unit_len)`
- `cl_em_refit` (function) `src/css_length.c:219` `double cl_em_refit(double px, double em, double from_font_size, double font_size)`
- `cl_parse_number` (function) `src/css_length.c:233` `static int cl_parse_number(const char **pp, const char *end, double *out)` -- Parses a CSS <number> (CSS Syntax 4.3.12) without strtod -- strtod is locale-dependent, and a locale whose decimal...
- `cl_number` (function) `src/css_length.c:292` `int cl_number(const char *s, double *out, const char **endp)`
- `cl_resolve_core` (function) `src/css_length.c:309` `static cl_status cl_resolve_core(const char *value, const cl_ctx *ctx, cl_lp *out)` -- The shared core of cl_resolve and cl_resolve_lp: tokenize <number><unit> and resolve it into the two components of a...
- `cl_resolve` (function) `src/css_length.c:377` `cl_status cl_resolve(const char *value, const cl_ctx *ctx, double *out_px)`
- `cl_resolve_lp` (function) `src/css_length.c:391` `cl_status cl_resolve_lp(const char *value, const cl_ctx *ctx, cl_lp *out)`
- `cl_lp_used` (function) `src/css_length.c:395` `double cl_lp_used(cl_lp lp, double basis)`


Next: [API_p6.md](API_p6.md)
