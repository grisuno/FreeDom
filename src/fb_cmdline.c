#include "fb_cmdline.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fb_panes.h"
#include "freebug.h"

static char *dup_n(const char *s, size_t n) {
    if (n == (size_t)-1) return NULL;
    char *d = (char *)malloc(n + 1);
    if (d == NULL) return NULL;
    if (n > 0) memcpy(d, s, n);
    d[n] = '\0';
    return d;
}

void fbc_history_init(fbc_history *h) {
    if (h != NULL) memset(h, 0, sizeof *h);
}

void fbc_history_free(fbc_history *h) {
    if (h == NULL) return;
    for (size_t i = 0; i < h->n; ++i) { free(h->items[i]); h->items[i] = NULL; }
    free(h->draft);
    h->draft = NULL;
    h->n = 0;
    h->pos = 0;
}

int fbc_history_push(fbc_history *h, const char *text, size_t len) {
    if (h == NULL || (text == NULL && len > 0)) return -1;
    if (len > FBC_ENTRY_MAX) return -1;
    free(h->draft);
    h->draft = NULL;
    h->pos = h->n;
    if (len == 0) return 0;
    if (h->n > 0 && strlen(h->items[h->n - 1]) == len && memcmp(h->items[h->n - 1], text, len) == 0)
        return 0;
    char *copy = dup_n(text, len);
    if (copy == NULL) return -1;
    if (h->n == FBC_HIST_MAX) {
        free(h->items[0]);
        memmove(h->items, h->items + 1, (FBC_HIST_MAX - 1) * sizeof h->items[0]);
        h->n--;
    }
    h->items[h->n++] = copy;
    h->pos = h->n;
    return 0;
}

const char *fbc_history_prev(fbc_history *h, const char *cur, size_t curlen) {
    if (h == NULL || h->pos == 0 || h->n == 0) return NULL;
    if (h->pos == h->n) {
        free(h->draft);
        h->draft = dup_n(cur != NULL ? cur : "", cur != NULL ? curlen : 0);
    }
    h->pos--;
    return h->items[h->pos];
}

const char *fbc_history_next(fbc_history *h) {
    if (h == NULL || h->pos >= h->n) return NULL;
    h->pos++;
    if (h->pos < h->n) return h->items[h->pos];
    return h->draft != NULL ? h->draft : "";
}

static int path_char(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '$' || c == '.';
}

long fbc_complete_split(const char *text, size_t n, char *base, size_t cap, size_t *prefix_off) {
    if (text == NULL || base == NULL || cap == 0 || prefix_off == NULL) return -1;
    size_t start = n;
    while (start > 0 && path_char(text[start - 1])) start--;
    /* a path is not preceded by `]`, `)` or a quote: that is an expression this model cannot resolve */
    if (start > 0 && (text[start - 1] == ']' || text[start - 1] == ')' || text[start - 1] == '"'
                      || text[start - 1] == '\'')) return -1;
    size_t len = n - start;
    if (len == 0 || text[start] == '.' || (text[start] >= '0' && text[start] <= '9')) return -1;
    for (size_t i = start + 1; i < n; ++i)
        if (text[i] == '.' && text[i - 1] == '.') return -1;
    size_t dot = n;
    while (dot > start && text[dot - 1] != '.') dot--;
    size_t base_len = (dot > start) ? dot - 1 - start : 0;
    if (base_len >= cap || base_len >= FBC_BASE_MAX) return -1;
    memcpy(base, text + start, base_len);
    base[base_len] = '\0';
    *prefix_off = (dot > start) ? dot : start;
    return (long)(n - *prefix_off);
}

size_t fbc_names_expr(const char *base, char *out, size_t cap) {
    if (base == NULL || out == NULL) return 0;
    size_t bl = strlen(base);
    if (bl >= FBC_BASE_MAX) return 0;
    for (size_t i = 0; i < bl; ++i) if (!path_char(base[i])) return 0;
    char q[FBC_BASE_MAX + 4];
    if (fbp_js_quote(base, bl, q, sizeof q) == 0) return 0;
    static const char BODY[] =
        "(function(p){var o=globalThis,s=p?p.split('.'):[],i,x,f;"
        "for(i=0;i<s.length;i++){x=o;f=null;"
        "while(x!=null&&!f){f=Object.getOwnPropertyDescriptor(x,s[i]);if(!f)x=Object.getPrototypeOf(x);}"
        "if(!f)return '';try{o=('value' in f)?f.value:(f.get?f.get.call(o):undefined);}catch(e){return '';}"
        "if(o==null)return '';}"
        "var r={},k=0;x=Object(o);"
        "for(;x!=null&&k<64;k++){Object.getOwnPropertyNames(x).forEach(function(n){r[n]=1;});x=Object.getPrototypeOf(x);}"
        "return Object.keys(r).sort().join('\\n');})(";
    size_t need = (sizeof BODY - 1) + strlen(q) + 2;
    if (need > cap) return 0;
    int r = snprintf(out, cap, "%s%s)", BODY, q);
    if (r < 0 || (size_t)r >= cap) { out[0] = '\0'; return 0; }
    return (size_t)r;
}

size_t fbc_complete_pick(const char *names, const char *prefix, size_t plen,
                         char *ins, size_t ins_cap, char *list, size_t list_cap, size_t *count) {
    size_t cnt = 0, common = 0, ln = 0;
    char first[256];
    first[0] = '\0';
    if (ins != NULL && ins_cap > 0) ins[0] = '\0';
    if (list != NULL && list_cap > 0) list[0] = '\0';
    if (names == NULL || prefix == NULL) { if (count != NULL) *count = 0; return 0; }
    const char *p = names;
    while (*p != '\0') {
        const char *nl = strchr(p, '\n');
        size_t nlen = nl != NULL ? (size_t)(nl - p) : strlen(p);
        if (nlen >= plen && memcmp(p, prefix, plen) == 0 && nlen < sizeof first) {
            if (cnt == 0) { memcpy(first, p, nlen); first[nlen] = '\0'; common = nlen; }
            else {
                size_t k = 0;
                while (k < common && k < nlen && first[k] == p[k]) k++;
                common = k;
            }
            if (cnt < FBC_LIST_NAMES && list != NULL && list_cap > 0
                && ln + nlen + 2 <= list_cap) {
                if (ln > 0) list[ln++] = ' ';
                memcpy(list + ln, p, nlen);
                ln += nlen;
                list[ln] = '\0';
            }
            cnt++;
        }
        if (nl == NULL) break;
        p = nl + 1;
    }
    if (count != NULL) *count = cnt;
    size_t extra = (cnt > 0 && common > plen) ? common - plen : 0;
    if (extra > 0 && ins != NULL && extra < ins_cap) {
        memcpy(ins, first + plen, extra);
        ins[extra] = '\0';
        return extra;
    }
    return 0;
}

int fbc_filter_passes(int filter, int level) {
    switch (filter) {
    case FBC_FILTER_ERRORS:   return level == FB_ERROR;
    case FBC_FILTER_WARNINGS: return level == FB_WARN;
    case FBC_FILTER_LOGS:     return level == FB_LOG || level == FB_INFO || level == FB_DEBUG;
    default:                  return 1;
    }
}

int fbc_filter_next(int filter) {
    if (filter < 0 || filter >= FBC_FILTER_COUNT) filter = FBC_FILTER_ALL;
    return (filter + 1) % FBC_FILTER_COUNT;
}

const char *fbc_filter_label(int filter) {
    switch (filter) {
    case FBC_FILTER_ERRORS:   return "Errors";
    case FBC_FILTER_WARNINGS: return "Warnings";
    case FBC_FILTER_LOGS:     return "Logs";
    default:                  return "All";
    }
}
