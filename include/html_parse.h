#ifndef FREEDOM_HTML_PARSE_H
#define FREEDOM_HTML_PARSE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * html_parse — turns untrusted HTML into an inert, queryable DOM.
 *
 * First Zero-Trust boundary after the network: remote content is hostile by
 * default. The parser never executes scripts; by default it strips <script>
 * nodes and inline on* event-handler attributes from the tree.
 *
 * The Lexbor backend is fully encapsulated: no lxb_* type appears here.
 * See spec/html_parse.md for the full contract.
 */

typedef enum hp_status {
    HP_OK = 0,
    HP_ERR_NULL_ARG,   /* a required pointer argument was NULL */
    HP_ERR_EMPTY,      /* input length was zero */
    HP_ERR_TOO_LARGE,  /* input exceeded max_bytes */
    HP_ERR_PARSE,      /* backend failed to create or parse the document */
    HP_ERR_OOM,        /* allocation failed */
    HP_ERR_INTERNAL    /* backend returned an unexpected state */
} hp_status;

typedef struct hp_config {
    size_t max_bytes;            /* hard cap on input; 0 => HP_DEFAULT_MAX_BYTES */
    int    strip_scripts;        /* nonzero (default): remove <script> nodes */
    int    strip_event_handlers; /* nonzero (default): remove inline on* attributes */
} hp_config;

/* Opaque parsed document. */
typedef struct hp_document hp_document;

#define HP_DEFAULT_MAX_BYTES ((size_t)(32u * 1024u * 1024u))

/* Returns a configuration with the secure defaults applied. */
hp_config hp_config_default(void);

/* Pure validator (no parsing): NULL / empty / size-cap checks. */
hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg);

/* Parses untrusted HTML into an inert document and applies the sanitisation
 * policy in cfg (cfg == NULL => secure defaults). No script is ever executed.
 * html == NULL or out == NULL => HP_ERR_NULL_ARG.
 * On HP_OK, *out is set and must be released with hp_document_free. */
hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out);

/* Read-only queries over the (already sanitised) tree. NULL doc => 0. */
size_t hp_element_count(const hp_document *doc);
size_t hp_script_count(const hp_document *doc);
size_t hp_event_handler_count(const hp_document *doc);

/* Owned, NUL-terminated buffers; release with hp_free. *out_len (optional)
 * excludes the trailing NUL. Returns NULL on allocation failure or NULL doc. */
char *hp_extract_text(const hp_document *doc, size_t *out_len);
char *hp_get_title(const hp_document *doc, size_t *out_len);

/* Release a buffer returned by hp_extract_text / hp_get_title. NULL-safe. */
void hp_free(char *buf);

/* Idempotent; safe on NULL and safe to call twice. */
void hp_document_free(hp_document *doc);

/* Internal seam for the dom layer: returns the document's root node as an
 * opaque handle (so html_parse.h stays free of backend types), or NULL. The
 * returned pointer is owned by doc and valid only while doc is alive. The dom
 * module is the only intended consumer; general code should use the queries. */
const void *hp_document_root(const hp_document *doc);

#endif /* FREEDOM_HTML_PARSE_H */
