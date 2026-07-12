/*
 * TDD suite for secure_fetch (Hito 1).
 *
 * RED state: there is no src/secure_fetch.c yet, so this links and fails on
 * purpose. Implementing the module to satisfy these assertions is the next step.
 *
 * Build: make test   (requires libcmocka-dev)
 * ASan:  make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <cmocka.h>

#include "secure_fetch.h"

/* --- sf_config_default --- */

static void test_config_default_is_secure(void **state) {
    (void)state;
    sf_config c = sf_config_default();
    assert_int_equal(c.policy, SF_POLICY_PQ_HYBRID_KE);
    assert_int_equal((int)c.timeout_ms, (int)SF_DEFAULT_TIMEOUT_MS);
    assert_int_equal((unsigned long)c.max_body_bytes, (unsigned long)SF_DEFAULT_MAX_BODY);
    assert_non_null(c.kex_groups);
    assert_string_equal(c.kex_groups, SF_DEFAULT_KEX_GROUPS);
    assert_null(c.user_agent); /* NULL => resolved to the default at request time */
}

static void test_config_blend_fields_default_null(void **state) {
    (void)state;
    sf_config c = sf_config_default();
    assert_null(c.referrer_url);
    assert_null(c.sec_fetch_dest);
    assert_null(c.sec_fetch_mode);
    assert_null(c.progress_ctx);
    assert_null(c.progress_cb);
}

/* --- sf_user_agent_or_default --- */

static void test_user_agent_default_when_unset(void **state) {
    (void)state;
    assert_string_equal(sf_user_agent_or_default(NULL), SF_DEFAULT_USER_AGENT);
    assert_string_equal(sf_user_agent_or_default(""), SF_DEFAULT_USER_AGENT);
}

static void test_user_agent_uses_override(void **state) {
    (void)state;
    const char *ua = "Mozilla/5.0 (X11; Linux x86_64; rv:128.0) Gecko/20100101 Firefox/128.0";
    assert_string_equal(sf_user_agent_or_default(ua), ua);
}

/* --- sf_validate_url --- */

static void test_url_rejects_null(void **state) {
    (void)state;
    assert_int_equal(sf_validate_url(NULL), SF_ERR_INVALID_URL);
}

static void test_url_rejects_plain_http(void **state) {
    (void)state;
    assert_int_equal(sf_validate_url("http://example.com"), SF_ERR_INVALID_URL);
}

static void test_url_rejects_dangerous_schemes(void **state) {
    (void)state;
    assert_int_equal(sf_validate_url("file:///etc/passwd"), SF_ERR_INVALID_URL);
    assert_int_equal(sf_validate_url("javascript:alert(1)"), SF_ERR_INVALID_URL);
    assert_int_equal(sf_validate_url("data:text/html,<b>x"), SF_ERR_INVALID_URL);
    assert_int_equal(sf_validate_url("ftp://example.com"), SF_ERR_INVALID_URL);
    assert_int_equal(sf_validate_url("example.com"), SF_ERR_INVALID_URL);
    assert_int_equal(sf_validate_url("https://"), SF_ERR_INVALID_URL);
}

static void test_url_accepts_https(void **state) {
    (void)state;
    assert_int_equal(sf_validate_url("https://example.com/path"), SF_OK);
    assert_int_equal(sf_validate_url("HTTPS://EXAMPLE.COM"), SF_OK);
}

/* --- sf_check_tls_version --- (requirement (a)) */

static void test_tls_rejects_12(void **state) {
    (void)state;
    assert_int_equal(sf_check_tls_version("TLSv1.2"), SF_ERR_TLS_VERSION);
}

static void test_tls_rejects_older_and_garbage(void **state) {
    (void)state;
    assert_int_equal(sf_check_tls_version("TLSv1.1"), SF_ERR_TLS_VERSION);
    assert_int_equal(sf_check_tls_version("TLSv1"), SF_ERR_TLS_VERSION);
    assert_int_equal(sf_check_tls_version("SSLv3"), SF_ERR_TLS_VERSION);
    assert_int_equal(sf_check_tls_version(NULL), SF_ERR_TLS_VERSION);
    assert_int_equal(sf_check_tls_version("nonsense"), SF_ERR_TLS_VERSION);
}

static void test_tls_accepts_13(void **state) {
    (void)state;
    assert_int_equal(sf_check_tls_version("TLSv1.3"), SF_OK);
}

/* --- sf_check_group_is_pq --- */

static void test_group_rejects_classical(void **state) {
    (void)state;
    assert_int_equal(sf_check_group_is_pq("x25519"), SF_ERR_KEM_NOT_PQ);
    assert_int_equal(sf_check_group_is_pq("secp256r1"), SF_ERR_KEM_NOT_PQ);
    assert_int_equal(sf_check_group_is_pq(NULL), SF_ERR_KEM_NOT_PQ);
}

static void test_group_rejects_pure_pq(void **state) {
    (void)state;
    /* Pure PQ has no classical fallback: rejected by design. */
    assert_int_equal(sf_check_group_is_pq("MLKEM768"), SF_ERR_KEM_NOT_PQ);
    assert_int_equal(sf_check_group_is_pq("MLKEM1024"), SF_ERR_KEM_NOT_PQ);
}

static void test_group_accepts_hybrid(void **state) {
    (void)state;
    assert_int_equal(sf_check_group_is_pq("X25519MLKEM768"), SF_OK);
    assert_int_equal(sf_check_group_is_pq("SecP256r1MLKEM768"), SF_OK);
    assert_int_equal(sf_check_group_is_pq("X448MLKEM1024"), SF_OK);
}

/* --- sf_check_chain_policy --- (requirement (b)) */

static void test_chain_strict_rejects_classical(void **state) {
    (void)state;
    sf_chain_info classical = {
        .leaf_sig_alg = "ecdsa-with-SHA256", .rsa_bits = 0, .uses_sha1 = 0, .has_pq_sig = 0
    };
    assert_int_equal(sf_check_chain_policy(&classical, SF_POLICY_STRICT_PQ),
                     SF_ERR_CERT_NOT_PQ);
}

static void test_chain_strict_accepts_pq(void **state) {
    (void)state;
    sf_chain_info pq = {
        .leaf_sig_alg = "ML-DSA-65", .rsa_bits = 0, .uses_sha1 = 0, .has_pq_sig = 1
    };
    assert_int_equal(sf_check_chain_policy(&pq, SF_POLICY_STRICT_PQ), SF_OK);
}

static void test_chain_hybrid_allows_classical(void **state) {
    (void)state;
    sf_chain_info classical = {
        .leaf_sig_alg = "rsaEncryption", .rsa_bits = 4096, .uses_sha1 = 0, .has_pq_sig = 0
    };
    assert_int_equal(sf_check_chain_policy(&classical, SF_POLICY_PQ_HYBRID_KE), SF_OK);
}

static void test_chain_rejects_sha1_in_any_policy(void **state) {
    (void)state;
    sf_chain_info sha1 = {
        .leaf_sig_alg = "sha1WithRSAEncryption", .rsa_bits = 4096, .uses_sha1 = 1, .has_pq_sig = 0
    };
    assert_int_equal(sf_check_chain_policy(&sha1, SF_POLICY_PQ_HYBRID_KE), SF_ERR_WEAK_ALGO);
    assert_int_equal(sf_check_chain_policy(&sha1, SF_POLICY_STRICT_PQ), SF_ERR_WEAK_ALGO);
}

static void test_chain_permissive_allows_weak_certs(void **state) {
    (void)state;
    sf_chain_info weak = {
        .leaf_sig_alg = "rsaEncryption", .rsa_bits = 2048, .uses_sha1 = 0, .has_pq_sig = 0
    };
    assert_int_equal(sf_check_chain_policy(&weak, SF_POLICY_PERMISSIVE), SF_OK);

    sf_chain_info sha1 = {
        .leaf_sig_alg = "sha1WithRSAEncryption", .rsa_bits = 4096, .uses_sha1 = 1, .has_pq_sig = 0
    };
    assert_int_equal(sf_check_chain_policy(&sha1, SF_POLICY_PERMISSIVE), SF_OK);
}

static void test_chain_rejects_weak_rsa(void **state) {
    (void)state;
    sf_chain_info weak = {
        .leaf_sig_alg = "rsaEncryption", .rsa_bits = 2048, .uses_sha1 = 0, .has_pq_sig = 0
    };
    assert_int_equal(sf_check_chain_policy(&weak, SF_POLICY_PQ_HYBRID_KE), SF_ERR_WEAK_ALGO);
}

static void test_chain_rejects_null(void **state) {
    (void)state;
    assert_int_equal(sf_check_chain_policy(NULL, SF_POLICY_PQ_HYBRID_KE), SF_ERR_NULL_ARG);
}

/* --- sf_enforce_policy --- (the orchestration glue, fail-closed) */

static const sf_chain_info OK_CLASSICAL = {
    .leaf_sig_alg = "ecdsa-with-SHA256", .rsa_bits = 0, .uses_sha1 = 0, .has_pq_sig = 0
};
static const sf_chain_info OK_PQ = {
    .leaf_sig_alg = "ML-DSA-65", .rsa_bits = 0, .uses_sha1 = 0, .has_pq_sig = 1
};

static void test_enforce_all_good_hybrid(void **state) {
    (void)state;
    assert_int_equal(sf_enforce_policy("TLSv1.3", "X25519MLKEM768", &OK_CLASSICAL,
                                       SF_POLICY_PQ_HYBRID_KE), SF_OK);
}

static void test_enforce_checks_version_first(void **state) {
    (void)state;
    /* Bad version short-circuits even with a good group and chain. */
    assert_int_equal(sf_enforce_policy("TLSv1.2", "X25519MLKEM768", &OK_CLASSICAL,
                                       SF_POLICY_PQ_HYBRID_KE), SF_ERR_TLS_VERSION);
    assert_int_equal(sf_enforce_policy(NULL, "X25519MLKEM768", &OK_CLASSICAL,
                                       SF_POLICY_PQ_HYBRID_KE), SF_ERR_TLS_VERSION);
}

static void test_enforce_checks_group_after_version(void **state) {
    (void)state;
    assert_int_equal(sf_enforce_policy("TLSv1.3", "x25519", &OK_CLASSICAL,
                                       SF_POLICY_PQ_HYBRID_KE), SF_ERR_KEM_NOT_PQ);
    assert_int_equal(sf_enforce_policy("TLSv1.3", NULL, &OK_CLASSICAL,
                                       SF_POLICY_PQ_HYBRID_KE), SF_ERR_KEM_NOT_PQ);
}

static void test_enforce_fails_closed_on_null_chain(void **state) {
    (void)state;
    /* Version and group good but chain could not be inspected => refuse. */
    assert_int_equal(sf_enforce_policy("TLSv1.3", "X25519MLKEM768", NULL,
                                       SF_POLICY_PQ_HYBRID_KE), SF_ERR_INTERNAL);
}

static void test_enforce_strict_requires_pq_chain(void **state) {
    (void)state;
    assert_int_equal(sf_enforce_policy("TLSv1.3", "X25519MLKEM768", &OK_CLASSICAL,
                                       SF_POLICY_STRICT_PQ), SF_ERR_CERT_NOT_PQ);
    assert_int_equal(sf_enforce_policy("TLSv1.3", "X25519MLKEM768", &OK_PQ,
                                       SF_POLICY_STRICT_PQ), SF_OK);
}

/* A weak chain: SHA-1 signature (forbidden in every non-permissive policy). */
static const sf_chain_info WEAK_SHA1 = {
    .leaf_sig_alg = "sha1WithRSAEncryption", .rsa_bits = 4096, .uses_sha1 = 1, .has_pq_sig = 0
};

static void test_enforce_allow_classical_ke(void **state) {
    (void)state;
    /* The navigability fallback accepts a classical KE that strict mode rejects... */
    assert_int_equal(sf_enforce_policy("TLSv1.3", "x25519", &OK_CLASSICAL,
                                       SF_POLICY_PQ_HYBRID_KE), SF_ERR_KEM_NOT_PQ);
    assert_int_equal(sf_enforce_policy("TLSv1.3", "x25519", &OK_CLASSICAL,
                                       SF_POLICY_ALLOW_CLASSICAL_KE), SF_OK);
    /* ...but it still enforces TLS 1.3, a non-NULL chain, and the cert checks. */
    assert_int_equal(sf_enforce_policy("TLSv1.2", "x25519", &OK_CLASSICAL,
                                       SF_POLICY_ALLOW_CLASSICAL_KE), SF_ERR_TLS_VERSION);
    assert_int_equal(sf_enforce_policy("TLSv1.3", "x25519", NULL,
                                       SF_POLICY_ALLOW_CLASSICAL_KE), SF_ERR_INTERNAL);
    assert_int_equal(sf_enforce_policy("TLSv1.3", "x25519", &WEAK_SHA1,
                                       SF_POLICY_ALLOW_CLASSICAL_KE), SF_ERR_WEAK_ALGO);
}

/* The allowlist override: the user's sovereign per-host escape hatch for sites below
 * Freedom's elevated standard. Tolerates TLS 1.2, a classical KE, and weak-but-valid
 * leaf primitives; still authenticates the chain (non-NULL) and refuses below 1.2. */
static void test_enforce_allowlisted_insecure(void **state) {
    (void)state;
    /* A TLS 1.2, classical-KE host with a fine cert (e.g. Hacker News) now passes... */
    assert_int_equal(sf_enforce_policy("TLSv1.2", "x25519", &OK_CLASSICAL,
                                       SF_POLICY_ALLOWLISTED_INSECURE), SF_OK);
    /* ...as does plain TLS 1.3, and a weak/SHA-1 leaf (override = permissive chain). */
    assert_int_equal(sf_enforce_policy("TLSv1.3", "x25519", &OK_CLASSICAL,
                                       SF_POLICY_ALLOWLISTED_INSECURE), SF_OK);
    assert_int_equal(sf_enforce_policy("TLSv1.2", "x25519", &WEAK_SHA1,
                                       SF_POLICY_ALLOWLISTED_INSECURE), SF_OK);
    /* But authenticity is never waived: a non-inspectable chain still fails closed,
     * and anything below TLS 1.2 is still refused. */
    assert_int_equal(sf_enforce_policy("TLSv1.2", "x25519", NULL,
                                       SF_POLICY_ALLOWLISTED_INSECURE), SF_ERR_INTERNAL);
    assert_int_equal(sf_enforce_policy("TLSv1.1", "x25519", &OK_CLASSICAL,
                                       SF_POLICY_ALLOWLISTED_INSECURE), SF_ERR_TLS_VERSION);
    assert_int_equal(sf_enforce_policy(NULL, "x25519", &OK_CLASSICAL,
                                       SF_POLICY_ALLOWLISTED_INSECURE), SF_ERR_TLS_VERSION);
}

/* --- sf_is_redirect_code --- */

static void test_redirect_code_recognizes_3xx(void **state) {
    (void)state;
    assert_true(sf_is_redirect_code(301));
    assert_true(sf_is_redirect_code(302));
    assert_true(sf_is_redirect_code(303));
    assert_true(sf_is_redirect_code(307));
    assert_true(sf_is_redirect_code(308));
}

static void test_redirect_code_rejects_others(void **state) {
    (void)state;
    assert_false(sf_is_redirect_code(200));
    assert_false(sf_is_redirect_code(204));
    assert_false(sf_is_redirect_code(304)); /* Not Modified is not a redirect target */
    assert_false(sf_is_redirect_code(404));
    assert_false(sf_is_redirect_code(0));
}

/* --- sf_parse_location_header --- */

static void test_location_parses_value(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(sf_parse_location_header("Location: https://www.google.com/\r\n",
                                              out, sizeof out), SF_OK);
    assert_string_equal(out, "https://www.google.com/");
}

static void test_location_is_case_insensitive_and_trims(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(sf_parse_location_header("LOCATION:   https://x.example/p  \r\n",
                                              out, sizeof out), SF_OK);
    assert_string_equal(out, "https://x.example/p");
    assert_int_equal(sf_parse_location_header("location: /next\n", out, sizeof out), SF_OK);
    assert_string_equal(out, "/next");
}

static void test_location_rejects_non_location_and_empty(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(sf_parse_location_header("Content-Type: text/html\r\n",
                                              out, sizeof out), SF_ERR_INVALID_URL);
    assert_int_equal(sf_parse_location_header("Location:\r\n", out, sizeof out),
                     SF_ERR_INVALID_URL);
    assert_int_equal(sf_parse_location_header("Location:    \r\n", out, sizeof out),
                     SF_ERR_INVALID_URL);
    assert_int_equal(sf_parse_location_header(NULL, out, sizeof out), SF_ERR_INVALID_URL);
}

static void test_location_rejects_overflow(void **state) {
    (void)state;
    char small[8];
    assert_int_equal(sf_parse_location_header("Location: https://toolong.example/\r\n",
                                              small, sizeof small), SF_ERR_INVALID_URL);
}

/* --- sf_resolve_redirect --- */

static void test_resolve_absolute_https(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(sf_resolve_redirect("https://google.com/", "https://www.google.com/",
                                         out, sizeof out), SF_OK);
    assert_string_equal(out, "https://www.google.com/");
}

static void test_resolve_refuses_http_downgrade(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(sf_resolve_redirect("https://secure.example/", "http://secure.example/",
                                         out, sizeof out), SF_ERR_INVALID_URL);
}

static void test_resolve_refuses_dangerous_schemes(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(sf_resolve_redirect("https://x.example/", "javascript:alert(1)",
                                         out, sizeof out), SF_ERR_INVALID_URL);
    assert_int_equal(sf_resolve_redirect("https://x.example/", "data:text/html,x",
                                         out, sizeof out), SF_ERR_INVALID_URL);
    assert_int_equal(sf_resolve_redirect("https://x.example/", "ftp://x.example/",
                                         out, sizeof out), SF_ERR_INVALID_URL);
}

static void test_resolve_scheme_relative(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(sf_resolve_redirect("https://a.example/x", "//b.example/y",
                                         out, sizeof out), SF_OK);
    assert_string_equal(out, "https://b.example/y");
}

static void test_resolve_absolute_path(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(sf_resolve_redirect("https://google.com/a/b", "/search?q=1",
                                         out, sizeof out), SF_OK);
    assert_string_equal(out, "https://google.com/search?q=1");
    /* origin-only base + absolute path */
    assert_int_equal(sf_resolve_redirect("https://google.com", "/foo",
                                         out, sizeof out), SF_OK);
    assert_string_equal(out, "https://google.com/foo");
}

static void test_resolve_relative_path(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(sf_resolve_redirect("https://h.example/a/b", "foo",
                                         out, sizeof out), SF_OK);
    assert_string_equal(out, "https://h.example/a/foo");
    /* relative against an origin-only base resolves to /foo */
    assert_int_equal(sf_resolve_redirect("https://h.example", "foo",
                                         out, sizeof out), SF_OK);
    assert_string_equal(out, "https://h.example/foo");
}

static void test_resolve_null_args(void **state) {
    (void)state;
    char out[256];
    assert_int_equal(sf_resolve_redirect(NULL, "/x", out, sizeof out), SF_ERR_NULL_ARG);
    assert_int_equal(sf_resolve_redirect("https://h/", NULL, out, sizeof out), SF_ERR_NULL_ARG);
    assert_int_equal(sf_resolve_redirect("https://h/", "/x", NULL, sizeof out), SF_ERR_NULL_ARG);
    assert_int_equal(sf_resolve_redirect("https://h/", "/x", out, 0), SF_ERR_NULL_ARG);
}

/* --- memory safety --- (requirement (c)) */

static void test_response_free_on_zeroed(void **state) {
    (void)state;
    sf_response r;
    memset(&r, 0, sizeof r);
    sf_response_free(&r); /* must not crash on all-NULL members */
    sf_response_free(&r); /* idempotent: second call also safe */
    sf_response_free(NULL); /* NULL is a no-op */
}

static void test_response_free_releases_location(void **state) {
    (void)state;
    /* A populated location must be freed by sf_response_free (ASan catches leaks). */
    sf_response r;
    memset(&r, 0, sizeof r);
    const char *u = "https://www.google.com/";
    size_t n = strlen(u) + 1;
    r.location = malloc(n);
    assert_non_null(r.location);
    memcpy(r.location, u, n);
    sf_response_free(&r);
    assert_null(r.location);
}

static void test_get_follow_null_args(void **state) {
    (void)state;
    sf_config cfg = sf_config_default();
    sf_response out;
    memset(&out, 0, sizeof out);
    assert_int_equal(sf_get_follow(NULL, &cfg, &out, 5), SF_ERR_NULL_ARG);
    assert_int_equal(sf_get_follow("https://example.com", &cfg, NULL, 5), SF_ERR_NULL_ARG);
}

static void test_get_null_args(void **state) {
    (void)state;
    sf_config cfg = sf_config_default();
    sf_response out;
    memset(&out, 0, sizeof out);
    assert_int_equal(sf_get(NULL, &cfg, &out), SF_ERR_NULL_ARG);
    assert_int_equal(sf_get("https://example.com", &cfg, NULL), SF_ERR_NULL_ARG);
}

static void test_post_null_args(void **state) {
    (void)state;
    sf_config cfg = sf_config_default();
    sf_response out;
    memset(&out, 0, sizeof out);
    assert_int_equal(sf_post(NULL, &cfg, "a=b", 3, NULL, &out), SF_ERR_NULL_ARG);
    assert_int_equal(sf_post("https://example.com", &cfg, "a=b", 3, NULL, NULL), SF_ERR_NULL_ARG);
    /* A NULL body with a non-zero length is rejected before any network use. */
    assert_int_equal(sf_post("https://example.com", &cfg, NULL, 5, NULL, &out), SF_ERR_NULL_ARG);
}

/* The URL scheme is validated before any socket is opened, so a downgrade is
 * rejected without network (Secure by Default: an insecure POST is unrepresentable). */
static void test_post_rejects_non_https(void **state) {
    (void)state;
    sf_config cfg = sf_config_default();
    sf_response out;
    memset(&out, 0, sizeof out);
    assert_int_equal(sf_post("http://example.com/login", &cfg, "a=b", 3, NULL, &out),
                     SF_ERR_INVALID_URL);
    assert_int_equal(sf_post("javascript:alert(1)", &cfg, "", 0, NULL, &out),
                     SF_ERR_INVALID_URL);
}

/* --- session cookie jar (document.cookie bridge for trusted hosts) --- */

static void test_cookie_line_matches_pure(void **state) {
    (void)state;
    char out[256];
    const long now = 2000000000L; /* far future: session cookies (expiry 0) stay valid */
    /* domain cookie (.google.com) reaches www.google.com */
    assert_int_equal(sf_cookie_line_matches(
        ".google.com\tTRUE\t/\tFALSE\t0\tSID\tabc", "www.google.com", "/search",
        now, out, sizeof out), 1);
    assert_string_equal(out, "SID=abc");
    /* host-only cookie matches exact host but NOT a bare parent domain */
    assert_int_equal(sf_cookie_line_matches(
        "google.com\tFALSE\t/\tFALSE\t0\tA\t1", "www.google.com", "/",
        now, out, sizeof out), 0);
    /* unrelated domain never matches */
    assert_int_equal(sf_cookie_line_matches(
        ".evil.com\tTRUE\t/\tFALSE\t0\tX\t1", "www.google.com", "/",
        now, out, sizeof out), 0);
    /* HttpOnly marker is network-only -> excluded from the document.cookie view */
    assert_int_equal(sf_cookie_line_matches(
        "#HttpOnly_.google.com\tTRUE\t/\tFALSE\t0\tSEC\ty", "www.google.com", "/",
        now, out, sizeof out), 0);
    /* an expired cookie is skipped; a path that is not a prefix is skipped */
    assert_int_equal(sf_cookie_line_matches(
        ".google.com\tTRUE\t/\tFALSE\t1000000000\tOLD\tz", "www.google.com", "/",
        now, out, sizeof out), 0);
    assert_int_equal(sf_cookie_line_matches(
        ".google.com\tTRUE\t/deep\tFALSE\t0\tP\t1", "www.google.com", "/",
        now, out, sizeof out), 0);
    assert_int_equal(sf_cookie_line_matches(
        ".google.com\tTRUE\t/deep\tFALSE\t0\tP\t1", "www.google.com", "/deep/x",
        now, out, sizeof out), 1);
    /* a Netscape comment line is ignored */
    assert_int_equal(sf_cookie_line_matches(
        "# Netscape HTTP Cookie File", "www.google.com", "/", now, out, sizeof out), 0);
}

static void test_cookie_jar_put_and_header(void **state) {
    (void)state;
    sf_global_init(); /* creates the shared in-memory jar */
    sf_cookie_put("https://www.google.com/", "SOCS=xyz123");
    sf_cookie_put("https://www.google.com/", "CONSENT=yes; path=/; SameSite=Lax");
    char buf[512];
    size_t n = sf_cookie_header_for("https://www.google.com/search?q=x", buf, sizeof buf);
    assert_true(n > 0);
    assert_non_null(strstr(buf, "SOCS=xyz123"));
    assert_non_null(strstr(buf, "CONSENT=yes")); /* attributes past ';' were dropped */
    /* an unrelated host never receives google's cookies (domain-scoped) */
    char buf2[512];
    sf_cookie_header_for("https://example.com/", buf2, sizeof buf2);
    assert_null(strstr(buf2, "SOCS"));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_config_default_is_secure),
        cmocka_unit_test(test_config_blend_fields_default_null),
        cmocka_unit_test(test_user_agent_default_when_unset),
        cmocka_unit_test(test_user_agent_uses_override),
        cmocka_unit_test(test_url_rejects_null),
        cmocka_unit_test(test_url_rejects_plain_http),
        cmocka_unit_test(test_url_rejects_dangerous_schemes),
        cmocka_unit_test(test_url_accepts_https),
        cmocka_unit_test(test_tls_rejects_12),
        cmocka_unit_test(test_tls_rejects_older_and_garbage),
        cmocka_unit_test(test_tls_accepts_13),
        cmocka_unit_test(test_group_rejects_classical),
        cmocka_unit_test(test_group_rejects_pure_pq),
        cmocka_unit_test(test_group_accepts_hybrid),
        cmocka_unit_test(test_chain_strict_rejects_classical),
        cmocka_unit_test(test_chain_strict_accepts_pq),
        cmocka_unit_test(test_chain_hybrid_allows_classical),
        cmocka_unit_test(test_chain_rejects_sha1_in_any_policy),
        cmocka_unit_test(test_chain_permissive_allows_weak_certs),
        cmocka_unit_test(test_chain_rejects_weak_rsa),
        cmocka_unit_test(test_chain_rejects_null),
        cmocka_unit_test(test_enforce_all_good_hybrid),
        cmocka_unit_test(test_enforce_checks_version_first),
        cmocka_unit_test(test_enforce_checks_group_after_version),
        cmocka_unit_test(test_enforce_fails_closed_on_null_chain),
        cmocka_unit_test(test_enforce_strict_requires_pq_chain),
        cmocka_unit_test(test_enforce_allow_classical_ke),
        cmocka_unit_test(test_enforce_allowlisted_insecure),
        cmocka_unit_test(test_redirect_code_recognizes_3xx),
        cmocka_unit_test(test_redirect_code_rejects_others),
        cmocka_unit_test(test_location_parses_value),
        cmocka_unit_test(test_location_is_case_insensitive_and_trims),
        cmocka_unit_test(test_location_rejects_non_location_and_empty),
        cmocka_unit_test(test_location_rejects_overflow),
        cmocka_unit_test(test_resolve_absolute_https),
        cmocka_unit_test(test_resolve_refuses_http_downgrade),
        cmocka_unit_test(test_resolve_refuses_dangerous_schemes),
        cmocka_unit_test(test_resolve_scheme_relative),
        cmocka_unit_test(test_resolve_absolute_path),
        cmocka_unit_test(test_resolve_relative_path),
        cmocka_unit_test(test_resolve_null_args),
        cmocka_unit_test(test_response_free_on_zeroed),
        cmocka_unit_test(test_response_free_releases_location),
        cmocka_unit_test(test_get_null_args),
        cmocka_unit_test(test_get_follow_null_args),
        cmocka_unit_test(test_post_null_args),
        cmocka_unit_test(test_post_rejects_non_https),
        cmocka_unit_test(test_cookie_line_matches_pure),
        cmocka_unit_test(test_cookie_jar_put_and_header),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
