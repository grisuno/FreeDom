/*
 * hostblock — implementation: pure /etc/hosts-format host filter.
 *
 * Two string hash sets (blocklist, allowlist) with open addressing and FNV-1a
 * hashing. No I/O, no global mutable state; every domain is owned by the set and
 * freed once. The decision walks the host's domain suffixes: the allowlist wins
 * over the blocklist and both cover subdomains. On any malformed input the filter
 * fails OPEN (never over-blocks) -- it is an adblock-style filter, not a security
 * boundary.
 */

#include "hostblock.h"
#include "util.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HB_MAX_HOST   253u   /* longest domain we store or query */
#define HB_INIT_CAP   64u    /* initial slot count (power of two) */

/* --- string hash set (open addressing, linear probing) --- */

typedef struct hb_table {
    char  **slots;  /* NULL = empty slot; otherwise an owned NUL-terminated domain */
    size_t  cap;    /* slot count, a power of two, or 0 if unallocated */
    size_t  count;  /* number of occupied slots */
} hb_table;

struct hb_set {
    hb_table block;
    hb_table allow;
};


/* Finds the slot for key (length klen) in t, which must have a free slot. Returns
 * the index of either the matching entry or the first empty slot for it. */
static size_t table_probe(const hb_table *t, const char *key, size_t klen) {
    size_t mask = t->cap - 1;
    size_t i = (size_t)fnv1a(key, klen) & mask;
    while (t->slots[i] != NULL) {
        if (strlen(t->slots[i]) == klen && memcmp(t->slots[i], key, klen) == 0) break;
        i = (i + 1) & mask;
    }
    return i;
}

/* Grows (or first-allocates) t to newcap slots and rehashes. Returns 0, -1 OOM. */
static int table_grow(hb_table *t, size_t newcap) {
    char **ns = (char **)calloc(newcap, sizeof *ns);
    if (ns == NULL) return -1;

    char **old = t->slots;
    size_t oldcap = t->cap;
    t->slots = ns;
    t->cap = newcap;

    size_t mask = newcap - 1;
    for (size_t k = 0; k < oldcap; ++k) {
        if (old[k] == NULL) continue;
        size_t i = (size_t)fnv1a(old[k], strlen(old[k])) & mask;
        while (t->slots[i] != NULL) i = (i + 1) & mask;
        t->slots[i] = old[k];   /* move the existing owned string */
    }
    free(old);
    return 0;
}

/* Inserts key (length klen) into t, deduping. Returns 0 (inserted or already
 * present), -1 on OOM. */
static int table_insert(hb_table *t, const char *key, size_t klen) {
    /* Keep the load factor under 0.7 so probing stays cheap and terminates. */
    if (t->cap == 0) {
        if (table_grow(t, HB_INIT_CAP) != 0) return -1;
    } else if ((t->count + 1) * 10u >= t->cap * 7u) {
        if (table_grow(t, t->cap * 2u) != 0) return -1;
    }

    size_t i = table_probe(t, key, klen);
    if (t->slots[i] != NULL) return 0;   /* already present */

    if (klen == (size_t)-1) return -1;
    char *copy = (char *)malloc(klen + 1);
    if (copy == NULL) return -1;
    memcpy(copy, key, klen);
    copy[klen] = '\0';
    t->slots[i] = copy;
    t->count++;
    return 0;
}

static int table_contains(const hb_table *t, const char *key) {
    if (t->cap == 0) return 0;
    size_t i = table_probe(t, key, strlen(key));
    return t->slots[i] != NULL;
}

static void table_free(hb_table *t) {
    if (t->slots == NULL) return;
    for (size_t i = 0; i < t->cap; ++i) free(t->slots[i]);
    free(t->slots);
    t->slots = NULL; t->cap = 0; t->count = 0;
}

/* --- token helpers --- */

static char lower(char c) {
    return (c >= 'A' && c <= 'Z') ? (char)(c + ('a' - 'A')) : c;
}

/* A token made only of digits, '.' and ':' is an IP literal (v4 or v6), not a
 * domain. An empty token never reaches here. */
static int is_ip_token(const char *s, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        char c = s[i];
        if (!((c >= '0' && c <= '9') || c == '.' || c == ':')) return 0;
    }
    return 1;
}

/* True if c may appear in a domain we accept (after lowercasing). */
static int is_domain_char(char c) {
    return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')
        || c == '.' || c == '-' || c == '_';
}

/* Normalises a raw token into out (lowercased, one trailing dot trimmed) and
 * validates it (1..253 chars, domain charset). Returns the length, or 0 if the
 * token is not a domain we accept (caller skips it). */
static size_t normalise_domain(const char *tok, size_t n, char *out, size_t out_size) {
    if (n == 0 || n + 1 > out_size) return 0;
    for (size_t i = 0; i < n; ++i) out[i] = lower(tok[i]);
    out[n] = '\0';
    if (out[n - 1] == '.') { --n; out[n] = '\0'; }  /* trim one trailing dot */
    if (n == 0 || n > HB_MAX_HOST) return 0;
    for (size_t i = 0; i < n; ++i) {
        if (!is_domain_char(out[i])) return 0;
    }
    return n;
}

/* --- public --- */

hb_set *hb_new(void) {
    hb_set *s = (hb_set *)calloc(1, sizeof *s);
    return s;  /* both tables zeroed: slots NULL, cap 0, count 0 */
}

void hb_free(hb_set *s) {
    if (s == NULL) return;
    table_free(&s->block);
    table_free(&s->allow);
    free(s);
}

hb_status hb_load(hb_set *s, const char *text, hb_list list) {
    if (s == NULL || text == NULL) return HB_ERR_NULL_ARG;
    hb_table *t = (list == HB_LIST_ALLOW) ? &s->allow : &s->block;

    const char *p = text;
    char buf[HB_MAX_HOST + 2];
    while (*p != '\0') {
        /* One line: stop at '\n' or end; '#' starts a comment to end of line. */
        const char *line = p;
        while (*p != '\0' && *p != '\n') ++p;
        const char *line_end = p;
        if (*p == '\n') ++p;

        for (const char *q = line; q < line_end; ++q) {
            if (*q == '#') { line_end = q; break; }
        }

        /* Tokenise the line on ASCII whitespace. */
        const char *q = line;
        while (q < line_end) {
            while (q < line_end && (*q == ' ' || *q == '\t' || *q == '\r' ||
                                    *q == '\f' || *q == '\v')) ++q;
            const char *ts = q;
            while (q < line_end && !(*q == ' ' || *q == '\t' || *q == '\r' ||
                                     *q == '\f' || *q == '\v')) ++q;
            size_t tl = (size_t)(q - ts);
            if (tl == 0) continue;
            if (is_ip_token(ts, tl)) continue;

            size_t dl = normalise_domain(ts, tl, buf, sizeof buf);
            if (dl == 0) continue;  /* invalid token: skip, do not abort */
            if (table_insert(t, buf, dl) != 0) return HB_ERR_OOM;
        }
    }
    return HB_OK;
}

hb_decision hb_check(const hb_set *s, const char *host) {
    if (s == NULL || host == NULL) return HB_ALLOW;
    size_t n = strlen(host);
    if (n == 0 || n > HB_MAX_HOST) return HB_ALLOW;

    char buf[HB_MAX_HOST + 1];
    for (size_t i = 0; i < n; ++i) buf[i] = lower(host[i]);
    buf[n] = '\0';
    if (buf[n - 1] == '.') { --n; buf[n] = '\0'; }
    if (n == 0) return HB_ALLOW;

    /* Walk the domain suffixes from most to least specific. The allowlist wins, so
     * a match there short-circuits to ALLOW even if a broader suffix is blocked; a
     * block match is remembered but the scan continues in case a broader suffix is
     * allowlisted. */
    int blocked = 0;
    for (const char *suffix = buf; suffix != NULL; ) {
        if (table_contains(&s->allow, suffix)) return HB_ALLOW;
        if (!blocked && table_contains(&s->block, suffix)) blocked = 1;
        const char *dot = strchr(suffix, '.');
        suffix = (dot != NULL) ? dot + 1 : NULL;
    }
    return blocked ? HB_BLOCK : HB_ALLOW;
}

int hb_is_allowlisted(const hb_set *s, const char *host) {
    if (s == NULL || host == NULL) return 0;
    size_t n = strlen(host);
    if (n == 0 || n > HB_MAX_HOST) return 0;

    char buf[HB_MAX_HOST + 1];
    for (size_t i = 0; i < n; ++i) buf[i] = lower(host[i]);
    buf[n] = '\0';
    if (buf[n - 1] == '.') { --n; buf[n] = '\0'; }
    if (n == 0) return 0;

    /* Same suffix walk as hb_check's allowlist arm: an entry covers subdomains. */
    for (const char *suffix = buf; suffix != NULL; ) {
        if (table_contains(&s->allow, suffix)) return 1;
        const char *dot = strchr(suffix, '.');
        suffix = (dot != NULL) ? dot + 1 : NULL;
    }
    return 0;
}

size_t hb_count(const hb_set *s, hb_list list) {
    if (s == NULL) return 0;
    return (list == HB_LIST_ALLOW) ? s->allow.count : s->block.count;
}
