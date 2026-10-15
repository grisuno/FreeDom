# `include/hostedit.h`

> Source: [include/hostedit.h:1](../../include/hostedit.h#L1) | language `h` | coverage 60.0% | [API index](../index.md)

## Contents

- **Enums:** [`he_status`](#he_status)
- **Functions:** [`he_text_has_host`](#he_text_has_host), [`he_suggest`](#he_suggest)
- **Macros:** [`HE_MAX_HOST`](#he_max_host)

## Enums

<a id="he_status"></a>

### `he_status`

`enum` | [include/hostedit.h:24](../../include/hostedit.h#L24)

```c
typedef enum he_status
```

---

## Functions

<a id="he_text_has_host"></a>

### `he_text_has_host`

`function` | [include/hostedit.h:46](../../include/hostedit.h#L46)

```c
int he_text_has_host(const char *text, const char *host);
```

Returns 1 if text (the body of a hosts-format file) already lists host as a domain token on a non-comment line (case-insensitive; a leading IP token like "0.0.0.0" is ignored, matching hostblock), else 0.

NULL args -> 0. Lets the orchestrator skip a duplicate append.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `text` | `char *` |  |  |
| `host` | `char *` |  |  |

**Returns:** `int`

---

<a id="he_suggest"></a>

### `he_suggest`

`function` | [include/hostedit.h:55](../../include/hostedit.h#L55)

```c
int he_suggest(const char *text, const char *query, char results[][HE_MAX_HOST + 1], int max);
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

---

## Macros

<a id="he_max_host"></a>

### `HE_MAX_HOST`

`macro` | [include/hostedit.h:32](../../include/hostedit.h#L32)

```c
#define HE_MAX_HOST
```

Maximum hostname length written (DNS limit).

---
