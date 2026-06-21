/*
 * js_policy — implementation: pure per-host JavaScript policy decision.
 *
 * No I/O, no global state. Fail-closed: an unknown mode never enables JS.
 */

#include "js_policy.h"

#include <string.h>

/* Case-insensitive ASCII equality (no locale dependence). */
static int eq_ci(const char *a, const char *b) {
    for (size_t i = 0;; ++i) {
        int ca = (unsigned char)a[i], cb = (unsigned char)b[i];
        if (ca >= 'A' && ca <= 'Z') ca += 'a' - 'A';
        if (cb >= 'A' && cb <= 'Z') cb += 'a' - 'A';
        if (ca != cb) return 0;
        if (ca == '\0') return 1;
    }
}

bool jsp_enabled(jsp_mode mode, int host_allowlisted) {
    switch (mode) {
        case JSP_OFF:       return false;
        case JSP_ALLOWLIST: return host_allowlisted != 0;
        case JSP_ON:        return true;
    }
    return false; /* fail closed on an out-of-range mode */
}

jsp_mode jsp_mode_from_str(const char *s) {
    if (s == NULL) return JSP_ALLOWLIST;
    if (eq_ci(s, "off") || eq_ci(s, "0") || eq_ci(s, "no") ||
        eq_ci(s, "false") || eq_ci(s, "none"))
        return JSP_OFF;
    if (eq_ci(s, "on") || eq_ci(s, "1") || eq_ci(s, "yes") ||
        eq_ci(s, "true") || eq_ci(s, "all"))
        return JSP_ON;
    /* "allowlist"/"list"/"auto" and any unrecognized value => the safe default. */
    return JSP_ALLOWLIST;
}

const char *jsp_mode_str(jsp_mode mode) {
    switch (mode) {
        case JSP_OFF:       return "off";
        case JSP_ALLOWLIST: return "allowlist";
        case JSP_ON:        return "on";
    }
    return "off";
}
