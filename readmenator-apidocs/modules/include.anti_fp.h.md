# `include/anti_fp.h`

> Source: [include/anti_fp.h:1](../../include/anti_fp.h#L1) | language `h` | coverage 60.0% | [API index](../index.md)

## Contents

- **Functions:** [`fp_timer_resolution_ms`](#fp_timer_resolution_ms), [`fp_coarsen_time_ms`](#fp_coarsen_time_ms), [`fp_user_agent`](#fp_user_agent), [`fp_accept_language`](#fp_accept_language), [`fp_accept_language_header`](#fp_accept_language_header), [`fp_timezone`](#fp_timezone), [`fp_platform`](#fp_platform), [`fp_vendor`](#fp_vendor), [`fp_hardware_concurrency`](#fp_hardware_concurrency), [`fp_device_memory_gb`](#fp_device_memory_gb), [`properties`](#properties), [`fp_app_code_name`](#fp_app_code_name), [`fp_product`](#fp_product), [`fp_app_name`](#fp_app_name), [`fp_product_sub`](#fp_product_sub), [`fp_oscpu`](#fp_oscpu), [`fp_build_id`](#fp_build_id), [`fp_max_touch_points`](#fp_max_touch_points), [`fp_on_line`](#fp_on_line), [`fp_cookie_enabled`](#fp_cookie_enabled), [`fp_bucket_screen`](#fp_bucket_screen), [`fp_perturb`](#fp_perturb), [`domain`](#domain), [`probability`](#probability), [`fp_origin_key`](#fp_origin_key)
- **Macros:** [`FP_TIMER_RESOLUTION_MS`](#fp_timer_resolution_ms), [`FP_USER_AGENT`](#fp_user_agent), [`FP_ACCEPT_LANGUAGE`](#fp_accept_language), [`FP_ACCEPT_LANGUAGE_HEADER`](#fp_accept_language_header), [`FP_ACCEPT_HEADER_NAV`](#fp_accept_header_nav), [`FP_SEC_FETCH_DEST_NAV`](#fp_sec_fetch_dest_nav), [`FP_SEC_FETCH_MODE_NAV`](#fp_sec_fetch_mode_nav), [`FP_SEC_FETCH_SITE_NONE`](#fp_sec_fetch_site_none), [`FP_SEC_FETCH_USER_ON`](#fp_sec_fetch_user_on)

## Functions

<a id="fp_timer_resolution_ms"></a>

### `fp_timer_resolution_ms`

`function` | [include/anti_fp.h:52](../../include/anti_fp.h#L52)

```c
uint64_t fp_timer_resolution_ms(void);
```

**Returns:** `uint64_t`

---

<a id="fp_coarsen_time_ms"></a>

### `fp_coarsen_time_ms`

`function` | [include/anti_fp.h:53](../../include/anti_fp.h#L53)

```c
uint64_t fp_coarsen_time_ms(uint64_t raw_ms);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `raw_ms` | `uint64_t` |  |  |

**Returns:** `uint64_t`

---

<a id="fp_user_agent"></a>

### `fp_user_agent`

`function` `const` | [include/anti_fp.h:57](../../include/anti_fp.h#L57)

```c
const char *fp_user_agent(void);
```

**Returns:** `char *`

*Called by:* [`idn_user_agent`](src.identity.c.md#idn_user_agent)

---

<a id="fp_accept_language"></a>

### `fp_accept_language`

`function` `const` | [include/anti_fp.h:58](../../include/anti_fp.h#L58)

```c
const char *fp_accept_language(void);
```

**Returns:** `char *`

*Called by:* [`idn_primary_language`](src.identity.c.md#idn_primary_language), [`idn_render_page`](src.identity.c.md#idn_render_page)

---

<a id="fp_accept_language_header"></a>

### `fp_accept_language_header`

`function` `const` | [include/anti_fp.h:59](../../include/anti_fp.h#L59)

```c
const char *fp_accept_language_header(void);
```

list form, e.g.

"en-US,en"

**Returns:** `char *`

*Called by:* [`idn_accept_language`](src.identity.c.md#idn_accept_language)

---

<a id="fp_timezone"></a>

### `fp_timezone`

`function` `const` | [include/anti_fp.h:60](../../include/anti_fp.h#L60)

```c
const char *fp_timezone(void);
```

HTTP header value, e.g.

"en-US,en;q=0.5"

**Returns:** `char *`

---

<a id="fp_platform"></a>

### `fp_platform`

`function` `const` | [include/anti_fp.h:61](../../include/anti_fp.h#L61)

```c
const char *fp_platform(void);
```

"UTC"

**Returns:** `char *`

---

<a id="fp_vendor"></a>

### `fp_vendor`

`function` `const` | [include/anti_fp.h:62](../../include/anti_fp.h#L62)

```c
const char *fp_vendor(void);
```

"Linux x86_64" (consistent with the UA)

**Returns:** `char *`

---

<a id="fp_hardware_concurrency"></a>

### `fp_hardware_concurrency`

`function` | [include/anti_fp.h:63](../../include/anti_fp.h#L63)

```c
int fp_hardware_concurrency(void);
```

"" (no vendor; minimal entropy)

**Returns:** `int`

---

<a id="fp_device_memory_gb"></a>

### `fp_device_memory_gb`

`function` | [include/anti_fp.h:64](../../include/anti_fp.h#L64)

```c
int fp_device_memory_gb(void);
```

**Returns:** `int`

---

<a id="properties"></a>

### `properties`

`function` | [include/anti_fp.h:67](../../include/anti_fp.h#L67)

```c
* Legacy navigator properties (Hito 30b): normalized Firefox values shared by * js_env and the network layer so JS and HTTP present the same identity. */ const char *fp_app_version(void);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `Hito 30` |  |  |

**Returns:** `normalized Firefox values shared by * js_env and the network layer so JS and HTTP present the same identity. */ const char *fp_app_version(void)`

---

<a id="fp_app_code_name"></a>

### `fp_app_code_name`

`function` `const` | [include/anti_fp.h:71](../../include/anti_fp.h#L71)

```c
const char *fp_app_code_name(void);
```

same string as fp_user_agent()

**Returns:** `char *`

---

<a id="fp_product"></a>

### `fp_product`

`function` `const` | [include/anti_fp.h:72](../../include/anti_fp.h#L72)

```c
const char *fp_product(void);
```

"Mozilla" (historic, all browsers)

**Returns:** `char *`

---

<a id="fp_app_name"></a>

### `fp_app_name`

`function` `const` | [include/anti_fp.h:73](../../include/anti_fp.h#L73)

```c
const char *fp_app_name(void);
```

"Gecko" (Firefox engine identity)

**Returns:** `char *`

---

<a id="fp_product_sub"></a>

### `fp_product_sub`

`function` `const` | [include/anti_fp.h:74](../../include/anti_fp.h#L74)

```c
const char *fp_product_sub(void);
```

"Netscape" (historic)

**Returns:** `char *`

---

<a id="fp_oscpu"></a>

### `fp_oscpu`

`function` `const` | [include/anti_fp.h:75](../../include/anti_fp.h#L75)

```c
const char *fp_oscpu(void);
```

"20100101" (Gecko build date)

**Returns:** `char *`

---

<a id="fp_build_id"></a>

### `fp_build_id`

`function` `const` | [include/anti_fp.h:76](../../include/anti_fp.h#L76)

```c
const char *fp_build_id(void);
```

"Linux x86_64" (consistent with UA)

**Returns:** `char *`

---

<a id="fp_max_touch_points"></a>

### `fp_max_touch_points`

`function` | [include/anti_fp.h:77](../../include/anti_fp.h#L77)

```c
int fp_max_touch_points(void);
```

fixed Firefox build ID

**Returns:** `int`

---

<a id="fp_on_line"></a>

### `fp_on_line`

`function` | [include/anti_fp.h:78](../../include/anti_fp.h#L78)

```c
int fp_on_line(void);
```

0 (desktop, no touch)

**Returns:** `int`

---

<a id="fp_cookie_enabled"></a>

### `fp_cookie_enabled`

`function` | [include/anti_fp.h:79](../../include/anti_fp.h#L79)

```c
int fp_cookie_enabled(void);
```

1 (connected)

**Returns:** `int`

---

<a id="fp_bucket_screen"></a>

### `fp_bucket_screen`

`function` | [include/anti_fp.h:83](../../include/anti_fp.h#L83)

```c
void fp_bucket_screen(int w, int h, int *out_w, int *out_h);
```

Snaps a screen size to a standard bucket (cuts entropy). out_w/out_h non-NULL.

Picks the largest-area bucket that fits in (w,h); if none fits, the smallest.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `w` | `int` |  |  |
| `h` | `int` |  |  |
| `out_w` | `int *` |  |  |
| `out_h` | `int *` |  |  |

---

<a id="fp_perturb"></a>

### `fp_perturb`

`function` | [include/anti_fp.h:88](../../include/anti_fp.h#L88)

```c
void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key);
```

Deterministic per-session readback poisoning (canvas/audio): flips only the least-significant bit of a sparse, key-selected subset of bytes.

Same (buf,key) => same output; different key => different output. NULL/len 0 = no-op.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `uint8_t *` |  |  |
| `len` | `size_t` |  |  |
| `session_key` | `uint64_t` |  |  |

---

<a id="domain"></a>

### `domain`

`function` | [include/anti_fp.h:91](../../include/anti_fp.h#L91)

```c
* registrable domain (eTLD+1). Same (session_key, domain) => same key (poisoning * is stable within a site);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `eTLD` |  |  |  |

**Returns:** `* registrable`

*Called by:* [`proceed`](gui.browser_ui.c.md#proceed)

---

<a id="probability"></a>

### `probability`

`function` | [include/anti_fp.h:93](../../include/anti_fp.h#L93)

```c
* keys with overwhelming probability (canvas/audio noise is not linkable across * sites, defeating cross-origin fingerprint linking). registrable_domain NULL or * "" collapses to a single namespace (i
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sites` | `canvas/audio noise is not linkable across *` |  |  |
| `linking` | `defeating cross-origin fingerprint` |  |  |

**Returns:** `* keys with overwhelming`

---

<a id="fp_origin_key"></a>

### `fp_origin_key`

`function` | [include/anti_fp.h:98](../../include/anti_fp.h#L98)

```c
uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain);
```

Derives the per-origin readback key from the per-session secret and a site's registrable domain (eTLD+1).

Same (session_key, domain) => same key (poisoning is stable within a site); different domains under the same session => different keys with overwhelming probability (canvas/audio noise is not linkable across sites, defeating cross-origin fingerprint linking). registrable_domain NULL or "" collapses to a single namespace (its own stable key, distinct from any real domain); never aborts, never leaks. Pure: no I/O, no allocation. The caller (tab worker) computes the eTLD+1 via request_policy and passes it here.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `session_key` | `uint64_t` |  |  |
| `registrable_domain` | `char *` |  |  |

**Returns:** `uint64_t`

---

## Macros

<a id="fp_timer_resolution_ms"></a>

### `FP_TIMER_RESOLUTION_MS`

`macro` | [include/anti_fp.h:22](../../include/anti_fp.h#L22)

```c
#define FP_TIMER_RESOLUTION_MS
```

---

<a id="fp_user_agent"></a>

### `FP_USER_AGENT`

`macro` | [include/anti_fp.h:31](../../include/anti_fp.h#L31)

```c
#define FP_USER_AGENT
```

The normalized identity strings live here as macros so they are a single source of truth shared by the JS bindings (navigator.*) AND the network layer (the User-Agent / Accept-Language HTTP headers in secure_fetch).

A mismatch between the JS-visible identity and the on-the-wire identity is itself a high-entropy fingerprint (and a bot signal), so both MUST present the same blend-in identity. The value is a common, current Firefox-on-Linux string: it maximizes the anonymity set instead of advertising "Freedom".

---

<a id="fp_accept_language"></a>

### `FP_ACCEPT_LANGUAGE`

`macro` | [include/anti_fp.h:33](../../include/anti_fp.h#L33)

```c
#define FP_ACCEPT_LANGUAGE
```

---

<a id="fp_accept_language_header"></a>

### `FP_ACCEPT_LANGUAGE_HEADER`

`macro` | [include/anti_fp.h:34](../../include/anti_fp.h#L34)

```c
#define FP_ACCEPT_LANGUAGE_HEADER
```

list form (navigator.languages)

---

<a id="fp_accept_header_nav"></a>

### `FP_ACCEPT_HEADER_NAV`

`macro` | [include/anti_fp.h:40](../../include/anti_fp.h#L40)

```c
#define FP_ACCEPT_HEADER_NAV
```

Blending-in network constants (Hito 30b): Firefox-like HTTP headers shared with secure_fetch so the JS-visible identity and on-the-wire identity agree.

---

<a id="fp_sec_fetch_dest_nav"></a>

### `FP_SEC_FETCH_DEST_NAV`

`macro` | [include/anti_fp.h:45](../../include/anti_fp.h#L45)

```c
#define FP_SEC_FETCH_DEST_NAV
```

Sec-Fetch headers for top-level navigation.

Subresource requests (images, scripts, stylesheets) use the dest string from sf_config.sec_fetch_dest.

---

<a id="fp_sec_fetch_mode_nav"></a>

### `FP_SEC_FETCH_MODE_NAV`

`macro` | [include/anti_fp.h:46](../../include/anti_fp.h#L46)

```c
#define FP_SEC_FETCH_MODE_NAV
```

---

<a id="fp_sec_fetch_site_none"></a>

### `FP_SEC_FETCH_SITE_NONE`

`macro` | [include/anti_fp.h:47](../../include/anti_fp.h#L47)

```c
#define FP_SEC_FETCH_SITE_NONE
```

---

<a id="fp_sec_fetch_user_on"></a>

### `FP_SEC_FETCH_USER_ON`

`macro` | [include/anti_fp.h:48](../../include/anti_fp.h#L48)

```c
#define FP_SEC_FETCH_USER_ON
```

---
