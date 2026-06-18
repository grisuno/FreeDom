/*
 * render_doc — implementation: pure, I/O-free transform from an inert page_view
 * display list (plus render capabilities) into a flat, paint-ready block list.
 *
 * No network, no backend types, no global state. Every string copied into the
 * document is normalised to valid UTF-8 so the presentation layer (cairo, which
 * rejects invalid UTF-8) can never be poisoned by a hostile or legacy-encoded
 * page. Image blocks carry the render_policy decision; the tracking warning is
 * prepended whenever the page declares images while the capability is off.
 */

#include "render_doc.h"

#include <stdlib.h>
#include <string.h>

/* UTF-8 sanitisation, kept local so render_doc stays self-contained (matching
 * the convention in browser.c and page_view.c). Output is never longer than the
 * input. */

static size_t utf8_seq_len(unsigned char c) {
    if (c < 0x80) return 1;
    if (c >= 0xC2 && c <= 0xDF) return 2;
    if (c >= 0xE0 && c <= 0xEF) return 3;
    if (c >= 0xF0 && c <= 0xF4) return 4;
    return 0;
}

static char *utf8_sanitized_dup(const char *s) {
    if (s == NULL) return NULL;
    size_t n = strlen(s);
    char *d = (char *)malloc(n + 1);
    if (d == NULL) return NULL;
    size_t i = 0, o = 0;
    while (i < n) {
        unsigned char c = (unsigned char)s[i];
        size_t L = utf8_seq_len(c);
        int ok = (L >= 1 && i + L <= n);
        for (size_t k = 1; ok && k < L; ++k) {
            if (((unsigned char)s[i + k] & 0xC0) != 0x80) ok = 0;
        }
        if (ok && L == 3 && c == 0xE0 && (unsigned char)s[i + 1] < 0xA0) ok = 0;
        if (ok && L == 3 && c == 0xED && (unsigned char)s[i + 1] > 0x9F) ok = 0;
        if (ok && L == 4 && c == 0xF0 && (unsigned char)s[i + 1] < 0x90) ok = 0;
        if (ok && L == 4 && c == 0xF4 && (unsigned char)s[i + 1] > 0x8F) ok = 0;
        if (ok) {
            for (size_t k = 0; k < L; ++k) d[o++] = s[i + k];
            i += L;
        } else {
            d[o++] = '?';
            i += 1;
        }
    }
    d[o] = '\0';
    return d;
}

/* Appends one block, taking owned copies of text (required) and href (optional).
 * Returns 0 on success, -1 on allocation failure (the doc is left consistent). */
static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,
                   const char *text, const char *href, rdp_img_decision dec, int fg_rgb) {
    if (d->count == d->cap) {
        size_t ncap = d->cap ? d->cap * 2 : 16;
        rd_block *grown = (rd_block *)realloc(d->blocks, ncap * sizeof *grown);
        if (grown == NULL) return -1;
        d->blocks = grown;
        d->cap = ncap;
    }

    char *t = utf8_sanitized_dup(text != NULL ? text : "");
    if (t == NULL) return -1;
    char *h = NULL;
    if (href != NULL) {
        h = utf8_sanitized_dup(href);
        if (h == NULL) { free(t); return -1; }
    }

    rd_block *b = &d->blocks[d->count++];
    b->kind = kind;
    b->heading_level = heading_level;
    b->block_break = block_break;
    b->text = t;
    b->href = h;
    b->img_decision = dec;
    b->fg_rgb = fg_rgb;
    return 0;
}

rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_url, rd_doc **out) {
    if (out == NULL) return RD_ERR_NULL_ARG;
    *out = NULL;

    rd_doc *d = (rd_doc *)calloc(1, sizeof *d);
    if (d == NULL) return RD_ERR_OOM;

    size_t n = pv_count(view);
    for (size_t i = 0; i < n; ++i) {
        if (pv_at(view, i)->kind == PV_IMAGE) { d->has_images = 1; break; }
    }

    /* The user is always told when a page wants to load images while the
     * capability is off (the default). */
    if (d->has_images && !caps.images) {
        if (rd_push(d, RD_NOTICE, 0, 1, rdp_images_warning(), NULL, RDP_IMG_ALLOW, -1) != 0) {
            rd_free(d);
            return RD_ERR_OOM;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        const pv_run *r = pv_at(view, i);
        /* Author colors are presentation: applied only when author CSS is enabled
         * (Privacy/Secure by Default off). Inline text color reveals nothing to the
         * network, so it is safe to honor once the user opts in. */
        int fg = (caps.css && r->fg_rgb >= 0) ? r->fg_rgb : -1;
        int rc;
        switch (r->kind) {
            case PV_IMAGE: {
                rdp_img_decision dec = rdp_image_decision(caps, top_level_url, r->src,
                                                          r->img_w, r->img_h);
                rc = rd_push(d, RD_IMAGE, 0, r->block_break, r->text, r->src, dec, -1);
                break;
            }
            case PV_LINK:
                rc = rd_push(d, RD_LINK, r->heading, r->block_break, r->text, r->href,
                             RDP_IMG_ALLOW, fg);
                break;
            case PV_TEXT:
            default:
                rc = rd_push(d, r->heading > 0 ? RD_HEADING : RD_PARAGRAPH,
                             r->heading, r->block_break, r->text, NULL, RDP_IMG_ALLOW, fg);
                break;
        }
        if (rc != 0) { rd_free(d); return RD_ERR_OOM; }
    }

    *out = d;
    return RD_OK;
}

void rd_free(rd_doc *d) {
    if (d == NULL) return;
    for (size_t i = 0; i < d->count; ++i) {
        free(d->blocks[i].text);
        free(d->blocks[i].href);
    }
    free(d->blocks);
    free(d);
}

size_t rd_count(const rd_doc *d) {
    return (d != NULL) ? d->count : 0;
}

const rd_block *rd_at(const rd_doc *d, size_t i) {
    if (d == NULL || i >= d->count) return NULL;
    return &d->blocks[i];
}

const char *rd_kind_name(rd_kind k) {
    switch (k) {
        case RD_HEADING:   return "heading";
        case RD_PARAGRAPH: return "paragraph";
        case RD_LINK:      return "link";
        case RD_IMAGE:     return "image";
        case RD_NOTICE:    return "notice";
    }
    return "block";
}

const char *rd_image_label(rdp_img_decision d) {
    switch (d) {
        case RDP_IMG_ALLOW:          return "image (allowed)";
        case RDP_IMG_BLOCK_DISABLED: return "image blocked: images disabled";
        case RDP_IMG_BLOCK_INVALID:  return "image blocked: invalid URL";
        case RDP_IMG_BLOCK_SCHEME:   return "image blocked: non-https";
        case RDP_IMG_BLOCK_TRACKER:  return "image blocked: tracking pixel";
    }
    return "image";
}
