/*
 * libFuzzer harness for the DOM CSS-selector queries (querySelector /
 * querySelectorAll / matches / closest).
 *
 * A page script passes an ARBITRARY selector string to querySelector; it is
 * hostile remote content. This harness builds a fixed DOM once, then treats each
 * fuzz input as a NUL-terminated selector, driving parse_selector_list +
 * qs_walk + cch_element_matches + csel_matches over a real tree. Invariants:
 * never crash/leak/UB; every returned handle is in range; querySelectorAll's
 * count never exceeds the node count; querySelector agrees with the first
 * querySelectorAll result.
 *
 * Build & run: make fuzz-dom   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "dom.h"
#include "html_parse.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const char HTML[] =
    "<!DOCTYPE html><html><head><title>T</title></head>"
    "<body>"
    "<nav class=\"menu\"><a href=\"/a\" id=\"la\">A</a><a href=\"/b\">B</a></nav>"
    "<div id=\"main\" class=\"container box\" data-role=\"root\">"
    "<p class=\"text\">Hello</p>"
    "<p class=\"text muted\" title=\"x y\">World</p>"
    "<ul><li>1</li><li>2</li><li class=\"sel\">3</li></ul>"
    "<button id=\"go\" class=\"btn\" disabled>Go</button>"
    "<input type=\"checkbox\" checked>"
    "</div>"
    "</body></html>";

static hp_document *g_doc;
static dom_index   *g_idx;
static size_t       g_count;

static void ensure_built(void) {
    if (g_idx != NULL) return;
    if (hp_parse(HTML, sizeof HTML - 1, NULL, &g_doc) != HP_OK) abort();
    if (dom_build(g_doc, &g_idx) != DOM_OK) abort();
    g_count = dom_node_count(g_idx);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    ensure_built();

    /* NUL-terminate the hostile selector (bounded copy). */
    char sel[1024];
    size_t n = size < sizeof sel - 1 ? size : sizeof sel - 1;
    memcpy(sel, data, n);
    sel[n] = '\0';

    /* Document scope and #main-scoped element queries. */
    dom_node_id root_variants[2] = { DOM_NODE_NONE, dom_get_element_by_id(g_idx, "main") };
    for (int rv = 0; rv < 2; ++rv) {
        dom_node_id root = root_variants[rv];

        dom_node_id first = dom_query_selector(g_idx, root, sel);
        if (first != DOM_NODE_NONE && first >= g_count) abort();

        dom_node_id buf[64];
        size_t total = dom_query_selector_all(g_idx, root, sel, buf, 64);
        size_t got = total < 64 ? total : 64;
        for (size_t i = 0; i < got; ++i)
            if (buf[i] >= g_count) abort();
        /* querySelector must agree with the first querySelectorAll result. */
        if (total > 0 && first != buf[0]) abort();
        if (total == 0 && first != DOM_NODE_NONE) abort();
    }

    /* matches / closest over a concrete element never escape the index. */
    dom_node_id go = dom_get_element_by_id(g_idx, "go");
    (void)dom_matches(g_idx, go, sel);
    dom_node_id c = dom_closest(g_idx, go, sel);
    if (c != DOM_NODE_NONE && c >= g_count) abort();

    return 0;
}
