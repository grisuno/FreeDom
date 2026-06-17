/*
 * render_policy — implementation: pure, I/O-free render-capabilities gate and
 * per-image load decision.
 *
 * Secure/Privacy by Default: images, author CSS, and page JS are opt-in; the
 * zero-valued rdp_caps is the safe baseline. When images are enabled the posture
 * is "load all but obvious trackers": cross-site is permitted (the deliberate
 * relaxation versus request_policy), but a tracking-pixel heuristic and any
 * non-https/unparseable URL are blocked. No network, no allocation, no state.
 */

#include "render_policy.h"

#include "request_policy.h"

rdp_caps rdp_caps_safe(void) {
    rdp_caps c = {0};  /* images=false, css=false, js=false */
    return c;
}

int rdp_is_tracking_pixel(int w, int h) {
    if (w < 0 || h < 0) return 0;          /* unknown: not classifiable */
    if (w == 0 || h == 0) return 1;        /* zero-area beacon */
    return (w <= RDP_TRACKER_MAX_DIM && h <= RDP_TRACKER_MAX_DIM) ? 1 : 0;
}

rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char *top_level_url,
                                    const char *image_url,
                                    int declared_w, int declared_h) {
    /* The capability gate short-circuits: with images off, nothing about the
     * image matters and the URL is not consulted. */
    if (!caps.images) return RDP_IMG_BLOCK_DISABLED;

    /* Zero Trust: revalidate scheme + host on every image through request_policy.
     * Cross-site (RP_BLOCK_THIRD_PARTY) is allowed for opt-in images; only an
     * invalid URL or a non-https scheme is fatal. */
    switch (rp_evaluate(top_level_url, image_url)) {
        case RP_BLOCK_INVALID: return RDP_IMG_BLOCK_INVALID;
        case RP_BLOCK_SCHEME:  return RDP_IMG_BLOCK_SCHEME;
        case RP_ALLOW:
        case RP_BLOCK_THIRD_PARTY:
            break;  /* origin permitted for images; fall through to tracker check */
    }

    if (rdp_is_tracking_pixel(declared_w, declared_h)) return RDP_IMG_BLOCK_TRACKER;
    return RDP_IMG_ALLOW;
}

const char *rdp_img_reason(rdp_img_decision d) {
    switch (d) {
        case RDP_IMG_ALLOW:          return "allow";
        case RDP_IMG_BLOCK_DISABLED: return "images-disabled";
        case RDP_IMG_BLOCK_INVALID:  return "invalid-url";
        case RDP_IMG_BLOCK_SCHEME:   return "non-https-scheme";
        case RDP_IMG_BLOCK_TRACKER:  return "tracking-pixel";
    }
    return "unknown";
}

const char *rdp_images_warning(void) {
    return "Loading remote images can reveal your IP address and let sites track "
           "you (tracking pixels). Images are off by default.";
}
