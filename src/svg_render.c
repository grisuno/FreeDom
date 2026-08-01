/* svg_render — inline <svg> markup -> a bounded list of geometric shapes.
 *
 * PURE: no I/O, no allocation, no globals. See spec/svg_render.md.
 *
 * The accepted grammar deliberately contains NO element or attribute that can name
 * a resource. <image>, <use>, <foreignObject>, <script> and <style> are dropped with
 * their whole subtree, so a parsed SVG structurally cannot fetch, execute or leak.
 * That is what lets inline SVG paint unconditionally while <img> stays gated.
 */

#include "svg_render.h"

#include <math.h>
#include <stddef.h>
#include <string.h>

#include "css_color.h"

/* --- small scanning helpers (no locale, no allocation) --- */

static int sv_is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

static int sv_is_digit(char c) { return c >= '0' && c <= '9'; }

static char sv_lower(char c) {
    return (c >= 'A' && c <= 'Z') ? (char)(c - 'A' + 'a') : c;
}

/* Case-insensitive compare of the span [s, s+n) against a NUL-terminated literal. */
static int sv_span_eq(const char *s, size_t n, const char *lit) {
    size_t i = 0;
    for (; i < n; ++i) {
        if (lit[i] == '\0') return 0;
        if (sv_lower(s[i]) != sv_lower(lit[i])) return 0;
    }
    return lit[i] == '\0';
}

/* Parses a decimal number at s[*i]; returns 1 and advances *i on success.
 * Accepts a leading sign, a fraction and an exponent -- the SVG number grammar.
 * Rejects (returns 0) anything else, leaving *i where it was: a malformed value
 * degrades to its default instead of poisoning the shape. */
static int sv_number(const char *s, size_t n, size_t *i, double *out) {
    size_t p = *i;
    while (p < n && sv_is_space(s[p])) ++p;
    size_t start = p;
    int neg = 0;
    if (p < n && (s[p] == '+' || s[p] == '-')) { neg = (s[p] == '-'); ++p; }
    double v = 0.0;
    int any = 0;
    while (p < n && sv_is_digit(s[p])) { v = v * 10.0 + (s[p] - '0'); ++p; any = 1; }
    if (p < n && s[p] == '.') {
        ++p;
        double f = 0.1;
        while (p < n && sv_is_digit(s[p])) { v += (s[p] - '0') * f; f *= 0.1; ++p; any = 1; }
    }
    if (!any) { *i = start; return 0; }
    if (p < n && (s[p] == 'e' || s[p] == 'E')) {
        size_t q = p + 1;
        int eneg = 0;
        if (q < n && (s[q] == '+' || s[q] == '-')) { eneg = (s[q] == '-'); ++q; }
        int edig = 0, ev = 0;
        while (q < n && sv_is_digit(s[q]) && ev < 1000) { ev = ev * 10 + (s[q] - '0'); ++q; edig = 1; }
        if (edig) {
            /* Bounded: a hostile exponent must not spin or produce inf. */
            if (ev > 300) ev = 300;
            double m = pow(10.0, eneg ? -(double)ev : (double)ev);
            v *= m;
            p = q;
        }
    }
    if (neg) v = -v;
    if (!isfinite(v)) v = 0.0;
    *out = v;
    *i = p;
    return 1;
}

/* Skips one separator run (whitespace and/or a single comma) in a coordinate list. */
static void sv_sep(const char *s, size_t n, size_t *i) {
    while (*i < n && sv_is_space(s[*i])) ++*i;
    if (*i < n && s[*i] == ',') ++*i;
    while (*i < n && sv_is_space(s[*i])) ++*i;
}

/* --- attribute lookup ---------------------------------------------------- */

/* One attribute of the tag currently being scanned. */
typedef struct sv_attr {
    const char *name; size_t nlen;
    const char *val;  size_t vlen;
} sv_attr;

#define SV_MAX_ATTRS 32

/* Value of attribute `name` among the parsed attrs, or NULL. */
static const char *sv_attr_get(const sv_attr *at, size_t nat, const char *name, size_t *len) {
    for (size_t i = 0; i < nat; ++i) {
        if (sv_span_eq(at[i].name, at[i].nlen, name)) { *len = at[i].vlen; return at[i].val; }
    }
    return NULL;
}

/* Numeric attribute, or `dflt` when absent/malformed. Unit suffixes (px, pt, %) are
 * ignored: the leading number is what the geometry uses. */
static double sv_attr_num(const sv_attr *at, size_t nat, const char *name, double dflt) {
    size_t vl = 0;
    const char *v = sv_attr_get(at, nat, name, &vl);
    if (v == NULL) return dflt;
    size_t i = 0;
    double out = 0.0;
    if (!sv_number(v, vl, &i, &out)) return dflt;
    return out;
}

/* Copies a span into a NUL-terminated scratch buffer, trimmed. Returns 0 when it
 * does not fit (the caller then treats the value as absent -- fail closed). */
static int sv_span_copy(const char *s, size_t n, char *dst, size_t cap) {
    while (n > 0 && sv_is_space(*s)) { ++s; --n; }
    while (n > 0 && sv_is_space(s[n - 1])) --n;
    if (n + 1 > cap) return 0;
    memcpy(dst, s, n);
    dst[n] = '\0';
    return 1;
}

/* Parses a paint value ("none" | "currentColor" | any CSS colour) into the packed
 * form the shapes carry: >= 0 RGB, -1 none, CC_COLOR_CURRENT currentColor.
 * Anything unrecognised (including url(...) references, which this module refuses
 * to resolve) becomes -1: no paint, never a fetch. */
static int sv_paint(const char *v, size_t vlen, int dflt) {
    char buf[64];
    if (!sv_span_copy(v, vlen, buf, sizeof buf)) return dflt;
    if (buf[0] == '\0') return dflt;
    if (sv_span_eq(buf, strlen(buf), "none")) return -1;
    if (sv_span_eq(buf, strlen(buf), "transparent")) return -1;
    cc_rgb c;
    cc_status st = cc_parse(buf, &c);
    if (st == CC_OK) return cc_pack(c);
    if (st == CC_CURRENT_COLOR) return CC_COLOR_CURRENT;
    return -1;
}

/* --- inherited presentation state --------------------------------------- */

/* The presentation context an element inherits from its <g> chain, plus the
 * accumulated transform. Copied by value at each level, so a group can never leak
 * its state to a later sibling. */
typedef struct sv_ctx {
    int    fill, stroke;
    double stroke_w;
    int    opacity, fill_opacity, stroke_opacity;
    int    fill_even_odd;
    int    linecap, linejoin;
    double font_size;
    double m[6];
} sv_ctx;

static void sv_mat_identity(double *m) {
    m[0] = 1.0; m[1] = 0.0; m[2] = 0.0; m[3] = 1.0; m[4] = 0.0; m[5] = 0.0;
}

/* out = a * b  (apply b first, then a -- Cairo/SVG convention). */
static void sv_mat_mul(const double *a, const double *b, double *out) {
    double r[6];
    r[0] = a[0] * b[0] + a[2] * b[1];
    r[1] = a[1] * b[0] + a[3] * b[1];
    r[2] = a[0] * b[2] + a[2] * b[3];
    r[3] = a[1] * b[2] + a[3] * b[3];
    r[4] = a[0] * b[4] + a[2] * b[5] + a[4];
    r[5] = a[1] * b[4] + a[3] * b[5] + a[5];
    memcpy(out, r, sizeof r);
}

/* Parses a `transform` list and composes it onto ctx->m. Unknown functions are
 * skipped; a malformed argument list ends the parse with what was composed. */
static void sv_parse_transform(const char *s, size_t n, double *m) {
    size_t i = 0;
    while (i < n) {
        while (i < n && (sv_is_space(s[i]) || s[i] == ',')) ++i;
        size_t ns = i;
        while (i < n && s[i] != '(' && !sv_is_space(s[i])) ++i;
        size_t nlen = i - ns;
        while (i < n && sv_is_space(s[i])) ++i;
        if (i >= n || s[i] != '(') break;
        ++i;
        double arg[6];
        size_t na = 0;
        while (na < 6 && i < n) {
            size_t save = i;
            double v = 0.0;
            if (!sv_number(s, n, &i, &v)) { i = save; break; }
            arg[na++] = v;
            sv_sep(s, n, &i);
        }
        while (i < n && s[i] != ')') ++i;
        if (i < n) ++i;

        double t[6];
        sv_mat_identity(t);
        if (sv_span_eq(s + ns, nlen, "translate") && na >= 1) {
            t[4] = arg[0];
            t[5] = (na >= 2) ? arg[1] : 0.0;
        } else if (sv_span_eq(s + ns, nlen, "scale") && na >= 1) {
            t[0] = arg[0];
            t[3] = (na >= 2) ? arg[1] : arg[0];
        } else if (sv_span_eq(s + ns, nlen, "rotate") && na >= 1) {
            double r = arg[0] * 3.14159265358979323846 / 180.0;
            double cs = cos(r), sn = sin(r);
            if (na >= 3) {
                /* rotate(a, cx, cy) == translate(c) rotate(a) translate(-c) */
                double pre[6] = { 1, 0, 0, 1, arg[1], arg[2] };
                double rot[6] = { cs, sn, -sn, cs, 0, 0 };
                double post[6] = { 1, 0, 0, 1, -arg[1], -arg[2] };
                sv_mat_mul(pre, rot, t);
                sv_mat_mul(t, post, t);
            } else {
                t[0] = cs; t[1] = sn; t[2] = -sn; t[3] = cs;
            }
        } else if (sv_span_eq(s + ns, nlen, "skewx") && na >= 1) {
            t[2] = tan(arg[0] * 3.14159265358979323846 / 180.0);
        } else if (sv_span_eq(s + ns, nlen, "skewy") && na >= 1) {
            t[1] = tan(arg[0] * 3.14159265358979323846 / 180.0);
        } else if (sv_span_eq(s + ns, nlen, "matrix") && na >= 6) {
            for (int k = 0; k < 6; ++k) t[k] = arg[k];
        } else {
            continue;   /* unknown function: identity, keep scanning */
        }
        sv_mat_mul(m, t, m);
    }
}

/* Reads one `name:value` declaration out of a style="" attribute. Returns 0 at the
 * end. Only the presentation properties this module honours are looked up by the
 * caller, so an unknown declaration is simply skipped. */
static int sv_style_next(const char *s, size_t n, size_t *i,
                         const char **np, size_t *nl,
                         const char **vp, size_t *vl) {
    while (*i < n && (sv_is_space(s[*i]) || s[*i] == ';')) ++*i;
    if (*i >= n) return 0;
    size_t ns = *i;
    while (*i < n && s[*i] != ':' && s[*i] != ';') ++*i;
    size_t ne = *i;
    if (*i >= n || s[*i] != ':') { while (*i < n && s[*i] != ';') ++*i; return 1; }
    ++*i;
    size_t vs = *i;
    while (*i < n && s[*i] != ';') ++*i;
    size_t ve = *i;
    while (ne > ns && sv_is_space(s[ne - 1])) --ne;
    while (vs < ve && sv_is_space(s[vs])) ++vs;
    while (ve > vs && sv_is_space(s[ve - 1])) --ve;
    *np = s + ns; *nl = ne - ns;
    *vp = s + vs; *vl = ve - vs;
    return 1;
}

/* Applies one presentation property (from an attribute or from style="") to ctx. */
static void sv_apply_prop(sv_ctx *ctx, const char *nm, size_t nl,
                          const char *v, size_t vl) {
    if (sv_span_eq(nm, nl, "fill")) {
        ctx->fill = sv_paint(v, vl, ctx->fill);
    } else if (sv_span_eq(nm, nl, "stroke")) {
        ctx->stroke = sv_paint(v, vl, ctx->stroke);
    } else if (sv_span_eq(nm, nl, "stroke-width")) {
        size_t i = 0; double x = 0.0;
        if (sv_number(v, vl, &i, &x) && x >= 0.0) ctx->stroke_w = x;
    } else if (sv_span_eq(nm, nl, "opacity")) {
        size_t i = 0; double x = 0.0;
        if (sv_number(v, vl, &i, &x)) {
            if (x < 0.0) x = 0.0;
            if (x > 1.0) x = 1.0;
            ctx->opacity = (int)(x * 100.0 + 0.5);
        }
    } else if (sv_span_eq(nm, nl, "fill-opacity")) {
        size_t i = 0; double x = 0.0;
        if (sv_number(v, vl, &i, &x)) {
            if (x < 0.0) x = 0.0;
            if (x > 1.0) x = 1.0;
            ctx->fill_opacity = (int)(x * 100.0 + 0.5);
        }
    } else if (sv_span_eq(nm, nl, "stroke-opacity")) {
        size_t i = 0; double x = 0.0;
        if (sv_number(v, vl, &i, &x)) {
            if (x < 0.0) x = 0.0;
            if (x > 1.0) x = 1.0;
            ctx->stroke_opacity = (int)(x * 100.0 + 0.5);
        }
    } else if (sv_span_eq(nm, nl, "fill-rule")) {
        ctx->fill_even_odd = sv_span_eq(v, vl, "evenodd") ? 1 : 0;
    } else if (sv_span_eq(nm, nl, "stroke-linecap")) {
        ctx->linecap = sv_span_eq(v, vl, "round") ? 1 : sv_span_eq(v, vl, "square") ? 2 : 0;
    } else if (sv_span_eq(nm, nl, "stroke-linejoin")) {
        ctx->linejoin = sv_span_eq(v, vl, "round") ? 1 : sv_span_eq(v, vl, "bevel") ? 2 : 0;
    } else if (sv_span_eq(nm, nl, "font-size")) {
        size_t i = 0; double x = 0.0;
        if (sv_number(v, vl, &i, &x) && x > 0.0) ctx->font_size = x;
    } else if (sv_span_eq(nm, nl, "transform")) {
        sv_parse_transform(v, vl, ctx->m);
    }
}

/* Folds every presentation attribute of the current tag (and its style="") into a
 * copy of the inherited context. Attribute order follows the markup; style= wins,
 * matching CSS specificity for presentation attributes. */
static void sv_ctx_from_attrs(sv_ctx *ctx, const sv_attr *at, size_t nat) {
    for (size_t i = 0; i < nat; ++i)
        sv_apply_prop(ctx, at[i].name, at[i].nlen, at[i].val, at[i].vlen);
    size_t sl = 0;
    const char *st = sv_attr_get(at, nat, "style", &sl);
    if (st != NULL) {
        size_t i = 0;
        const char *np, *vp;
        size_t nl, vl;
        while (sv_style_next(st, sl, &i, &np, &nl, &vp, &vl)) {
            if (nl > 0) sv_apply_prop(ctx, np, nl, vp, vl);
        }
    }
}

/* --- shape emission ------------------------------------------------------ */

static sv_shape *sv_new_shape(sv_image *im, int kind, const sv_ctx *ctx) {
    if (im->nshape >= SV_MAX_SHAPES) return NULL;
    sv_shape *sh = &im->shapes[im->nshape++];
    memset(sh, 0, sizeof *sh);
    sh->kind = kind;
    sh->fill = ctx->fill;
    sh->stroke = ctx->stroke;
    sh->stroke_w = ctx->stroke_w;
    sh->opacity = ctx->opacity;
    sh->fill_opacity = ctx->fill_opacity;
    sh->stroke_opacity = ctx->stroke_opacity;
    sh->fill_even_odd = ctx->fill_even_odd;
    sh->linecap = ctx->linecap;
    sh->linejoin = ctx->linejoin;
    memcpy(sh->m, ctx->m, sizeof sh->m);
    return sh;
}

/* points="x,y x,y ..." into the shared point pool. */
static void sv_parse_points(sv_image *im, sv_shape *sh, const char *s, size_t n) {
    sh->first = im->npt;
    sh->count = 0;
    size_t i = 0;
    for (;;) {
        double x = 0.0, y = 0.0;
        sv_sep(s, n, &i);
        if (!sv_number(s, n, &i, &x)) break;
        sv_sep(s, n, &i);
        if (!sv_number(s, n, &i, &y)) break;
        if (im->npt >= SV_MAX_POINTS) break;
        im->px[im->npt] = x;
        im->py[im->npt] = y;
        ++im->npt;
        ++sh->count;
    }
}

/* --- <path d="..."> ------------------------------------------------------ */

static sv_seg *sv_new_seg(sv_image *im, sv_shape *sh) {
    if (im->nseg >= SV_MAX_SEGS) return NULL;
    sv_seg *sg = &im->segs[im->nseg++];
    memset(sg, 0, sizeof *sg);
    ++sh->count;
    return sg;
}

static int sv_seg_move(sv_image *im, sv_shape *sh, double x, double y) {
    sv_seg *sg = sv_new_seg(im, sh);
    if (sg == NULL) return 0;
    sg->verb = SV_MOVE; sg->x[0] = x; sg->y[0] = y;
    return 1;
}

static int sv_seg_line(sv_image *im, sv_shape *sh, double x, double y) {
    sv_seg *sg = sv_new_seg(im, sh);
    if (sg == NULL) return 0;
    sg->verb = SV_LINETO; sg->x[0] = x; sg->y[0] = y;
    return 1;
}

static int sv_seg_cubic(sv_image *im, sv_shape *sh,
                        double x1, double y1, double x2, double y2, double x, double y) {
    sv_seg *sg = sv_new_seg(im, sh);
    if (sg == NULL) return 0;
    sg->verb = SV_CUBIC;
    sg->x[0] = x1; sg->y[0] = y1;
    sg->x[1] = x2; sg->y[1] = y2;
    sg->x[2] = x;  sg->y[2] = y;
    return 1;
}

/* Endpoint-parameterised elliptical arc -> up to 4 cubic segments (F.6.5 of the SVG
 * spec). A degenerate arc (zero radius, coincident endpoints) degrades to a line,
 * which is what the spec itself prescribes. */
static int sv_arc_to_cubics(sv_image *im, sv_shape *sh,
                            double x0, double y0, double rx, double ry,
                            double phi_deg, int large, int sweep,
                            double x, double y) {
    const double PI = 3.14159265358979323846;
    if (rx == 0.0 || ry == 0.0) return sv_seg_line(im, sh, x, y);
    rx = fabs(rx); ry = fabs(ry);
    double phi = phi_deg * PI / 180.0;
    double cp = cos(phi), sp = sin(phi);
    double dx2 = (x0 - x) / 2.0, dy2 = (y0 - y) / 2.0;
    double x1 =  cp * dx2 + sp * dy2;
    double y1 = -sp * dx2 + cp * dy2;
    double rx2 = rx * rx, ry2 = ry * ry, x12 = x1 * x1, y12 = y1 * y1;
    double lam = x12 / rx2 + y12 / ry2;
    if (lam > 1.0) {
        double s = sqrt(lam);
        rx *= s; ry *= s;
        rx2 = rx * rx; ry2 = ry * ry;
    }
    double denom = rx2 * y12 + ry2 * x12;
    if (denom <= 0.0) return sv_seg_line(im, sh, x, y);
    double num = rx2 * ry2 - denom;
    if (num < 0.0) num = 0.0;
    double co = sqrt(num / denom);
    if (large == sweep) co = -co;
    double cx1 =  co * rx * y1 / ry;
    double cy1 = -co * ry * x1 / rx;
    double cx = cp * cx1 - sp * cy1 + (x0 + x) / 2.0;
    double cy = sp * cx1 + cp * cy1 + (y0 + y) / 2.0;

    double ux = (x1 - cx1) / rx, uy = (y1 - cy1) / ry;
    double vx = (-x1 - cx1) / rx, vy = (-y1 - cy1) / ry;
    double n1 = sqrt(ux * ux + uy * uy);
    if (n1 <= 0.0) return sv_seg_line(im, sh, x, y);
    double th1 = acos(ux / n1 > 1.0 ? 1.0 : (ux / n1 < -1.0 ? -1.0 : ux / n1));
    if (uy < 0.0) th1 = -th1;
    double nd = sqrt((ux * ux + uy * uy) * (vx * vx + vy * vy));
    double dth = 0.0;
    if (nd > 0.0) {
        double cosd = (ux * vx + uy * vy) / nd;
        if (cosd > 1.0) cosd = 1.0;
        if (cosd < -1.0) cosd = -1.0;
        dth = acos(cosd);
        if (ux * vy - uy * vx < 0.0) dth = -dth;
    }
    if (!sweep && dth > 0.0) dth -= 2.0 * PI;
    else if (sweep && dth < 0.0) dth += 2.0 * PI;

    int nseg = (int)ceil(fabs(dth) / (PI / 2.0));
    if (nseg < 1) nseg = 1;
    if (nseg > 4) nseg = 4;
    double delta = dth / nseg;
    double t = 4.0 / 3.0 * tan(delta / 4.0);
    double th = th1;
    double px = x0, py = y0;
    for (int k = 0; k < nseg; ++k) {
        double th2 = th + delta;
        double c1 = cos(th), s1 = sin(th), c2 = cos(th2), s2 = sin(th2);
        /* endpoint of this sub-arc, in user space */
        double ex = cx + rx * cp * c2 - ry * sp * s2;
        double ey = cy + rx * sp * c2 + ry * cp * s2;
        /* control points, from the derivative at each end */
        double d1x = -rx * cp * s1 - ry * sp * c1;
        double d1y = -rx * sp * s1 + ry * cp * c1;
        double d2x = -rx * cp * s2 - ry * sp * c2;
        double d2y = -rx * sp * s2 + ry * cp * c2;
        if (!sv_seg_cubic(im, sh, px + t * d1x, py + t * d1y,
                          ex - t * d2x, ey - t * d2y, ex, ey))
            return 0;
        px = ex; py = ey;
        th = th2;
    }
    return 1;
}

/* Parses path data. An unrecognised command ENDS the path with whatever has been
 * accumulated: guessing at a malformed `d` would invent geometry the author never
 * wrote. Every emitter is bounded, so a hostile `d` cannot exhaust the pools. */
static void sv_parse_path(sv_image *im, sv_shape *sh, const char *s, size_t n) {
    sh->first = im->nseg;
    sh->count = 0;
    double cx = 0.0, cy = 0.0;      /* current point */
    double sx = 0.0, sy = 0.0;      /* subpath start */
    double px2 = 0.0, py2 = 0.0;    /* last cubic control point (for S/s) */
    double qx = 0.0, qy = 0.0;      /* last quadratic control point (for T/t) */
    char prev = '\0';
    char cmd = '\0';
    size_t i = 0;
    for (;;) {
        while (i < n && (sv_is_space(s[i]) || s[i] == ',')) ++i;
        if (i >= n) break;
        char c = s[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            cmd = c;
            ++i;
        } else if (cmd == '\0') {
            break;                  /* data before any command */
        } else if (cmd == 'M') {
            cmd = 'L';              /* implicit lineto after a moveto */
        } else if (cmd == 'm') {
            cmd = 'l';
        }
        int rel = (cmd >= 'a' && cmd <= 'z');
        char u = (char)(rel ? cmd - 'a' + 'A' : cmd);
        double a1, a2, a3, a4, a5, a6, a7;
        int ok = 1;
        switch (u) {
            case 'M':
                if (!sv_number(s, n, &i, &a1)) { ok = 0; break; }
                sv_sep(s, n, &i);
                if (!sv_number(s, n, &i, &a2)) { ok = 0; break; }
                cx = rel ? cx + a1 : a1;
                cy = rel ? cy + a2 : a2;
                sx = cx; sy = cy;
                if (!sv_seg_move(im, sh, cx, cy)) return;
                break;
            case 'L':
                if (!sv_number(s, n, &i, &a1)) { ok = 0; break; }
                sv_sep(s, n, &i);
                if (!sv_number(s, n, &i, &a2)) { ok = 0; break; }
                cx = rel ? cx + a1 : a1;
                cy = rel ? cy + a2 : a2;
                if (!sv_seg_line(im, sh, cx, cy)) return;
                break;
            case 'H':
                if (!sv_number(s, n, &i, &a1)) { ok = 0; break; }
                cx = rel ? cx + a1 : a1;
                if (!sv_seg_line(im, sh, cx, cy)) return;
                break;
            case 'V':
                if (!sv_number(s, n, &i, &a1)) { ok = 0; break; }
                cy = rel ? cy + a1 : a1;
                if (!sv_seg_line(im, sh, cx, cy)) return;
                break;
            case 'C':
                if (!sv_number(s, n, &i, &a1)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a2)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a3)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a4)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a5)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a6)) { ok = 0; break; }
                {
                    double c1x = rel ? cx + a1 : a1, c1y = rel ? cy + a2 : a2;
                    double c2x = rel ? cx + a3 : a3, c2y = rel ? cy + a4 : a4;
                    double ex  = rel ? cx + a5 : a5, ey  = rel ? cy + a6 : a6;
                    if (!sv_seg_cubic(im, sh, c1x, c1y, c2x, c2y, ex, ey)) return;
                    px2 = c2x; py2 = c2y; cx = ex; cy = ey;
                }
                break;
            case 'S':
                if (!sv_number(s, n, &i, &a1)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a2)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a3)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a4)) { ok = 0; break; }
                {
                    /* The first control point mirrors the previous one when the
                     * previous command was itself a cubic; otherwise it is the
                     * current point (SVG 8.3.6). */
                    int had = (prev == 'C' || prev == 'c' || prev == 'S' || prev == 's');
                    double c1x = had ? 2.0 * cx - px2 : cx;
                    double c1y = had ? 2.0 * cy - py2 : cy;
                    double c2x = rel ? cx + a1 : a1, c2y = rel ? cy + a2 : a2;
                    double ex  = rel ? cx + a3 : a3, ey  = rel ? cy + a4 : a4;
                    if (!sv_seg_cubic(im, sh, c1x, c1y, c2x, c2y, ex, ey)) return;
                    px2 = c2x; py2 = c2y; cx = ex; cy = ey;
                }
                break;
            case 'Q':
                if (!sv_number(s, n, &i, &a1)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a2)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a3)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a4)) { ok = 0; break; }
                {
                    double qcx = rel ? cx + a1 : a1, qcy = rel ? cy + a2 : a2;
                    double ex  = rel ? cx + a3 : a3, ey  = rel ? cy + a4 : a4;
                    /* Exact degree elevation: a quadratic IS a cubic. */
                    double c1x = cx + 2.0 / 3.0 * (qcx - cx);
                    double c1y = cy + 2.0 / 3.0 * (qcy - cy);
                    double c2x = ex + 2.0 / 3.0 * (qcx - ex);
                    double c2y = ey + 2.0 / 3.0 * (qcy - ey);
                    if (!sv_seg_cubic(im, sh, c1x, c1y, c2x, c2y, ex, ey)) return;
                    qx = qcx; qy = qcy; cx = ex; cy = ey;
                }
                break;
            case 'T':
                if (!sv_number(s, n, &i, &a1)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a2)) { ok = 0; break; }
                {
                    int had = (prev == 'Q' || prev == 'q' || prev == 'T' || prev == 't');
                    double qcx = had ? 2.0 * cx - qx : cx;
                    double qcy = had ? 2.0 * cy - qy : cy;
                    double ex = rel ? cx + a1 : a1, ey = rel ? cy + a2 : a2;
                    double c1x = cx + 2.0 / 3.0 * (qcx - cx);
                    double c1y = cy + 2.0 / 3.0 * (qcy - cy);
                    double c2x = ex + 2.0 / 3.0 * (qcx - ex);
                    double c2y = ey + 2.0 / 3.0 * (qcy - ey);
                    if (!sv_seg_cubic(im, sh, c1x, c1y, c2x, c2y, ex, ey)) return;
                    qx = qcx; qy = qcy; cx = ex; cy = ey;
                }
                break;
            case 'A':
                if (!sv_number(s, n, &i, &a1)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a2)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a3)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a4)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a5)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a6)) { ok = 0; break; }
                sv_sep(s, n, &i); if (!sv_number(s, n, &i, &a7)) { ok = 0; break; }
                {
                    double ex = rel ? cx + a6 : a6, ey = rel ? cy + a7 : a7;
                    if (!sv_arc_to_cubics(im, sh, cx, cy, a1, a2, a3,
                                          a4 != 0.0, a5 != 0.0, ex, ey)) return;
                    cx = ex; cy = ey;
                }
                break;
            case 'Z':
                {
                    sv_seg *sg = sv_new_seg(im, sh);
                    if (sg == NULL) return;
                    sg->verb = SV_CLOSE;
                    cx = sx; cy = sy;
                }
                break;
            default:
                return;   /* unknown command: stop with what we have */
        }
        if (!ok) return;  /* malformed argument list: same fail-closed exit */
        prev = cmd;
    }
}

/* --- element dispatch ----------------------------------------------------- */

/* True for elements whose whole subtree is dropped. <image>/<use>/<foreignObject>
 * can name external resources; <script>/<style> carry code. Dropping the SUBTREE
 * (not just the element) is what keeps a nested <img> or a url() out of reach. */
static int sv_is_dropped_element(const char *name, size_t n) {
    return sv_span_eq(name, n, "image") || sv_span_eq(name, n, "use")
        || sv_span_eq(name, n, "foreignobject") || sv_span_eq(name, n, "script")
        || sv_span_eq(name, n, "style") || sv_span_eq(name, n, "defs")
        || sv_span_eq(name, n, "pattern") || sv_span_eq(name, n, "filter")
        || sv_span_eq(name, n, "mask") || sv_span_eq(name, n, "clippath")
        || sv_span_eq(name, n, "lineargradient") || sv_span_eq(name, n, "radialgradient")
        || sv_span_eq(name, n, "symbol") || sv_span_eq(name, n, "marker");
}

/* Scans the attributes of a tag whose body starts at s[*i] (just past the name).
 * Stops at '>' and reports whether the tag was self-closing. */
static void sv_scan_attrs(const char *s, size_t n, size_t *i,
                          sv_attr *at, size_t *nat, int *self_close) {
    *nat = 0;
    *self_close = 0;
    while (*i < n) {
        while (*i < n && sv_is_space(s[*i])) ++*i;
        if (*i >= n) return;
        if (s[*i] == '>') { ++*i; return; }
        if (s[*i] == '/') {
            *self_close = 1;
            ++*i;
            continue;
        }
        size_t ns = *i;
        while (*i < n && !sv_is_space(s[*i]) && s[*i] != '=' && s[*i] != '>' && s[*i] != '/') ++*i;
        size_t nlen = *i - ns;
        while (*i < n && sv_is_space(s[*i])) ++*i;
        const char *vp = NULL;
        size_t vlen = 0;
        if (*i < n && s[*i] == '=') {
            ++*i;
            while (*i < n && sv_is_space(s[*i])) ++*i;
            if (*i < n && (s[*i] == '"' || s[*i] == '\'')) {
                char q = s[*i];
                ++*i;
                size_t vs = *i;
                while (*i < n && s[*i] != q) ++*i;
                vp = s + vs; vlen = *i - vs;
                if (*i < n) ++*i;
            } else {
                size_t vs = *i;
                while (*i < n && !sv_is_space(s[*i]) && s[*i] != '>') ++*i;
                vp = s + vs; vlen = *i - vs;
            }
        }
        if (nlen > 0 && *nat < SV_MAX_ATTRS) {
            at[*nat].name = s + ns; at[*nat].nlen = nlen;
            at[*nat].val = (vp != NULL) ? vp : "";
            at[*nat].vlen = vlen;
            ++*nat;
        }
    }
}

/* Skips to just past the matching close tag of `name`, honouring nesting. Used to
 * drop a whole disallowed subtree. */
static void sv_skip_subtree(const char *s, size_t n, size_t *i, const char *name, size_t nlen) {
    int depth = 1;
    while (*i < n && depth > 0) {
        if (s[*i] != '<') { ++*i; continue; }
        size_t p = *i + 1;
        int closing = 0;
        if (p < n && s[p] == '/') { closing = 1; ++p; }
        size_t ns = p;
        while (p < n && !sv_is_space(s[p]) && s[p] != '>' && s[p] != '/') ++p;
        int match = sv_span_eq(s + ns, p - ns, "") ? 0 : 0;
        if (p - ns == nlen) {
            match = 1;
            for (size_t k = 0; k < nlen; ++k)
                if (sv_lower(s[ns + k]) != sv_lower(name[k])) { match = 0; break; }
        }
        int selfc = 0;
        while (p < n && s[p] != '>') {
            if (s[p] == '/') selfc = 1;
            else if (!sv_is_space(s[p])) selfc = 0;
            ++p;
        }
        if (p < n) ++p;
        if (match) {
            if (closing) --depth;
            else if (!selfc) ++depth;
        }
        *i = p;
    }
}

/* Collects the literal text of the element that just opened, up to its close tag,
 * into a bounded buffer. Entities are not expanded (v1); markup inside is skipped. */
static void sv_collect_text(const char *s, size_t n, size_t *i, char *dst, size_t cap) {
    size_t o = 0;
    while (*i < n) {
        if (s[*i] == '<') break;
        char c = s[*i];
        if (sv_is_space(c)) c = ' ';
        if (o + 1 < cap) {
            /* collapse whitespace runs, like the HTML text pipeline does */
            if (!(c == ' ' && o > 0 && dst[o - 1] == ' ')) dst[o++] = c;
        }
        ++*i;
    }
    while (o > 0 && dst[o - 1] == ' ') --o;
    dst[o] = '\0';
}

/* --- viewBox / fitting ---------------------------------------------------- */

void sv_fit(const sv_image *img, double dw, double dh,
            double *scale, double *off_x, double *off_y) {
    double sc = 1.0, ox = 0.0, oy = 0.0;
    if (img != NULL) {
        double uw = img->has_viewbox ? img->vb_w : img->width;
        double uh = img->has_viewbox ? img->vb_h : img->height;
        if (uw > 0.0 && uh > 0.0 && dw > 0.0 && dh > 0.0) {
            double sx = dw / uw, sy = dh / uh;
            sc = (sx < sy) ? sx : sy;         /* "meet": the tighter axis wins */
            ox = (dw - uw * sc) / 2.0;        /* xMidYMid: centre the slack */
            oy = (dh - uh * sc) / 2.0;
        }
    }
    if (scale != NULL) *scale = sc;
    if (off_x != NULL) *off_x = ox;
    if (off_y != NULL) *off_y = oy;
}

/* --- entry point ---------------------------------------------------------- */

sv_status sv_parse(const char *markup, size_t len, sv_image *out) {
    return sv_parse_ex(markup, len, out, 0x000000);
}

sv_status sv_parse_ex(const char *markup, size_t len, sv_image *out, int root_fill) {
    if (markup == NULL || out == NULL) return SV_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (len > SV_MAX_INPUT) return SV_ERR_LIMIT;
    /* root_fill seeds the default fill every shape inherits until a fill attribute up
     * its <g> chain overrides it: the CSS `fill` on the <svg> element. A negative
     * value other than currentColor is meaningless as a root default, so it falls back
     * to the SVG default (black) -- sv_parse's own callers pass black. */
    if (root_fill < 0 && root_fill != CC_COLOR_CURRENT) root_fill = 0x000000;

    out->width = 0.0; out->height = 0.0;

    /* The <g> context stack. Explicit, not recursion: a hostile document must not
     * be able to drive the C stack (spec §2, SV_MAX_DEPTH). */
    sv_ctx stack[SV_MAX_DEPTH + 1];
    size_t depth = 0;
    memset(&stack[0], 0, sizeof stack[0]);
    stack[0].fill = root_fill;     /* SVG default fill is black, or the CSS override */
    stack[0].stroke = -1;          /* ...and the default stroke is none */
    stack[0].stroke_w = 1.0;
    stack[0].opacity = 100;
    stack[0].fill_opacity = 100;
    stack[0].stroke_opacity = 100;
    stack[0].font_size = 16.0;
    sv_mat_identity(stack[0].m);

    /* Names of the currently open elements that pushed a context, so a close tag
     * pops exactly the level it opened. */
    const char *open_name[SV_MAX_DEPTH + 1];
    size_t open_nlen[SV_MAX_DEPTH + 1];

    int seen_svg = 0;
    size_t i = 0;
    while (i < len) {
        if (markup[i] != '<') { ++i; continue; }
        size_t p = i + 1;
        if (p < len && (markup[p] == '!' || markup[p] == '?')) {
            /* comment / doctype / PI: skip to the next '>' */
            while (p < len && markup[p] != '>') ++p;
            i = (p < len) ? p + 1 : len;
            continue;
        }
        int closing = 0;
        if (p < len && markup[p] == '/') { closing = 1; ++p; }
        size_t ns = p;
        while (p < len && !sv_is_space(markup[p]) && markup[p] != '>' && markup[p] != '/') ++p;
        size_t nlen = p - ns;
        if (nlen == 0) { i = p + 1; continue; }
        const char *name = markup + ns;

        if (closing) {
            /* Pop the context this element pushed, if it is the one on top. */
            if (depth > 0 && open_nlen[depth] == nlen) {
                int same = 1;
                for (size_t k = 0; k < nlen; ++k)
                    if (sv_lower(open_name[depth][k]) != sv_lower(name[k])) { same = 0; break; }
                if (same) --depth;
            }
            while (p < len && markup[p] != '>') ++p;
            i = (p < len) ? p + 1 : len;
            continue;
        }

        sv_attr at[SV_MAX_ATTRS];
        size_t nat = 0;
        int self_close = 0;
        sv_scan_attrs(markup, len, &p, at, &nat, &self_close);
        i = p;

        if (sv_is_dropped_element(name, nlen)) {
            if (!self_close) sv_skip_subtree(markup, len, &i, name, nlen);
            continue;
        }

        if (sv_span_eq(name, nlen, "svg")) {
            seen_svg = 1;
            size_t vl = 0;
            const char *vb = sv_attr_get(at, nat, "viewbox", &vl);
            if (vb != NULL) {
                size_t k = 0;
                double v[4];
                int got = 0;
                for (; got < 4; ++got) {
                    sv_sep(vb, vl, &k);
                    if (!sv_number(vb, vl, &k, &v[got])) break;
                }
                if (got == 4 && v[2] > 0.0 && v[3] > 0.0) {
                    out->vb_x = v[0]; out->vb_y = v[1];
                    out->vb_w = v[2]; out->vb_h = v[3];
                    out->has_viewbox = 1;
                }
            }
            double w = sv_attr_num(at, nat, "width", 0.0);
            double h = sv_attr_num(at, nat, "height", 0.0);
            if (w > 0.0) out->width = w;
            if (h > 0.0) out->height = h;
            /* A nested <svg> keeps the outer dimensions; only the root sets them. */
            if (depth < SV_MAX_DEPTH) {
                sv_ctx next = stack[depth];
                sv_ctx_from_attrs(&next, at, nat);
                ++depth;
                stack[depth] = next;
                open_name[depth] = name;
                open_nlen[depth] = nlen;
            }
            continue;
        }

        if (!seen_svg) continue;   /* markup outside any <svg> is not ours */

        if (sv_span_eq(name, nlen, "g") || sv_span_eq(name, nlen, "a")
            || sv_span_eq(name, nlen, "switch")) {
            if (!self_close && depth < SV_MAX_DEPTH) {
                sv_ctx next = stack[depth];
                sv_ctx_from_attrs(&next, at, nat);
                ++depth;
                stack[depth] = next;
                open_name[depth] = name;
                open_nlen[depth] = nlen;
            }
            continue;
        }

        sv_ctx ctx = stack[depth];
        sv_ctx_from_attrs(&ctx, at, nat);

        if (sv_span_eq(name, nlen, "rect")) {
            double w = sv_attr_num(at, nat, "width", 0.0);
            double h = sv_attr_num(at, nat, "height", 0.0);
            if (w <= 0.0 || h <= 0.0) continue;
            sv_shape *sh = sv_new_shape(out, SV_RECT, &ctx);
            if (sh == NULL) continue;
            sh->a = sv_attr_num(at, nat, "x", 0.0);
            sh->b = sv_attr_num(at, nat, "y", 0.0);
            sh->c = w; sh->d = h;
            sh->rx = sv_attr_num(at, nat, "rx", 0.0);
            sh->ry = sv_attr_num(at, nat, "ry", sh->rx);
            if (sh->rx <= 0.0) sh->rx = sh->ry;
            if (sh->rx > w / 2.0) sh->rx = w / 2.0;
            if (sh->ry > h / 2.0) sh->ry = h / 2.0;
        } else if (sv_span_eq(name, nlen, "circle")) {
            double r = sv_attr_num(at, nat, "r", 0.0);
            if (r <= 0.0) continue;
            sv_shape *sh = sv_new_shape(out, SV_CIRCLE, &ctx);
            if (sh == NULL) continue;
            sh->a = sv_attr_num(at, nat, "cx", 0.0);
            sh->b = sv_attr_num(at, nat, "cy", 0.0);
            sh->c = r;
        } else if (sv_span_eq(name, nlen, "ellipse")) {
            double rx = sv_attr_num(at, nat, "rx", 0.0);
            double ry = sv_attr_num(at, nat, "ry", 0.0);
            if (rx <= 0.0 || ry <= 0.0) continue;
            sv_shape *sh = sv_new_shape(out, SV_ELLIPSE, &ctx);
            if (sh == NULL) continue;
            sh->a = sv_attr_num(at, nat, "cx", 0.0);
            sh->b = sv_attr_num(at, nat, "cy", 0.0);
            sh->c = rx; sh->d = ry;
        } else if (sv_span_eq(name, nlen, "line")) {
            sv_shape *sh = sv_new_shape(out, SV_LINE, &ctx);
            if (sh == NULL) continue;
            sh->a = sv_attr_num(at, nat, "x1", 0.0);
            sh->b = sv_attr_num(at, nat, "y1", 0.0);
            sh->c = sv_attr_num(at, nat, "x2", 0.0);
            sh->d = sv_attr_num(at, nat, "y2", 0.0);
            /* A line has no interior: only the stroke can paint it. */
            sh->fill = -1;
            if (sh->stroke < 0 && sh->stroke != CC_COLOR_CURRENT) sh->stroke = 0x000000;
        } else if (sv_span_eq(name, nlen, "polyline") || sv_span_eq(name, nlen, "polygon")) {
            size_t vl = 0;
            const char *pts = sv_attr_get(at, nat, "points", &vl);
            if (pts == NULL) continue;
            int is_poly = sv_span_eq(name, nlen, "polygon");
            sv_shape *sh = sv_new_shape(out, is_poly ? SV_POLYGON : SV_POLYLINE, &ctx);
            if (sh == NULL) continue;
            sv_parse_points(out, sh, pts, vl);
            if (sh->count < 2) { --out->nshape; continue; }
            if (!is_poly) sh->fill = -1;   /* an open polyline is stroked, not filled */
        } else if (sv_span_eq(name, nlen, "path")) {
            size_t vl = 0;
            const char *d = sv_attr_get(at, nat, "d", &vl);
            if (d == NULL) continue;
            sv_shape *sh = sv_new_shape(out, SV_PATH, &ctx);
            if (sh == NULL) continue;
            sv_parse_path(out, sh, d, vl);
            if (sh->count == 0) { --out->nshape; continue; }
        } else if (sv_span_eq(name, nlen, "text") || sv_span_eq(name, nlen, "tspan")) {
            sv_shape *sh = sv_new_shape(out, SV_TEXT, &ctx);
            if (sh == NULL) continue;
            sh->a = sv_attr_num(at, nat, "x", 0.0);
            sh->b = sv_attr_num(at, nat, "y", 0.0);
            sh->c = ctx.font_size;
            if (!self_close) sv_collect_text(markup, len, &i, sh->text, sizeof sh->text);
            if (sh->text[0] == '\0') { --out->nshape; continue; }
        }
        /* Any other element: ignored, its children still visited (a <title> or
         * <desc> carries no geometry, and an unknown wrapper must not hide one). */
    }

    if (!seen_svg || out->nshape == 0) {
        memset(out, 0, sizeof *out);
        return SV_ERR_PARSE;
    }

    /* Intrinsic size: explicit width/height, else the viewBox, else the CSS
     * default replaced-element size. */
    if (out->width <= 0.0)
        out->width = out->has_viewbox ? out->vb_w : SV_DEFAULT_W;
    if (out->height <= 0.0)
        out->height = out->has_viewbox ? out->vb_h : SV_DEFAULT_H;
    return SV_OK;
}
