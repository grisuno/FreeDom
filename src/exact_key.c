#include "exact_key.h"

#include <stdlib.h>
#include <string.h>

void ek_init(ek_key *k) {
    if (k == NULL) return;
    k->b = NULL;
    k->n = k->cap = 0;
    k->bad = 0;
}

void ek_reset(ek_key *k) {
    if (k == NULL) return;
    k->n = 0;
    k->bad = 0;
}

void ek_put(ek_key *k, const void *p, size_t len) {
    if (k == NULL || k->bad || len == 0) return;
    if (p == NULL || len > EK_MAX_BYTES || k->n > EK_MAX_BYTES - len) { k->bad = 1; return; }
    size_t need = k->n + len;
    if (need > k->cap) {
        size_t nc = (k->cap != 0) ? k->cap : 256;
        while (nc < need) nc *= 2;
        if (nc > EK_MAX_BYTES) nc = EK_MAX_BYTES;
        unsigned char *g = (unsigned char *)realloc(k->b, nc);
        if (g == NULL) { k->bad = 1; return; }
        k->b = g;
        k->cap = nc;
    }
    memcpy(k->b + k->n, p, len);
    k->n = need;
}

int ek_equal(const ek_key *a, const ek_key *b) {
    if (a == NULL || b == NULL || a->bad || b->bad || a->n != b->n) return 0;
    return a->n == 0 || memcmp(a->b, b->b, a->n) == 0;
}

void ek_swap(ek_key *a, ek_key *b) {
    if (a == NULL || b == NULL) return;
    ek_key t = *a;
    *a = *b;
    *b = t;
}

void ek_free(ek_key *k) {
    if (k == NULL) return;
    free(k->b);
    ek_init(k);
}
