#ifndef FREEDOM_CSS_LENGTH_H
#define FREEDOM_CSS_LENGTH_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * css_length (cl_) -- the single source of truth for resolving a CSS <length>
 * into px.
 *
 * Normative reference: CSS Values and Units Module Level 4, section 5 (distance
 * units) and section 6 (font-relative and viewport-relative lengths). Every
 * conversion factor below is a literal quote from that spec, not a heuristic:
 * 1in = 96px, 1pt = 1/72in, 1pc = 1/6in, 1cm = 1/2.54in, 1mm = 1/10cm,
 * 1Q = 1/40cm.
 *
 * This module exists because the engine used to resolve lengths in four
 * divergent private tables, each with its own hardcoded 16.0, none of which
 * agreed: the box-model resolver dropped `pt` entirely, `rem` and `em` were the
 * same number, and `vmax` was an alias of `vw`. See spec/css_length.md.
 *
 * Pure: no allocation, no I/O, no global state, no errno. Safe to call inside
 * the confined worker. Total: every input yields a cl_status, and *out_px is
 * written only on CL_OK.
 */

/* Longest value accepted. A <length> token is a number plus at most a handful
 * of ASCII unit characters; anything longer is not a length and fails closed
 * rather than being scanned. Also bounds a value that is missing its NUL. */
#define CL_MAX_TOKEN 64u

/* CSS initial value of `font-size` (the `medium` absolute-size keyword mapped
 * to px). Not a Freedom convention: it is what every UA uses as the initial
 * computed font-size, and it is the value against which a media query's `em`
 * is defined to resolve. */
#define CL_INITIAL_FONT_SIZE 16.0

/* Ratio used for `line_height` in cl_ctx_initial: `line-height: normal` is the
 * font's natural line box. The engine measures that box for real during layout
 * (see gui/bui_theme.c line_spacing) and passes it in; this is only the value
 * used when no font has been measured yet. */
#define CL_NORMAL_LINE_RATIO 1.0

/* Spec-named fallbacks for font metrics the caller has not supplied.
 * CSS Values 4:
 *   6.1.1 ex  -- "a value of 0.5em should be used" when x-height is unknown.
 *   6.1.2 ch  -- the `0` glyph "must be assumed to be 0.5em wide" when unknown.
 *   6.1.3 cap -- falls back to the font's ascent metric; 0.7em approximates the
 *                cap-height of the default serif/sans faces.
 *   6.1.4 ic  -- the CJK water ideograph "must be assumed to be 1em" when
 *                unknown.
 * These are ratios of the element's font-size, never absolute px. */
#define CL_FALLBACK_EX_RATIO   0.5
#define CL_FALLBACK_CH_RATIO   0.5
#define CL_FALLBACK_CAP_RATIO  0.7
#define CL_FALLBACK_IC_RATIO   1.0

typedef enum cl_status {
    CL_OK = 0,
    CL_ERR_NULL_ARG,  /* a required pointer argument was NULL */
    CL_ERR_SYNTAX,    /* not a CSS <number>, or trailing junk after the unit */
    CL_ERR_UNIT,      /* syntactically fine, but the unit is not a <length> */
    CL_ERR_RANGE      /* the result is not finite (overflow, inf, nan) */
} cl_status;

/*
 * The state a <length> is measured against. A CSS length is a number PLUS its
 * context; making that context an explicit argument is what keeps the
 * conversion factors out of the call sites.
 *
 * Anti-fingerprinting doctrine: viewport_w/viewport_h default to the NORMALIZED
 * desktop (CSS_MEDIA_DEFAULT_WIDTH/HEIGHT), never the real window. A computed
 * length must never leak real window geometry to hostile content. Only @media
 * width queries see the render width.
 *
 * The four font-metric fields are <= 0 until a font has actually been measured,
 * in which case the spec-named fallbacks above apply. They exist so text_shape
 * (trusted side, local fonts) can supply real metrics later without this module
 * changing at all.
 */
typedef struct cl_ctx {
    double font_size;            /* computed font-size of the element (px) */
    double root_font_size;       /* computed font-size of the root element (px) */
    double line_height;          /* used line-height of the element (px) */
    double root_line_height;     /* used line-height of the root element (px) */
    double viewport_w;           /* normalized viewport width (px) */
    double viewport_h;           /* normalized viewport height (px) */
    double x_height;             /* font x-height (px); <= 0 -> spec fallback */
    double zero_advance;         /* advance of glyph '0' (px); <= 0 -> fallback */
    double cap_height;           /* font cap-height (px); <= 0 -> fallback */
    double ideographic_advance;  /* advance of U+6C34 (px); <= 0 -> fallback */
} cl_ctx;

/* The context every length resolves against before any element is known: CSS
 * initial font-size, normalized viewport, no measured font metrics. This is the
 * correct context for a media query prelude (whose `em` is defined to use the
 * initial font size, never the author's root) and the conservative default
 * everywhere else. */
cl_ctx cl_ctx_initial(void);

/*
 * Resolves `value` -- a complete CSS <length> token such as "10pt", "-1.5em",
 * "0", "50vmin" -- to px.
 *
 * Leading and trailing ASCII spaces/tabs are ignored; a space BETWEEN the
 * number and its unit is a syntax error (a <dimension> is one token). Unit
 * names are ASCII case-insensitive. A unitless zero is a valid length; a
 * unitless non-zero value is not (CL_ERR_UNIT) -- assuming px for it would be
 * exactly the kind of invented rule this engine refuses to have.
 *
 * Returns CL_OK and writes *out_px, or one of the CL_ERR_* codes leaving
 * *out_px untouched.
 */
cl_status cl_resolve(const char *value, const cl_ctx *ctx, double *out_px);

/*
 * Parses a CSS <number> at the start of `s` (CSS Syntax Level 3, 4.3.12):
 *
 *     [+-]?  ( digit+ ('.' digit*)?  |  '.' digit+ )  ( [eE] [+-]? digit+ )?
 *
 * Returns 1 on success, writing *out and pointing *endp at the first
 * unconsumed character; 0 if there is no number there.
 *
 * Exported because it is the same grammar for a length, a colour channel, an
 * opacity and a transform argument, and having one implementation is what
 * prevents them from disagreeing. The previous private parser required a digit
 * BEFORE the decimal point, so the extremely common `.5` spelling -- as in
 * `rgba(0,0,0,.5)`, `opacity:.75` or `padding:0 28px 0 .75em` -- was rejected
 * and the whole declaration dropped.
 *
 * Locale-independent by construction: it never calls strtod, so a locale whose
 * decimal separator is ',' cannot truncate "1.5px" to 1px.
 */
int cl_number(const char *s, double *out, const char **endp);

/*
 * Resolves a bare unit name to how many px one of it is worth in `ctx`
 * ("pt" -> 1.333..., "em" -> ctx->font_size). Exposed so an expression
 * evaluator (calc()) can resolve a dimension it has already tokenized without
 * reassembling the text. Returns CL_ERR_UNIT for a non-<length> unit.
 *
 * `unit` need not be NUL-terminated within CL_MAX_TOKEN if unit_len is given;
 * pass unit_len == 0 to measure a NUL-terminated string.
 */
cl_status cl_unit_scale(const char *unit, size_t unit_len,
                        const cl_ctx *ctx, double *out_px_per_unit);

/* Non-zero when `unit` names a <length> unit at all (any of the three families
 * plus px). Used to tell "unsupported unit" apart from "not a length". */
int cl_is_length_unit(const char *unit, size_t unit_len);

/*
 * Non-zero when `unit` is FONT-RELATIVE (em/ex/ch/cap/ic/lh -- but NOT rem/rlh,
 * which are relative to the root and therefore absolute from any non-root
 * element's point of view).
 *
 * This is what lets `font-size` classify a declaration as absolute or relative
 * without maintaining a hand-written unit whitelist at that call site: add a
 * unit here and every consumer classifies it correctly on its own. See
 * spec/css.md "font-size: absolute vs relative".
 */
int cl_unit_is_font_relative(const char *unit, size_t unit_len);

#endif /* FREEDOM_CSS_LENGTH_H */
