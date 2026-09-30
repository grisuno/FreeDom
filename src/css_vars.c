/*
 * css_vars -- custom-property table and var() substitution. See
 * include/css_vars.h and spec/css_vars.md.
 */
#include "css_vars.h"
#include "css_select.h"  /* csel_ident_ch, csel_lower_ch, csel_ci_eq */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static size_t name_hash(const char *s, size_t n) {
    uint64_t h = 1469598103934665603ull;          /* FNV-1a */
    for (size_t i = 0; i < n; ++i) {
        h ^= (unsigned char)s[i];
        h *= 1099511628211ull;
    }
    return (size_t)h;
}

static char *dup_n(const char *s, size_t n) {
    if (n == (size_t)-1) return NULL;             /* V-001 */
    char *d = (char *)malloc(n + 1);
    if (d == NULL) return NULL;
    memcpy(d, s, n);
    d[n] = '\0';
    return d;
}

/* Index into t->slot where name lives, or the empty slot where it would go.
 * Requires t->nslot > t->n (the index is never full). */
static size_t find_slot(const cvr_table *t, const char *name, size_t nlen) {
    size_t mask = t->nslot - 1;
    size_t i = name_hash(name, nlen) & mask;
    for (;;) {
        size_t e = t->slot[i];
        if (e == 0) return i;
        const char *en = t->ent[e - 1].name;
        if (strlen(en) == nlen && memcmp(en, name, nlen) == 0) return i;
        i = (i + 1) & mask;
    }
}

/* Doubles the entry array and rebuilds the index at twice its size. */
static int grow(cvr_table *t) {
    size_t ncap = t->cap ? t->cap * 2 : 64;
    if (ncap > CVR_MAX_ENTRIES) ncap = CVR_MAX_ENTRIES;
    if (ncap <= t->cap) return 0;
    if (ncap > SIZE_MAX / 2 / sizeof(size_t)) return 0;
    cvr_ent *ne = (cvr_ent *)realloc(t->ent, ncap * sizeof *ne);
    if (ne == NULL) return 0;
    t->ent = ne;
    t->cap = ncap;
    size_t nslot = ncap * 2;
    size_t *ns = (size_t *)calloc(nslot, sizeof *ns);
    if (ns == NULL) return 0;
    free(t->slot);
    t->slot = ns;
    t->nslot = nslot;
    for (size_t k = 0; k < t->n; ++k) {
        const char *en = t->ent[k].name;
        t->slot[find_slot(t, en, strlen(en))] = k + 1;
    }
    return 1;
}

int cvr_set(cvr_table *t, const char *name, size_t nlen, const char *value, size_t vlen) {
    if (t == NULL || name == NULL || value == NULL) return 0;
    if (nlen < 3 || name[0] != '-' || name[1] != '-') return 0;
    if (nlen >= CVR_NAME_MAX || vlen == 0 || vlen >= CVR_VALUE_MAX) return 0;
    if (memchr(name, '\0', nlen) != NULL) return 0;
    if (t->nslot != 0) {
        size_t i = find_slot(t, name, nlen);
        if (t->slot[i] != 0) {
            char *v = dup_n(value, vlen);
            if (v == NULL) return 0;
            cvr_ent *e = &t->ent[t->slot[i] - 1];
            free(e->value);
            e->value = v;
            return 1;
        }
    }
    if (t->n >= t->cap && !grow(t)) return 0;
    char *nm = dup_n(name, nlen);
    char *v = dup_n(value, vlen);
    if (nm == NULL || v == NULL) { free(nm); free(v); return 0; }
    t->ent[t->n].name = nm;
    t->ent[t->n].value = v;
    t->slot[find_slot(t, name, nlen)] = t->n + 1;
    ++t->n;
    return 1;
}

const char *cvr_get(const cvr_table *t, const char *name, size_t nlen) {
    if (t == NULL || name == NULL || t->nslot == 0 || t->n == 0) return NULL;
    size_t e = t->slot[find_slot(t, name, nlen)];
    return e ? t->ent[e - 1].value : NULL;
}

size_t cvr_count(const cvr_table *t) { return t ? t->n : 0; }

void cvr_reset(cvr_table *t) {
    if (t == NULL) return;
    for (size_t k = 0; k < t->n; ++k) {
        free(t->ent[k].name);
        free(t->ent[k].value);
    }
    t->n = 0;
    if (t->slot != NULL) memset(t->slot, 0, t->nslot * sizeof *t->slot);
}

void cvr_free(cvr_table *t) {
    if (t == NULL) return;
    cvr_reset(t);
    free(t->ent);
    free(t->slot);
    memset(t, 0, sizeof *t);
}

static int is_ws(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }

/* Length of val[0,n) once a trailing !important (optional blanks around the '!')
 * is removed, trailing blanks included. A '!' that is not !important is kept. */
static size_t without_important(const char *val, size_t n) {
    for (size_t i = n; i-- > 0; ) {
        if (val[i] != '!') continue;
        size_t r = i + 1;
        while (r < n && (val[r] == ' ' || val[r] == '\t')) ++r;
        static const char kw[] = "important";
        if (n - r != sizeof kw - 1) return n;
        for (size_t k = 0; k < sizeof kw - 1; ++k)
            if (csel_lower_ch(val[r + k]) != kw[k]) return n;
        while (i > 0 && is_ws(val[i - 1])) --i;
        return i;
    }
    return n;
}

void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b) {
    if (t == NULL || s == NULL) return;
    size_t i = a;
    while (i < b) {
        if (s[i] == '-' && i + 1 < b && s[i + 1] == '-' &&
            (i == a || !csel_ident_ch(s[i - 1]))) {
            size_t j = i + 2;
            while (j < b && csel_ident_ch(s[j])) ++j;
            size_t k = j;
            while (k < b && is_ws(s[k])) ++k;
            if (k < b && s[k] == ':') {
                size_t v0 = k + 1, v = csel_decl_end(s, v0, b, 1);
                size_t va = v0, vb = v;
                while (va < vb && is_ws(s[va])) ++va;
                while (vb > va && is_ws(s[vb - 1])) --vb;
                vb = va + without_important(s + va, vb - va);
                (void)cvr_set(t, s + i, j - i, s + va, vb - va);
                i = v;
                continue;
            }
        }
        ++i;
    }
}

static const char *scope_get(const cvr_scope *sc, const char *name, size_t nlen) {
    if (sc == NULL) return NULL;
    const char *v = cvr_get(sc->first, name, nlen);
    if (v != NULL) return v;
    int hops = 0;
    for (const cvr_chain *c = sc->chain; c != NULL && hops < CVR_CHAIN_MAX;
         c = c->parent, ++hops) {
        v = cvr_get(c->own, name, nlen);
        if (v != NULL) return v;
    }
    v = cvr_get(sc->second, name, nlen);
    return v ? v : cvr_get(sc->initial, name, nlen);
}

static int resolve_rec(const char *val, size_t vlen, char *out, size_t outcap,
                       size_t *o, const cvr_scope *sc, int depth, int *budget) {
    size_t i = 0;
    while (i < vlen) {
        if (i + 4 <= vlen && csel_lower_ch(val[i]) == 'v' && csel_lower_ch(val[i + 1]) == 'a' &&
            csel_lower_ch(val[i + 2]) == 'r' && val[i + 3] == '(') {
            size_t j = i + 4, argstart = j;
            int pdepth = 1;
            while (j < vlen) {
                if (val[j] == '(') ++pdepth;
                else if (val[j] == ')' && --pdepth == 0) break;
                ++j;
            }
            if (pdepth != 0) return 0;               /* unbalanced var(...) */
            size_t argend = j;
            /* First TOP-LEVEL comma splits name from fallback. */
            size_t comma = argend;
            int cd = 0;
            for (size_t k = argstart; k < argend; ++k) {
                if (val[k] == '(') ++cd;
                else if (val[k] == ')') --cd;
                else if (val[k] == ',' && cd == 0) { comma = k; break; }
            }
            size_t na = argstart, nb = comma;
            while (na < nb && is_ws(val[na])) ++na;
            while (nb > na && is_ws(val[nb - 1])) --nb;
            if (nb - na < 3 || val[na] != '-' || val[na + 1] != '-') return 0;
            if (depth >= CVR_MAX_DEPTH || --*budget < 0) return 0;
            /* A name that is absent, or present but itself unresolvable (a cycle,
             * CSS Variables 1 section 2.3), is guaranteed-invalid: the reference
             * takes its fallback. The partial expansion is rewound first. */
            const char *hit = scope_get(sc, val + na, nb - na);
            size_t mark = *o;
            if (hit == NULL ||
                !resolve_rec(hit, strlen(hit), out, outcap, o, sc, depth + 1, budget)) {
                *o = mark;
                if (comma >= argend || *budget < 0) return 0;
                size_t fa = comma + 1, fb = argend;
                while (fa < fb && is_ws(val[fa])) ++fa;
                while (fb > fa && is_ws(val[fb - 1])) --fb;
                if (!resolve_rec(val + fa, fb - fa, out, outcap, o, sc, depth + 1, budget))
                    return 0;
            }
            i = argend + 1;
            continue;
        }
        if (*o + 1 >= outcap) return 0;              /* overflow: fail closed */
        out[(*o)++] = val[i++];
    }
    return 1;
}

int cvr_resolve(const char *val, char *out, size_t outcap, const cvr_scope *sc) {
    if (val == NULL || out == NULL || outcap == 0) return 0;
    size_t o = 0;
    int budget = CVR_MAX_LOOKUPS;
    if (!resolve_rec(val, strlen(val), out, outcap, &o, sc, 0, &budget)) return 0;
    out[o] = '\0';
    return 1;
}

const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen) {
    return (name == NULL) ? NULL : scope_get(sc, name, nlen);
}
