#include "text_case.h"

#include "css.h"

/* Latin Extended-A and the Cyrillic historic block pair letters on adjacent code
 * points, uppercase first. Returns the parity (1 odd, 0 even) of the LOWERCASE
 * member in cp's pair range, -1 outside every pair range. */
static int pair_parity(uint32_t cp) {
    if ((cp >= 0x0100 && cp <= 0x012F) || (cp >= 0x0132 && cp <= 0x0137) ||
        (cp >= 0x014A && cp <= 0x0177) || (cp >= 0x0460 && cp <= 0x0481) ||
        (cp >= 0x048A && cp <= 0x04BF))
        return 1;
    if ((cp >= 0x0139 && cp <= 0x0148) || (cp >= 0x0179 && cp <= 0x017E))
        return 0;
    return -1;
}

uint32_t tc_upper(uint32_t cp) {
    if (cp >= 'a' && cp <= 'z') return cp - 0x20;
    if (cp < 0x80) return cp;
    if (cp >= 0x00E0 && cp <= 0x00FE && cp != 0x00F7) return cp - 0x20;
    if (cp == 0x00FF) return 0x0178;
    if (cp == 0x00B5) return 0x039C;
    int par = pair_parity(cp);
    if (par >= 0) return ((cp & 1u) == (uint32_t)par) ? cp - 1 : cp;
    if (cp >= 0x03B1 && cp <= 0x03CB && cp != 0x03C2) return cp - 0x20;
    if (cp == 0x03C2) return 0x03A3;
    if (cp == 0x03AC) return 0x0386;
    if (cp >= 0x03AD && cp <= 0x03AF) return cp - 0x25;
    if (cp == 0x03CC) return 0x038C;
    if (cp == 0x03CD || cp == 0x03CE) return cp - 0x3F;
    if (cp >= 0x0430 && cp <= 0x044F) return cp - 0x20;
    if (cp >= 0x0450 && cp <= 0x045F) return cp - 0x50;
    return cp;
}

uint32_t tc_lower(uint32_t cp) {
    if (cp >= 'A' && cp <= 'Z') return cp + 0x20;
    if (cp < 0x80) return cp;
    if (cp >= 0x00C0 && cp <= 0x00DE && cp != 0x00D7) return cp + 0x20;
    if (cp == 0x0178) return 0x00FF;
    int par = pair_parity(cp);
    if (par >= 0) return ((cp & 1u) != (uint32_t)par) ? cp + 1 : cp;
    if (cp >= 0x0391 && cp <= 0x03AB && cp != 0x03A2) return cp + 0x20;
    if (cp == 0x0386) return 0x03AC;
    if (cp >= 0x0388 && cp <= 0x038A) return cp + 0x25;
    if (cp == 0x038C) return 0x03CC;
    if (cp == 0x038E || cp == 0x038F) return cp + 0x3F;
    if (cp >= 0x0410 && cp <= 0x042F) return cp + 0x20;
    if (cp >= 0x0400 && cp <= 0x040F) return cp + 0x50;
    return cp;
}

int tc_is_lower(uint32_t cp) {
    return tc_upper(cp) != cp;
}

/* Decodes one UTF-8 code point of s[0,n) into *cp. Returns its byte length, or 0
 * for an invalid/truncated sequence (the caller copies that byte untouched). Only
 * 1-3 byte forms matter here: every mapped letter is in the BMP below U+0500. */
static size_t utf8_decode(const unsigned char *s, size_t n, uint32_t *cp) {
    if (n == 0) return 0;
    unsigned c = s[0];
    if (c < 0x80) { *cp = c; return 1; }
    if ((c >> 5) == 0x6) {
        if (n < 2 || (s[1] & 0xC0) != 0x80) return 0;
        *cp = ((c & 0x1Fu) << 6) | (s[1] & 0x3Fu);
        return (*cp >= 0x80) ? 2 : 0;
    }
    if ((c >> 4) == 0xE) {
        if (n < 3 || (s[1] & 0xC0) != 0x80 || (s[2] & 0xC0) != 0x80) return 0;
        *cp = ((c & 0x0Fu) << 12) | ((s[1] & 0x3Fu) << 6) | (s[2] & 0x3Fu);
        return (*cp >= 0x800) ? 3 : 0;
    }
    return 0;
}

/* Writes cp (known to need exactly len bytes) into out. */
static void utf8_put(uint32_t cp, size_t len, unsigned char *out) {
    if (len == 1) { out[0] = (unsigned char)cp; return; }
    if (len == 2) {
        out[0] = (unsigned char)(0xC0 | (cp >> 6));
        out[1] = (unsigned char)(0x80 | (cp & 0x3F));
        return;
    }
    out[0] = (unsigned char)(0xE0 | (cp >> 12));
    out[1] = (unsigned char)(0x80 | ((cp >> 6) & 0x3F));
    out[2] = (unsigned char)(0x80 | (cp & 0x3F));
}

static size_t utf8_len_of(uint32_t cp) {
    return (cp < 0x80) ? 1 : (cp < 0x800) ? 2 : (cp < 0x10000) ? 3 : 4;
}

size_t tc_transform(const char *s, size_t n, int transform, int word_start,
                    char *out, size_t cap) {
    if (s == NULL || out == NULL || cap < n) return 0;
    const unsigned char *u = (const unsigned char *)s;
    unsigned char *o = (unsigned char *)out;
    int at_word = word_start;
    for (size_t i = 0; i < n; ) {
        uint32_t cp = 0;
        size_t l = utf8_decode(u + i, n - i, &cp);
        if (l == 0) { o[i] = u[i]; ++i; at_word = 0; continue; }
        uint32_t m = cp;
        if (transform == CSS_TT_UPPERCASE) m = tc_upper(cp);
        else if (transform == CSS_TT_LOWERCASE) m = tc_lower(cp);
        else if (transform == CSS_TT_CAPITALIZE && at_word) m = tc_upper(cp);
        if (utf8_len_of(m) != l) m = cp;
        utf8_put(m, l, o + i);
        at_word = (cp == ' ' || cp == '\t' || cp == '\n');
        i += l;
    }
    return n;
}

size_t tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap) {
    if (s == NULL || out == NULL || n == 0 || cap == 0) return 0;
    const unsigned char *u = (const unsigned char *)s;
    size_t count = 0;
    for (size_t i = 0; i < n; ) {
        uint32_t cp = 0;
        size_t l = utf8_decode(u + i, n - i, &cp);
        int low = 0;
        if (l == 0) l = 1;
        else low = tc_is_lower(cp);
        if (count > 0 && (out[count - 1].lowered == low || count == cap)) {
            out[count - 1].len += l;
        } else {
            out[count].off = i;
            out[count].len = l;
            out[count].lowered = low;
            ++count;
        }
        i += l;
    }
    return count;
}
