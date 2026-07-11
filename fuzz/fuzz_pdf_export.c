/*
 * libFuzzer harness for pdf_export (PDF "save as" filename sanitizer).
 *
 * The PDF output filename is derived from the page TITLE, which is hostile remote
 * content. Arbitrary bytes -> pe_safe_basename / pe_build_path must never crash,
 * leak or trigger UB, and must never produce a name that escapes the output
 * directory. The invariants below are asserted so a containment bug aborts here
 * (not only a memory bug).
 *
 * Build & run: make fuzz-pe   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "pdf_export.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void check_basename(const char *name) {
    /* Never a path separator (cannot escape a directory once joined). */
    if (strchr(name, '/') != NULL) abort();
    if (strchr(name, '\\') != NULL) abort();
    /* Never starts with a trim byte: no hidden files, no leading "..". */
    if (name[0] == '.' || name[0] == '_' || name[0] == '-') abort();
    /* Always non-empty and within the length bound. */
    size_t n = strlen(name);
    if (n == 0 || n > PE_NAME_MAX) abort();
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    /* Treat the bytes as a C-string title (NUL-terminated copy). */
    char *title = (char *)malloc(size + 1);
    if (title == NULL) return 0;
    memcpy(title, data, size);
    title[size] = '\0';

    char base[PE_NAME_MAX + 1];
    if (pe_safe_basename(title, base, sizeof base) == PE_OK) {
        check_basename(base);
    }

    char path[PE_NAME_MAX + 64];
    const char *dir = "/tmp/freedom-out";
    if (pe_build_path(dir, title, path, sizeof path) == PE_OK) {
        /* The path must stay under dir: the dir prefix, then exactly one '/', then a
         * single basename segment with no further separator. Containment follows
         * from the segment holding no '/' and not starting with '.' (so it can be
         * neither "." nor ".."); interior dots in a filename are harmless. */
        size_t dlen = strlen(dir);
        if (strncmp(path, dir, dlen) != 0) abort();
        if (path[dlen] != '/') abort();
        const char *tail = path + dlen + 1;
        if (strchr(tail, '/') != NULL) abort();
        if (tail[0] == '.') abort();
    }

    free(title);
    return 0;
}
