# `src/hostedit.c`

> Source: [src/hostedit.c:1](../../src/hostedit.c#L1) | language `c` | coverage 40.0% | [API index](../index.md)

## Contents

- **Structs:** [`suggest_ctx`](#suggest_ctx)
- **Functions:** [`he_make_line`](#he_make_line), [`he_text_has_host`](#he_text_has_host), [`he_suggest`](#he_suggest)

## Structs

<a id="suggest_ctx"></a>

### `suggest_ctx`

`struct` | [src/hostedit.c:136](../../src/hostedit.c#L136)

```c
struct suggest_ctx
```

---

## Functions

<a id="he_make_line"></a>

### `he_make_line`

`function` | [src/hostedit.c:41](../../src/hostedit.c#L41)

```c
he_status he_make_line(const char *host, char *out, size_t cap)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `host` | `char *` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `he_status`

---

<a id="he_text_has_host"></a>

### `he_text_has_host`

`function` | [src/hostedit.c:109](../../src/hostedit.c#L109)

```c
int he_text_has_host(const char *text, const char *host)
```

Returns 1 if text (the body of a hosts-format file) already lists host as a domain token on a non-comment line (case-insensitive; a leading IP token like "0.0.0.0" is ignored, matching hostblock), else 0.

NULL args -> 0. Lets the orchestrator skip a duplicate append.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `text` | `char *` |  |  |
| `host` | `char *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`he_text_has_host`](#he_text_has_host) (include/hostedit.h:46).

---

<a id="he_suggest"></a>

### `he_suggest`

`function` | [src/hostedit.c:164](../../src/hostedit.c#L164)

```c
int he_suggest(const char *text, const char *query, char results[][HE_MAX_HOST + 1], int max)
```

Omnibar autocomplete: treats allow.conf (a hosts-format text) as a favorites list.

Fills results[0..max) with up to max distinct domain tokens of text that match query case-insensitively -- PREFIX matches first (document order), then non-prefix SUBSTRING matches. query "" matches everything (favorites browsing). Each result is lowercased and NUL-terminated; hosts longer than HE_MAX_HOST are skipped. results is a caller array results[max][HE_MAX_HOST+1]. Returns the count written. Pure (no allocation, no I/O). NULL args / max <= 0 -> 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `text` | `char *` |  |  |
| `query` | `char *` |  |  |
| `HE_MAX_HOST` | `char results[][ + 1]` |  |  |
| `max` | `int` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`he_suggest`](#he_suggest) (include/hostedit.h:55).

---
