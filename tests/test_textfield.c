/*
 * test_textfield — CMocka suite for the pure editable text-field primitive.
 *
 * Covers init/clear/set, insert at the cursor, backspace/delete edges, cursor
 * movement with saturation, home/end, the NULL-safe accessors, and the
 * fail-closed FULL edges (set too long, insert into a full buffer leave the field
 * intact).
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "textfield.h"

static void test_init_and_accessors(void **state) {
    (void)state;
    tf_field f;
    tf_init(&f);
    assert_int_equal(tf_len(&f), 0);
    assert_int_equal(tf_cursor(&f), 0);
    assert_string_equal(tf_text(&f), "");
}

static void test_null_safe(void **state) {
    (void)state;
    /* void ops are no-ops, status ops report NULL, readers return neutral. */
    tf_init(NULL);
    tf_clear(NULL);
    tf_backspace(NULL);
    tf_delete(NULL);
    tf_move(NULL, 3);
    tf_home(NULL);
    tf_end(NULL);
    assert_int_equal(tf_insert(NULL, 'x'), TF_ERR_NULL_ARG);
    assert_int_equal(tf_set(NULL, "hi"), TF_ERR_NULL_ARG);
    assert_string_equal(tf_text(NULL), "");
    assert_int_equal(tf_len(NULL), 0);
    assert_int_equal(tf_cursor(NULL), 0);
}

static void test_set(void **state) {
    (void)state;
    tf_field f;
    tf_init(&f);
    assert_int_equal(tf_set(&f, "Freedom/0.1"), TF_OK);
    assert_string_equal(tf_text(&f), "Freedom/0.1");
    assert_int_equal(tf_len(&f), 11);
    assert_int_equal(tf_cursor(&f), 11); /* cursor at end */
    assert_int_equal(tf_set(&f, NULL), TF_ERR_NULL_ARG);
    assert_int_equal(tf_set(&f, ""), TF_OK);
    assert_int_equal(tf_len(&f), 0);
}

static void test_insert_sequence(void **state) {
    (void)state;
    tf_field f;
    tf_init(&f);
    const char *s = "abc";
    for (const char *p = s; *p; ++p) assert_int_equal(tf_insert(&f, *p), TF_OK);
    assert_string_equal(tf_text(&f), "abc");
    assert_int_equal(tf_cursor(&f), 3);

    /* Insert in the middle: move cursor back two, insert 'X' -> "aXbc". */
    tf_move(&f, -2);
    assert_int_equal(tf_cursor(&f), 1);
    assert_int_equal(tf_insert(&f, 'X'), TF_OK);
    assert_string_equal(tf_text(&f), "aXbc");
    assert_int_equal(tf_cursor(&f), 2);
}

static void test_backspace_delete(void **state) {
    (void)state;
    tf_field f;
    tf_init(&f);
    assert_int_equal(tf_set(&f, "hello"), TF_OK);

    tf_backspace(&f); /* remove 'o' */
    assert_string_equal(tf_text(&f), "hell");
    assert_int_equal(tf_cursor(&f), 4);

    tf_home(&f);
    tf_delete(&f); /* remove leading 'h' */
    assert_string_equal(tf_text(&f), "ell");
    assert_int_equal(tf_cursor(&f), 0);

    /* Edges: backspace at start, delete at end are no-ops. */
    tf_backspace(&f);
    assert_string_equal(tf_text(&f), "ell");
    tf_end(&f);
    tf_delete(&f);
    assert_string_equal(tf_text(&f), "ell");
    assert_int_equal(tf_cursor(&f), 3);
}

static void test_move_saturates(void **state) {
    (void)state;
    tf_field f;
    tf_init(&f);
    assert_int_equal(tf_set(&f, "ab"), TF_OK);
    tf_move(&f, -100);
    assert_int_equal(tf_cursor(&f), 0);
    tf_move(&f, 100);
    assert_int_equal(tf_cursor(&f), 2);
    tf_move(&f, -1);
    assert_int_equal(tf_cursor(&f), 1);
}

static void test_full_fails_closed(void **state) {
    (void)state;
    tf_field f;
    tf_init(&f);

    /* Fill to capacity-1 (TF_CAP includes the NUL). */
    for (size_t i = 0; i + 1 < TF_CAP; ++i) {
        assert_int_equal(tf_insert(&f, 'a'), TF_OK);
    }
    assert_int_equal(tf_len(&f), TF_CAP - 1);

    /* One more must fail and leave the field intact. */
    assert_int_equal(tf_insert(&f, 'b'), TF_ERR_FULL);
    assert_int_equal(tf_len(&f), TF_CAP - 1);
    assert_int_equal(tf_text(&f)[TF_CAP - 2], 'a');

    /* set with an over-long string fails closed (field unchanged). */
    tf_field g;
    tf_init(&g);
    assert_int_equal(tf_set(&g, "seed"), TF_OK);
    char big[TF_CAP + 8];
    memset(big, 'z', sizeof big);
    big[sizeof big - 1] = '\0';
    assert_int_equal(tf_set(&g, big), TF_ERR_FULL);
    assert_string_equal(tf_text(&g), "seed");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_init_and_accessors),
        cmocka_unit_test(test_null_safe),
        cmocka_unit_test(test_set),
        cmocka_unit_test(test_insert_sequence),
        cmocka_unit_test(test_backspace_delete),
        cmocka_unit_test(test_move_saturates),
        cmocka_unit_test(test_full_fails_closed),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
