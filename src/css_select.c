/*
 * css_select — selector engine of the author-CSS module. See include/css_select.h,
 * spec/css_select.md.
 *
 * Hostile content: bounded (compounds/attrs/token caps), fails closed (anything
 * unsupported drops the whole selector), pure (no allocation, no I/O).
 */

#include "css_select.h"

/* For :has() pseudo-class: descendant DOM traversal via el->dom_node. */
#include <lexbor/html/html.h>
#include <string.h>

/* CSS Syntax 4.3.7 escape consumption (moved from css.c; shared by quoted
 * content values and selector identifiers). Backslash +
 * 1-6 hex digits (then one optional whitespace, eaten as the terminator) is the
 * codepoint, emitted UTF-8; backslash + newline eats both (continuation);
 * backslash + anything else is that char; a trailing backslash is dropped. Null,
 * surrogates and > U+10FFFF become U+FFFD. Decoded output only ever shrinks,
 * except \0-like escapes (2 chars -> 3 bytes), so the write is capped and a
 * hostile value truncates instead of overflowing. */
int csel_hex_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

size_t csel_emit_utf8(unsigned int cp, char *out) {
    if (cp == 0 || (cp >= 0xD800 && cp <= 0xDFFF) || cp > 0x10FFFF)
        cp = 0xFFFD;
    if (cp < 0x80) { out[0] = (char)cp; return 1; }
    if (cp < 0x800) {
        out[0] = (char)(0xC0 | (cp >> 6));
        out[1] = (char)(0x80 | (cp & 0x3F));
        return 2;
    }
    if (cp < 0x10000) {
        out[0] = (char)(0xE0 | (cp >> 12));
        out[1] = (char)(0x80 | ((cp >> 6) & 0x3F));
        out[2] = (char)(0x80 | (cp & 0x3F));
        return 3;
    }
    out[0] = (char)(0xF0 | (cp >> 18));
    out[1] = (char)(0x80 | ((cp >> 12) & 0x3F));
    out[2] = (char)(0x80 | ((cp >> 6) & 0x3F));
    out[3] = (char)(0x80 | (cp & 0x3F));
    return 4;
}

void csel_unescape(char *dst, size_t cap, const char *src, size_t n) {
    size_t o = 0, i = 0;
    while (i < n && o + 1 < cap) {
        if (src[i] != '\\' || i + 1 >= n) {
            if (src[i] == '\\') break; /* trailing backslash: dropped */
            dst[o++] = src[i++];
            continue;
        }
        char nx = src[i + 1];
        if (nx == '\n') { i += 2; continue; }
        if (nx == '\r') { i += 2; if (i < n && src[i] == '\n') ++i; continue; }
        int hv = csel_hex_val(nx);
        if (hv < 0) {
            if (o + 1 >= cap) break;
            dst[o++] = nx;
            i += 2;
            continue;
        }
        unsigned int cp = 0;
        size_t k = 0;
        while (k < 6 && i + 1 + k < n && csel_hex_val(src[i + 1 + k]) >= 0) {
            cp = cp * 16u + (unsigned int)csel_hex_val(src[i + 1 + k]);
            ++k;
        }
        i += 1 + k;
        if (i < n && (src[i] == ' ' || src[i] == '\t')) ++i;
        else if (i < n && src[i] == '\n') ++i;
        else if (i + 1 < n && src[i] == '\r' && src[i + 1] == '\n') i += 2;
        else if (i < n && src[i] == '\r') ++i;
        char enc[4];
        size_t elen = csel_emit_utf8(cp, enc);
        if (o + elen >= cap) break;
        memcpy(dst + o, enc, elen);
        o += elen;
    }
    dst[o] = '\0';
}


size_t csel_escape_len(const char *s, size_t i, size_t b) {
    if (i >= b || s[i] != '\\') return 0;
    if (i + 1 >= b || s[i + 1] == '\n' || s[i + 1] == '\r' || s[i + 1] == '\f') return 0;
    size_t k = i + 1;
    if (csel_hex_val(s[k]) < 0) return 2;
    size_t h = 0;
    while (h < 6 && k < b && csel_hex_val(s[k]) >= 0) { ++k; ++h; }
    if (k + 1 < b && s[k] == '\r' && s[k + 1] == '\n') k += 2;
    else if (k < b && (s[k] == ' ' || s[k] == '\t' || s[k] == '\n' || s[k] == '\r' ||
                       s[k] == '\f')) ++k;
    return k - i;
}

size_t csel_decl_end(const char *s, size_t i, size_t b, int stop_brace) {
    int depth = 0;
    char q = 0;
    for (; i < b; ++i) {
        char c = s[i];
        if (c == '\\' && i + 1 < b) { ++i; continue; }
        if (q) { if (c == q) q = 0; continue; }
        if (c == '"' || c == '\'') q = c;
        else if (c == '(') ++depth;
        else if (c == ')') { if (depth > 0) --depth; }
        else if (depth == 0 && (c == ';' || (stop_brace && c == '}'))) return i;
    }
    return b;
}

/* 64-bit FNV-1a of the whole identifier: what makes a folded long name exact up to
 * a hash collision -- and a collision only lets a page style its own elements. */
static unsigned long long ident_hash(const char *s, size_t n) {
    unsigned long long h = 1469598103934665603ull;
    for (size_t i = 0; i < n; ++i) { h ^= (unsigned char)s[i]; h *= 1099511628211ull; }
    return h;
}

void csel_ident_fold(const char *src, size_t len, char *dst) {
    static const char hex[] = "0123456789abcdef";
    if (len < CSS_TOK_MAX) {
        memcpy(dst, src, len);
        dst[len] = '\0';
        return;
    }
    memcpy(dst, src, CSEL_FOLD_PREFIX);
    size_t o = CSEL_FOLD_PREFIX;
    dst[o++] = CSEL_FOLD_MARK;
    unsigned long long h = ident_hash(src, len);
    for (int k = 15; k >= 0; --k) dst[o++] = hex[(h >> (4 * k)) & 0xFu];
    dst[o] = '\0';
}

int csel_ident_eq(const char *stored, const char *tok, size_t tlen) {
    if (stored == NULL || tok == NULL) return 0;
    if (tlen < CSS_TOK_MAX) return strlen(stored) == tlen && memcmp(stored, tok, tlen) == 0;
    char f[CSS_TOK_MAX];
    csel_ident_fold(tok, tlen, f);
    return strcmp(stored, f) == 0;
}

int csel_read_ident(const char *s, size_t *ip, size_t b, char *dst, int lower) {
    size_t i = *ip;
    size_t a = i;
    while (i < b) {
        size_t el = csel_escape_len(s, i, b);
        if (el > 0) { i += el; continue; }
        if (csel_ident_ch(s[i]) || (unsigned char)s[i] >= 0x80) { ++i; continue; }
        break;
    }
    if (i == a) return 0;
    char buf[CSEL_IDENT_SCRATCH];
    size_t n;
    if (memchr(s + a, '\\', i - a) != NULL) {
        csel_unescape(buf, sizeof buf, s + a, i - a);
        n = strlen(buf);
    } else {
        n = i - a;
        if (n >= sizeof buf) n = sizeof buf - 1;
        memcpy(buf, s + a, n);
        buf[n] = '\0';
    }
    if (n == 0) return 0;
    if (lower) for (size_t k = 0; k < n; ++k) buf[k] = csel_lower_ch(buf[k]);
    csel_ident_fold(buf, n, dst);
    *ip = i;
    return 1;
}


/* Parses one attribute selector starting at s[*ip] == '[' (within s[.,b)) into *am.
 * Advances *ip past the closing ']'. Returns 1 if supported, 0 (fail closed) on any
 * malformation (no name, unknown operator, unterminated). Grammar:
 *   '[' ws name ws ( ']' | op '=' ws value ws (i|s)? ws ']' )
 * value may be quoted (single/double; quotes stripped, may contain whitespace). */
static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am) {
    size_t i = *ip + 1;  /* past '[' */
    memset(am, 0, sizeof *am);
    while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;

    size_t k = 0;
    while (i < b && csel_ident_ch(s[i])) {
        if (k + 1 < CSS_TOK_MAX) am->name[k++] = csel_lower_ch(s[i]);
        ++i;
    }
    am->name[k] = '\0';
    if (k == 0) return 0;  /* no attribute name */
    while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;

    if (i < b && s[i] == ']') { am->op = ATTR_PRESENT; *ip = i + 1; return 1; }

    if (i < b && s[i] == '=') { am->op = ATTR_EQ; ++i; }
    else if (i + 1 < b && s[i + 1] == '=') {
        switch (s[i]) {
            case '~': am->op = ATTR_TILDE;  break;
            case '|': am->op = ATTR_PIPE;   break;
            case '^': am->op = ATTR_CARET;  break;
            case '$': am->op = ATTR_DOLLAR; break;
            case '*': am->op = ATTR_STAR;   break;
            default:  return 0;            /* unknown operator */
        }
        i += 2;
    } else {
        return 0;
    }

    while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;
    char q = 0;
    if (i < b && (s[i] == '"' || s[i] == '\'')) { q = s[i]; ++i; }
    size_t vk = 0;
    while (i < b) {
        char ch = s[i];
        if (q) { if (ch == q) { ++i; break; } }
        else if (ch == ']' || ch == ' ' || ch == '\t') break;
        if (vk + 1 < CSS_TOK_MAX) am->value[vk++] = ch;
        ++i;
    }
    am->value[vk] = '\0';

    while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;
    if (i < b && (s[i] == 'i' || s[i] == 'I')) { am->ci = 1; ++i; }
    else if (i < b && (s[i] == 's' || s[i] == 'S')) { am->ci = 0; ++i; }
    while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;
    if (i >= b || s[i] != ']') return 0;   /* unterminated attribute selector */
    *ip = i + 1;
    return 1;
}

/* Parses the An+B argument of the nth-child family, s[a,b) (surrounding space
 * trimmed here). Accepts odd/even, N, An, An+B, An-B, n, -n+B, +n... (spaces
 * around the +/- of the B part allowed, case-insensitive n). |A| and |B| are
 * bounded by CSS_NTH_MAX; anything else fails (drops the selector). */
static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B) {
    while (a < b && (s[a] == ' ' || s[a] == '\t')) ++a;
    while (b > a && (s[b-1] == ' ' || s[b-1] == '\t')) --b;
    if (a >= b) return 0;

    if (b - a == 3 && csel_span_eq(s + a, "odd", 3, 1))  { *A = 2; *B = 1; return 1; }
    if (b - a == 4 && csel_span_eq(s + a, "even", 4, 1)) { *A = 2; *B = 0; return 1; }

    size_t i = a;
    int sign1 = 1;
    if (s[i] == '+' || s[i] == '-') { sign1 = (s[i] == '-') ? -1 : 1; ++i; }
    long v1 = 0;
    int digits1 = 0;
    while (i < b && s[i] >= '0' && s[i] <= '9') {
        v1 = v1 * 10 + (s[i] - '0');
        if (v1 > CSS_NTH_MAX) return 0;
        digits1 = 1;
        ++i;
    }

    if (i < b && (s[i] == 'n' || s[i] == 'N')) {
        ++i;
        *A = sign1 * (int)(digits1 ? v1 : 1);
        while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;
        if (i >= b) { *B = 0; return 1; }
        int sign2;
        if (s[i] == '+') sign2 = 1;
        else if (s[i] == '-') sign2 = -1;
        else return 0;
        ++i;
        while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;
        long v2 = 0;
        int digits2 = 0;
        while (i < b && s[i] >= '0' && s[i] <= '9') {
            v2 = v2 * 10 + (s[i] - '0');
            if (v2 > CSS_NTH_MAX) return 0;
            digits2 = 1;
            ++i;
        }
        if (!digits2 || i < b) return 0;
        *B = sign2 * (int)v2;
        return 1;
    }

    if (!digits1 || i < b) return 0;   /* bare number only */
    *A = 0;
    *B = sign1 * (int)v1;
    return 1;
}

/* Forward declaration for parse_pseudo sub-selector parsing. */
static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub);
static int take_sub_arg(const char *s, size_t a, size_t b, css_sel *sel, int strict);

/* Parses one pseudo-class starting at s[*ip] == ':' (within s[.,b)) into *pm.
 * Advances *ip past it (including a (arg) for the nth-child family). Returns 1
 * if supported, 0 (fail closed) otherwise — unknown names, functional pseudos
 * other than nth-child/nth-last-child, and pseudo-ELEMENTS other than
 * ::before/::after (including the legacy single-colon :first-line/:first-letter,
 * which have no first-line model here) drop the whole selector. Single-colon
 * :before/:after are the CSS 2.1 §5.12.3 legacy spelling of the pseudo-elements
 * and match exactly like the double-colon form. */
static int parse_pseudo(const char *s, size_t *ip, size_t b, css_pseudo_match *pm,
                        css_sel *sel) {
    size_t i = *ip + 1;  /* past ':' */
    memset(pm, 0, sizeof *pm);
    if (i < b && s[i] == ':') {
        /* ::before / ::after pseudo-element */
        ++i;  /* past second ':' */
        char pename[CSS_TOK_MAX];
        size_t nk = 0;
        while (i < b && csel_ident_ch(s[i])) {
            if (nk + 1 < sizeof pename) pename[nk++] = csel_lower_ch(s[i]);
            ++i;
        }
        pename[nk] = '\0';
        if (csel_ci_eq(pename, "before"))       pm->kind = PSEUDO_BEFORE;
        else if (csel_ci_eq(pename, "after"))   pm->kind = PSEUDO_AFTER;
        else return 0;  /* unsupported pseudo-element */
        *ip = i;
        return 1;
    }

    char name[CSS_TOK_MAX];
    size_t nk = 0;
    while (i < b && csel_ident_ch(s[i])) {
        if (nk + 1 < sizeof name) name[nk++] = csel_lower_ch(s[i]);
        ++i;
    }
    name[nk] = '\0';
    if (nk == 0) return 0;

    int wants_arg = 0;
    if (csel_ci_eq(name, "link") || csel_ci_eq(name, "any-link")) pm->kind = PSEUDO_LINK;
    else if (csel_ci_eq(name, "visited"))
        pm->kind = PSEUDO_NEVER;
    else if (csel_ci_eq(name, "hover"))          pm->kind = PSEUDO_HOVER;
    else if (csel_ci_eq(name, "active"))         pm->kind = PSEUDO_ACTIVE;
    else if (csel_ci_eq(name, "focus"))          pm->kind = PSEUDO_FOCUS;
    else if (csel_ci_eq(name, "focus-within"))   pm->kind = PSEUDO_FOCUS_WITHIN;
    else if (csel_ci_eq(name, "focus-visible"))  pm->kind = PSEUDO_FOCUS_VISIBLE;
    else if (csel_ci_eq(name, "root"))        pm->kind = PSEUDO_ROOT;
    else if (csel_ci_eq(name, "first-child")) pm->kind = PSEUDO_FIRST_CHILD;
    else if (csel_ci_eq(name, "last-child"))  pm->kind = PSEUDO_LAST_CHILD;
    else if (csel_ci_eq(name, "only-child"))  pm->kind = PSEUDO_ONLY_CHILD;
    else if (csel_ci_eq(name, "nth-child"))      { pm->kind = PSEUDO_NTH_CHILD; wants_arg = 1; }
    else if (csel_ci_eq(name, "nth-last-child")) { pm->kind = PSEUDO_NTH_LAST_CHILD; wants_arg = 1; }
    else if (csel_ci_eq(name, "checked"))  pm->kind = PSEUDO_CHECKED;
    else if (csel_ci_eq(name, "disabled")) pm->kind = PSEUDO_DISABLED;
    else if (csel_ci_eq(name, "enabled"))  pm->kind = PSEUDO_ENABLED;
    else if (csel_ci_eq(name, "not"))      { pm->kind = PSEUDO_NOT; wants_arg = 2; }
    else if (csel_ci_eq(name, "is"))       { pm->kind = PSEUDO_IS; wants_arg = 2; }
    else if (csel_ci_eq(name, "where"))    { pm->kind = PSEUDO_WHERE; wants_arg = 2; }
    else if (csel_ci_eq(name, "has"))      { pm->kind = PSEUDO_HAS; wants_arg = 2; }
    else if (csel_ci_eq(name, "nth-of-type"))      { pm->kind = PSEUDO_NTH_OF_TYPE; wants_arg = 1; }
    else if (csel_ci_eq(name, "nth-last-of-type")) { pm->kind = PSEUDO_NTH_LAST_OF_TYPE; wants_arg = 1; }
    else if (csel_ci_eq(name, "first-of-type"))    pm->kind = PSEUDO_FIRST_OF_TYPE;
    else if (csel_ci_eq(name, "last-of-type"))     pm->kind = PSEUDO_LAST_OF_TYPE;
    else if (csel_ci_eq(name, "only-of-type"))     pm->kind = PSEUDO_ONLY_OF_TYPE;
    else if (csel_ci_eq(name, "empty"))            pm->kind = PSEUDO_EMPTY;
    else if (csel_ci_eq(name, "before"))           pm->kind = PSEUDO_BEFORE;
    else if (csel_ci_eq(name, "after"))            pm->kind = PSEUDO_AFTER;
    else if (csel_ci_eq(name, "target"))           pm->kind = PSEUDO_TARGET;
    else if (csel_ci_eq(name, "lang"))             { pm->kind = PSEUDO_LANG; wants_arg = 3; }
    else return 0;   /* unknown pseudo-class: drop the selector */

    if (wants_arg == 1) {
        if (i >= b || s[i] != '(') return 0;
        size_t as = ++i;
        while (i < b && s[i] != ')') ++i;
        if (i >= b) return 0;   /* unterminated */
        if (!parse_nth_arg(s, as, i, &pm->a, &pm->b)) return 0;
        ++i;   /* past ')' */
    } else if (wants_arg == 2) {
        /* Parse comma-separated sub-selectors inside (:not/.is/:where). The content
         * between ( and ) is split on commas (not inside [] or ()); each segment is
         * parsed as a simple compound (tag, .class, #id only, no combinators). At
         * most CSS_MAX_SUB_SELS total per selector, no nesting. */
        if (i >= b || s[i] != '(') return 0;
        /* :not() is not forgiving (Selectors 4 4.3): dropping an argument it
         * cannot read would exclude LESS than the author asked for. */
        int strict = (pm->kind == PSEUDO_NOT);
        size_t as = ++i;
        int depth = 0;
        size_t seg_start = as;
        pm->sub_first = sel->nsubs;
        pm->sub_count = 0;
        while (i < b) {
            size_t esc = csel_escape_len(s, i, b);
            if (esc > 0) { i += esc; continue; }
            if (s[i] == ')' && depth == 0) break;
            if (s[i] == '(') ++depth;
            else if (s[i] == '[') ++depth;
            else if (s[i] == ']' || s[i] == ')') { if (depth > 0) --depth; }
            else if (s[i] == ',' && depth == 0) {
                if (!take_sub_arg(s, seg_start, i, sel, strict)) return 0;
                seg_start = i + 1;
            }
            ++i;
        }
        if (i >= b) return 0;   /* unterminated */
        /* Parse the last segment (after the last comma, or the only one). */
        if (!take_sub_arg(s, seg_start, i, sel, strict)) return 0;
        pm->sub_count = sel->nsubs - pm->sub_first;
        ++i;   /* past ')' */
    } else if (wants_arg == 3) {
        /* :lang(ident): capture the language identifier (lowercased). */
        if (i >= b || s[i] != '(') return 0;
        size_t as = ++i;
        while (i < b && s[i] != ')') ++i;
        if (i >= b) return 0;
        size_t lk = 0;
        for (size_t j = as; j < i && lk + 1 < CSS_TOK_MAX; ++j) {
            if ((s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z') ||
                s[j] == '-' || s[j] == '_')
                pm->lang[lk++] = csel_lower_ch(s[j]);
        }
        pm->lang[lk] = '\0';
        if (lk == 0) return 0;
        ++i;
    } else if (i < b && s[i] == '(') {
        return 0;   /* argument on a non-functional pseudo-class */
    }

    *ip = i;
    return 1;
}

/* The PSEUDO_* kind of an argument-less pseudo-class usable inside a
 * sub-selector, or -1. */
static int simple_pseudo_kind(const char *nm) {
    static const struct { const char *n; int k; } T[] = {
        { "link", PSEUDO_LINK }, { "any-link", PSEUDO_LINK }, { "visited", PSEUDO_NEVER },
        { "hover", PSEUDO_HOVER }, { "active", PSEUDO_ACTIVE }, { "focus", PSEUDO_FOCUS },
        { "focus-within", PSEUDO_FOCUS_WITHIN }, { "focus-visible", PSEUDO_FOCUS_VISIBLE },
        { "root", PSEUDO_ROOT }, { "first-child", PSEUDO_FIRST_CHILD },
        { "last-child", PSEUDO_LAST_CHILD }, { "only-child", PSEUDO_ONLY_CHILD },
        { "checked", PSEUDO_CHECKED }, { "disabled", PSEUDO_DISABLED },
        { "enabled", PSEUDO_ENABLED }, { "first-of-type", PSEUDO_FIRST_OF_TYPE },
        { "last-of-type", PSEUDO_LAST_OF_TYPE }, { "only-of-type", PSEUDO_ONLY_OF_TYPE },
        { "empty", PSEUDO_EMPTY }, { "target", PSEUDO_TARGET },
    };
    for (size_t k = 0; k < sizeof T / sizeof T[0]; ++k)
        if (strcmp(nm, T[k].n) == 0) return T[k].k;
    return -1;
}

/* Parses one SIMPLE sub-selector span s[a,b) for :not()/:is()/:where(): only
 * tag name, .class, #id, or [attr] (no pseudo-classes, no combinators).
 * The caller MUST trim leading/trailing space. Returns 1 if any component was
 * parsed; 0 means the span is empty or junk (fail closed for that alternative). */
static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub) {
    if (a >= b) return 0;
    memset(sub, 0, sizeof *sub);
    size_t i = a;
    if (s[i] == '*') {
        ++i;  /* universal: no type */
    } else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') ||
               s[i] == '_') {
        if (!csel_read_ident(s, &i, b, sub->tag, 1)) return 0;
        sub->has_tag = 1;
    }
    while (i < b) {
        if (s[i] == '.') {
            ++i;
            /* One class slot: a second class would silently overwrite the first. */
            if (sub->has_cls || !csel_read_ident(s, &i, b, sub->cls, 0)) return 0;
            sub->has_cls = 1;
        } else if (s[i] == '#') {
            ++i;
            if (sub->has_id || !csel_read_ident(s, &i, b, sub->id, 0)) return 0;
            sub->has_id = 1;
        } else if (s[i] == '[') {
            if (sub->nattrs >= CSS_SUB_MAX_ATTRS) return 0;
            if (!parse_attr_sel(s, &i, b, &sub->attrs[sub->nattrs])) return 0;
            ++sub->nattrs;
        } else if (s[i] == ':' && i + 1 < b && s[i + 1] != ':') {
            /* A simple pseudo-class (state or structure): `:not(:focus)`,
             * `:not(:last-child)`. Functional ones stay out (fail closed). */
            ++i;
            char nm[CSS_TOK_MAX];
            size_t nk = 0;
            while (i < b && csel_ident_ch(s[i])) {
                if (nk + 1 < sizeof nm) nm[nk++] = csel_lower_ch(s[i]);
                ++i;
            }
            nm[nk] = '\0';
            int kind = simple_pseudo_kind(nm);
            if (kind < 0 || sub->npseudos >= CSS_SUB_MAX_PSEUDOS) return 0;
            sub->pseudos[sub->npseudos++] = kind;
        } else {
            return 0;
        }
    }
    return sub->has_tag || sub->has_cls || sub->has_id || sub->nattrs > 0
        || sub->npseudos > 0;
}

/* Stores one functional-pseudo argument s[a,b) (untrimmed) into sel->subs[].
 * Returns 0 only when strict (the :not() list) and the argument is unreadable or
 * the storage is full -- the caller then drops the whole selector. A forgiving
 * list (:is/:where/:has) just skips such an argument. */
static int take_sub_arg(const char *s, size_t a, size_t b, css_sel *sel, int strict) {
    while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == '\r')) ++a;
    while (b > a && (s[b-1] == ' ' || s[b-1] == '\t' || s[b-1] == '\n' || s[b-1] == '\r')) --b;
    if (sel->nsubs < CSS_MAX_SUB_SELS &&
        parse_sub_compound(s, a, b, &sel->subs[sel->nsubs])) {
        ++sel->nsubs;
        return 1;
    }
    return !strict;
}

/* Parses one COMPOUND selector span s[a,b) (no combinators, no surrounding space)
 * into *cp. sel holds the sub-selector storage for :not()/:is()/:where() 
 * pseudo-classes being parsed. Returns 1 if supported. */
static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,
                          css_sel *sel) {
    if (a >= b) return 0;
    memset(cp, 0, sizeof *cp);
    size_t i = a;
    if (s[i] == '*') {
        ++i;  /* universal: no type */
    } else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
        if (!csel_read_ident(s, &i, b, cp->tag, 1)) return 0;
        cp->has_tag = 1;
    } else if (s[i] != '.' && s[i] != '#' && s[i] != '[' && s[i] != ':') {
        return 0;
    }

    while (i < b) {
        if (s[i] == ':') {
            if (cp->npseudo >= CSS_MAX_PSEUDO_SEL) return 0;
            if (!parse_pseudo(s, &i, b, &cp->pseudos[cp->npseudo], sel)) return 0;
            ++cp->npseudo;
        } else if (s[i] == '.') {
            ++i;
            if (cp->ncls >= CSS_MAX_CLASSES_PER_SEL) return 0;
            if (!csel_read_ident(s, &i, b, cp->cls[cp->ncls], 0)) return 0;
            ++cp->ncls;
        } else if (s[i] == '#') {
            ++i;
            if (cp->has_id || !csel_read_ident(s, &i, b, cp->id, 0)) return 0;
            cp->has_id = 1;
        } else if (s[i] == '[') {
            if (cp->nattrs >= CSS_MAX_ATTR_SEL) return 0;
            if (!parse_attr_sel(s, &i, b, &cp->attrs[cp->nattrs])) return 0;
            ++cp->nattrs;
        } else {
            return 0;  /* unexpected char inside a compound */
        }
    }
    return 1;
}

/* Parses a complex selector span s[a,b) into *sel: a chain of compounds joined by
 * the descendant (whitespace), child (`>`), adjacent-sibling (`+`) or general-
 * sibling (`~`) combinator. Returns 1 if supported; anything unsupported drops
 * the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is
 * dropped. Whitespace inside a bracket (a quoted attribute value) or inside the
 * parentheses of :nth-child(...) does NOT split a compound. Specificity is the
 * sum over all compounds (id*100 + (class+attr+pseudo)*10 + type). */
int csel_parse(const char *s, size_t a, size_t b, css_sel *sel) {
    while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == '\r')) ++a;
    while (b > a && (s[b-1] == ' ' || s[b-1] == '\t' || s[b-1] == '\n' || s[b-1] == '\r')) --b;
    if (a >= b) return 0;

    memset(sel, 0, sizeof *sel);
    int n = 0;
    size_t i = a;
    while (i < b) {
        /* Skip the separator before this compound, noting a combinator char. At
         * most ONE of `>`/`+`/`~` may appear between two compounds. */
        int comb = COMB_DESCENDANT, comb_seen = 0;
        while (i < b && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' ||
                         s[i] == '\r' || s[i] == '>' || s[i] == '+' || s[i] == '~')) {
            if (s[i] == '>' || s[i] == '+' || s[i] == '~') {
                if (comb_seen) return 0;   /* `>>`, `+ +`, `> +`... invalid */
                comb_seen = 1;
                comb = (s[i] == '>') ? COMB_CHILD :
                       (s[i] == '+') ? COMB_ADJACENT : COMB_GENERAL;
            }
            ++i;
        }
        if (i >= b) { if (comb_seen) return 0; break; } /* trailing combinator */
        if (n == 0 && comb_seen) return 0;              /* leading combinator */

        /* The compound runs until whitespace or a combinator char at bracket AND
         * paren depth 0; `[..]` keeps a quoted value with spaces in the same
         * compound, `(..)` keeps an nth-child argument with spaces/signs. */
        size_t ts = i;
        int br = 0, par = 0;
        while (i < b) {
            size_t esc = csel_escape_len(s, i, b);
            if (esc > 0) { i += esc; continue; }   /* `\(`, `\ `, `\>` are ident bytes */
            char c = s[i];
            if (c == '[') br = 1;
            else if (c == ']') br = 0;
            else if (!br && c == '(') ++par;
            else if (!br && c == ')') { if (par == 0) return 0; --par; }
            else if (!br && par == 0 &&
                     (c == ' ' || c == '\t' || c == '\n' || c == '\r' ||
                      c == '>' || c == '+' || c == '~'))
                break;
            ++i;
        }
        if (par != 0) return 0;                        /* unbalanced parenthesis */
        if (n >= CSS_MAX_COMPOUNDS) return 0;          /* too deep: fail closed */
        if (!parse_compound(s, ts, i, &sel->parts[n], sel)) return 0;
        sel->comb[n] = (n == 0) ? COMB_DESCENDANT : comb;
        ++n;
    }
    if (n == 0) return 0;
    sel->nparts = n;

    int spec = 0;
    for (int k = 0; k < n; ++k) {
        int psel = 0;
        for (int p = 0; p < sel->parts[k].npseudo; ++p) {
            int pk = sel->parts[k].pseudos[p].kind;
            if (pk == PSEUDO_WHERE) {
                /* :where() contributes 0 specificity. */
            } else if (pk == PSEUDO_NOT || pk == PSEUDO_IS) {
                /* :not()/:is() contribute the max specificity of their sub-selectors.
                 * Each sub is a compound with tag=1, class=10, id=100, [attr]=10. */
                int max_sub = 0;
                int first = sel->parts[k].pseudos[p].sub_first;
                int cnt   = sel->parts[k].pseudos[p].sub_count;
                for (int si = 0; si < cnt; ++si) {
                    int idx = first + si;
                    if (idx >= 0 && idx < sel->nsubs) {
                        int ss = (sel->subs[idx].has_id ? 100 : 0) +
                                 (sel->subs[idx].has_cls ? 10 : 0) +
                                 (sel->subs[idx].nattrs * 10) +
                                 (sel->subs[idx].has_tag ? 1 : 0);
                        if (ss > max_sub) max_sub = ss;
                    }
                }
                psel += max_sub;
            } else {
                psel += 10;
            }
        }
        spec += 100 * (sel->parts[k].has_id ? 1 : 0) +
                10 * (sel->parts[k].ncls + sel->parts[k].nattrs) +
                psel +
                (sel->parts[k].has_tag ? 1 : 0);
    }
    sel->spec = spec;
    return 1;
}

/* The value of element attribute `name` (case-insensitive name), or NULL if absent.
 * A present attribute with no value reads as "". */
static const char *el_attr_value(const css_element *el, const char *name) {
    if (el->attrs == NULL) return NULL;
    for (size_t i = 0; i < el->nattrs; ++i) {
        if (el->attrs[i].name != NULL && csel_ci_eq(el->attrs[i].name, name))
            return el->attrs[i].value != NULL ? el->attrs[i].value : "";
    }
    return NULL;
}

/* True if `v` ends with `suf` (non-empty), case-folded when ci. */
static int ends_with(const char *v, const char *suf, int ci) {
    size_t vl = strlen(v), fl = strlen(suf);
    if (fl == 0 || fl > vl) return 0;
    return csel_span_eq(v + vl - fl, suf, fl, ci);
}

/* True if `v` is a whitespace-separated list containing the word `w` (non-empty),
 * case-folded when ci (the `~=` operator). */
static int has_word(const char *v, const char *w, int ci) {
    size_t wl = strlen(w);
    if (wl == 0) return 0;
    const char *p = v;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' || *p == '\f') ++p;
        const char *st = p;
        while (*p != '\0' && *p != ' ' && *p != '\t' && *p != '\n' &&
               *p != '\r' && *p != '\f') ++p;
        if ((size_t)(p - st) == wl && csel_span_eq(st, w, wl, ci)) return 1;
    }
    return 0;
}

/* True if attribute selector `am` matches element `el`. */
static int attr_matches(const css_attr_match *am, const css_element *el) {
    const char *v = el_attr_value(el, am->name);
    if (v == NULL) return 0;                 /* attribute absent */
    if (am->op == ATTR_PRESENT) return 1;
    size_t vl = strlen(v), nl = strlen(am->value);
    switch (am->op) {
        case ATTR_EQ:     return vl == nl && csel_span_eq(v, am->value, nl, am->ci);
        case ATTR_TILDE:  return has_word(v, am->value, am->ci);
        case ATTR_PIPE:   return (vl == nl && csel_span_eq(v, am->value, nl, am->ci)) ||
                                 (vl > nl && csel_span_eq(v, am->value, nl, am->ci) &&
                                  v[nl] == '-');
        case ATTR_CARET:  return nl > 0 && vl >= nl && csel_span_eq(v, am->value, nl, am->ci);
        case ATTR_DOLLAR: return ends_with(v, am->value, am->ci);
        case ATTR_STAR:   return csel_substr(v, am->value, am->ci);
        default:          return 0;
    }
}

/* True if the 1-based index idx satisfies idx = A*m + B for some integer m >= 0.
 * idx <= 0 means "unknown sibling position" and never matches (fail closed). */
static int nth_matches(int A, int B, int idx) {
    if (idx <= 0) return 0;
    if (A == 0) return idx == B;
    long d = (long)idx - B;
    if (A > 0) return d >= 0 && d % A == 0;
    return d <= 0 && (-d) % (long)(-A) == 0;
}

/* Form controls for :enabled (per HTML: elements that can actually be disabled). */
static int is_form_control(const char *tag) {
    if (tag == NULL) return 0;
    return csel_ci_eq(tag, "input") || csel_ci_eq(tag, "button") ||
           csel_ci_eq(tag, "select") || csel_ci_eq(tag, "textarea") ||
           csel_ci_eq(tag, "option") || csel_ci_eq(tag, "optgroup") ||
           csel_ci_eq(tag, "fieldset");
}

/* True if a css_sub_sel (tag/class/id/[attr]) matches element el. */
static int pseudo_matches(const css_pseudo_match *pm, const css_element *el,
                          const css_sel *sel, const char *target_id,
                          int allow_pseudo_el);

static int sub_sel_matches(const css_sub_sel *sub, const css_element *el) {
    if (sub->has_tag && (el->tag == NULL || !csel_ci_eq(sub->tag, el->tag)))
        return 0;
    if (sub->has_id && (el->id == NULL || !csel_ident_eq(sub->id, el->id, strlen(el->id))))
        return 0;
    if (sub->has_cls) {
        int found = 0;
        for (size_t j = 0; j < el->nclasses; ++j) {
            if (el->classes[j] != NULL &&
                csel_ident_eq(sub->cls, el->classes[j], strlen(el->classes[j]))) {
                found = 1; break;
            }
        }
        if (!found) return 0;
    }
    for (int i = 0; i < sub->nattrs; ++i)
        if (!attr_matches(&sub->attrs[i], el)) return 0;
    for (int i = 0; i < sub->npseudos; ++i) {
        css_pseudo_match pm;
        memset(&pm, 0, sizeof pm);
        pm.kind = sub->pseudos[i];
        pm.sub_first = -1;
        if (!pseudo_matches(&pm, el, NULL, NULL, 0)) return 0;
    }
    return 1;
}

/* True if pseudo-class `pm` matches element `el`. Zero Knowledge semantics:
 * :link covers every a/area[href] (no history, everything is unvisited) and
 * PSEUDO_NEVER (:visited) never matches. The dynamic pseudos read el->state, so
 * a freshly loaded page (state == 0, pointer nowhere) matches none of them --
 * the page paints the way its author wrote it for the resting state.
 * Structural pseudos read nth/nsib, where 0 = unknown = no match (fail closed).
 * For :not/:is/:where, the sel pointer provides the sub-selector array. */
static int pseudo_matches(const css_pseudo_match *pm, const css_element *el,
                          const css_sel *sel, const char *target_id,
                          int allow_pseudo_el) {
    switch (pm->kind) {
        case PSEUDO_LINK:
            return el->tag != NULL &&
                   (csel_ci_eq(el->tag, "a") || csel_ci_eq(el->tag, "area")) &&
                   el_attr_value(el, "href") != NULL;
        case PSEUDO_NEVER:        return 0;
        /* Driven by the engine, never by a constant. See CSEL_STATE_*. */
        case PSEUDO_HOVER:          return (el->state & CSEL_STATE_HOVER) != 0;
        case PSEUDO_ACTIVE:         return (el->state & CSEL_STATE_ACTIVE) != 0;
        case PSEUDO_FOCUS:          return (el->state & CSEL_STATE_FOCUS) != 0;
        case PSEUDO_FOCUS_WITHIN:   return (el->state & CSEL_STATE_FOCUS_WITHIN) != 0;
        case PSEUDO_FOCUS_VISIBLE:  return (el->state & CSEL_STATE_FOCUS_VISIBLE) != 0;
        case PSEUDO_ROOT:         return el->tag != NULL && csel_ci_eq(el->tag, "html");
        case PSEUDO_FIRST_CHILD:  return el->nth == 1;
        case PSEUDO_LAST_CHILD:   return el->nth > 0 && el->nth == el->nsib;
        case PSEUDO_ONLY_CHILD:   return el->nth == 1 && el->nsib == 1;
        case PSEUDO_NTH_CHILD:    return nth_matches(pm->a, pm->b, el->nth);
        case PSEUDO_NTH_LAST_CHILD:
            return el->nth > 0 && el->nsib >= el->nth &&
                   nth_matches(pm->a, pm->b, el->nsib - el->nth + 1);
        case PSEUDO_CHECKED:      return el_attr_value(el, "checked") != NULL;
        case PSEUDO_DISABLED:     return el_attr_value(el, "disabled") != NULL;
        case PSEUDO_ENABLED:
            return is_form_control(el->tag) && el_attr_value(el, "disabled") == NULL;
        case PSEUDO_NOT:
            if (sel == NULL || pm->sub_first < 0) return 0;
            for (int si = 0; si < pm->sub_count; ++si) {
                int idx = pm->sub_first + si;
                if (idx < sel->nsubs && sub_sel_matches(&sel->subs[idx], el))
                    return 0;  /* a sub-selector matches → :not() fails */
            }
            return 1;  /* no sub-selector matched */
        case PSEUDO_IS:
        case PSEUDO_WHERE:
            if (sel == NULL || pm->sub_first < 0) return 0;
            for (int si = 0; si < pm->sub_count; ++si) {
                int idx = pm->sub_first + si;
                if (idx < sel->nsubs && sub_sel_matches(&sel->subs[idx], el))
                    return 1;  /* any sub-selector matches → succeed */
            }
            return 0;  /* none matched */
        /* R2: structural-of-type — reuses nth with type counting */
        case PSEUDO_FIRST_OF_TYPE:  return el->nth_of_type == 1 && el->nsib_of_type >= 1;
        case PSEUDO_LAST_OF_TYPE:   return el->nth_of_type > 0 && el->nsib_of_type > 0 &&
                                           el->nth_of_type == el->nsib_of_type;
        case PSEUDO_ONLY_OF_TYPE:   return el->nth_of_type == 1 && el->nsib_of_type == 1;
        case PSEUDO_NTH_OF_TYPE:    return el->nth_of_type > 0 &&
                                           nth_matches(pm->a, pm->b, el->nth_of_type);
        case PSEUDO_NTH_LAST_OF_TYPE:
            return el->nth_of_type > 0 && el->nsib_of_type >= el->nth_of_type &&
                   nth_matches(pm->a, pm->b, el->nsib_of_type - el->nth_of_type + 1);
        /* R2: element-state pseudos */
        case PSEUDO_EMPTY:          return el->child_count == 0;
        case PSEUDO_TARGET:         return (target_id != NULL && el->id != NULL &&
                                           strcmp(el->id, target_id) == 0);
        case PSEUDO_LANG: {
            /* Match if element's lang attribute starts with pm->lang (e.g. "en"
             * matches "en", "en-US"). Fail closed on missing attr. */
            const char *lv = el_attr_value(el, "lang");
            if (lv == NULL) return 0;
            size_t pl = strlen(pm->lang);
            if (strlen(lv) < pl) return 0;
            if (!csel_span_eq(lv, pm->lang, pl, 1)) return 0;
            return (lv[pl] == '\0' || lv[pl] == '-');
        }
        case PSEUDO_HAS: {
            /* :has(selector): walk DOM descendants and return 1 if any match
             * any sub-selector. Uses el->dom_node to traverse the real DOM tree.
             * v1: tag/id/class/attr matching, no combinators in the argument. */
            if (el->dom_node == NULL || sel == NULL || pm->sub_first < 0)
                return 0;
            /* Recursive depth cap to prevent unbounded traversal on deep DOM. */
            #define HAS_MAX_DEPTH 32
            /* Stack-based DFS: pairs of (node, depth). */
            const lxb_dom_node_t *stack[128];
            int depth[128];
            int sp = 0;
            const lxb_dom_node_t *root = (const lxb_dom_node_t *)el->dom_node;
            for (const lxb_dom_node_t *ch = root->first_child;
                 ch != NULL && sp < 128; ch = ch->next) {
                stack[sp] = ch; depth[sp] = 1; ++sp;
            }
            while (sp > 0) {
                --sp;
                const lxb_dom_node_t *cur = stack[sp];
                int cd = depth[sp];
                if (cur->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
                lxb_dom_element_t *cel = (lxb_dom_element_t *)cur;
                /* Check all sub-selectors against this descendant element. */
                for (int si = 0; si < pm->sub_count; ++si) {
                    int idx = pm->sub_first + si;
                    if (idx >= sel->nsubs) break;
                    const css_sub_sel *sub = &sel->subs[idx];
                    int match = 1;
                    /* Check tag */
                    if (sub->has_tag) {
                        size_t nl = 0;
                        const lxb_char_t *nm = lxb_dom_element_local_name(cel, &nl);
                        if (nm == NULL || strlen(sub->tag) != nl ||
                            !csel_span_eq((const char *)nm, sub->tag, nl, 1))
                            match = 0;
                    }
                    if (!match) continue;
                    /* Check id */
                    if (sub->has_id) {
                        size_t il = 0;
                        const lxb_char_t *idv = lxb_dom_element_get_attribute(
                            cel, (const lxb_char_t *)"id", 2, &il);
                        if (idv == NULL || !csel_ident_eq(sub->id, (const char *)idv, il))
                            match = 0;
                    }
                    if (!match) continue;
                    /* Check class */
                    if (sub->has_cls) {
                        size_t cl = 0;
                        const lxb_char_t *cv = lxb_dom_element_get_attribute(
                            cel, (const lxb_char_t *)"class", 5, &cl);
                        int found = 0;
                        if (cv != NULL) {
                            size_t tok_start = 0, tok_end = 0;
                            while (tok_end <= cl) {
                                if (tok_end == cl || cv[tok_end] == ' ') {
                                    size_t tkl = tok_end - tok_start;
                                    if (tkl > 0 &&
                                        csel_ident_eq(sub->cls, (const char *)cv + tok_start, tkl))
                                        { found = 1; break; }
                                    tok_start = tok_end + 1;
                                }
                                ++tok_end;
                            }
                        }
                        if (!found) match = 0;
                    }
                    if (!match) continue;
                    /* Check attribute selectors */
                    for (int ai = 0; ai < sub->nattrs; ++ai) {
                        size_t avl = 0;
                        const lxb_char_t *av = lxb_dom_element_get_attribute(
                            cel, (const lxb_char_t *)sub->attrs[ai].name,
                            strlen(sub->attrs[ai].name), &avl);
                        if (!av) { match = 0; break; }
                        if (sub->attrs[ai].op != ATTR_PRESENT) {
                            const char *val = sub->attrs[ai].value;
                            size_t vl = strlen(val);
                            switch (sub->attrs[ai].op) {
                                case ATTR_EQ:
                                    if (avl != vl || memcmp(av, val, vl) != 0)
                                        match = 0;
                                    break;
                                case ATTR_TILDE: {
                                    int f = 0;
                                    size_t tk_s = 0, tk_e = 0;
                                    while (tk_e <= avl) {
                                        if (tk_e == avl || av[tk_e] == ' ') {
                                            size_t tkl = tk_e - tk_s;
                                            if (tkl == vl && memcmp(av+tk_s,val,vl)==0)
                                                { f=1; break; }
                                            tk_s = tk_e+1;
                                        }
                                        ++tk_e;
                                    }
                                    if (!f) match = 0;
                                    break;
                                }
                                case ATTR_PIPE: {
                                    if (avl < vl || memcmp(av, val, vl) != 0)
                                        { match=0; break; }
                                    if (avl > vl && av[vl] != '-') match=0;
                                    break;
                                }
                                case ATTR_CARET:
                                    if (avl < vl || memcmp(av, val, vl) != 0)
                                        match = 0;
                                    break;
                                case ATTR_DOLLAR: {
                                    if (avl < vl || memcmp(av+avl-vl, val, vl) != 0)
                                        match = 0;
                                    break;
                                }
                                case ATTR_STAR: {
                                    int f = 0;
                                    for (size_t o = 0; o+vl <= avl; ++o)
                                        if (memcmp(av+o, val, vl)==0) { f=1; break; }
                                    if (!f) match = 0;
                                    break;
                                }
                                default: match = 0;
                            }
                        }
                        if (!match) break;
                    }
                    if (match) return 1;  /* found a matching descendant */
                }
                /* Push children for deeper traversal (capped). */
                if (cd < HAS_MAX_DEPTH) {
                    for (const lxb_dom_node_t *ch = cur->first_child;
                         ch != NULL && sp < 128; ch = ch->next) {
                        stack[sp] = ch; depth[sp] = cd + 1; ++sp;
                    }
                }
            }
            return 0;  /* no matching descendant found */
        }
        case PSEUDO_BEFORE:
        case PSEUDO_AFTER:        return allow_pseudo_el;  /* R8: match only in CSS cascade */
        default:                  return 0;
    }
}

/* True if one compound matches one element (no ancestor context).
 * When pseudo_kind is non-NULL and the compound matches via PSEUDO_BEFORE or
 * PSEUDO_AFTER, *pseudo_kind is set to that pseudo-element kind; otherwise -1. */
static int compound_matches(const css_compound *c, const css_element *el,
                            const css_sel *sel, const char *target_id,
                            int allow_pseudo_el, int *pseudo_kind) {
    if (el == NULL) return 0;
    if (c->has_tag) { if (el->tag == NULL || !csel_ci_eq(c->tag, el->tag)) return 0; }
    if (c->has_id && (el->id == NULL || !csel_ident_eq(c->id, el->id, strlen(el->id))))
        return 0;
    for (int i = 0; i < c->ncls; ++i) {
        int found = 0;
        for (size_t j = 0; j < el->nclasses; ++j) {
            if (el->classes[j] != NULL &&
                csel_ident_eq(c->cls[i], el->classes[j], strlen(el->classes[j]))) {
                found = 1; break;
            }
        }
        if (!found) return 0;
    }
    for (int i = 0; i < c->nattrs; ++i)
        if (!attr_matches(&c->attrs[i], el)) return 0;
    int pk = -1;
    for (int i = 0; i < c->npseudo; ++i) {
        if (!pseudo_matches(&c->pseudos[i], el, sel, target_id, allow_pseudo_el)) return 0;
        if (allow_pseudo_el) {
            int k = c->pseudos[i].kind;
            if (k == PSEUDO_BEFORE || k == PSEUDO_AFTER) pk = k;
        }
    }
    if (pseudo_kind != NULL) *pseudo_kind = pk;
    return 1;
}

/* True if parts[0..k] match the ancestor/sibling chains ending at el (el matches
 * parts[k]). Right-to-left: child requires the immediate parent; descendant tries
 * each ancestor; adjacent requires the immediately preceding sibling; general
 * tries each preceding sibling. Bounded by k (<= CSS_MAX_COMPOUNDS) and by the
 * chains the caller built (an element without parent/prev links never matches
 * through that combinator — fail closed). When pseudo_kind is non-NULL and the
 * subject compound (rightmost, index k) matches via PSEUDO_BEFORE or
 * PSEUDO_AFTER, *pseudo_kind is set to that kind. */
static int complex_matches(const css_sel *sel, int k, const css_element *el,
                           const char *target_id, int allow_pseudo_el,
                           int *pseudo_kind) {
    if (!compound_matches(&sel->parts[k], el, sel, target_id, allow_pseudo_el, pseudo_kind))
        return 0;
    if (k == 0) return 1;
    /* Only the SUBJECT compound reports the pseudo-element, and the call above --
     * this level's own compound_matches -- is the one that just did it when k is the
     * subject index. Every recursive call below walks to an ANCESTOR (k-1), which by
     * definition carries no pseudo-element and would report "none", so it must write
     * to a scratch slot instead of the caller's.
     *
     * This ternary used to name pseudo_kind for `k == nparts - 1`, which is exactly
     * backwards: at the subject level it handed the caller's slot to the ancestor
     * walk, which promptly overwrote PSEUDO_BEFORE with -1. So the marker survived
     * only for single-compound selectors, and every real-world rule -- they all have
     * combinators -- silently lost it, leaking the pseudo's declarations onto the
     * originating element (spec/css.md "pseudo-elementos"). Also matters for the
     * descendant/general loops, where a FAILED attempt must not leave a mark. */
    int dummy = -1;
    int *pk = &dummy;
    switch (sel->comb[k]) {
        case COMB_CHILD:
            return (el->parent != NULL) && complex_matches(sel, k - 1, el->parent, target_id, allow_pseudo_el, pk);
        case COMB_ADJACENT:
            return (el->prev != NULL) && complex_matches(sel, k - 1, el->prev, target_id, allow_pseudo_el, pk);
        case COMB_GENERAL:
            for (const css_element *sib = el->prev; sib != NULL; sib = sib->prev)
                if (complex_matches(sel, k - 1, sib, target_id, allow_pseudo_el, pk)) return 1;
            return 0;
        default:
            for (const css_element *anc = el->parent; anc != NULL; anc = anc->parent)
                if (complex_matches(sel, k - 1, anc, target_id, allow_pseudo_el, pk)) return 1;
            return 0;
    }
}

int csel_matches(const css_sel *sel, const css_element *el, const char *target_id,
                 int allow_pseudo_el, int *pseudo_kind) {
    int pk = -1;
    int ok = complex_matches(sel, sel->nparts - 1, el, target_id, allow_pseudo_el, &pk);
    if (pseudo_kind != NULL) *pseudo_kind = pk;
    return ok;
}
