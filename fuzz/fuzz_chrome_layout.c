/* libFuzzer harness for chrome_layout (spec/chrome_layout.md): a hostile URL (a page
 * or a redirect chooses it) and hostile geometry. Invariants: the identity parser never
 * reads past the NUL and never answers the only "green" badge (PQ) unless the transport
 * is known, the URL is https, nothing was downgraded and verification is on; layout
 * rectangles are finite and non-negative and every hit lands on a part that exists. */
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "chrome_layout.h"

static double take_double(const uint8_t **p, size_t *n) {
    double d = 0.0;
    if (*n >= sizeof d) {
        memcpy(&d, *p, sizeof d);
        *p += sizeof d;
        *n -= sizeof d;
    }
    return d;
}

static void check_rect(chl_rect r) {
    if (!isfinite(r.x) || !isfinite(r.y) || !isfinite(r.w) || !isfinite(r.h)) abort();
    if (r.w < 0.0 || r.h < 0.0) abort();
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 4 || size > 4096) return 0;
    int known = data[0] & 1, insecure = (data[0] >> 1) & 1;
    int downgrade = (int)(int8_t)data[1];
    int tabs = data[2] % 40;
    int active = (int)data[3] - 8;
    const uint8_t *p = data + 4;
    size_t n = size - 4;

    double width = take_double(&p, &n);
    double hx = take_double(&p, &n), hy = take_double(&p, &n);
    chl_layout l;
    if (chl_compute(width, tabs & 1, tabs, active, &l) == CHL_OK) {
        if (tabs < 1 || active < 0 || active >= tabs) abort();
        const chl_rect rs[] = { l.new_tab, l.win_min, l.win_max, l.win_close, l.back, l.fwd,
                                l.reload, l.url, l.identity, l.menu };
        for (size_t i = 0; i < sizeof rs / sizeof rs[0]; ++i) check_rect(rs[i]);
        for (int i = 0; i < tabs; ++i) {
            chl_rect t;
            if (chl_tab_rect(&l, i, &t)) check_rect(t);
        }
        chl_rect t;
        if (active < l.tab_first || (l.tabs_visible > 0 && !chl_tab_rect(&l, active, &t))) abort();
        int ti = -2;
        chl_part part = chl_hit(&l, hx, hy, &ti);
        if ((part == CHL_PART_TAB || part == CHL_PART_TAB_CLOSE) != (ti >= 0)) abort();
        if (ti >= 0 && !chl_tab_rect(&l, ti, NULL)) abort();
        /* Hidden-tab indicators: exact counts, live only when they hide something. */
        check_rect(l.more_left);
        check_rect(l.more_right);
        if (l.hidden_left != l.tab_first || l.hidden_left < 0 || l.hidden_right < 0
            || l.hidden_left + l.tabs_visible + l.hidden_right != tabs) abort();
        if (part == CHL_PART_TABS_LEFT && l.hidden_left == 0) abort();
        if (part == CHL_PART_TABS_RIGHT && l.hidden_right == 0) abort();
        /* A drop lands on a visible tab; a move is a permutation. */
        int d = chl_tab_drop_index(&l, hx);
        if (l.tabs_visible > 0 ? (d < l.tab_first || d >= l.tab_first + l.tabs_visible) : d != -1)
            abort();
        if (tabs > 0) {
            int from = (int)((unsigned)data[1] % (unsigned)tabs), to = (d >= 0) ? d : 0;
            unsigned char seen[40] = { 0 };
            for (int i = 0; i < tabs; ++i) {
                int j = chl_move_index(i, from, to);
                if (j < 0 || j >= tabs || seen[j]) abort();
                seen[j] = 1;
            }
        }
    }

    chl_findbar fb;
    if (chl_findbar_compute(width, hy, &fb) != CHL_OK) abort();
    {
        const chl_rect fr[] = { fb.field, fb.prev, fb.next, fb.count, fb.close };
        check_rect(fb.bar);
        for (size_t i = 0; i < 5; ++i) {
            check_rect(fr[i]);
            if (fr[i].w > 0.0 && (fr[i].x < fb.bar.x || fr[i].x + fr[i].w > fb.bar.x + fb.bar.w + 1e-6))
                abort();
            for (size_t j = i + 1; j < 5; ++j)
                if (fr[i].w > 0.0 && fr[j].w > 0.0 && fr[i].x < fr[j].x + fr[j].w
                    && fr[j].x < fr[i].x + fr[i].w && fr[i].y < fr[j].y + fr[j].h
                    && fr[j].y < fr[i].y + fr[i].h) abort();
        }
        chl_find_part fp = chl_findbar_hit(&fb, hx, hy);
        if ((fp != CHL_FIND_NONE) != chl_rect_has(fb.bar, hx, hy)) abort();
    }

    char *url = (char *)malloc(n + 1);
    if (url == NULL) return 0;
    if (n != 0) memcpy(url, p, n);
    url[n] = '\0';
    chl_identity id = chl_identity_of(url, known, downgrade, insecure);
    if (id == CHL_ID_PQ) {
        if (!known || insecure || downgrade != CHL_DG_NONE) abort();
        if (strncasecmp(url, "https://", 8) != 0) abort();
    }
    if (chl_identity_label(id) == NULL) abort();
    free(url);
    return 0;
}
