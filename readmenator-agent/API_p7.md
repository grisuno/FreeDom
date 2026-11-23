# API (page 7 of 13)
Previous: [API_p6.md](API_p6.md)

## src/css.c
Depends on: `include/css.h`, `include/css_atrule.h`, `include/css_box.h`, `include/css_color.h`, `include/css_decl.h`, `include/css_gradient.h`, `include/css_index.h`, `include/css_length.h`, `include/css_mask.h`, `include/css_mq.h`, `include/css_select.h`, `include/css_text.h`, `include/css_values.h`, `include/css_vars.h`, `include/flex_layout.h`, `include/interp.h`, `include/webfont.h`
- `emit` (function) `src/css.c:64` `* * It must exceed the most slots ANY single declaration can emit (the widest today * is the `background` shorthand...`
- `css_decl` (function) `src/css.c:91` `* text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL);`
- `parse_num` (function) `src/css.c:188` `static int parse_num(const char *s, double *out, const char **endp)` -- Parses a leading non-negative number (digits + optional fraction).
- `parse_color` (function) `src/css.c:199` `static int parse_color(const char *v)` -- Delegates to the canonical CSS <number> grammar so a number means the same thing here as in a length, a colour...
- `interp_color` (function) `src/css.c:203` `static int interp_color(const char *v)`
- `through` (function) `src/css.c:219` `* at the two SHARED chokepoints every property funnels through (the generic
 * dispatch tail, and...`
- `bg_alpha_of` (function) `src/css.c:243` `static int bg_alpha_of(const char *v)` -- Alpha (4th) component of the first rgba()/hsla() call inside v, as a percent 0..100; CSS_LEN_UNSET when there is none.
- `interp_bg` (function) `src/css.c:247` `static int interp_bg(const char *v)`
- `expand_bg_image` (function) `src/css.c:255` `static int expand_bg_image(const char *val, css_decl *dst, int cap,
                           ch...`
- `expand_bg_position` (function) `src/css.c:260` `static int expand_bg_position(const char *val, css_decl *dst, int cap);`
- `expand_background` (function) `src/css.c:263` `static int expand_background(const char *val, css_decl *dst, int cap,
                           ...`
- `text` (function) `src/css.c:275` `* source text (rem_rebase, see below) rather than by threading a context here.
 *
 * Viewport uni...`
- `expand_box4` (function) `src/css.c:295` `static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,
            ...`
- `expand_box2` (function) `src/css.c:300` `static int expand_box2(const char *val, int slot_start, int slot_end,
                       int ...`
- `interp_len` (function) `src/css.c:305` `static int interp_len(const char *v, int allow_auto, int *out)`
- `interp_lp` (function) `src/css.c:309` `static int interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_...`
- `lp_can_be_nonneg` (function) `src/css.c:314` `static int lp_can_be_nonneg(int px_val, int pct_pm)`
- `next_ws_token` (function) `src/css.c:318` `static int next_ws_token(const char **p, char *tok, size_t cap)`
- `interp_align` (function) `src/css.c:322` `static int interp_align(const char *v)`
- `interp_fontsize_ex` (function) `src/css.c:326` `static int interp_fontsize_ex(const char *v, int *abs_out)`
- `interp_lineheight` (function) `src/css.c:340` `static int interp_lineheight(const char *v)`
- `interp_weight` (function) `src/css.c:344` `static int interp_weight(const char *v)`
- `interp_style` (function) `src/css.c:348` `static int interp_style(const char *v)`
- `interp_textdeco` (function) `src/css.c:352` `static int interp_textdeco(const char *v)`
- `interp_display` (function) `src/css.c:356` `static int interp_display(const char *v)`
- `interp_gap` (function) `src/css.c:360` `static int interp_gap(const char *v)`
- `interp_justify` (function) `src/css.c:364` `static int interp_justify(const char *v)`
- `expand_grid_template_cols` (function) `src/css.c:368` `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)`
- `interp_fontfamily` (function) `src/css.c:374` `static int interp_fontfamily(const char *v)` -- Text-presentation family lives in css_text.c (single owner).
- `interp_texttransform` (function) `src/css.c:375` `static int interp_texttransform(const char *v)`
- `interp_opacity` (function) `src/css.c:376` `static int interp_opacity(const char *v)`
- `expand_valign` (function) `src/css.c:377` `static int expand_valign(const char *val, css_decl *dst, int cap)`
- `interp_transition_property` (function) `src/css.c:378` `static int interp_transition_property(const char *v)`
- `interp_whitespace` (function) `src/css.c:379` `static int interp_whitespace(const char *v)`
- `interp_tabsize` (function) `src/css.c:380` `static int interp_tabsize(const char *v)`
- `interp_textdeco_style` (function) `src/css.c:381` `static int interp_textdeco_style(const char *v)`
- `interp_textdeco_thickness` (function) `src/css.c:382` `static int interp_textdeco_thickness(const char *v)`
- `interp_aspect_ratio` (function) `src/css.c:383` `static int interp_aspect_ratio(const char *v, int *num, int *den)`
- `interp_direction` (function) `src/css.c:384` `static int interp_direction(const char *v)`
- `interp_liststyle` (function) `src/css.c:385` `static int interp_liststyle(const char *v)`
- `emit_spacing` (function) `src/css.c:386` `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
- `expand_shadow` (function) `src/css.c:387` `static int expand_shadow(const char *val, css_decl *dst, int cap)`
- `interp_position` (function) `src/css.c:391` `static int interp_position(const char *v)`
- `interp_boxsizing` (function) `src/css.c:400` `static int interp_boxsizing(const char *v)`
- `interp_float` (function) `src/css.c:406` `static int interp_float(const char *v)`
- `interp_clear` (function) `src/css.c:413` `static int interp_clear(const char *v)`
- `interp_visibility` (function) `src/css.c:423` `static int interp_visibility(const char *v)`
- `interp_overflow` (function) `src/css.c:430` `static int interp_overflow(const char *v)`
- `interp_cursor` (function) `src/css.c:462` `static int interp_cursor(const char *v)`
- `interp_text_overflow` (function) `src/css.c:494` `static int interp_text_overflow(const char *v)`
- `interp_word_break` (function) `src/css.c:500` `static int interp_word_break(const char *v)`
- `interp_overflow_wrap` (function) `src/css.c:508` `static int interp_overflow_wrap(const char *v)`
- `interp_border_collapse` (function) `src/css.c:516` `static int interp_border_collapse(const char *v)` -- if (csel_ci_eq(v, "break-all"))  return CSS_WB_BREAK;       /* greedy mid-line break if (csel_ci_eq(v...
- `number` (function) `src/css.c:525` `* number (no unit) as px (common in shorthand context like "10 5"). */
static int interp_border_s...`
- `interp_empty_cells` (function) `src/css.c:550` `static int interp_empty_cells(const char *v)` -- if (interp_len(tok, 0, &px) && px >= 0) { if (px > CSS_BORDER_SPACING_MAX) px = CSS_BORDER_SPACING_MAX; return px; }...
- `interp_caption_side` (function) `src/css.c:557` `static int interp_caption_side(const char *v)` -- px = css_round_clamp(num, 0, CSS_BORDER_SPACING_MAX); return px; } return -1; } /* empty-cells: show/hide. -1...
- `interp_table_layout` (function) `src/css.c:564` `static int interp_table_layout(const char *v)` -- static int interp_empty_cells(const char *v) { if (csel_ci_eq(v, "show")) return CSS_EC_SHOW; if (csel_ci_eq(v...
- `interp_font_variant` (function) `src/css.c:571` `static int interp_font_variant(const char *v)` -- static int interp_caption_side(const char *v) { if (csel_ci_eq(v, "top"))    return CSS_CS_TOP; if (csel_ci_eq(v...
- `interp_hyphens` (function) `src/css.c:579` `static int interp_hyphens(const char *v)` -- if (csel_ci_eq(v, "auto"))  return CSS_TL_AUTO; if (csel_ci_eq(v, "fixed")) return CSS_TL_FIXED; return -1; } /*...
- `interp_user_select` (function) `src/css.c:587` `static int interp_user_select(const char *v)` -- if (csel_ci_eq(v, "small-caps")) return CSS_FV_SMALL_CAPS; /* all-small-caps, petite-caps, etc: out of scope, fail...
- `interp_caret_color` (function) `src/css.c:596` `static int interp_caret_color(const char *v)` -- if (csel_ci_eq(v, "auto"))   return CSS_HY_AUTO; return -1; } /* user-select: none/text/all/auto. -1 unknown. static...
- `interp_appearance` (function) `src/css.c:608` `static int interp_appearance(const char *v)` -- appearance (CSS Basic UI 4 section 6.1).
- `interp_pointer_events` (function) `src/css.c:626` `static int interp_pointer_events(const char *v)` -- pointer-events.
- `interp_bg_repeat` (function) `src/css.c:638` `static int interp_bg_repeat(const char *v)` -- of them means "this element is a target" -- the same answer as `auto`.
- `interp_bg_repeat2` (function) `src/css.c:649` `static int interp_bg_repeat2(const char *v)` -- Two-value background-repeat (CSS Backgrounds 3 3.4): `repeat no-repeat` is * repeat-x, `no-repeat repeat` is...
- `layer` (function) `src/css.c:670` `* first layer (the one painted) -- so `background: url(x) no-repeat` stops tiling
 * and a later ...`
- `expand_background_layer` (function) `src/css.c:679` `static int expand_background_layer(const char *val, css_decl *dst, int cap)`
- `first_comma_item` (function) `src/css.c:753` `static void first_comma_item(const char *val, char *buf, size_t cap);` -- The mask layer shares the background layer's geometry vocabulary (CSS Masking 1 7.4-7.6 define...
- `bg_to_mask_slot` (function) `src/css.c:755` `static int bg_to_mask_slot(int prop)`
- `remap_to_mask` (function) `src/css.c:769` `static int remap_to_mask(css_decl *dst, int n)`
- `expand_mask_geometry` (function) `src/css.c:778` `static int expand_mask_geometry(const char *prop, const char *val, css_decl *dst, int cap)`
- `emit_mask_image` (function) `src/css.c:797` `static int emit_mask_image(const char *prop, const char *val, css_decl *dst, int cap,
           ...` -- mask / mask-image with a url(): the URL into the image pool (gated downstream like a background-image; a data: SVG...
- `interp_bg_size` (function) `src/css.c:816` `static int interp_bg_size(const char *v)` -- dst[n].prop = P_MASK_URL; dst[n].ival = -1; if (has && urltab != NULL && *nurl < urlcap) { memcpy(urltab[*nurl], u...
- `interp_bg_clip` (function) `src/css.c:823` `static int interp_bg_clip(const char *v)` -- +n; if (strcmp(prop, "mask") == 0 && !css_wide_keyword(val)) n += remap_to_mask(dst + n...
- `interp_bg_origin` (function) `src/css.c:831` `static int interp_bg_origin(const char *v)` -- if (csel_ci_eq(v, "auto"))    return CSS_BGS_AUTO; if (csel_ci_eq(v, "cover"))   return CSS_BGS_COVER; if...
- `interp_bg_attachment` (function) `src/css.c:838` `static int interp_bg_attachment(const char *v)` -- if (csel_ci_eq(v, "border-box"))   return CSS_BGC_BORDER_BOX; if (csel_ci_eq(v, "padding-box"))  return...
- `interp_isolation` (function) `src/css.c:845` `static int interp_isolation(const char *v)` -- static int interp_bg_origin(const char *v) { if (csel_ci_eq(v, "padding-box"))  return CSS_BGO_PADDING_BOX; if...
- `interp_contain` (function) `src/css.c:851` `static int interp_contain(const char *v)` -- /* background-attachment: scroll/fixed/local. -1 unknown. static int interp_bg_attachment(const char *v) { if...
- `interp_content_visibility` (function) `src/css.c:872` `static int interp_content_visibility(const char *v)` -- while (*p == ' ' || *p == '\t') ++p; if (*p == '\0') break; char tok[CSS_TOK_MAX]; size_t k = 0; while (*p != '\0'...
- `interp_image_rendering` (function) `src/css.c:879` `static int interp_image_rendering(const char *v)` -- else if (csel_ci_eq(tok, "layout")) mask |= CSS_CONTAIN_LAYOUT; else if (csel_ci_eq(tok, "style"))  mask |=...
- `interp_color_scheme` (function) `src/css.c:886` `static int interp_color_scheme(const char *v)` -- static int interp_content_visibility(const char *v) { if (csel_ci_eq(v, "visible")) return CSS_CV_VISIBLE; if...
- `interp_accent_color` (function) `src/css.c:904` `static int interp_accent_color(const char *v)` -- const char *p = v; while (*p != '\0') { while (*p == ' ' || *p == '\t') ++p; if (*p == '\0') break; char...
- `interp_print_color_adjust` (function) `src/css.c:909` `static int interp_print_color_adjust(const char *v)` -- size_t k = 0; while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++; tok[k] = '\0'; if...
- `interp_forced_color_adjust` (function) `src/css.c:915` `static int interp_forced_color_adjust(const char *v)` -- return -1; } /* accent-color: auto -> CSS_LEN_AUTO; color -> 0xRRGGBB; -1 unknown. static int...
- `interp_mix_blend_mode` (function) `src/css.c:922` `static int interp_mix_blend_mode(const char *v)` -- /* print-color-adjust: economy/exact. -1 unknown. static int interp_print_color_adjust(const char *v) { if...
- `interp_object_pos` (function) `src/css.c:945` `static int interp_object_pos(const char *v)` -- object-position: <position> restricted to keywords and percentages (a length would need the free space at paint...
- `interp_object_fit` (function) `src/css.c:987` `static int interp_object_fit(const char *v)`
- `interp_list_style_pos` (function) `src/css.c:996` `static int interp_list_style_pos(const char *v)` -- y = swap ? pm[0] : pm[1]; } return CSS_OBJPOS_PACK(x, y); } static int interp_object_fit(const char *v) { if...
- `interp_font_kerning` (function) `src/css.c:1002` `static int interp_font_kerning(const char *v)` -- if (csel_ci_eq(v, "fill"))        return CSS_OFI_FILL; if (csel_ci_eq(v, "contain"))     return CSS_OFI_CONTAIN; if...
- `interp_text_rendering` (function) `src/css.c:1009` `static int interp_text_rendering(const char *v)` -- /* list-style-position: inside/outside. -1 unknown. static int interp_list_style_pos(const char *v) { if...
- `interp_font_stretch` (function) `src/css.c:1017` `static int interp_font_stretch(const char *v)` -- if (csel_ci_eq(v, "auto"))   return CSS_FK_AUTO; if (csel_ci_eq(v, "normal")) return CSS_FK_NORMAL; if...
- `interp_resize` (function) `src/css.c:1030` `static int interp_resize(const char *v)` -- /* font-stretch: normal/condensed/expanded/etc. -1 unknown. static int interp_font_stretch(const char *v) { if...
- `interp_scroll_behavior` (function) `src/css.c:1038` `static int interp_scroll_behavior(const char *v)` -- if (csel_ci_eq(v, "semi-expanded"))      return CSS_FS_SEMI_EXPANDED; if (csel_ci_eq(v, "extra-expanded"))...
- `interp_overscroll_behavior` (function) `src/css.c:1060` `static int interp_overscroll_behavior(const char *v)` -- all, so every one of them behaves exactly like the default -- the same answer as `auto`.
- `interp_backface_visibility` (function) `src/css.c:1067` `static int interp_backface_visibility(const char *v)` -- if (csel_ci_eq(v, "pan-x") || csel_ci_eq(v, "pan-y") || csel_ci_eq(v, "pan-left") || csel_ci_eq(v, "pan-right") ||...
- `interp_border_style` (function) `src/css.c:1090` `static int interp_border_style(const char *v)`
- `interp_bwidth1` (function) `src/css.c:1116` `static int interp_bwidth1(const char *v)`
- `interp_time_ms` (function) `src/css.c:1125` `static int interp_time_ms(const char *v)` -- Parses a CSS time: "2s" → 2000, "500ms" → 500, "0s" → 0. * Returns -1 on invalid/missing unit.
- `emit_radius_corner` (function) `src/css.c:1158` `static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val)` -- One corner longhand (border-top-left-radius and friends).
- `interp_bw_tok` (function) `src/css.c:1166` `static int interp_bw_tok(const char *t, int *o)` -- One corner longhand (border-top-left-radius and friends).
- `interp_bs_tok` (function) `src/css.c:1167` `static int interp_bs_tok(const char *t, int *o)`
- `interp_border_color` (function) `src/css.c:1170` `static int interp_border_color(const char *v)` -- A border color keeps its alpha as transparency in bits 24..30 (cv_parse_color_t7), the * encoding box-shadow already...
- `interp_bc_tok` (function) `src/css.c:1171` `static int interp_bc_tok(const char *t, int *o)`
- `interp_outline_style` (function) `src/css.c:1239` `static int interp_outline_style(const char *v)` -- `outline-style: auto` (CSS UI 4 section 3.3) is the UA focus ring.
- `expand_outline` (function) `src/css.c:1244` `static int expand_outline(const char *val, css_decl *dst, int cap)`
- `interp_column_count` (function) `src/css.c:1270` `static int interp_column_count(const char *v)` -- `column-count`: a positive <integer>, or `auto`.
- `interp_column_width` (function) `src/css.c:1282` `static int interp_column_width(const char *v)` -- layout, for the same reason CSS_LEN_MAX lives on the emitter: it is an * anti-DoS policy of the box model, not a...
- `expand_columns` (function) `src/css.c:1293` `static int expand_columns(const char *val, css_decl *dst, int cap)` -- `columns` shorthand: <'column-width'> || <'column-count'> in either order, one or two tokens.
- `expand_flex_flow` (function) `src/css.c:1327` `static int expand_flex_flow(const char *val, css_decl *dst, int cap)` -- `flex-flow` shorthand: the direction and the wrap keyword in either order, one or two tokens.
- `expand_column_rule` (function) `src/css.c:1349` `static int expand_column_rule(const char *val, css_decl *dst, int cap)` -- `column-rule` shorthand: same <line-width> || <line-style> || <color> grammar * as `border`/`outline`, so it reuses...
- `interp_filter_pct` (function) `src/css.c:1361` `static int interp_filter_pct(const char *s)` -- Parse a percentage (or 0..1 float) from inside a filter function's parens. * Returns 0..100 (clamped), -1 on error.
- `interp_filter_deg` (function) `src/css.c:1375` `static int interp_filter_deg(const char *s)` -- Parse a degrees value (e.g. "45deg") from inside a filter function's parens.
- `filter_paren_body` (function) `src/css.c:1390` `static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen)` -- Helper: extract content inside filter(...) parens.
- `item` (function) `src/css.c:1403` `* timing list takes its first item (CSS Animations/Transitions 1: with one
 * transition/animatio...`
- `easing_steps` (function) `src/css.c:1474` `static int easing_steps(const char *tok)`
- `anim_easing_iv` (function) `src/css.c:1496` `static int anim_easing_iv(const char *tok)`
- `is_anim_ident` (function) `src/css.c:1513` `static int is_anim_ident(const char *tok)` -- True when tok is a CSS <custom-ident> (the shape an animation-name takes): starts with a letter, underscore, hyphen...
- `expand_animation` (function) `src/css.c:1529` `static int expand_animation(const char *val, css_decl *dst, int cap)` -- animation shorthand (CSS Animations 1 6.2): every longhand in any order in the first top-level comma item.
- `order` (function) `src/css.c:1755` `* declaration order (dx, dy, optional blur >= 0);`
- `blur` (function) `src/css.c:1791` `* consumes ONLY blur(Npx);`
- `expand_backdrop_filter` (function) `src/css.c:1794` `static int expand_backdrop_filter(const char *val, css_decl *dst, int cap)` -- backdrop-filter / -webkit-backdrop-filter (2026-07-19, glassmorphism v1): same lax space-separated function-list...
- `axis` (function) `src/css.c:1828` `* bare center displaces it to the free axis (`center right` = x:right, y:center).
 * Any other co...`
- `expand_bg_size` (function) `src/css.c:1944` `static int expand_bg_size(const char *val, css_decl *dst, int cap)` -- background-size (CSS Backgrounds 3 section 3.9): either a keyword (cover/contain) or one-to-two...
- `emit_content` (function) `src/css.c:1984` `static int emit_content(css_decl *dst, int cap, const char *str,
                        char (*c...` -- h = (n == 2) ? comp_px[1] : CSS_LEN_AUTO; hp = (n == 2) ? comp_pm[1] : 0; /* The bare keyword keeps its own code; an...
- `cap` (function) `src/css.c:2060` `* string past the cap (emit_content): a conforming declaration must not * count as a discard just because an icon...`
- `expand_counter_decls` (function) `src/css.c:2091` `static int expand_counter_decls(const char *prop, const char *val, css_decl *dst, int cap,
      ...` -- counter-reset / counter-increment: validated here (hostile text), stored VERBATIM in the content pool and re-parsed...
- `expand_content` (function) `src/css.c:2109` `static int expand_content(const char *val, css_decl *dst, int cap,
                          char...` -- R8: content property.
- `empty` (function) `src/css.c:2113` `* the slot with an explicit empty (ival -1) instead of dropping, or a * lower-priority string would leak through and...`
- `expand_grid_areas` (function) `src/css.c:2160` `static int expand_grid_areas(const char *val, css_decl *dst, int cap,
                           ...` -- grid-template-areas (CSS Grid 1 7.3): the value is a list of quoted strings, one per grid row.
- `expand_grid_area_lines` (function) `src/css.c:2188` `static int expand_grid_area_lines(const char *val, css_decl *dst, int cap)` -- grid-area on an ITEM.
- `expand_grid_line` (function) `src/css.c:2213` `static int expand_grid_line(const char *val, css_decl *dst, int cap, int p_start, int p_end)` -- if (!fx_grid_line_side(part, &side[k])) return 0; if (slash == NULL) break; p = slash + 1; if (k == 3) return 0...
- `expand_grid_area` (function) `src/css.c:2222` `static int expand_grid_area(const char *val, css_decl *dst, int cap)`
- `expand_grid_template` (function) `src/css.c:2261` `static int expand_grid_template(const char *val, css_decl *dst, int cap,
                        ...` -- grid-template: <rows> / <columns>            e.g.
- `sel_list_comma` (function) `src/css.c:2306` `static size_t sel_list_comma(const char *s, size_t i, size_t end);`
- `box_shadow_layer` (function) `src/css.c:2313` `static int box_shadow_layer(const char *val, size_t len, int out[6])` -- One box-shadow layer: up to four lengths in order dx, dy, blur, spread, an optional color, and an optional `inset`...
- `declaration` (function) `src/css.c:2349` `* invalid layer drops the whole declaration (fail closed). `none` is an explicit
 * no-shadow. ur...`
- `interp_flex_factor` (function) `src/css.c:2391` `static int interp_flex_factor(const char *v)` -- flex-grow / flex-shrink: a non-negative number stored x100 (0.5 -> 50), clamped to * [0, CSS_FLEX_FACTOR_MAX].
- `interp_flex_basis` (function) `src/css.c:2401` `static int interp_flex_basis(const char *v, int *out)` -- flex-basis: `auto`/`content` -> CSS_LEN_AUTO; a non-negative length -> px; a percentage as per-mille encoded...
- `column` (function) `src/css.c:2414` `* column (`flex: 1 1 0%`);`
- `expand_flex` (function) `src/css.c:2435` `static int expand_flex(const char *val, css_decl *dst, int cap)` -- flex shorthand -> the three contiguous P_FLEX_GROW/SHRINK/BASIS slots.
- `interp_align_kw` (function) `src/css.c:2480` `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` -- align-items / align-self / align-content / justify-items keyword. allow_auto is for * align-self; allow_dist...
- `interp_flex_direction` (function) `src/css.c:2504` `static int interp_flex_direction(const char *v)`
- `interp_box_orient` (function) `src/css.c:2522` `static int interp_box_orient(const char *v)` -- 2009 flexbox `box-orient` axis names onto `css_flex_direction`.
- `interp_flex_line_pack` (function) `src/css.c:2549` `static int interp_flex_line_pack(const char *v)` -- `flex-line-pack` (2012 align-content): the `flex-pack` vocabulary plus `stretch`, mapped onto the css_align_kw slots...
- `interp_flex_wrap` (function) `src/css.c:2559` `static int interp_flex_wrap(const char *v)`
- `interp_grid_flow` (function) `src/css.c:2567` `static int interp_grid_flow(const char *v)` -- if (csel_ci_eq(v, "justify")) return CSS_AK_SPACE_BETWEEN; if (csel_ci_eq(v, "distribute")) return...
- `copy_trim` (function) `src/css.c:2585` `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` -- Copies s[a,b) into dst (bounded, NUL-terminated), trimming ASCII whitespace from * both ends.
- `strip_important` (function) `src/css.c:2598` `static int strip_important(char *val)` -- Strips a trailing "!important" (case-insensitive, with optional whitespace before '!' and between '!' and the...
- `var` (function) `src/css.c:2623` `* cvr_resolve then substitutes var() references when a declaration's value is
 * interpreted (par...`
- `has_double_dash` (function) `src/css.c:2645` `static int has_double_dash(const char *p, size_t n)` -- True when the caller's root matcher (css_media.scope_match) says the selector s[a,b) matches the document's <html>...
- `subject_may_be_root` (function) `src/css.c:2654` `static int subject_may_be_root(const char *s, size_t a, size_t b, const char *root_scope)`
- `selector_matches_root` (function) `src/css.c:2702` `static int selector_matches_root(const char *s, size_t a, size_t b, const css_media *m,
         ...`
- `tr_mul` (function) `src/css.c:2831` `static void tr_mul(double out[6], const double l[6], const double r[6])` -- Right-multiply 2D affine matrices: out = l * r (r applies first).
- `matrix` (function) `src/css.c:2844` `* * Contract: the matrix() branch's math, shared so the single-function and * list paths cannot disagree. Skew lands...`
- `tr_decompose` (function) `src/css.c:2851` `static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,
                        in...` -- QR-decompose an affine matrix into whole px/percent/degree slots.
- `parse_numlist` (function) `src/css.c:2874` `static int parse_numlist(const char *p, size_t argn, double *m6, int count)` -- Parse matrix(a,b,c,d,e,f): six comma-separated unitless numbers.
- `parse_matrix6` (function) `src/css.c:2897` `static int parse_matrix6(const char *p, size_t argn, double m6[6])`
- `split_top_args` (function) `src/css.c:2910` `static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,
               ...` -- Split a top-level comma list honouring paren depth.
- `LIST` (function) `src/css.c:2933` `* transform FUNCTION LIST (CSS Transforms 1 3). * * Contract: space-separated functions apply in order and compose...`
- `translate3d` (function) `src/css.c:2940` `* translate3d()/translateZ() flatten to their 2D projection (a 2D engine
 * renders z as nothing,...`
- `translateX` (function) `src/css.c:3251` `* translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %, * viewport units and bare non-calc...`
- `parse_angle_deg` (function) `src/css.c:3255` `* parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to * whole degrees);`
- `expand_transform_list` (function) `src/css.c:3258` `* LISTS compose in order through expand_transform_list (CSS Transforms 1 3);`
- `translateZ` (function) `src/css.c:3260` `* translateZ(), rotateX(0) and rotateY(0) emit the identity (with the stacking * context Firefox builds);`
- `function` (function) `src/css.c:3262` `* transform function (perspective/rotate3d/...), or unparseable syntax,
 * rejects the WHOLE decl...`
- `origin_component` (function) `src/css.c:3463` `static int origin_component(const char *tok, int axis, int *out)` -- One transform-origin component: keyword (axis-checked), a percent, or a bare zero. axis: 0 = x (left/right valid), 1...
- `expand_transform_origin` (function) `src/css.c:3489` `static int expand_transform_origin(const char *val, css_decl *dst, int cap)` -- transform-origin (M1.2c): 1-2 values; keywords and percents only (px lengths fail closed -- the parser has no box...
- `expand_gap` (function) `src/css.c:3521` `static int expand_gap(const char *val, css_decl *dst, int cap)` -- gap / grid-gap (2026-07-10): one value keeps the pre-existing semantics (both axes; row-gap stays unset and falls...
- `shorthand` (function) `src/css.c:3545` `* An uninterpretable token drops the whole shorthand (fail closed). */
static int expand_place(co...`
- `property` (function) `src/css.c:3580` `* error drops the whole property (fail closed). */
static int expand_clip(const char *val, css_de...`
- `expand_clip_path` (function) `src/css.c:3624` `static int expand_clip_path(const char *val, css_decl *dst, int cap)` -- clip-path (CSS Masking 1 3).
- `font_list_alias` (function) `src/css.c:3671` `static void font_list_alias(const css_sheet *sheet, const char *ls, char *out, size_t cap)` -- Copies the normalized family list `ls` into out, replacing every name that matches a local()-only @font-face of the...
- `font_list_norm` (function) `src/css.c:3705` `static int font_list_norm(const char *val, char *out, size_t cap)`
- `writing` (function) `src/css.c:3749` `* Wide keywords claim BOTH slots without writing (inheritance then flows, as
 * the tail does for...`
- `shorthand` (function) `src/css.c:3791` `* generic bucket keeps the rest of the shorthand (same net effect as the
 * font-family longhand ...`
- `caller` (function) `src/css.c:3871` `* left to the caller (parse_one_decl stamps it). */ /* `known` (optional) reports whether the property NAME reached...`
- `multiplying` (function) `src/css.c:3888` `* instead of the two multiplying (no page measured needs both on one element).
 * A third (z) com...`
- `is_inert_prop` (function) `src/css.c:3941` `static int is_inert_prop(const char *prop)` -- Properties that are valid CSS but change nothing in a static, non-interactive render: scrolling affordances...
- `interpret_prop_dispatch` (function) `src/css.c:3964` `static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,
   ...`
- `slots` (function) `src/css.c:4154` `* expand to several slots (border / box-shadow / outline / flex). */ if (strcmp(prop, "top") == 0) return...`
- `sentinel` (function) `src/css.c:4294` `* cascade carries as the currentColor sentinel (in `color` the two are the * same thing);`
- `here` (function) `src/css.c:4507` `* servers have no form here (fail closed). */ int o = csel_ci_eq(val, "none") ? CSS_SVG_PAINT_NONE : interp_color(val);`
- `wide_claim` (function) `src/css.c:4767` `static int wide_claim(const char *prop, css_decl *dst, int cap,
                      char (*urlt...` -- SHORTHAND it applies to every longhand the shorthand expands to.
- `interpret_prop` (function) `src/css.c:4807` `static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,
            ...` -- The two value-level rules that hold for EVERY property, applied once around the dispatch so no per-property branch...
- `drop_copy_text` (function) `src/css.c:4836` `static void drop_copy_text(char *dst, size_t cap, const char *src)` -- Copies hostile CSS text into a fixed report buffer: bounded, NUL-terminated, truncated with a visible "..." marker...
- `drop_record` (function) `src/css.c:4855` `static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause)` -- Records one dropped declaration, coalescing by (property, cause).
- `raw_add` (function) `src/css.c:4881` `static int raw_add(css_sheet *sh, const char *a, size_t al, const char *b, size_t bl)` -- Interprets one declaration span s[0,n) into dst (up to cap).
- `interpret_decls` (function) `src/css.c:5000` `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,
               ...` -- Splits a ';'-separated declaration block into dst (up to cap).
- `sheet_pools_reserve` (function) `src/css.c:5058` `static void sheet_pools_reserve(css_sheet *sh)`
- `add_rule` (function) `src/css.c:5064` `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,
                     siz...` -- while (nc - n < CSS_POOL_HEADROOM && nc < hard_cap) nc *= 2; if (nc > hard_cap) nc = hard_cap; char...
- `skip_at_rule` (function) `src/css.c:5178` `static size_t skip_at_rule(const char *s, size_t i, size_t n)` -- Skips an @-rule starting at s[i] ('@'): to the terminating ';' or past a * brace-balanced block.
- `block_end` (function) `src/css.c:5194` `static size_t block_end(const char *s, size_t open, size_t n)` -- Index just past the '}' that closes the block whose '{' is at s[open]. n if * unbalanced.
- `at_is_media` (function) `src/css.c:5216` `static int at_is_media(const char *s, size_t i, size_t n)` -- A media query list s[a,b), evaluated by the Media Queries 4 module against the render width (the only real datum...
- `at_keyword` (function) `src/css.c:5227` `static int at_keyword(const char *s, size_t i, size_t n, const char *kw)` -- True when s[i] ('@') begins the at-keyword kw (lowercase, without '@') followed * by a delimiter.
- `csel_substr` (function) `src/css.c:5249` `return known && csel_substr(val, "var(", 1);`
- `supports_selector_ok` (function) `src/css.c:5252` `static int supports_selector_ok(void *ctx, const char *sel)`
- `supports_matches` (function) `src/css.c:5261` `static int supports_matches(const char *s, size_t a, size_t b)`
- `cq_register` (function) `src/css.c:5319` `static int cq_register(css_sheet *sh, const char *text, size_t len, int max_w)` -- Records an @container prelude under the condition the parser is inside and returns * its 1-based id, or 0 when it...
- `cq_holds` (function) `src/css.c:5341` `static int cq_holds(const css_sheet *sheet, int id, const cmq_container *scope)` -- Every @container condition from id outward holds for an element whose ancestor containers are `scope`.
- `layer_register` (function) `src/css.c:5355` `static int layer_register(css_sheet *sh, const char *s, size_t a, size_t b,
                     ...` -- Registers the layer name s[a,b) (trimmed; empty = anonymous) nested under the sheet's current layer, and returns its...
- `collect_custom_props_scoped` (function) `src/css.c:5398` `static void collect_custom_props_scoped(const char *s, size_t start, size_t end,
                ...` -- Structure-aware custom-property collection (see the block comment above cvr_collect_decls): walks s[start,end) with...
- `parse_block` (function) `src/css.c:5480` `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                 ...` -- Parses rules in s[start,end).
- `download` (function) `src/css.c:5657` `* the download (spec/webfont.md b3b). An empty src_url
                     * simply never resolv...`
- `rem_ident_ch` (function) `src/css.c:5789` `static int rem_ident_ch(char c)` -- True for a character that continues a CSS identifier, so a `rem` glued to one is * part of a name and not a unit.
- `rem_num_starts_after` (function) `src/css.c:5797` `static int rem_num_starts_after(char prev)` -- True when a number may START at a character preceded by prev -- i.e. prev cannot be part of a longer name or number.
- `rem_emit_px` (function) `src/css.c:5807` `static int rem_emit_px(char *out, size_t cap, size_t *o, double px)` -- Appends the px equivalent of num rem.
- `len_unit_px` (function) `src/css.c:5837` `static double len_unit_px(const char *u, size_t len, const len_rebase_ctx *c)` -- px per unit for a unit identifier u[0,len) under c, or 0 when c leaves it alone.
- `len_rebase` (function) `src/css.c:5867` `static char *len_rebase(const char *s, size_t n, const len_rebase_ctx *c, size_t *outlen)` -- width family) in s[0,n) into `<number x scale>px`.
- `rem_rebase` (function) `src/css.c:5933` `static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen)`
- `sheet_index` (function) `src/css.c:5941` `static void sheet_index(css_sheet *sh)` -- Rewinds a sheet to empty while keeping every allocation, so the text can be * re-parsed in place.
- `sheet_rewind` (function) `src/css.c:5946` `static void sheet_rewind(css_sheet *sh)`
- `sheet_root_font_px` (function) `src/css.c:5993` `static double sheet_root_font_px(const css_sheet *sh)` -- The root element's font-size in px, as the cascade resolves it (16px when the sheet leaves the root alone).
- `strip_comments` (function) `src/css.c:6001` `static char *strip_comments(const char *text, size_t len, size_t *outlen)` -- Removes C-style block comments into a fresh NUL-terminated buffer (each comment * becomes one space).
- `var` (function) `src/css.c:6011` `* collected and forty var() declarations -- font sizes, widths, radii, the
     * whole theme -- ...`
- `css_parse` (function) `src/css.c:6036` `css_status css_parse(const char *text, size_t len, css_sheet **out)`
- `css_parse_media` (function) `src/css.c:6040` `css_status css_parse_media(const char *text, size_t len, const css_media *media,
                ...`
- `css_parse_scoped` (function) `src/css.c:6045` `css_status css_parse_scoped(const char *text, size_t len, const css_media *media,
               ...`
- `css_parse_logged` (function) `src/css.c:6050` `css_status css_parse_logged(const char *text, size_t len, const css_media *media,
               ...`
- `consumer` (function) `src/css.c:6084` `* consumer (shorthands, calc(), var() values) gets it with no context
         * threaded through...`
- `css_free` (function) `src/css.c:6142` `void css_free(css_sheet *s)`
- `content_attr_of` (function) `src/css.c:6167` `static const char *content_attr_of(const css_element *el, const char *name)` -- Looks up an attribute value on the element being styled (names are stored * lowercased by css_chain; the query is...
- `apply_decl` (function) `src/css.c:6176` `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...`
- `page_view` (function) `src/css.c:6183` `* the generated text reaches page_view (which materialises it as a synthetic * run);`
- `parent` (function) `src/css.c:6216` `* property from the parent (`inherit`), and an unset non-inherited one
         * stands at its i...`
- `css_ua_heading_em` (function) `src/css.c:6671` `double css_ua_heading_em(int level)`
- `css_computed_font_size_for_tag` (function) `src/css.c:6676` `double css_computed_font_size_for_tag(const css_style *o, double inherited_px, const char *tag)`
- `computed_font_size` (function) `src/css.c:6684` `static double computed_font_size(const css_style *o, const css_element *el)`
- `cand_cmp` (function) `src/css.c:6701` `static int cand_cmp(const void *pa, const void *pb)`
- `apply_var_source` (function) `src/css.c:6766` `static void apply_var_source(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
        ...` -- Re-resolves one var() source ("prop\0value") against the element's scope and * applies what it interprets to...
- `apply_rule` (function) `src/css.c:6793` `static void apply_rule(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
              ...` -- Applies one matched rule. es == NULL: the page-global meaning of every var() (markers skipped, their spans applied).
- `fold_font_relative` (function) `src/css.c:6831` `static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,
                         ...` -- computed font-size.
- `css_resolve_el` (function) `src/css.c:6862` `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         ...`
- `css_resolve_el_ex` (function) `src/css.c:6871` `css_style css_resolve_el_ex(const css_sheet *sheet, const css_element *el,
                      ...`
- `pseudo_of` (function) `src/css.c:6878` `static int pseudo_of(int which)` -- return css_resolve_el_ex(sheet, el, inline_style, inline_len, NULL); } static css_style resolve_core(const css_sheet...
- `css_resolve_pseudo` (function) `src/css.c:6887` `css_style css_resolve_pseudo(const css_sheet *sheet, const css_element *el, int which)`
- `resolve_core` (function) `src/css.c:6898` `static css_style resolve_core(const css_sheet *sheet, const css_element *el,
                    ...` -- The cascade. want_pseudo 0 resolves the ELEMENT (a ::before/::after rule only hands it `content`)...
- `css_resolve` (function) `src/css.c:7160` `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                  ...`
- `NULL` (function) `src/css.c:7184` `* Sheet can be NULL (inline style, no @keyframes). */
void css_resolve_anim_keyframes(css_style *...`
- `css_font_face_count` (function) `src/css.c:7216` `size_t css_font_face_count(const css_sheet *sheet)`
- `css_font_face_at` (function) `src/css.c:7220` `int css_font_face_at(const css_sheet *sheet, size_t i,
                     char *family, size_t ...`
- `css_parse_inline` (function) `src/css.c:7230` `css_style css_parse_inline(const char *style, size_t len)`
- `css_sheet_uses_containers` (function) `src/css.c:7234` `int css_sheet_uses_containers(const css_sheet *sheet)`
- `css_sheet_uses_counters` (function) `src/css.c:7238` `int css_sheet_uses_counters(const css_sheet *sheet)`

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
- `RELATIVE` (function) `src/css_box.c:63` `* or RELATIVE (of the inherited size). Absolute: px/pt/rem/viewport units and the * absolute keywords. Relative: em...`
- `cb_interp_fontsize_ex` (function) `src/css_box.c:72` `int cb_interp_fontsize_ex(const char *v, int *abs_out)`
- `cb_interp_lineheight` (function) `src/css_box.c:145` `int cb_interp_lineheight(const char *v)` -- line-height as a percent of the natural line box.
- `cb_interp_weight` (function) `src/css_box.c:194` `int cb_interp_weight(const char *v)`
- `cb_interp_style` (function) `src/css_box.c:203` `int cb_interp_style(const char *v)`
- `cb_interp_textdeco` (function) `src/css_box.c:213` `int cb_interp_textdeco(const char *v)` -- text-decoration / text-decoration-line: OR of the line keywords underline / overline / line-through found in the...
- `cb_interp_display` (function) `src/css_box.c:233` `int cb_interp_display(const char *v)`
- `cb_interp_gap` (function) `src/css_box.c:313` `int cb_interp_gap(const char *v)` -- One gap length.
- `cb_interp_justify` (function) `src/css_box.c:320` `int cb_interp_justify(const char *v)`
- `repeat` (function) `src/css_box.c:341` `* repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern). * repeat(auto-fill|...) /...`
- `cb_starts_with_ci` (function) `src/css_box.c:352` `static int cb_starts_with_ci(const char *s, const char *pre)`
- `count_tracks` (function) `src/css_box.c:358` `static int count_tracks(const char *s, size_t n)`
- `track_size_of` (function) `src/css_box.c:366` `static int track_size_of(const char *tok)` -- Size of ONE track token: `<N>fr` -> -(N*100); a px/em/rem length -> px (> 0); minmax(a,b) -> the size of its max...
- `count_one_repeat` (function) `src/css_box.c:396` `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,
                      ...`
- `walk_tracks` (function) `src/css_box.c:439` `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)`
- `track_min_of` (function) `src/css_box.c:507` `static int track_min_of(const char *tok)` -- Minimum width of ONE track token for repeat(auto-fill): minmax(a,b) takes a's length; a plain track takes itself....
- `expand_auto_fill` (function) `src/css_box.c:545` `static int expand_auto_fill(const char *val, css_decl *dst, int cap)` -- repeat(auto-fill|auto-fit, <single-track pattern>) tried as a whole value: returns 1 and emits grid_cols = -min_px...
- `cb_expand_grid_template_cols` (function) `src/css_box.c:623` `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap)` -- grid-template-columns: track count PLUS the first CSS_GRID_TRACKS_MAX track sizes, emitted in lock-step (P_GRIDCOLS...
- `cb_expand_grid_template_rows` (function) `src/css_box.c:646` `int cb_expand_grid_template_rows(const char *val, css_decl *dst, int cap)`
- `accepts` (function) `src/css_box.c:706` `* itself accepts (no %: this engine has no containing block to resolve it * against, so calc() cannot reach further...`
- `calc_skip_ws` (function) `src/css_box.c:739` `static void calc_skip_ws(calc_parser *p)`
- `calc_match_fn` (function) `src/css_box.c:746` `static int calc_match_fn(calc_parser *p, const char *name)` -- bare0: the token was a unitless 0.
- `calc_piecewise` (function) `src/css_box.c:773` `static double calc_piecewise(const calc_val *args, int nargs, int want_pct)` -- Shared by BOTH symbolic components: the percentage is piecewise for exactly the same reason the em derivative is...
- `calc_mathfn` (function) `src/css_box.c:788` `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` -- min()/max()/clamp() (2026-07-10): comma-separated full expressions, every argument the same shape (all lengths or...
- `min` (function) `src/css_box.c:807` `* without the basis: min(50%, 600px) would compare a px half of 0 against 600 * and pick 0, i.e. collapse the...`
- `calc_term` (function) `src/css_box.c:911` `static int calc_term(calc_parser *p, calc_val *out, int depth)` -- out->pct = num; out->is_length = 1;   /* a <percentage> is dimensional, like a length ++p->i; return 1; } out->px =...
- `calc_expr` (function) `src/css_box.c:938` `static int calc_expr(calc_parser *p, calc_val *out, int depth)`
- `calc_eval_full` (function) `src/css_box.c:960` `static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,
           ...` -- Evaluates the inside of a calc(...) (v[0,vlen), the "calc(" prefix and matching ")" already stripped by the caller).
- `calc_eval_em` (function) `src/css_box.c:974` `static int calc_eval_em(const char *v, size_t vlen, double *out_em)` -- static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em, double *out_pct) { calc_parser...
- `calc_unwrap` (function) `src/css_box.c:982` `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` -- True if s (already trimmed) is a "calc(...)" call spanning the whole string (case-insensitive keyword, balanced...
- `cb_math_length_px` (function) `src/css_box.c:1033` `int cb_math_length_px(const char *v, double *px)`
- `cb_interp_len` (function) `src/css_box.c:1042` `int cb_interp_len(const char *v, int allow_auto, int *out)`
- `pct_slot_of` (function) `src/css_box.c:1071` `static int pct_slot_of(int slot)` -- The css_pct_slot mirroring a px length slot, or -1 when the property does not accept the <length-percentage> type.
- `cb_value_em_milli` (function) `src/css_box.c:1121` `int cb_value_em_milli(const char *v)` -- The font-relative derivative of `v`, in thousandths of an em, saturating at CSS_EM_MILLI_MAX.
- `cb_clip_inset` (function) `src/css_box.c:1141` `int cb_clip_inset(const char *val, int px[4], int pm[4])`
- `cb_interp_lp` (function) `src/css_box.c:1175` `int cb_interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_px, ...`
- `term` (function) `src/css_box.c:1182` `* the same expression and failed closed on the percentage term (its property * may not accept one);`
- `interp_len` (function) `src/css_box.c:1351` `* this file that might hand a token to interp_len (transitively: margin/padding/
 * inset, flex-b...`
- `cb_expand_box2` (function) `src/css_box.c:1422` `int cb_expand_box2(const char *val, int slot_start, int slot_end,
                       int allo...` -- Expands a two-slot logical shorthand (margin-inline / padding-block / inset-inline: one value sets both sides, two...

## src/css_chain.c
Depends on: `include/css_chain.h`, `include/css_select.h`
- `cls_space` (function) `src/css_chain.c:42` `static int cls_space(char c)`
- `release_nodes` (function) `src/css_chain.c:90` `static void release_nodes(cch_node *nodes, int n)` -- memcpy(buf, v, n); buf[n] = '\0'; size_t nc = 0; for (size_t i = 0; i < n && nc < cap_tok; ) { while (i < n &&...
- `fill_css_node` (function) `src/css_chain.c:99` `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)` -- Fills *node with element e's tag/id/class tokens (no style=, no parent link yet). * Over-long tokens are simply...
- `sibling_position` (function) `src/css_chain.c:181` `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)` -- Computes the 1-based index of n among its ELEMENT siblings and the total element-sibling count (both walks bounded...
- `sibling_type_position` (function) `src/css_chain.c:199` `static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib)` -- Like sibling_position but only counts siblings with the SAME local name as n. * R2: for :nth-of-type() /...
- `count_children` (function) `src/css_chain.c:227` `static int count_children(lxb_dom_node_t *n)` -- Counts ALL child nodes (elements, text, comments) of the DOM element n. * R2: for :empty matching.
- `inputs` (function) `src/css_chain.c:241` `* identical inputs (single source of truth). */
static const css_element *build_chain(lxb_dom_ele...`
- `cch_element_style_vars` (function) `src/css_chain.c:310` `css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,
                 ...`
- `cch_path_new` (function) `src/css_chain.c:353` `cch_path *cch_path_new(void)`
- `path_truncate` (function) `src/css_chain.c:357` `static void path_truncate(cch_path *pa, int keep)`
- `cch_path_free` (function) `src/css_chain.c:365` `void cch_path_free(cch_path *pa)`
- `cch_element_style_path` (function) `src/css_chain.c:372` `css_style cch_element_style_path(cch_path *pa, lxb_dom_element_t *el, const css_sheet *sheet,
   ...`
- `cch_pseudo_style` (function) `src/css_chain.c:442` `css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,
            ...`
- `cch_element_style` (function) `src/css_chain.c:461` `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)`
- `cch_element_matches` (function) `src/css_chain.c:465` `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)`
- `cch_element_matches_any` (function) `src/css_chain.c:479` `int cch_element_matches_any(lxb_dom_element_t *el, const css_sel *sels, size_t n)`

## src/css_color.c
Depends on: `include/css_color.h`
- `ascii_lower` (function) `src/css_color.c:119` `static int ascii_lower(int c)`
- `hex_val` (function) `src/css_color.c:123` `static int hex_val(int c)`
- `normalize` (function) `src/css_color.c:132` `static int normalize(const char *token, char *out)` -- Trims surrounding ASCII spaces and lowercases into out (CC_TOKEN_MAX bytes). * Returns 0, or -1 if the trimmed token...
- `parse_hex` (function) `src/css_color.c:146` `static int parse_hex(const char *s, cc_rgb *out)` -- static int normalize(const char *token, char *out) { size_t start = 0; while (token[start] == ' ' || token[start] ==...
- `cc_cws` (function) `src/css_color.c:226` `static void cc_cws(cc_cp *c)`
- `cc_cfactor` (function) `src/css_color.c:229` `static int cc_cfactor(cc_cp *c, cc_cv *out, int depth)`
- `cc_cterm` (function) `src/css_color.c:250` `static int cc_cterm(cc_cp *c, cc_cv *out, int depth)`
- `cc_cexpr` (function) `src/css_color.c:269` `static int cc_cexpr(cc_cp *c, cc_cv *out, int depth)`
- `cc_fold_calc` (function) `src/css_color.c:285` `static int cc_fold_calc(const char **b, const char **e, char *buf, size_t cap)` -- When [*b, *e) is exactly one calc(...), folds it into buf (cap bytes) and repoints the span there.
- `cc_round` (function) `src/css_color.c:305` `static long cc_round(double v)` -- cc_cv r; if (cc_cfactor(&c, &r, 0) != 0) return -1; cc_cws(&c); if (c.p != y || r.v != r.v) return -1; if (r.v >...
- `parse_component` (function) `src/css_color.c:310` `static int parse_component(const char *b, const char *e, int is_alpha, int *out)` -- Parses one rgb() component in [b, e).
- `parse_hsl_comp` (function) `src/css_color.c:343` `static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out)` -- Parses one hsl() component: H is integer 0..360, S/L are 0%..100%. * Returns 0 / -1.
- `span` (function) `src/css_color.c:431` `* span (when a slash is present) into ab/ae, and returns the component count,
 * or -1. Bounded: ...`
- `parse_func` (function) `src/css_color.c:508` `static int parse_func(const char *s, cc_rgb *out)` -- Parses the functional rgb()/rgba()/hsl()/hsla() form (lowercased token).
- `lab_comp` (function) `src/css_color.c:581` `static int lab_comp(const char *b, const char *e, double pct_ref, int is_hue, double *out)` -- One component: a <number>, a <percentage> (scaled so 100% == pct_ref), `none` * (0), or -- when is_hue -- an <angle>...
- `srgb_encode` (function) `src/css_color.c:609` `static unsigned char srgb_encode(double lin)`
- `oklab_to_rgb` (function) `src/css_color.c:616` `static void oklab_to_rgb(double L, double a, double b, cc_rgb *out)`
- `lab_to_rgb` (function) `src/css_color.c:627` `static void lab_to_rgb(double L, double a, double b, cc_rgb *out)` -- return (unsigned char)cc_round(v * 255.0); } static void oklab_to_rgb(double L, double a, double b, cc_rgb *out) {...
- `parse_lab_family` (function) `src/css_color.c:643` `static int parse_lab_family(const char *s, cc_rgb *out)` -- double fy = (L + 16.0) / 116.0, fx = a / 500.0 + fy, fz = fy - b / 200.0; double xr = (fx * fx * fx > e) ? fx * fx *...
- `named_cmp` (function) `src/css_color.c:681` `static int named_cmp(const void *key, const void *element)`
- `parse_named` (function) `src/css_color.c:715` `static int parse_named(const char *s, cc_rgb *out)`
- `cc_parse` (function) `src/css_color.c:728` `cc_status cc_parse(const char *token, cc_rgb *out)`
- `strncmp` (function) `src/css_color.c:743` `strncmp(buf, "oklab(", 6) == 0 || strncmp(buf, "oklch(", 6) == 0)`
- `cc_pack` (function) `src/css_color.c:768` `int cc_pack(cc_rgb c)`
- `cc_unpack` (function) `src/css_color.c:772` `cc_rgb cc_unpack(int packed)`

## src/css_computed.c
Depends on: `include/css_computed.h`
- `put` (function) `src/css_computed.c:9` `static size_t put(char *out, size_t cap, const char *s)`
- `putf` (function) `src/css_computed.c:17` `static size_t putf(char *out, size_t cap, const char *fmt, ...)`
- `put_rgb` (function) `src/css_computed.c:26` `static size_t put_rgb(char *out, size_t cap, int rgb, int alpha_pct)`
- `put_len` (function) `src/css_computed.c:37` `static size_t put_len(char *out, size_t cap, int v, const char *unset_text)`
- `put_enum` (function) `src/css_computed.c:42` `static size_t put_enum(char *out, size_t cap, int v, const char *const *names, size_t n,
        ...`
- `ua_display` (function) `src/css_computed.c:49` `static const char *ua_display(const char *tag)` -- The HTML Rendering UA sheet's `display` for a tag when the cascade declared none * (the engine keeps block-ness of...
- `f_display` (function) `src/css_computed.c:77` `static size_t f_display(const ccm_input *in, char *out, size_t cap)`
- `f_position` (function) `src/css_computed.c:97` `static size_t f_position(const ccm_input *in, char *out, size_t cap)`
- `f_visibility` (function) `src/css_computed.c:102` `static size_t f_visibility(const ccm_input *in, char *out, size_t cap)`
- `f_float` (function) `src/css_computed.c:107` `static size_t f_float(const ccm_input *in, char *out, size_t cap)`
- `f_clear` (function) `src/css_computed.c:112` `static size_t f_clear(const ccm_input *in, char *out, size_t cap)`
- `f_overflow_x` (function) `src/css_computed.c:117` `static size_t f_overflow_x(const ccm_input *in, char *out, size_t cap)`
- `f_overflow_y` (function) `src/css_computed.c:122` `static size_t f_overflow_y(const ccm_input *in, char *out, size_t cap)`
- `f_text_align` (function) `src/css_computed.c:127` `static size_t f_text_align(const ccm_input *in, char *out, size_t cap)`
- `f_box_sizing` (function) `src/css_computed.c:132` `static size_t f_box_sizing(const ccm_input *in, char *out, size_t cap)`
- `f_flex_direction` (function) `src/css_computed.c:137` `static size_t f_flex_direction(const ccm_input *in, char *out, size_t cap)`
- `f_flex_wrap` (function) `src/css_computed.c:142` `static size_t f_flex_wrap(const ccm_input *in, char *out, size_t cap)`
- `f_justify` (function) `src/css_computed.c:147` `static size_t f_justify(const ccm_input *in, char *out, size_t cap)`
- `f_align_items` (function) `src/css_computed.c:153` `static size_t f_align_items(const ccm_input *in, char *out, size_t cap)`
- `f_cursor` (function) `src/css_computed.c:159` `static size_t f_cursor(const ccm_input *in, char *out, size_t cap)`
- `f_white_space` (function) `src/css_computed.c:165` `static size_t f_white_space(const ccm_input *in, char *out, size_t cap)`
- `f_text_transform` (function) `src/css_computed.c:170` `static size_t f_text_transform(const ccm_input *in, char *out, size_t cap)`
- `f_font_style` (function) `src/css_computed.c:175` `static size_t f_font_style(const ccm_input *in, char *out, size_t cap)`
- `f_font_weight` (function) `src/css_computed.c:179` `static size_t f_font_weight(const ccm_input *in, char *out, size_t cap)`
- `f_font_size` (function) `src/css_computed.c:183` `static size_t f_font_size(const ccm_input *in, char *out, size_t cap)`
- `f_line_height` (function) `src/css_computed.c:189` `static size_t f_line_height(const ccm_input *in, char *out, size_t cap)`
- `f_color` (function) `src/css_computed.c:195` `static size_t f_color(const ccm_input *in, char *out, size_t cap)`
- `f_background_color` (function) `src/css_computed.c:200` `static size_t f_background_color(const ccm_input *in, char *out, size_t cap)`
- `f_opacity` (function) `src/css_computed.c:206` `static size_t f_opacity(const ccm_input *in, char *out, size_t cap)`
- `f_z_index` (function) `src/css_computed.c:214` `static size_t f_z_index(const ccm_input *in, char *out, size_t cap)`
- `f_border_style` (function) `src/css_computed.c:219` `static size_t f_border_style(int v, char *out, size_t cap)`
- `NAME` (function) `src/css_computed.c:226` `static size_t NAME(const ccm_input *in, char *out, size_t cap)` -- define LEN_FIELD(NAME, FIELD, UNSET) \
- `f_gap` (function) `src/css_computed.c:246` `static size_t f_gap(const ccm_input *in, char *out, size_t cap)`
- `f_border_top_style` (function) `src/css_computed.c:258` `static size_t f_border_top_style(const ccm_input *in, char *out, size_t cap)`
- `f_border_right_style` (function) `src/css_computed.c:261` `static size_t f_border_right_style(const ccm_input *in, char *out, size_t cap)`
- `f_border_bottom_style` (function) `src/css_computed.c:264` `static size_t f_border_bottom_style(const ccm_input *in, char *out, size_t cap)`
- `f_border_left_style` (function) `src/css_computed.c:267` `static size_t f_border_left_style(const ccm_input *in, char *out, size_t cap)`
- `f_flex_grow` (function) `src/css_computed.c:271` `static size_t f_flex_grow(const ccm_input *in, char *out, size_t cap)`
- `f_flex_shrink` (function) `src/css_computed.c:274` `static size_t f_flex_shrink(const ccm_input *in, char *out, size_t cap)`
- `ccm_get` (function) `src/css_computed.c:312` `size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap)`
- `ccm_property_count` (function) `src/css_computed.c:325` `size_t ccm_property_count(void)`
- `ccm_property_name` (function) `src/css_computed.c:327` `const char *ccm_property_name(size_t i)`


Next: [API_p8.md](API_p8.md)
