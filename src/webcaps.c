/*
 * webcaps — implementation: pure per-page capability derivation.
 *
 * No I/O, no global state. Fail-closed. Reuses js_policy's predicates for the trust
 * decision; never re-implements host membership. See spec/webcaps.md.
 */

#include "webcaps.h"

wc_caps wc_safe(void) {
    wc_caps c = {0};
    return c;
}

wc_caps wc_derive(wc_input in) {
    /* Trust predicates (js_policy, the single tested source of the decision). */
    bool js_enabled = jsp_enabled(in.js_mode, in.host_in_js);
    bool present     = jsp_present_trusted(in.host_in_allow);     /* allow.conf alone */
    bool trusted     = jsp_trusted(js_enabled, in.host_in_allow); /* allow.conf AND js */

    /* Reader mode drops author presentation (it wins), without touching the user's
     * persistent toggles. */
    bool not_reader = (in.reader == 0);

    wc_caps c = {0};
    /* leak-free: user toggle OR presentation-trust, minus reader for presentation. */
    c.js     = js_enabled;
    c.css    = (in.user_css != 0 || present) && not_reader;
    c.images = (in.user_images != 0 || present) && not_reader;
    /* privacy-sensitive: the allow.conf AND js.conf double-consent. */
    c.net = c.cookies = c.persist = c.readback = c.gpu = c.sw = c.rtc = trusted;
    return c;
}

wc_caps wc_from_flags(bool js, bool css, bool images) {
    wc_caps c = {0};
    c.js     = js;
    c.css    = css;
    c.images = images;
    /* Headless: the operator's --js=on is the trust signal for network + every
     * privacy capability (orthogonal to the presentation flags). */
    c.net = c.cookies = c.persist = c.readback = c.gpu = c.sw = c.rtc = js;
    return c;
}

rdp_caps wc_render_caps(wc_caps c) {
    rdp_caps r;
    r.images = c.images;
    r.css    = c.css;
    r.js     = c.js;
    return r;
}
