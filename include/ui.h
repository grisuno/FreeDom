#ifndef FREEDOM_UI_H
#define FREEDOM_UI_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * ui — Wayland + Cairo presentation. Wayland only, never X11.
 *
 * The verifiable logic (text layout, scrolling) lives in pure, I/O-free
 * functions; the Wayland/Cairo orchestrator only wires them to a real display.
 *
 * See spec/ui.md for the full contract.
 */

typedef enum ui_status {
    UI_OK = 0,
    UI_ERR_NULL_ARG,
    UI_ERR_OOM,
    UI_ERR_DISPLAY,   /* could not connect to a Wayland display */
    UI_ERR_INTERNAL
} ui_status;

/* A laid-out line is a contiguous slice [offset, offset+len) of the source
 * text (no copy): render with text + offset over len bytes. */
typedef struct ui_line {
    size_t offset;
    size_t len;
} ui_line;

typedef struct ui_layout {
    ui_line *lines;
    size_t   count;
    size_t   cap;
} ui_layout;

/* --- Pure core (no I/O): the primary test surface. --- */

/* Word-wraps text into lines of at most max_cols columns (monospace model).
 * Breaks at the last fitting space (the break space is consumed), hard-breaks
 * words longer than max_cols, and treats '\n' as a forced break. max_cols == 0
 * is treated as 1. len == 0 yields zero lines.
 * text == NULL or out == NULL => UI_ERR_NULL_ARG. On UI_OK, *out is owned by
 * the caller and released with ui_layout_free. */
ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out);

/* Idempotent; safe on a zero-initialised struct and safe to call twice. */
void ui_layout_free(ui_layout *lay);

/* Clamps desired to [0, max(0, total_lines - viewport_lines)]. */
size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines);

/* --- Orchestrator (I/O; tested visually on a real display). --- */

/* Opens a Wayland window titled `title` and renders text as a scrollable,
 * word-wrapped monospace view. Blocks until the window is closed. Requires a
 * Wayland display; returns UI_ERR_DISPLAY if none is available. */
ui_status ui_run_text_view(const char *title, const char *text, size_t text_len);

/* Opens a minimal browser window with Back/Forward/URL bar and renders pages
 * via the secure tab pipeline. If start_url is non-NULL it is loaded on open.
 * Blocks until the window is closed. Visual-only (no headless test). */
ui_status ui_run_browser(const char *start_url);

#endif /* FREEDOM_UI_H */
