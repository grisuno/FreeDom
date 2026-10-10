/*
 * webfont — trusted-side @font-face lookahead scanner. See include/webfont.h,
 * spec/webfont.md.
 *
 * Hostile CSS in, bounded refs out. No allocation except the caller's list, no
 * I/O, no global state. It mirrors the worker parser's @font-face
 * understanding just far enough to find candidates (family + first url() per
 * src entry + weight/style descriptors); the fetch layer picks the first
 * SUPPORTED format and policy-gates the download.
 */

#include "webfont.h"
#include "data_url.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static int is_ws(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f';
}

static int lower_ch(char c) {
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

/* Case-insensitive span equality: s[0,n) vs NUL-terminated kw. */
static int ci_eq_span(const char *s, size_t n, const char *kw) {
    size_t k = 0;
    while (kw[k] != '\0') ++k;
    if (k != n) return 0;
    for (size_t i = 0; i < n; ++i)
        if (lower_ch(s[i]) != kw[i]) return 0;
    return 1;
}

/* Copies [a,b) trimmed of ASCII blanks into dst (cap bytes, NUL-terminated).
 * Truncates (fail closed: a truncated token simply will not match anything). */
static void copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap) {
    while (a < b && is_ws(s[a])) ++a;
    while (b > a && is_ws(s[b - 1])) --b;
    size_t n = b - a;
    if (cap == 0) return;
    if (n + 1 > cap) n = cap - 1;
    if (n > 0) memcpy(dst, s + a, n);
    dst[n] = '\0';
}

void wf_list_free(wf_list *l) {
    if (l == NULL) return;
    if (l->refs != NULL) {
        for (size_t i = 0; i < l->count; ++i) {
            free(l->refs[i].data_bytes);
            l->refs[i].data_bytes = NULL;
            l->refs[i].data_len = 0;
        }
        free(l->refs);
    }
    l->refs = NULL;
    l->count = 0;
    l->cap = 0;
}

void wf_ref_move(wf_ref *dst, wf_ref *src) {
    if (dst == NULL || src == NULL || dst == src) return;
    *dst = *src;
    src->data_bytes = NULL;
    src->data_len = 0;
    src->is_data = 0;
}



int wf_supported_format(const char *fmt) {
    if (fmt == NULL) return 0;
    if (fmt[0] == '\0') return 1;   /* no hint: fetch, sniff magic at receipt */
    return ci_eq_span(fmt, strlen(fmt), "woff")
        || ci_eq_span(fmt, strlen(fmt), "truetype")
        || ci_eq_span(fmt, strlen(fmt), "opentype");
}

/* Grows out for one more ref. Returns the slot, or NULL (full/OOM). */
static wf_ref *emit_slot(wf_list *out) {
    if (out->count >= WF_MAX_REFS) return NULL;
    if (out->count >= out->cap) {
        size_t nc = (out->cap != 0) ? out->cap * 2 : 8;
        if (nc > WF_MAX_REFS) nc = WF_MAX_REFS;
        wf_ref *g = (wf_ref *)realloc(out->refs, nc * sizeof *g);
        if (g == NULL) return NULL;
        out->refs = g;
        out->cap = nc;
    }
    wf_ref *r = &out->refs[out->count++];
    memset(r, 0, sizeof *r);
    return r;
}

static void emit_family_format(wf_ref *r, const char *family, const char *format) {
    size_t fl = strlen(family);
    if (fl >= WF_FAMILY_MAX) fl = WF_FAMILY_MAX - 1;
    memcpy(r->family, family, fl);
    r->family[fl] = '\0';
    if (format != NULL) {
        size_t xl = strlen(format);
        if (xl >= WF_FORMAT_MAX) xl = WF_FORMAT_MAX - 1;
        for (size_t i = 0; i < xl; ++i) r->format[i] = (char)lower_ch(format[i]);
        r->format[xl] = '\0';
    } else {
        r->format[0] = '\0';
    }
}

/* True when span[0,slen) is a data: URL (case-insensitive scheme). */
static int span_is_data(const char *span, size_t slen) {
    static const char pre[] = "data:";
    if (slen < sizeof pre - 1) return 0;
    for (size_t i = 0; i < sizeof pre - 1; ++i) {
        char a = span[i], b = pre[i];
        if (a >= 'A' && a <= 'Z') a = (char)(a + 32);
        if (a != b) return 0;
    }
    return 1;
}

/* Appends one https ref; drops silently past WF_MAX_REFS (bounded, fail closed). */
static void emit(wf_list *out, const char *family,
                 const char *url, size_t ulen,
                 const char *format, int bold, int italic) {
    if (family == NULL || family[0] == '\0') return;
    if (url == NULL || ulen == 0 || ulen >= WF_URL_MAX) return;
    wf_ref *r = emit_slot(out);
    if (r == NULL) return;
    emit_family_format(r, family, format);
    memcpy(r->url, url, ulen);
    r->url[ulen] = '\0';
    r->bold = bold ? 1 : 0;
    r->italic = italic ? 1 : 0;
}

/* Appends one data: ref, decoding the bytes NOW (a data: URL never fits url[];
 * the bytes ride the ref instead). Garbage/oversize decodes emit nothing. */
static void emit_data(wf_list *out, const char *family,
                      const char *span, size_t slen,
                      const char *format, int bold, int italic) {
    if (family == NULL || family[0] == '\0') return;
    if (span == NULL || slen == 0 || slen > WF_DATA_URL_MAX) return;
    char *tmp = (char *)malloc(slen + 1);
    if (tmp == NULL) return;
    memcpy(tmp, span, slen);
    tmp[slen] = '\0';
    uint8_t *bytes = NULL;
    size_t bn = 0;
    char mime[128];
    int ok = (du_decode(tmp, mime, sizeof mime, &bytes, &bn) == DU_OK)
             && bn > 0 && bn <= WF_MAX_FACE_BYTES;
    free(tmp);
    if (!ok) {
        free(bytes);
        return;
    }
    wf_ref *r = emit_slot(out);
    if (r == NULL) {
        free(bytes);
        return;
    }
    emit_family_format(r, family, format);
    r->url[0] = '\0';
    r->bold = bold ? 1 : 0;
    r->italic = italic ? 1 : 0;
    r->is_data = 1;
    r->data_bytes = bytes;
    r->data_len = bn;
}

/* Parses one @font-face {...} body (bstart..bend, braces excluded) into the
 * block's family/weight/style, then emits one ref per url() in src, in order.
 * A block without a usable family emits nothing. Malformed pieces are skipped,
 * never aborting the scan. */
static void scan_face_block(const char *s, size_t bstart, size_t bend,
                            wf_list *out) {
    char family[WF_FAMILY_MAX];
    family[0] = '\0';
    int bold = 0, italic = 0;
    size_t j = bstart;
    /* Pass 1: descriptors (family first, so src entries below inherit them). */
    while (j < bend) {
        while (j < bend && (is_ws(s[j]) || s[j] == ';')) ++j;
        if (j >= bend) break;
        size_t pstart = j;
        while (j < bend && s[j] != ':' && s[j] != ';' && s[j] != '{' && s[j] != '}') ++j;
        if (j >= bend || s[j] != ':') {
            /* Junk to the next separator; nested blocks cannot appear here. */
            while (j < bend && s[j] != ';' && s[j] != '}') ++j;
            continue;
        }
        /* Trim the name for comparison (pstart..j). */
        size_t na = pstart, nb = j;
        while (na < nb && is_ws(s[na])) ++na;
        while (nb > na && is_ws(s[nb - 1])) --nb;
        size_t vstart = j + 1;
        /* Value ends at ';' or at a paren-aware boundary (a data: URL holds
         * inner semicolons, so track depth and quotes). */
        size_t vend = vstart;
        {
            int depth = 0;
            char quote = 0;
            while (vend < bend) {
                char c = s[vend];
                if (quote != 0) {
                    if (c == quote) quote = 0;
                } else if (c == '"' || c == '\'') {
                    quote = c;
                } else if (c == '(') {
                    ++depth;
                } else if (c == ')') {
                    if (depth > 0) --depth;
                } else if (c == ';' && depth == 0) {
                    break;
                }
                ++vend;
            }
        }
        size_t nlen = nb - na;
        if (nlen == 10) {
            char nm[11];
            for (size_t k = 0; k < 10; ++k) nm[k] = (char)lower_ch(s[na + k]);
            nm[10] = '\0';
            if (memcmp(nm, "font-style", 10) == 0) {
                char tmp[32];
                copy_trim(s, vstart, vend, tmp, sizeof tmp);
                if (ci_eq_span(tmp, strlen(tmp), "italic")
                    || ci_eq_span(tmp, strlen(tmp), "oblique"))
                    italic = 1;
            }
        } else if (nlen == 11) {
            char nm[12];
            for (size_t k = 0; k < 11; ++k) nm[k] = (char)lower_ch(s[na + k]);
            nm[11] = '\0';
            if (memcmp(nm, "font-family", 11) == 0) {
                /* First name only (stacks are selection's job, out of scope):
                 * up to the first top-level comma, quotes stripped. */
                size_t vs = vstart, ve = vend;
                while (vs < ve && is_ws(s[vs])) ++vs;
                while (ve > vs && is_ws(s[ve - 1])) --ve;
                {
                    int d2 = 0;
                    char q2 = 0;
                    size_t k = vs;
                    while (k < ve) {
                        char c = s[k];
                        if (q2 != 0) { if (c == q2) q2 = 0; }
                        else if (c == '"' || c == '\'') q2 = c;
                        else if (c == '(') ++d2;
                        else if (c == ')') { if (d2 > 0) --d2; }
                        else if (c == ',' && d2 == 0) break;
                        ++k;
                    }
                    ve = k;
                }
                while (vs < ve && is_ws(s[vs])) ++vs;
                while (ve > vs && is_ws(s[ve - 1])) --ve;
                if (ve > vs && (s[vs] == '"' || s[vs] == '\'')) {
                    char q = s[vs];
                    ++vs;
                    if (ve > vs && s[ve - 1] == q) --ve;
                }
                if (ve > vs) {
                    size_t fl = ve - vs;
                    if (fl >= WF_FAMILY_MAX) fl = WF_FAMILY_MAX - 1;
                    memcpy(family, s + vs, fl);
                    family[fl] = '\0';
                }
            } else if (memcmp(nm, "font-weight", 11) == 0) {
                char tmp[32];
                copy_trim(s, vstart, vend, tmp, sizeof tmp);
                if (ci_eq_span(tmp, strlen(tmp), "bold")) {
                    bold = 1;
                } else {
                    /* Numeric 100..900: >= 600 is bold. */
                    size_t q = 0;
                    if (tmp[0] == '+') q = 1;
                    long v = 0;
                    int digits = 0;
                    while (tmp[q] >= '0' && tmp[q] <= '9') {
                        v = v * 10 + (tmp[q] - '0');
                        if (v > 9000) break;
                        ++q;
                        digits = 1;
                    }
                    if (digits && tmp[q] == '\0' && v >= 600) bold = 1;
                }
            }
            /* Any other 11-char name: not tracked, still consumed. */
        }
        j = (vend < bend) ? vend + 1 : bend;
    }
    if (family[0] == '\0') return;
    /* Pass 2: every url() in src:, in order, with its format() hint. */
    j = bstart;
    while (j < bend) {
        /* Find "src" as a declaration name (not inside another word). */
        size_t k = j;
        int found = 0;
        while (k < bend) {
            if ((k == bstart || s[k - 1] == ';' || is_ws(s[k - 1]) || s[k - 1] == '{')
                && lower_ch(s[k]) == 's' && k + 3 < bend
                && lower_ch(s[k + 1]) == 'r' && lower_ch(s[k + 2]) == 'c'
                && (s[k + 3] == ':' || is_ws(s[k + 3]))) {
                found = 1;
                break;
            }
            ++k;
        }
        if (!found) break;
        /* Value span: to ';' at depth 0 (a data: URL holds inner semicolons). */
        size_t vs = k + 3;
        while (vs < bend && s[vs] != ':') ++vs;
        if (vs < bend) ++vs;
        size_t ve = vs;
        {
            int depth = 0;
            char quote = 0;
            while (ve < bend) {
                char c = s[ve];
                if (quote != 0) { if (c == quote) quote = 0; }
                else if (c == '"' || c == '\'') quote = c;
                else if (c == '(') ++depth;
                else if (c == ')') { if (depth > 0) --depth; }
                else if (c == ';' && depth == 0) break;
                ++ve;
            }
        }
        /* Walk url(...) entries; each may carry format(...). */
        size_t u = vs;
        while (u < ve) {
            /* Next url( (case-insensitive), not local(. */
            size_t f = ve;
            for (size_t q = u; q + 4 < ve + 1; ++q) {
                if (q + 4 <= ve && lower_ch(s[q]) == 'u' && lower_ch(s[q + 1]) == 'r'
                    && lower_ch(s[q + 2]) == 'l' && s[q + 3] == '(') {
                    f = q;
                    break;
                }
                if (q + 6 <= ve && lower_ch(s[q]) == 'l' && lower_ch(s[q + 1]) == 'o'
                    && lower_ch(s[q + 2]) == 'c' && lower_ch(s[q + 3]) == 'a'
                    && lower_ch(s[q + 4]) == 'l' && s[q + 5] == '(') {
                    /* Skip local(...) entirely (never a fetch). */
                    int d2 = 1;
                    q += 6;
                    while (q < ve && d2 > 0) {
                        if (s[q] == '(') ++d2;
                        else if (s[q] == ')') --d2;
                        ++q;
                    }
                    u = q;
                    f = ve;
                    break;
                }
            }
            if (f >= ve) break;
            /* An opening quote is consumed up front, so the span holds the
             * URL proper; an unterminated quote ends at the value end (CSS
             * Syntax closes strings at EOF), never emitting a stray ". */
            size_t us = f + 4, ue = us;
            {
                char qq = 0;
                if (ue < ve && (s[ue] == '"' || s[ue] == '\'')) {
                    qq = s[ue];
                    us = ++ue;
                }
                while (ue < ve && (qq != 0 ? s[ue] != qq : s[ue] != ')')) ++ue;
            }
            size_t ua = us, ub = ue;
            while (ua < ub && is_ws(s[ua])) ++ua;
            while (ub > ua && is_ws(s[ub - 1])) --ub;
            /* Optional format(...) right after this url(...). */
            char fmt[WF_FORMAT_MAX];
            fmt[0] = '\0';
            {
                size_t q = ue;
                if (q < ve && (s[q] == '"' || s[q] == '\'')) ++q;
                if (q < ve && s[q] == ')') ++q;
                while (q < ve && (is_ws(s[q]) || s[q] == ',')) ++q;
                if (q + 7 <= ve && lower_ch(s[q]) == 'f' && lower_ch(s[q + 1]) == 'o'
                    && lower_ch(s[q + 2]) == 'r' && lower_ch(s[q + 3]) == 'm'
                    && lower_ch(s[q + 4]) == 'a' && lower_ch(s[q + 5]) == 't'
                    && s[q + 6] == '(') {
                    size_t fs = q + 7, fe = fs;
                    while (fs < ve && is_ws(s[fs])) ++fs;
                    fe = fs;
                    char fq = 0;
                    if (fe < ve && (s[fe] == '"' || s[fe] == '\'')) {
                        fq = s[fe];
                        fs = ++fe;
                    }
                    while (fe < ve && (fq != 0 ? s[fe] != fq : s[fe] != ')')) ++fe;
                    size_t fa = fs, fb = fe;
                    while (fa < fb && is_ws(s[fa])) ++fa;
                    while (fb > fa && is_ws(s[fb - 1])) --fb;
                    size_t fl = fb - fa;
                    if (fl >= WF_FORMAT_MAX) fl = WF_FORMAT_MAX - 1;
                    for (size_t t = 0; t < fl; ++t)
                        fmt[t] = (char)lower_ch(s[fa + t]);
                    fmt[fl] = '\0';
                    u = fe + 1;
                } else {
                    u = ue + 1;
                }
            }
            if (ub > ua) {
                if (span_is_data(s + ua, ub - ua))
                    emit_data(out, family, s + ua, ub - ua, fmt, bold, italic);
                else
                    emit(out, family, s + ua, ub - ua, fmt, bold, italic);
            }
            if (out->count >= WF_MAX_REFS) return;
        }
        j = (ve < bend) ? ve + 1 : bend;
    }
}

int wf_scan(const char *css, size_t len, wf_list *out) {
    if (css == NULL || out == NULL) return -1;
    out->refs = NULL;
    out->count = 0;
    out->cap = 0;
    if (len == 0) return 0;
    size_t i = 0;
    while (i < len) {
        /* Find "@font-face" case-insensitively. */
        size_t f = len;
        for (size_t k = i; k + 10 <= len; ++k) {
            if (css[k] != '@' && css[k] != '!') continue;
            if (css[k] == '@' && k + 10 <= len
                && lower_ch(css[k + 1]) == 'f' && lower_ch(css[k + 2]) == 'o'
                && lower_ch(css[k + 3]) == 'n' && lower_ch(css[k + 4]) == 't'
                && lower_ch(css[k + 5]) == '-' && lower_ch(css[k + 6]) == 'f'
                && lower_ch(css[k + 7]) == 'a' && lower_ch(css[k + 8]) == 'c'
                && lower_ch(css[k + 9]) == 'e') {
                f = k;
                break;
            }
        }
        if (f >= len) break;
        /* Body: next '{' ... matching '}' (strings skipped, comments skipped). */
        size_t bs = f + 10;
        while (bs < len && css[bs] != '{') {
            if (css[bs] == ';') break;   /* not a block at-rule */
            ++bs;
        }
        if (bs >= len || css[bs] != '{') { i = f + 10; continue; }
        size_t be = bs + 1;
        {
            int depth = 1;
            char quote = 0;
            int comment = 0;
            while (be < len && depth > 0) {
                char c = css[be];
                if (comment) {
                    if (c == '*' && be + 1 < len && css[be + 1] == '/') {
                        comment = 0;
                        ++be;
                    }
                } else if (quote != 0) {
                    if (c == quote) quote = 0;
                } else if (c == '/' && be + 1 < len && css[be + 1] == '*') {
                    comment = 1;
                    ++be;
                } else if (c == '"' || c == '\'') {
                    quote = c;
                } else if (c == '{') {
                    ++depth;
                } else if (c == '}') {
                    --depth;
                }
                ++be;
            }
            if (depth != 0) break;   /* unclosed: nothing more to scan safely */
        }
        scan_face_block(css, bs + 1, be - 1, out);
        if (out->count >= WF_MAX_REFS) break;
        i = be;
    }
    return 0;
}
