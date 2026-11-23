/* group_index (gi_) -- spec/group_index.md. */
#include "group_index.h"

#include <stdint.h>

static int key_ok(int k, size_t nkeys) {
    return k >= 0 && (size_t)k < nkeys;
}

size_t gi_build(const int *keys, size_t n, size_t nkeys, size_t *offs, size_t *items) {
    if (offs == NULL || nkeys == SIZE_MAX) return (size_t)-1;
    if (n > 0 && (keys == NULL || items == NULL)) return (size_t)-1;
    /* Counting sort: offs[k + 1] counts group k, the prefix sum turns counts into starts,
     * and the placement pass walks items in index order (stable). */
    for (size_t k = 0; k <= nkeys; ++k) offs[k] = 0;
    for (size_t i = 0; i < n; ++i)
        if (key_ok(keys[i], nkeys)) offs[(size_t)keys[i] + 1]++;
    for (size_t k = 0; k < nkeys; ++k) offs[k + 1] += offs[k];
    /* offs[k] doubles as group k's write cursor, then is shifted back below. */
    for (size_t i = 0; i < n; ++i)
        if (key_ok(keys[i], nkeys)) items[offs[keys[i]]++] = i;
    for (size_t k = nkeys; k > 0; --k) offs[k] = offs[k - 1];
    offs[0] = 0;
    return offs[nkeys];
}
