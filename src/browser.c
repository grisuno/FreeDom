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

/* Drops any active transient status. */
static void clear_status(browser_state *bs) {
    bs->status_msg[0] = '\0';
    bs->status_expiry_ms = 0;
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
    if (n == (size_t)-1) return NULL;
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

/* Unicode scalar for a Windows-1252 byte (only meaningful for c >= 0x80). 0xA0..
 * 0xFF map identically to Latin-1; 0x80..0x9F carry the Windows-1252 glyphs; the
 * five undefined positions return 0 (the caller emits '?'). */
static unsigned int cp1252_to_ucs(unsigned char c) {
    static const unsigned short hi[32] = {
        0x20AC, 0x0000, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
        0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0x0000, 0x017D, 0x0000,
        0x0000, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
        0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0x0000, 0x017E, 0x0178
    };
    if (c < 0x80) return c;
    if (c < 0xA0) return hi[c - 0x80];
    return c;
}

/* Encodes a BMP scalar (<= 0xFFFF) as UTF-8 into out (up to 3 bytes); returns the
 * byte count written. */
static size_t utf8_encode(unsigned int cp, char *out) {
    if (cp < 0x80) { out[0] = (char)cp; return 1; }
    if (cp < 0x800) {
        out[0] = (char)(0xC0 | (cp >> 6));
        out[1] = (char)(0x80 | (cp & 0x3F));
        return 2;
    }
    out[0] = (char)(0xE0 | (cp >> 12));
    out[1] = (char)(0x80 | ((cp >> 6) & 0x3F));
    out[2] = (char)(0x80 | (cp & 0x3F));
    return 3;
}

/* Duplicates s as guaranteed well-formed UTF-8. Valid UTF-8 passes through; a
 * byte not part of a valid sequence (overlong, surrogate, out-of-range, lone byte)
 * is reinterpreted as Windows-1252 (a superset of Latin-1) and re-emitted as UTF-8,
 * recovering accents from legacy-encoded pages instead of dropping them to '?'.
 * Remote pages are hostile data: many are served in legacy encodings whose high
 * bytes are invalid UTF-8, and a single invalid byte poisons the text renderer
 * (cairo_show_text rejects invalid UTF-8 and silently stops drawing). Output may be
 * longer than the input (a byte >=0x80 -> up to 3 UTF-8 bytes), so size for 3x. */
static char *utf8_sanitized_dup(const char *s) {
    if (s == NULL) return NULL;
    size_t n = strlen(s);
    if (n == (size_t)-1 || n > (size_t)-1 / 3) return NULL;
    char *d = (char *)malloc(3 * n + 1);
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
            unsigned int cp = cp1252_to_ucs(c);
            if (cp == 0) d[o++] = '?';
            else o += utf8_encode(cp, d + o);
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
    bs->url_bar_anchor = 0;
}

browser_status browser_set_url_bar(browser_state *bs, const char *url) {
    if (bs == NULL || url == NULL) return BROWSER_ERR_NULL;
    size_t n = strlen(url);
    if (n >= BROWSER_URL_MAX) n = BROWSER_URL_MAX - 1;
    memcpy(bs->url_bar, url, n);
    bs->url_bar[n] = '\0';
    bs->url_bar_len = n;
    bs->url_bar_cursor = n;
    bs->url_bar_anchor = n;   /* a freshly set URL has no selection */
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
    clear_status(bs);
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
    clear_status(bs);
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
    clear_status(bs);
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

int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len) {
    if (bs == NULL || bs->url_bar_anchor == bs->url_bar_cursor) return 0;
    size_t a = bs->url_bar_anchor, c = bs->url_bar_cursor;
    size_t s = (a < c) ? a : c, e = (a < c) ? c : a;
    if (e > bs->url_bar_len) e = bs->url_bar_len;   /* defensive clamp */
    if (s >= e) return 0;
    if (start != NULL) *start = s;
    if (len != NULL) *len = e - s;
    return 1;
}

int browser_url_bar_delete_selection(browser_state *bs) {
    size_t s = 0, l = 0;
    if (!browser_url_bar_selection(bs, &s, &l)) return 0;
    memmove(bs->url_bar + s, bs->url_bar + s + l, bs->url_bar_len - (s + l) + 1);
    bs->url_bar_len -= l;
    bs->url_bar_cursor = s;
    bs->url_bar_anchor = s;
    return 1;
}

browser_status browser_url_bar_insert(browser_state *bs, char c) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    browser_url_bar_delete_selection(bs);   /* typing replaces a selection */
    if (bs->url_bar_len + 1 >= BROWSER_URL_MAX) return BROWSER_ERR_OOM;
    if (bs->url_bar_cursor > bs->url_bar_len) bs->url_bar_cursor = bs->url_bar_len;
    memmove(bs->url_bar + bs->url_bar_cursor + 1,
            bs->url_bar + bs->url_bar_cursor,
            bs->url_bar_len - bs->url_bar_cursor + 1);
    bs->url_bar[bs->url_bar_cursor] = c;
    bs->url_bar_len++;
    bs->url_bar_cursor++;
    bs->url_bar_anchor = bs->url_bar_cursor;
    return BROWSER_OK;
}

browser_status browser_url_bar_backspace(browser_state *bs) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    if (browser_url_bar_delete_selection(bs)) return BROWSER_OK;
    if (bs->url_bar_cursor == 0) return BROWSER_OK;
    size_t pos = bs->url_bar_cursor - 1;
    memmove(bs->url_bar + pos,
            bs->url_bar + pos + 1,
            bs->url_bar_len - pos);
    bs->url_bar_len--;
    bs->url_bar_cursor = pos;
    bs->url_bar_anchor = pos;
    return BROWSER_OK;
}

browser_status browser_url_bar_delete(browser_state *bs) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    if (browser_url_bar_delete_selection(bs)) return BROWSER_OK;
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
    bs->url_bar_anchor = bs->url_bar_cursor;   /* plain motion collapses the selection */
    return BROWSER_OK;
}

browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    long pos = (long)bs->url_bar_cursor + delta;
    if (pos < 0) pos = 0;
    if ((size_t)pos > bs->url_bar_len) pos = (long)bs->url_bar_len;
    bs->url_bar_cursor = (size_t)pos;          /* anchor kept: extends the selection */
    return BROWSER_OK;
}

browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    if (pos > bs->url_bar_len) pos = bs->url_bar_len;
    bs->url_bar_cursor = pos;
    if (!extend) bs->url_bar_anchor = pos;
    return BROWSER_OK;
}

browser_status browser_url_bar_select_all(browser_state *bs) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    bs->url_bar_anchor = 0;
    bs->url_bar_cursor = bs->url_bar_len;
    return BROWSER_OK;
}

browser_status browser_url_bar_clear(browser_state *bs) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    bs->url_bar[0] = '\0';
    bs->url_bar_len = 0;
    bs->url_bar_cursor = 0;
    bs->url_bar_anchor = 0;
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

browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms) {
    if (bs == NULL) return BROWSER_ERR_NULL;
    if (msg == NULL || msg[0] == '\0') {
        clear_status(bs);
        return BROWSER_OK;
    }
    size_t n = strlen(msg);
    if (n >= BROWSER_STATUS_MAX) n = BROWSER_STATUS_MAX - 1;
    memcpy(bs->status_msg, msg, n);
    bs->status_msg[n] = '\0';
    bs->status_expiry_ms = now_ms + BROWSER_STATUS_DURATION_MS;
    return BROWSER_OK;
}

const char *browser_status_text(const browser_state *bs, uint64_t now_ms) {
    if (bs == NULL || bs->status_msg[0] == '\0') return NULL;
    if (now_ms >= bs->status_expiry_ms) return NULL;
    return bs->status_msg;
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
