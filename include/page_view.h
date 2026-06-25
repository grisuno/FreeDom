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
    PV_IMAGE = 2,  /* an <img>: src is set, text holds the alt text */
    PV_INPUT = 3   /* a form control (<input>/<textarea>/<button>): see pv_input_type */
} pv_kind;

/* Class of a PV_INPUT control. Drives how the GUI paints and submits it. Unknown
 * input types collapse to PV_IN_TEXT (a one-line editable box). */
typedef enum pv_input_type {
    PV_IN_TEXT = 0,   /* text/search/email/url/tel/number/...: one-line editable box */
    PV_IN_PASSWORD,   /* password: editable, masked when painted */
    PV_IN_TEXTAREA,   /* <textarea>: editable (one-line box for now); value = its content */
    PV_IN_HIDDEN,     /* hidden: not painted; value still submitted */
    PV_IN_SUBMIT,     /* submit button (triggers the owning form) */
    PV_IN_BUTTON      /* non-submitting button (button/reset): painted, inert */
} pv_input_type;

/* Form method carried on a PV_INPUT run (denormalised from the owning <form>). */
typedef enum pv_form_method {
    PV_METHOD_GET = 0,
    PV_METHOD_POST = 1
} pv_form_method;

/* One inline run in document order. text is owned, NUL-terminated, valid UTF-8
 * (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated
 * for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for PV_IMAGE
 * runs (the image URL, data with provenance, never fetched here), NULL otherwise;
 * img_w/img_h carry the declared <img> dimensions in pixels, or -1 when unknown.
 * An image is never a link, so href and src are never both set. fg_rgb carries the
 * author foreground color (nearest inline style "color:" or <font color>) packed
 * as 0xRRGGBB, or -1 when none/unparseable; it is presentation data the renderer
 * applies only when author CSS is enabled. */
typedef struct pv_run {
    pv_kind kind;
    int     heading;      /* 0 = body text; 1..6 = inside h1..h6 */
    int     bold;         /* nonzero: inside <b>/<strong>/<th> (inline emphasis) */
    int     italic;       /* nonzero: inside <i>/<em> (inline emphasis) */
    int     indent;       /* list nesting depth (count of <ul>/<ol> ancestors); 0 if none */
    int     block_break;  /* nonzero: a block boundary precedes this run */
    char   *text;         /* PV_INPUT: the placeholder (text) or button label */
    char   *href;         /* PV_LINK target; PV_INPUT: the owning form's raw action */
    char   *src;          /* PV_IMAGE only: image URL; NULL otherwise */
    int     img_w;        /* PV_IMAGE declared width in px, or -1 if unknown */
    int     img_h;        /* PV_IMAGE declared height in px, or -1 if unknown */
    int     fg_rgb;       /* author color packed 0xRRGGBB, or -1 if none */
    int     bg_rgb;       /* author background-color packed 0xRRGGBB, or -1 if none */
    /* Author text presentation resolved from <style> + inline style= (the css
     * module). text_align is a css_align (0 unset, 1 left, 2 center, 3 right,
     * 4 justify); font_scale is a font-size percent (100 = normal) or 0 (unset);
     * line_scale is a line-height percent of the natural line box (0 = unset).
     * All are presentation: render_doc applies them only with caps.css, exactly
     * like fg_rgb/bg_rgb. Defaults: text_align 0, font_scale 0, line_scale 0. */
    int     text_align;
    int     font_scale;
    int     line_scale;
    /* Nearest author flex/grid container ancestor (display:flex|grid in style), so
     * the presentation layer can lay the container's children out with box_tree.
     * cont_id groups runs of one container (-1 = none); cont_display is the
     * bx_display (flex/grid); the rest are the container's parsed params. Defaults:
     * cont_id -1, the others 0. Carried by render_doc regardless of caps.css
     * (layout is structure; only author colors are gated). */
    int     cont_id;      /* container group id in document order, or -1 */
    int     cont_display; /* bx_display of the container (flex/grid), or 0 */
    int     cont_gap;     /* container gap in px (>= 0) */
    int     cont_justify; /* fx_justify of the container */
    int     cont_cols;    /* grid column count (>= 1 for grid), or 0 */
    /* form controls (PV_INPUT only; defaults: type 0, name/value NULL, form_id -1,
     * method GET). name/value carry the submitted bytes verbatim (not whitespace
     * collapsed); form_id groups controls of the same <form> (-1 = no form). */
    int     input_type;   /* pv_input_type */
    char   *name;         /* control name, or NULL */
    char   *value;        /* control current/default value, or NULL */
    int     form_id;      /* owning-form group id in document order, or -1 */
    int     form_method;  /* pv_form_method of the owning form */
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
pv_status pv_build(const hp_document *doc, pv_view **out); /* == pv_build_ex(doc, 0, out) */

/* As pv_build, but js_enabled selects <noscript> handling: when 0 (JS off, the
 * default) the <noscript> fallback content IS rendered (a no-JS browser shows it);
 * when nonzero (JS allowed for this page) the <noscript> subtree is suppressed. */
pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out);

/* As pv_build_ex, plus a distraction-free (reader) flag and the user's color-scheme
 * preference (prefers_dark != 0 selects dark for the author's
 * @media(prefers-color-scheme) rules). When reader is nonzero, boilerplate subtrees
 * (<nav>/<header>/<footer>/<aside>) are skipped so only the main content is emitted;
 * author CSS is still resolved (the presentation layer decides whether to apply it).
 * pv_build_ex is pv_build_full with reader == 0 and prefers_dark == 0. */
pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                        int prefers_dark, pv_view **out);

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

/* Appends one PV_INPUT run (a form control). text is the placeholder/label (may be
 * NULL -> ""); name/value are the control identity and value (may be NULL); action
 * is the owning form's raw action href (may be NULL); form_id groups controls of a
 * form (-1 if none); method is the form's pv_form_method. text is normalised to
 * valid UTF-8 (display); name/value/action are copied verbatim (submitted bytes /
 * resolved later). Returns PV_OK or PV_ERR_OOM / PV_ERR_NULL_ARG. */
pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_input_type input_type, const char *text,
                          const char *name, const char *value,
                          const char *action, int form_id, int method);

/* Sets the author foreground color (packed 0xRRGGBB, or -1 for none) on the most
 * recently appended run. No-op when the view is empty or NULL. Both append helpers
 * default a new run's color to -1, so this only needs calling when a color is
 * present. */
/* Sets the inline emphasis flags (bold from <b>/<strong>/<th>, italic from
 * <i>/<em>) on the most recently appended run. No-op on an empty or NULL view.
 * Both append helpers default a new run to bold=0, italic=0. Emphasis is structure
 * (which glyph weight/slant), not author styling, so it is carried by default and
 * is not gated by caps.css. */
void pv_set_emphasis(pv_view *v, int bold, int italic);

/* Sets the list nesting depth (count of <ul>/<ol> ancestors) on the most recently
 * appended run. No-op on an empty or NULL view; defaults to 0. The list marker
 * ("* " or "N. ") is prepended to the run text by pv_build, not here. List
 * structure is carried by default (not gated by caps.css). */
void pv_set_indent(pv_view *v, int indent);

void pv_set_color(pv_view *v, int fg_rgb);

/* Sets the author background-color (packed 0xRRGGBB, or -1 for none) on the most
 * recently appended run. No-op when the view is empty or NULL. Both append helpers
 * default a new run's bg_rgb to -1. background-color does not inherit in CSS; in
 * this flat model pv_build resolves it from the nearest ancestor that sets one, so
 * a block's background shows behind its text runs. */
void pv_set_bgcolor(pv_view *v, int bg_rgb);

/* Sets the author text presentation (text_align as a css_align, font_scale as a
 * font-size percent or 0, line_scale as a line-height percent or 0) on the most
 * recently appended run. No-op on an empty or NULL view. The append helpers default
 * all three to 0. Like author colors, render_doc applies these only with caps.css. */
void pv_set_text_style(pv_view *v, int text_align, int font_scale, int line_scale);

/* Sets the nearest flex/grid container annotation on the most recently appended
 * run (cont_id, the bx_display, and the parsed gap/justify/cols). No-op on an empty
 * or NULL view. Both append helpers default cont_id to -1 (no container). */
void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_gap, int cont_justify, int cont_cols);

/* Idempotent; safe on NULL and safe to call twice. */
void pv_free(pv_view *v);

/* Read accessors. NULL-safe. */
size_t        pv_count(const pv_view *v);
const pv_run *pv_at(const pv_view *v, size_t i);

#endif /* FREEDOM_PAGE_VIEW_H */
