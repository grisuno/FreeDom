#ifndef FREEDOM_WEBFONT_LOAD_H
#define FREEDOM_WEBFONT_LOAD_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * webfont_load — trusted-side @font-face fetch-and-register pass (spec/webfont.md).
 *
 * The parent (GUI/headless) collects candidate stylesheets, resolves each
 * reference, downloads it through its own policy-gated fetcher and registers
 * the validated bytes with text_shape. The worker never touches font bytes;
 * the loader never touches the network directly (the fetch callback does).
 *
 * Everything fails closed per face, fail-open per page: one bad face never
 * breaks the load, and an empty registry renders exactly the fallback stack.
 */

/* One collected stylesheet: text plus the URL it was fetched from (the
 * resolution base for its relative font URLs; inline <style> uses page_url). */
typedef struct wf_sheet {
    const char *text;
    size_t      len;
    const char *url;
} wf_sheet;

/* GETs an absolute URL. Returns 0 with malloc'd body/ctype (caller frees via
 * free()), *out_status the HTTP status. Nonzero on refusal/error (fail-closed:
 * the face is skipped, never the page). Implemented by the parent around its
 * own policy-gated fetcher. */
typedef int (*wf_fetch_fn)(void *ctx, const char *url,
                           int *out_status, char **out_body, size_t *out_len,
                           char **out_ctype);

/* Full document pass. Scans extern sheets in order, then inline <style> bodies
 * in document order (matching the worker sheet order extern-then-inline), picks
 * the first supported format per (family, bold, italic) with in-list fallback
 * (up to WF_LOAD_TRIES_PER_KEY URLs per key), resolves each URL (data: decoded
 * locally, https absolute or https-resolved; anything else skipped), GETs it
 * through fetch, checks status/ctype/size caps and registers the magic-valid
 * bytes. fetch == NULL (untrusted page): no-op, returns -1 without touching
 * anything. page_url == NULL (local file) still runs in data:-only mode: data:
 * faces decode locally, absolute https goes through the fetch gate, relative
 * URLs are skipped (no base). Returns faces registered (>= 0) otherwise. */
int wf_load_document(wf_fetch_fn fetch, void *fctx, const char *page_url,
                     const wf_sheet *extern_sheets, size_t nextern,
                     const char *html, size_t html_len);

#define WF_LOAD_TRIES_PER_KEY 4
#define WF_LOAD_MAX_KEYS      256
#define WF_LOAD_MAX_FETCHES   32

#endif /* FREEDOM_WEBFONT_LOAD_H */
