/*
 * download — pure helpers for "save this resource to disk".
 * See include/download.h and spec/download.md.
 */

#include "download.h"
#include "pdf_export.h"   /* pe_safe_basename: the single audited sanitizer */

#include <ctype.h>
#include <string.h>

/* ASCII lowercase, locale-independent (the C locale's tolower for bytes < 0x80). */
static int lc(int c) {
    if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
    return c;
}

/* Case-insensitive substring search (ASCII). Returns a pointer into hay or NULL. */
static const char *ci_find(const char *hay, const char *needle) {
    if (hay == NULL || needle == NULL) return NULL;
    size_t nl = strlen(needle);
    if (nl == 0) return hay;
    for (const char *p = hay; *p != '\0'; ++p) {
        size_t i = 0;
        while (i < nl && p[i] != '\0' && lc((unsigned char)p[i]) == lc((unsigned char)needle[i])) ++i;
        if (i == nl) return p;
    }
    return NULL;
}

/* Writes the lowercased media type of content_type (the part before ';', with
 * surrounding spaces trimmed) into buf. Empty/NULL -> empty buf. */
static void media_type(const char *content_type, char *buf, size_t bufsz) {
    if (bufsz == 0) return;
    buf[0] = '\0';
    if (content_type == NULL) return;
    const char *p = content_type;
    while (*p == ' ' || *p == '\t') ++p;
    size_t n = 0;
    for (; *p != '\0' && *p != ';' && n + 1 < bufsz; ++p) {
        if (*p == ' ' || *p == '\t') break;
        buf[n++] = (char)lc((unsigned char)*p);
    }
    buf[n] = '\0';
}

int dl_should_download(const char *content_type, const char *content_disposition) {
    if (ci_find(content_disposition, "attachment") != NULL) return 1;

    char mt[96];
    media_type(content_type, mt, sizeof mt);
    if (mt[0] == '\0') return 0;                       /* missing type: render */
    if (strncmp(mt, "text/", 5) == 0) return 0;        /* any text subtype renders */
    if (strcmp(mt, "application/xhtml+xml") == 0) return 0;
    return 1;                                          /* everything else: save */
}

const char *dl_ext_for_type(const char *content_type) {
    char mt[96];
    media_type(content_type, mt, sizeof mt);
    if (mt[0] == '\0') return "";

    static const struct { const char *type; const char *ext; } MAP[] = {
        { "application/pdf",       ".pdf"  },
        { "application/zip",       ".zip"  },
        { "application/epub+zip",  ".epub" },
        { "application/gzip",      ".gz"   },
        { "application/x-tar",     ".tar"  },
        { "application/json",      ".json" },
        { "text/html",             ".html" },
        { "application/xhtml+xml",  ".html" },
        { "text/plain",            ".txt"  },
        { "image/png",             ".png"  },
        { "image/jpeg",            ".jpg"  },
        { "image/gif",             ".gif"  },
        { "image/svg+xml",         ".svg"  },
    };
    for (size_t i = 0; i < sizeof MAP / sizeof MAP[0]; ++i) {
        if (strcmp(mt, MAP[i].type) == 0) return MAP[i].ext;
    }
    return "";
}

/* Copies [src, end) into buf, bounded and NUL-terminated. */
static void copy_span(const char *src, const char *end, char *buf, size_t bufsz) {
    if (bufsz == 0) return;
    size_t n = 0;
    for (const char *p = src; p < end && n + 1 < bufsz; ++p) buf[n++] = *p;
    buf[n] = '\0';
}

/* Extracts a filename candidate from a Content-Disposition value into buf.
 * Handles filename="...", filename=..., and RFC 5987 filename*=charset''value
 * (the part after the second quote; not percent-decoded). Returns 1 if a
 * non-empty candidate was written. */
static int extract_disposition_name(const char *cd, char *buf, size_t bufsz) {
    if (bufsz == 0) return 0;
    buf[0] = '\0';
    const char *p = ci_find(cd, "filename");
    if (p == NULL) return 0;
    p += 8; /* strlen("filename") */

    int ext_form = 0;
    if (*p == '*') { ext_form = 1; ++p; }
    while (*p == ' ' || *p == '\t') ++p;
    if (*p != '=') return 0;
    ++p;
    while (*p == ' ' || *p == '\t') ++p;

    if (ext_form) {
        const char *q1 = strchr(p, '\'');
        if (q1 != NULL) {
            const char *q2 = strchr(q1 + 1, '\'');
            if (q2 != NULL) p = q2 + 1;
        }
        const char *end = p;
        while (*end != '\0' && *end != ';' && *end != ' ' && *end != '\t') ++end;
        copy_span(p, end, buf, bufsz);
    } else if (*p == '"') {
        ++p;
        const char *end = strchr(p, '"');
        if (end == NULL) end = p + strlen(p);
        copy_span(p, end, buf, bufsz);
    } else {
        const char *end = p;
        while (*end != '\0' && *end != ';' && *end != ' ' && *end != '\t') ++end;
        copy_span(p, end, buf, bufsz);
    }
    return buf[0] != '\0';
}

/* Extracts the last path segment of url (without ?query or #fragment) into buf.
 * Returns 1 if a non-empty candidate was written. */
static int extract_url_name(const char *url, char *buf, size_t bufsz) {
    if (bufsz == 0) return 0;
    buf[0] = '\0';
    if (url == NULL) return 0;
    const char *end = url;
    while (*end != '\0' && *end != '?' && *end != '#') ++end;
    const char *seg = end;
    while (seg > url && seg[-1] != '/') --seg;
    copy_span(seg, end, buf, bufsz);
    return buf[0] != '\0';
}

/* Does name already carry an extension (a '.' past the first byte with at least
 * one character after it)? */
static int has_extension(const char *name) {
    const char *dot = strrchr(name, '.');
    return dot != NULL && dot != name && dot[1] != '\0';
}

dl_status dl_pick_name(const char *url, const char *content_disposition,
                       const char *content_type, char *out, size_t outsz) {
    if (out == NULL || outsz == 0) return DL_ERR_NULL_ARG;
    out[0] = '\0';

    char cand[512];
    cand[0] = '\0';
    if (!(content_disposition != NULL && extract_disposition_name(content_disposition, cand, sizeof cand))) {
        if (!extract_url_name(url, cand, sizeof cand)) cand[0] = '\0';
    }

    /* If the candidate has no alphanumeric byte, it would sanitize to nothing;
     * use the controlled fallback instead of pe_safe_basename's generic one. */
    int has_alnum = 0;
    for (const char *p = cand; *p != '\0'; ++p) {
        if (isalnum((unsigned char)*p)) { has_alnum = 1; break; }
    }
    if (!has_alnum) {
        size_t fl = strlen(DL_FALLBACK_NAME);
        memcpy(cand, DL_FALLBACK_NAME, fl + 1);
    }

    char name[DL_NAME_MAX + 1];
    if (pe_safe_basename(cand, name, sizeof name) != PE_OK || name[0] == '\0') {
        size_t fl = strlen(DL_FALLBACK_NAME);
        memcpy(name, DL_FALLBACK_NAME, fl + 1);
    }

    if (!has_extension(name)) {
        const char *ext = dl_ext_for_type(content_type);
        if (ext[0] != '\0') {
            size_t l = strlen(name), e = strlen(ext);
            if (l + e < sizeof name) memcpy(name + l, ext, e + 1);
        }
    }

    size_t need = strlen(name) + 1;
    if (need > outsz) { out[0] = '\0'; return DL_ERR_OVERFLOW; }
    memcpy(out, name, need);
    return DL_OK;
}

dl_status dl_build_path(const char *dir, const char *name, char *out, size_t outsz) {
    if (dir == NULL || name == NULL || out == NULL || outsz == 0) return DL_ERR_NULL_ARG;
    out[0] = '\0';
    if (strchr(name, '/') != NULL) return DL_ERR_OVERFLOW; /* never escape dir */

    size_t dl = strlen(dir);
    int need_sep = (dl > 0 && dir[dl - 1] != '/');
    size_t need = dl + (need_sep ? 1u : 0u) + strlen(name) + 1u;
    if (need > outsz) { out[0] = '\0'; return DL_ERR_OVERFLOW; }

    memcpy(out, dir, dl);
    size_t pos = dl;
    if (need_sep) out[pos++] = '/';
    size_t nl = strlen(name);
    memcpy(out + pos, name, nl + 1);
    return DL_OK;
}

dl_status dl_check_size(size_t len) {
    return (len <= DL_MAX_BYTES) ? DL_OK : DL_ERR_TOO_LARGE;
}
