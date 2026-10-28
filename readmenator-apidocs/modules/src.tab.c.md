# `src/tab.c`

> Source: [src/tab.c:1](../../src/tab.c#L1) | language `c` | coverage 40.7% | [API index](../index.md)

## Contents

- **Structs:** [`child_state`](#child_state), [`net_reply`](#net_reply), [`tab`](#tab)
- **Functions:** [`replies`](#replies), [`run_js`](#run_js), [`buffer`](#buffer), [`blocks`](#blocks), [`FB_MAX_FILE_BYTES`](#fb_max_file_bytes), [`run`](#run), [`window`](#window), [`fallback`](#fallback), [`WHERE`](#where), [`content`](#content), [`once`](#once), [`swap`](#swap), [`write_full`](#write_full), [`EPIPE`](#epipe), [`tzset`](#tzset), [`depth`](#depth), [`tab_parse_worker_args`](#tab_parse_worker_args), [`tab_worker_dispatch`](#tab_worker_dispatch), [`tests`](#tests), [`layout`](#layout), [`column`](#column), [`tab_set_fetcher`](#tab_set_fetcher), [`tab_set_css_sink`](#tab_set_css_sink), [`tab_set_op_net_budget_ms`](#tab_set_op_net_budget_ms), [`tab_set_net_allowed`](#tab_set_net_allowed), [`tab_set_css_allowed`](#tab_set_css_allowed), [`tab_last_subreq_stats`](#tab_last_subreq_stats), [`tab_set_identity`](#tab_set_identity), [`tab_set_frame_id`](#tab_set_frame_id), [`tab_set_viewport_w`](#tab_set_viewport_w), [`tab_set_cookies`](#tab_set_cookies), [`tab_subreq_permitted`](#tab_subreq_permitted), [`tab_report_response_headers`](#tab_report_response_headers), [`tab_inflight_request_headers`](#tab_inflight_request_headers), [`tab_load`](#tab_load), [`tab_load_ex`](#tab_load_ex), [`tab_load_full`](#tab_load_full), [`tab_click`](#tab_click), [`tab_tick`](#tab_tick), [`tab_submit`](#tab_submit), [`tab_read_view`](#tab_read_view), [`frames`](#frames), [`tab_eval`](#tab_eval), [`tab_decode_image`](#tab_decode_image), [`tab_decode_image_data_url`](#tab_decode_image_data_url), [`tab_alive`](#tab_alive), [`tab_child_pid`](#tab_child_pid), [`tab_close`](#tab_close), [`tab_page_free`](#tab_page_free), [`tab_eval_result_free`](#tab_eval_result_free), [`tab_image_free`](#tab_image_free), [`tab_set_geometry`](#tab_set_geometry), [`tab_async_fd`](#tab_async_fd), [`tab_async_busy`](#tab_async_busy), [`tab_tick_async`](#tab_tick_async), [`tab_geometry_async`](#tab_geometry_async), [`tab_async_finish`](#tab_async_finish), [`tab_popstate`](#tab_popstate), [`tab_ws_event`](#tab_ws_event), [`tab_set_storage`](#tab_set_storage)
- **Macros:** [`_GNU_SOURCE`](#_gnu_source), [`TAB_SCREEN_W`](#tab_screen_w), [`TAB_WIRE_HEAD_N`](#tab_wire_head_n), [`TAB_WIRE_A_N`](#tab_wire_a_n), [`TAB_WIRE_B_N`](#tab_wire_b_n), [`TAB_WIRE_BOX_F_N`](#tab_wire_box_f_n), [`TAB_WIRE_GRID_N`](#tab_wire_grid_n), [`TAB_MAX_RUNS`](#tab_max_runs), [`PV_MAX_CONTAINERS_WIRE`](#pv_max_containers_wire), [`TAB_MAX_URL`](#tab_max_url), [`TAB_MAX_WS_MSG`](#tab_max_ws_msg), [`TAB_MAX_STORAGE`](#tab_max_storage), [`TAB_MAX_HIST_OPS`](#tab_max_hist_ops), [`TAB_MAX_HIST_BYTES`](#tab_max_hist_bytes), [`TAB_MAX_OPENS`](#tab_max_opens), [`TAB_MAX_OPEN_BYTES`](#tab_max_open_bytes), [`TAB_MAX_GEOM_WORDS`](#tab_max_geom_words), [`TAB_MAX_ASYNC_PENDING`](#tab_max_async_pending), [`TAB_MAX_NET_ROUNDS`](#tab_max_net_rounds), [`TAB_ASYNC_THREADS`](#tab_async_threads), [`TAB_MAX_BATCH_BYTES`](#tab_max_batch_bytes), [`TAB_MAX_SUBREQ`](#tab_max_subreq), [`TAB_MAX_SUBRESOURCE`](#tab_max_subresource), [`TAB_MAX_JS_JOBS`](#tab_max_js_jobs), [`TAB_MAX_EXTERN_CSS`](#tab_max_extern_css)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class child_state
    <<struct>> child_state
    class net_reply
    <<struct>> net_reply
    class net_reply_status
    <<type_alias>> net_reply_status
    class tab
    <<struct>> tab
    tab : load()
```

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_tab_c__replies(["replies"])
    n_src_tab_c__write_full(["write_full"])
    n_src_tab_c__blocks(["blocks"])
    n_src_tab_c__FB_MAX_FILE_BYTES(["FB_MAX_FILE_BYTES"])
    n_src_tab_c__tab_worker_dispatch(["tab_worker_dispatch"])
    n_src_tab_c__tab_parse_worker_args(["tab_parse_worker_args"])
    n_src_tab_c__tab_load(["tab_load"])
    n_src_tab_c__tab_load_ex(["tab_load_ex"])
    n_src_tab_c__tab_load_full(["tab_load_full"])
    n_src_tab_c__tab_submit(["tab_submit"])
    n_include_js_sandbox_h__js_pump_jobs["js_sandbox.js_pump_jobs"]
    n_src_js_fetch_c__jd_net_deliver["js_fetch.jd_net_deliver"]
    n_src_tab_c__run_js(["run_js"])
    n_include_anti_fp_h__fp_origin_key["anti_fp.fp_origin_key"]
    n_include_dom_h__dom_free["dom.dom_free"]
    n_include_freebug_h__fb_buffer_reset["freebug.fb_buffer_reset"]
    n_include_html_parse_h__hp_document_free["html_parse.hp_document_free"]
    n_include_identity_h__idn_parse["identity.idn_parse"]
    n_include_js_dom_h__jd_click_state_free["js_dom.jd_click_state_free"]
    n_include_js_sandbox_h__js_context_free["js_sandbox.js_context_free"]
    n_include_request_policy_h__rp_host_of["request_policy.rp_host_of"]
    n_include_request_policy_h__rp_site_of["request_policy.rp_site_of"]
    n_src_dom_c__dom_build["dom.dom_build"]
    n_src_html_parse_c__hp_config_default["html_parse.hp_config_default"]
    n_src_html_parse_c__hp_parse["html_parse.hp_parse"]
    n_src_js_dom_c__jd_install["js_dom.jd_install"]
    n_src_js_dom_c__jd_install_console["js_dom.jd_install_console"]
    n_src_tab_c__replies --> n_src_tab_c__write_full
    n_src_tab_c__blocks --> n_src_tab_c__write_full
    n_src_tab_c__FB_MAX_FILE_BYTES --> n_src_tab_c__write_full
    n_src_tab_c__tab_worker_dispatch --> n_src_tab_c__tab_parse_worker_args
    n_src_tab_c__tab_load --> n_src_tab_c__tab_load_ex
    n_src_tab_c__tab_load_ex --> n_src_tab_c__tab_load_full
    n_src_tab_c__tab_load_full --> n_src_tab_c__write_full
    n_src_tab_c__tab_submit --> n_src_tab_c__write_full
    n_src_tab_c__replies -.-> n_include_js_sandbox_h__js_pump_jobs
    n_src_tab_c__replies -.-> n_src_js_fetch_c__jd_net_deliver
    n_src_tab_c__run_js -.-> n_include_anti_fp_h__fp_origin_key
    n_src_tab_c__run_js -.-> n_include_dom_h__dom_free
    n_src_tab_c__run_js -.-> n_include_freebug_h__fb_buffer_reset
    n_src_tab_c__run_js -.-> n_include_html_parse_h__hp_document_free
    n_src_tab_c__run_js -.-> n_include_identity_h__idn_parse
    n_src_tab_c__run_js -.-> n_include_js_dom_h__jd_click_state_free
    n_src_tab_c__run_js -.-> n_include_js_sandbox_h__js_context_free
    n_src_tab_c__run_js -.-> n_include_request_policy_h__rp_host_of
    n_src_tab_c__run_js -.-> n_include_request_policy_h__rp_site_of
    n_src_tab_c__run_js -.-> n_src_dom_c__dom_build
    n_src_tab_c__run_js -.-> n_src_html_parse_c__hp_config_default
    n_src_tab_c__run_js -.-> n_src_html_parse_c__hp_parse
    n_src_tab_c__run_js -.-> n_src_js_dom_c__jd_install
    n_src_tab_c__run_js -.-> n_src_js_dom_c__jd_install_console
```

## Structs

<a id="child_state"></a>

### `child_state`

`struct` | [src/tab.c:156](../../src/tab.c#L156)

```c
typedef struct child_state
```

---

<a id="net_reply"></a>

### `net_reply`

`struct` | [src/tab.c:317](../../src/tab.c#L317)

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

`type_alias` | [src/tab.c:317](../../src/tab.c#L317)

```c
typedef struct net_reply { int32_t status;
```

jd_fetch_fn: the confined worker has NO network (CLONE_NEWNET + seccomp).

An XHR/fetch from page script is proxied to the TRUSTED parent over the existing pipes: write a TAG_SUBREQ frame, block for the parent's reply. The parent re-applies the FULL network policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a compromised worker still cannot reach a blocked host. Refused/over-budget/IO-error => non-zero (XHR completes with status 0). Only callable inside a page-load script window (net_active) so it never desyncs the OP_EVAL/OP_DECODE_IMAGE response paths.

---

<a id="tab"></a>

### `tab`

`struct` | [src/tab.c:2344](../../src/tab.c#L2344)

```c
struct tab
```

**Members**

| Member | Kind | Summary |
|---|---|---|
| [`load`](#tab-load) | method |  |

<a id="tab-load"></a>

#### `tab.load`

`method` | [src/tab.c:2351](../../src/tab.c#L2351)

```c
* subresource requests this load (set per page: host in allow.conf AND js.conf);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `conf` | `set per page: host in allow.conf AND js.` |  |  |

**Returns:** `* subresource requests this`

---

## Functions

<a id="replies"></a>

### `replies`

`function` | [src/tab.c:410](../../src/tab.c#L410)

```c
* writing replies (no pipe deadlock). */ static void child_net_drain(child_state *cs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `deadlock` | `no pipe` |  |  |

**Returns:** `* writing`

*Calls:* [`js_pump_jobs`](include.js_sandbox.h.md#js_pump_jobs), [`jd_net_deliver`](src.js_fetch.c.md#jd_net_deliver), [`write_full`](#write_full)

---

<a id="run_js"></a>

### `run_js`

`function` | [src/tab.c:455](../../src/tab.c#L455)

```c
* regardless of run_js (a no-JS load simply never records a request). */ static int child_load(ch...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `request` | `a no-JS load simply never records a` |  |  |

**Returns:** `* regardless of`

*Calls:* [`fp_origin_key`](include.anti_fp.h.md#fp_origin_key), [`dom_free`](include.dom.h.md#dom_free), [`fb_buffer_reset`](include.freebug.h.md#fb_buffer_reset), [`hp_document_free`](include.html_parse.h.md#hp_document_free), [`idn_parse`](include.identity.h.md#idn_parse), [`jd_click_state_free`](include.js_dom.h.md#jd_click_state_free), [`js_context_free`](include.js_sandbox.h.md#js_context_free), [`rp_host_of`](include.request_policy.h.md#rp_host_of), [`rp_site_of`](include.request_policy.h.md#rp_site_of), [`dom_build`](src.dom.c.md#dom_build), [`hp_config_default`](src.html_parse.c.md#hp_config_default), [`hp_parse`](src.html_parse.c.md#hp_parse) and 13 more

---

<a id="buffer"></a>

### `buffer`

`function` | [src/tab.c:505](../../src/tab.c#L505)

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

`function` | [src/tab.c:570](../../src/tab.c#L570)

```c
* The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the * grid array, block B[26]) exactly like the box-def f[] array, NOT one write_full per * field: the block literal lists each field once, so read_view mirrors it by index and * a desync becomes structurally hard. Adding a field is one entry in the write block + * one in the read extraction, like the box def. NO tags/versioning: the worker is the * SAME binary as the parent (/proc/self/exe --tab-worker), so write_view and read_view * are always the same build -- there is no version skew to tolerate. */ static int write_view(int wfd, const pv_view *v)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `head` |  |  |  |
| `A` | `block [36]` |  |  |
| `array` | `the * grid` |  |  |
| `B` | `block [26]` |  |  |

**Returns:** `* The scalar fields are marshalled as bulk int32`

*Calls:* [`pv_at`](include.page_view.h.md#pv_at), [`pv_box_at`](include.page_view.h.md#pv_box_at), [`pv_box_count`](include.page_view.h.md#pv_box_count), [`pv_cont_at`](include.page_view.h.md#pv_cont_at), [`pv_cont_count`](include.page_view.h.md#pv_cont_count), [`pv_count`](include.page_view.h.md#pv_count), [`write_full`](#write_full)

---

<a id="fb_max_file_bytes"></a>

### `FB_MAX_FILE_BYTES`

`function` | [src/tab.c:1002](../../src/tab.c#L1002)

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

`function` | [src/tab.c:1081](../../src/tab.c#L1081)

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

<a id="window"></a>

### `window`

`function` | [src/tab.c:1210](../../src/tab.c#L1210)

```c
* net window (cs->net_active). */ static void child_fetch_stylesheets(child_state *cs)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `net_active` | `cs->` |  |  |

**Returns:** `* net`

*Calls:* [`dropped`](include.html_parse.h.md#dropped), [`hp_extract_stylesheet_hrefs`](include.html_parse.h.md#hp_extract_stylesheet_hrefs), [`hp_free_stylesheet_hrefs`](include.html_parse.h.md#hp_free_stylesheet_hrefs)

---

<a id="fallback"></a>

### `fallback`

`function` | [src/tab.c:1336](../../src/tab.c#L1336)

```c
* <noscript> fallback (rendered only under js=0) inflates the block * count and the fuller-view heuristic picks it even with JS on. */ (void)pv_build_styled(cs->doc, run_js, reader, prefers_dark, cs->
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `js` | `rendered only under` | `0` |  |

**Returns:** `* <noscript>`

---

<a id="where"></a>

### `WHERE`

`function` | [src/tab.c:1526](../../src/tab.c#L1526)

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

`function` | [src/tab.c:1588](../../src/tab.c#L1588)

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

`function` | [src/tab.c:1637](../../src/tab.c#L1637)

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

`function` | [src/tab.c:1646](../../src/tab.c#L1646)

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

`function` | [src/tab.c:1667](../../src/tab.c#L1667)

```c
&& write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0) && write_view(wfd, write_which) == 0 && write_full(wfd, &nlen, sizeof nlen) == 0 && (nlen == 0 || write_full(wfd,
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `xl` |  |  |  |
| `xl` | `sizeof` |  |  |

**Returns:** `&&`

*Called by:* [`FB_MAX_FILE_BYTES`](#fb_max_file_bytes), [`blocks`](#blocks), [`replies`](#replies), [`tab_load_full`](#tab_load_full), [`tab_submit`](#tab_submit)

---

<a id="epipe"></a>

### `EPIPE`

`function` | [src/tab.c:2087](../../src/tab.c#L2087)

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

`function` | [src/tab.c:2103](../../src/tab.c#L2103)

```c
* tzset() caches it while syscalls are still unrestricted. */ setenv("TZ", "UTC0", 1);
```

**Returns:** `*`

---

<a id="depth"></a>

### `depth`

`function` | [src/tab.c:2117](../../src/tab.c#L2117)

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

`function` | [src/tab.c:2324](../../src/tab.c#L2324)

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

> **Inherited:** Documentation from [`tab_parse_worker_args`](#tab_parse_worker_args) (include/tab.h:167).

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp)

*Called by:* [`tab_worker_dispatch`](#tab_worker_dispatch)

---

<a id="tab_worker_dispatch"></a>

### `tab_worker_dispatch`

`function` | [src/tab.c:2334](../../src/tab.c#L2334)

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

`function` | [src/tab.c:2508](../../src/tab.c#L2508)

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

`function` | [src/tab.c:2615](../../src/tab.c#L2615)

```c
* only at layout (bx_lp_px): setting one without the other would make * the pair disagree about the same property. */ pv_set_box_pct(v, (int)bwpct, (int)b[36], (int)b[37], (int)b[38], (int)b[39]);
```

**Returns:** `setting one without the other would make * the pair disagree about the same property. */ pv_set_box_pct(v, (int)bwpct, (int)b[36], (int)b[37], (int)b[38], (int)b[39])`

---

<a id="column"></a>

### `column`

`function` | [src/tab.c:2626](../../src/tab.c#L2626)

```c
* a narrow column (jkanime's player). Mirrors the emission side, where a * control now carries the same annotation as text runs. */ pv_set_container(v, (int)cid, (int)cdisp, (int)cgap, (int)cjust, (in
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `player` | `jkanime's` |  |  |

**Returns:** `* a narrow`

---

<a id="tab_set_fetcher"></a>

### `tab_set_fetcher`

`function` | [src/tab.c:3088](../../src/tab.c#L3088)

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

> **Inherited:** Documentation from [`tab_set_fetcher`](#tab_set_fetcher) (include/tab.h:190).

---

<a id="tab_set_css_sink"></a>

### `tab_set_css_sink`

`function` | [src/tab.c:3094](../../src/tab.c#L3094)

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

`function` | [src/tab.c:3100](../../src/tab.c#L3100)

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

> **Inherited:** Documentation from [`tab_set_op_net_budget_ms`](#tab_set_op_net_budget_ms) (include/tab.h:222).

---

<a id="tab_set_net_allowed"></a>

### `tab_set_net_allowed`

`function` | [src/tab.c:3104](../../src/tab.c#L3104)

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

> **Inherited:** Documentation from [`tab_set_net_allowed`](#tab_set_net_allowed) (include/tab.h:218).

---

<a id="tab_set_css_allowed"></a>

### `tab_set_css_allowed`

`function` | [src/tab.c:3109](../../src/tab.c#L3109)

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

`function` | [src/tab.c:3114](../../src/tab.c#L3114)

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

> **Inherited:** Documentation from [`tab_last_subreq_stats`](#tab_last_subreq_stats) (include/tab.h:279).

---

<a id="tab_set_identity"></a>

### `tab_set_identity`

`function` | [src/tab.c:3119](../../src/tab.c#L3119)

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

> **Inherited:** Documentation from [`tab_set_identity`](#tab_set_identity) (include/tab.h:273).

---

<a id="tab_set_frame_id"></a>

### `tab_set_frame_id`

`function` | [src/tab.c:3127](../../src/tab.c#L3127)

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

`function` | [src/tab.c:3132](../../src/tab.c#L3132)

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

> **Inherited:** Documentation from [`tab_set_viewport_w`](#tab_set_viewport_w) (include/tab.h:263).

---

<a id="tab_set_cookies"></a>

### `tab_set_cookies`

`function` | [src/tab.c:3137](../../src/tab.c#L3137)

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

> **Inherited:** Documentation from [`tab_set_cookies`](#tab_set_cookies) (include/tab.h:244).

---

<a id="tab_subreq_permitted"></a>

### `tab_subreq_permitted`

`function` | [src/tab.c:3143](../../src/tab.c#L3143)

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

> **Inherited:** Documentation from [`tab_subreq_permitted`](#tab_subreq_permitted) (include/tab.h:284).

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp)

---

<a id="tab_report_response_headers"></a>

### `tab_report_response_headers`

`function` | [src/tab.c:3157](../../src/tab.c#L3157)

```c
void tab_report_response_headers(const char *lines)
```

Inside a tab_fetch_fn call: reports the response header lines ("name: value\n", no Set-Cookie) the page's XHR/fetch may read.

Copied (bounded); the fetcher keeps ownership of `lines`. Outside a fetcher call it is a no-op.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lines` | `char *` |  |  |

> **Inherited:** Documentation from [`tab_report_response_headers`](#tab_report_response_headers) (include/tab.h:200).

---

<a id="tab_inflight_request_headers"></a>

### `tab_inflight_request_headers`

`function` `const` | [src/tab.c:3169](../../src/tab.c#L3169)

```c
const char *tab_inflight_request_headers(void)
```

Inside a tab_fetch_fn call: the request headers the page attached to this XHR/fetch, already filtered by rp_sanitize_request_headers ("Name: value\n" lines), or NULL when it set none.

Valid only for the duration of that call, on the calling thread; NULL anywhere else.

**Returns:** `char *`

> **Inherited:** Documentation from [`tab_inflight_request_headers`](#tab_inflight_request_headers) (include/tab.h:195).

---

<a id="tab_load"></a>

### `tab_load`

`function` | [src/tab.c:3551](../../src/tab.c#L3551)

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

*Calls:* [`tab_load_ex`](#tab_load_ex)

---

<a id="tab_load_ex"></a>

### `tab_load_ex`

`function` | [src/tab.c:3555](../../src/tab.c#L3555)

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

*Calls:* [`tab_load_full`](#tab_load_full)

*Called by:* [`tab_load`](#tab_load)

---

<a id="tab_load_full"></a>

### `tab_load_full`

`function` | [src/tab.c:3559](../../src/tab.c#L3559)

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

*Calls:* [`fb_buffer_free`](include.freebug.h.md#fb_buffer_free), [`fb_buffer_init`](include.freebug.h.md#fb_buffer_init), [`pv_free`](include.page_view.h.md#pv_free), [`read_full`](include.util.h.md#read_full), [`write_full`](#write_full)

*Called by:* [`tab_load_ex`](#tab_load_ex)

---

<a id="tab_click"></a>

### `tab_click`

`function` | [src/tab.c:3760](../../src/tab.c#L3760)

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

`function` | [src/tab.c:3768](../../src/tab.c#L3768)

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

`function` | [src/tab.c:3778](../../src/tab.c#L3778)

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

*Calls:* [`read_full`](include.util.h.md#read_full), [`write_full`](#write_full)

---

<a id="tab_read_view"></a>

### `tab_read_view`

`function` | [src/tab.c:3886](../../src/tab.c#L3886)

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

`function` | [src/tab.c:3892](../../src/tab.c#L3892)

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

`function` | [src/tab.c:4007](../../src/tab.c#L4007)

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

`function` | [src/tab.c:4090](../../src/tab.c#L4090)

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

`function` | [src/tab.c:4097](../../src/tab.c#L4097)

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

`function` | [src/tab.c:4116](../../src/tab.c#L4116)

```c
int tab_alive(const tab *t)
```

Nonzero while the worker process is believed alive.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`tab_alive`](#tab_alive) (include/tab.h:400).

---

<a id="tab_child_pid"></a>

### `tab_child_pid`

`function` | [src/tab.c:4122](../../src/tab.c#L4122)

```c
pid_t tab_child_pid(const tab *t)
```

The worker's process id (for monitoring), or -1.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |

**Returns:** `pid_t`

> **Inherited:** Documentation from [`tab_child_pid`](#tab_child_pid) (include/tab.h:403).

---

<a id="tab_close"></a>

### `tab_close`

`function` | [src/tab.c:4126](../../src/tab.c#L4126)

```c
void tab_close(tab *t)
```

Terminates the worker and frees the handle.

Safe on NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `t` | `tab *` |  |  |

> **Inherited:** Documentation from [`tab_close`](#tab_close) (include/tab.h:406).

---

<a id="tab_page_free"></a>

### `tab_page_free`

`function` | [src/tab.c:4144](../../src/tab.c#L4144)

```c
void tab_page_free(tab_page *p)
```

Idempotent releasers for the result structs.

Safe on NULL / zeroed structs.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `p` | `tab_page *` |  |  |

> **Inherited:** Documentation from [`tab_page_free`](#tab_page_free) (include/tab.h:409).

---

<a id="tab_eval_result_free"></a>

### `tab_eval_result_free`

`function` | [src/tab.c:4174](../../src/tab.c#L4174)

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

`function` | [src/tab.c:4183](../../src/tab.c#L4183)

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

`function` | [src/tab.c:4223](../../src/tab.c#L4223)

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

`function` | [src/tab.c:4275](../../src/tab.c#L4275)

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

`function` | [src/tab.c:4284](../../src/tab.c#L4284)

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

`function` | [src/tab.c:4301](../../src/tab.c#L4301)

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

`function` | [src/tab.c:4311](../../src/tab.c#L4311)

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

`function` | [src/tab.c:4326](../../src/tab.c#L4326)

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

`function` | [src/tab.c:4348](../../src/tab.c#L4348)

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

`function` | [src/tab.c:4355](../../src/tab.c#L4355)

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

`function` | [src/tab.c:4375](../../src/tab.c#L4375)

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

> **Inherited:** Documentation from [`tab_set_storage`](#tab_set_storage) (include/tab.h:249).

---

## Macros

<a id="_gnu_source"></a>

### `_GNU_SOURCE`

`macro` | [src/tab.c:14](../../src/tab.c#L14)

```c
#define _GNU_SOURCE
```

---

<a id="tab_screen_w"></a>

### `TAB_SCREEN_W`

`macro` | [src/tab.c:65](../../src/tab.c#L65)

```c
#define TAB_SCREEN_W
```

Fixed, normalized output size; fp_bucket_screen snaps it the same for all.

---

<a id="tab_wire_head_n"></a>

### `TAB_WIRE_HEAD_N`

`macro` | [src/tab.c:70](../../src/tab.c#L70)

```c
#define TAB_WIRE_HEAD_N
```

IPC wire block widths.

Single source of truth for write_view/read_view. Change requires same-diff in both functions; _Static_assert below enforces.

---

<a id="tab_wire_a_n"></a>

### `TAB_WIRE_A_N`

`macro` | [src/tab.c:71](../../src/tab.c#L71)

```c
#define TAB_WIRE_A_N
```

---

<a id="tab_wire_b_n"></a>

### `TAB_WIRE_B_N`

`macro` | [src/tab.c:72](../../src/tab.c#L72)

```c
#define TAB_WIRE_B_N
```

---

<a id="tab_wire_box_f_n"></a>

### `TAB_WIRE_BOX_F_N`

`macro` | [src/tab.c:73](../../src/tab.c#L73)

```c
#define TAB_WIRE_BOX_F_N
```

---

<a id="tab_wire_grid_n"></a>

### `TAB_WIRE_GRID_N`

`macro` | [src/tab.c:74](../../src/tab.c#L74)

```c
#define TAB_WIRE_GRID_N
```

---

<a id="tab_max_runs"></a>

### `TAB_MAX_RUNS`

`macro` | [src/tab.c:93](../../src/tab.c#L93)

```c
#define TAB_MAX_RUNS
```

Anti-amplification cap on the number of display-list runs the parent will accept from the (possibly exploited) child.

Plenty for any real page.

---

<a id="pv_max_containers_wire"></a>

### `PV_MAX_CONTAINERS_WIRE`

`macro` | [src/tab.c:97](../../src/tab.c#L97)

```c
#define PV_MAX_CONTAINERS_WIRE
```

Upper bound on the container table coming off the wire.

Mirrors page_view's own PV_MAX_CONTAINERS: the worker can never register more than that, so a larger count is a corrupt or hostile stream and the whole view is rejected.

---

<a id="tab_max_url"></a>

### `TAB_MAX_URL`

`macro` | [src/tab.c:100](../../src/tab.c#L100)

```c
#define TAB_MAX_URL
```

Cap on the page URL carried by OP_LOAD (URLs are small; defensive vs a desync).

---

<a id="tab_max_ws_msg"></a>

### `TAB_MAX_WS_MSG`

`macro` | [src/tab.c:109](../../src/tab.c#L109)

```c
#define TAB_MAX_WS_MSG
```

A WebSocket message pushed to the page (OP_WS_EVENT) is bounded like the connection's own per-message cap.

---

<a id="tab_max_storage"></a>

### `TAB_MAX_STORAGE`

`macro` | [src/tab.c:113](../../src/tab.c#L113)

```c
#define TAB_MAX_STORAGE
```

A localStorage snapshot on the wire: the quota plus the per-pair framing of a store of WST_MAX_KEYS pairs (spec/web_storage.md).

---

<a id="tab_max_hist_ops"></a>

### `TAB_MAX_HIST_OPS`

`macro` | [src/tab.c:117](../../src/tab.c#L117)

```c
#define TAB_MAX_HIST_OPS
```

History ops one response may carry (2 x JD_HIST_MAX: every push can be followed by a coalesced replace) and the bytes of their serialised form.

---

<a id="tab_max_hist_bytes"></a>

### `TAB_MAX_HIST_BYTES`

`macro` | [src/tab.c:118](../../src/tab.c#L118)

```c
#define TAB_MAX_HIST_BYTES
```

---

<a id="tab_max_opens"></a>

### `TAB_MAX_OPENS`

`macro` | [src/tab.c:120](../../src/tab.c#L120)

```c
#define TAB_MAX_OPENS
```

window.open targets one response may carry (the shim records at most 4).

---

<a id="tab_max_open_bytes"></a>

### `TAB_MAX_OPEN_BYTES`

`macro` | [src/tab.c:121](../../src/tab.c#L121)

```c
#define TAB_MAX_OPEN_BYTES
```

---

<a id="tab_max_geom_words"></a>

### `TAB_MAX_GEOM_WORDS`

`macro` | [src/tab.c:124](../../src/tab.c#L124)

```c
#define TAB_MAX_GEOM_WORDS
```

OP_GEOM payload bound in int32 words: a full js_geom table.

---

<a id="tab_max_async_pending"></a>

### `TAB_MAX_ASYNC_PENDING`

`macro` | [src/tab.c:136](../../src/tab.c#L136)

```c
#define TAB_MAX_ASYNC_PENDING
```

---

<a id="tab_max_net_rounds"></a>

### `TAB_MAX_NET_ROUNDS`

`macro` | [src/tab.c:137](../../src/tab.c#L137)

```c
#define TAB_MAX_NET_ROUNDS
```

deferred requests outstanding

---

<a id="tab_async_threads"></a>

### `TAB_ASYNC_THREADS`

`macro` | [src/tab.c:138](../../src/tab.c#L138)

```c
#define TAB_ASYNC_THREADS
```

drain rounds per operation

---

<a id="tab_max_batch_bytes"></a>

### `TAB_MAX_BATCH_BYTES`

`macro` | [src/tab.c:139](../../src/tab.c#L139)

```c
#define TAB_MAX_BATCH_BYTES
```

overlapping fetches (Firefox per-host limit)

---

<a id="tab_max_subreq"></a>

### `TAB_MAX_SUBREQ`

`macro` | [src/tab.c:143](../../src/tab.c#L143)

```c
#define TAB_MAX_SUBREQ
```

Per-page subresource caps (anti-DoS): a hostile script cannot drive unbounded fetches or amplification through the parent.

---

<a id="tab_max_subresource"></a>

### `TAB_MAX_SUBRESOURCE`

`macro` | [src/tab.c:144](../../src/tab.c#L144)

```c
#define TAB_MAX_SUBRESOURCE
```

---

<a id="tab_max_js_jobs"></a>

### `TAB_MAX_JS_JOBS`

`macro` | [src/tab.c:145](../../src/tab.c#L145)

```c
#define TAB_MAX_JS_JOBS
```

matches SF_DEFAULT_MAX_BODY; modern app bundles (e.g. youtube main) exceed 8 MiB

---

<a id="tab_max_extern_css"></a>

### `TAB_MAX_EXTERN_CSS`

`macro` | [src/tab.c:1075](../../src/tab.c#L1075)

```c
#define TAB_MAX_EXTERN_CSS
```

Cap on the accumulated external stylesheet text (same order as page_view's PV_MAX_STYLE_BYTES): a sheet that would overflow it is dropped WHOLE (fail closed, never truncated mid-rule).

---
