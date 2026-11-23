/* Fuzzer for link_preview (spec/link_preview.md): input = base NUL href. The status text
 * must be printable ASCII, bounded, its host span inside it, and its kind must agree with
 * the click decision of ln_resolve. */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "link_nav.h"
#include "link_preview.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char *buf = malloc(size + 2);
    if (buf == NULL) return 0;
    memcpy(buf, data, size);
    buf[size] = '\0';
    buf[size + 1] = '\0';
    size_t split = strlen(buf);
    const char *base = split > 0 ? buf : NULL;
    const char *href = buf + (split < size ? split + 1 : size);

    lp_preview p;
    if (lp_describe(base, href, &p) != LP_OK) abort();
    size_t n = 0;
    while (n < LP_TEXT_MAX && p.text[n] != '\0') ++n;
    if (n >= LP_TEXT_MAX) abort();
    for (size_t i = 0; i < n; ++i) {
        unsigned char c = (unsigned char)p.text[i];
        if (c < 0x20 || c >= 0x7F) abort();
    }
    if (p.host_off + p.host_len > n) abort();

    static ln_result r;
    if (ln_resolve(base, href, &r) != LN_OK) abort();
    if ((r.action == LN_NAVIGATE) != (p.kind == LP_NAVIGATE)) abort();
    if ((r.action == LN_BLOCKED) != (p.kind == LP_BLOCKED)) abort();
    free(buf);
    return 0;
}
