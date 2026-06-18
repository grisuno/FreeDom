#ifndef FREEDOM_TEXTFIELD_H
#define FREEDOM_TEXTFIELD_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * textfield — a pure, single-line editable text buffer with a cursor.
 *
 * No I/O, no global state, no dynamic allocation: a fixed-capacity buffer the GUI
 * embeds in its own state and drives from the keyboard. The same primitive backs
 * the configurable User-Agent field and the form text inputs, so the edit
 * mechanics live in one tested place. Hostile/user bytes are inserted verbatim
 * (the caller sanitises to valid UTF-8 when painting). Fails closed: an operation
 * that would not fit is rejected whole, never a partial out-of-bounds write.
 *
 * See spec/textfield.md for the full contract.
 */

#define TF_CAP 1024u /* fixed buffer capacity, including the trailing NUL */

typedef struct tf_field {
    char   buf[TF_CAP]; /* content, always NUL-terminated at [len] */
    size_t len;         /* bytes used, excluding the NUL; len < TF_CAP */
    size_t cursor;      /* byte insertion position, 0..len */
} tf_field;

typedef enum tf_status {
    TF_OK = 0,
    TF_ERR_NULL_ARG, /* a required pointer was NULL */
    TF_ERR_FULL      /* the operation does not fit (fails closed, no partial write) */
} tf_status;

/* Resets the field to empty with the cursor at 0. NULL-safe. */
void tf_init(tf_field *f);

/* Replaces the whole content and places the cursor at the end. s == NULL =>
 * TF_ERR_NULL_ARG. strlen(s) >= TF_CAP => TF_ERR_FULL and the field is unchanged. */
tf_status tf_set(tf_field *f, const char *s);

/* Empties the field (cursor at 0). NULL-safe. */
void tf_clear(tf_field *f);

/* Inserts one byte at the cursor, shifting the tail right; the cursor advances by
 * one. Returns TF_ERR_FULL (field unchanged) when the buffer is full, or
 * TF_ERR_NULL_ARG when f is NULL. */
tf_status tf_insert(tf_field *f, char c);

/* Deletes the byte before the cursor (no-op at the start). NULL-safe. */
void tf_backspace(tf_field *f);

/* Deletes the byte at the cursor (no-op at the end). NULL-safe. */
void tf_delete(tf_field *f);

/* Moves the cursor by delta, saturating to [0, len]. NULL-safe. */
void tf_move(tf_field *f, long delta);

/* Moves the cursor to the start / end. NULL-safe. */
void tf_home(tf_field *f);
void tf_end(tf_field *f);

/* Read accessors. NULL-safe (return ""/0). */
const char *tf_text(const tf_field *f);
size_t      tf_len(const tf_field *f);
size_t      tf_cursor(const tf_field *f);

#endif /* FREEDOM_TEXTFIELD_H */
