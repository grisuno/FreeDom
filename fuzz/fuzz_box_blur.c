/* libFuzzer harness for box_blur (spec/box_blur.md): a hostile mask, size, stride and sigma
 * (the radius comes from page CSS). Differential: bb_blur_a8 must equal, byte for byte, the
 * pre-tanda-95 implementation kept below (division per pixel, column-at-a-time), and never
 * write past w in a row. */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "box_blur.h"

static void ref_line(unsigned char *p, int n, int step, int bw, unsigned char *tmp) {
    int r = bw / 2;
    long sum = 0;
    for (int i = 0; i < n; ++i) tmp[i] = p[(long)i * step];
    for (int i = 0; i <= r && i < n; ++i) sum += tmp[i];
    for (int i = 0; i < n; ++i) {
        p[(long)i * step] = (unsigned char)((sum + bw / 2) / bw);
        int add = i + r + 1, sub = i - r;
        if (add < n) sum += tmp[add];
        if (sub >= 0) sum -= tmp[sub];
    }
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 5) return 0;
    int w = 1 + data[0] % 64, h = 1 + data[1] % 64, pad = data[2] % 5;
    double sigma = (double)(data[3] | (data[4] << 8)) / 64.0;   /* 0 .. ~1024 */
    int stride = w + pad;
    size_t n = (size_t)stride * (size_t)h;
    unsigned char *a = calloc(n, 1), *b = calloc(n, 1);
    if (a == NULL || b == NULL) { free(a); free(b); return 0; }
    for (size_t i = 0; i < n && 5 + i < size; ++i) a[i] = data[5 + i];
    for (int y = 0; y < h; ++y) memset(a + (size_t)y * stride + w, 0xa5, (size_t)pad);
    memcpy(b, a, n);
    int r = bb_blur_a8(a, w, h, stride, sigma);
    int sizes[3];
    if (r == 1 && bb_box_sizes(sigma, sizes)) {
        int longest = (w > h) ? w : h;
        unsigned char *tmp = calloc((size_t)longest, 1);
        if (tmp != NULL) {
            for (int k = 0; k < 3; ++k) {
                for (int y = 0; y < h; ++y) ref_line(b + (long)y * stride, w, 1, sizes[k], tmp);
                for (int x = 0; x < w; ++x) ref_line(b + x, h, stride, sizes[k], tmp);
            }
            free(tmp);
            if (memcmp(a, b, n) != 0) abort();
        }
    } else if (r != 1 && memcmp(a, b, n) != 0) {
        abort();                                  /* refused or no-op: buffer untouched */
    }
    for (int y = 0; y < h; ++y)
        for (int x = w; x < stride; ++x)
            if (a[(size_t)y * stride + x] != 0xa5) abort();
    free(a);
    free(b);
    return 0;
}
