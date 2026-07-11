/*
 * libFuzzer harness for freebug (bounded console-log buffer).
 *
 * console.* output is hostile remote content: a page script can emit arbitrary
 * bytes, enormous single lines, and an unbounded volume. Pushing such a stream
 * into an fb_buffer must never crash, leak or trigger UB, and the caps must hold:
 * count <= FB_MAX_ENTRIES, every entry len <= FB_MAX_ENTRY_BYTES, total <=
 * FB_MAX_TOTAL_BYTES. The invariants are asserted so a containment regression
 * aborts here (not only a memory bug). reset/free exercise the lifetime paths.
 *
 * Build & run: make fuzz-fb   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "freebug.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void check_invariants(const fb_buffer *b) {
    if (fb_buffer_count(b) > FB_MAX_ENTRIES) abort();
    if (b->total_bytes > FB_MAX_TOTAL_BYTES) abort();
    size_t sum = 0;
    for (size_t i = 0; i < fb_buffer_count(b); ++i) {
        const fb_entry *e = fb_buffer_at(b, i);
        if (e == NULL) abort();
        if (e->len > FB_MAX_ENTRY_BYTES) abort();
        if (e->text[e->len] != '\0') abort();             /* always NUL-terminated at len */
        if (strlen(e->text) > e->len) abort();            /* C-string view is a prefix (text may hold embedded NULs) */
        if (e->level < FB_LOG || e->level > FB_DEBUG) abort();
        if (e->file != NULL && strlen(e->file) > FB_MAX_FILE_BYTES) abort(); /* file cap holds */
        sum += e->len;
    }
    if (sum != b->total_bytes) abort();
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    fb_buffer b;
    fb_buffer_init(&b);

    /* Carve the input into (level, length-prefixed text) records and push each.
     * One byte selects the level; one byte gives a chunk length; the chunk feeds
     * push. Run until the bytes are consumed, exercising the caps repeatedly. */
    size_t off = 0;
    int pushes = 0;
    while (off < size && pushes < 100000) {
        int level = (int)((int8_t)data[off++]);        /* may be out of range -> clamped */
        size_t want = 0;
        if (off < size) want = data[off++];            /* 0..255 base */
        if (off < size) want |= ((size_t)data[off++] << 8); /* up to ~64KiB, exceeds entry cap */
        const char *txt = (const char *)(data + off);
        size_t avail = size - off;
        size_t len = (want < avail) ? want : avail;
        /* Alternate between the plain push and the located push (with a file name
         * carved from the same bytes and arbitrary line/col, including negatives). */
        if (pushes & 1) {
            char fbuf[64];
            size_t fl = (len < sizeof fbuf - 1) ? len : sizeof fbuf - 1;
            if (fl != 0) memcpy(fbuf, txt, fl);
            fbuf[fl] = '\0';
            int line = (int)((int8_t)(len & 0xff)) * 7;
            fb_buffer_push_loc(&b, level, txt, len, fbuf, line, -(int)len);
        } else {
            fb_buffer_push(&b, level, txt, len);
        }
        off += len;
        pushes++;

        /* Occasionally reset to exercise array reuse without leaking. */
        if ((pushes & 0x3f) == 0) {
            check_invariants(&b);
            fb_buffer_reset(&b);
            if (b.overflow != 0 || fb_buffer_count(&b) != 0) abort();
        }
    }
    check_invariants(&b);
    fb_buffer_free(&b);
    return 0;
}
