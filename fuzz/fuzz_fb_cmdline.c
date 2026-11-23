#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "fb_cmdline.h"
int LLVMFuzzerTestOneInput(const uint8_t *d, size_t n) {
    if (n < 2) return 0;
    size_t cut = d[0] % n; char *t = (char *)malloc(n); memcpy(t, d + 1, n - 1); t[n - 1] = '\0';
    size_t tn = n - 1; if (cut > tn) cut = tn;
    char base[FBC_BASE_MAX]; size_t off = 0;
    long pl = fbc_complete_split(t, cut, base, sizeof base, &off);
    char ins[256], list[1024], ex[2048]; size_t cnt;
    if (pl >= 0 && off + (size_t)pl <= cut) fbc_complete_pick(t, t + off, (size_t)pl, ins, sizeof ins, list, sizeof list, &cnt);
    fbc_complete_pick(t, "a", 1, ins, sizeof ins, list, sizeof list, &cnt);
    fbc_names_expr(t, ex, sizeof ex);
    fbc_history h; fbc_history_init(&h); fbc_history_push(&h, t, tn); fbc_history_prev(&h, t, tn); fbc_history_next(&h); fbc_history_free(&h);
    free(t); return 0;
}
