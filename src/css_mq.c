/*
 * css_mq -- Media Queries 4 evaluation (spec/css_mq.md).
 *
 * A recursive-descent evaluator over the bounded query text with Kleene logic:
 * every condition is TRUE, FALSE or UNKNOWN (an unknown feature, a malformed
 * condition). `not` keeps UNKNOWN unknown and the top level only matches on TRUE,
 * which is MQ4 section 3.2's "a malformed query is `not all`". Device features
 * answer the normalized desktop identity, never the hardware.
 */
#include "css_mq.h"
#include "css_length.h"

#include <string.h>

enum { MQ_FALSE = 0, MQ_TRUE = 1, MQ_UNKNOWN = -1 };

/* The device the engine claims to be (anti-fingerprinting): never measured. */
#define CMQ_DEVICE_W      1920.0
#define CMQ_DEVICE_H      1080.0
#define CMQ_DPPX          1.0
#define CMQ_COLOR_BITS    8.0
#define CMQ_DPI_PER_DPPX  96.0
#define CMQ_CM_PER_IN     2.54

typedef struct mq_cur {
    const char *s;
    size_t      i, b;
    const cmq_env *env;
} mq_cur;

static char lower_ch(char c) {
    return (c >= 'A' && c <= 'Z') ? (char)(c - 'A' + 'a') : c;
}

static int is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f';
}

static int is_ident_ch(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')
        || c == '-' || c == '_';
}

static void skip_ws(mq_cur *c) {
    while (c->i < c->b && is_space(c->s[c->i])) ++c->i;
}

/* Reads one identifier at the cursor (lowercased into w); 0 if none. */
static int read_word(mq_cur *c, char *w, size_t cap) {
    skip_ws(c);
    size_t n = 0;
    while (c->i < c->b && is_ident_ch(c->s[c->i])) {
        if (n + 1 >= cap) return 0;
        w[n++] = lower_ch(c->s[c->i++]);
    }
    w[n] = '\0';
    return n > 0;
}

/* Peeks the next identifier without consuming it. */
static int peek_word(const mq_cur *c, char *w, size_t cap) {
    mq_cur t = *c;
    return read_word(&t, w, cap);
}

static int and3(int a, int b) {
    if (a == MQ_FALSE || b == MQ_FALSE) return MQ_FALSE;
    if (a == MQ_UNKNOWN || b == MQ_UNKNOWN) return MQ_UNKNOWN;
    return MQ_TRUE;
}

static int or3(int a, int b) {
    if (a == MQ_TRUE || b == MQ_TRUE) return MQ_TRUE;
    if (a == MQ_UNKNOWN || b == MQ_UNKNOWN) return MQ_UNKNOWN;
    return MQ_FALSE;
}

static int not3(int a) {
    return (a == MQ_UNKNOWN) ? MQ_UNKNOWN : !a;
}

/* Copies s[a,b) trimmed and lowercased into dst; 0 when it does not fit. */
static int copy_trim_lower(const char *s, size_t a, size_t b, char *dst, size_t cap) {
    while (a < b && is_space(s[a])) ++a;
    while (b > a && is_space(s[b - 1])) --b;
    if (b - a + 1 > cap) return 0;
    for (size_t k = a; k < b; ++k) dst[k - a] = lower_ch(s[k]);
    dst[b - a] = '\0';
    return 1;
}

/* --- feature values --- */

typedef enum { FV_NONE, FV_NUM, FV_KW } fv_kind;

typedef struct fval {
    fv_kind     kind;
    double      num;    /* FV_NUM: px for lengths, dppx, a ratio or a plain number */
    const char *kw;     /* FV_KW: the keyword the engine answers */
    int         unit;   /* what a value for this feature must be: see VU_* */
} fval;

enum { VU_LENGTH = 1, VU_RATIO, VU_RES, VU_INT };

/* The engine's answer for a feature name (without min-/max- prefix). */
static fval feature_of(const char *name, const cmq_env *env) {
    fval v = { FV_NONE, 0.0, NULL, 0 };
    double w = (double)env->width_px, h = (double)env->height_px;
    if (strcmp(name, "width") == 0)  { v.kind = FV_NUM; v.num = w; v.unit = VU_LENGTH; }
    else if (strcmp(name, "height") == 0) { v.kind = FV_NUM; v.num = h; v.unit = VU_LENGTH; }
    else if (strcmp(name, "device-width") == 0) {
        v.kind = FV_NUM; v.num = CMQ_DEVICE_W; v.unit = VU_LENGTH;
    } else if (strcmp(name, "device-height") == 0) {
        v.kind = FV_NUM; v.num = CMQ_DEVICE_H; v.unit = VU_LENGTH;
    } else if (strcmp(name, "aspect-ratio") == 0) {
        v.kind = FV_NUM; v.num = (h > 0.0) ? w / h : 0.0; v.unit = VU_RATIO;
    } else if (strcmp(name, "device-aspect-ratio") == 0) {
        v.kind = FV_NUM; v.num = CMQ_DEVICE_W / CMQ_DEVICE_H; v.unit = VU_RATIO;
    } else if (strcmp(name, "resolution") == 0) {
        v.kind = FV_NUM; v.num = CMQ_DPPX; v.unit = VU_RES;
    } else if (strcmp(name, "-webkit-device-pixel-ratio") == 0
               || strcmp(name, "device-pixel-ratio") == 0) {
        v.kind = FV_NUM; v.num = CMQ_DPPX; v.unit = VU_INT;
    } else if (strcmp(name, "color") == 0) {
        v.kind = FV_NUM; v.num = CMQ_COLOR_BITS; v.unit = VU_INT;
    } else if (strcmp(name, "color-index") == 0 || strcmp(name, "monochrome") == 0
               || strcmp(name, "grid") == 0) {
        v.kind = FV_NUM; v.num = 0.0; v.unit = VU_INT;
    } else if (strcmp(name, "orientation") == 0) {
        v.kind = FV_KW; v.kw = "landscape";
    } else if (strcmp(name, "prefers-color-scheme") == 0) {
        v.kind = FV_KW; v.kw = env->prefers_dark ? "dark" : "light";
    } else if (strcmp(name, "prefers-reduced-motion") == 0
               || strcmp(name, "prefers-reduced-transparency") == 0
               || strcmp(name, "prefers-reduced-data") == 0
               || strcmp(name, "prefers-contrast") == 0) {
        v.kind = FV_KW; v.kw = "no-preference";
    } else if (strcmp(name, "forced-colors") == 0 || strcmp(name, "inverted-colors") == 0) {
        v.kind = FV_KW; v.kw = "none";
    } else if (strcmp(name, "hover") == 0 || strcmp(name, "any-hover") == 0) {
        v.kind = FV_KW; v.kw = "hover";
    } else if (strcmp(name, "pointer") == 0 || strcmp(name, "any-pointer") == 0) {
        v.kind = FV_KW; v.kw = "fine";
    } else if (strcmp(name, "color-gamut") == 0) {
        v.kind = FV_KW; v.kw = "srgb";
    } else if (strcmp(name, "display-mode") == 0) {
        v.kind = FV_KW; v.kw = "browser";
    } else if (strcmp(name, "update") == 0) {
        v.kind = FV_KW; v.kw = "fast";
    } else if (strcmp(name, "overflow-block") == 0 || strcmp(name, "overflow-inline") == 0) {
        v.kind = FV_KW; v.kw = "scroll";
    } else if (strcmp(name, "dynamic-range") == 0
               || strcmp(name, "video-dynamic-range") == 0) {
        v.kind = FV_KW; v.kw = "standard";
    } else if (strcmp(name, "scan") == 0) {
        v.kind = FV_KW; v.kw = "progressive";
    }
    return v;
}

/* Reads a number (the CSS <number> grammar) from t into *out; *end after it. */
static int read_num(const char *t, double *out, const char **end) {
    return cl_number(t, out, end);
}

/* Parses a value token for a numeric feature into the feature's own scale. */
static int parse_value(const char *t, int unit, double *out) {
    if (unit == VU_LENGTH) {
        cl_ctx ctx = cl_ctx_initial();
        return cl_resolve(t, &ctx, out) == CL_OK;
    }
    const char *e = NULL;
    double n;
    if (!read_num(t, &n, &e)) return 0;
    while (is_space(*e)) ++e;
    if (unit == VU_RATIO) {
        if (*e == '\0') { *out = n; return 1; }
        if (*e != '/') return 0;
        ++e;
        while (is_space(*e)) ++e;
        double d;
        const char *e2 = NULL;
        if (!read_num(e, &d, &e2) || d <= 0.0) return 0;
        while (is_space(*e2)) ++e2;
        if (*e2 != '\0') return 0;
        *out = n / d;
        return 1;
    }
    if (unit == VU_RES) {
        if (strcmp(e, "dppx") == 0 || strcmp(e, "x") == 0) { *out = n; return 1; }
        if (strcmp(e, "dpi") == 0) { *out = n / CMQ_DPI_PER_DPPX; return 1; }
        if (strcmp(e, "dpcm") == 0) {
            *out = n * CMQ_CM_PER_IN / CMQ_DPI_PER_DPPX;
            return 1;
        }
        return 0;
    }
    if (*e != '\0') return 0;
    *out = n;
    return 1;
}

#define MQ_EPS 1e-6

/* op: '<' '<=' '>' '>=' '=' encoded as 1..5. Returns lhs op rhs. */
static int cmp_op(double lhs, int op, double rhs) {
    switch (op) {
        case 1: return lhs < rhs - MQ_EPS;
        case 2: return lhs <= rhs + MQ_EPS;
        case 3: return lhs > rhs + MQ_EPS;
        case 4: return lhs >= rhs - MQ_EPS;
        case 5: return lhs > rhs - MQ_EPS && lhs < rhs + MQ_EPS;
        default: return 0;
    }
}

/* Flips an operator so that `v op name` reads `name op' v`. */
static int flip_op(int op) {
    switch (op) {
        case 1: return 3;
        case 2: return 4;
        case 3: return 1;
        case 4: return 2;
        default: return op;
    }
}

/* Boolean context (MQ4 2.4.2): true unless the value is 0 or `none`. */
static int bool_ctx(const fval *v) {
    if (v->kind == FV_NUM) return v->num != 0.0;
    if (v->kind == FV_KW)
        return strcmp(v->kw, "none") != 0 && strcmp(v->kw, "no-preference") != 0;
    return MQ_UNKNOWN;
}

/* `(name: value)` with the min-/max- prefixes. */
static int eval_plain(const char *name, const char *value, const cmq_env *env) {
    int range = 0;  /* -1 max-, +1 min- */
    const char *base = name;
    if (strncmp(name, "min-", 4) == 0) { range = 1; base = name + 4; }
    else if (strncmp(name, "max-", 4) == 0) { range = -1; base = name + 4; }
    else if (strncmp(name, "-webkit-min-", 12) == 0) { range = 1; base = name + 12; }
    else if (strncmp(name, "-webkit-max-", 12) == 0) { range = -1; base = name + 12; }
    char wk[CMQ_TOK_MAX];
    if (base != name + 4 && base != name && strncmp(name, "-webkit-", 8) == 0) {
        /* -webkit-min-device-pixel-ratio -> device-pixel-ratio */
        size_t bl = strlen(base);
        if (bl + 1 > sizeof wk) return MQ_UNKNOWN;
        memcpy(wk, base, bl + 1);
        base = wk;
    }
    fval f = feature_of(base, env);
    if (f.kind == FV_NONE) return MQ_UNKNOWN;
    if (f.kind == FV_KW) {
        if (range != 0) return MQ_UNKNOWN;
        return strcmp(value, f.kw) == 0;
    }
    double v;
    if (!parse_value(value, f.unit, &v)) return MQ_UNKNOWN;
    if (range > 0) return cmp_op(f.num, 4, v);
    if (range < 0) return cmp_op(f.num, 2, v);
    return cmp_op(f.num, 5, v);
}

/* Reads one comparison operator at *p; returns 1..5 and advances, 0 if none. */
static int read_op(const char **p) {
    const char *q = *p;
    int op = 0;
    if (q[0] == '<' && q[1] == '=') { op = 2; q += 2; }
    else if (q[0] == '>' && q[1] == '=') { op = 4; q += 2; }
    else if (q[0] == '<') { op = 1; q += 1; }
    else if (q[0] == '>') { op = 3; q += 1; }
    else if (q[0] == '=') { op = 5; q += 1; }
    if (op != 0 && (*q == '<' || *q == '>' || *q == '=')) return 0;  /* `>>`, `==` */
    *p = q;
    return op;
}

/* A range feature `(a op b [op c])` (MQ4 2.4.3). t is lowercased and trimmed. */
static int eval_range(const char *t, const cmq_env *env) {
    char part[3][CMQ_TOK_MAX];
    int ops[2] = { 0, 0 };
    int np = 0;
    const char *p = t;
    while (np < 3) {
        while (is_space(*p)) ++p;
        const char *st = p;
        while (*p != '\0' && *p != '<' && *p != '>' && *p != '=') ++p;
        const char *en = p;
        while (en > st && is_space(en[-1])) --en;
        size_t n = (size_t)(en - st);
        if (n == 0 || n + 1 > CMQ_TOK_MAX) return MQ_UNKNOWN;
        memcpy(part[np], st, n);
        part[np][n] = '\0';
        ++np;
        if (*p == '\0') break;
        if (np == 3) return MQ_UNKNOWN;
        int op = read_op(&p);
        if (op == 0) return MQ_UNKNOWN;
        ops[np - 1] = op;
    }
    if (np < 2) return MQ_UNKNOWN;
    if (np == 2) {
        fval f = feature_of(part[0], env);
        int name_left = (f.kind != FV_NONE);
        const char *name = name_left ? part[0] : part[1];
        const char *val  = name_left ? part[1] : part[0];
        if (!name_left) f = feature_of(name, env);
        if (f.kind != FV_NUM) return MQ_UNKNOWN;
        double v;
        if (!parse_value(val, f.unit, &v)) return MQ_UNKNOWN;
        int op = name_left ? ops[0] : flip_op(ops[0]);
        return cmp_op(f.num, op, v);
    }
    /* v1 op name op v2: both operators point the same way (MQ4 grammar). */
    int lt = (ops[0] == 1 || ops[0] == 2) && (ops[1] == 1 || ops[1] == 2);
    int gt = (ops[0] == 3 || ops[0] == 4) && (ops[1] == 3 || ops[1] == 4);
    if (!lt && !gt) return MQ_UNKNOWN;
    fval f = feature_of(part[1], env);
    if (f.kind != FV_NUM) return MQ_UNKNOWN;
    double a, b;
    if (!parse_value(part[0], f.unit, &a) || !parse_value(part[2], f.unit, &b))
        return MQ_UNKNOWN;
    return cmp_op(f.num, flip_op(ops[0]), a) && cmp_op(f.num, ops[1], b);
}

/* The inside of one `( ... )` that is a feature, not a nested condition. */
static int eval_feature(const char *s, size_t a, size_t b, const cmq_env *env) {
    char t[CMQ_TOK_MAX * 2];
    if (!copy_trim_lower(s, a, b, t, sizeof t)) return MQ_UNKNOWN;
    if (t[0] == '\0') return MQ_UNKNOWN;
    char *colon = strchr(t, ':');
    if (colon != NULL) {
        *colon = '\0';
        char name[CMQ_TOK_MAX], value[CMQ_TOK_MAX];
        if (!copy_trim_lower(t, 0, strlen(t), name, sizeof name)) return MQ_UNKNOWN;
        if (!copy_trim_lower(colon + 1, 0, strlen(colon + 1), value, sizeof value))
            return MQ_UNKNOWN;
        if (name[0] == '\0' || value[0] == '\0') return MQ_UNKNOWN;
        return eval_plain(name, value, env);
    }
    if (strpbrk(t, "<>=") != NULL) return eval_range(t, env);
    for (const char *q = t; *q != '\0'; ++q)
        if (!is_ident_ch(*q)) return MQ_UNKNOWN;
    fval f = feature_of(t, env);
    if (f.kind == FV_NONE) return MQ_UNKNOWN;
    return bool_ctx(&f);
}

static int eval_cond(mq_cur *c, int depth);

/* `( condition | feature )` at the cursor. */
static int eval_in_parens(mq_cur *c, int depth) {
    skip_ws(c);
    if (c->i >= c->b || c->s[c->i] != '(') return MQ_UNKNOWN;
    if (depth >= CMQ_MAX_DEPTH) return MQ_UNKNOWN;
    size_t open = c->i;
    int d = 0;
    size_t close = c->b;
    for (size_t k = open; k < c->b; ++k) {
        if (c->s[k] == '(') ++d;
        else if (c->s[k] == ')' && --d == 0) { close = k; break; }
    }
    if (close >= c->b) return MQ_UNKNOWN;
    c->i = close + 1;
    mq_cur in = { c->s, open + 1, close, c->env };
    skip_ws(&in);
    char w[16];
    int nested = (in.i < in.b && in.s[in.i] == '(')
              || (peek_word(&in, w, sizeof w) && strcmp(w, "not") == 0);
    if (nested) {
        int r = eval_cond(&in, depth + 1);
        skip_ws(&in);
        return (in.i == in.b) ? r : MQ_UNKNOWN;
    }
    return eval_feature(c->s, open + 1, close, c->env);
}

/* <media-condition>: `not (x)` | (x) [and (y)]* | (x) [or (y)]*. */
static int eval_cond(mq_cur *c, int depth) {
    if (depth >= CMQ_MAX_DEPTH) return MQ_UNKNOWN;
    char w[16];
    if (peek_word(c, w, sizeof w) && strcmp(w, "not") == 0) {
        (void)read_word(c, w, sizeof w);
        return not3(eval_in_parens(c, depth + 1));
    }
    int r = eval_in_parens(c, depth + 1);
    int mode = 0;  /* 1 and, 2 or */
    for (;;) {
        skip_ws(c);
        if (c->i >= c->b) break;
        mq_cur save = *c;
        if (!read_word(c, w, sizeof w)) { *c = save; break; }
        int m = (strcmp(w, "and") == 0) ? 1 : (strcmp(w, "or") == 0) ? 2 : 0;
        if (m == 0 || (mode != 0 && m != mode)) { *c = save; return MQ_UNKNOWN; }
        mode = m;
        int x = eval_in_parens(c, depth + 1);
        r = (m == 1) ? and3(r, x) : or3(r, x);
    }
    return r;
}

/* One <media-query> of the list, s[a,b). */
static int eval_query(const char *s, size_t a, size_t b, const cmq_env *env) {
    mq_cur c = { s, a, b, env };
    skip_ws(&c);
    if (c.i >= c.b) return MQ_TRUE;  /* empty = all */
    char w[CMQ_TOK_MAX];
    if (c.s[c.i] == '(' ) {
        int r = eval_cond(&c, 0);
        skip_ws(&c);
        return (c.i == c.b) ? r : MQ_UNKNOWN;
    }
    if (!peek_word(&c, w, sizeof w)) return MQ_UNKNOWN;
    if (strcmp(w, "not") == 0) {
        /* `not (cond)` is a condition; `not <type> ...` negates the query. */
        mq_cur t = c;
        (void)read_word(&t, w, sizeof w);
        skip_ws(&t);
        if (t.i < t.b && t.s[t.i] == '(') {
            int r = eval_cond(&c, 0);
            skip_ws(&c);
            return (c.i == c.b) ? r : MQ_UNKNOWN;
        }
    }
    int neg = 0;
    (void)read_word(&c, w, sizeof w);
    if (strcmp(w, "not") == 0) { neg = 1; if (!read_word(&c, w, sizeof w)) return MQ_UNKNOWN; }
    else if (strcmp(w, "only") == 0) { if (!read_word(&c, w, sizeof w)) return MQ_UNKNOWN; }
    int type;
    if (strcmp(w, "all") == 0) type = MQ_TRUE;
    else if (strcmp(w, "screen") == 0) type = env->print ? MQ_FALSE : MQ_TRUE;
    else if (strcmp(w, "print") == 0) type = env->print ? MQ_TRUE : MQ_FALSE;
    else type = MQ_FALSE;  /* an unknown media type matches nothing (MQ4 2.3) */
    int r = type;
    skip_ws(&c);
    if (c.i < c.b) {
        if (!read_word(&c, w, sizeof w) || strcmp(w, "and") != 0) return MQ_UNKNOWN;
        /* <media-condition-without-or>: `or` here is malformed. */
        char nw[16];
        if (peek_word(&c, nw, sizeof nw) && strcmp(nw, "not") == 0) {
            (void)read_word(&c, nw, sizeof nw);
            r = and3(r, not3(eval_in_parens(&c, 1)));
        } else {
            r = and3(r, eval_in_parens(&c, 1));
        }
        for (;;) {
            skip_ws(&c);
            if (c.i >= c.b) break;
            if (!read_word(&c, w, sizeof w) || strcmp(w, "and") != 0) return MQ_UNKNOWN;
            r = and3(r, eval_in_parens(&c, 1));
        }
    }
    if (r == MQ_UNKNOWN) return MQ_UNKNOWN;
    return neg ? !r : r;
}

int cmq_matches(const char *s, size_t len, const cmq_env *env) {
    if (s == NULL || env == NULL) return 0;
    size_t i = 0;
    int any = 0;
    while (i <= len) {
        size_t seg = i;
        int d = 0;
        while (i < len && !(s[i] == ',' && d == 0)) {
            if (s[i] == '(') ++d;
            else if (s[i] == ')') --d;
            ++i;
        }
        if (eval_query(s, seg, i, env) == MQ_TRUE) return 1;
        any = 1;
        if (i >= len) break;
        ++i;
    }
    return !any;
}
