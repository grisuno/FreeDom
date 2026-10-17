#include "box_blur.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

int bb_box_sizes(double sigma, int sizes[3]) {
    if (sizes == NULL || !isfinite(sigma) || !(sigma > 0.0)) return 0;
    /* Three successive boxes whose variances add up to sigma^2 (a box of odd
     * width w has variance (w^2 - 1) / 12): the ideal common width, rounded down
     * to an odd wl and up to wu = wl + 2, mixed so the sum lands on sigma^2. */
    double wideal = sqrt(12.0 * sigma * sigma / 3.0 + 1.0);
    int wl = (int)floor(wideal);
    if (wl % 2 == 0) --wl;
    if (wl < 1) wl = 1;
    int wu = wl + 2;
    double mideal = (12.0 * sigma * sigma - 3.0 * wl * wl - 12.0 * wl - 9.0)
                  / (-4.0 * wl - 4.0);
    int m = (int)lround(mideal);
    if (m < 0) m = 0;
    if (m > 3) m = 3;
    for (int k = 0; k < 3; ++k) sizes[k] = (k < m) ? wl : wu;
    return 1;
}

/* One box pass of odd width bw over n samples spaced `step` apart, through tmp
 * (n bytes). Samples outside [0, n) are 0. Running sum, so O(n) per line. */
static void box_line(unsigned char *p, int n, int step, int bw, unsigned char *tmp) {
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

int bb_blur_a8(unsigned char *buf, int w, int h, int stride, double sigma) {
    if (buf == NULL || w <= 0 || h <= 0 || stride < w) return -1;
    if ((long long)w * (long long)h > (long long)BB_MAX_PIXELS) return -1;
    int sizes[3];
    if (!bb_box_sizes(sigma, sizes)) return 0;
    int longest = (w > h) ? w : h;
    unsigned char *tmp = (unsigned char *)calloc((size_t)longest, 1);
    if (tmp == NULL) return -1;
    for (int k = 0; k < 3; ++k) {
        for (int y = 0; y < h; ++y) box_line(buf + (long)y * stride, w, 1, sizes[k], tmp);
        for (int x = 0; x < w; ++x) box_line(buf + x, h, stride, sizes[k], tmp);
    }
    free(tmp);
    return 1;
}
