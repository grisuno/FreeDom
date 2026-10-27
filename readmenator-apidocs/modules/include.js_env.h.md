# `include/js_env.h`

> Source: [include/js_env.h:1](../../include/js_env.h#L1) | language `h` | coverage 25.0% | [API index](../index.md)

## Contents

- **Enums:** [`je_status`](#je_status)
- **Functions:** [`poisoned`](#poisoned)
- **Macros:** [`JE_READBACK_EXACT`](#je_readback_exact)

## Enums

<a id="je_status"></a>

### `je_status`

`enum` | [include/js_env.h:27](../../include/js_env.h#L27)

```c
typedef enum je_status
```

---

## Functions

<a id="poisoned"></a>

### `poisoned`

`function` | [include/js_env.h:49](../../include/js_env.h#L49)

```c
* readback is poisoned (deterministic within an origin, unlinkable across * sessions and across origins) to defeat readback fingerprinting. readback_key * is the per-origin key the orchestrator derive
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `origin` | `deterministic within an` |  |  |
| `origins` | `unlinkable across * sessions and across` |  |  |

**Returns:** `* readback is`

---

## Macros

<a id="je_readback_exact"></a>

### `JE_READBACK_EXACT`

`macro` | [include/js_env.h:59](../../include/js_env.h#L59)

```c
#define JE_READBACK_EXACT
```

readback_key value meaning "do not perturb": canvas/audio readback returns the bytes as drawn.

For a trusted host only (allow.conf AND js.conf, owner decision 2026-10-26): a poisoned canvas is itself a bot signal (two readbacks that differ from a real browser's), so the host sees a coherent, deterministic canvas instead.

---
