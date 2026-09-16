# Subsystem: fuzz

## fuzz/fuzz_css.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 61) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

## fuzz/fuzz_data_url.c
- Layer: data_access
- Language: c
- Symbols:
  - `worker` (function, line 5) `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, never
 * interpreted...`

## fuzz/fuzz_dom.c
- Layer: utility
- Language: c
- Symbols:
  - `ensure_built` (function, line 40) `static void ensure_built(void)`
  - `LLVMFuzzerTestOneInput` (function, line 47) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

## fuzz/fuzz_dom_debug.c
- Layer: utility
- Language: c
- Symbols:
  - `pass` (function, line 8) `* the measure pass (cap 0) must agree with the would-write return value.
 *
 * Build & run: make ...`

## fuzz/fuzz_download.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 30) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

## fuzz/fuzz_freebug.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 36) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

## fuzz/fuzz_html_parse.c
- Layer: utility
- Language: c

## fuzz/fuzz_image_decode.c
- Layer: utility
- Language: c
- Symbols:
  - `poke_and_free` (function, line 21) `static void poke_and_free(img_pixels *px)`
  - `LLVMFuzzerTestOneInput` (function, line 31) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

## fuzz/fuzz_js_sandbox.c
- Layer: utility
- Language: c

## fuzz/fuzz_page_view.c
- Layer: presentation
- Language: c

## fuzz/fuzz_pdf_export.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 29) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

## fuzz/fuzz_prefetch.c
- Layer: utility
- Doc: libFuzzer harness for the prefetch lookahead scanner (Hito 29). The scanned
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 9) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

## fuzz/fuzz_prefs.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 20) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

## fuzz/fuzz_svg_render.c
- Layer: presentation
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 23) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

## fuzz/fuzz_text_shape.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 24) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `FZ_CAP` (macro, line 22)

## fuzz/fuzz_tls_impersonate.c
- Layer: utility
- Language: c

## fuzz/fuzz_url.c
- Layer: utility
- Language: c
- Symbols:
  - `check_split` (function, line 29) `static void check_split(const char *url)`
  - `LLVMFuzzerTestOneInput` (function, line 57) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
