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

#include "url.h"

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
                   const char *text, const char *href, rdp_img_decision dec,
                   int fg_rgb, int bg_rgb) {
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
    b->bold = 0;
    b->italic = 0;
    b->indent = 0;
    b->block_break = block_break;
    b->text = t;
    b->href = h;
    b->img_decision = dec;
    b->fg_rgb = fg_rgb;
    b->bg_rgb = bg_rgb;
    b->text_align = 0;
    b->font_scale = 0;
    b->line_scale = 0;
    b->text_decoration = -1;
    b->cont_id = -1;
    b->cont_display = 0;
    b->cont_gap = 0;
    b->cont_justify = 0;
    b->cont_cols = 0;
    b->box_l = 0;
    b->box_r = 0;
    b->box_w = 0;
    b->box_center = 0;
    b->box_mt = PV_LEN_UNSET;
    b->box_mb = PV_LEN_UNSET;
    b->input_type = 0;
    b->name = NULL;
    b->value = NULL;
    b->form_id = -1;
    b->form_method = 0;
    return 0;
}

/* Appends an RD_INPUT block, copying text (placeholder/label), the form action
 * (href), and the control name/value. Returns 0, or -1 on allocation failure. */
static int rd_push_input(rd_doc *d, int block_break, const pv_run *r) {
    if (rd_push(d, RD_INPUT, 0, block_break, r->text, r->href, RDP_IMG_ALLOW, -1, -1) != 0)
        return -1;
    rd_block *b = &d->blocks[d->count - 1];
    b->input_type = r->input_type;
    b->form_id = r->form_id;
    b->form_method = r->form_method;
    if (r->name != NULL) {
        b->name = utf8_sanitized_dup(r->name);
        if (b->name == NULL) return -1;
    }
    if (r->value != NULL) {
        b->value = utf8_sanitized_dup(r->value);
        if (b->value == NULL) return -1;
    }
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
        if (rd_push(d, RD_NOTICE, 0, 1, rdp_images_warning(), NULL, RDP_IMG_ALLOW, -1, -1) != 0) {
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
        int bg = (caps.css && r->bg_rgb >= 0) ? r->bg_rgb : -1;
        int rc;
        switch (r->kind) {
            case PV_IMAGE: {
                /* Resolve a (possibly relative) image src against the page URL before
                 * judging it: a relative "/logo.png" is NOT an invalid URL, it resolves
                 * against the top-level document. The policy decision and the later
                 * fetch must both act on the real absolute URL, or every relative image
                 * (the common case) would be blocked as "invalid URL". */
                char resolved[URL_MAX_LEN + 1];
                const char *img_url = r->src;
                rdp_img_decision dec;
                if (top_level_url != NULL && url_is_file(top_level_url)) {
                    /* Local (file://) page: only same-subtree LOCAL images load. A
                     * remote, foreign-scheme or "../"-escaping src fails closed (no
                     * phone-home, no reading files outside the document directory).
                     * url_resolve_file enforces the confinement. */
                    if (!caps.images) {
                        dec = RDP_IMG_BLOCK_DISABLED;
                    } else if (r->src != NULL &&
                               url_resolve_file(top_level_url, r->src,
                                                resolved, sizeof resolved) == URL_OK) {
                        img_url = resolved;
                        dec = rdp_is_tracking_pixel(r->img_w, r->img_h)
                                  ? RDP_IMG_BLOCK_TRACKER : RDP_IMG_ALLOW;
                    } else {
                        dec = RDP_IMG_BLOCK_SCHEME;
                    }
                } else {
                    /* Remote (https) pipeline. On failure (data:/javascript:/no base)
                     * the raw src is kept and fails closed in rdp_image_decision. */
                    if (top_level_url != NULL && r->src != NULL
                        && url_resolve_https(top_level_url, r->src, resolved,
                                             sizeof resolved) == URL_OK) {
                        img_url = resolved;
                    }
                    dec = rdp_image_decision(caps, top_level_url, img_url,
                                             r->img_w, r->img_h);
                }
                rc = rd_push(d, RD_IMAGE, 0, r->block_break, r->text, img_url, dec, -1, -1);
                break;
            }
            case PV_INPUT:
                rc = rd_push_input(d, r->block_break, r);
                break;
            case PV_LINK:
                rc = rd_push(d, RD_LINK, r->heading, r->block_break, r->text, r->href,
                             RDP_IMG_ALLOW, fg, bg);
                break;
            case PV_TEXT:
            default:
                rc = rd_push(d, r->heading > 0 ? RD_HEADING : RD_PARAGRAPH,
                             r->heading, r->block_break, r->text, NULL, RDP_IMG_ALLOW, fg, bg);
                break;
        }
        if (rc != 0) { rd_free(d); return RD_ERR_OOM; }

        /* Author flex/grid container layout is structure, not author styling: it
         * reveals nothing to the network (no fetch, no fingerprint), so the box
         * model and column layout apply by default, decoupled from caps.css (which
         * still gates author *colors* above). Carried only on text/link blocks (the
         * flex content this engine groups). */
        if ((r->kind == PV_TEXT || r->kind == PV_LINK) && d->count > 0) {
            rd_block *lb = &d->blocks[d->count - 1];
            lb->bold = r->bold;
            lb->italic = r->italic;
            lb->indent = r->indent;
            /* Author text-align/font-size are presentation, gated by caps.css like
             * the colors above (they reveal nothing to the network, but Privacy by
             * Default keeps author styling off until the user opts in). */
            lb->text_align = caps.css ? r->text_align : 0;
            lb->font_scale = (caps.css && r->font_scale > 0) ? r->font_scale : 0;
            lb->line_scale = (caps.css && r->line_scale > 0) ? r->line_scale : 0;
            lb->text_decoration = caps.css ? r->text_decoration : -1;
            lb->cont_id = r->cont_id;
            lb->cont_display = r->cont_display;
            lb->cont_gap = r->cont_gap;
            lb->cont_justify = r->cont_justify;
            lb->cont_cols = r->cont_cols;
            /* Author box model is presentation (it can shrink content to
             * unreadability), so it is gated by caps.css like the colors above. */
            if (caps.css) {
                lb->box_l = r->box_l;
                lb->box_r = r->box_r;
                lb->box_w = r->box_w;
                lb->box_center = r->box_center;
                lb->box_mt = r->box_mt;
                lb->box_mb = r->box_mb;
            }
        }
    }

    *out = d;
    return RD_OK;
}

void rd_free(rd_doc *d) {
    if (d == NULL) return;
    for (size_t i = 0; i < d->count; ++i) {
        free(d->blocks[i].text);
        free(d->blocks[i].href);
        free(d->blocks[i].name);
        free(d->blocks[i].value);
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
        case RD_INPUT:     return "input";
    }
    return "block";
}

const char *rd_block_tag(const rd_block *b) {
    if (b == NULL) return NULL;
    switch (b->kind) {
        case RD_HEADING: {
            int lvl = b->heading_level;
            if (lvl < 1) lvl = 1;
            if (lvl > 6) lvl = 6;
            static const char *const H[6] = { "h1", "h2", "h3", "h4", "h5", "h6" };
            return H[lvl - 1];
        }
        case RD_PARAGRAPH: return "p";
        case RD_LINK:      return "a";
        case RD_IMAGE:     return "img";
        case RD_INPUT:
            switch (b->input_type) {
                case PV_IN_TEXTAREA: return "textarea";
                case PV_IN_SUBMIT:
                case PV_IN_BUTTON:   return "button";
                default:             return "input";
            }
        case RD_NOTICE:    return NULL;
    }
    return NULL;
}

const char *rd_input_label(int input_type) {
    switch (input_type) {
        case PV_IN_TEXT:     return "text";
        case PV_IN_PASSWORD: return "password";
        case PV_IN_TEXTAREA: return "textarea";
        case PV_IN_HIDDEN:   return "hidden";
        case PV_IN_SUBMIT:   return "submit";
        case PV_IN_BUTTON:   return "button";
    }
    return "field";
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
