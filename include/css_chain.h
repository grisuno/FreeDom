#ifndef FREEDOM_CSS_CHAIN_H
#define FREEDOM_CSS_CHAIN_H

#include <lexbor/html/html.h>

#include "css.h"
#include "css_select.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * css_chain — bridges the live (hostile, already-parsed) lexbor DOM to the pure
 * css/css_select engine: builds the bounded css_element chain for one element
 * (ancestors for descendant/child combinators, sibling context for the
 * structural pseudo-classes and the `+`/`~` combinators, attributes for [attr]
 * selectors) and resolves its author style through the cascade. Split out of
 * page_view (anti-monolith clause). Pure with respect to effects: reads the DOM,
 * allocates nothing, no I/O. See spec/css_chain.md.
 */

/* Bounds (anti-DoS; beyond each the context reads unknown/absent, fail closed):
 * ancestors carried for combinator matching, preceding siblings carried for the
 * subject's `+`/`~`, and the sibling-position walk cap. */
#define CCH_CHAIN_MAX 32
#define CCH_SIB_MAX   16
#define CCH_NTH_MAX   1024

/* Resolves the author presentation for one element from the document sheet plus
 * its own inline style= (inline wins; the css module does the cascade). The
 * element, its ancestor chain and its preceding-sibling context (all bounded)
 * become the selector match inputs, so descendant/child/adjacent/general
 * combinators, [attr] selectors and the structural pseudo-classes resolve
 * against the real DOM. sheet may be NULL (inline only). */
css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet);

/* Nonzero iff the parsed selector *sel matches element `el`, built against the
 * same bounded ancestor/sibling/attribute context as cch_element_style. This is
 * the single source of truth for selector matching: the DOM's querySelector and
 * the author-CSS cascade agree by construction. `sel` is a pre-parsed css_sel
 * (see csel_parse); NULL args return 0 (fail closed). */
int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel);

#endif /* FREEDOM_CSS_CHAIN_H */
