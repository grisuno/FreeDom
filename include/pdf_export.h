#ifndef FREEDOM_PDF_EXPORT_H
#define FREEDOM_PDF_EXPORT_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * pdf_export — pure helpers for "save the current page as a vector PDF".
 *
 * Cairo can redirect its output from the screen to a cairo_pdf_surface_t and
 * re-draw the same render_doc display list into a vector PDF: selectable,
 * searchable text with infinite zoom (not a screenshot). The Cairo I/O is the
 * GUI orchestrator's job; what lives here is the directly auditable surface:
 *
 *   1. The output filename is derived from the page TITLE, which is hostile
 *      remote content. A title like "../../.bashrc", with control bytes or path
 *      separators, must never escape the output directory or name an arbitrary
 *      file. Secure by Default / fail closed: an unsafe name is not representable.
 *   2. Pagination (laying rows of known height onto fixed-height pages without
 *      splitting a row) is deterministic math, testable without Cairo.
 *
 * Pure, I/O-free, reentrant, no global state. See spec/pdf_export.md.
 */

#define PE_NAME_MAX       128u    /* max bytes of the sanitized basename (excl. extension) */
#define PE_EXT            ".pdf"
#define PE_EXT_PNG        ".png"  /* raster export (visual review): see ui_render_png */
#define PE_FALLBACK_NAME  "page"  /* used when the title yields nothing usable */

typedef enum pe_status {
    PE_OK = 0,
    PE_ERR_NULL_ARG, /* a required pointer was NULL / outsz == 0 */
    PE_ERR_OVERFLOW  /* the result did not fit; out left empty (fail closed) */
} pe_status;

/* Sanitizes a hostile page title into a safe filename base (no extension, no path
 * separators, no leading dot). Keeps [A-Za-z0-9._-]; maps every other byte
 * (including '/', '\\', spaces, control bytes and non-ASCII >= 0x80) to '_';
 * collapses runs of '_'; trims '_'/'.'/'-' from both ends; bounds the length to
 * PE_NAME_MAX. If nothing usable remains (NULL/empty/all separators), writes
 * PE_FALLBACK_NAME. The result is always non-empty and NUL-terminated unless
 * out == NULL / outsz == 0 (PE_ERR_NULL_ARG) or outsz cannot hold even the
 * fallback (PE_ERR_OVERFLOW, out left empty). title == NULL is treated as empty.
 * Does NOT append the extension (that is pe_build_path's job). */
pe_status pe_safe_basename(const char *title, char *out, size_t outsz);

/* Builds the full output path dir + "/" + pe_safe_basename(title) + ext into out.
 * dir is trusted (chosen by the app from XDG/$HOME); title is hostile. ext is a
 * trusted literal (e.g. PE_EXT / PE_EXT_PNG); ext == NULL is treated as "" (no
 * extension). A trailing '/' on dir is respected (not duplicated). Because the
 * basename can hold no '/', the result cannot escape dir (no traversal) by
 * construction. Fails closed on overflow (out left empty). dir/out NULL or
 * outsz == 0 => PE_ERR_NULL_ARG. */
pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,
                            char *out, size_t outsz);

/* pe_build_path_ext with the default PDF extension (PE_EXT). */
pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz);

/* Deterministic pagination: lays the rows (document-space tops + heights, in
 * order) onto pages of usable height page_h without ever splitting a row. Writes
 * out_page[i] (0-based page index) and out_page_y[i] (y within that page) for each
 * of the n rows. Returns the page count (last page + 1), or 0 if n == 0,
 * page_h <= 0, or any pointer is NULL. A row taller than page_h gets its own page
 * starting at y == 0 and overflows (it is not split). Vertical gaps between rows
 * are preserved within a page. */
size_t pe_paginate(const double *tops, const double *heights, size_t n,
                   double page_h, int *out_page, double *out_page_y);

#endif /* FREEDOM_PDF_EXPORT_H */
