/* libFuzzer harness for mask_cache (spec/mask_cache.md). The input is a script of put/get/
 * clear operations over a small key space (the geometry comes from page CSS, so it is hostile)
 * against a tight byte and entry budget. A shadow model remembers what every put wrote; every
 * hit must return the stride and the bytes of the LAST put of that key, and the budgets must
 * hold after every step. ASan/UBSan catch the memory side. */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "mask_cache.h"

#define KEYS 12

static mkc_key key_for(unsigned id, int w, int h) {
    mkc_key k = { w, h, (double)(id % 3), (double)(id % 5), (double)w, (double)h,
                  (double)(id & 1), 1.0 + (double)(id % 4), (int)(id % 2) };
    return k;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    const size_t budget = 4096, entries = 6;
    mkc_cache *c = mkc_new(budget, entries);
    if (c == NULL) return 0;
    struct { int live, stride, w, h; uint8_t tag; } model[KEYS];
    memset(model, 0, sizeof model);
    for (size_t i = 0; i + 3 < size; i += 4) {
        unsigned op = data[i] % 4, id = data[i + 1] % KEYS;
        int w = 1 + data[i + 2] % 40, h = 1 + data[i + 3] % 40;
        if (model[id].live) { w = model[id].w; h = model[id].h; }
        mkc_key k = key_for(id, w, h);
        if (op == 0 || op == 1) {
            int stride = w + (int)(data[i + 2] % 3);
            unsigned char *b = mkc_put(c, &k, stride);
            if (b != NULL) {
                for (int q = 0; q < stride * h; ++q)
                    if (b[q] != 0) abort();                  /* V-002: zeroed */
                memset(b, data[i] | 1, (size_t)stride * (size_t)h);
                model[id].live = 1; model[id].stride = stride;
                model[id].w = w; model[id].h = h; model[id].tag = data[i] | 1;
            } else if ((size_t)stride * (size_t)h <= budget) {
                abort();                                     /* fits the budget: must succeed */
            } else {
                model[id].live = 0;
            }
        } else if (op == 2) {
            int stride = 0;
            const unsigned char *g = mkc_get(c, &k, &stride);
            if (g != NULL) {
                if (!model[id].live || stride != model[id].stride) abort();
                for (int q = 0; q < stride * h; ++q)
                    if (g[q] != model[id].tag) abort();
            }
        } else {
            mkc_clear(c);
            memset(model, 0, sizeof model);
            if (mkc_count(c) != 0 || mkc_bytes(c) != 0) abort();
        }
        if (mkc_bytes(c) > budget || mkc_count(c) > entries) abort();
    }
    mkc_free(c);
    return 0;
}
