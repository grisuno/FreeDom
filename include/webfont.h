#ifndef FREEDOM_WEBFONT_H
#define FREEDOM_WEBFONT_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * webfont — pure @font-face lookahead scanner for the trusted side.
 *
 * Reads hostile CSS bytes and extracts (family, url, format, bold, italic)
 * references. It never fetches, never resolves URLs against an origin (that is
 * policy), and never changes rendering by itself. The fetch/register/select
 * pipeline consumes its output under the page_trusted gate; see spec/webfont.md
 * for the full trust model.
 */

#define WF_FAMILY_MAX 64
#define WF_URL_MAX    1024
#define WF_FORMAT_MAX 16
#define WF_MAX_REFS   128
#define WF_MAX_FACE_BYTES ((size_t)1u << 20)
#define WF_MAX_TOTAL_BYTES ((size_t)8u << 20)
/* Upper bound on a data: font URL string: it must decode within the face cap
 * (base64 inflates 4/3), plus scheme/mime slack. Longer is rejected before
 * decoding (fail closed, no big allocation). */
#define WF_DATA_URL_MAX ((WF_MAX_FACE_BYTES * 4u) / 3u + 256u)

typedef struct wf_ref {
    char family[WF_FAMILY_MAX];
    char url[WF_URL_MAX];
    char format[WF_FORMAT_MAX];
    int  bold;
    int  italic;
    /* data: fonts decode at scan time (a data: URL never fits url[]): is_data
     * set with the decoded bytes owned here (freed by wf_list_free); url is
     * then "" and the loader registers the bytes with no fetch. Struct copies
     * must transfer ownership via wf_ref_move (a shallow copy double-frees). */
    int            is_data;
    unsigned char *data_bytes;
    size_t         data_len;
} wf_ref;

typedef struct wf_list {
    wf_ref *refs;
    size_t  count;
    size_t  cap;
} wf_list;

int wf_scan(const char *css, size_t len, wf_list *out);
void wf_list_free(wf_list *l);

/* Moves *src into *dst, transferring data_bytes ownership (src is left
 * without bytes). Use instead of struct assignment wherever refs cross list
 * boundaries (scan_inline accumulation, loader collection). */
void wf_ref_move(wf_ref *dst, wf_ref *src);

int wf_supported_format(const char *fmt);

/* FNV-1a (32-bit) over s[0,n), lowercased per byte, for author family names.
 * The worker hashes the cascaded first-name, the parent hashes scanned
 * @font-face families; equal names hash equal on both sides regardless of the
 * author's capitalisation. Empty/NULL hashes to 0 (="no webfont"); a nonempty
 * name that hashes to 0 is remapped to 1 so 0 keeps its single meaning.
 * Pure, no allocation. Static inline (like the csel_* ASCII helpers) so the
 * cascade side needs no new link edge: every css.o consumer already links. */
static inline unsigned wf_name_hash(const char *s, size_t n) {
    if (s == NULL || n == 0) return 0;
    unsigned h = 2166136261u;
    for (size_t i = 0; i < n; ++i) {
        unsigned char c = (unsigned char)s[i];
        if (c >= 'A' && c <= 'Z') c = (unsigned char)(c + 32);
        h ^= c;
        h *= 16777619u;
    }
    return (h != 0) ? h : 1u;
}

#endif /* FREEDOM_WEBFONT_H */
