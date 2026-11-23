/* libFuzzer harness for net_guard (spec/net_guard.md): hostile host and address text.
 * Invariants: the text classifier never reads past the NUL and never answers "public"
 * for text the binary classifier would call private (the two cannot disagree); a host
 * that is local is never judged a public initiator; and no input makes a public page
 * reach a private peer. */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

#include "net_guard.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size > 512) return 0;
    char *s = (char *)malloc(size + 1);
    if (s == NULL) return 0;
    if (size != 0) memcpy(s, data, size);
    s[size] = '\0';

    int text_private = ng_text_is_private(s);
    int is_ip = ng_host_is_ip(s);
    int local = ng_host_is_local(s);

    /* Differential oracle against libc: whatever inet_pton accepts must be classified
     * exactly as its binary form (brackets aside, which only ng_ strips). */
    unsigned char b[16];
    if (inet_pton(AF_INET, s, b) == 1) {
        if (!is_ip || text_private != ng_addr_is_private(NG_FAMILY_V4, b, 4)) abort();
    } else if (inet_pton(AF_INET6, s, b) == 1) {
        if (!is_ip || text_private != ng_addr_is_private(NG_FAMILY_V6, b, 16)) abort();
    } else if (s[0] != '[' && (is_ip || !text_private)) {
        abort();   /* not an address: never an IP, always fail-closed private */
    }
    if (is_ip && local != text_private) abort();

    /* Raw bytes as addresses, every length: only exact 4/16 can ever be public. */
    for (size_t len = 0; len <= size && len <= 17; ++len) {
        int p4 = ng_addr_is_private(NG_FAMILY_V4, data, len);
        int p6 = ng_addr_is_private(NG_FAMILY_V6, data, len);
        if (len != 4 && !p4) abort();
        if (len != 16 && !p6) abort();
    }

    ng_request r = { s, 0, 0 };
    if (!local && ng_decide(&r, 1) != NG_DENY) abort();
    if (local && ng_decide(&r, 1) != NG_ALLOW) abort();
    if (ng_decide(&r, 0) != NG_ALLOW) abort();

    free(s);
    return 0;
}
