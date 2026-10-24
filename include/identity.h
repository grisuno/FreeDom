#ifndef FREEDOM_IDENTITY_H
#define FREEDOM_IDENTITY_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * identity -- user-configurable identity and sensitive-API settings (spec/identity.md).
 * Pure: no I/O, no global state, reentrant. The default IS the anti_fp normalized
 * identity; every override is an explicit, validated, opt-in user choice.
 */

#define IDN_UA_MAX        256   /* user_agent buffer, terminator included */
#define IDN_LANG_MAX      128   /* languages buffer, terminator included */
#define IDN_LANG_TAGS_MAX 8
#define IDN_SERIAL_MAX    1024  /* longest idn_serialize output, terminator included */
#define IDN_PAGE_MAX      16384 /* about:config page buffer the GUI provides */

#define IDN_GEO_ACC_MIN 1.0
#define IDN_GEO_ACC_MAX 100000.0

typedef enum idn_geo_mode {
    IDN_GEO_OFF = 0,   /* navigator.geolocation does not exist */
    IDN_GEO_FIXED = 1  /* trusted hosts get the user's fixed coordinates */
} idn_geo_mode;

/* Rejected-field mask returned by idn_apply_query. */
enum {
    IDN_REJ_UA   = 1 << 0,
    IDN_REJ_LANG = 1 << 1,
    IDN_REJ_GEO  = 1 << 2
};

typedef struct idn_config {
    char   user_agent[IDN_UA_MAX];  /* "" = FP_USER_AGENT */
    char   languages[IDN_LANG_MAX]; /* "" = the anti_fp default; comma-separated tags */
    int    geo_mode;                /* idn_geo_mode */
    double geo_lat, geo_lon, geo_accuracy_m;
} idn_config;

/* The anti_fp identity, geolocation off. NULL-safe. */
void idn_defaults(idn_config *c);

/* 1 when c carries no override at all (NULL counts as default). */
int idn_is_default(const idn_config *c);

/* Validated setters: 0 on success, -1 (c untouched) when the value is not representable. */
int idn_set_user_agent(idn_config *c, const char *ua);
int idn_set_languages(idn_config *c, const char *list);
int idn_set_geo(idn_config *c, double lat, double lon, double accuracy_m);
void idn_clear_geo(idn_config *c);

/* Effective values: the override, else the anti_fp default. Never NULL / always terminated. */
const char *idn_user_agent(const idn_config *c);
size_t idn_accept_language(const idn_config *c, char *out, size_t cap);
size_t idn_primary_language(const idn_config *c, char *out, size_t cap);

/* One-line text form for prefs and the worker IPC. Returns the length (0 on cap overflow,
 * out then ""). */
size_t idn_serialize(const idn_config *c, char *out, size_t cap);

/* Parses idn_serialize output field by field; an invalid field keeps its default. Always
 * leaves c valid. */
void idn_parse(idn_config *c, const char *text);

/* Applies a GET-form query (spec/identity.md). Returns the IDN_REJ_* mask. */
unsigned idn_apply_query(idn_config *c, const char *query);

/* Writes the about:config HTML. Returns its length (0 when cap is too small, out ""). */
size_t idn_render_page(const idn_config *c, char *out, size_t cap);

#endif
