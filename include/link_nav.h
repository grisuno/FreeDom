#ifndef FREEDOM_LINK_NAV_H
#define FREEDOM_LINK_NAV_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * link_nav — pure navigation policy for a clicked hyperlink.
 *
 * Given the current page location and a document's raw href, decides what a
 * click should do: navigate to a resolved target, stay on the same document
 * (fragment), or block (fail closed). No I/O: it produces a decision the GUI
 * orchestrator executes (hit-test -> ln_resolve -> load). The link is hostile
 * data with provenance, never an instruction.
 *
 * Reuses the pure url module for https resolution (the same rule a redirect
 * follows) and for "." / ".." collapsing in local file paths.
 *
 * Secure by Default: only https (and a local file under a local base) is
 * navigable; http downgrade and javascript:/data:/file:/mailto: are blocked.
 * The real network policy (third parties, TLS/PQ) is enforced by secure_fetch at
 * load time; this module only decides navigability.
 *
 * See spec/link_nav.md for the full contract.
 */

/* Fits an https URL (<= URL_MAX_LEN) or a local filesystem path (PATH_MAX). */
#define LN_MAX_TARGET 4096u

typedef enum ln_action {
    LN_NAVIGATE = 0,    /* load out->target */
    LN_SAME_DOCUMENT,   /* empty href or fragment (#...): same page, do not reload */
    LN_BLOCKED          /* unsupported/unsafe reference: do not navigate */
} ln_action;

typedef enum ln_target_kind {
    LN_TARGET_NONE = 0,
    LN_TARGET_HTTPS,    /* target is an absolute https URL */
    LN_TARGET_FILE      /* target is a local filesystem path */
} ln_target_kind;

typedef struct ln_result {
    ln_action      action;
    ln_target_kind kind;                /* meaningful only when action == LN_NAVIGATE */
    char           target[LN_MAX_TARGET]; /* resolved destination; "" unless NAVIGATE */
} ln_result;

typedef enum ln_status {
    LN_OK = 0,
    LN_ERR_NULL_ARG   /* out was NULL */
} ln_status;

/* Decides what clicking href on the page located at base should do.
 *   base — current page location: "https://...", a local file path, or NULL.
 *   href — the raw link target from the document (may carry surrounding/embedded
 *          whitespace); NULL is treated as blocked.
 *   out  — fully populated on LN_OK; out == NULL => LN_ERR_NULL_ARG.
 * Fails closed: anything not provably safe to navigate yields LN_BLOCKED. */
ln_status ln_resolve(const char *base, const char *href, ln_result *out);

#endif /* FREEDOM_LINK_NAV_H */
