# `src/secure_fetch.c`

> Source: [src/secure_fetch.c:1](../../src/secure_fetch.c#L1) | language `c` | coverage 25.6% | [API index](../index.md)

## Contents

- **Structs:** [`body_sink`](#body_sink), [`tls_capture`](#tls_capture), [`fetch_ctx`](#fetch_ctx), [`sf_ws`](#sf_ws)
- **Type Aliases:** [`sink`](#sink)
- **Functions:** [`sf_global_init`](#sf_global_init), [`sf_cookie_line_matches`](#sf_cookie_line_matches), [`sf_cookie_header_for`](#sf_cookie_header_for), [`sf_cookie_put`](#sf_cookie_put), [`sf_config_default`](#sf_config_default), [`sf_user_agent_or_default`](#sf_user_agent_or_default), [`sf_impersonate_kex_groups`](#sf_impersonate_kex_groups), [`sf_impersonate_tls13_ciphers`](#sf_impersonate_tls13_ciphers), [`sf_validate_url`](#sf_validate_url), [`sf_check_tls_version`](#sf_check_tls_version), [`sf_check_group_is_pq`](#sf_check_group_is_pq), [`sf_check_chain_policy`](#sf_check_chain_policy), [`sf_enforce_policy`](#sf_enforce_policy), [`sf_is_redirect_code`](#sf_is_redirect_code), [`sf_parse_location_header`](#sf_parse_location_header), [`sf_resolve_redirect`](#sf_resolve_redirect), [`module`](#module), [`sf_response_free`](#sf_response_free), [`progress`](#progress), [`database`](#database), [`group`](#group), [`this`](#this), [`redirect`](#redirect), [`sf_get`](#sf_get), [`sf_post`](#sf_post), [`sf_get_follow`](#sf_get_follow), [`sf_ws_url_check`](#sf_ws_url_check), [`sf_ws_open`](#sf_ws_open), [`sf_ws_send`](#sf_ws_send), [`sf_ws_recv`](#sf_ws_recv), [`sf_ws_fd`](#sf_ws_fd), [`sf_ws_close`](#sf_ws_close)
- **Macros:** [`_POSIX_C_SOURCE`](#_posix_c_source)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class body_sink
    <<struct>> body_sink
    class tls_capture
    <<struct>> tls_capture
    class sink
    <<type_alias>> sink
    class fetch_ctx
    <<struct>> fetch_ctx
    class sf_ws
    <<struct>> sf_ws
```

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_secure_fetch_c__sf_cookie_header_for(["sf_cookie_header_for"])
    n_src_secure_fetch_c__sf_cookie_line_matches(["sf_cookie_line_matches"])
    n_src_secure_fetch_c__sf_enforce_policy(["sf_enforce_policy"])
    n_src_secure_fetch_c__sf_check_chain_policy(["sf_check_chain_policy"])
    n_src_secure_fetch_c__sf_check_group_is_pq(["sf_check_group_is_pq"])
    n_src_secure_fetch_c__sf_check_tls_version(["sf_check_tls_version"])
    n_src_secure_fetch_c__sf_get_follow(["sf_get_follow"])
    n_src_secure_fetch_c__sf_get(["sf_get"])
    n_src_secure_fetch_c__sf_is_redirect_code(["sf_is_redirect_code"])
    n_src_secure_fetch_c__sf_resolve_redirect(["sf_resolve_redirect"])
    n_src_secure_fetch_c__sf_response_free(["sf_response_free"])
    n_src_secure_fetch_c__sf_ws_url_check(["sf_ws_url_check"])
    n_src_secure_fetch_c__sf_validate_url(["sf_validate_url"])
    n_src_secure_fetch_c__sf_ws_open(["sf_ws_open"])
    n_src_secure_fetch_c__sf_config_default(["sf_config_default"])
    n_src_css_color_c__strncmp["css_color.strncmp"]
    n_src_url_c__url_validate_https["url.url_validate_https"]
    n_src_url_c__url_resolve_https["url.url_resolve_https"]
    n_src_secure_fetch_c__sf_cookie_header_for --> n_src_secure_fetch_c__sf_cookie_line_matches
    n_src_secure_fetch_c__sf_enforce_policy --> n_src_secure_fetch_c__sf_check_chain_policy
    n_src_secure_fetch_c__sf_enforce_policy --> n_src_secure_fetch_c__sf_check_group_is_pq
    n_src_secure_fetch_c__sf_enforce_policy --> n_src_secure_fetch_c__sf_check_tls_version
    n_src_secure_fetch_c__sf_get_follow --> n_src_secure_fetch_c__sf_get
    n_src_secure_fetch_c__sf_get_follow --> n_src_secure_fetch_c__sf_is_redirect_code
    n_src_secure_fetch_c__sf_get_follow --> n_src_secure_fetch_c__sf_resolve_redirect
    n_src_secure_fetch_c__sf_get_follow --> n_src_secure_fetch_c__sf_response_free
    n_src_secure_fetch_c__sf_ws_url_check --> n_src_secure_fetch_c__sf_validate_url
    n_src_secure_fetch_c__sf_ws_open --> n_src_secure_fetch_c__sf_config_default
    n_src_secure_fetch_c__sf_ws_open --> n_src_secure_fetch_c__sf_enforce_policy
    n_src_secure_fetch_c__sf_ws_open --> n_src_secure_fetch_c__sf_ws_url_check
    n_src_secure_fetch_c__sf_cookie_line_matches -.-> n_src_css_color_c__strncmp
    n_src_secure_fetch_c__sf_validate_url -.-> n_src_url_c__url_validate_https
    n_src_secure_fetch_c__sf_resolve_redirect -.-> n_src_url_c__url_resolve_https
```

## Structs

<a id="body_sink"></a>

### `body_sink`

`struct` | [src/secure_fetch.c:434](../../src/secure_fetch.c#L434)

```c
typedef struct body_sink
```

---

<a id="tls_capture"></a>

### `tls_capture`

`struct` | [src/secure_fetch.c:447](../../src/secure_fetch.c#L447)

```c
typedef struct tls_capture
```

Snapshot of the negotiated TLS state. curl exposes the live SSL* only while a transfer is in progress (via CURLINFO_TLS_SSL_PTR); after curl_easy_perform returns, internals is NULL.

So we capture from inside the header/write callbacks and copy everything into owned storage, since SSL_get0_group_name / the chain pointers are only valid while the SSL object lives.

---

<a id="fetch_ctx"></a>

### `fetch_ctx`

`struct` | [src/secure_fetch.c:457](../../src/secure_fetch.c#L457)

```c
typedef struct fetch_ctx
```

---

<a id="sf_ws"></a>

### `sf_ws`

`struct` | [src/secure_fetch.c:1098](../../src/secure_fetch.c#L1098)

```c
struct sf_ws
```

---

## Type Aliases

<a id="sink"></a>

### `sink`

`type_alias` | [src/secure_fetch.c:456](../../src/secure_fetch.c#L456)

```c
typedef struct fetch_ctx { body_sink sink;
```

---

## Functions

<a id="sf_global_init"></a>

### `sf_global_init`

`function` | [src/secure_fetch.c:81](../../src/secure_fetch.c#L81)

```c
void sf_global_init(void)
```

Initialises process-global transport state (libcurl/OpenSSL) once, from the main thread, before any concurrent sf_get/sf_post. libcurl's implicit init on first use is NOT thread-safe, so an orchestrator that fetches from worker threads MUST call this first.

Idempotent; safe to call more than once. A single-threaded caller need not call it. There is intentionally no cleanup: it would race in-flight fetches at shutdown, and the OS reclaims everything on exit.

> **Inherited:** Documentation from [`sf_global_init`](#sf_global_init) (include/secure_fetch.h:204).

---

<a id="sf_cookie_line_matches"></a>

### `sf_cookie_line_matches`

`function` | [src/secure_fetch.c:96](../../src/secure_fetch.c#L96)

```c
int sf_cookie_line_matches(const char *line, const char *host, const char *path, long now, char *out, size_t outsz)
```

Pure: parses one CURLINFO_COOKIELIST Netscape line ("domain\\tflag\\tpath\\tsecure\\t expiry\\tname\\tvalue"); if the cookie applies to (host, path), is not HttpOnly and is unexpired at `now`, writes "name=value" to out (bounded) and returns 1, else 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `line` | `char *` |  |  |
| `host` | `char *` |  |  |
| `path` | `char *` |  |  |
| `now` | `long` |  |  |
| `out` | `char *` |  |  |
| `outsz` | `size_t` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`sf_cookie_line_matches`](#sf_cookie_line_matches) (include/secure_fetch.h:222).

*Calls:* [`strncmp`](src.css_color.c.md#strncmp)

*Called by:* [`sf_cookie_header_for`](#sf_cookie_header_for)

---

<a id="sf_cookie_header_for"></a>

### `sf_cookie_header_for`

`function` | [src/secure_fetch.c:166](../../src/secure_fetch.c#L166)

```c
size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `url` | `char *` |  |  |
| `out` | `char *` |  |  |
| `outsz` | `size_t` |  |  |

**Returns:** `size_t`

*Calls:* [`sf_cookie_line_matches`](#sf_cookie_line_matches)

---

<a id="sf_cookie_put"></a>

### `sf_cookie_put`

`function` | [src/secure_fetch.c:195](../../src/secure_fetch.c#L195)

```c
void sf_cookie_put(const char *url, const char *namevalue)
```

Injects a JS-set cookie ("name=value") into the shared jar, scoped to url's host, as if it arrived via Set-Cookie -- so a trusted page's document.cookie writes reach the next request. namevalue past the first ';' (attributes) is ignored.

No-op on malformed input.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `url` | `char *` |  |  |
| `namevalue` | `char *` |  |  |

> **Inherited:** Documentation from [`sf_cookie_put`](#sf_cookie_put) (include/secure_fetch.h:217).

---

<a id="sf_config_default"></a>

### `sf_config_default`

`function` | [src/secure_fetch.c:216](../../src/secure_fetch.c#L216)

```c
sf_config sf_config_default(void)
```

**Returns:** `sf_config`

*Called by:* [`HL_JS_NAV_MAX`](src.freedom.c.md#hl_js_nav_max), [`gets`](src.freedom.c.md#gets), [`sf_ws_open`](#sf_ws_open), [`wh_open_async`](src.ws_hub.c.md#wh_open_async)

---

<a id="sf_user_agent_or_default"></a>

### `sf_user_agent_or_default`

`function` `const` | [src/secure_fetch.c:241](../../src/secure_fetch.c#L241)

```c
const char *sf_user_agent_or_default(const char *ua)
```

Returns ua when it is a non-empty string, else SF_DEFAULT_USER_AGENT.

Pure: the single place that resolves the effective User-Agent, so the orchestrator never sends an empty header and the default lives in one tested spot.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ua` | `char *` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`sf_user_agent_or_default`](#sf_user_agent_or_default) (include/secure_fetch.h:231).

---

<a id="sf_impersonate_kex_groups"></a>

### `sf_impersonate_kex_groups`

`function` `const` | [src/secure_fetch.c:245](../../src/secure_fetch.c#L245)

```c
const char *sf_impersonate_kex_groups(void)
```

The interim impersonation ClientHello strings (pure; single source of truth so the shaping is unit-testable without a live handshake).

Both are classical (no MLKEM).

**Returns:** `char *`

> **Inherited:** Documentation from [`sf_impersonate_kex_groups`](#sf_impersonate_kex_groups) (include/secure_fetch.h:235).

---

<a id="sf_impersonate_tls13_ciphers"></a>

### `sf_impersonate_tls13_ciphers`

`function` `const` | [src/secure_fetch.c:246](../../src/secure_fetch.c#L246)

```c
const char *sf_impersonate_tls13_ciphers(void)
```

**Returns:** `char *`

---

<a id="sf_validate_url"></a>

### `sf_validate_url`

`function` | [src/secure_fetch.c:250](../../src/secure_fetch.c#L250)

```c
sf_status sf_validate_url(const char *url)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `url` | `char *` |  |  |

**Returns:** `sf_status`

*Calls:* [`url_validate_https`](src.url.c.md#url_validate_https)

*Called by:* [`sf_ws_url_check`](#sf_ws_url_check)

---

<a id="sf_check_tls_version"></a>

### `sf_check_tls_version`

`function` | [src/secure_fetch.c:270](../../src/secure_fetch.c#L270)

```c
sf_status sf_check_tls_version(const char *negotiated_version)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `negotiated_version` | `char *` |  |  |

**Returns:** `sf_status`

*Called by:* [`sf_enforce_policy`](#sf_enforce_policy)

---

<a id="sf_check_group_is_pq"></a>

### `sf_check_group_is_pq`

`function` | [src/secure_fetch.c:275](../../src/secure_fetch.c#L275)

```c
sf_status sf_check_group_is_pq(const char *negotiated_group)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `negotiated_group` | `char *` |  |  |

**Returns:** `sf_status`

*Called by:* [`sf_enforce_policy`](#sf_enforce_policy)

---

<a id="sf_check_chain_policy"></a>

### `sf_check_chain_policy`

`function` | [src/secure_fetch.c:284](../../src/secure_fetch.c#L284)

```c
sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `chain` | `sf_chain_info *` |  |  |
| `policy` | `sf_policy` |  |  |

**Returns:** `sf_status`

*Called by:* [`sf_enforce_policy`](#sf_enforce_policy)

---

<a id="sf_enforce_policy"></a>

### `sf_enforce_policy`

`function` | [src/secure_fetch.c:294](../../src/secure_fetch.c#L294)

```c
sf_status sf_enforce_policy(const char *tls_version, const char *group, const sf_chain_info *chain, sf_policy policy)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `tls_version` | `char *` |  |  |
| `group` | `char *` |  |  |
| `chain` | `sf_chain_info *` |  |  |
| `policy` | `sf_policy` |  |  |

**Returns:** `sf_status`

*Calls:* [`sf_check_chain_policy`](#sf_check_chain_policy), [`sf_check_group_is_pq`](#sf_check_group_is_pq), [`sf_check_tls_version`](#sf_check_tls_version)

*Called by:* [`sf_ws_open`](#sf_ws_open)

---

<a id="sf_is_redirect_code"></a>

### `sf_is_redirect_code`

`function` | [src/secure_fetch.c:334](../../src/secure_fetch.c#L334)

```c
int sf_is_redirect_code(long http_code)
```

Nonzero only for HTTP redirect status codes (301, 302, 303, 307, 308).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `http_code` | `long` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`sf_is_redirect_code`](#sf_is_redirect_code) (include/secure_fetch.h:267).

*Called by:* [`sf_get_follow`](#sf_get_follow)

---

<a id="sf_parse_location_header"></a>

### `sf_parse_location_header`

`function` | [src/secure_fetch.c:341](../../src/secure_fetch.c#L341)

```c
sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `header_line` | `char *` |  |  |
| `out` | `char *` |  |  |
| `outsz` | `size_t` |  |  |

**Returns:** `sf_status`

---

<a id="sf_resolve_redirect"></a>

### `sf_resolve_redirect`

`function` | [src/secure_fetch.c:359](../../src/secure_fetch.c#L359)

```c
sf_status sf_resolve_redirect(const char *base_url, const char *location, char *out, size_t outsz)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `base_url` | `char *` |  |  |
| `location` | `char *` |  |  |
| `out` | `char *` |  |  |
| `outsz` | `size_t` |  |  |

**Returns:** `sf_status`

*Calls:* [`url_resolve_https`](src.url.c.md#url_resolve_https)

*Called by:* [`sf_get_follow`](#sf_get_follow)

---

<a id="module"></a>

### `module`

`function` | [src/secure_fetch.c:364](../../src/secure_fetch.c#L364)

```c
* pure url module (DRY);
```

**Returns:** `* pure url`

---

<a id="sf_response_free"></a>

### `sf_response_free`

`function` | [src/secure_fetch.c:411](../../src/secure_fetch.c#L411)

```c
void sf_response_free(sf_response *resp)
```

Idempotent; safe on a zero-initialised struct and safe to call twice.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `resp` | `sf_response *` |  |  |

> **Inherited:** Documentation from [`sf_response_free`](#sf_response_free) (include/secure_fetch.h:344).

*Called by:* [`sf_get_follow`](#sf_get_follow)

---

<a id="progress"></a>

### `progress`

`function` | [src/secure_fetch.c:443](../../src/secure_fetch.c#L443)

```c
* transfer is in progress (via CURLINFO_TLS_SSL_PTR);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `CURLINFO_TLS_SSL_PTR` | `via` |  |  |

**Returns:** `* transfer is in`

---

<a id="database"></a>

### `database`

`function` | [src/secure_fetch.c:485](../../src/secure_fetch.c#L485)

```c
* NID in the OBJ database (OBJ_sn2nid returns 0 on OpenSSL 3.6), so the * NID path below reports every PQ-hybrid handshake as unnamed and the * policy check rejects it -- exactly the sites doing TLS r
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `OpenSSL` | `OBJ_sn2nid returns 0 on 3.6` |  |  |

**Returns:** `* NID in the OBJ`

---

<a id="group"></a>

### `group`

`function` | [src/secure_fetch.c:499](../../src/secure_fetch.c#L499)

```c
* group (for both TLS 1.2 ECDHE and TLS 1.3). */ nid = SSL_get_shared_group(ssl, 0);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `TLS` | `for both TLS 1.2 ECDHE and 1.3` |  |  |

**Returns:** `*`

---

<a id="this"></a>

### `this`

`function` | [src/secure_fetch.c:531](../../src/secure_fetch.c#L531)

```c
* We must NOT hardcode this (e.g., to "X25519"), as it breaks the checks. * PQ for groups that are not X25519 and causes false rejections. * If it is NULL (no group / not TLS 1.3 / no PFS), we copy ""
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `g` | `e. .` |  |  |
| `X25519` | `to " "` |  |  |

**Returns:** `* We must NOT hardcode`

---

<a id="redirect"></a>

### `redirect`

`function` | [src/secure_fetch.c:811](../../src/secure_fetch.c#L811)

```c
* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a * different orig...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `is` | `CURLOPT_UNRESTRICTED_AUTH 0` |  |  |

**Returns:** `*`

---

<a id="sf_get"></a>

### `sf_get`

`function` | [src/secure_fetch.c:1014](../../src/secure_fetch.c#L1014)

```c
sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `url` | `char *` |  |  |
| `cfg` | `sf_config *` |  |  |
| `out` | `sf_response *` |  |  |

**Returns:** `sf_status`

*Called by:* [`sf_get_follow`](#sf_get_follow)

---

<a id="sf_post"></a>

### `sf_post`

`function` | [src/secure_fetch.c:1018](../../src/secure_fetch.c#L1018)

```c
sf_status sf_post(const char *url, const sf_config *cfg, const void *body, size_t body_len, const char *content_type, sf_response *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `url` | `char *` |  |  |
| `cfg` | `sf_config *` |  |  |
| `body` | `void *` |  |  |
| `body_len` | `size_t` |  |  |
| `content_type` | `char *` |  |  |
| `out` | `sf_response *` |  |  |

**Returns:** `sf_status`

*Called by:* [`GET`](gui.browser_ui.c.md#get), [`gets`](src.freedom.c.md#gets)

---

<a id="sf_get_follow"></a>

### `sf_get_follow`

`function` | [src/secure_fetch.c:1032](../../src/secure_fetch.c#L1032)

```c
sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out, int max_redirects)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `url` | `char *` |  |  |
| `cfg` | `sf_config *` |  |  |
| `out` | `sf_response *` |  |  |
| `max_redirects` | `int` |  |  |

**Returns:** `sf_status`

*Calls:* [`sf_get`](#sf_get), [`sf_is_redirect_code`](#sf_is_redirect_code), [`sf_resolve_redirect`](#sf_resolve_redirect), [`sf_response_free`](#sf_response_free)

*Called by:* [`HL_JS_NAV_MAX`](src.freedom.c.md#hl_js_nav_max), [`gets`](src.freedom.c.md#gets)

---

<a id="sf_ws_url_check"></a>

### `sf_ws_url_check`

`function` | [src/secure_fetch.c:1105](../../src/secure_fetch.c#L1105)

```c
sf_status sf_ws_url_check(const char *url)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `url` | `char *` |  |  |

**Returns:** `sf_status`

*Calls:* [`sf_validate_url`](#sf_validate_url)

*Called by:* [`sf_ws_open`](#sf_ws_open)

---

<a id="sf_ws_open"></a>

### `sf_ws_open`

`function` | [src/secure_fetch.c:1126](../../src/secure_fetch.c#L1126)

```c
sf_status sf_ws_open(const char *url, const sf_config *cfg, sf_ws **out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `url` | `char *` |  |  |
| `cfg` | `sf_config *` |  |  |
| `out` | `sf_ws **` |  |  |

**Returns:** `sf_status`

*Calls:* [`sf_config_default`](#sf_config_default), [`sf_enforce_policy`](#sf_enforce_policy), [`sf_ws_url_check`](#sf_ws_url_check)

---

<a id="sf_ws_send"></a>

### `sf_ws_send`

`function` | [src/secure_fetch.c:1181](../../src/secure_fetch.c#L1181)

```c
sf_status sf_ws_send(sf_ws *ws, const void *data, size_t len, int binary)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ws` | `sf_ws *` |  |  |
| `data` | `void *` |  |  |
| `len` | `size_t` |  |  |
| `binary` | `int` |  |  |

**Returns:** `sf_status`

*Called by:* [`wh_send`](src.ws_hub.c.md#wh_send)

---

<a id="sf_ws_recv"></a>

### `sf_ws_recv`

`function` | [src/secure_fetch.c:1204](../../src/secure_fetch.c#L1204)

```c
sf_status sf_ws_recv(sf_ws *ws, void *buf, size_t cap, size_t *got, int *flags, size_t *left)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ws` | `sf_ws *` |  |  |
| `buf` | `void *` |  |  |
| `cap` | `size_t` |  |  |
| `got` | `size_t *` |  |  |
| `flags` | `int *` |  |  |
| `left` | `size_t *` |  |  |

**Returns:** `sf_status`

*Called by:* [`wh_on_readable`](src.ws_hub.c.md#wh_on_readable)

---

<a id="sf_ws_fd"></a>

### `sf_ws_fd`

`function` | [src/secure_fetch.c:1226](../../src/secure_fetch.c#L1226)

```c
int sf_ws_fd(const sf_ws *ws)
```

The connection's socket for poll(), or -1.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ws` | `sf_ws *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`sf_ws_fd`](#sf_ws_fd) (include/secure_fetch.h:317).

---

<a id="sf_ws_close"></a>

### `sf_ws_close`

`function` | [src/secure_fetch.c:1233](../../src/secure_fetch.c#L1233)

```c
void sf_ws_close(sf_ws *ws)
```

Sends a close frame when possible and frees the connection.

NULL is a no-op.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ws` | `sf_ws *` |  |  |

> **Inherited:** Documentation from [`sf_ws_close`](#sf_ws_close) (include/secure_fetch.h:320).

---

## Macros

<a id="_posix_c_source"></a>

### `_POSIX_C_SOURCE`

`macro` | [src/secure_fetch.c:12](../../src/secure_fetch.c#L12)

```c
#define _POSIX_C_SOURCE
```

---
