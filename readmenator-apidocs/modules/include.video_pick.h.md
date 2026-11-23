# `include/video_pick.h`

> Source: [include/video_pick.h:1](../../include/video_pick.h#L1) | language `h` | coverage 100.0% | [API index](../index.md)

Which video a click plays (spec/video_pick.md).

Pure, no I/O; the returned pointers alias the views and stay valid while they live.

## Contents

- **Functions:** [`vpk_playable`](#vpk_playable), [`vpk_first_video`](#vpk_first_video), [`vpk_for_frame`](#vpk_for_frame)

## Functions

<a id="vpk_playable"></a>

### `vpk_playable`

`function` | [include/video_pick.h:15](../../include/video_pick.h#L15)

```c
int vpk_playable(const char *src);
```

1 when src is an absolute http(s) URL with something after the scheme (the only kind the decoder can fetch); 0 for NULL, "[object Object]", blob:, javascript:...

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `src` | `char *` |  |  |

**Returns:** `int`

*Called by:* [`vpk_first_video`](src.video_pick.c.md#vpk_first_video), [`vpk_for_frame`](src.video_pick.c.md#vpk_for_frame)

---

<a id="vpk_first_video"></a>

### `vpk_first_video`

`function` `const` | [include/video_pick.h:18](../../include/video_pick.h#L18)

```c
const char *vpk_first_video(const pv_view *v);
```

src of the first playable PV_VIDEO run or NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `pv_view *` |  |  |

**Returns:** `char *`

---

<a id="vpk_for_frame"></a>

### `vpk_for_frame`

`function` `const` | [include/video_pick.h:23](../../include/video_pick.h#L23)

```c
const char *vpk_for_frame(const pv_view *frame_view, const char *top_video);
```

Video for a click on a live frame's box: the frame's own first video, else top_video (the top document's first video, extracted by the worker's iframe scan; NULL or "" when none), else NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `frame_view` | `pv_view *` |  |  |
| `top_video` | `char *` |  |  |

**Returns:** `char *`

---
