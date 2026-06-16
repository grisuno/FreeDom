/*
 * ui_layout — pure layout core (no I/O).
 *
 * Monospace word-wrapping and scroll clamping. Lines are contiguous slices of
 * the source text, so no text is copied. This is the directly testable surface;
 * the Wayland/Cairo orchestrator (gui/ui_render.c) consumes it.
 */

#include "ui.h"

#include <stdlib.h>

static int layout_push(ui_layout *lay, size_t offset, size_t len) {
    if (lay->count == lay->cap) {
        size_t ncap = lay->cap ? lay->cap * 2 : 32;
        ui_line *grown = (ui_line *)realloc(lay->lines, ncap * sizeof *grown);
        if (grown == NULL) return -1;
        lay->lines = grown;
        lay->cap = ncap;
    }
    lay->lines[lay->count].offset = offset;
    lay->lines[lay->count].len = len;
    lay->count++;
    return 0;
}

ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out) {
    if (text == NULL || out == NULL) return UI_ERR_NULL_ARG;

    out->lines = NULL;
    out->count = 0;
    out->cap = 0;

    if (max_cols == 0) max_cols = 1; /* defensive: no zero-width, no infinite loop */

    size_t i = 0;
    while (i < len) {
        size_t line_start = i;
        size_t col = 0;
        long brk = -1; /* absolute index of the last space seen on this line */
        size_t j = i;

        while (j < len && text[j] != '\n' && col < max_cols) {
            if (text[j] == ' ') brk = (long)j;
            /* Advance one whole UTF-8 character so a hard break never splits a
             * multibyte sequence (a split sequence is invalid UTF-8 and the text
             * renderer rejects it). Malformed bytes fall back to a single step. */
            unsigned char c = (unsigned char)text[j];
            size_t clen = 1;
            if (c >= 0xF0 && c <= 0xF4)      clen = 4;
            else if (c >= 0xE0 && c <= 0xEF) clen = 3;
            else if (c >= 0xC2 && c <= 0xDF) clen = 2;
            if (j + clen > len) clen = len - j;
            for (size_t k = 1; k < clen; ++k) {
                if (((unsigned char)text[j + k] & 0xC0) != 0x80) { clen = 1; break; }
            }
            j += clen;
            ++col;
        }

        size_t end;     /* one past the last byte kept on this line */
        size_t next;    /* where the next line starts */

        if (j < len && text[j] == '\n') {
            end = j;
            next = j + 1;            /* consume the newline */
        } else if (j >= len) {
            end = j;
            next = j;                /* end of input */
        } else if (text[j] == ' ') {
            end = j;
            next = j + 1;            /* break exactly at the boundary space */
        } else if (brk >= 0 && (size_t)brk > line_start) {
            end = (size_t)brk;
            next = (size_t)brk + 1;  /* break at the last space, consume it */
        } else {
            end = j;
            next = j;                /* no break point: hard break */
        }

        if (layout_push(out, line_start, end - line_start) != 0) {
            ui_layout_free(out);
            return UI_ERR_OOM;
        }
        i = next;
    }

    return UI_OK;
}

void ui_layout_free(ui_layout *lay) {
    if (lay == NULL) return;
    free(lay->lines);
    lay->lines = NULL;
    lay->count = 0;
    lay->cap = 0;
}

size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines) {
    if (viewport_lines >= total_lines) return 0;
    size_t max_off = total_lines - viewport_lines;
    return (desired > max_off) ? max_off : desired;
}
