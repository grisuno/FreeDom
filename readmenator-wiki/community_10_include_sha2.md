# include: sha2

*Community 10 | 3 files | cohesion 0.67*

## Definition

This community groups 3 file(s) rooted at `include` with dominant language c (cohesion 0.67). Central symbols: `FREEDOM_SHA2_H`, `ROL32`, `ROR32`, `ROR64`, `SHA_MAX_DIGEST`, `be32`, `be64`, `check`. Core file: `src/sha2.c` (15 symbols). Documented purpose: test_sha2 -- CMocka suite for the pure SHA-1/256/384/512 (FIPS 180-4 vectors)..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/sha2.h` | h | utility | 6 | no |
| `src/sha2.c` | c | utility | 15 | no |
| `tests/test_sha2.c` | c | testing | 7 | yes |

## Key Symbols

- `FREEDOM_SHA2_H` (macro, `include/sha2.h:2`) `#define FREEDOM_SHA2_H`
- `sha_alg` (enum, `include/sha2.h:16`)
- `SHA_MAX_DIGEST` (macro, `include/sha2.h:18`) `#define SHA_MAX_DIGEST`
- `sha_digest_len` (function, `include/sha2.h:21`) `size_t sha_digest_len(sha_alg alg);` - sha2 -- one-shot SHA-1 / SHA-256 / SHA-384 / SHA-512 (FIPS 180-4), pure and allocation-free. Backs c
- `sha_alg_from_name` (function, `include/sha2.h:24`) `int sha_alg_from_name(const char *name, sha_alg *out);` - sha2 -- one-shot SHA-1 / SHA-256 / SHA-384 / SHA-512 (FIPS 180-4), pure and allocation-free. Backs c
- `sha_digest` (function, `include/sha2.h:28`) `int sha_digest(sha_alg alg, const void *data, size_t len, uint8_t *out);` - Hashes data[0..len) into out (>= sha_digest_len(alg) bytes). 0 on success, -1 on a bad argument. * d
- `ROR32` (macro, `src/sha2.c:8`) `#define ROR32(x, n)`
- `ROL32` (macro, `src/sha2.c:9`) `#define ROL32(x, n)`
- `ROR64` (macro, `src/sha2.c:10`) `#define ROR64(x, n)`
- `sha_digest_len` (function, `src/sha2.c:12`) `size_t sha_digest_len(sha_alg alg)`
- `ieq` (function, `src/sha2.c:22`) `static int ieq(const char *a, const char *b)`
- `sha_alg_from_name` (function, `src/sha2.c:31`) `int sha_alg_from_name(const char *name, sha_alg *out)`
- `be32` (function, `src/sha2.c:40`) `static uint32_t be32(const uint8_t *p)`
- `be64` (function, `src/sha2.c:43`) `static uint64_t be64(const uint8_t *p)`
- `put32` (function, `src/sha2.c:44`) `static void put32(uint8_t *p, uint32_t v)`
- `put64` (function, `src/sha2.c:45`) `static void put64(uint8_t *p, uint64_t v)`
- `pad_tail` (function, `src/sha2.c:49`) `static size_t pad_tail(uint8_t *blk, size_t bs, size_t lenbytes, const uint8_t *` - Pads the tail of a message into at most two blocks of `bs` bytes with a `lenbytes`-byte * big-endian
- `sha1_block` (function, `src/sha2.c:61`) `static void sha1_block(uint32_t h[5], const uint8_t *p)`
- `sha256_block` (function, `src/sha2.c:88`) `static void sha256_block(uint32_t h[8], const uint8_t *p)`
- `sha512_block` (function, `src/sha2.c:131`) `static void sha512_block(uint64_t h[8], const uint8_t *p)`
- `sha_digest` (function, `src/sha2.c:152`) `int sha_digest(sha_alg alg, const void *data, size_t len, uint8_t *out)`
- `hex` (function, `tests/test_sha2.c:14`) `static void hex(const uint8_t *d, size_t n, char *out)`
- `check` (function, `tests/test_sha2.c:18`) `static void check(sha_alg a, const char *msg, size_t rep, const char *want)`
- `test_abc_vectors` (function, `tests/test_sha2.c:31`) `static void test_abc_vectors(void **state)`
- `test_empty_and_long` (function, `tests/test_sha2.c:39`) `static void test_empty_and_long(void **state)`
- `test_padding_boundaries` (function, `tests/test_sha2.c:52`) `static void test_padding_boundaries(void **state)`
- `test_names_and_errors` (function, `tests/test_sha2.c:60`) `static void test_names_and_errors(void **state)`
- `main` (function, `tests/test_sha2.c:74`) `int main(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 2 file(s) lack file-level docs (e.g. `include/sha2.h`)? What purpose do they serve?
- What would break if the most connected file in include: sha2 changed?
- Should include: sha2 be split, given cohesion 0.67?

## Sources

- `include/sha2.h`
- `src/sha2.c`
- `tests/test_sha2.c`
