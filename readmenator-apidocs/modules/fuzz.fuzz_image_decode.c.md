# `fuzz/fuzz_image_decode.c`

> Source: [fuzz/fuzz_image_decode.c:1](../../fuzz/fuzz_image_decode.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`LLVMFuzzerTestOneInput`](#llvmfuzzertestoneinput)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_fuzz_fuzz_image_decode_c__LLVMFuzzerTestOneInput(["LLVMFuzzerTestOneInput"])
    n_include_svg_raster_h__sr_sniff["svg_raster.sr_sniff"]
    n_src_image_decode_c__img_decode["image_decode.img_decode"]
    n_src_image_decode_c__img_decode_jpeg["image_decode.img_decode_jpeg"]
    n_src_image_decode_c__img_decode_png["image_decode.img_decode_png"]
    n_src_image_decode_c__img_png_dimensions["image_decode.img_png_dimensions"]
    n_src_svg_raster_c__sr_rasterize["svg_raster.sr_rasterize"]
    n_fuzz_fuzz_image_decode_c__LLVMFuzzerTestOneInput -.-> n_include_svg_raster_h__sr_sniff
    n_fuzz_fuzz_image_decode_c__LLVMFuzzerTestOneInput -.-> n_src_image_decode_c__img_decode
    n_fuzz_fuzz_image_decode_c__LLVMFuzzerTestOneInput -.-> n_src_image_decode_c__img_decode_jpeg
    n_fuzz_fuzz_image_decode_c__LLVMFuzzerTestOneInput -.-> n_src_image_decode_c__img_decode_png
    n_fuzz_fuzz_image_decode_c__LLVMFuzzerTestOneInput -.-> n_src_image_decode_c__img_png_dimensions
    n_fuzz_fuzz_image_decode_c__LLVMFuzzerTestOneInput -.-> n_src_svg_raster_c__sr_rasterize
```

## Functions

<a id="llvmfuzzertestoneinput"></a>

### `LLVMFuzzerTestOneInput`

`function` | [fuzz/fuzz_image_decode.c:33](../../fuzz/fuzz_image_decode.c#L33)

```c
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`sr_sniff`](include.svg_raster.h.md#sr_sniff), [`img_decode`](src.image_decode.c.md#img_decode), [`img_decode_jpeg`](src.image_decode.c.md#img_decode_jpeg), [`img_decode_png`](src.image_decode.c.md#img_decode_png), [`img_png_dimensions`](src.image_decode.c.md#img_png_dimensions), [`sr_rasterize`](src.svg_raster.c.md#sr_rasterize)

---
