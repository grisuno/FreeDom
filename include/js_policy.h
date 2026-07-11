#ifndef FREEDOM_JS_POLICY_H
#define FREEDOM_JS_POLICY_H

#include <stdbool.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * js_policy — pure per-host JavaScript policy decision.
 *
 * Secure by Default: page JavaScript is hostile content, so it is OFF unless the
 * user opts a host in. This module is the single, testable decision "should JS be
 * enabled for this host?", combining a global mode with per-host allowlist
 * membership (the allowlist itself is matched by the hostblock module, which
 * already covers subdomains). No I/O, no global state.
 *
 * The decision is surfaced as rdp_caps.js and consumed by the render pipeline (the
 * worker): today it controls <noscript> rendering (a no-JS browser shows the
 * fallback); executing allowlisted page scripts is staged on the same flag for the
 * live-DOM milestone.
 *
 * See spec/js_policy.md for the full contract.
 */

typedef enum jsp_mode {
    JSP_OFF = 0,    /* never run page JS (no host) */
    JSP_ALLOWLIST,  /* run JS only for hosts on the allowlist (the default) */
    JSP_ON          /* run JS for every host (least safe; explicit opt-in) */
} jsp_mode;

/* The decision. host_allowlisted is nonzero iff the page host is on the JS
 * allowlist (e.g. hb_is_allowlisted over js.conf). Fails closed: an unknown mode
 * yields false. */
bool jsp_enabled(jsp_mode mode, int host_allowlisted);

/* Trusted-host doctrine (Hito 28): a host the user declared trustworthy TWICE --
 * its JS is enabled (js_enabled, e.g. the jsp_enabled result) AND it is explicitly
 * on allow.conf (host_allowlisted, e.g. hb_is_allowlisted over allow.conf) -- gets
 * the full modern experience: author CSS and images on without per-session toggles.
 * Either signal alone fails closed; a global JSP_ON without the allowlist entry is
 * NOT trust. Reader mode is applied by the orchestrator afterwards and wins. */
bool jsp_trusted(bool js_enabled, int host_allowlisted);

/* Parses a CLI/env mode string. NULL or an unrecognized value yields the default
 * JSP_ALLOWLIST (conservative: only explicit hosts run JS). "off"/"0"/"no"/"false"/
 * "none" => JSP_OFF; "on"/"1"/"yes"/"true"/"all" => JSP_ON;
 * "allowlist"/"list"/"auto" => JSP_ALLOWLIST. Case-insensitive. */
jsp_mode jsp_mode_from_str(const char *s);

/* Stable lowercase name of a mode ("off"/"allowlist"/"on"); an unknown value
 * yields "off" (fail closed). Never NULL. */
const char *jsp_mode_str(jsp_mode mode);

#endif /* FREEDOM_JS_POLICY_H */
