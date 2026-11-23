#ifndef FREEDOM_GROUP_INDEX_H
#define FREEDOM_GROUP_INDEX_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * group_index (gi_) -- stable group-by of n items by an integer key, in CSR form, so a
 * per-group pass visits only its own items in their original order. Pure, no allocation,
 * O(n + nkeys). Contract: spec/group_index.md.
 */

#include <stddef.h>

/* Groups item i under keys[i] when 0 <= keys[i] < nkeys (other keys are left out).
 * Writes offs[0..nkeys] and items[0..m); group k is items[offs[k] .. offs[k+1]) in
 * increasing index order. Returns m, or (size_t)-1 on invalid arguments (nothing written
 * to items; offs untouched when NULL). */
size_t gi_build(const int *keys, size_t n, size_t nkeys, size_t *offs, size_t *items);

#endif
