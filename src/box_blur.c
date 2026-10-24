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

int bb_ink_rect(const unsigned char *argb, int w, int h, int stride, double sigma, int rect[4]) {
    int sizes[3];
    if (argb == NULL || rect == NULL || w <= 0 || h <= 0 || stride < w * 4) return 0;
    if (!bb_box_sizes(sigma, sizes)) return 0;
    int x0 = w, y0 = h, x1 = -1, y1 = -1;
    for (int y = 0; y < h; ++y) {
        const unsigned char *row = argb + (size_t)y * (size_t)stride;
        int first = -1, last = -1;
        for (int x = 0; x < w; ++x)
            if (row[x * 4 + 3] != 0) { first = x; break; }
        if (first < 0) continue;
        for (int x = w - 1; x >= first; --x)
            if (row[x * 4 + 3] != 0) { last = x; break; }
        if (first < x0) x0 = first;
        if (last > x1) x1 = last;
        if (y < y0) y0 = y;
        y1 = y;
    }
    if (x1 < 0) return 0;
    int reach = sizes[0] / 2 + sizes[1] / 2 + sizes[2] / 2;
    rect[0] = (x0 - reach > 0) ? x0 - reach : 0;
    rect[1] = (y0 - reach > 0) ? y0 - reach : 0;
    rect[2] = (x1 + reach + 1 < w) ? x1 + reach + 1 : w;
    rect[3] = (y1 + reach + 1 < h) ? y1 + reach + 1 : h;
    return 1;
}
