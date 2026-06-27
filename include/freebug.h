#ifndef FREEDOM_FREEBUG_H
#define FREEDOM_FREEBUG_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * freebug — a pure, bounded console-log buffer for the developer console.
 *
 * The directly auditable surface of the "Freebug" devtools: it decides what is
 * stored when page JS (or the user's REPL) writes to console.*, how much is kept,
 * and how an overflowing / hostile stream is dropped (fail-closed, never
 * unbounded). Shared by the confined worker (js_dom's native console binding +
 * tab's uncaught-exception capture) and the trusted parent (GUI storage/display).
 *
 * No QuickJS / Cairo / Wayland type, no I/O, no global state, reentrant.
 * See spec/freebug.md for the full contract.
 */

/* Severity of a console entry. Out-of-range integers clamp to FB_LOG. */
typedef enum fb_level {
    FB_LOG   = 0,
    FB_INFO  = 1,
    FB_WARN  = 2,
    FB_ERROR = 3,
    FB_DEBUG = 4
} fb_level;

/* One captured console message. text is owned by the buffer (NUL-terminated). */
typedef struct fb_entry {
    int    level;
    char  *text;
    size_t len; /* bytes in text, excluding the trailing NUL */
} fb_entry;

/* An ordered, bounded list of entries. Zero-initialise with fb_buffer_init. */
typedef struct fb_buffer {
    fb_entry *entries;
    size_t    count;       /* stored entries */
    size_t    cap;         /* allocated slots in entries */
    size_t    total_bytes; /* sum of stored text lengths */
    int       overflow;    /* set once any push was dropped by a cap */
} fb_buffer;

/* Caps (Secure by Default: unbounded is not representable). */
#define FB_MAX_ENTRIES      ((size_t)512)
#define FB_MAX_ENTRY_BYTES  ((size_t)(8u * 1024u))
#define FB_MAX_TOTAL_BYTES  ((size_t)(256u * 1024u))

/* Zero-initialise b (no allocation). */
void fb_buffer_init(fb_buffer *b);

/* Appends text[0..len) at level (clamped to a valid fb_level). Copies the bytes.
 * Returns 1 if stored, 0 if dropped by a cap or on allocation failure / NULL b.
 * A message longer than FB_MAX_ENTRY_BYTES is stored truncated (not dropped). A
 * dropped push raises b->overflow and leaves prior entries intact. */
int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len);

/* Frees every entry's text; resets count/total_bytes/overflow to 0 but KEEPS the
 * entry array allocation for reuse. Safe on NULL / a zeroed struct. */
void fb_buffer_reset(fb_buffer *b);

/* Frees the entries and the array, then re-zeroes b. Idempotent; safe on NULL. */
void fb_buffer_free(fb_buffer *b);

/* Number of stored entries (0 for NULL). */
size_t fb_buffer_count(const fb_buffer *b);

/* The i-th entry, or NULL if out of range / NULL b. */
const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i);

/* A stable lowercase level name ("log"/"info"/"warn"/"error"/"debug"); an
 * out-of-range level clamps to "log". Pure, no allocation. */
const char *fb_level_name(int level);

#endif /* FREEDOM_FREEBUG_H */
