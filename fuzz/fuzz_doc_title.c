/* Fuzzer for doc_title (spec/doc_title.md): the title is always valid UTF-8, bounded by
 * cap, free of C0/DEL/C1 controls and bidi overrides, untrimmed of nothing, and the scan
 * never reads past len (ASan on an exact-size copy). */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "doc_title.h"

static uint32_t next_cp(const unsigned char *s, size_t n, size_t *k) {
    unsigned c = s[0];
    if (c < 0x80u) { *k = 1; return c; }
    size_t m = (c >= 0xF0u) ? 4 : (c >= 0xE0u) ? 3 : (c >= 0xC2u) ? 2 : 0;
    if (m == 0 || m > n) abort();
    uint32_t v = c & (0x7Fu >> m);
    for (size_t i = 1; i < m; ++i) {
        if ((s[i] & 0xC0u) != 0x80u) abort();
        v = (v << 6) | (s[i] & 0x3Fu);
    }
    static const uint32_t min[5] = { 0, 0, 0x80u, 0x800u, 0x10000u };
    if (v < min[m] || v > 0x10FFFFu || (v >= 0xD800u && v <= 0xDFFFu)) abort();
    *k = m;
    return v;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 1) return 0;
    size_t cap = (size_t)data[0] % 64u + 1u;
    char *buf = malloc(size - 1 ? size - 1 : 1);
    if (buf == NULL) return 0;
    memcpy(buf, data + 1, size - 1);
    char *out = malloc(cap);
    if (out == NULL) { free(buf); return 0; }
    int r = dt_scan(buf, size - 1, out, cap);
    size_t n = 0;
    while (n < cap && out[n] != '\0') ++n;
    if (n >= cap) abort();
    if (r != (n > 0)) abort();
    if (n > 0 && (out[0] == ' ' || out[n - 1] == ' ')) abort();
    for (size_t i = 0; i < n; ) {
        size_t k;
        uint32_t cp = next_cp((const unsigned char *)out + i, n - i, &k);
        if (cp < 0x20u || cp == 0x7Fu || (cp >= 0x80u && cp <= 0x9Fu)) abort();
        if ((cp >= 0x202Au && cp <= 0x202Eu) || (cp >= 0x2066u && cp <= 0x2069u) ||
            cp == 0x200Eu || cp == 0x200Fu) abort();
        if (cp == ' ' && i + 1 < n && out[i + 1] == ' ') abort();
        i += k;
    }
    free(out);
    free(buf);
    return 0;
}
