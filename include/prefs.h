#ifndef FREEDOM_PREFS_H
#define FREEDOM_PREFS_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * prefs — pure user-profile model: session preferences, bookmarks and
 * persistent history (Hito 10).
 *
 * Pure logic only (no I/O, no clock, no network): the in-memory state, its
 * versioned text serialization and the fail-closed parse. The encrypted
 * persistence lives in the profile orchestrator (profile.h), which seals
 * this module's text with local_store/disk_store — nothing readable ever
 * lands on disk.
 *
 * Bookmark titles were born in hostile remote content: they are cleaned on
 * entry (control bytes stripped, UTF-8-boundary truncation) and escaped in
 * the generated bookmarks page. URLs with control bytes are not representable
 * (fail closed). See spec/prefs.md for the full contract.
 */

#define PREFS_VERSION       1u
#define PREFS_MAX_URL       1024u   /* mirrors BROWSER_URL_MAX */
#define PREFS_MAX_TITLE     200u    /* cleaned title bytes kept */
#define PREFS_MAX_BOOKMARKS 200u
#define PREFS_MAX_HISTORY   500u
#define PREFS_MAX_TEXT      (2u * 1024u * 1024u)  /* serialized/parsed text cap */

/* Entries of the recent-history section of the bookmarks page. */
#define PREFS_PAGE_HISTORY  50u

typedef enum prefs_status {
    PREFS_OK = 0,
    PREFS_ERR_NULL_ARG,
    PREFS_ERR_FORMAT,   /* unknown magic/version or text over the cap */
    PREFS_ERR_INVALID,  /* URL not representable (empty, control bytes, too long) */
    PREFS_ERR_FULL,     /* bookmark cap reached */
    PREFS_ERR_OOM
} prefs_status;

typedef struct prefs_entry {
    char *url;
    char *title;
} prefs_entry;

typedef struct prefs_state {
    int theme_mode;        /* 0 light, 1 dark, 2 sepia (ui_theme_mode) */
    int force_theme;       /* ignore author colors */
    int images, css;       /* render capabilities (rdp_caps) */
    int reader;            /* distraction-free mode */
    int js_mode;           /* jsp_mode: 0 off, 1 allowlist, 2 on */
    int tor, i2p, torify;  /* opt-in network routing */
    int zoom_pct;          /* zm_clamp owns the ladder bounds */
    int remember_history;  /* 1 = persist visits (default) */
    prefs_entry *bookmarks; size_t bookmarks_len;  /* insertion order */
    char **history;         size_t history_len;    /* most recent first */
} prefs_state;

/* Safe defaults (a virgin session: everything private/off, zoom 100%,
 * remember_history on). NULL-safe. */
void prefs_init(prefs_state *p);

/* Releases owned lists. Idempotent; NULL-safe. */
void prefs_free(prefs_state *p);

/* Serializes p into an owned, NUL-terminated text (*out, *out_len). Free with
 * free(). */
prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len);

/* Parses text[0..len) over an out ALREADY initialised with prefs_init. Unknown
 * magic/version or len > PREFS_MAX_TEXT => PREFS_ERR_FORMAT and out stays at
 * defaults. Unknown keys and malformed lines are skipped (forward compat);
 * out-of-range values are normalised to the safe default. */
prefs_status prefs_parse(const char *text, size_t len, prefs_state *out);

/* Index of the bookmark with exactly that URL, or -1. NULL-safe. */
int prefs_bookmark_index(const prefs_state *p, const char *url);

/* Adds (*added=1) or removes (*added=0) the bookmark for url. The (possibly
 * hostile/NULL) title is cleaned, never a reason to fail. Invalid URL =>
 * PREFS_ERR_INVALID; cap reached => PREFS_ERR_FULL. */
prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,
                                   const char *title, int *added);

/* Records a visit: dedup (an existing entry moves to the front; a visit equal
 * to the front is a no-op), FIFO eviction past PREFS_MAX_HISTORY. Invalid URL
 * => PREFS_ERR_INVALID. */
prefs_status prefs_history_add(prefs_state *p, const char *url);

/* Omnibox autocomplete: up to max_rows distinct URLs matching query (case-
 * insensitive) written to out (rows of row_len bytes, NUL-terminated).
 * Priority: bookmark-prefix, history-prefix, bookmark-substring (URL or
 * title), history-substring; "prefix" also matches past the scheme and a
 * leading "www.". Empty query matches everything (bookmarks first). Returns
 * the count written. Pure. */
int prefs_suggest(const prefs_state *p, const char *query,
                  char *out, size_t row_len, int max_rows);

/* Builds the internal "about:bookmarks" page: bookmarks plus the last
 * PREFS_PAGE_HISTORY visits as links. All hostile text is HTML-escaped; the
 * page is rendered by the normal confined pipeline anyway (defence in depth).
 * *out is owned (free()); NUL-terminated besides *out_len. */
prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len);

#endif /* FREEDOM_PREFS_H */
