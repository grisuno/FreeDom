/* pres_hints (ph_) -- HTML presentational attributes as zero-specificity style.
 *
 * HTML "Rendering" section 15: <table width>, <td align>, nowrap, <center>. Pure, total,
 * allocation-free, reentrant. Writes only the fields the cascade left undeclared, so any CSS
 * declaration wins. Contract and table of mappings: spec/pres_hints.md.
 */
#ifndef FREEDOM_PRES_HINTS_H
#define FREEDOM_PRES_HINTS_H

#ifdef __cplusplus
#error "Freedom is pure C11 by policy; C++ is not supported."
#endif

#include <stddef.h>
#include "css.h"

#define PH_ATTR_MAX   32u      /* longest attribute value read; longer is ignored */
#define PH_DIM_MAX_PX 100000   /* largest pixel dimension accepted */

/* The value of attribute `name` (not NUL-terminated, *len bytes) or NULL when absent. */
typedef const char *(*ph_attr_fn)(void *ctx, const char *name, size_t *len);

/* Parses an HTML dimension: 1 with *px set (percent 0), 2 with *per_mille set, 0 = invalid. */
int ph_parse_dimension(const char *s, size_t len, int *px, int *per_mille);

#define PH_CENTERED 1u   /* an ancestor centres its block children (<center>, align=center) */
#define PH_QUIRKS   2u   /* the document is in quirks mode */

/* Applies the hints of element `tag` (lower-case, NUL-terminated) to *cs; flags is a set of
 * PH_*. No-op on a NULL tag, getter or style. */
void ph_apply(const char *tag, ph_attr_fn get, void *ctx, unsigned flags, css_style *cs);

#endif /* FREEDOM_PRES_HINTS_H */
