# include: tab

*Community 8 | 7 files | cohesion 0.41*

## Definition

This community groups 7 file(s) rooted at `include` with dominant language c (cohesion 0.41). Central symbols: `FBK_MAX_DEPTH`, `FBK_MAX_FRAMES`, `FBK_MAX_MSG`, `FBK_ORIGIN_MAX`, `FBK_URL_MAX`, `FH_MAX_DEPTH`, `FREEDOM_FRAME_BROKER_H`, `FREEDOM_FRAME_HOST_H`. Core file: `include/tab.h` (49 symbols). Documented purpose: test_frame_broker -- CMocka suite for the pure iframe tree + postMessage router..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/frame_broker.h` | h | utility | 17 | no |
| `include/frame_host.h` | h | utility | 11 | no |
| `include/tab.h` | h | utility | 49 | no |
| `src/frame_broker.c` | c | utility | 10 | no |
| `src/frame_host.c` | c | utility | 16 | no |
| `tests/test_frame_broker.c` | c | testing | 10 | yes |
| `tests/test_frame_host.c` | c | testing | 9 | no |

## Key Symbols

- `FREEDOM_FRAME_BROKER_H` (macro, `include/frame_broker.h:2`) `#define FREEDOM_FRAME_BROKER_H`
- `FBK_MAX_FRAMES` (macro, `include/frame_broker.h:16`) `#define FBK_MAX_FRAMES`
- `FBK_MAX_DEPTH` (macro, `include/frame_broker.h:17`) `#define FBK_MAX_DEPTH`
- `FBK_MAX_MSG` (macro, `include/frame_broker.h:18`) `#define FBK_MAX_MSG`
- `FBK_ORIGIN_MAX` (macro, `include/frame_broker.h:19`) `#define FBK_ORIGIN_MAX`
- `FBK_URL_MAX` (macro, `include/frame_broker.h:20`) `#define FBK_URL_MAX`
- `fbk_rel` (enum, `include/frame_broker.h:22`)
- `fbk_verdict` (enum, `include/frame_broker.h:24`)
- `used` (type_alias, `include/frame_broker.h:30`) `typedef struct fbk_frame { int used;`
- `fbk_frame` (struct, `include/frame_broker.h:31`)
- `f` (type_alias, `include/frame_broker.h:37`) `typedef struct fbk_table { fbk_frame f[FBK_MAX_FRAMES];`
- `fbk_table` (struct, `include/frame_broker.h:38`)
- `fbk_origin_of` (function, `include/frame_broker.h:42`) `int fbk_origin_of(const char *url, char *out, size_t cap);` - Serialized origin ("https://host[:port]", lowercase) or "null" for opaque/non-https/unparseable. * 0
- `fbk_init` (function, `include/frame_broker.h:45`) `int fbk_init(fbk_table *t, const char *top_url);` - Serialized origin ("https://host[:port]", lowercase) or "null" for opaque/non-https/unparseable. * 0
- `fbk_add` (function, `include/frame_broker.h:49`) `int fbk_add(fbk_table *t, int parent, const char *url, int *out_id);` - Adds a child of `parent` for url. Writes its id. 0 on success; -1 on a bad parent, depth over * FBK_
- `fbk_remove` (function, `include/frame_broker.h:52`) `void fbk_remove(fbk_table *t, int id);` - Adds a child of `parent` for url. Writes its id. 0 on success; -1 on a bad parent, depth over * FBK_
- `fbk_origin` (function, `include/frame_broker.h:55`) `const char *fbk_origin(const fbk_table *t, int id);` - Adds a child of `parent` for url. Writes its id. 0 on success; -1 on a bad parent, depth over * FBK_
- `FREEDOM_FRAME_HOST_H` (macro, `include/frame_host.h:2`) `#define FREEDOM_FRAME_HOST_H`
- `FH_MAX_DEPTH` (macro, `include/frame_host.h:18`) `#define FH_MAX_DEPTH`
- `fh_host` (type_alias, `include/frame_host.h:19`) `typedef struct fh_host fh_host;` - frame_host -- trusted-parent side of iframes: one confined worker tab per frame, messages routed wit
- `fh_new` (function, `include/frame_host.h:28`) `fh_host *fh_new(const char *top_url, tab_fetch_fn fetch, void *fetch_ctx, fh_top` - top_url: the trusted top document; fetch/fetch_ctx: the page's policy-gated subresource fetcher (use
- `fh_free` (function, `include/frame_host.h:32`) `void fh_free(fh_host *h);` - top_url: the trusted top document; fetch/fetch_ctx: the page's policy-gated subresource fetcher (use
- `fh_apply_top` (function, `include/frame_host.h:36`) `void fh_apply_top(fh_host *h, const tab_page *page);` - Processes the frame ops (kinds FRAME_OPEN/CLOSE/POST) among page->ws of the TOP document; other * ki
- `fh_tick` (function, `include/frame_host.h:40`) `int fh_tick(fh_host *h, int elapsed_ms);` - Advances every frame's virtual clock by elapsed_ms and processes what they posted. Returns the * sma
- `fh_count` (function, `include/frame_host.h:43`) `int fh_count(const fh_host *h);` - Advances every frame's virtual clock by elapsed_ms and processes what they posted. Returns the * sma
- `it` (function, `include/frame_host.h:46`) `* confined worker last built it (NULL when no live frame has that URL);`
- `fh_frame_view` (function, `include/frame_host.h:49`) `const pv_view *fh_frame_view(const fh_host *h, const char *url, tab **t_out);` - Painting (spec/frame_broker.md section 5). The document of the frame loaded from `url`, as its confi
- `fh_generation` (function, `include/frame_host.h:52`) `unsigned fh_generation(const fh_host *h);` - Painting (spec/frame_broker.md section 5). The document of the frame loaded from `url`, as its confi
- `FREEDOM_TAB_H` (macro, `include/tab.h:2`) `#define FREEDOM_TAB_H`
- `tab_status` (enum, `include/tab.h:31`)

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 7
- Cross-boundary resolved imports (EXTRACTED): 10

## Connections

- [EXTRACTED] depends_on community 0 <-> 8 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/tab.h.
- [EXTRACTED] depends_on community 8 <-> 4 (strength 0.9): Extracted import edge crosses communities: include/frame_host.h imports include/page_view.h.
- [EXTRACTED] depends_on community 8 <-> 2 (strength 0.9): Extracted import edge crosses communities: include/tab.h imports include/freebug.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 6 file(s) lack file-level docs (e.g. `include/frame_broker.h`)? What purpose do they serve?
- What would break if the most connected file in include: tab changed?
- Should include: tab be split, given cohesion 0.41?

## Sources

- `include/frame_broker.h`
- `include/frame_host.h`
- `include/tab.h`
- `src/frame_broker.c`
- `src/frame_host.c`
- `tests/test_frame_broker.c`
- `tests/test_frame_host.c`
