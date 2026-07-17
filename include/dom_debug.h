#ifndef FREEDOM_DOM_DEBUG_H
#define FREEDOM_DOM_DEBUG_H

#include <stddef.h>

#include "render_doc.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * dom_debug (dd_) — a deterministic, agent-readable dump of the paint-ready render
 * tree (rd_doc): the block list and the box-definition tree, with each block's
 * container/box/author-style annotations.
 *
 * Pure, I/O-free: it formats an already-built, inert rd_doc into a caller buffer.
 * No socket, no file, no script, no hostile-DOM walk; the hostile bytes it touches
 * (a block's text/href) were already normalised to valid UTF-8 by page_view. It is
 * the instrument for diagnosing why a node lays out wrong (the "CSS paint gap"),
 * readable headless (freedom --dump-dom, stdout) and, via the PNG export, in the GUI.
 *
 * See spec/dom_debug.md for the full contract.
 */

/* Per-field cap for a variable-length value (block text / href) so one block stays
 * one line and a hostile document cannot blow up the dump. */
#define DD_FIELD_MAX 2048

/* Formats doc into out[0..cap) as a NUL-terminated, line-oriented dump (see the spec
 * for the stable format). Returns the number of bytes that WOULD be written excluding
 * the NUL (snprintf semantics): a value >= cap means the output was truncated. Never
 * writes past out[cap-1]; always NUL-terminates when cap > 0. doc == NULL formats a
 * valid empty tree. out == NULL or cap == 0 only measures (writes nothing). Allocates
 * nothing and cannot fail. */
size_t dd_format(const rd_doc *doc, char *out, size_t cap);

/* CSS inspector: dumps every block with its FULL resolved css_style fields as a
 * compact property list. Designed for Freebug / --dump-css. Same contract as
 * dd_format. */
size_t dd_format_css(const rd_doc *doc, char *out, size_t cap);

#endif /* FREEDOM_DOM_DEBUG_H */
