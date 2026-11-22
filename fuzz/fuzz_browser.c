/*
 * Fuzz target for browser history (spec/browser.md 3b/3c): a hostile sequence of
 * navigate / back / forward / pushState / replaceState / commit / abort. URLs come
 * from the input (pushState URLs are page-controlled). Oracle: Stop restores EXACTLY
 * the history that was committed before the pending navigation, and the structural
 * invariants (pos < len, URL bar terminated) hold after every step.
 */
#define _POSIX_C_SOURCE 200809L
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "browser.h"

#define SNAP_MAX 512

typedef struct snap {
    size_t n, pos;
    char  *url[SNAP_MAX];
    int    doc[SNAP_MAX];
} snap;

static void snap_free(snap *s) {
    for (size_t i = 0; i < s->n; ++i) free(s->url[i]);
    s->n = 0;
}

static void snap_take(snap *s, const browser_state *bs) {
    snap_free(s);
    for (size_t i = 0; i < bs->history_len && i < SNAP_MAX; ++i) {
        s->url[i] = strdup(bs->history[i]);
        if (s->url[i] == NULL) abort();
        s->doc[i] = bs->history_doc[i];
        s->n = i + 1;
    }
    s->pos = bs->history_pos;
}

static void snap_check(const snap *s, const browser_state *bs) {
    if (bs->history_len != s->n || bs->history_pos != s->pos) abort();
    for (size_t i = 0; i < s->n; ++i) {
        if (strcmp(bs->history[i], s->url[i]) != 0 || bs->history_doc[i] != s->doc[i]) abort();
    }
}

static void invariants(const browser_state *bs) {
    if (bs->history_len > 0 && bs->history_pos >= bs->history_len) abort();
    if (bs->url_bar_len >= BROWSER_URL_MAX || bs->url_bar[bs->url_bar_len] != '\0') abort();
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    browser_state bs;
    memset(&bs, 0, sizeof bs);
    if (browser_init(&bs) != BROWSER_OK) return 0;
    snap committed;
    memset(&committed, 0, sizeof committed);
    char url[96];
    size_t i = 0, steps = 0;
    while (i < size && steps < 400 && bs.history_len < SNAP_MAX - 2) {
        uint8_t op = data[i++] % 8;
        size_t ul = (i < size) ? data[i++] % 24 : 0;
        if (ul > size - i) ul = size - i;
        /* A URL the history accepts most of the time, with hostile bytes inside. */
        size_t k = (size_t)snprintf(url, sizeof url, (op & 1) ? "/p" : "https://h/");
        memcpy(url + k, data + i, ul);
        url[k + ul] = '\0';
        i += ul;
        switch (op) {
            case 0: case 1: (void)browser_navigate(&bs, url); break;
            case 2: (void)browser_back(&bs); break;
            case 3: (void)browser_forward(&bs); break;
            case 4: (void)browser_push_state(&bs, url); break;
            case 5: (void)browser_replace_state(&bs, url); break;
            case 6: browser_commit_pending(&bs); break;
            case 7:
                if (browser_has_pending(&bs)) {
                    if (browser_abort_pending(&bs) != 1) abort();
                    snap_check(&committed, &bs);
                } else if (browser_abort_pending(&bs) != 0) {
                    abort();
                }
                break;
        }
        invariants(&bs);
        if (!browser_has_pending(&bs)) snap_take(&committed, &bs);
        steps++;
    }
    snap_free(&committed);
    browser_free(&bs);
    return 0;
}
