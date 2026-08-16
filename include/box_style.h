#ifndef FREEDOM_BOX_STYLE_H
#define FREEDOM_BOX_STYLE_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

#include "css.h"   /* css_display: the author side of the display property */

/*
 * box_style — the user-agent box model, per HTML tag.
 *
 * Pure, I/O-free, allocation-free classification (the directly auditable layer
 * between the DOM and the layout). Given a tag name it returns the default box
 * metrics (margins and padding, in em) and the display type; given an author
 * display token it decodes the keyword. It measures nothing and paints nothing.
 *
 * This is Freedom's user-agent stylesheet: the subset of CSS 2.1 default rules the
 * engine always applies. They are not author styles, so they are not gated by
 * caps.css. The author display parser (bx_parse_display) only decodes the token;
 * the CALLER decides whether to honour it, gated by caps.css (Secure by Default: a
 * document does not reconfigure the engine unless the user allows it).
 *
 * It is also the entry point to flex_layout: once an element is classified
 * BX_DISPLAY_FLEX or BX_DISPLAY_GRID, the geometric solver takes over.
 *
 * See spec/box_style.md for the full contract.
 */

/* Buffer size a caller needs to hand a tag name to this module. Generous: the
 * longest recognised tag is "blockquote" (10), so a real tag always fits and
 * anything longer fails closed instead of truncating into a wrong match. */
#define BX_TAG_NAME_MAX 32u

typedef enum bx_display {
    BX_DISPLAY_BLOCK = 0,     /* stacks vertically, takes the available width */
    BX_DISPLAY_INLINE,        /* flows with text; vertical margins ignored by layout */
    BX_DISPLAY_INLINE_BLOCK,  /* in-line box with its own dimensions (img, input) */
    BX_DISPLAY_LIST_ITEM,     /* like block, but the layout draws a marker (li) */
    BX_DISPLAY_FLEX,          /* flex container: resolved by flex_layout */
    BX_DISPLAY_GRID,          /* grid container: resolved by flex_layout */
    BX_DISPLAY_NONE           /* not rendered and takes no space (head, script...) */
} bx_display;

/* Box edges in em (multiples of the element's own font size). */
typedef struct bx_edges {
    double top, right, bottom, left;
} bx_edges;

typedef struct bx_box {
    bx_display display;
    bx_edges   margin;
    bx_edges   padding;
} bx_box;

typedef enum bx_status {
    BX_OK = 0,
    BX_ERR_NULL_ARG,  /* token or out was NULL */
    BX_ERR_SYNTAX     /* not a recognised display keyword (fails closed) */
} bx_status;

/* Horizontal placement of an author box inside an available width (px). */
typedef struct bx_hplace {
    double x_off;      /* left offset from the content area's left edge */
    double content_w;  /* width available to the block's inline content */
} bx_hplace;

/* UA default box for an HTML tag name (case-insensitive). tag == NULL, empty, or
 * unknown yields a neutral inline box with zero margins and padding (the safe
 * default: an unknown element invents no spacing). Returned by value; no
 * allocation. */
bx_box bx_default_for_tag(const char *tag);

/* Compact, stable identity of a block's SOURCE element, just wide enough to recover
 * its user-agent box on the far side of the render IPC without shipping a tag string
 * per block. Only the tags the HTML user-agent sheet gives a non-zero vertical margin
 * need a code: everything else (div, section, header, article, footer, nav, main,
 * table, tr, td, form, ...) shares BX_UA_NONE, whose UA margin is zero -- which is
 * both the correct answer and the fail-closed one (an unrecognised element invents no
 * spacing). spec/box_style.md 4d.
 *
 * The codes are an ABI between page_view, the IPC codec and the painter; APPEND
 * only, never renumber. */
typedef enum bx_ua_tag {
    BX_UA_NONE = 0,   /* no user-agent margin: div/section/td/... and unknown tags */
    BX_UA_P,
    BX_UA_H1, BX_UA_H2, BX_UA_H3, BX_UA_H4, BX_UA_H5, BX_UA_H6,
    BX_UA_UL, BX_UA_OL, BX_UA_MENU,
    BX_UA_DL,
    BX_UA_PRE,
    BX_UA_BLOCKQUOTE,
    BX_UA_FIGURE,
    BX_UA_HR,
    BX_UA_LI,         /* zero margin, but distinct: a list item is NOT an unknown tag */
    BX_UA_COUNT
} bx_ua_tag;

/* Maps an HTML tag name (case-insensitive) to its bx_ua_tag code. A tag the user-agent
 * sheet gives no vertical margin -- and any unknown, empty or NULL tag -- maps to
 * BX_UA_NONE. Pure, allocation-free, total. */
bx_ua_tag bx_ua_of_tag(const char *tag);

/* UA default box for a bx_ua_tag code: the same row of the same table
 * bx_default_for_tag reads, so the user-agent sheet has ONE definition. A code
 * outside 0..BX_UA_COUNT-1 fails closed to the neutral zero-margin box. Pure. */
bx_box bx_default_for_ua(bx_ua_tag id);

/* The user-agent box of a laid-out BLOCK, resolving the three questions the painter
 * would otherwise answer with a guess (spec/box_style.md 4f). Pure and total.
 *
 *   heading_level  1..6 when the block IS a heading (its own level, not its
 *                  ancestry, picks h1..h6), 0 otherwise; out-of-range clamps into
 *                  1..6 rather than inventing a box.
 *   in_list        nonzero when the block sits inside a list item: it then takes
 *                  the <li> box (zero margin), keeping items tight. A heading
 *                  escapes this, per 4d.
 *   ua             identity of the nearest BLOCK-LEVEL ancestor (bx_ua_tag).
 *
 * `ua` is the authority for every non-heading block whatever kind of run carried
 * it: an <a>/<img>/<svg>/<input> is inline-level and contributes no vertical margin
 * of its own (CSS 2.1 8.3), so asking ITS tag returns zero and silently deletes the
 * containing block's margin. */
bx_box bx_block_ua_box(int heading_level, int in_list, bx_ua_tag ua);

/* The role an element plays in a table (CSS 2.1 17.2). BX_TROLE_COLUMN generates no
 * box of its own; the rest are the boxes the table layout is built from. */
typedef enum bx_table_role {
    BX_TROLE_NONE = 0,   /* not part of a table */
    BX_TROLE_TABLE,      /* display:table / inline-table   -- UA: <table>          */
    BX_TROLE_ROW_GROUP,  /* display:table-*-group          -- UA: tbody/thead/tfoot*/
    BX_TROLE_ROW,        /* display:table-row              -- UA: <tr>             */
    BX_TROLE_CELL,       /* display:table-cell             -- UA: <td>, <th>       */
    BX_TROLE_CAPTION,    /* display:table-caption          -- UA: <caption>        */
    BX_TROLE_COLUMN      /* display:table-column(-group)   -- UA: <col>, <colgroup>*/
} bx_table_role;

/* Which table role (tag, display) plays. The computed `display` decides whenever it
 * names a role -- that is what CSS 2.1 17.2 says a table box IS -- and otherwise the
 * HTML user-agent sheet's role for the tag applies, which is where every <table> the
 * engine already laid out comes from. So `<div style="display:table-cell">` is a cell
 * and `<td style="display:block">` is not, both without a second table engine.
 *
 * Pure and total: tag NULL/empty/unknown with no role-naming display yields
 * BX_TROLE_NONE (an unrecognised element joins no table -- fail closed). */
bx_table_role bx_table_role_of(const char *tag, css_display display);

/* Decodes a CSS display keyword token (case-insensitive, ASCII-trimmed) into *out.
 * Recognises none / block / inline / inline-block / list-item / flex / inline-flex
 * / grid / inline-grid (inline-flex => FLEX, inline-grid => GRID). token/out NULL
 * => BX_ERR_NULL_ARG; empty, oversized, or unsupported => BX_ERR_SYNTAX (out
 * untouched). On BX_OK, *out is set. */
bx_status bx_parse_display(const char *token, bx_display *out);

/* Stable, short English name of a display type for structured/agent output. Never
 * NULL; an unknown enum value yields "inline". */
const char *bx_display_name(bx_display d);

/* Resolves the horizontal placement of an author box within avail_w (px). inset_l/
 * inset_r are the left/right insets (padding + non-auto margin of that side);
 * width_cap is the content-width cap (min of width/max-width already resolved, 0 =
 * none); center is 1 for `margin: 0 auto` (both horizontal margins auto + a width
 * cap). Pure, no allocation. Negative insets are clamped to 0; avail_w < 1 is
 * raised to 1; the result always has content_w >= 1 and x_off >= 0. With no box
 * (inset_l=inset_r=0, width_cap=0) it returns x_off 0 and content_w == avail_w. */
bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,
                   double avail_w);

/* Effective width cap combining the px cap (w_px, 0 = none) with a symbolic
 * per-mille cap (w_pct, 0 = none; Hito 32) resolved against the real available
 * width: both set => the tighter wins; neither (or avail_w <= 0 for the pct)
 * => 0 (no cap). Never negative. Pure. */
double bx_width_cap(int w_px, int w_pct, double avail_w);

/* The used BOX of a replaced element (image/video) that has no intrinsic pixel size
 * of its own -- because it did not load, or was never allowed to.
 *
 * CSS Sizing 4 section 4: when one axis is definite and an aspect-ratio is present,
 * the ratio supplies the other. That is what makes a blocked thumbnail keep the
 * shape the author reserved for it instead of collapsing to a text-height bar and
 * letting its `alt` reflow the page. Freedom renders this case by default (images
 * off; third-party images blocked even when on), so it is the common path, not an
 * edge case.
 *
 * w_px / w_pct are the declared width's two halves (CSS_LEN_UNSET / 0 for absent),
 * resolved against avail_w exactly like every other <length-percentage>.
 * aspect_num / aspect_den are the ratio x1000 (0 = none).
 *
 * Returns 1 and writes *out_w / *out_h only when BOTH a positive used width and a
 * usable ratio are available; otherwise returns 0 and touches nothing, leaving the
 * caller's own fallback in place rather than inventing a height. Pure. */
int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den,
                    double avail_w, double *out_w, double *out_h);


/* Border-box height for a DECLARED height under box-sizing (CSS 2.1 10.6.3,
 * CSS Box Sizing 3 section 4). With content-box -- the CSS default, so the
 * common case -- `height` sizes the CONTENT, and the vertical padding and
 * border sit OUTSIDE it: a `height:60px; padding:2%` box is taller than 60px.
 * With border-box the declared height already includes them and this is the
 * identity. Negative edges are treated as 0; the result is never negative.
 *
 * The horizontal twin is bx_content_cap, which converts the other way (a
 * declared border-box WIDTH into the content width cap) because widths are
 * capped and heights are set. Pure. */
double bx_border_box_h(double declared_h, int border_box,
                       double pad_t, double pad_b, double bord_t, double bord_b);

/* Used px value of a <length-percentage> (CSS Values 4 section 5.3): the px
 * half plus pct_pm per-mille of `basis`. This is the ONLY place the engine
 * turns a percentage into pixels, and the rule is the whole of it -- there is
 * no clamping, no minimum and no special case here, because none of those are
 * properties of the value type.
 *
 * `basis` is the containing-block dimension the property resolves against.
 * Which dimension that is belongs to the caller and is NOT symmetric: CSS 2.1
 * sections 8.3/8.4 resolve ALL FOUR margin and padding percentages against the
 * containing block WIDTH, padding-top and padding-bottom included. The full
 * property -> basis table is spec/css_length.md section 7.3.
 *
 * px_val may carry a CSS_LEN_UNSET/CSS_LEN_AUTO sentinel, which contributes 0
 * (a percentage-only value states no absolute length). A basis that is not a
 * usable length contributes nothing while the absolute half survives. Pure. */
double bx_lp_px(int px_val, int pct_pm, double basis);

/* Content-width cap adjusted for box-sizing (2026-07-11). With border_box set,
 * the declared width includes the horizontal padding and border, so the cap on
 * the CONTENT is width_cap minus those edges, clamped >= 1 (a border-box
 * narrower than its own edges never yields a negative width). border_box == 0
 * (content-box or unset) or width_cap <= 0 (no cap) are the identity. Negative
 * edges are treated as 0. Pure. */
double bx_content_cap(double width_cap, int border_box,
                      double pad_l, double pad_r, double bord_l, double bord_r);

#endif /* FREEDOM_BOX_STYLE_H */
