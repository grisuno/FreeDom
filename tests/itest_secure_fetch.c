/*
 * Integration test for secure_fetch (Hito 1, closure).
 *
 * NETWORK-DEPENDENT: not part of `make test`. Run with `make itest`.
 * Proves the end-to-end network path against a live endpoint that supports
 * the hybrid PQ key exchange (Cloudflare negotiates X25519MLKEM768).
 */

#include "secure_fetch.h"

#include <stdio.h>
#include <string.h>

static int failures = 0;

static int always_cancel(void *ctx) { ++*(int *)ctx; return 1; }

#define CHECK(cond, msg)                                  \
    do {                                                  \
        if (cond) {                                       \
            printf("  ok   : %s\n", (msg));               \
        } else {                                          \
            printf("  FAIL : %s\n", (msg));               \
            ++failures;                                   \
        }                                                 \
    } while (0)

int main(void) {
    const char *url = "https://cloudflare.com/";

    /* (1) No network needed: a non-https scheme is rejected up front. */
    sf_response r0;
    sf_status s0 = sf_get("http://example.com/", NULL, &r0);
    CHECK(s0 == SF_ERR_INVALID_URL, "rejects http:// scheme before any I/O");
    sf_response_free(&r0);

    /* (2) Default policy: a real request must succeed under hybrid PQ KE. */
    sf_response r;
    sf_status s = sf_get(url, NULL, &r);
    printf("  -> status=%d http=%ld tls=%s group=%s body=%zu bytes\n",
           s, r.http_code,
           r.tls_version ? r.tls_version : "(null)",
           r.negotiated_group ? r.negotiated_group : "(null)",
           r.body_len);
    CHECK(s == SF_OK, "live GET succeeds under default PQ-hybrid policy");
    CHECK(r.tls_version != NULL && strcmp(r.tls_version, "TLSv1.3") == 0,
          "negotiated TLS 1.3");
    CHECK(r.negotiated_group != NULL && strstr(r.negotiated_group, "MLKEM") != NULL,
          "negotiated a hybrid ML-KEM group");
    CHECK(r.http_code > 0, "received an HTTP status code");
    sf_response_free(&r);

    /* (2b) Stop: a cancel callback that says yes aborts the transfer during
     *      connect with SF_ERR_CANCELLED, and the allowlist ladder does not retry. */
    int polls = 0;
    sf_config cc = sf_config_default();
    cc.cancel_cb = always_cancel;
    cc.cancel_ctx = &polls;
    sf_response rc;
    int dg = -1;
    sf_status sc = sf_get_follow_navigable(url, &cc, &rc, &dg, 1);
    printf("  -> cancelled status=%d polls=%d\n", sc, polls);
    CHECK(sc == SF_ERR_CANCELLED, "cancel_cb aborts the transfer with SF_ERR_CANCELLED");
    CHECK(polls == 1, "a cancelled allowlisted request is not retried");
    sf_response_free(&rc);

    /* (3) Force classical-only groups: the browser must refuse the connection
     *     because the negotiated group would not be PQ-hybrid. */
    sf_config classical = sf_config_default();
    classical.kex_groups = "x25519";
    sf_response r2;
    sf_status s2 = sf_get(url, &classical, &r2);
    printf("  -> classical-only status=%d\n", s2);
    CHECK(s2 == SF_ERR_KEM_NOT_PQ,
          "refuses connection when only classical key exchange is offered");
    sf_response_free(&r2);

    printf("\n%s (%d failure(s))\n", failures ? "ITEST FAILED" : "ITEST PASSED", failures);
    return failures ? 1 : 0;
}
