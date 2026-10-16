/* libFuzzer harness for the prefetch lookahead scanner (Hito 29). The scanned
 * HTML is hostile remote content read on the TRUSTED side: arbitrary bytes must
 * never crash/leak/UB, the ref cap must hold, and no I/O may ever happen. */

#include <stddef.h>
#include <stdint.h>

#include "prefetch.h"

#include <string.h>

static char g_specs[PF_MAX_IMPORTS][PF_SPEC_MAX];

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    pf_list l;
    if (pf_scan((const char *)data, size, &l) == 0) {
        if (l.count > PF_MAX_REFS) __builtin_trap();
        pf_list_free(&l);
    }
    /* The same bytes as a hostile ES module body (spec/prefetch.md section 8):
     * bounded output, NUL-terminated specifiers, no read past the input. */
    size_t n = pf_scan_imports((const char *)data, size, g_specs, PF_MAX_IMPORTS);
    if (n > PF_MAX_IMPORTS) __builtin_trap();
    for (size_t k = 0; k < n; ++k)
        if (memchr(g_specs[k], '\0', PF_SPEC_MAX) == NULL) __builtin_trap();
    size_t st = 0, mn = 0;
    if (pf_find_importmap((const char *)data, size, &st, &mn) && (st > size || mn > size - st))
        __builtin_trap();
    return 0;
}
