# src: tab

*Community 2 | 53 files | cohesion 0.70*

## Definition

This community groups 53 file(s) rooted at `src` with dominant language c (cohesion 0.70). Central symbols: `CI_COND_MAX`, `CI_MAX_DEPTH`, `CI_MAX_PER_PAGE`, `CI_MAX_PER_SHEET`, `CI_URL_MAX`, `CSS_PAGE`, `DOC`, `DOM_KIND_COMMENT`. Core file: `tests/test_js_dom.c` (277 symbols). Documented purpose: css_import -- @import prelude reader (spec/css_import.md). Pure: no I/O, no allocation, no global state. Every read is bounded by len..

## Files

### `src` (24 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/css_import.c` | c | utility | 17 | yes |
| `src/fb_cmdline.c` | c | utility | 13 | no |
| `src/freebug.c` | c | utility | 9 | no |
| `src/html_parse.c` | c | utility | 29 | no |
| `src/js_custom_elements.c` | c | utility | 1 | no |
| `src/js_custom_elements.h` | h | utility | 2 | yes |
| `src/js_dom.c` | c | utility | 64 | no |

### `include` (15 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/css_import.h` | h | utility | 12 | no |
| `include/dom.h` | h | utility | 32 | no |
| `include/fb_cmdline.h` | h | utility | 18 | no |
| `include/freebug.h` | h | utility | 18 | no |
| `include/html_parse.h` | h | utility | 24 | no |
| `include/js_dom.h` | h | utility | 23 | no |
| `include/js_env.h` | h | infrastructure | 4 | no |

### `tests` (14 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_css_import.c` | c | testing | 20 | yes |
| `tests/test_dom.c` | c | testing | 45 | no |
| `tests/test_fb_cmdline.c` | c | testing | 7 | no |
| `tests/test_freebug.c` | c | testing | 13 | no |
| `tests/test_html_parse.c` | c | testing | 24 | no |
| `tests/test_js_dom.c` | c | testing | 277 | no |

*... and 33 more files in this community.*


## Key Symbols

- `FREEDOM_CSS_IMPORT_H` (macro, `include/css_import.h:2`) `#define FREEDOM_CSS_IMPORT_H`
- `CI_URL_MAX` (macro, `include/css_import.h:19`) `#define CI_URL_MAX`
- `CI_COND_MAX` (macro, `include/css_import.h:20`) `#define CI_COND_MAX`
- `CI_MAX_DEPTH` (macro, `include/css_import.h:21`) `#define CI_MAX_DEPTH`
- `CI_MAX_PER_PAGE` (macro, `include/css_import.h:22`) `#define CI_MAX_PER_PAGE`
- `CI_MAX_PER_SHEET` (macro, `include/css_import.h:23`) `#define CI_MAX_PER_SHEET`
- `url` (type_alias, `include/css_import.h:24`) `typedef struct ci_import { char url[CI_URL_MAX];` - css_import -- pure reader of a stylesheet's @import prelude (spec/css_import.md).  No I/O, no alloca
- `ci_import` (struct, `include/css_import.h:25`)
- `ci_scan` (function, `include/css_import.h:36`) `size_t ci_scan(const char *css, size_t len, ci_import *out, size_t cap);` - Reads the leading @import rules of css[0,len) into out (at most cap). Skips whitespace, comments, @c
- `ci_wrap` (function, `include/css_import.h:41`) `int ci_wrap(const ci_import *im, char *open, size_t ocap, char *close, size_t cc` - Builds the wrapper for one import: open = "@layer N {@supports (S) {@media M {" (only the parts pres
- `ci_balanced` (function, `include/css_import.h:45`) `int ci_balanced(const char *css, size_t len);` - 1 iff every comment and string in css[0,len) terminates and the braces outside * them never go negat
- `url` (function, `include/css_import.h:55`) `* rewritten to url("ABS"), ABS = resolve(base, ref) (spec/css_import.md, "Rebase`
- `FREEDOM_DOM_H` (macro, `include/dom.h:2`) `#define FREEDOM_DOM_H`
- `dom_status` (enum, `include/dom.h:26`)
- `dom_node_id` (type_alias, `include/dom.h:34`) `typedef uint32_t dom_node_id;` - tree. The Lexbor backend stays encapsulated: no lxb_* type appears here.  The index references the t
- `DOM_NODE_NONE` (macro, `include/dom.h:37`) `#define DOM_NODE_NONE`
- `dom_index` (type_alias, `include/dom.h:40`) `typedef struct dom_index dom_index;` - typedef enum dom_status { DOM_OK = 0, DOM_ERR_NULL_ARG,  /* doc/out was NULL, or the document had no
- `dom_free` (function, `include/dom.h:48`) `void dom_free(dom_index *idx);` - Builds the index over an already-parsed document. doc must outlive *out. doc == NULL / out == NULL =
- `dom_node_count` (function, `include/dom.h:51`) `size_t dom_node_count(const dom_index *idx);` - Builds the index over an already-parsed document. doc must outlive *out. doc == NULL / out == NULL =
- `tree` (function, `include/dom.h:59`) `* tree (the index only grows, so a node a script removed is still registered and`
- `count` (function, `include/dom.h:64`) `* match count (which may exceed cap, so the caller can size a buffer). */ size_t`
- `dom_get_by_class` (function, `include/dom.h:67`) `size_t dom_get_by_class(const dom_index *idx, const char *cls, dom_node_id *out,`
- `dom_matches` (function, `include/dom.h:96`) `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector);` - Writes up to cap matching ids (document order) into out; returns the total * match count (may exceed
- `dom_document_position` (function, `include/dom.h:106`) `size_t dom_document_position(const dom_index *idx, dom_node_id node);` - Nearest element at or above node matching the selector list, or DOM_NODE_NONE * (Element.closest). d
- `dom_precedes` (function, `include/dom.h:109`) `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);` - Nearest element at or above node matching the selector list, or DOM_NODE_NONE * (Element.closest). d
- `dom_tag_name` (function, `include/dom.h:123`) `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);` - int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b); /* Node at the given document-
- `dom_get_attribute` (function, `include/dom.h:126`) `const char *dom_get_attribute(const dom_index *idx, dom_node_id node, const char` - dom_node_id dom_node_at(const dom_index *idx, size_t position); /* --- navigation (element-only; DOM
- `dom_attribute_names` (function, `include/dom.h:133`) `size_t dom_attribute_names(const dom_index *idx, dom_node_id node, const char **` - Qualified names of node's attributes, in document order, written to names[] (borrowed, valid while i
- `dom_text_content` (function, `include/dom.h:138`) `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len` - Concatenated text content of node's subtree (borrowed, valid while idx/doc are * alive), or NULL. *l
- `dom_document_title` (function, `include/dom.h:141`) `const char *dom_document_title(const dom_index *idx, size_t *len);` - Concatenated text content of node's subtree (borrowed, valid while idx/doc are * alive), or NULL. *l

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 127
- Cross-boundary resolved imports (EXTRACTED): 56

## Connections

- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/freebug.h.
- [EXTRACTED] depends_on community 4 <-> 2 (strength 0.9): Extracted import edge crosses communities: include/page_view.h imports include/dom.h.
- [EXTRACTED] depends_on community 8 <-> 2 (strength 0.9): Extracted import edge crosses communities: include/tab.h imports include/freebug.h.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: src/fb_cmdline.c imports include/fb_panes.h.

## Risks

- [cycle] `include/js_dom.h` -> `include/js_location.h` -> `include/js_dom.h`
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [dataflow UNCHECKED_ALLOC] `src/js_events.c:31` `jd_click_state_new` `s`: Result of allocator stored in `s` is never checked against NULL.

## Open Questions

- Why do 47 file(s) lack file-level docs (e.g. `include/css_import.h`)? What purpose do they serve?
- Can the cycle `include/js_dom.h` -> `include/js_location.h` be broken with an interface?
- What would break if the most connected file in src: tab changed?
- Should src: tab be split, given cohesion 0.70?

## Sources

- `include/css_import.h`
- `include/dom.h`
- `include/fb_cmdline.h`
- `include/freebug.h`
- `include/html_parse.h`
- `include/js_dom.h`
- `include/js_env.h`
- `include/js_geom.h`
- `include/js_intl.h`
- `include/js_location.h`
- `include/js_native.h`
- `include/js_sandbox.h`
- `include/js_trusted.h`
- `include/url.h`
- `include/web_storage.h`
- `src/css_import.c`
- `src/fb_cmdline.c`
- `src/freebug.c`
- `src/html_parse.c`
- `src/js_custom_elements.c`
- *... and 33 more*
