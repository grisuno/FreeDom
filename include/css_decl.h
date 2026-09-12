#ifndef FREEDOM_CSS_DECL_H
#define FREEDOM_CSS_DECL_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

#include "css.h"
#include "css_select.h"

#define CSS_MAX_BG_URLS 256u

#define CSS_MAX_KEYFRAMES 4
#define CSS_MAX_KEYFRAME_STOPS 8
#define CSS_MAX_KEYFRAME_DECLS 8
#define CSS_INLINE_BG_URLS 8u

/* Scratch size for the CSS-wide-keyword probe (wide_claim). Bounds the widest
 * shorthand expansion in the dispatch: the four-side length shorthands emit a px
 * and a percentage slot per side (8), grid-template-columns emits one slot per
 * track plus the count (9), and matrix() emits seven. */
#define CSS_WIDE_PROBE_DECLS 24

/* Rounds v to the nearest int, clamped to [lo, hi]. Single owner of the
 * helper formerly copied per-module (css.c/css_values.c/css_box.c/css_text.c).
 * Clamps the double BEFORE the cast: casting an out-of-range double (e.g. a
 * hostile "99999999999px") to int is UB. Every value interpreter that casts a
 * parsed double routes through here. Boundary mutants (>= vs > at exact hi/lo)
 * are equivalent: the C cast truncates, so both spellings yield the same int. */
static inline int css_round_clamp(double v, int lo, int hi) {
    if (v >= (double)hi) return hi;
    if (v <= (double)lo) return lo;
    return (int)(v + (v < 0.0 ? -0.5 : 0.5));
}

/* Property slots. The enum value IS the css_style slot index used by apply().
 * The four margin slots are contiguous in CSS shorthand order (top,right,bottom,
 * left); the four padding slots likewise — expand_box4 relies on that. */
enum { P_COLOR = 0, P_BG, P_ALIGN, P_FONTSIZE, P_FONTABS, P_LINEHEIGHT, P_WEIGHT, P_STYLE,
       P_TEXTDECO, P_TEXTDECO_COLOR, P_TEXTDECO_STYLE,
       P_DISPLAY, P_GAP, P_JUSTIFY, P_GRIDCOLS,
       P_MARGIN_TOP, P_MARGIN_RIGHT, P_MARGIN_BOTTOM, P_MARGIN_LEFT,
       P_PAD_TOP, P_PAD_RIGHT, P_PAD_BOTTOM, P_PAD_LEFT,
       P_WIDTH, P_MAXWIDTH, P_MINWIDTH, P_HEIGHT, P_MINHEIGHT, P_MAXHEIGHT,
       /* The percentage half of every <length-percentage> property, one slot per
        * css_pct_slot and in that exact order, so pct_slot_of() is a table lookup
        * rather than a second hand-maintained switch. apply() writes them into
        * css_style.pct[]. */
       P_PCT_FIRST,
       P_PCT_LAST = P_PCT_FIRST + CSS_PCT_N - 1,
       /* Text-presentation extensions (Hito 23b-6). The three text-shadow slots are
        * contiguous (dx,dy,color) so expand_shadow writes them as a group. */
       P_FONTFAMILY, P_TEXTTRANSFORM, P_LETTERSPACING, P_WORDSPACING,
       P_SHADOW_DX, P_SHADOW_DY, P_SHADOW_COLOR,
       P_OPACITY, P_VALIGN, P_TEXTINDENT, P_WHITESPACE, P_TABSIZE, P_LISTSTYLE, P_DIRECTION,
       /* Layout / box decoration (Hito 23b-7). Contiguous groups feed the box4-style
        * expanders: insets (T R B L); border widths/styles/colors (each T R B L);
        * box-shadow (dx dy blur spread color inset); flex (grow shrink basis). */
       P_POSITION,
       P_INSET_TOP, P_INSET_RIGHT, P_INSET_BOTTOM, P_INSET_LEFT,
       P_ZINDEX, P_BOXSIZING,
       P_BW_TOP, P_BW_RIGHT, P_BW_BOTTOM, P_BW_LEFT,
       P_BS_TOP, P_BS_RIGHT, P_BS_BOTTOM, P_BS_LEFT,
       P_BC_TOP, P_BC_RIGHT, P_BC_BOTTOM, P_BC_LEFT,
       /* The four border-radius corners, contiguous in CSS corner order
        * (top-left, top-right, bottom-right, bottom-left) so the shorthand
        * expander can write them as a group. */
       P_BORDER_RADIUS, P_RADIUS_TR, P_RADIUS_BR, P_RADIUS_BL,
       P_BSHADOW_DX, P_BSHADOW_DY, P_BSHADOW_BLUR, P_BSHADOW_SPREAD,
       P_BSHADOW_COLOR, P_BSHADOW_INSET,
       P_OUTLINE_W, P_OUTLINE_S, P_OUTLINE_C, P_OUTLINE_OFFSET,
       P_FLEX_GROW, P_FLEX_SHRINK, P_FLEX_BASIS,
       P_ORDER, P_ALIGN_ITEMS, P_ALIGN_SELF, P_ALIGN_CONTENT, P_JUSTIFY_ITEMS,
       P_FLEX_DIR, P_FLEX_WRAP,
       P_GRID_ROWS, P_ROW_GAP, P_GRID_FLOW, P_GRID_COL_SPAN, P_GRID_ROW_SPAN,
       P_FLOAT, P_CLEAR,
        P_VISIBILITY, P_OVERFLOW_X, P_OVERFLOW_Y, P_CURSOR,
        P_TEXT_OVERFLOW, P_WORD_BREAK,
        P_BORDER_COLLAPSE, P_BORDER_SPACING, P_EMPTY_CELLS,
        P_CAPTION_SIDE, P_TABLE_LAYOUT,
        P_FONT_VARIANT, P_HYPHENS, P_USER_SELECT, P_CARET_COLOR,
        P_APPEARANCE, P_POINTER_EVENTS,
        P_BG_REPEAT, P_BG_SIZE, P_BG_CLIP, P_BG_ORIGIN, P_BG_ATTACHMENT,
        P_ISOLATION, P_CONTAIN, P_CONTENT_VISIBILITY, P_IMAGE_RENDERING,
        P_COLOR_SCHEME, P_ACCENT_COLOR, P_PRINT_COLOR_ADJUST, P_FORCED_COLOR_ADJUST,
        P_MIX_BLEND_MODE, P_OBJECT_FIT, P_LIST_STYLE_POS,
        P_FONT_KERNING, P_TEXT_RENDERING, P_FONT_STRETCH,
        P_RESIZE, P_SCROLL_BEHAVIOR, P_TOUCH_ACTION, P_OVERSCROLL_BEHAVIOR,
        P_BACKFACE_VISIBILITY,
        P_TEXTDECO_THICKNESS, P_ASPECT_NUM, P_ASPECT_DEN,
        /* linear-gradient background (2026-07-11). Contiguous group: one declaration
         * emits angle + stop count + the stop colors in lock-step. */
        P_BG_GRAD_ANGLE, P_BG_GRAD_N,
        P_BG_GRAD_C0, P_BG_GRAD_C1, P_BG_GRAD_C2, P_BG_GRAD_C3,
        /* gradient stop positions (R5d): 0-100% stored as 0-1000. P_BG_GRAD_N
         * controls how many are valid. */
        P_BG_GRAD_POS0, P_BG_GRAD_POS1, P_BG_GRAD_POS2, P_BG_GRAD_POS3,
        /* grid-template-columns track sizes (2026-07-11). Contiguous group of
         * CSS_GRID_TRACKS_MAX slots emitted in lock-step with P_GRIDCOLS. */
        P_GRID_TRACK0, P_GRID_TRACK1, P_GRID_TRACK2, P_GRID_TRACK3,
        P_GRID_TRACK4, P_GRID_TRACK5, P_GRID_TRACK6, P_GRID_TRACK7,
        /* transform (M1.2): translate()/translateX()/translateY() px offsets.
         * M1.2b adds scale()/scaleX()/scaleY() (percent) and rotate() (degrees),
         * each its own independent-cascade slot (see css.h). */
        P_TRANSFORM_TX, P_TRANSFORM_TY,
        P_TRANSFORM_SX, P_TRANSFORM_SY, P_TRANSFORM_ROTATE,
        /* M1.2c: skew()/skewX()/skewY() whole degrees + transform-origin percent
         * slots (CSS_LEN_UNSET = 50% center default). */
        P_TRANSFORM_SKX, P_TRANSFORM_SKY, P_TRANSFORM_OX, P_TRANSFORM_OY,
        /* background-image: url(...) (2026-07-16). ival is an INDEX into a small
         * per-parse url table (css_sheet.bg_urls for stylesheet rules, a stack-local
         * table for inline style="") -- css_decl stays int-only, no per-declaration
         * string payload, so the 32768-entry decls[] array does not balloon. -1
         * means the explicit "no image" reset (see expand_bg_image). */
        P_BG_IMAGE_URL,
        /* animation-duration (Phase R1): parsed time in ms. 0 = unset (no animation).
         * Other animation-* properties and @keyframes parsing are follow-up work
         * (the E2E test uses hardcoded keyframes for v1). */
        P_ANIM_DURATION,
        /* @keyframes / animation-* (R1b) */
        P_ANIM_NAME, P_ANIM_ITERS, P_ANIM_DIR, P_ANIM_FILL, P_ANIM_TIMING,
        P_ANIM_DELAY,
        /* filter (Phase R3) */
        P_FILTER_BLUR, P_FILTER_GRAYSCALE, P_FILTER_BRIGHTNESS, P_FILTER_CONTRAST,
        P_FILTER_SEPIA, P_FILTER_INVERT, P_FILTER_SATURATE, P_FILTER_HUE_ROTATE,
        /* filter: drop-shadow (2026-07-19). Contiguous group emitted in
         * lock-step by expand_filter's drop-shadow branch. */
        P_FILTER_DROP_DX, P_FILTER_DROP_DY, P_FILTER_DROP_BLUR, P_FILTER_DROP_COLOR,
        /* -webkit-text-fill-color (2026-07-19, gradient text) */
        P_TEXT_FILL,
        /* SVG `fill` presentation property: colours inline-<svg> shapes without
         * their own fill (the .social svg{fill:#fff} icon-tint pattern). */
        P_SVG_FILL,
        /* backdrop-filter: blur(Npx) (2026-07-19, glassmorphism v1). */
        P_BACKDROP_BLUR,
        /* Background alpha percent from rgba()/hsla() (2026-07-19). */
        P_BG_ALPHA,
        /* background-position (R5a) */
        P_BG_POS_X, P_BG_POS_Y,
        /* multi-layer background-image layer 2 (R5b): second url() behind the first. */
        P_BG_IMAGE_URL2,
        /* radial-gradient flag (R5c): 0=linear(default), 1=radial */
        P_BG_GRAD_RADIAL,
        /* content property (R8) for ::before/::after */
        P_CONTENT,
        /* transition (v1 parse-only, runtime deferred to hito phase-4) */
        P_TRANSITION_DURATION, P_TRANSITION_PROPERTY,
        P_TRANSITION_TIMING, P_TRANSITION_DELAY,
        /* clip: rect(top,right,bottom,left) for positioned boxes (2016-07-30).
         * Each slot carries px, CSS_LEN_UNSET = auto (the border-box edge). */
        P_CLIP_TOP, P_CLIP_RIGHT, P_CLIP_BOTTOM, P_CLIP_LEFT,
        /* Multi-column (2026-08-12). column-gap is not here: it is the same
         * property as the flex/grid gap in CSS Box Alignment and keeps writing
         * P_GAP, which multicol now reads instead of ignoring. */
        P_LINE_CLAMP,
        P_COLUMN_COUNT, P_COLUMN_WIDTH, P_COLUMN_FILL, P_COLUMN_SPAN,
        P_COLRULE_W, P_COLRULE_S, P_COLRULE_C,
        /* Named grid placement (2026-08-14, CSS Grid 1 7.3 + 8.4).
         * P_GRID_AREAS carries an INDEX into the same string pool P_CONTENT uses
         * (the template is one short quoted-string list, exactly the shape that
         * pool holds) -- reusing it keeps one pool to audit instead of two.
         * P_GRID_AREA_NAME carries the item's area name already HASHED to an int,
         * so an item's placement needs no string channel at all. */
        P_GRID_AREAS, P_GRID_AREA_NAME,
        /* background-size's explicit <length-percentage>|auto pair (Backgrounds 3
         * 3.9) and vertical-align's <length-percentage> production (CSS 2.1
         * 10.8.1). Each is the OTHER half of a property whose keyword production
         * already had a slot; they are separate slots because a keyword enum
         * cannot also hold a signed length, and the cascade has to be able to let
         * a later keyword clear an earlier length. */
        P_BG_SIZE_W, P_BG_SIZE_H, P_VALIGN_SHIFT,
        P_NSLOTS };

typedef struct css_decl {
    int prop;       /* P_* */
    int ival;       /* interpreted value (color packed / enum / scale / bool) */
    int important;  /* 1 if the declaration carried !important (higher cascade tier) */
    /* Font-relative component of a <length>, in THOUSANDTHS of an em: the
     * derivative cl_lp.em, scaled like the per-mille percentage channel and for
     * the same reason (the cascade is integer). 0 = the value does not move with
     * the font-size, which is true of every non-length declaration by
     * construction -- only the length emitters ever write it.
     *
     * `ival` stays the value resolved at the INITIAL 16px context, so an element
     * that computes to 16px is unaffected and the fold is a pure correction.
     * See spec/css_length.md section 8. */
    int emil;
    /* CSS Cascade 5 section 7.3: the declaration's value was a CSS-WIDE KEYWORD
     * (initial / inherit / unset / revert / revert-layer), which is valid on
     * EVERY property. The declaration still competes for -- and can win -- its
     * cascade slot; what it does not do is write a value. Leaving the slot at the
     * style's unset default is what makes it mean the right thing: the caller's
     * ancestor merge then supplies the parent's value (`inherit`), or the initial
     * value stands where nothing is inherited (`initial`/`revert`).
     *
     * The point is that the slot is CLAIMED. Dropping the declaration instead --
     * which is what happened before -- handed the slot to a LOWER-specificity
     * rule, so `a{color:#333} a.x{color:inherit}` painted #333 where every other
     * engine paints the parent's colour.
     *
     * 0 = an ordinary declaration. 1 = claim the slot and leave the field alone
     * (the generic dispatch tail, which has no way to know the property's unset
     * default). 2 = claim the slot AND write `ival`, for an emitter that DOES know
     * that default. The distinction is not cosmetic: winning a slot without
     * writing it leaves whatever an EARLIER, lower-specificity declaration already
     * put there, so `.a{width:50%} .a.b{width:auto}` kept the 50%. */
    int wide;
} css_decl;

#endif
