/*
 * dom — implementation: a queryable index over the Lexbor tree owned by an
 * hp_document. Built once, in document order, into integer-addressable node
 * handles plus O(1) by-id/tag/class hash indices and a node->id reverse map.
 *
 * Read-only: queries never execute script and never mutate the tree. The walk
 * is iterative (child/sibling/parent), so attacker-controlled nesting cannot
 * overflow the stack. The index does not own the tree (hp_document does).
 */

#define _POSIX_C_SOURCE 200809L

#include "dom.h"
#include "html_parse.h"
#include "css_chain.h"
#include "css_select.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <lexbor/dom/dom.h>
#include <lexbor/html/html.h>

/* --- small character helpers (no locale dependence) --- */

static int is_ws(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r';
}

/* Lowercase s[0..n) into out (NUL-terminated). Fails if it would not fit. */
static int to_lower_buf(const char *s, size_t n, char *out, size_t outcap) {
    if (n + 1 > outcap) return -1;
    for (size_t i = 0; i < n; ++i) {
        int c = (unsigned char)s[i];
        if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
        out[i] = (char)c;
    }
    out[n] = '\0';
    return 0;
}

static uint64_t fnv1a(const char *s, size_t n) {
    uint64_t h = 1469598103934665603ULL;
    for (size_t i = 0; i < n; ++i) {
        h ^= (unsigned char)s[i];
        h *= 1099511628211ULL;
    }
    return h;
}

static size_t ptr_hash(const void *p) {
    uintptr_t x = (uintptr_t)p;
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdULL;
    x ^= x >> 33;
    return (size_t)x;
}

/* --- string multimap: key -> ascending list of node ids --- */

typedef struct sm_entry {
    char        *key;     /* owned */
    size_t       key_len;
    dom_node_id *ids;     /* owned, ascending (document order) */
    size_t       count;
    size_t       cap;
    int          used;
} sm_entry;

typedef struct strmap {
    sm_entry *buckets;
    size_t    cap;        /* power of two, or 0 */
    size_t    size;
} strmap;

static int sm_entry_append(sm_entry *e, dom_node_id id) {
    if (e->count == e->cap) {
        size_t ncap = e->cap ? e->cap * 2 : 4;
        dom_node_id *grown = (dom_node_id *)realloc(e->ids, ncap * sizeof *grown);
        if (grown == NULL) return -1;
        e->ids = grown;
        e->cap = ncap;
    }
    e->ids[e->count++] = id;
    return 0;
}

static int sm_grow(strmap *m) {
    size_t ncap = m->cap ? m->cap * 2 : 16;
    sm_entry *nb = (sm_entry *)calloc(ncap, sizeof *nb);
    if (nb == NULL) return -1;
    size_t nmask = ncap - 1;
    for (size_t k = 0; k < m->cap; ++k) {
        if (!m->buckets[k].used) continue;
        size_t i = (size_t)fnv1a(m->buckets[k].key, m->buckets[k].key_len) & nmask;
        while (nb[i].used) i = (i + 1) & nmask;
        nb[i] = m->buckets[k];
    }
    free(m->buckets);
    m->buckets = nb;
    m->cap = ncap;
    return 0;
}

static int sm_put(strmap *m, const char *key, size_t klen, dom_node_id id) {
    if ((m->size + 1) * 4 >= m->cap * 3) {
        if (sm_grow(m) != 0) return -1;
    }
    size_t mask = m->cap - 1;
    size_t i = (size_t)fnv1a(key, klen) & mask;
    while (m->buckets[i].used) {
        sm_entry *e = &m->buckets[i];
        if (e->key_len == klen && memcmp(e->key, key, klen) == 0) {
            return sm_entry_append(e, id);
        }
        i = (i + 1) & mask;
    }
    sm_entry *e = &m->buckets[i];
    if (klen == (size_t)-1) return -1;
    e->key = (char *)malloc(klen + 1);
    if (e->key == NULL) return -1;
    memcpy(e->key, key, klen);
    e->key[klen] = '\0';
    e->key_len = klen;
    e->ids = NULL;
    e->count = 0;
    e->cap = 0;
    e->used = 1;
    m->size++;
    return sm_entry_append(e, id);
}

static const sm_entry *sm_find(const strmap *m, const char *key, size_t klen) {
    if (m->cap == 0) return NULL;
    size_t mask = m->cap - 1;
    size_t i = (size_t)fnv1a(key, klen) & mask;
    while (m->buckets[i].used) {
        const sm_entry *e = &m->buckets[i];
        if (e->key_len == klen && memcmp(e->key, key, klen) == 0) return e;
        i = (i + 1) & mask;
    }
    return NULL;
}

static void sm_free(strmap *m) {
    for (size_t i = 0; i < m->cap; ++i) {
        if (m->buckets[i].used) {
            free(m->buckets[i].key);
            free(m->buckets[i].ids);
        }
    }
    free(m->buckets);
    m->buckets = NULL;
    m->cap = 0;
    m->size = 0;
}

/* --- pointer map: node pointer -> node id --- */

typedef struct pm_entry {
    const void *key;
    dom_node_id id;
    int         used;
} pm_entry;

typedef struct ptrmap {
    pm_entry *buckets;
    size_t    cap;
    size_t    size;
} ptrmap;

static int pm_grow(ptrmap *m) {
    size_t ncap = m->cap ? m->cap * 2 : 16;
    pm_entry *nb = (pm_entry *)calloc(ncap, sizeof *nb);
    if (nb == NULL) return -1;
    size_t nmask = ncap - 1;
    for (size_t k = 0; k < m->cap; ++k) {
        if (!m->buckets[k].used) continue;
        size_t i = ptr_hash(m->buckets[k].key) & nmask;
        while (nb[i].used) i = (i + 1) & nmask;
        nb[i] = m->buckets[k];
    }
    free(m->buckets);
    m->buckets = nb;
    m->cap = ncap;
    return 0;
}

static int pm_put(ptrmap *m, const void *key, dom_node_id id) {
    if ((m->size + 1) * 4 >= m->cap * 3) {
        if (pm_grow(m) != 0) return -1;
    }
    size_t mask = m->cap - 1;
    size_t i = ptr_hash(key) & mask;
    while (m->buckets[i].used) {
        if (m->buckets[i].key == key) { m->buckets[i].id = id; return 0; }
        i = (i + 1) & mask;
    }
    m->buckets[i].key = key;
    m->buckets[i].id = id;
    m->buckets[i].used = 1;
    m->size++;
    return 0;
}

static int pm_get(const ptrmap *m, const void *key, dom_node_id *out) {
    if (m->cap == 0) return 0;
    size_t mask = m->cap - 1;
    size_t i = ptr_hash(key) & mask;
    while (m->buckets[i].used) {
        if (m->buckets[i].key == key) { *out = m->buckets[i].id; return 1; }
        i = (i + 1) & mask;
    }
    return 0;
}

static void pm_free(ptrmap *m) {
    free(m->buckets);
    m->buckets = NULL;
    m->cap = 0;
    m->size = 0;
}

/* --- the index --- */

struct dom_index {
    lxb_dom_node_t      **nodes;    /* arena: id -> element node, in document order */
    size_t                count;
    size_t                cap;      /* capacity of nodes[] (grows when JS creates nodes) */
    lxb_dom_document_t   *document; /* owning document (for title / text-node creation) */
    strmap                by_id;
    strmap                by_tag;
    strmap                by_class;
    ptrmap                rev;      /* node pointer -> id */
};

/* Iterative pre-order successor within the subtree rooted at root. */
static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root) {
    if (node->first_child != NULL) return node->first_child;
    while (node != root && node->next == NULL) {
        if (node->parent == NULL) return NULL;
        node = node->parent;
    }
    if (node == root) return NULL;
    return node->next;
}

static int valid(const dom_index *idx, dom_node_id n) {
    return idx != NULL && n < idx->count;
}

/* Index a single element's id, class tokens and tag name. */
static int index_element(dom_index *idx, lxb_dom_element_t *el, dom_node_id id) {
    size_t len = 0;

    const lxb_char_t *idv =
        lxb_dom_element_get_attribute(el, (const lxb_char_t *)"id", 2, &len);
    if (idv != NULL && len > 0) {
        if (sm_put(&idx->by_id, (const char *)idv, len, id) != 0) return -1;
    }

    const lxb_char_t *cls =
        lxb_dom_element_get_attribute(el, (const lxb_char_t *)"class", 5, &len);
    if (cls != NULL && len > 0) {
        const char *s = (const char *)cls;
        size_t i = 0;
        while (i < len) {
            while (i < len && is_ws((unsigned char)s[i])) ++i;
            size_t start = i;
            while (i < len && !is_ws((unsigned char)s[i])) ++i;
            if (i > start) {
                if (sm_put(&idx->by_class, s + start, i - start, id) != 0) return -1;
            }
        }
    }

    size_t tlen = 0;
    const lxb_char_t *tag = lxb_dom_element_qualified_name(el, &tlen);
    if (tag != NULL && tlen > 0) {
        char lower[256];
        if (to_lower_buf((const char *)tag, tlen, lower, sizeof lower) == 0) {
            if (sm_put(&idx->by_tag, lower, tlen, id) != 0) return -1;
        }
    }
    return 0;
}

/* --- public: build / free --- */

dom_status dom_build(const hp_document *doc, dom_index **out) {
    if (doc == NULL || out == NULL) return DOM_ERR_NULL_ARG;
    *out = NULL;

    lxb_dom_node_t *root = (lxb_dom_node_t *)hp_document_root(doc);
    if (root == NULL) return DOM_ERR_NULL_ARG;

    size_t n = 0;
    for (lxb_dom_node_t *node = root; node != NULL; node = node_next(node, root)) {
        if (node->type == LXB_DOM_NODE_TYPE_ELEMENT) ++n;
    }

    dom_index *idx = (dom_index *)calloc(1, sizeof *idx);
    if (idx == NULL) return DOM_ERR_OOM;

    idx->count = n;
    idx->cap = n;
    idx->nodes = (n > 0) ? (lxb_dom_node_t **)malloc(n * sizeof *idx->nodes) : NULL;
    if (n > 0 && idx->nodes == NULL) {
        free(idx);
        return DOM_ERR_OOM;
    }

    dom_node_id id = 0;
    for (lxb_dom_node_t *node = root; node != NULL; node = node_next(node, root)) {
        if (node->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
        if (idx->document == NULL) idx->document = node->owner_document;
        idx->nodes[id] = node;
        if (pm_put(&idx->rev, node, id) != 0) goto oom;
        if (index_element(idx, lxb_dom_interface_element(node), id) != 0) goto oom;
        ++id;
    }

    *out = idx;
    return DOM_OK;

oom:
    dom_free(idx);
    return DOM_ERR_OOM;
}

void dom_free(dom_index *idx) {
    if (idx == NULL) return;
    free(idx->nodes);
    sm_free(&idx->by_id);
    sm_free(&idx->by_tag);
    sm_free(&idx->by_class);
    pm_free(&idx->rev);
    free(idx);
}

/* --- public: queries --- */

size_t dom_node_count(const dom_index *idx) {
    return (idx != NULL) ? idx->count : 0;
}

dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id) {
    if (idx == NULL || id == NULL) return DOM_NODE_NONE;
    const sm_entry *e = sm_find(&idx->by_id, id, strlen(id));
    return (e != NULL && e->count > 0) ? e->ids[0] : DOM_NODE_NONE;
}

static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap) {
    if (e == NULL) return 0;
    size_t n = e->count < cap ? e->count : cap;
    for (size_t i = 0; i < n; ++i) out[i] = e->ids[i];
    return e->count;
}

size_t dom_get_by_tag(const dom_index *idx, const char *tag,
                      dom_node_id *out, size_t cap) {
    if (idx == NULL || tag == NULL) return 0;
    char lower[256];
    size_t tlen = strlen(tag);
    if (to_lower_buf(tag, tlen, lower, sizeof lower) != 0) return 0;
    return copy_ids(sm_find(&idx->by_tag, lower, tlen), out, cap);
}

size_t dom_get_by_class(const dom_index *idx, const char *cls,
                        dom_node_id *out, size_t cap) {
    if (idx == NULL || cls == NULL) return 0;
    return copy_ids(sm_find(&idx->by_class, cls, strlen(cls)), out, cap);
}

/* --- CSS-selector queries (querySelector / matches / closest) --- */

/* Max complex selectors in one comma-separated list. A longer list is truncated
 * (anti-DoS): the extra selectors are dropped, which only narrows matches. */
#define DOM_QS_MAX_SELECTORS 16

/* Reverse lookup: node pointer -> handle, or DOM_NODE_NONE if unindexed. */
static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node) {
    dom_node_id id;
    return pm_get(&idx->rev, node, &id) ? id : DOM_NODE_NONE;
}

/* Parses a selector list "a, b, c" into up to cap css_sel. Splits only on
 * TOP-LEVEL commas (respecting [], () and quotes so `[a="x,y"]` and `:not(a,b)`
 * do not split); each complex selector goes through csel_parse and an
 * unsupported/malformed one is dropped (fail closed) while the rest survive.
 * Returns the number parsed. */
static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap) {
    if (sel == NULL) return 0;
    size_t len = strlen(sel), start = 0, n = 0;
    int br = 0, par = 0;
    char quote = 0;
    for (size_t i = 0; i <= len; ++i) {
        char c = (i < len) ? sel[i] : ',';  /* virtual trailing comma flushes the last */
        if (quote) { if (c == quote) quote = 0; continue; }
        switch (c) {
            case '"': case '\'': quote = c; break;
            case '[': ++br; break;
            case ']': if (br) --br; break;
            case '(': ++par; break;
            case ')': if (par) --par; break;
            case ',':
                if (br == 0 && par == 0) {
                    if (n < cap) {
                        css_sel s;
                        if (csel_parse(sel, start, i, &s)) {
                            s.order = (int)n; s.rule = 0;
                            out[n++] = s;
                        }
                    }
                    start = i + 1;
                }
                break;
            default: break;
        }
    }
    return n;
}

/* Nonzero iff element node `cn` matches any selector in the parsed list. */
static int node_matches_any(const lxb_dom_node_t *cn,
                            const css_sel *sels, size_t nsel) {
    lxb_dom_element_t *e = lxb_dom_interface_element((lxb_dom_node_t *)cn);
    for (size_t k = 0; k < nsel; ++k)
        if (cch_element_matches(e, &sels[k])) return 1;
    return 0;
}

/* Walks candidate elements under `root` (DOM_NODE_NONE = whole document) in
 * document order, matching against the parsed list. When find_first, returns the
 * first matching handle; otherwise fills out[] up to cap, sets *total to the full
 * count (may exceed cap), and returns DOM_NODE_NONE. */
static dom_node_id qs_walk(const dom_index *idx, dom_node_id root,
                           const css_sel *sels, size_t nsel,
                           dom_node_id *out, size_t cap, size_t *total,
                           int find_first) {
    if (total != NULL) *total = 0;
    lxb_dom_node_t *walk_root, *start;
    if (root == DOM_NODE_NONE) {
        if (idx->count == 0) return DOM_NODE_NONE;
        walk_root = idx->nodes[0];                 /* topmost element */
        start = walk_root;                         /* document scope: include it */
    } else {
        if (!valid(idx, root)) return DOM_NODE_NONE;
        walk_root = idx->nodes[root];
        start = node_next(walk_root, walk_root);   /* element scope: descendants only */
    }
    size_t cnt = 0;
    for (lxb_dom_node_t *cn = start; cn != NULL; cn = node_next(cn, walk_root)) {
        if (cn->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
        if (!node_matches_any(cn, sels, nsel)) continue;
        dom_node_id id = id_of(idx, cn);
        if (id == DOM_NODE_NONE) continue;         /* unindexed: no handle to expose */
        if (find_first) return id;
        if (cnt < cap) out[cnt] = id;
        ++cnt;
    }
    if (total != NULL) *total = cnt;
    return DOM_NODE_NONE;
}

dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,
                               const char *selector) {
    if (idx == NULL || selector == NULL) return DOM_NODE_NONE;
    css_sel sels[DOM_QS_MAX_SELECTORS];
    size_t nsel = parse_selector_list(selector, sels, DOM_QS_MAX_SELECTORS);
    if (nsel == 0) return DOM_NODE_NONE;
    return qs_walk(idx, root, sels, nsel, NULL, 0, NULL, 1);
}

size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,
                              const char *selector, dom_node_id *out, size_t cap) {
    if (idx == NULL || selector == NULL) return 0;
    css_sel sels[DOM_QS_MAX_SELECTORS];
    size_t nsel = parse_selector_list(selector, sels, DOM_QS_MAX_SELECTORS);
    if (nsel == 0) return 0;
    size_t total = 0;
    (void)qs_walk(idx, root, sels, nsel, out, cap, &total, 0);
    return total;
}

int dom_matches(const dom_index *idx, dom_node_id node, const char *selector) {
    if (!valid(idx, node) || selector == NULL) return 0;
    lxb_dom_node_t *n = idx->nodes[node];
    if (n->type != LXB_DOM_NODE_TYPE_ELEMENT) return 0;
    css_sel sels[DOM_QS_MAX_SELECTORS];
    size_t nsel = parse_selector_list(selector, sels, DOM_QS_MAX_SELECTORS);
    return node_matches_any(n, sels, nsel);
}

dom_node_id dom_closest(const dom_index *idx, dom_node_id node,
                        const char *selector) {
    if (!valid(idx, node) || selector == NULL) return DOM_NODE_NONE;
    css_sel sels[DOM_QS_MAX_SELECTORS];
    size_t nsel = parse_selector_list(selector, sels, DOM_QS_MAX_SELECTORS);
    if (nsel == 0) return DOM_NODE_NONE;
    for (lxb_dom_node_t *p = idx->nodes[node];
         p != NULL && p->type == LXB_DOM_NODE_TYPE_ELEMENT; p = p->parent) {
        if (node_matches_any(p, sels, nsel)) {
            dom_node_id id = id_of(idx, p);
            if (id != DOM_NODE_NONE) return id;
        }
    }
    return DOM_NODE_NONE;
}

size_t dom_document_position(const dom_index *idx, dom_node_id node) {
    /* Ids are assigned in document order in this read-only build. */
    return valid(idx, node) ? (size_t)node : 0;
}

int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b) {
    if (!valid(idx, a) || !valid(idx, b)) return 0;
    return a < b;
}

dom_node_id dom_node_at(const dom_index *idx, size_t position) {
    if (idx == NULL || position >= idx->count) return DOM_NODE_NONE;
    return (dom_node_id)position;
}

dom_node_id dom_parent(const dom_index *idx, dom_node_id node) {
    if (!valid(idx, node)) return DOM_NODE_NONE;
    lxb_dom_node_t *p = idx->nodes[node]->parent;
    dom_node_id pid;
    if (p != NULL && p->type == LXB_DOM_NODE_TYPE_ELEMENT && pm_get(&idx->rev, p, &pid)) {
        return pid;
    }
    return DOM_NODE_NONE;
}

dom_node_id dom_first_child(const dom_index *idx, dom_node_id node) {
    if (!valid(idx, node)) return DOM_NODE_NONE;
    lxb_dom_node_t *c = idx->nodes[node]->first_child;
    while (c != NULL && c->type != LXB_DOM_NODE_TYPE_ELEMENT) c = c->next;
    dom_node_id cid;
    return (c != NULL && pm_get(&idx->rev, c, &cid)) ? cid : DOM_NODE_NONE;
}

dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node) {
    if (!valid(idx, node)) return DOM_NODE_NONE;
    lxb_dom_node_t *s = idx->nodes[node]->next;
    while (s != NULL && s->type != LXB_DOM_NODE_TYPE_ELEMENT) s = s->next;
    dom_node_id sid;
    return (s != NULL && pm_get(&idx->rev, s, &sid)) ? sid : DOM_NODE_NONE;
}

const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len) {
    if (len != NULL) *len = 0;
    if (!valid(idx, node)) return NULL;
    size_t tlen = 0;
    const lxb_char_t *tag =
        lxb_dom_element_qualified_name(lxb_dom_interface_element(idx->nodes[node]), &tlen);
    if (tag == NULL) return NULL;
    if (len != NULL) *len = tlen;
    return (const char *)tag;
}

const char *dom_get_attribute(const dom_index *idx, dom_node_id node,
                              const char *name, size_t *len) {
    if (len != NULL) *len = 0;
    if (!valid(idx, node) || name == NULL) return NULL;
    lxb_dom_element_t *el = lxb_dom_interface_element(idx->nodes[node]);
    size_t vlen = 0;
    const lxb_char_t *val = lxb_dom_element_get_attribute(el,
        (const lxb_char_t *)name, strlen(name), &vlen);
    if (val != NULL) {
        if (len != NULL) *len = vlen;
        return (const char *)val;
    }
    /* Boolean HTML attributes (checked, disabled, selected, readonly, etc.) are
     * stored by Lexbor with a NULL value pointer (valueless). Check existence via
     * has_attribute and return "" so the caller sees the attribute IS present. */
    if (lxb_dom_element_has_attribute(el, (const lxb_char_t *)name, strlen(name))) {
        if (len != NULL) *len = 0;
        return "";
    }
    return NULL;
}

size_t dom_attribute_names(const dom_index *idx, dom_node_id node,
                           const char **names, size_t *lens, size_t cap) {
    if (!valid(idx, node)) return 0;
    lxb_dom_element_t *el = lxb_dom_interface_element(idx->nodes[node]);
    size_t count = 0;
    for (lxb_dom_attr_t *attr = lxb_dom_element_first_attribute(el);
         attr != NULL; attr = lxb_dom_element_next_attribute(attr)) {
        size_t nlen = 0;
        const lxb_char_t *nm = lxb_dom_attr_qualified_name(attr, &nlen);
        if (nm != NULL && count < cap) {
            names[count] = (const char *)nm;
            if (lens != NULL) lens[count] = nlen;
        }
        count++;
    }
    return count;
}

const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len) {
    if (len != NULL) *len = 0;
    if (!valid(idx, node)) return NULL;
    size_t tl = 0;
    const lxb_char_t *t = lxb_dom_node_text_content(idx->nodes[node], &tl);
    if (t == NULL) return NULL;
    if (len != NULL) *len = tl;
    return (const char *)t;
}

const char *dom_document_title(const dom_index *idx, size_t *len) {
    if (len != NULL) *len = 0;
    if (idx == NULL || idx->document == NULL) return NULL;
    size_t tl = 0;
    const lxb_char_t *t =
        lxb_html_document_title((lxb_html_document_t *)idx->document, &tl);
    if (t == NULL) return NULL;
    if (len != NULL) *len = tl;
    return (const char *)t;
}

/* --- mutation (live JS) --- */

dom_status dom_set_text_content(dom_index *idx, dom_node_id node,
                                const char *text, size_t len) {
    if (!valid(idx, node)) return DOM_ERR_NULL_ARG;
    lxb_dom_node_t *el = idx->nodes[node];

    /* Detach (not destroy) every child so any index handle into the removed subtree
     * stays a valid pointer (it just leaves the rendered tree). */
    lxb_dom_node_t *c = el->first_child;
    while (c != NULL) {
        lxb_dom_node_t *next = c->next;
        lxb_dom_node_remove(c);
        c = next;
    }

    if (text != NULL && len > 0) {
        if (el->owner_document == NULL) return DOM_ERR_INTERNAL;
        lxb_dom_text_t *t =
            lxb_dom_document_create_text_node(el->owner_document,
                                              (const lxb_char_t *)text, len);
        if (t == NULL) return DOM_ERR_OOM;
        lxb_dom_node_insert_child(el, lxb_dom_interface_node(t));
    }
    return DOM_OK;
}

dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len) {
    if (idx == NULL || idx->document == NULL) return DOM_ERR_NULL_ARG;
    lxb_status_t s =
        lxb_html_document_title_set((lxb_html_document_t *)idx->document,
                                    (const lxb_char_t *)(text != NULL ? text : ""), len);
    return (s == LXB_STATUS_OK) ? DOM_OK : DOM_ERR_INTERNAL;
}

/* --- DOM construction (live JS) --- */

/* Appends an element node to the index, assigning the next handle. */
static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id) {
    if (idx->count == idx->cap) {
        size_t ncap = idx->cap ? idx->cap * 2 : 8;
        lxb_dom_node_t **grown =
            (lxb_dom_node_t **)realloc(idx->nodes, ncap * sizeof *grown);
        if (grown == NULL) return DOM_ERR_OOM;
        idx->nodes = grown;
        idx->cap = ncap;
    }
    dom_node_id id = (dom_node_id)idx->count;
    idx->nodes[id] = node;
    if (pm_put(&idx->rev, node, id) != 0) return DOM_ERR_OOM;
    idx->count++;
    *out_id = id;
    return DOM_OK;
}

dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id) {
    if (idx == NULL || tag == NULL || out_id == NULL || idx->document == NULL)
        return DOM_ERR_NULL_ARG;
    size_t tlen = strlen(tag);
    char lower[256];
    if (tlen == 0 || to_lower_buf(tag, tlen, lower, sizeof lower) != 0)
        return DOM_ERR_NULL_ARG;

    lxb_dom_element_t *el =
        lxb_dom_document_create_element(idx->document, (const lxb_char_t *)lower, tlen, NULL);
    if (el == NULL) return DOM_ERR_OOM;

    dom_node_id id;
    dom_status s = idx_push(idx, lxb_dom_interface_node(el), &id);
    if (s != DOM_OK) return s;
    (void)sm_put(&idx->by_tag, lower, tlen, id); /* queryable via getByTag */
    *out_id = id;
    return DOM_OK;
}

dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child) {
    if (!valid(idx, parent) || !valid(idx, child) || parent == child)
        return DOM_ERR_NULL_ARG;
    lxb_dom_node_t *p = idx->nodes[parent];
    lxb_dom_node_t *c = idx->nodes[child];
    /* Reject a cycle: child must not be an ancestor of parent (would loop the walk). */
    for (lxb_dom_node_t *a = p; a != NULL; a = a->parent) {
        if (a == c) return DOM_ERR_NULL_ARG;
    }
    lxb_dom_node_remove(c);          /* detach from any current position */
    lxb_dom_node_insert_child(p, c); /* append as last child */
    return DOM_OK;
}

dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child) {
    if (!valid(idx, parent) || !valid(idx, child)) return DOM_ERR_NULL_ARG;
    lxb_dom_node_t *c = idx->nodes[child];
    if (c->parent != idx->nodes[parent]) return DOM_ERR_NULL_ARG;
    lxb_dom_node_remove(c); /* detach; node stays valid in the index */
    return DOM_OK;
}

dom_status dom_set_attribute(dom_index *idx, dom_node_id node,
                             const char *name, const char *value) {
    if (!valid(idx, node) || name == NULL) return DOM_ERR_NULL_ARG;
    const char *v = (value != NULL) ? value : "";
    size_t nl = strlen(name), vl = strlen(v);

    lxb_dom_attr_t *a =
        lxb_dom_element_set_attribute(lxb_dom_interface_element(idx->nodes[node]),
                                      (const lxb_char_t *)name, nl,
                                      (const lxb_char_t *)v, vl);
    if (a == NULL) return DOM_ERR_OOM;

    /* Keep id/class lookups working for dynamically-set attributes. */
    if (nl == 2 && (name[0] | 0x20) == 'i' && (name[1] | 0x20) == 'd' && vl > 0) {
        (void)sm_put(&idx->by_id, v, vl, node);
    } else if (nl == 5 && (name[0] | 0x20) == 'c' && (name[1] | 0x20) == 'l' &&
               (name[2] | 0x20) == 'a' && (name[3] | 0x20) == 's' &&
               (name[4] | 0x20) == 's') {
        size_t i = 0;
        while (i < vl) {
            while (i < vl && is_ws((unsigned char)v[i])) ++i;
            size_t start = i;
            while (i < vl && !is_ws((unsigned char)v[i])) ++i;
            if (i > start) (void)sm_put(&idx->by_class, v + start, i - start, node);
        }
    }
    return DOM_OK;
}

dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name) {
    if (!valid(idx, node) || name == NULL) return DOM_ERR_NULL_ARG;
    lxb_status_t st =
        lxb_dom_element_remove_attribute(lxb_dom_interface_element(idx->nodes[node]),
                                         (const lxb_char_t *)name, strlen(name));
    return (st == LXB_STATUS_OK) ? DOM_OK : DOM_ERR_INTERNAL;
}

/* Indexes the element subtree rooted at sub (sub included), in pre-order. */
static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub) {
    for (lxb_dom_node_t *w = sub; w != NULL; w = node_next(w, sub)) {
        if (w->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
        dom_node_id id;
        if (idx_push(idx, w, &id) != DOM_OK) return DOM_ERR_OOM;
        if (index_element(idx, lxb_dom_interface_element(w), id) != 0) return DOM_ERR_OOM;
    }
    return DOM_OK;
}

dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,
                              const char *html, size_t len) {
    if (!valid(idx, node)) return DOM_ERR_NULL_ARG;
    if (idx->document == NULL) return DOM_ERR_INTERNAL;
    lxb_dom_node_t *el = idx->nodes[node];

    lxb_dom_node_t *frag =
        lxb_html_document_parse_fragment((lxb_html_document_t *)idx->document,
                                         lxb_dom_interface_element(el),
                                         (const lxb_char_t *)(html != NULL ? html : ""),
                                         len);
    if (frag == NULL) return DOM_ERR_OOM;

    /* Detach (not destroy) the current children: any index handle into them stays valid. */
    lxb_dom_node_t *c = el->first_child;
    while (c != NULL) {
        lxb_dom_node_t *next = c->next;
        lxb_dom_node_remove(c);
        c = next;
    }

    /* Move each parsed top-level node into el and index its (new) element subtree. */
    lxb_dom_node_t *child = frag->first_child;
    while (child != NULL) {
        lxb_dom_node_t *next = child->next;
        lxb_dom_node_remove(child);
        lxb_dom_node_insert_child(el, child);
        dom_status s = index_subtree(idx, child);
        if (s != DOM_OK) return s;
        child = next;
    }
    return DOM_OK;
}

/* Accumulator for the serializer callback: a growing buffer hard-capped at
 * DOM_INNER_HTML_MAX so hostile content cannot force an unbounded allocation. */
typedef struct ih_acc {
    char  *buf;
    size_t len, cap;
    int    overflow;
} ih_acc;

static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx) {
    ih_acc *a = (ih_acc *)ctx;
    if (a->overflow) return LXB_STATUS_ERROR;
    if (a->len + len + 1u > DOM_INNER_HTML_MAX) {
        a->overflow = 1;
        return LXB_STATUS_ERROR;
    }
    if (a->len + len + 1u > a->cap) {
        size_t nc = (a->cap != 0u) ? a->cap * 2u : 256u;
        while (nc < a->len + len + 1u) nc *= 2u;
        char *g = (char *)realloc(a->buf, nc);
        if (g == NULL) { a->overflow = 1; return LXB_STATUS_ERROR; }
        a->buf = g;
        a->cap = nc;
    }
    memcpy(a->buf + a->len, data, len);
    a->len += len;
    return LXB_STATUS_OK;
}

dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,
                              char **out, size_t *out_len) {
    if (out != NULL) *out = NULL;
    if (out_len != NULL) *out_len = 0;
    if (!valid(idx, node) || out == NULL || out_len == NULL) return DOM_ERR_NULL_ARG;

    ih_acc a = { NULL, 0, 0, 0 };
    lxb_status_t st = lxb_html_serialize_deep_cb(idx->nodes[node], ih_append, &a);
    if (st != LXB_STATUS_OK) {
        free(a.buf);
        return DOM_ERR_OOM;   /* over the cap or allocation failure: fail closed */
    }
    if (a.buf == NULL) {
        a.buf = (char *)malloc(1u);
        if (a.buf == NULL) return DOM_ERR_OOM;
    }
    a.buf[a.len] = '\0';
    *out = a.buf;
    *out_len = a.len;
    return DOM_OK;
}
