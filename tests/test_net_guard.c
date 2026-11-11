/* Suite for net_guard (spec/net_guard.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>

#include "net_guard.h"

static void expect_private(const char *const *ips, size_t n, int want) {
    for (size_t i = 0; i < n; ++i) {
        if (ng_text_is_private(ips[i]) != want) fail_msg("%s: expected %d", ips[i], want);
    }
}

static void test_ipv4_private_and_special_ranges(void **state) {
    (void)state;
    static const char *const priv[] = {
        "127.0.0.1", "127.255.255.254", "10.0.0.1", "10.255.255.255", "172.16.0.1",
        "172.31.255.255", "192.168.0.1", "192.168.255.255", "169.254.169.254", "0.0.0.0",
        "0.1.2.3", "100.64.0.1", "100.127.255.255", "100.100.100.200", "192.0.0.1",
        "192.0.0.8", "192.0.2.1", "192.88.99.1", "198.18.0.1", "198.19.255.255",
        "198.51.100.7", "203.0.113.7", "224.0.0.1", "239.255.255.255", "240.0.0.1",
        "255.255.255.255",
    };
    expect_private(priv, sizeof priv / sizeof priv[0], 1);
}

static void test_ipv4_public_edges(void **state) {
    (void)state;
    static const char *const pub[] = {
        "8.8.8.8", "1.1.1.1", "9.255.255.255", "11.0.0.0", "126.255.255.255", "128.0.0.1",
        "100.63.255.255", "100.128.0.0", "169.253.255.255", "169.255.0.0", "172.15.255.255",
        "172.32.0.0", "192.167.255.255", "192.169.0.0", "192.0.0.9", "192.0.0.10",
        "192.0.1.1", "192.0.3.1", "192.88.98.1", "198.17.255.255", "198.20.0.0",
        "198.51.99.1", "198.51.101.1", "203.0.112.1", "203.0.114.1", "223.255.255.255",
    };
    expect_private(pub, sizeof pub / sizeof pub[0], 0);
}

static void test_ipv6_private_and_special_ranges(void **state) {
    (void)state;
    static const char *const priv[] = {
        "::", "::1", "fc00::1", "fdff:ffff::1", "fe80::1", "febf::1", "fec0::1", "ff02::1",
        "2001:db8::1", "3fff:0fff::1", "100::1", "64:ff9b:1::1", "[::1]", "[fe80::1]",
    };
    expect_private(priv, sizeof priv / sizeof priv[0], 1);
    static const char *const pub[] = {
        "2606:4700:4700::1111", "2001:4860:4860::8888", "fbff::1", "fe00::1", "2001:db9::1",
        "3fff:1000::1", "100:0:0:1::1", "64:ff9b:2::1", "[2606:4700:4700::1111]",
    };
    expect_private(pub, sizeof pub / sizeof pub[0], 0);
}

/* Every way of carrying an IPv4 address inside an IPv6 one is judged as that IPv4. */
static void test_ipv4_embedded_in_ipv6_is_unwrapped(void **state) {
    (void)state;
    static const char *const priv[] = {
        "::ffff:127.0.0.1", "::ffff:169.254.169.254", "::ffff:10.0.0.1", "::127.0.0.1",
        "::192.168.1.1", "64:ff9b::7f00:1", "64:ff9b::a00:1", "2002:7f00:1::",
        "2002:c0a8:101::1", "2001:0:7f00:1::1", "2001:0:808:808::f5ff:fffe",
    };
    expect_private(priv, sizeof priv / sizeof priv[0], 1);
    static const char *const pub[] = {
        "::ffff:8.8.8.8", "::8.8.8.8", "64:ff9b::808:808", "2002:808:808::1",
        "2001:0:808:808::f7f7:f7f7",
    };
    expect_private(pub, sizeof pub / sizeof pub[0], 0);
}

static void test_unclassifiable_fails_closed(void **state) {
    (void)state;
    static const char *const bad[] = {
        "", "example.com", "127.1", "0x7f.0.0.1", "2130706433", "8.8.8.8 ", " 8.8.8.8",
        "8.8.8.8/32", "8.8.8", "8.8.8.8.8", "[8.8.8.8", "::g", "1::2::3", "[]",
        "8.8.8.8\n", "fe80::1%eth0",
    };
    expect_private(bad, sizeof bad / sizeof bad[0], 1);
    assert_int_equal(ng_text_is_private(NULL), 1);
    char huge[200];
    memset(huge, '1', sizeof huge - 1);
    huge[sizeof huge - 1] = '\0';
    assert_int_equal(ng_text_is_private(huge), 1);

    unsigned char pub4[4] = { 8, 8, 8, 8 };
    assert_int_equal(ng_addr_is_private(NG_FAMILY_V4, pub4, 4), 0);
    assert_int_equal(ng_addr_is_private(NG_FAMILY_V4, pub4, 3), 1);
    assert_int_equal(ng_addr_is_private(NG_FAMILY_V6, pub4, 4), 1);
    assert_int_equal(ng_addr_is_private(0, pub4, 4), 1);
    assert_int_equal(ng_addr_is_private(NG_FAMILY_V4, NULL, 4), 1);
}

static void test_host_is_local(void **state) {
    (void)state;
    assert_int_equal(ng_host_is_local("localhost"), 1);
    assert_int_equal(ng_host_is_local("LocalHost"), 1);
    assert_int_equal(ng_host_is_local("localhost."), 1);
    assert_int_equal(ng_host_is_local("dev.localhost"), 1);
    assert_int_equal(ng_host_is_local("a.b.LOCALHOST"), 1);
    assert_int_equal(ng_host_is_local("192.168.1.1"), 1);
    assert_int_equal(ng_host_is_local("[::1]"), 1);
    assert_int_equal(ng_host_is_local("::1"), 1);
    assert_int_equal(ng_host_is_local("notlocalhost"), 0);
    assert_int_equal(ng_host_is_local("localhost.example.com"), 0);
    assert_int_equal(ng_host_is_local("example.com"), 0);
    assert_int_equal(ng_host_is_local("8.8.8.8"), 0);
    assert_int_equal(ng_host_is_local(".localhost"), 1);
    assert_int_equal(ng_host_is_local(""), 0);
    assert_int_equal(ng_host_is_local(NULL), 0);
}

static void test_host_is_ip(void **state) {
    (void)state;
    assert_int_equal(ng_host_is_ip("8.8.8.8"), 1);
    assert_int_equal(ng_host_is_ip("192.168.1.1"), 1);
    assert_int_equal(ng_host_is_ip("[2606:4700::1]"), 1);
    assert_int_equal(ng_host_is_ip("::1"), 1);
    assert_int_equal(ng_host_is_ip("example.com"), 0);
    assert_int_equal(ng_host_is_ip("1.1"), 0);
    assert_int_equal(ng_host_is_ip(""), 0);
    assert_int_equal(ng_host_is_ip(NULL), 0);
}

static void test_decide(void **state) {
    (void)state;
    ng_request user = { NULL, 0, 0 };
    ng_request pub_page = { "news.example", 0, 0 };
    ng_request same = { "wiki.corp.example", 1, 0 };
    ng_request local_page = { "localhost", 0, 0 };
    ng_request lan_page = { "192.168.1.10", 0, 0 };
    ng_request proxied = { "news.example", 0, 1 };
    ng_request empty_init = { "", 0, 0 };

    /* A public peer is never the guard's business. */
    assert_int_equal(ng_decide(&pub_page, 0), NG_ALLOW);
    assert_int_equal(ng_decide(NULL, 0), NG_ALLOW);
    /* The user may go anywhere; remote content may not go private on their behalf. */
    assert_int_equal(ng_decide(&user, 1), NG_ALLOW);
    assert_int_equal(ng_decide(&pub_page, 1), NG_DENY);
    assert_int_equal(ng_decide(&empty_init, 1), NG_DENY);
    assert_int_equal(ng_decide(NULL, 1), NG_DENY);
    /* Same zone. */
    assert_int_equal(ng_decide(&same, 1), NG_ALLOW);
    assert_int_equal(ng_decide(&local_page, 1), NG_ALLOW);
    assert_int_equal(ng_decide(&lan_page, 1), NG_ALLOW);
    /* An overlay proxy is the peer; the overlay does not route to the LAN. */
    assert_int_equal(ng_decide(&proxied, 1), NG_ALLOW);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_ipv4_private_and_special_ranges),
        cmocka_unit_test(test_ipv4_public_edges),
        cmocka_unit_test(test_ipv6_private_and_special_ranges),
        cmocka_unit_test(test_ipv4_embedded_in_ipv6_is_unwrapped),
        cmocka_unit_test(test_unclassifiable_fails_closed),
        cmocka_unit_test(test_host_is_local),
        cmocka_unit_test(test_host_is_ip),
        cmocka_unit_test(test_decide),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
