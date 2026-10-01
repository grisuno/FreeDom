#ifndef FREEDOM_IMPORT_MAP_H
#define FREEDOM_IMPORT_MAP_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * import_map — <script type="importmap"> (WHATWG HTML 8.1.5.3). Pure, I/O-free: a
 * bounded parser for the one JSON shape an import map can take, and the specifier
 * resolution algorithm (scopes, exact and prefix matches). URL resolution is the
 * caller's (the same resolver the module loader uses). See spec/import_map.md.
 */

#define IM_MAX_TEXT    ((size_t)(1u * 1024u * 1024u))
#define IM_MAX_ENTRIES 4096u
#define IM_MAX_SCOPES  256u

/* Resolves ref against base into out (absolute URL); 0, or -1 when it cannot. */
typedef int (*im_url_fn)(void *ctx, const char *base, const char *ref, char *out, size_t outsz);

typedef struct im_map im_map;

/* Parses an import map's JSON, normalizing addresses (and URL-like keys, scope
 * prefixes) against doc_url with resolve. Invalid or over-bound input yields an EMPTY
 * map (fail closed = no mapping). NULL only on OOM. */
im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn resolve, void *ctx);

/* Resolves specifier as imported from base (the importing module's URL). 0 with the
 * absolute URL in out, or -1 (a bare specifier without a mapping, or overflow). */
int im_resolve(const im_map *m, const char *base, const char *specifier,
               im_url_fn resolve, void *ctx, char *out, size_t outsz);

/* Total entries (imports + every scope's). 0 for NULL. */
size_t im_count(const im_map *m);

/* NULL is a no-op. */
void im_free(im_map *m);

#endif /* FREEDOM_IMPORT_MAP_H */
