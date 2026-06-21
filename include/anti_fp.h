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

/* Snaps a screen size to a standard bucket (cuts entropy). out_w/out_h non-NULL.
 * Picks the largest-area bucket that fits in (w,h); if none fits, the smallest. */
void fp_bucket_screen(int w, int h, int *out_w, int *out_h);

/* Deterministic per-session readback poisoning (canvas/audio): flips only the
 * least-significant bit of a sparse, key-selected subset of bytes. Same
 * (buf,key) => same output; different key => different output. NULL/len 0 = no-op. */
void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key);

#endif /* FREEDOM_ANTI_FP_H */
