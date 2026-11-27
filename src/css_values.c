#include "css_values.h"
#include "css.h"
#include "css_decl.h"
#include "css_color.h"
#include "css_length.h"
#include "css_select.h"

#include <ctype.h>
#include <string.h>

static int cv_parse_num(const char *s, double *out, const char **endp)
{
    return cl_number(s, out, endp);
}

static int mix_color(const char *v, int depth);

#define CV_LD_MAX 256

/* light-dark(<light>, <dark>) (CSS Color 5 section 6) at v: copies the LIGHT argument,
 * trimmed, into buf. This engine renders the light scheme (prefers-color-scheme is light),
 * so that branch is the used colour. *end gets the byte after the closing parenthesis.
 * 0 = not exactly two top-level arguments, unbalanced, or too long (fail closed). */
static int light_dark_arg(const char *v, char *buf, size_t cap, const char **end)
{
    const char *open = strchr(v, '(');
    if (open == NULL) return 0;
    const char *comma = NULL, *q = open + 1;
    int d = 1, commas = 0;
    for (; *q != '\0' && d > 0; ++q) {
        if (*q == '(') ++d;
        else if (*q == ')') --d;
        else if (*q == ',' && d == 1) { if (++commas == 1) comma = q; }
    }
    if (d != 0 || commas != 1) return 0;
    const char *a = open + 1, *b = comma;
    while (a < b && (*a == ' ' || *a == '\t')) ++a;
    while (b > a && (b[-1] == ' ' || b[-1] == '\t')) --b;
    size_t n = (size_t)(b - a);
    if (n == 0 || n >= cap) return 0;
    memcpy(buf, a, n);
    buf[n] = '\0';
    if (end != NULL) *end = q;
    return 1;
}

static int is_light_dark(const char *v)
{
    static const char name[] = "light-dark(";
    for (size_t k = 0; k + 1 < sizeof name; ++k)
        if (csel_lower_ch(v[k]) != name[k]) return 0;
    return 1;
}

static int parse_color_depth(const char *v, int depth)
{
    cc_rgb c;
    cc_status st;
    if (v == NULL) {
        return -1;
    }
    while (*v == ' ' || *v == '\t') ++v;
    if (strncmp(v, "color-mix(", 10) == 0 || strncmp(v, "COLOR-MIX(", 10) == 0) {
        return mix_color(v, depth);
    }
    if (is_light_dark(v)) {
        char arg[CV_LD_MAX];
        const char *end = NULL;
        if (depth > 8 || !light_dark_arg(v, arg, sizeof arg, &end)) return -1;
        while (*end == ' ' || *end == '\t') ++end;
        if (*end != '\0') return -1;
        return parse_color_depth(arg, depth + 1);
    }
    st = cc_parse(v, &c);
    if (st == CC_OK) {
        return cc_pack(c);
    }
    if (st == CC_CURRENT_COLOR) {
        return CC_COLOR_CURRENT;
    }
    if (st == CC_TRANSPARENT) {
        return CC_COLOR_TRANSPARENT;
    }
    return -1;
}

int cv_parse_color(const char *v)
{
    return parse_color_depth(v, 0);
}

int cv_interp_color(const char *v)
{
    return cv_parse_color(v);
}

int cv_color_ok(int c)
{
    return c != -1;
}

static int alpha_of_depth(const char *v, int depth);

/* One color-mix() argument `[<pct>] <color> [<pct>]` in s[0,n): its percentage (-1 when
 * absent) and its alpha in percent (transparent = 0, an opaque color = 100). 0 = malformed. */
static int mix_arg(const char *s, size_t n, double *pct, double *alpha, int *rgb, int depth)
{
    char buf[CSS_TOK_MAX];
    while (n > 0 && (s[0] == ' ' || s[0] == '\t')) { ++s; --n; }
    while (n > 0 && (s[n - 1] == ' ' || s[n - 1] == '\t')) --n;
    if (n == 0 || n >= sizeof buf) return 0;
    memcpy(buf, s, n);
    buf[n] = '\0';
    *pct = -1.0;
    char *col = buf;
    size_t len = n;
    /* trailing `NN%` */
    char *sp = strrchr(col, ' ');
    if (sp != NULL && len > 1 && col[len - 1] == '%') {
        double num;
        const char *end;
        if (cv_parse_num(sp + 1, &num, &end) && *end == '%' && end[1] == '\0') {
            *pct = num;
            *sp = '\0';
        }
    } else if (isdigit((unsigned char)col[0]) || col[0] == '.') {
        double num;
        const char *end;
        if (cv_parse_num(col, &num, &end) && *end == '%') {
            *pct = num;
            col = (char *)end + 1;
        }
    }
    while (*col == ' ' || *col == '\t') ++col;
    size_t cl = strlen(col);
    while (cl > 0 && (col[cl - 1] == ' ' || col[cl - 1] == '\t')) col[--cl] = '\0';
    if (cl == 0 || (*pct != -1.0 && (*pct < 0.0 || *pct > 100.0))) return 0;
    if (strlen(col) == 11 && csel_span_eq(col, "transparent", 11, 1)) {
        *alpha = 0.0;
        *rgb = 0;
        return 1;
    }
    *rgb = parse_color_depth(col, depth + 1);
    if (*rgb < 0 && *rgb != CC_COLOR_TRANSPARENT) return 0;   /* currentColor/junk: unmixable */
    if (*rgb == CC_COLOR_TRANSPARENT) { *alpha = 0.0; *rgb = 0; return 1; }
    int a = alpha_of_depth(col, depth + 1);
    *alpha = (a == CSS_LEN_UNSET) ? 100.0 : (double)a;
    return 1;
}

/* color-mix(in <space>, c1 [p1], c2 [p2]) (CSS Color 5 §2): percentages normalised to 100,
 * a sum under 100 scales the alpha; premultiplied, so mixing with `transparent` keeps the
 * other color's channels. The space is accepted and the mix is done in sRGB (approximation,
 * spec/css_color.md). v points at "color-mix(". 0 = malformed. */
static int mix_solve(const char *v, int depth, int *rgb_out, double *alpha_out)
{
    if (depth > 8) return 0;
    const char *open = strchr(v, '(');
    if (open == NULL) return 0;
    const char *close = open + 1;
    int d = 1;
    while (*close != '\0' && d > 0) {
        if (*close == '(') ++d;
        else if (*close == ')') --d;
        if (d > 0) ++close;
    }
    if (d != 0) return 0;
    const char *seg[3];
    size_t segn[3];
    int ns = 0;
    d = 0;
    const char *a = open + 1;
    for (const char *q = open + 1; q <= close; ++q) {
        if (q < close && *q == '(') ++d;
        else if (q < close && *q == ')') --d;
        else if (q == close || (*q == ',' && d == 0)) {
            if (ns == 3) return 0;
            seg[ns] = a;
            segn[ns++] = (size_t)(q - a);
            a = q + 1;
        }
    }
    if (ns != 3) return 0;
    {
        const char *in = seg[0];
        size_t n = segn[0];
        while (n > 0 && (*in == ' ' || *in == '\t')) { ++in; --n; }
        if (n < 3 || csel_lower_ch(in[0]) != 'i' || csel_lower_ch(in[1]) != 'n' ||
            (in[2] != ' ' && in[2] != '\t'))
            return 0;
    }
    double p1, p2, a1, a2;
    int c1, c2;
    if (!mix_arg(seg[1], segn[1], &p1, &a1, &c1, depth) ||
        !mix_arg(seg[2], segn[2], &p2, &a2, &c2, depth))
        return 0;
    if (p1 < 0.0 && p2 < 0.0) { p1 = 50.0; p2 = 50.0; }
    else if (p1 < 0.0) p1 = 100.0 - p2;
    else if (p2 < 0.0) p2 = 100.0 - p1;
    double sum = p1 + p2;
    if (!(sum > 0.0)) return 0;
    double w1 = a1 * p1, w2 = a2 * p2, wt = w1 + w2;
    double mult = sum < 100.0 ? sum / 100.0 : 1.0;
    *alpha_out = wt / sum * mult;
    if (wt <= 0.0) { *rgb_out = 0; return 1; }
    int ch[3];
    for (int k = 0; k < 3; ++k) {
        int sh = 16 - 8 * k;
        double v1 = (double)((c1 >> sh) & 0xff), v2 = (double)((c2 >> sh) & 0xff);
        ch[k] = css_round_clamp((v1 * w1 + v2 * w2) / wt, 0, 255);
    }
    *rgb_out = (ch[0] << 16) | (ch[1] << 8) | ch[2];
    return 1;
}

static int mix_color(const char *v, int depth)
{
    int rgb;
    double alpha;
    if (!mix_solve(v, depth, &rgb, &alpha)) return -1;
    return rgb;
}

static int mix_alpha(const char *v, int depth)
{
    int rgb;
    double alpha;
    if (!mix_solve(v, depth, &rgb, &alpha)) return CSS_LEN_UNSET;
    int r = css_round_clamp(alpha, 0, 100);
    return r >= 100 ? CSS_LEN_UNSET : r;
}

/* Whether the identifier `name` (lowercase) starts at p and is followed by '(' and does not
 * continue a longer identifier (so `lab(` is not found inside `oklab(`). */
static int fn_at(const char *v, const char *p, const char *name)
{
    if (p > v && (csel_ident_ch(p[-1]))) return 0;
    size_t n = strlen(name);
    for (size_t k = 0; k < n; ++k)
        if (csel_lower_ch(p[k]) != name[k]) return 0;
    return p[n] == '(';
}

int cv_bg_alpha_of(const char *v)
{
    return alpha_of_depth(v, 0);
}

static int alpha_of_depth(const char *v, int depth)
{
    const char *p;
    if (v == NULL || depth > 8) {
        return CSS_LEN_UNSET;
    }
    for (p = v; *p != '\0'; ++p) {
        if (fn_at(v, p, "color-mix")) {
            return mix_alpha(p, depth);
        }
        if (fn_at(v, p, "light-dark")) {
            char arg[CV_LD_MAX];
            if (!light_dark_arg(p, arg, sizeof arg, NULL)) return CSS_LEN_UNSET;
            return alpha_of_depth(arg, depth + 1);
        }
        /* #RGBA / #RRGGBBAA (CSS Color 4 section 5.2): a hex token standing on
         * its own (start or after a space/comma -- never `url(#id)`). */
        if (*p == '#' && (p == v || p[-1] == ' ' || p[-1] == '\t' || p[-1] == ',')) {
            size_t nd = 0;
            while (nd < 9 && isxdigit((unsigned char)p[1 + nd])) ++nd;
            char after = p[1 + nd];
            if ((nd == 4 || nd == 8)
                && (after == '\0' || after == ' ' || after == '\t' || after == ',')) {
                int a;
                if (nd == 4) {
                    char h = p[4];
                    a = isdigit((unsigned char)h) ? h - '0' : (csel_lower_ch(h) - 'a' + 10);
                    return (int)((double)a * 100.0 / 15.0 + 0.5);
                }
                char h1 = p[7], h2 = p[8];
                int d1 = isdigit((unsigned char)h1) ? h1 - '0' : (csel_lower_ch(h1) - 'a' + 10);
                int d2 = isdigit((unsigned char)h2) ? h2 - '0' : (csel_lower_ch(h2) - 'a' + 10);
                a = d1 * 16 + d2;
                return (int)((double)a * 100.0 / 255.0 + 0.5);
            }
        }
        int is_rgba = (csel_lower_ch(p[0]) == 'r' && csel_lower_ch(p[1]) == 'g' &&
                       csel_lower_ch(p[2]) == 'b' && csel_lower_ch(p[3]) == 'a' && p[4] == '(');
        int is_rgb = !is_rgba && csel_lower_ch(p[0]) == 'r' && csel_lower_ch(p[1]) == 'g' &&
                     csel_lower_ch(p[2]) == 'b' && p[3] == '(';
        int is_hsla = (csel_lower_ch(p[0]) == 'h' && csel_lower_ch(p[1]) == 's' &&
                       csel_lower_ch(p[2]) == 'l' && csel_lower_ch(p[3]) == 'a' && p[4] == '(');
        int is_hsl = !is_hsla && csel_lower_ch(p[0]) == 'h' && csel_lower_ch(p[1]) == 's' &&
                     csel_lower_ch(p[2]) == 'l' && p[3] == '(';
        /* CSS Color 4 made rgb()/rgba() (hsl()/hsla()) aliases: the slash form
         * rides on any of the four names, so all four are probed, not just the
         * legacy alias pair. */
        /* CSS Color 4: the other color functions only take the slash form. */
        int is_modern = fn_at(v, p, "oklab") || fn_at(v, p, "oklch") || fn_at(v, p, "lab") ||
                        fn_at(v, p, "lch") || fn_at(v, p, "hwb") || fn_at(v, p, "color");
        int is_fn = is_rgba || is_rgb || is_hsla || is_hsl || is_modern;
        if (!is_fn) {
            continue;
        }
        {
            const char *open = strchr(p, '(');
            const char *close = (open != NULL) ? strchr(open + 1, ')') : NULL;
            const char *q;
            const char *a = NULL;
            int commas = 0;
            int pdepth = 0;
            double num;
            const char *end;
            double pct;
            if (open == NULL || close == NULL) {
                return CSS_LEN_UNSET;
            }
            /* Modern slash alpha first: a single top-level '/' names what
             * follows it, on any of the four function names. */
            for (q = open + 1; q < close; ++q) {
                if (*q == '(') ++pdepth;
                else if (*q == ')') --pdepth;
                else if (*q == '/' && pdepth == 0) {
                    if (a != NULL) return CSS_LEN_UNSET;  /* second slash */
                    a = q + 1;
                }
            }
            if (pdepth != 0) {
                return CSS_LEN_UNSET;
            }
            if (a == NULL) {
                /* Legacy comma alpha: only the alias names ever carried it,
                 * and only as the 4th component. */
                if (!is_rgba && !is_hsla) {
                    continue;
                }
                for (q = open + 1; q < close; ++q) {
                    if (*q == ',') {
                        ++commas;
                        if (commas == 3) {
                            a = q + 1;
                            break;
                        }
                    }
                }
                if (a == NULL) {
                    continue;
                }
            }
            while (a < close && (*a == ' ' || *a == '\t')) {
                ++a;
            }
            {
                const char *ae = close;
                while (ae > a && (ae[-1] == ' ' || ae[-1] == '\t')) --ae;
                char abuf[CSS_TOK_MAX];
                size_t alen = (size_t)(ae - a);
                if (alen == 0 || alen >= sizeof abuf) return CSS_LEN_UNSET;
                memcpy(abuf, a, alen);
                abuf[alen] = '\0';
                if (!cv_parse_num(abuf, &num, &end)) {
                    return CSS_LEN_UNSET;
                }
                if (*end != '\0' && !(*end == '%' && end[1] == '\0')) {
                    return CSS_LEN_UNSET;
                }
                /* `end` points into abuf: read it before abuf leaves scope. */
                pct = (*end == '%') ? num : num * 100.0;
            }
            return css_round_clamp(pct, 0, 100);
        }
    }
    return CSS_LEN_UNSET;
}

int cv_interp_bg(const char *v)
{
    int result;
    const char *p;
    char tok[CSS_TOK_MAX];
    if (v == NULL) {
        return -1;
    }
    result = cv_parse_color(v);
    if (result != -1) {
        return result;
    }
    p = v;
    while (*p != '\0') {
        size_t k = 0;
        while (*p == ' ' || *p == '\t') {
            ++p;
        }
        if (*p == '\0') {
            break;
        }
        if ((p[0] == 'u' || p[0] == 'U') && (p[1] == 'r' || p[1] == 'R') &&
            (p[2] == 'l' || p[2] == 'L') && p[3] == '(') {
            while (*p != '\0' && *p != ')') {
                ++p;
            }
            if (*p == ')') {
                ++p;
            }
            continue;
        }
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) {
            tok[k++] = *p++;
        }
        tok[k] = '\0';
        {
            int tok_col = cv_parse_color(tok);
            if (tok_col != -1) {
                return tok_col;
            }
        }
    }
    return -1;
}

int cv_parse_color_t7(const char *v)
{
    int cv = cv_parse_color(v);
    if (cv < 0) {
        return cv;
    }
    int sa = cv_bg_alpha_of(v);   /* percent, or CSS_LEN_UNSET */
    if (sa != CSS_LEN_UNSET && sa < 100) {
        if (sa < 0) {
            sa = 0;
        }
        int t7 = (int)((double)(100 - sa) * 127.0 / 100.0 + 0.5);
        cv = (cv & 0xffffff) | (t7 << 24);
    }
    return cv;
}

int cv_text_color(const char *v)
{
    int c = cv_parse_color_t7(v);
    if (c == CC_COLOR_TRANSPARENT) {
        return 127 << 24;
    }
    return c;
}

double cv_filter_scale(int pct) {
    if (pct <= 0 || pct == 100) return 1.0;
    return (double)pct / 100.0;
}
