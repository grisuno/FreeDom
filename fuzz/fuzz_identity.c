/* libFuzzer harness for identity (spec/identity.md) and he_cdn_kind (spec/hostedit.md):
 * hostile form queries, persisted lines and subresource URLs. Invariants: a query never
 * leaves the config invalid, serialize/parse is a fixed point, the page always fits or is
 * empty, and the classifier stays inside the string. */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hostedit.h"
#include "identity.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 1 || size > 4096) return 0;
    char *s = (char *)malloc(size + 1);
    if (s == NULL) return 0;
    memcpy(s, data + 1, size - 1);
    s[size - 1] = '\0';

    he_cdn_kind_t k = he_cdn_kind(s);
    if (k != HE_CDN_CSS && k != HE_CDN_JS && k != HE_CDN_RES) abort();

    idn_config c;
    idn_defaults(&c);
    if (data[0] & 1) idn_parse(&c, s); else (void)idn_apply_query(&c, s);
    if (c.auto_allow > IDN_AA_ALL) abort();

    char line[1024];
    size_t n = idn_serialize(&c, line, sizeof line);
    if (n > 0) {
        idn_config d;
        idn_parse(&d, line);
        char again[1024];
        if (idn_serialize(&d, again, sizeof again) != n || strcmp(line, again) != 0) abort();
    }
    static char page[16384];
    size_t pn = idn_render_page(&c, page, sizeof page);
    if (pn >= sizeof page) abort();
    free(s);
    return 0;
}
