#ifndef FREEDOM_CSS_VARS_H
#define FREEDOM_CSS_VARS_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * css_vars -- the custom-property table and var() substitution (CSS Variables 1),
 * extracted from css.c. Pure: no I/O, no DOM; every allocation is owned by the
 * table and released by cvr_reset/cvr_free. See spec/css_vars.md.
 *
 * Bounds (anti-DoS). They sit above what real design systems ship -- measured on
 * github.com's Primer: 2443 distinct names, values past 64 bytes, 4-hop chains --
 * because a bound an ordinary page reaches is a render bug, not a defence.
 */
#define CVR_NAME_MAX    256u    /* bytes of "--name", NUL excluded, exclusive */
#define CVR_VALUE_MAX   1024u   /* bytes of a stored value, exclusive (== CSS_URL_MAX) */
#define CVR_MAX_ENTRIES 65536u  /* distinct names per table */
#define CVR_MAX_DEPTH   32      /* nested lookups per substitution */
/* Total var() lookups one substitution may perform. Depth alone does not bound
 * the work once an unresolvable reference falls back: `--a: var(--a, var(--a))`
 * retries both branches at every level, 2^depth lookups. */
#define CVR_MAX_LOOKUPS 1024

typedef struct cvr_ent {
    char *name;   /* "--ident", owned */
    char *value;  /* trimmed, !important stripped, owned */
} cvr_ent;

/* Zero-initialise ({0}) before first use. Open-addressed hash index over ent[]:
 * slot[] holds entry index + 1, 0 = empty; nslot is a power of two >= 2 * cap. */
typedef struct cvr_table {
    cvr_ent *ent;
    size_t   n, cap;
    size_t  *slot;
    size_t   nslot;
} cvr_table;

/* An element's INHERITED custom properties (spec/css_vars.md, "Alcance por
 * elemento"): one node per ancestor that declares any, nearest first. Walks are
 * bounded by CVR_CHAIN_MAX nodes. */
#define CVR_CHAIN_MAX 256
typedef struct cvr_chain {
    const cvr_table        *own;
    const struct cvr_chain *parent;
} cvr_chain;

/* Lookup order for one substitution: first, then the inherited chain, then second
 * (the sheet's page-global table), then initial (@property initial-value). Any may
 * be NULL; `first` wins a name collision. */
typedef struct cvr_scope {
    const cvr_table *first;
    const cvr_table *second;
    const cvr_chain *chain;
    const cvr_table *initial;
} cvr_scope;

/* Stores name[0,nlen) -> value[0,vlen), overwriting an existing entry of the same
 * name (last declaration wins). Returns 1 when stored, 0 when dropped: a name that
 * is not "--" + at least one byte, a name or value at/over its bound, an empty
 * value, the entry bound reached, or OOM. Dropped means absent, never truncated. */
int cvr_set(cvr_table *t, const char *name, size_t nlen, const char *value, size_t vlen);

/* The stored value for name[0,nlen), or NULL. Case-sensitive (custom property
 * names are). t may be NULL. */
const char *cvr_get(const cvr_table *t, const char *name, size_t nlen);

size_t cvr_count(const cvr_table *t);

/* Frees every stored string and empties the table, keeping its arrays for reuse.
 * NULL-safe. */
void cvr_reset(cvr_table *t);

/* Releases everything; the table is left zeroed and reusable. Idempotent. */
void cvr_free(cvr_table *t);

/* Scans the declaration span s[a,b) for `--ident : value` pairs and stores each
 * (a trailing !important is stripped). A name is recognised only where it cannot
 * be the tail of a longer identifier. */
void cvr_collect_decls(cvr_table *t, const char *s, size_t a, size_t b);

/* Copies val into out (NUL-terminated, at most outcap bytes including the NUL),
 * expanding every var(--name[, fallback]) against sc, recursively and bounded by
 * CVR_MAX_DEPTH and CVR_MAX_LOOKUPS. A reference whose name is absent OR whose own
 * value does not resolve (a cycle) takes its fallback. Returns 1 on success; 0 on
 * such a reference without fallback, a malformed var(), the lookup budget spent, or
 * output overflow -- the caller
 * then drops the whole declaration (CSS Variables 1: invalid at computed time). */
int cvr_resolve(const char *val, char *out, size_t outcap, const cvr_scope *sc);

/* The value name[0,nlen) has in scope sc (same lookup order as cvr_resolve), or
 * NULL. Not substituted: the stored text. */
const char *cvr_lookup(const cvr_scope *sc, const char *name, size_t nlen);

#endif /* FREEDOM_CSS_VARS_H */
