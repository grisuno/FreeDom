/* libFuzzer harness for hls (spec/hls.md): hostile playlist text, hostile
 * segment bytes, hostile segment URL. Oracles: a payload offset is in range and
 * points at media; a mirror URL is https, NUL-terminated at its reported length,
 * keeps the segment's path and stays on the segment's registrable domain. */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hls.h"
#include "request_policy.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 3) return 0;
    long http = (long)data[0] * 2;
    size_t k = data[1] % 5;
    data += 2;
    size -= 2;
    const uint8_t *sep = memchr(data, 0, size);
    size_t plen = sep != NULL ? (size_t)(sep - data) : size;
    const uint8_t *rest = sep != NULL ? sep + 1 : data + size;
    size_t rlen = (size_t)(data + size - rest);

    long off = hls_segment_payload(http, rest, rlen);
    if (off >= 0) {
        if ((size_t)off >= rlen || http < 200 || http > 299) abort();
        if (off > 0 && rest[off] != 0x47) abort();
    }

    hls_playlist *pl = NULL;
    if (hls_parse((const char *)data, plen, &pl) != HLS_OK || pl == NULL) return 0;
    (void)hls_select_variant(pl, (int)(rlen % 4000), (int)(plen % 3000));

    char seg[1024];
    size_t sl = rlen < sizeof seg - 1 ? rlen : sizeof seg - 1;
    memcpy(seg, rest, sl);
    seg[sl] = '\0';
    char out[512];
    if (hls_resolve_url("https://a.example/p/list.m3u8", seg, out, sizeof out) > 0
        && memchr(out, 0, sizeof out) == NULL) abort();

    const char *probe = pl->count > 0 ? pl->segments[pl->count - 1].url : seg;
    size_t n = hls_mirror_url(pl, probe, k, out, sizeof out);
    if (n > 0) {
        if (n >= sizeof out || strlen(out) != n || strncmp(out, "https://", 8) != 0) abort();
        char h1[256], h2[256], s1[256], s2[256];
        if (rp_host_of(probe, h1, sizeof h1) != 0 || rp_host_of(out, h2, sizeof h2) != 0) abort();
        if (rp_site_of(h1, s1, sizeof s1) != 0 || rp_site_of(h2, s2, sizeof s2) != 0) abort();
        if (strcmp(s1, s2) != 0 || strcmp(h1, h2) == 0) abort();
        const char *p1 = strpbrk(probe + 8, "/?#"), *p2 = strpbrk(out + 8, "/?#");
        if ((p1 == NULL) != (p2 == NULL) || (p1 != NULL && strcmp(p1, p2) != 0)) abort();
    }
    hls_playlist_free(pl);
    return 0;
}
