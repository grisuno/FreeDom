#ifndef FREEDOM_WEBCAPS_H
#define FREEDOM_WEBCAPS_H

#include <stdbool.h>

#include "js_policy.h"
#include "render_policy.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * webcaps — unified per-page capability model (M0.1).
 *
 * Pure, I/O-free, no global state. Derives the COMPLETE capability table of a page
 * from a host's trust signals, so every load site (GUI + headless) and every future
 * modernization milestone reads ONE struct instead of recomputing an inline mix of
 * trusted/present_trusted/css_grant/net flags.
 *
 * Gating doctrine (owner, 2026-07-15):
 *   - leak-free (js/css/images) => granted by the user toggle OR allow.conf
 *     presentation-trust; applied to every site.
 *   - privacy-sensitive (net/cookies/persist/readback/gpu/sw/rtc) => require
 *     allow.conf AND js.conf (the jsp_trusted double-consent).
 * The confined worker keeps all its structural invariants regardless: "trusted"
 * opens WHICH capability is installed, never WHO touches the socket (the parent
 * re-applies the full network policy on every subrequest).
 *
 * This module reuses js_policy's predicates (jsp_enabled/jsp_trusted/
 * jsp_present_trusted); it never re-implements host membership (that is hostblock).
 * See spec/webcaps.md.
 */

/* Full capability table for one page. The zero value ({0}) is the safe baseline:
 * every capability off. Only an explicit derivation turns a field on, keeping every
 * opt-in auditable. */
typedef struct wc_caps {
    /* leak-free (global): granted by user toggle or allow.conf presentation-trust. */
    bool js;        /* run page JavaScript */
    bool css;       /* apply author CSS + fetch external <link rel=stylesheet> */
    bool images;    /* load/render images */
    /* privacy-sensitive (allow.conf AND js.conf, i.e. jsp_trusted). */
    bool net;       /* real XHR/fetch + external <script src> (parent-gated) */
    bool cookies;   /* seed/foldback ephemeral session cookies */
    bool persist;   /* persistent storage/IndexedDB/cookies-to-disk (Fase 3) */
    bool readback;  /* un-poisoned canvas/audio readback (Fase 3) */
    bool gpu;       /* WebGL via isolated GPU helper (Fase 4) */
    bool sw;        /* service workers (Fase 4) */
    bool rtc;       /* WebRTC / getUserMedia (Fase 4) */
} wc_caps;

/* Per-host derivation inputs (GUI path). host_in_js / host_in_allow are nonzero iff
 * the page host is on js.conf / allow.conf (e.g. hb_is_allowlisted, subdomain-aware).
 * user_css / user_images are the user's session toggles; reader is distraction-free
 * (reader) mode. */
typedef struct wc_input {
    jsp_mode js_mode;
    int      host_in_js;
    int      host_in_allow;
    int      reader;
    int      user_css;
    int      user_images;
} wc_input;

/* The safe default: every capability off. Identical to (wc_caps){0}. */
wc_caps wc_safe(void);

/* Per-host GUI derivation. Reproduces exactly today's inline trusted/present_trusted/
 * css_grant/net policy; derives the forward-looking privacy caps from the same
 * jsp_trusted double-consent. Fail-closed (an out-of-range js_mode yields js off). */
wc_caps wc_derive(wc_input in);

/* Headless / operator-flag derivation. Headless does not gate by host: the operator's
 * --js=on / --author-css / --images ARE the trust signal (orthogonal). net and every
 * privacy cap follow --js=on. Reproduces exactly today's headless policy. */
wc_caps wc_from_flags(bool js, bool css, bool images);

/* Projects the leak-free triple to rdp_caps for rd_build, whose signature is
 * unchanged: { images, css, js }. (rd_build ignores caps.js; projected anyway for
 * completeness.) */
rdp_caps wc_render_caps(wc_caps c);

#endif /* FREEDOM_WEBCAPS_H */
