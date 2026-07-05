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

/* Parses one pseudo-class starting at s[*ip] == ':' (within s[.,b)) into *pm.
 * Advances *ip past it (including a (arg) for the nth-child family). Returns 1
 * if supported, 0 (fail closed) otherwise — unknown names, functional pseudos
 * other than nth-child/nth-last-child, and every pseudo-ELEMENT (`::name` and
 * the legacy single-colon spellings :before/:after/:first-line/:first-letter)
 * drop the whole selector. */
static int parse_pseudo(const char *s, size_t *ip, size_t b, css_pseudo_match *pm) {
    size_t i = *ip + 1;  /* past ':' */
    memset(pm, 0, sizeof *pm);
    if (i < b && s[i] == ':') return 0;   /* pseudo-element */

    char name[CSS_TOK_MAX];
    size_t k = 0;
    while (i < b && csel_ident_ch(s[i])) {
        if (k + 1 < sizeof name) name[k++] = csel_lower_ch(s[i]);
        ++i;
    }
    name[k] = '\0';
    if (k == 0) return 0;

    int wants_arg = 0;
    if (csel_ci_eq(name, "link") || csel_ci_eq(name, "any-link")) pm->kind = PSEUDO_LINK;
    else if (csel_ci_eq(name, "visited") || csel_ci_eq(name, "hover") ||
             csel_ci_eq(name, "active") || csel_ci_eq(name, "focus") ||
             csel_ci_eq(name, "focus-within") || csel_ci_eq(name, "focus-visible"))
        pm->kind = PSEUDO_NEVER;
    else if (csel_ci_eq(name, "root"))        pm->kind = PSEUDO_ROOT;
    else if (csel_ci_eq(name, "first-child")) pm->kind = PSEUDO_FIRST_CHILD;
    else if (csel_ci_eq(name, "last-child"))  pm->kind = PSEUDO_LAST_CHILD;
    else if (csel_ci_eq(name, "only-child"))  pm->kind = PSEUDO_ONLY_CHILD;
    else if (csel_ci_eq(name, "nth-child"))      { pm->kind = PSEUDO_NTH_CHILD; wants_arg = 1; }
    else if (csel_ci_eq(name, "nth-last-child")) { pm->kind = PSEUDO_NTH_LAST_CHILD; wants_arg = 1; }
    else if (csel_ci_eq(name, "checked"))  pm->kind = PSEUDO_CHECKED;
    else if (csel_ci_eq(name, "disabled")) pm->kind = PSEUDO_DISABLED;
    else if (csel_ci_eq(name, "enabled"))  pm->kind = PSEUDO_ENABLED;
    else return 0;   /* unknown pseudo-class: drop the selector */

    if (wants_arg) {
        if (i >= b || s[i] != '(') return 0;
        size_t as = ++i;
        while (i < b && s[i] != ')') ++i;
        if (i >= b) return 0;   /* unterminated */
        if (!parse_nth_arg(s, as, i, &pm->a, &pm->b)) return 0;
        ++i;   /* past ')' */
    } else if (i < b && s[i] == '(') {
        return 0;   /* argument on a non-functional pseudo-class */
    }

    *ip = i;
    return 1;
}

/* Parses one COMPOUND selector span s[a,b) (no combinators, no surrounding space)
 * into *cp. Returns 1 if supported (type, .class, #id, *, [attr], :pseudo). */
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
    } else if (s[i] != '.' && s[i] != '#' && s[i] != '[' && s[i] != ':') {
        return 0;
    }

    while (i < b) {
        if (s[i] == ':') {
            if (cp->npseudo >= CSS_MAX_PSEUDO_SEL) return 0;
            if (!parse_pseudo(s, &i, b, &cp->pseudos[cp->npseudo])) return 0;
            ++cp->npseudo;
        } else if (s[i] == '.') {
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
        if (!parse_compound(s, ts, i, &sel->parts[n])) return 0;
        sel->comb[n] = (n == 0) ? COMB_DESCENDANT : comb;
        ++n;
    }
    if (n == 0) return 0;
    sel->nparts = n;

    int spec = 0;
    for (int k = 0; k < n; ++k)
        spec += 100 * (sel->parts[k].has_id ? 1 : 0) +
                10 * (sel->parts[k].ncls + sel->parts[k].nattrs +
                      sel->parts[k].npseudo) +
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

/* True if pseudo-class `pm` matches element `el`. Zero Knowledge semantics:
 * :link covers every a/area[href] (no history, everything is unvisited) and
 * PSEUDO_NEVER (:visited and the dynamic pseudos) never matches. Structural
 * pseudos read nth/nsib, where 0 = unknown = no match (fail closed). */
static int pseudo_matches(const css_pseudo_match *pm, const css_element *el) {
    switch (pm->kind) {
        case PSEUDO_LINK:
            return el->tag != NULL &&
                   (csel_ci_eq(el->tag, "a") || csel_ci_eq(el->tag, "area")) &&
                   el_attr_value(el, "href") != NULL;
        case PSEUDO_NEVER:        return 0;
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
        default:                  return 0;
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
    for (int i = 0; i < c->npseudo; ++i)
        if (!pseudo_matches(&c->pseudos[i], el)) return 0;
    return 1;
}

/* True if parts[0..k] match the ancestor/sibling chains ending at el (el matches
 * parts[k]). Right-to-left: child requires the immediate parent; descendant tries
 * each ancestor; adjacent requires the immediately preceding sibling; general
 * tries each preceding sibling (the recursion backtracks). Bounded by k
 * (<= CSS_MAX_COMPOUNDS) and by the chains the caller built (an element without
 * parent/prev links simply never matches through that combinator — fail closed). */
static int complex_matches(const css_sel *sel, int k, const css_element *el) {
    if (!compound_matches(&sel->parts[k], el)) return 0;
    if (k == 0) return 1;
    switch (sel->comb[k]) {
        case COMB_CHILD:
            return (el->parent != NULL) && complex_matches(sel, k - 1, el->parent);
        case COMB_ADJACENT:
            return (el->prev != NULL) && complex_matches(sel, k - 1, el->prev);
        case COMB_GENERAL:
            for (const css_element *sib = el->prev; sib != NULL; sib = sib->prev)
                if (complex_matches(sel, k - 1, sib)) return 1;
            return 0;
        default:
            for (const css_element *anc = el->parent; anc != NULL; anc = anc->parent)
                if (complex_matches(sel, k - 1, anc)) return 1;
            return 0;
    }
}

int csel_matches(const css_sel *sel, const css_element *el) {
    return complex_matches(sel, sel->nparts - 1, el);
}
