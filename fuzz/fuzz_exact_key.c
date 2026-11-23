/* libFuzzer harness for exact_key (spec/exact_key.md). The input is split into two key
 * streams, each fed through ek_put in fuzz-chosen chunk sizes; ek_equal must answer exactly
 * memcmp of the two concatenations (the partition never matters), and a swap must exchange
 * the answer's operands. Page state builds these keys every frame, so it is hostile input. */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "exact_key.h"

static void feed(ek_key *k, const uint8_t *p, size_t n, const uint8_t *cuts, size_t ncuts) {
    size_t off = 0, c = 0;
    while (off < n) {
        size_t step = (ncuts > 0) ? 1 + cuts[c++ % ncuts] % 17 : n;
        if (step > n - off) step = n - off;
        ek_put(k, p + off, step);
        off += step;
    }
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 2) return 0;
    size_t split = data[0] % size, ncut = data[1] % 8;
    const uint8_t *body = data + 2;
    size_t n = size - 2;
    if (split > n) split = n;
    if (ncut > n) ncut = n;
    const uint8_t *a = body, *b = body + split;
    size_t na = split, nb = n - split;
    ek_key ka, kb;
    ek_init(&ka);
    ek_init(&kb);
    feed(&ka, a, na, body, ncut);
    feed(&kb, b, nb, body + (n - ncut), ncut);
    int want = (na == nb) && (na == 0 || memcmp(a, b, na) == 0);
    if (ek_equal(&ka, &kb) != want) abort();
    if (ka.n != na || kb.n != nb) abort();
    ek_swap(&ka, &kb);
    if (ka.n != nb || ek_equal(&kb, &ka) != want) abort();
    ek_reset(&ka);
    if (ka.n != 0 || ka.bad) abort();
    ek_free(&ka);
    ek_free(&kb);
    ek_free(&kb);
    return 0;
}
