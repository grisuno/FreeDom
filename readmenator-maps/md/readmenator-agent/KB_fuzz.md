# Subsystem: fuzz

## fuzz/fuzz_anchor.c
- Doc: Fuzzer for anchor (spec/anchor.md) and url_split_location: a hostile document x a
- Layer: utility
- Language: c
- Symbols:
  - `check_decode` (function, line 15) `static void check_decode(const char *frag)`
  - `check_location` (function, line 23) `static void check_location(const char *frag)`
  - `LLVMFuzzerTestOneInput` (function, line 37) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/anchor.h`, `include/dom.h`, `include/html_parse.h`, `include/url.h`

## fuzz/fuzz_box_blur.c
- Doc: libFuzzer harness for box_blur (spec/box_blur.md): a hostile mask, size, stride and sigma
- Layer: utility
- Language: c
- Symbols:
  - `ref_line` (function, line 12) `static void ref_line(unsigned char *p, int n, int step, int bw, unsigned char *tmp)`
  - `LLVMFuzzerTestOneInput` (function, line 25) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/box_blur.h`

## fuzz/fuzz_box_tree.c
- Doc: Hostile box trees (any parent graph, cycles included) through the positioned paint
- Layer: utility
- Language: c
- Symbols:
  - `FB_MAX` (macro, line 8) `#define FB_MAX`
- Depends on: `include/box_tree.h`, `include/page_view.h`

## fuzz/fuzz_browser.c
- Doc: pos: define SNAP_MAX 512
- Layer: utility
- Language: c
- Symbols:
  - `snap` (struct, line 19)
  - `pos` (type_alias, line 18) `typedef struct snap { size_t n, pos;`
  - `snap_free` (function, line 25) `static void snap_free(snap *s)`
  - `snap_take` (function, line 30) `static void snap_take(snap *s, const browser_state *bs)`
  - `snap_check` (function, line 41) `static void snap_check(const snap *s, const browser_state *bs)`
  - `invariants` (function, line 48) `static void invariants(const browser_state *bs)`
  - `LLVMFuzzerTestOneInput` (function, line 53) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `_POSIX_C_SOURCE` (macro, line 8) `#define _POSIX_C_SOURCE`
  - `SNAP_MAX` (macro, line 17) `#define SNAP_MAX`
- Depends on: `include/browser.h`

## fuzz/fuzz_chrome_layout.c
- Doc: libFuzzer harness for chrome_layout (spec/chrome_layout.md): a hostile URL (a page
- Layer: presentation
- Language: c
- Symbols:
  - `take_double` (function, line 15) `static double take_double(const uint8_t **p, size_t *n)`
  - `check_rect` (function, line 25) `static void check_rect(chl_rect r)`
  - `LLVMFuzzerTestOneInput` (function, line 30) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/chrome_layout.h`

## fuzz/fuzz_css.c
- Doc: fuzz_root_match: Root matcher for the attribute-scoped custom-property path: a fixed <html...
- Layer: utility
- Language: c
- Symbols:
  - `fuzz_root_match` (function, line 77) `static int fuzz_root_match(void *ctx, const css_sel *sel)`
  - `LLVMFuzzerTestOneInput` (function, line 91) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/css.h`, `include/css_mq.h`, `include/css_select.h`, `include/flex_layout.h`

## fuzz/fuzz_css_counter.c
- Doc: libFuzzer harness for css_counter (spec/css_counter.md): hostile `content` and counter
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 11) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/css_counter.h`

## fuzz/fuzz_css_import.c
- Doc: fuzz_css_import -- hostile stylesheet text through the @import prelude reader
- Layer: utility
- Language: c
- Symbols:
  - `fz_out` (struct, line 13)
  - `fz_emit` (function, line 15) `static int fz_emit(void *ctx, const char *s, size_t n)`
  - `fz_resolve` (function, line 25) `static int fz_resolve(void *ctx, const char *base, const char *ref, char *out, size_t outsz)`
  - `LLVMFuzzerTestOneInput` (function, line 50) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/css_import.h`

## fuzz/fuzz_data_url.c
- Layer: data_access
- Language: c
- Symbols:
  - `worker` (function, line 6) `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, never
 * interpreted...`
- Depends on: `include/data_url.h`

## fuzz/fuzz_doc_title.c
- Doc: Fuzzer for doc_title (spec/doc_title.md): the title is always valid UTF-8, bounded by
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 26) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/doc_title.h`

## fuzz/fuzz_dom.c
- Layer: utility
- Language: c
- Symbols:
  - `ensure_built` (function, line 41) `static void ensure_built(void)`
  - `LLVMFuzzerTestOneInput` (function, line 48) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/dom.h`, `include/html_parse.h`

## fuzz/fuzz_dom_debug.c
- Layer: utility
- Language: c
- Symbols:
  - `pass` (function, line 8) `* the measure pass (cap 0) must agree with the would-write return value.
 *
 * Build & run: make ...`
- Depends on: `include/dom_debug.h`, `include/html_parse.h`, `include/page_view.h`, `include/render_doc.h`, `include/render_policy.h`

## fuzz/fuzz_download.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 31) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/download.h`

## fuzz/fuzz_exact_key.c
- Doc: libFuzzer harness for exact_key (spec/exact_key.md).
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 22) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/exact_key.h`

## fuzz/fuzz_fb_cmdline.c
- Doc: LLVMFuzzerTestOneInput: include <stdint.h> include <stdlib.h> include <string.h> include...
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 5) `int LLVMFuzzerTestOneInput(const uint8_t *d, size_t n)`
- Depends on: `include/fb_cmdline.h`

## fuzz/fuzz_find_text.c
- Doc: libFuzzer harness for find_text (spec/find_text.md).
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 11) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `MAXP` (macro, line 9) `#define MAXP`
- Depends on: `include/find_text.h`

## fuzz/fuzz_frame_broker.c
- Layer: utility
- Language: c
- Depends on: `include/frame_broker.h`

## fuzz/fuzz_freebug.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 37) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/freebug.h`

## fuzz/fuzz_group_index.c
- Doc: libFuzzer harness for group_index (spec/group_index.md): random keys (including out-of-range...
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 9) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/group_index.h`

## fuzz/fuzz_hls.c
- Doc: libFuzzer harness for hls (spec/hls.md): hostile playlist text, hostile
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 13) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/hls.h`, `include/request_policy.h`

## fuzz/fuzz_html_parse.c
- Layer: utility
- Language: c
- Depends on: `include/html_parse.h`

## fuzz/fuzz_identity.c
- Doc: libFuzzer harness for identity (spec/identity.md) and he_cdn_kind (spec/hostedit.md):
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 13) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/hostedit.h`, `include/identity.h`

## fuzz/fuzz_image_decode.c
- Doc: poke_and_free: Touch every claimed pixel corner so the sanitizer flags an out-of-bounds extent...
- Layer: utility
- Language: c
- Symbols:
  - `poke_and_free` (function, line 22) `static void poke_and_free(img_pixels *px)`
  - `LLVMFuzzerTestOneInput` (function, line 33) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/image_decode.h`, `include/svg_raster.h`

## fuzz/fuzz_import_map.c
- Layer: utility
- Language: c
- Symbols:
  - `fres` (function, line 17) `static int fres(void *ctx, const char *base, const char *ref, char *out, size_t outsz)`
  - `LLVMFuzzerTestOneInput` (function, line 24) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/import_map.h`

## fuzz/fuzz_js_dom.c
- Layer: utility
- Language: c
- Symbols:
  - `fz_dom_parent` (function, line 34) `static dom_node_id fz_dom_parent(void *ctx, dom_node_id n)`
  - `LLVMFuzzerTestOneInput` (function, line 41) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `FUZZ_JSDOM_MAX_NODES` (macro, line 39) `#define FUZZ_JSDOM_MAX_NODES`
- Depends on: `include/dom.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_geom.h`, `include/js_native.h`, `include/js_sandbox.h`, `include/js_trusted.h`, `include/url.h`, `include/web_storage.h`

## fuzz/fuzz_js_geom.c
- Doc: fz_parent_of: trigger UB, and a decoded table must re-encode to a table that decodes again.
- Layer: utility
- Language: c
- Symbols:
  - `fz_parent` (struct, line 17)
  - `fz_parent_of` (function, line 20) `static dom_node_id fz_parent_of(void *ctx, dom_node_id n)`
  - `LLVMFuzzerTestOneInput` (function, line 27) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/js_geom.h`

## fuzz/fuzz_js_sandbox.c
- Doc: fz_mod: Module host for the fuzzer: every "./" specifier resolves, and "./self.js" loads the...
- Layer: utility
- Language: c
- Symbols:
  - `fz_mod` (struct, line 21)
  - `fz_resolve` (function, line 23) `static int fz_resolve(void *host, const char *base, const char *spec, char *out, size_t outsz)`
  - `fz_fetch` (function, line 33) `static char *fz_fetch(void *host, const char *url, size_t *len)`
  - `LLVMFuzzerTestOneInput` (function, line 48) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `js_sandbox` (function, line 2) `* libFuzzer harness for js_sandbox (Hito 3). * * Goal: arbitrary bytes treated as untrusted script through the full...`
- Depends on: `include/js_sandbox.h`

## fuzz/fuzz_link_preview.c
- Doc: Fuzzer for link_preview (spec/link_preview.md): input = base NUL href.
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 11) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/link_nav.h`, `include/link_preview.h`

## fuzz/fuzz_mask_cache.c
- Doc: libFuzzer harness for mask_cache (spec/mask_cache.md).
- Layer: infrastructure
- Language: c
- Symbols:
  - `key_for` (function, line 15) `static mkc_key key_for(unsigned id, int w, int h)`
  - `LLVMFuzzerTestOneInput` (function, line 21) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `KEYS` (macro, line 13) `#define KEYS`
- Depends on: `include/mask_cache.h`

## fuzz/fuzz_nav_token.c
- Doc: libFuzzer harness for nav_token (spec/nav_token.md): a byte program of new / ref
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 13) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `POOL` (macro, line 11) `#define POOL`
- Depends on: `include/nav_token.h`

## fuzz/fuzz_net_guard.c
- Doc: libFuzzer harness for net_guard (spec/net_guard.md): hostile host and address text.
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 15) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `private` (function, line 3) `* for text the binary classifier would call private (the two cannot disagree);`
- Depends on: `include/net_guard.h`

## fuzz/fuzz_page_view.c
- Layer: presentation
- Language: c
- Depends on: `include/freedom_config.h`, `include/html_parse.h`, `include/page_view.h`, `include/sheet_cache.h`

## fuzz/fuzz_pdf_export.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 30) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/pdf_export.h`

## fuzz/fuzz_prefetch.c
- Doc: libFuzzer harness for the prefetch lookahead scanner (Hito 29).
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 14) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/prefetch.h`

## fuzz/fuzz_prefs.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 21) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/prefs.h`

## fuzz/fuzz_request_headers.c
- Layer: utility
- Language: c
- Depends on: `include/request_policy.h`

## fuzz/fuzz_scroll_req.c
- Doc: fuzz_scroll_req -- spec/scroll_req.md: a hostile wire record either decodes to an
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 11) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/scroll_req.h`

## fuzz/fuzz_site_panel.c
- Doc: libFuzzer harness for site_panel (spec/site_panel.md): a hostile URL and KE-group text
- Layer: utility
- Language: c
- Symbols:
  - `take_double` (function, line 14) `static double take_double(const uint8_t **p, size_t *n)`
  - `check_text` (function, line 20) `static void check_text(const char *s, size_t cap)`
  - `check_rect` (function, line 28) `static void check_rect(chl_rect r)`
  - `LLVMFuzzerTestOneInput` (function, line 33) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

## fuzz/fuzz_smooth_scroll.c
- Doc: libFuzzer harness for smooth_scroll (spec/smooth_scroll.md): drives random sequences of
- Layer: utility
- Language: c
- Symbols:
  - `take` (function, line 11) `static double take(const uint8_t **d, size_t *n)`
  - `LLVMFuzzerTestOneInput` (function, line 18) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/smooth_scroll.h`

## fuzz/fuzz_svg_render.c
- Layer: presentation
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 24) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/svg_render.h`

## fuzz/fuzz_table_layout.c
- Doc: libFuzzer harness for table_layout and pres_hints (spec/table_layout.md, spec/pres_hints.md).
- Layer: presentation
- Language: c
- Symbols:
  - `attr_src` (struct, line 15)
  - `attr_get` (function, line 17) `static const char *attr_get(void *ctx, const char *name, size_t *len)`
  - `LLVMFuzzerTestOneInput` (function, line 24) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/pres_hints.h`, `include/table_layout.h`

## fuzz/fuzz_text_case.c
- Doc: libFuzzer harness for text_case (spec/text_case.md): case mapping and the
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 13) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/css.h`, `include/text_case.h`

## fuzz/fuzz_text_shape.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 25) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `glyph` (function, line 54) `* one lacks a glyph (spec/text_shape.md 8);`
  - `ASCII` (function, line 56) `* printable ASCII (one run, the requested face) the two must agree. */ double m = tsh_measure(&f, px, text, len);`
  - `FZ_CAP` (macro, line 23) `#define FZ_CAP`
- Depends on: `include/text_shape.h`

## fuzz/fuzz_tls_impersonate.c
- Layer: utility
- Language: c
- Depends on: `include/tls_impersonate.h`

## fuzz/fuzz_url.c
- Layer: utility
- Language: c
- Symbols:
  - `check_split` (function, line 31) `static void check_split(const char *url)`
  - `LLVMFuzzerTestOneInput` (function, line 59) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/link_nav.h`, `include/url.h`

## fuzz/fuzz_video_controls.c
- Layer: utility
- Language: c
- Symbols:
  - `take` (function, line 8) `static double take(const uint8_t **p, size_t *n)`
  - `LLVMFuzzerTestOneInput` (function, line 14) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/video_controls.h`

## fuzz/fuzz_web_storage.c
- Layer: data_access
- Language: c
- Depends on: `include/web_storage.h`

## fuzz/fuzz_webfont.c
- Doc: libFuzzer harness for the webfont lookahead scanner (spec/webfont.md).
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 11) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/webfont.h`

## fuzz/fuzz_webfont_register.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 26) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `FZ_GLYPHS` (macro, line 24) `#define FZ_GLYPHS`
- Depends on: `include/text_shape.h`, `include/webfont.h`
