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

/* Upper bound on the number of executable <script> elements returned by
 * hp_extract_script_list. A real page has a handful; the cap is a fail-closed,
 * anti-DoS limit so a hostile document (up to HP_DEFAULT_MAX_BYTES of tiny
 * scripts) cannot force an unbounded eval loop. Scripts beyond the cap are
 * dropped (not executed). */
#define HP_MAX_SCRIPTS ((size_t)4096)

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

/* One executable <script>. Inline: text is a NUL-terminated buffer of `len` bytes
 * (the NUL is not counted in len) and src == NULL. External: src is the RAW,
 * unresolved value of the src attribute (hostile input; the parser never fetches)
 * and text == NULL. Both buffers are owned by the hp_script array. */
typedef struct hp_script {
    char  *text;
    size_t len;
    char  *src;
} hp_script;

/* Returns the executable <script> elements in document order, as an owned array;
 * *out_count receives the number found. Inline scripts carry text; external ones
 * carry their raw src (a <script src> with an inline body lists ONLY the src --
 * browser rule: when src is present the content is ignored). JSON data blocks
 * (type containing "json") and modules (type containing "module") are excluded,
 * fail-closed: import/export cannot run as a classic script. Each entry is a
 * SEPARATE program: the caller must evaluate each one independently, so an
 * uncaught exception in one aborts only that script and not the rest -- exactly
 * as a browser runs <script> elements. (Concatenating them into a single eval
 * would let the first failing script kill all the others.) Whether an external
 * script's bytes may be fetched at all is the tab worker's decision, gated by the
 * trusted parent's policy (spec/tab.md, Hito 24 EXT) -- never this parser's.
 * Only meaningful when the document was parsed with strip_scripts == 0. At most
 * HP_MAX_SCRIPTS scripts are returned (extras are dropped, fail-closed). Returns
 * NULL (with *out_count == 0) when there are no executable scripts or on
 * allocation failure. Release with hp_free_scripts. */
hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count);

/* Releases an array returned by hp_extract_script_list (each text/src and the
 * array). Idempotent on NULL. */
void hp_free_scripts(hp_script *scripts, size_t count);

/* Upper bound on external stylesheets reported per document (a real page uses a
 * handful; extras are dropped, fail-closed anti-DoS). */
#define HP_MAX_STYLESHEETS ((size_t)64)

/* Returns the RAW href of every applicable <link rel=stylesheet>, in document
 * order, as an owned array of NUL-terminated strings; *out_count receives the
 * number found. The parser never fetches: whether those bytes may be requested at
 * all is the tab worker's decision, gated by the trusted parent (spec/tab.md §8).
 * Applicable means: rel contains the whitespace-separated token "stylesheet"
 * (ASCII case-insensitive) and NOT the token "alternate"; href is present and
 * non-empty; and media is absent/empty or mentions "screen"/"all" (anything else,
 * e.g. print, is skipped -- fail closed). Returns NULL (with *out_count == 0)
 * when there are none or on allocation failure. Release with
 * hp_free_stylesheet_hrefs. */
char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count);

/* Releases an array returned by hp_extract_stylesheet_hrefs. Idempotent on NULL. */
void hp_free_stylesheet_hrefs(char **hrefs, size_t count);

/* Release a buffer returned by hp_extract_text / hp_get_title. */
void hp_free(char *buf);

/* Idempotent; safe on NULL and safe to call twice. */
void hp_document_free(hp_document *doc);

/* Internal seam for the dom layer: returns the document's root node as an
 * opaque handle (so html_parse.h stays free of backend types), or NULL. The
 * returned pointer is owned by doc and valid only while doc is alive. The dom
 * module is the only intended consumer; general code should use the queries. */
const void *hp_document_root(const hp_document *doc);

#endif /* FREEDOM_HTML_PARSE_H */
