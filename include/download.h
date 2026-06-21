#ifndef FREEDOM_DOWNLOAD_H
#define FREEDOM_DOWNLOAD_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * download — pure helpers for "save this resource to disk".
 *
 * When the user follows a link to a non-renderable resource (PDF, archive,
 * e-book) or asks to save the current page, Freedom writes the fetched bytes to
 * a file under ~/Downloads/freedom/ instead of rendering them. The disk I/O is
 * the GUI orchestrator's job; what lives here is the directly auditable surface:
 *
 *   1. The output filename is derived from HOSTILE remote input (the
 *      Content-Disposition header and the URL path). A name like "../../.bashrc",
 *      with control bytes or path separators, must never escape the download
 *      directory. Fail closed: an unsafe name is not representable.
 *   2. The render-vs-download decision is a small, testable classification.
 *   3. The size cap is pure arithmetic.
 *
 * Reuses pe_safe_basename (pdf_export) as the single sanitizer. Pure, reentrant,
 * no global state. See spec/download.md.
 */

#define DL_NAME_MAX       128u
#define DL_FALLBACK_NAME  "download"
#define DL_MAX_BYTES      (256u * 1024u * 1024u)   /* 256 MiB hard cap */

typedef enum dl_status {
    DL_OK = 0,
    DL_ERR_NULL_ARG,   /* a required pointer was NULL / outsz == 0 */
    DL_ERR_OVERFLOW,   /* the result did not fit; out left empty (fail closed) */
    DL_ERR_TOO_LARGE   /* body exceeds DL_MAX_BYTES */
} dl_status;

/* 1 if the response should be saved (attachment, or a non-renderable media
 * type), 0 if it should be rendered. NULL/empty content_type renders (preserves
 * behavior for servers that omit it); an unknown/binary type downloads. See spec. */
int dl_should_download(const char *content_type, const char *content_disposition);

/* Conventional dotted extension (".pdf", ".zip", ...) for a known media type
 * (params stripped, case-insensitive), or "" for an unknown one. The pointer is
 * a static string literal (never freed). */
const char *dl_ext_for_type(const char *content_type);

/* Derives a safe download filename into out. Candidate priority: the
 * Content-Disposition filename, then the URL's last path segment, then
 * DL_FALLBACK_NAME. Sanitized via pe_safe_basename (no path separators, no
 * traversal, no leading dot); if the result has no extension and content_type
 * maps to one, it is appended. Always non-empty + NUL-terminated on DL_OK.
 * out == NULL / outsz == 0 => DL_ERR_NULL_ARG; a name that cannot fit =>
 * DL_ERR_OVERFLOW (out left empty). url/content_disposition NULL => absent. */
dl_status dl_pick_name(const char *url, const char *content_disposition,
                       const char *content_type, char *out, size_t outsz);

/* Builds dir + "/" + name into out. dir is trusted; name MUST already be a
 * sanitized basename (a name still containing '/' is rejected => DL_ERR_OVERFLOW,
 * so the path can never escape dir). Trailing '/' on dir respected. Fails closed
 * on overflow. dir/name/out NULL or outsz == 0 => DL_ERR_NULL_ARG. */
dl_status dl_build_path(const char *dir, const char *name, char *out, size_t outsz);

/* DL_OK if len <= DL_MAX_BYTES, else DL_ERR_TOO_LARGE. */
dl_status dl_check_size(size_t len);

#endif /* FREEDOM_DOWNLOAD_H */
