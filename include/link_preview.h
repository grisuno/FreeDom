#ifndef FREEDOM_LINK_PREVIEW_H
#define FREEDOM_LINK_PREVIEW_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

#include <stddef.h>

/*
 * link_preview -- what the status strip says about the link under the pointer.
 *
 * Pure (no I/O, no Cairo, no state). The decision is always ln_resolve's: the preview
 * shows the resolved destination a click would load, the page URL + fragment for a
 * same-document link, or "Blocked (<reason>): <href>" for a link the click refuses.
 * Every byte outside printable ASCII is written %XX, so a hostile href cannot hide a
 * bidi override, a control byte or a homograph from the user. See spec/link_preview.md.
 */

/* Upper bound of lp_preview.text including its NUL: what a one-line strip can show. */
#define LP_TEXT_MAX 512u

typedef enum lp_kind {
    LP_NAVIGATE = 0,
    LP_SAME_DOCUMENT,
    LP_BLOCKED
} lp_kind;

typedef struct lp_preview {
    lp_kind kind;
    char    text[LP_TEXT_MAX];
    size_t  host_off;   /* host span inside text (for emphasis); host_len 0 = none */
    size_t  host_len;
} lp_preview;

typedef enum lp_status {
    LP_OK = 0,
    LP_EINVAL
} lp_status;

/* Describes clicking href on the page at base (an https URL, a local path or NULL). */
lp_status lp_describe(const char *base, const char *href, lp_preview *out);

#endif /* FREEDOM_LINK_PREVIEW_H */
