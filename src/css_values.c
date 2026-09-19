#include "css_values.h"
#include "css.h"
#include "css_decl.h"
#include "css_color.h"
#include "css_length.h"
#include "css_select.h"

#include <string.h>

static int cv_parse_num(const char *s, double *out, const char **endp)
{
    return cl_number(s, out, endp);
}

int cv_parse_color(const char *v)
{
    cc_rgb c;
    cc_status st;
    if (v == NULL) {
        return -1;
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

int cv_interp_color(const char *v)
{
    return cv_parse_color(v);
}

int cv_color_ok(int c)
{
    return c != -1;
}

int cv_bg_alpha_of(const char *v)
{
    const char *p;
    if (v == NULL) {
        return CSS_LEN_UNSET;
    }
    for (p = v; *p != '\0'; ++p) {
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
        int is_fn = is_rgba || is_rgb || is_hsla || is_hsl;
        if (!is_fn) {
            continue;
        }
        {
            const char *open = strchr(p, '(');
            const char *close = (open != NULL) ? strchr(open + 1, ')') : NULL;
            const char *q;
            const char *a = NULL;
            int commas = 0;
            int depth = 0;
            double num;
            const char *end;
            double pct;
            if (open == NULL || close == NULL) {
                return CSS_LEN_UNSET;
            }
            /* Modern slash alpha first: a single top-level '/' names what
             * follows it, on any of the four function names. */
            for (q = open + 1; q < close; ++q) {
                if (*q == '(') ++depth;
                else if (*q == ')') --depth;
                else if (*q == '/' && depth == 0) {
                    if (a != NULL) return CSS_LEN_UNSET;  /* second slash */
                    a = q + 1;
                }
            }
            if (depth != 0) {
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
            }
            pct = (*end == '%') ? num : num * 100.0;
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
