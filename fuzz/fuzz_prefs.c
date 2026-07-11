/*
 * libFuzzer target for the prefs codec (Hito 10).
 *
 * The serialized text is sealed on disk, but bookmark titles were born in
 * hostile remote pages and the whole text round-trips through parse/format
 * plus the generated bookmarks page. Arbitrary bytes must never crash, leak
 * or trip UBSan; the caps must hold; every parsed state must re-serialize and
 * re-parse cleanly (fixpoint).
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prefs.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    prefs_state p;
    prefs_init(&p);

    /* Hostile text through the parser (both raw and with the magic line glued
     * on, so the line grammar gets coverage past the magic check). */
    prefs_parse((const char *)data, size, &p);

    char *glued = (char *)malloc(size + 32);
    if (glued != NULL) {
        size_t off = (size_t)snprintf(glued, 32, "freedom-prefs 1\n");
        memcpy(glued + off, data, size);
        prefs_parse(glued, off + size, &p);
        free(glued);
    }

    /* Hostile bytes as a title and as a URL through the entry points. */
    char *s = (char *)malloc(size + 1);
    if (s != NULL) {
        memcpy(s, data, size);
        s[size] = '\0';
        int added = 0;
        prefs_bookmark_toggle(&p, "https://fuzz.test/", s, &added);
        prefs_bookmark_toggle(&p, s, "title", &added);
        prefs_history_add(&p, s);
        char rows[4][64];
        prefs_suggest(&p, s, (char *)rows, sizeof rows[0], 4);
        free(s);
    }

    /* Round-trip fixpoint: format -> parse must always succeed on our own
     * output and the page must always build. */
    char *text = NULL;
    size_t tlen = 0;
    if (prefs_format(&p, &text, &tlen) == PREFS_OK) {
        prefs_state q;
        prefs_init(&q);
        if (prefs_parse(text, tlen, &q) != PREFS_OK) abort();
        if (q.bookmarks_len != p.bookmarks_len) abort();
        if (q.history_len != p.history_len) abort();
        prefs_free(&q);
        free(text);
    }
    char *html = NULL;
    size_t hlen = 0;
    if (prefs_bookmarks_page(&p, &html, &hlen) == PREFS_OK) free(html);

    prefs_free(&p);
    return 0;
}
