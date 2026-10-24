/*
 * pq_seal -- hybrid ML-KEM-512 + AEAD sealing (spec/pq_seal.md). The data key is
 * HKDF-SHA256(ss || wrap): the KEM secret and the profile key are both required.
 */

#include "pq_seal.h"

#include <stdlib.h>
#include <string.h>

#include <openssl/core_names.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/kdf.h>
#include <openssl/x509.h>

#define PQS_SS_LEN 32u

struct pqs_keys {
    EVP_PKEY *pkey;
};

void pqs_buf_free(uint8_t *buf, size_t len) {
    if (buf == NULL) return;
    OPENSSL_cleanse(buf, len);
    free(buf);
}

void pqs_free(pqs_keys *k) {
    if (k == NULL) return;
    EVP_PKEY_free(k->pkey);
    free(k);
}

static pqs_keys *keys_wrap(EVP_PKEY *pkey) {
    pqs_keys *k = (pqs_keys *)calloc(1, sizeof *k);
    if (k == NULL) { EVP_PKEY_free(pkey); return NULL; }
    k->pkey = pkey;
    return k;
}

pqs_status pqs_generate(pqs_keys **out) {
    if (out == NULL) return PQS_ERR_NULL_ARG;
    *out = NULL;
    EVP_PKEY_CTX *c = EVP_PKEY_CTX_new_from_name(NULL, "ML-KEM-512", NULL);
    if (c == NULL) return PQS_ERR_CRYPTO;
    EVP_PKEY *pk = NULL;
    int ok = EVP_PKEY_keygen_init(c) == 1 && EVP_PKEY_keygen(c, &pk) == 1;
    EVP_PKEY_CTX_free(c);
    if (!ok || pk == NULL) { EVP_PKEY_free(pk); return PQS_ERR_CRYPTO; }
    *out = keys_wrap(pk);
    return *out != NULL ? PQS_OK : PQS_ERR_OOM;
}

pqs_status pqs_export(const pqs_keys *k, uint8_t **der, size_t *len) {
    if (k == NULL || der == NULL || len == NULL) return PQS_ERR_NULL_ARG;
    *der = NULL; *len = 0;
    int n = i2d_PrivateKey(k->pkey, NULL);
    if (n <= 0) return PQS_ERR_CRYPTO;
    uint8_t *buf = (uint8_t *)malloc((size_t)n);
    if (buf == NULL) return PQS_ERR_OOM;
    uint8_t *p = buf;
    if (i2d_PrivateKey(k->pkey, &p) != n) { pqs_buf_free(buf, (size_t)n); return PQS_ERR_CRYPTO; }
    *der = buf; *len = (size_t)n;
    return PQS_OK;
}

pqs_status pqs_import(const uint8_t *der, size_t len, pqs_keys **out) {
    if (der == NULL || out == NULL) return PQS_ERR_NULL_ARG;
    *out = NULL;
    if (len == 0 || len > (1u << 16)) return PQS_ERR_CRYPTO;
    const uint8_t *p = der;
    EVP_PKEY *pk = d2i_AutoPrivateKey(NULL, &p, (long)len);
    if (pk == NULL) return PQS_ERR_CRYPTO;
    if (EVP_PKEY_is_a(pk, "ML-KEM-512") != 1) { EVP_PKEY_free(pk); return PQS_ERR_CRYPTO; }
    *out = keys_wrap(pk);
    return *out != NULL ? PQS_OK : PQS_ERR_OOM;
}

/* HKDF-SHA256 over ss || wrap: the AEAD key. */
static int derive_key(const uint8_t ss[PQS_SS_LEN], const uint8_t wrap[LS_KEY_LEN],
                      uint8_t key[LS_KEY_LEN]) {
    uint8_t ikm[PQS_SS_LEN + LS_KEY_LEN];
    memcpy(ikm, ss, PQS_SS_LEN);
    memcpy(ikm + PQS_SS_LEN, wrap, LS_KEY_LEN);
    EVP_KDF *kdf = EVP_KDF_fetch(NULL, "HKDF", NULL);
    if (kdf == NULL) { OPENSSL_cleanse(ikm, sizeof ikm); return -1; }
    EVP_KDF_CTX *kc = EVP_KDF_CTX_new(kdf);
    EVP_KDF_free(kdf);
    if (kc == NULL) { OPENSSL_cleanse(ikm, sizeof ikm); return -1; }
    OSSL_PARAM params[5];
    char digest[] = "SHA256";
    char salt[] = "freedom-pqseal-v1";
    char info[] = "aead-key";
    params[0] = OSSL_PARAM_construct_utf8_string(OSSL_KDF_PARAM_DIGEST, digest, 0);
    params[1] = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_KEY, ikm, sizeof ikm);
    params[2] = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_SALT, salt, sizeof salt - 1);
    params[3] = OSSL_PARAM_construct_octet_string(OSSL_KDF_PARAM_INFO, info, sizeof info - 1);
    params[4] = OSSL_PARAM_construct_end();
    int ok = EVP_KDF_derive(kc, key, LS_KEY_LEN, params) == 1;
    EVP_KDF_CTX_free(kc);
    OPENSSL_cleanse(ikm, sizeof ikm);
    return ok ? 0 : -1;
}

pqs_status pqs_seal(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],
                    const uint8_t *pt, size_t pt_len, uint8_t **out, size_t *out_len) {
    if (k == NULL || wrap == NULL || out == NULL || out_len == NULL || (pt == NULL && pt_len != 0))
        return PQS_ERR_NULL_ARG;
    *out = NULL; *out_len = 0;
    if (pt_len > LS_MAX_PLAINTEXT) return PQS_ERR_TOO_LARGE;

    EVP_PKEY_CTX *c = EVP_PKEY_CTX_new_from_pkey(NULL, k->pkey, NULL);
    if (c == NULL) return PQS_ERR_CRYPTO;
    size_t ctl = 0, ssl = 0;
    uint8_t ct[PQS_CT_LEN], ss[PQS_SS_LEN];
    int ok = EVP_PKEY_encapsulate_init(c, NULL) == 1
          && EVP_PKEY_encapsulate(c, NULL, &ctl, NULL, &ssl) == 1
          && ctl == PQS_CT_LEN && ssl == PQS_SS_LEN
          && EVP_PKEY_encapsulate(c, ct, &ctl, ss, &ssl) == 1;
    EVP_PKEY_CTX_free(c);
    if (!ok) return PQS_ERR_CRYPTO;

    uint8_t key[LS_KEY_LEN];
    int dk = derive_key(ss, wrap, key);
    OPENSSL_cleanse(ss, sizeof ss);
    if (dk != 0) return PQS_ERR_CRYPTO;

    uint8_t *body = NULL;
    size_t blen = 0;
    ls_status ls = ls_seal(key, LS_AEAD_CHACHA20_POLY1305, pt, pt_len, &body, &blen);
    OPENSSL_cleanse(key, sizeof key);
    if (ls != LS_OK) return ls == LS_ERR_OOM ? PQS_ERR_OOM : PQS_ERR_CRYPTO;

    size_t total = PQS_MAGIC_LEN + PQS_CT_LEN + blen;
    if (total < blen) { ls_free(body, blen); return PQS_ERR_TOO_LARGE; }
    uint8_t *blob = (uint8_t *)malloc(total);
    if (blob == NULL) { ls_free(body, blen); return PQS_ERR_OOM; }
    memcpy(blob, PQS_MAGIC, PQS_MAGIC_LEN);
    memcpy(blob + PQS_MAGIC_LEN, ct, PQS_CT_LEN);
    memcpy(blob + PQS_MAGIC_LEN + PQS_CT_LEN, body, blen);
    ls_free(body, blen);
    *out = blob; *out_len = total;
    return PQS_OK;
}

pqs_status pqs_open(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],
                    const uint8_t *in, size_t in_len, uint8_t **out, size_t *out_len) {
    if (k == NULL || wrap == NULL || in == NULL || out == NULL || out_len == NULL)
        return PQS_ERR_NULL_ARG;
    *out = NULL; *out_len = 0;
    if (in_len < PQS_MAGIC_LEN + PQS_CT_LEN + LS_OVERHEAD
        || memcmp(in, PQS_MAGIC, PQS_MAGIC_LEN) != 0)
        return PQS_ERR_FORMAT;

    EVP_PKEY_CTX *c = EVP_PKEY_CTX_new_from_pkey(NULL, k->pkey, NULL);
    if (c == NULL) return PQS_ERR_CRYPTO;
    uint8_t ss[PQS_SS_LEN];
    size_t ssl = sizeof ss;
    /* ML-KEM decapsulation never fails on a wrong ciphertext (implicit rejection): it yields a
     * pseudo-random secret, so the AEAD tag below is what reports the mismatch. */
    int ok = EVP_PKEY_decapsulate_init(c, NULL) == 1
          && EVP_PKEY_decapsulate(c, ss, &ssl, in + PQS_MAGIC_LEN, PQS_CT_LEN) == 1
          && ssl == PQS_SS_LEN;
    EVP_PKEY_CTX_free(c);
    if (!ok) return PQS_ERR_AUTH;

    uint8_t key[LS_KEY_LEN];
    int dk = derive_key(ss, wrap, key);
    OPENSSL_cleanse(ss, sizeof ss);
    if (dk != 0) return PQS_ERR_CRYPTO;

    uint8_t *pt = NULL;
    size_t ptl = 0;
    ls_status ls = ls_open(key, in + PQS_MAGIC_LEN + PQS_CT_LEN,
                           in_len - PQS_MAGIC_LEN - PQS_CT_LEN, &pt, &ptl);
    OPENSSL_cleanse(key, sizeof key);
    if (ls == LS_ERR_FORMAT) return PQS_ERR_FORMAT;
    if (ls == LS_ERR_OOM) return PQS_ERR_OOM;
    if (ls != LS_OK) return PQS_ERR_AUTH;
    *out = pt; *out_len = ptl;
    return PQS_OK;
}
