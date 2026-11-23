# `include/subreq_batch.h`

> Source: [include/subreq_batch.h:1](../../include/subreq_batch.h#L1) | language `h` | coverage 64.7% | [API index](../index.md)

## Contents

- **Structs:** [`sqb_req`](#sqb_req), [`sqb_res`](#sqb_res)
- **Type Aliases:** [`ok`](#ok), [`sqb`](#sqb)
- **Functions:** [`sqb_new`](#sqb_new), [`sqb_new_owned`](#sqb_new_owned), [`sqb_abandon`](#sqb_abandon), [`sqb_submit`](#sqb_submit), [`sqb_count`](#sqb_count), [`sqb_wait_all`](#sqb_wait_all), [`sqb_result`](#sqb_result), [`sqb_wait_ready`](#sqb_wait_ready), [`sqb_remove`](#sqb_remove), [`sqb_reset`](#sqb_reset), [`sqb_free`](#sqb_free)
- **Macros:** [`SQB_MAX_JOBS`](#sqb_max_jobs)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class sqb_req
    <<struct>> sqb_req
    class ok
    <<type_alias>> ok
    class sqb_res
    <<struct>> sqb_res
    class sqb
    <<type_alias>> sqb
```

## Structs

<a id="sqb_req"></a>

### `sqb_req`

`struct` | [include/subreq_batch.h:16](../../include/subreq_batch.h#L16)

```c
typedef struct sqb_req
```

---

<a id="sqb_res"></a>

### `sqb_res`

`struct` | [include/subreq_batch.h:23](../../include/subreq_batch.h#L23)

```c
typedef struct sqb_res
```

Filled by the run callback; every pointer malloc'd and owned by the batch afterwards.

---

## Type Aliases

<a id="ok"></a>

### `ok`

`type_alias` | [include/subreq_batch.h:23](../../include/subreq_batch.h#L23)

```c
typedef struct sqb_res { int ok;
```

Filled by the run callback; every pointer malloc'd and owned by the batch afterwards.

---

<a id="sqb"></a>

### `sqb`

`type_alias` | [include/subreq_batch.h:34](../../include/subreq_batch.h#L34)

```c
typedef struct sqb sqb;
```

---

## Functions

<a id="sqb_new"></a>

### `sqb_new`

`function` | [include/subreq_batch.h:37](../../include/subreq_batch.h#L37)

```c
sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `max_threads` | `int` |  |  |
| `run` | `sqb_run_fn` |  |  |
| `ctx` | `void *` |  |  |

**Returns:** `sqb *`

---

<a id="sqb_new_owned"></a>

### `sqb_new_owned`

`function` | [include/subreq_batch.h:40](../../include/subreq_batch.h#L40)

```c
sqb *sqb_new_owned(int max_threads, sqb_run_fn run, void *ctx, void (*free_ctx)(void *));
```

sqb_new whose ctx the batch OWNS: free_ctx(ctx) runs once the batch is freed AND every abandoned request has finished -- the run callback may use ctx until then.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `max_threads` | `int` |  |  |
| `run` | `sqb_run_fn` |  |  |
| `ctx` | `void *` |  |  |
| `void` | `void (*free_ctx)( *)` |  |  |

**Returns:** `sqb *`

---

<a id="sqb_abandon"></a>

### `sqb_abandon`

`function` | [include/subreq_batch.h:43](../../include/subreq_batch.h#L43)

```c
void sqb_abandon(sqb *b);
```

Frees every finished job and ABANDONS every running one: its thread is detached, its result is discarded when it ends, and nothing here waits.

The batch is empty and reusable.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `sqb *` |  |  |

---

<a id="sqb_submit"></a>

### `sqb_submit`

`function` | [include/subreq_batch.h:47](../../include/subreq_batch.h#L47)

```c
int sqb_submit(sqb *b, int refused, const sqb_req *req);
```

Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result count always equals the submit count.

Returns 0, or -1 when full / out of memory (nothing queued: the caller must answer the worker itself).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `sqb *` |  |  |
| `refused` | `int` |  |  |
| `req` | `sqb_req *` |  |  |

**Returns:** `int`

---

<a id="sqb_count"></a>

### `sqb_count`

`function` | [include/subreq_batch.h:48](../../include/subreq_batch.h#L48)

```c
size_t sqb_count(const sqb *b);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `sqb *` |  |  |

**Returns:** `size_t`

---

<a id="sqb_wait_all"></a>

### `sqb_wait_all`

`function` | [include/subreq_batch.h:50](../../include/subreq_batch.h#L50)

```c
void sqb_wait_all(sqb *b);
```

Joins every running request.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `sqb *` |  |  |

---

<a id="sqb_result"></a>

### `sqb_result`

`function` `const` | [include/subreq_batch.h:52](../../include/subreq_batch.h#L52)

```c
const sqb_res *sqb_result(const sqb *b, size_t i);
```

Valid after sqb_wait_all, for i < sqb_count.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `sqb *` |  |  |
| `i` | `size_t` |  |  |

**Returns:** `sqb_res *`

---

<a id="sqb_wait_ready"></a>

### `sqb_wait_ready`

`function` | [include/subreq_batch.h:56](../../include/subreq_batch.h#L56)

```c
size_t sqb_wait_ready(sqb *b, long wait_ms, size_t *idx, size_t cap);
```

Waits until every request finished or `wait_ms` elapsed (0 = do not wait), then writes the indices of EVERY finished request, ascending, into idx (at most cap) and returns how many (spec/subreq_async.md, "Entrega con plazo").

Those results are valid through sqb_result.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `sqb *` |  |  |
| `wait_ms` | `long` |  |  |
| `idx` | `size_t *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `size_t`

---

<a id="sqb_remove"></a>

### `sqb_remove`

`function` | [include/subreq_batch.h:59](../../include/subreq_batch.h#L59)

```c
void sqb_remove(sqb *b, const size_t *idx, size_t k);
```

Joins and frees the jobs at the k ascending indices (unfinished or out-of-range ones are skipped); the others keep running and keep their relative order.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `sqb *` |  |  |
| `idx` | `size_t *` |  |  |
| `k` | `size_t` |  |  |

---

<a id="sqb_reset"></a>

### `sqb_reset`

`function` | [include/subreq_batch.h:61](../../include/subreq_batch.h#L61)

```c
void sqb_reset(sqb *b);
```

Joins (waits for) and frees every job and result; the batch is reusable.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `sqb *` |  |  |

---

<a id="sqb_free"></a>

### `sqb_free`

`function` | [include/subreq_batch.h:64](../../include/subreq_batch.h#L64)

```c
void sqb_free(sqb *b);
```

Abandons what is still running (sqb_abandon) and releases the batch; the memory goes when the last abandoned request ends.

Never waits.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `sqb *` |  |  |

---

## Macros

<a id="sqb_max_jobs"></a>

### `SQB_MAX_JOBS`

`macro` | [include/subreq_batch.h:14](../../include/subreq_batch.h#L14)

```c
#define SQB_MAX_JOBS
```

---
