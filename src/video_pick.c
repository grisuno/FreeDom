#include "video_pick.h"

#include <stddef.h>
#include <strings.h>

/* Only an absolute http(s) URL names a stream the decoder can fetch; anything else a script
 * stored in src ("[object Object]", blob:, javascript:) is not a video. */
int vpk_playable(const char *src) {
    if (src == NULL) return 0;
    size_t skip = strncasecmp(src, "https://", 8) == 0 ? 8
                : strncasecmp(src, "http://", 7) == 0 ? 7 : 0;
    return skip != 0 && src[skip] != '\0';
}

const char *vpk_first_video(const pv_view *v) {
    if (v == NULL) return NULL;
    size_t n = pv_count(v);
    for (size_t i = 0; i < n; ++i) {
        const pv_run *r = pv_at(v, i);
        if (r != NULL && r->kind == PV_VIDEO && vpk_playable(r->src))
            return r->src;
    }
    return NULL;
}

const char *vpk_for_frame(const pv_view *frame_view, const char *top_video) {
    const char *own = vpk_first_video(frame_view);
    if (own != NULL) return own;
    return vpk_playable(top_video) ? top_video : NULL;
}
