# src: tab

*Community 2 | 45 files | cohesion 0.70*

## Definition

This community groups 45 file(s) rooted at `src` with dominant language c (cohesion 0.70). Central symbols: `CCM_NPROPS`, `CCM_VALUE_MAX`, `CSS_PAGE`, `DOC`, `DOM_KIND_COMMENT`, `DOM_KIND_ELEMENT`, `DOM_KIND_NONE`, `DOM_KIND_TEXT`. Core file: `tests/test_js_dom.c` (200 symbols). Documented purpose: Private to js_dom.c: installs Custom Elements v1 (spec/js_custom_elements.md) on top of the document facade. Returns 0 or -1..

## Files

### `src` (21 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `src/css_computed.c` | c | utility | 45 | no |
| `src/freebug.c` | c | utility | 9 | no |
| `src/html_parse.c` | c | utility | 29 | no |
| `src/js_custom_elements.c` | c | utility | 1 | no |
| `src/js_custom_elements.h` | h | utility | 2 | yes |
| `src/js_dom.c` | c | utility | 62 | no |
| `src/js_dom_ext.c` | c | utility | 5 | no |

### `include` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/css_computed.h` | h | utility | 6 | no |
| `include/dom.h` | h | utility | 29 | no |
| `include/freebug.h` | h | utility | 18 | no |
| `include/html_parse.h` | h | utility | 24 | no |
| `include/js_dom.h` | h | utility | 20 | no |
| `include/js_env.h` | h | infrastructure | 3 | no |
| `include/js_geom.h` | h | utility | 19 | no |

### `tests` (11 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_css_computed.c` | c | testing | 9 | no |
| `tests/test_dom.c` | c | testing | 41 | no |
| `tests/test_freebug.c` | c | testing | 13 | no |
| `tests/test_html_parse.c` | c | testing | 24 | no |
| `tests/test_js_dom.c` | c | testing | 200 | no |
| `tests/test_js_env.c` | c | testing | 26 | no |

*... and 25 more files in this community.*


## Key Symbols

- `FREEDOM_CSS_COMPUTED_H` (macro, `include/css_computed.h:2`) `#define FREEDOM_CSS_COMPUTED_H`
- `CCM_VALUE_MAX` (macro, `include/css_computed.h:17`) `#define CCM_VALUE_MAX`
- `ccm_input` (struct, `include/css_computed.h:19`)
- `ccm_get` (function, `include/css_computed.h:29`) `size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap);` - Writes the computed value of the kebab-case property `prop` into out (cap bytes, NUL terminated). Re
- `ccm_property_count` (function, `include/css_computed.h:32`) `size_t ccm_property_count(void);` - Writes the computed value of the kebab-case property `prop` into out (cap bytes, NUL terminated). Re
- `ccm_property_name` (function, `include/css_computed.h:33`) `const char *ccm_property_name(size_t i);`
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
- `dom_attribute_names` (function, `include/dom.h:128`) `size_t dom_attribute_names(const dom_index *idx, dom_node_id node, const char **` - Qualified names of node's attributes, in document order, written to names[] (borrowed, valid while i
- `dom_text_content` (function, `include/dom.h:133`) `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len` - Concatenated text content of node's subtree (borrowed, valid while idx/doc are * alive), or NULL. *l
- `dom_document_title` (function, `include/dom.h:136`) `const char *dom_document_title(const dom_index *idx, size_t *len);` - Concatenated text content of node's subtree (borrowed, valid while idx/doc are * alive), or NULL. *l
- `cycle` (function, `include/dom.h:164`) `* Rejects a cycle (child being an ancestor of parent). Invalid handle / self / c`
- `dom_place` (enum, `include/dom.h:182`) - Where dom_move_children places the moved nodes (insertAdjacent* needs all four: * "after this node"
- `parent` (function, `include/dom.h:191`) `* child of parent (for the *_REF places) or an invalid handle => DOM_ERR_NULL_AR`
- `DOM_KIND_NONE` (macro, `include/dom.h:198`) `#define DOM_KIND_NONE`
- `DOM_KIND_ELEMENT` (macro, `include/dom.h:199`) `#define DOM_KIND_ELEMENT`
- `DOM_KIND_TEXT` (macro, `include/dom.h:200`) `#define DOM_KIND_TEXT`
- `DOM_KIND_COMMENT` (macro, `include/dom.h:201`) `#define DOM_KIND_COMMENT`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 102
- Cross-boundary resolved imports (EXTRACTED): 44

## Connections

- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/freebug.h.
- [EXTRACTED] depends_on community 2 <-> 1 (strength 0.9): Extracted import edge crosses communities: include/css_computed.h imports include/css.h.
- [EXTRACTED] depends_on community 5 <-> 2 (strength 0.9): Extracted import edge crosses communities: include/page_view.h imports include/dom.h.
- [EXTRACTED] depends_on community 3 <-> 2 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/html_parse.h.
- [EXTRACTED] depends_on community 2 <-> 4 (strength 0.9): Extracted import edge crosses communities: src/html_parse.c imports include/util.h.
- [EXTRACTED] depends_on community 2 <-> 6 (strength 0.9): Extracted import edge crosses communities: src/js_env.c imports include/anti_fp.h.

## Risks

- [cycle] `include/js_dom.h` -> `include/js_location.h` -> `include/js_dom.h`
- [layer strict] `gui/browser_ui.c` (presentation) -> `include/web_storage.h` (data_access)
- [dataflow UNCHECKED_ALLOC] `src/js_events.c:30` `jd_click_state_new` `s`: Result of allocator stored in `s` is never checked against NULL.
- [dataflow DEAD_STORE] `src/js_geom.c:71` `unite` `w`: `w` assigned at line 71 but never read afterwards.

## Open Questions

- Why do 41 file(s) lack file-level docs (e.g. `include/css_computed.h`)? What purpose do they serve?
- Can the cycle `include/js_dom.h` -> `include/js_location.h` be broken with an interface?
- What would break if the most connected file in src: tab changed?
- Should src: tab be split, given cohesion 0.70?

## Sources

- `include/css_computed.h`
- `include/dom.h`
- `include/freebug.h`
- `include/html_parse.h`
- `include/js_dom.h`
- `include/js_env.h`
- `include/js_geom.h`
- `include/js_location.h`
- `include/js_sandbox.h`
- `include/js_trusted.h`
- `include/tab.h`
- `include/url.h`
- `include/web_storage.h`
- `src/css_computed.c`
- `src/freebug.c`
- `src/html_parse.c`
- `src/js_custom_elements.c`
- `src/js_custom_elements.h`
- `src/js_dom.c`
- `src/js_dom_ext.c`
- *... and 25 more*
