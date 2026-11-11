/* net_guard -- see include/net_guard.h and spec/net_guard.md. */
#include "net_guard.h"

#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>

#define NG_V4_LEN 4u
#define NG_V6_LEN 16u
#define NG_TEXT_MAX 64u   /* INET6_ADDRSTRLEN is 46; brackets and slack */

static int ng_v4_is_private(const unsigned char o[NG_V4_LEN]) {
    if (o[0] == 0 || o[0] == 10 || o[0] == 127) return 1;        /* this-net, RFC 1918, loopback */
    if (o[0] == 100 && o[1] >= 64 && o[1] <= 127) return 1;      /* CGNAT, RFC 6598 */
    if (o[0] == 169 && o[1] == 254) return 1;                    /* link-local, cloud metadata */
    if (o[0] == 172 && o[1] >= 16 && o[1] <= 31) return 1;       /* RFC 1918 */
    if (o[0] == 192 && o[1] == 168) return 1;                    /* RFC 1918 */
    if (o[0] == 192 && o[1] == 0 && o[2] == 0)                   /* IETF protocol assignments, */
        return !(o[3] == 9 || o[3] == 10);                       /* minus the two global anycasts */
    if (o[0] == 192 && o[1] == 0 && o[2] == 2) return 1;         /* TEST-NET-1 */
    if (o[0] == 192 && o[1] == 88 && o[2] == 99) return 1;       /* 6to4 relay anycast */
    if (o[0] == 198 && (o[1] == 18 || o[1] == 19)) return 1;     /* benchmarking, RFC 2544 */
    if (o[0] == 198 && o[1] == 51 && o[2] == 100) return 1;      /* TEST-NET-2 */
    if (o[0] == 203 && o[1] == 0 && o[2] == 113) return 1;       /* TEST-NET-3 */
    if (o[0] >= 224) return 1;                                   /* multicast, reserved, broadcast */
    return 0;
}

static unsigned ng_seg(const unsigned char a[NG_V6_LEN], int i) {
    return ((unsigned)a[2 * i] << 8) | (unsigned)a[2 * i + 1];
}

static int ng_v6_is_private(const unsigned char a[NG_V6_LEN]) {
    unsigned s[8];
    int head_zero = 1;
    for (int i = 0; i < 8; ++i) s[i] = ng_seg(a, i);
    for (int i = 0; i < 5; ++i) if (s[i] != 0) head_zero = 0;

    /* ::, ::1, IPv4-compatible ::a.b.c.d and IPv4-mapped ::ffff:a.b.c.d: the embedded
     * IPv4 decides (:: and ::1 embed 0.0.0.0 and 0.0.0.1, both in 0/8). */
    if (head_zero && (s[5] == 0 || s[5] == 0xffff)) return ng_v4_is_private(a + 12);
    if ((s[0] & 0xfe00) == 0xfc00) return 1;                     /* unique-local fc00::/7 */
    if ((s[0] & 0xffc0) == 0xfe80) return 1;                     /* link-local fe80::/10 */
    if ((s[0] & 0xffc0) == 0xfec0) return 1;                     /* deprecated site-local */
    if ((s[0] & 0xff00) == 0xff00) return 1;                     /* multicast */
    if (s[0] == 0x0064 && s[1] == 0xff9b) {
        if (s[2] == 0 && s[3] == 0 && s[4] == 0 && s[5] == 0)    /* NAT64 64:ff9b::/96 */
            return ng_v4_is_private(a + 12);
        if (s[2] == 1) return 1;                                 /* local-use NAT64 /48 */
    }
    if (s[0] == 0x2002) return ng_v4_is_private(a + 2);          /* 6to4 */
    if (s[0] == 0x2001 && s[1] == 0) {                           /* Teredo: server, ~client */
        unsigned char client[NG_V4_LEN];
        for (unsigned i = 0; i < NG_V4_LEN; ++i) client[i] = (unsigned char)~a[12 + i];
        return ng_v4_is_private(a + 4) || ng_v4_is_private(client);
    }
    if (s[0] == 0x2001 && s[1] == 0x0db8) return 1;              /* documentation */
    if (s[0] == 0x3fff && (s[1] & 0xf000) == 0) return 1;        /* documentation 3fff::/20 */
    if (s[0] == 0x0100 && s[1] == 0 && s[2] == 0 && s[3] == 0) return 1; /* discard-only */
    return 0;
}

int ng_addr_is_private(int family, const unsigned char *addr, size_t len) {
    if (addr == NULL) return 1;
    if (family == NG_FAMILY_V4 && len == NG_V4_LEN) return ng_v4_is_private(addr);
    if (family == NG_FAMILY_V6 && len == NG_V6_LEN) return ng_v6_is_private(addr);
    return 1;
}

/* Parses one textual address into *family / out[16]. 0 on success, -1 otherwise. */
static int ng_parse(const char *text, int *family, unsigned char out[NG_V6_LEN]) {
    if (text == NULL) return -1;
    size_t n = strlen(text);
    if (n >= 2 && text[0] == '[' && text[n - 1] == ']') { ++text; n -= 2; }
    if (n == 0 || n >= NG_TEXT_MAX) return -1;
    char buf[NG_TEXT_MAX];
    memcpy(buf, text, n);
    buf[n] = '\0';
    if (inet_pton(AF_INET, buf, out) == 1) { *family = NG_FAMILY_V4; return 0; }
    if (inet_pton(AF_INET6, buf, out) == 1) { *family = NG_FAMILY_V6; return 0; }
    return -1;
}

int ng_text_is_private(const char *ip_text) {
    unsigned char a[NG_V6_LEN];
    int family = 0;
    if (ng_parse(ip_text, &family, a) != 0) return 1;
    return ng_addr_is_private(family, a, (family == NG_FAMILY_V4) ? NG_V4_LEN : NG_V6_LEN);
}

int ng_host_is_ip(const char *host) {
    unsigned char a[NG_V6_LEN];
    int family = 0;
    return ng_parse(host, &family, a) == 0;
}

static int ng_ci_eq(const char *a, const char *b, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        unsigned char x = (unsigned char)a[i], y = (unsigned char)b[i];
        if (x >= 'A' && x <= 'Z') x = (unsigned char)(x - 'A' + 'a');
        if (y >= 'A' && y <= 'Z') y = (unsigned char)(y - 'A' + 'a');
        if (x != y) return 0;
    }
    return 1;
}

int ng_host_is_local(const char *host) {
    static const char LOCALHOST[] = "localhost";
    const size_t ll = sizeof LOCALHOST - 1;
    if (host == NULL || host[0] == '\0') return 0;
    size_t n = strlen(host);
    if (n > 1 && host[n - 1] == '.') --n;                        /* absolute form */
    if (n == ll && ng_ci_eq(host, LOCALHOST, ll)) return 1;
    if (n > ll && host[n - ll - 1] == '.' && ng_ci_eq(host + n - ll, LOCALHOST, ll)) return 1;
    unsigned char a[NG_V6_LEN];
    int family = 0;
    if (ng_parse(host, &family, a) != 0) return 0;               /* a name: not known local */
    return ng_addr_is_private(family, a, (family == NG_FAMILY_V4) ? NG_V4_LEN : NG_V6_LEN);
}

ng_verdict ng_decide(const ng_request *r, int peer_private) {
    if (r != NULL && r->via_proxy) return NG_ALLOW;
    if (!peer_private) return NG_ALLOW;
    if (r == NULL) return NG_DENY;
    if (r->initiator_host == NULL) return NG_ALLOW;
    if (ng_host_is_local(r->initiator_host)) return NG_ALLOW;
    if (r->same_site) return NG_ALLOW;
    return NG_DENY;
}
