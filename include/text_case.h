#ifndef FREEDOM_TEXT_CASE_H
#define FREEDOM_TEXT_CASE_H

#ifdef __cplusplus
#error "Freedom is pure C11"
#endif

#include <stddef.h>
#include <stdint.h>

/* Case mapping for text-transform and synthesized small caps (spec/text_case.md).
 * Pure: no I/O, no state, no allocation. */

/* Font-size factor of a synthesized small capital (Gecko's SMALL_CAPS_SCALE_FACTOR). */
#define TC_SMALLCAPS_SCALE 0.8

/* Simple 1:1 case mapping for ASCII, Latin-1, Latin Extended-A, basic Greek and
 * basic Cyrillic. The result always encodes to the SAME number of UTF-8 bytes as
 * cp (identity otherwise), so a transformed text keeps its length. */
uint32_t tc_upper(uint32_t cp);
uint32_t tc_lower(uint32_t cp);

/* 1 when cp is a lowercase letter tc_upper maps to something else. */
int tc_is_lower(uint32_t cp);

/* Copies s[0,n) to out applying transform (CSS_TT_UPPERCASE / _LOWERCASE /
 * _CAPITALIZE; any other value copies verbatim). word_start says s begins a word
 * (for capitalize). Returns n, or 0 (out untouched) when s/out is NULL or cap < n. */
size_t tc_transform(const char *s, size_t n, int transform, int word_start,
                    char *out, size_t cap);

/* One maximal run of tc_smallcaps_runs. */
typedef struct {
    size_t off, len;
    int    lowered;   /* 1: lowercase letters, painted uppercase at TC_SMALLCAPS_SCALE */
} tc_run;

/* Splits s[0,n) into consecutive maximal runs of lowercase letters vs the rest,
 * covering the whole text in order. Returns the runs written; when cap is too
 * small the last run absorbs the remainder. 0 for NULL/empty input or cap 0. */
size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap);

#endif
