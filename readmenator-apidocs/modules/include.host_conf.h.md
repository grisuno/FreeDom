# `include/host_conf.h`

> Source: [include/host_conf.h:1](../../include/host_conf.h#L1) | language `h` | coverage 55.6% | [API index](../index.md)

## Contents

- **Structs:** [`hcf_dirs`](#hcf_dirs)
- **Functions:** [`hcf_search_dirs`](#hcf_search_dirs), [`hcf_search_dirs_from_env`](#hcf_search_dirs_from_env), [`hcf_load_filter`](#hcf_load_filter), [`hcf_load_allowlist`](#hcf_load_allowlist)
- **Macros:** [`HCF_MAX_DIRS`](#hcf_max_dirs), [`HCF_PATH_MAX`](#hcf_path_max), [`HCF_MAX_FILE_BYTES`](#hcf_max_file_bytes)

## Structs

<a id="hcf_dirs"></a>

### `hcf_dirs`

`struct` | [include/host_conf.h:20](../../include/host_conf.h#L20)

```c
typedef struct hcf_dirs
```

---

## Functions

<a id="hcf_search_dirs"></a>

### `hcf_search_dirs`

`function` | [include/host_conf.h:28](../../include/host_conf.h#L28)

```c
void hcf_search_dirs(const char *env, const char *home, hcf_dirs *out);
```

Pure.

Fills out with, in order: env (when non-empty), home + "/.config/freedom" (when home is non-empty), and "config". A directory already present is not added twice. out == NULL is a no-op.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `env` | `char *` |  |  |
| `home` | `char *` |  |  |
| `out` | `hcf_dirs *` |  |  |

---

<a id="hcf_search_dirs_from_env"></a>

### `hcf_search_dirs_from_env`

`function` | [include/host_conf.h:31](../../include/host_conf.h#L31)

```c
void hcf_search_dirs_from_env(hcf_dirs *out);
```

hcf_search_dirs over $FREEDOM_HOSTS_DIR and $HOME.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `out` | `hcf_dirs *` |  |  |

---

<a id="hcf_load_filter"></a>

### `hcf_load_filter`

`function` | [include/host_conf.h:35](../../include/host_conf.h#L35)

```c
hb_set *hcf_load_filter(const hcf_dirs *dirs);
```

block.conf (BLOCK) + allow.conf (ALLOW) from every directory, cumulative.

Missing or unreadable files fail open. NULL only on OOM or dirs == NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dirs` | `hcf_dirs *` |  |  |

**Returns:** `hb_set *`

---

<a id="hcf_load_allowlist"></a>

### `hcf_load_allowlist`

`function` | [include/host_conf.h:39](../../include/host_conf.h#L39)

```c
hb_set *hcf_load_allowlist(const hcf_dirs *dirs, const char *fname);
```

One file (js.conf, allow.conf, ...) from every directory as an ALLOW list.

NULL only on OOM or a NULL argument.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dirs` | `hcf_dirs *` |  |  |
| `fname` | `char *` |  |  |

**Returns:** `hb_set *`

---

## Macros

<a id="hcf_max_dirs"></a>

### `HCF_MAX_DIRS`

`macro` | [include/host_conf.h:15](../../include/host_conf.h#L15)

```c
#define HCF_MAX_DIRS
```

---

<a id="hcf_path_max"></a>

### `HCF_PATH_MAX`

`macro` | [include/host_conf.h:16](../../include/host_conf.h#L16)

```c
#define HCF_PATH_MAX
```

---

<a id="hcf_max_file_bytes"></a>

### `HCF_MAX_FILE_BYTES`

`macro` | [include/host_conf.h:18](../../include/host_conf.h#L18)

```c
#define HCF_MAX_FILE_BYTES
```

A list file larger than this is ignored whole (never truncated mid-line).

---
