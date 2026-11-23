/* doc_title -- the <title> of a received document that has not been laid out yet.
 * Contract and rationale: spec/doc_title.md. */
#include "doc_title.h"

#include <stdint.h>
#include <string.h>

#define DT_REPLACEMENT 0xFFFDu
#define DT_MAX_CP      0x10FFFFu
#define DT_REF_DIGITS  8   /* longer numeric references are clamped past U+10FFFF anyway */

typedef struct dt_writer {
    char  *out;
    size_t cap, n;
    int    pending_space;  /* a collapsed whitespace run waits for the next visible char */
    int    full;
} dt_writer;

static int is_ascii_space(unsigned c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f';
}

static int is_bidi_control(uint32_t cp) {
    return (cp >= 0x202Au && cp <= 0x202Eu) || (cp >= 0x2066u && cp <= 0x2069u) ||
           cp == 0x200Eu || cp == 0x200Fu;
}

static unsigned lower(unsigned c) { return (c >= 'A' && c <= 'Z') ? c + 32u : c; }

/* Appends one code point; whitespace and controls collapse, bidi controls vanish, and a
 * character that does not fit whole ends the output (never half a sequence). */
static void put_cp(dt_writer *w, uint32_t cp) {
    if (w->full) return;
    if (cp == 0 || (cp >= 0xD800u && cp <= 0xDFFFu) || cp > DT_MAX_CP) cp = DT_REPLACEMENT;
    if (is_bidi_control(cp)) return;
    if (cp < 0x20u || cp == 0x7Fu || (cp >= 0x80u && cp <= 0x9Fu)) {
        if (w->n > 0) w->pending_space = 1;
        return;
    }
    unsigned char b[4];
    size_t k;
    if (cp < 0x80u) { b[0] = (unsigned char)cp; k = 1; }
    else if (cp < 0x800u) {
        b[0] = (unsigned char)(0xC0u | (cp >> 6)); b[1] = (unsigned char)(0x80u | (cp & 0x3Fu)); k = 2;
    } else if (cp < 0x10000u) {
        b[0] = (unsigned char)(0xE0u | (cp >> 12)); b[1] = (unsigned char)(0x80u | ((cp >> 6) & 0x3Fu));
        b[2] = (unsigned char)(0x80u | (cp & 0x3Fu)); k = 3;
    } else {
        b[0] = (unsigned char)(0xF0u | (cp >> 18)); b[1] = (unsigned char)(0x80u | ((cp >> 12) & 0x3Fu));
        b[2] = (unsigned char)(0x80u | ((cp >> 6) & 0x3Fu)); b[3] = (unsigned char)(0x80u | (cp & 0x3Fu));
        k = 4;
    }
    size_t need = k + (w->pending_space ? 1u : 0u);
    if (w->n + need >= w->cap) { w->full = 1; return; }
    if (w->pending_space) w->out[w->n++] = ' ';
    w->pending_space = 0;
    memcpy(w->out + w->n, b, k);
    w->n += k;
}

/* Decodes one UTF-8 sequence at s[0..n); an invalid one is U+FFFD over one byte. */
static size_t utf8_next(const unsigned char *s, size_t n, uint32_t *cp) {
    unsigned c = s[0];
    if (c < 0x80u) { *cp = c; return 1; }
    size_t k;
    uint32_t v, min;
    if (c >= 0xC2u && c <= 0xDFu)      { k = 2; v = c & 0x1Fu; min = 0x80u; }
    else if (c >= 0xE0u && c <= 0xEFu) { k = 3; v = c & 0x0Fu; min = 0x800u; }
    else if (c >= 0xF0u && c <= 0xF4u) { k = 4; v = c & 0x07u; min = 0x10000u; }
    else { *cp = DT_REPLACEMENT; return 1; }
    if (k > n) { *cp = DT_REPLACEMENT; return 1; }
    for (size_t i = 1; i < k; ++i) {
        if ((s[i] & 0xC0u) != 0x80u) { *cp = DT_REPLACEMENT; return 1; }
        v = (v << 6) | (s[i] & 0x3Fu);
    }
    if (v < min || v > DT_MAX_CP || (v >= 0xD800u && v <= 0xDFFFu)) { *cp = DT_REPLACEMENT; return 1; }
    *cp = v;
    return k;
}

/* A character reference at s[0] == '&'. Returns the bytes consumed (0 = not a
 * reference: the '&' is literal) and the code point. */
static size_t char_ref(const unsigned char *s, size_t n, uint32_t *cp) {
    static const struct { const char *name; uint32_t cp; } named[] = {
        { "amp;", '&' }, { "lt;", '<' }, { "gt;", '>' }, { "quot;", '"' },
        { "apos;", '\'' }, { "nbsp;", 0xA0u },
    };
    if (n >= 2 && s[1] == '#') {
        size_t i = 2;
        int hex = (i < n && lower(s[i]) == 'x');
        if (hex) ++i;
        size_t d0 = i;
        uint32_t v = 0;
        while (i < n) {
            unsigned c = lower(s[i]), dv;
            if (c >= '0' && c <= '9') dv = c - '0';
            else if (hex && c >= 'a' && c <= 'f') dv = c - 'a' + 10u;
            else break;
            if (i - d0 < DT_REF_DIGITS) v = v * (hex ? 16u : 10u) + dv;
            else v = DT_MAX_CP + 1u;
            ++i;
        }
        if (i == d0) return 0;
        if (i < n && s[i] == ';') ++i;
        *cp = v;
        return i;
    }
    for (size_t k = 0; k < sizeof named / sizeof named[0]; ++k) {
        size_t l = strlen(named[k].name);
        if (1 + l <= n && memcmp(s + 1, named[k].name, l) == 0) { *cp = named[k].cp; return 1 + l; }
    }
    return 0;
}

/* Does s[i..n) start with `</name` followed by a tag-name terminator (or the end)? */
static int at_end_tag(const unsigned char *s, size_t i, size_t n, const char *name) {
    size_t l = strlen(name);
    if (i + 2 + l > n || s[i] != '<' || s[i + 1] != '/') return 0;
    for (size_t k = 0; k < l; ++k)
        if (lower(s[i + 2 + k]) != (unsigned char)name[k]) return 0;
    size_t e = i + 2 + l;
    return e == n || is_ascii_space(s[e]) || s[e] == '>' || s[e] == '/';
}

static size_t find_end_tag(const unsigned char *s, size_t i, size_t n, const char *name) {
    for (; i < n; ++i)
        if (s[i] == '<' && at_end_tag(s, i, n, name)) return i;
    return n;
}

int dt_scan(const char *html, size_t len, char *out, size_t cap) {
    if (out == NULL || cap == 0) return 0;
    out[0] = '\0';
    if (html == NULL) return 0;
    static const char *const raw_text[] = { "script", "style", "template", "textarea", "noscript" };
    const unsigned char *s = (const unsigned char *)html;
    size_t n = (len < DT_SCAN_MAX) ? len : DT_SCAN_MAX;
    size_t i = 0;
    while (i < n) {
        if (s[i] != '<') { ++i; continue; }
        if (i + 4 <= n && memcmp(s + i, "<!--", 4) == 0) {
            size_t j = i + 4;
            while (j + 3 <= n && memcmp(s + j, "-->", 3) != 0) ++j;
            i = (j + 3 <= n) ? j + 3 : n;
            continue;
        }
        size_t j = i + 1, ns = j;
        while (j < n && j - ns < 16 && ((s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z') ||
                                        (s[j] >= '0' && s[j] <= '9')))
            ++j;
        size_t nl = j - ns;
        if (nl == 0 || (j < n && !is_ascii_space(s[j]) && s[j] != '>' && s[j] != '/')) { i = i + 1; continue; }
        char name[17];
        for (size_t k = 0; k < nl; ++k) name[k] = (char)lower(s[ns + k]);
        name[nl] = '\0';
        while (j < n && s[j] != '>') ++j;          /* end of the start tag */
        size_t body = (j < n) ? j + 1 : n;
        if (strcmp(name, "title") == 0) {
            size_t end = find_end_tag(s, body, n, "title");
            dt_writer w = { out, cap, 0, 0, 0 };
            for (size_t p = body; p < end && !w.full; ) {
                uint32_t cp;
                size_t used = 0;
                if (s[p] == '&') used = char_ref(s + p, end - p, &cp);
                if (used == 0) used = utf8_next(s + p, end - p, &cp);
                if (is_ascii_space(cp)) { if (w.n > 0) w.pending_space = 1; }
                else put_cp(&w, cp);
                p += used;
            }
            out[w.n] = '\0';
            return w.n > 0;
        }
        i = body;
        for (size_t k = 0; k < sizeof raw_text / sizeof raw_text[0]; ++k)
            if (strcmp(name, raw_text[k]) == 0) { i = find_end_tag(s, body, n, raw_text[k]); break; }
        if (i == body) continue;
        if (i < n) ++i;   /* past the '<' of the end tag; its name is skipped as a tag */
    }
    return 0;
}
