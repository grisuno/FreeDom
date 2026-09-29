# include

*Community 11 | 3 files | cohesion 0.67*

## Definition

This community groups 3 file(s) rooted at `include` with dominant language c (cohesion 0.67). Central symbols: `FREEDOM_HOSTEDIT_H`, `HE_MAX_HOST`, `contains_ci`, `has_host_cb`, `he_lower`, `he_make_line`, `he_scan`, `he_status`. Core file: `src/hostedit.c` (13 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/hostedit.h` | h | infrastructure | 5 | no |
| `src/hostedit.c` | c | infrastructure | 13 | no |
| `tests/test_hostedit.c` | c | testing | 11 | no |

## Key Symbols

- `FREEDOM_HOSTEDIT_H` (macro, `include/hostedit.h:2`) `#define FREEDOM_HOSTEDIT_H`
- `he_status` (enum, `include/hostedit.h:24`)
- `HE_MAX_HOST` (macro, `include/hostedit.h:32`) `#define HE_MAX_HOST`
- `he_text_has_host` (function, `include/hostedit.h:46`) `int he_text_has_host(const char *text, const char *host);` - Returns 1 if text (the body of a hosts-format file) already lists host as a domain token on a non-co
- `he_suggest` (function, `include/hostedit.h:55`) `int he_suggest(const char *text, const char *query, char results[][HE_MAX_HOST +` - Omnibar autocomplete: treats allow.conf (a hosts-format text) as a favorites list. Fills results[0..
- `he_lower` (function, `src/hostedit.c:12`) `static char he_lower(char c)`
- `is_label_char` (function, `src/hostedit.c:16`) `static int is_label_char(char c)`
- `valid_host` (function, `src/hostedit.c:22`) `static int valid_host(const char *host, size_t n)` - #include "hostedit.h" #include <string.h> static char he_lower(char c) { return (c >= 'A' && c <= 'Z
- `he_make_line` (function, `src/hostedit.c:41`) `he_status he_make_line(const char *host, char *out, size_t cap)`
- `is_ip_token` (function, `src/hostedit.c:67`) `static int is_ip_token(const char *ts, const char *te)` - True if the token looks like an IPv4 dotted-quad / contains only digits and dots * (matches hostbloc
- `he_scan` (function, `src/hostedit.c:80`) `static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), vo` - Visits each domain token (non-comment, non-IP) of a hosts-format text in document order, calling fn(
- `has_host_cb` (function, `src/hostedit.c:105`) `static int has_host_cb(const char *ts, size_t tl, void *ctx)`
- `he_text_has_host` (function, `src/hostedit.c:109`) `int he_text_has_host(const char *text, const char *host)`
- `contains_ci` (function, `src/hostedit.c:115`) `static int contains_ci(const char *hs, size_t hl, const char *needle)` - } return 0; } static int has_host_cb(const char *ts, size_t tl, void *ctx) { return token_eq_host(ts
- `starts_with_ci` (function, `src/hostedit.c:128`) `static int starts_with_ci(const char *hs, size_t hl, const char *pfx)`
- `suggest_ctx` (struct, `src/hostedit.c:136`)
- `suggest_cb` (function, `src/hostedit.c:144`) `static int suggest_cb(const char *ts, size_t tl, void *vctx)`
- `he_suggest` (function, `src/hostedit.c:164`) `int he_suggest(const char *text, const char *query,                char results[`
- `test_make_line_lowercases` (function, `tests/test_hostedit.c:11`) `static void test_make_line_lowercases(void **state)`
- `test_make_line_plain_host` (function, `tests/test_hostedit.c:18`) `static void test_make_line_plain_host(void **state)`
- `test_make_line_rejects_path_scheme_garbage` (function, `tests/test_hostedit.c:25`) `static void test_make_line_rejects_path_scheme_garbage(void **state)`
- `test_make_line_rejects_bad_labels` (function, `tests/test_hostedit.c:36`) `static void test_make_line_rejects_bad_labels(void **state)`
- `test_make_line_null_and_range` (function, `tests/test_hostedit.c:47`) `static void test_make_line_null_and_range(void **state)`
- `test_make_line_single_label_ok` (function, `tests/test_hostedit.c:56`) `static void test_make_line_single_label_ok(void **state)`
- `test_text_has_host` (function, `tests/test_hostedit.c:63`) `static void test_text_has_host(void **state)`
- `test_suggest_prefix_first` (function, `tests/test_hostedit.c:76`) `static void test_suggest_prefix_first(void **state)`
- `test_suggest_case_insensitive_and_dedup` (function, `tests/test_hostedit.c:92`) `static void test_suggest_case_insensitive_and_dedup(void **state)`
- `test_suggest_empty_query_and_cap` (function, `tests/test_hostedit.c:101`) `static void test_suggest_empty_query_and_cap(void **state)`
- `main` (function, `tests/test_hostedit.c:114`) `int main(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- [EXTRACTED] depends_on community 2 <-> 11 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/hostedit.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 3 file(s) lack file-level docs (e.g. `include/hostedit.h`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.67?

## Sources

- `include/hostedit.h`
- `src/hostedit.c`
- `tests/test_hostedit.c`
