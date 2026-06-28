/*
 * libFuzzer harness for js_sandbox (Hito 3).
 *
 * Goal: arbitrary bytes treated as untrusted script through the full
 * eval + result + free pipeline must never crash, leak, or trigger UB on the
 * host. Tight limits keep each input cheap and bound time/memory per run.
 *
 * Build & run: make fuzz-js   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "js_sandbox.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    /* The pure stack parser sees engine-derived strings whose function names and
     * filenames are script-controlled, so fuzz it directly on the raw bytes (cheap,
     * no engine). It must never read out of bounds on any input. */
    char *nt = (char *)malloc(size + 1);
    if (nt != NULL) {
        if (size != 0) memcpy(nt, data, size);
        nt[size] = '\0';
        char file[JS_LOC_FILE_MAX];
        int line = 0, col = 0;
        (void)js_loc_from_stack(nt, file, sizeof file, &line, &col);
        (void)js_loc_from_stack(nt, NULL, 0, NULL, NULL); /* NULL outputs tolerated */
        free(nt);
    }

    js_limits lim = js_limits_default();
    lim.memory_limit_bytes = 16u * 1024u * 1024u;
    lim.time_budget_ms = 100;
    lim.max_source_bytes = 1u * 1024u * 1024u;

    js_result r;
    js_eval_once((const char *)data, size, &lim, &r);
    js_result_free(&r);
    return 0;
}
