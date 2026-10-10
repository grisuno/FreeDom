# Subsystem: src (page 3 of 8)
Previous: [KB_src_p2.md](KB_src_p2.md)

## src/dom_debug.c
- Doc: dd_cursor: Bounded write cursor: `pos` bytes are committed to `out` (always leaving room for the...
- Layer: utility
- Language: c
- Symbols:
  - `dd_cursor` (struct, line 24)
  - `dd_putc` (function, line 31) `static void dd_putc(dd_cursor *c, char ch)`
  - `dd_emit` (function, line 36) `static void dd_emit(dd_cursor *c, const char *s, size_t len)`
  - `dd_puts` (function, line 40) `static void dd_puts(dd_cursor *c, const char *s)`
  - `dd_printf` (function, line 48) `static void dd_printf(dd_cursor *c, const char *fmt, ...)`
  - `dd_w` (function, line 80) `static int dd_w(int v)`
  - `dd_color` (function, line 83) `static void dd_color(dd_cursor *c, int rgb)`
  - `dd_display_name` (function, line 88) `static const char *dd_display_name(int d)`
  - `dd_justify_name` (function, line 96) `static const char *dd_justify_name(int j)`
  - `dd_align_name` (function, line 108) `static const char *dd_align_name(int a)`
  - `dd_position_name` (function, line 118) `static const char *dd_position_name(int p)`
  - `dd_visibility_name` (function, line 129) `static const char *dd_visibility_name(int v)`
  - `dd_mix_blend_name` (function, line 137) `static const char *dd_mix_blend_name(int m)`
  - `dd_overflow_name` (function, line 156) `static const char *dd_overflow_name(int o)`
  - `dd_cursor_name` (function, line 165) `static const char *dd_cursor_name(int c)`
  - `dd_text_overflow_name` (function, line 198) `static const char *dd_text_overflow_name(int t)`
  - `dd_inset` (function, line 203) `static int dd_inset(int v)`
  - `dd_object_fit_name` (function, line 207) `static const char *dd_object_fit_name(int o)`
  - `dd_image_rendering_name` (function, line 218) `static const char *dd_image_rendering_name(int r)`
  - `dd_border_style_name` (function, line 227) `static const char *dd_border_style_name(int s)`
  - `dd_box_line` (function, line 260) `static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b)`
  - `dd_block_line` (function, line 320) `static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b)`
  - `dd_format` (function, line 396) `size_t dd_format(const rd_doc *doc, char *out, size_t cap)`
  - `dd_format_css` (function, line 428) `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)`
- Depends on: `include/box_style.h`, `include/css.h`, `include/dom_debug.h`, `include/flex_layout.h`, `include/page_view.h`

## src/download.c
- Doc: lc: download — pure helpers for "save this resource to disk".
- Layer: utility
- Language: c
- Symbols:
  - `lc` (function, line 13) `static int lc(int c)`
  - `ci_find` (function, line 19) `static const char *ci_find(const char *hay, const char *needle)`
  - `media_type` (function, line 33) `static void media_type(const char *content_type, char *buf, size_t bufsz)`
  - `dl_should_download` (function, line 47) `int dl_should_download(const char *content_type, const char *content_disposition)`
  - `dl_ext_for_type` (function, line 58) `const char *dl_ext_for_type(const char *content_type)`
  - `copy_span` (function, line 85) `static void copy_span(const char *src, const char *end, char *buf, size_t bufsz)`
  - `extract_disposition_name` (function, line 96) `static int extract_disposition_name(const char *cd, char *buf, size_t bufsz)`
  - `extract_url_name` (function, line 134) `static int extract_url_name(const char *url, char *buf, size_t bufsz)`
  - `has_extension` (function, line 148) `static int has_extension(const char *name)`
  - `dl_pick_name` (function, line 153) `dl_status dl_pick_name(const char *url, const char *content_disposition,
                       c...`
  - `dl_build_path` (function, line 195) `dl_status dl_build_path(const char *dir, const char *name, char *out, size_t outsz)`
  - `dl_check_size` (function, line 213) `dl_status dl_check_size(size_t len)`
- Depends on: `include/download.h`, `include/pdf_export.h`

## src/flex_layout.c
- Doc: nn: No I/O, no global state, no dynamic allocation: fixed-size stack scratch buffers bounded by...
- Layer: presentation
- Language: c
- Symbols:
  - `nn` (function, line 18) `static double nn(double v)`
  - `fx_flex_line` (function, line 22) `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                ...`
  - `fx_grid_columns` (function, line 127) `fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          doubl...`
  - `fx_autofill_count` (function, line 132) `size_t fx_autofill_count(double avail, double gap, double minw)`
  - `fx_grid_columns_weighted` (function, line 142) `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                      ...`
  - `fx_grid_place_span` (function, line 176) `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                      ...`
  - `fx_grid_area_hash` (function, line 280) `unsigned fx_grid_area_hash(const char *name)`
  - `area_token_is_null_cell` (function, line 304) `static int area_token_is_null_cell(const char *tok, size_t len)`
  - `fx_grid_areas_parse` (function, line 310) `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)`
  - `fx_grid_area_rect` (function, line 385) `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,
                            int ...`
  - `float_pack_impl` (function, line 427) `static fx_status float_pack_impl(const double *width, const int *side, size_t n,
                ...`
  - `fx_float_insets` (function, line 467) `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,
                 ...`
  - `fx_float_pack` (function, line 507) `fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        d...`
  - `fx_float_pack_wrap` (function, line 512) `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,
                    ...`
  - `fx_grid_cell` (function, line 554) `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)`
  - `fx_auto_margins` (function, line 566) `fx_status fx_auto_margins(fx_result *res, size_t n, const unsigned char *auto_l,
                ...`
  - `fx_auto_min_size` (function, line 589) `double fx_auto_min_size(double min_content, double basis, double author_min,
                    ...`
  - `fx_multicol_used` (function, line 603) `fx_status fx_multicol_used(double avail_w, int column_count, double column_width,
               ...`
  - `fx_multicol_balance` (function, line 640) `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,
                        ...`
  - `fx_justify_name` (function, line 671) `const char *fx_justify_name(fx_justify j)`
  - `fx_column_place` (function, line 683) `fx_status fx_column_place(const double *h, const double *grow, size_t n, double gap,
            ...`
  - `fx_column_place_m` (function, line 690) `fx_status fx_column_place_m(const double *h, const double *grow, const int *mauto,
              ...`
  - `fx_cross_offset` (function, line 751) `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r)`
  - `FX_EPS` (macro, line 15) `#define FX_EPS`
- Depends on: `include/flex_layout.h`

## src/form.c
- Doc: put_char: No I/O, no global state.
- Layer: utility
- Language: c
- Symbols:
  - `put_char` (function, line 17) `static int put_char(char *out, size_t outsz, size_t *pos, char c)`
  - `enc_component` (function, line 25) `static int enc_component(const char *s, char *out, size_t outsz, size_t *pos)`
  - `fm_encode` (function, line 43) `fm_status fm_encode(const fm_field *fields, size_t n,
                    char *out, size_t outsz...`
  - `copy_fit` (function, line 66) `static int copy_fit(char *dst, size_t dstsz, const char *src)`
  - `clean_action` (function, line 75) `static int clean_action(const char *action, char *out, size_t outsz)`
  - `strip_query` (function, line 93) `static void strip_query(char *url)`
  - `resolve_target` (function, line 101) `static fm_block_reason resolve_target(const char *base, const char *act,
                        ...`
  - `fm_build` (function, line 120) `fm_status fm_build(const char *base, const char *action, fm_method method,
                   con...`
- Depends on: `include/form.h`

## src/frame_clock.c
- Layer: utility
- Language: c
- Symbols:
  - `fc_set_active` (function, line 16) `void fc_set_active(fc_clock *c, int active)`
  - `fc_needs_tick` (function, line 21) `int fc_needs_tick(const fc_clock *c)`
  - `fc_interval_ms` (function, line 26) `int fc_interval_ms(const fc_clock *c)`
  - `FC_DEFAULT_INTERVAL_MS` (macro, line 8) `#define FC_DEFAULT_INTERVAL_MS`
- Depends on: `include/frame_clock.h`

## src/freebug.c
- Layer: utility
- Language: c
- Symbols:
  - `fb_buffer_init` (function, line 15) `void fb_buffer_init(fb_buffer *b)`
  - `fb_buffer_push` (function, line 19) `int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)`
  - `fb_buffer_push_loc` (function, line 23) `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len,
                   ...`
  - `fb_buffer_reset` (function, line 78) `void fb_buffer_reset(fb_buffer *b)`
  - `fb_buffer_free` (function, line 91) `void fb_buffer_free(fb_buffer *b)`
  - `fb_buffer_count` (function, line 101) `size_t fb_buffer_count(const fb_buffer *b)`
  - `fb_buffer_at` (function, line 105) `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)`
  - `fb_level_name` (function, line 110) `const char *fb_level_name(int level)`
  - `whole` (function, line 5) `* FB_MAX_TOTAL_BYTES is dropped whole (overflow flag raised, prior entries kept);`
- Depends on: `include/freebug.h`

## src/freedom.c
- Doc: is_overlay_http: fprintf(fp, "  --dump-video-url: headless, print the first detected video...
- Layer: utility
- Language: c
- Symbols:
  - `print_usage` (function, line 47) `static void print_usage(FILE *fp, const char *prog)`
  - `is_https_url` (function, line 73) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 77) `static int is_http_url(const char *s)`
  - `is_overlay_http` (function, line 82) `static int is_overlay_http(const char *s)`
  - `now_us` (function, line 136) `static uint64_t now_us(void)`
  - `timings_ensure_init` (function, line 142) `static void timings_ensure_init(void)`
  - `timings_enabled` (function, line 146) `static int timings_enabled(void)`
  - `timings_dump` (function, line 150) `static void timings_dump(void)`
  - `user_impersonate_enabled` (function, line 198) `static int user_impersonate_enabled(void)`
  - `read_file` (function, line 205) `static char *read_file(const char *path, size_t *out_len)`
  - `headless_load_hosts` (function, line 223) `static void headless_load_hosts(void)`
  - `is_blank_text` (function, line 253) `static int is_blank_text(const char *s)`
  - `print_doc` (function, line 266) `static void print_doc(const rd_doc *doc)`
  - `print_console` (function, line 359) `static void print_console(const fb_buffer *log)`
  - `print_dom` (function, line 376) `static void print_dom(const rd_doc *doc)`
  - `print_dom_css` (function, line 391) `static void print_dom_css(const rd_doc *doc)`
  - `headless_fetch` (function, line 415) `static int headless_fetch(void *ctx, const char *method, const char *url,
                       ...`
  - `foldback_cookies` (function, line 477) `static void foldback_cookies(const char *url, const char *jar)`
  - `print_css_drops` (function, line 501) `static void print_css_drops(const char *html, size_t len)`
  - `render_page` (function, line 532) `static int render_page(const char *html, size_t len, const char *top_url,
                       ...`
  - `sf_reason` (function, line 757) `static const char *sf_reason(sf_status ss)`
  - `fetch_and_render_one` (function, line 776) `static int fetch_and_render_one(const char *url, char **out_nav)`
  - `elsewhere` (function, line 837) `* page whose script immediately forwards elsewhere (e.g. a search engine's
 * JS-capability inter...`
  - `parent` (function, line 863) `* gated by the parent (ln_resolve: a local target stays under the document's
 * directory, a remo...`
  - `run_headless` (function, line 900) `static int run_headless(const char *target)`
  - `video_fetch_with_fallback` (function, line 936) `static sf_status video_fetch_with_fallback(const char *url, sf_config *cfg,
                     ...`
  - `run_dump_video` (function, line 1047) `static int run_dump_video(const char *url)`
  - `main` (function, line 1066) `int main(int argc, char **argv)`
  - `gets` (function, line 411) `* gate a click gets (https-only, no downgrade, no foreign scheme), so relative * subresources work. Realm-routed...`
  - `pool` (function, line 592) `* the pool (unconsumed results freed, in-flight fetches joined). */ tab_set_fetcher(t, headless_fetch, (void...`
  - `only` (function, line 645) `* styling for the local render only (no network). --images enables image loading * AND rendering, including remote...`
  - `BLOCKED` (function, line 802) `* is BLOCKED (fail closed), never leaked over the clearnet. */ nr_route route = nr_route_for(url, global_net);`
  - `_POSIX_C_SOURCE` (macro, line 9) `#define _POSIX_C_SOURCE`
  - `_DEFAULT_SOURCE` (macro, line 10) `#define _DEFAULT_SOURCE`
  - `EXIT_OK` (macro, line 43) `#define EXIT_OK`
  - `EXIT_ERROR` (macro, line 44) `#define EXIT_ERROR`
  - `EXIT_USAGE` (macro, line 45) `#define EXIT_USAGE`
  - `CSS_DROPS_REPORT_MAX` (macro, line 161) `#define CSS_DROPS_REPORT_MAX`
  - `HL_JS_NAV_MAX` (macro, line 772) `#define HL_JS_NAV_MAX`
- Depends on: `include/dom_debug.h`, `include/freebug.h`, `include/hls.h`, `include/hostblock.h`, `include/html_parse.h`, `include/js_policy.h`, `include/link_nav.h`, `include/media_decoder.h`, `include/net_realm.h`, `include/page_view.h`, `include/perf_trace.h`, `include/prefetch.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/tab.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/webcaps.h`

## src/hls.c
- Doc: last_char: Finds the last occurrence of character `c` in `s` (length `n`). * Returns NULL if not...
- Layer: utility
- Language: c
- Symbols:
  - `last_char` (function, line 38) `static const char *last_char(const char *s, size_t n, int c)`
  - `parse_attr_long` (function, line 48) `static int parse_attr_long(const char *attrs, const char *end,
                           const c...`
  - `parse_attr_resolution` (function, line 62) `static void parse_attr_resolution(const char *attrs, const char *end,
                           ...`
  - `hls_parse` (function, line 80) `hls_status hls_parse(const char *text, size_t len, hls_playlist **out)`
  - `hls_select_variant` (function, line 202) `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h)`
  - `hls_resolve_url` (function, line 223) `size_t hls_resolve_url(const char *base_url, const char *segment_url,
                       char...`
  - `hls_playlist_free` (function, line 253) `void hls_playlist_free(hls_playlist *pl)`
  - `name` (function, line 46) `* attr is the attribute name (e.g. "BANDWIDTH=");`
  - `_GNU_SOURCE` (macro, line 21) `#define _GNU_SOURCE`
  - `_POSIX_C_SOURCE` (macro, line 22) `#define _POSIX_C_SOURCE`
- Depends on: `include/hls.h`

## src/hostblock.c
- Doc: table_probe: Finds the slot for key (length klen) in t, which must have a free slot.
- Layer: utility
- Language: c
- Symbols:
  - `hb_table` (struct, line 24)
  - `hb_set` (struct, line 30)
  - `table_probe` (function, line 38) `static size_t table_probe(const hb_table *t, const char *key, size_t klen)`
  - `table_grow` (function, line 49) `static int table_grow(hb_table *t, size_t newcap)`
  - `table_insert` (function, line 71) `static int table_insert(hb_table *t, const char *key, size_t klen)`
  - `table_contains` (function, line 92) `static int table_contains(const hb_table *t, const char *key)`
  - `table_free` (function, line 98) `static void table_free(hb_table *t)`
  - `lower` (function, line 107) `static char lower(char c)`
  - `is_ip_token` (function, line 113) `static int is_ip_token(const char *s, size_t n)`
  - `is_domain_char` (function, line 122) `static int is_domain_char(char c)`
  - `hb_new` (function, line 144) `hb_set *hb_new(void)`
  - `hb_free` (function, line 149) `void hb_free(hb_set *s)`
  - `hb_load` (function, line 156) `hb_status hb_load(hb_set *s, const char *text, hb_list list)`
  - `hb_check` (function, line 193) `hb_decision hb_check(const hb_set *s, const char *host)`
  - `hb_is_allowlisted` (function, line 218) `int hb_is_allowlisted(const hb_set *s, const char *host)`
  - `hb_count` (function, line 238) `size_t hb_count(const hb_set *s, hb_list list)`
  - `HB_MAX_HOST` (macro, line 19) `#define HB_MAX_HOST`
  - `HB_INIT_CAP` (macro, line 20) `#define HB_INIT_CAP`
- Depends on: `include/hostblock.h`, `include/util.h`

## src/hostedit.c
- Doc: valid_host: #include "hostedit.h" #include <string.h> static char he_lower(char c) { return (c...
- Layer: utility
- Language: c
- Symbols:
  - `suggest_ctx` (struct, line 136)
  - `he_lower` (function, line 12) `static char he_lower(char c)`
  - `is_label_char` (function, line 16) `static int is_label_char(char c)`
  - `valid_host` (function, line 22) `static int valid_host(const char *host, size_t n)`
  - `he_make_line` (function, line 41) `he_status he_make_line(const char *host, char *out, size_t cap)`
  - `is_ip_token` (function, line 67) `static int is_ip_token(const char *ts, const char *te)`
  - `he_scan` (function, line 80) `static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), void *ctx)`
  - `has_host_cb` (function, line 105) `static int has_host_cb(const char *ts, size_t tl, void *ctx)`
  - `he_text_has_host` (function, line 109) `int he_text_has_host(const char *text, const char *host)`
  - `contains_ci` (function, line 115) `static int contains_ci(const char *hs, size_t hl, const char *needle)`
  - `starts_with_ci` (function, line 128) `static int starts_with_ci(const char *hs, size_t hl, const char *pfx)`
  - `suggest_cb` (function, line 144) `static int suggest_cb(const char *ts, size_t tl, void *vctx)`
  - `he_suggest` (function, line 164) `int he_suggest(const char *text, const char *query,
               char results[][HE_MAX_HOST + 1...`
- Depends on: `include/hostedit.h`

## src/html_parse.c
- Doc: node_next: }; /* --- helpers --- static char *dup_bytes(const lxb_char_t *src, size_t len) { if...
- Layer: utility
- Language: c
- Symbols:
  - `hp_document` (struct, line 21)
  - `dup_bytes` (function, line 27) `static char *dup_bytes(const lxb_char_t *src, size_t len)`
  - `node_next` (function, line 37) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)`
  - `attr_is_event_handler` (function, line 47) `static int attr_is_event_handler(const lxb_dom_attr_t *attr)`
  - `node_is_script` (function, line 54) `static int node_is_script(const lxb_dom_node_t *node)`
  - `strip_scripts` (function, line 60) `static void strip_scripts(lxb_html_document_t *document)`
  - `type_is` (function, line 100) `static int type_is(const lxb_char_t *t, size_t len, const char *word)`
  - `type_is_module` (function, line 117) `static int type_is_module(const lxb_char_t *t, size_t len)`
  - `script_classify` (function, line 121) `static int script_classify(const lxb_dom_node_t *n,
                           const lxb_char_t *...`
  - `hp_extract_script_list` (function, line 164) `hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count)`
  - `hp_free_scripts` (function, line 238) `void hp_free_scripts(hp_script *scripts, size_t count)`
  - `attr_has_token_ci` (function, line 251) `static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle)`
  - `link_is_active_stylesheet` (function, line 272) `static int link_is_active_stylesheet(lxb_dom_element_t *el,
                                     ...`
  - `hp_extract_stylesheet_hrefs` (function, line 294) `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count)`
  - `hp_free_stylesheet_hrefs` (function, line 328) `void hp_free_stylesheet_hrefs(char **hrefs, size_t count)`
  - `strip_event_handlers` (function, line 334) `static void strip_event_handlers(lxb_html_document_t *document)`
  - `hp_config_default` (function, line 357) `hp_config hp_config_default(void)`
  - `hp_validate_input` (function, line 365) `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg)`
  - `hp_parse` (function, line 375) `hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out)`
  - `hp_element_count` (function, line 409) `size_t hp_element_count(const hp_document *doc)`
  - `hp_script_count` (function, line 419) `size_t hp_script_count(const hp_document *doc)`
  - `hp_event_handler_count` (function, line 429) `size_t hp_event_handler_count(const hp_document *doc)`
  - `hp_extract_text` (function, line 445) `char *hp_extract_text(const hp_document *doc, size_t *out_len)`
  - `hp_get_title` (function, line 464) `char *hp_get_title(const hp_document *doc, size_t *out_len)`
  - `hp_free` (function, line 479) `void hp_free(char *buf)`
  - `hp_document_free` (function, line 483) `void hp_document_free(hp_document *doc)`
  - `hp_document_root` (function, line 489) `const void *hp_document_root(const hp_document *doc)`
  - `lxb_dom_element_has_attribute` (function, line 230) `&& lxb_dom_element_has_attribute(sel, (const lxb_char_t *)"nomodule", 8);`
  - `_POSIX_C_SOURCE` (macro, line 9) `#define _POSIX_C_SOURCE`
- Depends on: `include/dom.h`, `include/html_parse.h`, `include/util.h`

## src/image_decode.c
- Doc: jpeg_err_ctx: libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG *...
- Layer: utility
- Language: c
- Symbols:
  - `jpeg_err_ctx` (struct, line 153)
  - `gif_reader` (struct, line 255)
  - `gif_bits` (struct, line 290)
  - `read_be32` (function, line 52) `static uint32_t read_be32(const uint8_t *p)`
  - `img_png_dimensions` (function, line 57) `img_status img_png_dimensions(const uint8_t *bytes, size_t len,
                              uin...`
  - `img_dimensions_ok` (function, line 68) `int img_dimensions_ok(uint32_t w, uint32_t h)`
  - `img_fit` (function, line 76) `void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,
             double *out_w, do...`
  - `premultiply` (function, line 90) `static void premultiply(uint8_t *data, size_t pixels)`
  - `img_decode_png` (function, line 102) `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `jpeg_error_longjmp` (function, line 158) `static void jpeg_error_longjmp(j_common_ptr cinfo)`
  - `jpeg_silence` (function, line 164) `static void jpeg_silence(j_common_ptr cinfo)`
  - `img_decode_jpeg` (function, line 166) `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `gr_u8` (function, line 260) `static int gr_u8(gif_reader *r, uint8_t *out)`
  - `gr_u16le` (function, line 266) `static int gr_u16le(gif_reader *r, uint16_t *out)`
  - `gr_skip` (function, line 273) `static int gr_skip(gif_reader *r, size_t n)`
  - `gr_skip_subblocks` (function, line 280) `static int gr_skip_subblocks(gif_reader *r)`
  - `gb_next_code` (function, line 298) `static int gb_next_code(gif_bits *b, unsigned width, unsigned *out)`
  - `gif_deinterlace_row` (function, line 319) `static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh)`
  - `gif_put_pixel` (function, line 334) `static void gif_put_pixel(uint32_t *canvas, uint32_t cw, uint32_t ch,
                          u...`
  - `img_decode_gif` (function, line 354) `img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `img_decode_webp` (function, line 520) `img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `img_decode` (function, line 553) `img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out)`
  - `img_pixels_free` (function, line 566) `void img_pixels_free(img_pixels *p)`
  - `img_format_name` (function, line 575) `const char *img_format_name(img_format f)`
  - `exit` (function, line 6) `* malformed stream fails closed instead of calling exit(). GIF uses an own pure-C * bounded LZW decoder (no giflib)....`
  - `PNG_IHDR_MIN` (macro, line 34) `#define PNG_IHDR_MIN`
  - `GIF_LZW_MAX_CODES` (macro, line 253) `#define GIF_LZW_MAX_CODES`
- Depends on: `include/image_decode.h`

## src/import_map.c
- Doc: str: A JSON string into an owned UTF-8 buffer (escapes decoded; a lone surrogate or a * raw...
- Layer: utility
- Language: c
- Symbols:
  - `im_entry` (struct, line 19)
  - `im_map` (struct, line 25)
  - `jr` (struct, line 34)
  - `scope` (type_alias, line 18) `typedef struct im_entry { int scope;`
  - `ws` (function, line 39) `static void ws(jr *r)`
  - `eat` (function, line 44) `static int eat(jr *r, char c)`
  - `hex4` (function, line 50) `static int hex4(const char *s, uint32_t *out)`
  - `put_utf8` (function, line 64) `static size_t put_utf8(char *o, uint32_t cp)`
  - `str` (function, line 78) `static char *str(jr *r)`
  - `skip` (function, line 128) `static void skip(jr *r, int depth)`
  - `url_like` (function, line 156) `static int url_like(const char *s)`
  - `dup_s` (function, line 168) `static char *dup_s(const char *s)`
  - `clear` (function, line 175) `static void clear(im_map *m)`
  - `add` (function, line 185) `static int add(im_map *m, int scope, const char *key, const char *addr, const char *doc_url,
    ...`
  - `specifier_map` (function, line 209) `static void specifier_map(jr *r, im_map *m, int scope, const char *doc_url,
                     ...`
  - `im_parse` (function, line 225) `im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn resolve, void *ctx)`
  - `match` (function, line 272) `static int match(const im_map *m, int scope, const char *key, char *out, size_t outsz)`
  - `im_resolve` (function, line 301) `int im_resolve(const im_map *m, const char *base, const char *specifier,
               im_url_fn...`
  - `im_count` (function, line 339) `size_t im_count(const im_map *m)`
  - `im_free` (function, line 343) `void im_free(im_map *m)`
  - `IM_MAX_DEPTH` (macro, line 16) `#define IM_MAX_DEPTH`
  - `IM_URL_MAX` (macro, line 17) `#define IM_URL_MAX`
- Depends on: `include/import_map.h`

## src/interp.c
- Doc: solve_bezier_t: } static double sample_bezier_dx(double t, double cx1, double cx2) { return 3.0...
- Layer: utility
- Language: c
- Symbols:
  - `sample_bezier_x` (function, line 18) `static double sample_bezier_x(double t, double cx1, double cx2)`
  - `sample_bezier_dx` (function, line 23) `static double sample_bezier_dx(double t, double cx1, double cx2)`
  - `sample_bezier_y` (function, line 29) `static double sample_bezier_y(double t, double cy1, double cy2)`
  - `solve_bezier_t` (function, line 35) `static double solve_bezier_t(double x, double cx1, double cx2)`
  - `ip_ease` (function, line 55) `double ip_ease(double t, const ip_ease_fn *fn)`
  - `ip_ease` (function, line 64) `case IP_EASE_EASE:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_ease` (function, line 70) `case IP_EASE_EASE_IN:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_ease` (function, line 76) `case IP_EASE_EASE_OUT:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_ease` (function, line 82) `case IP_EASE_EASE_IN_OUT:
        return ip_ease(t, &(ip_ease_fn)`
  - `ip_lerp` (function, line 134) `double ip_lerp(double a, double b, double t)`
  - `ip_lerp_color` (function, line 139) `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t)`
  - `ip_interp` (function, line 162) `double ip_interp(ip_val_kind kind, double a, double b, double t)`
  - `ip_kf_interp` (function, line 175) `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf,
                    int n_kf, do...`
  - `ip_anim_init` (function, line 196) `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease,
                  const ip_...`
  - `anim_effective_dir_for` (function, line 222) `static int anim_effective_dir_for(const ip_anim *a, int iter)`
  - `anim_effective_dir` (function, line 232) `static int anim_effective_dir(const ip_anim *a)`
  - `ip_anim_tick` (function, line 236) `int ip_anim_tick(ip_anim *a, double dt_ms)`
  - `ip_anim_current` (function, line 282) `double ip_anim_current(const ip_anim *a)`
  - `ip_anim_done` (function, line 320) `int ip_anim_done(const ip_anim *a)`
- Depends on: `include/interp.h`

## src/js_dom.c
- Doc: jd_handle: Coerces a JS argument to a node handle.
- Layer: utility
- Language: c
- Symbols:
  - `jd_method` (struct, line 428)
  - `jd_opaque_get` (function, line 27) `jd_opaque *jd_opaque_get(JSContext *ctx)`
  - `jd_idx` (function, line 31) `dom_index *jd_idx(JSContext *ctx)`
  - `jd_handle` (function, line 40) `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out)`
  - `jd_handle_or_null` (function, line 47) `JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h)`
  - `m_node_count` (function, line 53) `static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `m_get_element_by_id` (function, line 59) `static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val,
                       ...`
  - `jd_query_list` (function, line 70) `static JSValue jd_query_list(JSContext *ctx, JSValueConst arg, int by_class)`
  - `m_get_by_tag` (function, line 100) `static JSValue m_get_by_tag(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `m_get_by_class` (function, line 106) `static JSValue m_get_by_class(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_tag_name` (function, line 112) `static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_get_attribute` (function, line 122) `static JSValue m_get_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
  - `m_parent` (function, line 135) `static JSValue m_parent(JSContext *ctx, JSValueConst this_val,
                        int argc, ...`
  - `m_first_child` (function, line 143) `static JSValue m_first_child(JSContext *ctx, JSValueConst this_val,
                             ...`
  - `m_node_kind` (function, line 152) `static JSValue m_node_kind(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_child_node` (function, line 159) `static JSValue m_child_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_sibling_node` (function, line 166) `static JSValue m_sibling_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_create_char` (function, line 174) `static JSValue m_create_char(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_next_sibling` (function, line 188) `static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_precedes` (function, line 196) `static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_text_content` (function, line 207) `static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_set_text` (function, line 217) `static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,
                          int ar...`
  - `m_get_title` (function, line 231) `static JSValue m_get_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
  - `m_set_title` (function, line 239) `static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
  - `m_create_element` (function, line 252) `static JSValue m_create_element(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_append_child` (function, line 264) `static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_move_children` (function, line 275) `static JSValue m_move_children(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_clone_node` (function, line 289) `static JSValue m_clone_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_insert_before` (function, line 299) `static JSValue m_insert_before(JSContext *ctx, JSValueConst this_val,
                           ...`
  - `m_remove_child` (function, line 311) `static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,
                            ...`
  - `m_set_attribute` (function, line 320) `static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
  - `m_remove_attribute` (function, line 336) `static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,
                        ...`
  - `m_set_inner_html` (function, line 348) `static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_get_inner_html` (function, line 364) `static JSValue m_get_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_rect` (function, line 396) `static JSValue m_rect(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
  - `m_query_selector` (function, line 437) `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,
                          ...`
  - `m_query_selector_all` (function, line 450) `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,
                      ...`
  - `m_matches` (function, line 479) `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,
                         int argc...`
  - `m_closest` (function, line 491) `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,
                         int argc...`
  - `m_attr_names` (function, line 503) `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,
                            in...`
  - `attrNames` (function, line 610) `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so
     * a missing '...`
  - `js_env` (function, line 1223) `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the
 * document shim (uses...`
  - `jd_install` (function, line 1775) `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)`
  - `fails` (function, line 1852) `* cap is reached or an allocation fails (caller stops), else 0. */
static int cb_append(char **bu...`
  - `jd_install_console` (function, line 1966) `jd_status jd_install_console(js_context *ctx, fb_buffer *log)`
  - `jd_set_cookies` (function, line 2003) `jd_status jd_set_cookies(js_context *ctx, const char *cookies)`
  - `jd_get_cookies` (function, line 2023) `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)`
  - `jd_set_geometry` (function, line 2046) `jd_status jd_set_geometry(js_context *ctx, const jg_table *geom)`
  - `table` (function, line 571) `* a table (dom.viewport() non-null);`
  - `scripts` (function, line 768) `* player scripts (canPlayType feature-detection, play/pause, muted/loop * reflection, buffered ranges) run without...`
  - `enough` (function, line 931) `* enough (cloneNode/lastChild/removeChild/insertBefore) that library feature * detection does not throw: jQuery...`
  - `ms` (function, line 1067) `* due is the remaining virtual ms (the trusted parent advances the clock via * OP_TICK -> __tickTimers(elapsed);`
  - `empty` (function, line 1215) `* inert: DOM interface constructors are empty (instanceof yields false, harmless);`
  - `geometry` (function, line 1217) `* constant geometry (zero real leak);`
  - `size` (function, line 1220) `* the viewport reads a fixed normalized size (matches the 1920 width * anti_fp uses for @media, not the real window);`
  - `_GNU_SOURCE` (macro, line 10) `#define _GNU_SOURCE`
- Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `include/web_storage.h`, `src/js_dom_ext.h`, `src/js_dom_internal.h`, `src/js_location_internal.h`


Next: [KB_src_p4.md](KB_src_p4.md)
