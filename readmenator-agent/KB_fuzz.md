# Subsystem: fuzz

## fuzz/fuzz_css.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 62) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/css.h`

## fuzz/fuzz_data_url.c
- Layer: data_access
- Language: c
- Symbols:
  - `worker` (function, line 5) `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, never
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
- Layer: utility
- Language: c
- Symbols:
  - `poke_and_free` (function, line 21) `static void poke_and_free(img_pixels *px)`
  - `LLVMFuzzerTestOneInput` (function, line 32) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/image_decode.h`

## fuzz/fuzz_js_sandbox.c
- Layer: utility
- Language: c
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
- Layer: utility
- Doc: libFuzzer harness for the prefetch lookahead scanner (Hito 29). The scanned
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
  - `check_split` (function, line 30) `static void check_split(const char *url)`
  - `LLVMFuzzerTestOneInput` (function, line 58) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- Depends on: `include/link_nav.h`, `include/url.h`
