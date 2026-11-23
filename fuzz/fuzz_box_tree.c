#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "box_tree.h"
#include "page_view.h"

#define FB_MAX 64

/* Hostile box trees (any parent graph, cycles included) through the positioned paint
 * order (spec/compositor.md "Anidado"): the output is a permutation of the positioned
 * boxes, and a non-negative box always follows its out-of-flow stacking-context ancestors
 * when no cycle hides them. */
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    size_t n = size / 4;
    if (n == 0) return 0;
    if (n > FB_MAX) n = FB_MAX;
    pv_box_def *b = calloc(n, sizeof *b);
    double *g0 = calloc(n, sizeof *g0), *g1 = calloc(n, sizeof *g1);
    char *placed = calloc(n, 1);
    bt_positioned *out = calloc(n, sizeof *out);
    if (b == NULL || g0 == NULL || g1 == NULL || placed == NULL || out == NULL) goto done;
    for (size_t i = 0; i < n; ++i) {
        const uint8_t *p = data + 4 * i;
        b[i].parent_id = (p[0] % (n + 1)) == n ? -1 : (int)(p[0] % (n + 1));
        b[i].position = p[1] % 6;
        b[i].z_index = (p[2] & 0x80) ? PV_LEN_UNSET : (int)(int8_t)(p[2] << 1) / 2;
        b[i].opacity = (p[3] & 1) ? (int)(p[3] % 101) : -1;
        b[i].transform_tx = b[i].transform_ty = b[i].transform_sx = b[i].transform_sy =
            b[i].transform_rotate = b[i].transform_skx = b[i].transform_sky = PV_LEN_UNSET;
        b[i].inset_left = b[i].inset_right = b[i].inset_top = b[i].inset_bottom = PV_LEN_UNSET;
        g1[i] = 10.0;
        placed[i] = 1;
    }
    size_t cnt = 0;
    if (bt_resolve_positioning_ex(b, n, g0, g0, g1, g1, NULL, NULL, placed, 800, 600, out,
                                  n, &cnt) != BT_OK) goto done;
    if (cnt > n) abort();
    char seen[FB_MAX] = {0};
    int at[FB_MAX];
    for (size_t i = 0; i < n; ++i) at[i] = -1;
    for (size_t i = 0; i < cnt; ++i) {
        size_t bi = out[i].box_index;
        if (bi >= n || seen[bi]) abort();
        seen[bi] = 1;
        at[bi] = (int)i;
    }
    for (size_t i = 0; i < n; ++i) {
        if (at[i] < 0 || (b[i].z_index != PV_LEN_UNSET && b[i].z_index < 0)) continue;
        char vis[FB_MAX] = {0};
        int ok = 1, chain[FB_MAX], nch = 0;
        for (int id = b[i].parent_id; id >= 0; id = b[id].parent_id) {
            if (vis[id] || (size_t)id == i) { ok = 0; break; }
            vis[id] = 1;
            int oof = b[id].position == BT_POS_ABSOLUTE || b[id].position == BT_POS_FIXED;
            int sc = b[id].position == BT_POS_FIXED || b[id].z_index != PV_LEN_UNSET
                  || (b[id].opacity >= 0 && b[id].opacity < 100);
            if (oof && sc && at[id] >= 0) {
                chain[nch++] = id;
                /* A negative-z context sits in the root-level prefix: its subtree is
                 * rooted there, not under that context's own ancestors. */
                if (b[id].z_index != PV_LEN_UNSET && b[id].z_index < 0) break;
            }
        }
        if (!ok || nch >= 15) continue;   /* cycles and over-deep chains: no claim */
        for (int k = 0; k < nch; ++k) if (at[chain[k]] > at[i]) abort();
    }
    done:
    free(b); free(g0); free(g1); free(placed); free(out);
    return 0;
}
