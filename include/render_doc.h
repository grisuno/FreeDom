#ifndef FREEDOM_RENDER_DOC_H
#define FREEDOM_RENDER_DOC_H

#include <stddef.h>

#include "page_view.h"
#include "render_policy.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * render_doc — turns a page_view display list plus the page's render
 * capabilities into a flat, paint-ready document of styled blocks.
 *
 * Pure, I/O-free policy/shape logic: the directly auditable layer between the
 * inert display list (page_view) and the presentation orchestrator (the GUI and
 * the --headless writer). It decides WHAT to show and HOW to label it (a semantic
 * style plus, for images, the render_policy decision); it never produces pixels,
 * fonts or colours, which belong to the presentation layer.
 *
 * Both orchestrators consume the same rd_doc, so the "this is a heading / this is
 * a blocked tracking image / warn the user about images" rules live in exactly
 * one tested place. See spec/render_doc.md for the full contract.
 */

typedef enum rd_kind {
    RD_HEADING = 0,   /* heading text; heading_level is 1..6 */
    RD_PARAGRAPH,     /* body text */
    RD_LINK,          /* hyperlink text; href is the target */
    RD_IMAGE,         /* image placeholder; href is the src, img_decision is set */
    RD_NOTICE,        /* a user-agent notice (e.g. the image tracking warning) */
    RD_INPUT          /* a form control; text is placeholder/label, href is the form action */
} rd_kind;

/* One paint-ready block in document order. text is owned, NUL-terminated and
 * valid UTF-8. href is owned and NUL-terminated for RD_LINK (link target),
 * RD_IMAGE (image src) and RD_INPUT (the owning form's action); NULL otherwise.
 * img_decision is meaningful only for RD_IMAGE. The input_* fields are meaningful
 * only for RD_INPUT: input_type is a pv_input_type; name/value are owned (NULL when
 * absent) and carry the submitted bytes verbatim; form_id groups controls of one
 * form (-1 = none); form_method is a pv_form_method. */
typedef struct rd_block {
    rd_kind          kind;
    int              heading_level;  /* 1..6 for RD_HEADING, else 0 */
    int              block_break;    /* nonzero: a block boundary precedes this block */
    char            *text;
    char            *href;
    rdp_img_decision img_decision;
    int              fg_rgb;         /* author color packed 0xRRGGBB, or -1; set only with caps.css */
    int              bg_rgb;         /* author background-color packed 0xRRGGBB, or -1; set only with caps.css */
    /* Nearest author flex/grid container of this block (page_view), carried by
     * default (layout is structure, not author styling, and leaks nothing to the
     * network) so the presentation layer can lay it out with box_tree/flex_layout.
     * cont_id groups blocks of one container (-1 = none); the rest are its params. */
    int              cont_id;        /* container group id, or -1 */
    int              cont_display;   /* bx_display (flex/grid), or 0 */
    int              cont_gap;       /* container gap in px */
    int              cont_justify;   /* fx_justify of the container */
    int              cont_cols;      /* grid column count, or 0 */
    int              input_type;     /* RD_INPUT: pv_input_type, else 0 */
    char            *name;           /* RD_INPUT: control name, or NULL */
    char            *value;          /* RD_INPUT: control value, or NULL */
    int              form_id;        /* RD_INPUT: owning-form group id, or -1 */
    int              form_method;    /* RD_INPUT: pv_form_method */
} rd_block;

typedef struct rd_doc {
    rd_block *blocks;
    size_t    count;
    size_t    cap;
    int       has_images;  /* the page declared at least one image */
} rd_doc;

typedef enum rd_status {
    RD_OK = 0,
    RD_ERR_NULL_ARG,  /* a required out pointer was NULL */
    RD_ERR_OOM        /* allocation failed */
} rd_status;

/* Builds the paint-ready document from an inert display list and the page's
 * capabilities. view == NULL is treated as an empty view. When the page declares
 * images and caps.images is false, a single RD_NOTICE block carrying
 * rdp_images_warning() is prepended so the user is always told. Each image
 * becomes an RD_IMAGE block whose img_decision is computed with
 * rdp_image_decision(caps, top_level_url, src, img_w, img_h) — Zero Trust,
 * revalidated per image. top_level_url may be NULL (e.g. a local file): image
 * decisions then fail closed. out == NULL => RD_ERR_NULL_ARG. On RD_OK, *out must
 * be released with rd_free. */
rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_url, rd_doc **out);

/* Idempotent; safe on NULL and safe to call twice. */
void rd_free(rd_doc *d);

/* Read accessors. NULL-safe. */
size_t          rd_count(const rd_doc *d);
const rd_block *rd_at(const rd_doc *d, size_t i);

/* Stable, short English name of a block kind for structured/agent output. Never
 * NULL; an unknown enum value yields "block". */
const char *rd_kind_name(rd_kind k);

/* Canonical HTML tag name for a block, so the presentation layer can look up its
 * user-agent box (box_style) without re-deriving the kind->tag mapping at the call
 * site. RD_HEADING -> "h1".."h6" (heading_level clamped to 1..6), RD_PARAGRAPH ->
 * "p", RD_LINK -> "a", RD_IMAGE -> "img", RD_INPUT -> "textarea"/"button"/"input"
 * by input_type. RD_NOTICE (a user-agent banner, not an HTML element) and a NULL
 * block yield NULL. The returned string is a static literal (not owned). */
const char *rd_block_tag(const rd_block *b);

/* Stable, short English label for an image placeholder, derived from its
 * decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never
 * NULL. */
const char *rd_image_label(rdp_img_decision d);

/* Stable, short English name of a form control type (a pv_input_type value), e.g.
 * "text" / "password" / "submit". Never NULL; an unknown value yields "field". */
const char *rd_input_label(int input_type);

#endif /* FREEDOM_RENDER_DOC_H */
