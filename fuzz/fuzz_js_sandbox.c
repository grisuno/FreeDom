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

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    js_limits lim = js_limits_default();
    lim.memory_limit_bytes = 16u * 1024u * 1024u;
    lim.time_budget_ms = 100;
    lim.max_source_bytes = 1u * 1024u * 1024u;

    js_result r;
    js_eval_once((const char *)data, size, &lim, &r);
    js_result_free(&r);
    return 0;
}
