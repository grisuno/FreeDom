/* find_text (ft_) -- find in page over the rendered text. spec/find_text.md. */
#include "find_text.h"

#define FT_INVALID 0xFFFFFFFFu  /* decoded from a bad UTF-8 byte: equals no query code point */

/* Base letter of U+00C0..U+00FF and U+0100..U+017F; '.' = case fold only. */
static const char k_latin1[64 + 1] =
    "aaaaaa.ceeeeiiii" "dnooooo.ouuuuy.." "aaaaaa.ceeeeiiii" "dnooooo.ouuuuy.y";
static const char k_ext_a[128 + 1] =
    "aaaaaaccccccccdd" "ddeeeeeeeeeegggg" "gggghhhhiiiiiiii" "ii..jjkk.lllllll"
    "lllnnnnnnn..oooo" "oo..rrrrrrssssss" "ssttttttuuuuuuuu" "uuuuwwyyyzzzzzzs";

uint32_t ft_fold(uint32_t cp) {
    if (cp >= 'A' && cp <= 'Z') return cp + 32u;
    if (cp < 0xC0u) return cp;
    if (cp <= 0xFFu) {
        char b = k_latin1[cp - 0xC0u];
        if (b != '.') return (uint32_t)(unsigned char)b;
        return (cp <= 0xDEu && cp != 0xD7u) ? cp + 0x20u : cp;
    }
    if (cp <= 0x17Fu) {
        char b = k_ext_a[cp - 0x100u];
        if (b != '.') return (uint32_t)(unsigned char)b;
        return (cp != 0x138u && (cp & 1u) == 0u) ? cp + 1u : cp;
    }
    if (cp >= 0x391u && cp <= 0x3A9u && cp != 0x3A2u) return cp + 0x20u;
    if (cp == 0x3C2u) return 0x3C3u;                      /* final sigma */
    if (cp >= 0x410u && cp <= 0x42Fu) return cp + 0x20u;
    if (cp >= 0x400u && cp <= 0x40Fu) return cp + 0x50u;
    return cp;
}

static int is_ws(uint32_t cp) {
    return cp == ' ' || cp == '\t' || cp == '\n' || cp == '\r' || cp == '\f' || cp == '\v'
        || cp == 0xA0u || (cp >= 0x2000u && cp <= 0x200Au) || cp == 0x202Fu
        || cp == 0x205Fu || cp == 0x3000u;
}

/* Decodes one code point of s[0..n) (n >= 1). Returns the bytes consumed (>= 1). */
static size_t decode(const unsigned char *s, size_t n, uint32_t *cp) {
    unsigned char c = s[0];
    if (c < 0x80u) { *cp = c; return 1; }
    size_t len;
    uint32_t v, min;
    if (c >= 0xC2u && c <= 0xDFu)      { len = 2; v = c & 0x1Fu; min = 0x80u; }
    else if (c >= 0xE0u && c <= 0xEFu) { len = 3; v = c & 0x0Fu; min = 0x800u; }
    else if (c >= 0xF0u && c <= 0xF4u) { len = 4; v = c & 0x07u; min = 0x10000u; }
    else { *cp = FT_INVALID; return 1; }
    if (len > n) { *cp = FT_INVALID; return 1; }
    for (size_t i = 1; i < len; ++i) {
        if ((s[i] & 0xC0u) != 0x80u) { *cp = FT_INVALID; return 1; }
        v = (v << 6) | (s[i] & 0x3Fu);
    }
    if (v < min || v > 0x10FFFFu || (v >= 0xD800u && v <= 0xDFFFu)) { *cp = FT_INVALID; return 1; }
    *cp = v;
    return len;
}

size_t ft_compile(const char *q, size_t qlen, uint32_t *out, size_t cap) {
    if (q == NULL || out == NULL) return 0;
    if (cap > FT_QUERY_MAX) cap = FT_QUERY_MAX;
    size_t n = 0;
    int pending_space = 0;
    for (size_t i = 0; i < qlen && n < cap;) {
        uint32_t cp;
        i += decode((const unsigned char *)q + i, qlen - i, &cp);
        if (is_ws(cp)) { pending_space = (n > 0); continue; }
        if (pending_space) {
            if (n + 1 >= cap) break;
            out[n++] = ' ';
            pending_space = 0;
        }
        out[n++] = ft_fold(cp);
    }
    return n;
}

static size_t piece_len(const ft_piece *p) { return p->text != NULL ? p->len : 0; }

/* Moves pos onto a readable byte. 1 = a gap was crossed, 0 = none, -1 = end of text. */
static int settle(const ft_piece *p, size_t n, ft_pos *pos) {
    int gap = 0;
    while (pos->piece < n && pos->off >= piece_len(&p[pos->piece])) {
        pos->piece++;
        pos->off = 0;
        if (pos->piece < n && p[pos->piece].gap_before) gap = 1;
    }
    return pos->piece < n ? gap : -1;
}

/* Reads the code point at a settled pos; *adv gets its byte length. */
static uint32_t peek(const ft_piece *p, ft_pos pos, size_t *adv) {
    const ft_piece *pc = &p[pos.piece];
    uint32_t cp;
    *adv = decode((const unsigned char *)pc->text + pos.off, pc->len - pos.off, &cp);
    return cp;
}

/* Tries q at the settled, non-space position s; on success *end is its end. */
static int match_at(const ft_piece *p, size_t n, ft_pos s, const uint32_t *q, size_t qn,
                    ft_pos *end) {
    ft_pos cur = s;
    for (size_t i = 0; i < qn; ++i) {
        size_t adv;
        if (q[i] == ' ') {
            int any = 0;
            for (;;) {
                int g = settle(p, n, &cur);
                if (g < 0) return 0;
                if (g > 0) any = 1;
                if (!is_ws(peek(p, cur, &adv))) break;
                cur.off += adv;
                any = 1;
            }
            if (!any) return 0;
            continue;
        }
        if (settle(p, n, &cur) != 0) return 0;
        uint32_t cp = peek(p, cur, &adv);
        if (cp == FT_INVALID || ft_fold(cp) != q[i]) return 0;
        cur.off += adv;
    }
    *end = cur;
    return 1;
}

ft_status ft_search(const ft_piece *pieces, size_t n, const uint32_t *q, size_t qn,
                    ft_match *out, size_t cap, size_t *nout, int *truncated) {
    if (nout == NULL || (pieces == NULL && n > 0) || (out == NULL && cap > 0)
        || (q == NULL && qn > 0))
        return FT_EINVAL;
    if (truncated != NULL) *truncated = 0;
    *nout = 0;
    if (qn == 0 || n == 0) return FT_OK;
    ft_pos s = { 0, 0 };
    size_t found = 0;
    while (settle(pieces, n, &s) >= 0) {
        size_t adv;
        uint32_t cp = peek(pieces, s, &adv);
        ft_pos end;
        if (!is_ws(cp) && match_at(pieces, n, s, q, qn, &end)) {
            if (found == cap) {
                if (truncated != NULL) *truncated = 1;
                break;
            }
            out[found].start = s;
            out[found].end = end;
            ++found;
            s = end;
            continue;
        }
        s.off += adv;
    }
    *nout = found;
    return FT_OK;
}

size_t ft_spans(const ft_piece *pieces, size_t n, const ft_match *m, size_t nm,
                ft_span *out, size_t cap) {
    if (pieces == NULL || m == NULL || out == NULL) return 0;
    size_t k = 0;
    for (size_t i = 0; i < nm && k < cap; ++i) {
        ft_pos a = m[i].start, b = m[i].end;
        for (size_t pc = a.piece; pc <= b.piece && pc < n && k < cap; ++pc) {
            size_t len = piece_len(&pieces[pc]);
            size_t st = (pc == a.piece) ? a.off : 0;
            size_t en = (pc == b.piece) ? b.off : len;
            if (en > len) en = len;
            if (st >= en) continue;
            out[k].piece = pc;
            out[k].start = st;
            out[k].end = en;
            out[k].match = i;
            ++k;
        }
    }
    return k;
}

long ft_step(long cur, size_t n, int dir) {
    if (n == 0) return -1;
    long ln = (long)n;
    if (cur < 0 || cur >= ln) return dir < 0 ? ln - 1 : 0;
    if (dir < 0) return cur == 0 ? ln - 1 : cur - 1;
    return cur + 1 == ln ? 0 : cur + 1;
}
