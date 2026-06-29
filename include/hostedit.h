#ifndef FREEDOM_HOSTEDIT_H
#define FREEDOM_HOSTEDIT_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * hostedit — pure helpers for editing the user's /etc/hosts-format lists
 * (block.conf / allow.conf / js.conf) from the UI.
 *
 * The host to add comes from the current page's URL, so it is data with
 * provenance: hostedit validates it fail-closed (it must be a plausible
 * registrable hostname, never a path/scheme/garbage) and produces the exact line
 * to append. The I/O (reading the file, the atomic append, reloading the in-memory
 * filter) is the orchestrator's job; this module is the directly-auditable,
 * I/O-free decision of "what text, if any, gets written."
 *
 * See spec/hostedit.md for the full contract.
 */

typedef enum he_status {
    HE_OK = 0,
    HE_ERR_NULL_ARG,      /* a required argument was NULL */
    HE_ERR_INVALID_HOST,  /* host is not a plausible registrable hostname */
    HE_ERR_RANGE          /* output buffer too small for the line */
} he_status;

/* Maximum hostname length written (DNS limit). */
#define HE_MAX_HOST 253

/* Validates host and writes the hosts-format line "<host>\n" (host lowercased) to
 * out. A valid host is 1..HE_MAX_HOST bytes of [A-Za-z0-9.-], split into dot-
 * separated labels each 1..63 bytes, no label empty (so "a..b" is rejected) and no
 * label starting or ending with '-'. Anything carrying a scheme, '/', ':', '@',
 * '?', '#', whitespace or a control byte is rejected (fail-closed). On HE_OK, out is
 * NUL-terminated. cap must hold the host + "\n" + NUL. */
he_status he_make_line(const char *host, char *out, size_t cap);

/* Returns 1 if text (the body of a hosts-format file) already lists host as a domain
 * token on a non-comment line (case-insensitive; a leading IP token like "0.0.0.0"
 * is ignored, matching hostblock), else 0. NULL args -> 0. Lets the orchestrator
 * skip a duplicate append. */
int he_text_has_host(const char *text, const char *host);

/* Omnibar autocomplete: treats allow.conf (a hosts-format text) as a favorites list.
 * Fills results[0..max) with up to max distinct domain tokens of text that match
 * query case-insensitively -- PREFIX matches first (document order), then non-prefix
 * SUBSTRING matches. query "" matches everything (favorites browsing). Each result is
 * lowercased and NUL-terminated; hosts longer than HE_MAX_HOST are skipped. results
 * is a caller array results[max][HE_MAX_HOST+1]. Returns the count written. Pure (no
 * allocation, no I/O). NULL args / max <= 0 -> 0. */
int he_suggest(const char *text, const char *query,
               char results[][HE_MAX_HOST + 1], int max);

#endif /* FREEDOM_HOSTEDIT_H */
