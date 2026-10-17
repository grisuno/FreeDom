# API (page 7 of 10)
Previous: [API_p6.md](API_p6.md)

## src/freebug.c
Depends on: `include/freebug.h`
- `whole` (function) `src/freebug.c:5` `* FB_MAX_TOTAL_BYTES is dropped whole (overflow flag raised, prior entries kept);`
- `fb_buffer_init` (function) `src/freebug.c:15` `void fb_buffer_init(fb_buffer *b)`
- `fb_buffer_push` (function) `src/freebug.c:19` `int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)`
- `fb_buffer_push_loc` (function) `src/freebug.c:23` `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len,
                   ...`
- `fb_buffer_reset` (function) `src/freebug.c:78` `void fb_buffer_reset(fb_buffer *b)`
- `fb_buffer_free` (function) `src/freebug.c:91` `void fb_buffer_free(fb_buffer *b)`
- `fb_buffer_count` (function) `src/freebug.c:101` `size_t fb_buffer_count(const fb_buffer *b)`
- `fb_buffer_at` (function) `src/freebug.c:105` `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)`
- `fb_level_name` (function) `src/freebug.c:110` `const char *fb_level_name(int level)`

## src/freedom.c
Depends on: `include/dom_debug.h`, `include/freebug.h`, `include/hls.h`, `include/hostblock.h`, `include/html_parse.h`, `include/js_policy.h`, `include/link_nav.h`, `include/media_decoder.h`, `include/net_realm.h`, `include/page_view.h`, `include/perf_trace.h`, `include/prefetch.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/tab.h`, `include/text_shape.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/webcaps.h`, `include/webfont.h`, `include/webfont_load.h`
- `print_usage` (function) `src/freedom.c:50` `static void print_usage(FILE *fp, const char *prog)`
- `is_https_url` (function) `src/freedom.c:76` `static int is_https_url(const char *s)`
- `is_http_url` (function) `src/freedom.c:80` `static int is_http_url(const char *s)`
- `is_overlay_http` (function) `src/freedom.c:85` `static int is_overlay_http(const char *s)` -- fprintf(fp, "  --dump-video-url: headless, print the first detected video source URL to stdout (no truncation)\n")...
- `now_us` (function) `src/freedom.c:139` `static uint64_t now_us(void)`
- `timings_ensure_init` (function) `src/freedom.c:145` `static void timings_ensure_init(void)`
- `timings_enabled` (function) `src/freedom.c:149` `static int timings_enabled(void)`
- `timings_dump` (function) `src/freedom.c:153` `static void timings_dump(void)`
- `user_impersonate_enabled` (function) `src/freedom.c:201` `static int user_impersonate_enabled(void)`
- `read_file` (function) `src/freedom.c:208` `static char *read_file(const char *path, size_t *out_len)` -- User opt-in for TLS-impersonation blend: --impersonate or FREEDOM_IMPERSONATE=1.
- `headless_load_hosts` (function) `src/freedom.c:226` `static void headless_load_hosts(void)`
- `is_blank_text` (function) `src/freedom.c:256` `static int is_blank_text(const char *s)` -- No impersonate.conf: third signal is the user flag (--impersonate / * FREEDOM_IMPERSONATE=1). impersonate.conf on...
- `print_doc` (function) `src/freedom.c:269` `static void print_doc(const rd_doc *doc)` -- Writes the render document as deterministic, flowing plain text for a terminal and for an AI agent (content as data...
- `print_console` (function) `src/freedom.c:362` `static void print_console(const fb_buffer *log)` -- Prints the captured Freebug console (the developer-visible JS transcript) to stdout, one entry per line, prefixed...
- `print_dom` (function) `src/freedom.c:379` `static void print_dom(const rd_doc *doc)` -- Prints the paint-ready render tree (dom_debug) to stdout.
- `print_dom_css` (function) `src/freedom.c:394` `static void print_dom_css(const rd_doc *doc)` -- Prints the CSS property inspector (dd_format_css) to stdout.
- `gets` (function) `src/freedom.c:414` `* gate a click gets (https-only, no downgrade, no foreign scheme), so relative * subresources work. Realm-routed...`
- `headless_fetch` (function) `src/freedom.c:418` `static int headless_fetch(void *ctx, const char *method, const char *url,
                       ...` -- tab_fetch_fn for the headless renderer: a policy-checked subresource fetch for page XHR/fetch and external <script...
- `foldback_cookies` (function) `src/freedom.c:480` `static void foldback_cookies(const char *url, const char *jar)` -- Folds a page's document.cookie jar ("a=1; b=2") back into the ephemeral network * jar, one pair at a time, so JS-set...
- `print_css_drops` (function) `src/freedom.c:504` `static void print_css_drops(const char *html, size_t len)` -- Prints the author-CSS drop report for `html`, sorted by occurrence count.
- `hl_font_stash_free` (function) `src/freedom.c:549` `static void hl_font_stash_free(hl_font_stash *s)`
- `hl_css_sink` (function) `src/freedom.c:562` `static void hl_css_sink(void *vctx, const char *url,
                        const char *body, si...` -- tab_css_sink_fn for headless: retains served 2xx CSS bodies (serial and pool paths alike) with an absolute https...
- `hl_font_fetch` (function) `src/freedom.c:599` `static int hl_font_fetch(void *vctx, const char *url,
                         int *out_status, c...` -- wf_fetch_fn around the headless policy gate (font bytes download like any * other subresource of this page). data...
- `render_page` (function) `src/freedom.c:608` `static int render_page(const char *html, size_t len, const char *top_url,
                       ...`
- `pool` (function) `src/freedom.c:669` `* the pool (unconsumed results freed, in-flight fetches joined). */ tab_set_fetcher(t, headless_fetch, (void...`
- `first` (function) `src/freedom.c:683` `* always cleared first (fetch_and_render may paint several pages per
     * process). A NULL top_...`
- `only` (function) `src/freedom.c:740` `* styling for the local render only (no network). --images enables image loading * AND rendering, including remote...`
- `sf_reason` (function) `src/freedom.c:852` `static const char *sf_reason(sf_status ss)`
- `fetch_and_render_one` (function) `src/freedom.c:871` `static int fetch_and_render_one(const char *url, char **out_nav)` -- Fetches one url with secure_fetch and renders the result.
- `BLOCKED` (function) `src/freedom.c:897` `* is BLOCKED (fail closed), never leaked over the clearnet. */ nr_route route = nr_route_for(url, global_net);`
- `elsewhere` (function) `src/freedom.c:932` `* page whose script immediately forwards elsewhere (e.g. a search engine's
 * JS-capability inter...`
- `parent` (function) `src/freedom.c:958` `* gated by the parent (ln_resolve: a local target stays under the document's
 * directory, a remo...`
- `run_headless` (function) `src/freedom.c:995` `static int run_headless(const char *target)`
- `video_fetch_with_fallback` (function) `src/freedom.c:1031` `static sf_status video_fetch_with_fallback(const char *url, sf_config *cfg,
                     ...` -- Fetches a URL with TLS fallbacks (PQ-hybrid -> classical KE -> allowlisted insecure), same chain as...
- `run_dump_video` (function) `src/freedom.c:1142` `static int run_dump_video(const char *url)` -- -dump-video handler: fetches a video URL and writes the stream to a file * or stdout.
- `main` (function) `src/freedom.c:1161` `int main(int argc, char **argv)`

## src/hls.c
Depends on: `include/hls.h`
- `last_char` (function) `src/hls.c:38` `static const char *last_char(const char *s, size_t n, int c)` -- Finds the last occurrence of character `c` in `s` (length `n`). * Returns NULL if not found.
- `name` (function) `src/hls.c:46` `* attr is the attribute name (e.g. "BANDWIDTH=");`
- `parse_attr_long` (function) `src/hls.c:48` `static int parse_attr_long(const char *attrs, const char *end,
                           const c...` -- Extracts a named attribute value from an #EXT-X-STREAM-INF attribute string. attr is the attribute name (e.g....
- `parse_attr_resolution` (function) `src/hls.c:62` `static void parse_attr_resolution(const char *attrs, const char *end,
                           ...` -- static int parse_attr_long(const char *attrs, const char *end, const char *attr, long *val) { size_t alen =...
- `hls_parse` (function) `src/hls.c:80` `hls_status hls_parse(const char *text, size_t len, hls_playlist **out)`
- `hls_select_variant` (function) `src/hls.c:202` `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h)`
- `hls_resolve_url` (function) `src/hls.c:223` `size_t hls_resolve_url(const char *base_url, const char *segment_url,
                       char...`
- `hls_playlist_free` (function) `src/hls.c:253` `void hls_playlist_free(hls_playlist *pl)`

## src/hostblock.c
Depends on: `include/hostblock.h`, `include/util.h`
- `table_probe` (function) `src/hostblock.c:38` `static size_t table_probe(const hb_table *t, const char *key, size_t klen)` -- Finds the slot for key (length klen) in t, which must have a free slot.
- `table_grow` (function) `src/hostblock.c:49` `static int table_grow(hb_table *t, size_t newcap)` -- Finds the slot for key (length klen) in t, which must have a free slot.
- `table_insert` (function) `src/hostblock.c:71` `static int table_insert(hb_table *t, const char *key, size_t klen)` -- Inserts key (length klen) into t, deduping.
- `table_contains` (function) `src/hostblock.c:92` `static int table_contains(const hb_table *t, const char *key)`
- `table_free` (function) `src/hostblock.c:98` `static void table_free(hb_table *t)`
- `lower` (function) `src/hostblock.c:107` `static char lower(char c)`
- `is_ip_token` (function) `src/hostblock.c:113` `static int is_ip_token(const char *s, size_t n)` -- A token made only of digits, '.' and ':' is an IP literal (v4 or v6), not a * domain.
- `is_domain_char` (function) `src/hostblock.c:122` `static int is_domain_char(char c)` -- A token made only of digits, '.' and ':' is an IP literal (v4 or v6), not a * domain.
- `hb_new` (function) `src/hostblock.c:144` `hb_set *hb_new(void)`
- `hb_free` (function) `src/hostblock.c:149` `void hb_free(hb_set *s)`
- `hb_load` (function) `src/hostblock.c:156` `hb_status hb_load(hb_set *s, const char *text, hb_list list)`
- `hb_check` (function) `src/hostblock.c:193` `hb_decision hb_check(const hb_set *s, const char *host)`
- `hb_is_allowlisted` (function) `src/hostblock.c:218` `int hb_is_allowlisted(const hb_set *s, const char *host)`
- `hb_count` (function) `src/hostblock.c:238` `size_t hb_count(const hb_set *s, hb_list list)`

## src/hostedit.c
Depends on: `include/hostedit.h`
- `he_lower` (function) `src/hostedit.c:12` `static char he_lower(char c)`
- `is_label_char` (function) `src/hostedit.c:16` `static int is_label_char(char c)`
- `valid_host` (function) `src/hostedit.c:22` `static int valid_host(const char *host, size_t n)` -- #include "hostedit.h" #include <string.h> static char he_lower(char c) { return (c >= 'A' && c <= 'Z') ?
- `he_make_line` (function) `src/hostedit.c:41` `he_status he_make_line(const char *host, char *out, size_t cap)`
- `is_ip_token` (function) `src/hostedit.c:67` `static int is_ip_token(const char *ts, const char *te)` -- True if the token looks like an IPv4 dotted-quad / contains only digits and dots * (matches hostblock's is_ip_token...
- `he_scan` (function) `src/hostedit.c:80` `static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), void *ctx)` -- Visits each domain token (non-comment, non-IP) of a hosts-format text in document order, calling fn(ts, tl, ctx).
- `has_host_cb` (function) `src/hostedit.c:105` `static int has_host_cb(const char *ts, size_t tl, void *ctx)`
- `he_text_has_host` (function) `src/hostedit.c:109` `int he_text_has_host(const char *text, const char *host)`
- `contains_ci` (function) `src/hostedit.c:115` `static int contains_ci(const char *hs, size_t hl, const char *needle)` -- } return 0; } static int has_host_cb(const char *ts, size_t tl, void *ctx) { return token_eq_host(ts, ts + tl...
- `starts_with_ci` (function) `src/hostedit.c:128` `static int starts_with_ci(const char *hs, size_t hl, const char *pfx)`
- `suggest_cb` (function) `src/hostedit.c:144` `static int suggest_cb(const char *ts, size_t tl, void *vctx)`
- `he_suggest` (function) `src/hostedit.c:164` `int he_suggest(const char *text, const char *query,
               char results[][HE_MAX_HOST + 1...`

## src/html_parse.c
Depends on: `include/dom.h`, `include/html_parse.h`, `include/util.h`
- `dup_bytes` (function) `src/html_parse.c:27` `static char *dup_bytes(const lxb_char_t *src, size_t len)`
- `node_next` (function) `src/html_parse.c:37` `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` -- }; /* --- helpers --- static char *dup_bytes(const lxb_char_t *src, size_t len) { if (len == (size_t)-1) return...
- `attr_is_event_handler` (function) `src/html_parse.c:47` `static int attr_is_event_handler(const lxb_dom_attr_t *attr)`
- `node_is_script` (function) `src/html_parse.c:54` `static int node_is_script(const lxb_dom_node_t *node)`
- `strip_scripts` (function) `src/html_parse.c:60` `static void strip_scripts(lxb_html_document_t *document)`
- `type_is` (function) `src/html_parse.c:100` `static int type_is(const lxb_char_t *t, size_t len, const char *word)` -- HTML "the script element": type="module" (ASCII case-insensitive, whitespace * stripped) is an ES module; nothing...
- `type_is_module` (function) `src/html_parse.c:117` `static int type_is_module(const lxb_char_t *t, size_t len)`
- `script_classify` (function) `src/html_parse.c:121` `static int script_classify(const lxb_dom_node_t *n,
                           const lxb_char_t *...`
- `hp_extract_script_list` (function) `src/html_parse.c:164` `hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count)` -- Collects each executable <script> as its own entry, in document order: inline source for classic inline scripts, the...
- `lxb_dom_element_has_attribute` (function) `src/html_parse.c:230` `&& lxb_dom_element_has_attribute(sel, (const lxb_char_t *)"nomodule", 8);`
- `hp_free_scripts` (function) `src/html_parse.c:238` `void hp_free_scripts(hp_script *scripts, size_t count)`
- `attr_has_token_ci` (function) `src/html_parse.c:251` `static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle)` -- Whitespace-separated token test over a length-delimited attribute value, ASCII case-insensitive: rel="preload...
- `link_is_active_stylesheet` (function) `src/html_parse.c:272` `static int link_is_active_stylesheet(lxb_dom_element_t *el,
                                     ...` -- An applicable stylesheet <link>: rel token "stylesheet" and not "alternate"; a non-empty href; media absent/empty or...
- `hp_extract_stylesheet_hrefs` (function) `src/html_parse.c:294` `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count)`
- `hp_free_stylesheet_hrefs` (function) `src/html_parse.c:328` `void hp_free_stylesheet_hrefs(char **hrefs, size_t count)`
- `strip_event_handlers` (function) `src/html_parse.c:334` `static void strip_event_handlers(lxb_html_document_t *document)`
- `hp_config_default` (function) `src/html_parse.c:357` `hp_config hp_config_default(void)`
- `hp_validate_input` (function) `src/html_parse.c:365` `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg)`
- `hp_parse` (function) `src/html_parse.c:375` `hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out)`
- `hp_element_count` (function) `src/html_parse.c:409` `size_t hp_element_count(const hp_document *doc)`
- `hp_script_count` (function) `src/html_parse.c:419` `size_t hp_script_count(const hp_document *doc)`
- `hp_event_handler_count` (function) `src/html_parse.c:429` `size_t hp_event_handler_count(const hp_document *doc)`
- `hp_extract_text` (function) `src/html_parse.c:445` `char *hp_extract_text(const hp_document *doc, size_t *out_len)`
- `hp_get_title` (function) `src/html_parse.c:464` `char *hp_get_title(const hp_document *doc, size_t *out_len)`
- `hp_free` (function) `src/html_parse.c:479` `void hp_free(char *buf)`
- `hp_document_free` (function) `src/html_parse.c:483` `void hp_document_free(hp_document *doc)`
- `hp_document_root` (function) `src/html_parse.c:489` `const void *hp_document_root(const hp_document *doc)`

## src/image_decode.c
Depends on: `include/image_decode.h`
- `exit` (function) `src/image_decode.c:6` `* malformed stream fails closed instead of calling exit(). GIF uses an own pure-C * bounded LZW decoder (no giflib)....`
- `read_be32` (function) `src/image_decode.c:52` `static uint32_t read_be32(const uint8_t *p)`
- `img_png_dimensions` (function) `src/image_decode.c:57` `img_status img_png_dimensions(const uint8_t *bytes, size_t len,
                              uin...`
- `img_dimensions_ok` (function) `src/image_decode.c:68` `int img_dimensions_ok(uint32_t w, uint32_t h)`
- `img_fit` (function) `src/image_decode.c:76` `void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,
             double *out_w, do...`
- `premultiply` (function) `src/image_decode.c:90` `static void premultiply(uint8_t *data, size_t pixels)` -- void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h, double *out_w, double *out_h) { if (out_w == NULL...
- `img_decode_png` (function) `src/image_decode.c:102` `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)`
- `jpeg_error_longjmp` (function) `src/image_decode.c:158` `static void jpeg_error_longjmp(j_common_ptr cinfo)`
- `jpeg_silence` (function) `src/image_decode.c:164` `static void jpeg_silence(j_common_ptr cinfo)` -- libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG * fails closed (IMG_ERR_DECODE)...
- `img_decode_jpeg` (function) `src/image_decode.c:166` `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)`
- `gr_u8` (function) `src/image_decode.c:260` `static int gr_u8(gif_reader *r, uint8_t *out)`
- `gr_u16le` (function) `src/image_decode.c:266` `static int gr_u16le(gif_reader *r, uint16_t *out)`
- `gr_skip` (function) `src/image_decode.c:273` `static int gr_skip(gif_reader *r, size_t n)`
- `gr_skip_subblocks` (function) `src/image_decode.c:280` `static int gr_skip_subblocks(gif_reader *r)` -- static int gr_u16le(gif_reader *r, uint16_t *out) { if (r->pos + 2u > r->len) return 0; out =...
- `gb_next_code` (function) `src/image_decode.c:298` `static int gb_next_code(gif_bits *b, unsigned width, unsigned *out)`
- `gif_deinterlace_row` (function) `src/image_decode.c:319` `static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh)` -- } uint8_t byte; if (!gr_u8(b->r, &byte)) return 0; b->block_left--; b->acc |= (uint32_t)byte << b->nbits; b->nbits...
- `gif_put_pixel` (function) `src/image_decode.c:334` `static void gif_put_pixel(uint32_t *canvas, uint32_t cw, uint32_t ch,
                          u...` -- Writes one palette pixel into the canvas at frame-relative index i (clipped to * the canvas; transparent index ->...
- `img_decode_gif` (function) `src/image_decode.c:354` `img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out)`
- `img_decode_webp` (function) `src/image_decode.c:520` `img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out)`
- `img_decode` (function) `src/image_decode.c:553` `img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out)`
- `img_pixels_free` (function) `src/image_decode.c:566` `void img_pixels_free(img_pixels *p)`
- `img_format_name` (function) `src/image_decode.c:575` `const char *img_format_name(img_format f)`

## src/import_map.c
Depends on: `include/import_map.h`
- `ws` (function) `src/import_map.c:39` `static void ws(jr *r)`
- `eat` (function) `src/import_map.c:44` `static int eat(jr *r, char c)`
- `hex4` (function) `src/import_map.c:50` `static int hex4(const char *s, uint32_t *out)`
- `put_utf8` (function) `src/import_map.c:64` `static size_t put_utf8(char *o, uint32_t cp)`
- `str` (function) `src/import_map.c:78` `static char *str(jr *r)` -- A JSON string into an owned UTF-8 buffer (escapes decoded; a lone surrogate or a * raw control character is malformed).
- `skip` (function) `src/import_map.c:128` `static void skip(jr *r, int depth)` -- } n += put_utf8(o + n, cp);   /* <= the 6/12 escape bytes it replaces break; } default: goto fail; } } fail...
- `url_like` (function) `src/import_map.c:156` `static int url_like(const char *s)`
- `dup_s` (function) `src/import_map.c:168` `static char *dup_s(const char *s)`
- `clear` (function) `src/import_map.c:175` `static void clear(im_map *m)`
- `add` (function) `src/import_map.c:185` `static int add(im_map *m, int scope, const char *key, const char *addr, const char *doc_url,
    ...` -- if (d != NULL) memcpy(d, s, n + 1); return d; } static void clear(im_map *m) { for (size_t i = 0; i < m->n; ++i) {...
- `specifier_map` (function) `src/import_map.c:209` `static void specifier_map(jr *r, im_map *m, int scope, const char *doc_url,
                     ...` -- if (m->n == m->cap) { size_t nc = m->cap ? m->cap * 2 : 16; im_entry *g = (im_entry *)realloc(m->e, nc * sizeof *g)...
- `im_parse` (function) `src/import_map.c:225` `im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn resolve, void *ctx)`
- `match` (function) `src/import_map.c:272` `static int match(const im_map *m, int scope, const char *key, char *out, size_t outsz)` -- WHATWG "resolve an imports match" within one specifier map (scope).
- `im_resolve` (function) `src/import_map.c:301` `int im_resolve(const im_map *m, const char *base, const char *specifier,
               im_url_fn...`
- `im_count` (function) `src/import_map.c:339` `size_t im_count(const im_map *m)`
- `im_free` (function) `src/import_map.c:343` `void im_free(im_map *m)`

## src/interp.c
Depends on: `include/interp.h`
- `sample_bezier_x` (function) `src/interp.c:18` `static double sample_bezier_x(double t, double cx1, double cx2)`
- `sample_bezier_dx` (function) `src/interp.c:23` `static double sample_bezier_dx(double t, double cx1, double cx2)`
- `sample_bezier_y` (function) `src/interp.c:29` `static double sample_bezier_y(double t, double cy1, double cy2)`
- `solve_bezier_t` (function) `src/interp.c:35` `static double solve_bezier_t(double x, double cx1, double cx2)` -- } static double sample_bezier_dx(double t, double cx1, double cx2) { return 3.0 * cx1 * (1.0 - 4.0 * t + 3.0 * t *...
- `ip_ease` (function) `src/interp.c:55` `double ip_ease(double t, const ip_ease_fn *fn)`
- `ip_ease` (function) `src/interp.c:64` `case IP_EASE_EASE:
        return ip_ease(t, &(ip_ease_fn)`
- `ip_ease` (function) `src/interp.c:70` `case IP_EASE_EASE_IN:
        return ip_ease(t, &(ip_ease_fn)`
- `ip_ease` (function) `src/interp.c:76` `case IP_EASE_EASE_OUT:
        return ip_ease(t, &(ip_ease_fn)`
- `ip_ease` (function) `src/interp.c:82` `case IP_EASE_EASE_IN_OUT:
        return ip_ease(t, &(ip_ease_fn)`
- `ip_lerp` (function) `src/interp.c:134` `double ip_lerp(double a, double b, double t)`
- `ip_lerp_color` (function) `src/interp.c:139` `uint32_t ip_lerp_color(uint32_t c1, uint32_t c2, double t)`
- `ip_interp` (function) `src/interp.c:162` `double ip_interp(ip_val_kind kind, double a, double b, double t)`
- `ip_kf_interp` (function) `src/interp.c:175` `double ip_kf_interp(ip_val_kind val_kind, const ip_keyframe *kf,
                    int n_kf, do...`
- `ip_anim_init` (function) `src/interp.c:196` `void ip_anim_init(ip_anim *a, ip_val_kind vk, const ip_ease_fn *ease,
                  const ip_...`
- `anim_effective_dir_for` (function) `src/interp.c:222` `static int anim_effective_dir_for(const ip_anim *a, int iter)`
- `anim_effective_dir` (function) `src/interp.c:232` `static int anim_effective_dir(const ip_anim *a)`
- `ip_anim_tick` (function) `src/interp.c:236` `int ip_anim_tick(ip_anim *a, double dt_ms)`
- `ip_anim_current` (function) `src/interp.c:282` `double ip_anim_current(const ip_anim *a)`
- `ip_anim_done` (function) `src/interp.c:320` `int ip_anim_done(const ip_anim *a)`

## src/js_dom.c
Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `include/web_storage.h`, `src/js_dom_ext.h`, `src/js_dom_internal.h`, `src/js_location_internal.h`
- `jd_opaque_get` (function) `src/js_dom.c:27` `jd_opaque *jd_opaque_get(JSContext *ctx)`
- `jd_idx` (function) `src/js_dom.c:31` `dom_index *jd_idx(JSContext *ctx)`
- `jd_handle` (function) `src/js_dom.c:40` `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out)` -- Coerces a JS argument to a node handle.
- `jd_handle_or_null` (function) `src/js_dom.c:47` `JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h)`
- `m_node_count` (function) `src/js_dom.c:53` `static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,
                            in...`
- `m_get_element_by_id` (function) `src/js_dom.c:59` `static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val,
                       ...`
- `jd_query_list` (function) `src/js_dom.c:70` `static JSValue jd_query_list(JSContext *ctx, JSValueConst arg, int by_class)` -- return JS_NewInt64(ctx, (int64_t)dom_node_count(jd_idx(ctx))); } static JSValue m_get_element_by_id(JSContext *ctx...
- `m_get_by_tag` (function) `src/js_dom.c:100` `static JSValue m_get_by_tag(JSContext *ctx, JSValueConst this_val,
                            in...`
- `m_get_by_class` (function) `src/js_dom.c:106` `static JSValue m_get_by_class(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_tag_name` (function) `src/js_dom.c:112` `static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_get_attribute` (function) `src/js_dom.c:122` `static JSValue m_get_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
- `m_parent` (function) `src/js_dom.c:135` `static JSValue m_parent(JSContext *ctx, JSValueConst this_val,
                        int argc, ...`
- `m_first_child` (function) `src/js_dom.c:143` `static JSValue m_first_child(JSContext *ctx, JSValueConst this_val,
                             ...`
- `m_node_kind` (function) `src/js_dom.c:152` `static JSValue m_node_kind(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` -- dom_node_id h; if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION; return jd_handle_or_null(ctx...
- `m_child_node` (function) `src/js_dom.c:159` `static JSValue m_child_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
- `m_sibling_node` (function) `src/js_dom.c:166` `static JSValue m_sibling_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)`
- `m_create_char` (function) `src/js_dom.c:174` `static JSValue m_create_char(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` -- (void)this_val; (void)argc; dom_node_id h; if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION; return...
- `m_next_sibling` (function) `src/js_dom.c:188` `static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_precedes` (function) `src/js_dom.c:196` `static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_text_content` (function) `src/js_dom.c:207` `static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_set_text` (function) `src/js_dom.c:217` `static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_get_title` (function) `src/js_dom.c:231` `static JSValue m_get_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
- `m_set_title` (function) `src/js_dom.c:239` `static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
- `m_create_element` (function) `src/js_dom.c:252` `static JSValue m_create_element(JSContext *ctx, JSValueConst this_val,
                          ...`
- `m_append_child` (function) `src/js_dom.c:264` `static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_move_children` (function) `src/js_dom.c:275` `static JSValue m_move_children(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` -- dom.moveChildren(src, parent, where, ref|null): every child node of src (text * included) into parent at where (0...
- `m_clone_node` (function) `src/js_dom.c:289` `static JSValue m_clone_node(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` -- static JSValue m_move_children(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {...
- `m_insert_before` (function) `src/js_dom.c:299` `static JSValue m_insert_before(JSContext *ctx, JSValueConst this_val,
                           ...` -- return JS_NewBool(ctx, dom_move_children(jd_idx(ctx), src, parent, (dom_place)where, ref) == DOM_OK); } /*...
- `m_remove_child` (function) `src/js_dom.c:311` `static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_set_attribute` (function) `src/js_dom.c:320` `static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
- `m_remove_attribute` (function) `src/js_dom.c:336` `static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,
                        ...`
- `m_set_inner_html` (function) `src/js_dom.c:348` `static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...`
- `m_get_inner_html` (function) `src/js_dom.c:364` `static JSValue m_get_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...` -- innerHTML getter (2026-07-11): serializes the node's children (bounded in dom.c; * over-cap or invalid handle yields...
- `m_rect` (function) `src/js_dom.c:396` `static JSValue m_rect(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` -- dom.rect(h): [x, y, w, h] of h in document coordinates from the installed * layout geometry, or null (no table, or...
- `m_query_selector` (function) `src/js_dom.c:437` `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,
                          ...` -- return a; } /* --- install --- typedef struct jd_method { const char *name; JSCFunction *fn; int          nargs; }...
- `m_query_selector_all` (function) `src/js_dom.c:450` `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,
                      ...` -- /* dom.querySelector(root, sel): root is a handle or -1 for document scope. static JSValue...
- `m_matches` (function) `src/js_dom.c:479` `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,
                         int argc...`
- `m_closest` (function) `src/js_dom.c:491` `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,
                         int argc...`
- `m_attr_names` (function) `src/js_dom.c:503` `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,
                            in...`
- `table` (function) `src/js_dom.c:571` `* a table (dom.viewport() non-null);`
- `attrNames` (function) `src/js_dom.c:610` `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so
     * a missing '...`
- `scripts` (function) `src/js_dom.c:768` `* player scripts (canPlayType feature-detection, play/pause, muted/loop * reflection, buffered ranges) run without...`
- `enough` (function) `src/js_dom.c:931` `* enough (cloneNode/lastChild/removeChild/insertBefore) that library feature * detection does not throw: jQuery...`
- `ms` (function) `src/js_dom.c:1067` `* due is the remaining virtual ms (the trusted parent advances the clock via * OP_TICK -> __tickTimers(elapsed);`
- `empty` (function) `src/js_dom.c:1215` `* inert: DOM interface constructors are empty (instanceof yields false, harmless);`
- `geometry` (function) `src/js_dom.c:1217` `* constant geometry (zero real leak);`
- `size` (function) `src/js_dom.c:1220` `* the viewport reads a fixed normalized size (matches the 1920 width * anti_fp uses for @media, not the real window);`
- `js_env` (function) `src/js_dom.c:1223` `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the
 * document shim (uses...`
- `jd_install` (function) `src/js_dom.c:1775` `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)`
- `fails` (function) `src/js_dom.c:1852` `* cap is reached or an allocation fails (caller stops), else 0. */
static int cb_append(char **bu...`
- `jd_install_console` (function) `src/js_dom.c:1966` `jd_status jd_install_console(js_context *ctx, fb_buffer *log)`
- `jd_set_cookies` (function) `src/js_dom.c:2003` `jd_status jd_set_cookies(js_context *ctx, const char *cookies)`
- `jd_get_cookies` (function) `src/js_dom.c:2023` `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)`
- `jd_set_geometry` (function) `src/js_dom.c:2046` `jd_status jd_set_geometry(js_context *ctx, const jg_table *geom)`

## src/js_dom_ext.c
Depends on: `src/js_dom_ext.h`
- `identity` (function) `src/js_dom_ext.c:96` `* identity (host/shadowRoot/mode preserved) but every mutation ALSO mirrors * into the host's light DOM via dom.*...`
- `run` (function) `src/js_dom_ext.c:366` `static int run(JSContext *ctx, const char *src, size_t len, const char *name)`
- `jdx_install` (function) `src/js_dom_ext.c:374` `int jdx_install(JSContext *ctx)`

## src/js_dom_ext.h
Imported by: `src/js_dom.c`, `src/js_dom_ext.c`
- `jdx_install` (function) `src/js_dom_ext.h:10` `int jdx_install(JSContext *ctx);`

## src/js_dom_internal.h
Depends on: `include/dom.h`, `include/js_dom.h`
Imported by: `src/js_dom.c`, `src/js_embed.c`, `src/js_events.c`, `src/js_fetch.c`
- `jd_opaque_get` (function) `src/js_dom_internal.h:11` `jd_opaque *jd_opaque_get(JSContext *ctx);`
- `jd_idx` (function) `src/js_dom_internal.h:12` `dom_index *jd_idx(JSContext *ctx);`
- `jd_handle` (function) `src/js_dom_internal.h:14` `int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out);` -- Private to the js_dom family (js_dom.c, js_fetch.c, js_events.c, js_embed.c): * the context accessors every native...

## src/js_embed.c
Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`
- `try_create_iframe_from_script` (function) `src/js_embed.c:86` `static int try_create_iframe_from_script(dom_index *idx,
                                        ...` -- Scans an inline script body for `video[N]` or `video_data` assignment and extracts the first usable iframe src.
- `jd_video_from_scripts` (function) `src/js_embed.c:203` `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,
                   ...`
- `jd_inject_video_shim` (function) `src/js_embed.c:242` `jd_status jd_inject_video_shim(js_context *ctx)`
- `scan_video_url` (function) `src/js_embed.c:256` `static int scan_video_url(const char *body, size_t blen,
                           char *out, si...` -- Scans a body buffer for `.m3u8` (HLS) or `.mp4` (progressive) video URLs.
- `jd_process_iframes` (function) `src/js_embed.c:294` `void jd_process_iframes(js_context *ctx, dom_index *idx,
                        jd_fetch_fn fn, ...`

## src/js_env.c
Depends on: `include/anti_fp.h`, `include/js_env.h`, `include/js_sandbox.h`
- `primitives` (function) `src/js_env.c:6` `* the pure anti_fp primitives (one audited source of normalized constants);`
- `wall_clock_ms` (function) `src/js_env.c:35` `static uint64_t wall_clock_ms(void)`
- `monotonic_ms` (function) `src/js_env.c:41` `static double monotonic_ms(void)`
- `m_date_now` (function) `src/js_env.c:49` `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_perf_now` (function) `src/js_env.c:57` `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,
                          int ar...` -- performance.now: coarsened elapsed since the origin bound at install time, so * it never leaks the host uptime.
- `m_empty_array` (function) `src/js_env.c:77` `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,
                             ...`
- `m_get_random_values` (function) `src/js_env.c:85` `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,
                       ...`
- `m_random_uuid` (function) `src/js_env.c:125` `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,
                             ...`
- `m_subtle_null` (function) `src/js_env.c:142` `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,
                             ...`
- `def_val` (function) `src/js_env.c:153` `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)` -- Always takes ownership of v: JS_DefinePropertyValueStr consumes it (freeing it even when the define fails).
- `def_str` (function) `src/js_env.c:159` `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)`
- `def_int` (function) `src/js_env.c:163` `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)`
- `def_fn` (function) `src/js_env.c:167` `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,
                  JSCFuncti...`
- `build_languages` (function) `src/js_env.c:174` `static JSValue build_languages(JSContext *ctx)` -- navigator.languages: a sealed array built by splitting fp_accept_language() * (e.g. "en-US,en") on commas.
- `build_navigator` (function) `src/js_env.c:198` `static int build_navigator(JSContext *ctx, JSValueConst global)`
- `methods` (function) `src/js_env.c:201` `* capability methods (sendBeacon, spec/js_dom.md 7h) without touching any * fingerprintable field. An untrusted...`
- `build_screen` (function) `src/js_env.c:302` `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)`
- `build_crypto` (function) `src/js_env.c:346` `static int build_crypto(JSContext *ctx, JSValueConst global)`
- `build_perf_timing` (function) `src/js_env.c:374` `static int build_perf_timing(JSContext *ctx, JSValueConst perf)`
- `build_perf_navigation` (function) `src/js_env.c:388` `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)`
- `build_performance` (function) `src/js_env.c:400` `static int build_performance(JSContext *ctx, JSValueConst global)`
- `override_date_now` (function) `src/js_env.c:432` `static int override_date_now(JSContext *ctx, JSValueConst global)` -- Replaces the built-in Date.now with the coarsened version, non-writable and * non-configurable so a script cannot...
- `make_readback` (function) `src/js_env.c:476` `static JSValue make_readback(JSContext *ctx, uint64_t key)`
- `build_readback_obj` (function) `src/js_env.c:484` `static int build_readback_obj(JSContext *ctx, JSValueConst global,
                              ...`
- `je_install` (function) `src/js_env.c:497` `je_status je_install(js_context *ctx, int screen_w, int screen_h)`
- `je_install_canvas` (function) `src/js_env.c:516` `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)`

## src/js_events.c
Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`
- `jd_click_state_new` (function) `src/js_events.c:29` `jd_click_state *jd_click_state_new(void)`
- `jd_click_state_free` (function) `src/js_events.c:34` `void jd_click_state_free(jd_click_state *s)`
- `jd_install_events` (function) `src/js_events.c:38` `jd_status jd_install_events(js_context *ctx, jd_click_state *state)`
- `jd_eval_default_action` (function) `src/js_events.c:52` `static int jd_eval_default_action(JSContext *jsctx, const char *src, size_t n,
                  ...` -- Runs one engine event-dispatch expression and maps its result to the C contract: 1 = default action proceeds, 0 = a...
- `jd_fire_click` (function) `src/js_events.c:66` `int jd_fire_click(js_context *ctx, dom_node_id node_id)`
- `jd_fire_submit` (function) `src/js_events.c:78` `int jd_fire_submit(js_context *ctx, dom_node_id form_node_id)` -- Fires the submit event for form_node_id.
- `jd_escape_js_str` (function) `src/js_events.c:91` `static size_t jd_escape_js_str(const char *src, char *dst, size_t dstsz)` -- Escapes a string for safe interpolation into JS double-quoted string literal: replaces backslash with \\ and...
- `jd_fire_mouse_event` (function) `src/js_events.c:163` `int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,
                        const char ...`

## src/js_fetch.c
Depends on: `include/dom.h`, `include/freebug.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_sandbox.h`, `src/js_dom_internal.h`
- `jd_pack_ptr` (function) `src/js_fetch.c:28` `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)` -- Carry the host fetch fn + its ctx as a function's closure data, each split into 32-bit halves (no assumption about...
- `jd_unpack_ptr` (function) `src/js_fetch.c:33` `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)`
- `m_host_fetch` (function) `src/js_fetch.c:46` `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,
                            in...` -- __hostFetch(method, url, body) -> { status, body, contentType }.
- `send` (function) `src/js_fetch.c:92` `* callbacks fire right after send();`
- `task` (function) `src/js_fetch.c:179` `* current task (the page never waits on it);`
- `jd_install_xhr` (function) `src/js_fetch.c:197` `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)`

## src/js_geom.c
Depends on: `include/js_geom.h`
- `jg_init` (function) `src/js_geom.c:17` `void jg_init(jg_table *t)`
- `jg_free` (function) `src/js_geom.c:21` `void jg_free(jg_table *t)`
- `clamp_coord` (function) `src/js_geom.c:27` `static int32_t clamp_coord(double v, double lo)`
- `grow` (function) `src/js_geom.c:33` `static int grow(jg_table *t)`
- `push` (function) `src/js_geom.c:45` `static int push(jg_table *t, dom_node_id node, int32_t x, int32_t y, int32_t w, int32_t h)`
- `jg_add` (function) `src/js_geom.c:52` `int jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h)`
- `unite` (function) `src/js_geom.c:63` `static int unite(jg_rect *a, const jg_rect *b)` -- Bounding box of a and b into a; returns 1 if a changed.
- `cmp_node` (function) `src/js_geom.c:78` `static int cmp_node(const void *pa, const void *pb)`
- `jg_finish` (function) `src/js_geom.c:83` `int jg_finish(jg_table *t)`
- `jg_find` (function) `src/js_geom.c:96` `const jg_rect *jg_find(const jg_table *t, dom_node_id node)`
- `slot_of` (function) `src/js_geom.c:102` `static uint32_t slot_of(dom_node_id n)`
- `index_of` (function) `src/js_geom.c:109` `static size_t index_of(jg_table *t, uint32_t *slots, dom_node_id node, const jg_rect *seed,
     ...` -- Index of node in t->r via the local hash, inserting an empty-at-rect entry * (a copy of seed) when absent.
- `jg_aggregate` (function) `src/js_geom.c:124` `int jg_aggregate(jg_table *t, dom_node_id (*parent)(void *ctx, dom_node_id node), void *ctx)`
- `jg_wire_len` (function) `src/js_geom.c:163` `size_t jg_wire_len(const jg_table *t)`
- `jg_encode` (function) `src/js_geom.c:167` `int jg_encode(const jg_table *t, int32_t *out, size_t cap)`
- `in_range` (function) `src/js_geom.c:182` `static int in_range(int32_t v, int32_t lo)`
- `jg_decode` (function) `src/js_geom.c:186` `int jg_decode(const int32_t *in, size_t n, jg_table *out)`
- `fnv` (function) `src/js_geom.c:212` `static uint64_t fnv(uint64_t h, int32_t v)`
- `jg_hash` (function) `src/js_geom.c:221` `uint64_t jg_hash(const jg_table *t)`

## src/js_location.c
Depends on: `include/js_dom.h`, `include/url.h`, `src/js_location_internal.h`
- `jd_lp_set` (function) `src/js_location.c:24` `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,
                      const ...` -- Defines a string property on the __locParts data object from a (ptr,len) span. * The span is copied into an engine...
- `jl_m_hist_target` (function) `src/js_location.c:35` `JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)` -- dom.histTarget(base, ref): the same-origin target of history.pushState/replaceState (url_history_target) as a...
- `jd_set_location` (function) `src/js_location.c:139` `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)`
- `jd_take_nav_request` (function) `src/js_location.c:173` `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)`
- `jd_take_history` (function) `src/js_location.c:219` `char *jd_take_history(js_context *ctx, int *go)`
- `jd_pop_state` (function) `src/js_location.c:250` `int jd_pop_state(js_context *ctx, int index)`

## src/js_location_internal.h
Imported by: `src/js_dom.c`, `src/js_location.c`
- `header` (function) `src/js_location_internal.h:6` `* stay out of every public header (include/ never sees quickjs.h). */ #include "quickjs.h" JSValue...`

## src/js_policy.c
Depends on: `include/js_policy.h`
- `eq_ci` (function) `src/js_policy.c:12` `static int eq_ci(const char *a, const char *b)` -- js_policy — implementation: pure per-host JavaScript policy decision.
- `jsp_enabled` (function) `src/js_policy.c:22` `bool jsp_enabled(jsp_mode mode, int host_allowlisted)`
- `jsp_trusted` (function) `src/js_policy.c:31` `bool jsp_trusted(bool js_enabled, int host_allowlisted)`
- `jsp_present_trusted` (function) `src/js_policy.c:35` `bool jsp_present_trusted(int host_allowlisted)`
- `jsp_mode_from_str` (function) `src/js_policy.c:39` `jsp_mode jsp_mode_from_str(const char *s)`
- `jsp_mode_str` (function) `src/js_policy.c:51` `const char *jsp_mode_str(jsp_mode mode)`

## src/js_sandbox.c
Depends on: `include/js_sandbox.h`
- `jm_malloc` (function) `src/js_sandbox.c:55` `static void *jm_malloc(void *opaque, size_t size)`
- `jm_calloc` (function) `src/js_sandbox.c:63` `static void *jm_calloc(void *opaque, size_t count, size_t size)`
- `jm_free` (function) `src/js_sandbox.c:73` `static void jm_free(void *opaque, void *ptr)`
- `jm_realloc` (function) `src/js_sandbox.c:79` `static void *jm_realloc(void *opaque, void *ptr, size_t size)`
- `jm_usable_size` (function) `src/js_sandbox.c:89` `static size_t jm_usable_size(const void *ptr)`
- `host_dup` (function) `src/js_sandbox.c:99` `static char *host_dup(const char *src, size_t len)`
- `timespec_reached` (function) `src/js_sandbox.c:108` `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)`
- `js_interrupt_cb` (function) `src/js_sandbox.c:114` `static int js_interrupt_cb(JSRuntime *rt, void *opaque)` -- if (len == (size_t)-1) return NULL; /* guard: len+1 would overflow to 0 char *out = (char *)malloc(len + 1); if (out...
- `is_ascii_digit` (function) `src/js_sandbox.c:127` `static int is_ascii_digit(char c)`
- `js_loc_from_stack` (function) `src/js_sandbox.c:129` `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      i...`
- `undefined` (function) `src/js_sandbox.c:221` `* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx...`
- `js_limits_default` (function) `src/js_sandbox.c:248` `js_limits js_limits_default(void)`
- `limits_resolve` (function) `src/js_sandbox.c:257` `static js_limits limits_resolve(const js_limits *lim)`
- `js_validate_source` (function) `src/js_sandbox.c:266` `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)`
- `js_context_new` (function) `src/js_sandbox.c:277` `js_status js_context_new(const js_limits *lim, js_context **out)`
- `js_context_free` (function) `src/js_sandbox.c:316` `void js_context_free(js_context *ctx)`
- `arm_deadline` (function) `src/js_sandbox.c:327` `static void arm_deadline(js_context *ctx, uint64_t budget_ms)`
- `js_set_time_budget` (function) `src/js_sandbox.c:342` `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)`
- `js_eval` (function) `src/js_sandbox.c:347` `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)`
- `js_eval_named` (function) `src/js_sandbox.c:351` `js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        con...`
- `js_pump_jobs` (function) `src/js_sandbox.c:434` `int js_pump_jobs(js_context *ctx, int max_jobs)`
- `js_eval_once` (function) `src/js_sandbox.c:452` `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)`
- `js_result_free` (function) `src/js_sandbox.c:465` `void js_result_free(js_result *res)`
- `js_set_current_script` (function) `src/js_sandbox.c:489` `void js_set_current_script(js_context *ctx, const char *src, const char *type)`
- `js_context_raw` (function) `src/js_sandbox.c:522` `void *js_context_raw(js_context *ctx)`
- `mod_set_meta` (function) `src/js_sandbox.c:543` `static void mod_set_meta(JSContext *jc, JSValueConst compiled, const char *url)` -- QuickJS normalizer: every specifier goes through the host resolver.
- `mod_loader` (function) `src/js_sandbox.c:552` `static JSModuleDef *mod_loader(JSContext *jc, const char *name, void *opaque)` -- } return js_strdup(jc, out); } /* Sets import.meta.url of a compiled module to its absolute URL. static void...
- `js_set_module_host` (function) `src/js_sandbox.c:588` `void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve,
                        js...`
- `mod_fail` (function) `src/js_sandbox.c:598` `static js_status mod_fail(js_context *ctx, js_result *res, JSValue reason, int use_reason,
      ...` -- Fills res from the pending exception (or the given rejection value, which is * thrown first so the one capture path...
- `js_eval_module` (function) `src/js_sandbox.c:613` `js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name,
        ...`
- `realm_of` (function) `src/js_sandbox.c:680` `static JSContext *realm_of(js_context *c, JSValueConst g)` -- The owning js_context rides in each native's closure data, split into 32-bit * halves (no assumption about JS number...
- `throw_named` (function) `src/js_sandbox.c:693` `static JSValue throw_named(JSContext *ctx, const char *name, const char *msg)`
- `m_realm_new` (function) `src/js_sandbox.c:703` `static JSValue m_realm_new(JSContext *ctx, JSValueConst this_val, int argc,
                     ...`
- `m_realm_eval` (function) `src/js_sandbox.c:717` `static JSValue m_realm_eval(JSContext *ctx, JSValueConst this_val, int argc,
                    ...` -- __realmEval(global, code, name): a classic script in that realm.
- `m_realm_clone` (function) `src/js_sandbox.c:753` `static JSValue m_realm_clone(JSContext *ctx, JSValueConst this_val, int argc,
                   ...` -- __realmClone(value, global): structured copy into global's realm through the * serializer WITHOUT bytecode -- a...
- `js_install_realms` (function) `src/js_sandbox.c:775` `js_status js_install_realms(js_context *ctx)`


Next: [API_p8.md](API_p8.md)
