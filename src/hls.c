/*
 * hls — implementation: pure m3u8 playlist parser.
 *
 * Parses VOD (single-quality) and multi-variant master HLS playlists.
 * Produces a flat list of segment URLs and their durations, or a list of
 * variant quality tiers. The caller resolves relative URLs against the
 * playlist's base URL with hls_resolve_url.
 *
 * Grammar (simplified):
 *   playlist  ::= "#EXTM3U" NL entries
 *   entries   ::= (tag | variant | segment | comment)*
 *   tag       ::= "#EXTINF:" duration "," title NL
 *               | "#EXT-X-TARGETDURATION:" seconds NL
 *               | "#EXT-X-MEDIA-SEQUENCE:" number NL
 *               | "#EXT-X-PLAYLIST-TYPE:" value NL
 *   variant   ::= "#EXT-X-STREAM-INF:" attrs NL url NL
 *   segment   ::= url NL   (following an #EXTINF tag)
 *   comment   ::= "#" ... NL  (except known tags)
 */

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L

#include "hls.h"

#include <stdlib.h>
#include <string.h>

/* Normalised integer comparison: checks if the string `s` starts with `prefix`
 * (case-sensitive). Returns 1 if yes, 0 otherwise. */
static int starts_with(const char *s, const char *prefix) {
    while (*prefix != '\0') { if (*s != *prefix) return 0; ++s; ++prefix; }
    return 1;
}

/* Finds the last occurrence of character `c` in `s` (length `n`).
 * Returns NULL if not found. Pure, no _GNU_SOURCE dependency. */
static const char *last_char(const char *s, size_t n, int c) {
    if (s == NULL || n == 0) return NULL;
    for (const char *p = s + n; p > s; --p)
        if (*(p - 1) == c) return p - 1;
    return NULL;
}

/* Extracts a named attribute value from an #EXT-X-STREAM-INF attribute string.
 * attr is the attribute name (e.g. "BANDWIDTH="); end points to end of the line.
 * Writes the parsed long into *val. Returns 1 on success, 0 otherwise. */
static int parse_attr_long(const char *attrs, const char *end,
                           const char *attr, long *val) {
    size_t alen = strlen(attr);
    const char *p = (const char *)memmem(attrs, (size_t)(end - attrs), attr, alen);
    if (p == NULL) return 0;
    p += alen;
    char *endp = NULL;
    long v = strtol(p, &endp, 10);
    if (endp == p) return 0;
    *val = v;
    return 1;
}

/* Extracts a RESOLUTION=WxH attribute. Writes w and h only (default 0). */
static void parse_attr_resolution(const char *attrs, const char *end,
                                   int *w, int *h) {
    *w = 0; *h = 0;
    const char *p = (const char *)memmem(attrs, (size_t)(end - attrs),
                                          "RESOLUTION=", 11);
    if (p == NULL) return;
    p += 11;
    char *endp = NULL;
    long vw = strtol(p, &endp, 10);
    if (endp == p || vw <= 0) return;
    *w = (int)(vw & 0x7FFFFFFF);
    if (*endp != 'x' && *endp != 'X') return;
    p = endp + 1;
    long vh = strtol(p, &endp, 10);
    if (endp == p || vh <= 0) return;
    *h = (int)(vh & 0x7FFFFFFF);
}

hls_status hls_parse(const char *text, size_t len, hls_playlist **out) {
    if (text == NULL || out == NULL) return HLS_ERR_NULL_ARG;
    *out = NULL;

    /* Must start with #EXTM3U. */
    if (len < 7 || memcmp(text, "#EXTM3U", 7) != 0)
        return HLS_ERR_PARSE;

    hls_playlist *pl = (hls_playlist *)calloc(1, sizeof *pl);
    if (pl == NULL) return HLS_ERR_OOM;

    double current_duration = 0.0;
    int have_duration = 0;
    hls_variant current_variant;
    memset(&current_variant, 0, sizeof current_variant);
    int have_variant = 0;
    const char *end = text + len;
    const char *line = text;

    while (line < end) {
        const char *nl = (const char *)memchr(line, '\n', (size_t)(end - line));
        if (nl == NULL) nl = end;
        size_t llen = (size_t)(nl - line);
        while (llen > 0 && (line[llen - 1] == '\r' || line[llen - 1] == '\n'))
            --llen;

        if (llen == 0) {
            line = nl + 1;
            continue;
        }

        if (line[0] == '#') {
            if (starts_with(line, "#EXTINF:")) {
                const char *val = line + 8;
                char *endp = NULL;
                const char *comma = (const char *)memchr(val, ',',
                    (size_t)(nl - val));
                if (comma != NULL) {
                    size_t vallen = (size_t)(comma - val);
                    char dbuf[64];
                    if (vallen < sizeof dbuf) {
                        memcpy(dbuf, val, vallen);
                        dbuf[vallen] = '\0';
                        double dur = strtod(dbuf, &endp);
                        if (endp != dbuf) {
                            current_duration = dur;
                            have_duration = 1;
                        }
                    }
                }
            } else if (starts_with(line, "#EXT-X-TARGETDURATION:")) {
                const char *val = line + 22;
                char *endp = NULL;
                double td = strtod(val, &endp);
                if (endp != val && td > 0)
                    pl->target_duration = td;
            } else if (starts_with(line, "#EXT-X-STREAM-INF:")) {
                pl->is_variant = 1;
                memset(&current_variant, 0, sizeof current_variant);
                parse_attr_long(line, (const char *)nl, "BANDWIDTH=",
                                &current_variant.bandwidth);
                parse_attr_resolution(line, (const char *)nl,
                                       &current_variant.width,
                                       &current_variant.height);
                have_variant = 1;
            }
            line = nl + 1;
            continue;
        }

        /* Non-empty, non-comment line: segment URL or variant URL. */
        if (llen > 0) {
            if (have_variant) {
                if (pl->nvariants == pl->varcap) {
                    size_t ncap = pl->varcap ? pl->varcap * 2 : 8;
                    hls_variant *grown = (hls_variant *)realloc(pl->variants,
                        ncap * sizeof *grown);
                    if (grown == NULL) { hls_playlist_free(pl); return HLS_ERR_OOM; }
                    pl->variants = grown;
                    pl->varcap = ncap;
                }
                hls_variant *v = &pl->variants[pl->nvariants++];
                if (llen == (size_t)-1) { hls_playlist_free(pl); return HLS_ERR_OOM; }
                v->url = (char *)malloc(llen + 1);
                if (v->url == NULL) { hls_playlist_free(pl); return HLS_ERR_OOM; }
                memcpy(v->url, line, llen);
                v->url[llen] = '\0';
                v->url_len = llen;
                v->bandwidth = current_variant.bandwidth;
                v->width     = current_variant.width;
                v->height    = current_variant.height;
                memset(&current_variant, 0, sizeof current_variant);
                have_variant = 0;
            } else {
                if (pl->count == pl->cap) {
                    size_t ncap = pl->cap ? pl->cap * 2 : 64;
                    hls_segment *grown = (hls_segment *)realloc(pl->segments,
                        ncap * sizeof *grown);
                    if (grown == NULL) { hls_playlist_free(pl); return HLS_ERR_OOM; }
                    pl->segments = grown;
                    pl->cap = ncap;
                }

                hls_segment *seg = &pl->segments[pl->count++];
                if (llen == (size_t)-1) { hls_playlist_free(pl); return HLS_ERR_OOM; }
                seg->url = (char *)malloc(llen + 1);
                if (seg->url == NULL) { hls_playlist_free(pl); return HLS_ERR_OOM; }
                memcpy(seg->url, line, llen);
                seg->url[llen] = '\0';
                seg->url_len = llen;
                seg->duration = have_duration ? current_duration : 0.0;
                have_duration = 0;
            }
        }

        line = nl + 1;
    }

    *out = pl;
    return HLS_OK;
}

size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h) {
    if (pl == NULL || pl->nvariants == 0) return (size_t)-1;

    size_t best = 0;
    long best_bw = 0;
    int best_fits = 0;

    for (size_t i = 0; i < pl->nvariants; ++i) {
        int fits = 1;
        if (max_w > 0 && pl->variants[i].width > max_w) fits = 0;
        if (max_h > 0 && pl->variants[i].height > max_h) fits = 0;

        if (fits && !best_fits) { best = i; best_bw = pl->variants[i].bandwidth; best_fits = 1; }
        else if (fits == best_fits && pl->variants[i].bandwidth > best_bw) {
            best = i; best_bw = pl->variants[i].bandwidth;
        }
    }

    return best;
}

size_t hls_resolve_url(const char *base_url, const char *segment_url,
                       char *resolved, size_t resolved_sz) {
    if (base_url == NULL || segment_url == NULL || resolved == NULL
        || resolved_sz == 0) return 0;

    if (strncmp(segment_url, "http://", 7) == 0
        || strncmp(segment_url, "https://", 8) == 0) {
        size_t slen = strlen(segment_url);
        if (slen < resolved_sz) {
            memcpy(resolved, segment_url, slen + 1);
            return slen;
        }
        return 0;
    }

    size_t blen = strlen(base_url);
    const char *last_slash = last_char(base_url, blen, '/');
    if (last_slash == NULL) return 0;

    size_t base_part = (size_t)(last_slash - base_url) + 1;
    size_t slen = strlen(segment_url);

    if (base_part + slen < resolved_sz) {
        memcpy(resolved, base_url, base_part);
        memcpy(resolved + base_part, segment_url, slen + 1);
        return base_part + slen;
    }
    return 0;
}

void hls_playlist_free(hls_playlist *pl) {
    if (pl == NULL) return;
    for (size_t i = 0; i < pl->count; ++i)
        free(pl->segments[i].url);
    free(pl->segments);
    for (size_t i = 0; i < pl->nvariants; ++i)
        free(pl->variants[i].url);
    free(pl->variants);
    free(pl);
}
