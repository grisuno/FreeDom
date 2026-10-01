/*
 * libFuzzer harness for import_map (spec/import_map.md): hostile import map JSON
 * (first half of the input) and hostile specifiers (second half) through parse +
 * resolve. Must never crash/leak/UB; a successful resolve is always NUL-terminated
 * and within the buffer.
 *
 * Build & run: make fuzz-imap   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "import_map.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int fres(void *ctx, const char *base, const char *ref, char *out, size_t outsz) {
    (void)ctx;
    int n = (strncmp(ref, "https://", 8) == 0) ? snprintf(out, outsz, "%s", ref)
          : snprintf(out, outsz, "%s#%s", base, ref);
    return (n > 0 && (size_t)n < outsz) ? 0 : -1;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    size_t half = size / 2;
    im_map *m = im_parse((const char *)data, half, "https://d.test/p", fres, NULL);
    char *spec = (char *)malloc(size - half + 1);
    if (spec != NULL) {
        memcpy(spec, data + half, size - half);
        spec[size - half] = '\0';
        char out[256];
        if (im_resolve(m, "https://d.test/app/m.js", spec, fres, NULL, out, sizeof out) == 0
            && memchr(out, '\0', sizeof out) == NULL) __builtin_trap();
        (void)im_resolve(m, "https://d.test/app/m.js", "react", fres, NULL, out, sizeof out);
        free(spec);
    }
    im_free(m);
    return 0;
}
