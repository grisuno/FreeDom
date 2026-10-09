# include: local_store

*Community 4 | 16 files | cohesion 0.83*

## Definition

This community groups 16 file(s) rooted at `include` with dominant language c (cohesion 0.83). Central symbols: `FREEDOM_DISK_STORE_H`, `FREEDOM_LOCAL_STORE_H`, `FREEDOM_PREFS_H`, `FREEDOM_PROFILE_H`, `FREEDOM_ZOOM_H`, `LLVMFuzzerTestOneInput`, `LS_ARGON2_M_KIB`, `LS_ARGON2_P`. Core file: `src/local_store.c` (271 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_prefs.c` | c | utility | 1 | no |
| `include/disk_store.h` | h | data_access | 3 | no |
| `include/local_store.h` | h | data_access | 11 | no |
| `include/prefs.h` | h | utility | 18 | no |
| `include/profile.h` | h | utility | 9 | no |
| `include/zoom.h` | h | utility | 10 | no |
| `src/disk_store.c` | c | data_access | 6 | no |
| `src/local_store.c` | c | data_access | 271 | no |
| `src/prefs.c` | c | utility | 26 | no |
| `src/profile.c` | c | utility | 9 | no |
| `src/zoom.c` | c | utility | 7 | no |
| `tests/test_disk_store.c` | c | testing | 16 | no |
| `tests/test_local_store.c` | c | testing | 18 | no |
| `tests/test_prefs.c` | c | testing | 15 | no |
| `tests/test_profile.c` | c | testing | 17 | no |
| `tests/test_zoom.c` | c | testing | 11 | no |

## Key Symbols

- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_prefs.c:21`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
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
- `ls_aead` (enum, `include/local_store.h:34`)
- `ls_status` (enum, `include/local_store.h:39`)
- `ls_free` (function, `include/local_store.h:80`) `void ls_free(uint8_t *buf, size_t len);` - Passphrase variant: generates a random salt, derives the key with Argon2id, * and stores the salt in
- `FREEDOM_PREFS_H` (macro, `include/prefs.h:2`) `#define FREEDOM_PREFS_H`
- `PREFS_VERSION` (macro, `include/prefs.h:26`) `#define PREFS_VERSION`
- `PREFS_MAX_URL` (macro, `include/prefs.h:27`) `#define PREFS_MAX_URL`
- `PREFS_MAX_TITLE` (macro, `include/prefs.h:28`) `#define PREFS_MAX_TITLE`
- `PREFS_MAX_BOOKMARKS` (macro, `include/prefs.h:29`) `#define PREFS_MAX_BOOKMARKS`
- `PREFS_MAX_HISTORY` (macro, `include/prefs.h:30`) `#define PREFS_MAX_HISTORY`
- `PREFS_MAX_TEXT` (macro, `include/prefs.h:31`) `#define PREFS_MAX_TEXT`
- `PREFS_PAGE_HISTORY` (macro, `include/prefs.h:34`) `#define PREFS_PAGE_HISTORY`
- `prefs_status` (enum, `include/prefs.h:36`)
- `prefs_entry` (struct, `include/prefs.h:45`)
- `theme_mode` (type_alias, `include/prefs.h:49`) `typedef struct prefs_state { int theme_mode;`
- `prefs_state` (struct, `include/prefs.h:50`)
- `prefs_init` (function, `include/prefs.h:65`) `void prefs_init(prefs_state *p);` - Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on). NULL-saf
- `prefs_free` (function, `include/prefs.h:68`) `void prefs_free(prefs_state *p);` - Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on). NULL-saf
- `free` (function, `include/prefs.h:71`) `* free(). */ prefs_status prefs_format(const prefs_state *p, char **out, size_t`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 20
- Cross-boundary resolved imports (EXTRACTED): 4

## Connections

- [EXTRACTED] depends_on community 1 <-> 4 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefs.h.
- [EXTRACTED] depends_on community 4 <-> 0 (strength 0.9): Extracted import edge crosses communities: src/disk_store.c imports include/util.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 16 file(s) lack file-level docs (e.g. `fuzz/fuzz_prefs.c`)? What purpose do they serve?
- What would break if the most connected file in include: local_store changed?
- Should include: local_store be split, given cohesion 0.83?

## Sources

- `fuzz/fuzz_prefs.c`
- `include/disk_store.h`
- `include/local_store.h`
- `include/prefs.h`
- `include/profile.h`
- `include/zoom.h`
- `src/disk_store.c`
- `src/local_store.c`
- `src/prefs.c`
- `src/profile.c`
- `src/zoom.c`
- `tests/test_disk_store.c`
- `tests/test_local_store.c`
- `tests/test_prefs.c`
- `tests/test_profile.c`
- `tests/test_zoom.c`
