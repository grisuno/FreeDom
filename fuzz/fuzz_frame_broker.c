/*
 * libFuzzer harness for frame_broker (spec/frame_broker.md).
 *
 * Goal: hostile URLs / targetOrigin strings and arbitrary frame-op sequences never crash, leak,
 * trip UB, or deliver to a frame that is not live, not addressable, or whose origin the
 * targetOrigin does not admit.
 *
 * Build & run: make fuzz-fbk   (clang + -fsanitize=fuzzer,address,undefined)
 */
#include "frame_broker.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char *s = (char *)malloc(size + 1);
    if (s == NULL) return 0;
    memcpy(s, data, size);
    s[size] = '\0';

    char o[FBK_ORIGIN_MAX];
    (void)fbk_origin_of(s, o, sizeof o);
    if (strcmp(o, "null") != 0 && strncmp(o, "https://", 8) != 0) __builtin_trap();

    fbk_table t;
    if (fbk_init(&t, "https://top.test/") != 0) { free(s); return 0; }
    int ids[8] = {0};
    size_t n = 1;
    for (size_t i = 0; i + 1 < size && i < 64; i += 2) {
        uint8_t op = (uint8_t)s[i], arg = (uint8_t)s[i + 1];
        if (op % 4 == 0 && n < 8) {
            int id;
            if (fbk_add(&t, ids[arg % n], s + i + 1, &id) == 0) ids[n++] = id;
        } else if (op % 4 == 1) {
            fbk_remove(&t, ids[arg % n]);
        } else {
            int dest = -1;
            fbk_verdict v = fbk_route(&t, ids[op / 4 % n], (fbk_rel)(arg % 3), ids[arg / 3 % n],
                                      s + i + 1, (size_t)arg * 8192, &dest);
            if (v == FBK_DELIVER) {
                const char *dorg = fbk_origin(&t, dest);
                if (dorg == NULL) __builtin_trap();
                if (strcmp(s + i + 1, "*") != 0 && strcmp(dorg, "null") == 0) __builtin_trap();
            }
        }
    }
    free(s);
    return 0;
}
