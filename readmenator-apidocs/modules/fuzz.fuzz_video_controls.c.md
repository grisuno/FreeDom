# `fuzz/fuzz_video_controls.c`

> Source: [fuzz/fuzz_video_controls.c:1](../../fuzz/fuzz_video_controls.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_video_controls_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_video_controls_h__vcl_format_time["video_controls.vcl_format_time"]
    n_include_video_controls_h__vcl_layout["video_controls.vcl_layout"]
    n_include_video_controls_h__vcl_position["video_controls.vcl_position"]
    n_include_video_controls_h__vcl_total["video_controls.vcl_total"]
    n_src_box_style_c__take["box_style.take"]
    n_src_video_controls_c__vcl_hit["video_controls.vcl_hit"]
    n_src_video_controls_c__vcl_segment_at["video_controls.vcl_segment_at"]
    n_fuzz_fuzz_video_controls_c__LLVMFuzzerTestOneInput -.-> n_include_video_controls_h__vcl_format_time
    n_fuzz_fuzz_video_controls_c__LLVMFuzzerTestOneInput -.-> n_include_video_controls_h__vcl_layout
    n_fuzz_fuzz_video_controls_c__LLVMFuzzerTestOneInput -.-> n_include_video_controls_h__vcl_position
    n_fuzz_fuzz_video_controls_c__LLVMFuzzerTestOneInput -.-> n_include_video_controls_h__vcl_total
    n_fuzz_fuzz_video_controls_c__LLVMFuzzerTestOneInput -.-> n_src_box_style_c__take
    n_fuzz_fuzz_video_controls_c__LLVMFuzzerTestOneInput -.-> n_src_video_controls_c__vcl_hit
    n_fuzz_fuzz_video_controls_c__LLVMFuzzerTestOneInput -.-> n_src_video_controls_c__vcl_segment_at
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_video_controls.c:14](../../fuzz/fuzz_video_controls.c#L14)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`vcl_format_time`](include.video_controls.h.md#vcl_format_time), [`vcl_layout`](include.video_controls.h.md#vcl_layout), [`vcl_position`](include.video_controls.h.md#vcl_position), [`vcl_total`](include.video_controls.h.md#vcl_total), [`take`](src.box_style.c.md#take), [`vcl_hit`](src.video_controls.c.md#vcl_hit), [`vcl_segment_at`](src.video_controls.c.md#vcl_segment_at)

---
