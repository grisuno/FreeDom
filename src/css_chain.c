/*
 * css_chain — lexbor-DOM -> css_element chain builder + author-style resolution
 * for one element. See include/css_chain.h, spec/css_chain.md. Split out of
 * page_view (anti-monolith clause).
 */

#include "css_chain.h"
#include "css_select.h"

#include <string.h>

/* Bounds for the element selector inputs handed to css_resolve (anti-DoS; an
 * over-long token simply does not match, which fails closed). */
#define CCH_TAG_MAX     64u
#define CCH_ID_MAX      128u
#define CCH_CLASS_BUF   256u
#define CCH_MAX_CLASSES 16
#define CCH_MAX_ATTRS   16     /* attributes captured per element for [attr] selectors */
#define CCH_ATTR_BUF    512u   /* bytes for all captured attr names+values of one element */

/* One element's selector inputs (tag/id/classes) plus its css_element view, with
 * backing storage so the css_element pointers stay valid for the chain's lifetime. */
typedef struct cch_node {
    char        tag[CCH_TAG_MAX];
    char        idbuf[CCH_ID_MAX];
    char        clsbuf[CCH_CLASS_BUF];
    const char *clsptr[CCH_MAX_CLASSES];
    char        attrbuf[CCH_ATTR_BUF];
    css_attr    attrs[CCH_MAX_ATTRS];
    css_element el;
} cch_node;

/* Fills *node with element e's tag/id/class tokens (no style=, no parent link yet).
 * Over-long tokens are simply absent, which fails closed (does not match). */
static void fill_css_node(lxb_dom_element_t *e, cch_node *node) {
    size_t nl = 0;
    const lxb_char_t *ln = lxb_dom_element_local_name(e, &nl);
    size_t tn = (ln != NULL && nl > 0 && nl < sizeof node->tag) ? nl : 0;
    if (tn > 0) memcpy(node->tag, ln, tn);
    node->tag[tn] = '\0';

    node->el.id = NULL;
    size_t il = 0;
    const lxb_char_t *idv =
        lxb_dom_element_get_attribute(e, (const lxb_char_t *)"id", 2, &il);
    if (idv != NULL && il > 0 && il < sizeof node->idbuf) {
        memcpy(node->idbuf, idv, il);
        node->idbuf[il] = '\0';
        node->el.id = node->idbuf;
    }

    size_t nc = 0, cl = 0;
    const lxb_char_t *clv =
        lxb_dom_element_get_attribute(e, (const lxb_char_t *)"class", 5, &cl);
    if (clv != NULL && cl > 0 && cl < sizeof node->clsbuf) {
        memcpy(node->clsbuf, clv, cl);
        node->clsbuf[cl] = '\0';
        size_t i = 0;
        while (i < cl && nc < CCH_MAX_CLASSES) {
            while (i < cl && (node->clsbuf[i] == ' ' || node->clsbuf[i] == '\t' ||
                              node->clsbuf[i] == '\n' || node->clsbuf[i] == '\r' ||
                              node->clsbuf[i] == '\f'))
                node->clsbuf[i++] = '\0';
            if (i >= cl) break;
            node->clsptr[nc++] = &node->clsbuf[i];
            while (i < cl && !(node->clsbuf[i] == ' ' || node->clsbuf[i] == '\t' ||
                               node->clsbuf[i] == '\n' || node->clsbuf[i] == '\r' ||
                               node->clsbuf[i] == '\f'))
                ++i;
        }
    }

    /* Capture all attributes (name lowercased) for [attr] selectors, packed into one
     * bounded buffer. Over-long sets are truncated (anti-DoS): a missing attribute just
     * fails to match (fail closed). id/class/style are attributes too, so [id=...] etc.
     * work alongside the dedicated #id/.class paths. */
    size_t nat = 0, off = 0;
    for (lxb_dom_attr_t *at = lxb_dom_element_first_attribute(e);
         at != NULL && nat < CCH_MAX_ATTRS;
         at = lxb_dom_element_next_attribute(at)) {
        size_t anl = 0, avl = 0;
        const lxb_char_t *an = lxb_dom_attr_local_name(at, &anl);
        const lxb_char_t *av = lxb_dom_attr_value(at, &avl);
        if (an == NULL || anl == 0) continue;
        if (off + anl + 1 + avl + 1 > sizeof node->attrbuf) break;  /* buffer full */
        char *np = node->attrbuf + off;
        for (size_t k = 0; k < anl; ++k) {
            char ch = (char)an[k];
            np[k] = (ch >= 'A' && ch <= 'Z') ? (char)(ch + 32) : ch;
        }
        np[anl] = '\0';
        off += anl + 1;
        char *vp = node->attrbuf + off;
        if (av != NULL && avl > 0) memcpy(vp, av, avl);
        vp[avl] = '\0';
        off += avl + 1;
        node->attrs[nat].name = np;
        node->attrs[nat].value = vp;
        ++nat;
    }

    node->el.tag = (tn > 0) ? node->tag : NULL;
    node->el.classes = node->clsptr;
    node->el.nclasses = nc;
    node->el.attrs = (nat > 0) ? node->attrs : NULL;
    node->el.nattrs = nat;
    node->el.parent = NULL;  /* linked by the caller once the chain is built */
    node->el.nth = 0;        /* sibling context filled by the caller (0 = unknown, */
    node->el.nsib = 0;       /* structural pseudo-classes then fail closed) */
    node->el.prev = NULL;
}

/* Computes the 1-based index of n among its ELEMENT siblings and the total
 * element-sibling count (both walks bounded, anti-DoS: past CCH_NTH_MAX the
 * position reads unknown and :nth-child()-style selectors do not match). */
static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib) {
    int before = 0, after = 0;
    *nth = 0;
    *nsib = 0;
    for (lxb_dom_node_t *p = n->prev; p != NULL; p = p->prev) {
        if (p->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
        if (++before > CCH_NTH_MAX) return;
    }
    for (lxb_dom_node_t *p = n->next; p != NULL; p = p->next) {
        if (p->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
        if (++after > CCH_NTH_MAX - before) return;
    }
    *nth = before + 1;
    *nsib = before + 1 + after;
}

/* Resolves the author presentation for one element from the document <style> sheet
 * plus its own inline style= (inline wins; the css module does the cascade). The
 * element and its ancestor chain (bounded) become the selector match inputs, so
 * descendant/child combinators (`div p`, `nav > a`) resolve. Pure (no fetch, no
 * execution): the css module drops url() and @-rules. */
css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet) {
    cch_node chain[CCH_CHAIN_MAX];
    cch_node sibs[CCH_SIB_MAX];
    lxb_dom_node_t *nodes[CCH_CHAIN_MAX];
    int n = 0;
    for (lxb_dom_node_t *p = (lxb_dom_node_t *)el;
         p != NULL && p->type == LXB_DOM_NODE_TYPE_ELEMENT && n < CCH_CHAIN_MAX;
         p = p->parent) {
        fill_css_node(lxb_dom_interface_element(p), &chain[n]);
        nodes[n] = p;
        ++n;
    }
    for (int i = 0; i < n; ++i)
        chain[i].el.parent = (i + 1 < n) ? &chain[i + 1].el : NULL;

    /* Sibling context (Hito 23b-9): nth/nsib for every chain node (so a zebra
     * `tr:nth-child(even) td` can constrain an ancestor), and the prev-sibling
     * chain for the SUBJECT only, bounded to CCH_SIB_MAX (a `+`/`~` on a
     * non-subject compound or past the bound fails closed). Each sibling shares
     * the subject's parent and derives its position from the subject's. */
    for (int i = 0; i < n; ++i)
        sibling_position(nodes[i], &chain[i].el.nth, &chain[i].el.nsib);
    int ns = 0;
    if (n > 0) {
        for (lxb_dom_node_t *p = nodes[0]->prev; p != NULL && ns < CCH_SIB_MAX;
             p = p->prev) {
            if (p->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
            fill_css_node(lxb_dom_interface_element(p), &sibs[ns]);
            sibs[ns].el.parent = chain[0].el.parent;
            if (chain[0].el.nth > ns + 1) {
                sibs[ns].el.nth = chain[0].el.nth - (ns + 1);
                sibs[ns].el.nsib = chain[0].el.nsib;
            }
            ++ns;
        }
        chain[0].el.prev = (ns > 0) ? &sibs[0].el : NULL;
        for (int i = 0; i + 1 < ns; ++i)
            sibs[i].el.prev = &sibs[i + 1].el;
    }

    /* Inline style= applies to the subject element only. */
    size_t sl = 0;
    const lxb_char_t *st =
        lxb_dom_element_get_attribute(el, (const lxb_char_t *)"style", 5, &sl);

    return css_resolve_el(sheet, (n > 0) ? &chain[0].el : NULL,
                          (const char *)st, sl);
}
