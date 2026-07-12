#ifndef FREEDOM_ANTI_FP_H
#define FREEDOM_ANTI_FP_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * anti_fp — pure anti-fingerprinting primitives.
 *
 * Two strategies against device fingerprinting (adversary A3): present a
 * normalized, low-entropy identity shared by all users, and poison the
 * unavoidable signals (canvas/audio readback, clocks) with deterministic
 * per-session noise / coarse granularity. No I/O, no global state.
 *
 * See spec/anti_fp.md for the full contract.
 */

#define FP_TIMER_RESOLUTION_MS 100u

/* The normalized identity strings live here as macros so they are a single source
 * of truth shared by the JS bindings (navigator.*) AND the network layer (the
 * User-Agent / Accept-Language HTTP headers in secure_fetch). A mismatch between
 * the JS-visible identity and the on-the-wire identity is itself a high-entropy
 * fingerprint (and a bot signal), so both MUST present the same blend-in identity.
 * The value is a common, current Firefox-on-Linux string: it maximizes the
 * anonymity set instead of advertising "Freedom". */
#define FP_USER_AGENT \
    "Mozilla/5.0 (X11; Linux x86_64; rv:128.0) Gecko/20100101 Firefox/128.0"
#define FP_ACCEPT_LANGUAGE        "en-US,en"       /* list form (navigator.languages) */
#define FP_ACCEPT_LANGUAGE_HEADER "en-US,en;q=0.5" /* HTTP Accept-Language header value */

/*
 * Blending-in network constants (Hito 30b): Firefox-like HTTP headers shared with
 * secure_fetch so the JS-visible identity and on-the-wire identity agree.
 */
#define FP_ACCEPT_HEADER_NAV \
    "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8"

/* Sec-Fetch headers for top-level navigation. Subresource requests (images, scripts,
 * stylesheets) use the dest string from sf_config.sec_fetch_dest. */
#define FP_SEC_FETCH_DEST_NAV  "document"
#define FP_SEC_FETCH_MODE_NAV  "navigate"
#define FP_SEC_FETCH_SITE_NONE "none"
#define FP_SEC_FETCH_USER_ON   "?1"

/* --- clocks: coarse granularity against high-resolution timing --- */

uint64_t fp_timer_resolution_ms(void);
uint64_t fp_coarsen_time_ms(uint64_t raw_ms); /* floor to the resolution grid */

/* --- normalized identity (low entropy; identical for every user) --- */

const char *fp_user_agent(void);
const char *fp_accept_language(void);        /* list form, e.g. "en-US,en" */
const char *fp_accept_language_header(void); /* HTTP header value, e.g. "en-US,en;q=0.5" */
const char *fp_timezone(void);        /* "UTC" */
const char *fp_platform(void);        /* "Linux x86_64" (consistent with the UA) */
const char *fp_vendor(void);          /* "" (no vendor; minimal entropy) */
int         fp_hardware_concurrency(void);
int         fp_device_memory_gb(void);

/*
 * Legacy navigator properties (Hito 30b): normalized Firefox values shared by
 * js_env and the network layer so JS and HTTP present the same identity.
 */
const char *fp_app_version(void);       /* same string as fp_user_agent() */
const char *fp_app_code_name(void);     /* "Mozilla" (historic, all browsers) */
const char *fp_product(void);           /* "Gecko" (Firefox engine identity) */
const char *fp_app_name(void);          /* "Netscape" (historic) */
const char *fp_product_sub(void);       /* "20100101" (Gecko build date) */
const char *fp_oscpu(void);             /* "Linux x86_64" (consistent with UA) */
const char *fp_build_id(void);          /* fixed Firefox build ID */
int         fp_max_touch_points(void);  /* 0 (desktop, no touch) */
int         fp_on_line(void);           /* 1 (connected) */
int         fp_cookie_enabled(void);    /* 1 (cookies enabled) */

/* Snaps a screen size to a standard bucket (cuts entropy). out_w/out_h non-NULL.
 * Picks the largest-area bucket that fits in (w,h); if none fits, the smallest. */
void fp_bucket_screen(int w, int h, int *out_w, int *out_h);

/* Deterministic per-session readback poisoning (canvas/audio): flips only the
 * least-significant bit of a sparse, key-selected subset of bytes. Same
 * (buf,key) => same output; different key => different output. NULL/len 0 = no-op. */
void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key);

/* Derives the per-origin readback key from the per-session secret and a site's
 * registrable domain (eTLD+1). Same (session_key, domain) => same key (poisoning
 * is stable within a site); different domains under the same session => different
 * keys with overwhelming probability (canvas/audio noise is not linkable across
 * sites, defeating cross-origin fingerprint linking). registrable_domain NULL or
 * "" collapses to a single namespace (its own stable key, distinct from any real
 * domain); never aborts, never leaks. Pure: no I/O, no allocation. The caller
 * (tab worker) computes the eTLD+1 via request_policy and passes it here. */
uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain);

#endif /* FREEDOM_ANTI_FP_H */
