/*
 * pdf_export — pure helpers for "save the current page as a vector PDF".
 *
 * Pure, I/O-free, reentrant. The hostile page title is sanitized into a safe
 * filename (fail closed: no path separators, no traversal, no leading dot) and
 * the document rows are paginated deterministically. See spec/pdf_export.md.
 */

#include "pdf_export.h"

#include <string.h>

/* Bytes preserved verbatim in a filename basename. Everything else maps to '_'. */
static int pe_is_kept(unsigned char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
        || (c >= '0' && c <= '9') || c == '.' || c == '_' || c == '-';
}

/* Bytes trimmed from both ends so a name cannot start/end with a separator, a
 * dot (no hidden files / no "..") or a dash. */
static int pe_is_edge(unsigned char c) {
    return c == '_' || c == '.' || c == '-';
}

pe_status pe_safe_basename(const char *title, char *out, size_t outsz) {
    if (out == NULL || outsz == 0) return PE_ERR_NULL_ARG;

    /* Sanitize into a fixed local buffer bounded by PE_NAME_MAX, then copy to the
     * caller's buffer (fail closed if it does not fit). */
    char tmp[PE_NAME_MAX + 1];
    size_t n = 0;
    int prev_us = 0; /* the previous emitted byte was a collapsed '_' */

    if (title != NULL) {
        for (size_t i = 0; title[i] != '\0' && n < PE_NAME_MAX; ++i) {
            unsigned char c = (unsigned char)title[i];
            if (pe_is_kept(c)) {
                tmp[n++] = (char)c;
                prev_us = 0;
            } else if (!prev_us) {
                tmp[n++] = '_'; /* map any other byte to '_', collapsing runs */
                prev_us = 1;
            }
        }
    }
    tmp[n] = '\0';

    size_t start = 0;
    while (start < n && pe_is_edge((unsigned char)tmp[start])) ++start;
    size_t end = n;
    while (end > start && pe_is_edge((unsigned char)tmp[end - 1])) --end;

    const char *name = tmp + start;
    size_t name_len = end - start;
    if (name_len == 0) {
        name = PE_FALLBACK_NAME;
        name_len = strlen(PE_FALLBACK_NAME);
    }

    if (name_len + 1 > outsz) { out[0] = '\0'; return PE_ERR_OVERFLOW; }
    memcpy(out, name, name_len);
    out[name_len] = '\0';
    return PE_OK;
}

pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,
                            char *out, size_t outsz) {
    if (dir == NULL || out == NULL || outsz == 0) return PE_ERR_NULL_ARG;
    if (ext == NULL) ext = "";

    char base[PE_NAME_MAX + 1];
    pe_status st = pe_safe_basename(title, base, sizeof base);
    if (st != PE_OK) { out[0] = '\0'; return st; } /* base always fits PE_NAME_MAX+1 */

    size_t dlen = strlen(dir);
    int need_slash = (dlen > 0 && dir[dlen - 1] != '/');
    size_t blen = strlen(base);
    size_t extlen = strlen(ext);
    size_t total = dlen + (size_t)(need_slash ? 1 : 0) + blen + extlen; /* excl. NUL */
    if (total + 1 > outsz) { out[0] = '\0'; return PE_ERR_OVERFLOW; }

    size_t pos = 0;
    memcpy(out + pos, dir, dlen); pos += dlen;
    if (need_slash) out[pos++] = '/';
    memcpy(out + pos, base, blen); pos += blen;
    memcpy(out + pos, ext, extlen); pos += extlen;
    out[pos] = '\0';
    return PE_OK;
}

pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz) {
    return pe_build_path_ext(dir, title, PE_EXT, out, outsz);
}

size_t pe_paginate(const double *tops, const double *heights, size_t n,
                   double page_h, int *out_page, double *out_page_y) {
    if (tops == NULL || heights == NULL || out_page == NULL || out_page_y == NULL) return 0;
    if (n == 0 || page_h <= 0.0) return 0;

    int page = 0;
    double offset = 0.0; /* document-Y mapped to the top (y == 0) of the current page */
    for (size_t i = 0; i < n; ++i) {
        double y = tops[i] - offset;
        /* Break to a fresh page only if the row would overflow AND is not already
         * at the page top (an oversized row keeps its own page and overflows). */
        if (y > 0.0 && y + heights[i] > page_h) {
            ++page;
            offset = tops[i];
            y = 0.0;
        }
        out_page[i] = page;
        out_page_y[i] = y;
    }
    return (size_t)page + 1;
}
