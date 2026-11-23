# src: tab

*Community 0 | 72 files | cohesion 0.72*

## Definition

This community groups 72 file(s) rooted at `src` with dominant language c (cohesion 0.72). Central symbols: `ANC_MAX_FRAGMENT`, `ANC_MAX_HANDLES`, `CI_COND_MAX`, `CI_MAX_DEPTH`, `CI_MAX_PER_PAGE`, `CI_MAX_PER_SHEET`, `CI_URL_MAX`, `CSS_PAGE`. Core file: `tests/test_js_dom.c` (280 symbols). Documented purpose: Fuzzer for anchor (spec/anchor.md) and url_split_location: a hostile document x a.

## Files

### `src` (28 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/anchor.c` | c | utility | 11 | yes |
| `src/css_import.c` | c | utility | 17 | yes |
| `src/dom.c` | c | utility | 78 | no |
| `src/html_parse.c` | c | utility | 29 | no |
| `src/js_custom_elements.c` | c | utility | 1 | no |

### `include` (19 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/anchor.h` | h | utility | 9 | no |
| `include/css_import.h` | h | utility | 12 | no |
| `include/dom.h` | h | utility | 33 | no |
| `include/html_parse.h` | h | utility | 24 | no |
| `include/js_dom.h` | h | utility | 23 | no |

### `tests` (17 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_anchor.c` | c | testing | 16 | yes |
| `tests/test_css_import.c` | c | testing | 20 | yes |
| `tests/test_dom.c` | c | testing | 45 | no |
| `tests/test_html_parse.c` | c | testing | 24 | no |
| `tests/test_js_dom.c` | c | testing | 280 | no |

### `fuzz` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_anchor.c` | c | utility | 3 | yes |
| `fuzz/fuzz_css_import.c` | c | utility | 4 | yes |
| `fuzz/fuzz_dom.c` | c | utility | 2 | no |
| `fuzz/fuzz_html_parse.c` | c | utility | 0 | no |
| `fuzz/fuzz_js_dom.c` | c | utility | 3 | no |

*... and 52 more files in this community.*


## Key Symbols

- `check_decode` (function, `fuzz/fuzz_anchor.c:15`) `static void check_decode(const char *frag)`
- `check_location` (function, `fuzz/fuzz_anchor.c:23`) `static void check_location(const char *frag)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_anchor.c:37`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `fz_out` (struct, `fuzz/fuzz_css_import.c:13`)
- `fz_emit` (function, `fuzz/fuzz_css_import.c:15`) `static int fz_emit(void *ctx, const char *s, size_t n)`
- `fz_resolve` (function, `fuzz/fuzz_css_import.c:25`) `static int fz_resolve(void *ctx, const char *base, const char *ref, char *out, s` - ctx != NULL: fail. Otherwise a hostile resolver: joins with braces and comment * openers, the worst
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_css_import.c:50`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `ensure_built` (function, `fuzz/fuzz_dom.c:41`) `static void ensure_built(void)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_dom.c:48`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `fz_dom_parent` (function, `fuzz/fuzz_js_dom.c:34`) `static dom_node_id fz_dom_parent(void *ctx, dom_node_id n)`
- `FUZZ_JSDOM_MAX_NODES` (macro, `fuzz/fuzz_js_dom.c:39`) `#define FUZZ_JSDOM_MAX_NODES`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_js_dom.c:41`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `fz_parent` (struct, `fuzz/fuzz_js_geom.c:17`)
- `fz_parent_of` (function, `fuzz/fuzz_js_geom.c:20`) `static dom_node_id fz_parent_of(void *ctx, dom_node_id n)` - trigger UB, and a decoded table must re-encode to a table that decodes again.  Build & run: make fuz
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_js_geom.c:27`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `js_sandbox` (function, `fuzz/fuzz_js_sandbox.c:2`) `* libFuzzer harness for js_sandbox (Hito 3). * * Goal: arbitrary bytes treated a`
- `fz_mod` (struct, `fuzz/fuzz_js_sandbox.c:21`) - Module host for the fuzzer: every "./" specifier resolves, and "./self.js" loads the input itself (s
- `fz_resolve` (function, `fuzz/fuzz_js_sandbox.c:23`) `static int fz_resolve(void *host, const char *base, const char *spec, char *out,`
- `fz_fetch` (function, `fuzz/fuzz_js_sandbox.c:33`) `static char *fz_fetch(void *host, const char *url, size_t *len)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_js_sandbox.c:48`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_ANCHOR_H` (macro, `include/anchor.h:2`) `#define FREEDOM_ANCHOR_H`
- `ANC_MAX_FRAGMENT` (macro, `include/anchor.h:23`) `#define ANC_MAX_FRAGMENT`
- `ANC_MAX_HANDLES` (macro, `include/anchor.h:24`) `#define ANC_MAX_HANDLES`
- `anc_kind` (enum, `include/anchor.h:26`)
- `fit` (function, `include/anchor.h:35`) `* result does not fit (out is then "" when cap > 0). */ size_t anc_percent_decod`
- `anc_collect` (function, `include/anchor.h:50`) `size_t anc_collect(const dom_index *idx, dom_node_id target, dom_node_id *out, s` - Writes target and its element subtree in preorder (*nsub handles), then the elements that follow the
- `anc_target_top` (function, `include/anchor.h:57`) `int anc_target_top(const jg_table *g, const dom_node_id *h, size_t n, size_t nsu` - The document offset of the target from a FINISHED geometry table (jg_finish): the smallest y among t
- `anc_target_box` (function, `include/anchor.h:63`) `int anc_target_box(const jg_table *g, const dom_node_id *h, size_t n, size_t nsu` - As anc_target_top, plus the target's bottom: the largest y + h among the subtree's rects (= *top whe
- `anc_scroll_for` (function, `include/anchor.h:68`) `double anc_scroll_for(double top, double max_scroll);` - The scroll offset that puts top at the top of the viewport, clamped to * [0, max_scroll]. Non-finite
- `FREEDOM_CSS_IMPORT_H` (macro, `include/css_import.h:2`) `#define FREEDOM_CSS_IMPORT_H`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 163
- Cross-boundary resolved imports (EXTRACTED): 64

## Connections

- [EXTRACTED] depends_on community 4 <-> 0 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_dom_debug.c imports include/html_parse.h.
- [EXTRACTED] depends_on community 7 <-> 0 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_url.c imports include/url.h.
- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/anchor.h.
- [EXTRACTED] depends_on community 5 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/freedom_view.c imports include/html_parse.h.

## Risks

- [cycle] `include/js_dom.h` -> `include/js_location.h` -> `include/js_dom.h`
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [layer strict] `tests/test_renderer.c` (testing) -> `include/renderer.h` (presentation)
- [dataflow UNCHECKED_ALLOC] `fuzz/fuzz_css_import.c:37` `fz_resolve` `o`: Result of allocator stored in `o` is never checked against NULL.

## Open Questions

- Why do 58 file(s) lack file-level docs (e.g. `fuzz/fuzz_dom.c`)? What purpose do they serve?
- Can the cycle `include/js_dom.h` -> `include/js_location.h` be broken with an interface?
- What would break if the most connected file in src: tab changed?
- Should src: tab be split, given cohesion 0.72?

## Sources

- `fuzz/fuzz_anchor.c`
- `fuzz/fuzz_css_import.c`
- `fuzz/fuzz_dom.c`
- `fuzz/fuzz_html_parse.c`
- `fuzz/fuzz_js_dom.c`
- `fuzz/fuzz_js_geom.c`
- `fuzz/fuzz_js_sandbox.c`
- `fuzz/fuzz_web_storage.c`
- `include/anchor.h`
- `include/css_import.h`
- `include/dom.h`
- `include/html_parse.h`
- `include/js_dom.h`
- `include/js_env.h`
- `include/js_geom.h`
- `include/js_intl.h`
- `include/js_location.h`
- `include/js_native.h`
- `include/js_sandbox.h`
- `include/js_trusted.h`
- *... and 52 more*
