# video_pipeline — jkanime.net iframe→video extraction

## Scope

Extends the existing `js_dom` video extraction pipeline to handle the specific
patterns used by jkanime.net and similar anime-streaming sites (iframe-based
multi-server video delivery with HLS/MP4 fallback).

## Out of scope

- DASH (.mpd) parsing (not used by jkanime)
- MSE/EME (no streaming protocol beyond HLS)
- Video player UI (server selector tabs, quality switching)
- Any network fetch the parent does not gate (worker never touches a socket)

## API changes

### `jd_opaque` acquires `iframe_track`

```c
#define JD_IFRAME_TRACK_MAX 16

typedef struct jd_iframe_track {
    dom_node_id processed[JD_IFRAME_TRACK_MAX];
    size_t      nprocessed;
} jd_iframe_track;

typedef struct jd_opaque {
    dom_index       *idx;
    jd_click_state  *click;
    jd_iframe_track  iframe_track;
} jd_opaque;
```

The static `processed[]`/`nprocessed` inside `jd_process_iframes` moves to
`jd_opaque.iframe_track`, making it per-context and free of cross-page leaks.
The caller zero-initialises `jd_opaque` (already required), so `nprocessed`
starts at 0.

### `scan_video_url` replaces `scan_m3u8_url`

```c
/* Scans `body` for .m3u8 or .mp4 video URLs. Returns 1 if found, 0 otherwise.
 * Prefers .m3u8 (HLS) over .mp4 (progressive). The output URL is the full
 * URL string including the extension. Fail-closed: no match ⇒ out[0] = 0. */
static int scan_video_url(const char *body, size_t blen,
                           char *out, size_t outsz);
```

## Pattern matching

### `try_create_iframe_from_script` — jkanime patterns

The C-level extractor runs BEFORE JS execution. It must handle:

| Pattern | Example | Status |
|---------|---------|--------|
| `video[N] = '<iframe src="URL">...'` | `video[1] = '<iframe src="https://...">'` | Existing, works |
| `video_data = '<iframe src="URL">...'` | `video_data = '<iframe src="...">'` | Existing, works |
| `video_data = video[N]` | `var video_data = video[1];` | **NEW** — variable-to-variable |
| `video_data = video_data.replace('src="/', ...)` | Relative→absolute conversion | **NEW** — extract URL before replace |

The variable-to-variable pattern (`video_data = video[N]`) is handled by a
second pass: if the `video_data` pass finds a variable reference (not a string
literal), the extractor falls back to the `video[N]` scan result (already
available), which has the same URL.

### `jd_process_iframes` — multi-server fallback

When the first iframe's fetch fails (fetch error, 404, no .m3u8 found), the
processor tries the NEXT iframe from the DOM (jkanime has 5 native servers).
Up to `JD_IFRAME_TRACK_MAX` iframes can be tracked per-context.

## BDD scenarios

```
Scenario: jkanime video array with 5 servers
  Given a script containing:
    video[0] = '<iframe src="https://jk/jkplayer/um?e=A">'
    video[1] = '<iframe src="https://jk/jkplayer/umv?e=B">'
    video[2] = '<iframe src="https://jk/jkplayer/um?e=C">'
    if(video[1] !== undefined) { var video_data = video[1]; }
  When jd_video_from_scripts scans this script
  Then it extracts video[1]'s URL (priority over video[0])
    AND creates an <iframe> with src="https://jk/jkplayer/umv?e=B"

Scenario: video_data is a variable reference, not a string
  Given a script where video_data is assigned from video[1]
    var video_data = video[1];
  When try_create_iframe_from_script processes it
  Then the video_data pass finds no string literal
    AND the video[N] fallback extracts video[1]'s iframe URL
    AND the iframe is created

Scenario: jkplayer response with .m3u8 URL
  Given an iframe response body containing:
    <source src="https://cdn.example.com/hls/abc/index.m3u8" type="application/x-mpegURL">
  When scan_video_url scans the body
  Then it extracts "https://cdn.example.com/hls/abc/index.m3u8"
    AND status is 1 (found, HLS)

Scenario: jkplayer response with progressive .mp4 (no .m3u8)
  Given an iframe response body containing:
    <source src="https://cdn.example.com/video.mp4" type="video/mp4">
  When scan_video_url scans the body
  Then .m3u8 scan returns 0
    AND .mp4 scan finds "https://cdn.example.com/video.mp4"
    AND status is 1 (found, MP4)

Scenario: jkplayer response with no video URL
  Given an iframe response body with no .m3u8 or .mp4
  When scan_video_url scans the body
  Then status is 0 (not found)
    AND no <video> element is created

Scenario: iframe fetch fails (404/timeout)
  Given an iframe whose fetch returns status 404
  When jd_process_iframes processes it
  Then the fetch error is logged to Freebug
    AND the next iframe in the DOM is tried (if any)
    AND the page continues rendering (fail-open)

Scenario: multiple video iframes, first fails, second succeeds
  Given two iframes: first returns 404, second returns .m3u8
  When jd_process_iframes processes them
  Then the first is skipped (fetch failed)
    AND the second is fetched and its .m3u8 is extracted
    AND a <video> element is created

Scenario: iframe state does not leak between page loads
  Given two consecutive page loads, each with different iframes
  When jd_process_iframes runs on the second page
  Then the second page's iframes are processed (not skipped from first page)
```

## Error table

| Condition | Behaviour |
|-----------|-----------|
| NULL ctx or idx | No-op (fail-closed) |
| fetch fn returns error | Skip iframe, try next; Freebug [warn] |
| No .m3u8 or .mp4 in iframe body | Skip iframe, try next |
| DOM has no iframes | No-op |
| `> JD_IFRAME_TRACK_MAX` iframes per page | Extra iframes ignored (anti-DoS) |
| Body is oversized (>16 MiB) | fetch callback caps via TAB_MAX_SUBRESOURCE |

## Security posture

- All URL resolution within `jd_video_from_scripts` is pure C string handling
  (no JS evaluation). The hostile iframe src is validated and resolved with
  `resolve_video_url` (same trusted code as existing `hp_extract_script_src`).
- The iframe content is fetched through the parent-gated `TAG_SUBREQ` channel
  (`child_fetch`), which re-applies the full network policy (hostblock, realm,
  TLS-PQ). The worker NEVER opens a socket.
- `scan_video_url` scans a raw string buffer for `.m3u8`/`.mp4` — no regex,
  no JS eval, no remote execution. Bounded by `TAB_MAX_SUBRESOURCE`.
- The `jd_iframe_track` lives in `jd_opaque` on the caller's stack — out of
  reach of page JS, no static state to leak between contexts.
