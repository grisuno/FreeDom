# `src/dom.c`

> Source: [src/dom.c:1](../../src/dom.c#L1) | language `c` | coverage 25.0% | [API index](../index.md)

## Contents

- **Structs:** [`sm_entry`](#sm_entry), [`strmap`](#strmap), [`pm_entry`](#pm_entry), [`ptrmap`](#ptrmap), [`dom_index`](#dom_index), [`ih_block`](#ih_block), [`ih_acc`](#ih_acc)
- **Functions:** [`dom_build`](#dom_build), [`dom_free`](#dom_free), [`dom_mutation_count`](#dom_mutation_count), [`dom_node_count`](#dom_node_count), [`dom_get_element_by_id`](#dom_get_element_by_id), [`dom_get_connected_by_id`](#dom_get_connected_by_id), [`dom_get_by_tag`](#dom_get_by_tag), [`dom_get_by_class`](#dom_get_by_class), [`count`](#count), [`dom_query_selector`](#dom_query_selector), [`dom_query_selector_all`](#dom_query_selector_all), [`dom_matches`](#dom_matches), [`dom_closest`](#dom_closest), [`dom_document_position`](#dom_document_position), [`dom_precedes`](#dom_precedes), [`dom_node_at`](#dom_node_at), [`dom_parent`](#dom_parent), [`dom_first_child`](#dom_first_child), [`dom_next_sibling`](#dom_next_sibling), [`dom_tag_name`](#dom_tag_name), [`dom_get_attribute`](#dom_get_attribute), [`dom_attribute_names`](#dom_attribute_names), [`dom_text_content`](#dom_text_content), [`dom_document_title`](#dom_document_title), [`dom_set_text_content`](#dom_set_text_content), [`dom_set_document_title`](#dom_set_document_title), [`dom_create_element`](#dom_create_element), [`dom_append_child`](#dom_append_child), [`dom_remove_child`](#dom_remove_child), [`dom_set_attribute`](#dom_set_attribute), [`dom_remove_attribute`](#dom_remove_attribute), [`dom_set_inner_html`](#dom_set_inner_html), [`dom_get_inner_html`](#dom_get_inner_html), [`dom_insert_before`](#dom_insert_before), [`dom_clone_node`](#dom_clone_node), [`dom_move_children`](#dom_move_children), [`dom_node_kind`](#dom_node_kind), [`dom_child_node`](#dom_child_node), [`dom_sibling_node`](#dom_sibling_node), [`dom_create_char_node`](#dom_create_char_node), [`dom_native_node`](#dom_native_node)
- **Macros:** [`_POSIX_C_SOURCE`](#_posix_c_source), [`DOM_QS_MAX_SELECTORS`](#dom_qs_max_selectors), [`IH_BLOCK_SIZE`](#ih_block_size)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class sm_entry
    <<struct>> sm_entry
    class strmap
    <<struct>> strmap
    class pm_entry
    <<struct>> pm_entry
    class ptrmap
    <<struct>> ptrmap
    class dom_index
    <<struct>> dom_index
    class ih_block
    <<struct>> ih_block
    class ih_acc
    <<struct>> ih_acc
```

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_dom_c__dom_build(["dom_build"])
    n_src_dom_c__dom_free(["dom_free"])
    n_src_dom_c__dom_insert_before(["dom_insert_before"])
    n_src_dom_c__dom_append_child(["dom_append_child"])
    n_include_html_parse_h__hp_document_root["html_parse.hp_document_root"]
    n_src_dom_c__dom_document_position(["dom_document_position"])
    n_include_dom_h__valid["dom.valid"]
    n_src_dom_c__dom_precedes(["dom_precedes"])
    n_src_dom_c__dom_parent(["dom_parent"])
    n_src_dom_c__dom_first_child(["dom_first_child"])
    n_src_dom_c__dom_next_sibling(["dom_next_sibling"])
    n_src_dom_c__dom_get_attribute(["dom_get_attribute"])
    n_src_html_parse_c__lxb_dom_element_has_attribute["html_parse.lxb_dom_element_has_attribute"]
    n_src_dom_c__dom_text_content(["dom_text_content"])
    n_src_dom_c__dom_set_text_content(["dom_set_text_content"])
    n_src_dom_c__dom_remove_child(["dom_remove_child"])
    n_src_dom_c__dom_clone_node(["dom_clone_node"])
    n_src_dom_c__dom_move_children(["dom_move_children"])
    n_src_dom_c__dom_node_kind(["dom_node_kind"])
    n_src_dom_c__dom_sibling_node(["dom_sibling_node"])
    n_src_dom_c__dom_build --> n_src_dom_c__dom_free
    n_src_dom_c__dom_insert_before --> n_src_dom_c__dom_append_child
    n_src_dom_c__dom_build -.-> n_include_html_parse_h__hp_document_root
    n_src_dom_c__dom_document_position -.-> n_include_dom_h__valid
    n_src_dom_c__dom_precedes -.-> n_include_dom_h__valid
    n_src_dom_c__dom_parent -.-> n_include_dom_h__valid
    n_src_dom_c__dom_first_child -.-> n_include_dom_h__valid
    n_src_dom_c__dom_next_sibling -.-> n_include_dom_h__valid
    n_src_dom_c__dom_get_attribute -.-> n_src_html_parse_c__lxb_dom_element_has_attribute
    n_src_dom_c__dom_text_content -.-> n_include_dom_h__valid
    n_src_dom_c__dom_set_text_content -.-> n_include_dom_h__valid
    n_src_dom_c__dom_append_child -.-> n_include_dom_h__valid
    n_src_dom_c__dom_remove_child -.-> n_include_dom_h__valid
    n_src_dom_c__dom_insert_before -.-> n_include_dom_h__valid
    n_src_dom_c__dom_clone_node -.-> n_include_dom_h__valid
    n_src_dom_c__dom_move_children -.-> n_include_dom_h__valid
    n_src_dom_c__dom_node_kind -.-> n_include_dom_h__valid
    n_src_dom_c__dom_sibling_node -.-> n_include_dom_h__valid
```

## Structs

<a id="sm_entry"></a>

### `sm_entry`

`struct` | [src/dom.c:55](../../src/dom.c#L55)

```c
typedef struct sm_entry
```

---

<a id="strmap"></a>

### `strmap`

`struct` | [src/dom.c:64](../../src/dom.c#L64)

```c
typedef struct strmap
```

---

<a id="pm_entry"></a>

### `pm_entry`

`struct` | [src/dom.c:154](../../src/dom.c#L154)

```c
typedef struct pm_entry
```

---

<a id="ptrmap"></a>

### `ptrmap`

`struct` | [src/dom.c:160](../../src/dom.c#L160)

```c
typedef struct ptrmap
```

---

<a id="dom_index"></a>

### `dom_index`

`struct` | [src/dom.c:220](../../src/dom.c#L220)

```c
struct dom_index
```

---

<a id="ih_block"></a>

### `ih_block`

`struct` | [src/dom.c:862](../../src/dom.c#L862)

```c
typedef struct ih_block
```

---

<a id="ih_acc"></a>

### `ih_acc`

`struct` | [src/dom.c:867](../../src/dom.c#L867)

```c
typedef struct ih_acc
```

---

## Functions

<a id="dom_build"></a>

### `dom_build`

`function` | [src/dom.c:292](../../src/dom.c#L292)

```c
dom_status dom_build(const hp_document *doc, dom_index **out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `doc` | `hp_document *` |  |  |
| `out` | `dom_index **` |  |  |

**Returns:** `dom_status`

*Calls:* [`hp_document_root`](include.html_parse.h.md#hp_document_root), [`dom_free`](#dom_free)

*Called by:* [`run_js`](src.tab.c.md#run_js)

---

<a id="dom_free"></a>

### `dom_free`

`function` | [src/dom.c:333](../../src/dom.c#L333)

```c
void dom_free(dom_index *idx)
```

Idempotent; safe on NULL and safe to call twice.

Does not free the tree.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |

> **Inherited:** Documentation from [`dom_free`](#dom_free) (include/dom.h:48).

*Called by:* [`dom_build`](#dom_build)

---

<a id="dom_mutation_count"></a>

### `dom_mutation_count`

`function` | [src/dom.c:345](../../src/dom.c#L345)

```c
uint64_t dom_mutation_count(const dom_index *idx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |

**Returns:** `uint64_t`

---

<a id="dom_node_count"></a>

### `dom_node_count`

`function` | [src/dom.c:349](../../src/dom.c#L349)

```c
size_t dom_node_count(const dom_index *idx)
```

Number of element nodes indexed.

NULL idx => 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`dom_node_count`](#dom_node_count) (include/dom.h:51).

---

<a id="dom_get_element_by_id"></a>

### `dom_get_element_by_id`

`function` | [src/dom.c:363](../../src/dom.c#L363)

```c
dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `id` | `char *` |  |  |

**Returns:** `dom_node_id`

---

<a id="dom_get_connected_by_id"></a>

### `dom_get_connected_by_id`

`function` | [src/dom.c:369](../../src/dom.c#L369)

```c
dom_node_id dom_get_connected_by_id(const dom_index *idx, const char *id)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `id` | `char *` |  |  |

**Returns:** `dom_node_id`

---

<a id="dom_get_by_tag"></a>

### `dom_get_by_tag`

`function` | [src/dom.c:399](../../src/dom.c#L399)

```c
size_t dom_get_by_tag(const dom_index *idx, const char *tag, dom_node_id *out, size_t cap)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `tag` | `char *` |  |  |
| `out` | `dom_node_id *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

*Called by:* [`jd_process_iframes`](src.js_embed.c.md#jd_process_iframes), [`run`](src.tab.c.md#run)

---

<a id="dom_get_by_class"></a>

### `dom_get_by_class`

`function` | [src/dom.c:408](../../src/dom.c#L408)

```c
size_t dom_get_by_class(const dom_index *idx, const char *cls, dom_node_id *out, size_t cap)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `cls` | `char *` |  |  |
| `out` | `dom_node_id *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

---

<a id="count"></a>

### `count`

`function` | [src/dom.c:472](../../src/dom.c#L472)

```c
* count (may exceed cap), and returns DOM_NODE_NONE. */ static dom_node_id qs_walk(const dom_inde...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cap` | `may exceed` |  |  |

**Returns:** `*`

---

<a id="dom_query_selector"></a>

### `dom_query_selector`

`function` | [src/dom.c:502](../../src/dom.c#L502)

```c
dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root, const char *selector)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `root` | `dom_node_id` |  |  |
| `selector` | `char *` |  |  |

**Returns:** `dom_node_id`

---

<a id="dom_query_selector_all"></a>

### `dom_query_selector_all`

`function` | [src/dom.c:511](../../src/dom.c#L511)

```c
size_t dom_query_selector_all(const dom_index *idx, dom_node_id root, const char *selector, dom_node_id *out, size_t cap)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `root` | `dom_node_id` |  |  |
| `selector` | `char *` |  |  |
| `out` | `dom_node_id *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

*Called by:* [`JD_QSA_INLINE`](src.js_dom.c.md#jd_qsa_inline)

---

<a id="dom_matches"></a>

### `dom_matches`

`function` | [src/dom.c:522](../../src/dom.c#L522)

```c
int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)
```

Nonzero iff node itself matches the selector list (Element.matches).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `selector` | `char *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`dom_matches`](#dom_matches) (include/dom.h:96).

---

<a id="dom_closest"></a>

### `dom_closest`

`function` | [src/dom.c:531](../../src/dom.c#L531)

```c
dom_node_id dom_closest(const dom_index *idx, dom_node_id node, const char *selector)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `selector` | `char *` |  |  |

**Returns:** `dom_node_id`

---

<a id="dom_document_position"></a>

### `dom_document_position`

`function` | [src/dom.c:547](../../src/dom.c#L547)

```c
size_t dom_document_position(const dom_index *idx, dom_node_id node)
```

0-based document-order position of node, or 0 if node is invalid.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`dom_document_position`](#dom_document_position) (include/dom.h:106).

*Calls:* [`valid`](include.dom.h.md#valid)

---

<a id="dom_precedes"></a>

### `dom_precedes`

`function` | [src/dom.c:552](../../src/dom.c#L552)

```c
int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)
```

Nonzero iff a precedes b in document order.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `a` | `dom_node_id` |  |  |
| `b` | `dom_node_id` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`dom_precedes`](#dom_precedes) (include/dom.h:109).

*Calls:* [`valid`](include.dom.h.md#valid)

---

<a id="dom_node_at"></a>

### `dom_node_at`

`function` | [src/dom.c:557](../../src/dom.c#L557)

```c
dom_node_id dom_node_at(const dom_index *idx, size_t position)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `position` | `size_t` |  |  |

**Returns:** `dom_node_id`

---

<a id="dom_parent"></a>

### `dom_parent`

`function` | [src/dom.c:562](../../src/dom.c#L562)

```c
dom_node_id dom_parent(const dom_index *idx, dom_node_id node)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |

**Returns:** `dom_node_id`

*Calls:* [`valid`](include.dom.h.md#valid)

---

<a id="dom_first_child"></a>

### `dom_first_child`

`function` | [src/dom.c:572](../../src/dom.c#L572)

```c
dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |

**Returns:** `dom_node_id`

*Calls:* [`valid`](include.dom.h.md#valid)

*Called by:* [`jd_process_iframes`](src.js_embed.c.md#jd_process_iframes)

---

<a id="dom_next_sibling"></a>

### `dom_next_sibling`

`function` | [src/dom.c:580](../../src/dom.c#L580)

```c
dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |

**Returns:** `dom_node_id`

*Calls:* [`valid`](include.dom.h.md#valid)

*Called by:* [`jd_process_iframes`](src.js_embed.c.md#jd_process_iframes)

---

<a id="dom_tag_name"></a>

### `dom_tag_name`

`function` `const` | [src/dom.c:588](../../src/dom.c#L588)

```c
const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)
```

Lowercase qualified tag name, or NULL. *len (optional) excludes the NUL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `len` | `size_t *` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`dom_tag_name`](#dom_tag_name) (include/dom.h:123).

---

<a id="dom_get_attribute"></a>

### `dom_get_attribute`

`function` `const` | [src/dom.c:599](../../src/dom.c#L599)

```c
const char *dom_get_attribute(const dom_index *idx, dom_node_id node, const char *name, size_t *len)
```

Attribute value by name, or NULL if absent. *len (optional) excludes NUL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `name` | `char *` |  |  |
| `len` | `size_t *` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`dom_get_attribute`](#dom_get_attribute) (include/dom.h:126).

*Calls:* [`lxb_dom_element_has_attribute`](src.html_parse.c.md#lxb_dom_element_has_attribute)

---

<a id="dom_attribute_names"></a>

### `dom_attribute_names`

`function` | [src/dom.c:621](../../src/dom.c#L621)

```c
size_t dom_attribute_names(const dom_index *idx, dom_node_id node, const char **names, size_t *lens, size_t cap)
```

Qualified names of node's attributes, in document order, written to names[] (borrowed, valid while idx/doc are alive) with matching lens[] (excluding NUL).

Writes at most cap entries; returns the total attribute count (which may exceed cap, so the caller can tell it truncated). node without attributes returns 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `names` | `char **` |  |  |
| `lens` | `size_t *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`dom_attribute_names`](#dom_attribute_names) (include/dom.h:133).

---

<a id="dom_text_content"></a>

### `dom_text_content`

`function` `const` | [src/dom.c:639](../../src/dom.c#L639)

```c
const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)
```

Concatenated text content of node's subtree (borrowed, valid while idx/doc are alive), or NULL. *len (optional) excludes the NUL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `len` | `size_t *` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`dom_text_content`](#dom_text_content) (include/dom.h:138).

*Calls:* [`valid`](include.dom.h.md#valid)

---

<a id="dom_document_title"></a>

### `dom_document_title`

`function` `const` | [src/dom.c:649](../../src/dom.c#L649)

```c
const char *dom_document_title(const dom_index *idx, size_t *len)
```

Current document <title> text (borrowed), or NULL. *len excludes the NUL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `len` | `size_t *` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`dom_document_title`](#dom_document_title) (include/dom.h:141).

---

<a id="dom_set_text_content"></a>

### `dom_set_text_content`

`function` | [src/dom.c:662](../../src/dom.c#L662)

```c
dom_status dom_set_text_content(dom_index *idx, dom_node_id node, const char *text, size_t len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `text` | `char *` |  |  |
| `len` | `size_t` |  |  |

**Returns:** `dom_status`

*Calls:* [`valid`](include.dom.h.md#valid)

---

<a id="dom_set_document_title"></a>

### `dom_set_document_title`

`function` | [src/dom.c:697](../../src/dom.c#L697)

```c
dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `text` | `char *` |  |  |
| `len` | `size_t` |  |  |

**Returns:** `dom_status`

---

<a id="dom_create_element"></a>

### `dom_create_element`

`function` | [src/dom.c:727](../../src/dom.c#L727)

```c
dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `tag` | `char *` |  |  |
| `out_id` | `dom_node_id *` |  |  |

**Returns:** `dom_status`

*Called by:* [`jd_process_iframes`](src.js_embed.c.md#jd_process_iframes)

---

<a id="dom_append_child"></a>

### `dom_append_child`

`function` | [src/dom.c:747](../../src/dom.c#L747)

```c
dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `parent` | `dom_node_id` |  |  |
| `child` | `dom_node_id` |  |  |

**Returns:** `dom_status`

*Calls:* [`valid`](include.dom.h.md#valid)

*Called by:* [`dom_insert_before`](#dom_insert_before), [`jd_process_iframes`](src.js_embed.c.md#jd_process_iframes)

---

<a id="dom_remove_child"></a>

### `dom_remove_child`

`function` | [src/dom.c:762](../../src/dom.c#L762)

```c
dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `parent` | `dom_node_id` |  |  |
| `child` | `dom_node_id` |  |  |

**Returns:** `dom_status`

*Calls:* [`valid`](include.dom.h.md#valid)

---

<a id="dom_set_attribute"></a>

### `dom_set_attribute`

`function` | [src/dom.c:771](../../src/dom.c#L771)

```c
dom_status dom_set_attribute(dom_index *idx, dom_node_id node, const char *name, const char *value)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `name` | `char *` |  |  |
| `value` | `char *` |  |  |

**Returns:** `dom_status`

*Called by:* [`jd_process_iframes`](src.js_embed.c.md#jd_process_iframes)

---

<a id="dom_remove_attribute"></a>

### `dom_remove_attribute`

`function` | [src/dom.c:801](../../src/dom.c#L801)

```c
dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `name` | `char *` |  |  |

**Returns:** `dom_status`

---

<a id="dom_set_inner_html"></a>

### `dom_set_inner_html`

`function` | [src/dom.c:821](../../src/dom.c#L821)

```c
dom_status dom_set_inner_html(dom_index *idx, dom_node_id node, const char *html, size_t len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `html` | `char *` |  |  |
| `len` | `size_t` |  |  |

**Returns:** `dom_status`

---

<a id="dom_get_inner_html"></a>

### `dom_get_inner_html`

`function` | [src/dom.c:929](../../src/dom.c#L929)

```c
dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node, char **out, size_t *out_len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `out` | `char **` |  |  |
| `out_len` | `size_t *` |  |  |

**Returns:** `dom_status`

---

<a id="dom_insert_before"></a>

### `dom_insert_before`

`function` | [src/dom.c:959](../../src/dom.c#L959)

```c
dom_status dom_insert_before(dom_index *idx, dom_node_id parent, dom_node_id child, dom_node_id ref)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `parent` | `dom_node_id` |  |  |
| `child` | `dom_node_id` |  |  |
| `ref` | `dom_node_id` |  |  |

**Returns:** `dom_status`

*Calls:* [`valid`](include.dom.h.md#valid), [`dom_append_child`](#dom_append_child)

---

<a id="dom_clone_node"></a>

### `dom_clone_node`

`function` | [src/dom.c:977](../../src/dom.c#L977)

```c
dom_status dom_clone_node(dom_index *idx, dom_node_id node, int deep, dom_node_id *out_id)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `deep` | `int` |  |  |
| `out_id` | `dom_node_id *` |  |  |

**Returns:** `dom_status`

*Calls:* [`valid`](include.dom.h.md#valid)

---

<a id="dom_move_children"></a>

### `dom_move_children`

`function` | [src/dom.c:991](../../src/dom.c#L991)

```c
dom_status dom_move_children(dom_index *idx, dom_node_id src, dom_node_id parent, dom_place where, dom_node_id ref)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `src` | `dom_node_id` |  |  |
| `parent` | `dom_node_id` |  |  |
| `where` | `dom_place` |  |  |
| `ref` | `dom_node_id` |  |  |

**Returns:** `dom_status`

*Calls:* [`valid`](include.dom.h.md#valid)

---

<a id="dom_node_kind"></a>

### `dom_node_kind`

`function` | [src/dom.c:1044](../../src/dom.c#L1044)

```c
int dom_node_kind(const dom_index *idx, dom_node_id node)
```

DOM_KIND_* of node, DOM_KIND_NONE for an invalid handle.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`dom_node_kind`](#dom_node_kind) (include/dom.h:219).

*Calls:* [`valid`](include.dom.h.md#valid)

---

<a id="dom_child_node"></a>

### `dom_child_node`

`function` | [src/dom.c:1048](../../src/dom.c#L1048)

```c
dom_node_id dom_child_node(dom_index *idx, dom_node_id node, int last)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `last` | `int` |  |  |

**Returns:** `dom_node_id`

---

<a id="dom_sibling_node"></a>

### `dom_sibling_node`

`function` | [src/dom.c:1055](../../src/dom.c#L1055)

```c
dom_node_id dom_sibling_node(dom_index *idx, dom_node_id node, int prev)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |
| `prev` | `int` |  |  |

**Returns:** `dom_node_id`

*Calls:* [`valid`](include.dom.h.md#valid)

---

<a id="dom_create_char_node"></a>

### `dom_create_char_node`

`function` | [src/dom.c:1062](../../src/dom.c#L1062)

```c
dom_status dom_create_char_node(dom_index *idx, int kind, const char *text, size_t len, dom_node_id *out_id)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `kind` | `int` |  |  |
| `text` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `out_id` | `dom_node_id *` |  |  |

**Returns:** `dom_status`

---

<a id="dom_native_node"></a>

### `dom_native_node`

`function` `const` | [src/dom.c:1076](../../src/dom.c#L1076)

```c
const void *dom_native_node(const dom_index *idx, dom_node_id node)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `idx` | `dom_index *` |  |  |
| `node` | `dom_node_id` |  |  |

**Returns:** `void *`

---

## Macros

<a id="_posix_c_source"></a>

### `_POSIX_C_SOURCE`

`macro` | [src/dom.c:11](../../src/dom.c#L11)

```c
#define _POSIX_C_SOURCE
```

---

<a id="dom_qs_max_selectors"></a>

### `DOM_QS_MAX_SELECTORS`

`macro` | [src/dom.c:418](../../src/dom.c#L418)

```c
#define DOM_QS_MAX_SELECTORS
```

Max complex selectors in one comma-separated list.

A longer list is truncated (anti-DoS): the extra selectors are dropped, which only narrows matches.

---

<a id="ih_block_size"></a>

### `IH_BLOCK_SIZE`

`macro` | [src/dom.c:860](../../src/dom.c#L860)

```c
#define IH_BLOCK_SIZE
```

Accumulator for innerHTML serialization using a chain of fixed-size blocks.

When one block fills up, a new one is allocated and linked — no single contiguous allocation cap (anti-DoS is OOM from malloc, not an arbitrary cap). Blocks are freed by freeing the chain head.

---
