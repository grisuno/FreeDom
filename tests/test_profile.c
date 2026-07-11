/*
 * TDD suite for profile (Hito 10 - encrypted persistence orchestrator for the
 * prefs model: per-device key -> Argon2id -> disk_store).
 *
 * RED state until src/profile.c exists: this fails to link on purpose.
 * Uses a real temporary directory. Build: make test ; ASan: make asan
 */

#define _GNU_SOURCE   /* memmem for the nothing-readable-on-disk check */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "prefs.h"
#include "profile.h"

typedef struct fixture { char dir[64]; } fixture;

static int setup(void **state) {
    fixture *f = (fixture *)calloc(1, sizeof *f);
    if (f == NULL) return -1;
    strcpy(f->dir, "/tmp/freedom_prof_XXXXXX");
    if (mkdtemp(f->dir) == NULL) return -1;
    *state = f;
    return 0;
}

static int teardown(void **state) {
    fixture *f = (fixture *)*state;
    if (f != NULL) {
        DIR *d = opendir(f->dir);
        if (d != NULL) {
            struct dirent *e;
            while ((e = readdir(d)) != NULL) {
                if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0)
                    continue;
                char p[512];
                snprintf(p, sizeof p, "%s/%s", f->dir, e->d_name);
                unlink(p);
            }
            closedir(d);
        }
        rmdir(f->dir);
        free(f);
    }
    return 0;
}

static void path_of(const fixture *f, const char *name, char *out, size_t cap) {
    snprintf(out, cap, "%s/%s", f->dir, name);
}

static size_t file_size(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0) return (size_t)-1;
    return (size_t)st.st_size;
}

/* --- open: keyfile lifecycle -------------------------------------------------- */

static void test_open_creates_keyfile(void **state) {
    fixture *f = (fixture *)*state;
    profile_ctx ctx;
    assert_int_equal(profile_open(&ctx, f->dir), PROFILE_OK);
    assert_true(ctx.ready);
    char kp[512];
    path_of(f, PROFILE_KEY_FILE, kp, sizeof kp);
    assert_int_equal(file_size(kp), LS_SALT_LEN + LS_KEY_LEN);  /* 16 + 32 */
    struct stat st;
    assert_int_equal(stat(kp, &st), 0);
    assert_int_equal(st.st_mode & 0777, 0600);
    profile_close(&ctx);
    assert_false(ctx.ready);
    profile_close(&ctx);   /* idempotent */
    profile_close(NULL);   /* NULL-safe */
}

static void test_open_rejects_corrupt_keyfile(void **state) {
    fixture *f = (fixture *)*state;
    char kp[512];
    path_of(f, PROFILE_KEY_FILE, kp, sizeof kp);
    int fd = open(kp, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    assert_true(fd >= 0);
    assert_int_equal(write(fd, "short", 5), 5);
    close(fd);
    profile_ctx ctx;
    assert_int_equal(profile_open(&ctx, f->dir), PROFILE_ERR_KEY);
    /* Fail closed, never clobber: the corrupt file is untouched. */
    assert_int_equal(file_size(kp), 5);
}

static void test_open_bad_dir(void **state) {
    (void)state;
    profile_ctx ctx;
    assert_int_equal(profile_open(&ctx, "/nonexistent/freedom-prof"),
                     PROFILE_ERR_DIR);
    assert_int_equal(profile_open(&ctx, ""), PROFILE_ERR_DIR);
    assert_int_equal(profile_open(&ctx, NULL), PROFILE_ERR_NULL_ARG);
    assert_int_equal(profile_open(NULL, "/tmp"), PROFILE_ERR_NULL_ARG);
}

/* --- load/save ------------------------------------------------------------------ */

static void test_first_launch_defaults(void **state) {
    fixture *f = (fixture *)*state;
    profile_ctx ctx;
    assert_int_equal(profile_open(&ctx, f->dir), PROFILE_OK);
    prefs_state p;
    prefs_init(&p);
    assert_int_equal(profile_load(&ctx, &p), PROFILE_OK);  /* absent file: OK */
    assert_int_equal(p.zoom_pct, 100);
    assert_int_equal(p.bookmarks_len, 0);
    prefs_free(&p);
    profile_close(&ctx);
}

static void test_save_load_roundtrip_two_ctx(void **state) {
    fixture *f = (fixture *)*state;
    profile_ctx a;
    assert_int_equal(profile_open(&a, f->dir), PROFILE_OK);

    prefs_state p;
    prefs_init(&p);
    p.theme_mode = 1;
    p.images = 1;
    p.zoom_pct = 150;
    int added;
    assert_int_equal(prefs_bookmark_toggle(&p, "https://example.com/",
                                           "Example", &added), PREFS_OK);
    assert_int_equal(prefs_history_add(&p, "https://visited.test/page"), PREFS_OK);
    assert_int_equal(profile_save(&a, &p), PROFILE_OK);
    profile_close(&a);

    /* A second open re-derives the SAME key from the persisted salt+secret. */
    profile_ctx b;
    assert_int_equal(profile_open(&b, f->dir), PROFILE_OK);
    prefs_state q;
    prefs_init(&q);
    assert_int_equal(profile_load(&b, &q), PROFILE_OK);
    assert_int_equal(q.theme_mode, 1);
    assert_int_equal(q.images, 1);
    assert_int_equal(q.zoom_pct, 150);
    assert_int_equal(q.bookmarks_len, 1);
    assert_string_equal(q.bookmarks[0].url, "https://example.com/");
    assert_string_equal(q.bookmarks[0].title, "Example");
    assert_int_equal(q.history_len, 1);
    assert_string_equal(q.history[0], "https://visited.test/page");

    /* prefs.bin is 0600. */
    char pp[512];
    path_of(f, PROFILE_PREFS_FILE, pp, sizeof pp);
    struct stat st;
    assert_int_equal(stat(pp, &st), 0);
    assert_int_equal(st.st_mode & 0777, 0600);

    prefs_free(&p);
    prefs_free(&q);
    profile_close(&b);
}

/* --- Zero Knowledge: nothing readable on disk ------------------------------------ */

static void test_nothing_readable_on_disk(void **state) {
    fixture *f = (fixture *)*state;
    profile_ctx ctx;
    assert_int_equal(profile_open(&ctx, f->dir), PROFILE_OK);
    prefs_state p;
    prefs_init(&p);
    int added;
    const char *secret_url = "https://very-private-site.example/account";
    assert_int_equal(prefs_bookmark_toggle(&p, secret_url, "My bank", &added),
                     PREFS_OK);
    assert_int_equal(profile_save(&ctx, &p), PROFILE_OK);

    char pp[512];
    path_of(f, PROFILE_PREFS_FILE, pp, sizeof pp);
    FILE *fp = fopen(pp, "rb");
    assert_non_null(fp);
    static uint8_t blob[1 << 20];
    size_t blen = fread(blob, 1, sizeof blob, fp);
    fclose(fp);
    assert_true(blen > 0);
    assert_null(memmem(blob, blen, secret_url, strlen(secret_url)));
    assert_null(memmem(blob, blen, "My bank", 7));
    assert_null(memmem(blob, blen, "freedom-prefs", 13));

    prefs_free(&p);
    profile_close(&ctx);
}

/* --- fail closed on tamper / foreign key ------------------------------------------ */

static void test_tampered_blob_auth_fails(void **state) {
    fixture *f = (fixture *)*state;
    profile_ctx ctx;
    assert_int_equal(profile_open(&ctx, f->dir), PROFILE_OK);
    prefs_state p;
    prefs_init(&p);
    p.zoom_pct = 200;
    assert_int_equal(profile_save(&ctx, &p), PROFILE_OK);

    char pp[512];
    path_of(f, PROFILE_PREFS_FILE, pp, sizeof pp);
    size_t sz = file_size(pp);
    assert_true(sz > 0 && sz != (size_t)-1);
    int fd = open(pp, O_RDWR);
    assert_true(fd >= 0);
    off_t mid = (off_t)(sz / 2);
    uint8_t byte;
    assert_int_equal(pread(fd, &byte, 1, mid), 1);
    byte ^= 0x40;
    assert_int_equal(pwrite(fd, &byte, 1, mid), 1);
    close(fd);

    prefs_state q;
    prefs_init(&q);
    profile_status st = profile_load(&ctx, &q);
    assert_true(st == PROFILE_ERR_AUTH || st == PROFILE_ERR_FORMAT);
    assert_int_equal(q.zoom_pct, 100);  /* defaults, no partial state */
    prefs_free(&p);
    prefs_free(&q);
    profile_close(&ctx);
}

static void test_foreign_key_auth_fails(void **state) {
    fixture *f = (fixture *)*state;
    profile_ctx ctx;
    assert_int_equal(profile_open(&ctx, f->dir), PROFILE_OK);
    prefs_state p;
    prefs_init(&p);
    assert_int_equal(profile_save(&ctx, &p), PROFILE_OK);
    profile_close(&ctx);

    /* Replace the keyfile: the blob no longer authenticates (foreign device). */
    char kp[512];
    path_of(f, PROFILE_KEY_FILE, kp, sizeof kp);
    assert_int_equal(unlink(kp), 0);
    profile_ctx other;
    assert_int_equal(profile_open(&other, f->dir), PROFILE_OK);
    prefs_state q;
    prefs_init(&q);
    assert_int_equal(profile_load(&other, &q), PROFILE_ERR_AUTH);
    prefs_free(&p);
    prefs_free(&q);
    profile_close(&other);
}

/* --- NULL / not-ready args --------------------------------------------------------- */

static void test_null_and_not_ready(void **state) {
    fixture *f = (fixture *)*state;
    prefs_state p;
    prefs_init(&p);
    profile_ctx ctx;
    memset(&ctx, 0, sizeof ctx);  /* not ready */
    assert_int_equal(profile_load(&ctx, &p), PROFILE_ERR_NULL_ARG);
    assert_int_equal(profile_save(&ctx, &p), PROFILE_ERR_NULL_ARG);
    assert_int_equal(profile_open(&ctx, f->dir), PROFILE_OK);
    assert_int_equal(profile_load(&ctx, NULL), PROFILE_ERR_NULL_ARG);
    assert_int_equal(profile_save(&ctx, NULL), PROFILE_ERR_NULL_ARG);
    assert_int_equal(profile_load(NULL, &p), PROFILE_ERR_NULL_ARG);
    assert_int_equal(profile_save(NULL, &p), PROFILE_ERR_NULL_ARG);
    prefs_free(&p);
    profile_close(&ctx);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(test_open_creates_keyfile, setup, teardown),
        cmocka_unit_test_setup_teardown(test_open_rejects_corrupt_keyfile, setup, teardown),
        cmocka_unit_test_setup_teardown(test_open_bad_dir, setup, teardown),
        cmocka_unit_test_setup_teardown(test_first_launch_defaults, setup, teardown),
        cmocka_unit_test_setup_teardown(test_save_load_roundtrip_two_ctx, setup, teardown),
        cmocka_unit_test_setup_teardown(test_nothing_readable_on_disk, setup, teardown),
        cmocka_unit_test_setup_teardown(test_tampered_blob_auth_fails, setup, teardown),
        cmocka_unit_test_setup_teardown(test_foreign_key_auth_fails, setup, teardown),
        cmocka_unit_test_setup_teardown(test_null_and_not_ready, setup, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
