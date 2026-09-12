#include "css_gradient.h"
#include "css_decl.h"
#include "css_color.h"
#include "css_length.h"
#include "css_select.h"
#include "css_values.h"

#include <string.h>
#include <stdlib.h>

static int cg_parse_num(const char *s, double *out, const char **endp)
{
    return cl_number(s, out, endp);
}

static int cg_wide_keyword(const char *v)
{
    return csel_ci_eq(v, "initial") || csel_ci_eq(v, "inherit") ||
           csel_ci_eq(v, "unset") || csel_ci_eq(v, "revert") ||
           csel_ci_eq(v, "revert-layer");
}

/* --- linear-gradient backgrounds (2026-07-11, spec/css.md) ---
 * The accepted grammar has no URL form, so a gradient can never fetch. Everything
 * else about it fails closed: an unparseable direction or color, unbalanced parens
 * or fewer than 2 stops drop the gradient (and, for the `background` shorthand,
 * the whole declaration). */

/* `to <side-or-corner>` (two keywords in either order) or `<int>deg` -> CSS degrees
 * normalized [0,359]. Returns -1 when seg is not direction syntax at all (it may be
 * the first color stop), -2 when it IS direction syntax but invalid (poisons the
 * gradient). */
static int grad_direction(const char *seg) {
    const char *p = seg;
    if (*p == '-' || *p == '+' || (*p >= '0' && *p <= '9')) {
        char *end = NULL;
        long a = strtol(seg, &end, 10);
        if (end != seg && csel_ci_eq(end, "deg"))
            return (int)(((a % 360) + 360) % 360);
        return -2;   /* rad/grad/turn/junk angles: unsupported */
    }
    if (!(csel_lower_ch(p[0]) == 't' && csel_lower_ch(p[1]) == 'o' &&
          (p[2] == ' ' || p[2] == '\t')))
        return -1;
    p += 3;
    int vert = -1, horiz = -1;
    for (int w = 0; w < 2; ++w) {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char word[16];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof word)
            word[k++] = csel_lower_ch(*p++);
        word[k] = '\0';
        if      (strcmp(word, "top") == 0    && vert  < 0) vert = 0;
        else if (strcmp(word, "bottom") == 0 && vert  < 0) vert = 1;
        else if (strcmp(word, "right") == 0  && horiz < 0) horiz = 0;
        else if (strcmp(word, "left") == 0   && horiz < 0) horiz = 1;
        else return -2;
    }
    while (*p == ' ' || *p == '\t') ++p;
    if (*p != '\0') return -2;
    if (vert < 0 && horiz < 0) return -2;
    if (horiz < 0) return vert == 0 ? 0 : 180;
    if (vert < 0)  return horiz == 0 ? 90 : 270;
    if (vert == 0) return horiz == 0 ? 45 : 315;
    return horiz == 0 ? 135 : 225;
}

/* Locates a gradient function call `fn` (e.g. "linear-gradient(") in v
 * (case-insensitive; an occurrence that is the tail of a longer ident, e.g.
 * repeating-linear-gradient, does not count). Writes the call span [start,end)
 * (end past the closing paren) and the argument span. 1 = found, 0 = absent,
 * -1 = found but unbalanced (malformed). */
static int find_gradient_call(const char *v, const char *fn, size_t *start,
                              size_t *end, size_t *args, size_t *argn) {
    const size_t fnlen = strlen(fn);
    size_t n = strlen(v);
    for (size_t i = 0; i + fnlen <= n; ++i) {
        size_t k = 0;
        while (k < fnlen && csel_lower_ch(v[i + k]) == fn[k]) ++k;
        if (k != fnlen) continue;
        if (i > 0) {
            char pc = v[i - 1];
            if (pc == '-' || (pc >= 'a' && pc <= 'z') || (pc >= 'A' && pc <= 'Z') ||
                (pc >= '0' && pc <= '9'))
                continue;
        }
        size_t j = i + fnlen;
        int depth = 1;
        while (j < n && depth > 0) {
            if (v[j] == '(') ++depth;
            else if (v[j] == ')') --depth;
            ++j;
        }
        if (depth != 0) return -1;
        *start = i; *end = j;
        *args = i + fnlen; *argn = (j - 1) - (i + fnlen);
        return 1;
    }
    return 0;
}

/* conic-gradient prelude: `from <int>deg`, optionally followed by `at <pos>`
 * (position accepted and ignored -- always center, v1), or `at <pos>` alone.
 * Returns 1 = consumed (angle possibly set), 0 = not a prelude (it is the
 * first color stop), -1 = prelude syntax but malformed (poisons the gradient,
 * mirrors grad_direction's -2). */
static int conic_prelude(const char *seg, int *angle) {
    const char *p = seg;
    int saw = 0;
    if (csel_lower_ch(p[0]) == 'f' && csel_lower_ch(p[1]) == 'r' &&
        csel_lower_ch(p[2]) == 'o' && csel_lower_ch(p[3]) == 'm' &&
        (p[4] == ' ' || p[4] == '\t')) {
        p += 5;
        while (*p == ' ' || *p == '\t') ++p;
        char *end = NULL;
        long a = strtol(p, &end, 10);
        if (end == p ||
            !(csel_lower_ch(end[0]) == 'd' && csel_lower_ch(end[1]) == 'e' &&
              csel_lower_ch(end[2]) == 'g'))
            return -1;
        *angle = (int)(((a % 360) + 360) % 360);
        p = end + 3;
        saw = 1;
        while (*p == ' ' || *p == '\t') ++p;
    }
    if (csel_lower_ch(p[0]) == 'a' && csel_lower_ch(p[1]) == 't' &&
        (p[2] == ' ' || p[2] == '\t'))
        return 1;
    if (saw) return (*p == '\0') ? 1 : -1;
    return 0;
}

/* radial-gradient prelude (`circle ...`, `ellipse ...`, `at <pos>`): consumed
 * and ignored (always a centered circle, v1). 1 = consumed, 0 = not a prelude. */
static int radial_prelude(const char *seg) {
    static const char *const kw[] = { "circle", "ellipse", "at " };
    for (size_t k = 0; k < sizeof kw / sizeof kw[0]; ++k) {
        size_t kl = strlen(kw[k]);
        size_t m = 0;
        while (m < kl && csel_lower_ch(seg[m]) == kw[k][m]) ++m;
        if (m == kl) return 1;
    }
    return 0;
}

/* One stop position after a color: `N%` -> 0-1000 (x10); conic also accepts
 * `Ndeg` -> the same 0-1000 turn fraction; legacy bare 0..100 -> x10. Returns
 * the position or -1 (not a position / out of range; *endp untouched then). */
static int grad_stop_pos(const char *pp, int conic, const char **endp) {
    double dd;
    const char *ee;
    if (!cg_parse_num(pp, &dd, &ee)) return -1;
    if (*ee == '%') {
        if (dd < 0.0 || dd > 100.0) return -1;
        *endp = ee + 1;
        return (int)(dd * 10.0 + 0.5);
    }
    if (conic && csel_lower_ch(ee[0]) == 'd' && csel_lower_ch(ee[1]) == 'e' &&
        csel_lower_ch(ee[2]) == 'g') {
        if (dd < 0.0 || dd > 360.0) return -1;
        *endp = ee + 3;
        return (int)(dd / 360.0 * 1000.0 + 0.5);
    }
    if (*ee == '\0' || *ee == ' ' || *ee == '\t') {
        if (dd < 0.0 || dd > 100.0) return -1;
        *endp = ee;
        return (int)(dd * 10.0 + 0.5);
    }
    return -1;
}

/* Parses the argument list shared by linear-/radial-/conic-gradient (s[0,n) is
 * the text inside the parens): optional kind-specific prelude, then color stops
 * split on top-level commas. kind: 0 = linear (`to <side>`/`<int>deg` prelude),
 * 1 = radial (`circle`/`ellipse`/`at` prelude, ignored), 2 = conic (`from
 * <int>deg [at <pos>]` prelude; stop positions may be `deg`). Stop positions
 * (R5d, completed 2026-07-19) land in positions[] as 0-1000 (-1 = evenly
 * spaced); a stop with TWO positions emits its color twice (hard edge). Fills
 * *angle and colors[CSS_GRAD_STOPS_MAX]; returns the stop count clamped to
 * CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when
 * the gradient fails closed. */
static int parse_gradient_args(const char *s, size_t n, int kind, int *angle,
                               int *colors, int *positions) {
    *angle = (kind == 2) ? 0 : 180;
    int nstops = 0, first = 1;
    size_t i = 0;
    while (i < n) {
        size_t j = i;
        int depth = 0;
        while (j < n && (depth > 0 || s[j] != ',')) {
            if (s[j] == '(') ++depth;
            else if (s[j] == ')' && depth > 0) --depth;
            ++j;
        }
        size_t a = i, b = j;
        while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == '\r')) ++a;
        while (b > a && (s[b-1] == ' ' || s[b-1] == '\t' || s[b-1] == '\n' || s[b-1] == '\r')) --b;
        if (a == b) return 0;   /* empty segment */
        char seg[CSS_TOK_MAX];
        size_t len = b - a;
        if (len >= sizeof seg) return 0;
        memcpy(seg, s + a, len);
        seg[len] = '\0';

        if (first) {
            first = 0;
            if (kind == 2) {
                int c = conic_prelude(seg, angle);
                if (c == 1) { i = j + 1; continue; }
                if (c == -1) return 0;
            } else if (kind == 1) {
                if (radial_prelude(seg)) { i = j + 1; continue; }
            } else {
                int d = grad_direction(seg);
                if (d >= 0) { *angle = d; i = j + 1; continue; }
                if (d == -2) return 0;
            }
        }
        {
            size_t ce = 0;
            const char *lp = strchr(seg, '(');
            if (lp != NULL) {
                const char *rp = strchr(lp, ')');
                if (rp == NULL) return 0;
                ce = (size_t)(rp - seg) + 1;
            } else {
                while (seg[ce] != '\0' && seg[ce] != ' ' && seg[ce] != '\t') ++ce;
            }
            char color[CSS_TOK_MAX];
            memcpy(color, seg, ce);
            color[ce] = '\0';
            int cv = cv_parse_color(color);
            if (cv == -1) return 0;
            int p1 = -1, p2 = -1;
            const char *pp = seg + ce;
            while (*pp == ' ' || *pp == '\t') ++pp;
            if (*pp != '\0') {
                const char *e1 = pp;
                p1 = grad_stop_pos(pp, kind == 2, &e1);
                if (p1 >= 0) {
                    pp = e1;
                    while (*pp == ' ' || *pp == '\t') ++pp;
                    if (*pp != '\0') {
                        const char *e2 = pp;
                        p2 = grad_stop_pos(pp, kind == 2, &e2);
                    }
                }
            }
            if (nstops < CSS_GRAD_STOPS_MAX) {
                colors[nstops] = cv;
                if (positions != NULL) positions[nstops] = p1;
            }
            ++nstops;
            if (p2 >= 0) {
                /* two-position stop (`red 0 25%`): duplicate the color at the
                 * second position -> a hard edge (pie slices, stripes). */
                if (nstops < CSS_GRAD_STOPS_MAX) {
                    colors[nstops] = cv;
                    if (positions != NULL) positions[nstops] = p2;
                }
                ++nstops;
            }
        }
        i = j + 1;
    }
    if (nstops < 2) return 0;
    return nstops > CSS_GRAD_STOPS_MAX ? CSS_GRAD_STOPS_MAX : nstops;
}

/* Emits the gradient decl group. nstops == 0 emits only the explicit reset
 * (P_BG_GRAD_N = 0), which is how a shorthand clears a lower-tier gradient. */
static int emit_gradient(css_decl *dst, int cap, int angle, int nstops,
                          const int *colors, const int *positions) {
    if (nstops <= 0) {
        if (cap < 1) return 0;
        dst[0].prop = P_BG_GRAD_N;
        dst[0].ival = 0;
        return 1;
    }
    int pos_extra = (positions != NULL) ? nstops : 0;
    if (cap < 2 + nstops + pos_extra) return 0;
    dst[0].prop = P_BG_GRAD_ANGLE; dst[0].ival = angle;
    dst[1].prop = P_BG_GRAD_N;     dst[1].ival = nstops;
    for (int k = 0; k < nstops; ++k) {
        dst[2 + k].prop = P_BG_GRAD_C0 + k;
        dst[2 + k].ival = colors[k];
    }
    if (positions != NULL)
        for (int k = 0; k < nstops; ++k) {
            dst[2 + nstops + k].prop = P_BG_GRAD_POS0 + k;
            dst[2 + nstops + k].ival = positions[k];
        }
    return 2 + nstops + pos_extra;
}

/* Finds a single url(...) token in val (bare or quoted). On success (1) sets
 * [*us,*ue) to the full "url(...)" span in val and copies the trimmed, unquoted
 * inner text into out (bounded outcap, NUL-terminated). Returns 0 when val has no
 * url( at all, -1 when it does but the token is malformed (unbalanced parens) or
 * the inner text does not fit outcap -- fail closed: the caller must drop the
 * whole image (never fetch a truncated URL). */
static int find_url_token(const char *val, size_t *us, size_t *ue,
                          char *out, size_t outcap) {
    for (const char *p = val; *p != '\0'; ++p) {
        if (!((p[0] == 'u' || p[0] == 'U') && (p[1] == 'r' || p[1] == 'R') &&
              (p[2] == 'l' || p[2] == 'L') && p[3] == '('))
            continue;
        const char *inner = p + 4;
        const char *close = strchr(inner, ')');
        if (close == NULL) return -1;
        size_t ilen = (size_t)(close - inner);
        while (ilen > 0 && (*inner == ' ' || *inner == '\t')) { ++inner; --ilen; }
        while (ilen > 0 && (inner[ilen - 1] == ' ' || inner[ilen - 1] == '\t')) --ilen;
        if (ilen >= 2 && (inner[0] == '\'' || inner[0] == '"') && inner[ilen - 1] == inner[0]) {
            ++inner; ilen -= 2;
        }
        if (ilen == 0 || ilen >= outcap) return -1;
        memcpy(out, inner, ilen);
        out[ilen] = '\0';
        *us = (size_t)(p - val);
        *ue = (size_t)(close - val) + 1;
        return 1;
    }
    return 0;
}

/* R5c: detects radial-gradient(circle at center, color1, color2). Returns 1
 * with the argument span set. */
static int find_radial_gradient(const char *v, size_t *start, size_t *end,
                                 size_t *arg_start, size_t *arg_len) {
    size_t n = strlen(v);
    const char pre[] = "radial-gradient(";
    size_t pl = sizeof pre - 1;
    if (n < pl || memcmp(v, pre, pl) != 0) return 0;
    *start = 0;
    size_t p = pl, depth = 0;
    while (p < n) {
        if (v[p] == '(') ++depth;
        else if (v[p] == ')') { if (depth == 0) break; --depth; }
        ++p;
    }
    if (p >= n) return 0;
    *end = p + 1;
    *arg_start = pl;
    *arg_len = p - pl;
    return 1;
}

/* Emits the P_BG_IMAGE_URL decl: url==NULL emits the explicit "no image" reset
 * (ival=-1, mirrors emit_gradient's nstops<=0 reset); otherwise appends url to the
 * shared pool (bounded urlcap -- a pool overrun fails closed to reset rather than
 * silently keeping a stale image reference) and emits its index. */
static int emit_bg_image_url(css_decl *dst, int cap, const char *url,
                             char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap) {
    if (cap < 1) return 0;
    dst[0].prop = P_BG_IMAGE_URL;
    if (url == NULL || *nurl >= urlcap) {
        dst[0].ival = -1;
        return 1;
    }
    memcpy(urltab[*nurl], url, strlen(url) + 1);
    dst[0].ival = (int)*nurl;
    ++*nurl;
    return 1;
}

/* background-image: linear-gradient resolves to the gradient group (image-url
 * explicitly reset); a single url(...) (bare or quoted, with only whitespace
 * surrounding it -- multi-layer/trailing junk fails closed) resolves to the image
 * pool (gradient explicitly reset); none/radial/conic/repeating-gradients/
 * malformed/multi-layer emit both explicit resets. Never fetches: url() is only
 * ever a bounded string extraction, the same trust level as reading an href/src
 * attribute elsewhere in this pipeline -- deciding whether to actually fetch it
 * happens downstream (render_doc.c), gated by caps.images like an <img>. */
int cg_expand_bg_image(const char *val, css_decl *dst, int cap,
                           char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap) {
    size_t gs, ge, as, an;
    int colors[CSS_GRAD_STOPS_MAX] = { -1, -1, -1, -1 };
    int grad_pos[CSS_GRAD_STOPS_MAX] = { -1, -1, -1, -1 };
    int angle = 180, nst = 0, kind = 0;
    if (find_gradient_call(val, "linear-gradient(", &gs, &ge, &as, &an) == 1)
        nst = parse_gradient_args(val + as, an, 0, &angle, colors, grad_pos);
    if (nst == 0 && find_gradient_call(val, "conic-gradient(", &gs, &ge, &as, &an) == 1) {
        nst = parse_gradient_args(val + as, an, 2, &angle, colors, grad_pos);
        if (nst > 0) kind = 2;
    }
    if (nst == 0 && find_radial_gradient(val, &gs, &ge, &as, &an) == 1) {
        nst = parse_gradient_args(val + as, an, 1, &angle, colors, grad_pos);
        if (nst > 0) kind = 1;
    }
    int n = emit_gradient(dst, cap, angle, nst, colors, nst > 0 ? grad_pos : NULL);
    if (nst > 0) {
        /* the kind rides every gradient emission so a higher-tier linear fully
         * overrides a lower-tier radial/conic (independent cascade slots). */
        if (cap - n >= 1) { dst[n].prop = P_BG_GRAD_RADIAL; dst[n].ival = kind; ++n; }
        if (cap - n >= 1) n += emit_bg_image_url(dst + n, cap - n, NULL, urltab, nurl, urlcap);
        return n;
    }
    size_t us, ue;
    char urlbuf[CSS_URL_MAX];
    int uf = find_url_token(val, &us, &ue, urlbuf, sizeof urlbuf);
    const char *use_url = NULL;
    if (uf == 1) {
        int clean = 1;
        for (size_t i = 0; clean && i < us; ++i)
            if (val[i] != ' ' && val[i] != '\t') clean = 0;
        for (size_t i = ue; clean && val[i] != '\0'; ++i)
            if (val[i] != ' ' && val[i] != '\t') clean = 0;
        if (clean) use_url = urlbuf;
    }
    if (cap - n >= 1) n += emit_bg_image_url(dst + n, cap - n, use_url, urltab, nurl, urlcap);

    /* R5b: second comma-separated url (layer behind the first). */
    if (use_url != NULL && cap - n >= 1) {
        const char *comma = val + ue;
        while (*comma != '\0' && *comma != ',') ++comma;
        if (*comma == ',') {
            char urlbuf2[CSS_URL_MAX];
            size_t us2, ue2;
            int uf2 = find_url_token(comma + 1, &us2, &ue2, urlbuf2, sizeof urlbuf2);
            if (uf2 == 1 && *nurl < urlcap) {
                memcpy(urltab[*nurl], urlbuf2, strlen(urlbuf2) + 1);
                dst[n].prop = P_BG_IMAGE_URL2; dst[n].ival = (int)*nurl; ++*nurl; ++n;
            }
        }
    }
    return n;
}

/* background shorthand: CSS resets BOTH the color and the image layer (gradient or
 * url), so a color emits gradient-unset+image-unset and a gradient/url emits
 * color-unset. A present-but-broken gradient or malformed url(...) drops the whole
 * declaration (fail closed); a value with no color, gradient nor url keeps the
 * historical drop path. */
int cg_expand_background(const char *val, css_decl *dst, int cap,
                             char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap) {
    size_t gs = 0, ge = 0, as = 0, an = 0;
    int colors[CSS_GRAD_STOPS_MAX] = { -1, -1, -1, -1 };
    int grad_pos[CSS_GRAD_STOPS_MAX] = { -1, -1, -1, -1 };
    int angle = 180, nst = 0, kind = 0;
    int f = find_gradient_call(val, "linear-gradient(", &gs, &ge, &as, &an);
    if (f < 0) return 0;
    if (f == 1) {
        nst = parse_gradient_args(val + as, an, 0, &angle, colors, grad_pos);
        if (nst == 0) return 0;
    }
    if (f == 0) {
        f = find_gradient_call(val, "conic-gradient(", &gs, &ge, &as, &an);
        if (f < 0) return 0;
        if (f == 1) {
            nst = parse_gradient_args(val + as, an, 2, &angle, colors, grad_pos);
            if (nst == 0) return 0;
            kind = 2;
        }
    }
    if (f == 0) {
        f = find_gradient_call(val, "radial-gradient(", &gs, &ge, &as, &an);
        if (f < 0) return 0;
        if (f == 1) {
            nst = parse_gradient_args(val + as, an, 1, &angle, colors, grad_pos);
            if (nst == 0) return 0;
            kind = 1;
        }
    }
    size_t us = 0, ue = 0;
    char urlbuf[CSS_URL_MAX];
    int uf = 0;
    if (f != 1) {
        uf = find_url_token(val, &us, &ue, urlbuf, sizeof urlbuf);
        if (uf < 0) return 0;
    }
    char rest[CSS_URL_MAX];
    size_t n = strlen(val), r = 0;
    for (size_t i = 0; i < n && r + 1 < sizeof rest; ++i) {
        if (f == 1 && i >= gs && i < ge) continue;
        if (uf == 1 && i >= us && i < ue) continue;
        rest[r++] = val[i];
    }
    rest[r] = '\0';
    int color = cv_interp_bg(rest);
    /* `background: transparent` and `background: none` both mean "no colour and no
     * image layer", which is a RESET the shorthand must apply, not a value it fails
     * to understand: CSS Backgrounds 3 section 3.10 resets every longhand it omits.
     * Dropping them left whatever a lower-specificity rule (or the UA) painted. */
    if (f != 1 && uf != 1 && !cv_color_ok(color)) {
        char kw[CSS_TOK_MAX];
        const char *b = rest;
        while (*b == ' ' || *b == '\t') ++b;
        size_t tl = strlen(b);
        while (tl > 0 && (b[tl - 1] == ' ' || b[tl - 1] == '\t')) --tl;
        if (tl >= sizeof kw) return 0;
        memcpy(kw, b, tl);
        kw[tl] = '\0';
        if (!csel_ci_eq(kw, "none") && !cg_wide_keyword(kw)) return 0;
        color = CC_COLOR_TRANSPARENT;
    }
    if (cap < 2) return 0;
    dst[0].prop = P_BG;
    dst[0].ival = color;
    /* Alpha rides the shorthand too (2026-07-19); always emitted so
     * `background: red` resets a lower-tier rgba() alpha to opaque. */
    dst[1].prop = P_BG_ALPHA;
    dst[1].ival = cv_bg_alpha_of(rest);
    int w = 2;
    w += emit_gradient(dst + w, cap - w, angle, nst, colors, nst > 0 ? grad_pos : NULL);
    if (nst > 0 && cap - w >= 1) {
        dst[w].prop = P_BG_GRAD_RADIAL; dst[w].ival = kind; ++w;
    }
    if (cap - w >= 1) w += emit_bg_image_url(dst + w, cap - w, uf == 1 ? urlbuf : NULL,
                                             urltab, nurl, urlcap);
    return w;
}
