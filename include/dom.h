#ifndef FREEDOM_DOM_H
#define FREEDOM_DOM_H

#include <stddef.h>
#include <stdint.h>

#include "html_parse.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * dom — a queryable index over the inert tree produced by html_parse.
 *
 * Nodes become integer-addressable handles assigned in document order, with
 * O(1) by-id / by-tag / by-class hash indices and document-order primitives
 * that are binary-search friendly. This is the read-only substrate the JS
 * sandbox exposes to scripts; it never executes script and never mutates the
 * tree. The Lexbor backend stays encapsulated: no lxb_* type appears here.
 *
 * The index references the tree owned by hp_document, so the document MUST
 * outlive the index. See spec/dom.md for the full contract.
 */

typedef enum dom_status {
    DOM_OK = 0,
    DOM_ERR_NULL_ARG,  /* doc/out was NULL, or the document had no root */
    DOM_ERR_OOM,       /* allocation failed */
    DOM_ERR_INTERNAL   /* backend returned an unexpected state */
} dom_status;

/* Integer node handle. Assigned in document order at build time. */
typedef uint32_t dom_node_id;

/* "No such node" sentinel returned by lookups and navigation. */
#define DOM_NODE_NONE ((dom_node_id)0xFFFFFFFFu)

/* Opaque queryable index. */
typedef struct dom_index dom_index;

/* Builds the index over an already-parsed document. doc must outlive *out.
 * doc == NULL / out == NULL => DOM_ERR_NULL_ARG.
 * On DOM_OK, *out must be released with dom_free. */
dom_status dom_build(const hp_document *doc, dom_index **out);

/* Idempotent; safe on NULL and safe to call twice. Does not free the tree. */
void dom_free(dom_index *idx);

/* Number of element nodes indexed. NULL idx => 0. */
size_t dom_node_count(const dom_index *idx);

/* --- key lookups --- */

/* O(1). First match in document order, or DOM_NODE_NONE. Case-sensitive. */
dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id);

/* Writes up to cap matching ids (in document order) into out; returns the total
 * match count (which may exceed cap, so the caller can size a buffer). */
size_t dom_get_by_tag(const dom_index *idx, const char *tag,
                      dom_node_id *out, size_t cap);
size_t dom_get_by_class(const dom_index *idx, const char *cls,
                        dom_node_id *out, size_t cap);

/* --- CSS-selector queries (querySelector / matches / closest) --- */

/* These reuse the author-CSS selector engine (css_select via css_chain), so
 * `dom.querySelector('nav > a.link')` matches exactly like a stylesheet rule.
 * The selector is a hostile string: parsing is bounded and fails closed (an
 * unsupported or malformed complex selector in the list is dropped, the rest
 * survive; an empty result never matches). The supported subset is css_select's
 * (type, .class, #id, universal, [attr] operators, the structural/link
 * pseudo-classes, descendant/child/sibling combinators); :not()/:is() and
 * pseudo-elements are not.
 *
 * `root` scopes the walk: DOM_NODE_NONE searches the whole document (every
 * element); a valid element searches its STRICT descendants only (never itself),
 * matching the DOM Element.querySelector contract. Combinators still resolve
 * against each candidate's real ancestor chain regardless of scope. */

/* First element in document order matching the selector list, or DOM_NODE_NONE. */
dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,
                               const char *selector);

/* Writes up to cap matching ids (document order) into out; returns the total
 * match count (may exceed cap, so the caller can size a buffer). */
size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,
                              const char *selector, dom_node_id *out, size_t cap);

/* Nonzero iff node itself matches the selector list (Element.matches). */
int dom_matches(const dom_index *idx, dom_node_id node, const char *selector);

/* Nearest element at or above node matching the selector list, or DOM_NODE_NONE
 * (Element.closest). */
dom_node_id dom_closest(const dom_index *idx, dom_node_id node,
                        const char *selector);

/* --- document order (binary-search friendly) --- */

/* 0-based document-order position of node, or 0 if node is invalid. */
size_t dom_document_position(const dom_index *idx, dom_node_id node);

/* Nonzero iff a precedes b in document order. */
int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);

/* Node at the given document-order position, or DOM_NODE_NONE if out of range. */
dom_node_id dom_node_at(const dom_index *idx, size_t position);

/* --- navigation (element-only; DOM_NODE_NONE at boundaries) --- */

dom_node_id dom_parent(const dom_index *idx, dom_node_id node);
dom_node_id dom_first_child(const dom_index *idx, dom_node_id node);
dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node);

/* --- reads (borrowed memory, valid while idx and doc are alive) --- */

/* Lowercase qualified tag name, or NULL. *len (optional) excludes the NUL. */
const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);

/* Attribute value by name, or NULL if absent. *len (optional) excludes NUL. */
const char *dom_get_attribute(const dom_index *idx, dom_node_id node,
                              const char *name, size_t *len);

/* Concatenated text content of node's subtree (borrowed, valid while idx/doc are
 * alive), or NULL. *len (optional) excludes the NUL. */
const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len);

/* Current document <title> text (borrowed), or NULL. *len excludes the NUL. */
const char *dom_document_title(const dom_index *idx, size_t *len);

/* --- mutation (live JS) ---
 * Memory-safe under an existing index: removed children are DETACHED
 * (lxb_dom_node_remove unlinks but does NOT free), so a handle still pointing at a
 * detached node stays valid (it just becomes unreachable from the root and is no
 * longer rendered). These never call lxb_dom_node_destroy. */

/* Replaces node's children with a single text node carrying text[0..len) (an empty
 * text clears the children). node invalid => DOM_ERR_NULL_ARG; OOM => DOM_ERR_OOM. */
dom_status dom_set_text_content(dom_index *idx, dom_node_id node,
                                const char *text, size_t len);

/* Sets the document <title> (creates the element if missing, via the html document).
 * idx/document NULL => DOM_ERR_NULL_ARG; backend failure => DOM_ERR_INTERNAL. */
dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len);

/* --- DOM construction (live JS, Hito 20c) ---
 * Adding nodes is inherently memory-safe (it never frees indexed nodes). New nodes
 * are appended to the index so they get a queryable handle; document-order helpers
 * (precedes/position) are NOT recomputed for them. */

/* Creates a detached element with the given tag (lowercased), registers it in the
 * index (also under getByTag), and returns its handle in *out_id. Place it with
 * dom_append_child. tag empty / no document => DOM_ERR_NULL_ARG; OOM => DOM_ERR_OOM. */
dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id);

/* Appends child as parent's last child, detaching it from any current parent first.
 * Rejects a cycle (child being an ancestor of parent). Invalid handle / self / cycle
 * => DOM_ERR_NULL_ARG. */
dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child);

/* Detaches child (which must currently be a child of parent) from the tree; the node
 * stays valid in the index (not freed). Invalid handle / not-a-child => DOM_ERR_NULL_ARG. */
dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child);

/* Sets attribute name=value on node. Setting "id"/"class" also adds the value to the
 * lookup indices (so getElementById/getByClass find the node; old keys are not pruned).
 * Invalid handle / NULL name => DOM_ERR_NULL_ARG; OOM => DOM_ERR_OOM. */
dom_status dom_set_attribute(dom_index *idx, dom_node_id node,
                             const char *name, const char *value);

/* Removes attribute name from node (no-op if absent). Like dom_set_attribute, the
 * id/class lookup indices are not pruned (a removed id may still resolve until the
 * next render) -- consistent with set's best-effort dynamic indexing. Invalid handle
 * / NULL name => DOM_ERR_NULL_ARG; backend failure => DOM_ERR_INTERNAL. */
dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name);

/* Replaces node's children with the parsed HTML fragment (node as context element).
 * Old children are DETACHED (not freed), the parsed nodes are inserted, and the new
 * element subtree is indexed (queryable). Any <script> in the fragment is inert (never
 * executed; page_view hides it). Invalid handle => DOM_ERR_NULL_ARG; parse/OOM =>
 * DOM_ERR_OOM. */
dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,
                              const char *html, size_t len);

/* Cap on one innerHTML serialization (anti-DoS: hostile content cannot force an
 * unbounded allocation through the getter). Over the cap => DOM_ERR_OOM. */
#define DOM_INNER_HTML_MAX (1024u * 1024u)

/* Serializes node's CHILDREN back to HTML (the innerHTML getter). On DOM_OK *out
 * is a NUL-terminated heap buffer the CALLER frees (free()) and *out_len its
 * length (no children => an owned empty string). Bounded by DOM_INNER_HTML_MAX
 * (fail closed, nothing allocated on error). Invalid handle / NULL out =>
 * DOM_ERR_NULL_ARG. */
dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,
                              char **out, size_t *out_len);

#endif /* FREEDOM_DOM_H */
