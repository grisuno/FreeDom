/*
 * freedom-view — minimal end-to-end demo: parse a local HTML file with the
 * inert html_parse pipeline and render its title + extracted text in a
 * scrollable Wayland window.
 *
 * Visual test (on a Wayland session): ./build/freedom-view page.html
 * This is a demo harness, not part of the unit-tested core.
 */

#define _POSIX_C_SOURCE 200809L

#include "html_parse.h"
#include "ui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Reads the whole file into a NUL-terminated buffer. Caller frees. */
static char *read_file(const char *path, size_t *out_len) {
    FILE *f = fopen(path, "rb");
    if (f == NULL) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    rewind(f);

    char *buf = (char *)malloc((size_t)sz + 1);
    if (buf == NULL) { fclose(f); return NULL; }
    size_t n = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    buf[n] = '\0';
    if (out_len != NULL) *out_len = n;
    return buf;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <file.html>\n", argv[0]);
        return 2;
    }

    size_t html_len = 0;
    char *html = read_file(argv[1], &html_len);
    if (html == NULL) {
        fprintf(stderr, "freedom-view: cannot read '%s'\n", argv[1]);
        return 1;
    }

    hp_document *doc = NULL;
    hp_status ps = hp_parse(html, html_len, NULL, &doc);
    free(html);
    if (ps != HP_OK) {
        fprintf(stderr, "freedom-view: parse failed (status %d)\n", ps);
        return 1;
    }

    size_t title_len = 0, text_len = 0;
    char *title = hp_get_title(doc, &title_len);
    char *text = hp_extract_text(doc, &text_len);
    hp_document_free(doc);

    const char *win_title = (title != NULL && title_len > 0) ? title : "Freedom";
    ui_status us = ui_run_text_view(win_title,
                                    (text != NULL) ? text : "",
                                    (text != NULL) ? text_len : 0);

    hp_free(title);
    hp_free(text);

    if (us == UI_ERR_DISPLAY) {
        fprintf(stderr, "freedom-view: no Wayland display (set WAYLAND_DISPLAY)\n");
        return 1;
    }
    return (us == UI_OK) ? 0 : 1;
}
