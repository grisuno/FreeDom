/*
 * libFuzzer harness for web_storage (spec/web_storage.md).
 *
 * Goal: a hostile worker snapshot must never crash/leak/UB, a rejected one must
 * leave the database untouched, and an accepted one must re-encode byte-exact.
 *
 * Build & run: make fuzz-wst   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "web_storage.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    wst_db *db = wst_new();
    if (db == NULL) return 0;
    const char *blob = (const char *)data;
    int ok = wst_replace(db, "https://f.test", blob, size);
    if ((ok == 0) != (wst_decode_check(blob, size) == 0)) __builtin_trap();
    char *out = NULL;
    size_t len = 0;
    if (wst_encode(db, "https://f.test", &out, &len) == 0) {
        if (ok == 0 && (len != size || memcmp(out, blob, size) != 0)) __builtin_trap();
        if (ok != 0 && len != 4) __builtin_trap();          /* rejected: still empty */
        free(out);
    }
    wst_free(db);
    return 0;
}
