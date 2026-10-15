# `include/js_policy.h`

> Source: [include/js_policy.h:1](../../include/js_policy.h#L1) | language `h` | coverage 42.9% | [API index](../index.md)

## Contents

- **Enums:** [`jsp_mode`](#jsp_mode)
- **Functions:** [`membership`](#membership), [`allowlist`](#allowlist), [`jsp_trusted`](#jsp_trusted), [`jsp_present_trusted`](#jsp_present_trusted), [`jsp_mode_str`](#jsp_mode_str)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_include_js_policy_h__membership(["membership"])
    n_include_js_policy_h__allowlist(["allowlist"])
    n_include_js_policy_h__membership --> n_include_js_policy_h__allowlist
```

## Enums

<a id="jsp_mode"></a>

### `jsp_mode`

`enum` | [include/js_policy.h:27](../../include/js_policy.h#L27)

```c
typedef enum jsp_mode
```

---

## Functions

<a id="membership"></a>

### `membership`

`function` | [include/js_policy.h:16](../../include/js_policy.h#L16)

```c
* membership (the allowlist itself is matched by the hostblock module, which * already covers subdomains). No I/O, no global state. * * The decision is surfaced as rdp_caps.js and consumed by the rend
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `module` | `the allowlist itself is matched by the hostblock` |  |  |
| `subdomains` | `which * already covers` |  |  |

**Returns:** `*`

*Calls:* [`allowlist`](#allowlist)

---

<a id="allowlist"></a>

### `allowlist`

`function` | [include/js_policy.h:34](../../include/js_policy.h#L34)

```c
* allowlist (e.g. hb_is_allowlisted over js.conf). Fails closed: an unknown mode * yields false. */ bool jsp_enabled(jsp_mode mode, int host_allowlisted);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `conf` | `e.g. hb_is_allowlisted over js.` |  |  |

**Returns:** `*`

*Called by:* [`membership`](#membership)

---

<a id="jsp_trusted"></a>

### `jsp_trusted`

`function` | [include/js_policy.h:45](../../include/js_policy.h#L45)

```c
bool jsp_trusted(bool js_enabled, int host_allowlisted);
```

Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE -- its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over allow.conf) -- gets the full modern experience: author CSS and images on AND page-JS network access without per-session toggles.

Either signal alone fails closed; a global JSP_ON without the allowlist entry is NOT trust. Reader mode is applied by the orchestrator afterwards and wins.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `js_enabled` | `bool` |  |  |
| `host_allowlisted` | `int` |  |  |

**Returns:** `bool`

---

<a id="jsp_present_trusted"></a>

### `jsp_present_trusted`

`function` | [include/js_policy.h:54](../../include/js_policy.h#L54)

```c
bool jsp_present_trusted(int host_allowlisted);
```

Presentation-trust (2026-07-11): a host EXPLICITLY on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over allow.conf) gets author PRESENTATION -- author CSS and <img> images -- without per-session toggles, independent of JS.

Rationale: putting a host in allow.conf is an explicit statement of trust in that site; presentation (colours, borders, gradients, images) is strictly lower risk than script/network, which stay DOUBLE-gated on allow.conf AND js.conf via jsp_trusted. Fails closed for a non-allowlisted host (host_allowlisted == 0). Reader mode wins over this too.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `host_allowlisted` | `int` |  |  |

**Returns:** `bool`

---

<a id="jsp_mode_str"></a>

### `jsp_mode_str`

`function` `const` | [include/js_policy.h:64](../../include/js_policy.h#L64)

```c
const char *jsp_mode_str(jsp_mode mode);
```

Stable lowercase name of a mode ("off"/"allowlist"/"on"); an unknown value yields "off" (fail closed).

Never NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mode` | `jsp_mode` |  |  |

**Returns:** `char *`

---
