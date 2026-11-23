/* Suite for chrome_layout (spec/chrome_layout.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>
#include <string.h>

#include "chrome_layout.h"

static int overlaps(chl_rect a, chl_rect b) {
    if (a.w <= 0.0 || b.w <= 0.0 || a.h <= 0.0 || b.h <= 0.0) return 0;
    return a.x < b.x + b.w && b.x < a.x + a.w && a.y < b.y + b.h && b.y < a.y + a.h;
}

static double cx(chl_rect r) { return r.x + r.w / 2.0; }
static double cy(chl_rect r) { return r.y + r.h / 2.0; }

static void test_rejects_bad_input(void **state) {
    (void)state;
    chl_layout l;
    memset(&l, 0x5a, sizeof l);
    chl_layout before = l;
    assert_int_equal(chl_compute(1000, 1, 0, 0, &l), CHL_EINVAL);
    assert_int_equal(chl_compute(1000, 1, 2, 2, &l), CHL_EINVAL);
    assert_int_equal(chl_compute(1000, 1, 2, -1, &l), CHL_EINVAL);
    assert_int_equal(chl_compute(1000, 1, 1, 0, NULL), CHL_EINVAL);
    assert_memory_equal(&l, &before, sizeof l);
}

static void test_csd_single_tab(void **state) {
    (void)state;
    chl_layout l;
    assert_int_equal(chl_compute(1300, 1, 1, 0, &l), CHL_OK);
    assert_true(fabs(l.win_close.x + l.win_close.w - 1300.0) < 1e-9);
    assert_true(l.win_max.x + l.win_max.w <= l.win_close.x + 1e-9);
    assert_true(l.win_min.x + l.win_min.w <= l.win_max.x + 1e-9);
    chl_rect t, c;
    assert_int_equal(chl_tab_rect(&l, 0, &t), 1);
    assert_true(fabs(t.x - CHL_PAD) < 1e-9);
    assert_true(t.w <= CHL_TAB_MAX_W + 1e-9);
    assert_int_equal(chl_tab_close_rect(&l, 0, &c), 0); /* one tab: no close */
    assert_true(l.win_min.x - (l.new_tab.x + l.new_tab.w) >= CHL_DRAG_MIN - 1e-9);
    assert_true(fabs(l.content_top - (CHL_TABBAR_H + CHL_TOOLBAR_H)) < 1e-9);
    assert_true(fabs(l.toolbar_top - CHL_TABBAR_H) < 1e-9);
}

static void test_ssd_has_no_window_buttons(void **state) {
    (void)state;
    chl_layout l;
    assert_int_equal(chl_compute(900, 0, 3, 1, &l), CHL_OK);
    assert_true(l.win_close.w == 0.0 && l.win_min.w == 0.0 && l.win_max.w == 0.0);
    int tab = 7;
    assert_int_equal(chl_hit(&l, 899, 10, &tab), CHL_PART_NONE);
    assert_int_equal(tab, -1);
}

static void test_many_tabs_keep_minimum_and_drag(void **state) {
    (void)state;
    chl_layout l;
    assert_int_equal(chl_compute(1000, 1, 200, 150, &l), CHL_OK);
    assert_true(l.tab_w >= CHL_TAB_MIN_W - 1e-9);
    assert_true(l.tabs_visible > 0 && l.tabs_visible < 200);
    chl_rect t;
    for (int i = 0; i < 200; ++i) {
        int vis = chl_tab_rect(&l, i, &t);
        assert_int_equal(vis, i >= l.tab_first && i < l.tab_first + l.tabs_visible);
        if (!vis) continue;
        assert_false(overlaps(t, l.new_tab));
        assert_false(overlaps(t, l.win_min));
        assert_true(t.x + t.w <= l.new_tab.x + 1e-9);
    }
    assert_true(l.win_min.x - (l.new_tab.x + l.new_tab.w) >= CHL_DRAG_MIN - 1e-9);
    assert_int_equal(chl_tab_rect(&l, -1, &t), 0);
    assert_int_equal(chl_tab_rect(&l, 150, &t), 1); /* the active tab is always visible */
}

static void test_close_buttons(void **state) {
    (void)state;
    chl_layout l;
    chl_rect c, t;
    assert_int_equal(chl_compute(1300, 1, 3, 1, &l), CHL_OK);
    for (int i = 0; i < 3; ++i) {
        assert_int_equal(chl_tab_close_rect(&l, i, &c), 1);
        assert_int_equal(chl_tab_rect(&l, i, &t), 1);
        assert_true(c.x >= t.x && c.x + c.w <= t.x + t.w + 1e-9);
        int tab = -1;
        assert_int_equal(chl_hit(&l, cx(c), cy(c), &tab), CHL_PART_TAB_CLOSE);
        assert_int_equal(tab, i);
        assert_int_equal(chl_hit(&l, t.x + 4, cy(t), &tab), CHL_PART_TAB);
        assert_int_equal(tab, i);
    }
    /* Narrow tabs: only the active one keeps its close button. */
    assert_int_equal(chl_compute(700, 1, 12, 4, &l), CHL_OK);
    assert_true(l.tab_w < CHL_TAB_CLOSE_MIN_W);
    assert_int_equal(chl_tab_close_rect(&l, 4, &c), 1);
    assert_int_equal(chl_tab_close_rect(&l, 3, &c), 0);
}

static void test_toolbar_hits(void **state) {
    (void)state;
    chl_layout l;
    assert_int_equal(chl_compute(1300, 1, 2, 0, &l), CHL_OK);
    int tab;
    assert_int_equal(chl_hit(&l, cx(l.back), cy(l.back), &tab), CHL_PART_BACK);
    assert_int_equal(chl_hit(&l, cx(l.fwd), cy(l.fwd), &tab), CHL_PART_FWD);
    assert_int_equal(chl_hit(&l, cx(l.reload), cy(l.reload), &tab), CHL_PART_RELOAD);
    assert_int_equal(chl_hit(&l, cx(l.identity), cy(l.identity), &tab), CHL_PART_IDENTITY);
    assert_int_equal(chl_hit(&l, cx(l.url), cy(l.url), &tab), CHL_PART_URL);
    assert_int_equal(chl_hit(&l, cx(l.menu), cy(l.menu), &tab), CHL_PART_MENU);
    assert_int_equal(chl_hit(&l, cx(l.new_tab), cy(l.new_tab), &tab), CHL_PART_NEW_TAB);
    assert_int_equal(chl_hit(&l, cx(l.win_close), cy(l.win_close), &tab), CHL_PART_WIN_CLOSE);
    assert_int_equal(chl_hit(&l, cx(l.win_max), cy(l.win_max), &tab), CHL_PART_WIN_MAX);
    assert_int_equal(chl_hit(&l, cx(l.win_min), cy(l.win_min), &tab), CHL_PART_WIN_MIN);
    assert_int_equal(chl_hit(&l, l.win_min.x - 5, 10, &tab), CHL_PART_DRAG);
    assert_int_equal(chl_hit(&l, 600, l.content_top, &tab), CHL_PART_CONTENT);
    assert_int_equal(chl_hit(&l, 600, l.url.y + l.url.h - 0.5, &tab), CHL_PART_URL);
    assert_int_equal(chl_hit(&l, 600, l.content_top - 0.5, &tab), CHL_PART_NONE);
    /* Identity sits inside the pill, which sits between reload and menu. */
    assert_true(l.identity.x >= l.url.x && l.identity.x + l.identity.w <= l.url.x + l.url.w);
    assert_true(l.url.x >= l.reload.x + l.reload.w);
    assert_true(l.url.x + l.url.w <= l.menu.x);
    assert_true(l.menu.x + l.menu.w <= 1300.0 - CHL_PAD + 1e-9);
}

static void test_bookmark_star(void **state) {
    (void)state;
    chl_layout l;
    assert_int_equal(chl_compute(1300, 1, 2, 0, &l), CHL_OK);
    int tab;
    assert_true(l.star.w > 0.0 && l.star.h > 0.0);
    assert_true(l.star.x >= l.identity.x + l.identity.w);
    assert_true(l.star.x + l.star.w <= l.url.x + l.url.w);
    assert_true(l.url.x + l.url.w - (l.star.x + l.star.w) < 4.0);   /* at the right edge */
    assert_true(l.star.y >= l.url.y && l.star.y + l.star.h <= l.url.y + l.url.h);
    assert_int_equal(chl_hit(&l, cx(l.star), cy(l.star), &tab), CHL_PART_STAR);
    assert_int_equal(chl_hit(&l, l.star.x - 1.0, cy(l.star), &tab), CHL_PART_URL);
    /* A pill too narrow to hold text and a star keeps only the text. */
    assert_int_equal(chl_compute(CHL_STAR_MIN_URL + 3.0 * CHL_BTN + 2.0 * CHL_PAD, 1, 1, 0, &l), CHL_OK);
    assert_true(l.url.w < CHL_STAR_MIN_URL + 40.0);
    if (l.url.w < CHL_STAR_MIN_URL) {
        assert_true(l.star.w == 0.0);
        assert_int_equal(chl_hit(&l, l.url.x + l.url.w - 3.0, cy(l.url), &tab), CHL_PART_URL);
    }
    assert_int_equal(chl_compute(200, 1, 1, 0, &l), CHL_OK);
    assert_true(l.star.w == 0.0 && l.star.h == 0.0);
}

static void test_tab_fallback_title(void **state) {
    (void)state;
    char o[64];
    chl_tab_fallback_title("https://example.com/x?q=1", o, sizeof o);
    assert_string_equal(o, "example.com/x?q=1");
    chl_tab_fallback_title("file:///home/u/docs/mono.html", o, sizeof o);
    assert_string_equal(o, "mono.html");
    chl_tab_fallback_title("/tmp/a/b/page.html", o, sizeof o);
    assert_string_equal(o, "page.html");
    chl_tab_fallback_title("/tmp/dir/", o, sizeof o);
    assert_string_equal(o, "/tmp/dir/");
    chl_tab_fallback_title("about:blank", o, sizeof o);
    assert_string_equal(o, "about:blank");
    chl_tab_fallback_title(NULL, o, sizeof o);
    assert_string_equal(o, "");
    char t[6];
    chl_tab_fallback_title("https://\xC3\xB1\xC3\xB1\xC3\xB1.es", t, sizeof t);
    assert_string_equal(t, "\xC3\xB1\xC3\xB1");
    chl_tab_fallback_title("https://x", o, 0);   /* no write at all */
}

static void test_tiny_and_hostile_widths(void **state) {
    (void)state;
    const double ws[] = { -5.0, 0.0, 1.0, 37.0, 120.0, NAN, INFINITY, 1e300 };
    for (size_t k = 0; k < sizeof ws / sizeof ws[0]; ++k) {
        chl_layout l;
        assert_int_equal(chl_compute(ws[k], 1, 5, 2, &l), CHL_OK);
        assert_true(isfinite(l.width) && l.width >= 1.0);
        const chl_rect rs[] = { l.new_tab, l.win_min, l.win_max, l.win_close, l.back,
                                l.fwd, l.reload, l.url, l.identity, l.star, l.menu };
        for (size_t i = 0; i < sizeof rs / sizeof rs[0]; ++i) {
            assert_true(isfinite(rs[i].x) && isfinite(rs[i].w));
            assert_true(rs[i].w >= 0.0 && rs[i].h >= 0.0);
        }
        assert_true(l.tabs_visible >= 0 && l.tabs_visible <= 5);
        int tab;
        (void)chl_hit(&l, 10, 10, &tab);
    }
}

static void test_identity_table(void **state) {
    (void)state;
    assert_int_equal(chl_identity_of(NULL, 0, 0, 0), CHL_ID_INTERNAL);
    assert_int_equal(chl_identity_of("", 0, 0, 0), CHL_ID_INTERNAL);
    assert_int_equal(chl_identity_of("about:config", 0, 0, 0), CHL_ID_INTERNAL);
    assert_int_equal(chl_identity_of("file:///tmp/a.html", 1, 0, 1), CHL_ID_LOCAL);
    assert_int_equal(chl_identity_of("https://example.com/", 1, CHL_DG_NONE, 0), CHL_ID_PQ);
    assert_int_equal(chl_identity_of("HTTPS://example.com/", 1, CHL_DG_NONE, 0), CHL_ID_PQ);
    assert_int_equal(chl_identity_of("https://example.com/", 0, CHL_DG_NONE, 0), CHL_ID_UNKNOWN);
    assert_int_equal(chl_identity_of("https://example.com/", 1, CHL_DG_NONE, 1), CHL_ID_UNVERIFIED);
    assert_int_equal(chl_identity_of("https://example.com/", 1, CHL_DG_CLASSICAL_KE, 0), CHL_ID_CLASSICAL);
    assert_int_equal(chl_identity_of("https://example.com/", 1, CHL_DG_ALLOWLISTED, 0), CHL_ID_WEAK);
    assert_int_equal(chl_identity_of("https://example.com/", 1, 99, 0), CHL_ID_UNKNOWN);
    assert_int_equal(chl_identity_of("https://example.com/", 1, -1, 0), CHL_ID_UNKNOWN);
    assert_int_equal(chl_identity_of("https://abc.onion/", 1, CHL_DG_NONE, 0), CHL_ID_OVERLAY);
    assert_int_equal(chl_identity_of("https://abc.onion./x", 1, CHL_DG_NONE, 0), CHL_ID_OVERLAY);
    assert_int_equal(chl_identity_of("https://abc.onion/", 1, CHL_DG_CLASSICAL_KE, 0), CHL_ID_CLASSICAL);
    assert_int_equal(chl_identity_of("http://site.i2p/", 1, CHL_DG_NONE, 0), CHL_ID_OVERLAY);
    assert_int_equal(chl_identity_of("http://site.i2p:7657/", 1, CHL_DG_NONE, 0), CHL_ID_OVERLAY);
    assert_int_equal(chl_identity_of("http://example.com/", 1, CHL_DG_NONE, 0), CHL_ID_INSECURE);
    assert_int_equal(chl_identity_of("http://i2p.example.com/", 1, CHL_DG_NONE, 0), CHL_ID_INSECURE);
    assert_int_equal(chl_identity_of("http://user@x.i2p.evil.com/", 1, CHL_DG_NONE, 0), CHL_ID_INSECURE);
    assert_int_equal(chl_identity_of("https://x.onion.evil.com/", 1, CHL_DG_NONE, 0), CHL_ID_PQ);
    assert_int_equal(chl_identity_of("http://site.i2p/", 1, CHL_DG_NONE, 1), CHL_ID_UNVERIFIED);
    assert_int_equal(chl_identity_of("data:text/html,x", 1, CHL_DG_NONE, 0), CHL_ID_UNKNOWN);
    assert_int_equal(chl_identity_of("javascript:alert(1)", 1, CHL_DG_NONE, 0), CHL_ID_UNKNOWN);
    assert_int_equal(chl_identity_of("https:", 1, CHL_DG_NONE, 0), CHL_ID_UNKNOWN);
    assert_int_equal(chl_identity_of("https://", 1, CHL_DG_NONE, 0), CHL_ID_UNKNOWN);
}

static void test_identity_labels(void **state) {
    (void)state;
    for (int id = CHL_ID_UNKNOWN; id <= CHL_ID_INSECURE; ++id) {
        const char *s = chl_identity_label((chl_identity)id);
        assert_non_null(s);
        assert_true(strlen(s) > 0);
    }
    assert_non_null(chl_identity_label((chl_identity)1234));
}

static void test_findbar(void **state) {
    (void)state;
    assert_int_equal(chl_findbar_compute(1000, 800, NULL), CHL_EINVAL);
    chl_findbar f;
    assert_int_equal(chl_findbar_compute(1300, 900, &f), CHL_OK);
    assert_true(fabs(f.bar.y + f.bar.h - 900.0) < 1e-9);
    assert_true(fabs(f.bar.h - CHL_FIND_H) < 1e-9);
    assert_true(fabs(f.bar.w - 1300.0) < 1e-9);
    assert_true(fabs(f.field.w - CHL_FIND_FIELD_W) < 1e-9);
    assert_true(f.prev.x >= f.field.x + f.field.w);
    assert_true(f.next.x >= f.prev.x + f.prev.w);
    assert_true(f.count.x >= f.next.x + f.next.w);
    assert_true(fabs(f.close.x + f.close.w + CHL_PAD - 1300.0) < 1e-9);
    assert_int_equal(chl_findbar_hit(&f, cx(f.field), cy(f.field)), CHL_FIND_FIELD);
    assert_int_equal(chl_findbar_hit(&f, cx(f.prev), cy(f.prev)), CHL_FIND_PREV);
    assert_int_equal(chl_findbar_hit(&f, cx(f.next), cy(f.next)), CHL_FIND_NEXT);
    assert_int_equal(chl_findbar_hit(&f, cx(f.close), cy(f.close)), CHL_FIND_CLOSE);
    assert_int_equal(chl_findbar_hit(&f, cx(f.count), cy(f.count)), CHL_FIND_BAR);
    assert_int_equal(chl_findbar_hit(&f, 10, 10), CHL_FIND_NONE);
    assert_int_equal(chl_findbar_hit(NULL, 10, 10), CHL_FIND_NONE);
    const double widths[] = { 0.0, 1.0, 90.0, 250.0, 500.0, NAN, INFINITY, -5.0, 1e300 };
    for (size_t i = 0; i < sizeof widths / sizeof widths[0]; ++i) {
        assert_int_equal(chl_findbar_compute(widths[i], widths[i], &f), CHL_OK);
        chl_rect parts[] = { f.field, f.prev, f.next, f.count, f.close };
        for (size_t a = 0; a < 5; ++a) {
            assert_true(isfinite(parts[a].x) && isfinite(parts[a].w));
            if (parts[a].w > 0.0) {
                assert_true(parts[a].x >= f.bar.x - 1e-9);
                assert_true(parts[a].x + parts[a].w <= f.bar.x + f.bar.w + 1e-9);
            }
            for (size_t b = a + 1; b < 5; ++b) assert_false(overlaps(parts[a], parts[b]));
        }
    }
    /* narrow window: the field shrinks before anything overlaps */
    assert_int_equal(chl_findbar_compute(380, 600, &f), CHL_OK);
    assert_true(f.count.w < 1e-9);
    assert_true(f.field.w < CHL_FIND_FIELD_W);
    assert_true(f.field.w > 0.0);
}


static void test_hidden_tab_indicators(void **state) {
    (void)state;
    chl_layout l;
    /* Everything fits: no indicators. */
    assert_int_equal(chl_compute(1300, 1, 3, 1, &l), CHL_OK);
    assert_int_equal(l.hidden_left, 0);
    assert_int_equal(l.hidden_right, 0);
    assert_true(l.more_left.w == 0.0 && l.more_right.w == 0.0);

    /* 60 tabs, the middle one active: tabs hidden on both sides, counted exactly. */
    assert_int_equal(chl_compute(1300, 1, 60, 30, &l), CHL_OK);
    assert_true(l.tabs_visible > 0 && l.tabs_visible < 60);
    assert_int_equal(l.hidden_left, l.tab_first);
    assert_int_equal(l.hidden_left + l.tabs_visible + l.hidden_right, 60);
    assert_true(l.hidden_left > 0);
    assert_true(l.more_left.w > 0.0 && l.more_right.w > 0.0);
    chl_rect first, last;
    assert_int_equal(chl_tab_rect(&l, l.tab_first, &first), 1);
    assert_int_equal(chl_tab_rect(&l, l.tab_first + l.tabs_visible - 1, &last), 1);
    assert_false(overlaps(l.more_left, first));
    assert_false(overlaps(l.more_right, last));
    assert_false(overlaps(l.more_right, l.new_tab));
    assert_true(l.more_left.x + l.more_left.w <= first.x + 1e-9);
    assert_true(last.x + last.w <= l.more_right.x + 1e-9);
    assert_true(l.more_right.x + l.more_right.w <= l.new_tab.x + 1e-9);
    assert_true(l.new_tab.x + l.new_tab.w <= l.win_min.x - CHL_DRAG_MIN + 1e-9);
    int t = 9;
    assert_int_equal(chl_hit(&l, cx(l.more_left), cy(l.more_left), &t), CHL_PART_TABS_LEFT);
    assert_int_equal(t, -1);
    assert_int_equal(chl_hit(&l, cx(l.more_right), cy(l.more_right), NULL), CHL_PART_TABS_RIGHT);

    /* First tab active: nothing hidden on the left, so the left indicator is inert. */
    assert_int_equal(chl_compute(1300, 1, 60, 0, &l), CHL_OK);
    assert_int_equal(l.hidden_left, 0);
    assert_true(l.hidden_right > 0);
    assert_true(chl_hit(&l, cx(l.more_left), cy(l.more_left), NULL) != CHL_PART_TABS_LEFT);
}

static void test_tab_drop_index(void **state) {
    (void)state;
    chl_layout l;
    assert_int_equal(chl_compute(1300, 1, 5, 0, &l), CHL_OK);
    for (int i = 0; i < 5; ++i) {
        chl_rect r;
        assert_int_equal(chl_tab_rect(&l, i, &r), 1);
        assert_int_equal(chl_tab_drop_index(&l, r.x + 1.0), i);
        assert_int_equal(chl_tab_drop_index(&l, r.x + r.w - 1.0), i);
    }
    assert_int_equal(chl_tab_drop_index(&l, -500.0), 0);
    assert_int_equal(chl_tab_drop_index(&l, 1.0e9), 4);
    assert_int_equal(chl_tab_drop_index(&l, NAN), 0);
    assert_int_equal(chl_tab_drop_index(NULL, 10.0), -1);

    /* Scrolled strip: the index is absolute, inside the visible window. */
    assert_int_equal(chl_compute(1300, 1, 60, 40, &l), CHL_OK);
    assert_int_equal(chl_tab_drop_index(&l, -1.0), l.tab_first);
    assert_int_equal(chl_tab_drop_index(&l, 1.0e9), l.tab_first + l.tabs_visible - 1);
}

static void test_tab_for_digit(void **state) {
    (void)state;
    assert_int_equal(chl_tab_for_digit(1, 5), 0);
    assert_int_equal(chl_tab_for_digit(5, 5), 4);
    assert_int_equal(chl_tab_for_digit(6, 5), -1);
    assert_int_equal(chl_tab_for_digit(8, 20), 7);
    assert_int_equal(chl_tab_for_digit(9, 20), 19);  /* 9 = the last tab, Firefox */
    assert_int_equal(chl_tab_for_digit(9, 1), 0);
    assert_int_equal(chl_tab_for_digit(0, 5), -1);
    assert_int_equal(chl_tab_for_digit(10, 5), -1);
    assert_int_equal(chl_tab_for_digit(1, 0), -1);
}

static void test_move_index(void **state) {
    (void)state;
    /* Moving 1 -> 3 in [a b c d e] gives [a c d b e]. */
    assert_int_equal(chl_move_index(0, 1, 3), 0);
    assert_int_equal(chl_move_index(1, 1, 3), 3);
    assert_int_equal(chl_move_index(2, 1, 3), 1);
    assert_int_equal(chl_move_index(3, 1, 3), 2);
    assert_int_equal(chl_move_index(4, 1, 3), 4);
    /* Moving 3 -> 1 gives [a d b c e]. */
    assert_int_equal(chl_move_index(1, 3, 1), 2);
    assert_int_equal(chl_move_index(2, 3, 1), 3);
    assert_int_equal(chl_move_index(3, 3, 1), 1);
    assert_int_equal(chl_move_index(0, 3, 1), 0);
    assert_int_equal(chl_move_index(4, 3, 1), 4);
    assert_int_equal(chl_move_index(2, 2, 2), 2);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_rejects_bad_input),
        cmocka_unit_test(test_csd_single_tab),
        cmocka_unit_test(test_ssd_has_no_window_buttons),
        cmocka_unit_test(test_many_tabs_keep_minimum_and_drag),
        cmocka_unit_test(test_close_buttons),
        cmocka_unit_test(test_toolbar_hits),
        cmocka_unit_test(test_bookmark_star),
        cmocka_unit_test(test_tab_fallback_title),
        cmocka_unit_test(test_tiny_and_hostile_widths),
        cmocka_unit_test(test_identity_table),
        cmocka_unit_test(test_identity_labels),
        cmocka_unit_test(test_findbar),
        cmocka_unit_test(test_hidden_tab_indicators),
        cmocka_unit_test(test_tab_drop_index),
        cmocka_unit_test(test_move_index),
        cmocka_unit_test(test_tab_for_digit),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
