# `src/js_policy.c`

> Source: [src/js_policy.c:1](../../src/js_policy.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

## Contents

- **Functions:** [`jsp_enabled`](#jsp_enabled), [`jsp_trusted`](#jsp_trusted), [`jsp_present_trusted`](#jsp_present_trusted), [`jsp_mode_from_str`](#jsp_mode_from_str), [`jsp_mode_str`](#jsp_mode_str)

## Functions

<a id="jsp_enabled"></a>

### `jsp_enabled`

`function` | [src/js_policy.c:22](../../src/js_policy.c#L22)

```c
bool jsp_enabled(jsp_mode mode, int host_allowlisted)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mode` | `jsp_mode` |  |  |
| `host_allowlisted` | `int` |  |  |

**Returns:** `bool`

*Called by:* [`wc_derive`](src.webcaps.c.md#wc_derive)

---

<a id="jsp_trusted"></a>

### `jsp_trusted`

`function` | [src/js_policy.c:31](../../src/js_policy.c#L31)

```c
bool jsp_trusted(bool js_enabled, int host_allowlisted)
```

Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over allow.conf) -- gets the full modern experience: author CSS and images on AND page-JS network access without per-session toggles.

Either signal alone fails closed; a global JSP_ON without the allowlist entry is NOT trust. Reader mode is applied by the orchestrator afterwards and wins.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `js_enabled` | `bool` |  |  |
| `host_allowlisted` | `int` |  |  |

**Returns:** `bool`

> **Inherited:** Documentation from [`jsp_trusted`](#jsp_trusted) (include/js_policy.h:45).

---

<a id="jsp_present_trusted"></a>

### `jsp_present_trusted`

`function` | [src/js_policy.c:35](../../src/js_policy.c#L35)

```c
bool jsp_present_trusted(int host_allowlisted)
```

Presentation-trust (2026-07-11): a host EXPLICITLY on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over allow.conf) gets author PRESENTATION -- author CSS and <img> images -- without per-session toggles, independent of JS.

Rationale: putting a host in allow.conf is an explicit statement of trust in that site; presentation (colours, borders, gradients, images) is strictly lower risk than script/network, which stay DOUBLE-gated on allow.conf AND js.conf via jsp_trusted. Fails closed for a non-allowlisted host (host_allowlisted == 0). Reader mode wins over this too.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `host_allowlisted` | `int` |  |  |

**Returns:** `bool`

> **Inherited:** Documentation from [`jsp_present_trusted`](#jsp_present_trusted) (include/js_policy.h:54).

---

<a id="jsp_mode_from_str"></a>

### `jsp_mode_from_str`

`function` | [src/js_policy.c:39](../../src/js_policy.c#L39)

```c
jsp_mode jsp_mode_from_str(const char *s)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `s` | `char *` |  |  |

**Returns:** `jsp_mode`

*Called by:* [`main`](src.freedom.c.md#main)

---

<a id="jsp_mode_str"></a>

### `jsp_mode_str`

`function` `const` | [src/js_policy.c:51](../../src/js_policy.c#L51)

```c
const char *jsp_mode_str(jsp_mode mode)
```

Stable lowercase name of a mode ("off"/"allowlist"/"on"); an unknown value yields "off" (fail closed).

Never NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mode` | `jsp_mode` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`jsp_mode_str`](#jsp_mode_str) (include/js_policy.h:64).

---
