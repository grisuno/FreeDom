/* Fuzzer for anchor (spec/anchor.md) and url_split_location: a hostile document x a
 * hostile fragment. Properties: the percent decoder never overruns and is the identity on
 * text without '%'; a resolved target is connected and carries an id or a name; collect
 * writes the target first, never more than cap, 0 < nsub <= n, and no handle twice; the
 * location split of a file:///...#hostile URL stays inside the URL. */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "anchor.h"
#include "dom.h"
#include "html_parse.h"
#include "url.h"

static void check_decode(const char *frag) {
    char out[ANC_MAX_FRAGMENT];
    size_t n = anc_percent_decode(frag, out, sizeof out);
    if (n == (size_t)-1) { if (out[0] != '\0') abort(); return; }
    if (n >= sizeof out || out[n] != '\0') abort();
    if (strchr(frag, '%') == NULL && (n != strlen(frag) || memcmp(out, frag, n) != 0)) abort();
}

static void check_location(const char *frag) {
    char url[ANC_MAX_FRAGMENT + 32];
    memcpy(url, "file:///d/p.html#", 17);
    size_t fl = strlen(frag);
    memcpy(url + 17, frag, fl + 1);
    url_parts u;
    if (url_split_location(url, &u) != URL_OK) abort();
    const char *end = url + strlen(url);
    const char *f[] = { u.pathname, u.search, u.hash };
    size_t l[] = { u.pathname_len, u.search_len, u.hash_len };
    for (int i = 0; i < 3; ++i)
        if (f[i] < url || f[i] + l[i] > end) abort();
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 2) return 0;
    size_t fl = data[0] % (ANC_MAX_FRAGMENT + 8);
    if (fl > size - 1) fl = size - 1;
    char *frag = (char *)malloc(fl + 1);
    if (frag == NULL) return 0;
    memcpy(frag, data + 1, fl);
    frag[fl] = '\0';
    const char *html = (const char *)data + 1 + fl;
    size_t hl = size - 1 - fl;

    check_decode(frag);
    if (strlen(frag) < ANC_MAX_FRAGMENT) check_location(frag);

    hp_document *doc = NULL;
    dom_index *idx = NULL;
    if (hp_parse(html, hl, NULL, &doc) == HP_OK && dom_build(doc, &idx) == DOM_OK) {
        dom_node_id t = DOM_NODE_NONE;
        anc_kind k = anc_resolve(idx, frag, &t);
        if (k == ANC_ELEMENT) {
            if (!dom_is_connected(idx, t)) abort();
            if (dom_get_attribute(idx, t, "id", NULL) == NULL
                && dom_get_attribute(idx, t, "name", NULL) == NULL) abort();
            size_t cap = (size_t)(data[0] % 64) + 1;
            dom_node_id *h = (dom_node_id *)calloc(cap, sizeof *h);
            if (h != NULL) {
                size_t nsub = 0, n = anc_collect(idx, t, h, cap, &nsub);
                if (n == 0 || n > cap || nsub > n || nsub == 0 || h[0] != t) abort();
                for (size_t i = 0; i < n; ++i)
                    for (size_t j = i + 1; j < n; ++j)
                        if (h[i] == h[j]) abort();
                free(h);
            }
        } else if (k != ANC_NONE && k != ANC_TOP) {
            abort();
        }
    }
    dom_free(idx);
    hp_document_free(doc);
    free(frag);
    return 0;
}
