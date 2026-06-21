/*
 * anti_fp — implementation: pure anti-fingerprinting primitives.
 *
 * Normalized identity values are fixed constants (no real device data leaks).
 * Readback poisoning uses a keyed splitmix64 PRNG to flip a sparse set of LSBs
 * deterministically per session. No I/O, no allocation, no global state.
 */

#include "anti_fp.h"

/* --- clocks --- */

uint64_t fp_timer_resolution_ms(void) {
    return FP_TIMER_RESOLUTION_MS;
}

uint64_t fp_coarsen_time_ms(uint64_t raw_ms) {
    return raw_ms - (raw_ms % FP_TIMER_RESOLUTION_MS);
}

/* --- normalized identity (shared by all Freedom users) --- */

const char *fp_user_agent(void) {
    return FP_USER_AGENT;
}

const char *fp_accept_language(void) {
    return FP_ACCEPT_LANGUAGE;
}

const char *fp_accept_language_header(void) {
    return FP_ACCEPT_LANGUAGE_HEADER;
}

const char *fp_timezone(void) {
    return "UTC";
}

const char *fp_platform(void) {
    return "Linux x86_64"; /* consistent with the normalized user-agent */
}

const char *fp_vendor(void) {
    return ""; /* no vendor string: minimal entropy */
}

int fp_hardware_concurrency(void) {
    return 2; /* fixed: do not reveal the real core count */
}

int fp_device_memory_gb(void) {
    return 8; /* fixed: do not reveal the real memory size */
}

/* --- screen bucketing --- */

void fp_bucket_screen(int w, int h, int *out_w, int *out_h) {
    static const int buckets[][2] = {
        {1920, 1080}, {1600, 900}, {1536, 864}, {1440, 900},
        {1366, 768},  {1280, 720}, {1024, 768}, {800, 600},
    };
    const size_t n = sizeof buckets / sizeof buckets[0];
    const size_t smallest = n - 1; /* last entry has the smallest area */

    long best_area = -1;
    size_t best = smallest;
    for (size_t i = 0; i < n; ++i) {
        if (buckets[i][0] <= w && buckets[i][1] <= h) {
            long area = (long)buckets[i][0] * (long)buckets[i][1];
            if (area > best_area) { best_area = area; best = i; }
        }
    }
    if (out_w != NULL) *out_w = buckets[best][0];
    if (out_h != NULL) *out_h = buckets[best][1];
}

/* --- readback poisoning --- */

static uint64_t splitmix64(uint64_t *state) {
    uint64_t z = (*state += 0x9e3779b97f4a7c15ULL);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
    z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
    return z ^ (z >> 31);
}

void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key) {
    if (buf == NULL || len == 0) return;
    uint64_t state = session_key;
    for (size_t i = 0; i < len; ++i) {
        /* Sparse selection (~1/16) keyed by the session and the byte index. */
        if ((splitmix64(&state) & 0xF) == 0) {
            buf[i] ^= 1u; /* flip only the least-significant bit */
        }
    }
}
