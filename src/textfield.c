/*
 * textfield — implementation of the pure single-line editable buffer.
 *
 * Fixed-capacity, no allocation, no I/O. Every mutator keeps the invariant
 * cursor <= len < TF_CAP and buf[len] == '\0'. An operation that would overflow
 * the buffer is rejected whole (fail closed), never applied partially.
 */

#include "textfield.h"

#include <string.h>

void tf_init(tf_field *f) {
    if (f == NULL) return;
    f->buf[0] = '\0';
    f->len = 0;
    f->cursor = 0;
}

void tf_clear(tf_field *f) {
    tf_init(f);
}

tf_status tf_set(tf_field *f, const char *s) {
    if (f == NULL || s == NULL) return TF_ERR_NULL_ARG;
    size_t n = strlen(s);
    if (n >= TF_CAP) return TF_ERR_FULL; /* leave the field intact */
    memcpy(f->buf, s, n);
    f->buf[n] = '\0';
    f->len = n;
    f->cursor = n;
    return TF_OK;
}

tf_status tf_insert(tf_field *f, char c) {
    if (f == NULL) return TF_ERR_NULL_ARG;
    if (f->len + 1 >= TF_CAP) return TF_ERR_FULL; /* no room beside the NUL */
    /* Shift the tail [cursor, len) one byte right, then drop c in. */
    memmove(f->buf + f->cursor + 1, f->buf + f->cursor, f->len - f->cursor);
    f->buf[f->cursor] = c;
    f->len += 1;
    f->cursor += 1;
    f->buf[f->len] = '\0';
    return TF_OK;
}

void tf_backspace(tf_field *f) {
    if (f == NULL || f->cursor == 0) return;
    memmove(f->buf + f->cursor - 1, f->buf + f->cursor, f->len - f->cursor);
    f->len -= 1;
    f->cursor -= 1;
    f->buf[f->len] = '\0';
}

void tf_delete(tf_field *f) {
    if (f == NULL || f->cursor >= f->len) return;
    memmove(f->buf + f->cursor, f->buf + f->cursor + 1, f->len - f->cursor - 1);
    f->len -= 1;
    f->buf[f->len] = '\0';
}

void tf_move(tf_field *f, long delta) {
    if (f == NULL) return;
    if (delta < 0) {
        size_t back = (size_t)(-delta);
        f->cursor = (back >= f->cursor) ? 0 : f->cursor - back;
    } else {
        size_t fwd = (size_t)delta;
        f->cursor = (fwd >= f->len - f->cursor) ? f->len : f->cursor + fwd;
    }
}

void tf_home(tf_field *f) {
    if (f == NULL) return;
    f->cursor = 0;
}

void tf_end(tf_field *f) {
    if (f == NULL) return;
    f->cursor = f->len;
}

const char *tf_text(const tf_field *f) {
    return (f != NULL) ? f->buf : "";
}

size_t tf_len(const tf_field *f) {
    return (f != NULL) ? f->len : 0;
}

size_t tf_cursor(const tf_field *f) {
    return (f != NULL) ? f->cursor : 0;
}
