/* libFuzzer harness for css_counter (spec/css_counter.md): hostile `content` and counter
 * lists. Invariants: parsing never reads past the NUL, a marker always resolves into a
 * bounded NUL-terminated buffer, and the state machine stays inside its instance table. */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "css_counter.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 2 || size > 2048) return 0;
    char *s = (char *)malloc(size + 1);
    if (s == NULL) return 0;
    memcpy(s, data + 1, size - 1);
    s[size - 1] = '\0';

    cnt_decl d[CNT_MAX_DECL];
    int n = cnt_parse_decls(s, data[0] & 1, d);
    cnt_state *st = cnt_state_new();
    if (st != NULL) {
        if (n > 0) {
            cnt_reset(st, (int)(data[0] >> 4), d, n);
            cnt_increment(st, (int)(data[0] >> 4) + 1, d, n);
        }
        char marker[1024];
        if (cnt_parse_content(s, marker, sizeof marker) == 1) {
            char out[96];
            size_t len = cnt_resolve(st, marker, NULL, NULL, out, sizeof out);
            if (len >= sizeof out || out[len] != '\0') abort();
        }
        cnt_leave(st, 0);
        cnt_state_free(st);
    }
    char buf[16];
    size_t fl = cnt_format((int)(data[0] % 12), (long)(int32_t)(size * 2654435761u), buf, sizeof buf);
    if (fl >= sizeof buf || buf[fl] != '\0') abort();
    free(s);
    return 0;
}
