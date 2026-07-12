/*
 * fuzz_tls_impersonate — libFuzzer harness for the parent<->helper IPC codec.
 *
 * The freedom-tls-helper is a separate, heavily-vendored process; a compromised
 * helper (or a corrupted socketpair frame) hands the trusted parent ARBITRARY bytes.
 * ti_decode_req / ti_decode_resp must never crash/leak/UB, must honor every TI_MAX_*
 * cap fail-closed, and must never read past the frame. On a successful decode we also
 * re-encode and re-decode to exercise the round-trip and free paths.
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "tls_impersonate.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    ti_req rq;
    if (ti_decode_req(data, size, &rq) == 0) {
        uint8_t *buf = malloc(size + 64u);
        if (buf != NULL) {
            size_t n = ti_encode_req(&rq, buf, size + 64u);
            if (n != 0) {
                ti_req rq2;
                if (ti_decode_req(buf, n, &rq2) == 0) ti_req_free(&rq2);
            }
            free(buf);
        }
        ti_req_free(&rq);
    }

    ti_resp rp;
    if (ti_decode_resp(data, size, &rp) == 0) {
        uint8_t *buf = malloc(size + 64u);
        if (buf != NULL) {
            size_t n = ti_encode_resp(&rp, buf, size + 64u);
            if (n != 0) {
                ti_resp rp2;
                if (ti_decode_resp(buf, n, &rp2) == 0) ti_resp_free(&rp2);
            }
            free(buf);
        }
        ti_resp_free(&rp);
    }
    return 0;
}
