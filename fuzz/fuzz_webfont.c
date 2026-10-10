/* libFuzzer harness for the webfont lookahead scanner (spec/webfont.md). The
 * scanned CSS is hostile remote content read on the TRUSTED side: arbitrary
 * bytes must never crash/leak/UB, the ref cap must hold, and no I/O may ever
 * happen. */

#include <stddef.h>
#include <stdint.h>

#include "webfont.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    wf_list l;
    if (wf_scan((const char *)data, size, &l) == 0) {
        if (l.count > WF_MAX_REFS) __builtin_trap();
        for (size_t i = 0; i < l.count; ++i) {
            if (l.refs[i].family[WF_FAMILY_MAX - 1] != '\0') __builtin_trap();
            if (l.refs[i].url[WF_URL_MAX - 1] != '\0') __builtin_trap();
            if (l.refs[i].format[WF_FORMAT_MAX - 1] != '\0') __builtin_trap();
        }
        wf_list_free(&l);
    }
    return 0;
}
