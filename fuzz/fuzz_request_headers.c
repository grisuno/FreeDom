/*
 * libFuzzer harness for rp_sanitize_request_headers (spec/request_headers.md).
 *
 * The block is text a hostile page builds. Whatever it is, the output must be a well-formed,
 * NUL-terminated header block inside the caps, contain no forbidden/identity header, no control
 * byte and no CR/LF injection, and sanitizing it again must change nothing (idempotent).
 *
 * Build & run: make fuzz-rqh   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "request_policy.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size > 16384) return 0;
    char *raw = (char *)malloc(size + 1);
    if (raw == NULL) return 0;
    memcpy(raw, data, size);
    raw[size] = '\0';

    for (size_t cap = 1; cap <= RP_HDR_MAX_BYTES + 8; cap = cap * 3 + 1) {
        char *out = (char *)malloc(cap);
        if (out == NULL) break;
        int n = rp_sanitize_request_headers(raw, out, cap);
        if (n < 0 || n > RP_HDR_MAX_COUNT || strlen(out) >= cap) abort();
        if (strlen(out) > RP_HDR_MAX_BYTES) abort();
        if (strchr(out, '\r') != NULL) abort();
        if (cap == 1 && n != 0) abort();
        if (rp_headers_have(out, "host") || rp_headers_have(out, "cookie")
            || rp_headers_have(out, "user-agent") || rp_headers_have(out, "accept-language")
            || rp_headers_have(out, "origin") || rp_headers_have(out, "referer")) abort();
        for (const char *p = out; *p != '\0'; ++p)
            if ((unsigned char)*p < 0x20 && *p != '\n' && *p != '\t') abort();
        char *again = (char *)malloc(cap);
        if (again != NULL) {
            int m = rp_sanitize_request_headers(out, again, cap);
            if (m != n || strcmp(again, out) != 0) abort();
            free(again);
        }
        free(out);
    }
    free(raw);
    return 0;
}
