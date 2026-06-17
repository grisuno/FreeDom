#ifndef FREEDOM_PAGE_VIEW_H
#define FREEDOM_PAGE_VIEW_H

#include <stddef.h>
#include <stdint.h>

#include "html_parse.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * page_view — a flat, inert "display list" extracted from the inert DOM.
 *
 * The renderer must not walk the hostile DOM directly, and plain text loses the
 * structure a reader needs (headings, links, block boundaries). page_view turns
 * the sanitised tree into an ordered list of inline runs carrying just enough
 * structure to lay out and paint: a kind (text or link), a heading level, a
 * block-break flag, the run text, and a link target.
 *
 * It is data with provenance, never instruction: a link's href is stored but
 * never followed here; navigation re-validates it through secure_fetch.
 *
 * Run text is normalised to well-formed UTF-8 (invalid bytes -> '?') so the text
 * renderer can never be poisoned by a malformed or legacy-encoded document.
 *
 * The Lexbor backend stays encapsulated: no lxb_* type appears here.
 * See spec/page_view.md for the full contract.
 */

typedef enum pv_status {
    PV_OK = 0,
    PV_ERR_NULL_ARG,  /* a required pointer argument was NULL */
    PV_ERR_OOM,       /* allocation failed */
    PV_ERR_INTERNAL   /* backend returned an unexpected state */
} pv_status;

typedef enum pv_kind {
    PV_TEXT = 0,   /* inline text */
    PV_LINK = 1,   /* inline text that is a hyperlink (href is set) */
    PV_IMAGE = 2   /* an <img>: src is set, text holds the alt text */
} pv_kind;

/* One inline run in document order. text is owned, NUL-terminated, valid UTF-8
 * (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated
 * for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for PV_IMAGE
 * runs (the image URL, data with provenance, never fetched here), NULL otherwise;
 * img_w/img_h carry the declared <img> dimensions in pixels, or -1 when unknown.
 * An image is never a link, so href and src are never both set. */
typedef struct pv_run {
    pv_kind kind;
    int     heading;      /* 0 = body text; 1..6 = inside h1..h6 */
    int     block_break;  /* nonzero: a block boundary precedes this run */
    char   *text;
    char   *href;
    char   *src;          /* PV_IMAGE only: image URL; NULL otherwise */
    int     img_w;        /* PV_IMAGE declared width in px, or -1 if unknown */
    int     img_h;        /* PV_IMAGE declared height in px, or -1 if unknown */
} pv_run;

typedef struct pv_view {
    pv_run *runs;
    size_t  count;
    size_t  cap;
} pv_view;

/* Builds the display list from an already-parsed, sanitised document.
 * doc == NULL / out == NULL => PV_ERR_NULL_ARG.
 * On PV_OK, *out must be released with pv_free. An empty document yields a valid
 * view with count == 0. */
pv_status pv_build(const hp_document *doc, pv_view **out);

/* Allocates an empty view (used by the IPC deserialiser to rebuild a view on the
 * receiving side). Returns NULL on allocation failure. */
pv_view *pv_new(void);

/* Appends one text or link run, copying text (required) and href (NULL for
 * non-links). text is normalised to valid UTF-8; the image fields are cleared
 * (src=NULL, img_w=img_h=-1). Returns PV_OK or PV_ERR_OOM / PV_ERR_NULL_ARG. */
pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    const char *text, const char *href);

/* Appends one PV_IMAGE run. src is required (an image with no source is not
 * representable); alt may be NULL (stored as the empty string). Both alt and src
 * are copied and normalised to valid UTF-8 so they are safe to paint. w/h are the
 * declared dimensions, or -1 when unknown. Returns PV_OK or PV_ERR_OOM /
 * PV_ERR_NULL_ARG. */
pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          const char *alt, const char *src, int w, int h);

/* Idempotent; safe on NULL and safe to call twice. */
void pv_free(pv_view *v);

/* Read accessors. NULL-safe. */
size_t        pv_count(const pv_view *v);
const pv_run *pv_at(const pv_view *v, size_t i);

#endif /* FREEDOM_PAGE_VIEW_H */
