/*
 * frame_broker -- pure frame tree + postMessage routing decisions (spec/frame_broker.md).
 * No I/O, no allocation, no global state: every string is hostile data.
 */
#include "frame_broker.h"

#include <string.h>

static char lc(char c) { return (c >= 'A' && c <= 'Z') ? (char)(c + 32) : c; }

static int host_char_ok(char c) {
    return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '.' || c == '-' || c == '_';
}

int fbk_origin_of(const char *url, char *out, size_t cap) {
    if (url == NULL || out == NULL || cap < 5) return -1;
    static const char scheme[] = "https://";
    for (size_t i = 0; i < 8; ++i) {
        if (lc(url[i]) != scheme[i]) { memcpy(out, "null", 5); return 0; }
    }
    const char *p = url + 8;
    size_t alen = 0;
    while (p[alen] != '\0' && p[alen] != '/' && p[alen] != '?' && p[alen] != '#') ++alen;
    const char *auth = p;
    for (size_t i = 0; i < alen; ++i) {              /* drop userinfo: it is not part of an origin */
        if (auth[i] == '@') { auth += i + 1; alen -= i + 1; break; }
    }
    size_t hlen = 0;
    while (hlen < alen && auth[hlen] != ':') ++hlen;
    if (hlen == 0 || hlen > 253) { memcpy(out, "null", 5); return 0; }
    for (size_t i = 0; i < hlen; ++i)
        if (!host_char_ok(lc(auth[i]))) { memcpy(out, "null", 5); return 0; }
    size_t plen = alen - hlen;                        /* ":port" or 0 */
    char port[8]; size_t pn = 0;
    if (plen != 0) {
        if (plen < 2 || plen > 6) { memcpy(out, "null", 5); return 0; }
        for (size_t i = 1; i < plen; ++i) {
            if (auth[hlen + i] < '0' || auth[hlen + i] > '9') { memcpy(out, "null", 5); return 0; }
            port[pn++] = auth[hlen + i];
        }
        if (pn == 3 && memcmp(port, "443", 3) == 0) pn = 0;   /* default port is not serialized */
    }
    size_t need = 8 + hlen + (pn != 0 ? 1 + pn : 0) + 1;
    if (need > cap) return -1;
    memcpy(out, "https://", 8);
    for (size_t i = 0; i < hlen; ++i) out[8 + i] = lc(auth[i]);
    size_t n = 8 + hlen;
    if (pn != 0) { out[n++] = ':'; memcpy(out + n, port, pn); n += pn; }
    out[n] = '\0';
    return 0;
}

int fbk_init(fbk_table *t, const char *top_url) {
    if (t == NULL || top_url == NULL) return -1;
    memset(t, 0, sizeof *t);
    t->f[0].used = 1;
    t->f[0].parent = -1;
    t->f[0].depth = 0;
    return fbk_origin_of(top_url, t->f[0].origin, sizeof t->f[0].origin);
}

static int live(const fbk_table *t, int id) {
    return t != NULL && id >= 0 && id < FBK_MAX_FRAMES && t->f[id].used;
}

int fbk_add(fbk_table *t, int parent, const char *url, int *out_id) {
    if (t == NULL || url == NULL || out_id == NULL || !live(t, parent)) return -1;
    if (t->f[parent].depth + 1 > FBK_MAX_DEPTH) return -1;
    for (int i = 1; i < FBK_MAX_FRAMES; ++i) {
        if (t->f[i].used) continue;
        fbk_frame fr;
        memset(&fr, 0, sizeof fr);
        if (fbk_origin_of(url, fr.origin, sizeof fr.origin) != 0) return -1;
        fr.used = 1;
        fr.parent = parent;
        fr.depth = t->f[parent].depth + 1;
        t->f[i] = fr;
        *out_id = i;
        return 0;
    }
    return -1;
}

void fbk_remove(fbk_table *t, int id) {
    if (t == NULL || id <= 0 || !live(t, id)) return;
    t->f[id].used = 0;
    int changed = 1;                                  /* fixpoint: slots are reused, order is not a tree order */
    while (changed) {
        changed = 0;
        for (int i = 1; i < FBK_MAX_FRAMES; ++i) {
            if (t->f[i].used && !t->f[t->f[i].parent].used) { t->f[i].used = 0; changed = 1; }
        }
    }
}

const char *fbk_origin(const fbk_table *t, int id) {
    return live(t, id) ? t->f[id].origin : NULL;
}

/* 1 when the page-supplied targetOrigin admits a receiver of origin `recv` from a sender of origin `snd`. */
static int target_admits(const char *target, const char *snd, const char *recv) {
    if (target == NULL) return 0;
    if (strcmp(target, "*") == 0) return 1;
    if (strcmp(recv, "null") == 0) return 0;            /* an opaque origin matches nothing but "*" */
    if (strcmp(target, "/") == 0) return strcmp(snd, recv) == 0;
    char norm[FBK_ORIGIN_MAX];
    if (strlen(target) >= sizeof norm) return 0;
    if (fbk_origin_of(target, norm, sizeof norm) != 0 || strcmp(norm, "null") == 0) return 0;
    if (strlen(norm) != strlen(target)) {               /* must BE an origin: no path/query/userinfo, case aside */
        size_t i = 0;
        while (norm[i] != '\0' && lc(target[i]) == norm[i]) ++i;
        if (norm[i] != '\0' || (target[i] != '\0' && target[i] != '/')) return 0;
        if (target[i] == '/' && target[i + 1] != '\0') return 0;
    }
    return strcmp(norm, recv) == 0;
}

fbk_verdict fbk_route(const fbk_table *t, int from, fbk_rel rel, int child,
                      const char *target_origin, size_t size, int *dest) {
    if (dest == NULL || !live(t, from)) return FBK_ERR_FRAME;
    int to;
    switch (rel) {
        case FBK_REL_PARENT: to = t->f[from].parent; break;
        case FBK_REL_TOP:    to = (from == 0) ? -1 : 0; break;
        case FBK_REL_CHILD:
            to = (live(t, child) && t->f[child].parent == from) ? child : -1;
            break;
        default: return FBK_ERR_FRAME;
    }
    if (!live(t, to)) return FBK_ERR_FRAME;
    if (size > FBK_MAX_MSG) return FBK_ERR_SIZE;
    if (!target_admits(target_origin, t->f[from].origin, t->f[to].origin)) return FBK_DROP_ORIGIN;
    *dest = to;
    return FBK_DELIVER;
}
