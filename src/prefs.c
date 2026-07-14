/*
 * prefs — implementation: pure user-profile model (Hito 10).
 *
 * Preferences, bookmarks and persistent history plus the versioned text codec.
 * No I/O, no clock, no network: fully deterministic for tests and fuzzing.
 * Fail closed: unknown magic/version rejects the whole text; URLs with control
 * bytes are not representable; hostile titles are cleaned on entry and escaped
 * in the generated bookmarks page. See spec/prefs.md.
 */

#define _POSIX_C_SOURCE 200809L  /* strdup */

#include "prefs.h"
#include "zoom.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PREFS_MAGIC "freedom-prefs"

/* --- validation / cleaning ------------------------------------------------ */

/* A representable URL: 1..PREFS_MAX_URL-1 bytes, no control bytes, no DEL.
 * Space is allowed (local paths may carry it; fields are tab-separated). */
static int url_valid(const char *url) {
    if (url == NULL || url[0] == '\0') return 0;
    size_t n = 0;
    for (const unsigned char *c = (const unsigned char *)url; *c != '\0'; ++c, ++n) {
        if (*c < 0x20u || *c == 0x7fu) return 0;
        if (n + 1 >= PREFS_MAX_URL) return 0;
    }
    return 1;
}

/* Copies src into a fresh buffer, mapping control bytes/DEL to ' ' and
 * truncating to PREFS_MAX_TITLE bytes on a UTF-8 sequence boundary. A NULL
 * src yields "". Returns NULL only on OOM. */
static char *title_clean(const char *src) {
    if (src == NULL) src = "";
    char *dst = (char *)malloc(PREFS_MAX_TITLE + 1);
    if (dst == NULL) return NULL;
    size_t n = 0;
    for (const unsigned char *c = (const unsigned char *)src;
         *c != '\0' && n < PREFS_MAX_TITLE; ++c) {
        dst[n++] = (*c < 0x20u || *c == 0x7fu) ? ' ' : (char)*c;
    }
    /* Trim a trailing incomplete UTF-8 sequence left by byte truncation. */
    size_t back = 0;
    while (back < 3 && back < n &&
           ((unsigned char)dst[n - 1 - back] & 0xC0u) == 0x80u) {
        ++back;
    }
    if (back < n) {
        unsigned char lead = (unsigned char)dst[n - 1 - back];
        size_t need = (lead >= 0xF0u) ? 4 : (lead >= 0xE0u) ? 3
                    : (lead >= 0xC0u) ? 2 : 1;
        if (need > back + 1) n -= back + 1;  /* incomplete: drop the sequence */
    }
    dst[n] = '\0';
    return dst;
}

/* --- lifecycle ------------------------------------------------------------- */

void prefs_init(prefs_state *p) {
    if (p == NULL) return;
    memset(p, 0, sizeof *p);
    p->js_mode = 1;           /* JSP_ALLOWLIST: Secure by Default */
    p->zoom_pct = zm_reset(); /* 100% */
    p->remember_history = 1;
}

void prefs_free(prefs_state *p) {
    if (p == NULL) return;
    for (size_t i = 0; i < p->bookmarks_len; ++i) {
        free(p->bookmarks[i].url);
        free(p->bookmarks[i].title);
    }
    free(p->bookmarks);
    for (size_t i = 0; i < p->history_len; ++i) free(p->history[i]);
    free(p->history);
    p->bookmarks = NULL; p->bookmarks_len = 0;
    p->history = NULL;   p->history_len = 0;
}

/* --- list plumbing ---------------------------------------------------------- */

/* Appends a cleaned bookmark. Duplicate URLs are skipped (PREFS_OK). Used by
 * the toggle's add path and by the parser. */
static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title) {
    if (prefs_bookmark_index(p, url) >= 0) return PREFS_OK;
    if (p->bookmarks_len >= PREFS_MAX_BOOKMARKS) return PREFS_ERR_FULL;
    prefs_entry *grown = (prefs_entry *)realloc(
        p->bookmarks, (p->bookmarks_len + 1) * sizeof *grown);
    if (grown == NULL) return PREFS_ERR_OOM;
    p->bookmarks = grown;
    char *u = strdup(url);
    char *t = title_clean(title);
    if (u == NULL || t == NULL) { free(u); free(t); return PREFS_ERR_OOM; }
    p->bookmarks[p->bookmarks_len].url = u;
    p->bookmarks[p->bookmarks_len].title = t;
    p->bookmarks_len++;
    return PREFS_OK;
}

/* Appends a history entry at the BACK preserving document order (parser path;
 * the API path inserts at the front). Duplicates and overflow are skipped. */
static prefs_status history_push_back(prefs_state *p, const char *url) {
    if (p->history_len >= PREFS_MAX_HISTORY) return PREFS_OK;
    for (size_t i = 0; i < p->history_len; ++i)
        if (strcmp(p->history[i], url) == 0) return PREFS_OK;
    char **grown = (char **)realloc(p->history,
                                    (p->history_len + 1) * sizeof *grown);
    if (grown == NULL) return PREFS_ERR_OOM;
    p->history = grown;
    char *u = strdup(url);
    if (u == NULL) return PREFS_ERR_OOM;
    p->history[p->history_len++] = u;
    return PREFS_OK;
}

/* --- public list operations --------------------------------------------------- */

int prefs_bookmark_index(const prefs_state *p, const char *url) {
    if (p == NULL || url == NULL) return -1;
    for (size_t i = 0; i < p->bookmarks_len; ++i)
        if (strcmp(p->bookmarks[i].url, url) == 0) return (int)i;
    return -1;
}

prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,
                                   const char *title, int *added) {
    if (p == NULL || url == NULL) return PREFS_ERR_NULL_ARG;
    if (!url_valid(url)) return PREFS_ERR_INVALID;
    int idx = prefs_bookmark_index(p, url);
    if (idx >= 0) {
        free(p->bookmarks[idx].url);
        free(p->bookmarks[idx].title);
        memmove(&p->bookmarks[idx], &p->bookmarks[idx + 1],
                (p->bookmarks_len - (size_t)idx - 1) * sizeof p->bookmarks[0]);
        p->bookmarks_len--;
        if (added != NULL) *added = 0;
        return PREFS_OK;
    }
    if (p->bookmarks_len >= PREFS_MAX_BOOKMARKS) return PREFS_ERR_FULL;
    prefs_status st = bookmark_push(p, url, title);
    if (st == PREFS_OK && added != NULL) *added = 1;
    return st;
}

prefs_status prefs_history_add(prefs_state *p, const char *url) {
    if (p == NULL || url == NULL) return PREFS_ERR_NULL_ARG;
    if (!url_valid(url)) return PREFS_ERR_INVALID;
    if (p->history_len > 0 && strcmp(p->history[0], url) == 0) return PREFS_OK;
    for (size_t i = 1; i < p->history_len; ++i) {
        if (strcmp(p->history[i], url) == 0) {  /* move to front */
            char *hit = p->history[i];
            memmove(&p->history[1], &p->history[0], i * sizeof p->history[0]);
            p->history[0] = hit;
            return PREFS_OK;
        }
    }
    char *u = strdup(url);
    if (u == NULL) return PREFS_ERR_OOM;
    if (p->history_len >= PREFS_MAX_HISTORY) {
        free(p->history[p->history_len - 1]);  /* evict the oldest */
        p->history_len--;
    }
    char **grown = (char **)realloc(p->history,
                                    (p->history_len + 1) * sizeof *grown);
    if (grown == NULL) { free(u); return PREFS_ERR_OOM; }
    p->history = grown;
    memmove(&p->history[1], &p->history[0],
            p->history_len * sizeof p->history[0]);
    p->history[0] = u;
    p->history_len++;
    return PREFS_OK;
}

/* --- serialization ---------------------------------------------------------------- */

prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len) {
    if (p == NULL || out == NULL || out_len == NULL) return PREFS_ERR_NULL_ARG;
    *out = NULL;
    *out_len = 0;

    size_t cap = 256;  /* header + scalar keys */
    for (size_t i = 0; i < p->bookmarks_len; ++i)
        cap += 4 + strlen(p->bookmarks[i].url) + strlen(p->bookmarks[i].title);
    for (size_t i = 0; i < p->history_len; ++i)
        cap += 3 + strlen(p->history[i]);
    if (cap > PREFS_MAX_TEXT) return PREFS_ERR_FORMAT;  /* unreachable with the caps */

    char *buf = (char *)malloc(cap);
    if (buf == NULL) return PREFS_ERR_OOM;
    size_t n = (size_t)snprintf(buf, cap,
        PREFS_MAGIC " %u\n"
        "theme=%d\nforce=%d\nimages=%d\ncss=%d\nreader=%d\njs=%d\n"
        "tor=%d\ni2p=%d\ntorify=%d\nzoom=%d\nremhist=%d\n",
        PREFS_VERSION,
        p->theme_mode, p->force_theme, p->images, p->css, p->reader, p->js_mode,
        p->tor, p->i2p, p->torify, p->zoom_pct, p->remember_history);
    for (size_t i = 0; i < p->bookmarks_len; ++i) {
        size_t space = cap - n;
        if (space == 0) break;
        int r = snprintf(buf + n, space, "b\t%s\t%s\n",
                         p->bookmarks[i].url, p->bookmarks[i].title);
        if (r < 0 || (size_t)r >= space) { n = cap; break; }
        n += (size_t)r;
    }
    for (size_t i = 0; i < p->history_len; ++i) {
        size_t space = cap - n;
        if (space == 0) break;
        int r = snprintf(buf + n, space, "h\t%s\n", p->history[i]);
        if (r < 0 || (size_t)r >= space) { n = cap; break; }
        n += (size_t)r;
    }
    *out = buf;
    *out_len = n;
    return PREFS_OK;
}

/* Normalises one key=value pair into out (clamps / safe defaults). */
static void apply_kv(prefs_state *out, const char *key, long val) {
    int b = (val != 0);
    if      (strcmp(key, "theme") == 0)   out->theme_mode = (val >= 0 && val <= 2) ? (int)val : 0;
    else if (strcmp(key, "js") == 0)      out->js_mode = (val >= 0 && val <= 2) ? (int)val : 1;
    else if (strcmp(key, "zoom") == 0)    out->zoom_pct = zm_clamp((int)val);
    else if (strcmp(key, "force") == 0)   out->force_theme = b;
    else if (strcmp(key, "images") == 0)  out->images = b;
    else if (strcmp(key, "css") == 0)     out->css = b;
    else if (strcmp(key, "reader") == 0)  out->reader = b;
    else if (strcmp(key, "tor") == 0)     out->tor = b;
    else if (strcmp(key, "i2p") == 0)     out->i2p = b;
    else if (strcmp(key, "torify") == 0)  out->torify = b;
    else if (strcmp(key, "remhist") == 0) out->remember_history = b;
    /* unknown key: ignored (forward compatibility) */
}

prefs_status prefs_parse(const char *text, size_t len, prefs_state *out) {
    if (text == NULL || out == NULL) return PREFS_ERR_NULL_ARG;
    prefs_free(out);
    prefs_init(out);
    if (len > PREFS_MAX_TEXT) return PREFS_ERR_FORMAT;

    const char *end = text + len;
    const char *line = text;

    /* Magic line: "freedom-prefs <version>". */
    const char *nl = memchr(line, '\n', (size_t)(end - line));
    size_t ll = (nl != NULL) ? (size_t)(nl - line) : (size_t)(end - line);
    char head[64];
    if (ll == 0 || ll >= sizeof head) return PREFS_ERR_FORMAT;
    memcpy(head, line, ll);
    head[ll] = '\0';
    unsigned ver = 0;
    if (sscanf(head, PREFS_MAGIC " %u", &ver) != 1 || ver != PREFS_VERSION)
        return PREFS_ERR_FORMAT;
    line = (nl != NULL) ? nl + 1 : end;

    while (line < end) {
        nl = memchr(line, '\n', (size_t)(end - line));
        ll = (nl != NULL) ? (size_t)(nl - line) : (size_t)(end - line);
        char lbuf[PREFS_MAX_URL + PREFS_MAX_TITLE + 8];
        if (ll > 0 && ll < sizeof lbuf) {
            memcpy(lbuf, line, ll);
            lbuf[ll] = '\0';
            if (lbuf[0] == 'b' && lbuf[1] == '\t') {
                char *url = lbuf + 2;
                char *tab = strchr(url, '\t');
                if (tab != NULL) {
                    *tab = '\0';
                    if (url_valid(url)) {
                        prefs_status st = bookmark_push(out, url, tab + 1);
                        if (st == PREFS_ERR_OOM) return PREFS_ERR_OOM;
                    }
                }
            } else if (lbuf[0] == 'h' && lbuf[1] == '\t') {
                if (url_valid(lbuf + 2)) {
                    prefs_status st = history_push_back(out, lbuf + 2);
                    if (st == PREFS_ERR_OOM) return PREFS_ERR_OOM;
                }
            } else {
                char *eq = strchr(lbuf, '=');
                if (eq != NULL && eq != lbuf) {
                    *eq = '\0';
                    apply_kv(out, lbuf, strtol(eq + 1, NULL, 10));
                }
            }
        }
        /* Oversized or malformed lines are skipped (forward compatibility). */
        line = (nl != NULL) ? nl + 1 : end;
    }
    return PREFS_OK;
}

/* --- omnibox suggestions --------------------------------------------------------------- */

static int ci_eq(char a, char b) {
    if (a >= 'A' && a <= 'Z') a = (char)(a - 'A' + 'a');
    if (b >= 'A' && b <= 'Z') b = (char)(b - 'A' + 'a');
    return a == b;
}

static int ci_starts(const char *s, const char *q) {
    while (*q != '\0') {
        if (*s == '\0' || !ci_eq(*s, *q)) return 0;
        ++s; ++q;
    }
    return 1;
}

static int ci_contains(const char *s, const char *q) {
    if (*q == '\0') return 1;
    for (; *s != '\0'; ++s)
        if (ci_starts(s, q)) return 1;
    return 0;
}

/* Prefix match as the user types it: the raw URL, past the scheme, and past a
 * leading "www." ("wiki" hits "https://www.wikipedia.org/"). */
static int url_prefix_match(const char *url, const char *q) {
    if (ci_starts(url, q)) return 1;
    const char *p = strstr(url, "://");
    if (p != NULL) {
        p += 3;
        if (ci_starts(p, q)) return 1;
        if (ci_starts(p, "www.") && ci_starts(p + 4, q)) return 1;
    }
    return 0;
}

/* Appends url to the result rows unless present, oversized or full. */
static void sugg_push(char *out, size_t row_len, int max_rows, int *n,
                      const char *url) {
    if (*n >= max_rows || strlen(url) >= row_len) return;
    for (int i = 0; i < *n; ++i)
        if (strcmp(out + (size_t)i * row_len, url) == 0) return;
    memcpy(out + (size_t)*n * row_len, url, strlen(url) + 1);
    (*n)++;
}

int prefs_suggest(const prefs_state *p, const char *query,
                  char *out, size_t row_len, int max_rows) {
    if (p == NULL || query == NULL || out == NULL || row_len < 2 || max_rows <= 0)
        return 0;
    int n = 0;
    for (size_t i = 0; i < p->bookmarks_len && n < max_rows; ++i)
        if (url_prefix_match(p->bookmarks[i].url, query))
            sugg_push(out, row_len, max_rows, &n, p->bookmarks[i].url);
    for (size_t i = 0; i < p->history_len && n < max_rows; ++i)
        if (url_prefix_match(p->history[i], query))
            sugg_push(out, row_len, max_rows, &n, p->history[i]);
    for (size_t i = 0; i < p->bookmarks_len && n < max_rows; ++i)
        if (ci_contains(p->bookmarks[i].url, query) ||
            ci_contains(p->bookmarks[i].title, query))
            sugg_push(out, row_len, max_rows, &n, p->bookmarks[i].url);
    for (size_t i = 0; i < p->history_len && n < max_rows; ++i)
        if (ci_contains(p->history[i], query))
            sugg_push(out, row_len, max_rows, &n, p->history[i]);
    return n;
}

/* --- internal bookmarks page ------------------------------------------------------------- */

typedef struct sbuf { char *data; size_t len, cap; int oom; } sbuf;

static void sb_put(sbuf *b, const char *s, size_t n) {
    if (b->oom) return;
    if (b->len + n + 1 > b->cap) {
        size_t nc = (b->cap == 0) ? 1024 : b->cap;
        while (nc < b->len + n + 1) nc *= 2;
        char *nd = (char *)realloc(b->data, nc);
        if (nd == NULL) { b->oom = 1; return; }
        b->data = nd;
        b->cap = nc;
    }
    memcpy(b->data + b->len, s, n);
    b->len += n;
    b->data[b->len] = '\0';
}

static void sb_str(sbuf *b, const char *s) { sb_put(b, s, strlen(s)); }

/* HTML-escapes hostile text into the page (&<>"'). */
static void sb_esc(sbuf *b, const char *s) {
    for (; *s != '\0'; ++s) {
        switch (*s) {
        case '&':  sb_str(b, "&amp;");  break;
        case '<':  sb_str(b, "&lt;");   break;
        case '>':  sb_str(b, "&gt;");   break;
        case '"':  sb_str(b, "&quot;"); break;
        case '\'': sb_str(b, "&#39;");  break;
        default:   sb_put(b, s, 1);     break;
        }
    }
}

static void sb_link_item(sbuf *b, const char *url, const char *label) {
    sb_str(b, "<li><a href=\"");
    sb_esc(b, url);
    sb_str(b, "\">");
    sb_esc(b, (label != NULL && label[0] != '\0') ? label : url);
    sb_str(b, "</a></li>\n");
}

prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len) {
    if (p == NULL || out == NULL || out_len == NULL) return PREFS_ERR_NULL_ARG;
    *out = NULL;
    *out_len = 0;
    sbuf b = {0};
    sb_str(&b,
        "<html><head><title>Bookmarks</title></head><body>\n"
        "<h1>Bookmarks</h1>\n");
    if (p->bookmarks_len == 0) {
        sb_str(&b, "<p>No bookmarks yet. Press Ctrl+B on a page to bookmark it.</p>\n");
    } else {
        sb_str(&b, "<ul>\n");
        for (size_t i = 0; i < p->bookmarks_len; ++i)
            sb_link_item(&b, p->bookmarks[i].url, p->bookmarks[i].title);
        sb_str(&b, "</ul>\n");
    }
    sb_str(&b, "<h1>Recent history</h1>\n");
    if (p->history_len == 0) {
        sb_str(&b, "<p>No history recorded.</p>\n");
    } else {
        sb_str(&b, "<ul>\n");
        size_t shown = (p->history_len < PREFS_PAGE_HISTORY)
                     ? p->history_len : PREFS_PAGE_HISTORY;
        for (size_t i = 0; i < shown; ++i)
            sb_link_item(&b, p->history[i], NULL);
        sb_str(&b, "</ul>\n");
    }
    sb_str(&b, "</body></html>\n");
    if (b.oom) { free(b.data); return PREFS_ERR_OOM; }
    *out = b.data;
    *out_len = b.len;
    return PREFS_OK;
}
