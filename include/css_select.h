#ifndef FREEDOM_CSS_SELECT_H
#define FREEDOM_CSS_SELECT_H

#include <stddef.h>
#include <string.h>

#include "css.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * css_select — the selector engine of the author-CSS module: parsing one complex
 * selector into a css_sel and matching it against a css_element chain. Split out
 * of css.c (anti-monolith clause) so the cascade/value side and the selector side
 * stay independently auditable. Internal contract: consumed only by css.c and its
 * tests/fuzzers; the public browser-facing API remains css.h.
 *
 * Selectors are hostile remote content. The engine is pure (no allocation, no
 * I/O), bounded (CSS_MAX_COMPOUNDS / CSS_MAX_ATTR_SEL / CSS_TOK_MAX) and fails
 * closed: any unsupported or malformed construct drops the whole selector.
 * See spec/css_select.md.
 */

/* Bounds shared with the cascade side (css.c token buffers reuse CSS_TOK_MAX). */
#define CSS_TOK_MAX             64u
#define CSS_MAX_CLASSES_PER_SEL 6

/* Combinator joining a compound to the one on its left. */
enum { COMB_DESCENDANT = 0, COMB_CHILD = 1, COMB_ADJACENT = 2, COMB_GENERAL = 3 };

/* Attribute selector operator. PRESENT is bare `[attr]`; the rest carry a value. */
enum { ATTR_PRESENT = 0, ATTR_EQ, ATTR_TILDE, ATTR_PIPE, ATTR_CARET, ATTR_DOLLAR,
       ATTR_STAR };

/* Pseudo-class kind (Hito 23b-9). NEVER covers :visited (Zero Knowledge: no
 * history to match, and no CSS history sniffing). ALWAYS covers the dynamic
 * pseudos (:hover/:active/:focus/:focus-within/:focus-visible) — the cascade
 * is resolved once per load, so they always match: content hidden behind
 * :hover (common on Slashdot, menus etc.) becomes visible instead of
 * invisible. :visited stays NEVER (we never leak history). */
enum { PSEUDO_LINK = 0, PSEUDO_NEVER, PSEUDO_ALWAYS, PSEUDO_ROOT,
       PSEUDO_FIRST_CHILD, PSEUDO_LAST_CHILD, PSEUDO_ONLY_CHILD,
       PSEUDO_NTH_CHILD, PSEUDO_NTH_LAST_CHILD,
       PSEUDO_CHECKED, PSEUDO_DISABLED, PSEUDO_ENABLED,
       PSEUDO_NOT, PSEUDO_IS, PSEUDO_WHERE };

/* Sub-selector for :not()/:is()/:where(): a simple compound with only
 * tag/.class/#id (no combinators, no attributes, no pseudo-classes inside
 * sub-selectors). Bounded: CSS_MAX_SUB_SELS per selector, one level deep. */
#define CSS_MAX_SUB_SELS 4

typedef struct css_sub_sel {
    char tag[CSS_TOK_MAX];
    int  has_tag;
    char id[CSS_TOK_MAX];
    int  has_id;
    char cls[CSS_TOK_MAX];
    int  has_cls;
} css_sub_sel;

/* One pseudo-class inside a compound. a/b are the An+B coefficients of the
 * nth-child family (unused otherwise). sub_first/sub_count index into the
 * parent css_sel.subs[] for :not/:is/:where, or -1/0 for no sub-selectors. */
typedef struct css_pseudo_match {
    int kind;  /* PSEUDO_* */
    int a, b;
    int sub_first; /* first sub-selector in parent sel->subs[], -1 = none */
    int sub_count; /* number of consecutive sub-selectors */
} css_pseudo_match;

/* One attribute selector inside a compound: name OP value, with a case flag. */
typedef struct css_attr_match {
    char name[CSS_TOK_MAX];
    char value[CSS_TOK_MAX];
    int  op;   /* ATTR_* */
    int  ci;   /* 1 = match the value case-insensitively (the trailing `i` flag) */
} css_attr_match;

/* One compound selector: optional type, optional id, zero+ classes, zero+ [attr],
 * zero+ pseudo-classes. */
typedef struct css_compound {
    char tag[CSS_TOK_MAX];
    int  has_tag;
    char id[CSS_TOK_MAX];
    int  has_id;
    char cls[CSS_MAX_CLASSES_PER_SEL][CSS_TOK_MAX];
    int  ncls;
    css_attr_match attrs[CSS_MAX_ATTR_SEL];
    int  nattrs;
    css_pseudo_match pseudos[CSS_MAX_PSEUDO_SEL];
    int  npseudo;
} css_compound;

/* A complex selector: a chain of compounds, parts[nparts-1] being the subject (the
 * element a rule styles). comb[k] (k>=1) is the combinator to the LEFT of parts[k];
 * comb[0] is unused. A single compound is nparts == 1. subs[] holds sub-selectors
 * for :not()/:is()/:where() pseudo-classes, indexed by css_pseudo_match.sub_first. */
typedef struct css_sel {
    css_compound parts[CSS_MAX_COMPOUNDS];
    int  comb[CSS_MAX_COMPOUNDS];
    int  nparts;
    int  spec;
    int  order;     /* document order (tie-break) */
    int  rule;      /* index into rules[] */
    css_sub_sel subs[CSS_MAX_SUB_SELS];
    int  nsubs;
} css_sel;

/* Parses the complex selector s[a,b) into *sel (spec computed; order/rule left to
 * the caller). Returns 1 if supported, 0 to drop the selector (fail closed). */
int csel_parse(const char *s, size_t a, size_t b, css_sel *sel);

/* True if *sel matches element *el against its ancestor chain. Pure, bounded. */
int csel_matches(const css_sel *sel, const css_element *el);

/* --- ASCII helpers shared by the selector and cascade sides (internal) --- */

static inline char csel_lower_ch(char c) {
    return (c >= 'A' && c <= 'Z') ? (char)(c + 32) : c;
}

static inline int csel_ci_eq(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        if (csel_lower_ch(*a) != csel_lower_ch(*b)) return 0;
        ++a; ++b;
    }
    return *a == '\0' && *b == '\0';
}

/* True if a[0,n) equals b[0,n) up to n chars (b NUL-terminated), case-folded when ci. */
static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci) {
    for (size_t i = 0; i < n; ++i) {
        char x = a[i], y = b[i];
        if (ci) { x = csel_lower_ch(x); y = csel_lower_ch(y); }
        if (x != y) return 0;
    }
    return 1;
}

/* Substring test (used both to drop any value carrying url() — always ci — and by
 * the attribute `*=` operator). A non-empty needle only; an empty one never matches. */
static inline int csel_substr(const char *hay, const char *needle, int ci) {
    size_t nl = strlen(needle), hl = strlen(hay);
    if (nl == 0 || nl > hl) return 0;
    for (size_t off = 0; off + nl <= hl; ++off)
        if (csel_span_eq(hay + off, needle, nl, ci)) return 1;
    return 0;
}

static inline int csel_ident_ch(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '_' || c == '-';
}

#endif /* FREEDOM_CSS_SELECT_H */
