# src: tab

*Community 1 | 48 files | cohesion 0.67*

## Definition

This community groups 48 file(s) rooted at `src` with dominant language c (cohesion 0.67). Central symbols: `CSS_PAGE`, `DOC`, `DOM_KIND_COMMENT`, `DOM_KIND_ELEMENT`, `DOM_KIND_NONE`, `DOM_KIND_TEXT`, `DOM_MAX_HANDLES`, `DOM_NODE_NONE`. Core file: `tests/test_js_dom.c` (268 symbols). Documented purpose: Private to js_dom.c: installs Custom Elements v1 (spec/js_custom_elements.md) on top of the document facade. Returns 0 or -1..

## Files

### `src` (23 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/dom.c` | c | utility | 75 | no |
| `src/fb_cmdline.c` | c | utility | 13 | no |
| `src/fb_panes.c` | c | utility | 10 | no |
| `src/freebug.c` | c | utility | 9 | no |
| `src/html_parse.c` | c | utility | 29 | no |
| `src/js_custom_elements.c` | c | utility | 1 | no |
| `src/js_custom_elements.h` | h | utility | 2 | yes |

### `include` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/dom.h` | h | utility | 30 | no |
| `include/fb_cmdline.h` | h | utility | 18 | no |
| `include/fb_panes.h` | h | utility | 12 | no |
| `include/freebug.h` | h | utility | 18 | no |
| `include/html_parse.h` | h | utility | 24 | no |
| `include/js_dom.h` | h | utility | 23 | no |
| `include/js_env.h` | h | infrastructure | 4 | no |

### `tests` (12 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_dom.c` | c | testing | 44 | no |
| `tests/test_fb_cmdline.c` | c | testing | 7 | no |
| `tests/test_fb_panes.c` | c | testing | 10 | no |
| `tests/test_freebug.c` | c | testing | 13 | no |
| `tests/test_html_parse.c` | c | testing | 24 | no |
| `tests/test_js_dom.c` | c | testing | 268 | no |

*... and 28 more files in this community.*


## Key Symbols

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
- `cycle` (function, `include/dom.h:169`) `* Rejects a cycle (child being an ancestor of parent). Invalid handle / self / c`
- `dom_place` (enum, `include/dom.h:187`) - Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node"
- `parent` (function, `include/dom.h:196`) `* child of parent (for the *_REF places) or an invalid handle => DOM_ERR_NULL_AR`
- `DOM_KIND_NONE` (macro, `include/dom.h:203`) `#define DOM_KIND_NONE`
- `DOM_KIND_ELEMENT` (macro, `include/dom.h:204`) `#define DOM_KIND_ELEMENT`
- `DOM_KIND_TEXT` (macro, `include/dom.h:205`) `#define DOM_KIND_TEXT`
- `DOM_KIND_COMMENT` (macro, `include/dom.h:206`) `#define DOM_KIND_COMMENT`
- `DOM_MAX_HANDLES` (macro, `include/dom.h:209`) `#define DOM_MAX_HANDLES`
- `dom_node_kind` (function, `include/dom.h:212`) `int dom_node_kind(const dom_index *idx, dom_node_id node);` - -- text and comment nodes (spec/dom.md 9) --- Character-data nodes get LAZY handles in the same aren
- `index` (function, `include/dom.h:228`) `* stays valid in the index (not freed). Invalid handle / not-a-child => DOM_ERR_`
- `length` (function, `include/dom.h:253`) `* length (no children => an owned empty string). Uses a chain of fixed-size * bl`
- `process` (function, `include/dom.h:260`) `* modules in the same process (style resolution). NULL for a bad or non-element`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 107
- Cross-boundary resolved imports (EXTRACTED): 51

## Connections

- [EXTRACTED] depends_on community 2 <-> 1 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/freebug.h.
- [EXTRACTED] depends_on community 7 <-> 1 (strength 0.9): Extracted import edge crosses communities: gui/freedom_view.c imports include/html_parse.h.
- [EXTRACTED] depends_on community 5 <-> 1 (strength 0.9): Extracted import edge crosses communities: include/page_view.h imports include/dom.h.
- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: src/dom.c imports include/css_chain.h.
- [EXTRACTED] depends_on community 1 <-> 6 (strength 0.9): Extracted import edge crosses communities: src/dom.c imports include/util.h.

## Risks

- [cycle] `include/js_dom.h` -> `include/js_location.h` -> `include/js_dom.h`
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [dataflow UNCHECKED_ALLOC] `src/js_events.c:30` `jd_click_state_new` `s`: Result of allocator stored in `s` is never checked against NULL.
- [dataflow DEAD_STORE] `src/js_geom.c:71` `unite` `w`: `w` assigned at line 71 but never read afterwards.

## Open Questions

- Why do 44 file(s) lack file-level docs (e.g. `include/dom.h`)? What purpose do they serve?
- Can the cycle `include/js_dom.h` -> `include/js_location.h` be broken with an interface?
- What would break if the most connected file in src: tab changed?
- Should src: tab be split, given cohesion 0.67?

## Sources

- `include/dom.h`
- `include/fb_cmdline.h`
- `include/fb_panes.h`
- `include/freebug.h`
- `include/html_parse.h`
- `include/js_dom.h`
- `include/js_env.h`
- `include/js_geom.h`
- `include/js_location.h`
- `include/js_sandbox.h`
- `include/js_trusted.h`
- `include/url.h`
- `include/web_storage.h`
- `src/dom.c`
- `src/fb_cmdline.c`
- `src/fb_panes.c`
- `src/freebug.c`
- `src/html_parse.c`
- `src/js_custom_elements.c`
- `src/js_custom_elements.h`
- *... and 28 more*
