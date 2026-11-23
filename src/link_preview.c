/* link_preview -- the status-strip description of a hovered link (spec/link_preview.md). */
#include "link_preview.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "link_nav.h"

/* Growable-free escape sink: writes into a caller-sized buffer that is always large
 * enough (3 bytes per source byte), so no bound check is lost on a short write. */
typedef struct lp_sink {
    char  *buf;
    size_t len;
} lp_sink;

static void put_raw(lp_sink *s, const char *src, size_t n) {
    memcpy(s->buf + s->len, src, n);
    s->len += n;
}

static void put_escaped(lp_sink *s, const char *src, size_t n) {
    static const char hex[] = "0123456789ABCDEF";
    for (size_t i = 0; i < n; ++i) {
        unsigned char c = (unsigned char)src[i];
        if (c >= 0x20 && c < 0x7F) {
            s->buf[s->len++] = (char)c;
        } else {
            s->buf[s->len++] = '%';
            s->buf[s->len++] = hex[c >> 4];
            s->buf[s->len++] = hex[c & 0x0F];
        }
    }
}

/* Host span of an absolute URL in s[0..n): after "scheme://", without userinfo or port. */
static void host_span(const char *s, size_t n, size_t *off, size_t *len) {
    *off = 0;
    *len = 0;
    const char *sep = NULL;
    for (size_t i = 0; i + 2 < n; ++i) {
        if (s[i] == ':' && s[i + 1] == '/' && s[i + 2] == '/') { sep = s + i + 3; break; }
        if (s[i] == '/' || s[i] == '?' || s[i] == '#') return;
    }
    if (sep == NULL) return;
    size_t a = (size_t)(sep - s), e = a;
    while (e < n && s[e] != '/' && s[e] != '?' && s[e] != '#') ++e;
    for (size_t i = e; i > a; --i)
        if (s[i - 1] == '@') { a = i; break; }
    size_t h = e;
    if (a < e && s[a] == '[') {
        for (size_t i = a; i < e; ++i)
            if (s[i] == ']') { h = i + 1; break; }
    } else {
        for (size_t i = a; i < e; ++i)
            if (s[i] == ':') { h = i; break; }
    }
    *off = a;
    *len = h - a;
}

/* Copies s[0..n) into out->text, eliding the middle of the path when it does not fit
 * and keeping scheme + host (+ the slash after it) whole. */
static void fit(const char *s, size_t n, size_t hoff, size_t hlen, lp_preview *out) {
    const size_t cap = LP_TEXT_MAX - 1;
    out->host_off = hoff;
    out->host_len = hlen;
    if (n <= cap) {
        memcpy(out->text, s, n);
        out->text[n] = '\0';
        return;
    }
    size_t head = hlen > 0 ? hoff + hlen : 0;
    while (head < n && s[head] != '/' && s[head] != '?' && s[head] != '#') ++head;
    if (head < n && s[head] == '/') ++head;
    if (hlen > 0 && head + 3 + 16 <= cap) {
        size_t tail = cap - head - 3;
        size_t t = n - tail;
        if (s[t - 1] == '%') t += 2;
        else if (t >= 2 && s[t - 2] == '%') t += 1;
        memcpy(out->text, s, head);
        memcpy(out->text + head, "...", 3);
        memcpy(out->text + head + 3, s + t, n - t);
        out->text[head + 3 + (n - t)] = '\0';
        return;
    }
    size_t keep = cap - 3;
    if (keep >= 1 && s[keep - 1] == '%') keep -= 1;
    else if (keep >= 2 && s[keep - 2] == '%') keep -= 2;
    memcpy(out->text, s, keep);
    memcpy(out->text + keep, "...", 4);
    if (out->host_off >= keep) {
        out->host_off = 0;
        out->host_len = 0;
    } else if (out->host_off + out->host_len > keep) {
        out->host_len = keep - out->host_off;
    }
}

static size_t frag_free_len(const char *base) {
    const char *h = strchr(base, '#');
    return h != NULL ? (size_t)(h - base) : strlen(base);
}

lp_status lp_describe(const char *base, const char *href, lp_preview *out) {
    if (out == NULL) return LP_EINVAL;
    memset(out, 0, sizeof *out);
    ln_result *r = malloc(sizeof *r);
    if (r == NULL) {
        out->kind = LP_BLOCKED;
        memcpy(out->text, "Blocked", 8);
        return LP_OK;
    }
    if (ln_resolve(base, href, r) != LN_OK) r->action = LN_BLOCKED;

    const char *prefix = "";
    const char *a = "", *b = "";
    size_t alen = 0, blen = 0;
    int escape_a = 1;
    if (r->action == LN_NAVIGATE) {
        out->kind = LP_NAVIGATE;
        if (r->kind == LN_TARGET_FILE && r->target[0] == '/') prefix = "file://";
        a = r->target;
        alen = strlen(a);
    } else if (r->action == LN_SAME_DOCUMENT) {
        out->kind = LP_SAME_DOCUMENT;
        if (base != NULL) {
            if (base[0] == '/') prefix = "file://";
            a = base;
            alen = frag_free_len(base);
        }
        const char *h = href != NULL ? strchr(href, '#') : NULL;
        if (h != NULL) { b = h; blen = strlen(h); }
    } else {
        out->kind = LP_BLOCKED;
        const char *why = ln_block_reason_text(r->reason);
        if (strncmp(why, "blocked: ", 9) == 0) why += 9;
        a = why;
        alen = strlen(why);
        escape_a = 0;
        if (href != NULL) { b = href; blen = strlen(href); }
    }

    size_t plen = strlen(prefix);
    size_t extra = out->kind == LP_BLOCKED ? 12 : 0;   /* "Blocked (" + "): " */
    if (alen > (SIZE_MAX - 64) / 3 || blen > (SIZE_MAX - 64) / 3 - alen) {
        out->kind = LP_BLOCKED;
        memcpy(out->text, "Blocked", 8);
        free(r);
        return LP_OK;
    }
    size_t need = plen + extra + 3 * (alen + blen) + 1;
    lp_sink s = { malloc(need), 0 };
    if (s.buf == NULL) {
        strcpy(out->text, out->kind == LP_BLOCKED ? "Blocked" : "...");
        free(r);
        return LP_OK;
    }
    if (out->kind == LP_BLOCKED) {
        put_raw(&s, "Blocked (", 9);
        put_raw(&s, a, alen);
        put_raw(&s, "): ", 3);
    } else {
        put_raw(&s, prefix, plen);
        if (escape_a) put_escaped(&s, a, alen);
    }
    put_escaped(&s, b, blen);

    size_t hoff = 0, hlen = 0;
    if (out->kind != LP_BLOCKED && plen == 0) host_span(s.buf, s.len, &hoff, &hlen);
    fit(s.buf, s.len, hoff, hlen, out);
    free(s.buf);
    free(r);
    return LP_OK;
}
