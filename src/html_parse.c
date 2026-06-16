/*
 * html_parse — implementation (Lexbor 3.0.0 backend).
 *
 * The DOM tree is walked iteratively (child/sibling/parent pointers), never
 * recursively, so attacker-controlled nesting depth cannot overflow the stack.
 * Sanitisation mutates the tree once in hp_parse; the query functions only read.
 */

#define _POSIX_C_SOURCE 200809L

#include "html_parse.h"

#include <stdlib.h>
#include <string.h>

#include <lexbor/html/html.h>
#include <lexbor/dom/dom.h>
#include <lexbor/tag/const.h>

struct hp_document {
    lxb_html_document_t *doc;
};

/* --- helpers --- */

static char *dup_bytes(const lxb_char_t *src, size_t len) {
    char *out = (char *)malloc(len + 1);
    if (out == NULL) return NULL;
    if (len != 0 && src != NULL) memcpy(out, src, len);
    out[len] = '\0';
    return out;
}

/* Iterative pre-order successor of node within the subtree rooted at root. */
static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root) {
    if (node->first_child != NULL) return node->first_child;
    while (node != root && node->next == NULL) {
        if (node->parent == NULL) return NULL;
        node = node->parent;
    }
    if (node == root) return NULL;
    return node->next;
}

static int attr_is_event_handler(const lxb_dom_attr_t *attr) {
    size_t len = 0;
    const lxb_char_t *name = lxb_dom_attr_qualified_name(attr, &len);
    if (name == NULL || len < 3) return 0; /* "on" + at least one char */
    return (name[0] == 'o' || name[0] == 'O') && (name[1] == 'n' || name[1] == 'N');
}

static int node_is_script(const lxb_dom_node_t *node) {
    if (node->type != LXB_DOM_NODE_TYPE_ELEMENT) return 0;
    lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)node);
    return lxb_dom_element_tag_id(el) == LXB_TAG_SCRIPT;
}

static void strip_scripts(lxb_html_document_t *document) {
    lxb_dom_node_t *root = lxb_dom_interface_node(document);
    lxb_dom_node_t **list = NULL;
    size_t count = 0, cap = 0;

    for (lxb_dom_node_t *n = root; n != NULL; n = node_next(n, root)) {
        if (!node_is_script(n)) continue;
        if (count == cap) {
            size_t ncap = cap ? cap * 2 : 16;
            lxb_dom_node_t **grown = (lxb_dom_node_t **)realloc(list, ncap * sizeof *grown);
            if (grown == NULL) break; /* best effort; strip what we have */
            list = grown;
            cap = ncap;
        }
        list[count++] = n;
    }

    for (size_t i = 0; i < count; ++i) {
        lxb_dom_node_remove(list[i]);
        lxb_dom_node_destroy_deep(list[i]);
    }
    free(list);
}

static void strip_event_handlers(lxb_html_document_t *document) {
    lxb_dom_node_t *root = lxb_dom_interface_node(document);
    for (lxb_dom_node_t *n = root; n != NULL; n = node_next(n, root)) {
        if (n->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
        lxb_dom_element_t *el = lxb_dom_interface_element(n);
        int again = 1;
        while (again) {
            again = 0;
            for (lxb_dom_attr_t *attr = lxb_dom_element_first_attribute(el);
                 attr != NULL;
                 attr = lxb_dom_element_next_attribute(attr)) {
                if (attr_is_event_handler(attr)) {
                    (void)lxb_dom_element_attr_remove(el, attr);
                    again = 1; /* iterator invalidated; restart this element */
                    break;
                }
            }
        }
    }
}

/* --- public: config & validator --- */

hp_config hp_config_default(void) {
    hp_config c;
    c.max_bytes = HP_DEFAULT_MAX_BYTES;
    c.strip_scripts = 1;
    c.strip_event_handlers = 1;
    return c;
}

hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg) {
    if (html == NULL) return HP_ERR_NULL_ARG;
    size_t cap = (cfg != NULL && cfg->max_bytes != 0) ? cfg->max_bytes : HP_DEFAULT_MAX_BYTES;
    if (len == 0) return HP_ERR_EMPTY;
    if (len > cap) return HP_ERR_TOO_LARGE;
    return HP_OK;
}

/* --- public: parse --- */

hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out) {
    if (html == NULL || out == NULL) return HP_ERR_NULL_ARG;
    *out = NULL;

    hp_config local = (cfg != NULL) ? *cfg : hp_config_default();
    if (local.max_bytes == 0) local.max_bytes = HP_DEFAULT_MAX_BYTES;

    hp_status vs = hp_validate_input(html, len, &local);
    if (vs != HP_OK) return vs;

    lxb_html_document_t *document = lxb_html_document_create();
    if (document == NULL) return HP_ERR_OOM;

    lxb_status_t st = lxb_html_document_parse(document, (const lxb_char_t *)html, len);
    if (st != LXB_STATUS_OK) {
        lxb_html_document_destroy(document);
        return HP_ERR_PARSE;
    }

    if (local.strip_scripts) strip_scripts(document);
    if (local.strip_event_handlers) strip_event_handlers(document);

    hp_document *wrap = (hp_document *)malloc(sizeof *wrap);
    if (wrap == NULL) {
        lxb_html_document_destroy(document);
        return HP_ERR_OOM;
    }
    wrap->doc = document;
    *out = wrap;
    return HP_OK;
}

/* --- public: queries --- */

size_t hp_element_count(const hp_document *doc) {
    if (doc == NULL || doc->doc == NULL) return 0;
    size_t c = 0;
    lxb_dom_node_t *root = lxb_dom_interface_node(doc->doc);
    for (lxb_dom_node_t *n = root; n != NULL; n = node_next(n, root)) {
        if (n->type == LXB_DOM_NODE_TYPE_ELEMENT) ++c;
    }
    return c;
}

size_t hp_script_count(const hp_document *doc) {
    if (doc == NULL || doc->doc == NULL) return 0;
    size_t c = 0;
    lxb_dom_node_t *root = lxb_dom_interface_node(doc->doc);
    for (lxb_dom_node_t *n = root; n != NULL; n = node_next(n, root)) {
        if (node_is_script(n)) ++c;
    }
    return c;
}

size_t hp_event_handler_count(const hp_document *doc) {
    if (doc == NULL || doc->doc == NULL) return 0;
    size_t c = 0;
    lxb_dom_node_t *root = lxb_dom_interface_node(doc->doc);
    for (lxb_dom_node_t *n = root; n != NULL; n = node_next(n, root)) {
        if (n->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
        lxb_dom_element_t *el = lxb_dom_interface_element(n);
        for (lxb_dom_attr_t *attr = lxb_dom_element_first_attribute(el);
             attr != NULL;
             attr = lxb_dom_element_next_attribute(attr)) {
            if (attr_is_event_handler(attr)) ++c;
        }
    }
    return c;
}

char *hp_extract_text(const hp_document *doc, size_t *out_len) {
    if (out_len != NULL) *out_len = 0;
    if (doc == NULL || doc->doc == NULL) return NULL;

    lxb_html_body_element_t *body = lxb_html_document_body_element(doc->doc);
    lxb_dom_node_t *node = (body != NULL)
        ? lxb_dom_interface_node(body)
        : lxb_dom_interface_node(doc->doc);

    size_t len = 0;
    lxb_char_t *text = lxb_dom_node_text_content(node, &len);
    if (text == NULL) return dup_bytes((const lxb_char_t *)"", 0);

    char *copy = dup_bytes(text, len);
    lxb_dom_document_destroy_text(lxb_dom_interface_document(doc->doc), text);
    if (copy != NULL && out_len != NULL) *out_len = len;
    return copy;
}

char *hp_get_title(const hp_document *doc, size_t *out_len) {
    if (out_len != NULL) *out_len = 0;
    if (doc == NULL || doc->doc == NULL) return NULL;

    size_t len = 0;
    const lxb_char_t *title = lxb_html_document_title(doc->doc, &len);
    if (title == NULL) return dup_bytes((const lxb_char_t *)"", 0);

    char *copy = dup_bytes(title, len);
    if (copy != NULL && out_len != NULL) *out_len = len;
    return copy;
}

/* --- public: cleanup --- */

void hp_free(char *buf) {
    free(buf);
}

void hp_document_free(hp_document *doc) {
    if (doc == NULL) return;
    if (doc->doc != NULL) lxb_html_document_destroy(doc->doc);
    free(doc);
}

const void *hp_document_root(const hp_document *doc) {
    if (doc == NULL || doc->doc == NULL) return NULL;
    return lxb_dom_interface_node(doc->doc);
}
