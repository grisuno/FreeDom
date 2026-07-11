/*
 * libFuzzer harness for download (the "save to disk" filename derivation).
 *
 * The download filename is derived from the URL and the Content-Disposition
 * header, both hostile remote input. Arbitrary bytes -> dl_pick_name /
 * dl_build_path must never crash, leak or trigger UB, and must never produce a
 * name that escapes the download directory. The invariants below are asserted so
 * a containment bug aborts here (not only a memory bug). dl_should_download and
 * dl_ext_for_type are exercised for crashes too.
 *
 * The input is split on '\n' into up to three NUL-terminated fields the fuzzer
 * controls independently: url, content_disposition, content_type.
 *
 * Build & run: make fuzz-dl   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "download.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void check_name(const char *name) {
    if (strchr(name, '/') != NULL) abort();   /* never a separator */
    if (name[0] == '\0') abort();             /* always non-empty */
    if (name[0] == '.') abort();              /* no hidden / ".." */
    size_t n = strlen(name);
    if (n > DL_NAME_MAX + 8) abort();         /* bound + at most one ".xxxx" */
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char *buf = (char *)malloc(size + 1);
    if (buf == NULL) return 0;
    memcpy(buf, data, size);
    buf[size] = '\0';

    /* Split into url \n disposition \n content_type (any field may be empty). */
    char *url = buf;
    char *disp = strchr(url, '\n');
    char *ctype = NULL;
    if (disp != NULL) { *disp = '\0'; ++disp; ctype = strchr(disp, '\n'); }
    if (ctype != NULL) { *ctype = '\0'; ++ctype; }

    (void)dl_should_download(ctype, disp);
    (void)dl_ext_for_type(ctype);

    char name[DL_NAME_MAX + 8];
    if (dl_pick_name(url, disp, ctype, name, sizeof name) == DL_OK) {
        check_name(name);

        char path[DL_NAME_MAX + 64];
        const char *dir = "/tmp/freedom-dl";
        if (dl_build_path(dir, name, path, sizeof path) == DL_OK) {
            size_t dlen = strlen(dir);
            if (strncmp(path, dir, dlen) != 0) abort();
            if (path[dlen] != '/') abort();
            const char *tail = path + dlen + 1;
            if (strchr(tail, '/') != NULL) abort();
            if (tail[0] == '.') abort();
        }
    }

    free(buf);
    return 0;
}
