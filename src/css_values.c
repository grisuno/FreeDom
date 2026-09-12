#include "css_values.h"
#include "css.h"
#include "css_color.h"
#include "css_length.h"
#include "css_select.h"

#include <string.h>

static int cv_parse_num(const char *s, double *out, const char **endp)
{
    return cl_number(s, out, endp);
}

static int cv_round_clamp(double v, int lo, int hi)
{
    if (v >= (double)hi) {
        return hi;
    }
    if (v <= (double)lo) {
        return lo;
    }
    return (int)(v + (v < 0.0 ? -0.5 : 0.5));
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
        int is_fn = ((csel_lower_ch(p[0]) == 'r' && csel_lower_ch(p[1]) == 'g' &&
                      csel_lower_ch(p[2]) == 'b' && csel_lower_ch(p[3]) == 'a' && p[4] == '(') ||
                     (csel_lower_ch(p[0]) == 'h' && csel_lower_ch(p[1]) == 's' &&
                      csel_lower_ch(p[2]) == 'l' && csel_lower_ch(p[3]) == 'a' && p[4] == '('));
        if (!is_fn) {
            continue;
        }
        {
            const char *close = strchr(p + 5, ')');
            const char *q;
            const char *a = NULL;
            int commas = 0;
            double num;
            const char *end;
            double pct;
            if (close == NULL) {
                return CSS_LEN_UNSET;
            }
            for (q = p + 5; q < close; ++q) {
                if (*q == ',') {
                    ++commas;
                    if (commas == 3) {
                        a = q + 1;
                        break;
                    }
                }
            }
            if (a == NULL) {
                return CSS_LEN_UNSET;
            }
            while (a < close && (*a == ' ' || *a == '\t')) {
                ++a;
            }
            if (!cv_parse_num(a, &num, &end)) {
                return CSS_LEN_UNSET;
            }
            pct = (*end == '%') ? num : num * 100.0;
            return cv_round_clamp(pct, 0, 100);
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
