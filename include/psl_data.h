#ifndef FREEDOM_PSL_DATA_H
#define FREEDOM_PSL_DATA_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * psl_data — sorted, read-only Public Suffix List tables, generated at build
 * time by tools/gen_psl from third_party/psl/public_suffix_list.dat (see that
 * directory's VERSION.md). request_policy binary-searches these to compute the
 * registrable domain (eTLD+1). The lists are lowercased and strcmp-sorted.
 *
 *  - psl_rules:      normal rules, e.g. "com", "co.uk", "github.io".
 *  - psl_wildcards:  the parent of a "*." rule, e.g. "ck" for "*.ck".
 *  - psl_exceptions: "!" rules with the "!" stripped, e.g. "www.ck".
 */

extern const char *const psl_rules[];
extern const size_t       psl_rules_n;
extern const char *const psl_wildcards[];
extern const size_t       psl_wildcards_n;
extern const char *const psl_exceptions[];
extern const size_t       psl_exceptions_n;

#endif /* FREEDOM_PSL_DATA_H */
