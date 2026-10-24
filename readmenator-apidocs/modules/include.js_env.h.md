# `include/js_env.h`

> Source: [include/js_env.h:1](../../include/js_env.h#L1) | language `h` | coverage 0.0% | [API index](../index.md)

## Contents

- **Enums:** [`je_status`](#je_status)
- **Functions:** [`poisoned`](#poisoned)

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
