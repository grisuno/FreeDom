#ifndef FREEDOM_BROWSER_H
#define FREEDOM_BROWSER_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * browser — pure navigation state for the Freedom GUI.
 *
 * Maintains history, current URL bar, and last rendered page. All I/O
 * (network, disk, sandboxed render) is delegated to the GUI orchestrator;
 * this module is the auditable, testable state machine.
 *
 * See spec/browser.md for the contract.
 */

#define BROWSER_URL_MAX 1024

/* Transient status line (toast): capacity and how long it stays visible. */
#define BROWSER_STATUS_MAX 256
#define BROWSER_STATUS_DURATION_MS 4000u

typedef struct browser_state {
    char **history;
    size_t history_len;
    size_t history_cap;
    size_t history_pos;

    char   url_bar[BROWSER_URL_MAX];
    size_t url_bar_len;
    size_t url_bar_cursor;
    size_t url_bar_anchor;   /* selection anchor; selection = [min(anchor,cursor), max) */

    char  *page_title;
    char  *page_text;
    int    loading_error;

    char     status_msg[BROWSER_STATUS_MAX]; /* transient toast text ("" if none) */
    uint64_t status_expiry_ms;               /* monotonic ms when the toast hides; 0 = none */

    char **exceptions;     /* hostnames allowed with weak TLS */
    size_t exceptions_len;
    size_t exceptions_cap;
} browser_state;

typedef enum browser_status {
    BROWSER_OK = 0,
    BROWSER_ERR_NULL,
    BROWSER_ERR_OOM,
    BROWSER_ERR_INVALID_URL,
    BROWSER_ERR_NO_BACK,
    BROWSER_ERR_NO_FORWARD
} browser_status;

/* Zero-initialise or reset a state. Safe to call on an already-initialised
 * state (frees old history and page buffers). */
browser_status browser_init(browser_state *bs);

/* Release all owned memory. Safe on NULL and zero-initialised. */
void browser_free(browser_state *bs);

/* Navigation actions. browser_navigate does not perform I/O; it validates the
 * URL scheme, updates the URL bar, and records that a load should happen.
 * On BROWSER_OK, the caller must perform the actual load and then call
 * browser_set_page() with the result. */
browser_status browser_navigate(browser_state *bs, const char *url);

/* Move through history. Returns BROWSER_ERR_NO_* if impossible. */
browser_status browser_back(browser_state *bs);
browser_status browser_forward(browser_state *bs);

/* Query helpers. */
int  browser_can_back(const browser_state *bs);
int  browser_can_forward(const browser_state *bs);
const char *browser_current_url(const browser_state *bs);

/* Exception list: hosts explicitly allowed to use weak TLS. */
int  browser_is_exception(const browser_state *bs, const char *host);
browser_status browser_add_exception(browser_state *bs, const char *host);

/* URL bar editing. */
browser_status browser_set_url_bar(browser_state *bs, const char *url);
browser_status browser_commit_url_bar(browser_state *bs);

/* Insert or remove a character at the cursor. */
browser_status browser_url_bar_insert(browser_state *bs, char c);
browser_status browser_url_bar_backspace(browser_state *bs);
browser_status browser_url_bar_delete(browser_state *bs);
browser_status browser_url_bar_move_cursor(browser_state *bs, long delta);
browser_status browser_url_bar_clear(browser_state *bs);

/* Selection (for the omnibar). The selection is the half-open range
 * [min(anchor,cursor), max(anchor,cursor)); it is EMPTY when anchor == cursor. A
 * plain cursor move / insert / typed edit COLLAPSES it (anchor follows cursor);
 * extend keeps the anchor so shift+motion grows the selection. insert / backspace /
 * delete first remove any selection. */

/* Moves the cursor by delta, KEEPING the anchor (shift+Left/Right). Clamped. */
browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta);

/* Sets the cursor to pos (clamped). extend != 0 keeps the anchor (shift+Home/End or
 * shift+click); extend == 0 collapses the selection (plain Home/End/click). */
browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend);

/* Selects the whole field (anchor = 0, cursor = len). For Ctrl+A. */
browser_status browser_url_bar_select_all(browser_state *bs);

/* If a selection exists, writes its start offset and length and returns 1; else 0.
 * Lets the GUI copy/cut the selected text and paint the highlight. NULL-safe. */
int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len);

/* Removes the selected range (if any), placing the cursor at its start; returns 1 if
 * something was removed, else 0. Used by cut and by an edit over a selection. */
int browser_url_bar_delete_selection(browser_state *bs);

/* After a load (success or failure), the GUI reports the result here.
 * error != 0 means failure; title/text may be NULL. */
browser_status browser_set_page(browser_state *bs, const char *title,
                                const char *text, int error);

/* Transient status line (a toast, e.g. "blocked: insecure http link"). msg is
 * copied (truncated to fit) and shown until now_ms reaches the expiry
 * (now_ms + BROWSER_STATUS_DURATION_MS). A NULL or empty msg clears it. now_ms is a
 * caller-supplied monotonic millisecond clock, so this stays pure (no time syscall
 * here, fully testable). */
browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms);

/* The active status text, or NULL when there is none or it has expired at now_ms. */
const char *browser_status_text(const browser_state *bs, uint64_t now_ms);

#endif /* FREEDOM_BROWSER_H */
