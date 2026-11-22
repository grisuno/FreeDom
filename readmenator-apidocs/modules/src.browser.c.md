# `src/browser.c`

> Source: [src/browser.c:1](../../src/browser.c#L1) | language `c` | coverage 27.8% | [API index](../index.md)

## Contents

- **Functions:** [`browser_init`](#browser_init), [`browser_free`](#browser_free), [`browser_set_url_bar`](#browser_set_url_bar), [`browser_commit_url_bar`](#browser_commit_url_bar), [`browser_navigate`](#browser_navigate), [`browser_push_state`](#browser_push_state), [`browser_replace_state`](#browser_replace_state), [`browser_entry_doc`](#browser_entry_doc), [`browser_doc_index`](#browser_doc_index), [`browser_back`](#browser_back), [`browser_forward`](#browser_forward), [`browser_can_back`](#browser_can_back), [`browser_can_forward`](#browser_can_forward), [`browser_current_url`](#browser_current_url), [`browser_url_bar_selection`](#browser_url_bar_selection), [`browser_url_bar_delete_selection`](#browser_url_bar_delete_selection), [`browser_url_bar_insert`](#browser_url_bar_insert), [`browser_url_bar_backspace`](#browser_url_bar_backspace), [`browser_url_bar_delete`](#browser_url_bar_delete), [`browser_url_bar_move_cursor`](#browser_url_bar_move_cursor), [`browser_url_bar_extend_cursor`](#browser_url_bar_extend_cursor), [`browser_url_bar_set_cursor`](#browser_url_bar_set_cursor), [`browser_url_bar_select_all`](#browser_url_bar_select_all), [`browser_url_bar_clear`](#browser_url_bar_clear), [`browser_set_page`](#browser_set_page), [`browser_set_status`](#browser_set_status), [`browser_status_text`](#browser_status_text), [`browser_is_exception`](#browser_is_exception), [`browser_add_exception`](#browser_add_exception), [`browser_closed_push`](#browser_closed_push), [`browser_closed_pop`](#browser_closed_pop), [`browser_commit_pending`](#browser_commit_pending), [`browser_abort_pending`](#browser_abort_pending), [`browser_has_pending`](#browser_has_pending)
- **Macros:** [`_POSIX_C_SOURCE`](#_posix_c_source)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_browser_c__browser_init(["browser_init"])
    n_src_browser_c__browser_free(["browser_free"])
    n_src_browser_c__browser_set_url_bar(["browser_set_url_bar"])
    n_src_browser_c__browser_commit_url_bar(["browser_commit_url_bar"])
    n_src_browser_c__browser_navigate(["browser_navigate"])
    n_src_browser_c__browser_abort_pending(["browser_abort_pending"])
    n_src_browser_c__browser_replace_state(["browser_replace_state"])
    n_src_browser_c__browser_back(["browser_back"])
    n_src_browser_c__browser_forward(["browser_forward"])
    n_src_browser_c__browser_url_bar_delete_selection(["browser_url_bar_delete_selection"])
    n_src_browser_c__browser_url_bar_selection(["browser_url_bar_selection"])
    n_src_browser_c__browser_url_bar_insert(["browser_url_bar_insert"])
    n_src_browser_c__browser_url_bar_backspace(["browser_url_bar_backspace"])
    n_src_browser_c__browser_url_bar_delete(["browser_url_bar_delete"])
    n_src_browser_c__browser_add_exception(["browser_add_exception"])
    n_src_browser_c__browser_is_exception(["browser_is_exception"])
    n_src_browser_c__browser_current_url(["browser_current_url"])
    n_src_browser_c__browser_init --> n_src_browser_c__browser_free
    n_src_browser_c__browser_init --> n_src_browser_c__browser_set_url_bar
    n_src_browser_c__browser_commit_url_bar --> n_src_browser_c__browser_navigate
    n_src_browser_c__browser_navigate --> n_src_browser_c__browser_abort_pending
    n_src_browser_c__browser_replace_state --> n_src_browser_c__browser_set_url_bar
    n_src_browser_c__browser_back --> n_src_browser_c__browser_abort_pending
    n_src_browser_c__browser_back --> n_src_browser_c__browser_set_url_bar
    n_src_browser_c__browser_forward --> n_src_browser_c__browser_abort_pending
    n_src_browser_c__browser_forward --> n_src_browser_c__browser_set_url_bar
    n_src_browser_c__browser_url_bar_delete_selection --> n_src_browser_c__browser_url_bar_selection
    n_src_browser_c__browser_url_bar_insert --> n_src_browser_c__browser_url_bar_delete_selection
    n_src_browser_c__browser_url_bar_backspace --> n_src_browser_c__browser_url_bar_delete_selection
    n_src_browser_c__browser_url_bar_delete --> n_src_browser_c__browser_url_bar_delete_selection
    n_src_browser_c__browser_add_exception --> n_src_browser_c__browser_is_exception
    n_src_browser_c__browser_abort_pending --> n_src_browser_c__browser_current_url
    n_src_browser_c__browser_abort_pending --> n_src_browser_c__browser_set_url_bar
```

## Functions

<a id="browser_init"></a>

### `browser_init`

`function` | [src/browser.c:192](../../src/browser.c#L192)

```c
browser_status browser_init(browser_state *bs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `browser_status`

*Calls:* [`browser_free`](#browser_free), [`browser_set_url_bar`](#browser_set_url_bar)

---

<a id="browser_free"></a>

### `browser_free`

`function` | [src/browser.c:203](../../src/browser.c#L203)

```c
void browser_free(browser_state *bs)
```

Release all owned memory.

Safe on NULL and zero-initialised.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

> **Inherited:** Documentation from [`browser_free`](#browser_free) (include/browser.h:78).

*Called by:* [`browser_init`](#browser_init)

---

<a id="browser_set_url_bar"></a>

### `browser_set_url_bar`

`function` | [src/browser.c:215](../../src/browser.c#L215)

```c
browser_status browser_set_url_bar(browser_state *bs, const char *url)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `url` | `char *` |  |  |

**Returns:** `browser_status`

*Called by:* [`arrives`](gui.browser_ui.c.md#arrives), [`browser_abort_pending`](#browser_abort_pending), [`browser_back`](#browser_back), [`browser_forward`](#browser_forward), [`browser_init`](#browser_init), [`browser_replace_state`](#browser_replace_state)

---

<a id="browser_commit_url_bar"></a>

### `browser_commit_url_bar`

`function` | [src/browser.c:227](../../src/browser.c#L227)

```c
browser_status browser_commit_url_bar(browser_state *bs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `browser_status`

*Calls:* [`browser_navigate`](#browser_navigate)

---

<a id="browser_navigate"></a>

### `browser_navigate`

`function` | [src/browser.c:273](../../src/browser.c#L273)

```c
browser_status browser_navigate(browser_state *bs, const char *url)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `url` | `char *` |  |  |

**Returns:** `browser_status`

*Calls:* [`browser_abort_pending`](#browser_abort_pending)

*Called by:* [`browser_commit_url_bar`](#browser_commit_url_bar)

---

<a id="browser_push_state"></a>

### `browser_push_state`

`function` | [src/browser.c:303](../../src/browser.c#L303)

```c
browser_status browser_push_state(browser_state *bs, const char *url)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `url` | `char *` |  |  |

**Returns:** `browser_status`

---

<a id="browser_replace_state"></a>

### `browser_replace_state`

`function` | [src/browser.c:311](../../src/browser.c#L311)

```c
browser_status browser_replace_state(browser_state *bs, const char *url)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `url` | `char *` |  |  |

**Returns:** `browser_status`

*Calls:* [`browser_set_url_bar`](#browser_set_url_bar)

---

<a id="browser_entry_doc"></a>

### `browser_entry_doc`

`function` | [src/browser.c:324](../../src/browser.c#L324)

```c
int browser_entry_doc(const browser_state *bs, size_t pos)
```

Document id of entry pos, or -1 when out of range / NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `pos` | `size_t` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`browser_entry_doc`](#browser_entry_doc) (include/browser.h:110).

---

<a id="browser_doc_index"></a>

### `browser_doc_index`

`function` | [src/browser.c:329](../../src/browser.c#L329)

```c
int browser_doc_index(const browser_state *bs)
```

Index of the current entry within its document's contiguous run of entries (0 for the entry the document was loaded at) -- the worker's own history index.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`browser_doc_index`](#browser_doc_index) (include/browser.h:114).

---

<a id="browser_back"></a>

### `browser_back`

`function` | [src/browser.c:337](../../src/browser.c#L337)

```c
browser_status browser_back(browser_state *bs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `browser_status`

*Calls:* [`browser_abort_pending`](#browser_abort_pending), [`browser_set_url_bar`](#browser_set_url_bar)

---

<a id="browser_forward"></a>

### `browser_forward`

`function` | [src/browser.c:350](../../src/browser.c#L350)

```c
browser_status browser_forward(browser_state *bs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `browser_status`

*Calls:* [`browser_abort_pending`](#browser_abort_pending), [`browser_set_url_bar`](#browser_set_url_bar)

---

<a id="browser_can_back"></a>

### `browser_can_back`

`function` | [src/browser.c:363](../../src/browser.c#L363)

```c
int browser_can_back(const browser_state *bs)
```

Query helpers.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`browser_can_back`](#browser_can_back) (include/browser.h:117).

---

<a id="browser_can_forward"></a>

### `browser_can_forward`

`function` | [src/browser.c:367](../../src/browser.c#L367)

```c
int browser_can_forward(const browser_state *bs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `int`

---

<a id="browser_current_url"></a>

### `browser_current_url`

`function` `const` | [src/browser.c:371](../../src/browser.c#L371)

```c
const char *browser_current_url(const browser_state *bs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `char *`

*Called by:* [`browser_abort_pending`](#browser_abort_pending)

---

<a id="browser_url_bar_selection"></a>

### `browser_url_bar_selection`

`function` | [src/browser.c:376](../../src/browser.c#L376)

```c
int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)
```

If a selection exists, writes its start offset and length and returns 1; else 0.

Lets the GUI copy/cut the selected text and paint the highlight. NULL-safe.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `start` | `size_t *` |  |  |
| `len` | `size_t *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`browser_url_bar_selection`](#browser_url_bar_selection) (include/browser.h:154).

*Called by:* [`browser_url_bar_delete_selection`](#browser_url_bar_delete_selection)

---

<a id="browser_url_bar_delete_selection"></a>

### `browser_url_bar_delete_selection`

`function` | [src/browser.c:387](../../src/browser.c#L387)

```c
int browser_url_bar_delete_selection(browser_state *bs)
```

Removes the selected range (if any), placing the cursor at its start; returns 1 if something was removed, else 0.

Used by cut and by an edit over a selection.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`browser_url_bar_delete_selection`](#browser_url_bar_delete_selection) (include/browser.h:158).

*Calls:* [`browser_url_bar_selection`](#browser_url_bar_selection)

*Called by:* [`browser_url_bar_backspace`](#browser_url_bar_backspace), [`browser_url_bar_delete`](#browser_url_bar_delete), [`browser_url_bar_insert`](#browser_url_bar_insert)

---

<a id="browser_url_bar_insert"></a>

### `browser_url_bar_insert`

`function` | [src/browser.c:397](../../src/browser.c#L397)

```c
browser_status browser_url_bar_insert(browser_state *bs, char c)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `c` | `char` |  |  |

**Returns:** `browser_status`

*Calls:* [`browser_url_bar_delete_selection`](#browser_url_bar_delete_selection)

---

<a id="browser_url_bar_backspace"></a>

### `browser_url_bar_backspace`

`function` | [src/browser.c:412](../../src/browser.c#L412)

```c
browser_status browser_url_bar_backspace(browser_state *bs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `browser_status`

*Calls:* [`browser_url_bar_delete_selection`](#browser_url_bar_delete_selection)

---

<a id="browser_url_bar_delete"></a>

### `browser_url_bar_delete`

`function` | [src/browser.c:426](../../src/browser.c#L426)

```c
browser_status browser_url_bar_delete(browser_state *bs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `browser_status`

*Calls:* [`browser_url_bar_delete_selection`](#browser_url_bar_delete_selection)

---

<a id="browser_url_bar_move_cursor"></a>

### `browser_url_bar_move_cursor`

`function` | [src/browser.c:437](../../src/browser.c#L437)

```c
browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `delta` | `long` |  |  |

**Returns:** `browser_status`

---

<a id="browser_url_bar_extend_cursor"></a>

### `browser_url_bar_extend_cursor`

`function` | [src/browser.c:447](../../src/browser.c#L447)

```c
browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `delta` | `long` |  |  |

**Returns:** `browser_status`

---

<a id="browser_url_bar_set_cursor"></a>

### `browser_url_bar_set_cursor`

`function` | [src/browser.c:456](../../src/browser.c#L456)

```c
browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `pos` | `size_t` |  |  |
| `extend` | `int` |  |  |

**Returns:** `browser_status`

---

<a id="browser_url_bar_select_all"></a>

### `browser_url_bar_select_all`

`function` | [src/browser.c:464](../../src/browser.c#L464)

```c
browser_status browser_url_bar_select_all(browser_state *bs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `browser_status`

---

<a id="browser_url_bar_clear"></a>

### `browser_url_bar_clear`

`function` | [src/browser.c:471](../../src/browser.c#L471)

```c
browser_status browser_url_bar_clear(browser_state *bs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `browser_status`

---

<a id="browser_set_page"></a>

### `browser_set_page`

`function` | [src/browser.c:480](../../src/browser.c#L480)

```c
browser_status browser_set_page(browser_state *bs, const char *title, const char *text, int error)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `title` | `char *` |  |  |
| `text` | `char *` |  |  |
| `error` | `int` |  |  |

**Returns:** `browser_status`

---

<a id="browser_set_status"></a>

### `browser_set_status`

`function` | [src/browser.c:502](../../src/browser.c#L502)

```c
browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `msg` | `char *` |  |  |
| `now_ms` | `uint64_t` |  |  |

**Returns:** `browser_status`

*Called by:* [`arrives`](gui.browser_ui.c.md#arrives)

---

<a id="browser_status_text"></a>

### `browser_status_text`

`function` `const` | [src/browser.c:516](../../src/browser.c#L516)

```c
const char *browser_status_text(const browser_state *bs, uint64_t now_ms)
```

The active status text, or NULL when there is none or it has expired at now_ms.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `now_ms` | `uint64_t` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`browser_status_text`](#browser_status_text) (include/browser.h:173).

---

<a id="browser_is_exception"></a>

### `browser_is_exception`

`function` | [src/browser.c:535](../../src/browser.c#L535)

```c
int browser_is_exception(const browser_state *bs, const char *host)
```

Exception list: hosts explicitly allowed to use weak TLS.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `host` | `char *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`browser_is_exception`](#browser_is_exception) (include/browser.h:122).

*Called by:* [`browser_add_exception`](#browser_add_exception)

---

<a id="browser_add_exception"></a>

### `browser_add_exception`

`function` | [src/browser.c:543](../../src/browser.c#L543)

```c
browser_status browser_add_exception(browser_state *bs, const char *host)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |
| `host` | `char *` |  |  |

**Returns:** `browser_status`

*Calls:* [`browser_is_exception`](#browser_is_exception)

---

<a id="browser_closed_push"></a>

### `browser_closed_push`

`function` | [src/browser.c:561](../../src/browser.c#L561)

```c
browser_status browser_closed_push(browser_closed *c, const char *url)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `browser_closed *` |  |  |
| `url` | `char *` |  |  |

**Returns:** `browser_status`

---

<a id="browser_closed_pop"></a>

### `browser_closed_pop`

`function` | [src/browser.c:576](../../src/browser.c#L576)

```c
int browser_closed_pop(browser_closed *c, char *out, size_t cap)
```

Takes the most recently closed URL into out[cap].

1 = taken, 0 = none (or it does not fit, in which case it stays).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `browser_closed *` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`browser_closed_pop`](#browser_closed_pop) (include/browser.h:188).

---

<a id="browser_commit_pending"></a>

### `browser_commit_pending`

`function` | [src/browser.c:588](../../src/browser.c#L588)

```c
void browser_commit_pending(browser_state *bs)
```

Provisional navigation (spec/browser.md 3c). commit: the document (or its error page) landed -- the entry stays and the stashed forward entries are freed. abort: Stop -- the history returns to exactly what it was before the pending navigation and the URL bar shows the current entry; 1 if something was reverted, else 0.

A navigate while pending first aborts the pending one (the new one replaces it); several back/forward steps are ONE pending navigation. push/replace_state while pending return BROWSER_ERR_PENDING. All NULL-safe.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

> **Inherited:** Documentation from [`browser_commit_pending`](#browser_commit_pending) (include/browser.h:105).

---

<a id="browser_abort_pending"></a>

### `browser_abort_pending`

`function` | [src/browser.c:593](../../src/browser.c#L593)

```c
int browser_abort_pending(browser_state *bs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `int`

*Calls:* [`browser_current_url`](#browser_current_url), [`browser_set_url_bar`](#browser_set_url_bar)

*Called by:* [`browser_back`](#browser_back), [`browser_forward`](#browser_forward), [`browser_navigate`](#browser_navigate)

---

<a id="browser_has_pending"></a>

### `browser_has_pending`

`function` | [src/browser.c:622](../../src/browser.c#L622)

```c
int browser_has_pending(const browser_state *bs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bs` | `browser_state *` |  |  |

**Returns:** `int`

---

## Macros

<a id="_posix_c_source"></a>

### `_POSIX_C_SOURCE`

`macro` | [src/browser.c:7](../../src/browser.c#L7)

```c
#define _POSIX_C_SOURCE
```

---
