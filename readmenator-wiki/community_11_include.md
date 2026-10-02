# include

*Community 11 | 6 files | cohesion 0.70*

## Definition

This community groups 6 file(s) rooted at `include` with dominant language c (cohesion 0.70). Central symbols: `FREEDOM_DISK_STORE_H`, `FREEDOM_LOCAL_STORE_H`, `LS_ARGON2_M_KIB`, `LS_ARGON2_P`, `LS_ARGON2_T`, `LS_HEADER_LEN`, `LS_KDF_ARGON2ID`, `LS_KDF_NONE`. Core file: `src/local_store.c` (271 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/disk_store.h` | h | data_access | 3 | no |
| `include/local_store.h` | h | data_access | 11 | no |
| `src/disk_store.c` | c | data_access | 6 | no |
| `src/local_store.c` | c | data_access | 271 | no |
| `tests/test_disk_store.c` | c | testing | 16 | no |
| `tests/test_local_store.c` | c | testing | 18 | no |

## Key Symbols

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
- `_POSIX_C_SOURCE` (macro, `src/disk_store.c:11`) `#define _POSIX_C_SOURCE`
- `fsync_dir` (function, `src/disk_store.c:32`) `static void fsync_dir(const char *path)` - Best-effort fsync of the directory holding path, for crash durability of the * rename. Failures are
- `map_ls` (function, `src/disk_store.c:50`) `static ds_status map_ls(ls_status s)`
- `ds_write` (function, `src/disk_store.c:66`) `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead`
- `ds_read` (function, `src/disk_store.c:103`) `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],`
- `ds_free` (function, `src/disk_store.c:136`) `void ds_free(uint8_t *buf, size_t len)`
- `OSSL_KDF_PARAM_ARGON2_LANES` (macro, `src/local_store.c:3`) `#define OSSL_KDF_PARAM_ARGON2_LANES`
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, `src/local_store.c:6`) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
- `OSSL_KDF_PARAM_THREADS` (macro, `src/local_store.c:9`) `#define OSSL_KDF_PARAM_THREADS`
- `_GNU_SOURCE` (macro, `src/local_store.c:11`) `#define _GNU_SOURCE`
- `OSSL_KDF_PARAM_ARGON2_LANES` (macro, `src/local_store.c:14`) `#define OSSL_KDF_PARAM_ARGON2_LANES`
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, `src/local_store.c:17`) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`
- `OSSL_KDF_PARAM_THREADS` (macro, `src/local_store.c:20`) `#define OSSL_KDF_PARAM_THREADS`
- `_GNU_SOURCE` (macro, `src/local_store.c:22`) `#define _GNU_SOURCE`
- `OSSL_KDF_PARAM_ARGON2_LANES` (macro, `src/local_store.c:25`) `#define OSSL_KDF_PARAM_ARGON2_LANES`
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (macro, `src/local_store.c:28`) `#define OSSL_KDF_PARAM_ARGON2_MEMCOST`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 7
- Cross-boundary resolved imports (EXTRACTED): 3

## Connections

- [EXTRACTED] depends_on community 3 <-> 11 (strength 0.9): Extracted import edge crosses communities: include/profile.h imports include/local_store.h.
- [EXTRACTED] depends_on community 11 <-> 0 (strength 0.9): Extracted import edge crosses communities: src/disk_store.c imports include/util.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 6 file(s) lack file-level docs (e.g. `include/disk_store.h`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.70?

## Sources

- `include/disk_store.h`
- `include/local_store.h`
- `src/disk_store.c`
- `src/local_store.c`
- `tests/test_disk_store.c`
- `tests/test_local_store.c`
