/* libFuzzer harness for text_case (spec/text_case.md): case mapping and the
 * small-caps split run on page text. Invariants: a transform writes exactly n
 * bytes and never more, an ASCII byte only maps to ASCII, the runs cover the
 * text in order without gaps or overlap, and a split never loses a byte. */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "css.h"
#include "text_case.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 1 || size > 4096) return 0;
    int transform = (data[0] % 4 == 0) ? CSS_TT_UPPERCASE
                  : (data[0] % 4 == 1) ? CSS_TT_LOWERCASE
                  : (data[0] % 4 == 2) ? CSS_TT_CAPITALIZE : CSS_TT_NONE;
    const char *s = (const char *)data + 1;
    size_t n = size - 1;

    char *out = (char *)malloc(n + 1);
    if (out == NULL) return 0;
    out[n] = 0x5A;
    size_t w = tc_transform(s, n, transform, 1, out, n);
    if (w != n) abort();
    if (out[n] != 0x5A) abort();
    for (size_t i = 0; i < n; ++i)
        if (((unsigned char)s[i] < 0x80) != ((unsigned char)out[i] < 0x80)) abort();
    free(out);

    tc_run runs[8];
    size_t nr = tc_smallcaps_runs(s, n, runs, sizeof runs / sizeof runs[0]);
    if (n > 0 && nr == 0) abort();
    size_t at = 0;
    for (size_t k = 0; k < nr; ++k) {
        if (runs[k].off != at || runs[k].len == 0) abort();
        at += runs[k].len;
    }
    if (at != n) abort();
    return 0;
}
