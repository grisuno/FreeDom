#ifndef FREEDOM_VIDEO_PICK_H
#define FREEDOM_VIDEO_PICK_H

#ifdef __cplusplus
#error "freedom is pure C11"
#endif

#include "page_view.h"

/* Which video a click plays (spec/video_pick.md). Pure, no I/O; the returned
 * pointers alias the views and stay valid while they live. */

/* 1 when src is an absolute http(s) URL with something after the scheme (the only
 * kind the decoder can fetch); 0 for NULL, "[object Object]", blob:, javascript:... */
int vpk_playable(const char *src);

/* src of the first playable PV_VIDEO run or NULL. */
const char *vpk_first_video(const pv_view *v);

/* Video for a click on a live frame's box: the frame's own first video, else
 * top_video (the top document's first video, extracted by the worker's iframe
 * scan; NULL or "" when none), else NULL. */
const char *vpk_for_frame(const pv_view *frame_view, const char *top_video);

#endif /* FREEDOM_VIDEO_PICK_H */
