/*
 * import_map — implementation. See spec/import_map.md.
 *
 * The JSON reader accepts exactly what an import map is: a top-level object whose
 * "imports" is an object of strings and whose "scopes" is an object of such objects.
 * Other top-level members are skipped (bounded); anything malformed or over a bound
 * yields an EMPTY map -- fail closed to "no mapping", the behaviour before import maps.
 */

#include "import_map.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define IM_MAX_DEPTH 3          /* JSON nesting accepted anywhere in the text */
#define IM_URL_MAX   8192u      /* resolved URL buffer (url.h's URL_MAX_LEN) */

typedef struct im_entry {
    int   scope;      /* index into scopes[], or -1 for top-level "imports" */
    char *key;        /* normalized specifier key */
    char *addr;       /* resolved address */
} im_entry;

struct im_map {
    im_entry *e;
    size_t    n, cap;
    char    **scopes; /* resolved scope prefixes */
    size_t    nscopes;
};

/* --- bounded JSON reader --- */

typedef struct jr {
    const char *p, *end;
    int         bad;
} jr;

static void ws(jr *r) {
    while (r->p < r->end && (*r->p == ' ' || *r->p == '\t' || *r->p == '\n' || *r->p == '\r'))
        r->p++;
}

static int eat(jr *r, char c) {
    ws(r);
    if (r->p < r->end && *r->p == c) { r->p++; return 1; }
    return 0;
}

static int hex4(const char *s, uint32_t *out) {
    uint32_t v = 0;
    for (int i = 0; i < 4; ++i) {
        char c = s[i];
        v <<= 4;
        if (c >= '0' && c <= '9') v |= (uint32_t)(c - '0');
        else if (c >= 'a' && c <= 'f') v |= (uint32_t)(c - 'a' + 10);
        else if (c >= 'A' && c <= 'F') v |= (uint32_t)(c - 'A' + 10);
        else return -1;
    }
    *out = v;
    return 0;
}

static size_t put_utf8(char *o, uint32_t cp) {
    if (cp < 0x80) { o[0] = (char)cp; return 1; }
    if (cp < 0x800) { o[0] = (char)(0xC0 | (cp >> 6)); o[1] = (char)(0x80 | (cp & 0x3F)); return 2; }
    if (cp < 0x10000) {
        o[0] = (char)(0xE0 | (cp >> 12)); o[1] = (char)(0x80 | ((cp >> 6) & 0x3F));
        o[2] = (char)(0x80 | (cp & 0x3F)); return 3;
    }
    o[0] = (char)(0xF0 | (cp >> 18)); o[1] = (char)(0x80 | ((cp >> 12) & 0x3F));
    o[2] = (char)(0x80 | ((cp >> 6) & 0x3F)); o[3] = (char)(0x80 | (cp & 0x3F));
    return 4;
}

/* A JSON string into an owned UTF-8 buffer (escapes decoded; a lone surrogate or a
 * raw control character is malformed). NULL on failure (r->bad set). */
static char *str(jr *r) {
    ws(r);
    if (r->p >= r->end || *r->p != '"') { r->bad = 1; return NULL; }
    r->p++;
    size_t cap = (size_t)(r->end - r->p);
    char *o = (char *)malloc(cap + 1);   /* decoding never grows the text */
    if (o == NULL) { r->bad = 1; return NULL; }
    size_t n = 0;
    while (r->p < r->end) {
        unsigned char c = (unsigned char)*r->p++;
        if (c == '"') { o[n] = '\0'; return o; }
        if (c < 0x20) break;
        if (c != '\\') { o[n++] = (char)c; continue; }
        if (r->p >= r->end) break;
        char e = *r->p++;
        switch (e) {
            case '"': o[n++] = '"'; break;
            case '\\': o[n++] = '\\'; break;
            case '/': o[n++] = '/'; break;
            case 'b': o[n++] = '\b'; break;
            case 'f': o[n++] = '\f'; break;
            case 'n': o[n++] = '\n'; break;
            case 'r': o[n++] = '\r'; break;
            case 't': o[n++] = '\t'; break;
            case 'u': {
                uint32_t cp;
                if (r->end - r->p < 4 || hex4(r->p, &cp) != 0) goto fail;
                r->p += 4;
                if (cp >= 0xD800 && cp <= 0xDBFF) {
                    uint32_t lo;
                    if (r->end - r->p < 6 || r->p[0] != '\\' || r->p[1] != 'u'
                        || hex4(r->p + 2, &lo) != 0 || lo < 0xDC00 || lo > 0xDFFF) goto fail;
                    r->p += 6;
                    cp = 0x10000 + ((cp - 0xD800) << 10) + (lo - 0xDC00);
                } else if (cp >= 0xDC00 && cp <= 0xDFFF) {
                    goto fail;
                }
                n += put_utf8(o + n, cp);   /* <= the 6/12 escape bytes it replaces */
                break;
            }
            default: goto fail;
        }
    }
fail:
    free(o);
    r->bad = 1;
    return NULL;
}

/* Skips any JSON value (for ignored members), bounded by depth. */
static void skip(jr *r, int depth) {
    ws(r);
    if (r->p >= r->end || depth > IM_MAX_DEPTH) { r->bad = 1; return; }
    char c = *r->p;
    if (c == '"') { free(str(r)); return; }
    if (c == '{' || c == '[') {
        char close = (c == '{') ? '}' : ']';
        r->p++;
        if (eat(r, close)) return;
        do {
            if (c == '{') { free(str(r)); if (r->bad || !eat(r, ':')) { r->bad = 1; return; } }
            skip(r, depth + 1);
            if (r->bad) return;
        } while (eat(r, ','));
        if (!eat(r, close)) r->bad = 1;
        return;
    }
    /* number / true / false / null: a run of their characters */
    const char *s = r->p;
    while (r->p < r->end && ((*r->p >= '0' && *r->p <= '9') || *r->p == '-' || *r->p == '+'
                             || *r->p == '.' || *r->p == 'e' || *r->p == 'E'
                             || (*r->p >= 'a' && *r->p <= 'z')))
        r->p++;
    if (r->p == s) r->bad = 1;
}

/* --- map building --- */

static int url_like(const char *s) {
    if (s[0] == '/' || strncmp(s, "./", 2) == 0 || strncmp(s, "../", 3) == 0) return 1;
    /* RFC 3986 scheme: ALPHA *( ALPHA / DIGIT / "+" / "-" / "." ) ":" */
    if (!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))) return 0;
    for (const char *p = s + 1; *p; ++p) {
        if (*p == ':') return 1;
        if (!((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9')
              || *p == '+' || *p == '-' || *p == '.')) return 0;
    }
    return 0;
}

static char *dup_s(const char *s) {
    size_t n = strlen(s);
    char *d = (char *)malloc(n + 1);
    if (d != NULL) memcpy(d, s, n + 1);
    return d;
}

static void clear(im_map *m) {
    for (size_t i = 0; i < m->n; ++i) { free(m->e[i].key); free(m->e[i].addr); }
    free(m->e);
    for (size_t i = 0; i < m->nscopes; ++i) free(m->scopes[i]);
    free(m->scopes);
    m->e = NULL; m->n = m->cap = 0;
    m->scopes = NULL; m->nscopes = 0;
}

/* Adds (key, addr) normalized against doc_url; an unresolvable pair is dropped. */
static int add(im_map *m, int scope, const char *key, const char *addr, const char *doc_url,
               im_url_fn resolve, void *ctx) {
    if (m->n >= IM_MAX_ENTRIES) return -1;
    char kb[IM_URL_MAX], ab[IM_URL_MAX];
    const char *k = key;
    if (url_like(key)) {
        if (resolve(ctx, doc_url, key, kb, sizeof kb) != 0) return 0;
        k = kb;
    }
    if (resolve(ctx, doc_url, addr, ab, sizeof ab) != 0) return 0;
    if (m->n == m->cap) {
        size_t nc = m->cap ? m->cap * 2 : 16;
        im_entry *g = (im_entry *)realloc(m->e, nc * sizeof *g);
        if (g == NULL) return -1;
        m->e = g; m->cap = nc;
    }
    char *kc = dup_s(k), *ac = dup_s(ab);
    if (kc == NULL || ac == NULL) { free(kc); free(ac); return -1; }
    m->e[m->n].scope = scope; m->e[m->n].key = kc; m->e[m->n].addr = ac;
    m->n++;
    return 0;
}

/* An object of string -> string, added under scope. */
static void specifier_map(jr *r, im_map *m, int scope, const char *doc_url,
                          im_url_fn resolve, void *ctx) {
    if (!eat(r, '{')) { r->bad = 1; return; }
    if (eat(r, '}')) return;
    do {
        char *k = str(r);
        if (r->bad || !eat(r, ':')) { free(k); r->bad = 1; return; }
        char *v = str(r);
        if (r->bad) { free(k); return; }
        if (add(m, scope, k, v, doc_url, resolve, ctx) != 0) r->bad = 1;
        free(k); free(v);
        if (r->bad) return;
    } while (eat(r, ','));
    if (!eat(r, '}')) r->bad = 1;
}

im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn resolve, void *ctx) {
    im_map *m = (im_map *)calloc(1, sizeof *m);
    if (m == NULL) return NULL;
    if (json == NULL || doc_url == NULL || resolve == NULL || len > IM_MAX_TEXT) return m;
    jr r = { json, json + len, 0 };
    if (!eat(&r, '{')) return m;
    if (!eat(&r, '}')) {
        do {
            char *name = str(&r);
            if (r.bad || !eat(&r, ':')) { free(name); r.bad = 1; break; }
            if (strcmp(name, "imports") == 0) {
                specifier_map(&r, m, -1, doc_url, resolve, ctx);
            } else if (strcmp(name, "scopes") == 0) {
                if (!eat(&r, '{')) { r.bad = 1; }
                else if (!eat(&r, '}')) {
                    do {
                        char *prefix = str(&r);
                        if (r.bad || !eat(&r, ':') || m->nscopes >= IM_MAX_SCOPES) {
                            free(prefix); r.bad = 1; break;
                        }
                        char pb[IM_URL_MAX];
                        int ok = (resolve(ctx, doc_url, prefix, pb, sizeof pb) == 0);
                        free(prefix);
                        char **g = (char **)realloc(m->scopes, (m->nscopes + 1) * sizeof *g);
                        if (g == NULL) { r.bad = 1; break; }
                        m->scopes = g;
                        m->scopes[m->nscopes] = dup_s(ok ? pb : "");
                        if (m->scopes[m->nscopes] == NULL) { r.bad = 1; break; }
                        m->nscopes++;
                        specifier_map(&r, m, (int)m->nscopes - 1, doc_url, resolve, ctx);
                    } while (!r.bad && eat(&r, ','));
                    if (!r.bad && !eat(&r, '}')) r.bad = 1;
                }
            } else {
                skip(&r, 1);
            }
            free(name);
        } while (!r.bad && eat(&r, ','));
        if (!r.bad && !eat(&r, '}')) r.bad = 1;
    }
    ws(&r);
    if (r.bad || r.p != r.end) clear(m);   /* malformed or trailing bytes: empty map */
    return m;
}

/* WHATWG "resolve an imports match" within one specifier map (scope). 1 = matched
 * (out filled), 0 = no match, -1 = a match that is an error (prefix to non-'/'). */
static int match(const im_map *m, int scope, const char *key, char *out, size_t outsz) {
    const im_entry *best = NULL;
    size_t best_len = 0;
    for (size_t i = 0; i < m->n; ++i) {
        const im_entry *e = &m->e[i];
        if (e->scope != scope) continue;
        if (strcmp(e->key, key) == 0) {
            size_t n = strlen(e->addr);
            if (n >= outsz) return -1;
            memcpy(out, e->addr, n + 1);
            return 1;
        }
        size_t kl = strlen(e->key);
        if (kl > 0 && e->key[kl - 1] == '/' && strncmp(key, e->key, kl) == 0 && kl > best_len) {
            best = e;
            best_len = kl;
        }
    }
    if (best == NULL) return 0;
    size_t al = strlen(best->addr);
    if (al == 0 || best->addr[al - 1] != '/') return -1;
    const char *rest = key + best_len;
    size_t rl = strlen(rest);
    if (al + rl >= outsz) return -1;
    memcpy(out, best->addr, al);
    memcpy(out + al, rest, rl + 1);
    return 1;
}

int im_resolve(const im_map *m, const char *base, const char *specifier,
               im_url_fn resolve, void *ctx, char *out, size_t outsz) {
    if (base == NULL || specifier == NULL || resolve == NULL || out == NULL || outsz == 0)
        return -1;
    char as_url[IM_URL_MAX];
    int have_url = url_like(specifier)
                   && resolve(ctx, base, specifier, as_url, sizeof as_url) == 0;
    const char *key = have_url ? as_url : specifier;
    if (m != NULL) {
        /* Scopes whose prefix matches base, longest prefix first. */
        int tried[IM_MAX_SCOPES];
        memset(tried, 0, sizeof tried);
        for (size_t round = 0; round < m->nscopes; ++round) {
            int pick = -1;
            size_t pick_len = 0;
            for (size_t s = 0; s < m->nscopes; ++s) {
                const char *pre = m->scopes[s];
                size_t pl = strlen(pre);
                if (tried[s] || pl == 0) continue;
                int hit = (strcmp(pre, base) == 0)
                          || (pre[pl - 1] == '/' && strncmp(base, pre, pl) == 0);
                if (hit && pl >= pick_len) { pick = (int)s; pick_len = pl; }
            }
            if (pick < 0) break;
            tried[pick] = 1;
            int r = match(m, pick, key, out, outsz);
            if (r != 0) return (r > 0) ? 0 : -1;
        }
        int r = match(m, -1, key, out, outsz);
        if (r != 0) return (r > 0) ? 0 : -1;
    }
    if (!have_url) return -1;                  /* a bare specifier nobody mapped */
    size_t n = strlen(as_url);
    if (n >= outsz) return -1;
    memcpy(out, as_url, n + 1);
    return 0;
}

size_t im_count(const im_map *m) {
    return (m != NULL) ? m->n : 0;
}

void im_free(im_map *m) {
    if (m == NULL) return;
    clear(m);
    free(m);
}
