#include "box_blur.h"

#include <math.h>
#include <stdint.h>
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

/* floor((sum + bw/2) / bw) without a division: m = floor(2^32 / bw) + 1 makes (n * m) >> 32
 * exact for every n < 2^32 / bw (Granlund-Montgomery), and here n <= 256 * bw with bw <
 * BB_BOX_MAX, so 256 * bw^2 < 2^32 holds. The byte-for-byte test against the division keeps it
 * honest. */
#define BB_BOX_MAX 4096
static uint64_t box_recip(int bw) { return (UINT64_C(1) << 32) / (uint64_t)bw + 1u; }
static unsigned char box_avg(long sum, int bw, uint64_t m) {
    return (unsigned char)(((uint64_t)(sum + bw / 2) * m) >> 32);
}

/* One box pass of odd width bw over n samples spaced `step` apart, through tmp
 * (n bytes). Samples outside [0, n) are 0. Running sum, so O(n) per line. */
static void box_line(unsigned char *p, int n, int step, int bw, unsigned char *tmp) {
    int r = bw / 2;
    uint64_t m = box_recip(bw);
    long sum = 0;
    for (int i = 0; i < n; ++i) tmp[i] = p[(long)i * step];
    for (int i = 0; i <= r && i < n; ++i) sum += tmp[i];
    for (int i = 0; i < n; ++i) {
        p[(long)i * step] = box_avg(sum, bw, m);
        int add = i + r + 1, sub = i - r;
        if (add < n) sum += tmp[add];
        if (sub >= 0) sum -= tmp[sub];
    }
}

/* One box pass of odd width bw down every column at once: the same running sums as box_line
 * with step = stride, but walked row by row so every access is sequential (the column-at-a-time
 * walk touched one byte per cache line). src is an h x w copy of the rows; sum holds w longs. */
static void box_cols(unsigned char *buf, int w, int h, int stride, int bw,
                     unsigned char *src, long *sum) {
    int r = bw / 2;
    uint64_t m = box_recip(bw);
    for (int y = 0; y < h; ++y)
        memcpy(src + (size_t)y * (size_t)w, buf + (size_t)y * (size_t)stride, (size_t)w);
    memset(sum, 0, (size_t)w * sizeof *sum);
    for (int i = 0; i <= r && i < h; ++i) {
        const unsigned char *row = src + (size_t)i * (size_t)w;
        for (int x = 0; x < w; ++x) sum[x] += row[x];
    }
    for (int i = 0; i < h; ++i) {
        unsigned char *out = buf + (size_t)i * (size_t)stride;
        for (int x = 0; x < w; ++x) out[x] = box_avg(sum[x], bw, m);
        int add = i + r + 1, sub = i - r;
        if (add < h) {
            const unsigned char *row = src + (size_t)add * (size_t)w;
            for (int x = 0; x < w; ++x) sum[x] += row[x];
        }
        if (sub >= 0) {
            const unsigned char *row = src + (size_t)sub * (size_t)w;
            for (int x = 0; x < w; ++x) sum[x] -= row[x];
        }
    }
}

int bb_blur_a8(unsigned char *buf, int w, int h, int stride, double sigma) {
    if (buf == NULL || w <= 0 || h <= 0 || stride < w) return -1;
    if ((long long)w * (long long)h > (long long)BB_MAX_PIXELS) return -1;
    int sizes[3];
    if (!bb_box_sizes(sigma, sizes)) return 0;
    for (int k = 0; k < 3; ++k)
        if (sizes[k] >= BB_BOX_MAX) return -1;
    unsigned char *tmp = (unsigned char *)calloc((size_t)w * (size_t)h, 1);
    long *sum = (long *)calloc((size_t)w, sizeof *sum);
    if (tmp == NULL || sum == NULL) { free(tmp); free(sum); return -1; }
    for (int k = 0; k < 3; ++k) {
        if (sizes[k] <= 1) continue;   /* a width-1 box is the identity */
        for (int y = 0; y < h; ++y) box_line(buf + (long)y * stride, w, 1, sizes[k], tmp);
        box_cols(buf, w, h, stride, sizes[k], tmp, sum);
    }
    free(tmp);
    free(sum);
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
