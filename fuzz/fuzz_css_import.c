/* fuzz_css_import -- hostile stylesheet text through the @import prelude reader
 * (spec/css_import.md). Oracle: every wrapper built from hostile conditions is
 * itself balanced (a condition can never smuggle a brace), and every URL and
 * condition is NUL-terminated within its field. */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "css_import.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    static ci_import ims[CI_MAX_PER_SHEET];
    size_t n = ci_scan((const char *)data, size, ims, CI_MAX_PER_SHEET);
    if (n > CI_MAX_PER_SHEET) abort();
    (void)ci_balanced((const char *)data, size);
    for (size_t i = 0; i < n; ++i) {
        if (memchr(ims[i].url, '\0', sizeof ims[i].url) == NULL) abort();
        if (ims[i].url[0] == '\0') abort();
        if (memchr(ims[i].media, '\0', sizeof ims[i].media) == NULL) abort();
        char open[3 * CI_COND_MAX + 64], close[8], both[3 * CI_COND_MAX + 80];
        if (ci_wrap(&ims[i], open, sizeof open, close, sizeof close) != 0) abort();
        size_t ol = strlen(open), cl = strlen(close);
        memcpy(both, open, ol);
        memcpy(both + ol, close, cl);
        if (!ci_balanced(both, ol + cl)) abort();
    }
    return 0;
}
