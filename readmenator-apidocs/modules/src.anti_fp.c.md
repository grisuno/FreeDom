# `src/anti_fp.c`

> Source: [src/anti_fp.c:1](../../src/anti_fp.c#L1) | language `c` | coverage 73.9% | [API index](../index.md)

## Contents

- **Functions:** [`fp_coarsen_time_ms`](#fp_coarsen_time_ms), [`fp_user_agent`](#fp_user_agent), [`fp_accept_language`](#fp_accept_language), [`fp_accept_language_header`](#fp_accept_language_header), [`fp_timezone`](#fp_timezone), [`fp_platform`](#fp_platform), [`fp_vendor`](#fp_vendor), [`fp_hardware_concurrency`](#fp_hardware_concurrency), [`fp_device_memory_gb`](#fp_device_memory_gb), [`fp_app_version`](#fp_app_version), [`fp_app_code_name`](#fp_app_code_name), [`fp_product`](#fp_product), [`fp_app_name`](#fp_app_name), [`fp_product_sub`](#fp_product_sub), [`fp_oscpu`](#fp_oscpu), [`fp_build_id`](#fp_build_id), [`fp_max_touch_points`](#fp_max_touch_points), [`fp_on_line`](#fp_on_line), [`fp_cookie_enabled`](#fp_cookie_enabled), [`fp_bucket_screen`](#fp_bucket_screen), [`fp_perturb`](#fp_perturb), [`fp_origin_key`](#fp_origin_key)

## Functions

<a id="fp_coarsen_time_ms"></a>

### `fp_coarsen_time_ms`

`function` | [src/anti_fp.c:17](../../src/anti_fp.c#L17)

```c
uint64_t fp_coarsen_time_ms(uint64_t raw_ms)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `raw_ms` | `uint64_t` |  |  |

**Returns:** `uint64_t`

---

<a id="fp_user_agent"></a>

### `fp_user_agent`

`function` `const` | [src/anti_fp.c:23](../../src/anti_fp.c#L23)

```c
const char *fp_user_agent(void)
```

**Returns:** `char *`

---

<a id="fp_accept_language"></a>

### `fp_accept_language`

`function` `const` | [src/anti_fp.c:27](../../src/anti_fp.c#L27)

```c
const char *fp_accept_language(void)
```

**Returns:** `char *`

---

<a id="fp_accept_language_header"></a>

### `fp_accept_language_header`

`function` `const` | [src/anti_fp.c:31](../../src/anti_fp.c#L31)

```c
const char *fp_accept_language_header(void)
```

list form, e.g.

"en-US,en"

**Returns:** `char *`

> **Inherited:** Documentation from [`fp_accept_language_header`](#fp_accept_language_header) (include/anti_fp.h:59).

---

<a id="fp_timezone"></a>

### `fp_timezone`

`function` `const` | [src/anti_fp.c:35](../../src/anti_fp.c#L35)

```c
const char *fp_timezone(void)
```

HTTP header value, e.g.

"en-US,en;q=0.5"

**Returns:** `char *`

> **Inherited:** Documentation from [`fp_timezone`](#fp_timezone) (include/anti_fp.h:60).

---

<a id="fp_platform"></a>

### `fp_platform`

`function` `const` | [src/anti_fp.c:39](../../src/anti_fp.c#L39)

```c
const char *fp_platform(void)
```

"UTC"

**Returns:** `char *`

> **Inherited:** Documentation from [`fp_platform`](#fp_platform) (include/anti_fp.h:61).

---

<a id="fp_vendor"></a>

### `fp_vendor`

`function` `const` | [src/anti_fp.c:43](../../src/anti_fp.c#L43)

```c
const char *fp_vendor(void)
```

"Linux x86_64" (consistent with the UA)

**Returns:** `char *`

> **Inherited:** Documentation from [`fp_vendor`](#fp_vendor) (include/anti_fp.h:62).

---

<a id="fp_hardware_concurrency"></a>

### `fp_hardware_concurrency`

`function` | [src/anti_fp.c:47](../../src/anti_fp.c#L47)

```c
int fp_hardware_concurrency(void)
```

"" (no vendor; minimal entropy)

**Returns:** `int`

> **Inherited:** Documentation from [`fp_hardware_concurrency`](#fp_hardware_concurrency) (include/anti_fp.h:63).

---

<a id="fp_device_memory_gb"></a>

### `fp_device_memory_gb`

`function` | [src/anti_fp.c:51](../../src/anti_fp.c#L51)

```c
int fp_device_memory_gb(void)
```

**Returns:** `int`

---

<a id="fp_app_version"></a>

### `fp_app_version`

`function` `const` | [src/anti_fp.c:57](../../src/anti_fp.c#L57)

```c
const char *fp_app_version(void)
```

**Returns:** `char *`

---

<a id="fp_app_code_name"></a>

### `fp_app_code_name`

`function` `const` | [src/anti_fp.c:61](../../src/anti_fp.c#L61)

```c
const char *fp_app_code_name(void)
```

same string as fp_user_agent()

**Returns:** `char *`

> **Inherited:** Documentation from [`fp_app_code_name`](#fp_app_code_name) (include/anti_fp.h:71).

---

<a id="fp_product"></a>

### `fp_product`

`function` `const` | [src/anti_fp.c:65](../../src/anti_fp.c#L65)

```c
const char *fp_product(void)
```

"Mozilla" (historic, all browsers)

**Returns:** `char *`

> **Inherited:** Documentation from [`fp_product`](#fp_product) (include/anti_fp.h:72).

---

<a id="fp_app_name"></a>

### `fp_app_name`

`function` `const` | [src/anti_fp.c:69](../../src/anti_fp.c#L69)

```c
const char *fp_app_name(void)
```

"Gecko" (Firefox engine identity)

**Returns:** `char *`

> **Inherited:** Documentation from [`fp_app_name`](#fp_app_name) (include/anti_fp.h:73).

---

<a id="fp_product_sub"></a>

### `fp_product_sub`

`function` `const` | [src/anti_fp.c:73](../../src/anti_fp.c#L73)

```c
const char *fp_product_sub(void)
```

"Netscape" (historic)

**Returns:** `char *`

> **Inherited:** Documentation from [`fp_product_sub`](#fp_product_sub) (include/anti_fp.h:74).

---

<a id="fp_oscpu"></a>

### `fp_oscpu`

`function` `const` | [src/anti_fp.c:77](../../src/anti_fp.c#L77)

```c
const char *fp_oscpu(void)
```

"20100101" (Gecko build date)

**Returns:** `char *`

> **Inherited:** Documentation from [`fp_oscpu`](#fp_oscpu) (include/anti_fp.h:75).

---

<a id="fp_build_id"></a>

### `fp_build_id`

`function` `const` | [src/anti_fp.c:81](../../src/anti_fp.c#L81)

```c
const char *fp_build_id(void)
```

"Linux x86_64" (consistent with UA)

**Returns:** `char *`

> **Inherited:** Documentation from [`fp_build_id`](#fp_build_id) (include/anti_fp.h:76).

---

<a id="fp_max_touch_points"></a>

### `fp_max_touch_points`

`function` | [src/anti_fp.c:85](../../src/anti_fp.c#L85)

```c
int fp_max_touch_points(void)
```

fixed Firefox build ID

**Returns:** `int`

> **Inherited:** Documentation from [`fp_max_touch_points`](#fp_max_touch_points) (include/anti_fp.h:77).

---

<a id="fp_on_line"></a>

### `fp_on_line`

`function` | [src/anti_fp.c:89](../../src/anti_fp.c#L89)

```c
int fp_on_line(void)
```

0 (desktop, no touch)

**Returns:** `int`

> **Inherited:** Documentation from [`fp_on_line`](#fp_on_line) (include/anti_fp.h:78).

---

<a id="fp_cookie_enabled"></a>

### `fp_cookie_enabled`

`function` | [src/anti_fp.c:93](../../src/anti_fp.c#L93)

```c
int fp_cookie_enabled(void)
```

1 (connected)

**Returns:** `int`

> **Inherited:** Documentation from [`fp_cookie_enabled`](#fp_cookie_enabled) (include/anti_fp.h:79).

---

<a id="fp_bucket_screen"></a>

### `fp_bucket_screen`

`function` | [src/anti_fp.c:99](../../src/anti_fp.c#L99)

```c
void fp_bucket_screen(int w, int h, int *out_w, int *out_h)
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

> **Inherited:** Documentation from [`fp_bucket_screen`](#fp_bucket_screen) (include/anti_fp.h:83).

---

<a id="fp_perturb"></a>

### `fp_perturb`

`function` | [src/anti_fp.c:128](../../src/anti_fp.c#L128)

```c
void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key)
```

Deterministic per-session readback poisoning (canvas/audio): flips only the least-significant bit of a sparse, key-selected subset of bytes.

Same (buf,key) => same output; different key => different output. NULL/len 0 = no-op.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `uint8_t *` |  |  |
| `len` | `size_t` |  |  |
| `session_key` | `uint64_t` |  |  |

> **Inherited:** Documentation from [`fp_perturb`](#fp_perturb) (include/anti_fp.h:88).

---

<a id="fp_origin_key"></a>

### `fp_origin_key`

`function` | [src/anti_fp.c:139](../../src/anti_fp.c#L139)

```c
uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain)
```

Derives the per-origin readback key from the per-session secret and a site's registrable domain (eTLD+1).

Same (session_key, domain) => same key (poisoning is stable within a site); different domains under the same session => different keys with overwhelming probability (canvas/audio noise is not linkable across sites, defeating cross-origin fingerprint linking). registrable_domain NULL or "" collapses to a single namespace (its own stable key, distinct from any real domain); never aborts, never leaks. Pure: no I/O, no allocation. The caller (tab worker) computes the eTLD+1 via request_policy and passes it here.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `session_key` | `uint64_t` |  |  |
| `registrable_domain` | `char *` |  |  |

**Returns:** `uint64_t`

> **Inherited:** Documentation from [`fp_origin_key`](#fp_origin_key) (include/anti_fp.h:98).

---
