/*
 * libFuzzer harness for data_url: du_base64_payload (data: URL slicing) and
 * du_base64_decode (RFC 4648 decode). Both process bytes that came straight from a
 * hostile remote HTML document; du_base64_decode specifically runs inside the
 * confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, never
 * interpreted. Neither must ever crash, leak, read/write out of bounds, or (for
 * du_base64_payload) return a payload span outside the input string.
 *
 * Build & run: make fuzz-du   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "data_url.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char *buf = (char *)malloc(size + 1);
    if (buf == NULL) return 0;
    memcpy(buf, data, size);
    buf[size] = '\0';

    const char *payload = NULL;
    size_t plen = 0;
    du_status ps = du_base64_payload(buf, &payload, &plen);
    if (ps == DU_OK) {
        /* payload must alias the input, never point outside it or past its NUL. */
        if (payload < buf || payload > buf + size) abort();
        if (plen > (size_t)((buf + size) - payload)) abort();

        uint8_t *out = NULL;
        size_t out_len = 0;
        du_status ds = du_base64_decode(payload, plen, &out, &out_len);
        if (ds == DU_OK) {
            if (out == NULL) abort(); /* DU_OK always publishes a buffer, even len 0 */
            free(out);
        } else if (out != NULL) {
            abort(); /* a non-OK status must never leak an allocation */
        }
    }

    /* Also drive du_base64_decode directly on the raw bytes (not just the sliced
     * payload), independent of the data: URL wrapper. */
    {
        uint8_t *out = NULL;
        size_t out_len = 0;
        du_status ds = du_base64_decode(buf, size, &out, &out_len);
        if (ds == DU_OK) {
            if (out == NULL) abort();
            free(out);
        } else if (out != NULL) {
            abort();
        }
    }

    (void)du_is_data_url(buf);

    free(buf);
    return 0;
}
