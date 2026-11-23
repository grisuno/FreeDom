# `src/video_pick.c`

> Source: [src/video_pick.c:1](../../src/video_pick.c#L1) | language `c` | coverage 100.0% | [API index](../index.md)

Only an absolute http(s) URL names a stream the decoder can fetch; anything else a script stored in src ("[object Object]", blob:, javascript:) is not a video.

## Contents

- **Functions:** [`vpk_first_video`](#vpk_first_video), [`vpk_for_frame`](#vpk_for_frame)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_video_pick_c__vpk_for_frame(["vpk_for_frame"])
    n_src_video_pick_c__vpk_first_video(["vpk_first_video"])
    n_include_video_pick_h__vpk_playable["video_pick.vpk_playable"]
    n_src_video_pick_c__vpk_for_frame --> n_src_video_pick_c__vpk_first_video
    n_src_video_pick_c__vpk_first_video -.-> n_include_video_pick_h__vpk_playable
    n_src_video_pick_c__vpk_for_frame -.-> n_include_video_pick_h__vpk_playable
```

## Functions

<a id="vpk_first_video"></a>

### `vpk_first_video`

`function` `const` | [src/video_pick.c:15](../../src/video_pick.c#L15)

```c
const char *vpk_first_video(const pv_view *v)
```

src of the first playable PV_VIDEO run or NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `pv_view *` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`vpk_first_video`](#vpk_first_video) (include/video_pick.h:18).

*Calls:* [`vpk_playable`](include.video_pick.h.md#vpk_playable)

*Called by:* [`vpk_for_frame`](#vpk_for_frame)

---

<a id="vpk_for_frame"></a>

### `vpk_for_frame`

`function` `const` | [src/video_pick.c:26](../../src/video_pick.c#L26)

```c
const char *vpk_for_frame(const pv_view *frame_view, const char *top_video)
```

Video for a click on a live frame's box: the frame's own first video, else top_video (the top document's first video, extracted by the worker's iframe scan; NULL or "" when none), else NULL.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `frame_view` | `pv_view *` |  |  |
| `top_video` | `char *` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`vpk_for_frame`](#vpk_for_frame) (include/video_pick.h:23).

*Calls:* [`vpk_playable`](include.video_pick.h.md#vpk_playable), [`vpk_first_video`](#vpk_first_video)

---
