# API (page 11 of 11)
Previous: [API_p10.md](API_p10.md)

## src/text_shape.c
Depends on: `include/css.h`, `include/text_shape.h`, `include/webfont.h`
- `generic_name` (function) `src/text_shape.c:55` `static const char *generic_name(int family)`
- `backend_init` (function) `src/text_shape.c:65` `static int backend_init(void)`
- `read_font_file` (function) `src/text_shape.c:82` `static unsigned char *read_font_file(const char *path, long *out_n)`
- `characters` (function) `src/text_shape.c:100` `* hold characters ('-', ':') that the pattern syntax treats specially. */ static int load_entry_file(tsh_entry *e...`
- `load_entry_named` (function) `src/text_shape.c:103` `static int load_entry_named(tsh_entry *e, const char *fam, int bold, int italic)`
- `load_entry_file` (function) `src/text_shape.c:133` `static int load_entry_file(tsh_entry *e, const char *path, int index)` -- Loads face `index` of the font file at `path` into e (FreeType + cairo + * HarfBuzz over one owned copy of the bytes).
- `load_entry` (function) `src/text_shape.c:169` `static int load_entry(tsh_entry *e, int family, int bold, int italic)`
- `get_entry` (function) `src/text_shape.c:173` `static tsh_entry *get_entry(int family, int bold, int italic)`
- `web_entry_free` (function) `src/text_shape.c:201` `static void web_entry_free(tsh_web *w)`
- `slice` (function) `src/text_shape.c:213` `* woff2 slice (spec/webfont.md);`
- `web_magic_ok` (function) `src/text_shape.c:214` `static int web_magic_ok(const unsigned char *b, size_t n)` -- True for font programs FreeType parses without new decoders: wOFF/TrueType/ CFF-OpenType (and the mac aliases). wOF2...
- `web_make_entry` (function) `src/text_shape.c:227` `static int web_make_entry(tsh_entry *e, const unsigned char *bytes, size_t nbytes)` -- Builds the shaping faces over an OWNED copy of bytes[0,nbytes) into e (shared tail with load_entry's file path: same...
- `tsh_webfont_register` (function) `src/text_shape.c:267` `int tsh_webfont_register(const char *name,
                         const unsigned char *bytes, s...`
- `tsh_webfont_clear` (function) `src/text_shape.c:301` `void tsh_webfont_clear(void)`
- `web_find` (function) `src/text_shape.c:306` `static tsh_entry *web_find(unsigned h, int bold, int italic)`
- `entry_free` (function) `src/text_shape.c:318` `static void entry_free(tsh_entry *e)`
- `ascii_ieq` (function) `src/text_shape.c:331` `static int ascii_ieq(const char *a, const char *b)`
- `tsh_family_is_generic` (function) `src/text_shape.c:340` `int tsh_family_is_generic(const char *name)`
- `tsh_pick_from_list` (function) `src/text_shape.c:352` `int tsh_pick_from_list(const char *list, tsh_name_resolver resolve, void *ctx,
                  ...`
- `tsh_pick_family` (function) `src/text_shape.c:373` `const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong,
        ...`
- `fc_installed` (function) `src/text_shape.c:386` `static int fc_installed(const char *name, void *ctx)` -- const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong, size_t n, int...
- `fc_resolve` (function) `src/text_shape.c:429` `static int fc_resolve(const char *name, char *out, size_t cap, void *ctx)`
- `local_clear` (function) `src/text_shape.c:474` `static void local_clear(void)`
- `lfam_index` (function) `src/text_shape.c:484` `static int lfam_index(const char *fam)`
- `tsh_local_handle` (function) `src/text_shape.c:492` `int tsh_local_handle(const char *list)`
- `local_entry` (function) `src/text_shape.c:511` `static tsh_entry *local_entry(int handle, int bold, int italic)`
- `get_entry_ex` (function) `src/text_shape.c:531` `static tsh_entry *get_entry_ex(const tsh_font *f)` -- Entry for a full font selector: a registered @font-face wins over the local bucket stack; a set-but-unregistered...
- `tsh_ready` (function) `src/text_shape.c:543` `int tsh_ready(void)`
- `tsh_shape` (function) `src/text_shape.c:548` `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                ...`
- `utf8_next` (function) `src/text_shape.c:597` `static unsigned utf8_next(const char *s, size_t n, size_t *len)` -- Decodes one UTF-8 sequence at s[0..n): the code point (U+FFFD for a malformed * sequence) and its byte length (>= 1...
- `is_private_use` (function) `src/text_shape.c:616` `static int is_private_use(unsigned cp)` -- if (l > n) l = 1; if (l == 1) { *len = 1; return (c < 0x80) ? c : 0xFFFDu; } unsigned cp = c & (0x7fu >> l); for...
- `rides_previous` (function) `src/text_shape.c:621` `static int rides_previous(unsigned cp)` -- cp = (cp << 6) | (u[k] & 0x3fu); } len = l; return cp; } #define TSH_BLANK_GLYPH ((unsigned long)-1) /* Private Use...
- `tsh_segment` (function) `src/text_shape.c:629` `int tsh_segment(const char *text, size_t len, tsh_cover_fn cover, void *ctx,
                tsh_...`
- `fb_clear` (function) `src/text_shape.c:669` `static void fb_clear(void)`
- `fb_entry` (function) `src/text_shape.c:679` `static tsh_entry *fb_entry(unsigned cp, int bold)` -- The fallback entry covering cp (bold or regular), or NULL.
- `cover_cp` (function) `src/text_shape.c:750` `static int cover_cp(unsigned cp, void *vctx)` -- cover callback: 0 when the requested face has the glyph (or nothing else * does), else the id of the fallback face...
- `shape_entry` (function) `src/text_shape.c:764` `static tsh_status shape_entry(tsh_entry *e, double px, const char *text, size_t len,
            ...` -- static int cover_cp(unsigned cp, void *vctx) { tsh_cover_ctx *c = (tsh_cover_ctx *)vctx; hb_codepoint_t g; if (cp ==...
- `shape_runs` (function) `src/text_shape.c:800` `static tsh_status shape_runs(cairo_t *cr, const tsh_font *f, double px, double x,
               ...` -- Measures (cr == NULL) or draws [text,len) run by run, each with the face that * has its glyphs.
- `tsh_measure` (function) `src/text_shape.c:846` `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)`
- `tsh_draw` (function) `src/text_shape.c:852` `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, doub...`
- `tsh_face` (function) `src/text_shape.c:859` `cairo_font_face_t *tsh_face(const tsh_font *f)`
- `tsh_shutdown` (function) `src/text_shape.c:865` `void tsh_shutdown(void)`

## src/textfield.c
Depends on: `include/textfield.h`
- `whole` (function) `src/textfield.c:6` `* the buffer is rejected whole (fail closed), never applied partially.
 */

#include "textfield.h...`
- `tf_clear` (function) `src/textfield.c:20` `void tf_clear(tf_field *f)`
- `tf_set` (function) `src/textfield.c:24` `tf_status tf_set(tf_field *f, const char *s)`
- `tf_insert` (function) `src/textfield.c:35` `tf_status tf_insert(tf_field *f, char c)`
- `tf_backspace` (function) `src/textfield.c:47` `void tf_backspace(tf_field *f)`
- `tf_delete` (function) `src/textfield.c:55` `void tf_delete(tf_field *f)`
- `tf_move` (function) `src/textfield.c:62` `void tf_move(tf_field *f, long delta)`
- `tf_home` (function) `src/textfield.c:73` `void tf_home(tf_field *f)`
- `tf_end` (function) `src/textfield.c:78` `void tf_end(tf_field *f)`
- `tf_text` (function) `src/textfield.c:83` `const char *tf_text(const tf_field *f)`
- `tf_len` (function) `src/textfield.c:87` `size_t tf_len(const tf_field *f)`
- `tf_cursor` (function) `src/textfield.c:91` `size_t tf_cursor(const tf_field *f)`

## src/tls_impersonate.c
Depends on: `include/tls_impersonate.h`
- `ti_should_impersonate` (function) `src/tls_impersonate.c:18` `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,
                          i...`
- `bounded_len` (function) `src/tls_impersonate.c:25` `static size_t bounded_len(const char *s, size_t max)`
- `put_u8` (function) `src/tls_impersonate.c:35` `static void put_u8(ti_wr *w, uint8_t v)`
- `put_u32` (function) `src/tls_impersonate.c:40` `static void put_u32(ti_wr *w, uint32_t v)`
- `put_u64` (function) `src/tls_impersonate.c:48` `static void put_u64(ti_wr *w, uint64_t v)`
- `put_blob` (function) `src/tls_impersonate.c:53` `static void put_blob(ti_wr *w, const uint8_t *b, size_t n)`
- `get_u8` (function) `src/tls_impersonate.c:65` `static uint8_t get_u8(ti_rd *r)`
- `get_u32` (function) `src/tls_impersonate.c:70` `static uint32_t get_u32(ti_rd *r)`
- `get_u64` (function) `src/tls_impersonate.c:80` `static uint64_t get_u64(ti_rd *r)`
- `get_bytes` (function) `src/tls_impersonate.c:89` `static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len)` -- | ((uint32_t)r->p[r->off + 3] << 24); r->off += 4; return v; } static uint64_t get_u64(ti_rd *r) { if (r->err ||...
- `get_str` (function) `src/tls_impersonate.c:103` `static char *get_str(ti_rd *r, size_t cap)` -- static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len) { out = NULL; *out_len = 0; uint32_t n =...
- `valid_profile` (function) `src/tls_impersonate.c:116` `static int valid_profile(int p)`
- `ti_encode_req` (function) `src/tls_impersonate.c:122` `size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap)`
- `ti_decode_req` (function) `src/tls_impersonate.c:140` `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out)`
- `ti_req_free` (function) `src/tls_impersonate.c:166` `void ti_req_free(ti_req *r)`
- `ti_encode_resp` (function) `src/tls_impersonate.c:177` `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap)`
- `ti_decode_resp` (function) `src/tls_impersonate.c:196` `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out)`
- `ti_resp_free` (function) `src/tls_impersonate.c:230` `void ti_resp_free(ti_resp *r)`

## src/ui_layout.c
Depends on: `include/ui.h`
- `layout_push` (function) `src/ui_layout.c:13` `static int layout_push(ui_layout *lay, size_t offset, size_t len)`
- `ui_wrap_text` (function) `src/ui_layout.c:27` `ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out)`
- `ui_layout_free` (function) `src/ui_layout.c:91` `void ui_layout_free(ui_layout *lay)`
- `ui_clamp_scroll` (function) `src/ui_layout.c:99` `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines)`

## src/url.c
Depends on: `include/url.h`
- `ci_prefix` (function) `src/url.c:20` `static int ci_prefix(const char *haystack, const char *prefix)` -- produced; every assembly is bounded and reports overflow rather than truncate.  #define _POSIX_C_SOURCE 200809L...
- `copy_checked` (function) `src/url.c:32` `static int copy_checked(char *out, size_t outsz, const char *src)` -- /* Case-insensitive: does haystack start with prefix? static int ci_prefix(const char *haystack, const char *prefix)...
- `cat_checked` (function) `src/url.c:40` `static int cat_checked(char *out, size_t outsz, const char *src)` -- +haystack; ++prefix; } return 1; } /* Bounded copy: out gets src (NUL-terminated).
- `ncat_checked` (function) `src/url.c:49` `static int ncat_checked(char *out, size_t outsz, const char *src, size_t n)` -- memcpy(out, src, n + 1); return 0; } /* Bounded append: out += src.
- `url_has_scheme` (function) `src/url.c:59` `int url_has_scheme(const char *s)`
- `url_is_https` (function) `src/url.c:73` `int url_is_https(const char *s)`
- `url_validate_https` (function) `src/url.c:80` `url_status url_validate_https(const char *url)`
- `url_authority_len` (function) `src/url.c:91` `size_t url_authority_len(const char *url)`
- `out_pop_segment` (function) `src/url.c:102` `static void out_pop_segment(char *out, size_t *olen)` -- RFC 3986 3.2: the authority ends at the first '/', '?' or '#'.
- `url_remove_dot_segments` (function) `src/url.c:109` `url_status url_remove_dot_segments(const char *path, char *out, size_t outsz)`
- `dir_len` (function) `src/url.c:159` `static size_t dir_len(const char *base)` -- Length of base up to and including the last path '/', ignoring query/fragment. * If the path carries no slash...
- `url_resolve_https` (function) `src/url.c:170` `url_status url_resolve_https(const char *base, const char *ref,
                             char...`
- `is_space` (function) `src/url.c:218` `static int is_space(int c)`
- `is_unreserved` (function) `src/url.c:222` `static int is_unreserved(int c)`
- `append_query_encoded` (function) `src/url.c:229` `static int append_query_encoded(char *out, size_t outsz, const char *src)` -- Percent-encodes src into a query value appended to out (space -> '+', every * non-unreserved byte -> %XX).
- `assumed` (function) `src/url.c:254` `* assumed (the caller already routed whitespace to search). */
static int looks_like_host(const c...`
- `build_search` (function) `src/url.c:303` `static url_status build_search(const char *query, char *out, size_t outsz)`
- `url_omnibox` (function) `src/url.c:309` `url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz)`
- `host_equals` (function) `src/url.c:378` `static int host_equals(const url_parts *p, const char *want)` -- Any remaining explicit scheme is never executed nor downgraded: search for it * (so "javascript:...", "file:..."...
- `query_find_q` (function) `src/url.c:393` `static const char *query_find_q(const char *search, size_t len, size_t *vlen)` -- Returns a pointer to the value of the "q" parameter within a "?a=b&q=v&..." search span, with its length in *vlen...
- `url_search_rewrite` (function) `src/url.c:411` `url_status url_search_rewrite(const char *url, char *out, size_t outsz)`
- `url_extract_userinfo` (function) `src/url.c:431` `url_status url_extract_userinfo(const char *url, char *out, size_t outsz,
                       ...`
- `url_is_file` (function) `src/url.c:525` `int url_is_file(const char *s)`
- `url_file_path` (function) `src/url.c:531` `const char *url_file_path(const char *s)`
- `url_resolve_file` (function) `src/url.c:535` `url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz)`
- `url_split` (function) `src/url.c:584` `url_status url_split(const char *url, url_parts *out)`
- `copy_bounded` (function) `src/url.c:645` `static url_status copy_bounded(char *out, size_t outsz, const char *a, size_t alen,
             ...`
- `url_history_target` (function) `src/url.c:654` `url_status url_history_target(const char *base, const char *ref, char *out, size_t outsz)`

## src/web_storage.c
Depends on: `include/web_storage.h`
- `get_u32` (function) `src/web_storage.c:25` `static uint32_t get_u32(const unsigned char *p)`
- `utf8_ok` (function) `src/web_storage.c:32` `static int utf8_ok(const unsigned char *s, size_t n)` -- Well-formed UTF-8, allowing encoded surrogates (WTF-8): a JS string may hold a lone surrogate and rejecting it would...
- `key_cmp` (function) `src/web_storage.c:56` `static int key_cmp(const void *a, const void *b)`
- `check` (function) `src/web_storage.c:65` `static int check(const char *blob, size_t len, size_t *bytes_out)` -- return 1; } typedef struct key_ref { const unsigned char *p; uint32_t n; } key_ref; static int key_cmp(const void...
- `wst_decode_check` (function) `src/web_storage.c:101` `int wst_decode_check(const char *blob, size_t len)`
- `wst_new` (function) `src/web_storage.c:105` `wst_db *wst_new(void)`
- `wst_free` (function) `src/web_storage.c:109` `void wst_free(wst_db *db)`
- `find` (function) `src/web_storage.c:118` `static wst_origin *find(const wst_db *db, const char *origin)`
- `wst_encode` (function) `src/web_storage.c:125` `int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len)`
- `wst_replace` (function) `src/web_storage.c:140` `int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len)`
- `wst_origin_bytes` (function) `src/web_storage.c:175` `size_t wst_origin_bytes(const wst_db *db, const char *origin)`
- `wst_foreach` (function) `src/web_storage.c:181` `int wst_foreach(const char *blob, size_t len,
                void (*fn)(void *ctx, const char *k...`
- `put_u32` (function) `src/web_storage.c:201` `static void put_u32(char *b, uint32_t v)`
- `wst_pack` (function) `src/web_storage.c:206` `int wst_pack(const char *const *keys, const size_t *klens,
             const char *const *vals, ...`

## src/webcaps.c
Depends on: `include/webcaps.h`
- `wc_safe` (function) `src/webcaps.c:10` `wc_caps wc_safe(void)`
- `wc_derive` (function) `src/webcaps.c:15` `wc_caps wc_derive(wc_input in)`
- `wc_from_flags` (function) `src/webcaps.c:35` `wc_caps wc_from_flags(bool js, bool css, bool images)`
- `wc_render_caps` (function) `src/webcaps.c:46` `rdp_caps wc_render_caps(wc_caps c)`

## src/webfont.c
Depends on: `include/data_url.h`, `include/webfont.h`
- `candidates` (function) `src/webfont.c:7` `* understanding just far enough to find candidates (family + first url() per * src entry + weight/style descriptors);`
- `is_ws` (function) `src/webfont.c:19` `static int is_ws(char c)`
- `lower_ch` (function) `src/webfont.c:23` `static int lower_ch(char c)`
- `ci_eq_span` (function) `src/webfont.c:28` `static int ci_eq_span(const char *s, size_t n, const char *kw)` -- #include <stdint.h> #include <stdlib.h> #include <string.h> static int is_ws(char c) { return c == ' ' || c == '\t'...
- `wf_list_free` (function) `src/webfont.c:49` `void wf_list_free(wf_list *l)`
- `wf_ref_move` (function) `src/webfont.c:64` `void wf_ref_move(wf_ref *dst, wf_ref *src)`
- `wf_supported_format` (function) `src/webfont.c:74` `int wf_supported_format(const char *fmt)`
- `emit_slot` (function) `src/webfont.c:83` `static wf_ref *emit_slot(wf_list *out)` -- src->is_data = 0; } int wf_supported_format(const char *fmt) { if (fmt == NULL) return 0; if (fmt[0] == '\0') return...
- `emit_family_format` (function) `src/webfont.c:98` `static void emit_family_format(wf_ref *r, const char *family, const char *format)`
- `span_is_data` (function) `src/webfont.c:114` `static int span_is_data(const char *span, size_t slen)` -- if (fl >= WF_FAMILY_MAX) fl = WF_FAMILY_MAX - 1; memcpy(r->family, family, fl); r->family[fl] = '\0'; if (format !=...
- `emit` (function) `src/webfont.c:126` `static void emit(wf_list *out, const char *family,
                 const char *url, size_t ulen,...` -- /* True when span[0,slen) is a data: URL (case-insensitive scheme). static int span_is_data(const char *span, size_t...
- `emit_data` (function) `src/webfont.c:142` `static void emit_data(wf_list *out, const char *family,
                      const char *span, s...` -- Appends one data: ref, decoding the bytes NOW (a data: URL never fits url[]; * the bytes ride the ref instead).
- `scan_face_block` (function) `src/webfont.c:179` `static void scan_face_block(const char *s, size_t bstart, size_t bend,
                          ...` -- Parses one @font-face {...} body (bstart..bend, braces excluded) into the block's family/weight/style, then emits...
- `lower_ch` (function) `src/webfont.c:306` `&& lower_ch(s[k]) == 's' && k + 3 < bend
                && lower_ch(s[k + 1]) == 'r' && lower_ch...`
- `wf_scan` (function) `src/webfont.c:422` `int wf_scan(const char *css, size_t len, wf_list *out)`

## src/webfont_load.c
Depends on: `include/data_url.h`, `include/text_shape.h`, `include/url.h`, `include/webfont.h`, `include/webfont_load.h`
- `here` (function) `src/webfont_load.c:22` `* filtered here (a "" hint may still name one);`
- `ctype_ok` (function) `src/webfont_load.c:24` `static int ctype_ok(const char *ct)` -- Content types worth downloading as fonts.
- `key_find` (function) `src/webfont_load.c:66` `static int key_find(wf_key *keys, size_t nkeys, unsigned h, int b, int i)`
- `ref` (function) `src/webfont_load.c:167` `* their ref (the register call copies what it keeps). */ if (!is_data) free(fbytes);`
- `scan_inline` (function) `src/webfont_load.c:178` `static void scan_inline(const char *html, size_t len, const char *page_url,
                     ...` -- Finds inline <style>...</style> bodies in html (case-insensitive tags) and processes each sheet's refs against the...
- `wf_load_document` (function) `src/webfont_load.c:229` `int wf_load_document(wf_fetch_fn fetch, void *fctx, const char *page_url,
                     co...`

## src/wl_display.c
Depends on: `include/wl_display.h`
- `wd_index` (function) `src/wl_display.c:13` `static int wd_index(const char *name, unsigned long *idx)`
- `wd_pick` (function) `src/wl_display.c:27` `int wd_pick(const char *const *names, size_t n, char *out, size_t cap)`
- `wd_resolve_env` (function) `src/wl_display.c:42` `int wd_resolve_env(void)`

## src/wl_guard.c
Depends on: `include/wl_guard.h`
- `guard_main` (function) `src/wl_guard.c:26` `static void *guard_main(void *arg)`
- `wlg_start` (function) `src/wl_guard.c:45` `wl_guard *wlg_start(struct wl_display *display)`
- `wlg_stop` (function) `src/wl_guard.c:61` `void wlg_stop(wl_guard *g)`

## src/ws_hub.c
Depends on: `include/ws_hub.h`
- `dup_str` (function) `src/ws_hub.c:54` `static char *dup_str(const char *s)`
- `job_free` (function) `src/ws_hub.c:63` `static void job_free(wh_job *j)`
- `job_str` (function) `src/ws_hub.c:71` `static int job_str(wh_job *j, size_t slot, const char **field)` -- if (n == (size_t)-1) return NULL; char *d = (char *)malloc(n + 1); if (d != NULL) memcpy(d, s, n + 1); return d; }...
- `open_thread` (function) `src/ws_hub.c:79` `static void *open_thread(void *arg)`
- `conn_clear` (function) `src/ws_hub.c:98` `static void conn_clear(wh_conn *c)`
- `find_id` (function) `src/ws_hub.c:104` `static wh_conn *find_id(wh_hub *h, int id)`
- `find_token` (function) `src/ws_hub.c:110` `static wh_conn *find_token(wh_hub *h, uint64_t token)`
- `wh_new` (function) `src/ws_hub.c:116` `wh_hub *wh_new(void)`
- `wh_free` (function) `src/ws_hub.c:129` `void wh_free(wh_hub *h)`
- `wh_notify_fd` (function) `src/ws_hub.c:144` `int wh_notify_fd(const wh_hub *h)`
- `wh_open_async` (function) `src/ws_hub.c:148` `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg)`
- `wh_on_notify` (function) `src/ws_hub.c:192` `void wh_on_notify(wh_hub *h, wh_emit_fn emit, void *ctx)`
- `wh_send` (function) `src/ws_hub.c:221` `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary)`
- `wh_close` (function) `src/ws_hub.c:228` `void wh_close(wh_hub *h, int id)`
- `wh_close_all` (function) `src/ws_hub.c:234` `void wh_close_all(wh_hub *h)`
- `wh_poll_fds` (function) `src/ws_hub.c:240` `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap)`
- `fail_conn` (function) `src/ws_hub.c:258` `static void fail_conn(wh_conn *c, int id, wh_emit_fn emit, void *ctx)` -- const wh_conn *c = &h->c[i]; if (!c->used || c->pending || c->ws == NULL) continue; int fd = sf_ws_fd(c->ws); if (fd...
- `wh_on_readable` (function) `src/ws_hub.c:266` `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx)`
- `wh_count` (function) `src/ws_hub.c:314` `size_t wh_count(const wh_hub *h)`

## src/zoom.c
Depends on: `include/zoom.h`
- `zm_clamp` (function) `src/zoom.c:14` `int zm_clamp(int pct)`
- `zm_zoom_in` (function) `src/zoom.c:20` `int zm_zoom_in(int pct)`
- `zm_zoom_out` (function) `src/zoom.c:28` `int zm_zoom_out(int pct)`
- `zm_reset` (function) `src/zoom.c:36` `int zm_reset(void)`
- `zm_scale` (function) `src/zoom.c:40` `double zm_scale(int pct)`
- `zm_apply` (function) `src/zoom.c:44` `double zm_apply(double base_px, int pct)`

## tools/fbench.py
- `load_baseline` (function) `tools/fbench.py:53` `def load_baseline()`
- `load_current` (function) `tools/fbench.py:66` `def load_current()`
- `luma` (function) `tools/fbench.py:79` `def luma(img)`
- `bands` (function) `tools/fbench.py:83` `def bands(fd, ff, band)`
- `sbs` (function) `tools/fbench.py:95` `def sbs(name, start, nrows)`
- `publish_readme` (function) `tools/fbench.py:114` `def publish_readme(name, score)` -- Rewrite the README picture of `name` and the score printed beside its label.
- `run_timer` (function) `tools/fbench.py:140` `def run_timer(tool, pages, runs)` -- Runs a timing tool over the pages; returns ({name: median ms}, exit code).
- `load_timing_baseline` (function) `tools/fbench.py:158` `def load_timing_baseline()`
- `publish_timing` (function) `tools/fbench.py:171` `def publish_timing(rows)` -- Rewrites the README timing table (between the markers) for the README pages timed.
- `timing` (function) `tools/fbench.py:193` `def timing(names, runs, readme)`
- `main` (function) `tools/fbench.py:227` `def main()`

## tools/ffgeom.py
- `load_rows` (function) `tools/ffgeom.py:116` `def load_rows(path)`
- `lum` (function) `tools/ffgeom.py:169` `def lum(p)`
- `lum_at` (function) `tools/ffgeom.py:181` `def lum_at(x, y)`
- `bit` (function) `tools/ffgeom.py:206` `def bit(grid_row, cell, origin)`
- `word` (function) `tools/ffgeom.py:209` `def word(grid_row, origin)`
- `decode` (function) `tools/ffgeom.py:239` `def decode(path)`
- `probe` (function) `tools/ffgeom.py:265` `def probe(page, selector, out_html)`
- `height_probe` (function) `tools/ffgeom.py:279` `def height_probe(page, out_html)`
- `height` (function) `tools/ffgeom.py:292` `def height(path)` -- Decodes the scrollHeight carried by the #__ffh sentinel: the probe encodes one rect (its height), which decode()...
- `main` (function) `tools/ffgeom.py:301` `def main(argv)`

## tools/ffq.py
- `main` (function) `tools/ffq.py:22` `def main()`

## tools/ffshot.py
- `main` (function) `tools/ffshot.py:24` `def main()`

## tools/fftime.py
- `main` (function) `tools/fftime.py:38` `def main()`

## tools/gen_psl.c
- `vec_push` (function) `tools/gen_psl.c:27` `static void vec_push(vec *v, const char *s)`
- `cmp_str` (function) `tools/gen_psl.c:38` `static int cmp_str(const void *a, const void *b)`
- `sort_unique` (function) `tools/gen_psl.c:43` `static void sort_unique(vec *v)` -- v->cap = v->cap ? v->cap * 2 : 1024; v->items = (char **)realloc(v->items, v->cap * sizeof *v->items); if (v->items...
- `ascii_lower` (function) `tools/gen_psl.c:55` `static void ascii_lower(char *s)` -- /* Sorts then drops adjacent duplicates in place. static void sort_unique(vec *v) { qsort(v->items, v->len, sizeof...
- `emit` (function) `tools/gen_psl.c:61` `static void emit(const char *name, vec *v)`
- `main` (function) `tools/gen_psl.c:67` `int main(int argc, char **argv)`

## tools/guitime.py
- `start_display` (function) `tools/guitime.py:34` `def start_display(workdir)` -- Starts Xvfb and a nested weston; returns (env, processes) or None when unavailable.
- `one_run` (function) `tools/guitime.py:65` `def one_run(binary, page, env, hosts_dir, tmp)`
- `main` (function) `tools/guitime.py:92` `def main()`

## tools/mutate.py
- `line_sites` (function) `tools/mutate.py:41` `def line_sites(text)`
- `mutate_line` (function) `tools/mutate.py:75` `def mutate_line(line, op)`
- `find_modules` (function) `tools/mutate.py:107` `def find_modules(root)`
- `run_make` (function) `tools/mutate.py:116` `def run_make(root, target)`
- `run_bin` (function) `tools/mutate.py:125` `def run_bin(path)`
- `main` (function) `tools/mutate.py:137` `def main(argv)`

## tools/pngdiff.c
- `pd_reader_close` (function) `tools/pngdiff.c:79` `static void pd_reader_close(pd_reader *r)`
- `pd_reader_open` (function) `tools/pngdiff.c:88` `static int pd_reader_open(pd_reader *r, const char *path)` -- Opens `path` and normalises whatever colour type it carries into 8-bit RGB, so * the two passes below can assume...
- `png_set_background` (function) `tools/pngdiff.c:116` `png_set_background(r->png, &(png_color_16)` -- Compose against white rather than dropping alpha: a transparent region of a screenshot is what the viewer would see...
- `pd_lum` (function) `tools/pngdiff.c:141` `static double pd_lum(const png_byte *p)`
- `pd_background` (function) `tools/pngdiff.c:147` `static int pd_background(const char *path, double *out_bg)` -- Pass 1: the modal luminance IS the page background.
- `pd_profile_of` (function) `tools/pngdiff.c:175` `static int pd_profile_of(const char *path, pd_profile *out)` -- int b = (int)(pd_lum(&r.row[(size_t)x * 3u]) + 0.5); if (b < 0) b = 0; if (b > 255) b = 255; hist[b]++; } } int best...
- `pd_mae` (function) `tools/pngdiff.c:227` `static double pd_mae(const double *a, const double *b, size_t n)`
- `main` (function) `tools/pngdiff.c:233` `int main(int argc, char **argv)`

## tools/pngprof.py
- `load_rows` (function) `tools/pngprof.py:41` `def load_rows(path)`
- `lum` (function) `tools/pngprof.py:95` `def lum(p)`
- `render_glyph` (function) `tools/pngprof.py:99` `def render_glyph(v)`
- `main` (function) `tools/pngprof.py:109` `def main(argv)`

## tools/prune.py
- `main` (function) `tools/prune.py:21` `def main()`

## tools/snapshot.py
- `fetch` (function) `tools/snapshot.py:18` `def fetch(url)`
- `expand_imports` (function) `tools/snapshot.py:32` `def expand_imports(css, base, depth)` -- Replace each @import with the imported text (wrapped in @media when the import carries a media condition), resolved...
- `repl` (function) `tools/snapshot.py:35` `def repl(m)`
- `inline_css` (function) `tools/snapshot.py:49` `def inline_css(html, base)`
- `repl` (function) `tools/snapshot.py:50` `def repl(m)`
- `main` (function) `tools/snapshot.py:70` `def main()`

## tools/snapshot_age.py
- `main` (function) `tools/snapshot_age.py:16` `def main()`

