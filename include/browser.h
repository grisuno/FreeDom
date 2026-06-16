#ifndef FREEDOM_BROWSER_H
#define FREEDOM_BROWSER_H

#include <stddef.h>

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

typedef struct browser_state {
    char **history;
    size_t history_len;
    size_t history_cap;
    size_t history_pos;

    char   url_bar[BROWSER_URL_MAX];
    size_t url_bar_len;
    size_t url_bar_cursor;

    char  *page_title;
    char  *page_text;
    int    loading_error;

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

/* After a load (success or failure), the GUI reports the result here.
 * error != 0 means failure; title/text may be NULL. */
browser_status browser_set_page(browser_state *bs, const char *title,
                                const char *text, int error);

#endif /* FREEDOM_BROWSER_H */
