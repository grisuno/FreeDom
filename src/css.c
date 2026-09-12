/*
 * css — pure author-CSS parser + simple cascade. See include/css.h, spec/css.md.
 *
 * Hostile content: never fetches (url()/@-rules dropped), bounded (anti-DoS),
 * fails closed. No global state; the only allocation is the sheet.
 */

#include "css.h"
#include "css_color.h"
#include "css_length.h"
#include "css_values.h"
#include "css_gradient.h"
#include "css_box.h"
#include "css_text.h"
#include "flex_layout.h"  /* fx_grid_area_hash: an area name reduces to one int */
#include "css_select.h"

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Bounds (anti-DoS). A stylesheet beyond these is truncated, never unbounded.
 * CSS_TOK_MAX / CSS_MAX_CLASSES_PER_SEL live in css_select.h (shared with the
 * selector engine).
 *
 * These were 512/2048/384 until a real-world audit (a single vendored, minified
 * Bootstrap 4.5.2 stylesheet -- ~2100 rules, ~3600 individual selectors once
 * comma groups are split, ~2100 declarations) showed CSS_MAX_RULES silently
 * dropping essentially every utility class (.bg-dark, .text-success, ...): they
 * sit near the end of a real compiled stylesheet, past rule #384, so the visible
 * symptom was "the whole page ignores your background/text-color classes" with
 * no error anywhere (truncation here is deliberately silent -- see parse_block's
 * "leave decls; harmless, unreferenced" comment). Raised 16x to comfortably fit
 * one real component-library stylesheet plus a handful of smaller ones (this is
 * still a hard, finite cap -- a hostile/pathological sheet is still bounded, just
 * at a size that matches real pages instead of a toy one). Paired with the
 * per-element style cache in page_view.c's pv_style_cache: with the cascade now
 * O(nsels) per unique element instead of per (element, ancestor-visit) pair,
 * a bigger nsels does not multiply page_view's runtime by every text node. */
/* Initial capacities (anti-DoS hint: start small, grow on demand).
 * Every real browser does this; hardcoding an artificial ceiling is
 * a bug, not a feature. */
#define CSS_INIT_SELS            512u
#define CSS_INIT_DECLS           1024u
/* Free declaration slots guaranteed to be available before a rule's block is
 * interpreted, and the slack that must REMAIN afterwards for the result to be
 * trusted as complete.
 *
 * Without it, a rule parsed while the sheet's array happened to be nearly full lost
 * every declaration after the first few, silently: the array doubled only once it
 * was completely full, so the free space cycled down to 1 and whichever rules landed
 * there were truncated. Measured with the drop log, which reported them as
 * "bad-value" -- a plain `width: 70%` and `margin-left: 20px` appearing as invalid
 * is what exposed it.
 *
 * It must exceed the most slots ANY single declaration can emit (the widest today
 * is the `background` shorthand at 12), so that finishing with this much slack
 * proves no declaration in the rule was refused for lack of room. */
#define CSS_DECL_SLOTS_MIN         32u
#define CSS_INIT_RULES           256u
#define CSS_SELS_PER_GROUP      32
#define CSS_INLINE_DECLS        64u
#define CSS_INLINE_SPEC         (1 << 20)

/* Custom properties (--name: value) + var(--name[, fallback]) (see the "Custom
 * properties" section of spec/css.md). Deliberately simplified vs. real CSS custom
 * property scoping: every `--name` declaration found ANYWHERE in the stylesheet
 * (any rule, any @media) feeds one flat, page-global table (last declaration for a
 * name wins), which covers the overwhelmingly common `:root { --x: ... }` pattern.
 * A value is capped at CSS_TOK_MAX like every other token here (an overlong one
 * could never fit a re-substituted declaration value anyway), and lookups recurse
 * at most CSS_VAR_MAX_DEPTH deep (a chain or cycle beyond that fails the var(),
 * bounding the work to O(depth * CSS_TOK_MAX) -- anti-DoS, never a crash or hang). */
#define CSS_MAX_CUSTOM_PROPS 512u
#define CSS_VAR_MAX_DEPTH    4

/* background-image: url(...) text pool (2026-07-16). A page-global table, same
 * flavour as the custom-property table above: parse time appends the raw url()
 * text and stores the INDEX in the css_decl (int-only, see P_BG_IMAGE_URL); apply
 * time looks the string back up by index. Sized small on purpose (a real page
 * declares far fewer distinct background-image rules than colors/gradients) so
 * it does not multiply CSS_MAX_DECLS' footprint the way embedding the string in
 * every css_decl would. */
#include "css_decl.h"

/* One custom property (--name: value), for var() lookups. Both fields are bounded
 * like every other token buffer here. */
typedef struct css_custom_prop {
    char name[CSS_TOK_MAX];
    char value[CSS_TOK_MAX];
} css_custom_prop;

/* The selector types (css_attr_match/css_compound/css_sel) and their parser/matcher
 * live in css_select.{h,c}. */

typedef struct { size_t start, count; } css_rule;

struct css_sheet {
    css_decl *decls;
    size_t    decls_cap;
    size_t    ndecls;

    css_rule *rules;
    size_t    rules_cap;
    size_t    nrules;

    css_sel  *sels;
    size_t    sels_cap;
    size_t    nsels;

    css_custom_prop custom[CSS_MAX_CUSTOM_PROPS];  /* --name table, page-global */
    size_t          ncustom;
    char            bg_urls[CSS_MAX_BG_URLS][CSS_URL_MAX]; /* background-image url() pool */
    size_t          nbg_urls;
    char            content_urls[64][CSS_URL_MAX];  /* R8: ::before/::after content strings */
    size_t          ncontent_urls;
    /* @keyframes animation blocks (R1b). Bounded anti-DoS. */
    struct {
        char name[CSS_TOK_MAX];
        struct css_keyframe_stop {
            double pct;
            int opacity;       /* -1 = unset */
            int bg_color;      /* -1 = unset, packed 0xRRGGBB */
            int fg_color;      /* -1 = unset, packed 0xRRGGBB */
            int transform_tx;  /* CSS_LEN_UNSET = unset */
            int transform_ty;  /* CSS_LEN_UNSET = unset */
            int transform_sx;  /* 0 = unset (meaning 100% = identity) */
            int transform_sy;  /* 0 = unset */
            int transform_rotate; /* 0 = unset */
        } stops[CSS_MAX_KEYFRAME_STOPS];
        int nstops;
    } keyframes[CSS_MAX_KEYFRAMES];
    size_t          nkeyframes;
    /* @font-face declarations (v1: font-family name + src URL). No I/O, no
     * network — the caller resolves and downloads the URL against the page
     * origin, same as background-image. url() is the only source format that
     * is not discarded (other formats like local() are ignored). */
#define CSS_MAX_FONT_FACES 16
    struct {
        char family[CSS_TOK_MAX];
        char src_url[CSS_URL_MAX];
    } font_faces[CSS_MAX_FONT_FACES];
    size_t          nfont_faces;
};

/* The small ASCII helpers (csel_lower_ch / csel_ci_eq / csel_substr /
 * csel_ident_ch) are shared with the selector engine via css_select.h. */

/* Parses a leading non-negative number (digits + optional fraction). Returns 1 on
 * success, setting *out and *endp to the first unconsumed char. */
static int parse_num(const char *s, double *out, const char **endp) {
    /* Delegates to the canonical CSS <number> grammar so a number means the same
     * thing here as in a length, a colour channel and a transform argument. The
     * private version this replaced required a digit before the decimal point,
     * which silently dropped every `.5`-style value in the stylesheet. */
    return cl_number(s, out, endp);
}

/* --- value interpreters (return -1 / sentinel when the value is unsupported) --- */

/* Like cc_parse but returns packed int with sentinels for currentColor/transparent. */
static int parse_color(const char *v) {
    return cv_parse_color(v);
}

static int interp_color(const char *v) {
    return cv_interp_color(v);
}

/* Whether a parse_color/interp_color result is a VALUE. The two sentinels are
 * negative (CC_COLOR_CURRENT -2, CC_COLOR_TRANSPARENT -3) and only -1 means "not a
 * colour", so every acceptance test written as `>= 0` silently rejected
 * `transparent` and `currentColor` -- which is how a page clears an inherited or UA
 * background, and how it says "match the text colour". 65 declarations in the
 * measured corpus, on every page in it. One predicate so the next colour-valued
 * property cannot get it wrong again. */
static int color_ok(int c) { return cv_color_ok(c); }

/* A CSS-wide keyword (CSS Cascade 5 section 7.3). These are valid on EVERY
 * property and none of them names a value in the property's own grammar, so every
 * value interpreter in this file rejects them -- which is why they are recognised
 * at the two SHARED chokepoints every property funnels through (the generic
 * dispatch tail, and emit_len for the <length-percentage> family) rather than in a
 * per-property table that would go stale on the next property added.
 *
 * `revert`/`revert-layer` roll back to the previous cascade origin. With one author
 * origin and a UA sheet expressed as per-tag defaults rather than as declarations,
 * "the previous origin" IS the unset default here, so they collapse onto the same
 * handling -- correct by construction rather than by approximation. */
static int css_wide_keyword(const char *v) {
    return csel_ci_eq(v, "initial") || csel_ci_eq(v, "inherit") ||
           csel_ci_eq(v, "unset")   || csel_ci_eq(v, "revert")  ||
           csel_ci_eq(v, "revert-layer");
}

/* Alpha (4th) component of the first rgba()/hsla() call inside v, as a percent
 * 0..100; CSS_LEN_UNSET when there is none. Accepts a bare 0..1 float or an N%
 * form -- the same shapes css_color validates (it parses the channel and
 * discards it; the color itself resolves there unchanged). A malformed alpha
 * yields UNSET here AND an invalid color there, so the declaration still fails
 * closed as a whole. */
static int bg_alpha_of(const char *v) {
    return cv_bg_alpha_of(v);
}

static int interp_bg(const char *v) {
    return cv_interp_bg(v);
}

/* Gradient/background-image family lives in css_gradient.c (single owner).
 * Thin wrappers keep existing call sites stable while the cascade
 * decomposes. See spec/css_gradient.md. */

static int expand_bg_image(const char *val, css_decl *dst, int cap,
                           char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap) {
    return cg_expand_bg_image(val, dst, cap, urltab, nurl, urlcap);
}

static int expand_background(const char *val, css_decl *dst, int cap,
                             char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap) {
    return cg_expand_background(val, dst, cap, urltab, nurl, urlcap);
}


/*
 * The context every <length> in the cascade resolves against.
 *
 * The cascade is pure and element-free: it runs before any element is known, so
 * it cannot see a computed font-size and must use the CSS initial context. That
 * is precisely why the ROOT font-size is handled by rewriting `rem` in the
 * source text (rem_rebase, see below) rather than by threading a context here.
 *
 * Viewport units resolve against the NORMALIZED 1920x1080 desktop, never the
 * real window: the cascade runs on hostile content and a computed length must
 * not leak real geometry (only @media width queries see the render width).
 * cl_ctx_initial already encodes that.
 */
/* Length/box/grid/calc value family lives in css_box.c (single owner).
 * Thin wrappers keep existing call sites stable while the cascade
 * decomposes. See spec/css_box.md. */
#define AUTO_REJECT CB_AUTO_REJECT
#define AUTO_VALUE CB_AUTO_VALUE
#define AUTO_RESET CB_AUTO_RESET
#define AUTO_RESET_NONE CB_AUTO_RESET_NONE

static int emit_len(css_decl *dst, int cap, int slot, const char *val,
                    int allow_auto, int allow_neg) {
    return cb_emit_len(dst, cap, slot, val, allow_auto, allow_neg);
}

static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,
                       css_decl *dst, int cap) {
    return cb_expand_box4(val, slot_top, allow_auto, allow_neg, dst, cap);
}

static int expand_box2(const char *val, int slot_start, int slot_end,
                       int allow_auto, int allow_neg, css_decl *dst, int cap) {
    return cb_expand_box2(val, slot_start, slot_end, allow_auto, allow_neg, dst, cap);
}

static int interp_len(const char *v, int allow_auto, int *out) {
    return cb_interp_len(v, allow_auto, out);
}

static int length_px(const char *v, double *px) {
    return cb_length_px(v, px);
}

static int interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_px, int *out_pm) {
    return cb_interp_lp(v, allow_auto, allow_pct, out_px, out_pm);
}

static int lp_can_be_nonneg(int px_val, int pct_pm) {
    return cb_lp_can_be_nonneg(px_val, pct_pm);
}

static int next_ws_token(const char **p, char *tok, size_t cap) {
    return cb_next_ws_token(p, tok, cap);
}

static int interp_align(const char *v) {
    return cb_interp_align(v);
}

static int interp_fontsize_ex(const char *v, int *abs_out) {
    return cb_interp_fontsize_ex(v, abs_out);
}

static int interp_lineheight(const char *v) {
    return cb_interp_lineheight(v);
}

static int interp_weight(const char *v) {
    return cb_interp_weight(v);
}

static int interp_style(const char *v) {
    return cb_interp_style(v);
}

static int interp_textdeco(const char *v) {
    return cb_interp_textdeco(v);
}

static int interp_display(const char *v) {
    return cb_interp_display(v);
}

static int interp_gap(const char *v) {
    return cb_interp_gap(v);
}

static int interp_justify(const char *v) {
    return cb_interp_justify(v);
}

static int interp_gridcols(const char *v) {
    return cb_interp_gridcols(v);
}

static int expand_grid_template_cols(const char *val, css_decl *dst, int cap) {
    return cb_expand_grid_template_cols(val, dst, cap);
}

/* Text-presentation family lives in css_text.c (single owner). Wrappers keep
 * call sites stable. See spec/css_text.md. */
static int interp_fontfamily(const char *v) { return ct_interp_fontfamily(v); }
static int interp_texttransform(const char *v) { return ct_interp_texttransform(v); }
static int interp_opacity(const char *v) { return ct_interp_opacity(v); }
static int expand_valign(const char *val, css_decl *dst, int cap) { return ct_expand_valign(val, dst, cap); }
static int interp_transition_property(const char *v) { return ct_interp_transition_property(v); }
static int interp_whitespace(const char *v) { return ct_interp_whitespace(v); }
static int interp_tabsize(const char *v) { return ct_interp_tabsize(v); }
static int interp_textdeco_style(const char *v) { return ct_interp_textdeco_style(v); }
static int interp_textdeco_thickness(const char *v) { return ct_interp_textdeco_thickness(v); }
static int interp_aspect_ratio(const char *v, int *num, int *den) { return ct_interp_aspect_ratio(v, num, den); }
static int interp_direction(const char *v) { return ct_interp_direction(v); }
static int interp_liststyle(const char *v) { return ct_interp_liststyle(v); }
static int emit_spacing(css_decl *dst, int cap, int slot, const char *val) { return ct_emit_spacing(dst, cap, slot, val); }
static int expand_shadow(const char *val, css_decl *dst, int cap) { return ct_expand_shadow(val, dst, cap); }

/* --- Layout / box decoration (Hito 23b-7) --------------------------------- */

static int interp_position(const char *v) {
    if (csel_ci_eq(v, "static"))   return CSS_POS_STATIC;
    if (csel_ci_eq(v, "relative")) return CSS_POS_RELATIVE;
    if (csel_ci_eq(v, "absolute")) return CSS_POS_ABSOLUTE;
    if (csel_ci_eq(v, "fixed"))    return CSS_POS_FIXED;
    if (csel_ci_eq(v, "sticky"))   return CSS_POS_STICKY;
    return -1;
}

static int interp_boxsizing(const char *v) {
    if (csel_ci_eq(v, "content-box")) return CSS_BOXS_CONTENT;
    if (csel_ci_eq(v, "border-box"))  return CSS_BOXS_BORDER;
    return -1;
}

static int interp_float(const char *v) {
    if (csel_ci_eq(v, "none"))  return CSS_FLOAT_NONE;
    if (csel_ci_eq(v, "left"))  return CSS_FLOAT_LEFT;
    if (csel_ci_eq(v, "right")) return CSS_FLOAT_RIGHT;
    return -1;
}

static int interp_clear(const char *v) {
    if (csel_ci_eq(v, "none"))  return CSS_CLEAR_NONE;
    if (csel_ci_eq(v, "left"))  return CSS_CLEAR_LEFT;
    if (csel_ci_eq(v, "right")) return CSS_CLEAR_RIGHT;
    if (csel_ci_eq(v, "both"))  return CSS_CLEAR_BOTH;
    return -1;
}

/* --- visibility / overflow / cursor / text-overflow / word-break ---------- */

static int interp_visibility(const char *v) {
    if (csel_ci_eq(v, "visible"))  return CSS_VIS_VISIBLE;
    if (csel_ci_eq(v, "hidden"))   return CSS_VIS_HIDDEN;
    if (csel_ci_eq(v, "collapse")) return CSS_VIS_COLLAPSE;
    return -1;
}

static int interp_overflow(const char *v) {
    if (csel_ci_eq(v, "visible")) return CSS_OF_VISIBLE;
    if (csel_ci_eq(v, "hidden"))  return CSS_OF_HIDDEN;
    if (csel_ci_eq(v, "clip"))    return CSS_OF_HIDDEN; /* clip: like hidden, never scrolls */
    if (csel_ci_eq(v, "scroll"))  return CSS_OF_SCROLL;
    if (csel_ci_eq(v, "auto"))    return CSS_OF_AUTO;
    return -1;
}

/* `overflow` is a shorthand for overflow-x and overflow-y (CSS Overflow 3 3): one
 * token sets both, two tokens set x then y. The two-token form is how a page asks
 * for one scrollable axis (`hidden auto` on wikipedia's wide tables), and rejecting
 * it lost the clipping on BOTH axes, not just the one it could not express. */
static int expand_overflow(const char *val, css_decl *dst, int cap) {
    if (cap < 2) return 0;
    const char *p = val;
    char tx[CSS_TOK_MAX], ty[CSS_TOK_MAX];
    if (!next_ws_token(&p, tx, sizeof tx)) return 0;
    int ox = interp_overflow(tx);
    if (ox < 0) return 0;
    int oy = ox;
    if (next_ws_token(&p, ty, sizeof ty)) {
        oy = interp_overflow(ty);
        if (oy < 0) return 0;
        char extra[CSS_TOK_MAX];
        if (next_ws_token(&p, extra, sizeof extra)) return 0;  /* at most two */
    }
    dst[0].prop = P_OVERFLOW_X; dst[0].ival = ox;
    dst[1].prop = P_OVERFLOW_Y; dst[1].ival = oy;
    return 2;
}

static int interp_cursor(const char *v) {
    if (csel_ci_eq(v, "auto"))        return CSS_CUR_AUTO;
    if (csel_ci_eq(v, "default"))     return CSS_CUR_DEFAULT;
    if (csel_ci_eq(v, "pointer"))     return CSS_CUR_POINTER;
    if (csel_ci_eq(v, "text"))        return CSS_CUR_TEXT;
    if (csel_ci_eq(v, "move"))        return CSS_CUR_MOVE;
    if (csel_ci_eq(v, "not-allowed")) return CSS_CUR_NOT_ALLOWED;
    if (csel_ci_eq(v, "help"))        return CSS_CUR_HELP;
    if (csel_ci_eq(v, "wait"))        return CSS_CUR_WAIT;
    if (csel_ci_eq(v, "crosshair"))   return CSS_CUR_CROSSHAIR;
    if (csel_ci_eq(v, "grab"))        return CSS_CUR_GRAB;
    if (csel_ci_eq(v, "zoom-in"))     return CSS_CUR_ZOOM_IN;
    if (csel_ci_eq(v, "none"))        return CSS_CUR_NONE;
    return -1;
}

static int interp_text_overflow(const char *v) {
    if (csel_ci_eq(v, "clip"))     return CSS_TO_CLIP;
    if (csel_ci_eq(v, "ellipsis")) return CSS_TO_ELLIPSIS;
    return -1;
}

static int interp_word_break(const char *v) {
    if (csel_ci_eq(v, "normal"))     return CSS_WB_NORMAL;
    if (csel_ci_eq(v, "break-all"))  return CSS_WB_BREAK;       /* greedy mid-line break */
    if (csel_ci_eq(v, "break-word")) return CSS_WB_BREAK_WORD;  /* deprecated alias of overflow-wrap:break-word */
    if (csel_ci_eq(v, "keep-all"))   return CSS_WB_NORMAL; /* CJK line-breaking not modeled */
    return -1;
}

static int interp_overflow_wrap(const char *v) {
    if (csel_ci_eq(v, "normal"))     return CSS_WB_NORMAL;
    if (csel_ci_eq(v, "break-word")) return CSS_WB_BREAK_WORD;  /* last-resort break only */
    if (csel_ci_eq(v, "anywhere"))   return CSS_WB_BREAK_WORD;  /* last-resort break only (min-content diff not modeled) */
    return -1;
}

/* border-collapse: collapse/separate. -1 if unknown. */
static int interp_border_collapse(const char *v) {
    if (csel_ci_eq(v, "collapse")) return CSS_BCOL_COLLAPSE;
    if (csel_ci_eq(v, "separate")) return CSS_BCOL_SEPARATE;
    return -1;
}

/* border-spacing: the first length only (a single value: uniform; the two-value
 * h/v form gives horizontal and only the first is honoured in v1). px/em/rem/0,
 * clamped to [0, CSS_BORDER_SPACING_MAX]. -1 unsupported. Also accepts a bare
 * number (no unit) as px (common in shorthand context like "10 5"). */
static int interp_border_spacing(const char *v) {
    char tok[CSS_TOK_MAX];
    size_t k = 0;
    const char *p = v;
    while (*p == ' ' || *p == '\t') ++p;
    while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
    tok[k] = '\0';
    /* Try interp_len first (handles px/em/rem/0/calc). A bare non-zero number
     * fails there, so fall back to a simple numeric parse as px. */
    int px;
    if (interp_len(tok, 0, &px) && px >= 0) {
        if (px > CSS_BORDER_SPACING_MAX) px = CSS_BORDER_SPACING_MAX;
        return px;
    }
    double num;
    const char *end;
    if (parse_num(tok, &num, &end) && *end == '\0' && num >= 0.0) {
        px = css_round_clamp(num, 0, CSS_BORDER_SPACING_MAX);
        return px;
    }
    return -1;
}

/* empty-cells: show/hide. -1 unknown. */
static int interp_empty_cells(const char *v) {
    if (csel_ci_eq(v, "show")) return CSS_EC_SHOW;
    if (csel_ci_eq(v, "hide")) return CSS_EC_HIDE;
    return -1;
}

/* caption-side: top/bottom. -1 unknown. */
static int interp_caption_side(const char *v) {
    if (csel_ci_eq(v, "top"))    return CSS_CS_TOP;
    if (csel_ci_eq(v, "bottom")) return CSS_CS_BOTTOM;
    return -1;
}

/* table-layout: auto/fixed. -1 unknown. */
static int interp_table_layout(const char *v) {
    if (csel_ci_eq(v, "auto"))  return CSS_TL_AUTO;
    if (csel_ci_eq(v, "fixed")) return CSS_TL_FIXED;
    return -1;
}

/* font-variant (subset: only small-caps). normal/small-caps. -1 unknown. */
static int interp_font_variant(const char *v) {
    if (csel_ci_eq(v, "normal"))     return CSS_FV_NORMAL;
    if (csel_ci_eq(v, "small-caps")) return CSS_FV_SMALL_CAPS;
    /* all-small-caps, petite-caps, etc: out of scope, fail closed */
    return -1;
}

/* hyphens: none/manual/auto. -1 unknown. */
static int interp_hyphens(const char *v) {
    if (csel_ci_eq(v, "none"))   return CSS_HY_NONE;
    if (csel_ci_eq(v, "manual")) return CSS_HY_MANUAL;
    if (csel_ci_eq(v, "auto"))   return CSS_HY_AUTO;
    return -1;
}

/* user-select: none/text/all/auto. -1 unknown. */
static int interp_user_select(const char *v) {
    if (csel_ci_eq(v, "none")) return CSS_US_NONE;
    if (csel_ci_eq(v, "text")) return CSS_US_TEXT;
    if (csel_ci_eq(v, "all"))  return CSS_US_ALL;
    if (csel_ci_eq(v, "auto")) return CSS_US_AUTO;
    return -1;
}

/* caret-color: auto -> CSS_LEN_AUTO sentinel; color -> 0xRRGGBB; -1 unset. */
static int interp_caret_color(const char *v) {
    if (csel_ci_eq(v, "auto")) return CSS_LEN_AUTO;
    return parse_color(v);
}

/* appearance (CSS Basic UI 4 section 6.1). Beyond auto/none the property takes the
 * "compat" keywords (button, textfield, checkbox, ...), every one of which names a
 * NATIVE control look. This engine draws one chrome per control type from the
 * element's own tag, so every compat keyword means the same thing it does: keep the
 * native appearance. They resolve to AUTO rather than being dropped, because the
 * declaration's real job on a page is to compete for the slot against a `none` that
 * would strip the chrome. */
static int interp_appearance(const char *v) {
    if (csel_ci_eq(v, "auto")) return CSS_AP_AUTO;
    if (csel_ci_eq(v, "none")) return CSS_AP_NONE;
    static const char *const COMPAT[] = {
        "button", "textfield", "searchfield", "textarea", "checkbox", "radio",
        "menulist", "menulist-button", "listbox", "meter", "progress-bar",
        "push-button", "square-button", "slider-horizontal",
    };
    for (size_t i = 0; i < sizeof COMPAT / sizeof *COMPAT; ++i)
        if (csel_ci_eq(v, COMPAT[i])) return CSS_AP_AUTO;
    return -1;
}

/* pointer-events. Beyond auto/none the property takes the SVG hit-testing keywords
 * (visiblePainted, fill, stroke, all, ...), which differ only in WHICH part of an
 * SVG shape is a hit target. This engine hit-tests a box, not a shape, so every one
 * of them means "this element is a target" -- the same answer as `auto`. Only `none`
 * is a different answer, and it is the one pages actually rely on. */
static int interp_pointer_events(const char *v) {
    if (csel_ci_eq(v, "none")) return CSS_PE_NONE;
    static const char *const TARGET[] = {
        "auto", "all", "visible", "visiblepainted", "visiblefill", "visiblestroke",
        "painted", "fill", "stroke", "inherit-hit",
    };
    for (size_t i = 0; i < sizeof TARGET / sizeof *TARGET; ++i)
        if (csel_ci_eq(v, TARGET[i])) return CSS_PE_AUTO;
    return -1;
}

/* background-repeat: repeat/no-repeat/repeat-x/repeat-y/space/round. -1 unknown. */
static int interp_bg_repeat(const char *v) {
    if (csel_ci_eq(v, "repeat"))    return CSS_BGR_REPEAT;
    if (csel_ci_eq(v, "no-repeat")) return CSS_BGR_NO_REPEAT;
    if (csel_ci_eq(v, "repeat-x"))  return CSS_BGR_REPEAT_X;
    if (csel_ci_eq(v, "repeat-y"))  return CSS_BGR_REPEAT_Y;
    if (csel_ci_eq(v, "space"))     return CSS_BGR_SPACE;
    if (csel_ci_eq(v, "round"))     return CSS_BGR_ROUND;
    return -1;
}
/* background-size: auto/cover/contain. -1 unknown (lengths dropped). */
static int interp_bg_size(const char *v) {
    if (csel_ci_eq(v, "auto"))    return CSS_BGS_AUTO;
    if (csel_ci_eq(v, "cover"))   return CSS_BGS_COVER;
    if (csel_ci_eq(v, "contain")) return CSS_BGS_CONTAIN;
    return -1;
}
/* background-clip: border-box/padding-box/content-box/text. -1 unknown. */
static int interp_bg_clip(const char *v) {
    if (csel_ci_eq(v, "border-box"))   return CSS_BGC_BORDER_BOX;
    if (csel_ci_eq(v, "padding-box"))  return CSS_BGC_PADDING_BOX;
    if (csel_ci_eq(v, "content-box"))  return CSS_BGC_CONTENT_BOX;
    if (csel_ci_eq(v, "text"))         return CSS_BGC_TEXT;
    return -1;
}
/* background-origin: padding-box/border-box/content-box. -1 unknown. */
static int interp_bg_origin(const char *v) {
    if (csel_ci_eq(v, "padding-box"))  return CSS_BGO_PADDING_BOX;
    if (csel_ci_eq(v, "border-box"))   return CSS_BGO_BORDER_BOX;
    if (csel_ci_eq(v, "content-box"))  return CSS_BGO_CONTENT_BOX;
    return -1;
}
/* background-attachment: scroll/fixed/local. -1 unknown. */
static int interp_bg_attachment(const char *v) {
    if (csel_ci_eq(v, "scroll")) return CSS_BGA_SCROLL;
    if (csel_ci_eq(v, "fixed"))  return CSS_BGA_FIXED;
    if (csel_ci_eq(v, "local"))  return CSS_BGA_LOCAL;
    return -1;
}
/* isolation: auto/isolate. -1 unknown. */
static int interp_isolation(const char *v) {
    if (csel_ci_eq(v, "auto"))    return CSS_ISO_AUTO;
    if (csel_ci_eq(v, "isolate")) return CSS_ISO_ISOLATE;
    return -1;
}
/* contain: none/strict/content / space-separated size layout style paint. */
static int interp_contain(const char *v) {
    if (csel_ci_eq(v, "none"))    return 0;
    if (csel_ci_eq(v, "strict"))  return CSS_CONTAIN_SIZE|CSS_CONTAIN_LAYOUT|CSS_CONTAIN_STYLE|CSS_CONTAIN_PAINT;
    if (csel_ci_eq(v, "content")) return CSS_CONTAIN_LAYOUT|CSS_CONTAIN_STYLE|CSS_CONTAIN_PAINT;
    int mask = 0;
    const char *p = v;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char tok[CSS_TOK_MAX];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
        tok[k] = '\0';
        if (csel_ci_eq(tok, "size"))   mask |= CSS_CONTAIN_SIZE;
        else if (csel_ci_eq(tok, "layout")) mask |= CSS_CONTAIN_LAYOUT;
        else if (csel_ci_eq(tok, "style"))  mask |= CSS_CONTAIN_STYLE;
        else if (csel_ci_eq(tok, "paint"))  mask |= CSS_CONTAIN_PAINT;
    }
    return mask;
}
/* content-visibility: visible/auto/hidden. -1 unknown. */
static int interp_content_visibility(const char *v) {
    if (csel_ci_eq(v, "visible")) return CSS_CV_VISIBLE;
    if (csel_ci_eq(v, "auto"))    return CSS_CV_AUTO;
    if (csel_ci_eq(v, "hidden"))  return CSS_CV_HIDDEN;
    return -1;
}
/* image-rendering: auto/pixelated/crisp-edges. -1 unknown. */
static int interp_image_rendering(const char *v) {
    if (csel_ci_eq(v, "auto"))        return CSS_IR_AUTO;
    if (csel_ci_eq(v, "pixelated"))   return CSS_IR_PIXELATED;
    if (csel_ci_eq(v, "crisp-edges")) return CSS_IR_CRISP_EDGES;
    return -1;
}
/* color-scheme: normal/light/dark; multi-keyword "light dark" -> first wins. -1 unknown. */
static int interp_color_scheme(const char *v) {
    if (csel_ci_eq(v, "normal")) return CSS_CSH_NORMAL;
    if (csel_ci_eq(v, "light"))  return CSS_CSH_LIGHT;
    if (csel_ci_eq(v, "dark"))   return CSS_CSH_DARK;
    const char *p = v;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char tok[CSS_TOK_MAX];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
        tok[k] = '\0';
        if (csel_ci_eq(tok, "light")) return CSS_CSH_LIGHT;
        if (csel_ci_eq(tok, "dark"))  return CSS_CSH_DARK;
    }
    return -1;
}
/* accent-color: auto -> CSS_LEN_AUTO; color -> 0xRRGGBB; -1 unknown. */
static int interp_accent_color(const char *v) {
    if (csel_ci_eq(v, "auto")) return CSS_LEN_AUTO;
    return parse_color(v);
}
/* print-color-adjust: economy/exact. -1 unknown. */
static int interp_print_color_adjust(const char *v) {
    if (csel_ci_eq(v, "economy")) return CSS_PCA_ECONOMY;
    if (csel_ci_eq(v, "exact"))   return CSS_PCA_EXACT;
    return -1;
}
/* forced-color-adjust: auto/none. -1 unknown. */
static int interp_forced_color_adjust(const char *v) {
    if (csel_ci_eq(v, "auto")) return CSS_FCA_AUTO;
    if (csel_ci_eq(v, "none")) return CSS_FCA_NONE;
    return -1;
}

/* mix-blend-mode: normal/multiply/screen/… -1 unknown. */
static int interp_mix_blend_mode(const char *v) {
    if (csel_ci_eq(v, "normal"))       return CSS_MB_NORMAL;
    if (csel_ci_eq(v, "multiply"))     return CSS_MB_MULTIPLY;
    if (csel_ci_eq(v, "screen"))       return CSS_MB_SCREEN;
    if (csel_ci_eq(v, "overlay"))      return CSS_MB_OVERLAY;
    if (csel_ci_eq(v, "darken"))       return CSS_MB_DARKEN;
    if (csel_ci_eq(v, "lighten"))      return CSS_MB_LIGHTEN;
    if (csel_ci_eq(v, "color-dodge"))  return CSS_MB_COLOR_DODGE;
    if (csel_ci_eq(v, "color-burn"))   return CSS_MB_COLOR_BURN;
    if (csel_ci_eq(v, "difference"))   return CSS_MB_DIFFERENCE;
    if (csel_ci_eq(v, "exclusion"))    return CSS_MB_EXCLUSION;
    if (csel_ci_eq(v, "hue"))          return CSS_MB_HUE;
    if (csel_ci_eq(v, "saturation"))   return CSS_MB_SATURATION;
    if (csel_ci_eq(v, "color"))        return CSS_MB_COLOR;
    if (csel_ci_eq(v, "luminosity"))   return CSS_MB_LUMINOSITY;
    return -1;
}
/* object-fit: fill/contain/cover/none/scale-down. -1 unknown. */
static int interp_object_fit(const char *v) {
    if (csel_ci_eq(v, "fill"))        return CSS_OFI_FILL;
    if (csel_ci_eq(v, "contain"))     return CSS_OFI_CONTAIN;
    if (csel_ci_eq(v, "cover"))       return CSS_OFI_COVER;
    if (csel_ci_eq(v, "none"))        return CSS_OFI_NONE;
    if (csel_ci_eq(v, "scale-down"))  return CSS_OFI_SCALE_DOWN;
    return -1;
}
/* list-style-position: inside/outside. -1 unknown. */
static int interp_list_style_pos(const char *v) {
    if (csel_ci_eq(v, "inside"))  return CSS_LP_INSIDE;
    if (csel_ci_eq(v, "outside")) return CSS_LP_OUTSIDE;
    return -1;
}
/* font-kerning: auto/normal/none. -1 unknown. */
static int interp_font_kerning(const char *v) {
    if (csel_ci_eq(v, "auto"))   return CSS_FK_AUTO;
    if (csel_ci_eq(v, "normal")) return CSS_FK_NORMAL;
    if (csel_ci_eq(v, "none"))   return CSS_FK_NONE;
    return -1;
}
/* text-rendering: auto/optimizeSpeed/optimizeLegibility/geometricPrecision. -1 unknown. */
static int interp_text_rendering(const char *v) {
    if (csel_ci_eq(v, "auto"))                return CSS_TR_AUTO;
    if (csel_ci_eq(v, "optimizeSpeed"))       return CSS_TR_OPTIMIZE_SPEED;
    if (csel_ci_eq(v, "optimizeLegibility"))  return CSS_TR_OPTIMIZE_LEGIBILITY;
    if (csel_ci_eq(v, "geometricPrecision"))  return CSS_TR_GEOMETRIC_PRECISION;
    return -1;
}
/* font-stretch: normal/condensed/expanded/etc. -1 unknown. */
static int interp_font_stretch(const char *v) {
    if (csel_ci_eq(v, "normal"))             return CSS_FS_NORMAL;
    if (csel_ci_eq(v, "condensed"))          return CSS_FS_CONDENSED;
    if (csel_ci_eq(v, "expanded"))           return CSS_FS_EXPANDED;
    if (csel_ci_eq(v, "ultra-condensed"))    return CSS_FS_ULTRA_CONDENSED;
    if (csel_ci_eq(v, "extra-condensed"))    return CSS_FS_EXTRA_CONDENSED;
    if (csel_ci_eq(v, "semi-condensed"))     return CSS_FS_SEMI_CONDENSED;
    if (csel_ci_eq(v, "semi-expanded"))      return CSS_FS_SEMI_EXPANDED;
    if (csel_ci_eq(v, "extra-expanded"))     return CSS_FS_EXTRA_EXPANDED;
    if (csel_ci_eq(v, "ultra-expanded"))     return CSS_FS_ULTRA_EXPANDED;
    return -1;
}
/* resize: none/both/horizontal/vertical. -1 unknown. */
static int interp_resize(const char *v) {
    if (csel_ci_eq(v, "none"))        return CSS_RS_NONE;
    if (csel_ci_eq(v, "both"))        return CSS_RS_BOTH;
    if (csel_ci_eq(v, "horizontal"))  return CSS_RS_HORIZONTAL;
    if (csel_ci_eq(v, "vertical"))    return CSS_RS_VERTICAL;
    return -1;
}
/* scroll-behavior: auto/smooth. -1 unknown. */
static int interp_scroll_behavior(const char *v) {
    if (csel_ci_eq(v, "auto"))   return CSS_SB_AUTO;
    if (csel_ci_eq(v, "smooth")) return CSS_SB_SMOOTH;
    return -1;
}
/* touch-action: auto/none/manipulation. -1 unknown. */
static int interp_touch_action(const char *v) {
    if (csel_ci_eq(v, "auto"))         return CSS_TA_AUTO;
    if (csel_ci_eq(v, "none"))         return CSS_TA_NONE;
    if (csel_ci_eq(v, "manipulation")) return CSS_TA_MANIPULATION;
    return -1;
}
/* overscroll-behavior: auto/contain/none. -1 unknown. */
static int interp_overscroll_behavior(const char *v) {
    if (csel_ci_eq(v, "auto"))    return CSS_OS_AUTO;
    if (csel_ci_eq(v, "contain")) return CSS_OS_CONTAIN;
    if (csel_ci_eq(v, "none"))    return CSS_OS_NONE;
    return -1;
}
/* backface-visibility: visible/hidden. -1 unknown. */
static int interp_backface_visibility(const char *v) {
    if (csel_ci_eq(v, "visible")) return CSS_BF_VISIBLE;
    if (csel_ci_eq(v, "hidden"))  return CSS_BF_HIDDEN;
    return -1;
}
/* Signed integer (z-index/order). Returns 1 with *out (clamped to +-CSS_LEN_MAX),
 * 0 if not a pure integer (auto / floats / units -> dropped, leaving unset). */
static int interp_int(const char *v, int *out) {
    const char *p = v;
    int neg = 0;
    if (*p == '+') ++p; else if (*p == '-') { neg = 1; ++p; }
    if (*p < '0' || *p > '9') return 0;
    long val = 0;
    while (*p >= '0' && *p <= '9') {
        val = val * 10 + (*p - '0');
        if (val > CSS_LEN_MAX) val = CSS_LEN_MAX;
        ++p;
    }
    if (*p != '\0') return 0;   /* trailing fraction/unit: not an integer */
    *out = neg ? -(int)val : (int)val;
    return 1;
}

static int interp_border_style(const char *v) {
    if (csel_ci_eq(v, "none"))   return CSS_BST_NONE;
    if (csel_ci_eq(v, "hidden")) return CSS_BST_HIDDEN;
    if (csel_ci_eq(v, "solid"))  return CSS_BST_SOLID;
    if (csel_ci_eq(v, "dashed")) return CSS_BST_DASHED;
    if (csel_ci_eq(v, "dotted")) return CSS_BST_DOTTED;
    if (csel_ci_eq(v, "double")) return CSS_BST_DOUBLE;
    if (csel_ci_eq(v, "groove")) return CSS_BST_GROOVE;
    if (csel_ci_eq(v, "ridge"))  return CSS_BST_RIDGE;
    if (csel_ci_eq(v, "inset"))  return CSS_BST_INSET;
    if (csel_ci_eq(v, "outset")) return CSS_BST_OUTSET;
    return -1;
}

/* Border/outline width token: thin/medium/thick keywords or a non-negative length.
 * Returns 1 with *out (px >= 0), 0 if unsupported. */
static int interp_border_width(const char *v, int *out) {
    if (csel_ci_eq(v, "thin"))   { *out = 1; return 1; }
    if (csel_ci_eq(v, "medium")) { *out = 3; return 1; }
    if (csel_ci_eq(v, "thick"))  { *out = 5; return 1; }
    int px;
    if (!interp_len(v, 0, &px) || px < 0) return 0;
    *out = px;
    return 1;
}

static int interp_bwidth1(const char *v) {
    int o;
    return interp_border_width(v, &o) ? o : -1;
}

/* border-radius: the first value only (corner-by-corner / elliptical out of scope).
 * px >= 0, or -1 (unsupported: %/units dropped -> stays unset). */
/* Parses a CSS time: "2s" → 2000, "500ms" → 500, "0s" → 0.
 * Returns -1 on invalid/missing unit. */
static int interp_time_ms(const char *v) {
    double d; const char *e;
    if (!parse_num(v, &d, &e)) return -1;
    if (d < 0.0) return -1;
    while (*e == ' ' || *e == '\t') ++e;
    if (strcmp(e, "s") == 0 || strcmp(e, "S") == 0)
        return (int)(d * 1000.0 + 0.5);
    if (strcmp(e, "ms") == 0 || strcmp(e, "MS") == 0 || strcmp(e, "mS") == 0 || strcmp(e, "Ms") == 0)
        return (int)(d + 0.5);
    return -1;
}

/* The `border-radius` shorthand: one to four <length-percentage> corner values
 * in CSS corner order (all / "tl-br tr-bl" / "tl tr-bl br" / "tl tr br bl"),
 * optionally followed by `/` and the vertical radii.
 *
 * The vertical half is PARSED AND DROPPED on purpose: this engine draws a
 * circular corner, so it keeps the horizontal radius rather than failing the
 * whole declaration closed -- losing `border-radius: 50% / 20%` entirely would
 * turn a rounded card into a square one, which is further from the author's
 * intent than a circular approximation of it. */
static int expand_border_radius(const char *val, css_decl *dst, int cap) {
    /* Everything after '/' is the vertical radius set: cut it off. */
    char horiz[CSS_TOK_MAX];
    size_t hn = 0;
    for (const char *q = val; *q != '\0' && *q != '/' && hn + 1 < sizeof horiz; ++q)
        horiz[hn++] = *q;
    horiz[hn] = '\0';
    return expand_box4(horiz, P_BORDER_RADIUS, 0, 0, dst, cap);
}

/* One corner longhand (border-top-left-radius and friends). Same elliptical
 * simplification as the shorthand: `8px 4px` keeps the horizontal 8px. */
static int emit_radius_corner(css_decl *dst, int cap, int slot, const char *val) {
    char tok[CSS_TOK_MAX];
    const char *p = val;
    if (!next_ws_token(&p, tok, sizeof tok)) return 0;
    return emit_len(dst, cap, slot, tok, 0, 0);
}

/* token classifiers for the per-category border-{width,style,color} quad expanders. */
static int interp_bw_tok(const char *t, int *o) { return interp_border_width(t, o); }
static int interp_bs_tok(const char *t, int *o) { int r = interp_border_style(t); if (r < 0) return 0; *o = r; return 1; }
static int interp_bc_tok(const char *t, int *o) { int r = interp_color(t); if (!color_ok(r)) return 0; *o = r; return 1; }

typedef int (*tok_interp)(const char *tok, int *out);

/* Expands a 1-4 value box property (CSS order all / `v h` / `t h b` / `t r b l`) over
 * a token classifier f into the four contiguous slots from slot_top. Any unsupported
 * token drops the WHOLE shorthand (fail closed). Returns the number written (<= cap). */
static int expand_quad(const char *val, int slot_top, tok_interp f, css_decl *dst, int cap) {
    int vals[4], nv = 0;
    const char *p = val;
    char tok[CSS_TOK_MAX];
    while (nv < 4 && next_ws_token(&p, tok, sizeof tok)) {
        int o;
        if (!f(tok, &o)) return 0;
        vals[nv++] = o;
    }
    if (nv == 0) return 0;
    int top, right, bottom, left;
    switch (nv) {
        case 1: top = right = bottom = left = vals[0]; break;
        case 2: top = bottom = vals[0]; right = left = vals[1]; break;
        case 3: top = vals[0]; right = left = vals[1]; bottom = vals[2]; break;
        default: top = vals[0]; right = vals[1]; bottom = vals[2]; left = vals[3]; break;
    }
    int sides[4] = { top, right, bottom, left };
    int n = 0;
    for (int s = 0; s < 4 && n < cap; ++s) { dst[n].prop = slot_top + s; dst[n].ival = sides[s]; ++n; }
    return n;
}

/* Classifies a `border`/`outline` shorthand value into an optional width, style and
 * color (each at most once, any order). An unrecognised token drops the whole edge
 * (fail closed). url() is dropped (never fetch). Returns 1 if any part was set. */
static int classify_box_edge(const char *val, int *w, int *hw, int *s, int *hs,
                             int *c, int *hc) {
    *hw = *hs = *hc = 0;
    if (csel_substr(val, "url(", 1)) return 0;
    const char *p = val;
    char tok[CSS_TOK_MAX];
    while (next_ws_token(&p, tok, sizeof tok)) {
        int tmp;
        if (!*hw && interp_border_width(tok, &tmp)) { *w = tmp; *hw = 1; }
        else if (!*hs && (tmp = interp_border_style(tok)) >= 0) { *s = tmp; *hs = 1; }
        else if (!*hc && color_ok(tmp = interp_color(tok))) { *c = tmp; *hc = 1; }
        else return 0;   /* unrecognised token: drop the whole shorthand */
    }
    return (*hw || *hs || *hc);
}

/* border / border-<side> shorthand: sets the present width/style/color for each side
 * named in mask (bit s: 0 top, 1 right, 2 bottom, 3 left). Only the parts given are
 * emitted (omitted longhands stay unset — no initial-value reset). */
static int expand_border_shorthand(const char *val, int mask, css_decl *dst, int cap) {
    int w = 0, s = 0, c = 0, hw, hs, hc;
    if (!classify_box_edge(val, &w, &hw, &s, &hs, &c, &hc)) return 0;
    int n = 0;
    for (int side = 0; side < 4; ++side) {
        if (!(mask & (1 << side))) continue;
        if (hw && n < cap) { dst[n].prop = P_BW_TOP + side; dst[n].ival = w; ++n; }
        if (hs && n < cap) { dst[n].prop = P_BS_TOP + side; dst[n].ival = s; ++n; }
        if (hc && n < cap) { dst[n].prop = P_BC_TOP + side; dst[n].ival = c; ++n; }
    }
    return n;
}

static int expand_outline(const char *val, css_decl *dst, int cap) {
    int w = 0, s = 0, c = 0, hw, hs, hc;
    if (!classify_box_edge(val, &w, &hw, &s, &hs, &c, &hc)) return 0;
    int n = 0;
    if (hw && n < cap) { dst[n].prop = P_OUTLINE_W; dst[n].ival = w; ++n; }
    if (hs && n < cap) { dst[n].prop = P_OUTLINE_S; dst[n].ival = s; ++n; }
    if (hc && n < cap) { dst[n].prop = P_OUTLINE_C; dst[n].ival = c; ++n; }
    return n;
}

/* --- Multi-column (CSS Multi-column Layout 1) ------------------------------ */

/* `column-count`: a positive <integer>, or `auto`. Anything else fails closed.
 * The count is clamped to FX_MAX_COLUMNS' worth of sanity here rather than in
 * layout, for the same reason CSS_LEN_MAX lives on the emitter: it is an
 * anti-DoS policy of the box model, not a property of the value. */
static int interp_column_count(const char *v) {
    if (csel_ci_eq(v, "auto")) return 0;
    double num; const char *end;
    if (!cl_number(v, &num, &end)) return -1;
    while (*end == ' ' || *end == '\t') ++end;
    if (*end != '\0') return -1;
    if (num < 1.0) return -1;
    if (num > (double)CSS_COLUMN_COUNT_MAX) num = (double)CSS_COLUMN_COUNT_MAX;
    return (int)(num + 0.5);
}

/* `column-width`: a non-negative <length>, or `auto` (0). */
static int interp_column_width(const char *v) {
    if (csel_ci_eq(v, "auto")) return 0;
    int px;
    if (!interp_len(v, 0, &px) || px < 0) return -1;
    return px;
}

/* `columns` shorthand: <'column-width'> || <'column-count'> in either order,
 * one or two tokens. A bare number is the count, a length is the width, `auto`
 * fills whichever slot is still free -- which is exactly the grammar, and the
 * reason a positional reading would mis-parse the very common `columns: 2`. */
static int expand_columns(const char *val, css_decl *dst, int cap) {
    if (cap < 2) return 0;
    int count = 0, width = 0, have_count = 0, have_width = 0, nauto = 0;
    const char *p = val;
    char tok[CSS_TOK_MAX];
    int ntok = 0;
    while (ntok < 3 && next_ws_token(&p, tok, sizeof tok)) {
        ++ntok;
        if (csel_ci_eq(tok, "auto")) { ++nauto; continue; }
        double num; const char *end;
        if (cl_number(tok, &num, &end) && *end == '\0') {
            if (have_count) return 0;
            int c = interp_column_count(tok);
            if (c <= 0) return 0;
            count = c; have_count = 1;
            continue;
        }
        int wpx = interp_column_width(tok);
        if (wpx <= 0 || have_width) return 0;
        width = wpx; have_width = 1;
    }
    if (ntok == 0 || ntok > 2) return 0;
    if (!have_count && !have_width && nauto == 0) return 0;
    dst[0].prop = P_COLUMN_COUNT; dst[0].ival = count;
    dst[1].prop = P_COLUMN_WIDTH; dst[1].ival = width;
    return 2;
}

static int interp_flex_direction(const char *v);
static int interp_flex_wrap(const char *v);

/* `flex-flow` shorthand: the direction and the wrap keyword in either order,
 * one or two tokens. Fails closed on an unknown token rather than applying half
 * the declaration. */
static int expand_flex_flow(const char *val, css_decl *dst, int cap) {
    int dir = -1, wrap = -1;
    const char *p = val;
    char tok[CSS_TOK_MAX];
    int ntok = 0;
    while (ntok < 3 && next_ws_token(&p, tok, sizeof tok)) {
        ++ntok;
        int d = interp_flex_direction(tok);
        if (d > 0) { if (dir >= 0) return 0; dir = d; continue; }
        int wv = interp_flex_wrap(tok);
        if (wv > 0) { if (wrap >= 0) return 0; wrap = wv; continue; }
        return 0;
    }
    if (ntok == 0 || ntok > 2) return 0;
    int n = 0;
    if (dir  >= 0 && n < cap) { dst[n].prop = P_FLEX_DIR;  dst[n].ival = dir;  ++n; }
    if (wrap >= 0 && n < cap) { dst[n].prop = P_FLEX_WRAP; dst[n].ival = wrap; ++n; }
    return n;
}

/* `column-rule` shorthand: same <line-width> || <line-style> || <color> grammar
 * as `border`/`outline`, so it reuses classify_box_edge rather than repeating it. */
static int expand_column_rule(const char *val, css_decl *dst, int cap) {
    int w = 0, st = 0, c = 0, hw, hs, hc;
    if (!classify_box_edge(val, &w, &hw, &st, &hs, &c, &hc)) return 0;
    int n = 0;
    if (hw && n < cap) { dst[n].prop = P_COLRULE_W; dst[n].ival = w; ++n; }
    if (hs && n < cap) { dst[n].prop = P_COLRULE_S; dst[n].ival = st; ++n; }
    if (hc && n < cap) { dst[n].prop = P_COLRULE_C; dst[n].ival = c; ++n; }
    return n;
}

/* Parse a percentage (or 0..1 float) from inside a filter function's parens.
 * Returns 0..100 (clamped), -1 on error. */
static int interp_filter_pct(const char *s) {
    double d; const char *e;
    if (!parse_num(s, &d, &e)) return -1;
    int pct;
    if (*e == '%') pct = (int)(d + 0.5);
    else pct = (int)(d * 100.0 + 0.5);
    if (pct < 0) pct = 0;
    if (pct > 100) pct = 100;
    return pct;
}

/* Parse a degrees value (e.g. "45deg") from inside a filter function's parens.
 * Returns degrees 0..360 (modulo), or -1 on error. Returns the integer degree
 * nearest the parsed value. */
static int interp_filter_deg(const char *s) {
    double d; const char *e;
    if (!parse_num(s, &d, &e)) return -1;
    if (*e == 'g' && *(e+1) == 'r' && *(e+2) == 'a' && *(e+3) == 'd') d = d * 360.0 / 400.0;
    else if (*e == 'r' && *(e+1) == 'a' && *(e+2) == 'd') d = d * 57.29577951308232; /* 180/pi */
    else if (*e == 't' && *(e+1) == 'u' && *(e+2) == 'r' && *(e+3) == 'n') d = d * 360.0;
    /* otherwise assume deg */
    int deg = (int)(d + 0.5);
    deg = deg % 360;
    if (deg < 0) deg += 360;
    return deg;
}

/* Helper: extract content inside filter(...) parens. Modifies tok by replacing
 * the closing ')' with '\0'. Returns pointer past the opening '(', or NULL. */
static const char *filter_paren_body(char *tok, const char *fn, size_t fnlen) {
    if (strncmp(tok, fn, fnlen) != 0) return NULL;
    char *ep = strchr(tok, '(');
    if (ep == NULL) return NULL;
    char *cp = strrchr(tok, ')');
    if (cp == NULL || cp <= ep) return NULL;
    *cp = '\0';
    return ep + 1;
}

/* transition shorthand: "<property> <duration> <timing> <delay>". v1 handles
 * a single value set (non-comma). Returns the number of decls emitted. */
static int expand_transition(const char *val, css_decl *dst, int cap) {
    if (cap < 4) return 0;
    if (csel_ci_eq(val, "none")) {
        dst[0].prop = P_TRANSITION_PROPERTY; dst[0].ival = 0; return 1;
    }
    char tok[CSS_TOK_MAX];
    char toks[4][CSS_TOK_MAX];
    int nt = 0;
    const char *p = val;
    while (nt < 4 && next_ws_token(&p, tok, sizeof tok)) {
        size_t tl = strlen(tok);
        if (tl >= CSS_TOK_MAX) break;
        memcpy(toks[nt], tok, tl + 1);
        ++nt;
    }
    int nout = 0;
    int has_prop = 0, has_dur = 0, has_timing = 0, has_delay = 0;
    for (int i = 0; i < nt && nout + 1 <= cap; ++i) {
        if (!has_dur) {
            int ms = interp_time_ms(toks[i]);
            if (ms >= 0) {
                if (!has_delay && has_dur) {
                    dst[nout].prop = P_TRANSITION_DELAY; dst[nout].ival = ms;
                    has_delay = 1;
                } else {
                    dst[nout].prop = P_TRANSITION_DURATION; dst[nout].ival = ms;
                    has_dur = 1;
                }
                ++nout;
                continue;
            }
        }
        if (!has_timing && (csel_ci_eq(toks[i], "ease") ||
            csel_ci_eq(toks[i], "linear") || csel_ci_eq(toks[i], "ease-in") ||
            csel_ci_eq(toks[i], "ease-out") || csel_ci_eq(toks[i], "ease-in-out"))) {
            int iv = -1;
            if (csel_ci_eq(toks[i], "ease")) iv = 1;
            else if (csel_ci_eq(toks[i], "linear")) iv = 0;
            else if (csel_ci_eq(toks[i], "ease-in")) iv = 2;
            else if (csel_ci_eq(toks[i], "ease-out")) iv = 3;
            else if (csel_ci_eq(toks[i], "ease-in-out")) iv = 4;
            dst[nout].prop = P_TRANSITION_TIMING; dst[nout].ival = iv;
            has_timing = 1; ++nout;
            continue;
        }
        if (!has_prop) {
            int v = interp_transition_property(toks[i]);
            if (v >= 0) {
                dst[nout].prop = P_TRANSITION_PROPERTY; dst[nout].ival = v;
                has_prop = 1; ++nout;
                continue;
            }
        }
    }
    return nout;
}

/* filter (Phase R3): space-separated function list. Supported: blur(Npx),
 * grayscale(N%), brightness(N), contrast(N), sepia(N), invert(N), saturate(N),
 * hue-rotate(Ndeg). Unknown functions and chained filters beyond the first few
 * are ignored (fail closed). url() never accepted. */
static int expand_filter(const char *val, css_decl *dst, int cap) {
    if (csel_substr(val, "url(", 1)) return 0;
    if (csel_ci_eq(val, "none")) return 0;
    const char *p = val;
    char tok[CSS_TOK_MAX];
    int n = 0;
    while (n + 2 <= cap && next_ws_token(&p, tok, sizeof tok)) {
        if (strncmp(tok, "blur(", 5) == 0) {
            const char *body = filter_paren_body(tok, "blur(", 5);
            if (!body) continue;
            int px;
            if (interp_len(body, 0, &px) && px >= 0) {
                dst[n].prop = P_FILTER_BLUR; dst[n].ival = px; ++n;
            }
        } else if (strncmp(tok, "grayscale(", 10) == 0) {
            const char *body = filter_paren_body(tok, "grayscale(", 10);
            if (!body) continue;
            int pct = interp_filter_pct(body);
            if (pct >= 0) { dst[n].prop = P_FILTER_GRAYSCALE; dst[n].ival = pct; ++n; }
        } else if (strncmp(tok, "brightness(", 11) == 0) {
            const char *body = filter_paren_body(tok, "brightness(", 11);
            if (!body) continue;
            int pct = interp_filter_pct(body);
            if (pct >= 0) { dst[n].prop = P_FILTER_BRIGHTNESS; dst[n].ival = pct; ++n; }
        } else if (strncmp(tok, "contrast(", 9) == 0) {
            const char *body = filter_paren_body(tok, "contrast(", 9);
            if (!body) continue;
            int pct = interp_filter_pct(body);
            if (pct >= 0) { dst[n].prop = P_FILTER_CONTRAST; dst[n].ival = pct; ++n; }
        } else if (strncmp(tok, "sepia(", 6) == 0) {
            const char *body = filter_paren_body(tok, "sepia(", 6);
            if (!body) continue;
            int pct = interp_filter_pct(body);
            if (pct >= 0) { dst[n].prop = P_FILTER_SEPIA; dst[n].ival = pct; ++n; }
        } else if (strncmp(tok, "invert(", 7) == 0) {
            const char *body = filter_paren_body(tok, "invert(", 7);
            if (!body) continue;
            int pct = interp_filter_pct(body);
            if (pct >= 0) { dst[n].prop = P_FILTER_INVERT; dst[n].ival = pct; ++n; }
        } else if (strncmp(tok, "saturate(", 9) == 0) {
            const char *body = filter_paren_body(tok, "saturate(", 9);
            if (!body) continue;
            int pct = interp_filter_pct(body);
            if (pct >= 0) { dst[n].prop = P_FILTER_SATURATE; dst[n].ival = pct; ++n; }
        } else if (strncmp(tok, "hue-rotate(", 11) == 0) {
            const char *body = filter_paren_body(tok, "hue-rotate(", 11);
            if (!body) continue;
            int deg = interp_filter_deg(body);
            if (deg >= 0) { dst[n].prop = P_FILTER_HUE_ROTATE; dst[n].ival = deg; ++n; }
        } else if (strncmp(tok, "drop-shadow(", 12) == 0) {
            /* drop-shadow(<dx> <dy> [<blur>] [<color>]) (2026-07-19). The
             * outer tokenizer is paren-aware, so the whole call is one token.
             * Lengths in declaration order (dx, dy, optional blur >= 0); one
             * optional color anywhere among them. Malformed drops only this
             * function (the rest of the list still applies). Emits the whole
             * 4-decl group in lock-step or nothing. */
            const char *body = filter_paren_body(tok, "drop-shadow(", 12);
            if (!body) continue;
            if (cap - n < 4) continue;
            int lens[3], nl = 0, color = -1, ok = 1;
            const char *q = body;
            char arg[CSS_TOK_MAX];
            while (next_ws_token(&q, arg, sizeof arg)) {
                int px;
                if (interp_len(arg, 0, &px)) {
                    if (nl < 3) lens[nl++] = px;
                    else { ok = 0; break; }
                } else {
                    int cv = parse_color(arg);
                    if (color == -1 && cv >= 0) color = cv;
                    else if (color == -1 && cv == CC_COLOR_CURRENT) color = 0x000000;
                    else { ok = 0; break; }
                }
            }
            if (!ok || nl < 2) continue;
            if (nl >= 3 && lens[2] < 0) continue;   /* negative blur invalid */
            dst[n].prop = P_FILTER_DROP_DX;    dst[n].ival = lens[0]; ++n;
            dst[n].prop = P_FILTER_DROP_DY;    dst[n].ival = lens[1]; ++n;
            dst[n].prop = P_FILTER_DROP_BLUR;  dst[n].ival = nl >= 3 ? lens[2] : 0; ++n;
            dst[n].prop = P_FILTER_DROP_COLOR; dst[n].ival = color == -1 ? 0x000000 : color; ++n;
        }
    }
    return n;
}

/* backdrop-filter / -webkit-backdrop-filter (2026-07-19, glassmorphism v1):
 * same lax space-separated function-list grammar as expand_filter, but v1
 * consumes ONLY blur(Npx); other functions in the list are ignored (so the
 * ubiquitous "blur(10px) saturate(1.8)" combo still gets its blur). url()
 * never accepted; "none" emits nothing. */
static int expand_backdrop_filter(const char *val, css_decl *dst, int cap) {
    if (csel_substr(val, "url(", 1)) return 0;
    if (csel_ci_eq(val, "none")) return 0;
    const char *p = val;
    char tok[CSS_TOK_MAX];
    int n = 0;
    while (n + 1 <= cap && next_ws_token(&p, tok, sizeof tok)) {
        if (strncmp(tok, "blur(", 5) == 0) {
            const char *body = filter_paren_body(tok, "blur(", 5);
            if (!body) continue;
            int px;
            if (interp_len(body, 0, &px) && px >= 0) {
                dst[n].prop = P_BACKDROP_BLUR; dst[n].ival = px; ++n;
            }
        }
    }
    return n;
}

/* background-position (R5a): 1 or 2 values. Keywords map to edges/center; px
 * lengths are used directly. % is not supported in v1 (falls to 0). */
/* background-position (CSS Backgrounds 3 section 3.6).
 *
 * The keywords ARE percentages: left/top = 0%, center = 50%, right/bottom = 100%.
 * And a percentage does not mean "this fraction of the area" -- it aligns that
 * fraction of the IMAGE with the same fraction of the area, so the used offset is
 * (area - image) * pct. Writing the keywords as three private sentinels and
 * rejecting real percentages was two mechanisms for one value type, and it dropped
 * `background-position: 50% 50%` -- the centring idiom -- entirely.
 *
 * Both axes are always emitted, px half and percentage half, like every other
 * <length-percentage> emitter: a partially written pair lets a lower-specificity
 * declaration survive underneath the winner on the half it did not write. */
static int expand_bg_position(const char *val, css_decl *dst, int cap) {
    if (cap < 4) return 0;
    int px[2] = { CSS_LEN_UNSET, CSS_LEN_UNSET };
    int pm[2] = { 0, 0 };
    int seen[2] = { 0, 0 };
    const char *p = val;
    char tok[CSS_TOK_MAX];
    int order = 0;              /* next axis for an axis-agnostic component */
    int any = 0;
    while (next_ws_token(&p, tok, sizeof tok)) {
        int axis = -1, kwpm = -1;
        if (csel_ci_eq(tok, "left"))        { axis = 0; kwpm = 0; }
        else if (csel_ci_eq(tok, "right"))  { axis = 0; kwpm = 1000; }
        else if (csel_ci_eq(tok, "top"))    { axis = 1; kwpm = 0; }
        else if (csel_ci_eq(tok, "bottom")) { axis = 1; kwpm = 1000; }
        else if (csel_ci_eq(tok, "center")) { kwpm = 500; }
        if (kwpm >= 0) {
            if (axis < 0) { axis = (order < 2) ? order : 1; }
            if (axis > 1 || seen[axis]) return 0;
            seen[axis] = 1;
            pm[axis] = kwpm;
            px[axis] = CSS_LEN_UNSET;
            if (axis == order) ++order;
            any = 1;
            continue;
        }
        /* A <length-percentage>. NEGATIVE offsets are the whole point of a sprite
         * sheet: `background-position: -304px -82px` picks a tile out of a strip
         * (38 declarations on one corpus page). A position is an OFFSET, not a
         * size, so the non-negative rule that applies to widths never applied. */
        int lpx, lpm;
        if (!interp_lp(tok, AUTO_REJECT, 1, &lpx, &lpm)) return 0;
        axis = (order < 2) ? order : -1;
        if (axis < 0 || seen[axis]) return 0;
        seen[axis] = 1;
        px[axis] = lpx;
        pm[axis] = lpm;
        ++order;
        any = 1;
    }
    if (!any) return 0;
    /* One component sets the horizontal position; the vertical one is `center`
     * (Backgrounds 3 section 3.6), not "unset". */
    if (!seen[1]) pm[1] = 500;
    dst[0].prop = P_BG_POS_X; dst[0].ival = px[0];
    dst[1].prop = P_BG_POS_Y; dst[1].ival = px[1];
    dst[2].prop = P_PCT_FIRST + CSS_PCT_BG_POS_X; dst[2].ival = pm[0];
    dst[3].prop = P_PCT_FIRST + CSS_PCT_BG_POS_Y; dst[3].ival = pm[1];
    return 4;
}

/* background-size (CSS Backgrounds 3 section 3.9): either a keyword
 * (cover/contain) or one-to-two <length-percentage>|auto components, where one
 * component means "that width, auto height". The keyword and the explicit pair are
 * different kinds of value and take different slots; both are emitted on every
 * declaration so whichever the author wrote CLEARS the other.
 *
 * Only the keyword form existed, so `background-size: 44px 12px` (11 declarations
 * on ddg alone) and every calc() pair were dropped, taking the icon sprites with
 * them. */
static int expand_bg_size(const char *val, css_decl *dst, int cap) {
    if (cap < 5) return 0;
    int kw = interp_bg_size(val);
    int w = CSS_LEN_UNSET, h = CSS_LEN_UNSET, wp = 0, hp = 0;
    if (kw == CSS_BGS_COVER || kw == CSS_BGS_CONTAIN) {
        /* A keyword sizes both axes; the explicit pair must not survive under it. */
    } else {
        const char *p = val;
        char tok[CSS_TOK_MAX];
        int n = 0;
        int comp_px[2] = { CSS_LEN_AUTO, CSS_LEN_AUTO };
        int comp_pm[2] = { 0, 0 };
        while (n < 2 && next_ws_token(&p, tok, sizeof tok)) {
            if (csel_ci_eq(tok, "auto")) { comp_px[n] = CSS_LEN_AUTO; ++n; continue; }
            int lpx, lpm;
            if (!interp_lp(tok, AUTO_REJECT, 1, &lpx, &lpm) ||
                !lp_can_be_nonneg(lpx, lpm))
                return 0;                       /* a size cannot be negative */
            comp_px[n] = lpx;
            comp_pm[n] = lpm;
            ++n;
        }
        if (n == 0) return 0;
        char extra[CSS_TOK_MAX];
        if (next_ws_token(&p, extra, sizeof extra)) return 0;   /* at most two */
        w = comp_px[0]; wp = comp_pm[0];
        h = (n == 2) ? comp_px[1] : CSS_LEN_AUTO;
        hp = (n == 2) ? comp_pm[1] : 0;
        kw = CSS_BGS_UNSET;
    }
    dst[0].prop = P_BG_SIZE;   dst[0].ival = kw;
    dst[1].prop = P_BG_SIZE_W; dst[1].ival = w;
    dst[2].prop = P_BG_SIZE_H; dst[2].ival = h;
    dst[3].prop = P_PCT_FIRST + CSS_PCT_BG_SIZE_W; dst[3].ival = wp;
    dst[4].prop = P_PCT_FIRST + CSS_PCT_BG_SIZE_H; dst[4].ival = hp;
    return 5;
}

/* R8: emit a content string into the pool, storing its index in ival (-1 = none). */
static int emit_content(css_decl *dst, int cap, const char *str,
                        char (*contenttab)[CSS_URL_MAX], size_t *ncontent, size_t contentcap) {
    if (cap < 1) return 0;
    dst[0].prop = P_CONTENT;
    if (str == NULL || *ncontent >= contentcap) { dst[0].ival = -1; return 1; }
    memcpy(contenttab[*ncontent], str, strlen(str) + 1);
    dst[0].ival = (int)*ncontent;
    ++*ncontent;
    return 1;
}

/* R8: content property. Extracts quoted string, stores in content pool, emits
 * P_CONTENT with pool index. Returns 1 if parsed. */
static int expand_content(const char *val, css_decl *dst, int cap,
                          char (*contenttab)[CSS_URL_MAX], size_t *ncontent, size_t contentcap) {
    if (cap < 1) return 0;
    if (csel_ci_eq(val, "none") || csel_ci_eq(val, "normal")) return 0;
    if (csel_substr(val, "url(", 1)) return 0;
    int q = (val[0] == '"' || val[0] == '\'') ? val[0] : 0;
    if (!q) return 0;
    size_t len = strlen(val);
    /* len == 2 is the EMPTY string, `content: ""`, which is valid and meaningful:
     * it is how an author makes a pseudo-element exist so that its own box
     * properties (a decorative bar, an icon, a clearfix) have something to apply
     * to. Requiring three characters dropped it. */
    if (len < 2 || val[len-1] != q) return 0;
    size_t inner_len = len - 2;
    char buf[CSS_URL_MAX];
    if (inner_len >= sizeof buf) inner_len = sizeof buf - 1;
    memcpy(buf, val + 1, inner_len);
    buf[inner_len] = '\0';
    return emit_content(dst, cap, buf, contenttab, ncontent, contentcap);
}


/* grid-template-areas (CSS Grid 1 7.3): the value is a list of quoted strings, one
 * per grid row. It is stored VERBATIM in the shared string pool and parsed into a
 * cell grid later, by flex_layout, where the geometry lives -- the cascade's job is
 * only to decide which declaration wins.
 *
 * `none` resets it to the empty string (an explicit "no template" that overrides a
 * lower-tier declaration, which is why it emits rather than returning 0). Anything
 * with no quoted string in it, or longer than the cap, is DROPPED: half a template
 * would place items against a grid the author never wrote. url() is refused like
 * everywhere else -- a template can never be one, and the guard costs nothing. */
static int expand_grid_areas(const char *val, css_decl *dst, int cap,
                             char (*contenttab)[CSS_URL_MAX], size_t *ncontent,
                             size_t contentcap) {
    if (cap < 1) return 0;
    if (csel_substr(val, "url(", 1)) return 0;
    if (csel_ci_eq(val, "none") || csel_ci_eq(val, "normal")) {
        dst[0].prop = P_GRID_AREAS;
        dst[0].ival = -1;
        return 1;
    }
    if (strchr(val, '\'') == NULL && strchr(val, '"') == NULL) return 0;
    size_t len = strlen(val);
    if (len == 0 || len >= CSS_GRID_AREAS_MAX) return 0;
    if (*ncontent >= contentcap) return 0;
    memcpy(contenttab[*ncontent], val, len + 1);
    dst[0].prop = P_GRID_AREAS;
    dst[0].ival = (int)*ncontent;
    ++*ncontent;
    return 1;
}

/* grid-area on an ITEM. CSS Grid 1 8.3 gives the property two shapes: a single
 * <custom-ident> naming an area, and a slash-separated list of grid lines. Only the
 * first is interpreted here (spec/grid_areas.md 4 lists line placement as the
 * explicit out-of-scope point, and the measured corpus uses only names), and the
 * value is reduced to its hash on the spot so an item's placement is one int all
 * the way to the painter. A value containing `/` or a digit is a line-placement
 * form: dropped rather than mistaken for a name. */
static int expand_grid_area(const char *val, css_decl *dst, int cap) {
    if (cap < 1) return 0;
    if (csel_substr(val, "url(", 1)) return 0;
    if (csel_ci_eq(val, "auto") || csel_ci_eq(val, "none")) {
        dst[0].prop = P_GRID_AREA_NAME;
        dst[0].ival = 0;
        return 1;
    }
    if (strchr(val, '/') != NULL) return 0;   /* line placement: out of scope */
    const char *p = val;
    while (*p == ' ' || *p == '\t') ++p;
    /* A CSS custom-ident starts with a letter, underscore or a non-ASCII byte; a
     * leading digit means this is a line number, not a name. */
    if (!((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') ||
          *p == '_' || *p == '-' || (unsigned char)*p >= 0x80)) return 0;
    size_t len = strlen(val);
    if (len >= FX_AREA_NAME_MAX) return 0;
    unsigned h = fx_grid_area_hash(val);
    if (h == 0u) return 0;
    dst[0].prop = P_GRID_AREA_NAME;
    dst[0].ival = (int)h;
    return 1;
}

/* The `grid-template` shorthand (CSS Grid 1 7.4). Two forms reach a real page:
 *
 *   grid-template: <rows> / <columns>            e.g. `auto / 15.5rem minmax(0,1fr)`
 *   grid-template: "a b" 1fr "c d" 1fr / 20% 1fr  (rows interleaved with areas)
 *
 * Both are handled by splitting on the LAST top-level `/` -- top-level because
 * minmax(0,1fr) and repeat(2, 1fr) contain commas and parens but never a bare
 * slash -- and feeding each half to the longhand expander it already has. When the
 * row half contains quoted strings it is ALSO the areas template, which is exactly
 * how the shorthand is defined; expand_grid_areas ignores the track sizes between
 * the strings. Without a slash the whole value is the rows half.
 *
 * `grid` is the same shorthand plus the implicit-track properties this engine does
 * not model, so it routes here too: taking the tracks and areas from it is strictly
 * better than dropping the declaration. */
static int expand_grid_template(const char *val, css_decl *dst, int cap,
                                char (*contenttab)[CSS_URL_MAX], size_t *ncontent,
                                size_t contentcap) {
    if (csel_substr(val, "url(", 1)) return 0;
    if (csel_ci_eq(val, "none")) return 0;

    size_t len = strlen(val);
    if (len == 0 || len >= CSS_GRID_AREAS_MAX) return 0;

    /* Find the last slash that is neither inside parentheses nor inside a string. */
    long slash = -1;
    int depth = 0, quote = 0;
    for (size_t i = 0; i < len; ++i) {
        char ch = val[i];
        if (quote) { if (ch == quote) quote = 0; continue; }
        if (ch == '\'' || ch == '"') { quote = ch; continue; }
        if (ch == '(') ++depth;
        else if (ch == ')') { if (depth > 0) --depth; }
        else if (ch == '/' && depth == 0) slash = (long)i;
    }

    char rows[CSS_GRID_AREAS_MAX], cols[CSS_GRID_AREAS_MAX];
    size_t rlen = (slash >= 0) ? (size_t)slash : len;
    if (rlen >= sizeof rows) return 0;
    memcpy(rows, val, rlen);
    rows[rlen] = '\0';
    cols[0] = '\0';
    if (slash >= 0) {
        size_t clen = len - (size_t)slash - 1;
        if (clen >= sizeof cols) return 0;
        memcpy(cols, val + slash + 1, clen);
        cols[clen] = '\0';
    }

    int n = 0;
    if (cols[0] != '\0' && cap - n >= 1 + CSS_GRID_TRACKS_MAX)
        n += expand_grid_template_cols(cols, dst + n, cap - n);
    if (rows[0] != '\0' && cap - n >= 1) {
        int nrows = interp_gridcols(rows);
        if (nrows > 0) { dst[n].prop = P_GRID_ROWS; dst[n].ival = nrows; ++n; }
    }
    /* Quoted strings in the row half ARE the areas template (7.4). */
    if ((strchr(rows, '\'') != NULL || strchr(rows, '"') != NULL) && cap - n >= 1)
        n += expand_grid_areas(rows, dst + n, cap - n, contenttab, ncontent, contentcap);
    return n;
}

/* box-shadow (single layer): up to four lengths in order dx, dy, blur, spread, an
 * optional color, and an optional `inset` keyword, in any order. Needs >= 2 lengths
 * (dx, dy) or the whole declaration is dropped (fail closed). `none` is an explicit
 * no-shadow. url() dropped: never fetch. Writes the six contiguous P_BSHADOW_* slots. */
static int expand_box_shadow(const char *val, css_decl *dst, int cap) {
    if (cap < 6) return 0;
    if (csel_substr(val, "url(", 1)) return 0;
    int lens[4], nlen = 0, color = 0, have_color = 0, inset = 0;
    if (!csel_ci_eq(val, "none")) {
        const char *p = val;
        char tok[CSS_TOK_MAX];
        while (next_ws_token(&p, tok, sizeof tok)) {
            if (csel_ci_eq(tok, "inset")) { inset = 1; continue; }
            int px;
            if (interp_len(tok, 0, &px)) { if (nlen < 4) lens[nlen++] = px; }
            else if (!have_color) { int cv = parse_color(tok); if (cv != -1) { color = cv; have_color = 1; } }
            /* else: unknown token ignored */
        }
        if (nlen < 2) return 0;   /* need both offsets */
    }
    dst[0].prop = P_BSHADOW_DX;     dst[0].ival = nlen > 0 ? lens[0] : 0;
    dst[1].prop = P_BSHADOW_DY;     dst[1].ival = nlen > 1 ? lens[1] : 0;
    dst[2].prop = P_BSHADOW_BLUR;   dst[2].ival = nlen > 2 ? lens[2] : 0;
    dst[3].prop = P_BSHADOW_SPREAD; dst[3].ival = nlen > 3 ? lens[3] : 0;
    dst[4].prop = P_BSHADOW_COLOR;  dst[4].ival = csel_ci_eq(val, "none") ? -1
                                                : (have_color ? color : CC_COLOR_CURRENT);
    dst[5].prop = P_BSHADOW_INSET;  dst[5].ival = inset;
    return 6;
}

/* flex-grow / flex-shrink: a non-negative number stored x100 (0.5 -> 50), clamped to
 * [0, CSS_FLEX_FACTOR_MAX]. Negative / unparseable -> -1 (dropped, stays unset). */
static int interp_flex_factor(const char *v) {
    double num;
    const char *end;
    if (!parse_num(v, &num, &end) || *end != '\0' || num < 0.0) return -1;
    return css_round_clamp(num * 100.0, 0, CSS_FLEX_FACTOR_MAX);
}

/* flex-basis: `auto`/`content` -> CSS_LEN_AUTO; a non-negative length -> px; a
 * percentage as per-mille encoded negative (e.g. 75% -> -(1000000+750)). Returns 1
 * with *out, 0 if unsupported. */
static int interp_flex_basis(const char *v, int *out) {
    if (csel_ci_eq(v, "auto") || csel_ci_eq(v, "content")) { *out = CSS_LEN_AUTO; return 1; }
    /* Percentage: per-mille encoding so the painter can resolve against the
     * container width (no new IPC field needed). */
    {
        const char *p = v;
        if (*p == '+') ++p;
        double num;
        const char *end;
        if (parse_num(p, &num, &end)) {
            while (*end == ' ' || *end == '\t') ++end;
            if (end[0] == '%' && end[1] == '\0') {
                /* 0% is a valid <percentage> and is Bootstrap's basis on every
                 * column (`flex: 1 1 0%`); rejecting it dropped the whole
                 * shorthand, so the column lost its grow factor too. Only a
                 * NEGATIVE basis is invalid (Flexbox 1 section 7.2.3). */
                if (num < 0.0 || num > 1000.0) return 0;
                double pm = num * 10.0;
                if (pm > 10000.0) pm = 10000.0;
                *out = -(int)(1000000.0 + pm + 0.5);
                return 1;
            }
        }
    }
    int px;
    if (!interp_len(v, 0, &px) || px < 0) return 0;
    *out = px;
    return 1;
}

/* flex shorthand -> the three contiguous P_FLEX_GROW/SHRINK/BASIS slots. Keywords
 * none/auto/initial; otherwise up to three values (a unitless number is grow then
 * shrink; a length/auto is basis). Defaults: shrink 1, basis 0 when a grow is given,
 * else basis auto. */
static int expand_flex(const char *val, css_decl *dst, int cap) {
    if (cap < 3) return 0;
    int grow, shrink, basis;
    if (csel_ci_eq(val, "none"))         { grow = 0;   shrink = 0;   basis = CSS_LEN_AUTO; }
    else if (csel_ci_eq(val, "auto"))    { grow = 100; shrink = 100; basis = CSS_LEN_AUTO; }
    else if (csel_ci_eq(val, "initial")) { grow = 0;   shrink = 100; basis = CSS_LEN_AUTO; }
    else {
        int g = 0, sh = 0, ba = 0, have_g = 0, have_sh = 0, have_ba = 0;
        const char *p = val;
        int ntok = 0;
        char tok[CSS_TOK_MAX];
        while (ntok < 4 && next_ws_token(&p, tok, sizeof tok)) {
            ++ntok;
            double num;
            const char *end;
            /* A unitless number fills the grow slot, then the shrink slot. Once both
             * factors are taken only <'flex-basis'> is left in the grammar, and a
             * unitless ZERO is a valid <length> there -- so `flex: 1 1 0` (one of the
             * most common idioms on the web) means basis 0, not a third factor.
             * interp_flex_basis rejects a bare non-zero number, so `flex: 1 1 10`
             * still fails closed rather than inventing a unit. */
            if (parse_num(tok, &num, &end) && *end == '\0' && !(have_g && have_sh)) {
                if (num < 0.0) return 0;
                int x100 = css_round_clamp(num * 100.0, 0, CSS_FLEX_FACTOR_MAX);
                if (!have_g)       { g = x100;  have_g = 1; }
                else               { sh = x100; have_sh = 1; }
            } else {                                            /* a length / auto */
                int b;
                if (have_ba || !interp_flex_basis(tok, &b)) return 0;
                ba = b; have_ba = 1;
            }
        }
        if (!have_g && !have_ba) return 0;   /* nothing usable */
        grow   = have_g  ? g  : 100;
        shrink = have_sh ? sh : 100;
        basis  = have_ba ? ba : (have_g ? 0 : CSS_LEN_AUTO);
    }
    dst[0].prop = P_FLEX_GROW;   dst[0].ival = grow;
    dst[1].prop = P_FLEX_SHRINK; dst[1].ival = shrink;
    dst[2].prop = P_FLEX_BASIS;  dst[2].ival = basis;
    return 3;
}

/* align-items / align-self / align-content / justify-items keyword. allow_auto is for
 * align-self; allow_dist (space-*) is for align-content. Unknown -> -1 (drop). */
static int interp_align_kw(const char *v, int allow_auto, int allow_dist) {
    if (allow_auto && csel_ci_eq(v, "auto")) return CSS_AK_AUTO;
    if (csel_ci_eq(v, "stretch")) return CSS_AK_STRETCH;
    if (csel_ci_eq(v, "flex-start") || csel_ci_eq(v, "start")) return CSS_AK_START;
    if (csel_ci_eq(v, "flex-end") || csel_ci_eq(v, "end")) return CSS_AK_END;
    if (csel_ci_eq(v, "center")) return CSS_AK_CENTER;
    if (csel_ci_eq(v, "baseline")) return CSS_AK_BASELINE;
    if (allow_dist && csel_ci_eq(v, "space-between")) return CSS_AK_SPACE_BETWEEN;
    if (allow_dist && csel_ci_eq(v, "space-around")) return CSS_AK_SPACE_AROUND;
    if (allow_dist && csel_ci_eq(v, "space-evenly")) return CSS_AK_SPACE_EVENLY;
    return -1;
}

static int interp_flex_direction(const char *v) {
    if (csel_ci_eq(v, "row")) return CSS_FD_ROW;
    if (csel_ci_eq(v, "row-reverse")) return CSS_FD_ROW_REVERSE;
    if (csel_ci_eq(v, "column")) return CSS_FD_COLUMN;
    if (csel_ci_eq(v, "column-reverse")) return CSS_FD_COLUMN_REVERSE;
    return -1;
}

/**
 * 2009 flexbox `box-orient` axis names onto `css_flex_direction`.
 *
 * Contract: the 2009 draft names the main axis, not the direction, so
 * `horizontal`/`inline-axis` mean row and `vertical`/`block-axis` mean
 * column. Modern `row`/`column` spellings are NOT accepted here: they belong
 * to `flex-direction`, and accepting them would merge two grammars. Reached
 * via the strip-prefix-and-ask-again rule (`-webkit-box-orient` strips to
 * `box-orient`), never dispatched under a prefixed name directly.
 */
static int interp_box_orient(const char *v) {
    if (csel_ci_eq(v, "horizontal") || csel_ci_eq(v, "inline-axis")) return CSS_FD_ROW;
    if (csel_ci_eq(v, "vertical") || csel_ci_eq(v, "block-axis")) return CSS_FD_COLUMN;
    return -1;
}

static int interp_flex_wrap(const char *v) {
    if (csel_ci_eq(v, "nowrap")) return CSS_FW_NOWRAP;
    if (csel_ci_eq(v, "wrap")) return CSS_FW_WRAP;
    if (csel_ci_eq(v, "wrap-reverse")) return CSS_FW_WRAP_REVERSE;
    return -1;
}

/* grid-auto-flow: the first row/column axis keyword wins; `dense` ignored. */
static int interp_grid_flow(const char *v) {
    const char *p = v;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char tok[CSS_TOK_MAX];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
        tok[k] = '\0';
        if (csel_ci_eq(tok, "row")) return CSS_GF_ROW;
        if (csel_ci_eq(tok, "column")) return CSS_GF_COLUMN;
        /* dense / other: skip */
    }
    return -1;
}

/* True if s begins with the NUL-terminated prefix pre (case-insensitive), stopping at
 * the first NUL (no out-of-bounds read past a short s). */
static int starts_with_ci(const char *s, const char *pre) {
    for (; *pre != '\0'; ++s, ++pre)
        if (csel_lower_ch(*s) != csel_lower_ch(*pre)) return 0;
    return 1;
}

/* grid-column / grid-row: only the `span N` form is supported -> N (clamped to
 * [1, CSS_GRID_SPAN_MAX]). Line-number / named-line placement is out of scope (-1). */
static int interp_grid_span(const char *v) {
    const char *p = v;
    while (*p == ' ' || *p == '\t') ++p;
    if (!starts_with_ci(p, "span")) return -1;
    p += 4;
    if (*p != ' ' && *p != '\t') return -1;   /* "span" must be followed by a count */
    while (*p == ' ' || *p == '\t') ++p;
    double num;
    const char *end;
    if (!parse_num(p, &num, &end)) return -1;
    while (*end == ' ' || *end == '\t') ++end;
    if (*end != '\0') return -1;
    int n = css_round_clamp(num, 0, CSS_GRID_SPAN_MAX);
    if (n < 1) return -1;
    return n;
}

/* Copies s[a,b) into dst (bounded, NUL-terminated), trimming ASCII whitespace from
 * both ends. Returns the trimmed length, or SIZE_MAX if it does not fit dst. */
static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap) {
    while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == '\r')) ++a;
    while (b > a && (s[b-1] == ' ' || s[b-1] == '\t' || s[b-1] == '\n' || s[b-1] == '\r')) --b;
    size_t n = b - a;
    if (n + 1 > cap) return (size_t)-1;
    memcpy(dst, s + a, n);
    dst[n] = '\0';
    return n;
}

/* Strips a trailing "!important" (case-insensitive, with optional whitespace before
 * '!' and between '!' and the keyword) from val, in place. Returns 1 if found. A '!'
 * that does not begin "!important" is left intact (the value will fail to interpret). */
static int strip_important(char *val) {
    size_t len = strlen(val);
    for (size_t i = len; i-- > 0; ) {
        if (val[i] != '!') continue;
        const char *r = val + i + 1;
        while (*r == ' ' || *r == '\t') ++r;
        if (!csel_ci_eq(r, "important")) return 0;   /* a non-!important '!': leave as-is */
        size_t e = i;
        while (e > 0 && (val[e-1] == ' ' || val[e-1] == '\t')) --e;
        val[e] = '\0';
        return 1;
    }
    return 0;
}

/* --- Custom properties (--name: value) + var(--name[, fallback]) ---------------
 *
 * Deliberately simplified vs. real cascade-scoped custom properties: all collected
 * declarations feed one flat page-global table. Collection, however, is
 * structure-aware (collect_custom_props_scoped, further below): only rules whose
 * enclosing @media blocks match the render context AND whose selector is
 * root-scoped (`:root`, `html`, `body`, the universal selector, or a .class
 * actually present on <html>/<body>) contribute — an inactive theme palette
 * (e.g. a dark palette under
 * `.theme-night` or `@media (prefers-color-scheme: dark)`) must never clobber the
 * active one. resolve_var then substitutes var() references against that table
 * when a declaration's value is interpreted (parse_one_decl), bounded to
 * CSS_VAR_MAX_DEPTH nested lookups so a reference cycle (`--a: var(--a)`) or a
 * long chain fails the declaration instead of recursing/expanding unboundedly. */

/* Scans the declaration span s[a,b) for `--ident : value ;|}` pairs and folds them
 * into tab. A name is recognised only where it cannot be part of a longer
 * identifier (its preceding character, if any, is not itself an identifier
 * character). A later occurrence of a name overwrites an earlier one (last
 * collected wins, approximating the cascade among applicable rules). An overlong
 * name or value (would not fit CSS_TOK_MAX) is dropped, not truncated -- a
 * truncated custom property would silently feed a wrong value to every var() that
 * references it. Bounded to cap entries (extra distinct names are ignored, fail
 * closed, never an overflow). Does NOT reset *ntab: callers accumulate. */
static void collect_custom_decls(const char *s, size_t a, size_t b,
                                 css_custom_prop *tab, size_t cap, size_t *ntab) {
    size_t i = a;
    while (i < b) {
        if (s[i] == '-' && i + 1 < b && s[i + 1] == '-' &&
            (i == a || !csel_ident_ch(s[i - 1]))) {
            size_t j = i + 2;
            while (j < b && csel_ident_ch(s[j])) ++j;
            size_t name_len = j - i;
            size_t k = j;
            while (k < b && (s[k] == ' ' || s[k] == '\t' || s[k] == '\n' || s[k] == '\r')) ++k;
            if (k < b && s[k] == ':' && name_len < CSS_TOK_MAX) {
                size_t v0 = k + 1;
                size_t v = v0;
                while (v < b && s[v] != ';' && s[v] != '}') ++v;
                char namebuf[CSS_TOK_MAX];
                memcpy(namebuf, s + i, name_len);
                namebuf[name_len] = '\0';
                char valbuf[CSS_TOK_MAX];
                size_t vlen = copy_trim(s, v0, v, valbuf, sizeof valbuf);
                if (vlen != (size_t)-1 && vlen > 0) {
                    strip_important(valbuf);
                    size_t slot = *ntab;
                    for (size_t e = 0; e < *ntab; ++e) {
                        if (strcmp(tab[e].name, namebuf) == 0) { slot = e; break; }
                    }
                    if (slot < cap) {
                        memcpy(tab[slot].name, namebuf, name_len + 1);
                        strcpy(tab[slot].value, valbuf);
                        if (slot == *ntab) ++*ntab;
                    }
                }
                i = v;
                continue;
            }
        }
        ++i;
    }
}

/* True when name[0,len) appears as a whole space-separated token in list. */
static int scope_has_class(const char *list, const char *name, size_t len) {
    if (list == NULL || len == 0) return 0;
    const char *p = list;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') ++p;
        const char *t = p;
        while (*p != '\0' && *p != ' ' && *p != '\t') ++p;
        if ((size_t)(p - t) == len && memcmp(t, name, len) == 0) return 1;
    }
    return 0;
}

/* True when the selector s[a,b) is root-scoped: a single compound (no
 * combinators) made only of `:root`, `html`, `body`, `*` and/or `.class` parts
 * whose classes appear in root_scope (the space-separated class list of the
 * document's <html>/<body>). Anything else — an absent theme class, #id, [attr],
 * other pseudos, any descendant scope — is not document-wide: fail closed (a
 * skipped palette degrades to UA defaults, never to the wrong palette). */
static int selector_is_root_scoped(const char *s, size_t a, size_t b,
                                   const char *root_scope) {
    while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == '\r')) ++a;
    while (b > a && (s[b-1] == ' ' || s[b-1] == '\t' || s[b-1] == '\n' || s[b-1] == '\r')) --b;
    if (a >= b) return 0;
    size_t i = a;
    while (i < b) {
        char c = s[i];
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r' ||
            c == '>' || c == '+' || c == '~')
            return 0;                       /* combinator: not document-wide */
        if (c == '*') { ++i; continue; }
        if (c == '.') {
            size_t j = i + 1;
            while (j < b && csel_ident_ch(s[j])) ++j;
            if (j == i + 1 || !scope_has_class(root_scope, s + i + 1, j - i - 1))
                return 0;
            i = j;
            continue;
        }
        if (c == ':') {
            static const char kw[4] = { 'r', 'o', 'o', 't' };
            if (i + 5 > b) return 0;
            for (int k = 0; k < 4; ++k)
                if (csel_lower_ch(s[i + 1 + k]) != kw[k]) return 0;
            if (i + 5 < b && csel_ident_ch(s[i + 5])) return 0;
            i += 5;
            continue;
        }
        if (csel_ident_ch(c)) {
            size_t j = i;
            char t[8];
            size_t k = 0;
            while (j < b && csel_ident_ch(s[j])) {
                if (k + 1 < sizeof t) t[k++] = csel_lower_ch(s[j]);
                ++j;
            }
            t[k] = '\0';
            if (strcmp(t, "html") != 0 && strcmp(t, "body") != 0) return 0;
            i = j;
            continue;
        }
        return 0;                           /* #id, [attr], anything unknown */
    }
    return 1;
}

static int resolve_var_rec(const char *val, size_t vlen, char *out, size_t outcap,
                           size_t *o, const css_custom_prop *tab, size_t ntab, int depth);

/* Appends s[0,n) to out at *o; fails (0) if it would not fit outcap. */
static int var_append(char *out, size_t outcap, size_t *o, const char *s, size_t n) {
    if (*o + n >= outcap) return 0;
    memcpy(out + *o, s, n);
    *o += n;
    return 1;
}

/* Looks up name ("--ident", NUL-terminated) in tab; on a hit, recursively resolves
 * ITS stored value (which may itself reference var()) into out. Returns 1 on a
 * successful (found and resolved) expansion, 0 if not found or the nested
 * resolution failed/overflowed/exceeded depth. */
static int expand_lookup(const char *name, char *out, size_t outcap, size_t *o,
                         const css_custom_prop *tab, size_t ntab, int depth) {
    if (depth >= CSS_VAR_MAX_DEPTH) return 0;
    for (size_t i = 0; i < ntab; ++i) {
        if (strcmp(tab[i].name, name) == 0)
            return resolve_var_rec(tab[i].value, strlen(tab[i].value), out, outcap, o,
                                   tab, ntab, depth + 1);
    }
    return 0;
}

/* Copies val[0,vlen) to out (via *o), expanding every var(...) call found at the
 * top level (recursively, bounded by depth via expand_lookup). Returns 1 if the
 * whole value was resolved and fit within outcap; 0 on an unresolved var() (no
 * matching custom property and no fallback), a malformed/unbalanced var(...), or
 * an overflow -- the caller (resolve_var) then drops the whole declaration, like
 * any other unsupported value (fail closed, never a partially-substituted value). */
static int resolve_var_rec(const char *val, size_t vlen, char *out, size_t outcap,
                           size_t *o, const css_custom_prop *tab, size_t ntab, int depth) {
    size_t i = 0;
    while (i < vlen) {
        if (i + 4 <= vlen && csel_lower_ch(val[i]) == 'v' && csel_lower_ch(val[i + 1]) == 'a' &&
            csel_lower_ch(val[i + 2]) == 'r' && val[i + 3] == '(') {
            size_t j = i + 4;
            int pdepth = 1;
            size_t argstart = j;
            while (j < vlen && pdepth > 0) {
                if (val[j] == '(') ++pdepth;
                else if (val[j] == ')') { if (--pdepth == 0) break; }
                ++j;
            }
            if (pdepth != 0) return 0;             /* unbalanced var(...): invalid */
            size_t argend = j;
            size_t after = j + 1;                  /* past the matching ')' */

            /* Split the argument on the first TOP-LEVEL comma (a fallback like
             * rgb(1,2,3) must not split there). */
            size_t comma = argend;
            int cd = 0;
            for (size_t k = argstart; k < argend; ++k) {
                if (val[k] == '(') ++cd;
                else if (val[k] == ')') --cd;
                else if (val[k] == ',' && cd == 0) { comma = k; break; }
            }
            size_t na = argstart, nb = comma;
            while (na < nb && (val[na] == ' ' || val[na] == '\t')) ++na;
            while (nb > na && (val[nb - 1] == ' ' || val[nb - 1] == '\t')) --nb;
            size_t nlen = nb - na;
            char namebuf[CSS_TOK_MAX];
            if (nlen == 0 || nlen >= sizeof namebuf ||
                val[na] != '-' || na + 1 >= nb || val[na + 1] != '-')
                return 0;                           /* not a custom-property reference */
            memcpy(namebuf, val + na, nlen);
            namebuf[nlen] = '\0';

            if (!expand_lookup(namebuf, out, outcap, o, tab, ntab, depth)) {
                if (comma >= argend) return 0;      /* unresolved, no fallback: invalid */
                size_t fa = comma + 1, fb = argend;
                while (fa < fb && (val[fa] == ' ' || val[fa] == '\t')) ++fa;
                while (fb > fa && (val[fb - 1] == ' ' || val[fb - 1] == '\t')) --fb;
                if (depth >= CSS_VAR_MAX_DEPTH) return 0;
                if (!resolve_var_rec(val + fa, fb - fa, out, outcap, o, tab, ntab, depth + 1))
                    return 0;
            }
            i = after;
            continue;
        }
        if (!var_append(out, outcap, o, val + i, 1)) return 0;
        ++i;
    }
    return 1;
}

/* Entry point: if val contains no "var(" this is a no-op (caller keeps using val
 * directly); otherwise resolves every var() against tab/ntab into out (bounded to
 * outcap, NUL-terminated). Returns 1 on success, 0 if resolution failed or
 * overflowed (caller drops the declaration). */
static int resolve_var(const char *val, char *out, size_t outcap,
                       const css_custom_prop *tab, size_t ntab) {
    if (outcap == 0) return 0;
    size_t o = 0;
    if (!resolve_var_rec(val, strlen(val), out, outcap - 1, &o, tab, ntab, 0)) return 0;
    out[o] = '\0';
    return 1;
}

/* Unitless ratio argument for scale()/scaleX()/scaleY(): a bare signed decimal
 * number (CSS's <number>, no unit), returned as a PERCENT of identity
 * (scale(1) -> 100), matching font_scale's percent convention. A unit suffix,
 * empty string or junk fails closed. */
static int parse_scale_pct(const char *s, int *out) {
    const char *p = s;
    int neg = 0;
    if (*p == '+') ++p;
    else if (*p == '-') { neg = 1; ++p; }
    double num;
    const char *end;
    if (!parse_num(p, &num, &end)) return 0;
    while (*end == ' ' || *end == '\t') ++end;
    if (*end != '\0') return 0;                /* unitless only */
    if (neg) num = -num;
    *out = css_round_clamp(num * 100.0, -CSS_LEN_MAX, CSS_LEN_MAX);
    return 1;
}

/**
 * <angle> in whole degrees (CSS Values 4 6.1).
 *
 * Contract: a number plus any of the four angle units, fractional allowed;
 * the slot stores whole degrees so the result rounds (rotate(.5turn) is 180,
 * rotate(1rad) is 57). A missing unit fails closed, as does junk. Not
 * normalized mod 360 (a static rotation of e.g. 720deg is visually identical
 * to 0deg once fed through cos/sin at paint time).
 */
static int parse_angle_deg(const char *s, int *out) {
    const char *p = s;
    int neg = 0;
    if (*p == '+') ++p;
    else if (*p == '-') { neg = 1; ++p; }
    double num;
    const char *end;
    if (!parse_num(p, &num, &end)) return 0;
    while (*end == ' ' || *end == '\t') ++end;
    double deg;
    if (csel_ci_eq(end, "deg")) deg = num;
    else if (csel_ci_eq(end, "grad")) deg = num * 0.9;
    else if (csel_ci_eq(end, "rad")) deg = num * (180.0 / 3.14159265358979323846);
    else if (csel_ci_eq(end, "turn")) deg = num * 360.0;
    else return 0;
    if (neg) deg = -deg;
    *out = css_round_clamp(deg, -CSS_LEN_MAX, CSS_LEN_MAX);
    return 1;
}

enum { TR_LIST_MAX = 8 };

enum {
    SPEC_TX = 1u, SPEC_TY = 2u, SPEC_SX = 4u, SPEC_SY = 8u,
    SPEC_ROT = 16u, SPEC_SKX = 32u, SPEC_SKY = 64u,
    SPEC_ALL7 = SPEC_TX | SPEC_TY | SPEC_SX | SPEC_SY | SPEC_ROT | SPEC_SKX | SPEC_SKY
};

/**
 * Right-multiply 2D affine matrices: out = l * r (r applies first).
 *
 * Contract: matrices are {a,b,c,d,e,f} with x' = a*x + c*y + e and
 * y' = b*x + d*y + f, the layout expand_transform's matrix() branch
 * decomposes. Pure arithmetic, no allocation, no I/O.
 */
static void tr_mul(double out[6], const double l[6], const double r[6]) {
    double a = l[0] * r[0] + l[2] * r[1];
    double b = l[1] * r[0] + l[3] * r[1];
    double c = l[0] * r[2] + l[2] * r[3];
    double d = l[1] * r[2] + l[3] * r[3];
    double e = l[0] * r[4] + l[2] * r[5] + l[4];
    double f = l[1] * r[4] + l[3] * r[5] + l[5];
    out[0] = a; out[1] = b; out[2] = c; out[3] = d; out[4] = e; out[5] = f;
}

/**
 * QR-decompose an affine matrix into whole px/percent/degree slots.
 *
 * Contract: the matrix() branch's math, shared so the single-function and
 * list paths cannot disagree. Skew lands on skx only (the decomposition
 * convention: a shear pair has a family of factorizations and this one pins
 * sky to zero); skewY inside a multi-function list is therefore approximated
 * and documented as such in expand_transform_list. Returns 0 when singular
 * (zero first column or zero determinant): the caller falls back or fails.
 */
static int tr_decompose(const double m[6], int *tx, int *ty, int *rot,
                        int *sx, int *sy, int *skx) {
    double r11 = hypot(m[0], m[1]);
    double det = m[0] * m[3] - m[1] * m[2];
    if (r11 < 1e-9 || det == 0.0) return 0;
    const double rad2deg = 180.0 / 3.14159265358979323846;
    double r12 = (m[0] * m[2] + m[1] * m[3]) / r11;
    *tx = css_round_clamp(m[4], -CSS_LEN_MAX, CSS_LEN_MAX);
    *ty = css_round_clamp(m[5], -CSS_LEN_MAX, CSS_LEN_MAX);
    *rot = css_round_clamp(atan2(m[1], m[0]) * rad2deg, -CSS_LEN_MAX, CSS_LEN_MAX);
    *sx = css_round_clamp(r11 * 100.0, -CSS_LEN_MAX, CSS_LEN_MAX);
    *sy = css_round_clamp(det / r11 * 100.0, -CSS_LEN_MAX, CSS_LEN_MAX);
    *skx = css_round_clamp(atan(r12 / r11) * rad2deg, -CSS_LEN_MAX, CSS_LEN_MAX);
    return 1;
}

/**
 * Parse matrix(a,b,c,d,e,f): six comma-separated unitless numbers.
 *
 * Contract: the matrix() branch's argument grammar, shared with the list
 * path. Comma count must be exactly five; each argument is a bare signed
 * decimal. Anything else fails closed.
 */
static int parse_matrix6(const char *p, size_t argn, double m6[6]) {
    size_t k = 0;
    for (int arg = 0; arg < 6; ++arg) {
        char tok[CSS_TOK_MAX];
        size_t stop = argn;
        for (size_t q = k; q < argn; ++q) {
            if (p[q] == ',') { stop = q; break; }
        }
        if ((arg < 5) != (stop < argn)) return 0;
        if (copy_trim(p, k, stop, tok, sizeof tok) == (size_t)-1 || tok[0] == '\0')
            return 0;
        const char *tp = tok;
        int neg = 0;
        if (*tp == '+') ++tp;
        else if (*tp == '-') { neg = 1; ++tp; }
        const char *tend;
        if (!parse_num(tp, &m6[arg], &tend) || *tend != '\0') return 0;
        if (neg) m6[arg] = -m6[arg];
        k = stop + 1;
    }
    return 1;
}

/**
 * Split a top-level comma list honouring paren depth.
 *
 * Contract: calc()/min()/max() nest commas that must not split arguments, so
 * the scan tracks depth and only cuts at depth zero. Writes at most max spans
 * as [starts[i], stops[i]) offsets into s; returns the span count, or -1 when
 * more than max spans appear. Empty spans are kept (the caller's per-kind
 * validation rejects them), so a trailing comma fails closed downstream.
 */
static int split_top_args(const char *s, size_t n, size_t *starts, size_t *stops,
                          int max) {
    int cnt = 0;
    size_t i = 0;
    while (i < n) {
        while (i < n && (s[i] == ' ' || s[i] == '\t')) ++i;
        if (i >= n) break;
        if (cnt >= max) return -1;
        starts[cnt] = i;
        int depth = 0;
        while (i < n && (depth > 0 || s[i] != ',')) {
            if (s[i] == '(') ++depth;
            else if (s[i] == ')') --depth;
            ++i;
        }
        stops[cnt] = i;
        ++cnt;
        if (i < n && s[i] == ',') ++i;
    }
    return cnt;
}

/**
 * transform FUNCTION LIST (CSS Transforms 1 3).
 *
 * Contract: space-separated functions apply in order and compose into one
 * affine matrix, QR-decomposed into the seven slots (shared with matrix()).
 * Only slots a function of the list specifies are emitted, so a list never
 * invents a phantom axis (translateX stays single-axis, like the legacy
 * single path); translate percent halves ride as ever, both halves always.
 * translate3d()/translateZ() flatten to their 2D projection (a 2D engine
 * renders z as nothing, which is what the projection says), with the z
 * argument still validated as a length. Skew angles accumulate outside the
 * matrix: the painter applies shear innermost in a fixed order, so list-order
 * shear has no exact slot form, and the accumulator is exactly as correct as
 * any choice under that painter. A bare translateZ() list has no 2D effect
 * and fails closed. Unknown functions, bad arguments, more than TR_LIST_MAX
 * functions, or a singular coupled matrix reject the WHOLE declaration --
 * fail closed, never a half-applied transform.
 */
static int expand_transform_list(const char *val, css_decl *dst, int cap) {
    double m[6] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
    int txp = 0, typ = 0;
    int acc_skx = 0, acc_sky = 0;
    unsigned spec = 0u;
    int any2d = 0, seentr = 0;
    const char *p = val;
    int nfns = 0;
    const double pi = 3.14159265358979323846;
    for (;;) {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        if (++nfns > TR_LIST_MAX) return 0;
        char name[16];
        size_t nl = 0;
        while ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') ||
               (*p >= '0' && *p <= '9')) {
            if (nl + 1 >= sizeof name) return 0;
            name[nl++] = csel_lower_ch(*p++);
        }
        name[nl] = '\0';
        while (*p == ' ' || *p == '\t') ++p;
        if (*p != '(') return 0;
        ++p;
        const char *ab = p;
        int depth = 1;
        while (*p != '\0' && depth > 0) {
            if (*p == '(') ++depth;
            else if (*p == ')') --depth;
            ++p;
        }
        if (depth != 0) return 0;
        size_t argn = (size_t)(p - 1 - ab);
        double f[6] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
        size_t starts[3], stops[3];
        char a[CSS_TOK_MAX], b[CSS_TOK_MAX], c[CSS_TOK_MAX];
        if (strcmp(name, "translatex") == 0 || strcmp(name, "translatey") == 0) {
            if (split_top_args(ab, argn, starts, stops, 3) != 1) return 0;
            if (copy_trim(ab, starts[0], stops[0], a, sizeof a) == (size_t)-1 ||
                a[0] == '\0')
                return 0;
            int px, pm;
            if (!interp_lp(a, 0, 1, &px, &pm)) return 0;
            if (name[9] == 'x') { f[4] = (double)px; txp += pm; spec |= SPEC_TX; }
            else { f[5] = (double)px; typ += pm; spec |= SPEC_TY; }
            seentr = 1;
            any2d = 1;
        } else if (strcmp(name, "translate") == 0) {
            int nargs = split_top_args(ab, argn, starts, stops, 3);
            if (nargs < 1 || nargs > 2) return 0;
            if (copy_trim(ab, starts[0], stops[0], a, sizeof a) == (size_t)-1 ||
                a[0] == '\0')
                return 0;
            int px, pm, qx = 0, qm = 0;
            if (!interp_lp(a, 0, 1, &px, &pm)) return 0;
            if (nargs == 2) {
                if (copy_trim(ab, starts[1], stops[1], b, sizeof b) == (size_t)-1 ||
                    b[0] == '\0')
                    return 0;
                if (!interp_lp(b, 0, 1, &qx, &qm)) return 0;
            }
            f[4] = (double)px;
            f[5] = (double)qx;
            txp += pm;
            typ += qm;
            spec |= SPEC_TX | SPEC_TY;
            seentr = 1;
            any2d = 1;
        } else if (strcmp(name, "translate3d") == 0) {
            if (split_top_args(ab, argn, starts, stops, 3) != 3) return 0;
            if (copy_trim(ab, starts[0], stops[0], a, sizeof a) == (size_t)-1 ||
                a[0] == '\0')
                return 0;
            if (copy_trim(ab, starts[1], stops[1], b, sizeof b) == (size_t)-1 ||
                b[0] == '\0')
                return 0;
            if (copy_trim(ab, starts[2], stops[2], c, sizeof c) == (size_t)-1 ||
                c[0] == '\0')
                return 0;
            int px, pm, qx, qm, zd, zm;
            if (!interp_lp(a, 0, 1, &px, &pm)) return 0;
            if (!interp_lp(b, 0, 1, &qx, &qm)) return 0;
            if (!interp_lp(c, 0, 0, &zd, &zm)) return 0;
            f[4] = (double)px;
            f[5] = (double)qx;
            txp += pm;
            typ += qm;
            spec |= SPEC_TX | SPEC_TY;
            seentr = 1;
            any2d = 1;
        } else if (strcmp(name, "translatez") == 0) {
            if (split_top_args(ab, argn, starts, stops, 3) != 1) return 0;
            if (copy_trim(ab, starts[0], stops[0], a, sizeof a) == (size_t)-1 ||
                a[0] == '\0')
                return 0;
            int zd, zm;
            if (!interp_lp(a, 0, 0, &zd, &zm)) return 0;
        } else if (strcmp(name, "scalex") == 0 || strcmp(name, "scaley") == 0) {
            if (split_top_args(ab, argn, starts, stops, 3) != 1) return 0;
            if (copy_trim(ab, starts[0], stops[0], a, sizeof a) == (size_t)-1 ||
                a[0] == '\0')
                return 0;
            int v;
            if (!parse_scale_pct(a, &v)) return 0;
            if (name[5] == 'x') { f[0] = (double)v / 100.0; spec |= SPEC_SX; }
            else { f[3] = (double)v / 100.0; spec |= SPEC_SY; }
            any2d = 1;
        } else if (strcmp(name, "scale") == 0) {
            int nargs = split_top_args(ab, argn, starts, stops, 3);
            if (nargs < 1 || nargs > 2) return 0;
            if (copy_trim(ab, starts[0], stops[0], a, sizeof a) == (size_t)-1 ||
                a[0] == '\0')
                return 0;
            int vx, vy;
            if (!parse_scale_pct(a, &vx)) return 0;
            vy = vx;
            if (nargs == 2) {
                if (copy_trim(ab, starts[1], stops[1], b, sizeof b) == (size_t)-1 ||
                    b[0] == '\0')
                    return 0;
                if (!parse_scale_pct(b, &vy)) return 0;
            }
            f[0] = (double)vx / 100.0;
            f[3] = (double)vy / 100.0;
            spec |= SPEC_SX | SPEC_SY;
            any2d = 1;
        } else if (strcmp(name, "rotate") == 0) {
            if (split_top_args(ab, argn, starts, stops, 3) != 1) return 0;
            if (copy_trim(ab, starts[0], stops[0], a, sizeof a) == (size_t)-1 ||
                a[0] == '\0')
                return 0;
            int deg;
            if (!parse_angle_deg(a, &deg)) return 0;
            double r = (double)deg * pi / 180.0;
            f[0] = cos(r);
            f[1] = sin(r);
            f[2] = -sin(r);
            f[3] = cos(r);
            spec |= SPEC_ROT;
            any2d = 1;
        } else if (strcmp(name, "skewx") == 0 || strcmp(name, "skewy") == 0) {
            if (split_top_args(ab, argn, starts, stops, 3) != 1) return 0;
            if (copy_trim(ab, starts[0], stops[0], a, sizeof a) == (size_t)-1 ||
                a[0] == '\0')
                return 0;
            int deg;
            if (!parse_angle_deg(a, &deg)) return 0;
            if (name[4] == 'x') { acc_skx += deg; spec |= SPEC_SKX; }
            else { acc_sky += deg; spec |= SPEC_SKY; }
            any2d = 1;
        } else if (strcmp(name, "skew") == 0) {
            int nargs = split_top_args(ab, argn, starts, stops, 3);
            if (nargs < 1 || nargs > 2) return 0;
            if (copy_trim(ab, starts[0], stops[0], a, sizeof a) == (size_t)-1 ||
                a[0] == '\0')
                return 0;
            int ax, ay = 0;
            if (!parse_angle_deg(a, &ax)) return 0;
            if (nargs == 2) {
                if (copy_trim(ab, starts[1], stops[1], b, sizeof b) == (size_t)-1 ||
                    b[0] == '\0')
                    return 0;
                if (!parse_angle_deg(b, &ay)) return 0;
            }
            acc_skx += ax;
            acc_sky += ay;
            spec |= SPEC_SKX | SPEC_SKY;
            any2d = 1;
        } else if (strcmp(name, "matrix") == 0) {
            if (!parse_matrix6(ab, argn, f)) return 0;
            spec |= SPEC_ALL7;
            any2d = 1;
        } else {
            return 0;
        }
        double acc[6];
        tr_mul(acc, m, f);
        m[0] = acc[0]; m[1] = acc[1]; m[2] = acc[2];
        m[3] = acc[3]; m[4] = acc[4]; m[5] = acc[5];
    }
    if (!any2d && txp == 0 && typ == 0) return 0;
    int tx, ty, rot, sx, sy, dskx;
    if (tr_decompose(m, &tx, &ty, &rot, &sx, &sy, &dskx)) {
    } else if (m[1] == 0.0 && m[2] == 0.0) {
        tx = css_round_clamp(m[4], -CSS_LEN_MAX, CSS_LEN_MAX);
        ty = css_round_clamp(m[5], -CSS_LEN_MAX, CSS_LEN_MAX);
        rot = 0;
        dskx = 0;
        sx = css_round_clamp(m[0] * 100.0, -CSS_LEN_MAX, CSS_LEN_MAX);
        sy = css_round_clamp(m[3] * 100.0, -CSS_LEN_MAX, CSS_LEN_MAX);
    } else {
        return 0;
    }
    if (txp > CSS_PCT_MAX) txp = CSS_PCT_MAX;
    if (txp < -CSS_PCT_MAX) txp = -CSS_PCT_MAX;
    if (typ > CSS_PCT_MAX) typ = CSS_PCT_MAX;
    if (typ < -CSS_PCT_MAX) typ = -CSS_PCT_MAX;
    int skx = css_round_clamp((double)dskx + (double)acc_skx, -CSS_LEN_MAX, CSS_LEN_MAX);
    int sky = css_round_clamp((double)acc_sky, -CSS_LEN_MAX, CSS_LEN_MAX);
    int need = (seentr ? 2 : 0);
    if (spec & SPEC_TX) ++need;
    if (spec & SPEC_TY) ++need;
    if (spec & SPEC_SX) ++need;
    if (spec & SPEC_SY) ++need;
    if (spec & SPEC_ROT) ++need;
    if (spec & SPEC_SKX) ++need;
    if (spec & SPEC_SKY) ++need;
    if (cap < need) return 0;
    int n = 0;
    if (spec & SPEC_TX) {
        dst[n].prop = P_TRANSFORM_TX;
        dst[n].ival = (txp != 0 && tx == 0) ? CSS_LEN_UNSET : tx;
        ++n;
    }
    if (spec & SPEC_TY) {
        dst[n].prop = P_TRANSFORM_TY;
        dst[n].ival = (typ != 0 && ty == 0) ? CSS_LEN_UNSET : ty;
        ++n;
    }
    if (spec & SPEC_ROT) { dst[n].prop = P_TRANSFORM_ROTATE; dst[n].ival = rot; ++n; }
    if (spec & SPEC_SX) { dst[n].prop = P_TRANSFORM_SX; dst[n].ival = sx; ++n; }
    if (spec & SPEC_SY) { dst[n].prop = P_TRANSFORM_SY; dst[n].ival = sy; ++n; }
    if (spec & SPEC_SKX) { dst[n].prop = P_TRANSFORM_SKX; dst[n].ival = skx; ++n; }
    if (spec & SPEC_SKY) { dst[n].prop = P_TRANSFORM_SKY; dst[n].ival = sky; ++n; }
    if (seentr) {
        dst[n].prop = P_PCT_FIRST + CSS_PCT_TRANSLATE_X; dst[n].ival = txp; ++n;
        dst[n].prop = P_PCT_FIRST + CSS_PCT_TRANSLATE_Y; dst[n].ival = typ; ++n;
    }
    return n;
}

/* transform (M1.2 translate; M1.2b adds scale/rotate): translate()/
 * translateX()/translateY() offsets in px via interp_len (allow_auto=0 -- %,
 * viewport units and bare non-calc numbers all fail closed, same as any other
 * box-model length here); scale()/scaleX()/scaleY() unitless ratios via
 * parse_scale_pct; rotate()/skew()/skewX()/skewY() <angle> values via
 * parse_angle_deg (any of deg/grad/rad/turn, fractional allowed, rounded to
 * whole degrees); matrix(a,b,c,d,e,f) QR-decomposed at parse time into ALL
 * seven slots (M1.2c; singular matrices fail closed). Space-separated function
 * LISTS compose in order through expand_transform_list (CSS Transforms 1 3);
 * translate3d()/translateZ() flatten to their 2D projection. Any other
 * transform function (perspective/rotate3d/...), or unparseable syntax,
 * rejects the WHOLE declaration (no decl emitted -> cascades
 * as unset, byte-identical to a page that never declared transform at all --
 * fail closed, never a half-applied transform). Transformed hit-testing
 * (click, cursor, overflow-clip ancestor resolution) stays out of scope -- the
 * painter (gui/browser_ui.c box_transform_matrix) applies the real affine
 * transform, but hit-testing still resolves against the UNTRANSFORMED layout
 * rect, same documented limit as M1.2 translate. "none" is not special-cased
 * -- it simply fails every function-name match below and emits nothing, same
 * net effect (unset). */
static int expand_transform(const char *val, css_decl *dst, int cap) {
    if (cap < 2) return 0;
    const char *p = val;
    while (*p == ' ' || *p == '\t') ++p;

    /* `transform: none` is the initial value and, on a page, a RESET -- it is how a
     * rule cancels a transform a lower-specificity rule applied. Dropping it left
     * the transform in place, which is the opposite of what the author wrote. It
     * emits the identity explicitly rather than returning 0, so it claims the
     * cascade slots instead of yielding them. */
    if (csel_ci_eq(p, "none")) {
        dst[0].prop = P_TRANSFORM_TX; dst[0].ival = 0;
        dst[1].prop = P_TRANSFORM_TY; dst[1].ival = 0;
        int k = 2;
        if (k < cap) { dst[k].prop = P_TRANSFORM_SX;  dst[k].ival = 100; ++k; }
        if (k < cap) { dst[k].prop = P_TRANSFORM_SY;  dst[k].ival = 100; ++k; }
        if (k < cap) { dst[k].prop = P_TRANSFORM_ROTATE; dst[k].ival = 0; ++k; }
        if (k < cap) { dst[k].prop = P_TRANSFORM_SKX;    dst[k].ival = 0; ++k; }
        if (k < cap) { dst[k].prop = P_TRANSFORM_SKY;    dst[k].ival = 0; ++k; }
        return k;
    }

    enum { TR_X, TR_Y, TR_BOTH, TR_3D, TR_Z, SC_X, SC_Y, SC_BOTH, ROTATE,
           SK_X, SK_Y, SK_BOTH, MATRIX } kind;
    if (csel_span_eq(p, "translatex(", 11, 1))      { kind = TR_X;    p += 11; }
    else if (csel_span_eq(p, "translatey(", 11, 1)) { kind = TR_Y;    p += 11; }
    else if (csel_span_eq(p, "translate(", 10, 1))  { kind = TR_BOTH; p += 10; }
    else if (csel_span_eq(p, "translate3d(", 12, 1)) { kind = TR_3D;   p += 12; }
    else if (csel_span_eq(p, "translatez(", 11, 1)) { kind = TR_Z;    p += 11; }
    else if (csel_span_eq(p, "scalex(", 7, 1))      { kind = SC_X;    p += 7; }
    else if (csel_span_eq(p, "scaley(", 7, 1))      { kind = SC_Y;    p += 7; }
    else if (csel_span_eq(p, "scale(", 6, 1))       { kind = SC_BOTH; p += 6; }
    else if (csel_span_eq(p, "rotate(", 7, 1))      { kind = ROTATE;  p += 7; }
    else if (csel_span_eq(p, "skewx(", 6, 1))       { kind = SK_X;    p += 6; }
    else if (csel_span_eq(p, "skewy(", 6, 1))       { kind = SK_Y;    p += 6; }
    else if (csel_span_eq(p, "skew(", 5, 1))        { kind = SK_BOTH; p += 5; }
    else if (csel_span_eq(p, "matrix(", 7, 1))      { kind = MATRIX;  p += 7; }
    else return 0;

    size_t n = strlen(p);
    size_t j = 0;
    int depth = 1;
    while (j < n && depth > 0) {
        if (p[j] == '(') ++depth;
        else if (p[j] == ')') --depth;
        ++j;
    }
    if (depth != 0) return 0;                 /* unbalanced parens */
    size_t argn = j - 1;                       /* [0, argn) is the arg list */
    const char *rest = p + j;
    while (*rest == ' ' || *rest == '\t') ++rest;
    /* A second function, or a 3D spelling, takes the list path: single
     * legacy functions continue below exactly as before. */
    if (kind == TR_3D || kind == TR_Z || *rest != '\0')
        return expand_transform_list(val, dst, cap);

    if (kind == MATRIX) {
        /* matrix(a,b,c,d,e,f) (M1.2c): six comma-separated unitless numbers,
         * QR-decomposed into the seven independent slots at the resolution each
         * slot already has (whole degrees / whole percent / whole px -- same
         * convention as rotate()'s whole-degree grammar; the precision loss is
         * documented in spec/compositor.md). A matrix() is a COMPLETE transform,
         * so all seven slots are emitted (a slot it "overwrites" is exactly the
         * cascade semantics of a full matrix). Singular (det == 0 or zero first
         * column) fails closed. */
        if (cap < 7) return 0;
        double m6[6];
        if (!parse_matrix6(p, argn, m6)) return 0;
        int mtx, mty, mrot, msx, msy, mskx;
        if (!tr_decompose(m6, &mtx, &mty, &mrot, &msx, &msy, &mskx)) return 0;
        dst[0].prop = P_TRANSFORM_TX;     dst[0].ival = mtx;
        dst[1].prop = P_TRANSFORM_TY;     dst[1].ival = mty;
        dst[2].prop = P_TRANSFORM_ROTATE; dst[2].ival = mrot;
        dst[3].prop = P_TRANSFORM_SX;     dst[3].ival = msx;
        dst[4].prop = P_TRANSFORM_SY;     dst[4].ival = msy;
        dst[5].prop = P_TRANSFORM_SKX;    dst[5].ival = mskx;
        dst[6].prop = P_TRANSFORM_SKY;    dst[6].ival = 0;
        return 7;
    }

    size_t comma = argn;
    for (size_t k = 0; k < argn; ++k) {
        if (p[k] == ',') { comma = k; break; }
    }
    int has_second = comma < argn;

    char a[CSS_TOK_MAX], b[CSS_TOK_MAX];
    if (copy_trim(p, 0, comma, a, sizeof a) == (size_t)-1 || a[0] == '\0') return 0;
    if (has_second &&
        (copy_trim(p, comma + 1, argn, b, sizeof b) == (size_t)-1 || b[0] == '\0'))
        return 0;

    if (kind == ROTATE) {
        int deg;
        if (has_second || !parse_angle_deg(a, &deg)) return 0;
        dst[0].prop = P_TRANSFORM_ROTATE; dst[0].ival = deg;
        return 1;
    }

    if (kind == SK_X) {
        int deg;
        if (has_second || !parse_angle_deg(a, &deg)) return 0;
        dst[0].prop = P_TRANSFORM_SKX; dst[0].ival = deg;
        return 1;
    }
    if (kind == SK_Y) {
        int deg;
        if (has_second || !parse_angle_deg(a, &deg)) return 0;
        dst[0].prop = P_TRANSFORM_SKY; dst[0].ival = deg;
        return 1;
    }
    if (kind == SK_BOTH) {
        /* skew(ax) means skew(ax, 0) -- like translate(x), both slots emitted. */
        int ax, ay = 0;
        if (!parse_angle_deg(a, &ax)) return 0;
        if (has_second && !parse_angle_deg(b, &ay)) return 0;
        dst[0].prop = P_TRANSFORM_SKX; dst[0].ival = ax;
        dst[1].prop = P_TRANSFORM_SKY; dst[1].ival = ay;
        return 2;
    }

    if (kind == SC_X) {
        int sx;
        if (has_second || !parse_scale_pct(a, &sx)) return 0;
        dst[0].prop = P_TRANSFORM_SX; dst[0].ival = sx;
        return 1;
    }
    if (kind == SC_Y) {
        int sy;
        if (has_second || !parse_scale_pct(a, &sy)) return 0;
        dst[0].prop = P_TRANSFORM_SY; dst[0].ival = sy;
        return 1;
    }
    if (kind == SC_BOTH) {
        /* scale(sx) means scale(sx, sx) -- unlike translate(), the missing axis
         * MIRRORS the first argument, not an identity default. */
        int sx, sy;
        if (!parse_scale_pct(a, &sx)) return 0;
        sy = sx;
        if (has_second && !parse_scale_pct(b, &sy)) return 0;
        dst[0].prop = P_TRANSFORM_SX; dst[0].ival = sx;
        dst[1].prop = P_TRANSFORM_SY; dst[1].ival = sy;
        return 2;
    }

    /* Emit only the axis/axes this function actually specifies: translateX/Y are
     * single-axis (the OTHER axis must stay CSS_LEN_UNSET, not become an implicit
     * 0 -- a `<div>` with only translateX() must not also pick up a phantom
     * translateY(0) declaration that shadows a separately-cascaded translateY).
     * translate(x) alone DOES mean translate(x, 0) per spec, so TR_BOTH always
     * emits both slots. */
    int tx, ty, txp, typ;
    if (kind == TR_X) {
        if (has_second || !interp_lp(a, 0, 1, &tx, &txp)) return 0;
        if (cap < 2) return 0;
        dst[0].prop = P_TRANSFORM_TX; dst[0].ival = (txp != 0 && tx == 0) ? CSS_LEN_UNSET : tx;
        dst[1].prop = P_PCT_FIRST + CSS_PCT_TRANSLATE_X; dst[1].ival = txp;
        return 2;
    }
    if (kind == TR_Y) {
        if (has_second || !interp_lp(a, 0, 1, &ty, &typ)) return 0;
        if (cap < 2) return 0;
        dst[0].prop = P_TRANSFORM_TY; dst[0].ival = (typ != 0 && ty == 0) ? CSS_LEN_UNSET : ty;
        dst[1].prop = P_PCT_FIRST + CSS_PCT_TRANSLATE_Y; dst[1].ival = typ;
        return 2;
    }
    ty = 0; typ = 0;
    if (!interp_lp(a, 0, 1, &tx, &txp)) return 0;
    if (has_second && !interp_lp(b, 0, 1, &ty, &typ)) return 0;
    if (cap < 4) return 0;
    dst[0].prop = P_TRANSFORM_TX; dst[0].ival = (txp != 0 && tx == 0) ? CSS_LEN_UNSET : tx;
    dst[1].prop = P_TRANSFORM_TY; dst[1].ival = (typ != 0 && ty == 0) ? CSS_LEN_UNSET : ty;
    dst[2].prop = P_PCT_FIRST + CSS_PCT_TRANSLATE_X; dst[2].ival = txp;
    dst[3].prop = P_PCT_FIRST + CSS_PCT_TRANSLATE_Y; dst[3].ival = typ;
    return 4;
}

/* One transform-origin component: keyword (axis-checked), a percent, or a
 * bare zero. axis: 0 = x (left/right valid), 1 = y (top/bottom valid).
 * Percents clamp to [-1000, 1000] (values outside [0,100] are legal CSS, e.g.
 * "150%"). A unitless zero is 0px, and 0px of any box edge is 0% of it, so it
 * maps to 0; any other unitless number is not a length and fails closed. */
static int origin_component(const char *tok, int axis, int *out) {
    if (csel_ci_eq(tok, "center"))                { *out = 50;  return 1; }
    if (axis == 0 && csel_ci_eq(tok, "left"))     { *out = 0;   return 1; }
    if (axis == 0 && csel_ci_eq(tok, "right"))    { *out = 100; return 1; }
    if (axis == 1 && csel_ci_eq(tok, "top"))      { *out = 0;   return 1; }
    if (axis == 1 && csel_ci_eq(tok, "bottom"))   { *out = 100; return 1; }
    double num;
    const char *end;
    if (parse_num(tok, &num, &end) && end[0] == '%' && end[1] == '\0') {
        *out = css_round_clamp(num, -1000, 1000);
        return 1;
    }
    const char *q = tok;
    if (*q == '+' || *q == '-') ++q;
    if (parse_num(q, &num, &end) && *end == '\0' && num == 0.0) {
        *out = 0;
        return 1;
    }
    return 0;
}

/* transform-origin (M1.2c): 1-2 values; keywords and percents only (px lengths
 * fail closed -- the parser has no box size to resolve them against). One value
 * names the x axis (y = 50% center) unless it is a y-only keyword. Two keyword
 * values may come in either order ("bottom left" == "left bottom"), per CSS.
 * Emits both percent slots; unset downstream means the CSS default 50% 50%. */
static int expand_transform_origin(const char *val, css_decl *dst, int cap) {
    if (cap < 2) return 0;
    char a[CSS_TOK_MAX], b[CSS_TOK_MAX], extra[CSS_TOK_MAX];
    const char *p = val;
    if (!next_ws_token(&p, a, sizeof a)) return 0;
    int has_b = next_ws_token(&p, b, sizeof b);
    if (has_b && next_ws_token(&p, extra, sizeof extra)) return 0;
    int ox, oy;
    if (!has_b) {
        if (csel_ci_eq(a, "top") || csel_ci_eq(a, "bottom")) {
            ox = 50;
            if (!origin_component(a, 1, &oy)) return 0;
        } else {
            oy = 50;
            if (!origin_component(a, 0, &ox)) return 0;
        }
    } else {
        const char *xa = a, *ya = b;
        if (csel_ci_eq(a, "top") || csel_ci_eq(a, "bottom") ||
            csel_ci_eq(b, "left") || csel_ci_eq(b, "right")) { xa = b; ya = a; }
        if (!origin_component(xa, 0, &ox)) return 0;
        if (!origin_component(ya, 1, &oy)) return 0;
    }
    dst[0].prop = P_TRANSFORM_OX; dst[0].ival = ox;
    dst[1].prop = P_TRANSFORM_OY; dst[1].ival = oy;
    return 2;
}

/* gap / grid-gap (2026-07-10): one value keeps the pre-existing semantics (both
 * axes; row-gap stays unset and falls back to gap downstream), two values are
 * `<row> <col>` (row feeds row-gap, col feeds gap). column-gap stays a
 * single-value longhand in the dispatch below. */
static int expand_gap(const char *val, css_decl *dst, int cap) {
    char a[CSS_TOK_MAX], b[CSS_TOK_MAX], extra[CSS_TOK_MAX];
    const char *p = val;
    if (!next_ws_token(&p, a, sizeof a)) return 0;
    int has_b = next_ws_token(&p, b, sizeof b);
    if (has_b && next_ws_token(&p, extra, sizeof extra)) return 0;
    int ga = interp_gap(a);
    if (ga < 0 || cap < 1) return 0;
    if (!has_b) { dst[0].prop = P_GAP; dst[0].ival = ga; return 1; }
    int gb = interp_gap(b);
    if (gb < 0 || cap < 2) return 0;
    dst[0].prop = P_ROW_GAP; dst[0].ival = ga;
    dst[1].prop = P_GAP;     dst[1].ival = gb;
    return 2;
}

/* place-items / place-content / place-self (2026-07-10): `<align> [<justify>]`,
 * the justify half defaulting to the align token. place-content's justify half
 * feeds justify-content (its own keyword set). place-self's justify half has no
 * engine slot and is ignored (documented simplification, like list-style's
 * ignored tokens). An uninterpretable align token (or, where a slot exists, an
 * uninterpretable justify token) drops the whole shorthand (fail closed). */
static int expand_place(const char *prop, const char *val, css_decl *dst, int cap) {
    char a[CSS_TOK_MAX], b[CSS_TOK_MAX], extra[CSS_TOK_MAX];
    const char *p = val;
    if (!next_ws_token(&p, a, sizeof a)) return 0;
    int has_b = next_ws_token(&p, b, sizeof b);
    if (has_b && next_ws_token(&p, extra, sizeof extra)) return 0;

    if (strcmp(prop, "place-self") == 0) {
        int av = interp_align_kw(a, 1, 0);
        if (av < 0 || cap < 1) return 0;
        dst[0].prop = P_ALIGN_SELF; dst[0].ival = av;
        return 1;
    }
    if (strcmp(prop, "place-items") == 0) {
        int av = interp_align_kw(a, 0, 0);
        int jv = interp_align_kw(has_b ? b : a, 0, 0);
        if (av < 0 || jv < 0 || cap < 2) return 0;
        dst[0].prop = P_ALIGN_ITEMS;   dst[0].ival = av;
        dst[1].prop = P_JUSTIFY_ITEMS; dst[1].ival = jv;
        return 2;
    }
    int av = interp_align_kw(a, 0, 1);
    int jv = interp_justify(has_b ? b : a);
    if (av < 0 || jv < 0 || cap < 2) return 0;
    dst[0].prop = P_ALIGN_CONTENT; dst[0].ival = av;
    dst[1].prop = P_JUSTIFY;       dst[1].ival = jv;
    return 2;
}

/* clip: rect() / auto for positioned boxes (CSS 2.1 §11.1.2). Emits four
 * P_CLIP_TOP/RIGHT/BOTTOM/LEFT decls. auto → all CSS_LEN_UNSET (edge of
 * border-box). rect(t r b l) with commas or spaces → px values. Any parse
 * error drops the whole property (fail closed). */
static int expand_clip(const char *val, css_decl *dst, int cap) {
    if (cap < 4) return 0;
    const char *p = val;
    while (*p == ' ' || *p == '\t') ++p;
    if (p[0] == 'a' && p[1] == 'u' && p[2] == 't' && p[3] == 'o'
        && (p[4] == '\0' || p[4] == ' ' || p[4] == '\t' || p[4] == ';')) {
        for (int i = 0; i < 4; ++i)
            { dst[i].prop = P_CLIP_TOP + i; dst[i].ival = CSS_LEN_UNSET; }
        return 4;
    }
    if (!(p[0] == 'r' && p[1] == 'e' && p[2] == 'c' && p[3] == 't' && p[4] == '('))
        return 0;
    p += 5;  /* past "rect(" */
    int vals[4] = { CSS_LEN_UNSET, CSS_LEN_UNSET, CSS_LEN_UNSET, CSS_LEN_UNSET };
    for (int i = 0; i < 4; ++i) {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == ')') break;
        if (*p == ',') { ++p; while (*p == ' ' || *p == '\t') ++p; }
        if (*p == 'a' && *(p + 1) == 'u' && *(p + 2) == 't' && *(p + 3) == 'o') {
            p += 4; vals[i] = CSS_LEN_UNSET; continue;
        }
        double d = 0.0; int neg = (*p == '-') ? (++p, 1) : 0;
        const char *e = p; int has_digit = 0;
        while (*e >= '0' && *e <= '9') { d = d * 10.0 + (double)(*e - '0'); ++e; has_digit = 1; }
        if (*e == '.') { double f = 0.1; ++e;
            while (*e >= '0' && *e <= '9') { d += (double)(*e - '0') * f; f *= 0.1; ++e; has_digit = 1; } }
        if (!has_digit) return 0;
        if (neg) d = -d;
        vals[i] = (int)(d + (d < 0 ? -0.5 : 0.5));
        while ((*e >= 'a' && *e <= 'z') || (*e >= 'A' && *e <= 'Z') || *e == '%' || *e == '-') ++e;
        p = e;
    }
    for (int i = 0; i < 4; ++i)
        { dst[i].prop = P_CLIP_TOP + i; dst[i].ival = vals[i]; }
    return 4;
}

/* font shorthand (2026-07-10): `[style|variant|weight|normal]* size[/line-height]
 * family...`. size and family are both required (per CSS); system keywords
 * (`font: caption` etc.) have no size token and drop the whole shorthand (fail
 * closed). Unmentioned longhands stay unset -- this cascade has no
 * reset-to-initial, a documented simplification. A family that maps to no
 * generic bucket keeps the rest of the shorthand (same net effect as the
 * font-family longhand dropping an unknown name). */
static int expand_font(const char *val, css_decl *dst, int cap) {
    const char *p = val;
    char tok[CSS_TOK_MAX];
    int style = -1, weight = -1, variant = -1;

    for (;;) {
        const char *save = p;
        if (!next_ws_token(&p, tok, sizeof tok)) return 0;  /* ran out: no size */
        if (csel_ci_eq(tok, "normal")) continue;  /* ambiguous reset: leave unset */
        if (csel_ci_eq(tok, "italic") || csel_ci_eq(tok, "oblique")) { style = 1; continue; }
        if (csel_ci_eq(tok, "small-caps")) { variant = CSS_FV_SMALL_CAPS; continue; }
        if (csel_ci_eq(tok, "bold") || csel_ci_eq(tok, "bolder")) { weight = 1; continue; }
        if (csel_ci_eq(tok, "lighter")) { weight = 0; continue; }
        {   /* a bare 100..900 number is a weight (a size always carries a unit) */
            const char *q = tok;
            int all_digits = (*q != '\0');
            while (*q != '\0') { if (*q < '0' || *q > '9') { all_digits = 0; break; } ++q; }
            if (all_digits) {
                int w = interp_weight(tok);
                if (w >= 0) { weight = w; continue; }
            }
        }
        p = save;   /* not a leading keyword: must be the size token */
        break;
    }

    if (!next_ws_token(&p, tok, sizeof tok)) return 0;
    int line = 0;
    char *slash = strchr(tok, '/');
    if (slash != NULL) *slash = '\0';
    int size_abs;
    int size = interp_fontsize_ex(tok, &size_abs);
    if (size < 0) return 0;
    if (slash != NULL) {
        line = interp_lineheight(slash + 1);
        if (line < 0) return 0;   /* a present but invalid line-height: all invalid */
    }

    while (*p == ' ' || *p == '\t') ++p;
    if (*p == '\0') return 0;     /* family required */
    int fam = interp_fontfamily(p);

    int n = 0;
    if (cap < 7) return 0;
    if (style >= 0)   { dst[n].prop = P_STYLE;        dst[n].ival = style;   ++n; }
    if (weight >= 0)  { dst[n].prop = P_WEIGHT;       dst[n].ival = weight;  ++n; }
    if (variant >= 0) { dst[n].prop = P_FONT_VARIANT; dst[n].ival = variant; ++n; }
    dst[n].prop = P_FONTSIZE; dst[n].ival = size;     ++n;
    dst[n].prop = P_FONTABS;  dst[n].ival = size_abs; ++n;
    if (line > 0)     { dst[n].prop = P_LINEHEIGHT;   dst[n].ival = line;    ++n; }
    if (fam > 0)      { dst[n].prop = P_FONTFAMILY;   dst[n].ival = fam;     ++n; }
    return n;
}

/* Maps property name `prop` (lowercased) + value `val` to css_decl(s) in dst (up to
 * cap). Returns the number written (0 if unsupported). Most properties emit one; the
 * margin/padding shorthands expand to up to four (one per side). The important flag is
 * left to the caller (parse_one_decl stamps it). */
/* `known` (optional) reports whether the property NAME reached a branch of the
 * dispatch below, which is what separates "not implemented" from "implemented but
 * this value was rejected" for the drop log (spec/css_drops.md). It is written at
 * the two exits that mean "no name matched" and nowhere else, so the dispatch stays
 * the single source of truth -- a parallel list of known names would go stale on the
 * next property added. */
static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,
                           char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap,
                           char (*contenttab)[CSS_URL_MAX], size_t *ncontent, size_t contentcap,
                           int *known);

static int interpret_prop_dispatch(const char *prop, const char *val, css_decl *dst, int cap,
                           char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap,
                           char (*contenttab)[CSS_URL_MAX], size_t *ncontent, size_t contentcap,
                           int *known) {
    if (known != NULL) *known = 1;
    /*
     * A vendor-prefixed property IS the standard property: `-webkit-transform`
     * and `transform` are the same declaration, and every engine treats the
     * prefixed spelling as an alias. Dropping them cost ~900 declarations in the
     * parity corpus alone -- -webkit-transform (88), -moz-border-radius (70),
     * -webkit-border-radius (69), -webkit-box-shadow (44), -webkit/-moz-
     * box-sizing (26, and that one is geometry, not paint).
     *
     * The rule is exactly "strip the prefix and ask again", ONCE, and the alias
     * table falls out of the dispatch below instead of being a second list that
     * goes stale. What it deliberately does NOT do is map the IE10 tweener
     * flexbox names: there is no property called `flex-pack`, so `-ms-flex-pack`
     * finds nothing and stays dropped -- which is right, because its value
     * grammar (`justify`/`distribute`) is not `justify-content`'s. Guessing
     * there would be inventing a rule.
     *
     * `--x` is a custom property, not a vendor prefix, and is excluded by
     * requiring a letter after the leading '-'.
     */
    if (prop[0] == '-' && prop[1] != '\0' && prop[1] != '-') {
        static const char *const VENDOR[] = { "-webkit-", "-moz-", "-ms-", "-o-" };
        for (size_t v = 0; v < sizeof VENDOR / sizeof *VENDOR; ++v) {
            size_t plen = strlen(VENDOR[v]);
            if (strncmp(prop, VENDOR[v], plen) != 0) continue;
            const char *bare = prop + plen;
            /* Once only: a doubly-prefixed name is not a property, and
             * recursing on it would be a loop with attacker-chosen depth. */
            if (bare[0] == '\0' || bare[0] == '-') return 0;
            return interpret_prop(bare, val, dst, cap, urltab, nurl, urlcap,
                                  contenttab, ncontent, contentcap, known);
        }
        if (known != NULL) *known = 0;
        return 0;   /* an unknown vendor prefix: fail closed */
    }

    /* Box model: margins allow 'auto' and negatives; padding/width neither. The
     * shorthands expand; the longhands and width/max-width emit one. */
    if (strcmp(prop, "margin") == 0)  return expand_box4(val, P_MARGIN_TOP, 1, 1, dst, cap);
    if (strcmp(prop, "padding") == 0) return expand_box4(val, P_PAD_TOP, 0, 0, dst, cap);
    if (strcmp(prop, "margin-top") == 0)     return emit_len(dst, cap, P_MARGIN_TOP, val, 1, 1);
    if (strcmp(prop, "margin-right") == 0)   return emit_len(dst, cap, P_MARGIN_RIGHT, val, 1, 1);
    if (strcmp(prop, "margin-bottom") == 0)  return emit_len(dst, cap, P_MARGIN_BOTTOM, val, 1, 1);
    if (strcmp(prop, "margin-left") == 0)    return emit_len(dst, cap, P_MARGIN_LEFT, val, 1, 1);
    if (strcmp(prop, "padding-top") == 0)    return emit_len(dst, cap, P_PAD_TOP, val, 0, 0);
    if (strcmp(prop, "padding-right") == 0)  return emit_len(dst, cap, P_PAD_RIGHT, val, 0, 0);
    if (strcmp(prop, "padding-bottom") == 0) return emit_len(dst, cap, P_PAD_BOTTOM, val, 0, 0);
    if (strcmp(prop, "padding-left") == 0)   return emit_len(dst, cap, P_PAD_LEFT, val, 0, 0);
    /* width/max-width and every other box length go through the one
     * <length-percentage> emitter: the % half is carried symbolically and
     * resolved against the containing block at layout time. */
    if (strcmp(prop, "width") == 0)     return emit_len(dst, cap, P_WIDTH, val, AUTO_RESET, 0);
    if (strcmp(prop, "max-width") == 0) return emit_len(dst, cap, P_MAXWIDTH, val, AUTO_RESET_NONE, 0);
    if (strcmp(prop, "min-width") == 0) return emit_len(dst, cap, P_MINWIDTH, val, AUTO_RESET, 0);
    if (strcmp(prop, "height") == 0)    return emit_len(dst, cap, P_HEIGHT, val, AUTO_RESET, 0);
    if (strcmp(prop, "min-height") == 0)return emit_len(dst, cap, P_MINHEIGHT, val, AUTO_RESET, 0);
    if (strcmp(prop, "max-height") == 0)return emit_len(dst, cap, P_MAXHEIGHT, val, AUTO_RESET_NONE, 0);

    /* Logical properties (2026-07-10): physical horizontal-tb LTR mapping (the
     * engine has no writing-mode, and the cascade interprets values before it
     * knows the element's resolved direction -- see spec/css.md). */
    if (strcmp(prop, "margin-inline-start") == 0)  return emit_len(dst, cap, P_MARGIN_LEFT, val, 1, 1);
    if (strcmp(prop, "margin-inline-end") == 0)    return emit_len(dst, cap, P_MARGIN_RIGHT, val, 1, 1);
    if (strcmp(prop, "margin-block-start") == 0)   return emit_len(dst, cap, P_MARGIN_TOP, val, 1, 1);
    if (strcmp(prop, "margin-block-end") == 0)     return emit_len(dst, cap, P_MARGIN_BOTTOM, val, 1, 1);
    if (strcmp(prop, "margin-inline") == 0)  return expand_box2(val, P_MARGIN_LEFT, P_MARGIN_RIGHT, 1, 1, dst, cap);
    if (strcmp(prop, "margin-block") == 0)   return expand_box2(val, P_MARGIN_TOP, P_MARGIN_BOTTOM, 1, 1, dst, cap);
    if (strcmp(prop, "padding-inline-start") == 0) return emit_len(dst, cap, P_PAD_LEFT, val, 0, 0);
    if (strcmp(prop, "padding-inline-end") == 0)   return emit_len(dst, cap, P_PAD_RIGHT, val, 0, 0);
    if (strcmp(prop, "padding-block-start") == 0)  return emit_len(dst, cap, P_PAD_TOP, val, 0, 0);
    if (strcmp(prop, "padding-block-end") == 0)    return emit_len(dst, cap, P_PAD_BOTTOM, val, 0, 0);
    if (strcmp(prop, "padding-inline") == 0) return expand_box2(val, P_PAD_LEFT, P_PAD_RIGHT, 0, 0, dst, cap);
    if (strcmp(prop, "padding-block") == 0)  return expand_box2(val, P_PAD_TOP, P_PAD_BOTTOM, 0, 0, dst, cap);
    if (strcmp(prop, "inset-inline-start") == 0)   return emit_len(dst, cap, P_INSET_LEFT, val, 1, 1);
    if (strcmp(prop, "inset-inline-end") == 0)     return emit_len(dst, cap, P_INSET_RIGHT, val, 1, 1);
    if (strcmp(prop, "inset-block-start") == 0)    return emit_len(dst, cap, P_INSET_TOP, val, 1, 1);
    if (strcmp(prop, "inset-block-end") == 0)      return emit_len(dst, cap, P_INSET_BOTTOM, val, 1, 1);
    if (strcmp(prop, "inset-inline") == 0)   return expand_box2(val, P_INSET_LEFT, P_INSET_RIGHT, 1, 1, dst, cap);
    if (strcmp(prop, "inset-block") == 0)    return expand_box2(val, P_INSET_TOP, P_INSET_BOTTOM, 1, 1, dst, cap);
    if (strcmp(prop, "inline-size") == 0)     return emit_len(dst, cap, P_WIDTH, val, AUTO_RESET, 0);
    if (strcmp(prop, "block-size") == 0)      return emit_len(dst, cap, P_HEIGHT, val, AUTO_RESET, 0);
    if (strcmp(prop, "min-inline-size") == 0) return emit_len(dst, cap, P_MINWIDTH, val, AUTO_RESET, 0);
    if (strcmp(prop, "max-inline-size") == 0) return emit_len(dst, cap, P_MAXWIDTH, val, AUTO_RESET_NONE, 0);
    if (strcmp(prop, "min-block-size") == 0)  return emit_len(dst, cap, P_MINHEIGHT, val, AUTO_RESET, 0);
    if (strcmp(prop, "max-block-size") == 0)  return emit_len(dst, cap, P_MAXHEIGHT, val, AUTO_RESET_NONE, 0);

    /* Multi-slot shorthands (2026-07-10): two-value gap, place-*, font. */
    if (strcmp(prop, "gap") == 0 || strcmp(prop, "grid-gap") == 0)
        return expand_gap(val, dst, cap);
    if (strcmp(prop, "place-items") == 0 || strcmp(prop, "place-content") == 0 ||
        strcmp(prop, "place-self") == 0)
        return expand_place(prop, val, dst, cap);
    if (strcmp(prop, "font") == 0) return expand_font(val, dst, cap);
    if (strcmp(prop, "transform") == 0) return expand_transform(val, dst, cap);
    if (strcmp(prop, "transform-origin") == 0) return expand_transform_origin(val, dst, cap);
    if (strcmp(prop, "clip") == 0)   return expand_clip(val, dst, cap);

    /* Text-presentation extensions whose value may legitimately be 0 or negative
     * (so they bypass the generic ival<0 drop, like the box-model lengths). */
    if (strcmp(prop, "text-shadow") == 0)    return expand_shadow(val, dst, cap);
    if (strcmp(prop, "letter-spacing") == 0) return emit_spacing(dst, cap, P_LETTERSPACING, val);
    if (strcmp(prop, "word-spacing") == 0)   return emit_spacing(dst, cap, P_WORDSPACING, val);
    if (strcmp(prop, "text-indent") == 0)    return emit_len(dst, cap, P_TEXTINDENT, val, 0, 1);

    /* Layout box properties whose value may be negative or a sentinel (insets allow
     * auto + negatives; z-index/order are signed; flex-basis can be auto), or which
     * expand to several slots (border / box-shadow / outline / flex). */
    if (strcmp(prop, "top") == 0)     return emit_len(dst, cap, P_INSET_TOP, val, 1, 1);
    if (strcmp(prop, "right") == 0)   return emit_len(dst, cap, P_INSET_RIGHT, val, 1, 1);
    if (strcmp(prop, "bottom") == 0)  return emit_len(dst, cap, P_INSET_BOTTOM, val, 1, 1);
    if (strcmp(prop, "left") == 0)    return emit_len(dst, cap, P_INSET_LEFT, val, 1, 1);
    if (strcmp(prop, "inset") == 0)   return expand_box4(val, P_INSET_TOP, 1, 1, dst, cap);
    if (strcmp(prop, "z-index") == 0) {
        int o;
        if (cap < 1 || !interp_int(val, &o)) return 0;
        dst[0].prop = P_ZINDEX; dst[0].ival = o; return 1;
    }
    if (strcmp(prop, "order") == 0) {
        int o;
        if (cap < 1 || !interp_int(val, &o)) return 0;
        dst[0].prop = P_ORDER; dst[0].ival = o; return 1;
    }
    if (strcmp(prop, "flex-basis") == 0) {
        int o;
        if (cap < 1 || !interp_flex_basis(val, &o)) return 0;
        dst[0].prop = P_FLEX_BASIS; dst[0].ival = o; return 1;
    }
    if (strcmp(prop, "flex") == 0)         return expand_flex(val, dst, cap);
    if (strcmp(prop, "border") == 0)        return expand_border_shorthand(val, 0xF, dst, cap);
    if (strcmp(prop, "border-top") == 0)    return expand_border_shorthand(val, 0x1, dst, cap);
    if (strcmp(prop, "border-right") == 0)  return expand_border_shorthand(val, 0x2, dst, cap);
    if (strcmp(prop, "border-bottom") == 0) return expand_border_shorthand(val, 0x4, dst, cap);
    if (strcmp(prop, "border-left") == 0)   return expand_border_shorthand(val, 0x8, dst, cap);
    if (strcmp(prop, "border-width") == 0)  return expand_quad(val, P_BW_TOP, interp_bw_tok, dst, cap);
    if (strcmp(prop, "border-style") == 0)  return expand_quad(val, P_BS_TOP, interp_bs_tok, dst, cap);
    if (strcmp(prop, "border-color") == 0)  return expand_quad(val, P_BC_TOP, interp_bc_tok, dst, cap);
    if (strcmp(prop, "box-shadow") == 0)    return expand_box_shadow(val, dst, cap);
    if (strcmp(prop, "outline") == 0)       return expand_outline(val, dst, cap);
    if (strcmp(prop, "columns") == 0)       return expand_columns(val, dst, cap);
    /* flex-flow: <'flex-direction'> || <'flex-wrap'>, in either order. Dropping
     * it silently lost BOTH the axis and the wrapping of every container written
     * with the shorthand. */
    if (strcmp(prop, "flex-flow") == 0)     return expand_flex_flow(val, dst, cap);
    if (strcmp(prop, "column-rule") == 0)   return expand_column_rule(val, dst, cap);
    /* border-radius: the shorthand plus the four physical corners and the eight
     * logical spellings, all mapped onto the same four slots (horizontal-tb LTR,
     * like the rest of the logical properties here). Before this the shorthand
     * kept only ONE value and every corner longhand was dropped whole -- 158
     * declarations in the parity corpus alone. */
    if (strcmp(prop, "border-radius") == 0) return expand_border_radius(val, dst, cap);
    if (strcmp(prop, "border-top-left-radius") == 0)
        return emit_radius_corner(dst, cap, P_BORDER_RADIUS, val);
    if (strcmp(prop, "border-top-right-radius") == 0)
        return emit_radius_corner(dst, cap, P_RADIUS_TR, val);
    if (strcmp(prop, "border-bottom-right-radius") == 0)
        return emit_radius_corner(dst, cap, P_RADIUS_BR, val);
    if (strcmp(prop, "border-bottom-left-radius") == 0)
        return emit_radius_corner(dst, cap, P_RADIUS_BL, val);
    /* The pre-standard Gecko/Presto corner spellings put the corner LAST
     * (`border-radius-topright`), which is why stripping the vendor prefix and
     * asking again does not find them -- the bare name is a different name, not the
     * standard one. They are the same property with the same value grammar, so the
     * mapping is a rename, not an invented rule (unlike the IE10 tweener flexbox
     * names, whose VALUES differ and which therefore stay dropped). */
    if (strcmp(prop, "border-radius-topleft") == 0)
        return emit_radius_corner(dst, cap, P_BORDER_RADIUS, val);
    if (strcmp(prop, "border-radius-topright") == 0)
        return emit_radius_corner(dst, cap, P_RADIUS_TR, val);
    if (strcmp(prop, "border-radius-bottomright") == 0)
        return emit_radius_corner(dst, cap, P_RADIUS_BR, val);
    if (strcmp(prop, "border-radius-bottomleft") == 0)
        return emit_radius_corner(dst, cap, P_RADIUS_BL, val);
    if (strcmp(prop, "border-start-start-radius") == 0)
        return emit_radius_corner(dst, cap, P_BORDER_RADIUS, val);
    if (strcmp(prop, "border-start-end-radius") == 0)
        return emit_radius_corner(dst, cap, P_RADIUS_TR, val);
    if (strcmp(prop, "border-end-end-radius") == 0)
        return emit_radius_corner(dst, cap, P_RADIUS_BR, val);
    if (strcmp(prop, "border-end-start-radius") == 0)
        return emit_radius_corner(dst, cap, P_RADIUS_BL, val);
    if (strcmp(prop, "outline-offset") == 0) return emit_len(dst, cap, P_OUTLINE_OFFSET, val, 0, 1);
    if (strcmp(prop, "outline-width") == 0) {
        int o = interp_bwidth1(val);
        if (o < 0) return 0;
        dst[0].prop = P_OUTLINE_W; dst[0].ival = o; return 1;
    }
    if (strcmp(prop, "outline-style") == 0) {
        int o = interp_border_style(val);
        if (o < 0) return 0;
        dst[0].prop = P_OUTLINE_S; dst[0].ival = o; return 1;
    }
    if (strcmp(prop, "outline-color") == 0) {
        int o = interp_color(val);
        if (o < 0) return 0;
        dst[0].prop = P_OUTLINE_C; dst[0].ival = o; return 1;
    }
    if (strcmp(prop, "overflow") == 0)      return expand_overflow(val, dst, cap);
    if (strcmp(prop, "background-color") == 0) {
        /* Longhand: color + its rgba()/hsla() alpha (2026-07-19). Alpha is
         * always emitted -- a plain color's UNSET resets a lower-tier alpha,
         * matching how the color slot itself overwrites. */
        if (cap < 2) return 0;
        int o = interp_bg(val);
        if (!color_ok(o)) return 0;
        dst[0].prop = P_BG;       dst[0].ival = o;
        dst[1].prop = P_BG_ALPHA; dst[1].ival = bg_alpha_of(val);
        return 2;
    }
    if (strcmp(prop, "background") == 0)
        return expand_background(val, dst, cap, urltab, nurl, urlcap);
    if (strcmp(prop, "background-image") == 0)
        return expand_bg_image(val, dst, cap, urltab, nurl, urlcap);
    if (strcmp(prop, "grid-template-columns") == 0)
        return expand_grid_template_cols(val, dst, cap);

    int prop_id, ival;
    if (strcmp(prop, "color") == 0)                 { prop_id = P_COLOR;    ival = interp_color(val); }
    else if (strcmp(prop, "text-align") == 0)        { prop_id = P_ALIGN;    ival = interp_align(val); }
    /* font-size emits TWO pairs (percent + absolute flag) so the cascade keeps them
     * in lock-step, exactly like aspect-ratio's num/den below. */
    else if (strcmp(prop, "font-size") == 0) {
        int fabs_flag;
        int fs = interp_fontsize_ex(val, &fabs_flag);
        if (fs < 0) return 0;
        if (cap < 2) return 0;
        dst[0].prop = P_FONTSIZE; dst[0].ival = fs;
        dst[1].prop = P_FONTABS;  dst[1].ival = fabs_flag;
        return 2;
    }
    else if (strcmp(prop, "line-height") == 0)       { prop_id = P_LINEHEIGHT; ival = interp_lineheight(val); }
    else if (strcmp(prop, "font-weight") == 0)       { prop_id = P_WEIGHT;   ival = interp_weight(val); }
    else if (strcmp(prop, "font-style") == 0)        { prop_id = P_STYLE;    ival = interp_style(val); }
    else if (strcmp(prop, "text-decoration") == 0 ||
             strcmp(prop, "text-decoration-line") == 0) { prop_id = P_TEXTDECO; ival = interp_textdeco(val); }
    else if (strcmp(prop, "text-decoration-color") == 0) { prop_id = P_TEXTDECO_COLOR; ival = interp_color(val); }
    else if (strcmp(prop, "text-decoration-style") == 0) { prop_id = P_TEXTDECO_STYLE; ival = interp_textdeco_style(val); }
    else if (strcmp(prop, "text-decoration-thickness") == 0) { prop_id = P_TEXTDECO_THICKNESS; ival = interp_textdeco_thickness(val); }
    /* aspect-ratio emits TWO property-value pairs (num + den) so the cascade can
     * keep them in lock-step; the only caller that drops > 1 decl (var() in
     * shorthand expansion) sees the same order in parse_one_decl's fall-through. */
    else if (strcmp(prop, "aspect-ratio") == 0) {
        int num, den;
        interp_aspect_ratio(val, &num, &den);
        if (cap < 2) return 0;
        dst[0].prop = P_ASPECT_NUM; dst[0].ival = num;
        dst[1].prop = P_ASPECT_DEN; dst[1].ival = den;
        return 2;
    }
    else if (strcmp(prop, "display") == 0)           { prop_id = P_DISPLAY;  ival = interp_display(val); }
    else if (strcmp(prop, "column-gap") == 0)         { prop_id = P_GAP;      ival = interp_gap(val); }
    else if (strcmp(prop, "justify-content") == 0)    { prop_id = P_JUSTIFY;  ival = interp_justify(val); }
    else if (strcmp(prop, "font-family") == 0)        { prop_id = P_FONTFAMILY;    ival = interp_fontfamily(val); }
    else if (strcmp(prop, "text-transform") == 0)     { prop_id = P_TEXTTRANSFORM; ival = interp_texttransform(val); }
    else if (strcmp(prop, "opacity") == 0)            { prop_id = P_OPACITY;       ival = interp_opacity(val); }
    else if (strcmp(prop, "vertical-align") == 0)     return expand_valign(val, dst, cap);
    else if (strcmp(prop, "white-space") == 0)        { prop_id = P_WHITESPACE;    ival = interp_whitespace(val); }
    else if (strcmp(prop, "tab-size") == 0)            { prop_id = P_TABSIZE;       ival = interp_tabsize(val); }
    else if (strcmp(prop, "direction") == 0)           { prop_id = P_DIRECTION;     ival = interp_direction(val); }
    else if (strcmp(prop, "list-style-type") == 0 ||
             strcmp(prop, "list-style") == 0)          { prop_id = P_LISTSTYLE;     ival = interp_liststyle(val); }
    else if (strcmp(prop, "position") == 0)            { prop_id = P_POSITION;      ival = interp_position(val); }
    else if (strcmp(prop, "box-sizing") == 0)          { prop_id = P_BOXSIZING;     ival = interp_boxsizing(val); }
    else if (strcmp(prop, "line-clamp") == 0 ||
             strcmp(prop, "-webkit-line-clamp") == 0) { prop_id = P_LINE_CLAMP;
        /* Same positive-<integer>-or-none grammar as column-count, and the same
         * anti-DoS cap: a clamp of 10000 lines is not a clamp. */
        ival = csel_ci_eq(val, "none") ? 0 : interp_column_count(val);
        if (ival < 0) return 0; }
    else if (strcmp(prop, "column-count") == 0)        { prop_id = P_COLUMN_COUNT; ival = interp_column_count(val); if (ival < 0) return 0; }
    else if (strcmp(prop, "column-width") == 0)        { prop_id = P_COLUMN_WIDTH; ival = interp_column_width(val); if (ival < 0) return 0; }
    else if (strcmp(prop, "column-fill") == 0)         { prop_id = P_COLUMN_FILL;
        ival = csel_ci_eq(val, "balance") ? CSS_CF_BALANCE
             : csel_ci_eq(val, "auto")    ? CSS_CF_AUTO : -1; }
    else if (strcmp(prop, "column-span") == 0)         { prop_id = P_COLUMN_SPAN;
        ival = csel_ci_eq(val, "none") ? CSS_CSP_NONE
             : csel_ci_eq(val, "all")  ? CSS_CSP_ALL : -1; }
    else if (strcmp(prop, "column-rule-width") == 0)   { prop_id = P_COLRULE_W; ival = interp_bwidth1(val); }
    else if (strcmp(prop, "column-rule-style") == 0)   { prop_id = P_COLRULE_S; ival = interp_border_style(val); }
    else if (strcmp(prop, "column-rule-color") == 0)   { prop_id = P_COLRULE_C; ival = interp_color(val); }
    else if (strcmp(prop, "border-top-width") == 0)    { prop_id = P_BW_TOP;        ival = interp_bwidth1(val); }
    else if (strcmp(prop, "border-right-width") == 0)  { prop_id = P_BW_RIGHT;      ival = interp_bwidth1(val); }
    else if (strcmp(prop, "border-bottom-width") == 0) { prop_id = P_BW_BOTTOM;     ival = interp_bwidth1(val); }
    else if (strcmp(prop, "border-left-width") == 0)   { prop_id = P_BW_LEFT;       ival = interp_bwidth1(val); }
    else if (strcmp(prop, "border-top-style") == 0)    { prop_id = P_BS_TOP;        ival = interp_border_style(val); }
    else if (strcmp(prop, "border-right-style") == 0)  { prop_id = P_BS_RIGHT;      ival = interp_border_style(val); }
    else if (strcmp(prop, "border-bottom-style") == 0) { prop_id = P_BS_BOTTOM;     ival = interp_border_style(val); }
    else if (strcmp(prop, "border-left-style") == 0)   { prop_id = P_BS_LEFT;       ival = interp_border_style(val); }
    else if (strcmp(prop, "border-top-color") == 0)    { prop_id = P_BC_TOP;        ival = interp_color(val); }
    else if (strcmp(prop, "border-right-color") == 0)  { prop_id = P_BC_RIGHT;      ival = interp_color(val); }
    else if (strcmp(prop, "border-bottom-color") == 0) { prop_id = P_BC_BOTTOM;     ival = interp_color(val); }
    else if (strcmp(prop, "border-left-color") == 0)   { prop_id = P_BC_LEFT;       ival = interp_color(val); }
    else if (strcmp(prop, "flex-grow") == 0)           { prop_id = P_FLEX_GROW;     ival = interp_flex_factor(val); }
    else if (strcmp(prop, "flex-shrink") == 0)         { prop_id = P_FLEX_SHRINK;   ival = interp_flex_factor(val); }
    else if (strcmp(prop, "align-items") == 0)         { prop_id = P_ALIGN_ITEMS;   ival = interp_align_kw(val, 0, 0); }
    else if (strcmp(prop, "align-self") == 0)          { prop_id = P_ALIGN_SELF;    ival = interp_align_kw(val, 1, 0); }
    else if (strcmp(prop, "align-content") == 0)       { prop_id = P_ALIGN_CONTENT; ival = interp_align_kw(val, 0, 1); }
    else if (strcmp(prop, "justify-items") == 0)       { prop_id = P_JUSTIFY_ITEMS; ival = interp_align_kw(val, 0, 0); }
    else if (strcmp(prop, "flex-direction") == 0)      { prop_id = P_FLEX_DIR;      ival = interp_flex_direction(val); }
    else if (strcmp(prop, "box-orient") == 0)          { prop_id = P_FLEX_DIR;      ival = interp_box_orient(val); }
    else if (strcmp(prop, "flex-wrap") == 0)           { prop_id = P_FLEX_WRAP;     ival = interp_flex_wrap(val); }
    else if (strcmp(prop, "grid-template-rows") == 0)  { prop_id = P_GRID_ROWS;     ival = interp_gridcols(val); }
    else if (strcmp(prop, "row-gap") == 0)             { prop_id = P_ROW_GAP;       ival = interp_gap(val); }
    else if (strcmp(prop, "grid-auto-flow") == 0)      { prop_id = P_GRID_FLOW;     ival = interp_grid_flow(val); }
    else if (strcmp(prop, "grid-column") == 0)         { prop_id = P_GRID_COL_SPAN; ival = interp_grid_span(val); }
    else if (strcmp(prop, "grid-row") == 0)            { prop_id = P_GRID_ROW_SPAN; ival = interp_grid_span(val); }
    else if (strcmp(prop, "float") == 0)               { prop_id = P_FLOAT;         ival = interp_float(val); }
    else if (strcmp(prop, "clear") == 0)               { prop_id = P_CLEAR;         ival = interp_clear(val); }
    else if (strcmp(prop, "visibility") == 0)          { prop_id = P_VISIBILITY;    ival = interp_visibility(val); }
    else if (strcmp(prop, "overflow-x") == 0)          { prop_id = P_OVERFLOW_X;    ival = interp_overflow(val); }
    else if (strcmp(prop, "overflow-y") == 0)          { prop_id = P_OVERFLOW_Y;    ival = interp_overflow(val); }
    else if (strcmp(prop, "cursor") == 0)              { prop_id = P_CURSOR;        ival = interp_cursor(val); }
    else if (strcmp(prop, "text-overflow") == 0)       { prop_id = P_TEXT_OVERFLOW; ival = interp_text_overflow(val); }
    else if (strcmp(prop, "word-break") == 0)          { prop_id = P_WORD_BREAK;    ival = interp_word_break(val); }
    else if (strcmp(prop, "overflow-wrap") == 0 ||
             strcmp(prop, "word-wrap") == 0)            { prop_id = P_WORD_BREAK;    ival = interp_overflow_wrap(val); }
    else if (strcmp(prop, "border-collapse") == 0)      { prop_id = P_BORDER_COLLAPSE; ival = interp_border_collapse(val); }
    else if (strcmp(prop, "border-spacing") == 0)       { prop_id = P_BORDER_SPACING;  ival = interp_border_spacing(val); }
    else if (strcmp(prop, "empty-cells") == 0)           { prop_id = P_EMPTY_CELLS;     ival = interp_empty_cells(val); }
    else if (strcmp(prop, "caption-side") == 0)          { prop_id = P_CAPTION_SIDE;    ival = interp_caption_side(val); }
    else if (strcmp(prop, "table-layout") == 0)          { prop_id = P_TABLE_LAYOUT;    ival = interp_table_layout(val); }
    else if (strcmp(prop, "font-variant") == 0)          { prop_id = P_FONT_VARIANT;    ival = interp_font_variant(val); }
    else if (strcmp(prop, "hyphens") == 0)               { prop_id = P_HYPHENS;         ival = interp_hyphens(val); }
    else if (strcmp(prop, "user-select") == 0)           { prop_id = P_USER_SELECT;     ival = interp_user_select(val); }
    else if (strcmp(prop, "caret-color") == 0) {
        int o = interp_caret_color(val);
        if (o != CSS_LEN_AUTO && o < 0) return 0;
        dst[0].prop = P_CARET_COLOR; dst[0].ival = o; return 1;
    }
    else if (strcmp(prop, "appearance") == 0)            { prop_id = P_APPEARANCE;      ival = interp_appearance(val); }
    else if (strcmp(prop, "pointer-events") == 0)        { prop_id = P_POINTER_EVENTS;  ival = interp_pointer_events(val); }
    else if (strcmp(prop, "background-repeat") == 0)    { prop_id = P_BG_REPEAT;     ival = interp_bg_repeat(val); }
    else if (strcmp(prop, "background-size") == 0)      return expand_bg_size(val, dst, cap);
    else if (strcmp(prop, "background-clip") == 0 ||
             strcmp(prop, "-webkit-background-clip") == 0)
                                                        { prop_id = P_BG_CLIP;       ival = interp_bg_clip(val); }
    else if (strcmp(prop, "-webkit-text-fill-color") == 0 ||
             strcmp(prop, "text-fill-color") == 0) {
        /* transparent (CC_COLOR_TRANSPARENT, negative) must survive: the generic
         * `ival < 0` drop below would eat it. currentColor is a no-op (the fill
         * IS the element color) and junk fails closed, both dropped here. */
        int o = interp_color(val);
        if (o == -1 || o == CC_COLOR_CURRENT) return 0;
        dst[0].prop = P_TEXT_FILL; dst[0].ival = o; return 1;
    }
    else if (strcmp(prop, "fill") == 0) {
        /* SVG `fill` on an element tints its inline-<svg> shapes that carry no fill
         * of their own. currentColor stays a sentinel (the painter substitutes the
         * element colour); junk/none fail closed to unset (the SVG default black). */
        int o = interp_color(val);
        if (o == -1) return 0;
        prop_id = P_SVG_FILL; ival = o;
    }
    else if (strcmp(prop, "background-origin") == 0)    { prop_id = P_BG_ORIGIN;     ival = interp_bg_origin(val); }
    else if (strcmp(prop, "background-attachment") == 0){ prop_id = P_BG_ATTACHMENT; ival = interp_bg_attachment(val); }
    else if (strcmp(prop, "isolation") == 0)            { prop_id = P_ISOLATION;     ival = interp_isolation(val); }
    else if (strcmp(prop, "contain") == 0)              { prop_id = P_CONTAIN;       ival = interp_contain(val); }
    else if (strcmp(prop, "content-visibility") == 0)   { prop_id = P_CONTENT_VISIBILITY; ival = interp_content_visibility(val); }
    else if (strcmp(prop, "image-rendering") == 0)      { prop_id = P_IMAGE_RENDERING;    ival = interp_image_rendering(val); }
    else if (strcmp(prop, "color-scheme") == 0)         { prop_id = P_COLOR_SCHEME;       ival = interp_color_scheme(val); }
    else if (strcmp(prop, "accent-color") == 0) {
        int o = interp_accent_color(val);
        if (o != CSS_LEN_AUTO && o < 0) return 0;
        dst[0].prop = P_ACCENT_COLOR; dst[0].ival = o; return 1;
    }
    else if (strcmp(prop, "print-color-adjust") == 0)   { prop_id = P_PRINT_COLOR_ADJUST;   ival = interp_print_color_adjust(val); }
    else if (strcmp(prop, "forced-color-adjust") == 0)  { prop_id = P_FORCED_COLOR_ADJUST;  ival = interp_forced_color_adjust(val); }
    else if (strcmp(prop, "mix-blend-mode") == 0)       { prop_id = P_MIX_BLEND_MODE;   ival = interp_mix_blend_mode(val); }
    else if (strcmp(prop, "object-fit") == 0)           { prop_id = P_OBJECT_FIT;       ival = interp_object_fit(val); }
    else if (strcmp(prop, "list-style-position") == 0)  { prop_id = P_LIST_STYLE_POS;   ival = interp_list_style_pos(val); }
    else if (strcmp(prop, "font-kerning") == 0)         { prop_id = P_FONT_KERNING;     ival = interp_font_kerning(val); }
    else if (strcmp(prop, "text-rendering") == 0)       { prop_id = P_TEXT_RENDERING;   ival = interp_text_rendering(val); }
    else if (strcmp(prop, "font-stretch") == 0)         { prop_id = P_FONT_STRETCH;     ival = interp_font_stretch(val); }
    else if (strcmp(prop, "resize") == 0)               { prop_id = P_RESIZE;           ival = interp_resize(val); }
    else if (strcmp(prop, "scroll-behavior") == 0)      { prop_id = P_SCROLL_BEHAVIOR;  ival = interp_scroll_behavior(val); }
    else if (strcmp(prop, "touch-action") == 0)         { prop_id = P_TOUCH_ACTION;     ival = interp_touch_action(val); }
    else if (strcmp(prop, "overscroll-behavior") == 0)  { prop_id = P_OVERSCROLL_BEHAVIOR; ival = interp_overscroll_behavior(val); }
    else if (strcmp(prop, "backface-visibility") == 0)  { prop_id = P_BACKFACE_VISIBILITY; ival = interp_backface_visibility(val); }
    else if (strcmp(prop, "animation-duration") == 0) {
        int ms = interp_time_ms(val);
        if (ms < 0) return 0;
        dst[0].prop = P_ANIM_DURATION; dst[0].ival = ms; return 1;
    }
    else if (strcmp(prop, "animation-name") == 0) {
        /* store name in ival as first-char encoding for cascade; the full
         * name string is recovered later from sheet->keyframes[] by matching
         * first character + length (see resolve_anim_keyframes). */
        int enc = (int)(val[0]) | ((int)(strlen(val) > 63 ? 63 : strlen(val)) << 8);
        dst[0].prop = P_ANIM_NAME; dst[0].ival = enc; return 1;
    }
    else if (strcmp(prop, "animation-iteration-count") == 0) {
        if (csel_ci_eq(val, "infinite")) { dst[0].prop = P_ANIM_ITERS; dst[0].ival = -1; return 1; }
        double d; const char *e;
        if (!parse_num(val, &d, &e) || *e != '\0' || d < 0.0) return 0;
        dst[0].prop = P_ANIM_ITERS; dst[0].ival = (int)(d + 0.5); return 1;
    }
    else if (strcmp(prop, "animation-direction") == 0) {
        int iv = -1;
        if (csel_ci_eq(val, "normal")) iv = 0;
        else if (csel_ci_eq(val, "reverse")) iv = 1;
        else if (csel_ci_eq(val, "alternate")) iv = 2;
        else if (csel_ci_eq(val, "alternate-reverse")) iv = 3;
        else return 0;
        dst[0].prop = P_ANIM_DIR; dst[0].ival = iv; return 1;
    }
    else if (strcmp(prop, "animation-fill-mode") == 0) {
        int iv = -1;
        if (csel_ci_eq(val, "none")) iv = 0;
        else if (csel_ci_eq(val, "forwards")) iv = 1;
        else if (csel_ci_eq(val, "backwards")) iv = 2;
        else if (csel_ci_eq(val, "both")) iv = 3;
        else return 0;
        dst[0].prop = P_ANIM_FILL; dst[0].ival = iv; return 1;
    }
    else if (strcmp(prop, "animation-timing-function") == 0) {
        int iv = -1;
        if (csel_ci_eq(val, "ease")) iv = 1;
        else if (csel_ci_eq(val, "linear")) iv = 0;
        else if (csel_ci_eq(val, "ease-in")) iv = 2;
        else if (csel_ci_eq(val, "ease-out")) iv = 3;
        else if (csel_ci_eq(val, "ease-in-out")) iv = 4;
        else return 0;
        dst[0].prop = P_ANIM_TIMING; dst[0].ival = iv; return 1;
    }
    else if (strcmp(prop, "animation-delay") == 0) {
        int ms = interp_time_ms(val);
        if (ms < 0) return 0;
        dst[0].prop = P_ANIM_DELAY; dst[0].ival = ms; return 1;
    }
    else if (strcmp(prop, "transition-duration") == 0) {
        int ms = interp_time_ms(val);
        if (ms < 0) return 0;
        dst[0].prop = P_TRANSITION_DURATION; dst[0].ival = ms; return 1;
    }
    else if (strcmp(prop, "transition-property") == 0) {
        int v = interp_transition_property(val);
        if (v < 0) return 0;
        dst[0].prop = P_TRANSITION_PROPERTY; dst[0].ival = v; return 1;
    }
    else if (strcmp(prop, "transition-timing-function") == 0) {
        int iv = -1;
        if (csel_ci_eq(val, "ease")) iv = 1;
        else if (csel_ci_eq(val, "linear")) iv = 0;
        else if (csel_ci_eq(val, "ease-in")) iv = 2;
        else if (csel_ci_eq(val, "ease-out")) iv = 3;
        else if (csel_ci_eq(val, "ease-in-out")) iv = 4;
        else return 0;
        dst[0].prop = P_TRANSITION_TIMING; dst[0].ival = iv; return 1;
    }
    else if (strcmp(prop, "transition-delay") == 0) {
        int ms = interp_time_ms(val);
        if (ms < 0) return 0;
        dst[0].prop = P_TRANSITION_DELAY; dst[0].ival = ms; return 1;
    }
    else if (strcmp(prop, "transition") == 0)
        return expand_transition(val, dst, cap);
    else if (strcmp(prop, "filter") == 0)               return expand_filter(val, dst, cap);
    else if (strcmp(prop, "backdrop-filter") == 0 ||
             strcmp(prop, "-webkit-backdrop-filter") == 0)
        return expand_backdrop_filter(val, dst, cap);
    else if (strcmp(prop, "background-position") == 0)   return expand_bg_position(val, dst, cap);
    else if (strcmp(prop, "content") == 0)                return expand_content(val, dst, cap, contenttab, ncontent, contentcap);
    else if (strcmp(prop, "grid-template-areas") == 0)
        return expand_grid_areas(val, dst, cap, contenttab, ncontent, contentcap);
    else if (strcmp(prop, "grid-area") == 0)              return expand_grid_area(val, dst, cap);
    else if (strcmp(prop, "grid-template") == 0 || strcmp(prop, "grid") == 0)
        return expand_grid_template(val, dst, cap, contenttab, ncontent, contentcap);
    else { if (known != NULL) *known = 0; return 0; }

    /* `transparent` (-3) and `currentColor` (-2) are VALUES, not failures: the
     * colour interpreters return them as sentinels and the blanket `ival < 0`
     * below used to eat every one. `background-color:transparent` is how a page
     * clears an inherited or UA background, so dropping it left the old paint in
     * place -- 65 declarations in the measured corpus, on every page in it. */
    if (ival == CC_COLOR_CURRENT || ival == CC_COLOR_TRANSPARENT) {
        dst[0].prop = prop_id;
        dst[0].ival = ival;
        return 1;
    }
    if (ival < 0) {
        /* One chokepoint for every property that reaches the tail: a CSS-wide
         * keyword claims the slot without writing a value. */
        if (css_wide_keyword(val)) {
            dst[0].prop = prop_id;
            dst[0].wide = 1;
            return 1;
        }
        return 0;  /* unsupported value */
    }
    dst[0].prop = prop_id;
    dst[0].ival = ival;
    return 1;
}

/* True when `v` is a single identifier carrying a vendor prefix, and writes the
 * unprefixed spelling to `out`. A vendor prefix on a VALUE is the same aliasing
 * rule as one on a property name (`position: -webkit-sticky` IS `position: sticky`,
 * `user-select: -moz-none` IS `user-select: none`), so it is applied at the same
 * one place and with the same "strip once, ask again" bound. Multi-token values are
 * excluded on purpose: a prefixed token inside a shorthand names something the
 * standard grammar may not have (`-webkit-focus-ring-color` is not a colour), and
 * rewriting one token of several would be guessing. */
static int devendor_value(const char *v, char *out, size_t outcap) {
    if (v[0] != '-' || v[1] == '\0' || v[1] == '-') return 0;
    for (const char *q = v; *q != '\0'; ++q)
        if (*q == ' ' || *q == '\t' || *q == ',' || *q == '(') return 0;
    static const char *const VENDOR[] = { "-webkit-", "-moz-", "-ms-", "-o-" };
    for (size_t i = 0; i < sizeof VENDOR / sizeof *VENDOR; ++i) {
        size_t plen = strlen(VENDOR[i]);
        if (strncmp(v, VENDOR[i], plen) != 0) continue;
        const char *bare = v + plen;
        if (bare[0] == '\0' || bare[0] == '-') return 0;
        size_t n = strlen(bare);
        if (n + 1 > outcap) return 0;
        memcpy(out, bare, n + 1);
        return 1;
    }
    return 0;
}

/* The generic values a shorthand's grammar is most likely to accept. Used only to
 * DISCOVER which longhand slots a shorthand writes -- see wide_claim below. They are
 * ordinary CSS values, not sentinels: whichever one parses, parses through the same
 * dispatch that will parse the page's real declarations. */
static const char *const WIDE_PROBES[] = {
    "0", "none", "auto", "normal", "0 0", "medium serif", "1 1 auto",
    "medium none currentcolor", "0 0 0 0",
};

/* CSS Cascade 5 section 7.3: a CSS-wide keyword is valid on EVERY property, and on a
 * SHORTHAND it applies to every longhand the shorthand expands to. So honouring one
 * needs the longhand SLOT SET, not the property name -- and the set is already
 * encoded, exactly once, in the shorthand's own expander.
 *
 * Rather than keep a second shorthand->longhands table that would go stale on the
 * next shorthand added, the set is read back OUT of the dispatch: a shorthand writes
 * its slots for any value its grammar accepts, so parsing a generic probe value
 * yields the slots, and those slots are then claimed with no value written. A
 * property that accepts no probe (it has no shorthand grammar) falls through to the
 * single-slot claim the generic tail already did.
 *
 * Claiming matters because a dropped declaration hands its slot to a LOWER
 * specificity rule: `p{padding:8px} p.bare{padding:inherit}` painted 8px where every
 * other engine paints the parent's padding. */
static int wide_claim(const char *prop, css_decl *dst, int cap,
                      char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap,
                      char (*contenttab)[CSS_URL_MAX], size_t *ncontent, size_t contentcap) {
    (void)urltab; (void)nurl; (void)urlcap;
    (void)contenttab; (void)ncontent; (void)contentcap;
    /* Scratch pools: a probe must never consume an entry of the real url/content
     * pools, which belong to the declarations the page actually wrote. */
    char probe_urls[2][CSS_URL_MAX];
    char probe_content[2][CSS_URL_MAX];
    size_t nprobe_url = 0, nprobe_content = 0;
    for (size_t i = 0; i < sizeof WIDE_PROBES / sizeof *WIDE_PROBES; ++i) {
        /* Wide enough for the widest shorthand in the dispatch (the four-side
         * length shorthands emit a px and a percentage slot per side, and
         * grid-template-columns emits one slot per track). V-002: zero every
         * field, so a field added to css_decl cannot leak through the probe. */
        css_decl tmp[CSS_WIDE_PROBE_DECLS];
        memset(tmp, 0, sizeof tmp);
        int inner_known = 1;
        int n = interpret_prop_dispatch(prop, WIDE_PROBES[i], tmp,
                                        (int)(sizeof tmp / sizeof *tmp),
                                        probe_urls, &nprobe_url, 2,
                                        probe_content, &nprobe_content, 2,
                                        &inner_known);
        if (n <= 0) continue;
        if (n > cap) n = cap;
        for (int k = 0; k < n; ++k) {
            dst[k].prop = tmp[k].prop;
            dst[k].ival = 0;
            dst[k].emil = 0;
            dst[k].wide = 1;
        }
        return n;
    }
    return 0;
}

/* The two value-level rules that hold for EVERY property, applied once around the
 * dispatch so no per-property branch has to remember them. Order matters: the
 * dispatch runs first, so a property whose own grammar happens to define one of
 * these spellings keeps its meaning. */
static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap,
                           char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap,
                           char (*contenttab)[CSS_URL_MAX], size_t *ncontent, size_t contentcap,
                           int *known) {
    int nw = interpret_prop_dispatch(prop, val, dst, cap, urltab, nurl, urlcap,
                                     contenttab, ncontent, contentcap, known);
    if (nw > 0) return nw;
    /* An unknown property NAME has no grammar to retry against. */
    if (known != NULL && *known == 0) return 0;

    char bare[CSS_TOK_MAX];
    if (devendor_value(val, bare, sizeof bare)) {
        int inner_known = 1;
        nw = interpret_prop_dispatch(prop, bare, dst, cap, urltab, nurl, urlcap,
                                     contenttab, ncontent, contentcap, &inner_known);
        if (nw > 0) return nw;
    }
    if (css_wide_keyword(val))
        return wide_claim(prop, dst, cap, urltab, nurl, urlcap,
                          contenttab, ncontent, contentcap);
    return 0;
}

/* Copies hostile CSS text into a fixed report buffer: bounded, NUL-terminated,
 * truncated with a visible "..." marker rather than silently cut, and with control
 * bytes folded to '.' -- the drop report is printed to a terminal, and an ANSI escape
 * smuggled through a remote stylesheet must not be able to paint it. */
static void drop_copy_text(char *dst, size_t cap, const char *src) {
    if (cap == 0) return;
    size_t len = strlen(src);
    size_t room = cap - 1;
    size_t take = len;
    int trunc = 0;
    if (take > room) { trunc = 1; take = (room > 3) ? room - 3 : 0; }
    size_t o = 0;
    for (size_t i = 0; i < take; ++i) {
        unsigned char c = (unsigned char)src[i];
        dst[o++] = (c < 0x20 || c == 0x7f) ? '.' : (char)c;
    }
    if (trunc) { for (int k = 0; k < 3 && o + 1 < cap; ++k) dst[o++] = '.'; }
    dst[o] = '\0';
}

/* Records one dropped declaration, coalescing by (property, cause). `total` counts
 * every drop seen even once the listing is full, so a report can state the real
 * magnitude instead of understating it. */
static void drop_record(css_drop_log *log, const char *prop, const char *val, int cause) {
    if (log == NULL) return;
    ++log->total;
    if (log->items == NULL || log->cap == 0) return;
    for (size_t i = 0; i < log->n; ++i) {
        if (log->items[i].cause == cause &&
            strcmp(log->items[i].prop, prop) == 0) {
            if (log->items[i].count < INT_MAX) ++log->items[i].count;
            return;
        }
    }
    if (log->n >= log->cap) return;
    css_drop *d = &log->items[log->n++];
    drop_copy_text(d->prop, sizeof d->prop, prop);
    drop_copy_text(d->val, sizeof d->val, val);
    d->cause = cause;
    d->count = 1;
}

/* Interprets one declaration span s[0,n) into dst (up to cap). Returns the number of
 * css_decl written (0 if unsupported). Splits `prop: value`, strips a trailing
 * `!important` (stamping every emitted decl), resolves any var() reference against
 * tab/ntab (a custom-property declaration itself, `--name: ...`, is not a real
 * property and falls through interpret_prop's unknown-property path unchanged),
 * then dispatches on the property. `log` (optional) records what was discarded. */
static int parse_one_decl(const char *s, size_t n, css_decl *dst, int cap,
                           const css_custom_prop *tab, size_t ntab,
                           char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap,
                           char (*contenttab)[CSS_URL_MAX], size_t *ncontent, size_t contentcap,
                           css_drop_log *log) {
    if (cap < 1) return 0;
    size_t c = 0;
    while (c < n && s[c] != ':') ++c;
    if (c >= n) return 0;  /* no colon */

    char prop[CSS_TOK_MAX];
    char val[CSS_URL_MAX];
    if (copy_trim(s, 0, c, prop, sizeof prop) == (size_t)-1) return 0;
    if (copy_trim(s, c + 1, n, val, sizeof val) == (size_t)-1) return 0;
    if (prop[0] == '\0' || val[0] == '\0') return 0;
    for (char *p = prop; *p != '\0'; ++p) *p = csel_lower_ch(*p);

    int important = strip_important(val);
    if (val[0] == '\0') return 0;  /* bare "!important" with no value */

    const char *use_val = val;
    char resolved[CSS_URL_MAX];
    if (csel_substr(val, "var(", 1)) {
        if (!resolve_var(val, resolved, sizeof resolved, tab, ntab)) {
            /* An unresolvable var() is a value problem, not a missing property:
             * the referenced custom property was never declared (or the fallback
             * chain bottomed out), so the declaration is invalid at computed-value
             * time exactly as CSS Variables 1 says. */
            drop_record(log, prop, val, CSS_DROP_BAD_VALUE);
            return 0;
        }
        use_val = resolved;
    }

    /* A custom property declaration is not a property, so it is not a drop -- it
     * was already harvested into the var() table by collect_custom_props_scoped. */
    int is_custom = (prop[0] == '-' && prop[1] == '-');

    int known = 1;
    int nw = interpret_prop(prop, use_val, dst, cap, urltab, nurl, urlcap,
                             contenttab, ncontent, contentcap, &known);
    if (nw == 0 && !is_custom) {
        drop_record(log, prop, use_val,
                    known ? CSS_DROP_BAD_VALUE : CSS_DROP_UNKNOWN_PROP);
    }
    for (int i = 0; i < nw; ++i) dst[i].important = important;
    return nw;
}

/* Splits a ';'-separated declaration block into dst (up to cap). Returns count.
 * tab/ntab is the custom-property table var() resolves against (NULL/0 when none,
 * e.g. an inline style resolved against a NULL sheet). urltab/nurl/urlcap is the
 * background-image url() pool (see P_BG_IMAGE_URL). */
static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,
                               const css_custom_prop *tab, size_t ntab,
                               char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap,
                               char (*contenttab)[CSS_URL_MAX], size_t *ncontent, size_t contentcap,
                               css_drop_log *log) {
    size_t count = 0, i = 0;
    while (i < n && count < cap) {
        size_t j = i;
        while (j < n && s[j] != ';') ++j;
        count += (size_t)parse_one_decl(s + i, j - i, &dst[count], (int)(cap - count), tab, ntab,
                                        urltab, nurl, urlcap, contenttab, ncontent, contentcap,
                                        log);
        i = (j < n) ? j + 1 : j;
    }
    return count;
}

/* Adds a rule: selector list s[ss,se), declaration block s[ds,de). */
static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,
                     size_t ds, size_t de, css_drop_log *log) {
    css_sel tmp[CSS_SELS_PER_GROUP];
    int got = 0;
    size_t i = ss;
    while (i < se && got < CSS_SELS_PER_GROUP) {
        size_t j = i;
        while (j < se && s[j] != ',') ++j;
        if (csel_parse(s, i, j, &tmp[got])) ++got;
        i = (j < se) ? j + 1 : j;
    }
    if (got == 0) return;  /* no supported selector: skip the whole rule */

    /* Interpret the block with GUARANTEED headroom, growing and retrying until the
     * result is provably complete: the rule is trusted only when it finishes with
     * CSS_DECL_SLOTS_MIN slots still free, which proves no declaration in it was
     * refused for want of room. Growing once per rule (the old behaviour) left the
     * free space cycling down to 1, and whichever rules landed there lost most of
     * their declarations without a trace. */
    size_t dstart = sh->ndecls;
    size_t dn = 0;
    for (;;) {
        size_t room = sh->decls_cap - dstart;
        if (room >= CSS_DECL_SLOTS_MIN) {
            /* The retry re-reads the same text, so the log has to be rewound with
             * it or the same drop would be counted once per attempt. */
            size_t log_n = (log != NULL) ? log->n : 0;
            size_t log_total = (log != NULL) ? log->total : 0;
            dn = interpret_decls(s + ds, de - ds, &sh->decls[dstart], room,
                                 sh->custom, sh->ncustom,
                                 sh->bg_urls, &sh->nbg_urls, CSS_MAX_BG_URLS,
                                 sh->content_urls, &sh->ncontent_urls, 64, log);
            if (room - dn >= CSS_DECL_SLOTS_MIN) break;   /* finished with slack */
            if (log != NULL) { log->n = log_n; log->total = log_total; }
        }
        size_t nc = sh->decls_cap ? sh->decls_cap * 2 : CSS_INIT_DECLS;
        if (nc <= sh->decls_cap) return;                  /* overflow: fail closed */
        css_decl *g = (css_decl *)realloc(sh->decls, nc * sizeof *g);
        if (g == NULL) return;
        /* V-002: zero the fresh region. The property emitters write only the fields
         * their property has -- `emil`, the font-relative coefficient, is written by
         * the LENGTH emitters alone -- so an unzeroed tail would hand a non-length
         * slot a coefficient made of whatever realloc returned, and the cascade
         * would then scale it by the element's font-size. */
        memset(g + sh->decls_cap, 0, (nc - sh->decls_cap) * sizeof *g);
        sh->decls = g;
        sh->decls_cap = nc;
        dn = 0;
    }
    if (dn == 0) return;

    sh->ndecls += dn;

    /* Grow rules array if needed. */
    if (sh->nrules >= sh->rules_cap) {
        size_t nc = sh->rules_cap ? sh->rules_cap * 2 : CSS_INIT_RULES;
        css_rule *g = (css_rule *)realloc(sh->rules, nc * sizeof *g);
        if (g == NULL) return;
        sh->rules = g;
        sh->rules_cap = nc;
    }
    size_t rule_idx = sh->nrules;
    sh->rules[rule_idx].start = dstart;
    sh->rules[rule_idx].count = dn;
    ++sh->nrules;

    /* Grow sels array if needed. */
    for (int g = 0; g < got; ++g) {
        if (sh->nsels >= sh->sels_cap) {
            size_t nc = sh->sels_cap ? sh->sels_cap * 2 : CSS_INIT_SELS;
            css_sel *gr = (css_sel *)realloc(sh->sels, nc * sizeof *gr);
            if (gr == NULL) break;  /* keep what we have */
            sh->sels = gr;
            sh->sels_cap = nc;
        }
        css_sel *dst = &sh->sels[sh->nsels];
        *dst = tmp[g];
        dst->rule = (int)rule_idx;
        dst->order = (int)sh->nsels;
        ++sh->nsels;
    }
}

/* Skips an @-rule starting at s[i] ('@'): to the terminating ';' or past a
 * brace-balanced block. Returns the index just past it. */
static size_t skip_at_rule(const char *s, size_t i, size_t n) {
    while (i < n && s[i] != ';' && s[i] != '{') ++i;
    if (i < n && s[i] == ';') return i + 1;
    if (i < n && s[i] == '{') {
        int depth = 0;
        while (i < n) {
            if (s[i] == '{') ++depth;
            else if (s[i] == '}') { --depth; ++i; if (depth == 0) return i; continue; }
            ++i;
        }
    }
    return i;
}

/* Index just past the '}' that closes the block whose '{' is at s[open]. n if
 * unbalanced. */
static size_t block_end(const char *s, size_t open, size_t n) {
    int depth = 0;
    for (size_t i = open; i < n; ++i) {
        if (s[i] == '{') ++depth;
        else if (s[i] == '}') { --depth; if (depth == 0) return i + 1; }
    }
    return n;
}

/* --- @media query evaluation (Hito 23b). All inputs are bounded substrings; the
 * query never fetches and unknown features fail closed (do not match). --- */

#define CSS_MEDIA_TOK 128u

/* A media-query length in px ("600px" -> 600, "40em" -> 640).
 *
 * The unit is load-bearing and used to be discarded, which made the reader return
 * the bare number: `(min-width: 40em)` compared 40 against the viewport and every
 * em/rem-based query was therefore true no matter how wide the query asked for.
 * Inside a media query `em`/`rem` refer to the INITIAL font size (16px), never the
 * author's root font-size -- which is exactly why rem_rebase leaves at-rule
 * preludes alone. An unknown unit keeps the historical bare-number reading. */
static int media_len_px(const char *v) {
    double px;
    if (length_px(v, &px)) return css_round_clamp(px, 0, CSS_LEN_MAX);

    /* Not a length. Keep the historical bare-number reading so a query with a
     * unit this engine does not model still compares something rather than
     * collapsing to 0 (which would make every min-width query true). */
    double d;
    const char *e;
    if (!parse_num(v, &d, &e)) return 0;
    return css_round_clamp(d, 0, CSS_LEN_MAX);
}

/* Trims ASCII spaces/tabs from both ends of a NUL-terminated string, in place. */
static void trim_inplace(char *s) {
    size_t a = 0;
    while (s[a] == ' ' || s[a] == '\t') ++a;
    size_t n = strlen(s + a);
    memmove(s, s + a, n + 1);
    while (n > 0 && (s[n-1] == ' ' || s[n-1] == '\t')) s[--n] = '\0';
}

/* Lowercased, trimmed copy of s[a,b) into dst; SIZE_MAX if it does not fit. */
static size_t copy_lower_trim(const char *s, size_t a, size_t b, char *dst, size_t cap) {
    size_t n = copy_trim(s, a, b, dst, cap);
    if (n == (size_t)-1) return (size_t)-1;
    for (size_t i = 0; i < n; ++i) dst[i] = csel_lower_ch(dst[i]);
    return n;
}

/* One media part: a type word ("screen"/"print"/"all") or a "(feature: value)".
 * p is already lowercased and trimmed. Unknown -> 0 (fail closed). */
static int media_part_matches(const char *p, const css_media *m) {
    if (p[0] == '(') {
        size_t L = strlen(p);
        if (L < 2 || p[L-1] != ')') return 0;
        char inner[CSS_MEDIA_TOK];
        size_t k = 0;
        for (size_t i = 1; i + 1 < L && k + 1 < sizeof inner; ++i) inner[k++] = p[i];
        inner[k] = '\0';
        char *colon = strchr(inner, ':');
        if (colon == NULL) return 0;  /* boolean feature (e.g. "(color)"): fail closed */
        *colon = '\0';
        char *name = inner, *value = colon + 1;
        trim_inplace(name);
        trim_inplace(value);
        if (strcmp(name, "prefers-color-scheme") == 0)
            return (strcmp(value, "dark") == 0)  ? (m->prefers_dark ? 1 : 0)
                 : (strcmp(value, "light") == 0) ? (m->prefers_dark ? 0 : 1) : 0;
        if (strcmp(name, "min-width") == 0) return m->width_px >= media_len_px(value);
        if (strcmp(name, "max-width") == 0) return m->width_px <= media_len_px(value);
        return 0;  /* unknown feature: fail closed */
    }
    if (strcmp(p, "all") == 0) return 1;
    if (strcmp(p, "screen") == 0) return m->print ? 0 : 1;
    if (strcmp(p, "print") == 0) return m->print ? 1 : 0;
    return 0;  /* unknown media type: fail closed */
}

/* One media query segment (between commas): an AND of parts. `not`/`or`/unknown
 * fail closed. An empty segment matches (all). */
static int media_segment_matches(const char *s, size_t a, size_t b, const css_media *m) {
    int result = 1, any = 0;
    size_t i = a;
    while (i < b) {
        while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;
        if (i >= b) break;
        size_t ts = i;
        char buf[CSS_MEDIA_TOK];
        if (s[i] == '(') {
            int d = 0;
            while (i < b) {
                if (s[i] == '(') ++d;
                else if (s[i] == ')') { ++i; if (--d == 0) break; continue; }
                ++i;
            }
            if (copy_lower_trim(s, ts, i, buf, sizeof buf) == (size_t)-1) return 0;
            if (!media_part_matches(buf, m)) result = 0;
            any = 1;
        } else {
            size_t we = i;
            while (we < b && s[we] != ' ' && s[we] != '\t' && s[we] != '(') ++we;
            if (copy_lower_trim(s, ts, we, buf, sizeof buf) == (size_t)-1) return 0;
            i = we;
            if (strcmp(buf, "and") == 0 || strcmp(buf, "only") == 0) {
                /* connector / legacy keyword: ignore */
            } else if (strcmp(buf, "not") == 0 || strcmp(buf, "or") == 0) {
                return 0;  /* negation / level-4 or: fail closed */
            } else {
                if (!media_part_matches(buf, m)) result = 0;
                any = 1;
            }
        }
    }
    return any ? result : 1;
}

/* A media query list s[a,b): comma-separated segments OR'd together. */
static int media_matches(const char *s, size_t a, size_t b, const css_media *m) {
    while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == '\r')) ++a;
    if (a >= b) return 1;  /* empty query == all */
    size_t i = a;
    while (i < b) {
        size_t seg = i;
        while (i < b && s[i] != ',') ++i;
        if (media_segment_matches(s, seg, i, m)) return 1;
        if (i < b) ++i;
    }
    return 0;
}

/* True when s[i] ('@') begins an "@media" at-rule. */
static int at_is_media(const char *s, size_t i, size_t n) {
    static const char kw[5] = { 'm', 'e', 'd', 'i', 'a' };
    if (i + 6 > n) return 0;
    for (int k = 0; k < 5; ++k) if (csel_lower_ch(s[i + 1 + k]) != kw[k]) return 0;
    size_t j = i + 6;
    return j >= n || s[j] == ' ' || s[j] == '\t' || s[j] == '\n' || s[j] == '\r'
        || s[j] == '{' || s[j] == '(';
}

#define CSS_MEDIA_MAX_DEPTH 4

/* Structure-aware custom-property collection (see the block comment above
 * collect_custom_decls): walks s[start,end) with the same @media gating as
 * parse_block (a non-matching block — e.g. a dark palette in a light render — is
 * skipped whole; other @-rules are opaque) and folds `--name: value` declarations
 * into tab only from rules with a root-scoped selector (selector_is_root_scoped
 * against root_scope). Runs BEFORE parse_block so every rule's var() references
 * resolve against the complete applicable table regardless of document order. */
static void collect_custom_props_scoped(const char *s, size_t start, size_t end,
                                        const css_media *m, const char *root_scope,
                                        css_custom_prop *tab, size_t cap,
                                        size_t *ntab, int depth) {
    size_t i = start;
    while (i < end) {
        while (i < end && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r')) ++i;
        if (i >= end) break;
        if (s[i] == '@') {
            if (at_is_media(s, i, end)) {
                size_t q = i + 6;
                while (q < end && s[q] != '{' && s[q] != ';') ++q;
                if (q < end && s[q] == '{') {
                    size_t be = block_end(s, q, end);
                    size_t body_start = q + 1;
                    size_t body_end = (be > body_start) ? be - 1 : body_start;
                    if (depth < CSS_MEDIA_MAX_DEPTH && media_matches(s, i + 6, q, m))
                        collect_custom_props_scoped(s, body_start, body_end, m,
                                                    root_scope, tab, cap, ntab,
                                                    depth + 1);
                    i = be;
                    continue;
                }
                i = (q < end && s[q] == ';') ? q + 1 : end;
                continue;
            }
            i = skip_at_rule(s, i, end);
            continue;
        }
        if (s[i] == '}') { ++i; continue; }  /* stray */

        size_t ss = i;
        while (i < end && s[i] != '{' && s[i] != '}') ++i;
        if (i >= end || s[i] != '{') { if (i < end && s[i] == '}') ++i; continue; }
        size_t se = i;
        ++i;
        size_t ds = i;
        while (i < end && s[i] != '}') ++i;
        size_t de = i;
        if (i < end) ++i;

        size_t p = ss;
        while (p < se) {
            size_t q = p;
            while (q < se && s[q] != ',') ++q;
            if (selector_is_root_scoped(s, p, q, root_scope)) {
                collect_custom_decls(s, ds, de, tab, cap, ntab);
                break;
            }
            p = (q < se) ? q + 1 : q;
        }
    }
}

/* Parses rules in s[start,end). A matched @media block is descended into (bounded
 * depth); @import/@font-face/other @-rules and a non-matching @media are skipped. */
static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                        const css_media *media, int depth, css_drop_log *log) {
    size_t i = start;
    while (i < end) {
        while (i < end && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r')) ++i;
        if (i >= end) break;
        if (s[i] == '@') {
            if (at_is_media(s, i, end)) {
                size_t q = i + 6;
                while (q < end && s[q] != '{' && s[q] != ';') ++q;
                if (q < end && s[q] == '{') {
                    size_t be = block_end(s, q, end);     /* past the closing '}' */
                    size_t body_start = q + 1;
                    size_t body_end = (be > body_start) ? be - 1 : body_start;
                    if (depth < CSS_MEDIA_MAX_DEPTH && media_matches(s, i + 6, q, media))
                        parse_block(sh, s, body_start, body_end, media, depth + 1, log);
                    i = be;
                    continue;
                }
                i = (q < end && s[q] == ';') ? q + 1 : end;  /* @media with no block */
                continue;
            }
            /* @font-face { font-family: ...; src: url(...); } — v1: only
             * font-family and src are captured; local() and other descriptors
             * are ignored. The caller resolves src_url against the page origin
             * and downloads the font file, same as background-image. */
            if (i + 9 < end && memcmp(s + i, "@font-face", 10) == 0
                && (s[i + 10] == ' ' || s[i + 10] == '\t' || s[i + 10] == '{')) {
                size_t ob = i + 10;
                while (ob < end && s[ob] != '{') ++ob;
                if (ob < end && s[ob] == '{') {
                    size_t be = block_end(s, ob, end);
                    size_t bstart = ob + 1;
                    size_t bend = (be > bstart) ? be - 1 : bstart;
                    char fam[CSS_TOK_MAX] = "";
                    char surl[CSS_URL_MAX] = "";
                    /* Manually scan for font-family: and src: url(...). */
                    size_t j = bstart;
                    while (j < bend) {
                        while (j < bend && (s[j] == ' ' || s[j] == '\t'
                               || s[j] == '\n' || s[j] == '\r')) ++j;
                        if (j >= bend) break;
                        size_t pstart = j;
                        while (j < bend && s[j] != ':') ++j;
                        if (j >= bend) break;
                        size_t pnlen = j - pstart;
                        size_t vstart = j + 1;
                        while (vstart < bend && (s[vstart] == ' '
                               || s[vstart] == '\t')) ++vstart;
                        /* Find end of value (; or end of block). */
                        size_t vend = vstart;
                        int paren_depth = 0;
                        while (vend < bend) {
                            if (paren_depth == 0 && s[vend] == ';') break;
                            if (s[vend] == '(') ++paren_depth;
                            if (s[vend] == ')' && paren_depth > 0) --paren_depth;
                            ++vend;
                        }
                        if (pnlen == 11 && memcmp(s + pstart, "font-family", 11) == 0) {
                            size_t qs = vstart, qe = vend;
                            if (vend - vstart >= 2 && (s[qs] == '\'' || s[qs] == '"'))
                                { ++qs; --qe; }
                            if (qe > qs) {
                                size_t fl = qe - qs;
                                if (fl >= CSS_TOK_MAX) fl = CSS_TOK_MAX - 1;
                                memcpy(fam, s + qs, fl);
                                fam[fl] = '\0';
                            }
                        } else if (pnlen == 3 && memcmp(s + pstart, "src", 3) == 0) {
                            /* Extract URL inside url(...). */
                            size_t us = vstart;
                            while (us < vend && s[us] != '(') ++us;
                            if (us < vend) ++us;
                            size_t ue = us;
                            while (ue < vend && s[ue] != ')') ++ue;
                            if (us < ue && ue - us < CSS_URL_MAX) {
                                memcpy(surl, s + us, ue - us);
                                surl[ue - us] = '\0';
                            }
                        }
                        j = (vend < bend) ? vend + 1 : bend;
                    }
                    if (fam[0] != '\0' && surl[0] != '\0'
                        && sh->nfont_faces < CSS_MAX_FONT_FACES) {
                        memcpy(sh->font_faces[sh->nfont_faces].family, fam, sizeof fam);
                        memcpy(sh->font_faces[sh->nfont_faces].src_url, surl, sizeof surl);
                        sh->nfont_faces++;
                    }
                    i = be;
                    continue;
                }
            }
            /* R1b: @keyframes name { percentage { decls } ... } */
            if (i + 9 < end && memcmp(s + i, "@keyframes", 10) == 0 &&
                (s[i + 10] == ' ' || s[i + 10] == '\t')) {
                size_t ns = i + 11;
                while (ns < end && (s[ns] == ' ' || s[ns] == '\t')) ++ns;
                size_t ne = ns;
                while (ne < end && s[ne] != ' ' && s[ne] != '\t' && s[ne] != '{') ++ne;
                size_t be = 0;
                if (ne > ns && sh->nkeyframes < CSS_MAX_KEYFRAMES) {
                    char kname[CSS_TOK_MAX];
                    size_t kn = ne - ns;
                    if (kn >= sizeof kname) kn = sizeof kname - 1;
                    memcpy(kname, s + ns, kn);
                    kname[kn] = '\0';
                    size_t ob = ne;
                    while (ob < end && s[ob] != '{') ++ob;
                    if (ob < end) {
                        be = block_end(s, ob, end);
                        /* Parse stops: 0% { ... } 100% { ... } */
                        size_t kp = ob + 1, ke = be - 1;
                        int nst = 0;
                        while (kp < ke && nst < CSS_MAX_KEYFRAME_STOPS) {
                            while (kp < ke && (s[kp] == ' ' || s[kp] == '\t' || s[kp] == '\n')) ++kp;
                            if (kp >= ke || (s[kp] >= '0' && s[kp] <= '9') ||
                                (s[kp] == 'f' && ke - kp >= 4 && memcmp(s + kp, "from", 4) == 0) ||
                                (s[kp] == 't' && ke - kp >= 2 && memcmp(s + kp, "to", 2) == 0)) {
                                double pct;
                                if (s[kp] == 'f') { pct = 0.0; kp += 4; }
                                else if (s[kp] == 't') { pct = 100.0; kp += 2; }
                                else { double d; const char *ep;
                                       if (!parse_num(s + kp, &d, &ep)) break;
                                       pct = d; kp = (size_t)(ep - s); }
                                while (kp < ke && s[kp] != '{') ++kp;
                                if (kp >= ke) break;
                                size_t db = kp + 1;
                                size_t de2 = db;
                                while (de2 < ke && s[de2] != '}') ++de2;
                                /* Parse inner declarations to extract opacity */
                                css_decl kdecls[CSS_MAX_KEYFRAME_DECLS] = { { 0 } };  /* V-002: zero EVERY field, so a field added to css_decl cannot reintroduce the hole */
                                int nd = interpret_decls(s + db, de2 - db,
                                    kdecls, CSS_MAX_KEYFRAME_DECLS, sh->custom, sh->ncustom,
                                    sh->bg_urls, &sh->nbg_urls, CSS_MAX_BG_URLS,
                                    NULL, NULL, 0, log);
                                int kop = -1, kbg = -1, kfg = -1, ktx = CSS_LEN_UNSET, kty = CSS_LEN_UNSET, ksx = 0, ksy = 0, krot = 0;
                                for (int dd = 0; dd < nd; ++dd) {
                                    int p = kdecls[dd].prop;
                                    if (p == P_OPACITY)
                                        kop = kdecls[dd].ival;
                                    else if (p == P_BG)
                                        kbg = kdecls[dd].ival;
                                    else if (p == P_COLOR)
                                        kfg = kdecls[dd].ival;
                                    else if (p == P_TRANSFORM_TX) ktx = kdecls[dd].ival;
                                    else if (p == P_TRANSFORM_TY) kty = kdecls[dd].ival;
                                    else if (p == P_TRANSFORM_SX) ksx = kdecls[dd].ival;
                                    else if (p == P_TRANSFORM_SY) ksy = kdecls[dd].ival;
                                    else if (p == P_TRANSFORM_ROTATE) krot = kdecls[dd].ival;
                                }
                                int kfi = sh->nkeyframes;
                                sh->keyframes[kfi].stops[nst].pct = pct;
                                sh->keyframes[kfi].stops[nst].opacity = kop;
                                sh->keyframes[kfi].stops[nst].bg_color = kbg;
                                sh->keyframes[kfi].stops[nst].fg_color = kfg;
                                sh->keyframes[kfi].stops[nst].transform_tx = ktx;
                                sh->keyframes[kfi].stops[nst].transform_ty = kty;
                                sh->keyframes[kfi].stops[nst].transform_sx = ksx;
                                sh->keyframes[kfi].stops[nst].transform_sy = ksy;
                                sh->keyframes[kfi].stops[nst].transform_rotate = krot;
                                ++nst;
                                kp = de2 + 1;
                            } else break;
                        }
                        if (nst >= 2) {
                            memcpy(sh->keyframes[sh->nkeyframes].name, kname, kn + 1);
                            sh->keyframes[sh->nkeyframes].nstops = nst;
                            ++sh->nkeyframes;
                        }
                    }
                }
                i = (be > 0) ? be : skip_at_rule(s, i, end);
                continue;
            }
            i = skip_at_rule(s, i, end);
            continue;
        }
        if (s[i] == '}') { ++i; continue; }  /* stray */

        size_t ss = i;
        while (i < end && s[i] != '{' && s[i] != '}') ++i;
        if (i >= end || s[i] != '{') { if (i < end && s[i] == '}') ++i; continue; }
        size_t se = i;     /* at '{' */
        ++i;
        size_t ds = i;
        while (i < end && s[i] != '}') ++i;
        size_t de = i;     /* at '}' or end */
        if (i < end) ++i;
        add_rule(sh, s, ss, se, ds, de, log);
    }
}

/* --- rem rebased on the root font-size -------------------------------------
 *
 * The root element's font-size defines what `rem` means for the whole sheet, and
 * `html { font-size: 62.5% }` (so 1rem == 10px) is a near-universal idiom. Holding
 * rem at a fixed 16px rendered every such page 1.6x too large. See spec/css.md
 * "rem is rebased on the root font-size".
 *
 * The rebase rewrites the sheet TEXT rather than threading a base through the 22
 * interp_len call sites, so one change covers font-size, line-height, every box
 * length, calc()/min()/max()/clamp(), shorthands, gradients and var()-substituted
 * values at once, with no unit decoder left behind on the old base. */

/* True for a character that continues a CSS identifier, so a `rem` glued to one is
 * part of a name and not a unit. */
static int rem_ident_ch(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
        || (c >= '0' && c <= '9') || c == '_' || c == '-';
}

/* True when a number may START at a character preceded by prev -- i.e. prev cannot
 * be part of a longer name or number. A sign is deliberately allowed through so the
 * '-' of `-1.5rem` stays in the output and keeps the value negative. */
static int rem_num_starts_after(char prev) {
    if ((prev >= 'a' && prev <= 'z') || (prev >= 'A' && prev <= 'Z')) return 0;
    if (prev >= '0' && prev <= '9') return 0;
    return prev != '_' && prev != '.' && prev != '#' && prev != '%';
}

/* Appends the px equivalent of num rem. Returns 0 (and writes nothing) when the
 * product is not a sane finite length or does not fit, so the caller can fall back
 * to copying the source token verbatim -- fail closed to the pre-rebase reading
 * rather than emitting a bogus length. */
static int rem_emit_px(char *out, size_t cap, size_t *o, double px) {
    if (!(px > -1e9 && px < 1e9)) return 0;
    size_t space = cap - *o;
    if (space == 0) return 0;
    int r = snprintf(out + *o, space, "%.4f", px);
    if (r < 0 || (size_t)r >= space) return 0;
    size_t end = *o + (size_t)r;
    while (end > *o && out[end - 1] == '0') --end;          /* 10.0800 -> 10.08 */
    if (end > *o && out[end - 1] == '.') --end;             /* 16.0000 -> 16    */
    if (cap - end < 3) return 0;
    out[end++] = 'p';
    out[end++] = 'x';
    out[end] = '\0';
    *o = end;
    return 1;
}

/* Rewrites every `<number>rem` length in s[0,n) into `<number x rem_px>px`. Pure:
 * text in, freshly malloc'd NUL-terminated text out (*outlen excludes the NUL).
 * Returns NULL on OOM or an unrepresentable size; the caller then keeps the
 * unrebased sheet, so a failure costs correctness on rem and nothing else.
 *
 * Only DECLARATION VALUES are touched -- the scan tracks brace depth and rewrites
 * solely between a ':' inside a block and the next ';'/'{'/'}'. That single rule is
 * what keeps three classes of text safe at once:
 *   - at-rule preludes (`@media (min-width: 48rem)`), which sit at depth 0 and where
 *     rem means the INITIAL 16px, never the author's root (see media_len_px);
 *   - selectors, including a class that merely spells a unit (`.mt-1rem`);
 *   - quoted strings and url(...), skipped explicitly since `content: "5rem"` is
 *     text and a data: URI is opaque. */
static char *rem_rebase(const char *s, size_t n, double rem_px, size_t *outlen) {
    /* V-001: a rebased token is at most ~3x its source ("1rem" -> "10.08px" plus
     * headroom for the widest finite product), and the multiply must not wrap. */
    if (n > (SIZE_MAX - 64) / 3) return NULL;
    size_t cap = 3 * n + 64;
    char *out = (char *)malloc(cap);
    if (out == NULL) return NULL;

    size_t o = 0, i = 0;
    int depth = 0, in_value = 0;
    while (i < n && o + 1 < cap) {
        char c = s[i];

        if (c == '"' || c == '\'') {                 /* quoted text: verbatim */
            char q = c;
            out[o++] = s[i++];
            while (i < n && o + 2 < cap) {
                if (s[i] == '\\' && i + 1 < n) { out[o++] = s[i++]; out[o++] = s[i++]; continue; }
                int closing = (s[i] == q);
                out[o++] = s[i++];
                if (closing) break;
            }
            continue;
        }
        if (in_value && (c == 'u' || c == 'U') && i + 4 <= n
            && csel_lower_ch(s[i + 1]) == 'r' && csel_lower_ch(s[i + 2]) == 'l'
            && s[i + 3] == '(') {                    /* url(...): opaque */
            while (i < n && o + 1 < cap) {
                int closing = (s[i] == ')');
                out[o++] = s[i++];
                if (closing) break;
            }
            continue;
        }
        if (c == '{')      { ++depth; in_value = 0; out[o++] = s[i++]; continue; }
        if (c == '}')      { if (depth > 0) --depth; in_value = 0; out[o++] = s[i++]; continue; }
        if (c == ';')      { in_value = 0; out[o++] = s[i++]; continue; }
        if (c == ':')      { if (depth > 0) in_value = 1; out[o++] = s[i++]; continue; }

        /* A `<number>rem` unit token, and only in a declaration value. */
        if (in_value && (c == '.' || (c >= '0' && c <= '9'))
            && (i == 0 || rem_num_starts_after(s[i - 1]))
            && !(i >= 2 && s[i - 1] == '-' && s[i - 2] == '-')) {
            double num;
            const char *endp;
            if (parse_num(s + i, &num, &endp)) {
                size_t nlen = (size_t)(endp - (s + i));
                size_t u = i + nlen;
                if (u + 3 <= n && csel_lower_ch(s[u]) == 'r' && csel_lower_ch(s[u + 1]) == 'e'
                    && csel_lower_ch(s[u + 2]) == 'm'
                    && (u + 3 >= n || !rem_ident_ch(s[u + 3]))
                    && rem_emit_px(out, cap, &o, num * rem_px)) {
                    i = u + 3;
                    continue;
                }
            }
        }
        out[o++] = s[i++];
    }
    if (i < n) { free(out); return NULL; }   /* fail closed rather than truncate */
    out[o] = '\0';
    *outlen = o;
    return out;
}

/* Rewinds a sheet to empty while keeping every allocation, so the text can be
 * re-parsed in place. Caps are preserved; only the counters move. */
static void sheet_rewind(css_sheet *sh) {
    /* V-002: the declaration slots are RECYCLED by the re-parse, and a property
     * emitter only writes the fields its property has. Without this, a slot that
     * held `margin:2em` on the first pass would hand its coefficient to whatever
     * non-length declaration lands there on the second -- and rem_rebase makes
     * that second pass the normal case, not an edge one. */
    if (sh->decls != NULL && sh->decls_cap > 0)
        memset(sh->decls, 0, sh->decls_cap * sizeof *sh->decls);
    sh->ndecls = 0;
    sh->nrules = 0;
    sh->nsels = 0;
    sh->ncustom = 0;
    sh->nbg_urls = 0;
    sh->ncontent_urls = 0;
    sh->nkeyframes = 0;
    sh->nfont_faces = 0;
}

static void collect_custom_props_scoped(const char *s, size_t start, size_t end,
                                        const css_media *m, const char *root_scope,
                                        css_custom_prop *tab, size_t cap,
                                        size_t *ntab, int depth);
static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                        const css_media *media, int depth, css_drop_log *log);

/* Replaces a sheet's contents with the result of parsing s[0,n). Custom properties
 * are collected first so every var() reference resolves against the complete table
 * regardless of document order, exactly as on the first parse. */
static void sheet_reparse(css_sheet *sh, const char *s, size_t n,
                          const css_media *m, const char *root_scope,
                          css_drop_log *log) {
    sheet_rewind(sh);
    collect_custom_props_scoped(s, 0, n, m, root_scope,
                                sh->custom, CSS_MAX_CUSTOM_PROPS, &sh->ncustom, 0);
    parse_block(sh, s, 0, n, m, 0, log);
}

/* The root element's font-size in px, as the cascade resolves it (16px when the
 * sheet leaves the root alone). Tag "html" is what PSEUDO_ROOT matches, so `:root`
 * rules are included. */
static double sheet_root_font_px(const css_sheet *sh) {
    css_style root = css_resolve(sh, "html", NULL, NULL, 0, NULL, 0);
    if (root.font_scale <= 0) return 16.0;
    return 16.0 * (double)root.font_scale / 100.0;
}

/* Removes C-style block comments into a fresh NUL-terminated buffer (each comment
 * becomes one space). Caller frees. */
static char *strip_comments(const char *text, size_t len, size_t *outlen) {
    if (len == (size_t)-1) return NULL;
    /* CSS Syntax 3 section 3.2 "Decode bytes": a stylesheet that begins with a
     * U+FEFF BYTE ORDER MARK has it REMOVED before tokenizing. Everywhere else
     * U+FEFF is ZERO WIDTH NO-BREAK SPACE, an ordinary identifier-invalid
     * character, so only the leading one is stripped.
     *
     * Measured on ddg-results, whose <style> opens with a BOM: the first rule's
     * selector parsed as "<BOM>:root", which is not a selector this engine can
     * recognise as root-scoped, so the entire custom-property palette was never
     * collected and forty var() declarations -- font sizes, widths, radii, the
     * whole theme -- died as invalid values further down. One byte. */
    if (len >= 3 && (unsigned char)text[0] == 0xEF &&
        (unsigned char)text[1] == 0xBB && (unsigned char)text[2] == 0xBF) {
        text += 3;
        len  -= 3;
    }
    char *buf = (char *)malloc(len + 1);
    if (buf == NULL) return NULL;
    size_t o = 0, i = 0;
    while (i < len) {
        if (i + 1 < len && text[i] == '/' && text[i+1] == '*') {
            i += 2;
            while (i + 1 < len && !(text[i] == '*' && text[i+1] == '/')) ++i;
            i = (i + 1 < len) ? i + 2 : len;
            buf[o++] = ' ';
        } else {
            buf[o++] = text[i++];
        }
    }
    buf[o] = '\0';
    *outlen = o;
    return buf;
}

css_status css_parse(const char *text, size_t len, css_sheet **out) {
    return css_parse_media(text, len, NULL, out);
}

css_status css_parse_media(const char *text, size_t len, const css_media *media,
                           css_sheet **out) {
    return css_parse_scoped(text, len, media, NULL, out);
}

css_status css_parse_scoped(const char *text, size_t len, const css_media *media,
                            const char *root_scope, css_sheet **out) {
    return css_parse_logged(text, len, media, root_scope, out, NULL);
}

css_status css_parse_logged(const char *text, size_t len, const css_media *media,
                            const char *root_scope, css_sheet **out,
                            css_drop_log *log) {
    if (out == NULL) return CSS_ERR_NULL_ARG;
    if (log != NULL) { log->n = 0; log->total = 0; }
    css_sheet *sh = (css_sheet *)calloc(1, sizeof *sh);
    if (sh == NULL) return CSS_ERR_OOM;
    css_media def = { 0, 0, CSS_MEDIA_DEFAULT_WIDTH };  /* screen / light / desktop */
    const css_media *m = (media != NULL) ? media : &def;

    /* Allocate initial dynamic arrays. Start small; add_rule doubles on demand.
     * Leak-safe: if any alloc fails, css_free releases whatever was allocated. */
    /* V-002: calloc, not malloc. A property emitter writes only the fields its
     * property has -- `emil`, the font-relative coefficient, is written by the
     * LENGTH emitters alone -- so an unzeroed slot hands a non-length
     * declaration a coefficient made of whatever the allocator returned, and
     * the cascade then scales it by the element's font-size. Measured: a page
     * whose only rule was `font-size:32px` came out 158px tall instead of 45,
     * because P_FONT_SIZE picked up a coefficient off a recycled text buffer. */
    sh->decls = (css_decl *)calloc(CSS_INIT_DECLS, sizeof(css_decl));
    sh->decls_cap = sh->decls ? CSS_INIT_DECLS : 0;
    sh->rules = (css_rule *)malloc(CSS_INIT_RULES * sizeof(css_rule));
    sh->rules_cap = sh->rules ? CSS_INIT_RULES : 0;
    sh->sels = (css_sel *)malloc(CSS_INIT_SELS * sizeof(css_sel));
    sh->sels_cap = sh->sels ? CSS_INIT_SELS : 0;

    if (text != NULL) {
        if (len == 0) len = strlen(text);
        size_t clen = 0;
        char *clean = strip_comments(text, len, &clen);
        if (clean == NULL) { css_free(sh); return CSS_ERR_OOM; }
        collect_custom_props_scoped(clean, 0, clen, m, root_scope,
                                    sh->custom, CSS_MAX_CUSTOM_PROPS, &sh->ncustom, 0);
        parse_block(sh, clean, 0, clen, m, 0, log);

        /* Second pass, only when the sheet redefines the root font-size: `rem` is
         * the ROOT em, so `html{font-size:62.5%}` makes 1rem 10px and not 16px.
         * The size is read back through the real cascade, so specificity,
         * !important, document order and @media gating all apply with no second
         * selector engine to keep in sync. A sheet that leaves the root alone never
         * reaches the rebase, so the default path is byte-identical. */
        double rem_px = sheet_root_font_px(sh);
        if (rem_px != 16.0) {
            size_t rlen = 0;
            char *rebased = rem_rebase(clean, clen, rem_px, &rlen);
            if (rebased != NULL) {
                /* The rebase re-parses the whole sheet, so the first pass's drops
                 * are about text that no longer exists: restart the log rather than
                 * double-count. `total` is reset with it -- a report that counted
                 * both passes would claim twice the real number. */
                if (log != NULL) { log->n = 0; log->total = 0; }
                sheet_reparse(sh, rebased, rlen, m, root_scope, log);
                /* The rebase must be a FIXED POINT. If rewriting the sheet also
                 * moved the root size, the root declared its own font-size in rem
                 * -- where the spec says rem means the INITIAL 16px, not the value
                 * being defined -- so the rewrite fed on itself. Abstain and
                 * restore the unrebased parse rather than compound the error. */
                if (sheet_root_font_px(sh) != rem_px) {
                    if (log != NULL) { log->n = 0; log->total = 0; }
                    sheet_reparse(sh, clean, clen, m, root_scope, log);
                }
                free(rebased);
            }
        }
        free(clean);
    }
    *out = sh;
    return CSS_OK;
}

void css_free(css_sheet *s) {
    if (s == NULL) return;
    free(s->decls);
    free(s->rules);
    free(s->sels);
    free(s);
}


/* Applies one declaration to the running style if it wins its property slot. The
 * cascade is two-tiered: an !important declaration beats any non-important one
 * (regardless of specificity); within a tier the higher specificity wins, ties
 * broken by document order. wi/ws/wo track the winning tier/specificity/order so far. */
static void apply_decl(css_style *o, int *wi, int *ws, int *wo, int *wem, int *wv,
                        const css_decl *d,
                        int spec, int ord, const char (*urltab)[CSS_URL_MAX],
                        const char (*contenttab)[CSS_URL_MAX], int pseudo_kind) {
    /* CSS 2.1 §12.1: a ::before/::after rule styles the GENERATED box, never the
     * element it originates from. Only `content` crosses over, because that is how
     * the generated text reaches page_view (which materialises it as a synthetic
     * run); the pseudo's own geometry has no box of its own here yet.
     *
     * Letting the rest through handed the originating element the pseudo's layout.
     * Wikipedia's
     *   figure[typeof~='mw:File/Thumb'] > figcaption::before{content:'';width:15px;float:right}
     * gave the whole <figcaption> a 15px width cap -- the article's image captions
     * came out as 131 one-character lines in a column at the page edge.
     *
     * Rejected BEFORE the cascade slots are claimed: a pseudo rule that took the slot
     * and then declined to write would block a later real rule for the same property,
     * turning a visible leak into a silent drop. Fails closed either way -- an
     * unrepresentable pseudo box paints nothing rather than corrupting a real one. */
    if ((pseudo_kind == PSEUDO_BEFORE || pseudo_kind == PSEUDO_AFTER)
        && d->prop != P_CONTENT) {
        return;
    }
    int slot = d->prop;
    int imp = d->important;
    int win = imp > wi[slot] ||
              (imp == wi[slot] && (spec > ws[slot] || (spec == ws[slot] && ord >= wo[slot])));
    if (win) {
        wi[slot] = imp;
        ws[slot] = spec;
        wo[slot] = ord;
        /* A CSS-wide keyword WINS the slot and writes nothing (CSS Cascade 5
         * section 7.3). Leaving the field at the style's unset default is what
         * gives the keyword its meaning without a second slot->field switch that
         * would go stale: the caller's ancestor merge fills an unset inherited
         * property from the parent (`inherit`), and an unset non-inherited one
         * stands at its initial value (`initial`/`unset`/`revert`).
         *
         * The winner bookkeeping above is the whole point -- it is what stops a
         * lower-specificity rule from writing the slot afterwards. The font-relative
         * and value caches are cleared so the font-size fold cannot re-apply a
         * coefficient belonging to the declaration this one just beat. */
        if (d->wide) {
            if (wem != NULL) wem[slot] = 0;
            if (wv  != NULL) wv[slot]  = CSS_LEN_UNSET;
            /* wide == 1 cannot write: the generic tail claims slots for properties
             * whose unset default it does not know. wide == 2 comes from an emitter
             * that does know it and carries it in ival, so it falls through to the
             * switch and actually clears the field -- without that, the claim wins
             * the slot but leaves an earlier lower-specificity value in place. */
            if (d->wide == 1) return;
        }
        /* Remember the winner's font-relative coefficient so the fold below can
         * find it without a second slot->field mapping. wem may be NULL for
         * callers that do not fold (css_parse_inline, which has no element and
         * therefore no computed font-size). */
        if (wem != NULL) wem[slot] = d->emil;
        if (wv  != NULL) wv[slot]  = d->ival;
        switch (d->prop) {
            case P_COLOR:    o->color = d->ival; break;
            case P_SVG_FILL: o->svg_fill = d->ival; break;
            case P_BG:       o->background = d->ival; break;
            case P_BG_ALPHA: o->bg_alpha = d->ival; break;
            case P_BG_GRAD_ANGLE: o->bg_grad_angle = d->ival; break;
            case P_BG_GRAD_N:     o->bg_grad_n = d->ival; break;
            case P_BG_GRAD_RADIAL: o->bg_grad_radial = d->ival; break;
            case P_BG_GRAD_C0: case P_BG_GRAD_C1:
            case P_BG_GRAD_C2: case P_BG_GRAD_C3:
                o->bg_grad_c[d->prop - P_BG_GRAD_C0] = d->ival; break;
            case P_BG_GRAD_POS0: case P_BG_GRAD_POS1:
            case P_BG_GRAD_POS2: case P_BG_GRAD_POS3:
                o->bg_grad_pos[d->prop - P_BG_GRAD_POS0] = d->ival; break;
            case P_BG_IMAGE_URL:
                if (d->ival < 0) {
                    o->bg_image_url[0] = '\0';
                } else {
                    memcpy(o->bg_image_url, urltab[d->ival], CSS_URL_MAX);
                    o->bg_image_url[CSS_URL_MAX - 1] = '\0';
                }
                break;
            case P_BG_IMAGE_URL2:
                if (d->ival < 0) {
                    o->bg_image_url2[0] = '\0';
                } else {
                    memcpy(o->bg_image_url2, urltab[d->ival], CSS_URL_MAX);
                    o->bg_image_url2[CSS_URL_MAX - 1] = '\0';
                }
                break;
            case P_ALIGN:    o->text_align = (css_align)d->ival; break;
            case P_FONTSIZE: o->font_scale = d->ival; break;
            case P_FONTABS:  o->font_abs = d->ival; break;
            case P_LINEHEIGHT: o->line_scale = d->ival; break;
            case P_WEIGHT:   o->bold = d->ival; break;
            case P_STYLE:    o->italic = d->ival; break;
            case P_TEXTDECO:       o->text_decoration = d->ival; break;
            case P_TEXTDECO_COLOR: o->text_decoration_color = d->ival; break;
            case P_TEXTDECO_STYLE: o->text_decoration_style = d->ival; break;
            case P_DISPLAY:  o->display = (css_display)d->ival; break;
            case P_GAP:      o->gap = d->ival; break;
            case P_JUSTIFY:  o->justify = (css_justify)d->ival; break;
            case P_GRIDCOLS: o->grid_cols = d->ival; break;
            case P_GRID_TRACK0: case P_GRID_TRACK1: case P_GRID_TRACK2:
            case P_GRID_TRACK3: case P_GRID_TRACK4: case P_GRID_TRACK5:
            case P_GRID_TRACK6: case P_GRID_TRACK7:
                o->grid_col_w[d->prop - P_GRID_TRACK0] = d->ival; break;
            case P_MARGIN_TOP:    o->margin_top = d->ival; break;
            case P_MARGIN_RIGHT:  o->margin_right = d->ival; break;
            case P_MARGIN_BOTTOM: o->margin_bottom = d->ival; break;
            case P_MARGIN_LEFT:   o->margin_left = d->ival; break;
            case P_PAD_TOP:    o->pad_top = d->ival; break;
            case P_PAD_RIGHT:  o->pad_right = d->ival; break;
            case P_PAD_BOTTOM: o->pad_bottom = d->ival; break;
            case P_PAD_LEFT:   o->pad_left = d->ival; break;
            case P_WIDTH:      o->width = d->ival; break;
            case P_MAXWIDTH:   o->max_width = d->ival; break;

            case P_MINWIDTH:   o->min_width = d->ival; break;
            case P_HEIGHT:     o->height = d->ival; break;
            case P_MINHEIGHT:  o->min_height = d->ival; break;
            case P_MAXHEIGHT:  o->max_height = d->ival; break;
            case P_FONTFAMILY:    o->font_family = d->ival; break;
            case P_TEXTTRANSFORM: o->text_transform = d->ival; break;
            case P_LETTERSPACING: o->letter_spacing = d->ival; break;
            case P_WORDSPACING:   o->word_spacing = d->ival; break;
            case P_SHADOW_DX:     o->shadow_dx = d->ival; break;
            case P_SHADOW_DY:     o->shadow_dy = d->ival; break;
            case P_SHADOW_COLOR:  o->shadow_color = d->ival; break;
            case P_OPACITY:       o->opacity = d->ival; break;
            case P_VALIGN:        o->valign = d->ival; break;
            case P_TEXTINDENT:    o->text_indent = d->ival; break;
            case P_WHITESPACE:    o->white_space = d->ival; break;
            case P_TABSIZE:       o->tab_size = d->ival; break;
            case P_LISTSTYLE:     o->list_style = d->ival; break;
            case P_DIRECTION:     o->direction = d->ival; break;
            case P_POSITION:      o->position = d->ival; break;
            case P_INSET_TOP:     o->inset_top = d->ival; break;
            case P_INSET_RIGHT:   o->inset_right = d->ival; break;
            case P_INSET_BOTTOM:  o->inset_bottom = d->ival; break;
            case P_INSET_LEFT:    o->inset_left = d->ival; break;
            case P_ZINDEX:        o->z_index = d->ival; break;
            case P_BOXSIZING:     o->box_sizing = d->ival; break;
            case P_BW_TOP:        o->border_top_width = d->ival; break;
            case P_BW_RIGHT:      o->border_right_width = d->ival; break;
            case P_BW_BOTTOM:     o->border_bottom_width = d->ival; break;
            case P_BW_LEFT:       o->border_left_width = d->ival; break;
            case P_BS_TOP:        o->border_top_style = d->ival; break;
            case P_BS_RIGHT:      o->border_right_style = d->ival; break;
            case P_BS_BOTTOM:     o->border_bottom_style = d->ival; break;
            case P_BS_LEFT:       o->border_left_style = d->ival; break;
            case P_BC_TOP:        o->border_top_color = d->ival; break;
            case P_BC_RIGHT:      o->border_right_color = d->ival; break;
            case P_BC_BOTTOM:     o->border_bottom_color = d->ival; break;
            case P_BC_LEFT:       o->border_left_color = d->ival; break;
            case P_BORDER_RADIUS: o->border_radius = d->ival; break;
            case P_RADIUS_TR:     o->border_radius_tr = d->ival; break;
            case P_RADIUS_BR:     o->border_radius_br = d->ival; break;
            case P_RADIUS_BL:     o->border_radius_bl = d->ival; break;
            case P_BSHADOW_DX:     o->shadow2_dx = d->ival; break;
            case P_BSHADOW_DY:     o->shadow2_dy = d->ival; break;
            case P_BSHADOW_BLUR:   o->shadow2_blur = d->ival; break;
            case P_BSHADOW_SPREAD: o->shadow2_spread = d->ival; break;
            case P_BSHADOW_COLOR:  o->box_shadow_color = d->ival; break;
            case P_BSHADOW_INSET:  o->box_shadow_inset = d->ival; break;
            case P_OUTLINE_W:     o->outline_width = d->ival; break;
            case P_OUTLINE_S:     o->outline_style = d->ival; break;
            case P_OUTLINE_C:     o->outline_color = d->ival; break;
            case P_OUTLINE_OFFSET: o->outline_offset = d->ival; break;
            case P_FLEX_GROW:     o->flex_grow = d->ival; break;
            case P_FLEX_SHRINK:   o->flex_shrink = d->ival; break;
            case P_FLEX_BASIS:    o->flex_basis = d->ival; break;
            case P_ORDER:         o->order = d->ival; break;
            case P_ALIGN_ITEMS:   o->align_items = d->ival; break;
            case P_ALIGN_SELF:    o->align_self = d->ival; break;
            case P_ALIGN_CONTENT: o->align_content = d->ival; break;
            case P_JUSTIFY_ITEMS: o->justify_items = d->ival; break;
            case P_FLEX_DIR:      o->flex_direction = d->ival; break;
            case P_FLEX_WRAP:     o->flex_wrap = d->ival; break;
            case P_GRID_ROWS:     o->grid_rows = d->ival; break;
            case P_ROW_GAP:       o->row_gap = d->ival; break;
            case P_GRID_FLOW:     o->grid_auto_flow = d->ival; break;
            case P_GRID_COL_SPAN: o->grid_col_span = d->ival; break;
            case P_GRID_ROW_SPAN: o->grid_row_span = d->ival; break;
            case P_FLOAT:         o->float_side = d->ival; break;
            case P_CLEAR:         o->clear = d->ival; break;
            case P_VISIBILITY:    o->visibility = d->ival; break;
            case P_OVERFLOW_X:    o->overflow_x = d->ival; break;
            case P_OVERFLOW_Y:    o->overflow_y = d->ival; break;
            case P_CURSOR:        o->cursor = d->ival; break;
            case P_TEXT_OVERFLOW:   o->text_overflow = d->ival; break;
            case P_WORD_BREAK:      o->word_break = d->ival; break;
            case P_BORDER_COLLAPSE: o->border_collapse = d->ival; break;
            case P_BORDER_SPACING:  o->border_spacing = d->ival; break;
            case P_EMPTY_CELLS:     o->empty_cells = d->ival; break;
            case P_CAPTION_SIDE:    o->caption_side = d->ival; break;
            case P_TABLE_LAYOUT:    o->table_layout = d->ival; break;
            case P_FONT_VARIANT:    o->font_variant = d->ival; break;
            case P_HYPHENS:         o->hyphens = d->ival; break;
            case P_USER_SELECT:     o->user_select = d->ival; break;
            case P_CARET_COLOR:     o->caret_color = d->ival; break;
            case P_APPEARANCE:      o->appearance = d->ival; break;
            case P_POINTER_EVENTS:      o->pointer_events = d->ival; break;
            case P_BG_REPEAT:           o->bg_repeat = d->ival; break;
            case P_BG_SIZE:             o->bg_size = d->ival; break;
            case P_BG_CLIP:             o->bg_clip = d->ival; break;
            case P_TEXT_FILL:           o->text_fill_color = d->ival; break;
            case P_BG_ORIGIN:           o->bg_origin = d->ival; break;
            case P_BG_ATTACHMENT:       o->bg_attachment = d->ival; break;
            case P_ISOLATION:           o->isolation = d->ival; break;
            case P_CONTAIN:             o->contain = d->ival; break;
            case P_CONTENT_VISIBILITY:  o->content_visibility = d->ival; break;
            case P_IMAGE_RENDERING:     o->image_rendering = d->ival; break;
            case P_COLOR_SCHEME:        o->color_scheme = d->ival; break;
            case P_ACCENT_COLOR:        o->accent_color = d->ival; break;
            case P_PRINT_COLOR_ADJUST:  o->print_color_adjust = d->ival; break;
            case P_FORCED_COLOR_ADJUST: o->forced_color_adjust = d->ival; break;
            case P_MIX_BLEND_MODE:      o->mix_blend_mode = d->ival; break;
            case P_TRANSFORM_TX:        o->transform_tx = d->ival; break;
            case P_TRANSFORM_TY:        o->transform_ty = d->ival; break;
            case P_TRANSFORM_SX:        o->transform_sx = d->ival; break;
            case P_TRANSFORM_SY:        o->transform_sy = d->ival; break;
            case P_TRANSFORM_ROTATE:    o->transform_rotate = d->ival; break;
            case P_TRANSFORM_SKX:       o->transform_skx = d->ival; break;
            case P_TRANSFORM_SKY:       o->transform_sky = d->ival; break;
            case P_TRANSFORM_OX:        o->transform_ox = d->ival; break;
            case P_TRANSFORM_OY:        o->transform_oy = d->ival; break;
            case P_OBJECT_FIT:          o->object_fit = d->ival; break;
            case P_LIST_STYLE_POS:      o->list_style_pos = d->ival; break;
            case P_FONT_KERNING:        o->font_kerning = d->ival; break;
            case P_TEXT_RENDERING:      o->text_rendering = d->ival; break;
            case P_FONT_STRETCH:        o->font_stretch = d->ival; break;
            case P_RESIZE:              o->resize = d->ival; break;
            case P_SCROLL_BEHAVIOR:     o->scroll_behavior = d->ival; break;
            case P_TOUCH_ACTION:        o->touch_action = d->ival; break;
            case P_OVERSCROLL_BEHAVIOR: o->overscroll_behavior = d->ival; break;
            case P_BACKFACE_VISIBILITY: o->backface_visibility = d->ival; break;
            case P_TEXTDECO_THICKNESS:  o->text_decoration_thickness = d->ival; break;
            case P_ASPECT_NUM:          o->aspect_num = d->ival; break;
            case P_ASPECT_DEN:          o->aspect_den = d->ival; break;
            case P_ANIM_DURATION:       o->anim_duration_ms = d->ival; break;
            case P_ANIM_NAME: {
                /* Decode first-char + length from ival. Store the first
                 * character; the full name is recovered later in
                 * resolve_anim_keyframes by matching against sheet->keyframes[]. */
                char fc = (char)(d->ival & 0xff);
                int nlen = (d->ival >> 8) & 0xff;
                if (fc != '\0' && nlen > 0) {
                    o->anim_name[0] = fc;
                    o->anim_name[1] = '\0';
                } else {
                    o->anim_name[0] = '\0';
                }
                break;
            }
            case P_ANIM_ITERS:          o->anim_iterations = d->ival; break;
            case P_ANIM_DIR:            o->anim_direction = d->ival; break;
            case P_ANIM_FILL:           o->anim_fill_mode = d->ival; break;
            case P_ANIM_TIMING:         o->anim_timing = d->ival; break;
            case P_ANIM_DELAY:          o->anim_delay_ms = d->ival; break;
            case P_TRANSITION_DURATION: o->transition_duration_ms = d->ival; break;
            case P_TRANSITION_PROPERTY: o->transition_property = d->ival; break;
            case P_TRANSITION_TIMING:   o->transition_timing = d->ival; break;
            case P_TRANSITION_DELAY:    o->transition_delay_ms = d->ival; break;
            case P_FILTER_BLUR:         o->filter_blur = d->ival; break;
            case P_FILTER_GRAYSCALE:    o->filter_grayscale = d->ival; break;
            case P_FILTER_BRIGHTNESS:   o->filter_brightness = d->ival; break;
            case P_FILTER_CONTRAST:     o->filter_contrast = d->ival; break;
            case P_FILTER_SEPIA:        o->filter_sepia = d->ival; break;
            case P_FILTER_INVERT:       o->filter_invert = d->ival; break;
            case P_FILTER_SATURATE:     o->filter_saturate = d->ival; break;
            case P_FILTER_HUE_ROTATE:   o->filter_hue_rotate = d->ival; break;
            case P_FILTER_DROP_DX:      o->filter_drop_dx = d->ival; break;
            case P_FILTER_DROP_DY:      o->filter_drop_dy = d->ival; break;
            case P_FILTER_DROP_BLUR:    o->filter_drop_blur = d->ival; break;
            case P_FILTER_DROP_COLOR:   o->filter_drop_color = d->ival; break;
            case P_BACKDROP_BLUR:       o->backdrop_blur = d->ival; break;
            case P_BG_POS_X:            o->bg_pos_x = d->ival; break;
            case P_BG_POS_Y:            o->bg_pos_y = d->ival; break;
            case P_CLIP_TOP:            o->clip_top = d->ival; break;
            case P_CLIP_RIGHT:          o->clip_right = d->ival; break;
            case P_CLIP_BOTTOM:         o->clip_bottom = d->ival; break;
            case P_CLIP_LEFT:           o->clip_left = d->ival; break;
            case P_CONTENT:
                if (d->ival < 0) {
                    o->content_str[0] = '\0';
                } else if (contenttab != NULL) {
                    if (pseudo_kind == PSEUDO_BEFORE) {
                        memcpy(o->content_before_str, contenttab[d->ival], CSS_URL_MAX);
                        o->content_before_str[CSS_URL_MAX - 1] = '\0';
                        memcpy(o->content_str, contenttab[d->ival], CSS_URL_MAX);
                        o->content_str[CSS_URL_MAX - 1] = '\0';
                    } else if (pseudo_kind == PSEUDO_AFTER) {
                        memcpy(o->content_after_str, contenttab[d->ival], CSS_URL_MAX);
                        o->content_after_str[CSS_URL_MAX - 1] = '\0';
                    } else {
                        memcpy(o->content_str, contenttab[d->ival], CSS_URL_MAX);
                        o->content_str[CSS_URL_MAX - 1] = '\0';
                    }
                }
                break;
            case P_LINE_CLAMP:   o->line_clamp = d->ival; break;
            /* Named grid placement (2026-08-14). The template rides the same string
             * pool as P_CONTENT; ival < 0 is the explicit `none` reset. */
            case P_GRID_AREAS:
                if (d->ival < 0 || contenttab == NULL) {
                    o->grid_areas[0] = '\0';
                } else {
                    size_t gl = strlen(contenttab[d->ival]);
                    if (gl >= CSS_GRID_AREAS_MAX) gl = CSS_GRID_AREAS_MAX - 1;
                    memcpy(o->grid_areas, contenttab[d->ival], gl);
                    o->grid_areas[gl] = '\0';
                }
                break;
            case P_GRID_AREA_NAME: o->grid_area_name = (unsigned)d->ival; break;
            case P_COLUMN_COUNT: o->column_count = d->ival; break;
            case P_COLUMN_WIDTH: o->column_width = d->ival; break;
            case P_COLUMN_FILL:  o->column_fill = d->ival; break;
            case P_COLUMN_SPAN:  o->column_span = d->ival; break;
            case P_COLRULE_W:    o->column_rule_width = d->ival; break;
            case P_COLRULE_S:    o->column_rule_style = d->ival; break;
            case P_COLRULE_C:    o->column_rule_color = d->ival; break;
            case P_BG_SIZE_W:    o->bg_size_w = d->ival; break;
            case P_BG_SIZE_H:    o->bg_size_h = d->ival; break;
            case P_VALIGN_SHIFT: o->valign_shift = d->ival; break;
            default:
                /* The percentage half of every <length-percentage> property:
                 * one contiguous slot block mirroring css_pct_slot, so a new
                 * percentage-capable property needs no case of its own here. */
                if (d->prop >= P_PCT_FIRST && d->prop <= P_PCT_LAST)
                    o->pct[d->prop - P_PCT_FIRST] = d->ival;
                break;
        }
    }
}

/*
 * This element's computed font-size in px: the cascade result applied to the
 * inherited value (CSS Fonts 4.4, CSS 2.1 15.7).
 *
 * font_scale is a percentage and font_abs says what of -- an ABSOLUTE size
 * (px/pt/rem/keyword) is a percentage of the CSS initial size, a RELATIVE one
 * (em/%/smaller/larger) a percentage of the INHERITED size. font_scale == 0
 * means the element declared no font-size at all, so it inherits unchanged.
 */
double css_computed_font_size(const css_style *o, double inherited_px) {
    if (o == NULL) return (inherited_px > 0.0) ? inherited_px : CL_INITIAL_FONT_SIZE;
    if (!(inherited_px > 0.0)) inherited_px = CL_INITIAL_FONT_SIZE;
    if (o->font_scale == 0) return inherited_px;
    double base = o->font_abs ? CL_INITIAL_FONT_SIZE : inherited_px;
    double fs = base * (double)o->font_scale / 100.0;
    if (!isfinite(fs) || fs <= 0.0) return inherited_px;
    if (fs > (double)CSS_FONT_SIZE_MAX) fs = (double)CSS_FONT_SIZE_MAX;
    return fs;
}

static double computed_font_size(const css_style *o, const css_element *el) {
    return css_computed_font_size(o, (el != NULL) ? el->font_size : 0.0);
}

/*
 * Folds every font-relative length in the resolved style against this element's
 * computed font-size. This is the ONE place a font-relative length becomes
 * pixels, the way bx_lp_px is the one place a percentage does
 * (spec/css_length.md section 8.5).
 *
 * The correction is applied by re-running apply_decl with the winning
 * declaration's OWN specificity and order -- the cascade's test is
 * `ord >= wo[slot]`, so re-applying wins -- instead of a parallel slot->field
 * switch. A second mapping would be duplicated knowledge that goes stale the
 * next time a length property is added; this way a new property is folded as
 * soon as its emitter records a coefficient, with no edit here at all.
 *
 * Inert when the element computes to the initial font-size, which is what makes
 * the whole mechanism provably a no-op on a page that never restyles text.
 */
static void fold_font_relative(css_style *o, int *wi, int *ws, int *wo,
                               const int *wem, const int *wv,
                               const css_element *el,
                               const char (*urltab)[CSS_URL_MAX],
                               const char (*contenttab)[CSS_URL_MAX]) {
    double fs = computed_font_size(o, el);
    if (!isfinite(fs) || fs <= 0.0 || fs == CL_INITIAL_FONT_SIZE) return;

    for (int slot = 0; slot < P_NSLOTS; ++slot) {
        if (wem[slot] == 0) continue;
        /* CSS_LEN_AUTO/UNSET are sentinels, not lengths: scaling them would turn
         * `width:auto` into a number. The emitter already refuses to record a
         * coefficient for auto; this is the belt to that braces. */
        if (wv[slot] == CSS_LEN_AUTO || wv[slot] == CSS_LEN_UNSET) continue;

        double px = cl_em_refit((double)wv[slot], (double)wem[slot] / 1000.0,
                                CL_INITIAL_FONT_SIZE, fs);
        css_decl folded = {
            .prop = slot,
            .ival = css_round_clamp(px, -CSS_LEN_MAX, CSS_LEN_MAX),
            .important = wi[slot],
            .emil = 0,   /* already folded: never fold twice */
        };
        if (folded.ival == wv[slot]) continue;   /* nothing moved */
        apply_decl(o, wi, ws, wo, NULL, NULL, &folded,
                   ws[slot], wo[slot], urltab, contenttab, -1);
    }
}

css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         const char *inline_style, size_t inline_len) {
    /* Designated initializers: robust against field insertion/reordering (every
     * "unset" sentinel is named, so a new field cannot silently default to 0). */
    css_style out = {
        .color = -1, .svg_fill = -1, .background = -1, .bg_alpha = CSS_LEN_UNSET, .text_align = CSS_ALIGN_UNSET,
        .font_scale = 0, .font_abs = 0, .line_scale = 0, .text_decoration = -1, .text_decoration_color = -1,
        .text_decoration_style = CSS_TDS_UNSET,
        .bold = -1, .italic = -1, .display = CSS_DISP_UNSET,
        .gap = -1, .justify = CSS_JUSTIFY_UNSET, .grid_cols = 0,
        .grid_col_w = { 0 },
        .grid_areas = { 0 }, .grid_area_name = 0u,
        .margin_top = CSS_LEN_UNSET, .margin_right = CSS_LEN_UNSET,
        .margin_bottom = CSS_LEN_UNSET, .margin_left = CSS_LEN_UNSET,
        .pad_top = CSS_LEN_UNSET, .pad_right = CSS_LEN_UNSET,
        .pad_bottom = CSS_LEN_UNSET, .pad_left = CSS_LEN_UNSET,
        .width = CSS_LEN_UNSET, .max_width = CSS_LEN_UNSET,
        .min_width = CSS_LEN_UNSET, .height = CSS_LEN_UNSET,
        .min_height = CSS_LEN_UNSET, .max_height = CSS_LEN_UNSET,
        .font_family = CSS_FF_UNSET, .text_transform = CSS_TT_UNSET,
        .letter_spacing = CSS_LEN_UNSET, .word_spacing = CSS_LEN_UNSET,
        .shadow_dx = 0, .shadow_dy = 0, .shadow_color = -1,
        .opacity = -1, .valign = CSS_VA_UNSET, .valign_shift = CSS_LEN_UNSET,
        .text_indent = CSS_LEN_UNSET, .white_space = CSS_WS_UNSET,
        .tab_size = 0,
        .list_style = CSS_LS_UNSET,
        .direction = CSS_DIR_UNSET,
        .position = CSS_POS_UNSET,
        .inset_top = CSS_LEN_UNSET, .inset_right = CSS_LEN_UNSET,
        .inset_bottom = CSS_LEN_UNSET, .inset_left = CSS_LEN_UNSET,
        .z_index = CSS_LEN_UNSET, .box_sizing = CSS_BOXS_UNSET,
        .border_top_width = CSS_LEN_UNSET, .border_right_width = CSS_LEN_UNSET,
        .border_bottom_width = CSS_LEN_UNSET, .border_left_width = CSS_LEN_UNSET,
        .border_top_style = CSS_BST_UNSET, .border_right_style = CSS_BST_UNSET,
        .border_bottom_style = CSS_BST_UNSET, .border_left_style = CSS_BST_UNSET,
        .border_top_color = -1, .border_right_color = -1,
        .border_bottom_color = -1, .border_left_color = -1,
        .border_radius = CSS_LEN_UNSET, .border_radius_tr = CSS_LEN_UNSET,
        .border_radius_br = CSS_LEN_UNSET, .border_radius_bl = CSS_LEN_UNSET,
        .shadow2_dx = 0, .shadow2_dy = 0, .shadow2_blur = 0, .shadow2_spread = 0,
        .box_shadow_color = -1, .box_shadow_inset = -1,
        .outline_width = CSS_LEN_UNSET, .outline_style = CSS_BST_UNSET,
        .outline_color = -1, .outline_offset = CSS_LEN_UNSET,
        .flex_grow = -1, .flex_shrink = -1, .flex_basis = CSS_LEN_UNSET,
        .order = CSS_LEN_UNSET,
        .align_items = CSS_AK_UNSET, .align_self = CSS_AK_UNSET,
        .align_content = CSS_AK_UNSET, .justify_items = CSS_AK_UNSET,
        .flex_direction = CSS_FD_UNSET, .flex_wrap = CSS_FW_UNSET,
        .grid_rows = 0, .row_gap = -1, .grid_auto_flow = CSS_GF_UNSET,
        .grid_col_span = 0, .grid_row_span = 0,
        .float_side = CSS_FLOAT_UNSET, .clear = CSS_CLEAR_UNSET,
        .visibility = CSS_VIS_UNSET,
        .overflow_x = CSS_OF_UNSET, .overflow_y = CSS_OF_UNSET,
        .cursor = CSS_CUR_UNSET,
        .text_overflow = CSS_TO_UNSET, .word_break = CSS_WB_UNSET,
        .border_collapse = CSS_BCOL_UNSET, .border_spacing = CSS_LEN_UNSET,
        .empty_cells = CSS_EC_UNSET, .caption_side = CSS_CS_UNSET,
        .table_layout = CSS_TL_UNSET,
        .font_variant = CSS_FV_UNSET,
        .hyphens = CSS_HY_UNSET, .user_select = CSS_US_UNSET,
        .caret_color = -1,
        .appearance = CSS_AP_UNSET, .pointer_events = CSS_PE_UNSET,
        .bg_repeat = CSS_BGR_UNSET, .bg_size = CSS_BGS_UNSET,
        .bg_size_w = CSS_LEN_UNSET, .bg_size_h = CSS_LEN_UNSET,
        .bg_clip = CSS_BGC_UNSET, .bg_origin = CSS_BGO_UNSET,
        .bg_attachment = CSS_BGA_UNSET,
        .isolation = CSS_ISO_UNSET, .contain = 0,
        .content_visibility = CSS_CV_UNSET,
        .image_rendering = CSS_IR_UNSET,
        .color_scheme = CSS_CSH_UNSET, .accent_color = -1,
        .print_color_adjust = CSS_PCA_UNSET,
        .forced_color_adjust = CSS_FCA_UNSET,
        .mix_blend_mode = CSS_MB_UNSET, .object_fit = CSS_OFI_UNSET,
        .list_style_pos = CSS_LP_UNSET,
        .font_kerning = CSS_FK_UNSET, .text_rendering = CSS_TR_UNSET,
        .font_stretch = CSS_FS_UNSET,
        .resize = CSS_RS_UNSET, .scroll_behavior = CSS_SB_UNSET,
        .touch_action = CSS_TA_UNSET, .overscroll_behavior = CSS_OS_UNSET,
        .backface_visibility = CSS_BF_UNSET,
        .text_decoration_thickness = -1,
        .aspect_num = 0, .aspect_den = 0,
        .bg_grad_n = 0, .bg_grad_angle = 180, .bg_grad_radial = 0,
        .bg_grad_c = { -1, -1, -1, -1 },
        .bg_grad_pos = { -1, -1, -1, -1 },
        .transform_tx = CSS_LEN_UNSET, .transform_ty = CSS_LEN_UNSET,
        .transform_sx = CSS_LEN_UNSET, .transform_sy = CSS_LEN_UNSET,
        .transform_rotate = CSS_LEN_UNSET,
        .transform_skx = CSS_LEN_UNSET, .transform_sky = CSS_LEN_UNSET,
        .transform_ox = CSS_LEN_UNSET, .transform_oy = CSS_LEN_UNSET,
        .anim_duration_ms = 0,
        .anim_nkf = 0,
        .anim_kf_pct = { 0 },
        .anim_kf_val = { 0 },
        .anim_kf_bg = { 0 },
        .anim_kf_fg = { 0 },
        .filter_blur = 0, .filter_grayscale = 0, .backdrop_blur = 0,
        .filter_drop_dx = 0, .filter_drop_dy = 0, .filter_drop_blur = 0,
        .filter_drop_color = -1,
        .text_fill_color = -1,
        .bg_pos_x = CSS_LEN_UNSET, .bg_pos_y = CSS_LEN_UNSET,
        .clip_top = CSS_LEN_UNSET, .clip_right = CSS_LEN_UNSET,
        .clip_bottom = CSS_LEN_UNSET, .clip_left = CSS_LEN_UNSET,
        /* Multi-column: 0 is `auto` for both count and width, which is the CSS
         * initial value and means "not a multi-column container". */
        .line_clamp = 0,
        .column_count = 0, .column_width = 0,
        .column_fill = CSS_CF_UNSET, .column_span = CSS_CSP_UNSET,
        .column_rule_width = CSS_LEN_UNSET, .column_rule_style = CSS_BST_UNSET,
        .column_rule_color = -1,
        .pct = { 0 },
    };
    int wi[P_NSLOTS], ws[P_NSLOTS], wo[P_NSLOTS], wem[P_NSLOTS], wv[P_NSLOTS];
    for (int k = 0; k < P_NSLOTS; ++k) {
        wi[k] = -1; ws[k] = -1; wo[k] = -1; wem[k] = 0; wv[k] = 0;
    }

    if (sheet != NULL && el != NULL) {
        for (size_t si = 0; si < sheet->nsels; ++si) {
            const css_sel *sel = &sheet->sels[si];
            int pseudo_kind = -1;
            if (!csel_matches(sel, el, NULL, 1, &pseudo_kind)) continue;
            size_t start = sheet->rules[sel->rule].start;
            size_t cnt = sheet->rules[sel->rule].count;
            for (size_t d = 0; d < cnt; ++d)
                apply_decl(&out, wi, ws, wo, wem, wv, &sheet->decls[start + d], sel->spec, sel->order,
                           sheet->bg_urls, sheet->content_urls, pseudo_kind);
        }
    }

    if (inline_style != NULL) {
        if (inline_len == 0) inline_len = strlen(inline_style);
        /* var() in an inline style= can reference a custom property declared
         * either in this SAME inline block (`style="--x:1;color:var(--x)"`) or in
         * the stylesheet (e.g. a `:root` rule). Inline-declared names win on a
         * collision (closer to the use site), so they go first in the combined
         * table -- expand_lookup takes the first match, which also makes
         * deduplicating the sheet's entries unnecessary. Heap-allocated (the
         * table is too large for the stack); OOM degrades to sheet-only vars. */
        css_custom_prop *combined =
            (css_custom_prop *)calloc(2 * CSS_MAX_CUSTOM_PROPS, sizeof *combined);
        size_t ncombined = 0;
        if (combined != NULL) {
            collect_custom_decls(inline_style, 0, inline_len,
                                 combined, CSS_MAX_CUSTOM_PROPS, &ncombined);
            if (sheet != NULL) {
                for (size_t i = 0; i < sheet->ncustom &&
                                   ncombined < 2 * CSS_MAX_CUSTOM_PROPS; ++i)
                    combined[ncombined++] = sheet->custom[i];
            }
        }
        css_decl tmp[CSS_INLINE_DECLS] = { { 0 } };  /* V-002, as above */
        char inline_bg_urls[CSS_INLINE_BG_URLS][CSS_URL_MAX];
        size_t n_inline_bg_urls = 0;
        char inline_content_urls[CSS_INLINE_BG_URLS][CSS_URL_MAX];
        size_t n_inline_content_urls = 0;
        const css_custom_prop *vtab = combined;
        size_t nvtab = ncombined;
        if (vtab == NULL && sheet != NULL) {  /* OOM: degrade to sheet-only vars */
            vtab = sheet->custom;
            nvtab = sheet->ncustom;
        }
        size_t dn = interpret_decls(inline_style, inline_len, tmp, CSS_INLINE_DECLS,
                                    vtab, nvtab,
                                    inline_bg_urls, &n_inline_bg_urls, CSS_INLINE_BG_URLS,
                                    inline_content_urls, &n_inline_content_urls, CSS_INLINE_BG_URLS,
                                    NULL);
        for (size_t d = 0; d < dn; ++d)
            apply_decl(&out, wi, ws, wo, wem, wv, &tmp[d], CSS_INLINE_SPEC, INT_MAX,
                       inline_bg_urls, inline_content_urls, -1);
        free(combined);
    }

    fold_font_relative(&out, wi, ws, wo, wem, wv, el,
                       sheet != NULL ? sheet->bg_urls : NULL,
                       sheet != NULL ? sheet->content_urls : NULL);

    css_resolve_anim_keyframes(&out, sheet);
    return out;
}

css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                      const char *const *classes, size_t nclasses,
                      const char *inline_style, size_t inline_len) {
    /* No ancestor context: a parentless element. A complex (multi-compound) selector
     * therefore cannot match through its combinator (complex_matches needs parents).
     * No attributes are supplied, so [attr] selectors do not match via this entry
     * point (callers that need them build a css_element with attrs). */
    /* Designated and zero-based: a field added to css_element must not silently
     * shift the meaning of the ones after it (V-002 applied to view structs).
     * child_count -1 = unknown, so :empty keeps failing closed; font_size 0 =
     * unknown, so font-relative lengths keep the CSS initial context. */
    css_element el = {
        .tag = tag, .id = id, .classes = classes, .nclasses = nclasses,
        .attrs = NULL, .nattrs = 0, .parent = NULL,
        .nth = 0, .nsib = 0, .prev = NULL,
        .nth_of_type = 0, .nsib_of_type = 0,
        .child_count = -1, .dom_node = NULL, .state = 0, .font_size = 0.0,
    };
    return css_resolve_el(sheet, &el, inline_style, inline_len);
}

/* Resolve @keyframes for an animated element: scans sheet->keyframes[] for a
 * name matching anim_name[0] (first char + length from the cascade encoding).
 * If a unique match is found, copies stops into anim_kf_* fields.
 * Sheet can be NULL (inline style, no @keyframes). */
void css_resolve_anim_keyframes(css_style *s, const css_sheet *sheet) {
    if (s == NULL || sheet == NULL || s->anim_name[0] == '\0') return;
    char fc = s->anim_name[0];
    int match = -1;
    for (size_t i = 0; i < sheet->nkeyframes; ++i) {
        if (sheet->keyframes[i].name[0] == fc) {
            match = (int)i;
            break;
        }
    }
    if (match < 0) return;
    /* Copy full name and stops */
    size_t nlen = strlen(sheet->keyframes[match].name);
    if (nlen >= sizeof s->anim_name) nlen = sizeof s->anim_name - 1;
    memcpy(s->anim_name, sheet->keyframes[match].name, nlen);
    s->anim_name[nlen] = '\0';
    s->anim_nkf = sheet->keyframes[match].nstops;
    for (int k = 0; k < s->anim_nkf && k < CSS_MAX_KF_STOPS; ++k) {
        const struct css_keyframe_stop *st = &sheet->keyframes[match].stops[k];
        s->anim_kf_pct[k] = (int)(st->pct * 100.0 + 0.5);
        s->anim_kf_val[k] = st->opacity;
        s->anim_kf_bg[k]  = st->bg_color;
        s->anim_kf_fg[k]  = st->fg_color;
        s->anim_kf_tx[k]  = st->transform_tx;
        s->anim_kf_ty[k]  = st->transform_ty;
        s->anim_kf_sx[k]  = st->transform_sx;
        s->anim_kf_sy[k]  = st->transform_sy;
        s->anim_kf_rot[k] = st->transform_rotate;
    }
}

size_t css_font_face_count(const css_sheet *sheet) {
    return (sheet != NULL) ? sheet->nfont_faces : 0;
}

int css_font_face_at(const css_sheet *sheet, size_t i,
                     char *family, size_t fam_cap,
                     char *src_url, size_t url_cap) {
    if (sheet == NULL || i >= sheet->nfont_faces
        || family == NULL || src_url == NULL) return -1;
    snprintf(family, fam_cap, "%s", sheet->font_faces[i].family);
    snprintf(src_url, url_cap, "%s", sheet->font_faces[i].src_url);
    return 0;
}

css_style css_parse_inline(const char *style, size_t len) {
    return css_resolve(NULL, NULL, NULL, NULL, 0, style, len);
}
