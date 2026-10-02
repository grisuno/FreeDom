# include

*Community 6 | 4 files | cohesion 0.75*

## Definition

This community groups 4 file(s) rooted at `include` with dominant language c (cohesion 0.75). Central symbols: `DOC`, `FREEDOM_IMPORT_MAP_H`, `IM_MAX_DEPTH`, `IM_MAX_ENTRIES`, `IM_MAX_SCOPES`, `IM_MAX_TEXT`, `IM_URL_MAX`, `LLVMFuzzerTestOneInput`. Core file: `src/import_map.c` (22 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_import_map.c` | c | utility | 2 | no |
| `include/import_map.h` | h | utility | 10 | no |
| `src/import_map.c` | c | utility | 22 | no |
| `tests/test_import_map.c` | c | testing | 8 | no |

## Key Symbols

- `fres` (function, `fuzz/fuzz_import_map.c:17`) `static int fres(void *ctx, const char *base, const char *ref, char *out, size_t`
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_import_map.c:24`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_IMPORT_MAP_H` (macro, `include/import_map.h:2`) `#define FREEDOM_IMPORT_MAP_H`
- `algorithm` (function, `include/import_map.h:13`) `* resolution algorithm (scopes, exact and prefix matches). URL resolution is the`
- `IM_MAX_TEXT` (macro, `include/import_map.h:17`) `#define IM_MAX_TEXT`
- `IM_MAX_ENTRIES` (macro, `include/import_map.h:18`) `#define IM_MAX_ENTRIES`
- `IM_MAX_SCOPES` (macro, `include/import_map.h:19`) `#define IM_MAX_SCOPES`
- `im_map` (type_alias, `include/import_map.h:23`) `typedef struct im_map im_map;`
- `map` (function, `include/import_map.h:28`) `* map (fail closed = no mapping). NULL only on OOM. */ im_map *im_parse(const ch`
- `im_resolve` (function, `include/import_map.h:33`) `int im_resolve(const im_map *m, const char *base, const char *specifier, im_url_` - Resolves specifier as imported from base (the importing module's URL). 0 with the * absolute URL in
- `im_count` (function, `include/import_map.h:37`) `size_t im_count(const im_map *m);` - Resolves specifier as imported from base (the importing module's URL). 0 with the * absolute URL in
- `im_free` (function, `include/import_map.h:40`) `void im_free(im_map *m);` - Resolves specifier as imported from base (the importing module's URL). 0 with the * absolute URL in
- `IM_MAX_DEPTH` (macro, `src/import_map.c:16`) `#define IM_MAX_DEPTH`
- `IM_URL_MAX` (macro, `src/import_map.c:17`) `#define IM_URL_MAX`
- `scope` (type_alias, `src/import_map.c:18`) `typedef struct im_entry { int scope;` - The JSON reader accepts exactly what an import map is: a top-level object whose "imports" is an obje
- `im_entry` (struct, `src/import_map.c:19`)
- `im_map` (struct, `src/import_map.c:25`)
- `jr` (struct, `src/import_map.c:34`)
- `ws` (function, `src/import_map.c:39`) `static void ws(jr *r)`
- `eat` (function, `src/import_map.c:44`) `static int eat(jr *r, char c)`
- `hex4` (function, `src/import_map.c:50`) `static int hex4(const char *s, uint32_t *out)`
- `put_utf8` (function, `src/import_map.c:64`) `static size_t put_utf8(char *o, uint32_t cp)`
- `str` (function, `src/import_map.c:78`) `static char *str(jr *r)` - A JSON string into an owned UTF-8 buffer (escapes decoded; a lone surrogate or a * raw control chara
- `skip` (function, `src/import_map.c:128`) `static void skip(jr *r, int depth)` - } n += put_utf8(o + n, cp);   /* <= the 6/12 escape bytes it replaces break; } default: goto fail; }
- `url_like` (function, `src/import_map.c:156`) `static int url_like(const char *s)`
- `dup_s` (function, `src/import_map.c:168`) `static char *dup_s(const char *s)`
- `clear` (function, `src/import_map.c:175`) `static void clear(im_map *m)`
- `add` (function, `src/import_map.c:185`) `static int add(im_map *m, int scope, const char *key, const char *addr, const ch` - if (d != NULL) memcpy(d, s, n + 1); return d; } static void clear(im_map *m) { for (size_t i = 0; i
- `specifier_map` (function, `src/import_map.c:209`) `static void specifier_map(jr *r, im_map *m, int scope, const char *doc_url,` - if (m->n == m->cap) { size_t nc = m->cap ? m->cap * 2 : 16; im_entry *g = (im_entry *)realloc(m->e,
- `im_parse` (function, `src/import_map.c:225`) `im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn re`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 3
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 4 file(s) lack file-level docs (e.g. `fuzz/fuzz_import_map.c`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.75?

## Sources

- `fuzz/fuzz_import_map.c`
- `include/import_map.h`
- `src/import_map.c`
- `tests/test_import_map.c`
