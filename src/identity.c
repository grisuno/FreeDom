/*
 * identity -- implementation of the user identity settings (spec/identity.md).
 * Pure and reentrant: no I/O, no globals. Validation is fail-closed: a value that is not
 * representable is rejected and the configuration is left exactly as it was.
 */

#define _GNU_SOURCE
#include "identity.h"

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "anti_fp.h"

#define IDN_QUERY_FIELD_MAX (IDN_UA_MAX * 3u) /* decoded query value cap */

static int is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
static int is_alnum(char c) { return is_alpha(c) || (c >= '0' && c <= '9'); }

void idn_defaults(idn_config *c) {
    if (c == NULL) return;
    memset(c, 0, sizeof *c);
    c->geo_mode = IDN_GEO_OFF;
}

int idn_is_default(const idn_config *c) {
    if (c == NULL) return 1;
    return c->user_agent[0] == '\0' && c->languages[0] == '\0' && c->geo_mode == IDN_GEO_OFF
           && c->auto_allow == 0;
}

int idn_set_user_agent(idn_config *c, const char *ua) {
    if (c == NULL || ua == NULL) return -1;
    size_t n = strlen(ua);
    if (n >= IDN_UA_MAX) return -1;
    int printable = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned char ch = (unsigned char)ua[i];
        if (ch < 0x20 || ch > 0x7e) return -1;   /* controls (header injection) and non-ASCII */
        if (ch != ' ') printable = 1;
    }
    if (n != 0 && !printable) return -1;
    memcpy(c->user_agent, ua, n + 1);
    return 0;
}

/* Validates one language tag [s, s+n): aa|aaa then (-[alnum]{2,8})*. */
static int tag_valid(const char *s, size_t n) {
    size_t i = 0;
    while (i < n && is_alpha(s[i])) ++i;
    if (i < 2 || i > 3) return 0;
    while (i < n) {
        if (s[i] != '-') return 0;
        size_t j = ++i;
        while (i < n && is_alnum(s[i])) ++i;
        if (i - j < 2 || i - j > 8) return 0;
    }
    return 1;
}

int idn_set_languages(idn_config *c, const char *list) {
    if (c == NULL || list == NULL) return -1;
    char norm[IDN_LANG_MAX];
    size_t out = 0;
    unsigned tags = 0;
    const char *p = list;
    while (*p == ' ') ++p;
    if (*p == '\0') { c->languages[0] = '\0'; return 0; }
    for (;;) {
        const char *start = p;
        while (*p != '\0' && *p != ',') ++p;
        const char *end = p;
        while (end > start && end[-1] == ' ') --end;
        size_t n = (size_t)(end - start);
        if (!tag_valid(start, n) || ++tags > IDN_LANG_TAGS_MAX) return -1;
        if (out + n + 2 > sizeof norm) return -1;
        if (out != 0) norm[out++] = ',';
        memcpy(norm + out, start, n);
        out += n;
        if (*p == '\0') break;
        ++p;                                  /* skip ',' */
        while (*p == ' ') ++p;
    }
    norm[out] = '\0';
    memcpy(c->languages, norm, out + 1);
    return 0;
}

int idn_set_geo(idn_config *c, double lat, double lon, double accuracy_m) {
    if (c == NULL) return -1;
    if (!isfinite(lat) || !isfinite(lon) || !isfinite(accuracy_m)) return -1;
    if (lat < -90.0 || lat > 90.0 || lon < -180.0 || lon > 180.0) return -1;
    if (accuracy_m < IDN_GEO_ACC_MIN || accuracy_m > IDN_GEO_ACC_MAX) return -1;
    c->geo_mode = IDN_GEO_FIXED;
    c->geo_lat = lat;
    c->geo_lon = lon;
    c->geo_accuracy_m = accuracy_m;
    return 0;
}

void idn_clear_geo(idn_config *c) {
    if (c == NULL) return;
    c->geo_mode = IDN_GEO_OFF;
    c->geo_lat = c->geo_lon = c->geo_accuracy_m = 0.0;
}

const char *idn_user_agent(const idn_config *c) {
    return (c != NULL && c->user_agent[0] != '\0') ? c->user_agent : fp_user_agent();
}

size_t idn_accept_language(const idn_config *c, char *out, size_t cap) {
    if (out == NULL || cap == 0) return 0;
    out[0] = '\0';
    if (c == NULL || c->languages[0] == '\0') {
        const char *d = fp_accept_language_header();
        size_t n = strlen(d);
        if (n >= cap) return 0;
        memcpy(out, d, n + 1);
        return n;
    }
    size_t n = 0;
    int q = 10;
    const char *p = c->languages;
    while (*p != '\0') {
        const char *e = strchr(p, ',');
        size_t tl = (e != NULL) ? (size_t)(e - p) : strlen(p);
        int r;
        size_t space = cap - n;
        if (space == 0) { out[0] = '\0'; return 0; }
        if (n == 0) r = snprintf(out + n, space, "%.*s", (int)tl, p);
        else        r = snprintf(out + n, space, ",%.*s;q=0.%d", (int)tl, p, q > 1 ? q - 1 : 1);
        if (r < 0 || (size_t)r >= space) { out[0] = '\0'; return 0; }
        if (n != 0 && q > 1) --q;               /* the first tag carries no q */
        n += (size_t)r;
        p += tl;
        if (*p == ',') ++p;
    }
    return n;
}

size_t idn_primary_language(const idn_config *c, char *out, size_t cap) {
    if (out == NULL || cap == 0) return 0;
    out[0] = '\0';
    const char *src = (c != NULL && c->languages[0] != '\0') ? c->languages : fp_accept_language();
    const char *e = strchr(src, ',');
    size_t n = (e != NULL) ? (size_t)(e - src) : strlen(src);
    if (n >= cap) return 0;
    memcpy(out, src, n);
    out[n] = '\0';
    return n;
}

/* --- percent codec for the one-line form --- */

static int hexval(int ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
    if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
    return -1;
}

/* Decodes %XX (and '+' when plus) from [s, s+n) into out. Returns the length, or -1 when the
 * result does not fit in cap-1 bytes or a %-escape is malformed. */
static long pct_decode(const char *s, size_t n, char *out, size_t cap, int plus) {
    size_t o = 0;
    for (size_t i = 0; i < n; ++i) {
        char ch = s[i];
        if (ch == '%') {
            if (i + 2 >= n) return -1;
            int hi = hexval((unsigned char)s[i + 1]), lo = hexval((unsigned char)s[i + 2]);
            if (hi < 0 || lo < 0) return -1;
            ch = (char)(hi * 16 + lo);
            i += 2;
        } else if (plus && ch == '+') {
            ch = ' ';
        }
        if (o + 1 >= cap) return -1;
        out[o++] = ch;
    }
    out[o] = '\0';
    return (long)o;
}

static int append(char *buf, size_t *n, size_t cap, const char *fmt, ...) {
    if (*n >= cap) return -1;
    va_list ap;
    va_start(ap, fmt);
    int r = vsnprintf(buf + *n, cap - *n, fmt, ap);
    va_end(ap);
    if (r < 0 || (size_t)r >= cap - *n) { *n = cap; return -1; }
    *n += (size_t)r;
    return 0;
}

static int append_pct(char *buf, size_t *n, size_t cap, const char *s) {
    for (; *s != '\0'; ++s) {
        unsigned char ch = (unsigned char)*s;
        int bad = (ch == '|' || ch == '%' || ch < 0x20 || ch > 0x7e);
        if (append(buf, n, cap, bad ? "%%%02X" : "%c", bad ? (unsigned)ch : (int)ch) != 0) return -1;
    }
    return 0;
}

size_t idn_serialize(const idn_config *c, char *out, size_t cap) {
    if (out == NULL || cap == 0) return 0;
    out[0] = '\0';
    if (c == NULL) return 0;
    size_t n = 0;
    if (append(out, &n, cap, "ua=") != 0 || append_pct(out, &n, cap, c->user_agent) != 0
        || append(out, &n, cap, "|lang=") != 0 || append_pct(out, &n, cap, c->languages) != 0
        || append(out, &n, cap, "|geo=") != 0) { out[0] = '\0'; return 0; }
    if (c->geo_mode == IDN_GEO_FIXED
        && append(out, &n, cap, "%.6f,%.6f,%.1f", c->geo_lat, c->geo_lon, c->geo_accuracy_m) != 0) {
        out[0] = '\0';
        return 0;
    }
    if (c->auto_allow != 0 && append(out, &n, cap, "|aa=%u", c->auto_allow & IDN_AA_ALL) != 0) {
        out[0] = '\0';
        return 0;
    }
    return n;
}

/* Parses "lat,lon,acc" strictly; 0 on success. */
static int parse_geo(const char *s, double *lat, double *lon, double *acc) {
    char *e = NULL;
    *lat = strtod(s, &e);
    if (e == s || *e != ',') return -1;
    s = e + 1;
    *lon = strtod(s, &e);
    if (e == s || *e != ',') return -1;
    s = e + 1;
    *acc = strtod(s, &e);
    if (e == s || *e != '\0') return -1;
    return 0;
}

void idn_parse(idn_config *c, const char *text) {
    if (c == NULL) return;
    idn_defaults(c);
    if (text == NULL) return;
    const char *p = text;
    while (*p != '\0') {
        const char *e = strchr(p, '|');
        size_t sl = (e != NULL) ? (size_t)(e - p) : strlen(p);
        const char *eq = memchr(p, '=', sl);
        if (eq != NULL) {
            size_t kl = (size_t)(eq - p);
            const char *val = eq + 1;
            size_t vl = sl - kl - 1;
            char dec[IDN_QUERY_FIELD_MAX];
            if (kl == 2 && memcmp(p, "ua", 2) == 0) {
                if (pct_decode(val, vl, dec, sizeof dec, 0) >= 0) (void)idn_set_user_agent(c, dec);
            } else if (kl == 4 && memcmp(p, "lang", 4) == 0) {
                if (pct_decode(val, vl, dec, sizeof dec, 0) >= 0) (void)idn_set_languages(c, dec);
            } else if (kl == 2 && memcmp(p, "aa", 2) == 0 && vl == 1 && val[0] >= '0' && val[0] <= '7') {
                c->auto_allow = (unsigned)(val[0] - '0');
            } else if (kl == 3 && memcmp(p, "geo", 3) == 0 && vl > 0 && vl < sizeof dec) {
                memcpy(dec, val, vl);
                dec[vl] = '\0';
                double la, lo, ac;
                if (parse_geo(dec, &la, &lo, &ac) == 0) (void)idn_set_geo(c, la, lo, ac);
            }
        }
        if (e == NULL) break;
        p = e + 1;
    }
}

/* --- GET-form query --- */

static int parse_number(const char *s, double *out) {
    if (s[0] == '\0') return -1;
    char *e = NULL;
    *out = strtod(s, &e);
    return (*e == '\0') ? 0 : -1;
}

unsigned idn_apply_query(idn_config *c, const char *query) {
    if (c == NULL || query == NULL) return 0;
    char ua[IDN_QUERY_FIELD_MAX], lang[IDN_QUERY_FIELD_MAX], geo[32], lat[64], lon[64], acc[64];
    int has_ua = 0, has_lang = 0, has_geo = 0, has_lat = 0, has_lon = 0, has_acc = 0, reset = 0;
    int has_aa = 0;
    unsigned aa_bits = 0;
    unsigned rej = 0;
    const char *p = query;
    if (*p == '?') ++p;
    while (*p != '\0') {
        const char *amp = strchr(p, '&');
        size_t sl = (amp != NULL) ? (size_t)(amp - p) : strlen(p);
        const char *eq = memchr(p, '=', sl);
        if (eq != NULL && eq != p) {
            char key[16];
            size_t kl = (size_t)(eq - p);
            if (kl < sizeof key && pct_decode(p, kl, key, sizeof key, 1) >= 0) {
                const char *val = eq + 1;
                size_t vl = sl - kl - 1;
                if (strcmp(key, "ua") == 0) {
                    has_ua = 1;
                    if (pct_decode(val, vl, ua, sizeof ua, 1) < 0) { ua[0] = '\x01'; ua[1] = '\0'; }
                } else if (strcmp(key, "lang") == 0) {
                    has_lang = 1;
                    if (pct_decode(val, vl, lang, sizeof lang, 1) < 0) { lang[0] = '\x01'; lang[1] = '\0'; }
                } else if (strcmp(key, "geo") == 0) {
                    has_geo = 1;
                    if (pct_decode(val, vl, geo, sizeof geo, 1) < 0) strcpy(geo, "?");
                } else if (strcmp(key, "lat") == 0) {
                    has_lat = 1;
                    if (pct_decode(val, vl, lat, sizeof lat, 1) < 0) strcpy(lat, "?");
                } else if (strcmp(key, "lon") == 0) {
                    has_lon = 1;
                    if (pct_decode(val, vl, lon, sizeof lon, 1) < 0) strcpy(lon, "?");
                } else if (strcmp(key, "acc") == 0) {
                    has_acc = 1;
                    if (pct_decode(val, vl, acc, sizeof acc, 1) < 0) strcpy(acc, "?");
                } else if (strcmp(key, "aa") == 0 && vl == 1 && val[0] == '1') {
                    has_aa = 1;   /* the config form's marker: absent boxes then mean OFF */
                } else if (strcmp(key, "aacss") == 0) { aa_bits |= IDN_AA_CSS;
                } else if (strcmp(key, "aajs") == 0)  { aa_bits |= IDN_AA_JS;
                } else if (strcmp(key, "aares") == 0) { aa_bits |= IDN_AA_RES;
                } else if (strcmp(key, "reset") == 0 && vl == 1 && val[0] == '1') {
                    reset = 1;
                }
            }
        }
        if (amp == NULL) break;
        p = amp + 1;
    }
    if (reset) { idn_defaults(c); return 0; }
    if (has_aa) c->auto_allow = aa_bits;
    if (has_ua && idn_set_user_agent(c, ua) != 0) rej |= IDN_REJ_UA;
    if (has_lang && idn_set_languages(c, lang) != 0) rej |= IDN_REJ_LANG;
    if (has_geo || has_lat || has_lon || has_acc) {
        /* An empty field is "not given": the page's form sends all three, blank = off. */
        int gl = has_lat && lat[0] != '\0', go = has_lon && lon[0] != '\0', ga = has_acc && acc[0] != '\0';
        int off = has_geo ? strcmp(geo, "off") == 0 : (!gl && !go && !ga);
        int fixed = has_geo ? strcmp(geo, "fixed") == 0 : 1;   /* coordinates alone mean fixed */
        if (off) {
            idn_clear_geo(c);
        } else if (!fixed) {
            rej |= IDN_REJ_GEO;
        } else {
            double la = c->geo_lat, lo = c->geo_lon, ac = c->geo_accuracy_m;
            int ok = 1;
            if (gl) ok = ok && parse_number(lat, &la) == 0;
            if (go) ok = ok && parse_number(lon, &lo) == 0;
            if (ga) ok = ok && parse_number(acc, &ac) == 0;
            if (c->geo_mode != IDN_GEO_FIXED && !(gl && go && ga)) ok = 0;
            if (c->geo_mode == IDN_GEO_FIXED && !has_geo && !(gl && go && ga)) ok = 0;
            if (!ok || idn_set_geo(c, la, lo, ac) != 0) rej |= IDN_REJ_GEO;
        }
    }
    return rej;
}

/* --- about:config page --- */

static int esc_append(char *buf, size_t *n, size_t cap, const char *s) {
    for (; *s != '\0'; ++s) {
        const char *r = NULL;
        switch (*s) {
            case '&':  r = "&amp;"; break;
            case '<':  r = "&lt;"; break;
            case '>':  r = "&gt;"; break;
            case '"':  r = "&quot;"; break;
            case '\'': r = "&#39;"; break;
            default: break;
        }
        if ((r != NULL) ? append(buf, n, cap, "%s", r) != 0 : append(buf, n, cap, "%c", *s) != 0) return -1;
    }
    return 0;
}

size_t idn_render_page(const idn_config *c, char *out, size_t cap) {
    if (out == NULL || cap == 0) return 0;
    out[0] = '\0';
    idn_config def;
    idn_defaults(&def);
    if (c == NULL) c = &def;
    size_t n = 0;
    char lang[IDN_LANG_MAX];
    (void)idn_primary_language(c, lang, sizeof lang);
    int fixed = (c->geo_mode == IDN_GEO_FIXED);
    int bad = 0;
    bad |= append(out, &n, cap,
        "<!doctype html><html><head><meta charset=\"utf-8\"><title>Freedom configuration</title></head><body>"
        "<h1>Freedom configuration</h1>"
        "<p>The default identity is the same for every Freedom user, which is what keeps you in the crowd. "
        "Anything you change here makes you more distinguishable: it is your choice, it is stored only in your "
        "encrypted local profile, and it is never sent anywhere except as the header or API value you set.</p>"
        "<form method=\"get\" action=\"about:config\"><h2>Identity</h2>"
        "<p>User-Agent (blank = Freedom default): <input type=\"text\" name=\"ua\" value=\"") != 0;
    bad |= esc_append(out, &n, cap, c->user_agent) != 0;
    bad |= append(out, &n, cap, "\" size=\"80\"></p><p>In use: <code>") != 0;
    bad |= esc_append(out, &n, cap, idn_user_agent(c)) != 0;
    bad |= append(out, &n, cap, "</code></p><p>Languages (comma separated, blank = %s): <input type=\"text\" name=\"lang\" value=\"",
                  fp_accept_language()) != 0;
    bad |= esc_append(out, &n, cap, c->languages) != 0;
    bad |= append(out, &n, cap, "\" size=\"40\"></p><p>Primary language in use: <code>") != 0;
    bad |= esc_append(out, &n, cap, lang) != 0;
    bad |= append(out, &n, cap,
        "</code></p><h2>Geolocation</h2>"
        "<p>navigator.geolocation exists only on sites you allowed with both allow.conf and js.conf, and it "
        "answers with exactly the place you write here; no sensor and no network lookup is ever used.</p>"
        "<p>Currently: <code>%s</code>. Leave the three boxes empty to turn it off.</p>"
        "<p>Latitude: <input type=\"text\" name=\"lat\" value=\"", fixed ? "fixed place" : "off") != 0;
    if (fixed) bad |= append(out, &n, cap, "%.6f", c->geo_lat) != 0;
    bad |= append(out, &n, cap, "\" size=\"12\"> Longitude: <input type=\"text\" name=\"lon\" value=\"") != 0;
    if (fixed) bad |= append(out, &n, cap, "%.6f", c->geo_lon) != 0;
    bad |= append(out, &n, cap, "\" size=\"12\"> Accuracy in metres: <input type=\"text\" name=\"acc\" value=\"") != 0;
    if (fixed) bad |= append(out, &n, cap, "%.0f", c->geo_accuracy_m) != 0;
    bad |= append(out, &n, cap,
        "\" size=\"8\"></p><h2>Auto-allow CDN hosts</h2>"
        "<p>When a site you put on allow.conf pulls a stylesheet, a script or another resource from a "
        "different host, that host is appended to allow.conf so the site looks right and you can see and "
        "edit it. Allowed means allowed: the host gets the same sovereignty as any allow.conf entry (the "
        "certificate is still always verified). A host on block.conf stays blocked. Off by default.</p>"
        "<input type=\"hidden\" name=\"aa\" value=\"1\">"
        "<p><label><input type=\"checkbox\" name=\"aacss\"") != 0;
    bad |= append(out, &n, cap, "%s> stylesheets (CSS)</label></p>", (c->auto_allow & IDN_AA_CSS) ? " checked" : "") != 0;
    bad |= append(out, &n, cap, "<p><label><input type=\"checkbox\" name=\"aajs\"%s> scripts (JS)</label></p>",
                  (c->auto_allow & IDN_AA_JS) ? " checked" : "") != 0;
    bad |= append(out, &n, cap, "<p><label><input type=\"checkbox\" name=\"aares\"%s> other resources (images, fonts, media, data)</label></p>",
                  (c->auto_allow & IDN_AA_RES) ? " checked" : "") != 0;
    bad |= append(out, &n, cap,
        "<p><input type=\"submit\" value=\"Apply\"></p></form>"
        "<form method=\"get\" action=\"about:config\"><input type=\"hidden\" name=\"reset\" value=\"1\">"
        "<p><input type=\"submit\" value=\"Reset everything to the Freedom default\"></p></form>"
        "<h2>Not available in this engine</h2><ul>"
        "<li>WebGL: not available. Freedom has no GL renderer; a switch here would promise something that does not exist.</li>"
        "<li>Service Workers: not available. There is no background worker; pages that need one fall back to plain loading.</li>"
        "</ul></body></html>") != 0;
    if (bad) { out[0] = '\0'; return 0; }
    return n;
}
