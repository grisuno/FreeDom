# include: prefetch

*Community 7 | 6 files | cohesion 0.56*

## Definition

This community groups 6 file(s) rooted at `include` with dominant language c (cohesion 0.56). Central symbols: `DOC`, `FREEDOM_IMPORT_MAP_H`, `FREEDOM_PREFETCH_H`, `IM_MAX_DEPTH`, `IM_MAX_ENTRIES`, `IM_MAX_SCOPES`, `IM_MAX_TEXT`, `IM_URL_MAX`. Core file: `src/prefetch.c` (30 symbols). Documented purpose: Tests for prefetch (Hito 29): pure lookahead scanner + parallel download pool..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/import_map.h` | h | utility | 10 | no |
| `include/prefetch.h` | h | utility | 28 | no |
| `src/import_map.c` | c | utility | 22 | no |
| `src/prefetch.c` | c | utility | 30 | no |
| `tests/test_import_map.c` | c | testing | 8 | no |
| `tests/test_prefetch.c` | c | testing | 18 | yes |

## Key Symbols

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
- `FREEDOM_PREFETCH_H` (macro, `include/prefetch.h:2`) `#define FREEDOM_PREFETCH_H`
- `pf_kind` (enum, `include/prefetch.h:35`) - Subresource kinds the lookahead scanner recognizes. Anything else (icons, preload hints, images) is
- `pf_ref` (struct, `include/prefetch.h:42`) - One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and valid
- `kind` (type_alias, `include/prefetch.h:42`) `typedef struct pf_ref { pf_kind kind;` - One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and valid
- `PF_MAX_REFS` (macro, `include/prefetch.h:47`) `#define PF_MAX_REFS`
- `PF_MAX_THREADS` (macro, `include/prefetch.h:48`) `#define PF_MAX_THREADS`
- `PF_MAX_JOBS` (macro, `include/prefetch.h:49`) `#define PF_MAX_JOBS`
- `PF_MAX_IMPORTS` (macro, `include/prefetch.h:50`) `#define PF_MAX_IMPORTS`
- `PF_SPEC_MAX` (macro, `include/prefetch.h:51`) `#define PF_SPEC_MAX`
- `refs` (type_alias, `include/prefetch.h:52`) `typedef struct pf_list { pf_ref refs[PF_MAX_REFS];` - One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and valid
- `pf_list` (struct, `include/prefetch.h:53`)
- `pf_scan` (function, `include/prefetch.h:62`) `int pf_scan(const char *html, size_t len, pf_list *out);` - Lookahead scan of hostile HTML. Fills out (owns the URLs; free with pf_list_free). Comment, <script>
- `pf_list_free` (function, `include/prefetch.h:63`) `void pf_list_free(pf_list *l);`
- `pf_job_state` (enum, `include/prefetch.h:73`)
- `pf_job` (struct, `include/prefetch.h:80`)
- `jobs` (type_alias, `include/prefetch.h:89`) `typedef struct pf_pool { pf_job jobs[PF_MAX_JOBS];`
- `pf_pool` (struct, `include/prefetch.h:90`)
- `specifiers` (function, `include/prefetch.h:110`) `* specifiers (each < PF_SPEC_MAX) into out[k] and returns how many. Pure. */ siz`
- `pf_find_importmap` (function, `include/prefetch.h:115`) `int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n);` - Span of the first <script type=importmap> body in html (pure, bounded): 1 with * [*start, *start + *
- `started` (function, `include/prefetch.h:121`) `* to fetch or no thread started (the caller fetches serially). */ int pf_pool_st`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 5
- Cross-boundary resolved imports (EXTRACTED): 4

## Connections

- [EXTRACTED] depends_on community 0 <-> 7 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefetch.h.
- [EXTRACTED] depends_on community 3 <-> 7 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/prefetch.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 5 file(s) lack file-level docs (e.g. `include/import_map.h`)? What purpose do they serve?
- What would break if the most connected file in include: prefetch changed?
- Should include: prefetch be split, given cohesion 0.56?

## Sources

- `include/import_map.h`
- `include/prefetch.h`
- `src/import_map.c`
- `src/prefetch.c`
- `tests/test_import_map.c`
- `tests/test_prefetch.c`
