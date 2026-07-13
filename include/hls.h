#ifndef FREEDOM_HLS_H
#define FREEDOM_HLS_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * hls — pure HLS playlist (.m3u8) parser.
 *
 * Parses a simple VOD (single-quality) m3u8 playlist into a list of segment
 * URLs. No I/O, no network: takes the playlist text, returns segment info.
 * URLs are returned as they appear in the playlist (may be relative to the
 * playlist's base URL).
 *
 * See spec/hls.md for the full contract.
 */

typedef enum hls_status {
    HLS_OK = 0,
    HLS_ERR_NULL_ARG,
    HLS_ERR_PARSE,      /* not a valid m3u8 playlist */
    HLS_ERR_OOM
} hls_status;

/* One segment in the playlist. */
typedef struct hls_segment {
    char  *url;          /* owned; the raw segment URL as written in the playlist */
    size_t url_len;
    double duration;     /* segment duration in seconds (from #EXTINF) */
} hls_segment;

/* Parsed playlist. */
typedef struct hls_playlist {
    hls_segment *segments;
    size_t       count;
    size_t       cap;
    double       target_duration; /* from #EXT-X-TARGETDURATION, or 0 if absent */
    int          is_variant;      /* nonzero if this is a multi-variant playlist */
} hls_playlist;

/* Parses a plain-text m3u8 playlist. playlist_text must be NUL-terminated
 * (len is strlen). On HLS_OK, *out is allocated and must be freed with
 * hls_playlist_free. playlist_text is not modified. */
hls_status hls_parse(const char *playlist_text, size_t len, hls_playlist **out);

/* Resolves a (possibly relative) segment URL against the playlist base URL.
 * Writes the absolute URL into resolved (bounded by resolved_sz). Returns the
 * written length, or 0 on failure. */
size_t hls_resolve_url(const char *base_url, const char *segment_url,
                       char *resolved, size_t resolved_sz);

/* Frees a parsed playlist. Safe on NULL. */
void hls_playlist_free(hls_playlist *pl);

#endif /* FREEDOM_HLS_H */
