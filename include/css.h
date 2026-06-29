#ifndef FREEDOM_CSS_H
#define FREEDOM_CSS_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * css — pure parser + simple cascade for AUTHOR CSS (<style> blocks and inline
 * style= attributes). Renders the page closer to what the webmaster intended,
 * with a deliberately simpler subset.
 *
 * CSS is hostile remote content, so this module is an auditable surface:
 *   - It NEVER phones home: any value containing url( is dropped, and every
 *     @-rule (@import/@font-face/@media/...) is skipped.
 *   - It is bounded (anti-DoS): rules/selectors/declarations are capped.
 *   - It fails closed: unparseable selectors/declarations are dropped, not guessed.
 *   - It executes nothing (expression()/var()/calc()/JS URLs are unknown -> ignored).
 *
 * It produces no pixels and opens no sockets: it resolves a small css_style value
 * for an element. page_view consults it; render_doc still gates the result behind
 * caps.css (Privacy by Default). See spec/css.md for the full contract.
 */

typedef enum css_status {
    CSS_OK = 0,
    CSS_ERR_NULL_ARG, /* out was NULL */
    CSS_ERR_OOM       /* allocation failed */
} css_status;

typedef enum css_align {
    CSS_ALIGN_UNSET = 0,
    CSS_ALIGN_LEFT,
    CSS_ALIGN_CENTER,
    CSS_ALIGN_RIGHT,
    CSS_ALIGN_JUSTIFY
} css_align;

typedef enum css_display {
    CSS_DISP_UNSET = 0,
    CSS_DISP_NONE,
    CSS_DISP_BLOCK,
    CSS_DISP_INLINE,
    CSS_DISP_INLINE_BLOCK,
    CSS_DISP_FLEX,
    CSS_DISP_GRID,
    CSS_DISP_OTHER
} css_display;

typedef enum css_justify {  /* justify-content (flex/grid main axis) */
    CSS_JUSTIFY_UNSET = 0,
    CSS_JUSTIFY_START,
    CSS_JUSTIFY_END,
    CSS_JUSTIFY_CENTER,
    CSS_JUSTIFY_SPACE_BETWEEN,
    CSS_JUSTIFY_SPACE_AROUND,
    CSS_JUSTIFY_SPACE_EVENLY
} css_justify;

/* Anti-DoS bounds for the flex/grid container params. */
#define CSS_GAP_MAX       4096   /* px cap on gap */
#define CSS_GRID_COLS_MAX 64     /* cap on grid-template-columns track count */
#define CSS_LINE_MIN      50     /* line-height clamp floor (percent) */
#define CSS_LINE_MAX      400    /* line-height clamp ceiling (percent, anti-DoS) */

/* text-decoration line bits, OR-combined into css_style.text_decoration. The field
 * is -1 when unset and 0 for an explicit `none` (so `a { text-decoration: none }`
 * can drop the default link underline). */
#define CSS_DECO_UNDERLINE    0x1
#define CSS_DECO_LINE_THROUGH 0x2
#define CSS_DECO_OVERLINE     0x4

/* Generic font family bucket (font-family). A specific family name is mapped to its
 * generic group; an unrecognised name leaves the field unset (UA sans-serif). */
typedef enum css_font_family {
    CSS_FF_UNSET = 0, CSS_FF_SERIF, CSS_FF_SANS, CSS_FF_MONO,
    CSS_FF_CURSIVE, CSS_FF_FANTASY
} css_font_family;

/* text-transform. 0 is unset; CSS_TT_NONE is an explicit `none`. */
typedef enum css_text_transform {
    CSS_TT_UNSET = 0, CSS_TT_NONE, CSS_TT_UPPERCASE, CSS_TT_LOWERCASE, CSS_TT_CAPITALIZE
} css_text_transform;

/* vertical-align (subset: only the inline shifts). 0 unset. */
typedef enum css_valign {
    CSS_VA_UNSET = 0, CSS_VA_BASELINE, CSS_VA_SUB, CSS_VA_SUPER
} css_valign;

/* white-space (subset: only the wrap/keep distinction is consumed). 0 unset. */
typedef enum css_white_space {
    CSS_WS_UNSET = 0, CSS_WS_NORMAL, CSS_WS_NOWRAP, CSS_WS_PRE,
    CSS_WS_PRE_WRAP, CSS_WS_PRE_LINE
} css_white_space;

/* list-style-type (and the type token of the list-style shorthand). 0 unset. */
typedef enum css_list_style {
    CSS_LS_UNSET = 0, CSS_LS_NONE, CSS_LS_DISC, CSS_LS_CIRCLE, CSS_LS_SQUARE,
    CSS_LS_DECIMAL, CSS_LS_LOWER_ALPHA, CSS_LS_UPPER_ALPHA,
    CSS_LS_LOWER_ROMAN, CSS_LS_UPPER_ROMAN
} css_list_style;

/* Anti-DoS clamps for the new metric properties (px, absolute value). text-indent
 * reuses the box-model CSS_LEN_MAX clamp (below). */
#define CSS_SPACING_MAX 200      /* letter-spacing / word-spacing */
#define CSS_SHADOW_MAX  100      /* text-shadow offsets */

/* Box-model lengths (margin/padding/width/max-width), in px. Two out-of-band
 * sentinels distinguish "not declared" and the 'auto' keyword from a real length;
 * a real length is clamped to [-CSS_LEN_MAX, CSS_LEN_MAX] (anti-DoS). */
#define CSS_LEN_MAX       100000
#define CSS_LEN_UNSET     (-2147483647 - 1) /* INT_MIN: property not set */
#define CSS_LEN_AUTO      (-2147483647)     /* INT_MIN+1: the 'auto' keyword */

/* Max compounds in one complex selector (subject + ancestor/parent constraints).
 * A deeper chain is dropped (fail closed). */
#define CSS_MAX_COMPOUNDS 4

/* Max attribute selectors ([attr], [attr=v], ...) in one compound. More are dropped
 * (the whole selector fails closed). */
#define CSS_MAX_ATTR_SEL  4

/* A resolved presentation. Each field uses a sentinel for "unset" so the caller
 * can layer inheritance (take the first ancestor that sets each inheriting one).
 * The flex/grid container fields (gap/justify/grid_cols) are NOT inherited: they
 * describe the container element itself, so the caller reads them from that
 * element's resolved style, not up the ancestor chain. */
typedef struct css_style {
    int         color;       /* 0xRRGGBB or -1 (unset) */
    int         background;  /* 0xRRGGBB or -1 (unset) */
    css_align   text_align;  /* CSS_ALIGN_UNSET if absent */
    int         font_scale;  /* percent (e.g. 150), or 0 (unset) */
    int         line_scale;  /* line-height percent of the natural line box, or 0 (unset) */
    int         text_decoration; /* OR of CSS_DECO_*; 0 = none; -1 = unset */
    int         bold;        /* 1, 0, or -1 (unset) */
    int         italic;      /* 1, 0, or -1 (unset) */
    css_display display;     /* CSS_DISP_UNSET if absent */
    int         gap;         /* px between flex/grid items, or -1 (unset) */
    css_justify justify;     /* justify-content; CSS_JUSTIFY_UNSET if absent */
    int         grid_cols;   /* grid-template-columns track count, or 0 (unset) */
    /* Author box model (px; NOT inherited — read from the element's own style).
     * margins: CSS_LEN_UNSET / CSS_LEN_AUTO / signed px. padding: CSS_LEN_UNSET /
     * px >= 0. width/max_width: CSS_LEN_UNSET / px > 0 (auto/none -> unset). */
    int         margin_top, margin_right, margin_bottom, margin_left;
    int         pad_top, pad_right, pad_bottom, pad_left;
    int         width, max_width;
    /* Author text-presentation extensions (Hito 23b-6). All inherit in CSS; in this
     * flat model the caller takes the nearest ancestor that sets each. Like the other
     * author presentation, they are gated behind caps.css downstream. */
    int         font_family;     /* css_font_family, 0 (unset) */
    int         text_transform;  /* css_text_transform, 0 (unset) */
    int         letter_spacing;  /* px (signed), 0 = normal, CSS_LEN_UNSET (unset) */
    int         word_spacing;    /* px (signed), 0 = normal, CSS_LEN_UNSET (unset) */
    int         shadow_dx;       /* text-shadow x offset px (signed), 0 if no shadow */
    int         shadow_dy;       /* text-shadow y offset px (signed), 0 if no shadow */
    int         shadow_color;    /* text-shadow color 0xRRGGBB, or -1 (none/unset) */
    int         opacity;         /* percent 0..100, or -1 (unset) */
    int         valign;          /* css_valign, 0 (unset) */
    int         text_indent;     /* px (signed), CSS_LEN_UNSET (unset) */
    int         white_space;     /* css_white_space, 0 (unset) */
    int         list_style;      /* css_list_style, 0 (unset) */
} css_style;

typedef struct css_sheet css_sheet; /* opaque; owns the parsed rules */

/* Render-time media context for evaluating @media at parse time. width_px is a
 * fixed, normalized desktop width, so a (min/max-width) query leaks no real viewport
 * size (anti-fingerprinting). */
typedef struct css_media {
    int prefers_dark; /* 1: the user prefers a dark color scheme */
    int print;        /* 1: rendering for print (PDF); 0: screen */
    int width_px;     /* assumed viewport width for min/max-width queries */
} css_media;

#define CSS_MEDIA_DEFAULT_WIDTH 1920

/* Parses a <style> text (one or many blocks concatenated) into *out. Malformed
 * input never fails: unparseable rules are skipped. text == NULL is treated as
 * empty. out == NULL => CSS_ERR_NULL_ARG; allocation failure => CSS_ERR_OOM. On
 * CSS_OK, *out must be freed with css_free. Equivalent to css_parse_media with a
 * default screen / light / 1920px context. */
css_status css_parse(const char *text, size_t len, css_sheet **out);

/* As css_parse, but @media blocks are gated against *media (prefers-color-scheme,
 * screen/print/all, min/max-width). media == NULL uses the default screen/light/
 * 1920px context. Matched @media rules fold into the sheet as if unconditional, so
 * css_resolve is unchanged. @import/@font-face/other @-rules are still skipped. */
css_status css_parse_media(const char *text, size_t len, const css_media *media,
                           css_sheet **out);

/* Idempotent; NULL-safe. */
void css_free(css_sheet *s);

/* Computes the presentation for one element: every matching sheet rule applied in
 * cascade order (specificity, then document order), then the element's own
 * inline_style (which wins). sheet/tag/classes/inline_style may be NULL. Pure,
 * allocates nothing, reentrant. Inheritance is the caller's job (call per ancestor,
 * merge unset fields). */
css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                      const char *const *classes, size_t nclasses,
                      const char *inline_style, size_t inline_len);

/* One element attribute, for attribute selectors ([attr], [attr=v], [attr~=v], ...).
 * name is the lowercased local name; value is the attribute text ("" if empty). Both
 * alias caller storage (nothing is copied/owned). */
typedef struct css_attr {
    const char *name;
    const char *value;
} css_attr;

/* An element plus its ancestor chain, for combinator matching. Each field aliases
 * caller storage (nothing is copied/owned). parent walks toward the root (NULL at
 * the top). A bounded/partial chain is fine: a descendant compound that would have
 * matched a missing deeper ancestor simply does not match (fail closed). attrs/nattrs
 * may be empty (NULL/0): an attribute selector then simply does not match. */
typedef struct css_element {
    const char *tag;                  /* lowercased local name, or NULL */
    const char *id;                   /* id attribute value, or NULL */
    const char *const *classes;       /* class tokens (not NUL-joined) */
    size_t nclasses;
    const css_attr *attrs;            /* element attributes, or NULL */
    size_t nattrs;
    const struct css_element *parent; /* parent element, or NULL at the root */
} css_element;

/* As css_resolve, but matches descendant (`A B`) and child (`A > B`) combinators
 * against el's ancestor chain. el == NULL resolves only inline_style. Pure,
 * allocates nothing, reentrant. css_resolve is this with a parentless element. */
css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         const char *inline_style, size_t inline_len);

/* Convenience: resolve only an inline declaration list (no sheet, no selectors). */
css_style css_parse_inline(const char *style, size_t len);

#endif /* FREEDOM_CSS_H */
