/*
 * browser — pure navigation state for the Freedom GUI.
 *
 * No I/O, no GUI toolkit. See spec/browser.md and include/browser.h.
 */

#define _POSIX_C_SOURCE 200809L

#include "browser.h"

#include <stdlib.h>
#include <string.h>

static void free_page(browser_state *bs) {
    if (bs == NULL) return;
    free(bs->page_title);
    bs->page_title = NULL;
    free(bs->page_text);
    bs->page_text = NULL;
    bs->loading_error = 0;
}

static void free_history(browser_state *bs) {
    if (bs == NULL || bs->history == NULL) return;
    for (size_t i = 0; i < bs->history_len; ++i) free(bs->history[i]);
    free(bs->history);
    bs->history = NULL;
    bs->history_len = 0;
    bs->history_cap = 0;
    bs->history_pos = 0;
}

static void free_exceptions(browser_state *bs) {
    if (bs == NULL || bs->exceptions == NULL) return;
    for (size_t i = 0; i < bs->exceptions_len; ++i) free(bs->exceptions[i]);
    free(bs->exceptions);
    bs->exceptions = NULL;
    bs->exceptions_len = 0;
    bs->exceptions_cap = 0;
}

static int is_https_url(const char *s) {
    return strncmp(s, "https://", 8) == 0;
}

static int is_local_path(const char *s) {
    return s[0] == '/' || (s[0] == '.' && (s[1] == '/' || s[1] == '\0')) ||
           strchr(s, '/') != NULL || strchr(s, '.') != NULL;
}

static int url_is_allowed(const char *url) {
    if (url == NULL || url[0] == '\0') return 0;
    if (strcmp(url, "about:blank") == 0) return 1;
    if (is_https_url(url)) return 1;

    /* Any colon before the first slash means a non-https scheme (http:,
     * javascript:, data:, file:, etc.) — reject it. */
    const char *colon = strchr(url, ':');
    const char *slash = strchr(url, '/');
    if (colon != NULL && (slash == NULL || colon < slash)) return 0;

    return is_local_path(url);
}

static char *xstrdup(const char *s) {
    if (s == NULL) return NULL;
    size_t n = strlen(s);
    char *d = (char *)malloc(n + 1);
    if (d == NULL) return NULL;
    memcpy(d, s, n + 1);
    return d;
}

/* UTF-8 sequence length implied by a lead byte, or 0 for a continuation byte or
 * an invalid lead. */
static size_t utf8_seq_len(unsigned char c) {
    if (c < 0x80) return 1;
    if (c >= 0xC2 && c <= 0xDF) return 2;
    if (c >= 0xE0 && c <= 0xEF) return 3;
    if (c >= 0xF0 && c <= 0xF4) return 4;
    return 0;
}

/* Duplicates s as guaranteed well-formed UTF-8: any byte not part of a valid
 * sequence (overlong, surrogate, out-of-range, lone byte) is replaced with '?'.
 * Remote pages are hostile data: many are served in legacy encodings (Latin-1)
 * whose high bytes are invalid UTF-8, and a single invalid byte poisons the text
 * renderer (cairo_show_text rejects invalid UTF-8 and silently stops drawing).
 * Output is never longer than the input, so malloc(n+1) is sufficient. */
static char *utf8_sanitized_dup(const char *s) {
    if (s == NULL) return NULL;
    size_t n = strlen(s);
    char *d = (char *)malloc(n + 1);
    if (d == NULL) return NULL;

    size_t i = 0, o = 0;
    while (i < n) {
        unsigned char c = (unsigned char)s[i];
        size_t L = utf8_seq_len(c);
        int ok = (L >= 1 && i + L <= n);
        for (size_t k = 1; ok && k < L; ++k) {
            if (((unsigned char)s[i + k] & 0xC0) != 0x80) ok = 0;
        }
        if (ok && L == 3 && c == 0xE0 && (unsigned char)s[i + 1] < 0xA0) ok = 0; /* overlong */
        if (ok && L == 3 && c == 0xED && (unsigned char)s[i + 1] > 0x9F) ok = 0; /* surrogate */
        if (ok && L == 4 && c == 0xF0 && (unsigned char)s[i + 1] < 0x90) ok = 0; /* overlong */
        if (ok && L == 4 && c == 0xF4 && (unsigned char)s[i + 1] > 0x8F) ok = 0; /* > U+10FFFF */
        if (ok) {
            for (size_t k = 0; k < L; ++k) d[o++] = s[i + k];
            i += L;
        } else {
            d[o++] = '?';
            i += 1;
        }
    }
    d[o] = '\0';
    return d;
}

browser_status browser_init(browser_state *bs) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    browser_free(bs);
    memset(bs, 0, sizeof *bs);
    if (browser_set_url_bar(bs, "about:blank") != BROWSER_OK) {
        browser_free(bs);
        return BROWSER_ERR_OOM;
    }
    return BROWSER_OK;
}

void browser_free(browser_state *bs) {
    if (bs == NULL) return;
    free_history(bs);
    free_page(bs);
    free_exceptions(bs);
    bs->url_bar[0] = '\0';
    bs->url_bar_len = 0;
    bs->url_bar_cursor = 0;
}

browser_status browser_set_url_bar(browser_state *bs, const char *url) {
    if (bs == NULL || url == NULL) return BROWSER_ERR_NULL;
    size_t n = strlen(url);
    if (n >= BROWSER_URL_MAX) n = BROWSER_URL_MAX - 1;
    memcpy(bs->url_bar, url, n);
    bs->url_bar[n] = '\0';
    bs->url_bar_len = n;
    bs->url_bar_cursor = n;
    return BROWSER_OK;
}

browser_status browser_commit_url_bar(browser_state *bs) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    return browser_navigate(bs, bs->url_bar);
}

browser_status browser_navigate(browser_state *bs, const char *url) {
    if (bs == NULL || url == NULL) return BROWSER_ERR_NULL;
    if (!url_is_allowed(url)) return BROWSER_ERR_INVALID_URL;

    /* Discard forward history beyond current position. */
    if (bs->history_pos < bs->history_len) {
        for (size_t i = bs->history_pos + 1; i < bs->history_len; ++i) {
            free(bs->history[i]);
        }
        bs->history_len = bs->history_pos + 1;
    }

    /* Grow if needed. */
    if (bs->history_len >= bs->history_cap) {
        size_t new_cap = bs->history_cap ? bs->history_cap * 2 : 8;
        char **nh = (char **)realloc(bs->history, new_cap * sizeof *nh);
        if (nh == NULL) return BROWSER_ERR_OOM;
        bs->history = nh;
        bs->history_cap = new_cap;
    }

    char *copy = xstrdup(url);
    if (copy == NULL) return BROWSER_ERR_OOM;

    bs->history[bs->history_len] = copy;
    bs->history_len++;
    bs->history_pos = bs->history_len - 1;

    browser_set_url_bar(bs, url);
    free_page(bs);
    bs->loading_error = 0;
    return BROWSER_OK;
}

browser_status browser_back(browser_state *bs) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    if (bs->history_pos == 0 || bs->history_len == 0) return BROWSER_ERR_NO_BACK;
    bs->history_pos--;
    const char *url = bs->history[bs->history_pos];
    browser_set_url_bar(bs, url ? url : "");
    free_page(bs);
    bs->loading_error = 0;
    return BROWSER_OK;
}

browser_status browser_forward(browser_state *bs) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    if (bs->history_pos + 1 >= bs->history_len) return BROWSER_ERR_NO_FORWARD;
    bs->history_pos++;
    const char *url = bs->history[bs->history_pos];
    browser_set_url_bar(bs, url ? url : "");
    free_page(bs);
    bs->loading_error = 0;
    return BROWSER_OK;
}

int browser_can_back(const browser_state *bs) {
    return (bs != NULL && bs->history_pos > 0);
}

int browser_can_forward(const browser_state *bs) {
    return (bs != NULL && bs->history_len > 0 && bs->history_pos + 1 < bs->history_len);
}

const char *browser_current_url(const browser_state *bs) {
    if (bs == NULL || bs->history_len == 0) return NULL;
    return bs->history[bs->history_pos];
}

browser_status browser_url_bar_insert(browser_state *bs, char c) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    if (bs->url_bar_len + 1 >= BROWSER_URL_MAX) return BROWSER_ERR_OOM;
    if (bs->url_bar_cursor > bs->url_bar_len) bs->url_bar_cursor = bs->url_bar_len;
    memmove(bs->url_bar + bs->url_bar_cursor + 1,
            bs->url_bar + bs->url_bar_cursor,
            bs->url_bar_len - bs->url_bar_cursor + 1);
    bs->url_bar[bs->url_bar_cursor] = c;
    bs->url_bar_len++;
    bs->url_bar_cursor++;
    return BROWSER_OK;
}

browser_status browser_url_bar_backspace(browser_state *bs) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    if (bs->url_bar_cursor == 0) return BROWSER_OK;
    size_t pos = bs->url_bar_cursor - 1;
    memmove(bs->url_bar + pos,
            bs->url_bar + pos + 1,
            bs->url_bar_len - pos);
    bs->url_bar_len--;
    bs->url_bar_cursor = pos;
    return BROWSER_OK;
}

browser_status browser_url_bar_delete(browser_state *bs) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    if (bs->url_bar_cursor >= bs->url_bar_len) return BROWSER_OK;
    memmove(bs->url_bar + bs->url_bar_cursor,
            bs->url_bar + bs->url_bar_cursor + 1,
            bs->url_bar_len - bs->url_bar_cursor);
    bs->url_bar_len--;
    return BROWSER_OK;
}

browser_status browser_url_bar_move_cursor(browser_state *bs, long delta) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    long pos = (long)bs->url_bar_cursor + delta;
    if (pos < 0) pos = 0;
    if ((size_t)pos > bs->url_bar_len) pos = (long)bs->url_bar_len;
    bs->url_bar_cursor = (size_t)pos;
    return BROWSER_OK;
}

browser_status browser_url_bar_clear(browser_state *bs) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    bs->url_bar[0] = '\0';
    bs->url_bar_len = 0;
    bs->url_bar_cursor = 0;
    return BROWSER_OK;
}

browser_status browser_set_page(browser_state *bs, const char *title,
                                const char *text, int error) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    free_page(bs);
    bs->loading_error = error;
    if (error) {
        const char *msg = (text != NULL) ? text : "Failed to load page.";
        bs->page_text = utf8_sanitized_dup(msg);
        bs->page_title = xstrdup("Error");
        return (bs->page_text != NULL && bs->page_title != NULL) ? BROWSER_OK : BROWSER_ERR_OOM;
    }
    /* Page title and text come from a hostile remote document: store them as
     * well-formed UTF-8 so the renderer can never be poisoned by bad bytes. */
    bs->page_title = utf8_sanitized_dup(title);
    bs->page_text = utf8_sanitized_dup(text);
    if ((title != NULL && bs->page_title == NULL) || (text != NULL && bs->page_text == NULL)) {
        free_page(bs);
        return BROWSER_ERR_OOM;
    }
    return BROWSER_OK;
}

/* --- exceptions (user override for weak TLS) --- */

static int host_equal(const char *a, const char *b) {
    while (*a && *b) {
        int ca = (unsigned char)*a, cb = (unsigned char)*b;
        if (ca >= 'A' && ca <= 'Z') ca += 'a' - 'A';
        if (cb >= 'A' && cb <= 'Z') cb += 'a' - 'A';
        if (ca != cb) return 0;
        ++a; ++b;
    }
    return *a == '\0' && *b == '\0';
}

int browser_is_exception(const browser_state *bs, const char *host) {
    if (bs == NULL || host == NULL) return 0;
    for (size_t i = 0; i < bs->exceptions_len; ++i) {
        if (bs->exceptions[i] != NULL && host_equal(bs->exceptions[i], host)) return 1;
    }
    return 0;
}

browser_status browser_add_exception(browser_state *bs, const char *host) {
    if (bs == NULL || host == NULL) return BROWSER_ERR_NULL;
    if (browser_is_exception(bs, host)) return BROWSER_OK;

    if (bs->exceptions_len >= bs->exceptions_cap) {
        size_t new_cap = bs->exceptions_cap ? bs->exceptions_cap * 2 : 4;
        char **ne = (char **)realloc(bs->exceptions, new_cap * sizeof *ne);
        if (ne == NULL) return BROWSER_ERR_OOM;
        bs->exceptions = ne;
        bs->exceptions_cap = new_cap;
    }

    char *copy = xstrdup(host);
    if (copy == NULL) return BROWSER_ERR_OOM;
    bs->exceptions[bs->exceptions_len++] = copy;
    return BROWSER_OK;
}
