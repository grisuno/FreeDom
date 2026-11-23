# Symbols (page 3 of 18)
Previous: [SYMBOLS_p2.md](SYMBOLS_p2.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `browser_state` | struct | `include/browser.h:27` | `` |
| `browser_status` | enum | `include/browser.h:63` | `` |
| `browser_status_text` | function | `include/browser.h:173` | `const char *browser_status_text(const browser_state *bs, uint64_t now_ms);` |
| `browser_url_bar_delete_selection` | function | `include/browser.h:158` | `int browser_url_bar_delete_selection(browser_state *bs);` |
| `browser_url_bar_selection` | function | `include/browser.h:154` | `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len);` |
| `copied` | function | `include/browser.h:166` | `* copied (truncated to fit) and shown until now_ms reaches the expiry * (now_ms + BROWSER_STATUS_DURATION_MS). A...` |
| `one` | function | `include/browser.h:102` | `* A navigate while pending first aborts the pending one (the new one replaces it);` |
| `state` | function | `include/browser.h:74` | `* state (frees old history and page buffers). */ browser_status browser_init(browser_state *bs);` |
| `FREEDOM_CACHED_FETCH_H` | macro | `include/cached_fetch.h:2` | `#define FREEDOM_CACHED_FETCH_H` |
| `cf_attach_redirect_memory` | function | `include/cached_fetch.h:38` | `void cf_attach_redirect_memory(hc_store *store);` |
| `cf_set_store` | function | `include/cached_fetch.h:30` | `void cf_set_store(hc_store *store);` |
| `cf_store` | function | `include/cached_fetch.h:31` | `hc_store *cf_store(void);` |
| `CHL_BTN` | macro | `include/chrome_layout.h:27` | `#define CHL_BTN` |
| `CHL_BTN_GAP` | macro | `include/chrome_layout.h:28` | `#define CHL_BTN_GAP` |
| `CHL_DRAG_MIN` | macro | `include/chrome_layout.h:26` | `#define CHL_DRAG_MIN` |
| `CHL_DRAG_THRESHOLD` | macro | `include/chrome_layout.h:32` | `#define CHL_DRAG_THRESHOLD` |
| `CHL_FIND_BTN` | macro | `include/chrome_layout.h:107` | `#define CHL_FIND_BTN` |
| `CHL_FIND_COUNT_W` | macro | `include/chrome_layout.h:108` | `#define CHL_FIND_COUNT_W` |
| `CHL_FIND_FIELD_H` | macro | `include/chrome_layout.h:106` | `#define CHL_FIND_FIELD_H` |
| `CHL_FIND_FIELD_W` | macro | `include/chrome_layout.h:105` | `#define CHL_FIND_FIELD_W` |
| `CHL_FIND_H` | macro | `include/chrome_layout.h:104` | `#define CHL_FIND_H` |
| `CHL_ID_W` | macro | `include/chrome_layout.h:30` | `#define CHL_ID_W` |
| `CHL_MORE_W` | macro | `include/chrome_layout.h:31` | `#define CHL_MORE_W` |
| `CHL_NEWTAB_W` | macro | `include/chrome_layout.h:24` | `#define CHL_NEWTAB_W` |
| `CHL_PAD` | macro | `include/chrome_layout.h:17` | `#define CHL_PAD` |
| `CHL_TABBAR_H` | macro | `include/chrome_layout.h:15` | `#define CHL_TABBAR_H` |
| `CHL_TAB_CLOSE` | macro | `include/chrome_layout.h:22` | `#define CHL_TAB_CLOSE` |
| `CHL_TAB_CLOSE_MIN_W` | macro | `include/chrome_layout.h:23` | `#define CHL_TAB_CLOSE_MIN_W` |
| `CHL_TAB_GAP` | macro | `include/chrome_layout.h:21` | `#define CHL_TAB_GAP` |
| `CHL_TAB_MAX_W` | macro | `include/chrome_layout.h:20` | `#define CHL_TAB_MAX_W` |
| `CHL_TAB_MIN_W` | macro | `include/chrome_layout.h:19` | `#define CHL_TAB_MIN_W` |
| `CHL_TAB_TOP_GAP` | macro | `include/chrome_layout.h:18` | `#define CHL_TAB_TOP_GAP` |
| `CHL_TOOLBAR_H` | macro | `include/chrome_layout.h:16` | `#define CHL_TOOLBAR_H` |
| `CHL_URL_H` | macro | `include/chrome_layout.h:29` | `#define CHL_URL_H` |
| `CHL_WIN_BTN_W` | macro | `include/chrome_layout.h:25` | `#define CHL_WIN_BTN_W` |
| `FREEDOM_CHROME_LAYOUT_H` | macro | `include/chrome_layout.h:2` | `#define FREEDOM_CHROME_LAYOUT_H` |
| `chl_find_part` | enum | `include/chrome_layout.h:110` | `` |
| `chl_findbar` | struct | `include/chrome_layout.h:119` | `` |
| `chl_identity` | enum | `include/chrome_layout.h:132` | `` |
| `chl_identity_label` | function | `include/chrome_layout.h:151` | `const char *chl_identity_label(chl_identity id);` |
| `chl_layout` | struct | `include/chrome_layout.h:58` | `` |
| `chl_move_index` | function | `include/chrome_layout.h:97` | `int chl_move_index(int i, int from, int to);` |
| `chl_part` | enum | `include/chrome_layout.h:38` | `` |
| `chl_rect` | struct | `include/chrome_layout.h:36` | `` |
| `chl_rect_has` | function | `include/chrome_layout.h:85` | `int chl_rect_has(chl_rect r, double x, double y);` |
| `chl_status` | enum | `include/chrome_layout.h:34` | `` |
| `chl_tab_close_rect` | function | `include/chrome_layout.h:82` | `int chl_tab_close_rect(const chl_layout *l, int i, chl_rect *r);` |
| `chl_tab_drop_index` | function | `include/chrome_layout.h:93` | `int chl_tab_drop_index(const chl_layout *l, double x);` |
| `chl_tab_for_digit` | function | `include/chrome_layout.h:100` | `int chl_tab_for_digit(int digit, int tab_count);` |
| `chl_tab_rect` | function | `include/chrome_layout.h:81` | `int chl_tab_rect(const chl_layout *l, int i, chl_rect *r);` |
| `close` | type_alias | `include/chrome_layout.h:118` | `typedef struct chl_findbar { chl_rect bar, field, prev, next, count, close;` |
| `h` | type_alias | `include/chrome_layout.h:35` | `typedef struct chl_rect { double x, y, w, h;` |
| `width` | type_alias | `include/chrome_layout.h:57` | `typedef struct chl_layout { double width;` |
| `FREEDOM_COMPOSITOR_H` | macro | `include/compositor.h:2` | `#define FREEDOM_COMPOSITOR_H` |
| `cx_forms_stacking_context` | function | `include/compositor.h:60` | `int cx_forms_stacking_context(const cx_style *s);` |
| `cx_ink_reach` | function | `include/compositor.h:91` | `double cx_ink_reach(const int (*layers)[6], int n, int outline_w, int outline_offset);` |
| `cx_item` | struct | `include/compositor.h:69` | `` |
| `cx_item_compare` | function | `include/compositor.h:80` | `int cx_item_compare(const cx_item *a, const cx_item *b);` |
| `cx_layer` | enum | `include/compositor.h:27` | `` |
| `cx_sort` | function | `include/compositor.h:84` | `void cx_sort(cx_item *items, size_t n);` |
| `cx_span_visible` | function | `include/compositor.h:95` | `int cx_span_visible(double top, double h, double reach, double view_top, double view_h);` |
| `cx_style` | struct | `include/compositor.h:46` | `` |
| `layer` | type_alias | `include/compositor.h:69` | `typedef struct cx_item { cx_layer layer;` |
| `position` | type_alias | `include/compositor.h:46` | `typedef struct cx_style { int position;` |
| `CSS_BORDER_SPACING_MAX` | macro | `include/css.h:465` | `#define CSS_BORDER_SPACING_MAX` |
| `CSS_BORDER_W_MAX` | macro | `include/css.h:464` | `#define CSS_BORDER_W_MAX` |
| `CSS_BSHADOW_LAYERS` | macro | `include/css.h:473` | `#define CSS_BSHADOW_LAYERS` |
| `CSS_COLUMN_COUNT_MAX` | macro | `include/css.h:532` | `#define CSS_COLUMN_COUNT_MAX` |
| `CSS_CONTAIN_LAYOUT` | macro | `include/css.h:367` | `#define CSS_CONTAIN_LAYOUT` |
| `CSS_CONTAIN_PAINT` | macro | `include/css.h:369` | `#define CSS_CONTAIN_PAINT` |
| `CSS_CONTAIN_SIZE` | macro | `include/css.h:366` | `#define CSS_CONTAIN_SIZE` |
| `CSS_CONTAIN_STYLE` | macro | `include/css.h:368` | `#define CSS_CONTAIN_STYLE` |
| `CSS_DECO_LINE_THROUGH` | macro | `include/css.h:121` | `#define CSS_DECO_LINE_THROUGH` |
| `CSS_DECO_OVERLINE` | macro | `include/css.h:122` | `#define CSS_DECO_OVERLINE` |
| `CSS_DECO_UNDERLINE` | macro | `include/css.h:120` | `#define CSS_DECO_UNDERLINE` |
| `CSS_DISP_INLINE_OUTER` | macro | `include/css.h:74` | `#define CSS_DISP_INLINE_OUTER` |
| `CSS_DISP_INNER_MASK` | macro | `include/css.h:75` | `#define CSS_DISP_INNER_MASK` |
| `CSS_DROP_PROP_MAX` | macro | `include/css.h:1091` | `#define CSS_DROP_PROP_MAX` |
| `CSS_DROP_VAL_MAX` | macro | `include/css.h:1092` | `#define CSS_DROP_VAL_MAX` |
| `CSS_EM_MILLI_MAX` | macro | `include/css.h:522` | `#define CSS_EM_MILLI_MAX` |
| `CSS_FLEX_FACTOR_MAX` | macro | `include/css.h:466` | `#define CSS_FLEX_FACTOR_MAX` |
| `CSS_FONT_LIST_MAX` | macro | `include/css.h:107` | `#define CSS_FONT_LIST_MAX` |
| `CSS_FONT_SIZE_MAX` | macro | `include/css.h:528` | `#define CSS_FONT_SIZE_MAX` |
| `CSS_GAP_MAX` | macro | `include/css.h:88` | `#define CSS_GAP_MAX` |
| `CSS_GRAD_STOPS_MAX` | macro | `include/css.h:97` | `#define CSS_GRAD_STOPS_MAX` |
| `CSS_GRID_AREAS_MAX` | macro | `include/css.h:96` | `#define CSS_GRID_AREAS_MAX` |
| `CSS_GRID_COLS_MAX` | macro | `include/css.h:89` | `#define CSS_GRID_COLS_MAX` |
| `CSS_GRID_SPAN_MAX` | macro | `include/css.h:467` | `#define CSS_GRID_SPAN_MAX` |
| `CSS_GRID_TRACKS_MAX` | macro | `include/css.h:90` | `#define CSS_GRID_TRACKS_MAX` |
| `CSS_LEN_AUTO` | macro | `include/css.h:480` | `#define CSS_LEN_AUTO` |
| `CSS_LEN_END` | macro | `include/css.h:481` | `#define CSS_LEN_END` |
| `CSS_LEN_FIT_CONTENT` | macro | `include/css.h:490` | `#define CSS_LEN_FIT_CONTENT` |
| `CSS_LEN_IS_INTRINSIC` | macro | `include/css.h:493` | `#define CSS_LEN_IS_INTRINSIC(v)` |
| `CSS_LEN_MAX` | macro | `include/css.h:478` | `#define CSS_LEN_MAX` |
| `CSS_LEN_MAX_CONTENT` | macro | `include/css.h:489` | `#define CSS_LEN_MAX_CONTENT` |
| `CSS_LEN_MIN_CONTENT` | macro | `include/css.h:488` | `#define CSS_LEN_MIN_CONTENT` |
| `CSS_LEN_UNSET` | macro | `include/css.h:479` | `#define CSS_LEN_UNSET` |
| `CSS_LINE_ABS_BASE` | macro | `include/css.h:104` | `#define CSS_LINE_ABS_BASE` |
| `CSS_LINE_ABS_MAX_PX` | macro | `include/css.h:105` | `#define CSS_LINE_ABS_MAX_PX` |
| `CSS_LINE_MAX` | macro | `include/css.h:99` | `#define CSS_LINE_MAX` |
| `CSS_LINE_MIN` | macro | `include/css.h:98` | `#define CSS_LINE_MIN` |
| `CSS_MAX_ATTR_SEL` | macro | `include/css.h:591` | `#define CSS_MAX_ATTR_SEL` |
| `CSS_MAX_COMPOUNDS` | macro | `include/css.h:587` | `#define CSS_MAX_COMPOUNDS` |
| `CSS_MAX_KF_STOPS` | macro | `include/css.h:933` | `#define CSS_MAX_KF_STOPS` |
| `CSS_MAX_PSEUDO_SEL` | macro | `include/css.h:595` | `#define CSS_MAX_PSEUDO_SEL` |
| `CSS_MEDIA_DEFAULT_HEIGHT` | macro | `include/css.h:1044` | `#define CSS_MEDIA_DEFAULT_HEIGHT` |
| `CSS_MEDIA_DEFAULT_WIDTH` | macro | `include/css.h:1039` | `#define CSS_MEDIA_DEFAULT_WIDTH` |
| `CSS_NTH_MAX` | macro | `include/css.h:599` | `#define CSS_NTH_MAX` |
| `CSS_OBJPOS_PACK` | macro | `include/css.h:408` | `#define CSS_OBJPOS_PACK(x_pm, y_pm)` |
| `CSS_OBJPOS_X` | macro | `include/css.h:409` | `#define CSS_OBJPOS_X(p)` |
| `CSS_OBJPOS_Y` | macro | `include/css.h:410` | `#define CSS_OBJPOS_Y(p)` |
| `CSS_PCT_MAX` | macro | `include/css.h:516` | `#define CSS_PCT_MAX` |
| `CSS_PSEUDO_AFTER` | macro | `include/css.h:1233` | `#define CSS_PSEUDO_AFTER` |
| `CSS_PSEUDO_BEFORE` | macro | `include/css.h:1232` | `#define CSS_PSEUDO_BEFORE` |
| `CSS_PSEUDO_PLACEHOLDER` | macro | `include/css.h:1234` | `#define CSS_PSEUDO_PLACEHOLDER` |
| `CSS_SHADOW_MAX` | macro | `include/css.h:472` | `#define CSS_SHADOW_MAX` |
| `CSS_SPACING_MAX` | macro | `include/css.h:471` | `#define CSS_SPACING_MAX` |
| `CSS_SVG_PAINT_NONE` | macro | `include/css.h:106` | `#define CSS_SVG_PAINT_NONE` |
| `CSS_URL_MAX` | macro | `include/css.h:108` | `#define CSS_URL_MAX` |
| `FREEDOM_CSS_H` | macro | `include/css.h:2` | `#define FREEDOM_CSS_H` |
| `POINTER` | function | `include/css.h:235` | `* POINTER (shows the hand cursor already used for links) from every other value * (shows the default arrow);` |
| `color` | type_alias | `include/css.h:606` | `typedef struct css_style { int color;` |
| `container` | function | `include/css.h:674` | `* container (Display 3 section 2);` |
| `css_align` | enum | `include/css.h:36` | `` |
| `css_align_kw` | enum | `include/css.h:194` | `` |
| `css_appearance` | enum | `include/css.h:329` | `` |
| `css_attr` | struct | `include/css.h:1140` | `` |
| `css_backface` | enum | `include/css.h:457` | `` |
| `css_bg_attachment` | enum | `include/css.h:358` | `` |
| `css_bg_clip` | enum | `include/css.h:349` | `` |
| `css_bg_origin` | enum | `include/css.h:354` | `` |
| `css_bg_repeat` | enum | `include/css.h:340` | `` |
| `css_bg_size` | enum | `include/css.h:345` | `` |
| `css_border_collapse` | enum | `include/css.h:287` | `` |
| `css_border_style` | enum | `include/css.h:175` | `` |
| `css_box_sizing` | enum | `include/css.h:168` | `` |
| `css_caption_side` | enum | `include/css.h:299` | `` |
| `css_clear` | enum | `include/css.h:213` | `` |
| `css_color_scheme` | enum | `include/css.h:379` | `` |
| `css_column_fill` | enum | `include/css.h:448` | `` |
| `css_column_span` | enum | `include/css.h:453` | `` |
| `css_content_visibility` | enum | `include/css.h:371` | `` |
| `css_cursor` | enum | `include/css.h:240` | `` |
| `css_direction` | enum | `include/css.h:281` | `` |
| `css_display` | enum | `include/css.h:44` | `` |
| `css_drop` | struct | `include/css.h:1099` | `` |
| `css_drop_cause` | enum | `include/css.h:1086` | `` |
| `css_drop_log` | struct | `include/css.h:1111` | `` |
| `css_element` | struct | `include/css.h:1150` | `` |
| `css_empty_cells` | enum | `include/css.h:293` | `` |
| `css_flex_direction` | enum | `include/css.h:182` | `` |
| `css_flex_wrap` | enum | `include/css.h:188` | `` |
| `css_float` | enum | `include/css.h:207` | `` |
| `css_font_face_at` | function | `include/css.h:1274` | `int css_font_face_at(const css_sheet *sheet, size_t i, char *family, size_t fam_cap, char *src_url, size_t url_cap);` |
| `css_font_face_count` | function | `include/css.h:1273` | `size_t css_font_face_count(const css_sheet *sheet);` |
| `css_font_family` | enum | `include/css.h:126` | `` |
| `css_font_kerning` | enum | `include/css.h:416` | `` |
| `css_font_stretch` | enum | `include/css.h:425` | `` |
| `css_font_variant` | enum | `include/css.h:311` | `` |
| `css_forced_color_adjust` | enum | `include/css.h:387` | `` |
| `css_free` | function | `include/css.h:1126` | `void css_free(css_sheet *s);` |
| `css_grid_flow` | enum | `include/css.h:201` | `` |
| `css_hyphens` | enum | `include/css.h:317` | `` |
| `css_image_rendering` | enum | `include/css.h:375` | `` |
| `css_isolation` | enum | `include/css.h:362` | `` |
| `css_justify` | enum | `include/css.h:77` | `` |
| `css_list_pos` | enum | `include/css.h:412` | `` |
| `css_list_style` | enum | `include/css.h:149` | `` |
| `css_media` | struct | `include/css.h:1027` | `` |
| `css_mix_blend` | enum | `include/css.h:392` | `` |
| `css_object_fit` | enum | `include/css.h:400` | `` |
| `css_overflow` | enum | `include/css.h:230` | `` |
| `css_overscroll` | enum | `include/css.h:443` | `` |
| `css_pct_slot` | enum | `include/css.h:534` | `` |
| `css_pointer_events` | enum | `include/css.h:335` | `` |
| `css_position` | enum | `include/css.h:161` | `` |
| `css_print_color_adjust` | enum | `include/css.h:383` | `` |
| `css_resize` | enum | `include/css.h:431` | `` |
| `css_resolve_anim_keyframes` | function | `include/css.h:1282` | `void css_resolve_anim_keyframes(css_style *s, const css_sheet *sheet);` |
| `css_scroll_behavior` | enum | `include/css.h:435` | `` |
| `css_sel` | struct | `include/css.h:1025` | `` |
| `css_sheet` | type_alias | `include/css.h:1019` | `typedef struct css_sheet css_sheet;` |
| `css_sheet_uses_containers` | function | `include/css.h:1059` | `int css_sheet_uses_containers(const css_sheet *sheet);` |
| `css_sheet_uses_counters` | function | `include/css.h:1055` | `int css_sheet_uses_counters(const css_sheet *sheet);` |
| `css_status` | enum | `include/css.h:30` | `` |
| `css_style` | struct | `include/css.h:606` | `` |
| `css_table_layout` | enum | `include/css.h:305` | `` |
| `css_text_decoration_style` | enum | `include/css.h:274` | `` |
| `css_text_overflow` | enum | `include/css.h:253` | `` |
| `css_text_rendering` | enum | `include/css.h:420` | `` |
| `css_text_transform` | enum | `include/css.h:132` | `` |
| `css_touch_action` | enum | `include/css.h:439` | `` |
| `css_ua_heading_em` | function | `include/css.h:1258` | `double css_ua_heading_em(int level);` |
| `css_user_select` | enum | `include/css.h:323` | `` |
| `css_valign` | enum | `include/css.h:137` | `` |
| `css_visibility` | enum | `include/css.h:221` | `` |
| `css_white_space` | enum | `include/css.h:143` | `` |
| `css_word_break` | enum | `include/css.h:267` | `` |
| `cvr_table` | struct | `include/css.h:1222` | `` |
| `declared` | function | `include/css.h:898` | `* function was not declared (identity: 0 offset / 100% scale / 0deg). * Percentage translate arguments are not...` |
| `element` | function | `include/css.h:903` | `* so two different rules matching the same element (e.g. one setting * translate, a more specific one setting...` |
| `family` | function | `include/css.h:719` | `* LOCAL family (spec/text_shape.md section 7);` |
| `inherited_px` | function | `include/css.h:1246` | `* whose PARENT computes to inherited_px (<= 0 = unknown -> the CSS initial). * * Exported because the caller that...` |
| `name` | function | `include/css.h:1263` | `* name (NULL = not a heading). */ double css_computed_font_size_for_tag(const css_style *o, double inherited_px...` |
| `order` | function | `include/css.h:1129` | `* cascade order (specificity, then document order), then the element's own * inline_style (which wins)....` |
| `palette` | function | `include/css.h:1076` | `* so an inactive theme * palette (a dark palette in a light render) can never clobber the active one. *...` |
| `prefers_dark` | type_alias | `include/css.h:1026` | `typedef struct css_media { int prefers_dark;` |
| `prop` | type_alias | `include/css.h:1099` | `typedef struct css_drop { char prop[CSS_DROP_PROP_MAX];` |
| `scaleY` | function | `include/css.h:894` | `* scaleY() as a PERCENT of identity (100 = scale(1), matching font_scale's * convention);` |
| `slots` | function | `include/css.h:910` | `* parse time into ALL seven slots (singular matrices fail closed);` |
| `translate` | function | `include/css.h:893` | `* translate()/translateX()/translateY();` |
| `verbatim` | function | `include/css.h:92` | `* the quoted row strings verbatim (flex_layout parses them);` |
| `CAR_INLINE_SPEC` | macro | `include/css_atrule.h:18` | `#define CAR_INLINE_SPEC` |
| `CAR_LAYER_NAME_MAX` | macro | `include/css_atrule.h:17` | `#define CAR_LAYER_NAME_MAX` |
| `CAR_MAX_DEPTH` | macro | `include/css_atrule.h:15` | `#define CAR_MAX_DEPTH` |
| `CAR_MAX_LAYERS` | macro | `include/css_atrule.h:16` | `#define CAR_MAX_LAYERS` |
| `FREEDOM_CSS_ATRULE_H` | macro | `include/css_atrule.h:2` | `#define FREEDOM_CSS_ATRULE_H` |
| `car_effective_spec` | function | `include/css_atrule.h:44` | `int car_effective_spec(int spec, int layer, int important);` |
| `car_layer_rank` | function | `include/css_atrule.h:40` | `int car_layer_rank(car_layers *L, const char *name, size_t len);` |
| `car_layers` | struct | `include/css_atrule.h:31` | `` |
| `car_ops` | struct | `include/css_atrule.h:22` | `` |
| `car_supports` | function | `include/css_atrule.h:29` | `int car_supports(const char *s, size_t a, size_t b, const car_ops *ops);` |
| `CB_AUTO_REJECT` | macro | `include/css_box.h:10` | `#define CB_AUTO_REJECT` |
| `CB_AUTO_RESET` | macro | `include/css_box.h:12` | `#define CB_AUTO_RESET` |
| `CB_AUTO_RESET_NONE` | macro | `include/css_box.h:13` | `#define CB_AUTO_RESET_NONE` |
| `CB_AUTO_VALUE` | macro | `include/css_box.h:11` | `#define CB_AUTO_VALUE` |
| `FREEDOM_CSS_BOX_H` | macro | `include/css_box.h:2` | `#define FREEDOM_CSS_BOX_H` |
| `block` | function | `include/css_box.h:19` | `* For contexts with no element and no containing block (media query values). */ int cb_math_length_px(const char *v...` |
| `cb_emit_len` | function | `include/css_box.h:22` | `int cb_emit_len(css_decl *dst, int cap, int slot, const char *val, int allow_auto, int allow_neg);` |
| `cb_expand_box2` | function | `include/css_box.h:26` | `int cb_expand_box2(const char *val, int slot_start, int slot_end, int allow_auto, int allow_neg, css_decl *dst, int...` |
| `cb_expand_box4` | function | `include/css_box.h:24` | `int cb_expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg, css_decl *dst, int cap);` |
| `cb_expand_grid_template_cols` | function | `include/css_box.h:48` | `int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap);` |
| `cb_interp_align` | function | `include/css_box.h:38` | `int cb_interp_align(const char *v);` |
| `cb_interp_display` | function | `include/css_box.h:44` | `int cb_interp_display(const char *v);` |
| `cb_interp_fontsize_ex` | function | `include/css_box.h:39` | `int cb_interp_fontsize_ex(const char *v, int *abs_out);` |
| `cb_interp_gap` | function | `include/css_box.h:45` | `int cb_interp_gap(const char *v);` |
| `cb_interp_gridcols` | function | `include/css_box.h:47` | `int cb_interp_gridcols(const char *v);` |
| `cb_interp_justify` | function | `include/css_box.h:46` | `int cb_interp_justify(const char *v);` |
| `cb_interp_len` | function | `include/css_box.h:21` | `int cb_interp_len(const char *v, int allow_auto, int *out);` |
| `cb_interp_lineheight` | function | `include/css_box.h:40` | `int cb_interp_lineheight(const char *v);` |
| `cb_interp_lp` | function | `include/css_box.h:28` | `int cb_interp_lp(const char *v, int allow_auto, int allow_pct, int *out_px, int *out_pm);` |
| `cb_interp_style` | function | `include/css_box.h:42` | `int cb_interp_style(const char *v);` |
| `cb_interp_textdeco` | function | `include/css_box.h:43` | `int cb_interp_textdeco(const char *v);` |
| `cb_interp_weight` | function | `include/css_box.h:41` | `int cb_interp_weight(const char *v);` |
| `cb_length_px` | function | `include/css_box.h:15` | `int cb_length_px(const char *v, double *px);` |
| `cb_lp_can_be_nonneg` | function | `include/css_box.h:36` | `int cb_lp_can_be_nonneg(int px_val, int pct_pm);` |
| `cb_next_ws_token` | function | `include/css_box.h:37` | `int cb_next_ws_token(const char **p, char *tok, size_t cap);` |
| `cb_value_em_milli` | function | `include/css_box.h:30` | `int cb_value_em_milli(const char *v);` |
| `rectangle` | function | `include/css_box.h:32` | `* rectangle (top, right, bottom, left): px[i] + pm[i]/1000 of the border box (height for * top/bottom, width for...` |
| `strings` | function | `include/css_box.h:50` | `* Quoted area strings (the grid-template shorthand's row half) are skipped. */ int...` |
| `CCH_CHAIN_MAX` | macro | `include/css_chain.h:26` | `#define CCH_CHAIN_MAX` |
| `CCH_NTH_MAX` | macro | `include/css_chain.h:28` | `#define CCH_NTH_MAX` |
| `CCH_SIB_MAX` | macro | `include/css_chain.h:27` | `#define CCH_SIB_MAX` |
| `FREEDOM_CSS_CHAIN_H` | macro | `include/css_chain.h:2` | `#define FREEDOM_CSS_CHAIN_H` |
| `box` | function | `include/css_chain.h:92` | `* generated box (css_resolve_pseudo) against the same element context. * font_size is el's own COMPUTED font-size...` |
| `cch_element_matches` | function | `include/css_chain.h:82` | `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel);` |
| `cch_path` | type_alias | `include/css_chain.h:69` | `typedef struct cch_path cch_path;` |
| `cch_path_free` | function | `include/css_chain.h:71` | `void cch_path_free(cch_path *pa);` |
| `cch_path_new` | function | `include/css_chain.h:70` | `cch_path *cch_path_new(void);` |
| `cvr_chain` | struct | `include/css_chain.h:51` | `` |
| `cvr_table` | struct | `include/css_chain.h:52` | `` |
| `lacks` | function | `include/css_chain.h:86` | `* the element lacks (csel's subj_req) is rejected before the ancestor chain is built: on a * query that scans a...` |
| `CC_COLOR_CURRENT` | macro | `include/css_color.h:59` | `#define CC_COLOR_CURRENT` |
| `CC_COLOR_TRANSPARENT` | macro | `include/css_color.h:60` | `#define CC_COLOR_TRANSPARENT` |
| `FREEDOM_CSS_COLOR_H` | macro | `include/css_color.h:2` | `#define FREEDOM_CSS_COLOR_H` |
| `b` | type_alias | `include/css_color.h:26` | `typedef struct cc_rgb { unsigned char r, g, b;` |
| `cc_pack` | function | `include/css_color.h:49` | `int cc_pack(cc_rgb c);` |
| `cc_rgb` | struct | `include/css_color.h:27` | `` |
| `cc_status` | enum | `include/css_color.h:31` | `` |
| `CCM_VALUE_MAX` | macro | `include/css_computed.h:17` | `#define CCM_VALUE_MAX` |
| `FREEDOM_CSS_COMPUTED_H` | macro | `include/css_computed.h:2` | `#define FREEDOM_CSS_COMPUTED_H` |
| `ccm_get` | function | `include/css_computed.h:29` | `size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap);` |
| `ccm_input` | struct | `include/css_computed.h:19` | `` |
| `ccm_property_count` | function | `include/css_computed.h:32` | `size_t ccm_property_count(void);` |
| `ccm_property_name` | function | `include/css_computed.h:33` | `const char *ccm_property_name(size_t i);` |
| `CNT_MAX_DECL` | macro | `include/css_counter.h:17` | `#define CNT_MAX_DECL` |
| `CNT_MAX_INSTANCES` | macro | `include/css_counter.h:18` | `#define CNT_MAX_INSTANCES` |
| `CNT_NAME_MAX` | macro | `include/css_counter.h:19` | `#define CNT_NAME_MAX` |
| `FREEDOM_CSS_COUNTER_H` | macro | `include/css_counter.h:9` | `#define FREEDOM_CSS_COUNTER_H` |
| `cnt_decl` | struct | `include/css_counter.h:21` | `` |
| `cnt_format` | function | `include/css_counter.h:49` | `size_t cnt_format(int style, long value, char *out, size_t cap);` |
| `cnt_hash` | function | `include/css_counter.h:34` | `unsigned cnt_hash(const char *name, size_t len);` |
| `cnt_increment` | function | `include/css_counter.h:57` | `void cnt_increment(cnt_state *s, int depth, const cnt_decl *d, int n);` |
| `cnt_is_marker` | function | `include/css_counter.h:45` | `int cnt_is_marker(const char *s);` |
| `cnt_leave` | function | `include/css_counter.h:60` | `void cnt_leave(cnt_state *s, int depth);` |
| `cnt_parse_content` | function | `include/css_counter.h:44` | `int cnt_parse_content(const char *val, char *out, size_t cap);` |
| `cnt_reset` | function | `include/css_counter.h:56` | `void cnt_reset(cnt_state *s, int depth, const cnt_decl *d, int n);` |
| `cnt_resolve` | function | `include/css_counter.h:67` | `size_t cnt_resolve(const cnt_state *s, const char *marker, cnt_attr_fn attr, void *ctx, char *out, size_t cap);` |
| `cnt_state` | type_alias | `include/css_counter.h:50` | `typedef struct cnt_state cnt_state;` |
| `cnt_state_free` | function | `include/css_counter.h:53` | `void cnt_state_free(cnt_state *s);` |
| `cnt_state_new` | function | `include/css_counter.h:52` | `cnt_state *cnt_state_new(void);` |
| `cnt_style` | enum | `include/css_counter.h:26` | `` |
| `name` | type_alias | `include/css_counter.h:20` | `typedef struct cnt_decl { unsigned name;` |
| `written` | function | `include/css_counter.h:37` | `* written (0 for `none`) or -1 when invalid. `dflt` is the value of an entry with no * integer: 0 for reset, 1 for...` |
| `CSS_INLINE_BG_URLS` | macro | `include/css_decl.h:28` | `#define CSS_INLINE_BG_URLS` |
| `CSS_MAX_BG_URLS` | macro | `include/css_decl.h:22` | `#define CSS_MAX_BG_URLS` |
| `CSS_MAX_CONTENT_URLS` | macro | `include/css_decl.h:23` | `#define CSS_MAX_CONTENT_URLS` |
| `CSS_MAX_KEYFRAMES` | macro | `include/css_decl.h:25` | `#define CSS_MAX_KEYFRAMES` |
| `CSS_MAX_KEYFRAME_DECLS` | macro | `include/css_decl.h:27` | `#define CSS_MAX_KEYFRAME_DECLS` |
| `CSS_MAX_KEYFRAME_STOPS` | macro | `include/css_decl.h:26` | `#define CSS_MAX_KEYFRAME_STOPS` |
| `CSS_POOL_HEADROOM` | macro | `include/css_decl.h:21` | `#define CSS_POOL_HEADROOM` |
| `CSS_POOL_INIT` | macro | `include/css_decl.h:20` | `#define CSS_POOL_INIT` |
| `CSS_WIDE_PROBE_DECLS` | macro | `include/css_decl.h:35` | `#define CSS_WIDE_PROBE_DECLS` |
| `FREEDOM_CSS_DECL_H` | macro | `include/css_decl.h:2` | `#define FREEDOM_CSS_DECL_H` |
| `contiguous` | function | `include/css_decl.h:65` | `* contiguous (dx,dy,color) so expand_shadow writes them as a group. */ P_FONTFAMILY, P_TEXTTRANSFORM...` |
| `css_decl` | struct | `include/css_decl.h:241` | `` |
| `order` | function | `include/css_decl.h:50` | `* The four margin slots are contiguous in CSS shorthand order (top,right,bottom, * left);` |
| `part` | function | `include/css_decl.h:216` | `* each P_CLIP_* edge adds to its px part (the other half of a <length-percentage>). */ P_CLIP_TOP_PM...` |
| `prop` | type_alias | `include/css_decl.h:240` | `typedef struct css_decl { int prop;` |
| `CG_LEN_UNSET` | macro | `include/css_gradient.h:22` | `#define CG_LEN_UNSET` |
| `FREEDOM_CSS_GRADIENT_H` | macro | `include/css_gradient.h:2` | `#define FREEDOM_CSS_GRADIENT_H` |
| `cg_expand_background` | function | `include/css_gradient.h:17` | `int cg_expand_background(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...` |
| `cg_expand_bg_image` | function | `include/css_gradient.h:15` | `int cg_expand_bg_image(const char *val, css_decl *dst, int cap, char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t...` |
| `cg_first_url` | function | `include/css_gradient.h:13` | `int cg_first_url(const char *val, char *out, size_t outcap);` |
| `cg_parse_linear` | function | `include/css_gradient.h:55` | `int cg_parse_linear(const char *fn, int *angle, int *colors, int *positions);` |
| `cg_radial` | struct | `include/css_gradient.h:28` | `` |
| `cg_radial_len_px` | function | `include/css_gradient.h:41` | `double cg_radial_len_px(int enc, double dim);` |
| `cg_radial_shape` | enum | `include/css_gradient.h:23` | `` |
| `cg_radial_size` | enum | `include/css_gradient.h:24` | `` |
| `out` | function | `include/css_gradient.h:36` | `* Returns 1 and fills *out (defaults first) when seg is a valid prelude, 0 when seg is not * one (it is a colour...` |
| `shape` | type_alias | `include/css_gradient.h:28` | `typedef struct cg_radial { int shape;` |
| `width` | function | `include/css_gradient.h:21` | `* width (x, rx) or height (y, ry);` |
| `zero` | function | `include/css_gradient.h:45` | `* floored at a hair above zero (the spec paints the last colour for a degenerate size) and * never non-finite. Pure....` |
| `CI_COND_MAX` | macro | `include/css_import.h:20` | `#define CI_COND_MAX` |
| `CI_MAX_DEPTH` | macro | `include/css_import.h:21` | `#define CI_MAX_DEPTH` |
| `CI_MAX_PER_PAGE` | macro | `include/css_import.h:22` | `#define CI_MAX_PER_PAGE` |
| `CI_MAX_PER_SHEET` | macro | `include/css_import.h:23` | `#define CI_MAX_PER_SHEET` |
| `CI_URL_MAX` | macro | `include/css_import.h:19` | `#define CI_URL_MAX` |
| `FREEDOM_CSS_IMPORT_H` | macro | `include/css_import.h:2` | `#define FREEDOM_CSS_IMPORT_H` |
| `ci_balanced` | function | `include/css_import.h:45` | `int ci_balanced(const char *css, size_t len);` |
| `ci_import` | struct | `include/css_import.h:25` | `` |
| `ci_scan` | function | `include/css_import.h:36` | `size_t ci_scan(const char *css, size_t len, ci_import *out, size_t cap);` |
| `ci_wrap` | function | `include/css_import.h:41` | `int ci_wrap(const ci_import *im, char *open, size_t ocap, char *close, size_t ccap);` |
| `url` | type_alias | `include/css_import.h:24` | `typedef struct ci_import { char url[CI_URL_MAX];` |
| `url` | function | `include/css_import.h:55` | `* rewritten to url("ABS"), ABS = resolve(base, ref) (spec/css_import.md, "Rebase"). * Fragment-only, schemed, empty...` |
| `FREEDOM_CSS_INDEX_H` | macro | `include/css_index.h:11` | `#define FREEDOM_CSS_INDEX_H` |
| `cix_build` | function | `include/css_index.h:34` | `void cix_build(const css_sel *sels, size_t n, cix_index *idx);` |
| `cix_build_ptrs` | function | `include/css_index.h:37` | `void cix_build_ptrs(css_sel *const *sels, size_t n, cix_index *idx);` |
| `cix_entry` | struct | `include/css_index.h:18` | `` |
| `cix_free` | function | `include/css_index.h:40` | `void cix_free(cix_index *idx);` |
| `cix_index` | struct | `include/css_index.h:23` | `` |
| `index` | function | `include/css_index.h:44` | `* index (the caller then scans linearly). */ size_t cix_candidates(const cix_index *idx, const css_element *el...` |
| `key` | type_alias | `include/css_index.h:17` | `typedef struct cix_entry { uint64_t key;` |
| `CL_FALLBACK_CAP_RATIO` | macro | `include/css_length.h:65` | `#define CL_FALLBACK_CAP_RATIO` |
| `CL_FALLBACK_CH_RATIO` | macro | `include/css_length.h:64` | `#define CL_FALLBACK_CH_RATIO` |
| `CL_FALLBACK_EX_RATIO` | macro | `include/css_length.h:57` | `#define CL_FALLBACK_EX_RATIO` |
| `CL_FALLBACK_IC_RATIO` | macro | `include/css_length.h:66` | `#define CL_FALLBACK_IC_RATIO` |
| `CL_INITIAL_FONT_SIZE` | macro | `include/css_length.h:39` | `#define CL_INITIAL_FONT_SIZE` |
| `CL_MAX_TOKEN` | macro | `include/css_length.h:33` | `#define CL_MAX_TOKEN` |
| `CL_NORMAL_LINE_RATIO` | macro | `include/css_length.h:45` | `#define CL_NORMAL_LINE_RATIO` |
| `FREEDOM_CSS_LENGTH_H` | macro | `include/css_length.h:2` | `#define FREEDOM_CSS_LENGTH_H` |
| `cl_ctx` | struct | `include/css_length.h:91` | `` |
| `cl_is_length_unit` | function | `include/css_length.h:253` | `int cl_is_length_unit(const char *unit, size_t unit_len);` |
| `cl_lp` | struct | `include/css_length.h:139` | `` |
| `cl_number` | function | `include/css_length.h:237` | `int cl_number(const char *s, double *out, const char **endp);` |
| `cl_status` | enum | `include/css_length.h:68` | `` |
| `cl_unit_font_ratio` | function | `include/css_length.h:189` | `double cl_unit_font_ratio(const char *unit, size_t unit_len);` |
| `cl_unit_is_font_relative` | function | `include/css_length.h:164` | `* cl_unit_is_font_relative() draws. */ /* * Re-fits a resolved length to a different font-size: * * used = px + em *...` |
| `font_size` | type_alias | `include/css_length.h:91` | `typedef struct cl_ctx { double font_size;` |
| `here` | function | `include/css_length.h:193` | `* Every input cl_resolve accepts resolves identically here (with has_pct 0);` |
| `length` | function | `include/css_length.h:213` | `* * A basis that is not a usable length (negative, zero, non-finite) contributes * nothing, but the absolute...` |
| `prelude` | function | `include/css_length.h:106` | `* correct context for a media query prelude (whose `em` is defined to use the * initial font size, never the...` |
| `px` | type_alias | `include/css_length.h:139` | `typedef struct cl_lp { double px;` |
| `CM_LAYERS` | macro | `include/css_mask.h:12` | `#define CM_LAYERS` |
| `FREEDOM_CSS_MASK_H` | macro | `include/css_mask.h:2` | `#define FREEDOM_CSS_MASK_H` |
| `cm_clip` | enum | `include/css_mask.h:15` | `` |
| `cm_comp` | enum | `include/css_mask.h:14` | `` |
| `cm_decode_layer` | function | `include/css_mask.h:36` | `void cm_decode_layer(int meta, int alphas, int poss, cm_layer *out);` |
| `cm_encode_layer` | function | `include/css_mask.h:35` | `void cm_encode_layer(const cm_layer *l, int *meta, int *alphas, int *poss);` |
| `cm_is_mask_prop` | function | `include/css_mask.h:28` | `int cm_is_mask_prop(const char *prop);` |
| `cm_layer` | struct | `include/css_mask.h:19` | `` |
| `kind` | type_alias | `include/css_mask.h:19` | `typedef struct cm_layer { int kind;` |
| `malformed` | function | `include/css_mask.h:31` | `* the value is unsupported or malformed (the caller drops the declaration). */ int cm_expand(const char *prop, const...` |
| `CMQ_CONTAINER_NAMES` | macro | `include/css_mq.h:37` | `#define CMQ_CONTAINER_NAMES` |
| `CMQ_MAX_DEPTH` | macro | `include/css_mq.h:16` | `#define CMQ_MAX_DEPTH` |
| `CMQ_TOK_MAX` | macro | `include/css_mq.h:17` | `#define CMQ_TOK_MAX` |
| `FREEDOM_CSS_MQ_H` | macro | `include/css_mq.h:2` | `#define FREEDOM_CSS_MQ_H` |
| `cmq_container` | struct | `include/css_mq.h:41` | `` |
| `cmq_container_decl` | function | `include/css_mq.h:63` | `int cmq_container_decl(const char *prop, const char *val, int *type, unsigned names[CMQ_CONTAINER_NAMES], int...` |
| `cmq_container_surely` | function | `include/css_mq.h:34` | `int cmq_container_surely(const char *s, size_t len, int max_width);` |
| `cmq_env` | struct | `include/css_mq.h:19` | `` |
| `cmq_matches` | function | `include/css_mq.h:28` | `int cmq_matches(const char *s, size_t len, const cmq_env *env);` |
| `cmq_name_hash` | function | `include/css_mq.h:50` | `unsigned cmq_name_hash(const char *s, size_t n);` |
| `names` | type_alias | `include/css_mq.h:41` | `typedef struct cmq_container { unsigned names[CMQ_CONTAINER_NAMES];` |
| `width_px` | type_alias | `include/css_mq.h:18` | `typedef struct cmq_env { int width_px;` |
| `CSEL_FOLD_MARK` | macro | `include/css_select.h:216` | `#define CSEL_FOLD_MARK` |
| `CSEL_FOLD_PREFIX` | macro | `include/css_select.h:215` | `#define CSEL_FOLD_PREFIX` |
| `CSEL_IDENT_SCRATCH` | macro | `include/css_select.h:217` | `#define CSEL_IDENT_SCRATCH` |
| `CSS_MAX_CLASSES_PER_SEL` | macro | `include/css_select.h:28` | `#define CSS_MAX_CLASSES_PER_SEL` |
| `CSS_MAX_SUB_SELS` | macro | `include/css_select.h:83` | `#define CSS_MAX_SUB_SELS` |
| `CSS_SUB_MAX_ATTRS` | macro | `include/css_select.h:84` | `#define CSS_SUB_MAX_ATTRS` |
| `CSS_SUB_MAX_PSEUDOS` | macro | `include/css_select.h:85` | `#define CSS_SUB_MAX_PSEUDOS` |
| `CSS_TOK_MAX` | macro | `include/css_select.h:27` | `#define CSS_TOK_MAX` |
| `FREEDOM_CSS_SELECT_H` | macro | `include/css_select.h:2` | `#define FREEDOM_CSS_SELECT_H` |
| `comb` | type_alias | `include/css_select.h:139` | `typedef struct css_sel { int comb[CSS_MAX_COMPOUNDS];` |
| `conservative` | function | `include/css_select.h:202` | `* Pure and conservative (anything unrecognised answers 1). A selector that answers 0 matches * from the element's...` |
| `csel_anc_reject` | function | `include/css_select.h:195` | `static inline int csel_anc_reject(const css_sel *sel, const css_element *el)` |
| `csel_ci_eq` | function | `include/css_select.h:244` | `static inline int csel_ci_eq(const char *a, const char *b)` |
| `csel_ci_starts` | function | `include/css_select.h:253` | `static inline int csel_ci_starts(const char *a, const char *p)` |
| `csel_compact_dup` | function | `include/css_select.h:173` | `css_sel *csel_compact_dup(const css_sel *sel);` |
| `csel_compact_size` | function | `include/css_select.h:168` | `size_t csel_compact_size(int nparts);` |
| `csel_decl_end` | function | `include/css_select.h:236` | `size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace);` |
| `csel_element_feature_bits` | function | `include/css_select.h:194` | `unsigned long long csel_element_feature_bits(const css_element *e);` |
| `csel_emit_utf8` | function | `include/css_select.h:220` | `size_t csel_emit_utf8(unsigned int cp, char *out);` |
| `csel_escape_len` | function | `include/css_select.h:224` | `size_t csel_escape_len(const char *s, size_t i, size_t b);` |
| `csel_ident_ch` | function | `include/css_select.h:281` | `static inline int csel_ident_ch(char c)` |
| `csel_ident_eq` | function | `include/css_select.h:228` | `int csel_ident_eq(const char *stored, const char *tok, size_t tlen);` |
| `csel_ident_fold` | function | `include/css_select.h:226` | `void csel_ident_fold(const char *src, size_t len, char *dst);` |
| `csel_lower_ch` | function | `include/css_select.h:240` | `static inline char csel_lower_ch(char c)` |
| `csel_matches` | function | `include/css_select.h:186` | `int csel_matches(const css_sel *sel, const css_element *el, const char *target_id, int allow_pseudo_el, int...` |
| `csel_parse` | function | `include/css_select.h:177` | `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel);` |
| `csel_read_ident` | function | `include/css_select.h:231` | `int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower);` |
| `csel_span_eq` | function | `include/css_select.h:262` | `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)` |
| `csel_substr` | function | `include/css_select.h:273` | `static inline int csel_substr(const char *hay, const char *needle, int ci)` |
| `csel_unescape` | function | `include/css_select.h:222` | `void csel_unescape(char *dst, size_t cap, const char *src, size_t n);` |
| `css_attr_match` | struct | `include/css_select.h:88` | `` |
| `css_compound` | struct | `include/css_select.h:122` | `` |
| `css_pseudo_match` | struct | `include/css_select.h:112` | `` |
| `css_sel` | struct | `include/css_select.h:139` | `` |
| `css_sub_sel` | struct | `include/css_select.h:95` | `` |
| `identifier` | function | `include/css_select.h:208` | `* A selector identifier (tag, .class, #id) is read with CSS escapes decoded * (`.md\:flex` is the class "md:flex")...` |
| `kind` | type_alias | `include/css_select.h:112` | `typedef struct css_pseudo_match { int kind;` |
| `name` | type_alias | `include/css_select.h:88` | `typedef struct css_attr_match { char name[CSS_TOK_MAX];` |
| `tag` | type_alias | `include/css_select.h:94` | `typedef struct css_sub_sel { char tag[CSS_TOK_MAX];` |
| `tag` | type_alias | `include/css_select.h:122` | `typedef struct css_compound { char tag[CSS_TOK_MAX];` |
| `FREEDOM_CSS_TEXT_H` | macro | `include/css_text.h:2` | `#define FREEDOM_CSS_TEXT_H` |
| `ct_emit_spacing` | function | `include/css_text.h:24` | `int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val);` |
| `ct_expand_shadow` | function | `include/css_text.h:25` | `int ct_expand_shadow(const char *val, css_decl *dst, int cap);` |
| `ct_expand_valign` | function | `include/css_text.h:14` | `int ct_expand_valign(const char *val, css_decl *dst, int cap);` |
| `ct_interp_aspect_ratio` | function | `include/css_text.h:20` | `int ct_interp_aspect_ratio(const char *v, int *num, int *den);` |
| `ct_interp_direction` | function | `include/css_text.h:21` | `int ct_interp_direction(const char *v);` |
| `ct_interp_fontfamily` | function | `include/css_text.h:10` | `int ct_interp_fontfamily(const char *v);` |
| `ct_interp_liststyle` | function | `include/css_text.h:22` | `int ct_interp_liststyle(const char *v);` |
| `ct_interp_opacity` | function | `include/css_text.h:12` | `int ct_interp_opacity(const char *v);` |
| `ct_interp_spacing` | function | `include/css_text.h:23` | `int ct_interp_spacing(const char *v, int *out);` |
| `ct_interp_tabsize` | function | `include/css_text.h:17` | `int ct_interp_tabsize(const char *v);` |
| `ct_interp_textdeco_style` | function | `include/css_text.h:18` | `int ct_interp_textdeco_style(const char *v);` |
| `ct_interp_textdeco_thickness` | function | `include/css_text.h:19` | `int ct_interp_textdeco_thickness(const char *v);` |
| `ct_interp_texttransform` | function | `include/css_text.h:11` | `int ct_interp_texttransform(const char *v);` |
| `ct_interp_transition_property` | function | `include/css_text.h:15` | `int ct_interp_transition_property(const char *v);` |
| `ct_interp_valign` | function | `include/css_text.h:13` | `int ct_interp_valign(const char *v);` |
| `ct_interp_whitespace` | function | `include/css_text.h:16` | `int ct_interp_whitespace(const char *v);` |
| `FREEDOM_CSS_VALUES_H` | macro | `include/css_values.h:2` | `#define FREEDOM_CSS_VALUES_H` |
| `black` | function | `include/css_values.h:27` | `* transparent black (127 << 24) -- text that paints nothing, not an absent * value. CC_COLOR_CURRENT and -1...` |
| `cv_bg_alpha_of` | function | `include/css_values.h:15` | `int cv_bg_alpha_of(const char *v);` |
| `cv_color_ok` | function | `include/css_values.h:14` | `int cv_color_ok(int c);` |
| `cv_filter_scale` | function | `include/css_values.h:20` | `double cv_filter_scale(int pct);` |
| `cv_interp_bg` | function | `include/css_values.h:30` | `int cv_interp_bg(const char *v);` |
| `cv_interp_color` | function | `include/css_values.h:13` | `int cv_interp_color(const char *v);` |
| `cv_parse_color` | function | `include/css_values.h:12` | `int cv_parse_color(const char *v);` |
| `cv_parse_color_t7` | function | `include/css_values.h:24` | `int cv_parse_color_t7(const char *v);` |
| `CVR_CHAIN_MAX` | macro | `include/css_vars.h:45` | `#define CVR_CHAIN_MAX` |
| `CVR_MAX_DEPTH` | macro | `include/css_vars.h:22` | `#define CVR_MAX_DEPTH` |
| `CVR_MAX_ENTRIES` | macro | `include/css_vars.h:21` | `#define CVR_MAX_ENTRIES` |
| `CVR_MAX_LOOKUPS` | macro | `include/css_vars.h:26` | `#define CVR_MAX_LOOKUPS` |
| `CVR_NAME_MAX` | macro | `include/css_vars.h:19` | `#define CVR_NAME_MAX` |
| `CVR_VALUE_MAX` | macro | `include/css_vars.h:20` | `#define CVR_VALUE_MAX` |
| `FREEDOM_CSS_VARS_H` | macro | `include/css_vars.h:2` | `#define FREEDOM_CSS_VARS_H` |
| `cvr_chain` | struct | `include/css_vars.h:46` | `` |
| `cvr_collect_decls` | function | `include/css_vars.h:83` | `void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b);` |
| `cvr_count` | function | `include/css_vars.h:71` | `size_t cvr_count(const cvr_table *t);` |
| `cvr_ent` | struct | `include/css_vars.h:28` | `` |
| `cvr_free` | function | `include/css_vars.h:78` | `void cvr_free(cvr_table *t);` |
| `cvr_get` | function | `include/css_vars.h:69` | `const char *cvr_get(const cvr_table *t, const char *name, size_t nlen);` |
| `cvr_lookup` | function | `include/css_vars.h:96` | `const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen);` |
| `cvr_reset` | function | `include/css_vars.h:75` | `void cvr_reset(cvr_table *t);` |
| `cvr_scope` | struct | `include/css_vars.h:54` | `` |
| `cvr_table` | struct | `include/css_vars.h:35` | `` |
| `declaration` | function | `include/css_vars.h:91` | `* then drops the whole declaration (CSS Variables 1: invalid at computed time). */ int cvr_resolve(const char *val...` |
| `name` | function | `include/css_vars.h:62` | `* name (last declaration wins). Returns 1 when stored, 0 when dropped: a name that * is not "--" + at least one...` |
| `DU_MAX_ENCODED_LEN` | macro | `include/data_url.h:43` | `#define DU_MAX_ENCODED_LEN` |
| `FREEDOM_DATA_URL_H` | macro | `include/data_url.h:2` | `#define FREEDOM_DATA_URL_H` |
| `allocation` | function | `include/data_url.h:21` | `* * du_base64_payload does no allocation (it only slices the caller's url string);` |
| `closed` | function | `include/data_url.h:65` | `* 4 fails closed (DU_ERR_BAD_BASE64) -- never decodes a partial prefix. * b64/out/out_len == NULL (with b64_len !=...` |
| `du_is_data_url` | function | `include/data_url.h:46` | `int du_is_data_url(const char *url);` |
| `du_status` | enum | `include/data_url.h:27` | `` |
| `worker` | function | `include/data_url.h:59` | `* the confined worker (du_decode). */ du_status du_shape_ok(const char *url);` |
| `FREEDOM_DISK_STORE_H` | macro | `include/disk_store.h:2` | `#define FREEDOM_DISK_STORE_H` |
| `ds_free` | function | `include/disk_store.h:47` | `void ds_free(uint8_t *buf, size_t len);` |
| `ds_status` | enum | `include/disk_store.h:25` | `` |
| `DOM_KIND_COMMENT` | macro | `include/dom.h:213` | `#define DOM_KIND_COMMENT` |
| `DOM_KIND_ELEMENT` | macro | `include/dom.h:211` | `#define DOM_KIND_ELEMENT` |
| `DOM_KIND_NONE` | macro | `include/dom.h:210` | `#define DOM_KIND_NONE` |
| `DOM_KIND_TEXT` | macro | `include/dom.h:212` | `#define DOM_KIND_TEXT` |
| `DOM_MAX_HANDLES` | macro | `include/dom.h:216` | `#define DOM_MAX_HANDLES` |
| `DOM_NODE_NONE` | macro | `include/dom.h:37` | `#define DOM_NODE_NONE` |
| `FREEDOM_DOM_H` | macro | `include/dom.h:2` | `#define FREEDOM_DOM_H` |
| `count` | function | `include/dom.h:64` | `* match count (which may exceed cap, so the caller can size a buffer). */ size_t dom_get_by_tag(const dom_index...` |
| `cycle` | function | `include/dom.h:176` | `* Rejects a cycle (child being an ancestor of parent). Invalid handle / self / cycle * => DOM_ERR_NULL_ARG. */...` |
| `dom_attribute_names` | function | `include/dom.h:133` | `size_t dom_attribute_names(const dom_index *idx, dom_node_id node, const char **names, size_t *lens, size_t cap);` |
| `dom_document_position` | function | `include/dom.h:106` | `size_t dom_document_position(const dom_index *idx, dom_node_id node);` |
| `dom_document_title` | function | `include/dom.h:141` | `const char *dom_document_title(const dom_index *idx, size_t *len);` |
| `dom_free` | function | `include/dom.h:48` | `void dom_free(dom_index *idx);` |

Next: [SYMBOLS_p4.md](SYMBOLS_p4.md)
