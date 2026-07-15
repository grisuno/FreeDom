/*
 * freebug — implementation of the pure, bounded console-log buffer.
 *
 * Fail-closed at every cap: a push that would exceed FB_MAX_ENTRIES or
 * FB_MAX_TOTAL_BYTES is dropped whole (overflow flag raised, prior entries kept);
 * a single message over FB_MAX_ENTRY_BYTES is stored truncated. No I/O, no global
 * state. See spec/freebug.md.
 */

#include "freebug.h"

#include <stdlib.h>
#include <string.h>

void fb_buffer_init(fb_buffer *b) {
    if (b != NULL) memset(b, 0, sizeof *b);
}

int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len) {
    return fb_buffer_push_loc(b, level, text, len, NULL, 0, 0);
}

int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len,
                       const char *file, int line, int col) {
    if (b == NULL) return 0;

    if (b->count >= FB_MAX_ENTRIES) { b->overflow = 1; return 0; }

    /* A NULL source is an empty message (a bare console.log() still counts). */
    size_t store = (text == NULL) ? 0 : len;
    if (store > FB_MAX_ENTRY_BYTES) store = FB_MAX_ENTRY_BYTES;

    /* total_bytes is an invariant <= FB_MAX_TOTAL_BYTES, so the subtraction is
     * non-negative and cannot wrap; an over-budget push is dropped whole. */
    if (store > FB_MAX_TOTAL_BYTES - b->total_bytes) { b->overflow = 1; return 0; }

    if (b->count == b->cap) {
        size_t ncap = b->cap ? b->cap * 2 : 16;
        if (ncap > FB_MAX_ENTRIES) ncap = FB_MAX_ENTRIES;
        fb_entry *grown = (fb_entry *)realloc(b->entries, ncap * sizeof *grown);
        if (grown == NULL) return 0; /* allocation failure: state unchanged */
        b->entries = grown;
        b->cap = ncap;
    }

    if (store == (size_t)-1) return 0;
    char *copy = (char *)malloc(store + 1);
    if (copy == NULL) return 0;
    if (store != 0) memcpy(copy, text, store);
    copy[store] = '\0';

    /* Optional source name; failure to copy it degrades to "no location", never
     * fails the push (the message itself must still be recorded). */
    char *fcopy = NULL;
    if (file != NULL) {
        size_t flen = strlen(file);
        if (flen > FB_MAX_FILE_BYTES) flen = FB_MAX_FILE_BYTES;
        if (flen == (size_t)-1) flen = 0;
        fcopy = (char *)malloc(flen + 1);
        if (fcopy != NULL) {
            if (flen != 0) memcpy(fcopy, file, flen);
            fcopy[flen] = '\0';
        }
    }

    int lv = (level < FB_LOG || level > FB_DEBUG) ? FB_LOG : level;
    b->entries[b->count].level = lv;
    b->entries[b->count].text  = copy;
    b->entries[b->count].len   = store;
    b->entries[b->count].file  = fcopy;
    b->entries[b->count].line  = (line > 0) ? line : 0;
    b->entries[b->count].col   = (col  > 0) ? col  : 0;
    b->count++;
    b->total_bytes += store;
    return 1;
}

void fb_buffer_reset(fb_buffer *b) {
    if (b == NULL) return;
    for (size_t i = 0; i < b->count; ++i) {
        free(b->entries[i].text);
        free(b->entries[i].file);
        b->entries[i].text = NULL;
        b->entries[i].file = NULL;
    }
    b->count = 0;
    b->total_bytes = 0;
    b->overflow = 0;
}

void fb_buffer_free(fb_buffer *b) {
    if (b == NULL) return;
    for (size_t i = 0; i < b->count; ++i) {
        free(b->entries[i].text);
        free(b->entries[i].file);
    }
    free(b->entries);
    memset(b, 0, sizeof *b);
}

size_t fb_buffer_count(const fb_buffer *b) {
    return (b != NULL) ? b->count : 0;
}

const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i) {
    if (b == NULL || i >= b->count) return NULL;
    return &b->entries[i];
}

const char *fb_level_name(int level) {
    switch (level) {
        case FB_INFO:  return "info";
        case FB_WARN:  return "warn";
        case FB_ERROR: return "error";
        case FB_DEBUG: return "debug";
        case FB_LOG:
        default:       return "log";
    }
}
