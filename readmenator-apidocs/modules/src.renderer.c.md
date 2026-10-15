# `src/renderer.c`

> Source: [src/renderer.c:1](../../src/renderer.c#L1) | language `c` | coverage 20.0% | [API index](../index.md)

## Contents

- **Functions:** [`write_full`](#write_full), [`rd_render_html`](#rd_render_html), [`rd_result_free`](#rd_result_free)
- **Macros:** [`_POSIX_C_SOURCE`](#_posix_c_source)

## Functions

<a id="write_full"></a>

### `write_full`

`function` | [src/renderer.c:40](../../src/renderer.c#L40)

```c
&& write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 || write_full(wfd, title, tl) == 0) && write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `tl` |  |  |  |
| `tl` | `sizeof` |  |  |

**Returns:** `&&`

---

<a id="rd_render_html"></a>

### `rd_render_html`

`function` | [src/renderer.c:70](../../src/renderer.c#L70)

```c
rd_status rd_render_html(const char *html, size_t len, rd_result *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `html` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `out` | `rd_result *` |  |  |

**Returns:** `rd_status`

---

<a id="rd_result_free"></a>

### `rd_result_free`

`function` | [src/renderer.c:120](../../src/renderer.c#L120)

```c
void rd_result_free(rd_result *out)
```

Idempotent; safe on a zero-initialised struct and safe to call twice.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `out` | `rd_result *` |  |  |

> **Inherited:** Documentation from [`rd_result_free`](#rd_result_free) (include/renderer.h:46).

---

## Macros

<a id="_posix_c_source"></a>

### `_POSIX_C_SOURCE`

`macro` | [src/renderer.c:7](../../src/renderer.c#L7)

```c
#define _POSIX_C_SOURCE
```

---
