# Subsystem: fuzz

## fuzz/fuzz_css.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 61) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `memcpy` (function, line 65) `memcpy(buf, data, size);`
  - `check_style` (function, line 77) `check_style(css_resolve(sh, "p", NULL, NULL, 0, inl, 0));`
  - `css_free` (function, line 102) `css_free(sh);`
  - `free` (function, line 120) `free(buf);`
- Depends on: `include/css.h`

## fuzz/fuzz_data_url.c
- Layer: data_access
- Language: c
- Symbols:
  - `worker` (function, line 5) `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, never
 * interpreted...`
  - `memcpy` (function, line 21) `memcpy(buf, data, size);`
  - `free` (function, line 37) `free(out);`
  - `abort` (function, line 39) `abort();`
- Depends on: `include/data_url.h`

## fuzz/fuzz_dom.c
- Layer: utility
- Language: c
- Symbols:
  - `ensure_built` (function, line 40) `static void ensure_built(void)`
  - `LLVMFuzzerTestOneInput` (function, line 47) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `memcpy` (function, line 54) `memcpy(sel, data, n);`
- Depends on: `include/dom.h`, `include/html_parse.h`

## fuzz/fuzz_dom_debug.c
- Layer: utility
- Language: c
- Symbols:
  - `pass` (function, line 8) `* the measure pass (cap 0) must agree with the would-write return value.
 *
 * Build & run: make ...`
  - `hp_document_free` (function, line 27) `hp_document_free(doc);`
  - `memset` (function, line 42) `memset(guard, 0xAA, sizeof guard);`
  - `rd_free` (function, line 56) `rd_free(rd);`
  - `pv_free` (function, line 58) `pv_free(v);`
- Depends on: `include/dom_debug.h`, `include/html_parse.h`, `include/page_view.h`, `include/render_doc.h`, `include/render_policy.h`

## fuzz/fuzz_download.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 30) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `memcpy` (function, line 34) `memcpy(buf, data, size);`
  - `check_name` (function, line 49) `check_name(name);`
  - `free` (function, line 62) `free(buf);`
- Depends on: `include/download.h`

## fuzz/fuzz_freebug.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 36) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `fb_buffer_init` (function, line 39) `fb_buffer_init(&b);`
  - `fb_buffer_push_loc` (function, line 62) `fb_buffer_push_loc(&b, level, txt, len, fbuf, line, -(int)len);`
  - `fb_buffer_push` (function, line 64) `fb_buffer_push(&b, level, txt, len);`
  - `check_invariants` (function, line 71) `check_invariants(&b);`
  - `fb_buffer_reset` (function, line 72) `fb_buffer_reset(&b);`
  - `fb_buffer_free` (function, line 77) `fb_buffer_free(&b);`
- Depends on: `include/freebug.h`

## fuzz/fuzz_html_parse.c
- Layer: utility
- Language: c
- Symbols:
  - `hp_free` (function, line 23) `hp_free(text);`
  - `hp_free_scripts` (function, line 39) `hp_free_scripts(scripts, nscripts);`
  - `hp_free_stylesheet_hrefs` (function, line 50) `hp_free_stylesheet_hrefs(hrefs, nsheets);`
  - `hp_document_free` (function, line 56) `hp_document_free(doc);`
- Depends on: `include/html_parse.h`

## fuzz/fuzz_image_decode.c
- Layer: utility
- Language: c
- Symbols:
  - `poke_and_free` (function, line 21) `static void poke_and_free(img_pixels *px)`
  - `LLVMFuzzerTestOneInput` (function, line 31) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `img_pixels_free` (function, line 29) `img_pixels_free(px);`
- Depends on: `include/image_decode.h`

## fuzz/fuzz_js_sandbox.c
- Layer: utility
- Language: c
- Symbols:
  - `free` (function, line 30) `free(nt);`
  - `js_eval_once` (function, line 39) `js_eval_once((const char *)data, size, &lim, &r);`
  - `js_result_free` (function, line 40) `js_result_free(&r);`
- Depends on: `include/js_sandbox.h`

## fuzz/fuzz_page_view.c
- Layer: presentation
- Language: c
- Symbols:
  - `pv_free` (function, line 45) `pv_free(v);`
  - `hp_document_free` (function, line 48) `hp_document_free(doc);`
- Depends on: `include/html_parse.h`, `include/page_view.h`

## fuzz/fuzz_pdf_export.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 29) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `memcpy` (function, line 34) `memcpy(title, data, size);`
  - `check_basename` (function, line 39) `check_basename(base);`
  - `free` (function, line 56) `free(title);`
- Depends on: `include/pdf_export.h`

## fuzz/fuzz_prefetch.c
- Layer: utility
- Doc: libFuzzer harness for the prefetch lookahead scanner (Hito 29). The scanned
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 9) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `pf_list_free` (function, line 14) `pf_list_free(&l);`
- Depends on: `include/prefetch.h`

## fuzz/fuzz_prefs.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 20) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `prefs_init` (function, line 23) `prefs_init(&p);`
  - `prefs_parse` (function, line 27) `prefs_parse((const char *)data, size, &p);`
  - `memcpy` (function, line 32) `memcpy(glued + off, data, size);`
  - `free` (function, line 34) `free(glued);`
  - `prefs_bookmark_toggle` (function, line 43) `prefs_bookmark_toggle(&p, "https://fuzz.test/", s, &added);`
  - `prefs_history_add` (function, line 45) `prefs_history_add(&p, s);`
  - `prefs_suggest` (function, line 47) `prefs_suggest(&p, s, (char *)rows, sizeof rows[0], 4);`
  - `prefs_free` (function, line 61) `prefs_free(&q);`
- Depends on: `include/prefs.h`

## fuzz/fuzz_svg_render.c
- Layer: presentation
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 23) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `free` (function, line 34) `free(im);`
  - `sv_fit` (function, line 81) `sv_fit(im, dims[a], dims[b], &sc, &ox, &oy);`
- Depends on: `include/svg_render.h`

## fuzz/fuzz_text_shape.c
- Layer: utility
- Language: c
- Symbols:
  - `LLVMFuzzerTestOneInput` (function, line 24) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `cairo_surface_destroy` (function, line 67) `cairo_surface_destroy(s);`
  - `cairo_set_source_rgb` (function, line 70) `cairo_set_source_rgb(cr, 0, 0, 0);`
  - `tsh_draw` (function, line 71) `tsh_draw(cr, &f, px, 2.0, 16.0, text, len);`
  - `FZ_CAP` (macro, line 22) `#define FZ_CAP`
- Depends on: `include/text_shape.h`

## fuzz/fuzz_tls_impersonate.c
- Layer: utility
- Language: c
- Symbols:
  - `free` (function, line 27) `free(buf);`
  - `ti_req_free` (function, line 29) `ti_req_free(&rq);`
  - `ti_resp_free` (function, line 43) `ti_resp_free(&rp);`
- Depends on: `include/tls_impersonate.h`

## fuzz/fuzz_url.c
- Layer: utility
- Language: c
- Symbols:
  - `check_split` (function, line 29) `static void check_split(const char *url)`
  - `LLVMFuzzerTestOneInput` (function, line 57) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
  - `in_bounds` (function, line 37) `in_bounds(u.protocol, u.protocol_len, url, total);`
  - `memcpy` (function, line 61) `memcpy(buf, data, size);`
  - `abort` (function, line 85) `abort();`
  - `free` (function, line 89) `free(buf);`
- Depends on: `include/link_nav.h`, `include/url.h`
