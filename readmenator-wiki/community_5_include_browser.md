# include: browser

*Community 5 | 19 files | cohesion 0.55*

## Definition

This community groups 19 file(s) rooted at `include` with dominant language c (cohesion 0.55). Central symbols: `BROWSER_STATUS_DURATION_MS`, `BROWSER_STATUS_MAX`, `BROWSER_URL_MAX`, `FREEDOM_BROWSER_H`, `FREEDOM_HOSTBLOCK_H`, `FREEDOM_HOST_CONF_H`, `FREEDOM_MEDIA_DECODER_H`, `FREEDOM_OS_SANDBOX_H`. Core file: `src/browser.c` (41 symbols). Documented purpose: — shared pure helpers (no I/O except where noted). Static inline so each compilation unit gets its own copy without adding link dependencies..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/browser.h` | h | utility | 19 | no |
| `include/host_conf.h` | h | utility | 9 | no |
| `include/hostblock.h` | h | utility | 10 | no |
| `include/media_decoder.h` | h | utility | 12 | no |
| `include/os_sandbox.h` | h | utility | 12 | no |
| `include/renderer.h` | h | presentation | 7 | no |
| `include/util.h` | h | utility | 6 | yes |
| `src/browser.c` | c | utility | 41 | no |
| `src/host_conf.c` | c | utility | 9 | no |
| `src/hostblock.c` | c | utility | 18 | no |
| `src/media_decoder.c` | c | utility | 15 | no |
| `src/os_sandbox.c` | c | utility | 31 | no |
| `src/renderer.c` | c | presentation | 6 | no |
| `tests/test_browser.c` | c | testing | 17 | no |
| `tests/test_host_conf.c` | c | testing | 8 | no |
| `tests/test_hostblock.c` | c | testing | 23 | no |
| `tests/test_media_decoder.c` | c | testing | 6 | no |
| `tests/test_os_sandbox.c` | c | testing | 19 | no |
| `tests/test_renderer.c` | c | testing | 8 | no |

## Key Symbols

- `FREEDOM_BROWSER_H` (macro, `include/browser.h:2`) `#define FREEDOM_BROWSER_H`
- `BROWSER_URL_MAX` (macro, `include/browser.h:21`) `#define BROWSER_URL_MAX`
- `BROWSER_STATUS_MAX` (macro, `include/browser.h:24`) `#define BROWSER_STATUS_MAX`
- `BROWSER_STATUS_DURATION_MS` (macro, `include/browser.h:25`) `#define BROWSER_STATUS_DURATION_MS`
- `browser_state` (struct, `include/browser.h:27`)
- `browser_status` (enum, `include/browser.h:52`)
- `state` (function, `include/browser.h:62`) `* state (frees old history and page buffers). */ browser_status browser_init(bro`
- `browser_free` (function, `include/browser.h:66`) `void browser_free(browser_state *bs);` - Zero-initialise or reset a state. Safe to call on an already-initialised * state (frees old history
- `browser_set_page` (function, `include/browser.h:71`) `* browser_set_page() with the result. */ browser_status browser_navigate(browser`
- `browser_entry_doc` (function, `include/browser.h:87`) `int browser_entry_doc(const browser_state *bs, size_t pos);` - Same-document entries (history.pushState, spec/browser.md 3b). push adds an entry of the CURRENT doc
- `browser_doc_index` (function, `include/browser.h:91`) `int browser_doc_index(const browser_state *bs);` - Index of the current entry within its document's contiguous run of entries (0 for * the entry the do
- `browser_can_back` (function, `include/browser.h:94`) `int browser_can_back(const browser_state *bs);` - Index of the current entry within its document's contiguous run of entries (0 for * the entry the do
- `browser_can_forward` (function, `include/browser.h:95`) `int browser_can_forward(const browser_state *bs);`
- `browser_current_url` (function, `include/browser.h:96`) `const char *browser_current_url(const browser_state *bs);`
- `browser_is_exception` (function, `include/browser.h:99`) `int browser_is_exception(const browser_state *bs, const char *host);` - Index of the current entry within its document's contiguous run of entries (0 for * the entry the do
- `browser_url_bar_selection` (function, `include/browser.h:131`) `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *le` - If a selection exists, writes its start offset and length and returns 1; else 0. * Lets the GUI copy
- `browser_url_bar_delete_selection` (function, `include/browser.h:135`) `int browser_url_bar_delete_selection(browser_state *bs);` - Removes the selected range (if any), placing the cursor at its start; returns 1 if * something was r
- `copied` (function, `include/browser.h:143`) `* copied (truncated to fit) and shown until now_ms reaches the expiry * (now_ms`
- `browser_status_text` (function, `include/browser.h:150`) `const char *browser_status_text(const browser_state *bs, uint64_t now_ms);` - Transient status line (a toast, e.g. "blocked: insecure http link"). msg is copied (truncated to fit
- `FREEDOM_HOST_CONF_H` (macro, `include/host_conf.h:2`) `#define FREEDOM_HOST_CONF_H`
- `HCF_MAX_DIRS` (macro, `include/host_conf.h:15`) `#define HCF_MAX_DIRS`
- `HCF_PATH_MAX` (macro, `include/host_conf.h:16`) `#define HCF_PATH_MAX`
- `HCF_MAX_FILE_BYTES` (macro, `include/host_conf.h:18`) `#define HCF_MAX_FILE_BYTES`
- `hcf_dirs` (struct, `include/host_conf.h:20`)
- `hcf_search_dirs` (function, `include/host_conf.h:28`) `void hcf_search_dirs(const char *env, const char *home, hcf_dirs *out);` - Pure. Fills out with, in order: env (when non-empty), home + "/.config/freedom" (when home is non-em
- `hcf_search_dirs_from_env` (function, `include/host_conf.h:31`) `void hcf_search_dirs_from_env(hcf_dirs *out);` - Pure. Fills out with, in order: env (when non-empty), home + "/.config/freedom" (when home is non-em
- `hcf_load_filter` (function, `include/host_conf.h:35`) `hb_set *hcf_load_filter(const hcf_dirs *dirs);` - block.conf (BLOCK) + allow.conf (ALLOW) from every directory, cumulative. Missing or * unreadable fi
- `hcf_load_allowlist` (function, `include/host_conf.h:39`) `hb_set *hcf_load_allowlist(const hcf_dirs *dirs, const char *fname);` - One file (js.conf, allow.conf, ...) from every directory as an ALLOW list. NULL only on * OOM or a N
- `FREEDOM_HOSTBLOCK_H` (macro, `include/hostblock.h:2`) `#define FREEDOM_HOSTBLOCK_H`
- `hb_set` (type_alias, `include/hostblock.h:29`) `typedef struct hb_set hb_set;` - caller reads the list files and passes their text in; this module parses them into hash tables and d

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 18
- Cross-boundary resolved imports (EXTRACTED): 15

## Connections

- [EXTRACTED] depends_on community 1 <-> 5 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/browser.h.
- [EXTRACTED] depends_on community 6 <-> 5 (strength 0.9): Extracted import edge crosses communities: src/disk_store.c imports include/util.h.
- [EXTRACTED] depends_on community 0 <-> 5 (strength 0.9): Extracted import edge crosses communities: src/dom.c imports include/util.h.

## Risks

- [layer strict] `tests/test_renderer.c` (testing) -> `include/renderer.h` (presentation)
- [dataflow UNCHECKED_ALLOC] `src/hostblock.c:145` `hb_new` `s`: Result of allocator stored in `s` is never checked against NULL.

## Open Questions

- Why do 18 file(s) lack file-level docs (e.g. `include/browser.h`)? What purpose do they serve?
- What would break if the most connected file in include: browser changed?
- Should include: browser be split, given cohesion 0.55?

## Sources

- `include/browser.h`
- `include/host_conf.h`
- `include/hostblock.h`
- `include/media_decoder.h`
- `include/os_sandbox.h`
- `include/renderer.h`
- `include/util.h`
- `src/browser.c`
- `src/host_conf.c`
- `src/hostblock.c`
- `src/media_decoder.c`
- `src/os_sandbox.c`
- `src/renderer.c`
- `tests/test_browser.c`
- `tests/test_host_conf.c`
- `tests/test_hostblock.c`
- `tests/test_media_decoder.c`
- `tests/test_os_sandbox.c`
- `tests/test_renderer.c`
