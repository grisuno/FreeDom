/* doc_title -- the <title> of a received document that has not been laid out yet
 * (spec/doc_title.md). Pure, bounded, no allocation: runs on the trusted side over
 * hostile bytes. */
#ifndef FREEDOM_DOC_TITLE_H
#define FREEDOM_DOC_TITLE_H

#ifdef __cplusplus
#error "doc_title is C11 only"
#endif

#include <stddef.h>

/* Only this many leading bytes are scanned: a real title lives in <head>. */
#define DT_SCAN_MAX ((size_t)256 * 1024)

/* Writes the text of the document's first <title> into out (NUL-terminated, valid
 * UTF-8, whitespace collapsed and trimmed, bidi controls removed, truncated on a code
 * point boundary). Returns 1 when a non-empty title was written, 0 otherwise (out is
 * "" whenever cap > 0). */
int dt_scan(const char *html, size_t len, char *out, size_t cap);

#endif
