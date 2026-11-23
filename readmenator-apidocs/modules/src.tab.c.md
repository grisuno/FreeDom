# `src/tab.c`

> Source: [src/tab.c:1](../../src/tab.c#L1) | language `c` | coverage 44.2% | [API index](../index.md)

## Contents

- **Structs:** [`tab_iobuf`](#tab_iobuf), [`child_state`](#child_state), [`net_reply`](#net_reply), [`css_text`](#css_text), [`tab`](#tab), [`tab_spawned`](#tab_spawned), [`tab_net_fn`](#tab_net_fn)
- **Type Aliases:** [`fd`](#fd), [`fn`](#fn)
- **Functions:** [`run_js`](#run_js), [`buffer`](#buffer), [`blocks`](#blocks), [`FB_MAX_FILE_BYTES`](#fb_max_file_bytes), [`run`](#run), [`sheets`](#sheets), [`does`](#does), [`libraries`](#libraries), [`WHERE`](#where), [`content`](#content), [`once`](#once), [`swap`](#swap), [`write_full`](#write_full), [`EPIPE`](#epipe), [`tzset`](#tzset), [`depth`](#depth), [`tab_parse_worker_args`](#tab_parse_worker_args), [`tab_worker_dispatch`](#tab_worker_dispatch), [`tests`](#tests), [`layout`](#layout), [`column`](#column), [`tab_prewarm`](#tab_prewarm), [`tab_prewarmed`](#tab_prewarmed), [`tab_prewarmed_pid`](#tab_prewarmed_pid), [`tab_shutdown_spare`](#tab_shutdown_spare), [`tab_open`](#tab_open), [`tab_set_fetcher`](#tab_set_fetcher), [`tab_set_async_fetcher`](#tab_set_async_fetcher), [`tab_set_css_sink`](#tab_set_css_sink), [`tab_set_op_net_budget_ms`](#tab_set_op_net_budget_ms), [`tab_set_net_allowed`](#tab_set_net_allowed), [`tab_set_lazy_ticks`](#tab_set_lazy_ticks), [`tab_page_keep_view`](#tab_page_keep_view), [`tab_set_css_allowed`](#tab_set_css_allowed), [`tab_last_subreq_stats`](#tab_last_subreq_stats), [`tab_set_identity`](#tab_set_identity), [`tab_set_frame_id`](#tab_set_frame_id), [`tab_set_viewport_w`](#tab_set_viewport_w), [`tab_set_cookies`](#tab_set_cookies), [`tab_subreq_permitted`](#tab_subreq_permitted), [`tab_report_response_headers`](#tab_report_response_headers), [`tab_inflight_request_headers`](#tab_inflight_request_headers), [`fn`](#fn), [`tab_load`](#tab_load), [`tab_load_ex`](#tab_load_ex), [`tab_load_full`](#tab_load_full), [`tab_click`](#tab_click), [`tab_tick`](#tab_tick), [`tab_submit`](#tab_submit), [`tab_read_view`](#tab_read_view), [`frames`](#frames), [`tab_eval`](#tab_eval), [`tab_decode_image`](#tab_decode_image), [`tab_decode_image_data_url`](#tab_decode_image_data_url), [`tab_alive`](#tab_alive), [`tab_child_pid`](#tab_child_pid), [`tab_close`](#tab_close), [`tab_page_free`](#tab_page_free), [`tab_eval_result_free`](#tab_eval_result_free), [`tab_image_free`](#tab_image_free), [`tab_set_geometry`](#tab_set_geometry), [`tab_async_fd`](#tab_async_fd), [`tab_async_busy`](#tab_async_busy), [`tab_tick_async`](#tab_tick_async), [`tab_geometry_async`](#tab_geometry_async), [`tab_async_finish`](#tab_async_finish), [`tab_popstate`](#tab_popstate), [`tab_ws_event`](#tab_ws_event), [`tab_set_storage`](#tab_set_storage), [`tab_anchor_free`](#tab_anchor_free), [`tab_anchor_query`](#tab_anchor_query)
- **Macros:** [`_GNU_SOURCE`](#_gnu_source), [`TAB_IOBUF_BYTES`](#tab_iobuf_bytes), [`write_full`](#write_full), [`read_full`](#read_full), [`TAB_SCREEN_W`](#tab_screen_w), [`TAB_WIRE_HEAD_N`](#tab_wire_head_n), [`TAB_WIRE_A_N`](#tab_wire_a_n), [`TAB_WIRE_B_N`](#tab_wire_b_n), [`TAB_WIRE_BOX_F_N`](#tab_wire_box_f_n), [`TAB_WIRE_GRID_N`](#tab_wire_grid_n), [`TAB_MAX_RUNS`](#tab_max_runs), [`PV_MAX_CONTAINERS_WIRE`](#pv_max_containers_wire), [`TAB_MAX_URL`](#tab_max_url), [`TAB_MAX_WS_MSG`](#tab_max_ws_msg), [`TAB_MAX_STORAGE`](#tab_max_storage), [`TAB_MAX_HIST_OPS`](#tab_max_hist_ops), [`TAB_MAX_HIST_BYTES`](#tab_max_hist_bytes), [`TAB_MAX_OPENS`](#tab_max_opens), [`TAB_MAX_OPEN_BYTES`](#tab_max_open_bytes), [`TAB_MAX_GEOM_WORDS`](#tab_max_geom_words), [`TAB_MAX_ASYNC_PENDING`](#tab_max_async_pending), [`TAB_MAX_NET_ROUNDS`](#tab_max_net_rounds), [`TAB_ASYNC_THREADS`](#tab_async_threads), [`TAB_MAX_BATCH_BYTES`](#tab_max_batch_bytes), [`TAB_MAX_SUBREQ`](#tab_max_subreq), [`TAB_MAX_SUBRESOURCE`](#tab_max_subresource), [`TAB_MAX_JS_JOBS`](#tab_max_js_jobs), [`TAB_CQ_REDERIVE_MAX`](#tab_cq_rederive_max), [`TAB_MAX_EXTERN_CSS`](#tab_max_extern_css)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class fd
    <<type_alias>> fd
    class tab_iobuf
    <<struct>> tab_iobuf
    class child_state
    <<struct>> child_state
    child_state : unchanged()
    class net_reply
    <<struct>> net_reply
    class net_reply_status
    <<type_alias>> net_reply_status
    class css_text
    <<struct>> css_text
    class tab
    <<struct>> tab
    tab : load()
    class tab_spawned
    <<struct>> tab_spawned
    class fn
    <<type_alias>> fn
    class tab_net_fn
    <<struct>> tab_net_fn
```

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_tab_c__FB_MAX_FILE_BYTES(["FB_MAX_FILE_BYTES"])
    n_src_tab_c__write_full(["write_full"])
    n_src_tab_c__write_full_2146(["write_full"])
    n_src_tab_c__tab_worker_dispatch(["tab_worker_dispatch"])
    n_src_tab_c__tab_parse_worker_args(["tab_parse_worker_args"])
    n_src_tab_c__run_js(["run_js"])
    n_include_dom_h__dom_free["dom.dom_free"]
    n_include_html_parse_h__hp_document_free["html_parse.hp_document_free"]
    n_include_js_sandbox_h__js_context_free["js_sandbox.js_context_free"]
    n_src_dom_c__dom_build["dom.dom_build"]
    n_src_html_parse_c__hp_config_default["html_parse.hp_config_default"]
    n_src_html_parse_c__hp_parse["html_parse.hp_parse"]
    n_src_js_dom_c__jd_install["js_dom.jd_install"]
    n_src_js_native_c__jn_seal["js_native.jn_seal"]
    n_src_js_sandbox_c__js_context_new["js_sandbox.js_context_new"]
    n_include_freebug_h__fb_buffer_at["freebug.fb_buffer_at"]
    n_include_freebug_h__fb_buffer_count["freebug.fb_buffer_count"]
    n_src_tab_c__run(["run"])
    n_include_dom_h__dom_get_attribute["dom.dom_get_attribute"]
    n_include_page_view_h__pv_at["page_view.pv_at"]
    n_include_page_view_h__pv_count["page_view.pv_count"]
    n_src_dom_c__dom_get_by_tag["dom.dom_get_by_tag"]
    n_src_page_view_c__pv_append_video["page_view.pv_append_video"]
    n_src_tab_c__sheets(["sheets"])
    n_include_dom_h__dom_text_content["dom.dom_text_content"]
    n_include_html_parse_h__dropped["html_parse.dropped"]
    n_include_html_parse_h__hp_extract_stylesheet_hrefs["html_parse.hp_extract_stylesheet_hrefs"]
    n_include_html_parse_h__hp_free_stylesheet_hrefs["html_parse.hp_free_stylesheet_hrefs"]
    n_src_tab_c__FB_MAX_FILE_BYTES --> n_src_tab_c__write_full
    n_src_tab_c__write_full_2146 --> n_src_tab_c__write_full
    n_src_tab_c__tab_worker_dispatch --> n_src_tab_c__tab_parse_worker_args
    n_src_tab_c__run_js -.-> n_include_dom_h__dom_free
    n_src_tab_c__run_js -.-> n_include_html_parse_h__hp_document_free
    n_src_tab_c__run_js -.-> n_include_js_sandbox_h__js_context_free
    n_src_tab_c__run_js -.-> n_src_dom_c__dom_build
    n_src_tab_c__run_js -.-> n_src_html_parse_c__hp_config_default
    n_src_tab_c__run_js -.-> n_src_html_parse_c__hp_parse
    n_src_tab_c__run_js -.-> n_src_js_dom_c__jd_install
    n_src_tab_c__run_js -.-> n_src_js_native_c__jn_seal
    n_src_tab_c__run_js -.-> n_src_js_sandbox_c__js_context_new
    n_src_tab_c__FB_MAX_FILE_BYTES -.-> n_include_freebug_h__fb_buffer_at
    n_src_tab_c__FB_MAX_FILE_BYTES -.-> n_include_freebug_h__fb_buffer_count
    n_src_tab_c__run -.-> n_include_dom_h__dom_get_attribute
    n_src_tab_c__run -.-> n_include_page_view_h__pv_at
    n_src_tab_c__run -.-> n_include_page_view_h__pv_count
    n_src_tab_c__run -.-> n_src_dom_c__dom_get_by_tag
    n_src_tab_c__run -.-> n_src_page_view_c__pv_append_video
    n_src_tab_c__sheets -.-> n_include_dom_h__dom_text_content
    n_src_tab_c__sheets -.-> n_include_html_parse_h__dropped
    n_src_tab_c__sheets -.-> n_include_html_parse_h__hp_extract_stylesheet_hrefs
    n_src_tab_c__sheets -.-> n_include_html_parse_h__hp_free_stylesheet_hrefs
    n_src_tab_c__sheets -.-> n_src_dom_c__dom_get_by_tag
```

## Structs

<a id="tab_iobuf"></a>

### `tab_iobuf`

`struct` | [src/tab.c:62](../../src/tab.c#L62)

```c
typedef struct tab_iobuf
```

Batched pipe I/O for the view codec. write_view/read_view move one int32 block and one length-prefixed string at a time: ~46 000 read(2) and as many write(2) calls for a single Wikipedia page, each a context switch for 4-64 bytes.

Inside those two functions the traffic goes through a per-THREAD 64 KiB buffer instead (no state is shared: the async tick thread and the caller each have their own). The byte stream is unchanged. Writes are flushed before write_view returns. A read buffer may hold the bytes that follow the view in the same reply: they stay in it and the next read on that fd consumes them first, so no byte is ever lost; the protocol is request/response lockstep, so nothing beyond the reply can be in the pipe.  define TAB_IOBUF_BYTES (64u * 1024u)

---

<a id="child_state"></a>

### `child_state`

`struct` | [src/tab.c:233](../../src/tab.c#L233)

```c
typedef struct child_state
```

**Members**

| Member | Kind | Summary |
|---|---|---|
| [`unchanged`](#child_state-unchanged) | method |  |

<a id="child_state-unchanged"></a>

#### `child_state.unchanged`

`method` | [src/tab.c:272](../../src/tab.c#L272)

```c
* is unchanged (spec/sheet_cache.md);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `md` | `spec/sheet_cache.` |  |  |

**Returns:** `* is`

---

<a id="net_reply"></a>

### `net_reply`

`struct` | [src/tab.c:468](../../src/tab.c#L468)

```c
typedef struct net_reply
```

jd_fetch_fn: the confined worker has NO network (CLONE_NEWNET + seccomp).

An XHR/fetch from page script is proxied to the TRUSTED parent over the existing pipes: write a TAG_SUBREQ frame, block for the parent's reply. The parent re-applies the FULL network policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a compromised worker still cannot reach a blocked host. Refused/over-budget/IO-error => non-zero (XHR completes with status 0). Only callable inside a page-load script window (net_active) so it never desyncs the OP_EVAL/OP_DECODE_IMAGE response paths.

**Members**

| Member | Kind | Summary |
|---|---|---|
| [`status`](#net_reply-status) | type_alias | jd_fetch_fn: the confined worker has NO network (CLONE_NEWNET + seccomp). |

<a id="net_reply-status"></a>

#### `net_reply.status`

`type_alias` | [src/tab.c:468](../../src/tab.c#L468)

```c
typedef struct net_reply { int32_t status;
```

jd_fetch_fn: the confined worker has NO network (CLONE_NEWNET + seccomp).

An XHR/fetch from page script is proxied to the TRUSTED parent over the existing pipes: write a TAG_SUBREQ frame, block for the parent's reply. The parent re-applies the FULL network policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a compromised worker still cannot reach a blocked host. Refused/over-budget/IO-error => non-zero (XHR completes with status 0). Only callable inside a page-load script window (net_active) so it never desyncs the OP_EVAL/OP_DECODE_IMAGE response paths.

---

<a id="css_text"></a>

### `css_text`

`struct` | [src/tab.c:1486](../../src/tab.c#L1486)

```c
typedef struct css_text
```

A growable CSS text bounded by TAB_MAX_EXTERN_CSS (a protocol-level cap, so a realloc'd buffer is enough). put fails WHOLE when the text would not fit.

---

<a id="tab"></a>

### `tab`

`struct` | [src/tab.c:2913](../../src/tab.c#L2913)

```c
struct tab
```

**Members**

| Member | Kind | Summary |
|---|---|---|
| [`load`](#tab-load) | method |  |

<a id="tab-load"></a>

#### `tab.load`

`method` | [src/tab.c:2920](../../src/tab.c#L2920)

```c
* subresource requests this load (set per page: host in allow.conf AND js.conf);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `conf` | `set per page: host in allow.conf AND js.` |  |  |

**Returns:** `* subresource requests this`

---

<a id="tab_spawned"></a>

### `tab_spawned`

`struct` | [src/tab.c:3642](../../src/tab.c#L3642)

```c
typedef struct
```

An idle worker waiting for the next tab_open (spec/tab.md "Worker de repuesto").

---

<a id="tab_net_fn"></a>

### `tab_net_fn`

`struct` | [src/tab.c:4000](../../src/tab.c#L4000)

```c
typedef struct tab_net_fn { tab_fetch_fn fn; void *ctx; void (*free_ctx)(void *); } tab_net_fn;
```

The stable fetcher a batch owns (tab_set_async_fetcher): its requests may outlive the tab.

---

## Type Aliases

<a id="fd"></a>

### `fd`

`type_alias` | [src/tab.c:62](../../src/tab.c#L62)

```c
typedef struct tab_iobuf { int fd;
```

Batched pipe I/O for the view codec. write_view/read_view move one int32 block and one length-prefixed string at a time: ~46 000 read(2) and as many write(2) calls for a single Wikipedia page, each a context switch for 4-64 bytes.

Inside those two functions the traffic goes through a per-THREAD 64 KiB buffer instead (no state is shared: the async tick thread and the caller each have their own). The byte stream is unchanged. Writes are flushed before write_view returns. A read buffer may hold the bytes that follow the view in the same reply: they stay in it and the next read on that fd consumes them first, so no byte is ever lost; the protocol is request/response lockstep, so nothing beyond the reply can be in the pipe.  define TAB_IOBUF_BYTES (64u * 1024u)

---

<a id="fn"></a>

### `fn`

`type_alias` | [src/tab.c:4000](../../src/tab.c#L4000)

```c
typedef struct tab_net_fn { tab_fetch_fn fn;
```

The stable fetcher a batch owns (tab_set_async_fetcher): its requests may outlive the tab.

---

## Functions

<a id="run_js"></a>

### `run_js`

`function` | [src/tab.c:664](../../src/tab.c#L664)

```c
* regardless of run_js (a no-JS load simply never records a request). */ /* Installs the page-ind...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `request` | `a no-JS load simply never records a` |  |  |

**Returns:** `* regardless of`

*Calls:* [`dom_free`](include.dom.h.md#dom_free), [`hp_document_free`](include.html_parse.h.md#hp_document_free), [`js_context_free`](include.js_sandbox.h.md#js_context_free), [`dom_build`](src.dom.c.md#dom_build), [`hp_config_default`](src.html_parse.c.md#hp_config_default), [`hp_parse`](src.html_parse.c.md#hp_parse), [`jd_install`](src.js_dom.c.md#jd_install), [`jn_seal`](src.js_native.c.md#jn_seal), [`js_context_new`](src.js_sandbox.c.md#js_context_new)

---

<a id="buffer"></a>

### `buffer`

`function` | [src/tab.c:759](../../src/tab.c#L759)

```c
* the buffer (stable child_state member) is wired into the new context's runtime * opaque. Installed regardless of run_js so the REPL works on any page. */ fb_buffer_reset(&cs->log);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `member` | `stable child_state` |  |  |

**Returns:** `* the`

---

<a id="blocks"></a>

### `blocks`

`function` | [src/tab.c:829](../../src/tab.c#L829)

```c
* * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the * grid array, block B[26]) exactly like the box-def f[] array, NOT one write_full per * field: the block literal li
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `head` |  |  |  |
| `A` | `block [36]` |  |  |
| `array` | `the * grid` |  |  |
| `B` | `block [26]` |  |  |

**Returns:** `* * The scalar fields are marshalled as bulk int32`

---

<a id="fb_max_file_bytes"></a>

### `FB_MAX_FILE_BYTES`

`function` | [src/tab.c:1282](../../src/tab.c#L1282)

```c
* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify * the stream. ...
```

A stored source name is truncated to this many bytes (NUL excluded).

It is not counted against FB_MAX_TOTAL_BYTES: entries are capped, so total file memory is bounded at FB_MAX_ENTRIES * FB_MAX_FILE_BYTES regardless.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `all` | `the buffer enforces` |  |  |

**Returns:** `*`

> **Inherited:** Documentation from [`FB_MAX_FILE_BYTES`](#fb_max_file_bytes) (include/freebug.h:62).

*Calls:* [`fb_buffer_at`](include.freebug.h.md#fb_buffer_at), [`fb_buffer_count`](include.freebug.h.md#fb_buffer_count), [`write_full`](#write_full)

---

<a id="run"></a>

### `run`

`function` | [src/tab.c:1361](../../src/tab.c#L1361)

```c
* already contains a PV_VIDEO run (avoids duplicates on repeated injection). * Call after every ...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `injection` | `avoids duplicates on repeated` |  |  |

**Returns:** `* already contains a PV_VIDEO`

*Calls:* [`dom_get_attribute`](include.dom.h.md#dom_get_attribute), [`pv_at`](include.page_view.h.md#pv_at), [`pv_count`](include.page_view.h.md#pv_count), [`dom_get_by_tag`](src.dom.c.md#dom_get_by_tag), [`pv_append_video`](src.page_view.c.md#pv_append_video)

---

<a id="sheets"></a>

### `sheets`

`function` | [src/tab.c:1624](../../src/tab.c#L1624)

```c
* sheets (their own text is read from the DOM by page_view). Every failure is * fail-open for th...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `page_view` | `their own text is read from the DOM by` |  |  |

**Returns:** `*`

*Calls:* [`dom_text_content`](include.dom.h.md#dom_text_content), [`dropped`](include.html_parse.h.md#dropped), [`hp_extract_stylesheet_hrefs`](include.html_parse.h.md#hp_extract_stylesheet_hrefs), [`hp_free_stylesheet_hrefs`](include.html_parse.h.md#hp_free_stylesheet_hrefs), [`dom_get_by_tag`](src.dom.c.md#dom_get_by_tag)

---

<a id="does"></a>

### `does`

`function` | [src/tab.c:1799](../../src/tab.c#L1799)

```c
* native browser does (spec/js_native.md). Best effort -- an unsealed page still runs. */ (void)jn_seal(cs->js);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `md` | `spec/js_native.` |  |  |

**Returns:** `* browser`

---

<a id="libraries"></a>

### `libraries`

`function` | [src/tab.c:1816](../../src/tab.c#L1816)

```c
* load heavier libraries (jQuery, Bootstrap, etc.) that need more time. * Untrusted hosts get the default budget (1s) to limit abuse. */ prof_lap("js-enable", &ph);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `etc` |  |  |  |

**Returns:** `* load heavier`

---

<a id="where"></a>

### `WHERE`

`function` | [src/tab.c:1986](../../src/tab.c#L1986)

```c
* the console still says WHERE (a module's URL, "inline #n", a src). */ if (es != JS_OK && r.is_exception && r.value != NULL) fb_buffer_push_loc(&cs->log, FB_ERROR, r.value, r.value_len, r.file != NUL
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `src` | `a module's URL, "inline #n", a` |  |  |

**Returns:** `* the console still says`

---

<a id="content"></a>

### `content`

`function` | [src/tab.c:2063](../../src/tab.c#L2063)

```c
* content (same-origin fetches through the trusted parent), scan for * video URLs (.m3u8), and create <video> elements in the DOM for any * found. */ if (cs->idx != NULL) jd_process_iframes(cs->js, cs
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `parent` | `same-origin fetches through the trusted` |  |  |

**Returns:** `*`

---

<a id="once"></a>

### `once`

`function` | [src/tab.c:2116](../../src/tab.c#L2116)

```c
* ensures the preserved view gets the video only once (initial load). */ inject_video_into_view(cs, &view);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `load` | `initial` |  |  |

**Returns:** `* ensures the preserved view gets the video only`

---

<a id="swap"></a>

### `swap`

`function` | [src/tab.c:2125](../../src/tab.c#L2125)

```c
* display:none hiding an element via class swap (CSS, not * DOM removal). */ if (ok && v...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `removal` | `not * DOM` |  |  |

**Returns:** `* display:none hiding an element via`

*Calls:* [`pv_count`](include.page_view.h.md#pv_count)

---

<a id="write_full"></a>

### `write_full`

`function` | [src/tab.c:2146](../../src/tab.c#L2146)

```c
&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0) && write_view(wfd, write_which) == 0 && write_full(wfd, &nlen, sizeof nlen) == 0 && (nlen == 0 || write_full(wfd,
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `xl` |  |  |  |
| `xl` | `sizeof` |  |  |

**Returns:** `&&`

*Calls:* [`write_full`](#write_full)

---

<a id="epipe"></a>

### `EPIPE`

`function` | [src/tab.c:2634](../../src/tab.c#L2634)

```c
* surfaces as EPIPE (graceful loop exit), not a signal. */ ignore_sigpipe();
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `exit` | `graceful loop` |  |  |

**Returns:** `* surfaces as`

---

<a id="tzset"></a>

### `tzset`

`function` | [src/tab.c:2650](../../src/tab.c#L2650)

```c
* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);
```

**Returns:** `*`

---

<a id="depth"></a>

### `depth`

`function` | [src/tab.c:2664](../../src/tab.c#L2664)

```c
* defense in depth (seccomp already excludes open/socket/exec);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `exec` | `seccomp already excludes open/socket/` |  |  |

**Returns:** `* defense in`

*Called by:* [`form`](include.render_doc.h.md#form)

---

<a id="tab_parse_worker_args"></a>

### `tab_parse_worker_args`

`function` | [src/tab.c:2893](../../src/tab.c#L2893)

```c
int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)
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

> **Inherited:** Documentation from [`tab_parse_worker_args`](#tab_parse_worker_args) (include/tab.h:175).

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp)

*Called by:* [`tab_worker_dispatch`](#tab_worker_dispatch)

---

<a id="tab_worker_dispatch"></a>

### `tab_worker_dispatch`

`function` | [src/tab.c:2903](../../src/tab.c#L2903)

```c
void tab_worker_dispatch(int argc, char **argv)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

*Calls:* [`tab_parse_worker_args`](#tab_parse_worker_args)

---

<a id="tests"></a>

### `tests`

`function` | [src/tab.c:3094](../../src/tab.c#L3094)

```c
* here lost the reserved box in the real browser while the page_view * tests (which never cross the pipe) stayed green. */ st = pv_append_image(v, heading, brk, text, (src != NULL) ? src : "", img_w,
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pipe` | `which never cross the` |  |  |

**Returns:** `* here lost the reserved box in the real browser while the page_view *`

---

<a id="layout"></a>

### `layout`

`function` | [src/tab.c:3207](../../src/tab.c#L3207)

```c
* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property. */ pv_set_box_pct(v, (int)bwpct, (int)b[36], (int)b[37], (int)b[38], (int)b[39]);
```

**Returns:** `setting one without the other would make * the pair disagree about the same property. */ pv_set_box_pct(v, (int)bwpct, (int)b[36], (int)b[37], (int)b[38], (int)b[39])`

---

<a id="column"></a>

### `column`

`function` | [src/tab.c:3218](../../src/tab.c#L3218)

```c
* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation as text runs. */ pv_set_container(v, (int)cid, (int)cdisp, (int)cgap, (int)cjust, (in
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `player` | `jkanime's` |  |  |

**Returns:** `* a narrow`

---

<a id="tab_prewarm"></a>

### `tab_prewarm`

`function` | [src/tab.c:3715](../../src/tab.c#L3715)

```c
void tab_prewarm(void)
```

Starts one idle, confined worker in advance so the next tab_open does not wait for fork + exec + sandbox setup (spec/tab.md "Worker de repuesto").

Idempotent; best-effort (a failed spawn just means tab_open spawns on demand). The spare has received no content.

> **Inherited:** Documentation from [`tab_prewarm`](#tab_prewarm) (include/tab.h:184).

---

<a id="tab_prewarmed"></a>

### `tab_prewarmed`

`function` | [src/tab.c:3721](../../src/tab.c#L3721)

```c
int tab_prewarmed(void)
```

1 while a spare worker is waiting for the next tab_open.

**Returns:** `int`

> **Inherited:** Documentation from [`tab_prewarmed`](#tab_prewarmed) (include/tab.h:187).

---

<a id="tab_prewarmed_pid"></a>

### `tab_prewarmed_pid`

`function` | [src/tab.c:3728](../../src/tab.c#L3728)

```c
int tab_prewarmed_pid(void)
```

Process id of that spare, 0 when there is none (diagnostics and tests).

**Returns:** `int`

> **Inherited:** Documentation from [`tab_prewarmed_pid`](#tab_prewarmed_pid) (include/tab.h:190).

---

<a id="tab_shutdown_spare"></a>

### `tab_shutdown_spare`

`function` | [src/tab.c:3735](../../src/tab.c#L3735)

```c
void tab_shutdown_spare(void)
```

Kills and reaps the spare, if any.

Safe to call when there is none.

> **Inherited:** Documentation from [`tab_shutdown_spare`](#tab_shutdown_spare) (include/tab.h:193).

---

<a id="tab_open"></a>

### `tab_open`

`function` | [src/tab.c:3744](../../src/tab.c#L3744)

```c
tab_status tab_open(tab **out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `out` | `tab **` |  |  |

**Returns:** `tab_status`

---

<a id="tab_set_fetcher"></a>

### `tab_set_fetcher`

`function` | [src/tab.c:3767](../../src/tab.c#L3767)

```c
void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)
```

Installs the subresource fetcher used for XHR/fetch (NULL clears it: requests are then refused). fn/ctx must outlive any tab_load_full call that may trigger a subresource.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `fn` | `tab_fetch_fn` |  |  |
| `ctx` | `void *` |  |  |

> **Inherited:** Documentation from [`tab_set_fetcher`](#tab_set_fetcher) (include/tab.h:212).

---

<a id="tab_set_async_fetcher"></a>

### `tab_set_async_fetcher`

`function` | [src/tab.c:3784](../../src/tab.c#L3784)

```c
void tab_set_async_fetcher(tab *t, tab_fetch_fn fn, void *ctx, void (*free_ctx)(void *))
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `fn` | `tab_fetch_fn` |  |  |
| `ctx` | `void *` |  |  |
| `void` | `void (*free_ctx)( *)` |  |  |

*Calls:* [`free_ctx`](include.tab.h.md#free_ctx)

---

<a id="tab_set_css_sink"></a>

### `tab_set_css_sink`

`function` | [src/tab.c:3792](../../src/tab.c#L3792)

```c
void tab_set_css_sink(tab *t, tab_css_sink_fn fn, void *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `fn` | `tab_css_sink_fn` |  |  |
| `ctx` | `void *` |  |  |

---

<a id="tab_set_op_net_budget_ms"></a>

### `tab_set_op_net_budget_ms`

`function` | [src/tab.c:3798](../../src/tab.c#L3798)

```c
void tab_set_op_net_budget_ms(tab *t, int ms)
```

Per-operation network time budget in ms for requests the worker issues AFTER the load (default FC_TAB_OP_NET_BUDGET_MS; <= 0 restores it).

Tests lower it.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `ms` | `int` |  |  |

> **Inherited:** Documentation from [`tab_set_op_net_budget_ms`](#tab_set_op_net_budget_ms) (include/tab.h:265).

---

<a id="tab_set_net_allowed"></a>

### `tab_set_net_allowed`

`function` | [src/tab.c:3802](../../src/tab.c#L3802)

```c
void tab_set_net_allowed(tab *t, int allowed)
```

Grants/revokes page-JS network access (XMLHttpRequest/fetch) for the NEXT load.

Set it true ONLY when the page's host is in BOTH allow.conf AND js.conf (the sovereignty boundary); false (default) keeps XHR/fetch undefined (Same-Origin-by-construction).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `allowed` | `int` |  |  |

> **Inherited:** Documentation from [`tab_set_net_allowed`](#tab_set_net_allowed) (include/tab.h:250).

---

<a id="tab_set_lazy_ticks"></a>

### `tab_set_lazy_ticks`

`function` | [src/tab.c:3807](../../src/tab.c#L3807)

```c
void tab_set_lazy_ticks(tab *t, int on)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `on` | `int` |  |  |

---

<a id="tab_page_keep_view"></a>

### `tab_page_keep_view`

`function` | [src/tab.c:3812](../../src/tab.c#L3812)

```c
void tab_page_keep_view(tab_page *prev, tab_page *next)
```

For a caller that replaces its page with each tick's: when `next` is unchanged, moves the title, text and view of `prev` into it (prev keeps none).

No-op otherwise or on NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `prev` | `tab_page *` |  |  |
| `next` | `tab_page *` |  |  |

> **Inherited:** Documentation from [`tab_page_keep_view`](#tab_page_keep_view) (include/tab.h:261).

*Calls:* [`pv_free`](include.page_view.h.md#pv_free)

---

<a id="tab_set_css_allowed"></a>

### `tab_set_css_allowed`

`function` | [src/tab.c:3823](../../src/tab.c#L3823)

```c
void tab_set_css_allowed(tab *t, int allowed)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `allowed` | `int` |  |  |

---

<a id="tab_last_subreq_stats"></a>

### `tab_last_subreq_stats`

`function` | [src/tab.c:3828](../../src/tab.c#L3828)

```c
void tab_last_subreq_stats(const tab *t, size_t *count, uint64_t *total_us)
```

Subresources the parent served for the LAST load (the worker's TAG_SUBREQ: XHR, fetch, external scripts, ES modules): how many, and the total wall time the worker spent blocked on them, in microseconds.

A diagnostic (FREEDOM_PERF): it separates "the page's JS is slow" from "the page waited on the network".

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `count` | `size_t *` |  |  |
| `total_us` | `uint64_t *` |  |  |

> **Inherited:** Documentation from [`tab_last_subreq_stats`](#tab_last_subreq_stats) (include/tab.h:322).

---

<a id="tab_set_identity"></a>

### `tab_set_identity`

`function` | [src/tab.c:3833](../../src/tab.c#L3833)

```c
void tab_set_identity(tab *t, const char *serialized)
```

The user's identity override (idn_serialize text, spec/identity.md) for the NEXT loads: the worker applies it to navigator and, for a trusted host with a fixed place, installs geolocation.

"" / NULL (or a string that does not fit) is the normalized default.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `serialized` | `char *` |  |  |

> **Inherited:** Documentation from [`tab_set_identity`](#tab_set_identity) (include/tab.h:316).

---

<a id="tab_set_frame_id"></a>

### `tab_set_frame_id`

`function` | [src/tab.c:3841](../../src/tab.c#L3841)

```c
void tab_set_frame_id(tab *t, int id)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `id` | `int` |  |  |

---

<a id="tab_set_viewport_w"></a>

### `tab_set_viewport_w`

`function` | [src/tab.c:3846](../../src/tab.c#L3846)

```c
void tab_set_viewport_w(tab *t, int px)
```

Sets the render viewport width (px) used to evaluate @media width queries on the NEXT load, so a responsive page selects the same breakpoint the paint width would (the page is painted at this width). <= 0 restores the normalized default.

Only the @media width query sees it; viewport UNITS (vw/vh) still resolve against the fixed normalized desktop, so no real geometry leaks into computed lengths.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `px` | `int` |  |  |

> **Inherited:** Documentation from [`tab_set_viewport_w`](#tab_set_viewport_w) (include/tab.h:306).

---

<a id="tab_set_cookies"></a>

### `tab_set_cookies`

`function` | [src/tab.c:3851](../../src/tab.c#L3851)

```c
void tab_set_cookies(tab *t, const char *cookies)
```

Seeds the page's document.cookie jar for the NEXT load with cookies ("name=value; ...") the trusted parent read from its ephemeral network jar (sf_cookie_header_for).

Only meaningful for a trusted host (allow.conf AND js.conf); pass NULL/"" otherwise so the jar stays disabled (untrusted sites see no cookies -- Zero Knowledge). The bytes are copied. In-memory only; never persisted.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `cookies` | `char *` |  |  |

> **Inherited:** Documentation from [`tab_set_cookies`](#tab_set_cookies) (include/tab.h:287).

---

<a id="tab_subreq_permitted"></a>

### `tab_subreq_permitted`

`function` | [src/tab.c:3857](../../src/tab.c#L3857)

```c
int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)
```

Pure parent-side subresource gate (Zero Trust: decided from the PARENT's grants for this load, never the worker's claims): net_allowed permits any well-formed method; css_allowed alone permits exactly "GET"; a NULL/empty method or no grant is refused.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `net_allowed` | `int` |  |  |
| `css_allowed` | `int` |  |  |
| `method` | `char *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`tab_subreq_permitted`](#tab_subreq_permitted) (include/tab.h:327).

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp)

---

<a id="tab_report_response_headers"></a>

### `tab_report_response_headers`

`function` | [src/tab.c:3871](../../src/tab.c#L3871)

```c
void tab_report_response_headers(const char *lines)
```

Inside a tab_fetch_fn call: reports the response header lines ("name: value\n", no Set-Cookie) the page's XHR/fetch may read.

Copied (bounded); the fetcher keeps ownership of `lines`. Outside a fetcher call it is a no-op.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lines` | `char *` |  |  |

> **Inherited:** Documentation from [`tab_report_response_headers`](#tab_report_response_headers) (include/tab.h:222).

---

<a id="tab_inflight_request_headers"></a>

### `tab_inflight_request_headers`

`function` `const` | [src/tab.c:3883](../../src/tab.c#L3883)

```c
const char *tab_inflight_request_headers(void)
```

Inside a tab_fetch_fn call: the request headers the page attached to this XHR/fetch, already filtered by rp_sanitize_request_headers ("Name: value\n" lines), or NULL when it set none.

Valid only for the duration of that call, on the calling thread; NULL anywhere else.

**Returns:** `char *`

> **Inherited:** Documentation from [`tab_inflight_request_headers`](#tab_inflight_request_headers) (include/tab.h:217).

---

<a id="fn"></a>

### `fn`

`function` | [src/tab.c:3925](../../src/tab.c#L3925)

```c
&& fn(fctx, method, url, body, blen, status, rbody, rlen, rctype) == 0);
```

**Returns:** `&&`

*Called by:* [`jd_process_iframes`](src.js_embed.c.md#jd_process_iframes), [`wst_foreach`](src.web_storage.c.md#wst_foreach)

---

<a id="tab_load"></a>

### `tab_load`

`function` | [src/tab.c:4330](../../src/tab.c#L4330)

```c
tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `html` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `out` | `tab_page *` |  |  |

**Returns:** `tab_status`

---

<a id="tab_load_ex"></a>

### `tab_load_ex`

`function` | [src/tab.c:4334](../../src/tab.c#L4334)

```c
tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `html` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `run_js` | `int` |  |  |
| `out` | `tab_page *` |  |  |

**Returns:** `tab_status`

---

<a id="tab_load_full"></a>

### `tab_load_full`

`function` | [src/tab.c:4338](../../src/tab.c#L4338)

```c
tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url, int run_js, int reader, int prefers_dark, tab_page *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `html` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `page_url` | `char *` |  |  |
| `run_js` | `int` |  |  |
| `reader` | `int` |  |  |
| `prefers_dark` | `int` |  |  |
| `out` | `tab_page *` |  |  |

**Returns:** `tab_status`

---

<a id="tab_click"></a>

### `tab_click`

`function` | [src/tab.c:4543](../../src/tab.c#L4543)

```c
tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `node_id` | `dom_node_id` |  |  |
| `out` | `tab_page *` |  |  |

**Returns:** `tab_status`

---

<a id="tab_tick"></a>

### `tab_tick`

`function` | [src/tab.c:4551](../../src/tab.c#L4551)

```c
tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `elapsed_ms` | `int` |  |  |
| `out` | `tab_page *` |  |  |

**Returns:** `tab_status`

*Called by:* [`fh_tick`](src.frame_host.c.md#fh_tick)

---

<a id="tab_submit"></a>

### `tab_submit`

`function` | [src/tab.c:4561](../../src/tab.c#L4561)

```c
tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)
```

Dispatches a submit event on the form enclosing node_id.

Simple response: [TAG_RESULT][ok:int32][prevented:int32]. No view re-derivation.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `node_id` | `dom_node_id` |  |  |
| `prevented` | `int *` |  |  |

**Returns:** `tab_status`

---

<a id="tab_read_view"></a>

### `tab_read_view`

`function` | [src/tab.c:4669](../../src/tab.c#L4669)

```c
tab_status tab_read_view(tab *t, tab_page *out)
```

Reads the TAG_RESULT + TAG_VIEW response into *out (titles + view + console).

Used by tab_mutation_request, tab_subreq, tab_dispatch_event.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `out` | `tab_page *` |  |  |

**Returns:** `tab_status`

---

<a id="frames"></a>

### `frames`

`function` | [src/tab.c:4675](../../src/tab.c#L4675)

```c
* TAG_SUBREQ frames (XHR/fetch/import()/script src) on the way: the same gated fetcher as the * load, net grant of the page, never the stylesheet grant. Anything else is a desync. */ static tab_status
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `src` | `XHR/fetch/import()/script` |  |  |

**Returns:** `* TAG_SUBREQ`

---

<a id="tab_eval"></a>

### `tab_eval`

`function` | [src/tab.c:4802](../../src/tab.c#L4802)

```c
tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `js` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `out` | `tab_eval_result *` |  |  |

**Returns:** `tab_status`

---

<a id="tab_decode_image"></a>

### `tab_decode_image`

`function` | [src/tab.c:4890](../../src/tab.c#L4890)

```c
tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `bytes` | `uint8_t *` |  |  |
| `len` | `size_t` |  |  |
| `out` | `tab_image *` |  |  |

**Returns:** `tab_status`

---

<a id="tab_decode_image_data_url"></a>

### `tab_decode_image_data_url`

`function` | [src/tab.c:4897](../../src/tab.c#L4897)

```c
tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `data_url` | `char *` |  |  |
| `out` | `tab_image *` |  |  |

**Returns:** `tab_status`

---

<a id="tab_alive"></a>

### `tab_alive`

`function` | [src/tab.c:4911](../../src/tab.c#L4911)

```c
int tab_alive(const tab *t)
```

Nonzero while the worker process is believed alive.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`tab_alive`](#tab_alive) (include/tab.h:461).

---

<a id="tab_child_pid"></a>

### `tab_child_pid`

`function` | [src/tab.c:4917](../../src/tab.c#L4917)

```c
pid_t tab_child_pid(const tab *t)
```

The worker's process id (for monitoring), or -1.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |

**Returns:** `pid_t`

> **Inherited:** Documentation from [`tab_child_pid`](#tab_child_pid) (include/tab.h:464).

---

<a id="tab_close"></a>

### `tab_close`

`function` | [src/tab.c:4921](../../src/tab.c#L4921)

```c
void tab_close(tab *t)
```

Terminates the worker and frees the handle.

Safe on NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |

> **Inherited:** Documentation from [`tab_close`](#tab_close) (include/tab.h:467).

---

<a id="tab_page_free"></a>

### `tab_page_free`

`function` | [src/tab.c:4939](../../src/tab.c#L4939)

```c
void tab_page_free(tab_page *p)
```

Idempotent releasers for the result structs.

Safe on NULL / zeroed structs.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `p` | `tab_page *` |  |  |

> **Inherited:** Documentation from [`tab_page_free`](#tab_page_free) (include/tab.h:470).

---

<a id="tab_eval_result_free"></a>

### `tab_eval_result_free`

`function` | [src/tab.c:4969](../../src/tab.c#L4969)

```c
void tab_eval_result_free(tab_eval_result *r)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `r` | `tab_eval_result *` |  |  |

---

<a id="tab_image_free"></a>

### `tab_image_free`

`function` | [src/tab.c:4978](../../src/tab.c#L4978)

```c
void tab_image_free(tab_image *img)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `img` | `tab_image *` |  |  |

---

<a id="tab_set_geometry"></a>

### `tab_set_geometry`

`function` | [src/tab.c:5018](../../src/tab.c#L5018)

```c
tab_status tab_set_geometry(tab *t, const jg_table *g)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `g` | `jg_table *` |  |  |

**Returns:** `tab_status`

---

<a id="tab_async_fd"></a>

### `tab_async_fd`

`function` | [src/tab.c:5071](../../src/tab.c#L5071)

```c
int tab_async_fd(tab *t)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |

**Returns:** `int`

---

<a id="tab_async_busy"></a>

### `tab_async_busy`

`function` | [src/tab.c:5080](../../src/tab.c#L5080)

```c
int tab_async_busy(const tab *t)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |

**Returns:** `int`

---

<a id="tab_tick_async"></a>

### `tab_tick_async`

`function` | [src/tab.c:5097](../../src/tab.c#L5097)

```c
tab_status tab_tick_async(tab *t, int elapsed_ms)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `elapsed_ms` | `int` |  |  |

**Returns:** `tab_status`

---

<a id="tab_geometry_async"></a>

### `tab_geometry_async`

`function` | [src/tab.c:5107](../../src/tab.c#L5107)

```c
tab_status tab_geometry_async(tab *t, const jg_table *g)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `g` | `jg_table *` |  |  |

**Returns:** `tab_status`

---

<a id="tab_async_finish"></a>

### `tab_async_finish`

`function` | [src/tab.c:5122](../../src/tab.c#L5122)

```c
tab_status tab_async_finish(tab *t, tab_page *out, tab_status *job_status, int *was_tick)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `out` | `tab_page *` |  |  |
| `job_status` | `tab_status *` |  |  |
| `was_tick` | `int *` |  |  |

**Returns:** `tab_status`

---

<a id="tab_popstate"></a>

### `tab_popstate`

`function` | [src/tab.c:5144](../../src/tab.c#L5144)

```c
tab_status tab_popstate(tab *t, int index, tab_page *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `index` | `int` |  |  |
| `out` | `tab_page *` |  |  |

**Returns:** `tab_status`

---

<a id="tab_ws_event"></a>

### `tab_ws_event`

`function` | [src/tab.c:5151](../../src/tab.c#L5151)

```c
tab_status tab_ws_event(tab *t, int id, int kind, int code, const char *data, size_t len, tab_page *out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `id` | `int` |  |  |
| `kind` | `int` |  |  |
| `code` | `int` |  |  |
| `data` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `out` | `tab_page *` |  |  |

**Returns:** `tab_status`

---

<a id="tab_set_storage"></a>

### `tab_set_storage`

`function` | [src/tab.c:5171](../../src/tab.c#L5171)

```c
void tab_set_storage(tab *t, const char *blob, size_t len)
```

Seeds localStorage for the next load from the parent's in-memory store for the page origin (web_storage snapshot, copied).

Used only when the load is trusted (net granted); NULL/0 clears it. See spec/web_storage.md.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `blob` | `char *` |  |  |
| `len` | `size_t` |  |  |

> **Inherited:** Documentation from [`tab_set_storage`](#tab_set_storage) (include/tab.h:292).

---

<a id="tab_anchor_free"></a>

### `tab_anchor_free`

`function` | [src/tab.c:5184](../../src/tab.c#L5184)

```c
void tab_anchor_free(tab_anchor *a)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a` | `tab_anchor *` |  |  |

---

<a id="tab_anchor_query"></a>

### `tab_anchor_query`

`function` | [src/tab.c:5190](../../src/tab.c#L5190)

```c
tab_status tab_anchor_query(tab *t, const char *fragment, const char *push_url, tab_anchor *out, tab_page *page)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |
| `fragment` | `char *` |  |  |
| `push_url` | `char *` |  |  |
| `out` | `tab_anchor *` |  |  |
| `page` | `tab_page *` |  |  |

**Returns:** `tab_status`

---

## Macros

<a id="_gnu_source"></a>

### `_GNU_SOURCE`

`macro` | [src/tab.c:14](../../src/tab.c#L14)

```c
#define _GNU_SOURCE
```

---

<a id="tab_iobuf_bytes"></a>

### `TAB_IOBUF_BYTES`

`macro` | [src/tab.c:61](../../src/tab.c#L61)

```c
#define TAB_IOBUF_BYTES
```

Batched pipe I/O for the view codec. write_view/read_view move one int32 block and one length-prefixed string at a time: ~46 000 read(2) and as many write(2) calls for a single Wikipedia page, each a context switch for 4-64 bytes.

Inside those two functions the traffic goes through a per-THREAD 64 KiB buffer instead (no state is shared: the async tick thread and the caller each have their own). The byte stream is unchanged. Writes are flushed before write_view returns. A read buffer may hold the bytes that follow the view in the same reply: they stay in it and the next read on that fd consumes them first, so no byte is ever lost; the protocol is request/response lockstep, so nothing beyond the reply can be in the pipe.

---

<a id="write_full"></a>

### `write_full`

`macro` | [src/tab.c:115](../../src/tab.c#L115)

```c
#define write_full(fd, buf, n)
```

*Called by:* [`FB_MAX_FILE_BYTES`](#fb_max_file_bytes), [`write_full`](#write_full)

---

<a id="read_full"></a>

### `read_full`

`macro` | [src/tab.c:116](../../src/tab.c#L116)

```c
#define read_full(fd, buf, n)
```

---

<a id="tab_screen_w"></a>

### `TAB_SCREEN_W`

`macro` | [src/tab.c:137](../../src/tab.c#L137)

```c
#define TAB_SCREEN_W
```

Fixed, normalized output size; fp_bucket_screen snaps it the same for all.

---

<a id="tab_wire_head_n"></a>

### `TAB_WIRE_HEAD_N`

`macro` | [src/tab.c:142](../../src/tab.c#L142)

```c
#define TAB_WIRE_HEAD_N
```

IPC wire block widths.

Single source of truth for write_view/read_view. Change requires same-diff in both functions; _Static_assert below enforces.

---

<a id="tab_wire_a_n"></a>

### `TAB_WIRE_A_N`

`macro` | [src/tab.c:143](../../src/tab.c#L143)

```c
#define TAB_WIRE_A_N
```

---

<a id="tab_wire_b_n"></a>

### `TAB_WIRE_B_N`

`macro` | [src/tab.c:144](../../src/tab.c#L144)

```c
#define TAB_WIRE_B_N
```

---

<a id="tab_wire_box_f_n"></a>

### `TAB_WIRE_BOX_F_N`

`macro` | [src/tab.c:145](../../src/tab.c#L145)

```c
#define TAB_WIRE_BOX_F_N
```

---

<a id="tab_wire_grid_n"></a>

### `TAB_WIRE_GRID_N`

`macro` | [src/tab.c:146](../../src/tab.c#L146)

```c
#define TAB_WIRE_GRID_N
```

---

<a id="tab_max_runs"></a>

### `TAB_MAX_RUNS`

`macro` | [src/tab.c:165](../../src/tab.c#L165)

```c
#define TAB_MAX_RUNS
```

Anti-amplification cap on the number of display-list runs the parent will accept from the (possibly exploited) child.

Plenty for any real page.

---

<a id="pv_max_containers_wire"></a>

### `PV_MAX_CONTAINERS_WIRE`

`macro` | [src/tab.c:169](../../src/tab.c#L169)

```c
#define PV_MAX_CONTAINERS_WIRE
```

Upper bound on the container table coming off the wire.

Mirrors page_view's own PV_MAX_CONTAINERS: the worker can never register more than that, so a larger count is a corrupt or hostile stream and the whole view is rejected.

---

<a id="tab_max_url"></a>

### `TAB_MAX_URL`

`macro` | [src/tab.c:172](../../src/tab.c#L172)

```c
#define TAB_MAX_URL
```

Cap on the page URL carried by OP_LOAD (URLs are small; defensive vs a desync).

---

<a id="tab_max_ws_msg"></a>

### `TAB_MAX_WS_MSG`

`macro` | [src/tab.c:186](../../src/tab.c#L186)

```c
#define TAB_MAX_WS_MSG
```

A WebSocket message pushed to the page (OP_WS_EVENT) is bounded like the connection's own per-message cap.

---

<a id="tab_max_storage"></a>

### `TAB_MAX_STORAGE`

`macro` | [src/tab.c:190](../../src/tab.c#L190)

```c
#define TAB_MAX_STORAGE
```

A localStorage snapshot on the wire: the quota plus the per-pair framing of a store of WST_MAX_KEYS pairs (spec/web_storage.md).

---

<a id="tab_max_hist_ops"></a>

### `TAB_MAX_HIST_OPS`

`macro` | [src/tab.c:194](../../src/tab.c#L194)

```c
#define TAB_MAX_HIST_OPS
```

History ops one response may carry (2 x JD_HIST_MAX: every push can be followed by a coalesced replace) and the bytes of their serialised form.

---

<a id="tab_max_hist_bytes"></a>

### `TAB_MAX_HIST_BYTES`

`macro` | [src/tab.c:195](../../src/tab.c#L195)

```c
#define TAB_MAX_HIST_BYTES
```

---

<a id="tab_max_opens"></a>

### `TAB_MAX_OPENS`

`macro` | [src/tab.c:197](../../src/tab.c#L197)

```c
#define TAB_MAX_OPENS
```

window.open targets one response may carry (the shim records at most 4).

---

<a id="tab_max_open_bytes"></a>

### `TAB_MAX_OPEN_BYTES`

`macro` | [src/tab.c:198](../../src/tab.c#L198)

```c
#define TAB_MAX_OPEN_BYTES
```

---

<a id="tab_max_geom_words"></a>

### `TAB_MAX_GEOM_WORDS`

`macro` | [src/tab.c:201](../../src/tab.c#L201)

```c
#define TAB_MAX_GEOM_WORDS
```

OP_GEOM payload bound in int32 words: a full js_geom table.

---

<a id="tab_max_async_pending"></a>

### `TAB_MAX_ASYNC_PENDING`

`macro` | [src/tab.c:213](../../src/tab.c#L213)

```c
#define TAB_MAX_ASYNC_PENDING
```

---

<a id="tab_max_net_rounds"></a>

### `TAB_MAX_NET_ROUNDS`

`macro` | [src/tab.c:214](../../src/tab.c#L214)

```c
#define TAB_MAX_NET_ROUNDS
```

deferred requests outstanding

---

<a id="tab_async_threads"></a>

### `TAB_ASYNC_THREADS`

`macro` | [src/tab.c:215](../../src/tab.c#L215)

```c
#define TAB_ASYNC_THREADS
```

drain rounds per operation

---

<a id="tab_max_batch_bytes"></a>

### `TAB_MAX_BATCH_BYTES`

`macro` | [src/tab.c:216](../../src/tab.c#L216)

```c
#define TAB_MAX_BATCH_BYTES
```

overlapping fetches (Firefox per-host limit)

---

<a id="tab_max_subreq"></a>

### `TAB_MAX_SUBREQ`

`macro` | [src/tab.c:220](../../src/tab.c#L220)

```c
#define TAB_MAX_SUBREQ
```

Per-page subresource caps (anti-DoS): a hostile script cannot drive unbounded fetches or amplification through the parent.

---

<a id="tab_max_subresource"></a>

### `TAB_MAX_SUBRESOURCE`

`macro` | [src/tab.c:221](../../src/tab.c#L221)

```c
#define TAB_MAX_SUBRESOURCE
```

---

<a id="tab_max_js_jobs"></a>

### `TAB_MAX_JS_JOBS`

`macro` | [src/tab.c:222](../../src/tab.c#L222)

```c
#define TAB_MAX_JS_JOBS
```

matches SF_DEFAULT_MAX_BODY; modern app bundles (e.g. youtube main) exceed 8 MiB

---

<a id="tab_cq_rederive_max"></a>

### `TAB_CQ_REDERIVE_MAX`

`macro` | [src/tab.c:295](../../src/tab.c#L295)

```c
#define TAB_CQ_REDERIVE_MAX
```

Re-derivations one DOM generation may spend on container widths that moved.

---

<a id="tab_max_extern_css"></a>

### `TAB_MAX_EXTERN_CSS`

`macro` | [src/tab.c:1355](../../src/tab.c#L1355)

```c
#define TAB_MAX_EXTERN_CSS
```

Cap on the accumulated external stylesheet text (same order as page_view's PV_MAX_STYLE_BYTES): a sheet that would overflow it is dropped WHOLE (fail closed, never truncated mid-rule).

---
