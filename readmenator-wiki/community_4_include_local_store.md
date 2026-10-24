# include: local_store

*Community 4 | 20 files | cohesion 0.62*

## Definition

This community groups 20 file(s) rooted at `include` with dominant language c (cohesion 0.62). Central symbols: `BROWSER_STATUS_DURATION_MS`, `BROWSER_STATUS_MAX`, `BROWSER_URL_MAX`, `FREEDOM_BROWSER_H`, `FREEDOM_DISK_STORE_H`, `FREEDOM_LOCAL_STORE_H`, `FREEDOM_MEDIA_DECODER_H`, `FREEDOM_OS_SANDBOX_H`. Core file: `src/local_store.c` (307 symbols). Documented purpose: — shared pure helpers (no I/O except where noted). Static inline so each compilation unit gets its own copy without adding link dependencies..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/browser.h` | h | utility | 19 | no |
| `include/disk_store.h` | h | data_access | 3 | no |
| `include/local_store.h` | h | data_access | 11 | no |
| `include/media_decoder.h` | h | utility | 12 | no |
| `include/os_sandbox.h` | h | utility | 12 | no |
| `include/renderer.h` | h | presentation | 7 | no |
| `include/util.h` | h | utility | 6 | yes |
| `src/browser.c` | c | utility | 41 | no |
| `src/disk_store.c` | c | data_access | 6 | no |
| `src/local_store.c` | c | data_access | 307 | no |
| `src/media_decoder.c` | c | utility | 15 | no |
| `src/os_sandbox.c` | c | utility | 31 | no |
| `src/profile.c` | c | utility | 9 | no |
| `src/renderer.c` | c | presentation | 6 | no |
| `tests/test_browser.c` | c | testing | 17 | no |
| `tests/test_disk_store.c` | c | testing | 16 | no |
| `tests/test_local_store.c` | c | testing | 18 | no |
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
- `FREEDOM_DISK_STORE_H` (macro, `include/disk_store.h:2`) `#define FREEDOM_DISK_STORE_H`
- `ds_status` (enum, `include/disk_store.h:25`)
- `ds_free` (function, `include/disk_store.h:47`) `void ds_free(uint8_t *buf, size_t len);` - Reads and decrypts path. Wrong key / tampering => DS_ERR_AUTH (no plaintext). * *out is owned; relea
- `FREEDOM_LOCAL_STORE_H` (macro, `include/local_store.h:2`) `#define FREEDOM_LOCAL_STORE_H`
- `LS_KEY_LEN` (macro, `include/local_store.h:26`) `#define LS_KEY_LEN`
- `LS_SALT_LEN` (macro, `include/local_store.h:27`) `#define LS_SALT_LEN`
- `LS_NONCE_LEN` (macro, `include/local_store.h:28`) `#define LS_NONCE_LEN`
- `LS_TAG_LEN` (macro, `include/local_store.h:29`) `#define LS_TAG_LEN`
- `LS_HEADER_LEN` (macro, `include/local_store.h:30`) `#define LS_HEADER_LEN`
- `LS_OVERHEAD` (macro, `include/local_store.h:31`) `#define LS_OVERHEAD`
- `LS_MAX_PLAINTEXT` (macro, `include/local_store.h:32`) `#define LS_MAX_PLAINTEXT`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 21
- Cross-boundary resolved imports (EXTRACTED): 13

## Connections

- [EXTRACTED] depends_on community 1 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/browser.h.
- [EXTRACTED] depends_on community 0 <-> 4 (strength 0.9): Extracted import edge crosses communities: src/dom.c imports include/util.h.
- [EXTRACTED] depends_on community 3 <-> 4 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/media_decoder.h.

## Risks

- [layer strict] `tests/test_renderer.c` (testing) -> `include/renderer.h` (presentation)

## Open Questions

- Why do 19 file(s) lack file-level docs (e.g. `include/browser.h`)? What purpose do they serve?
- What would break if the most connected file in include: local_store changed?
- Should include: local_store be split, given cohesion 0.62?

## Sources

- `include/browser.h`
- `include/disk_store.h`
- `include/local_store.h`
- `include/media_decoder.h`
- `include/os_sandbox.h`
- `include/renderer.h`
- `include/util.h`
- `src/browser.c`
- `src/disk_store.c`
- `src/local_store.c`
- `src/media_decoder.c`
- `src/os_sandbox.c`
- `src/profile.c`
- `src/renderer.c`
- `tests/test_browser.c`
- `tests/test_disk_store.c`
- `tests/test_local_store.c`
- `tests/test_media_decoder.c`
- `tests/test_os_sandbox.c`
- `tests/test_renderer.c`
