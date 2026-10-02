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

/*
 * As cch_element_style, but supplying the element's INHERITED font-size in px
 * (its parent's computed value; <= 0 = unknown -> the CSS initial 16px).
 *
 * That value is what makes a font-relative length mean what the author wrote:
 * `width: 10em` is 320px on a 32px element and 80px on an 8px one. The caller
 * supplies it because only the caller walks the DOM top-down and can memoize
 * it -- resolving each ancestor from scratch here would be a full cascade per
 * level, per element. See spec/css_length.md section 8.5.
 */
css_style cch_element_style_fs(lxb_dom_element_t *el, const css_sheet *sheet,
                               double parent_font_size);

struct cvr_chain;
struct cvr_table;
/*
 * As cch_element_style_fs, plus the element's INHERITED custom properties
 * (`inherited`, its parent's chain, NULL = none) and, when own_out is non-NULL
 * (zeroed, caller frees with cvr_free), the element's OWN winning custom
 * properties -- what its children inherit. spec/css_vars.md, "Alcance por
 * elemento".
 */
css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,
                                 double parent_font_size,
                                 const struct cvr_chain *inherited,
                                 struct cvr_table *own_out);
/* Nonzero iff the parsed selector *sel matches element `el`, built against the
 * same bounded ancestor/sibling/attribute context as cch_element_style. This is
 * the single source of truth for selector matching: the DOM's querySelector and
 * the author-CSS cascade agree by construction. `sel` is a pre-parsed css_sel
 * (see csel_parse); NULL args return 0 (fail closed). */
int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel);

/* The style of el's ::before (CSS_PSEUDO_BEFORE) or ::after (CSS_PSEUDO_AFTER)
 * generated box (css_resolve_pseudo) against the same element context.
 * font_size is el's own COMPUTED font-size (the pseudo inherits it) and
 * inherited el's own custom-property chain (NULL = none). */
css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,
                           double font_size, const struct cvr_chain *inherited);

#endif /* FREEDOM_CSS_CHAIN_H */
