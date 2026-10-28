# `src/js_sandbox.c`

> Source: [src/js_sandbox.c:1](../../src/js_sandbox.c#L1) | language `c` | coverage 39.4% | [API index](../index.md)

## Contents

- **Structs:** [`js_mem_state`](#js_mem_state), [`js_context`](#js_context)
- **Functions:** [`js_profile_enable`](#js_profile_enable), [`js_profile_report`](#js_profile_report), [`js_throws_enable`](#js_throws_enable), [`js_throws_report`](#js_throws_report), [`js_devtools_enable`](#js_devtools_enable), [`js_devtools_expose`](#js_devtools_expose), [`js_loc_from_stack`](#js_loc_from_stack), [`undefined`](#undefined), [`js_stack_limit_for`](#js_stack_limit_for), [`js_prime_stack_limit`](#js_prime_stack_limit), [`js_limits_default`](#js_limits_default), [`js_validate_source`](#js_validate_source), [`js_context_new`](#js_context_new), [`js_context_free`](#js_context_free), [`js_set_time_budget`](#js_set_time_budget), [`js_eval`](#js_eval), [`js_eval_named`](#js_eval_named), [`js_pump_jobs`](#js_pump_jobs), [`js_eval_once`](#js_eval_once), [`js_result_free`](#js_result_free), [`js_set_current_script`](#js_set_current_script), [`js_context_raw`](#js_context_raw), [`js_set_module_host`](#js_set_module_host), [`js_eval_module`](#js_eval_module), [`js_install_realms`](#js_install_realms)
- **Macros:** [`_POSIX_C_SOURCE`](#_posix_c_source), [`JS_PROFILE_SLOTS`](#js_profile_slots), [`JS_PROFILE_KEY_MAX`](#js_profile_key_max), [`JS_MODULE_URL_MAX`](#js_module_url_max)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class js_mem_state
    <<struct>> js_mem_state
    class js_mem_state_limit
    <<type_alias>> js_mem_state_limit
    class js_context
    <<struct>> js_context
```

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_js_sandbox_c__js_devtools_enable(["js_devtools_enable"])
    n_src_js_sandbox_c__js_profile_enable(["js_profile_enable"])
    n_src_js_sandbox_c__js_throws_enable(["js_throws_enable"])
    n_src_js_sandbox_c__js_limits_default(["js_limits_default"])
    n_src_js_sandbox_c__js_stack_limit_for(["js_stack_limit_for"])
    n_src_js_sandbox_c__js_eval(["js_eval"])
    n_src_js_sandbox_c__js_eval_named(["js_eval_named"])
    n_src_js_sandbox_c__js_validate_source(["js_validate_source"])
    n_src_js_sandbox_c__js_eval_once(["js_eval_once"])
    n_src_js_sandbox_c__js_context_free(["js_context_free"])
    n_src_js_sandbox_c__js_context_new(["js_context_new"])
    n_src_js_sandbox_c__js_eval_module(["js_eval_module"])
    n_gui_browser_ui_c__strcmp["browser_ui.strcmp"]
    n_src_js_sandbox_c__js_devtools_enable --> n_src_js_sandbox_c__js_profile_enable
    n_src_js_sandbox_c__js_devtools_enable --> n_src_js_sandbox_c__js_throws_enable
    n_src_js_sandbox_c__js_limits_default --> n_src_js_sandbox_c__js_stack_limit_for
    n_src_js_sandbox_c__js_eval --> n_src_js_sandbox_c__js_eval_named
    n_src_js_sandbox_c__js_eval_named --> n_src_js_sandbox_c__js_validate_source
    n_src_js_sandbox_c__js_eval_once --> n_src_js_sandbox_c__js_context_free
    n_src_js_sandbox_c__js_eval_once --> n_src_js_sandbox_c__js_context_new
    n_src_js_sandbox_c__js_eval_once --> n_src_js_sandbox_c__js_eval
    n_src_js_sandbox_c__js_eval_module --> n_src_js_sandbox_c__js_validate_source
    n_src_js_sandbox_c__js_eval_module -.-> n_gui_browser_ui_c__strcmp
```

## Structs

<a id="js_mem_state"></a>

### `js_mem_state`

`struct` | [src/js_sandbox.c:29](../../src/js_sandbox.c#L29)

```c
typedef struct js_mem_state
```

We enforce the heap cap ourselves (not via JS_SetMemoryLimit, whose check runs *inside* QuickJS before our allocator and is therefore unobservable).

Leaving QuickJS's own limit at its default (0 == unlimited) makes this the sole enforcer, so a denied allocation is a deterministic, testable signal.

**Members**

| Member | Kind | Summary |
|---|---|---|
| [`limit`](#js_mem_state-limit) | type_alias | We enforce the heap cap ourselves (not via JS_SetMemoryLimit, whose check runs *inside* QuickJS before our allocator and is therefore unobservable). |

<a id="js_mem_state-limit"></a>

#### `js_mem_state.limit`

`type_alias` | [src/js_sandbox.c:29](../../src/js_sandbox.c#L29)

```c
typedef struct js_mem_state { size_t limit;
```

We enforce the heap cap ourselves (not via JS_SetMemoryLimit, whose check runs *inside* QuickJS before our allocator and is therefore unobservable).

Leaving QuickJS's own limit at its default (0 == unlimited) makes this the sole enforcer, so a denied allocation is a deterministic, testable signal.

---

<a id="js_context"></a>

### `js_context`

`struct` | [src/js_sandbox.c:38](../../src/js_sandbox.c#L38)

```c
struct js_context
```

---

## Functions

<a id="js_profile_enable"></a>

### `js_profile_enable`

`function` | [src/js_sandbox.c:222](../../src/js_sandbox.c#L222)

```c
void js_profile_enable(js_context *ctx)
```

Sampling profiler (FREEDOM_JS_PROFILE=2).

Once enabled, the interrupt handler samples the running JS stack at most once per JS_PROFILE_PERIOD_MS and counts the innermost two frames. js_profile_report writes "<percent>% <frame> <- <caller>" lines, hottest first, into out (NUL-terminated, truncated at cap); returns bytes written. Both are no-ops on a * NULL context; the table is fixed-size, so a hostile page cannot grow it. define JS_PROFILE_PERIOD_MS 1

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

> **Inherited:** Documentation from [`js_profile_enable`](#js_profile_enable) (include/js_sandbox.h:166).

*Called by:* [`js_devtools_enable`](#js_devtools_enable)

---

<a id="js_profile_report"></a>

### `js_profile_report`

`function` | [src/js_sandbox.c:228](../../src/js_sandbox.c#L228)

```c
size_t js_profile_report(js_context *ctx, char *out, size_t cap, size_t top_n)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |
| `top_n` | `size_t` |  |  |

**Returns:** `size_t`

---

<a id="js_throws_enable"></a>

### `js_throws_enable`

`function` | [src/js_sandbox.c:328](../../src/js_sandbox.c#L328)

```c
void js_throws_enable(js_context *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

*Called by:* [`js_devtools_enable`](#js_devtools_enable)

---

<a id="js_throws_report"></a>

### `js_throws_report`

`function` | [src/js_sandbox.c:334](../../src/js_sandbox.c#L334)

```c
size_t js_throws_report(js_context *ctx, char *out, size_t cap, size_t top_n)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |
| `top_n` | `size_t` |  |  |

**Returns:** `size_t`

---

<a id="js_devtools_enable"></a>

### `js_devtools_enable`

`function` | [src/js_sandbox.c:372](../../src/js_sandbox.c#L372)

```c
void js_devtools_enable(js_context *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

*Calls:* [`js_profile_enable`](#js_profile_enable), [`js_throws_enable`](#js_throws_enable)

*Called by:* [`run_js`](src.tab.c.md#run_js)

---

<a id="js_devtools_expose"></a>

### `js_devtools_expose`

`function` | [src/js_sandbox.c:378](../../src/js_sandbox.c#L378)

```c
js_status js_devtools_expose(js_context *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `js_status`

---

<a id="js_loc_from_stack"></a>

### `js_loc_from_stack`

`function` | [src/js_sandbox.c:420](../../src/js_sandbox.c#L420)

```c
int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap, int *line, int *col)
```

Pure parser: extracts the throw site (file, line, column) from the FIRST frame of a QuickJS .stack string.

Recognised frame forms: at <name> (<file>:<line>:<col>) at <file>:<line>:<col> Writes up to file_cap-1 bytes of <file> (NUL-terminated) into file_out and the numbers into *line / *col (*col is 0 when the frame carries only a line). Returns 1 when a line number was parsed, else 0 (file_out emptied, *line=*col=0). Tolerant of NULL/garbage input. No I/O, no allocation, reentrant.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `stack` | `char *` |  |  |
| `file_out` | `char *` |  |  |
| `file_cap` | `size_t` |  |  |
| `line` | `int *` |  |  |
| `col` | `int *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`js_loc_from_stack`](#js_loc_from_stack) (include/js_sandbox.h:150).

---

<a id="undefined"></a>

### `undefined`

`function` | [src/js_sandbox.c:512](../../src/js_sandbox.c#L512)

```c
* yields undefined (or a getter throws), in which case we leave it unknown. */ JSValue st = JS_GetPropertyStr(ctx, exc, "stack");
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `throws` | `or a getter` |  |  |

**Returns:** `* yields`

---

<a id="js_stack_limit_for"></a>

### `js_stack_limit_for`

`function` | [src/js_sandbox.c:539](../../src/js_sandbox.c#L539)

```c
size_t js_stack_limit_for(size_t soft_stack)
```

Engine stack cap for a process whose soft stack limit is `soft_stack` bytes (0 = unknown): 75 % of it (the rest is for native frames), within [JS_MIN_STACK_LIMIT, JS_MAX_STACK_LIMIT].

Pure.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `soft_stack` | `size_t` |  |  |

**Returns:** `size_t`

> **Inherited:** Documentation from [`js_stack_limit_for`](#js_stack_limit_for) (include/js_sandbox.h:75).

*Called by:* [`js_limits_default`](#js_limits_default)

---

<a id="js_prime_stack_limit"></a>

### `js_prime_stack_limit`

`function` | [src/js_sandbox.c:560](../../src/js_sandbox.c#L560)

```c
void js_prime_stack_limit(void)
```

Reads the process stack limit now.

A process that will confine itself with seccomp calls this first: getrlimit is not allowed afterwards, and js_limits_default() needs the value.

> **Inherited:** Documentation from [`js_prime_stack_limit`](#js_prime_stack_limit) (include/js_sandbox.h:79).

---

<a id="js_limits_default"></a>

### `js_limits_default`

`function` | [src/js_sandbox.c:562](../../src/js_sandbox.c#L562)

```c
js_limits js_limits_default(void)
```

**Returns:** `js_limits`

*Calls:* [`js_stack_limit_for`](#js_stack_limit_for)

---

<a id="js_validate_source"></a>

### `js_validate_source`

`function` | [src/js_sandbox.c:580](../../src/js_sandbox.c#L580)

```c
js_status js_validate_source(const char *src, size_t len, const js_limits *lim)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `src` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `lim` | `js_limits *` |  |  |

**Returns:** `js_status`

*Called by:* [`js_eval_module`](#js_eval_module), [`js_eval_named`](#js_eval_named)

---

<a id="js_context_new"></a>

### `js_context_new`

`function` | [src/js_sandbox.c:591](../../src/js_sandbox.c#L591)

```c
js_status js_context_new(const js_limits *lim, js_context **out)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lim` | `js_limits *` |  |  |
| `out` | `js_context **` |  |  |

**Returns:** `js_status`

*Called by:* [`js_eval_once`](#js_eval_once), [`run_js`](src.tab.c.md#run_js)

---

<a id="js_context_free"></a>

### `js_context_free`

`function` | [src/js_sandbox.c:631](../../src/js_sandbox.c#L631)

```c
void js_context_free(js_context *ctx)
```

Idempotent; safe on NULL and safe to call twice.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

> **Inherited:** Documentation from [`js_context_free`](#js_context_free) (include/js_sandbox.h:96).

*Called by:* [`js_eval_once`](#js_eval_once)

---

<a id="js_set_time_budget"></a>

### `js_set_time_budget`

`function` | [src/js_sandbox.c:658](../../src/js_sandbox.c#L658)

```c
void js_set_time_budget(js_context *ctx, uint64_t budget_ms)
```

Adjusts the wall-clock budget armed on each subsequent js_eval.

Used to enforce a single page-wide budget across a sequence of evaluations (e.g. a page's inline scripts run one by one): the caller lowers the budget to the time remaining before each call, so isolating scripts into separate evals does not multiply the cap. No-op on a NULL context. Does not affect an evaluation already in progress.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `budget_ms` | `uint64_t` |  |  |

> **Inherited:** Documentation from [`js_set_time_budget`](#js_set_time_budget) (include/js_sandbox.h:158).

---

<a id="js_eval"></a>

### `js_eval`

`function` | [src/js_sandbox.c:663](../../src/js_sandbox.c#L663)

```c
js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `src` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `res` | `js_result *` |  |  |

**Returns:** `js_status`

*Calls:* [`js_eval_named`](#js_eval_named)

*Called by:* [`js_eval_once`](#js_eval_once)

---

<a id="js_eval_named"></a>

### `js_eval_named`

`function` | [src/js_sandbox.c:667](../../src/js_sandbox.c#L667)

```c
js_status js_eval_named(js_context *ctx, const char *src, size_t len, const char *filename, js_result *res)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `src` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `filename` | `char *` |  |  |
| `res` | `js_result *` |  |  |

**Returns:** `js_status`

*Calls:* [`js_validate_source`](#js_validate_source)

*Called by:* [`js_eval`](#js_eval)

---

<a id="js_pump_jobs"></a>

### `js_pump_jobs`

`function` | [src/js_sandbox.c:750](../../src/js_sandbox.c#L750)

```c
int js_pump_jobs(js_context *ctx, int max_jobs)
```

Runs up to max_jobs pending microtasks/jobs (promise reactions queued by the last eval), under the context's current time budget.

Job exceptions (rejected promises with no handler, etc.) are swallowed -- a job never aborts the caller. Returns the number of jobs run. Needed because js_eval does not drain the queue itself, so promise/.then/await continuations (e.g. from fetch) would otherwise never run. No-op (returns 0) on a NULL context.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `max_jobs` | `int` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`js_pump_jobs`](#js_pump_jobs) (include/js_sandbox.h:195).

---

<a id="js_eval_once"></a>

### `js_eval_once`

`function` | [src/js_sandbox.c:769](../../src/js_sandbox.c#L769)

```c
js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `src` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `lim` | `js_limits *` |  |  |
| `res` | `js_result *` |  |  |

**Returns:** `js_status`

*Calls:* [`js_context_free`](#js_context_free), [`js_context_new`](#js_context_new), [`js_eval`](#js_eval)

---

<a id="js_result_free"></a>

### `js_result_free`

`function` | [src/js_sandbox.c:782](../../src/js_sandbox.c#L782)

```c
void js_result_free(js_result *res)
```

Idempotent; safe on a zero-initialised struct and safe to call twice.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `res` | `js_result *` |  |  |

> **Inherited:** Documentation from [`js_result_free`](#js_result_free) (include/js_sandbox.h:187).

---

<a id="js_set_current_script"></a>

### `js_set_current_script`

`function` | [src/js_sandbox.c:810](../../src/js_sandbox.c#L810)

```c
void js_set_current_script(js_context *ctx, const char *src, const char *type)
```

Sets document.currentScript on the global object so external scripts can read their own src / type / data-* attributes through getAttribute.

The script element is a fabricated plain object with {src, type, getAttribute} that answers these three keys. Pass src=NULL for an inline script (no src attribute). Call after the evaluation to restore currentScript to null.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `src` | `char *` |  |  |
| `type` | `char *` |  |  |

> **Inherited:** Documentation from [`js_set_current_script`](#js_set_current_script) (include/js_sandbox.h:207).

---

<a id="js_context_raw"></a>

### `js_context_raw`

`function` | [src/js_sandbox.c:843](../../src/js_sandbox.c#L843)

```c
void *js_context_raw(js_context *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `void *`

*Called by:* [`jd_inject_video_shim`](src.js_embed.c.md#jd_inject_video_shim), [`jd_process_iframes`](src.js_embed.c.md#jd_process_iframes), [`je_install_canvas`](src.js_env.c.md#je_install_canvas), [`je_install_identity_trusted`](src.js_env.c.md#je_install_identity_trusted), [`jd_fire_click`](src.js_events.c.md#jd_fire_click), [`jd_fire_mouse_event`](src.js_events.c.md#jd_fire_mouse_event), [`jd_fire_submit`](src.js_events.c.md#jd_fire_submit), [`jd_install_events`](src.js_events.c.md#jd_install_events), [`jd_install_xhr_ex`](src.js_fetch.c.md#jd_install_xhr_ex), [`jd_net_deliver`](src.js_fetch.c.md#jd_net_deliver), [`jd_pop_state`](src.js_location.c.md#jd_pop_state), [`jd_set_location`](src.js_location.c.md#jd_set_location) and 13 more

---

<a id="js_set_module_host"></a>

### `js_set_module_host`

`function` | [src/js_sandbox.c:923](../../src/js_sandbox.c#L923)

```c
void js_set_module_host(js_context *ctx, js_module_resolve_fn resolve, js_module_fetch_fn fetch, void *host)
```

Installs the host every static import and dynamic import() goes through. host must outlive ctx.

NULL functions uninstall it (every import then fails).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `resolve` | `js_module_resolve_fn` |  |  |
| `fetch` | `js_module_fetch_fn` |  |  |
| `host` | `void *` |  |  |

> **Inherited:** Documentation from [`js_set_module_host`](#js_set_module_host) (include/js_sandbox.h:129).

---

<a id="js_eval_module"></a>

### `js_eval_module`

`function` | [src/js_sandbox.c:953](../../src/js_sandbox.c#L953)

```c
js_status js_eval_module(js_context *ctx, const char *src, size_t len, const char *name, js_result *res)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |
| `src` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `name` | `char *` |  |  |
| `res` | `js_result *` |  |  |

**Returns:** `js_status`

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp), [`js_validate_source`](#js_validate_source)

---

<a id="js_install_realms"></a>

### `js_install_realms`

`function` | [src/js_sandbox.c:1115](../../src/js_sandbox.c#L1115)

```c
js_status js_install_realms(js_context *ctx)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ctx` | `js_context *` |  |  |

**Returns:** `js_status`

*Called by:* [`jt_enable_worker`](src.js_trusted.c.md#jt_enable_worker)

---

## Macros

<a id="_posix_c_source"></a>

### `_POSIX_C_SOURCE`

`macro` | [src/js_sandbox.c:12](../../src/js_sandbox.c#L12)

```c
#define _POSIX_C_SOURCE
```

---

<a id="js_profile_slots"></a>

### `JS_PROFILE_SLOTS`

`macro` | [src/js_sandbox.c:35](../../src/js_sandbox.c#L35)

```c
#define JS_PROFILE_SLOTS
```

---

<a id="js_profile_key_max"></a>

### `JS_PROFILE_KEY_MAX`

`macro` | [src/js_sandbox.c:36](../../src/js_sandbox.c#L36)

```c
#define JS_PROFILE_KEY_MAX
```

---

<a id="js_module_url_max"></a>

### `JS_MODULE_URL_MAX`

`macro` | [src/js_sandbox.c:848](../../src/js_sandbox.c#L848)

```c
#define JS_MODULE_URL_MAX
```

Longest module URL the resolver may produce (matches url.h's URL_MAX_LEN).

---
