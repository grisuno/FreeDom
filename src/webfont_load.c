/*
 * webfont_load — trusted-side @font-face fetch-and-register pass.
 * See include/webfont_load.h, spec/webfont.md.
 *
 * No network of its own (the fetch callback owns policy), no global state, no
 * worker contact. Every hostile input (CSS text, URLs, fetched bytes, content
 * types) is validated before use; every failure skips one face, never a page.
 */

#include "webfont_load.h"
#include "webfont.h"
#include "text_shape.h"
#include "url.h"
#include "data_url.h"

#include <stdlib.h>
#include <string.h>

/* Content types worth downloading as fonts. Empty (like the css/js fetchers'
 * tolerance) is allowed: magic at registration is authoritative, and servers
 * routinely lie. Parameters after ';' are ignored. woff2 is deliberately NOT
 * filtered here (a "" hint may still name one); unsupported bytes die at
 * tsh_webfont_register's magic check having cost only bounded bandwidth. */
static int ctype_ok(const char *ct) {
    if (ct == NULL || ct[0] == '\0') return 1;
    while (*ct == ' ' || *ct == '\t') ++ct;
    static const char *const PREF[] = {
        "font/", "application/font-", "application/x-font-",
        "application/octet-stream",
    };
    for (size_t i = 0; i < sizeof PREF / sizeof *PREF; ++i) {
        size_t k = 0;
        while (PREF[i][k] != '\0') ++k;
        size_t j = 0;
        for (; j < k; ++j) {
            char a = ct[j], b = PREF[i][j];
            if (a >= 'A' && a <= 'Z') a = (char)(a + 32);
            if (a != b) break;
        }
        if (j == k) return 1;
    }
    return 0;
}

/* Per-key attempt state for in-src-list fallback. */
typedef struct wf_key {
    unsigned hash;
    int      bold;
    int      italic;
    int      done;     /* registered: skip the rest */
    int      tries;    /* fetch attempts so far */
} wf_key;

/* Loader cursor: keys, budgets and counters shared across sheets so
 * first-wins and caps hold document-wide, not per sheet. */
typedef struct wf_cursor {
    wf_fetch_fn fetch;
    void       *fctx;
    wf_key      keys[WF_LOAD_MAX_KEYS];
    size_t      nkeys;
    int         registered;
    size_t      total_bytes;
    int         fetches;
} wf_cursor;

static int key_find(wf_key *keys, size_t nkeys, unsigned h, int b, int i) {
    for (size_t k = 0; k < nkeys; ++k)
        if (keys[k].hash == h && keys[k].bold == b && keys[k].italic == i)
            return (int)k;
    return -1;
}

/* Resolves a ref URL against base into out (absolute https). data: URLs never
 * reach here (decoded in place, see process_refs). Returns 1, else 0. */
static int resolve_ref(const char *base, const char *ref,
                       char *out, size_t outsz) {
    if (base == NULL || ref == NULL || out == NULL || outsz == 0) return 0;
    if (url_is_https(ref)) {
        size_t rl = strlen(ref);
        if (rl + 1 > outsz) return 0;
        memcpy(out, ref, rl + 1);
        return 1;
    }
    if (!url_is_https(base) || url_has_scheme(ref)) return 0;
    return url_resolve_https(base, ref, out, outsz) == URL_OK;
}

/* Upper bound on a data: font URL string: it must decode within the face cap
 * (base64 inflates 4/3), plus scheme/mime slack. Longer is rejected before
 * decoding (fail closed, no big allocation). */
#define WF_DATA_URL_MAX ((WF_MAX_FACE_BYTES * 4u) / 3u + 256u)

/* Processes one scanned ref list against base_url (the sheet's own URL, or
 * the page URL for inline <style>): first supported format wins per key with
 * in-list fallback, https/data:-only resolution, caps on everything. */
static void process_refs(wf_cursor *cur, const wf_ref *refs, size_t nrefs,
                         const char *base_url) {
    for (size_t r = 0; r < nrefs; ++r) {
        const wf_ref *ref = &refs[r];
        /* data: refs carry bytes with an empty url slot (by design). */
        if (ref->family[0] == '\0') continue;
        if (!ref->is_data && ref->url[0] == '\0') continue;
        unsigned h = wf_name_hash(ref->family, strlen(ref->family));
        if (h == 0) continue;
        int bb = ref->bold ? 1 : 0;
        int it = ref->italic ? 1 : 0;
        int ki = key_find(cur->keys, cur->nkeys, h, bb, it);
        if (ki < 0) {
            if (cur->nkeys >= WF_LOAD_MAX_KEYS) continue;
            ki = (int)cur->nkeys++;
            cur->keys[ki].hash = h;
            cur->keys[ki].bold = bb;
            cur->keys[ki].italic = it;
            cur->keys[ki].done = 0;
            cur->keys[ki].tries = 0;
        }
        if (cur->keys[ki].done) continue;
        if (cur->keys[ki].tries >= WF_LOAD_TRIES_PER_KEY) continue;
        /* First supported format wins per key; an unsupported hint skips
         * WITHOUT consuming the key (a later entry may name woff/ttf). */
        if (!wf_supported_format(ref->format)) continue;
        if (cur->fetches >= WF_LOAD_MAX_FETCHES) continue;
        /* data: refs carry decoded bytes from the scanner (no URL to resolve,
         * no fetch to run); https goes through resolve + fetch. */
        int is_data = ref->is_data && ref->data_bytes != NULL;
        char absurl[WF_URL_MAX];
        if (!is_data
            && !resolve_ref(base_url, ref->url, absurl, sizeof absurl))
            continue;
        cur->keys[ki].tries++;
        if (!is_data) cur->fetches++;
        unsigned char *fbytes = NULL;
        size_t fn = 0;
        if (is_data) {
            if (ref->data_len == 0 || ref->data_len > WF_MAX_FACE_BYTES)
                continue;
            fbytes = ref->data_bytes;
            fn = ref->data_len;
        } else {
            int st = 0;
            char *body = NULL;
            size_t blen = 0;
            char *ctype = NULL;
            if (cur->fetch(cur->fctx, absurl, &st, &body, &blen, &ctype) != 0)
                continue;
            int ok = (st >= 200 && st < 300) && ctype_ok(ctype)
                     && blen > 0 && blen <= WF_MAX_FACE_BYTES;
            if (!ok) {
                free(body);
                free(ctype);
                continue;
            }
            free(ctype);
            fbytes = (unsigned char *)body;
            fn = blen;
        }
        if (cur->total_bytes + fn > WF_MAX_TOTAL_BYTES) {
            if (!is_data) free(fbytes);
            continue;
        }
        if (tsh_webfont_register(ref->family, fbytes, fn, bb, it) == 0) {
            cur->keys[ki].done = 1;
            cur->registered++;
            cur->total_bytes += fn;
        }
        /* Fetched bodies are owned here; scanned data: bytes stay owned by
         * their ref (the register call copies what it keeps). */
        if (!is_data) free(fbytes);
    }
}

/* Finds inline <style>...</style> bodies in html (case-insensitive tags) and
 * processes each sheet's refs against the page URL. Spans alias html (no
 * copies); a body without a closing tag is ignored (fail closed). <style>
 * inside a JS string is indistinguishable at this level -- harmless: any URL
 * it yields is still fetched through the full policy gate and bounded like
 * every face. At most 64 bodies; extras are ignored (page still renders). */
static void scan_inline(const char *html, size_t len, const char *page_url,
                        wf_cursor *cur) {
    if (html == NULL || len == 0) return;
    size_t i = 0;
    int bodies = 0;
    while (i < len && bodies < 64) {
        /* Find "<style" (ci), then its '>'. */
        size_t t = len;
        for (size_t k = i; k + 6 <= len; ++k) {
            if (html[k] != '<') continue;
            if ((html[k + 1] == 's' || html[k + 1] == 'S')
                && (html[k + 2] == 't' || html[k + 2] == 'T')
                && (html[k + 3] == 'y' || html[k + 3] == 'Y')
                && (html[k + 4] == 'l' || html[k + 4] == 'L')
                && (html[k + 5] == 'e' || html[k + 5] == 'E')) {
                t = k;
                break;
            }
        }
        if (t >= len) break;
        size_t gt = t + 6;
        while (gt < len && html[gt] != '>') ++gt;
        if (gt >= len) break;
        size_t bs = gt + 1;
        /* Find "</style" (ci). */
        size_t be = len;
        for (size_t k = bs; k + 8 <= len; ++k) {
            if (html[k] == '<' && html[k + 1] == '/'
                && (html[k + 2] == 's' || html[k + 2] == 'S')
                && (html[k + 3] == 't' || html[k + 3] == 'T')
                && (html[k + 4] == 'y' || html[k + 4] == 'Y')
                && (html[k + 5] == 'l' || html[k + 5] == 'L')
                && (html[k + 6] == 'e' || html[k + 6] == 'E')) {
                be = k;
                break;
            }
        }
        if (be > bs && be <= len) {
            wf_list one;
            one.refs = NULL;
            one.count = 0;
            one.cap = 0;
            if (wf_scan(html + bs, be - bs, &one) == 0)
                process_refs(cur, one.refs, one.count, page_url);
            wf_list_free(&one);
            ++bodies;
        }
        i = (be < len) ? be + 8 : len;
    }
}

int wf_load_document(wf_fetch_fn fetch, void *fctx, const char *page_url,
                     const wf_sheet *extern_sheets, size_t nextern,
                     const char *html, size_t html_len) {
    /* Untrusted pages pass no fetcher: no-op. A NULL page (local file) still
     * runs in data:-only mode: data: faces decode locally while relative URLs
     * have no base and absolute https still goes through the fetch gate. */
    if (fetch == NULL) return -1;
    wf_cursor cur;
    cur.fetch = fetch;
    cur.fctx = fctx;
    cur.nkeys = 0;
    cur.registered = 0;
    cur.total_bytes = 0;
    cur.fetches = 0;
    /* Worker sheet order is extern-then-inline (collect_page_css): scan the
     * same way so first-wins agrees on duplicate families. */
    if (extern_sheets != NULL) {
        for (size_t s = 0; s < nextern; ++s) {
            if (extern_sheets[s].text == NULL || extern_sheets[s].len == 0
                || extern_sheets[s].url == NULL)
                continue;
            wf_list one;
            one.refs = NULL;
            one.count = 0;
            one.cap = 0;
            if (wf_scan(extern_sheets[s].text, extern_sheets[s].len, &one) == 0)
                process_refs(&cur, one.refs, one.count, extern_sheets[s].url);
            wf_list_free(&one);
        }
    }
    scan_inline(html, html_len, page_url, &cur);
    return cur.registered;
}
