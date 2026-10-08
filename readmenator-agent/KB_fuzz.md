# Subsystem: fuzz

## fuzz/fuzz_css.c
- Doc: fuzz_root_match: Root matcher for the attribute-scoped custom-property path: a fixed <html...
- Layer: utility
- Language: c
- Symbols:
  - `fuzz_root_match` (function, line 66) `static int fuzz_root_match(void *ctx, const css_sel *sel)`
  - `LLVMFuzzerTestOneInput` (function, line 80) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/css.h`, `include/css_select.h`

## fuzz/fuzz_data_url.c
- Layer: data_access
- Language: c
- Symbols:
  - `worker` (function, line 6) `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, never
 * interpreted...`
- Depends on: `include/data_url.h`

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

## fuzz/fuzz_freebug.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 37) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/freebug.h`

## fuzz/fuzz_html_parse.c
- Layer: utility
- Language: c
- Depends on: `include/html_parse.h`

## fuzz/fuzz_image_decode.c
- Doc: poke_and_free: Touch every claimed pixel corner so the sanitizer flags an out-of-bounds extent...
- Layer: utility
- Language: c
- Symbols:
  - `poke_and_free` (function, line 21) `static void poke_and_free(img_pixels *px)`
  - `LLVMFuzzerTestOneInput` (function, line 32) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/image_decode.h`

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
  - `fz_dom_parent` (function, line 33) `static dom_node_id fz_dom_parent(void *ctx, dom_node_id n)`
  - `LLVMFuzzerTestOneInput` (function, line 40) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `FUZZ_JSDOM_MAX_NODES` (macro, line 38) `#define FUZZ_JSDOM_MAX_NODES`
- Depends on: `include/dom.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_geom.h`, `include/js_sandbox.h`, `include/js_trusted.h`, `include/url.h`, `include/web_storage.h`

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

## fuzz/fuzz_page_view.c
- Layer: presentation
- Language: c
- Depends on: `include/freedom_config.h`, `include/html_parse.h`, `include/page_view.h`

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
  - `LLVMFuzzerTestOneInput` (function, line 10) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/prefetch.h`

## fuzz/fuzz_prefs.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 21) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/prefs.h`

## fuzz/fuzz_svg_render.c
- Layer: presentation
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 24) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/svg_render.h`

## fuzz/fuzz_text_shape.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 25) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
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

## fuzz/fuzz_web_storage.c
- Layer: data_access
- Language: c
- Depends on: `include/web_storage.h`
