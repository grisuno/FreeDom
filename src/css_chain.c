/*
 * css_chain — lexbor-DOM -> css_element chain builder + author-style resolution
 * for one element. See include/css_chain.h, spec/css_chain.md. Split out of
 * page_view (anti-monolith clause).
 */

#include "css_chain.h"
#include "css_select.h"

#include <stdlib.h>
#include <string.h>

/* Bounds for the element selector inputs handed to css_resolve (anti-DoS; an
 * over-long token simply does not match, which fails closed). */
#define CCH_TAG_MAX     64u
#define CCH_ID_MAX      128u
#define CCH_CLASS_BUF   256u   /* inline class storage; longer lists spill to the heap */
#define CCH_MAX_CLASSES 16     /* inline class slots; more spill to the heap */
/* Anti-DoS bound on one element's class list once it spills: a real page tops out
 * in the low thousands of bytes (CSS Modules, Tailwind), never this. */
#define CCH_CLASS_SPILL_MAX (64u * 1024u)
#define CCH_MAX_ATTRS   16     /* attributes captured per element for [attr] selectors */
#define CCH_ATTR_BUF    512u   /* bytes for all captured attr names+values of one element */

/* One element's selector inputs (tag/id/classes) plus its css_element view, with
 * backing storage so the css_element pointers stay valid for the chain's lifetime. */
typedef struct cch_node {
    char        tag[CCH_TAG_MAX];
    char        idbuf[CCH_ID_MAX];
    char        clsbuf[CCH_CLASS_BUF];
    const char *clsptr[CCH_MAX_CLASSES];
    /* A class attribute too long for clsbuf, or with more than CCH_MAX_CLASSES
     * tokens, lives here instead: one owned block holding the pointer array and a
     * copy of the string. NULL when the inline storage sufficed. Freed by
     * cch_release once the resolve is done. */
    void       *spill;
    char        attrbuf[CCH_ATTR_BUF];
    css_attr    attrs[CCH_MAX_ATTRS];
    css_element el;
} cch_node;

static int cls_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f';
}

/* Splits a class attribute into the node's selector view (el.classes/nclasses).
 * The common case fits the inline clsbuf/clsptr; a longer list or one with more
 * tokens spills into ONE owned heap block (pointer array + string copy), so no
 * class is ever dropped for being late in a long attribute -- the old fixed
 * storage dropped EVERY class of an attribute >= 256 bytes. OOM degrades to the
 * inline prefix (fail closed: a missing class does not match). */
static void split_classes(cch_node *node, const char *v, size_t n) {
    size_t ntok = 0;
    for (size_t i = 0; i < n; ) {
        while (i < n && cls_space(v[i])) ++i;
        if (i >= n) break;
        ++ntok;
        while (i < n && !cls_space(v[i])) ++i;
    }
    if (ntok == 0) return;
    char *buf = node->clsbuf;
    const char **ptr = node->clsptr;
    size_t cap_tok = CCH_MAX_CLASSES;
    if (n >= CCH_CLASS_BUF || ntok > CCH_MAX_CLASSES) {
        size_t bytes = ntok * sizeof(char *) + n + 1;
        void *blk = malloc(bytes);
        if (blk != NULL) {
            node->spill = blk;
            ptr = (const char **)blk;
            buf = (char *)blk + ntok * sizeof(char *);
            cap_tok = ntok;
        } else if (n >= CCH_CLASS_BUF) {
            return;
        }
    }
    memcpy(buf, v, n);
    buf[n] = '\0';
    size_t nc = 0;
    for (size_t i = 0; i < n && nc < cap_tok; ) {
        while (i < n && cls_space(buf[i])) buf[i++] = '\0';
        if (i >= n) break;
        ptr[nc++] = &buf[i];
        while (i < n && !cls_space(buf[i])) ++i;
    }
    node->el.classes = ptr;
    node->el.nclasses = nc;
}

/* Releases what fill_css_node spilled to the heap for the first n nodes. */
static void release_nodes(cch_node *nodes, int n) {
    for (int i = 0; i < n; ++i) {
        free(nodes[i].spill);
        nodes[i].spill = NULL;
    }
}

/* Fills *node with element e's tag/id/class tokens (no style=, no parent link yet).
 * Over-long tokens are simply absent, which fails closed (does not match). */
static void fill_css_node(lxb_dom_element_t *e, cch_node *node) {
    /* Zero the whole selector view FIRST, then fill it. The explicit per-field
     * assignments below are the documentation of what each input means, but they
     * cannot be the only initialisation: `chain[]`/`sibs[]` are stack arrays, so a
     * field this function forgets is read as stack GARBAGE by the matcher.
     *
     * That is not hypothetical -- it is how `state` (added with the dynamic pseudos)
     * shipped: `:hover`/`:active`/`:focus*` read an uninitialised bitmask, so whether
     * an author's :hover rules applied to a freshly loaded page depended on what
     * happened to be on the stack. It silently reinstated the ":hover always matches"
     * behaviour that was deliberately removed, and only on SOME builds -- -O2 matched,
     * the ASan build did not. Zero-init by construction so the next field added to
     * css_element cannot repeat it. */
    node->el = (css_element){ 0 };
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

    size_t cl = 0;
    const lxb_char_t *clv =
        lxb_dom_element_get_attribute(e, (const lxb_char_t *)"class", 5, &cl);
    node->spill = NULL;
    if (clv != NULL && cl > 0 && cl < CCH_CLASS_SPILL_MAX)
        split_classes(node, (const char *)clv, cl);

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
    node->el.attrs = (nat > 0) ? node->attrs : NULL;
    node->el.nattrs = nat;
    node->el.parent = NULL;  /* linked by the caller once the chain is built */
    node->el.nth = 0;        /* sibling context filled by the caller (0 = unknown, */
    node->el.nsib = 0;       /* structural pseudo-classes then fail closed) */
    node->el.nth_of_type = 0;
    node->el.nsib_of_type = 0;
    node->el.child_count = -1; /* unknown until the caller fills it */
    node->el.prev = NULL;
    node->el.dom_node = (const void *)((lxb_dom_node_t *)e);  /* for :has() descendant traversal */
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

/* Like sibling_position but only counts siblings with the SAME local name as n.
 * R2: for :nth-of-type() / :first-of-type / etc. */
static void sibling_type_position(lxb_dom_node_t *n, int *nth, int *nsib) {
    size_t nl = 0;
    const lxb_char_t *name = lxb_dom_element_local_name(lxb_dom_interface_element(n), &nl);
    if (name == NULL || nl == 0) { *nth = 0; *nsib = 0; return; }
    int before = 0, after = 0;
    *nth = 0; *nsib = 0;
    for (lxb_dom_node_t *p = n->prev; p != NULL; p = p->prev) {
        if (p->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
        size_t pl = 0;
        const lxb_char_t *pn = lxb_dom_element_local_name(lxb_dom_interface_element(p), &pl);
        if (pn != NULL && pl == nl && memcmp(name, pn, nl) == 0) {
            if (++before > CCH_NTH_MAX) return;
        }
    }
    for (lxb_dom_node_t *p = n->next; p != NULL; p = p->next) {
        if (p->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
        size_t pl = 0;
        const lxb_char_t *pn = lxb_dom_element_local_name(lxb_dom_interface_element(p), &pl);
        if (pn != NULL && pl == nl && memcmp(name, pn, nl) == 0) {
            if (++after > CCH_NTH_MAX - before) return;
        }
    }
    *nth = before + 1;
    *nsib = before + 1 + after;
}

/* Counts ALL child nodes (elements, text, comments) of the DOM element n.
 * R2: for :empty matching. */
static int count_children(lxb_dom_node_t *n) {
    int count = 0;
    for (lxb_dom_node_t *ch = n->first_child; ch != NULL; ch = ch->next)
        ++count;
    return count;
}

/* Builds the bounded css_element chain for `el` into the caller's storage:
 * the ancestor chain (for descendant/child combinators), nth/nsib on every node
 * (so a zebra `tr:nth-child(even) td` can constrain an ancestor) and the
 * preceding-sibling chain for the SUBJECT only (for its `+`/`~`, bounded to
 * CCH_SIB_MAX; a `+`/`~` on a non-subject compound or past the bound fails
 * closed). Returns the subject css_element (&chain[0].el) or NULL when el has no
 * element context. Shared by style resolution and selector matching so both see
 * identical inputs (single source of truth). */
static const css_element *build_chain(lxb_dom_element_t *el,
                                      cch_node chain[CCH_CHAIN_MAX],
                                      cch_node sibs[CCH_SIB_MAX],
                                      lxb_dom_node_t *nodes[CCH_CHAIN_MAX],
                                      int *out_n, int *out_ns, int structural) {
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
    /* Ancestor feature filter: element i carries the union of the features of everything ABOVE it,
     * so a selector needing an ancestor tag/id/class nobody above has is skipped unevaluated. */
    {
        unsigned long long acc = 0;
        for (int i = n - 1; i >= 0; --i) {
            chain[i].el.anc_bloom = acc;
            chain[i].el.anc_bloom_valid = 1;
            chain[i].el.own_bloom = csel_element_feature_bits(&chain[i].el);
            acc |= chain[i].el.own_bloom;
        }
    }

    /* Structure (positions among siblings, children counts) costs a scan of every sibling list
     * along the chain: only a selector that reads it pays for it (see csel_needs_structure). */
    for (int i = 0; structural && i < n; ++i) {
        sibling_position(nodes[i], &chain[i].el.nth, &chain[i].el.nsib);
        sibling_type_position(nodes[i], &chain[i].el.nth_of_type,
                              &chain[i].el.nsib_of_type);
        chain[i].el.child_count = count_children(nodes[i]);
    }
    int ns = 0;
    if (structural && n > 0) {
        for (lxb_dom_node_t *p = nodes[0]->prev; p != NULL && ns < CCH_SIB_MAX;
             p = p->prev) {
            if (p->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
            fill_css_node(lxb_dom_interface_element(p), &sibs[ns]);
            sibs[ns].el.parent = chain[0].el.parent;
            if (chain[0].el.nth > ns + 1) {
                sibs[ns].el.nth = chain[0].el.nth - (ns + 1);
                sibs[ns].el.nsib = chain[0].el.nsib;
            }
            sibs[ns].el.child_count = count_children(p);
            ++ns;
        }
        chain[0].el.prev = (ns > 0) ? &sibs[0].el : NULL;
        for (int i = 0; i + 1 < ns; ++i)
            sibs[i].el.prev = &sibs[i + 1].el;
    }
    *out_n = n;
    *out_ns = ns;
    return (n > 0) ? &chain[0].el : NULL;
}

/* Resolves the author presentation for one element from the document <style> sheet
 * plus its own inline style= (inline wins; the css module does the cascade). The
 * element and its ancestor chain (bounded) become the selector match inputs, so
 * descendant/child combinators (`div p`, `nav > a`) resolve. Pure (no fetch, no
 * execution): the css module drops url() and @-rules. */
css_style cch_element_style_fs(lxb_dom_element_t *el, const css_sheet *sheet,
                               double parent_font_size) {
    return cch_element_style_vars(el, sheet, parent_font_size, NULL, NULL);
}

css_style cch_element_style_vars(lxb_dom_element_t *el, const css_sheet *sheet,
                                 double parent_font_size,
                                 const struct cvr_chain *inherited,
                                 struct cvr_table *own_out) {
    cch_node chain[CCH_CHAIN_MAX];
    cch_node sibs[CCH_SIB_MAX];
    lxb_dom_node_t *nodes[CCH_CHAIN_MAX];
    int nfill = 0, nsfill = 0;
    const css_element *subject = build_chain(el, chain, sibs, nodes, &nfill, &nsfill, 1);

    /* The inherited font-size is an ENGINE INPUT, like `state`: the cascade
     * cannot discover it (font-size is computed before every other property),
     * and without it every `em` in the sheet would mean 16px regardless of the
     * element's own size. chain[0] is the subject; build_chain zeroes the view,
     * so leaving it 0 keeps the CSS initial context. */
    if (subject != NULL) {
        chain[0].el.font_size = parent_font_size;
        chain[0].el.vars = inherited;   /* an engine input too, like font_size */
    }

    /* Inline style= applies to the subject element only. */
    size_t sl = 0;
    const lxb_char_t *st =
        lxb_dom_element_get_attribute(el, (const lxb_char_t *)"style", 5, &sl);

    css_style out = css_resolve_el_ex(sheet, subject, (const char *)st, sl, own_out);
    release_nodes(chain, nfill);
    release_nodes(sibs, nsfill);
    return out;
}

css_style cch_pseudo_style(lxb_dom_element_t *el, const css_sheet *sheet, int which,
                           double font_size, const struct cvr_chain *inherited) {
    cch_node chain[CCH_CHAIN_MAX];
    cch_node sibs[CCH_SIB_MAX];
    lxb_dom_node_t *nodes[CCH_CHAIN_MAX];
    int nfill = 0, nsfill = 0;
    const css_element *subject = build_chain(el, chain, sibs, nodes, &nfill, &nsfill, 1);
    if (subject != NULL) {
        /* The generated box inherits from its element: the element's computed
         * size is the "parent" size its own em lengths resolve against. */
        chain[0].el.font_size = font_size;
        chain[0].el.vars = inherited;
    }
    css_style out = css_resolve_pseudo(sheet, subject, which);
    release_nodes(chain, nfill);
    release_nodes(sibs, nsfill);
    return out;
}

css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet) {
    return cch_element_style_fs(el, sheet, 0.0);
}

int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel) {
    if (el == NULL || sel == NULL) return 0;
    cch_node chain[CCH_CHAIN_MAX];
    cch_node sibs[CCH_SIB_MAX];
    lxb_dom_node_t *nodes[CCH_CHAIN_MAX];
    int nfill = 0, nsfill = 0;
    const css_element *subject = build_chain(el, chain, sibs, nodes, &nfill, &nsfill,
                                             csel_needs_structure(sel));
    int m = (subject != NULL) ? csel_matches(sel, subject, NULL, 0, NULL) : 0;
    release_nodes(chain, nfill);
    release_nodes(sibs, nsfill);
    return m;
}
