# `include/tab.h`

> Source: [include/tab.h:1](../../include/tab.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

## Contents

- **Structs:** [`tab_hist_op`](#tab_hist_op), [`tab_ws_op`](#tab_ws_op), [`tab_page`](#tab_page), [`tab_eval_result`](#tab_eval_result), [`tab_image`](#tab_image), [`tab_anchor`](#tab_anchor)
- **Enums:** [`tab_status`](#tab_status), [`tab_ws_kind`](#tab_ws_kind), [`tab_ws_event_kind`](#tab_ws_event_kind)
- **Type Aliases:** [`tab`](#tab), [`replace`](#replace), [`kind`](#kind), [`kind`](#kind)
- **Functions:** [`tab_worker_dispatch`](#tab_worker_dispatch), [`tab_open`](#tab_open), [`tab_parse_worker_args`](#tab_parse_worker_args), [`tab_prewarm`](#tab_prewarm), [`tab_prewarmed`](#tab_prewarmed), [`tab_prewarmed_pid`](#tab_prewarmed_pid), [`tab_shutdown_spare`](#tab_shutdown_spare), [`out_status`](#out_status), [`tab_set_fetcher`](#tab_set_fetcher), [`tab_inflight_request_headers`](#tab_inflight_request_headers), [`tab_report_response_headers`](#tab_report_response_headers), [`bytes`](#bytes), [`tab_set_css_sink`](#tab_set_css_sink), [`free_ctx`](#free_ctx), [`tab_set_net_allowed`](#tab_set_net_allowed), [`none`](#none), [`tab_page_keep_view`](#tab_page_keep_view), [`tab_set_op_net_budget_ms`](#tab_set_op_net_budget_ms), [`tab_async_fd`](#tab_async_fd), [`tab_async_busy`](#tab_async_busy), [`jar`](#jar), [`tab_set_cookies`](#tab_set_cookies), [`origin`](#origin), [`tab_set_storage`](#tab_set_storage), [`exclusively`](#exclusively), [`tab_set_viewport_w`](#tab_set_viewport_w), [`load`](#load), [`tab_set_identity`](#tab_set_identity), [`tab_last_subreq_stats`](#tab_last_subreq_stats), [`tab_subreq_permitted`](#tab_subreq_permitted), [`view`](#view), [`string`](#string), [`granted`](#granted), [`returned`](#returned), [`popstate`](#popstate), [`preorder`](#preorder), [`one`](#one), [`tab_anchor_free`](#tab_anchor_free), [`decode`](#decode), [`tab_alive`](#tab_alive), [`tab_child_pid`](#tab_child_pid), [`tab_close`](#tab_close), [`tab_page_free`](#tab_page_free), [`tab_eval_result_free`](#tab_eval_result_free), [`tab_image_free`](#tab_image_free)
- **Macros:** [`TAB_MAX_INPUT`](#tab_max_input), [`TAB_ANCHOR_REPLACE`](#tab_anchor_replace)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class tab_status
    <<enum>> tab_status
    class tab
    <<type_alias>> tab
    class replace
    <<type_alias>> replace
    class tab_hist_op
    <<struct>> tab_hist_op
    class tab_ws_kind
    <<enum>> tab_ws_kind
    class tab_ws_event_kind
    <<enum>> tab_ws_event_kind
    class kind
    <<type_alias>> kind
    class tab_ws_op
    <<struct>> tab_ws_op
    class tab_page
    <<struct>> tab_page
    class tab_eval_result
    <<struct>> tab_eval_result
    class tab_image
    <<struct>> tab_image
    class tab_image_width
    <<type_alias>> tab_image_width
    class kind
    <<type_alias>> kind
    class tab_anchor
    <<struct>> tab_anchor
```

## Structs

<a id="tab_hist_op"></a>

### `tab_hist_op`

`struct` | [include/tab.h:55](../../include/tab.h#L55)

```c
typedef struct tab_hist_op
```

One history operation the page's JS performed (spec/js_dom.md 7e): pushState (replace == 0) or replaceState (replace == 1) to url, an absolute same-origin URL the parent re-validated against the page URL.

Owned by the tab_page.

---

<a id="tab_ws_op"></a>

### `tab_ws_op`

`struct` | [include/tab.h:73](../../include/tab.h#L73)

```c
typedef struct tab_ws_op
```

---

<a id="tab_page"></a>

### `tab_page`

`struct` | [include/tab.h:80](../../include/tab.h#L80)

```c
typedef struct tab_page
```

---

<a id="tab_eval_result"></a>

### `tab_eval_result`

`struct` | [include/tab.h:150](../../include/tab.h#L150)

```c
typedef struct tab_eval_result
```

Result of evaluating script: the value, or a JS error message.

---

<a id="tab_image"></a>

### `tab_image`

`struct` | [include/tab.h:163](../../include/tab.h#L163)

```c
typedef struct tab_image
```

Pixels of a decoded image, produced inside the confined worker. data is owned and holds premultiplied ARGB32 (Cairo's CAIRO_FORMAT_ARGB32 layout: bytes B,G,R,A; stride == width*4). data == NULL means the worker could not decode the bytes (not a PNG, corrupt, or out of bounds): the caller shows the placeholder.

**Members**

| Member | Kind | Summary |
|---|---|---|
| [`width`](#tab_image-width) | type_alias | Pixels of a decoded image, produced inside the confined worker. data is owned and holds premultiplied ARGB32 (Cairo's CAIRO_FORMAT_ARGB32 layout: bytes... |

<a id="tab_image-width"></a>

#### `tab_image.width`

`type_alias` | [include/tab.h:163](../../include/tab.h#L163)

```c
typedef struct tab_image { uint32_t width;
```

Pixels of a decoded image, produced inside the confined worker. data is owned and holds premultiplied ARGB32 (Cairo's CAIRO_FORMAT_ARGB32 layout: bytes B,G,R,A; stride == width*4). data == NULL means the worker could not decode the bytes (not a PNG, corrupt, or out of bounds): the caller shows the placeholder.

---

<a id="tab_anchor"></a>

### `tab_anchor`

`struct` | [include/tab.h:435](../../include/tab.h#L435)

```c
typedef struct tab_anchor
```

The indicated part of the loaded document for fragment (spec/anchor.md, OP_ANCHOR). out->kind is an anc_kind; for ANC_ELEMENT out->handles holds the target's subtree in preorder (out->nsub handles) followed by the elements after it, at most ANC_MAX_HANDLES -- live DOM handles, the same ids the view carries. push_url (NULL or "" for none) is the same-document URL the parent just pushed: a page with JS records it in its own history, moves location and dispatches hashchange, and *page then receives the re-derived view (release with tab_page_free); otherwise *page is empty.

A fragment of ANC_MAX_FRAGMENT bytes or more resolves to ANC_NONE without asking. out must be released with tab_anchor_free (idempotent).

---

## Enums

<a id="tab_status"></a>

### `tab_status`

`enum` | [include/tab.h:32](../../include/tab.h#L32)

```c
typedef enum tab_status
```

---

<a id="tab_ws_kind"></a>

### `tab_ws_kind`

`enum` | [include/tab.h:62](../../include/tab.h#L62)

```c
typedef enum tab_ws_kind
```

One WebSocket operation a trusted page's JS recorded (spec/js_dom.md 7f); the trusted parent owns the socket.

Kinds mirror jd_ws_kind. Owned by the tab_page.

---

<a id="tab_ws_event_kind"></a>

### `tab_ws_event_kind`

`enum` | [include/tab.h:68](../../include/tab.h#L68)

```c
typedef enum tab_ws_event_kind
```

---

## Type Aliases

<a id="tab"></a>

### `tab`

`type_alias` | [include/tab.h:47](../../include/tab.h#L47)

```c
typedef struct tab tab;
```

Opaque parent-side handle to a tab worker.

---

<a id="replace"></a>

### `replace`

`type_alias` | [include/tab.h:55](../../include/tab.h#L55)

```c
typedef struct tab_hist_op { int replace;
```

One history operation the page's JS performed (spec/js_dom.md 7e): pushState (replace == 0) or replaceState (replace == 1) to url, an absolute same-origin URL the parent re-validated against the page URL.

Owned by the tab_page.

---

<a id="kind"></a>

### `kind`

`type_alias` | [include/tab.h:72](../../include/tab.h#L72)

```c
typedef struct tab_ws_op { int kind;
```

---

<a id="kind"></a>

### `kind`

`type_alias` | [include/tab.h:435](../../include/tab.h#L435)

```c
typedef struct tab_anchor { int kind;
```

The indicated part of the loaded document for fragment (spec/anchor.md, OP_ANCHOR). out->kind is an anc_kind; for ANC_ELEMENT out->handles holds the target's subtree in preorder (out->nsub handles) followed by the elements after it, at most ANC_MAX_HANDLES -- live DOM handles, the same ids the view carries. push_url (NULL or "" for none) is the same-document URL the parent just pushed: a page with JS records it in its own history, moves location and dispatches hashchange, and *page then receives the re-derived view (release with tab_page_free); otherwise *page is empty.

A fragment of ANC_MAX_FRAGMENT bytes or more resolves to ANC_NONE without asking. out must be released with tab_anchor_free (idempotent).

---

## Functions

<a id="tab_worker_dispatch"></a>

### `tab_worker_dispatch`

`function` | [include/tab.h:176](../../include/tab.h#L176)

```c
* Call tab_worker_dispatch(argc, argv) as the FIRST thing in main(): if argv is the * internal "--tab-worker <rfd> <wfd>" invocation it runs the confined worker loop on * those pipe fds and never retu
```

**Returns:** `* Call`

*Called by:* [`main`](src.freedom.c.md#main)

---

<a id="tab_open"></a>

### `tab_open`

`function` | [include/tab.h:180](../../include/tab.h#L180)

```c
* and reaches tab_open (the app and the test harness) must call this first. */ void tab_worker_dispatch(int argc, char **argv);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `harness` | `the app and the test` |  |  |

**Returns:** `* and reaches`

---

<a id="tab_parse_worker_args"></a>

### `tab_parse_worker_args`

`function` | [include/tab.h:187](../../include/tab.h#L187)

```c
int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd);
```

Pure validator of the worker handoff arguments (the security-relevant surface of the exec): returns nonzero and writes the two fds iff argv is exactly "<prog> --tab-worker <rfd> <wfd>" with both fds non-negative decimal integers within a sane bound.

No side effects; fail-closed (any malformation => 0).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char *const *` |  |  |
| `rfd` | `int *` |  |  |
| `wfd` | `int *` |  |  |

**Returns:** `int`

---

<a id="tab_prewarm"></a>

### `tab_prewarm`

`function` | [include/tab.h:196](../../include/tab.h#L196)

```c
void tab_prewarm(void);
```

Starts one idle, confined worker in advance so the next tab_open does not wait for fork + exec + sandbox setup (spec/tab.md "Worker de repuesto").

Idempotent; best-effort (a failed spawn just means tab_open spawns on demand). The spare has received no content.

---

<a id="tab_prewarmed"></a>

### `tab_prewarmed`

`function` | [include/tab.h:199](../../include/tab.h#L199)

```c
int tab_prewarmed(void);
```

1 while a spare worker is waiting for the next tab_open.

**Returns:** `int`

---

<a id="tab_prewarmed_pid"></a>

### `tab_prewarmed_pid`

`function` | [include/tab.h:202](../../include/tab.h#L202)

```c
int tab_prewarmed_pid(void);
```

Process id of that spare, 0 when there is none (diagnostics and tests).

**Returns:** `int`

---

<a id="tab_shutdown_spare"></a>

### `tab_shutdown_spare`

`function` | [include/tab.h:205](../../include/tab.h#L205)

```c
void tab_shutdown_spare(void);
```

Kills and reaps the spare, if any.

Safe to call when there is none.

---

<a id="out_status"></a>

### `out_status`

`function` | [include/tab.h:213](../../include/tab.h#L213)

```c
* On success return 0 and set *out_status (HTTP status), *out_body / *out_body_len * (malloc'd response bytes, tab frees with free()), *out_ctype (malloc'd Content-Type, * may be NULL). Return non-zer
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `status` | `HTTP` |  |  |

**Returns:** `* On success return 0 and set *`

---

<a id="tab_set_fetcher"></a>

### `tab_set_fetcher`

`function` | [include/tab.h:224](../../include/tab.h#L224)

```c
void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx);
```

Installs the subresource fetcher used for XHR/fetch (NULL clears it: requests are then refused). fn/ctx must outlive any tab_load_full call that may trigger a subresource.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `fn` | `tab_fetch_fn` |  |  |
| `ctx` | `void *` |  |  |

---

<a id="tab_inflight_request_headers"></a>

### `tab_inflight_request_headers`

`function` `const` | [include/tab.h:229](../../include/tab.h#L229)

```c
const char *tab_inflight_request_headers(void);
```

Inside a tab_fetch_fn call: the request headers the page attached to this XHR/fetch, already filtered by rp_sanitize_request_headers ("Name: value\n" lines), or NULL when it set none.

Valid only for the duration of that call, on the calling thread; NULL anywhere else.

**Returns:** `char *`

*Called by:* [`gets`](src.freedom.c.md#gets)

---

<a id="tab_report_response_headers"></a>

### `tab_report_response_headers`

`function` | [include/tab.h:234](../../include/tab.h#L234)

```c
void tab_report_response_headers(const char *lines);
```

Inside a tab_fetch_fn call: reports the response header lines ("name: value\n", no Set-Cookie) the page's XHR/fetch may read.

Copied (bounded); the fetcher keeps ownership of `lines`. Outside a fetcher call it is a no-op.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lines` | `char *` |  |  |

*Called by:* [`gets`](src.freedom.c.md#gets)

---

<a id="bytes"></a>

### `bytes`

`function` | [include/tab.h:238](../../include/tab.h#L238)

```c
* so the parent can retain the bytes (spec/webfont.md b3b feeds them to the * @font-face loader as extern sheets). url is the RAW worker-requested URL * (possibly relative: resolve it against the page
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sheets` | `spec/webfont.md b3b feeds them to the * @font-face loader as extern` |  |  |

**Returns:** `* so the parent can retain the`

---

<a id="tab_set_css_sink"></a>

### `tab_set_css_sink`

`function` | [include/tab.h:247](../../include/tab.h#L247)

```c
void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `fn` | `tab_css_sink_fn` |  |  |
| `ctx` | `void *` |  |  |

---

<a id="free_ctx"></a>

### `free_ctx`

`function` | [include/tab.h:254](../../include/tab.h#L254)

```c
* free_ctx(ctx) (may be NULL) runs once the tab is closed AND its last abandoned request ended, * so the fetcher may use ctx until then. ctx describes ONE page: a tab reused for another page * sets a
```

**Returns:** `*`

*Called by:* [`tab_set_async_fetcher`](src.tab.c.md#tab_set_async_fetcher)

---

<a id="tab_set_net_allowed"></a>

### `tab_set_net_allowed`

`function` | [include/tab.h:262](../../include/tab.h#L262)

```c
void tab_set_net_allowed(tab *t, int allowed);
```

Grants/revokes page-JS network access (XMLHttpRequest/fetch) for the NEXT load.

Set it true ONLY when the page's host is in BOTH allow.conf AND js.conf (the sovereignty boundary); false (default) keeps XHR/fetch undefined (Same-Origin-by-construction).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `allowed` | `int` |  |  |

---

<a id="none"></a>

### `none`

`function` | [include/tab.h:266](../../include/tab.h#L266)

```c
* worker sent carries none (tab_page.unchanged) -- on a live page that is almost every tick. * The caller must then keep its current view. Safe against lost results: the parent only * asks for a lazy
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `unchanged` | `tab_page.` |  |  |

**Returns:** `* worker sent carries`

---

<a id="tab_page_keep_view"></a>

### `tab_page_keep_view`

`function` | [include/tab.h:273](../../include/tab.h#L273)

```c
void tab_page_keep_view(tab_page *prev, tab_page *next);
```

For a caller that replaces its page with each tick's: when `next` is unchanged, moves the title, text and view of `prev` into it (prev keeps none).

No-op otherwise or on NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `prev` | `tab_page *` |  |  |
| `next` | `tab_page *` |  |  |

---

<a id="tab_set_op_net_budget_ms"></a>

### `tab_set_op_net_budget_ms`

`function` | [include/tab.h:277](../../include/tab.h#L277)

```c
void tab_set_op_net_budget_ms(tab *t, int ms);
```

Per-operation network time budget in ms for requests the worker issues AFTER the load (default FC_TAB_OP_NET_BUDGET_MS; <= 0 restores it).

Tests lower it.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `ms` | `int` |  |  |

---

<a id="tab_async_fd"></a>

### `tab_async_fd`

`function` | [include/tab.h:282](../../include/tab.h#L282)

```c
* the completion is signalled on tab_async_fd (readable). The pipe to the worker is a single * channel, so EVERY other worker call first waits for the job and DISCARDS its (now stale) * result. Everyt
```

**Returns:** `* the completion is signalled on`

---

<a id="tab_async_busy"></a>

### `tab_async_busy`

`function` | [include/tab.h:288](../../include/tab.h#L288)

```c
int tab_async_busy(const tab *t);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |

**Returns:** `int`

---

<a id="jar"></a>

### `jar`

`function` | [include/tab.h:295](../../include/tab.h#L295)

```c
* the trusted parent read from its ephemeral network jar (sf_cookie_header_for). Only * meaningful for a trusted host (allow.conf AND js.conf);
```

**Returns:** `* the trusted parent read from its ephemeral network`

---

<a id="tab_set_cookies"></a>

### `tab_set_cookies`

`function` | [include/tab.h:299](../../include/tab.h#L299)

```c
void tab_set_cookies(tab *t, const char *cookies);
```

Seeds the page's document.cookie jar for the NEXT load with cookies ("name=value; ...") the trusted parent read from its ephemeral network jar (sf_cookie_header_for).

Only meaningful for a trusted host (allow.conf AND js.conf); pass NULL/"" otherwise so the jar stays disabled (untrusted sites see no cookies -- Zero Knowledge). The bytes are copied. In-memory only; never persisted.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `cookies` | `char *` |  |  |

---

<a id="origin"></a>

### `origin`

`function` | [include/tab.h:302](../../include/tab.h#L302)

```c
* page origin (web_storage snapshot, copied). Used only when the load is trusted * (net granted);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `snapshot` | `web_storage` |  |  |

**Returns:** `* page`

---

<a id="tab_set_storage"></a>

### `tab_set_storage`

`function` | [include/tab.h:304](../../include/tab.h#L304)

```c
void tab_set_storage(tab *t, const char *blob, size_t len);
```

Seeds localStorage for the next load from the parent's in-memory store for the page origin (web_storage snapshot, copied).

Used only when the load is trusted (net granted); NULL/0 clears it. See spec/web_storage.md.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `blob` | `char *` |  |  |
| `len` | `size_t` |  |  |

---

<a id="exclusively"></a>

### `exclusively`

`function` | [include/tab.h:310](../../include/tab.h#L310)

```c
* exclusively (tab_subreq_permitted). Default 0: zero fetches, Privacy by Default. */ void tab_set_css_allowed(tab *t, int allowed);
```

**Returns:** `*`

---

<a id="tab_set_viewport_w"></a>

### `tab_set_viewport_w`

`function` | [include/tab.h:318](../../include/tab.h#L318)

```c
void tab_set_viewport_w(tab *t, int px);
```

Sets the render viewport width (px) used to evaluate @media width queries on the NEXT load, so a responsive page selects the same breakpoint the paint width would (the page is painted at this width). <= 0 restores the normalized default.

Only the @media width query sees it; viewport UNITS (vw/vh) still resolve against the fixed normalized desktop, so no real geometry leaks into computed lengths.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `px` | `int` |  |  |

---

<a id="load"></a>

### `load`

`function` | [include/tab.h:322](../../include/tab.h#L322)

```c
* trusted load (net granted). */ void tab_set_frame_id(tab *t, int id);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `granted` | `net` |  |  |

**Returns:** `* trusted`

---

<a id="tab_set_identity"></a>

### `tab_set_identity`

`function` | [include/tab.h:328](../../include/tab.h#L328)

```c
void tab_set_identity(tab *t, const char *serialized);
```

The user's identity override (idn_serialize text, spec/identity.md) for the NEXT loads: the worker applies it to navigator and, for a trusted host with a fixed place, installs geolocation.

"" / NULL (or a string that does not fit) is the normalized default.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `serialized` | `char *` |  |  |

---

<a id="tab_last_subreq_stats"></a>

### `tab_last_subreq_stats`

`function` | [include/tab.h:334](../../include/tab.h#L334)

```c
void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us);
```

Subresources the parent served for the LAST load (the worker's TAG_SUBREQ: XHR, fetch, external scripts, ES modules): how many, and the total wall time the worker spent blocked on them, in microseconds.

A diagnostic (FREEDOM_PERF): it separates "the page's JS is slow" from "the page waited on the network".

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `count` | `size_t *` |  |  |
| `total_us` | `uint64_t *` |  |  |

---

<a id="tab_subreq_permitted"></a>

### `tab_subreq_permitted`

`function` | [include/tab.h:339](../../include/tab.h#L339)

```c
int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method);
```

Pure parent-side subresource gate (Zero Trust: decided from the PARENT's grants for this load, never the worker's claims): net_allowed permits any well-formed method; css_allowed alone permits exactly "GET"; a NULL/empty method or no grant is refused.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `net_allowed` | `int` |  |  |
| `css_allowed` | `int` |  |  |
| `method` | `char *` |  |  |

**Returns:** `int`

---

<a id="view"></a>

### `view`

`function` | [include/tab.h:347](../../include/tab.h#L347)

```c
* <noscript> handling in the built view (off => fallback shown, on => suppressed) * and is where allowlisted page-script execution will hook in (live-DOM milestone). * tab_load is tab_load_ex with run
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `shown` | `off => fallback` |  |  |
| `suppressed` | `on =>` |  |  |

**Returns:** `* <noscript> handling in the built`

*Called by:* [`SRQ_WIRE_N`](include.scroll_req.h.md#srq_wire_n)

---

<a id="string"></a>

### `string`

`function` | [include/tab.h:367](../../include/tab.h#L367)

```c
* event_type is a JS event type string (e.g. "keydown", "input", "change"). * key is the keyboard key value (may be NULL). * key_code is the numeric keyCode/key value. * value is the element's current
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `keydown` | `e.g. " "` |  |  |
| `input` |  |  |  |
| `change` |  |  |  |

**Returns:** `* event_type is a JS event`

---

<a id="granted"></a>

### `granted`

`function` | [include/tab.h:416](../../include/tab.h#L416)

```c
* granted (allow.conf AND js.conf);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `conf` | `allow.conf AND js.` |  |  |

**Returns:** `*`

---

<a id="returned"></a>

### `returned`

`function` | [include/tab.h:417](../../include/tab.h#L417)

```c
* returned (the page keeps its zeros). The worker re-checks the same condition. * g must be finished (jg_finish). */ tab_status tab_set_geometry(tab *t, const jg_table *g);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `zeros` | `the page keeps its` |  |  |

**Returns:** `*`

---

<a id="popstate"></a>

### `popstate`

`function` | [include/tab.h:423](../../include/tab.h#L423)

```c
* popstate (+ hashchange) and re-derives the view like a click. */ tab_status tab_popstate(tab *t, int index, tab_page *out);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `hashchange` |  |  |  |

**Returns:** `*`

---

<a id="preorder"></a>

### `preorder`

`function` | [include/tab.h:428](../../include/tab.h#L428)

```c
* preorder (out->nsub handles) followed by the elements after it, at most * ANC_MAX_HANDLES -- live DOM handles, the same ids the view carries. push_url (NULL or * "" for none) is the same-document UR
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `handles` | `out->nsub` |  |  |

**Returns:** `*`

---

<a id="one"></a>

### `one`

`function` | [include/tab.h:445](../../include/tab.h#L445)

```c
* history entry with push_url instead of adding one (location.replace('#x'), a fragment * set while the document loads: spec/anchor.md 3b). */ #define TAB_ANCHOR_REPLACE 1u tab_status tab_anchor_query
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x` | `location.replace('# ')` |  |  |
| `b` | `a fragment * set while the document loads: spec/anchor.md 3` |  |  |

**Returns:** `* history entry with push_url instead of adding`

---

<a id="tab_anchor_free"></a>

### `tab_anchor_free`

`function` | [include/tab.h:450](../../include/tab.h#L450)

```c
void tab_anchor_free(tab_anchor *a);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `tab_anchor *` |  |  |

---

<a id="decode"></a>

### `decode`

`function` | [include/tab.h:468](../../include/tab.h#L468)

```c
* could not decode (caller shows the placeholder), which is not a transport error. * TAB_ERR_* is reserved for transport/worker failures. */ tab_status tab_decode_image(tab *t, const uint8_t *bytes, s
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `placeholder` | `caller shows the` |  |  |

**Returns:** `* could not`

---

<a id="tab_alive"></a>

### `tab_alive`

`function` | [include/tab.h:481](../../include/tab.h#L481)

```c
int tab_alive(const tab *t);
```

Nonzero while the worker process is believed alive.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |

**Returns:** `int`

---

<a id="tab_child_pid"></a>

### `tab_child_pid`

`function` | [include/tab.h:484](../../include/tab.h#L484)

```c
pid_t tab_child_pid(const tab *t);
```

The worker's process id (for monitoring), or -1.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |

**Returns:** `pid_t`

---

<a id="tab_close"></a>

### `tab_close`

`function` | [include/tab.h:487](../../include/tab.h#L487)

```c
void tab_close(tab *t);
```

Terminates the worker and frees the handle.

Safe on NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |

---

<a id="tab_page_free"></a>

### `tab_page_free`

`function` | [include/tab.h:490](../../include/tab.h#L490)

```c
void tab_page_free(tab_page *p);
```

Idempotent releasers for the result structs.

Safe on NULL / zeroed structs.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `p` | `tab_page *` |  |  |

---

<a id="tab_eval_result_free"></a>

### `tab_eval_result_free`

`function` | [include/tab.h:491](../../include/tab.h#L491)

```c
void tab_eval_result_free(tab_eval_result *r);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `r` | `tab_eval_result *` |  |  |

---

<a id="tab_image_free"></a>

### `tab_image_free`

`function` | [include/tab.h:492](../../include/tab.h#L492)

```c
void tab_image_free(tab_image *img);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `img` | `tab_image *` |  |  |

---

## Macros

<a id="tab_max_input"></a>

### `TAB_MAX_INPUT`

`macro` | [include/tab.h:172](../../include/tab.h#L172)

```c
#define TAB_MAX_INPUT
```

---

<a id="tab_anchor_replace"></a>

### `TAB_ANCHOR_REPLACE`

`macro` | [include/tab.h:447](../../include/tab.h#L447)

```c
#define TAB_ANCHOR_REPLACE
```

As tab_anchor_query; flags TAB_ANCHOR_REPLACE makes the page REPLACE its current history entry with push_url instead of adding one (location.replace('#x'), a fragment set while the document loads: spec/anchor.md 3b).

---
