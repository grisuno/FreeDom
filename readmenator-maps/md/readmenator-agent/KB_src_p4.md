# Subsystem: src (page 4 of 9)
Previous: [KB_src_p3.md](KB_src_p3.md)

## src/flex_layout.c
- Doc: nn: bounded by FX_MAX_ITEMS (no VLAs).
- Layer: presentation
- Language: c
- Symbols:
  - `nn` (function, line 19) `static double nn(double v)`
  - `fx_flex_line` (function, line 23) `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                ...`
  - `fx_grid_columns` (function, line 128) `fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          doubl...`
  - `fx_autofill_count` (function, line 133) `size_t fx_autofill_count(double avail, double gap, double minw)`
  - `fx_grid_columns_weighted` (function, line 143) `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                      ...`
  - `fx_grid_place_span` (function, line 177) `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                      ...`
  - `fx_grid_area_hash` (function, line 319) `unsigned fx_grid_area_hash(const char *name)`
  - `area_token_is_null_cell` (function, line 343) `static int area_token_is_null_cell(const char *tok, size_t len)`
  - `fx_grid_areas_parse` (function, line 349) `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)`
  - `fx_grid_area_rect` (function, line 424) `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,
                            int ...`
  - `float_pack_impl` (function, line 466) `static fx_status float_pack_impl(const double *width, const int *side, size_t n,
                ...`
  - `fx_float_insets` (function, line 506) `fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,
                 ...`
  - `fx_float_pack` (function, line 546) `fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        d...`
  - `fx_float_pack_wrap` (function, line 551) `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,
                    ...`
  - `fx_grid_cell` (function, line 593) `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)`
  - `fx_auto_margins` (function, line 605) `fx_status fx_auto_margins(fx_result *res, size_t n, const unsigned char *auto_l,
                ...`
  - `fx_auto_min_size` (function, line 628) `double fx_auto_min_size(double min_content, double basis, double author_min,
                    ...`
  - `fx_multicol_used` (function, line 645) `fx_status fx_multicol_used(double avail_w, int column_count, double column_width,
               ...`
  - `fx_multicol_balance` (function, line 682) `fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,
                        ...`
  - `fx_justify_name` (function, line 713) `const char *fx_justify_name(fx_justify j)`
  - `fx_column_place` (function, line 725) `fx_status fx_column_place(const double *h, const double *grow, size_t n, double gap,
            ...`
  - `fx_column_place_m` (function, line 732) `fx_status fx_column_place_m(const double *h, const double *grow, const int *mauto,
              ...`
  - `fx_cross_offset` (function, line 793) `double fx_cross_offset(double avail, double w, int align, int mauto_l, int mauto_r)`
  - `gl_ws` (function, line 805) `static int gl_ws(char c)`
  - `gl_lower` (function, line 809) `static int gl_lower(char c)`
  - `gl_kw` (function, line 812) `static int gl_kw(const char *p, const char *end, const char *kw)`
  - `gl_int` (function, line 822) `static int gl_int(const char *p, const char *end, long cap, long *out)`
  - `gl_side_range` (function, line 837) `static int gl_side_range(const char *p, const char *end, int *out)`
  - `fx_grid_line_side` (function, line 860) `int fx_grid_line_side(const char *s, int *out)`
  - `fx_grid_line_parse` (function, line 868) `int fx_grid_line_parse(const char *v, int *start, int *end)`
  - `gl_is_span` (function, line 885) `static int gl_is_span(int v)`
  - `gl_is_line` (function, line 886) `static int gl_is_line(int v)`
  - `fx_grid_line_resolve` (function, line 888) `void fx_grid_line_resolve(int start, int end, int ntracks, int *pos0, int *span)`
  - `fx_col_free_split` (function, line 930) `fx_status fx_col_free_split(double free_px, const int *grow, const int *mauto, size_t n,
        ...`
  - `FX_EPS` (macro, line 16) `#define FX_EPS`
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
  - `hl_font_stash` (struct, line 600)
  - `print_usage` (function, line 53) `static void print_usage(FILE *fp, const char *prog)`
  - `is_https_url` (function, line 81) `static int is_https_url(const char *s)`
  - `is_http_url` (function, line 85) `static int is_http_url(const char *s)`
  - `is_overlay_http` (function, line 90) `static int is_overlay_http(const char *s)`
  - `now_us` (function, line 145) `static uint64_t now_us(void)`
  - `timings_ensure_init` (function, line 151) `static void timings_ensure_init(void)`
  - `timings_enabled` (function, line 155) `static int timings_enabled(void)`
  - `timings_dump` (function, line 159) `static void timings_dump(void)`
  - `user_impersonate_enabled` (function, line 214) `static int user_impersonate_enabled(void)`
  - `read_file` (function, line 221) `static char *read_file(const char *path, size_t *out_len)`
  - `headless_load_hosts` (function, line 239) `static void headless_load_hosts(void)`
  - `apply_identity` (function, line 256) `static void apply_identity(sf_config *cfg)`
  - `apply_as_gui` (function, line 261) `static void apply_as_gui(const char *top_url, int flag_js, int flag_css, int flag_images)`
  - `is_blank_text` (function, line 299) `static int is_blank_text(const char *s)`
  - `print_doc` (function, line 312) `static void print_doc(const rd_doc *doc)`
  - `print_console` (function, line 405) `static void print_console(const fb_buffer *log)`
  - `print_dom` (function, line 422) `static void print_dom(const rd_doc *doc)`
  - `print_dom_css` (function, line 437) `static void print_dom_css(const rd_doc *doc)`
  - `headless_fetch` (function, line 461) `static int headless_fetch(void *ctx, const char *method, const char *url,
                       ...`
  - `foldback_cookies` (function, line 539) `static void foldback_cookies(const char *url, const char *jar)`
  - `print_css_drops` (function, line 563) `static void print_css_drops(const char *html, size_t len)`
  - `hl_font_stash_free` (function, line 608) `static void hl_font_stash_free(hl_font_stash *s)`
  - `hl_css_sink` (function, line 621) `static void hl_css_sink(void *vctx, const char *url,
                        const char *body, si...`
  - `hl_font_fetch` (function, line 658) `static int hl_font_fetch(void *vctx, const char *url,
                         int *out_status, c...`
  - `render_page` (function, line 667) `static int render_page(const char *html, size_t len, const char *top_url,
                       ...`
  - `first` (function, line 745) `* always cleared first (fetch_and_render may paint several pages per
     * process). A NULL top_...`
  - `sf_reason` (function, line 936) `static const char *sf_reason(sf_status ss)`
  - `fetch_and_render_one` (function, line 955) `static int fetch_and_render_one(const char *url, char **out_nav)`
  - `elsewhere` (function, line 1018) `* page whose script immediately forwards elsewhere (e.g. a search engine's
 * JS-capability inter...`
  - `parent` (function, line 1044) `* gated by the parent (ln_resolve: a local target stays under the document's
 * directory, a remo...`
  - `run_headless` (function, line 1081) `static int run_headless(const char *target)`
  - `video_fetch_with_fallback` (function, line 1118) `static sf_status video_fetch_with_fallback(const char *url, sf_config *cfg,
                     ...`
  - `run_dump_video` (function, line 1229) `static int run_dump_video(const char *url)`
  - `main` (function, line 1248) `int main(int argc, char **argv)`
  - `gets` (function, line 457) `* gate a click gets (https-only, no downgrade, no foreign scheme), so relative * subresources work. Realm-routed...`
  - `pool` (function, line 731) `* the pool (unconsumed results freed, in-flight fetches joined). */ tab_set_fetcher(t, headless_fetch, (void...`
  - `only` (function, line 813) `* styling for the local render only (no network). --images enables image loading * AND rendering, including remote...`
  - `BLOCKED` (function, line 983) `* is BLOCKED (fail closed), never leaked over the clearnet. */ nr_route route = nr_route_for(url, global_net);`
  - `_POSIX_C_SOURCE` (macro, line 9) `#define _POSIX_C_SOURCE`
  - `_DEFAULT_SOURCE` (macro, line 10) `#define _DEFAULT_SOURCE`
  - `EXIT_OK` (macro, line 49) `#define EXIT_OK`
  - `EXIT_ERROR` (macro, line 50) `#define EXIT_ERROR`
  - `EXIT_USAGE` (macro, line 51) `#define EXIT_USAGE`
  - `CSS_DROPS_REPORT_MAX` (macro, line 170) `#define CSS_DROPS_REPORT_MAX`
  - `HL_FONT_MAX_SHEETS` (macro, line 597) `#define HL_FONT_MAX_SHEETS`
  - `HL_FONT_MAX_BYTES` (macro, line 598) `#define HL_FONT_MAX_BYTES`
  - `HL_JS_NAV_MAX` (macro, line 951) `#define HL_JS_NAV_MAX`
- Depends on: `include/dom_debug.h`, `include/freebug.h`, `include/hls.h`, `include/host_conf.h`, `include/hostblock.h`, `include/html_parse.h`, `include/identity.h`, `include/js_policy.h`, `include/link_nav.h`, `include/media_decoder.h`, `include/net_realm.h`, `include/page_view.h`, `include/perf_trace.h`, `include/prefetch.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/tab.h`, `include/text_shape.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/webcaps.h`, `include/webfont.h`, `include/webfont_load.h`, `include/wl_display.h`

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

## src/host_conf.c
- Doc: read_conf: add_dir(out, env); if (home != NULL && home[0] != '\0') { char user[HCF_PATH_MAX]...
- Layer: utility
- Language: c
- Symbols:
  - `add_dir` (function, line 10) `static void add_dir(hcf_dirs *out, const char *path)`
  - `hcf_search_dirs` (function, line 20) `void hcf_search_dirs(const char *env, const char *home, hcf_dirs *out)`
  - `hcf_search_dirs_from_env` (function, line 32) `void hcf_search_dirs_from_env(hcf_dirs *out)`
  - `read_conf` (function, line 37) `static char *read_conf(const char *dir, const char *name)`
  - `load_into` (function, line 58) `static void load_into(hb_set *s, const char *dir, const char *name, hb_list list)`
  - `hcf_load_filter` (function, line 65) `hb_set *hcf_load_filter(const hcf_dirs *dirs)`
  - `hcf_load_allowlist` (function, line 76) `hb_set *hcf_load_allowlist(const hcf_dirs *dirs, const char *fname)`
  - `HCF_USER_SUBDIR` (macro, line 7) `#define HCF_USER_SUBDIR`
  - `HCF_REPO_DIR` (macro, line 8) `#define HCF_REPO_DIR`
- Depends on: `include/host_conf.h`

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

## src/identity.c
- Doc: tag_valid: size_t n = strlen(ua); if (n >= IDN_UA_MAX) return -1; int printable = 0; for (size_t...
- Layer: utility
- Language: c
- Symbols:
  - `is_alpha` (function, line 20) `static int is_alpha(char c)`
  - `is_alnum` (function, line 21) `static int is_alnum(char c)`
  - `idn_defaults` (function, line 23) `void idn_defaults(idn_config *c)`
  - `idn_is_default` (function, line 29) `int idn_is_default(const idn_config *c)`
  - `idn_set_user_agent` (function, line 34) `int idn_set_user_agent(idn_config *c, const char *ua)`
  - `tag_valid` (function, line 50) `static int tag_valid(const char *s, size_t n)`
  - `idn_set_languages` (function, line 63) `int idn_set_languages(idn_config *c, const char *list)`
  - `idn_set_geo` (function, line 91) `int idn_set_geo(idn_config *c, double lat, double lon, double accuracy_m)`
  - `idn_clear_geo` (function, line 103) `void idn_clear_geo(idn_config *c)`
  - `idn_user_agent` (function, line 109) `const char *idn_user_agent(const idn_config *c)`
  - `idn_accept_language` (function, line 113) `size_t idn_accept_language(const idn_config *c, char *out, size_t cap)`
  - `idn_primary_language` (function, line 143) `size_t idn_primary_language(const idn_config *c, char *out, size_t cap)`
  - `hexval` (function, line 157) `static int hexval(int ch)`
  - `pct_decode` (function, line 166) `static long pct_decode(const char *s, size_t n, char *out, size_t cap, int plus)`
  - `append` (function, line 186) `static int append(char *buf, size_t *n, size_t cap, const char *fmt, ...)`
  - `append_pct` (function, line 197) `static int append_pct(char *buf, size_t *n, size_t cap, const char *s)`
  - `idn_serialize` (function, line 206) `size_t idn_serialize(const idn_config *c, char *out, size_t cap)`
  - `parse_geo` (function, line 223) `static int parse_geo(const char *s, double *lat, double *lon, double *acc)`
  - `idn_parse` (function, line 236) `void idn_parse(idn_config *c, const char *text)`
  - `parse_number` (function, line 268) `static int parse_number(const char *s, double *out)`
  - `idn_apply_query` (function, line 275) `unsigned idn_apply_query(idn_config *c, const char *query)`
  - `esc_append` (function, line 346) `static int esc_append(char *buf, size_t *n, size_t cap, const char *s)`
  - `idn_render_page` (function, line 362) `size_t idn_render_page(const idn_config *c, char *out, size_t cap)`
  - `_GNU_SOURCE` (macro, line 7) `#define _GNU_SOURCE`
  - `IDN_QUERY_FIELD_MAX` (macro, line 18) `#define IDN_QUERY_FIELD_MAX`
- Depends on: `include/anti_fp.h`, `include/identity.h`

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

## src/js_custom_elements.c
- Layer: utility
- Language: c
- Symbols:
  - `jdce_install` (function, line 179) `int jdce_install(JSContext *ctx)`
- Depends on: `src/js_custom_elements.h`

## src/js_custom_elements.h
- Doc: Private to js_dom.c: installs Custom Elements v1 (spec/js_custom_elements.md) on top of the...
- Layer: utility
- Language: h
- Symbols:
  - `jdce_install` (function, line 9) `int jdce_install(JSContext *ctx);`
  - `FREEDOM_JS_CUSTOM_ELEMENTS_H` (macro, line 2) `#define FREEDOM_JS_CUSTOM_ELEMENTS_H`
- Imported by: `src/js_custom_elements.c`, `src/js_dom.c`


Next: [KB_src_p5.md](KB_src_p5.md)
