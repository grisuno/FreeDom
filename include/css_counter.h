/*
 * css_counter -- CSS counters (spec/css_counter.md). Pure: no I/O, bounded state.
 *
 * Parsing validates hostile stylesheet text; the state machine is driven in document
 * order by page_view, which owns the DOM walk. A counter's value depends on position,
 * so it can never be resolved inside the (per-element, memoized) cascade.
 */
#ifndef FREEDOM_CSS_COUNTER_H
#define FREEDOM_CSS_COUNTER_H

#include <stddef.h>

#ifndef __STDC_VERSION__
#error "css_counter requires C11"
#endif

#define CNT_MAX_DECL       4
#define CNT_MAX_INSTANCES  1024
#define CNT_NAME_MAX       64

typedef struct cnt_decl {
    unsigned name;   /* cnt_hash of the identifier */
    int      value;
} cnt_decl;

typedef enum cnt_style {
    CNT_DECIMAL = 0, CNT_DECIMAL_ZERO, CNT_LOWER_ROMAN, CNT_UPPER_ROMAN,
    CNT_LOWER_ALPHA, CNT_UPPER_ALPHA, CNT_LOWER_GREEK, CNT_DISC, CNT_CIRCLE,
    CNT_SQUARE, CNT_NONE
} cnt_style;

/* FNV-1a over `len` bytes of an identifier, ASCII case preserved (identifiers are
 * case-sensitive). Never 0. */
unsigned cnt_hash(const char *name, size_t len);

/* Parses a counter-reset / counter-increment value. Returns the number of entries
 * written (0 for `none`) or -1 when invalid. `dflt` is the value of an entry with no
 * integer: 0 for reset, 1 for increment. */
int cnt_parse_decls(const char *val, int dflt, cnt_decl out[CNT_MAX_DECL]);

/* Parses a `content` value that uses counter()/counters(). Writes a marker into
 * `out` and returns 1; returns 0 when the value has no counter function (not this
 * module's), -1 when it is malformed or does not fit in `cap`. */
int cnt_parse_content(const char *val, char *out, size_t cap);
int cnt_is_marker(const char *s);

/* Formats `value` in `style` (unknown or unrepresentable falls back to decimal).
 * Returns the length written; always NUL-terminated when cap > 0. */
size_t cnt_format(int style, long value, char *out, size_t cap);

typedef struct cnt_state cnt_state;
cnt_state *cnt_state_new(void);
void       cnt_state_free(cnt_state *s);

/* An element at tree depth `depth` runs these in order: reset, then increment. */
void cnt_reset(cnt_state *s, int depth, const cnt_decl *d, int n);
void cnt_increment(cnt_state *s, int depth, const cnt_decl *d, int n);
/* The children of an element have all been walked: drop what they created
 * (instances created at depth >= `depth`, i.e. the children's depth). */
void cnt_leave(cnt_state *s, int depth);

/* Attribute lookup for attr() items; returns NULL when absent. */
typedef const char *(*cnt_attr_fn)(void *ctx, const char *name);

/* Expands a marker against the live state. A string that is not a marker is copied
 * verbatim. Returns the length written, NUL-terminated, never beyond `cap`. */
size_t cnt_resolve(const cnt_state *s, const char *marker, cnt_attr_fn attr, void *ctx,
                   char *out, size_t cap);

#endif
