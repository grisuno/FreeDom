/* libFuzzer harness for css_nest (spec/css_nest.md): hostile nested stylesheets.
 * Invariants: the output stays within its documented bound and is NUL-terminated at its
 * length; the detector and the flattener never read past the input (the input is not
 * NUL-terminated here on purpose). Structural oracle: with no string or escape in the
 * input, the output has no nesting left. Bad strings/escapes in garbage may re-tokenize
 * differently once re-emitted; the flat parser drops such text either way, so only memory
 * safety and the bound are required there (spec/css_nest.md). */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "css_nest.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size > 65536) return 0;
    char *s = (char *)malloc(size ? size : 1);
    if (s == NULL) return 0;
    if (size) memcpy(s, data, size);
    (void)cn_has_nesting(s, size);
    char *out = NULL;
    size_t n = 0;
    if (cn_flatten(s, size, &out, &n) == CN_OK) {
        if (out == NULL) abort();
        if (n > size * CN_MAX_OUT_FACTOR + CN_OUT_SLACK) abort();
        if (out[n] != '\0') abort();
        if (memchr(s, '"', size) == NULL && memchr(s, '\'', size) == NULL &&
            memchr(s, '\\', size) == NULL && cn_has_nesting(out, n)) abort();
        free(out);
    }
    free(s);
    return 0;
}
