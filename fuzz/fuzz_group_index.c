/* libFuzzer harness for group_index (spec/group_index.md): random keys (including
 * out-of-range ones) and key counts, checked against a naive per-key scan. */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "group_index.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 1) return 0;
    size_t nkeys = data[0] % 40;
    data++; size--;
    size_t n = size / 2;
    int *keys = calloc(n ? n : 1, sizeof *keys);
    size_t *items = calloc(n ? n : 1, sizeof *items);
    size_t *offs = calloc(nkeys + 1, sizeof *offs);
    if (keys == NULL || items == NULL || offs == NULL) abort();
    for (size_t i = 0; i < n; ++i) keys[i] = (int)(int16_t)(data[2 * i] | (data[2 * i + 1] << 8)) % 48;
    size_t m = gi_build(keys, n, nkeys, offs, items);
    if (m == (size_t)-1 || offs[0] != 0 || offs[nkeys] != m || m > n) abort();
    size_t expect = 0;
    for (size_t k = 0; k < nkeys; ++k) {
        if (offs[k + 1] < offs[k]) abort();
        size_t at = offs[k];
        for (size_t i = 0; i < n; ++i) {     /* the naive reference: scan for key k in order */
            if (keys[i] != (int)k) continue;
            if (at >= offs[k + 1] || items[at] != i) abort();
            ++at;
            ++expect;
        }
        if (at != offs[k + 1]) abort();
    }
    if (expect != m) abort();
    free(keys); free(items); free(offs);
    return 0;
}
