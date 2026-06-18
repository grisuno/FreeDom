#ifndef FREEDOM_FORM_H
#define FREEDOM_FORM_H

#include <stddef.h>

#include "url.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * form — pure construction of an HTML form submission.
 *
 * From the page URL, a form's raw action href, the method and the named controls
 * with their current values, it decides WHAT request a submit represents:
 * navigate (GET), send a body (POST), or block. No sockets: it only builds the
 * plan, which the orchestrator runs through secure_fetch (which re-applies the
 * full TLS/PQ policy, Zero Trust).
 *
 * Secure by Default / fail closed: a non-https resolved target is not a
 * representable submission (FM_BLOCKED). The action/names/values are hostile data
 * with provenance: encoded and resolved, never executed. Reuses the canonical url
 * module so "what is a valid https target" lives in one tested place.
 *
 * See spec/form.md for the full contract.
 */

#define FM_URL_MAX    URL_MAX_LEN /* 2048; bound on the resulting URL */
#define FM_BODY_MAX   4096u       /* bound on the POST body / encoded GET query */
#define FM_MAX_FIELDS 64u         /* bound on controls per submission (anti-amplification) */

typedef enum fm_method { FM_GET = 0, FM_POST } fm_method;

/* One named control. value == NULL is treated as the empty value; name == NULL is
 * skipped by fm_encode and rejected (FM_BLOCK_INVALID) by fm_build. */
typedef struct fm_field { const char *name; const char *value; } fm_field;

typedef enum fm_kind {
    FM_NAVIGATE = 0,  /* GET: navigate to url */
    FM_POST_REQUEST,  /* POST: send body (body_len) to url with content_type */
    FM_BLOCKED        /* not securely submittable (fails closed) */
} fm_kind;

typedef enum fm_block_reason {
    FM_BLOCK_NONE = 0,
    FM_BLOCK_INSECURE, /* resolved target is not https (downgrade / foreign scheme / local base) */
    FM_BLOCK_OVERFLOW, /* encoded data or URL did not fit */
    FM_BLOCK_INVALID   /* too many fields, or a field with a NULL name */
} fm_block_reason;

typedef struct fm_plan {
    fm_kind         kind;
    fm_block_reason reason;       /* meaningful only when kind == FM_BLOCKED */
    char            url[FM_URL_MAX];
    char            body[FM_BODY_MAX];
    size_t          body_len;     /* bytes in body, excluding the NUL (0 for GET) */
    const char     *content_type; /* static string for FM_POST_REQUEST; NULL otherwise */
} fm_plan;

typedef enum fm_status {
    FM_OK = 0,
    FM_ERR_NULL_ARG,
    FM_ERR_OVERFLOW
} fm_status;

/* Static content type used for FM_POST_REQUEST plans. */
extern const char FM_CONTENT_TYPE_URLENCODED[];

/* Serialises the named pairs as application/x-www-form-urlencoded into out
 * (NUL-terminated). On overflow, out is left as the empty string (no partial
 * encoding) and FM_ERR_OVERFLOW is returned. fields/out NULL (with n > 0) or
 * outsz == 0 => FM_ERR_NULL_ARG. *out_len (if non-NULL) receives the length. */
fm_status fm_encode(const fm_field *fields, size_t n,
                    char *out, size_t outsz, size_t *out_len);

/* Builds a submission plan. base is the page URL (must be https for a relative
 * action); action is the raw form action href (NULL/"" => submit to base). Always
 * yields a plan on FM_OK; kind == FM_BLOCKED with a reason when it cannot submit
 * securely. base == NULL / out == NULL => FM_ERR_NULL_ARG. */
fm_status fm_build(const char *base, const char *action, fm_method method,
                   const fm_field *fields, size_t n, fm_plan *out);

#endif /* FREEDOM_FORM_H */
