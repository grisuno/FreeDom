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
    size_t vlen = 0;
    const lxb_char_t *val =
        lxb_dom_element_get_attribute(lxb_dom_interface_element(idx->nodes[node]),
                                      (const lxb_char_t *)name, strlen(name), &vlen);
    if (val == NULL) return NULL;
    if (len != NULL) *len = vlen;
    return (const char *)val;
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
