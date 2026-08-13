/*
 * css_length -- implementation: the canonical CSS <length> -> px resolver.
 *
 * Pure: no allocation, no I/O, no global state, no errno, no locale. Every
 * conversion factor is a literal quote from CSS Values and Units Module Level 4
 * sections 5.2, 6.1 and 6.2 -- there are no tuned constants here, and anything
 * this module cannot know (real font metrics, the viewport) arrives through
 * cl_ctx rather than being buried in the code. See spec/css_length.md.
 */

#include "css_length.h"

#include <math.h>
#include <string.h>

#include "css.h"   /* CSS_LEN_MAX, CSS_MEDIA_DEFAULT_WIDTH/HEIGHT */

/* CSS Values 4 section 5.2 anchors the whole absolute family to the inch:
 * 1in is defined as exactly 96px. Every other absolute unit is a fraction of
 * an inch, so all of them derive from this one number. */
#define CL_PX_PER_IN 96.0

static int cl_ascii_lower(int c) {
    return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
}

/* ASCII case-insensitive compare of a possibly-unterminated unit slice against
 * a lowercase literal. Unit identifiers are ASCII-only per the CSS grammar, so
 * no locale or UTF-8 handling is involved. */
static int cl_unit_eq(const char *unit, size_t len, const char *lit) {
    size_t i = 0;
    for (; i < len; ++i) {
        if (lit[i] == '\0') return 0;
        if (cl_ascii_lower((unsigned char)unit[i]) != (unsigned char)lit[i]) return 0;
    }
    return lit[i] == '\0';
}

/* Measures a NUL-terminated unit within CL_MAX_TOKEN. Returns 0 if `unit` has
 * no NUL in range (fail closed: an unbounded identifier is not a unit). */
static int cl_unit_len(const char *unit, size_t given, size_t *out) {
    if (given > 0) {
        if (given > CL_MAX_TOKEN) return 0;
        *out = given;
        return 1;
    }
    for (size_t i = 0; i <= CL_MAX_TOKEN; ++i) {
        if (unit[i] == '\0') { *out = i; return 1; }
    }
    return 0;
}

/* The element's font-size, falling back to the CSS initial value when the
 * caller left it unset. A zero or negative font-size would silently collapse
 * every font-relative length to 0, which is worse than using the initial. */
static double cl_font_size(const cl_ctx *ctx) {
    return (ctx->font_size > 0.0) ? ctx->font_size : CL_INITIAL_FONT_SIZE;
}

static double cl_root_font_size(const cl_ctx *ctx) {
    return (ctx->root_font_size > 0.0) ? ctx->root_font_size : CL_INITIAL_FONT_SIZE;
}

/* A font metric, or the fallback the spec itself names for when that metric is
 * unavailable -- expressed as a ratio of the font-size, never as absolute px.
 * See the CL_FALLBACK_*_RATIO documentation in the header. */
static double cl_metric_or(double measured, double ratio, const cl_ctx *ctx) {
    return (measured > 0.0) ? measured : ratio * cl_font_size(ctx);
}

/*
 * Viewport-relative units (section 6.2). The s/l/d prefixes select the small,
 * large and dynamic viewports; Freedom has no retractable browser chrome, so
 * all three coincide by construction and the prefix is accepted and skipped
 * rather than being a separate table.
 *
 * Returns 1 and writes *per (px per 1 unit) when the slice names a viewport
 * unit; 0 otherwise.
 */
static int cl_viewport_scale(const char *u, size_t len, const cl_ctx *ctx, double *per) {
    /* Skip the optional small/large/dynamic viewport prefix. */
    if (len >= 3) {
        int c0 = cl_ascii_lower((unsigned char)u[0]);
        if ((c0 == 's' || c0 == 'l' || c0 == 'd')
            && cl_ascii_lower((unsigned char)u[1]) == 'v') { ++u; --len; }
    }

    double w = ctx->viewport_w, h = ctx->viewport_h;
    double axis;
    if      (cl_unit_eq(u, len, "vw") || cl_unit_eq(u, len, "vi")) axis = w;
    else if (cl_unit_eq(u, len, "vh") || cl_unit_eq(u, len, "vb")) axis = h;
    else if (cl_unit_eq(u, len, "vmin")) axis = (w < h) ? w : h;
    else if (cl_unit_eq(u, len, "vmax")) axis = (w > h) ? w : h;
    else return 0;

    *per = axis / 100.0;
    return 1;
}

cl_ctx cl_ctx_initial(void) {
    cl_ctx c;
    c.font_size            = CL_INITIAL_FONT_SIZE;
    c.root_font_size       = CL_INITIAL_FONT_SIZE;
    c.line_height          = CL_NORMAL_LINE_RATIO * CL_INITIAL_FONT_SIZE;
    c.root_line_height     = CL_NORMAL_LINE_RATIO * CL_INITIAL_FONT_SIZE;
    /* Anti-fingerprinting: the NORMALIZED desktop, never the real window. */
    c.viewport_w           = (double)CSS_MEDIA_DEFAULT_WIDTH;
    c.viewport_h           = (double)CSS_MEDIA_DEFAULT_HEIGHT;
    /* No font measured yet -- the spec-named fallbacks apply. */
    c.x_height             = 0.0;
    c.zero_advance         = 0.0;
    c.cap_height           = 0.0;
    c.ideographic_advance  = 0.0;
    return c;
}

cl_status cl_unit_scale(const char *unit, size_t unit_len,
                        const cl_ctx *ctx, double *out_px_per_unit) {
    if (unit == NULL || ctx == NULL || out_px_per_unit == NULL) return CL_ERR_NULL_ARG;

    size_t len;
    if (!cl_unit_len(unit, unit_len, &len) || len == 0) return CL_ERR_UNIT;

    double per;

    /* Section 5.2 -- absolute lengths, all derived from 1in == 96px. */
    if      (cl_unit_eq(unit, len, "px")) per = 1.0;
    else if (cl_unit_eq(unit, len, "in")) per = CL_PX_PER_IN;
    else if (cl_unit_eq(unit, len, "pt")) per = CL_PX_PER_IN / 72.0;    /* 1pt = 1/72in  */
    else if (cl_unit_eq(unit, len, "pc")) per = CL_PX_PER_IN / 6.0;     /* 1pc = 1/6in   */
    else if (cl_unit_eq(unit, len, "cm")) per = CL_PX_PER_IN / 2.54;    /* 1cm = 1/2.54in*/
    else if (cl_unit_eq(unit, len, "mm")) per = CL_PX_PER_IN / 25.4;    /* 1mm = 1/10cm  */
    else if (cl_unit_eq(unit, len, "q"))  per = CL_PX_PER_IN / 101.6;   /* 1Q  = 1/40cm  */

    /* Section 6.1 -- font-relative lengths. */
    else if (cl_unit_eq(unit, len, "em"))  per = cl_font_size(ctx);
    else if (cl_unit_eq(unit, len, "rem")) per = cl_root_font_size(ctx);
    else if (cl_unit_eq(unit, len, "ex"))
        per = cl_metric_or(ctx->x_height, CL_FALLBACK_EX_RATIO, ctx);
    else if (cl_unit_eq(unit, len, "ch"))
        per = cl_metric_or(ctx->zero_advance, CL_FALLBACK_CH_RATIO, ctx);
    else if (cl_unit_eq(unit, len, "cap"))
        per = cl_metric_or(ctx->cap_height, CL_FALLBACK_CAP_RATIO, ctx);
    else if (cl_unit_eq(unit, len, "ic"))
        per = cl_metric_or(ctx->ideographic_advance, CL_FALLBACK_IC_RATIO, ctx);
    else if (cl_unit_eq(unit, len, "lh"))
        per = (ctx->line_height > 0.0)
            ? ctx->line_height : CL_NORMAL_LINE_RATIO * cl_font_size(ctx);
    else if (cl_unit_eq(unit, len, "rlh"))
        per = (ctx->root_line_height > 0.0)
            ? ctx->root_line_height : CL_NORMAL_LINE_RATIO * cl_root_font_size(ctx);

    /* Section 6.2 -- viewport-relative lengths. */
    else if (cl_viewport_scale(unit, len, ctx, &per)) { /* per written */ }

    /* Not a <length>: percentages, angles, times, container-query units. Fails
     * closed rather than guessing -- a cq* unit without a query container has no
     * correct answer, and inventing one is worse than rejecting the
     * declaration. */
    else return CL_ERR_UNIT;

    if (!isfinite(per)) return CL_ERR_RANGE;
    *out_px_per_unit = per;
    return CL_OK;
}

int cl_is_length_unit(const char *unit, size_t unit_len) {
    if (unit == NULL) return 0;
    cl_ctx c = cl_ctx_initial();
    double per;
    return cl_unit_scale(unit, unit_len, &c, &per) == CL_OK;
}

int cl_unit_is_font_relative(const char *unit, size_t unit_len) {
    if (unit == NULL) return 0;
    size_t len;
    if (!cl_unit_len(unit, unit_len, &len) || len == 0) return 0;
    /* rem/rlh resolve against the ROOT, so from any element's point of view
     * they are absolute -- inheriting a different font-size cannot change them.
     * That distinction is the entire point of this predicate. */
    return cl_unit_eq(unit, len, "em")  || cl_unit_eq(unit, len, "ex")
        || cl_unit_eq(unit, len, "ch")  || cl_unit_eq(unit, len, "cap")
        || cl_unit_eq(unit, len, "ic")  || cl_unit_eq(unit, len, "lh");
}

/*
 * How many px one of `unit` is worth per 1px of font-size -- the derivative the
 * cascade needs to re-fit a length once the element's computed font-size is
 * known (spec/css_length.md section 8.3).
 *
 * It is READ OUT OF cl_unit_scale, not written by hand: the probe context has
 * font_size 1.0 and no measured metrics, so the factor the table returns IS the
 * ratio. A unit added to section 6.1 therefore gets its coefficient for free,
 * and the two can never drift apart -- which is the same argument that made
 * this module the single length resolver in the first place.
 *
 * Non-font-relative units answer 0: for them the length simply does not move
 * with the font-size.
 */
double cl_unit_font_ratio(const char *unit, size_t unit_len) {
    if (!cl_unit_is_font_relative(unit, unit_len)) return 0.0;

    cl_ctx probe = cl_ctx_initial();
    probe.font_size = 1.0;
    /* Zeroed so the spec-named fallbacks (which ARE ratios of the font-size)
     * apply. A measured metric is absolute px taken at one size and would not
     * be a ratio at all -- see the honest-limit note in spec section 8.3. */
    probe.line_height         = 0.0;
    probe.x_height            = 0.0;
    probe.zero_advance        = 0.0;
    probe.cap_height          = 0.0;
    probe.ideographic_advance = 0.0;

    double per;
    if (cl_unit_scale(unit, unit_len, &probe, &per) != CL_OK) return 0.0;
    return isfinite(per) ? per : 0.0;
}

double cl_em_refit(double px, double em, double from_font_size, double font_size) {
    if (em == 0.0) return px;
    if (!isfinite(px) || !isfinite(em)) return px;
    if (!isfinite(from_font_size) || from_font_size <= 0.0) return px;
    if (!isfinite(font_size) || font_size <= 0.0) return px;
    double v = px + em * (font_size - from_font_size);
    return isfinite(v) ? v : px;
}

/*
 * Parses a CSS <number> (CSS Syntax 4.3.12) without strtod -- strtod is
 * locale-dependent, and a locale whose decimal separator is ',' would silently
 * truncate "1.5px" to 1px. Returns 1 and advances *pp past the number.
 */
static int cl_parse_number(const char **pp, const char *end, double *out) {
    const char *p = *pp;
    double sign = 1.0;

    if (p < end && (*p == '+' || *p == '-')) {
        if (*p == '-') sign = -1.0;
        ++p;
    }

    double mant = 0.0;
    int digits = 0;
    while (p < end && *p >= '0' && *p <= '9') {
        mant = mant * 10.0 + (*p - '0');
        ++p; ++digits;
    }
    if (p < end && *p == '.') {
        /* A '.' only belongs to the number if it is followed by a digit or
         * preceded by one; a bare "." is not a number. */
        ++p;
        double scale = 0.1;
        while (p < end && *p >= '0' && *p <= '9') {
            mant += (*p - '0') * scale;
            scale *= 0.1;
            ++p; ++digits;
        }
    }
    /* "5." and ".5" are both valid; "." alone is not. */
    if (digits == 0) return 0;

    /* Optional scientific exponent. A malformed exponent is not consumed, so
     * "1e" parses as the number 1 followed by the unit "e" -- which is not a
     * length unit and therefore fails closed one level up. */
    if (p < end && (*p == 'e' || *p == 'E')) {
        const char *save = p;
        const char *q = p + 1;
        double esign = 1.0;
        if (q < end && (*q == '+' || *q == '-')) {
            if (*q == '-') esign = -1.0;
            ++q;
        }
        int edigits = 0;
        double eval = 0.0;
        while (q < end && *q >= '0' && *q <= '9') {
            eval = eval * 10.0 + (*q - '0');
            ++q; ++edigits;
        }
        if (edigits > 0) {
            mant *= pow(10.0, esign * eval);
            p = q;
        } else {
            p = save;
        }
    }

    *out = sign * mant;
    *pp = p;
    return 1;
}

int cl_number(const char *s, double *out, const char **endp) {
    if (s == NULL || out == NULL || endp == NULL) return 0;
    size_t n = 0;
    while (n <= CL_MAX_TOKEN && s[n] != '\0') ++n;
    const char *p = s;
    if (!cl_parse_number(&p, s + n, out)) return 0;
    if (!isfinite(*out)) return 0;
    *endp = p;
    return 1;
}

/*
 * The shared core of cl_resolve and cl_resolve_lp: tokenize <number><unit> and
 * resolve it into the two components of a <length-percentage>. Keeping ONE
 * tokenizer is what stops the two entry points from disagreeing about, say,
 * whether "10 px" is legal.
 */
static cl_status cl_resolve_core(const char *value, const cl_ctx *ctx, cl_lp *out) {
    if (value == NULL || ctx == NULL || out == NULL) return CL_ERR_NULL_ARG;

    /* Bounded scan: a <length> token is short, and refusing to walk past
     * CL_MAX_TOKEN is what makes this safe on a value that lost its NUL. */
    size_t n = 0;
    while (n <= CL_MAX_TOKEN && value[n] != '\0') ++n;
    if (n > CL_MAX_TOKEN) return CL_ERR_SYNTAX;

    const char *p = value, *end = value + n;
    while (p < end && (*p == ' ' || *p == '\t')) ++p;
    while (end > p && (end[-1] == ' ' || end[-1] == '\t')) --end;
    if (p == end) return CL_ERR_SYNTAX;

    double num;
    if (!cl_parse_number(&p, end, &num)) return CL_ERR_SYNTAX;
    if (!isfinite(num)) return CL_ERR_RANGE;

    /* A <dimension> is a single token: no whitespace between number and unit.
     * Accepting "10 px" would be inventing grammar the CSS parser does not
     * have, and would make `margin: 10 px` mean something in Freedom that it
     * means in no other browser. The same holds for a <percentage>: "2 %". */
    if (p < end && (*p == ' ' || *p == '\t')) return CL_ERR_SYNTAX;

    out->px = 0.0;
    out->em = 0.0;
    out->pct = 0.0;
    out->has_pct = 0;

    if (p == end) {
        /* Unitless. Section 5: only zero is a valid <length> without a unit. */
        if (num != 0.0) return CL_ERR_UNIT;
        return CL_OK;
    }

    /* A <percentage> is the number plus exactly one '%' and nothing else. */
    if (*p == '%') {
        if (p + 1 != end) return CL_ERR_SYNTAX;
        out->pct = num;
        out->has_pct = 1;
        return CL_OK;
    }

    /* Whatever else follows the number must be a bare identifier: a trailing
     * ';' or any other non-identifier byte is a syntax error, not an unknown
     * unit. '%' is handled above, so it can no longer appear mid-token. */
    for (const char *q = p; q < end; ++q) {
        int c = cl_ascii_lower((unsigned char)*q);
        if (!(c >= 'a' && c <= 'z')) return CL_ERR_SYNTAX;
    }

    double per;
    cl_status st = cl_unit_scale(p, (size_t)(end - p), ctx, &per);
    if (st != CL_OK) return st;

    double px = num * per;
    /* Only non-finite results are rejected here. Magnitude clamping is the
     * CALLER's job: CSS_LEN_MAX is an anti-DoS policy of the box model, not a
     * property of the unit, and every emitter already saturates through
     * round_clamp. Rejecting instead of saturating would silently change
     * `width:99999999px` from "very wide" to "no width at all". */
    if (!isfinite(px)) return CL_ERR_RANGE;

    out->px = px;
    out->em = num * cl_unit_font_ratio(p, (size_t)(end - p));
    return CL_OK;
}

cl_status cl_resolve(const char *value, const cl_ctx *ctx, double *out_px) {
    if (out_px == NULL) return CL_ERR_NULL_ARG;
    cl_lp lp;
    cl_status st = cl_resolve_core(value, ctx, &lp);
    if (st != CL_OK) return st;
    /* A percentage is not a <length>. Properties that accept the wider type ask
     * for it explicitly through cl_resolve_lp; everything else keeps failing
     * closed here, which is what makes `letter-spacing: 5%` a dropped
     * declaration rather than an invented one. */
    if (lp.has_pct) return CL_ERR_UNIT;
    *out_px = lp.px;
    return CL_OK;
}

cl_status cl_resolve_lp(const char *value, const cl_ctx *ctx, cl_lp *out) {
    return cl_resolve_core(value, ctx, out);
}

double cl_lp_used(cl_lp lp, double basis) {
    if (!lp.has_pct) return lp.px;
    if (!isfinite(basis) || basis <= 0.0) return lp.px;
    double v = lp.px + lp.pct / 100.0 * basis;
    return isfinite(v) ? v : lp.px;
}
