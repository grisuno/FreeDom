/*
 * libFuzzer harness for image_decode (PNG + JPEG decode).
 *
 * Goal: arbitrary bytes through the full sniff + dimensions + decode + free
 * pipeline must never crash, leak, or trigger UB. This is the hostile-content
 * decoder that runs inside the confined tab worker, so its robustness is critical.
 * Both the format-specific decoders and the img_decode dispatcher (what the worker
 * actually calls) are driven; a JPEG magic prefix routes bytes into libjpeg with
 * the longjmp error manager, exercising its fail-closed path on corrupt streams.
 *
 * Build & run: make fuzz-img   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "image_decode.h"

#include <stddef.h>
#include <stdint.h>

/* Touch every claimed pixel corner so the sanitizer flags an out-of-bounds extent,
 * then release. Safe on a zeroed (failed-decode) struct. */
static void poke_and_free(img_pixels *px) {
    if (px->data != NULL && px->width > 0 && px->height > 0) {
        volatile uint8_t sink = px->data[0];
        size_t last = (size_t)(px->height - 1) * px->stride
                    + (size_t)(px->width - 1) * 4u + 3u;
        sink ^= px->data[last];
        (void)sink;
    }
    img_pixels_free(px);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    (void)img_sniff(data, size);

    uint32_t w = 0, h = 0;
    (void)img_png_dimensions(data, size, &w, &h);

    img_pixels px = {0, 0, 0, NULL};
    (void)img_decode_png(data, size, &px);
    poke_and_free(&px);
    (void)img_decode_jpeg(data, size, &px);
    poke_and_free(&px);
    /* The dispatcher the worker uses: sniff -> png/jpeg/format. */
    (void)img_decode(data, size, &px);
    poke_and_free(&px);
    return 0;
}
