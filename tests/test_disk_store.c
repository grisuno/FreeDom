/*
 * TDD suite for disk_store (Hito 5 - encrypted persistence).
 *
 * RED state until src/disk_store.c exists: this links and fails on purpose.
 * Uses a real temporary directory. Build: make test ; ASan: make asan
 */

#define _POSIX_C_SOURCE 200809L

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

#include "disk_store.h"
#include "local_store.h"

static const uint8_t KEY[LS_KEY_LEN] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
};
static const char PT[] = "bookmarks: https://example.com\nsession token=abc123";

typedef struct fixture { char dir[64]; char path[96]; } fixture;

static int setup(void **state) {
    fixture *f = (fixture *)calloc(1, sizeof *f);
    if (f == NULL) return -1;
    strcpy(f->dir, "/tmp/freedom_ds_XXXXXX");
    if (mkdtemp(f->dir) == NULL) return -1;
    snprintf(f->path, sizeof f->path, "%s/state", f->dir);
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
                if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0) continue;
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

static size_t count_dir_entries(const char *dir) {
    DIR *d = opendir(dir);
    if (d == NULL) return (size_t)-1;
    size_t n = 0;
    struct dirent *e;
    while ((e = readdir(d)) != NULL) {
        if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0) continue;
        ++n;
    }
    closedir(d);
    return n;
}

static void test_roundtrip(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(ds_write(f->path, KEY, LS_AEAD_AES256_GCM,
                              (const uint8_t *)PT, sizeof PT - 1), DS_OK);
    uint8_t *out = NULL; size_t out_len = 0;
    assert_int_equal(ds_read(f->path, KEY, &out, &out_len), DS_OK);
    assert_int_equal(out_len, sizeof PT - 1);
    assert_memory_equal(out, PT, sizeof PT - 1);
    ds_free(out, out_len);
}

static void test_roundtrip_chacha(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(ds_write(f->path, KEY, LS_AEAD_CHACHA20_POLY1305,
                              (const uint8_t *)PT, sizeof PT - 1), DS_OK);
    uint8_t *out = NULL; size_t out_len = 0;
    assert_int_equal(ds_read(f->path, KEY, &out, &out_len), DS_OK);
    assert_memory_equal(out, PT, sizeof PT - 1);
    ds_free(out, out_len);
}

static void test_empty(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(ds_write(f->path, KEY, LS_AEAD_AES256_GCM, NULL, 0), DS_OK);
    uint8_t *out = NULL; size_t out_len = 99;
    assert_int_equal(ds_read(f->path, KEY, &out, &out_len), DS_OK);
    assert_int_equal(out_len, 0);
    ds_free(out, out_len);
}

static void test_permissions(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(ds_write(f->path, KEY, LS_AEAD_AES256_GCM,
                              (const uint8_t *)PT, sizeof PT - 1), DS_OK);
    struct stat st;
    assert_int_equal(stat(f->path, &st), 0);
    assert_int_equal(st.st_mode & 0777, 0600);
}

static void test_no_temp_left(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(ds_write(f->path, KEY, LS_AEAD_AES256_GCM,
                              (const uint8_t *)PT, sizeof PT - 1), DS_OK);
    assert_int_equal(count_dir_entries(f->dir), 1); /* only the target file */
}

static void test_overwrite(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(ds_write(f->path, KEY, LS_AEAD_AES256_GCM,
                              (const uint8_t *)"old", 3), DS_OK);
    assert_int_equal(ds_write(f->path, KEY, LS_AEAD_AES256_GCM,
                              (const uint8_t *)"newer", 5), DS_OK);
    assert_int_equal(count_dir_entries(f->dir), 1);
    uint8_t *out = NULL; size_t out_len = 0;
    assert_int_equal(ds_read(f->path, KEY, &out, &out_len), DS_OK);
    assert_int_equal(out_len, 5);
    assert_memory_equal(out, "newer", 5);
    ds_free(out, out_len);
}

static void test_wrong_key(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(ds_write(f->path, KEY, LS_AEAD_AES256_GCM,
                              (const uint8_t *)PT, sizeof PT - 1), DS_OK);
    uint8_t bad[LS_KEY_LEN];
    memcpy(bad, KEY, LS_KEY_LEN);
    bad[5] ^= 0x40;
    uint8_t *out = (uint8_t *)0x1; size_t out_len = 1;
    assert_int_equal(ds_read(f->path, bad, &out, &out_len), DS_ERR_AUTH);
    assert_null(out);
}

static void test_tamper_on_disk(void **state) {
    fixture *f = (fixture *)*state;
    assert_int_equal(ds_write(f->path, KEY, LS_AEAD_AES256_GCM,
                              (const uint8_t *)PT, sizeof PT - 1), DS_OK);
    int fd = open(f->path, O_RDWR);
    assert_true(fd >= 0);
    uint8_t b;
    assert_int_equal(pread(fd, &b, 1, 40), 1);
    b ^= 0x01;
    assert_int_equal(pwrite(fd, &b, 1, 40), 1);
    close(fd);

    uint8_t *out = (uint8_t *)0x1; size_t out_len = 1;
    ds_status st = ds_read(f->path, KEY, &out, &out_len);
    assert_true(st == DS_ERR_AUTH || st == DS_ERR_FORMAT);
    assert_null(out);
}

static void test_missing_and_null(void **state) {
    fixture *f = (fixture *)*state;
    char missing[160];
    snprintf(missing, sizeof missing, "%s/nope", f->dir);
    uint8_t *out = NULL; size_t out_len = 0;
    assert_int_equal(ds_read(missing, KEY, &out, &out_len), DS_ERR_IO);

    assert_int_equal(ds_write(NULL, KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, 1),
                     DS_ERR_NULL_ARG);
    assert_int_equal(ds_read(NULL, KEY, &out, &out_len), DS_ERR_NULL_ARG);
    ds_free(NULL, 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(test_roundtrip, setup, teardown),
        cmocka_unit_test_setup_teardown(test_roundtrip_chacha, setup, teardown),
        cmocka_unit_test_setup_teardown(test_empty, setup, teardown),
        cmocka_unit_test_setup_teardown(test_permissions, setup, teardown),
        cmocka_unit_test_setup_teardown(test_no_temp_left, setup, teardown),
        cmocka_unit_test_setup_teardown(test_overwrite, setup, teardown),
        cmocka_unit_test_setup_teardown(test_wrong_key, setup, teardown),
        cmocka_unit_test_setup_teardown(test_tamper_on_disk, setup, teardown),
        cmocka_unit_test_setup_teardown(test_missing_and_null, setup, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
