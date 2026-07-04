/*
 * css_select — selector engine of the author-CSS module. See include/css_select.h,
 * spec/css_select.md.
 *
 * Hostile content: bounded (compounds/attrs/token caps), fails closed (anything
 * unsupported drops the whole selector), pure (no allocation, no I/O).
 */

#include "css_select.h"

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

/* Parses one COMPOUND selector span s[a,b) (no combinators, no surrounding space)
 * into *cp. Returns 1 if supported (type, .class, #id, *, [attr]). */
static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp) {
    if (a >= b) return 0;
    memset(cp, 0, sizeof *cp);
    size_t i = a;
    if (s[i] == '*') {
        ++i;  /* universal: no type */
    } else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
        size_t k = 0;
        while (i < b && csel_ident_ch(s[i])) {
            if (k + 1 < sizeof cp->tag) cp->tag[k++] = csel_lower_ch(s[i]);
            ++i;
        }
        cp->tag[k] = '\0';
        cp->has_tag = 1;
    } else if (s[i] != '.' && s[i] != '#' && s[i] != '[') {
        return 0;
    }

    while (i < b) {
        if (s[i] == '.') {
            ++i;
            if (i >= b || !csel_ident_ch(s[i])) return 0;
            if (cp->ncls >= CSS_MAX_CLASSES_PER_SEL) return 0;
            size_t k = 0;
            while (i < b && csel_ident_ch(s[i])) {
                if (k + 1 < CSS_TOK_MAX) cp->cls[cp->ncls][k++] = s[i];
                ++i;
            }
            cp->cls[cp->ncls][k] = '\0';
            ++cp->ncls;
        } else if (s[i] == '#') {
            ++i;
            if (i >= b || !csel_ident_ch(s[i]) || cp->has_id) return 0;
            size_t k = 0;
            while (i < b && csel_ident_ch(s[i])) {
                if (k + 1 < sizeof cp->id) cp->id[k++] = s[i];
                ++i;
            }
            cp->id[k] = '\0';
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
 * the descendant (whitespace) or child (`>`) combinator. Returns 1 if supported.
 * Attribute selectors `[...]` are supported; the sibling combinators (`+`/`~`)
 * and pseudo-classes (`:`) are unsupported: the whole selector is dropped (fail
 * closed). A chain deeper than CSS_MAX_COMPOUNDS is dropped. Whitespace inside a
 * bracket (a quoted attribute value) does NOT split a compound. Specificity is the
 * sum over all compounds (id*100 + (class+attr)*10 + type). */
int csel_parse(const char *s, size_t a, size_t b, css_sel *sel) {
    while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == '\r')) ++a;
    while (b > a && (s[b-1] == ' ' || s[b-1] == '\t' || s[b-1] == '\n' || s[b-1] == '\r')) --b;
    if (a >= b) return 0;

    /* Unsupported syntax OUTSIDE brackets => drop the whole selector. `>` and
     * whitespace are combinators; `[`/`]` open an attribute selector (whose contents
     * may legitimately contain `~`/`+`/`*`/etc, so they are skipped here). */
    int in_br = 0;
    for (size_t i = a; i < b; ++i) {
        char c = s[i];
        if (c == '[') { if (in_br) return 0; in_br = 1; continue; }
        if (c == ']') { if (!in_br) return 0; in_br = 0; continue; }
        if (in_br) continue;
        if (c == '+' || c == '~' || c == ':' || c == '(' || c == ')') return 0;
    }
    if (in_br) return 0;  /* unbalanced bracket */

    memset(sel, 0, sizeof *sel);
    int n = 0;
    size_t i = a;
    while (i < b) {
        /* Skip the separator before this compound, noting a `>` (child combinator). */
        int child = 0;
        while (i < b && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' ||
                         s[i] == '\r' || s[i] == '>')) {
            if (s[i] == '>') { if (child) return 0; child = 1; }  /* `>>` invalid */
            ++i;
        }
        if (i >= b) { if (child) return 0; break; }   /* trailing `>` with no compound */
        if (n == 0 && child) return 0;                /* leading `>` */

        /* The compound runs until whitespace/`>` at bracket depth 0; a `[..]` keeps a
         * quoted value with spaces in the same compound. */
        size_t ts = i;
        int br = 0;
        while (i < b) {
            char c = s[i];
            if (c == '[') br = 1;
            else if (c == ']') br = 0;
            else if (!br && (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '>'))
                break;
            ++i;
        }
        if (n >= CSS_MAX_COMPOUNDS) return 0;          /* too deep: fail closed */
        if (!parse_compound(s, ts, i, &sel->parts[n])) return 0;
        sel->comb[n] = (n == 0) ? COMB_DESCENDANT : (child ? COMB_CHILD : COMB_DESCENDANT);
        ++n;
    }
    if (n == 0) return 0;
    sel->nparts = n;

    int spec = 0;
    for (int k = 0; k < n; ++k)
        spec += 100 * (sel->parts[k].has_id ? 1 : 0) +
                10 * (sel->parts[k].ncls + sel->parts[k].nattrs) +
                (sel->parts[k].has_tag ? 1 : 0);
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

/* True if one compound matches one element (no ancestor context). */
static int compound_matches(const css_compound *c, const css_element *el) {
    if (el == NULL) return 0;
    if (c->has_tag) { if (el->tag == NULL || !csel_ci_eq(c->tag, el->tag)) return 0; }
    if (c->has_id)  { if (el->id == NULL || strcmp(c->id, el->id) != 0) return 0; }
    for (int i = 0; i < c->ncls; ++i) {
        int found = 0;
        for (size_t j = 0; j < el->nclasses; ++j) {
            if (el->classes[j] != NULL && strcmp(c->cls[i], el->classes[j]) == 0) {
                found = 1; break;
            }
        }
        if (!found) return 0;
    }
    for (int i = 0; i < c->nattrs; ++i)
        if (!attr_matches(&c->attrs[i], el)) return 0;
    return 1;
}

/* True if parts[0..k] match the ancestor chain ending at el (el matches parts[k]).
 * Right-to-left: child requires the immediate parent; descendant tries each ancestor
 * (the recursion backtracks). Bounded by k (<= CSS_MAX_COMPOUNDS) and the chain. */
static int complex_matches(const css_sel *sel, int k, const css_element *el) {
    if (!compound_matches(&sel->parts[k], el)) return 0;
    if (k == 0) return 1;
    if (sel->comb[k] == COMB_CHILD) {
        return (el->parent != NULL) && complex_matches(sel, k - 1, el->parent);
    }
    for (const css_element *anc = el->parent; anc != NULL; anc = anc->parent)
        if (complex_matches(sel, k - 1, anc)) return 1;
    return 0;
}

int csel_matches(const css_sel *sel, const css_element *el) {
    return complex_matches(sel, sel->nparts - 1, el);
}
