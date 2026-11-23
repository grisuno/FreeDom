#ifndef FREEDOM_HLS_H
#define FREEDOM_HLS_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * hls — pure HLS playlist (.m3u8) parser.
 *
 * Parses both simple VOD (single-quality) and multi-variant (master) m3u8
 * playlists. No I/O, no network: takes the playlist text, returns segment
 * or variant info. URLs are returned as they appear in the playlist (may be
 * relative to the playlist's base URL).
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

/* One variant (quality tier) in a multi-variant (master) playlist. */
typedef struct hls_variant {
    char  *url;          /* owned; the variant playlist URL */
    size_t url_len;
    long   bandwidth;    /* BANDWIDTH from #EXT-X-STREAM-INF, or 0 if absent */
    int    width;        /* RESOLUTION width, or 0 */
    int    height;       /* RESOLUTION height, or 0 */
} hls_variant;

/* Parsed playlist. */
typedef struct hls_playlist {
    hls_segment *segments;
    size_t       count;
    size_t       cap;
    hls_variant *variants;       /* multi-variant: list of quality tiers */
    size_t       nvariants;
    size_t       varcap;
    double       target_duration; /* from #EXT-X-TARGETDURATION, or 0 if absent */
    int          is_variant;      /* nonzero if this is a multi-variant playlist */
} hls_playlist;

/* Parses a plain-text m3u8 playlist. playlist_text must be NUL-terminated
 * (len is strlen). On HLS_OK, *out is allocated and must be freed with
 * hls_playlist_free. playlist_text is not modified. */
hls_status hls_parse(const char *playlist_text, size_t len, hls_playlist **out);

/* Selects the best variant from a multi-variant playlist. Returns the index
 * of the chosen variant, or (size_t)-1 on failure (empty variant list).
 * Prefers the variant with the highest bandwidth that fits within `max_w` x
 * `max_h` (0 = no resolution limit). Pure, no I/O. */
size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h);

/* Resolves a (possibly relative) segment URL against the playlist base URL.
 * Writes the absolute URL into resolved (bounded by resolved_sz). Returns the
 * written length, or 0 on failure. */
size_t hls_resolve_url(const char *base_url, const char *segment_url,
                       char *resolved, size_t resolved_sz);

/* Frees a parsed playlist. Safe on NULL. */
void hls_playlist_free(hls_playlist *pl);

/* Offset where the media starts inside a downloaded segment, or -1 when it is not
 * media (non-2xx status, HTML/text error body, empty). Recognises MPEG-TS (also
 * behind a fake image prefix, probed in the first 4 KiB), ISO BMFF and ID3 audio.
 * A rejected body must never reach the decoder (spec/hls.md). */
long hls_segment_payload(long http_code, const unsigned char *body, size_t len);

/* Mirrors the feeder may retry a rejected segment on (spec/hls.md). */
#define HLS_MAX_MIRRORS 3

/* seg_abs (an absolute https segment URL) with its host replaced by the k-th distinct
 * other host that the playlist's own absolute https URLs use under the same parent
 * domain (everything after the first label). Writes NUL-terminated into out and
 * returns the length, or 0 when there is no k-th mirror or it does not fit. */
size_t hls_mirror_url(const hls_playlist *pl, const char *seg_abs, size_t k,
                      char *out, size_t outsz);

#endif /* FREEDOM_HLS_H */
