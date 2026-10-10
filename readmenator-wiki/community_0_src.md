# src

*Community 0 | 59 files | cohesion 0.75*

## Definition

This community groups 59 file(s) rooted at `src` with dominant language c (cohesion 0.75). Central symbols: `CSS_PAGE`, `DOC`, `DOM_KIND_COMMENT`, `DOM_KIND_ELEMENT`, `DOM_KIND_NONE`, `DOM_KIND_TEXT`, `DOM_MAX_HANDLES`, `DOM_NODE_NONE`. Core file: `tests/test_js_dom.c` (175 symbols). Documented purpose: — shared pure helpers (no I/O except where noted). Static inline so each compilation unit gets its own copy without adding link dependencies..

## Files

### `src` (22 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/dom.c` | c | utility | 72 | no |
| `src/freebug.c` | c | utility | 9 | no |
| `src/html_parse.c` | c | utility | 29 | no |
| `src/js_dom.c` | c | utility | 56 | no |
| `src/js_dom_ext.c` | c | utility | 3 | no |

### `include` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/dom.h` | h | utility | 28 | no |
| `include/freebug.h` | h | utility | 18 | no |
| `include/html_parse.h` | h | utility | 24 | no |
| `include/js_dom.h` | h | utility | 17 | no |
| `include/js_env.h` | h | infrastructure | 3 | no |

### `tests` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_dom.c` | c | testing | 41 | no |
| `tests/test_freebug.c` | c | testing | 13 | no |
| `tests/test_html_parse.c` | c | testing | 24 | no |
| `tests/test_js_dom.c` | c | testing | 175 | no |
| `tests/test_js_env.c` | c | testing | 26 | no |

### `fuzz` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_dom.c` | c | utility | 2 | no |
| `fuzz/fuzz_freebug.c` | c | utility | 1 | no |
| `fuzz/fuzz_html_parse.c` | c | utility | 0 | no |
| `fuzz/fuzz_js_dom.c` | c | utility | 3 | no |
| `fuzz/fuzz_js_geom.c` | c | utility | 3 | no |

*... and 39 more files in this community.*


## Key Symbols

- `ensure_built` (function, `fuzz/fuzz_dom.c:41`) `static void ensure_built(void)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_dom.c:48`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_freebug.c:37`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `fz_dom_parent` (function, `fuzz/fuzz_js_dom.c:33`) `static dom_node_id fz_dom_parent(void *ctx, dom_node_id n)`
- `FUZZ_JSDOM_MAX_NODES` (macro, `fuzz/fuzz_js_dom.c:38`) `#define FUZZ_JSDOM_MAX_NODES`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_js_dom.c:40`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `fz_parent` (struct, `fuzz/fuzz_js_geom.c:17`)
- `fz_parent_of` (function, `fuzz/fuzz_js_geom.c:20`) `static dom_node_id fz_parent_of(void *ctx, dom_node_id n)` - trigger UB, and a decoded table must re-encode to a table that decodes again.  Build & run: make fuz
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_js_geom.c:27`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `js_sandbox` (function, `fuzz/fuzz_js_sandbox.c:2`) `* libFuzzer harness for js_sandbox (Hito 3). * * Goal: arbitrary bytes treated a`
- `fz_mod` (struct, `fuzz/fuzz_js_sandbox.c:21`) - Module host for the fuzzer: every "./" specifier resolves, and "./self.js" loads the input itself (s
- `fz_resolve` (function, `fuzz/fuzz_js_sandbox.c:23`) `static int fz_resolve(void *host, const char *base, const char *spec, char *out,`
- `fz_fetch` (function, `fuzz/fuzz_js_sandbox.c:33`) `static char *fz_fetch(void *host, const char *url, size_t *len)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_js_sandbox.c:48`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `check_split` (function, `fuzz/fuzz_url.c:31`) `static void check_split(const char *url)`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_url.c:59`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_DOM_H` (macro, `include/dom.h:2`) `#define FREEDOM_DOM_H`
- `dom_status` (enum, `include/dom.h:26`)
- `dom_node_id` (type_alias, `include/dom.h:34`) `typedef uint32_t dom_node_id;` - tree. The Lexbor backend stays encapsulated: no lxb_* type appears here.  The index references the t
- `DOM_NODE_NONE` (macro, `include/dom.h:37`) `#define DOM_NODE_NONE`
- `dom_index` (type_alias, `include/dom.h:40`) `typedef struct dom_index dom_index;` - typedef enum dom_status { DOM_OK = 0, DOM_ERR_NULL_ARG,  /* doc/out was NULL, or the document had no
- `dom_free` (function, `include/dom.h:48`) `void dom_free(dom_index *idx);` - Builds the index over an already-parsed document. doc must outlive *out. doc == NULL / out == NULL =
- `dom_node_count` (function, `include/dom.h:51`) `size_t dom_node_count(const dom_index *idx);` - Builds the index over an already-parsed document. doc must outlive *out. doc == NULL / out == NULL =
- `count` (function, `include/dom.h:59`) `* match count (which may exceed cap, so the caller can size a buffer). */ size_t`
- `dom_get_by_class` (function, `include/dom.h:62`) `size_t dom_get_by_class(const dom_index *idx, const char *cls, dom_node_id *out,`
- `dom_matches` (function, `include/dom.h:91`) `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector);` - Writes up to cap matching ids (document order) into out; returns the total * match count (may exceed
- `dom_document_position` (function, `include/dom.h:101`) `size_t dom_document_position(const dom_index *idx, dom_node_id node);` - Nearest element at or above node matching the selector list, or DOM_NODE_NONE * (Element.closest). d
- `dom_precedes` (function, `include/dom.h:104`) `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);` - Nearest element at or above node matching the selector list, or DOM_NODE_NONE * (Element.closest). d
- `dom_tag_name` (function, `include/dom.h:118`) `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);` - int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b); /* Node at the given document-
- `dom_get_attribute` (function, `include/dom.h:121`) `const char *dom_get_attribute(const dom_index *idx, dom_node_id node, const char` - dom_node_id dom_node_at(const dom_index *idx, size_t position); /* --- navigation (element-only; DOM

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 130
- Cross-boundary resolved imports (EXTRACTED): 43

## Connections

- [EXTRACTED] depends_on community 3 <-> 0 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_dom_debug.c imports include/html_parse.h.
- [EXTRACTED] depends_on community 6 <-> 0 (strength 0.9): Extracted import edge crosses communities: fuzz/fuzz_page_view.c imports include/html_parse.h.
- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/freebug.h.
- [EXTRACTED] depends_on community 5 <-> 0 (strength 0.9): Extracted import edge crosses communities: src/disk_store.c imports include/util.h.
- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: src/dom.c imports include/css_chain.h.
- [EXTRACTED] depends_on community 0 <-> 7 (strength 0.9): Extracted import edge crosses communities: src/js_env.c imports include/anti_fp.h.
- [EXTRACTED] depends_on community 0 <-> 4 (strength 0.9): Extracted import edge crosses communities: src/tab.c imports include/data_url.h.

## Risks

- [cycle] `include/js_dom.h` -> `include/js_location.h` -> `include/js_dom.h`
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [layer strict] `tests/test_renderer.c` (testing) -> `include/renderer.h` (presentation)
- [dataflow UNCHECKED_ALLOC] `src/js_events.c:30` `jd_click_state_new` `s`: Result of allocator stored in `s` is never checked against NULL.
- [dataflow DEAD_STORE] `src/js_geom.c:71` `unite` `w`: `w` assigned at line 71 but never read afterwards.
- [dataflow DEAD_STORE] `src/link_nav.c:58` `ci_prefix` `hash`: `hash` assigned at line 58 but never read afterwards.
- [dataflow DEAD_STORE] `src/os_sandbox.c:154` `os_harden` `n`: `n` assigned at line 154 but never read afterwards.

## Open Questions

- Why do 55 file(s) lack file-level docs (e.g. `fuzz/fuzz_dom.c`)? What purpose do they serve?
- Can the cycle `include/js_dom.h` -> `include/js_location.h` be broken with an interface?
- What would break if the most connected file in src changed?
- Should src be split, given cohesion 0.75?

## Sources

- `fuzz/fuzz_dom.c`
- `fuzz/fuzz_freebug.c`
- `fuzz/fuzz_html_parse.c`
- `fuzz/fuzz_js_dom.c`
- `fuzz/fuzz_js_geom.c`
- `fuzz/fuzz_js_sandbox.c`
- `fuzz/fuzz_url.c`
- `fuzz/fuzz_web_storage.c`
- `include/dom.h`
- `include/freebug.h`
- `include/html_parse.h`
- `include/js_dom.h`
- `include/js_env.h`
- `include/js_geom.h`
- `include/js_location.h`
- `include/js_sandbox.h`
- `include/js_trusted.h`
- `include/link_nav.h`
- `include/os_sandbox.h`
- `include/renderer.h`
- *... and 39 more*
