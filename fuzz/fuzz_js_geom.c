/*
 * libFuzzer harness for js_geom (spec/js_geom.md).
 *
 * Goal: arbitrary int32 words through decode -> aggregate (with a fuzz-derived,
 * possibly cyclic parent function) -> encode -> decode must never crash, leak or
 * trigger UB, and a decoded table must re-encode to a table that decodes again.
 *
 * Build & run: make fuzz-geom   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "js_geom.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct fz_parent { const uint8_t *data; size_t size; } fz_parent;

/* Parent from the fuzz bytes: may point anywhere, including cycles. */
static dom_node_id fz_parent_of(void *ctx, dom_node_id n) {
    const fz_parent *p = (const fz_parent *)ctx;
    if (p->size == 0) return DOM_NODE_NONE;
    uint8_t b = p->data[(size_t)n % p->size];
    return (b == 0xFF) ? DOM_NODE_NONE : (dom_node_id)(b % 64u);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    size_t n = size / sizeof(int32_t);
    int32_t *words = (int32_t *)calloc(n ? n : 1, sizeof *words);
    if (words == NULL) return 0;
    if (n != 0) memcpy(words, data, n * sizeof *words);

    jg_table t;
    jg_init(&t);
    if (jg_decode(words, n, &t) != 0) {
        /* Not a valid table: build one from the bytes through jg_add instead. */
        for (size_t i = 0; i + 4 < n && i < 4096; i += 5)
            (void)jg_add(&t, (dom_node_id)((uint32_t)words[i] % 64u),
                         (double)words[i + 1], (double)words[i + 2],
                         (double)words[i + 3], (double)words[i + 4]);
        (void)jg_finish(&t);
    }
    fz_parent pc = { data, size };
    (void)jg_aggregate(&t, fz_parent_of, &pc);
    (void)jg_find(&t, 3);
    (void)jg_hash(&t);

    size_t wl = jg_wire_len(&t);
    int32_t *enc = (int32_t *)calloc(wl, sizeof *enc);
    if (enc != NULL && jg_encode(&t, enc, wl) == 0) {
        jg_table u;
        jg_init(&u);
        if (jg_decode(enc, wl, &u) != 0) __builtin_trap();   /* encode output must decode */
        jg_free(&u);
    }
    free(enc);
    jg_free(&t);
    free(words);
    return 0;
}
