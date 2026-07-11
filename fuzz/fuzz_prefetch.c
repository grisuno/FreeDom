/* libFuzzer harness for the prefetch lookahead scanner (Hito 29). The scanned
 * HTML is hostile remote content read on the TRUSTED side: arbitrary bytes must
 * never crash/leak/UB, the ref cap must hold, and no I/O may ever happen. */

#include <stddef.h>
#include <stdint.h>

#include "prefetch.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    pf_list l;
    if (pf_scan((const char *)data, size, &l) == 0) {
        if (l.count > PF_MAX_REFS) __builtin_trap();
        pf_list_free(&l);
    }
    return 0;
}
