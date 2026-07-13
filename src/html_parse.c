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
    if (len == (size_t)-1) return NULL; /* guard: len+1 would overflow to 0 */
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

/* Case-insensitive (ASCII) substring test over a length-delimited attribute value.
 * needle must be lowercase letters. */
static int mem_contains_ci(const lxb_char_t *hay, size_t hlen, const char *needle) {
    size_t nlen = strlen(needle);
    if (hay == NULL || nlen == 0 || hlen < nlen) return 0;
    for (size_t i = 0; i + nlen <= hlen; ++i) {
        size_t j = 0;
        while (j < nlen && (char)(hay[i + j] | 0x20) == needle[j]) j++;
        if (j == nlen) return 1;
    }
    return 0;
}

/* How one <script> element executes. */
enum { SCRIPT_SKIP = 0, SCRIPT_INLINE = 1, SCRIPT_EXTERNAL = 2 };

/* Classifies a <script>: a classic program runs only when its type is absent/empty
 * or a JavaScript MIME type (contains "javascript"/"ecmascript"). Every other type
 * is a data block the browser never executes -- JSON/LD data, ES modules
 * (import/export cannot run as a classic script), and template blocks like
 * text/x-jquery-tmpl / text/html / text/template (executing their markup throws a
 * SyntaxError; this was Slashdot's "#each" errors). Fail closed: unrecognized type
 * -> skip. A src attribute makes it external (its inline body, if any, is ignored --
 * browser rule); otherwise it runs from its inline source. The parser never
 * fetches: external scripts are only REPORTED with their raw src. Mirrors
 * ctype_is_javascript in tab.c (same rule for the fetched Content-Type). */
static int script_classify(const lxb_dom_node_t *n,
                           const lxb_char_t **src, size_t *src_len) {
    lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)n);
    size_t len = 0;
    const lxb_char_t *type =
        lxb_dom_element_get_attribute(el, (const lxb_char_t *)"type", 4, &len);
    if (type != NULL && len > 0
        && !mem_contains_ci(type, len, "javascript")
        && !mem_contains_ci(type, len, "ecmascript"))
        return SCRIPT_SKIP;
    size_t slen = 0;
    const lxb_char_t *s =
        lxb_dom_element_get_attribute(el, (const lxb_char_t *)"src", 3, &slen);
    if (s != NULL) {
        if (slen == 0) return SCRIPT_SKIP; /* src="" names no resource */
        *src = s;
        *src_len = slen;
        return SCRIPT_EXTERNAL;
    }
    return SCRIPT_INLINE;
}

/* Collects each executable <script> as its own entry, in document order: inline
 * source for classic inline scripts, the raw src attribute for external ones.
 * Browsers run each <script> as a separate program, so the worker evaluates them
 * one by one: an uncaught exception in one script must not abort the others
 * (concatenating into a single eval would let the first failure kill them all).
 * Bounded by HP_MAX_SCRIPTS (fail-closed anti-DoS). NULL with *out_count == 0 when
 * there are none or on allocation failure; release with hp_free_scripts. */
hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count) {
    if (out_count != NULL) *out_count = 0;
    if (doc == NULL || doc->doc == NULL) return NULL;
    lxb_dom_node_t *root = lxb_dom_interface_node(doc->doc);

    hp_script *list = NULL;
    size_t count = 0, cap = 0;
    for (lxb_dom_node_t *n = root; n != NULL; n = node_next(n, root)) {
        if (count >= HP_MAX_SCRIPTS) break; /* fail closed: drop the excess */
        if (!node_is_script(n)) continue;
        const lxb_char_t *sattr = NULL;
        size_t slen = 0;
        int cls = script_classify(n, &sattr, &slen);
        if (cls == SCRIPT_SKIP) continue;
        char  *text = NULL, *src = NULL, *type = NULL;
        size_t tl = 0;
        {
            size_t tlen = 0;
            const lxb_char_t *tval =
                lxb_dom_element_get_attribute(
                    lxb_dom_interface_element((lxb_dom_node_t *)n),
                    (const lxb_char_t *)"type", 4, &tlen);
            if (tval != NULL) type = dup_bytes(tval, tlen);
        }
        if (cls == SCRIPT_INLINE) {
            const lxb_char_t *t = lxb_dom_node_text_content(n, &tl);
            if (t == NULL || tl == 0) { free(type); continue; }
            text = dup_bytes(t, tl);
            if (text == NULL) { free(type); hp_free_scripts(list, count); return NULL; }
        } else {
            src = dup_bytes(sattr, slen);
            if (src == NULL) { free(type); hp_free_scripts(list, count); return NULL; }
        }
        if (count == cap) {
            size_t ncap = cap ? cap * 2 : 8;
            hp_script *grown = (hp_script *)realloc(list, ncap * sizeof *grown);
            if (grown == NULL) {
                free(text); free(src); free(type);
                hp_free_scripts(list, count);
                return NULL;
            }
            list = grown; cap = ncap;
        }
        list[count].text = text;
        list[count].len  = tl;
        list[count].src  = src;
        list[count].type = type;
        count++;
    }
    if (count == 0) { free(list); return NULL; }
    if (out_count != NULL) *out_count = count;
    return list;
}

void hp_free_scripts(hp_script *scripts, size_t count) {
    if (scripts == NULL) return;
    for (size_t i = 0; i < count; ++i) {
        free(scripts[i].text);
        free(scripts[i].src);
        free(scripts[i].type);
    }
    free(scripts);
}

/* Whitespace-separated token test over a length-delimited attribute value, ASCII
 * case-insensitive: rel="preload stylesheet" has the token "stylesheet";
 * rel="notstylesheet" does not. needle must be lowercase. */
static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle) {
    size_t nlen = strlen(needle);
    size_t i = 0;
    while (i < vlen) {
        while (i < vlen && (val[i] == ' ' || val[i] == '\t' || val[i] == '\n'
                            || val[i] == '\r' || val[i] == '\f')) i++;
        size_t start = i;
        while (i < vlen && val[i] != ' ' && val[i] != '\t' && val[i] != '\n'
                        && val[i] != '\r' && val[i] != '\f') i++;
        if (i - start == nlen) {
            size_t j = 0;
            while (j < nlen && (char)(val[start + j] | 0x20) == needle[j]) j++;
            if (j == nlen) return 1;
        }
    }
    return 0;
}

/* An applicable stylesheet <link>: rel token "stylesheet" and not "alternate";
 * a non-empty href; media absent/empty or mentioning screen/all (fail closed).
 * On a match, href and hlen point into the element's attribute storage. */
static int link_is_active_stylesheet(lxb_dom_element_t *el,
                                     const lxb_char_t **href, size_t *hlen) {
    size_t rlen = 0;
    const lxb_char_t *rel =
        lxb_dom_element_get_attribute(el, (const lxb_char_t *)"rel", 3, &rlen);
    if (rel == NULL || !attr_has_token_ci(rel, rlen, "stylesheet")
        || attr_has_token_ci(rel, rlen, "alternate")) return 0;
    size_t len = 0;
    const lxb_char_t *h =
        lxb_dom_element_get_attribute(el, (const lxb_char_t *)"href", 4, &len);
    if (h == NULL || len == 0) return 0;
    size_t mlen = 0;
    const lxb_char_t *media =
        lxb_dom_element_get_attribute(el, (const lxb_char_t *)"media", 5, &mlen);
    if (media != NULL && mlen != 0
        && !mem_contains_ci(media, mlen, "screen")
        && !mem_contains_ci(media, mlen, "all")) return 0;
    *href = h;
    *hlen = len;
    return 1;
}

char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count) {
    if (out_count != NULL) *out_count = 0;
    if (doc == NULL || doc->doc == NULL) return NULL;
    lxb_dom_node_t *root = lxb_dom_interface_node(doc->doc);

    char **list = NULL;
    size_t count = 0, cap = 0;
    for (lxb_dom_node_t *n = root; n != NULL; n = node_next(n, root)) {
        if (count >= HP_MAX_STYLESHEETS) break; /* fail closed: drop the excess */
        if (n->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
        lxb_dom_element_t *el = lxb_dom_interface_element(n);
        if (lxb_dom_element_tag_id(el) != LXB_TAG_LINK) continue;
        const lxb_char_t *href = NULL;
        size_t hlen = 0;
        if (!link_is_active_stylesheet(el, &href, &hlen)) continue;
        char *dup = dup_bytes(href, hlen);
        if (dup == NULL) { hp_free_stylesheet_hrefs(list, count); return NULL; }
        if (count == cap) {
            size_t ncap = cap ? cap * 2 : 8;
            char **grown = (char **)realloc(list, ncap * sizeof *grown);
            if (grown == NULL) {
                free(dup);
                hp_free_stylesheet_hrefs(list, count);
                return NULL;
            }
            list = grown; cap = ncap;
        }
        list[count++] = dup;
    }
    if (count == 0) { free(list); return NULL; }
    if (out_count != NULL) *out_count = count;
    return list;
}

void hp_free_stylesheet_hrefs(char **hrefs, size_t count) {
    if (hrefs == NULL) return;
    for (size_t i = 0; i < count; ++i) free(hrefs[i]);
    free(hrefs);
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
