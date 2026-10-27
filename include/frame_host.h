#ifndef FREEDOM_FRAME_HOST_H
#define FREEDOM_FRAME_HOST_H

#include <stddef.h>

#include "tab.h"
#include "page_view.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * frame_host -- trusted-parent side of iframes: one confined worker tab per frame, messages
 * routed with frame_broker. See spec/frame_broker.md section 4.
 */

#define FH_MAX_DEPTH 8     /* nested deliveries handled inside one call; the rest waits for a tick */

typedef struct fh_host fh_host;

/* Delivers a routed message ("senderOrigin\nrelation\nJSON") into the TOP document. */
typedef void (*fh_top_msg_fn)(void *ctx, const char *data, size_t len);

/* top_url: the trusted top document; fetch/fetch_ctx: the page's policy-gated subresource fetcher
 * (used for the frame document and handed to each frame worker for its own XHR/fetch). NULL on OOM
 * or bad args. */
fh_host *fh_new(const char *top_url, tab_fetch_fn fetch, void *fetch_ctx,
                fh_top_msg_fn top_msg, void *top_ctx);

/* Closes every frame worker and frees the host. Idempotent on NULL. */
void fh_free(fh_host *h);

/* Processes the frame ops (kinds FRAME_OPEN/CLOSE/POST) among page->ws of the TOP document; other
 * kinds are ignored. */
void fh_apply_top(fh_host *h, const tab_page *page);

/* Advances every frame's virtual clock by elapsed_ms and processes what they posted. Returns the
 * smallest pending frame timer in ms, or -1 when none. */
int fh_tick(fh_host *h, int elapsed_ms);

/* Number of live frame workers (excludes the top). */
int fh_count(const fh_host *h);

/* Painting (spec/frame_broker.md section 5). The document of the frame loaded from `url`, as its
 * confined worker last built it (NULL when no live frame has that URL); *t_out (optional) is that
 * worker, which decodes the frame's own images. Both stay owned by the host and are valid until the
 * next fh_apply_top/fh_tick/fh_free. */
const pv_view *fh_frame_view(const fh_host *h, const char *url, tab **t_out);

/* Changes whenever any frame view appears, is replaced or goes away: repaint the frames then. */
unsigned fh_generation(const fh_host *h);

#endif /* FREEDOM_FRAME_HOST_H */
