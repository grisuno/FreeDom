#ifndef FREEDOM_RENDER_POLICY_H
#define FREEDOM_RENDER_POLICY_H

#include <stdbool.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * render_policy — render capabilities gate and per-image load decision.
 *
 * Pure, I/O-free policy logic (the directly auditable surface): the page loader
 * consults these before letting secure_fetch touch any image subresource.
 *
 * A remote image is a network request: it reveals the user's IP to the image
 * server and enables the classic tracking pixel. So images, author CSS, and page
 * JavaScript are opt-in capabilities, off by default (Secure/Privacy by Default).
 * When images are enabled the posture is "load all but obvious trackers": cross-
 * site is permitted, but a tracking-pixel heuristic (1x1 / tiny / zero-area) is
 * blocked. Non-https and unparseable URLs stay fatal (fail closed).
 *
 * This module performs no network I/O; it only decides. See spec/render_policy.md.
 */

/* Both declared dimensions at or below this are treated as a tracking pixel. */
#define RDP_TRACKER_MAX_DIM 2

/* Render capabilities for a page. The zero value ({0}) is the safe baseline:
 * every rich/risky capability off. The only way to opt in is to set a field to
 * true explicitly, which keeps every opt-in auditable. */
typedef struct rdp_caps {
    bool images;  /* load remote images (tracking risk) */
    bool css;     /* apply author CSS */
    bool js;      /* run page JavaScript */
} rdp_caps;

/* Decision for one image subresource. */
typedef enum rdp_img_decision {
    RDP_IMG_ALLOW = 0,        /* may be requested */
    RDP_IMG_BLOCK_DISABLED,   /* images capability is off (the default) */
    RDP_IMG_BLOCK_INVALID,    /* URL missing/unparseable, or top-level not https */
    RDP_IMG_BLOCK_SCHEME,     /* image scheme is not https */
    RDP_IMG_BLOCK_TRACKER     /* tracking-pixel heuristic */
} rdp_img_decision;

/* The safe default capabilities: images=false, css=false, js=false. */
rdp_caps rdp_caps_safe(void);

/* Tracking-pixel heuristic over an image's declared dimensions. w/h negative
 * means "unknown". Returns 1 for a tracking pixel (zero-area, or both dims
 * <= RDP_TRACKER_MAX_DIM), 0 otherwise (including unknown dimensions). */
int rdp_is_tracking_pixel(int w, int h);

/* Combined load decision for an image. declared_w/declared_h carry the image's
 * announced size (e.g. <img width height>); pass a negative value when unknown.
 * Fails closed: with images off, returns RDP_IMG_BLOCK_DISABLED without looking
 * at the URL. Re-validates scheme/host through request_policy on every call. */
rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char *top_level_url,
                                    const char *image_url,
                                    int declared_w, int declared_h);

/* Stable, short, English reason string for structured/agent-friendly output.
 * Never NULL; an unknown enum value yields "unknown". */
const char *rdp_img_reason(rdp_img_decision d);

/* Fixed warning shown when the user enables images. Never NULL or empty. */
const char *rdp_images_warning(void);

#endif /* FREEDOM_RENDER_POLICY_H */
