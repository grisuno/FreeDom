/*
 * hls — implementation: pure m3u8 playlist parser.
 *
 * Parses VOD (single-quality) HLS playlists. Produces a flat list of segment
 * URLs and their durations. The caller resolves relative URLs against the
 * playlist's base URL with hls_resolve_url.
 *
 * Grammar (simplified):
 *   playlist  ::= "#EXTM3U" NL entries
 *   entries   ::= (tag | segment | comment)*
 *   tag       ::= "#EXTINF:" duration "," title NL
 *               | "#EXT-X-TARGETDURATION:" seconds NL
 *               | "#EXT-X-MEDIA-SEQUENCE:" number NL
 *               | "#EXT-X-STREAM-INF:" ... NL  → is_variant = 1
 *   segment   ::= url NL   (following an #EXTINF tag)
 *   comment   ::= "#" ... NL  (except known tags)
 */

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
    const char *end = text + len;
    const char *line = text;

    while (line < end) {
        /* Find end of line. */
        const char *nl = (const char *)memchr(line, '\n', (size_t)(end - line));
        if (nl == NULL) nl = end;
        size_t llen = (size_t)(nl - line);
        /* Strip trailing \r (Windows line endings). */
        while (llen > 0 && (line[llen - 1] == '\r' || line[llen - 1] == '\n'))
            --llen;

        if (llen == 0) {
            /* Empty line. */
            line = nl + 1;
            continue;
        }

        /* Handle tags (lines starting with #). */
        if (line[0] == '#') {
            if (starts_with(line, "#EXTINF:")) {
                /* #EXTINF:<duration>,[<title>] */
                const char *val = line + 8; /* after "#EXTINF:" */
                char *endp = NULL;
                double dur = 0.0;
                /* Parse float duration, stop at comma. */
                const char *comma = (const char *)memchr(val, ',',
                    (size_t)(nl - val));
                if (comma != NULL) {
                    size_t vallen = (size_t)(comma - val);
                    char dbuf[64];
                    if (vallen < sizeof dbuf) {
                        memcpy(dbuf, val, vallen);
                        dbuf[vallen] = '\0';
                        dur = strtod(dbuf, &endp);
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
            }
            /* All other tags and comments are ignored. */
            line = nl + 1;
            continue;
        }

        /* Non-empty, non-comment line: should be a segment URL. */
        if (llen > 0) {
            if (pl->count == pl->cap) {
                size_t ncap = pl->cap ? pl->cap * 2 : 64;
                hls_segment *grown = (hls_segment *)realloc(pl->segments,
                    ncap * sizeof *grown);
                if (grown == NULL) { hls_playlist_free(pl); return HLS_ERR_OOM; }
                pl->segments = grown;
                pl->cap = ncap;
            }

            hls_segment *seg = &pl->segments[pl->count++];
            seg->url = (char *)malloc(llen + 1);
            if (seg->url == NULL) { hls_playlist_free(pl); return HLS_ERR_OOM; }
            memcpy(seg->url, line, llen);
            seg->url[llen] = '\0';
            seg->url_len = llen;
            seg->duration = have_duration ? current_duration : 0.0;
            have_duration = 0;
        }

        line = nl + 1;
    }

    *out = pl;
    return HLS_OK;
}

size_t hls_resolve_url(const char *base_url, const char *segment_url,
                       char *resolved, size_t resolved_sz) {
    if (base_url == NULL || segment_url == NULL || resolved == NULL
        || resolved_sz == 0) return 0;

    /* If segment URL is absolute (starts with http:// or https://), use as-is. */
    if (strncmp(segment_url, "http://", 7) == 0
        || strncmp(segment_url, "https://", 8) == 0) {
        size_t slen = strlen(segment_url);
        if (slen < resolved_sz) {
            memcpy(resolved, segment_url, slen + 1);
            return slen;
        }
        return 0;
    }

    /* Relative URL: resolve against the base URL (everything up to the last '/'). */
    size_t blen = strlen(base_url);
    const char *last_slash = last_char(base_url, blen, '/');
    if (last_slash == NULL) return 0;

    size_t base_part = (size_t)(last_slash - base_url) + 1; /* include the '/' */
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
    free(pl);
}
