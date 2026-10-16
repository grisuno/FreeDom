/*
 * text_shape (tsh_) — HarfBuzz shaping for the trusted-side painter.
 *
 * Resolves a LOCAL font per generic family bucket (fontconfig), parses it with
 * FreeType (for Cairo glyph rendering) and HarfBuzz (for shaping) from the same
 * in-memory font program so glyph ids agree, then shapes hostile UTF-8 into
 * cairo_glyph_t positions. Trusted-side only; never runs in the confined worker.
 * Fail-closed: any backend/input problem returns a status the painter handles by
 * falling back to the Cairo toy API. See spec/text_shape.md.
 */

#define _POSIX_C_SOURCE 200809L

#include "text_shape.h"
#include "css.h"
#include "webfont.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cairo/cairo-ft.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <harfbuzz/hb.h>
#include <fontconfig/fontconfig.h>

/* A single font file should never exceed this (CJK faces are the large case). */
#define TSH_MAX_FONT_BYTES ((long)(128 * 1024 * 1024))

/* One resolved face per (family, bold, italic). family is a CSS_FF_* bucket
 * (0..CSS_FF_FANTASY); idx = family*4 + bold*2 + italic. */
#define TSH_CACHE_SLOTS ((CSS_FF_FANTASY + 1) * 4)

typedef struct tsh_entry {
    int                loaded;  /* 0 untried, 1 ok, -1 failed (don't retry) */
    unsigned char     *bytes;   /* font file contents (owned; FT + hb reference it) */
    long               nbytes;
    FT_Face            ftface;
    cairo_font_face_t *cface;
    hb_blob_t         *blob;
    hb_face_t         *hbface;
    hb_font_t         *hbfont;
} tsh_entry;

static FT_Library   g_ft;
static int          g_init_attempted;
static int          g_backend_ok;
static hb_buffer_t *g_buf;
static tsh_entry    g_cache[TSH_CACHE_SLOTS];

/* Static scratch for the measure/draw convenience wrappers (single-threaded). */
static cairo_glyph_t g_scratch[TSH_MAX_GLYPHS];

static const char *generic_name(int family) {
    switch (family) {
        case CSS_FF_SERIF:   return "serif";
        case CSS_FF_MONO:    return "monospace";
        case CSS_FF_CURSIVE: return "cursive";
        case CSS_FF_FANTASY: return "fantasy";
        default:             return "sans-serif"; /* CSS_FF_SANS / UNSET */
    }
}

static int backend_init(void) {
    if (g_init_attempted) return g_backend_ok;
    g_init_attempted = 1;
    if (FT_Init_FreeType(&g_ft) != 0) { g_backend_ok = 0; return 0; }
    /* FcInit is idempotent; FcFontMatch(NULL,...) inits implicitly anyway. */
    FcInit();
    g_buf = hb_buffer_create();
    if (g_buf == NULL || !hb_buffer_allocation_successful(g_buf)) {
        if (g_buf != NULL) { hb_buffer_destroy(g_buf); g_buf = NULL; }
        FT_Done_FreeType(g_ft);
        g_backend_ok = 0;
        return 0;
    }
    g_backend_ok = 1;
    return 1;
}

static unsigned char *read_font_file(const char *path, long *out_n) {
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) return NULL;
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return NULL; }
    long sz = ftell(fp);
    if (sz <= 0 || sz > TSH_MAX_FONT_BYTES) { fclose(fp); return NULL; }
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return NULL; }
    unsigned char *b = (unsigned char *)malloc((size_t)sz);
    if (b == NULL) { fclose(fp); return NULL; }
    size_t rd = fread(b, 1, (size_t)sz, fp);
    fclose(fp);
    if (rd != (size_t)sz) { free(b); return NULL; }
    *out_n = sz;
    return b;
}

/* Loads the face fontconfig matches for family name fam (a generic keyword or
 * an exact local family). FcPatternAddString, not FcNameParse: a family name may
 * hold characters ('-', ':') that the pattern syntax treats specially. */
static int load_entry_named(tsh_entry *e, const char *fam, int bold, int italic) {
    FcPattern *pat = FcPatternCreate();
    if (pat == NULL) return 0;
    if (!FcPatternAddString(pat, FC_FAMILY, (const FcChar8 *)fam)) {
        FcPatternDestroy(pat);
        return 0;
    }
    FcPatternAddInteger(pat, FC_WEIGHT, bold ? FC_WEIGHT_BOLD : FC_WEIGHT_NORMAL);
    FcPatternAddInteger(pat, FC_SLANT, italic ? FC_SLANT_ITALIC : FC_SLANT_ROMAN);
    FcConfigSubstitute(NULL, pat, FcMatchPattern);
    FcDefaultSubstitute(pat);
    FcResult res;
    FcPattern *match = FcFontMatch(NULL, pat, &res);
    FcPatternDestroy(pat);
    if (match == NULL) return 0;

    FcChar8 *file = NULL;
    if (FcPatternGetString(match, FC_FILE, 0, &file) != FcResultMatch || file == NULL) {
        FcPatternDestroy(match);
        return 0;
    }
    int index = 0;
    FcPatternGetInteger(match, FC_INDEX, 0, &index);
    long nbytes = 0;
    unsigned char *bytes = read_font_file((const char *)file, &nbytes);
    FcPatternDestroy(match);
    if (bytes == NULL) return 0;

    FT_Face ft = NULL;
    if (FT_New_Memory_Face(g_ft, bytes, nbytes, index, &ft) != 0) {
        free(bytes);
        return 0;
    }
    cairo_font_face_t *cf = cairo_ft_font_face_create_for_ft_face(ft, 0);
    if (cf == NULL || cairo_font_face_status(cf) != CAIRO_STATUS_SUCCESS) {
        if (cf != NULL) cairo_font_face_destroy(cf);
        FT_Done_Face(ft);
        free(bytes);
        return 0;
    }
    hb_blob_t *blob = hb_blob_create((const char *)bytes, (unsigned)nbytes,
                                     HB_MEMORY_MODE_READONLY, NULL, NULL);
    hb_face_t *hf = hb_face_create(blob, (unsigned)index);
    hb_font_t *hfont = hb_font_create(hf);
    if (hfont == NULL || hf == NULL) {
        if (hfont != NULL) hb_font_destroy(hfont);
        if (hf != NULL) hb_face_destroy(hf);
        hb_blob_destroy(blob);
        cairo_font_face_destroy(cf);
        FT_Done_Face(ft);
        free(bytes);
        return 0;
    }

    e->bytes = bytes; e->nbytes = nbytes; e->ftface = ft; e->cface = cf;
    e->blob = blob; e->hbface = hf; e->hbfont = hfont;
    return 1;
}

static int load_entry(tsh_entry *e, int family, int bold, int italic) {
    return load_entry_named(e, generic_name(family), bold, italic);
}

static tsh_entry *get_entry(int family, int bold, int italic) {
    if (!backend_init()) return NULL;
    int fam = (family >= 0 && family <= CSS_FF_FANTASY) ? family : CSS_FF_SANS;
    int idx = fam * 4 + (bold ? 2 : 0) + (italic ? 1 : 0);
    tsh_entry *e = &g_cache[idx];
    if (e->loaded == 1) return e;
    if (e->loaded == -1) return NULL;
    if (load_entry(e, fam, bold, italic)) { e->loaded = 1; return e; }
    e->loaded = -1;
    return NULL;
}

/* Per-document @font-face table (spec/webfont.md): registered by the trusted
 * parent from policy-gated fetches, keyed by (name hash, bold, italic). Memory
 * only, freed by tsh_webfont_clear (navigation) and tsh_shutdown. Never the
 * worker: shaping a registered face runs on the painter side like every face. */
#define TSH_WEB_SLOTS 16

typedef struct tsh_web {
    int       used;
    unsigned  hash;
    int       bold;
    int       italic;
    tsh_entry e;
} tsh_web;

static tsh_web g_web[TSH_WEB_SLOTS];

static void web_entry_free(tsh_web *w) {
    if (w->e.hbfont != NULL) hb_font_destroy(w->e.hbfont);
    if (w->e.hbface != NULL) hb_face_destroy(w->e.hbface);
    if (w->e.blob != NULL) hb_blob_destroy(w->e.blob);
    if (w->e.cface != NULL) cairo_font_face_destroy(w->e.cface);
    if (w->e.ftface != NULL) FT_Done_Face(w->e.ftface);
    free(w->e.bytes);
    memset(w, 0, sizeof *w);
}

/* True for font programs FreeType parses without new decoders: wOFF/TrueType/
 * CFF-OpenType (and the mac aliases). wOF2 is deliberately refused until the
 * woff2 slice (spec/webfont.md); eot/svg are never faces in any engine. */
static int web_magic_ok(const unsigned char *b, size_t n) {
    if (b == NULL || n < 4) return 0;
    if (b[0] == 'w' && b[1] == 'O' && b[2] == 'F' && b[3] == 'F') return 1;
    if (b[0] == 0 && b[1] == 1 && b[2] == 0 && b[3] == 0) return 1;
    if (b[0] == 'O' && b[1] == 'T' && b[2] == 'T' && b[3] == 'O') return 1;
    if (b[0] == 't' && b[1] == 'r' && b[2] == 'u' && b[3] == 'e') return 1;
    if (b[0] == 't' && b[1] == 'y' && b[2] == 'p' && b[3] == '1') return 1;
    return 0;
}

/* Builds the shaping faces over an OWNED copy of bytes[0,nbytes) into e
 * (shared tail with load_entry's file path: same objects, same order, same
 * failure discipline -- free the copy on any failure, never half-register). */
static int web_make_entry(tsh_entry *e, const unsigned char *bytes, size_t nbytes) {
    unsigned char *copy = (unsigned char *)malloc(nbytes);
    if (copy == NULL) return 0;
    memcpy(copy, bytes, nbytes);
    FT_Face ft = NULL;
    if (FT_New_Memory_Face(g_ft, copy, (FT_Long)nbytes, 0, &ft) != 0) {
        free(copy);
        return 0;
    }
    cairo_font_face_t *cf = cairo_ft_font_face_create_for_ft_face(ft, 0);
    if (cf == NULL || cairo_font_face_status(cf) != CAIRO_STATUS_SUCCESS) {
        if (cf != NULL) cairo_font_face_destroy(cf);
        FT_Done_Face(ft);
        free(copy);
        return 0;
    }
    hb_blob_t *blob = hb_blob_create((const char *)copy, (unsigned)nbytes,
                                     HB_MEMORY_MODE_READONLY, NULL, NULL);
    hb_face_t *hf = hb_face_create(blob, 0);
    hb_font_t *hfont = hb_font_create(hf);
    if (hfont == NULL || hf == NULL) {
        if (hfont != NULL) hb_font_destroy(hfont);
        if (hf != NULL) hb_face_destroy(hf);
        hb_blob_destroy(blob);
        cairo_font_face_destroy(cf);
        FT_Done_Face(ft);
        free(copy);
        return 0;
    }
    e->bytes = copy;
    e->nbytes = (long)nbytes;
    e->ftface = ft;
    e->cface = cf;
    e->blob = blob;
    e->hbface = hf;
    e->hbfont = hfont;
    e->loaded = 1;
    return 1;
}

int tsh_webfont_register(const char *name,
                         const unsigned char *bytes, size_t nbytes,
                         int bold, int italic) {
    if (name == NULL || name[0] == '\0') return -1;
    if (bytes == NULL || nbytes == 0 || nbytes > WF_MAX_FACE_BYTES) return -1;
    if (!web_magic_ok(bytes, nbytes)) return -1;
    if (!backend_init()) return -1;
    unsigned h = wf_name_hash(name, strlen(name));
    if (h == 0) return -1;
    int bb = bold ? 1 : 0;
    int it = italic ? 1 : 0;
    tsh_web *slot = NULL;
    for (int i = 0; i < TSH_WEB_SLOTS; ++i) {
        if (g_web[i].used && g_web[i].hash == h
            && g_web[i].bold == bb && g_web[i].italic == it) {
            slot = &g_web[i];
            break;
        }
        if (slot == NULL && !g_web[i].used) slot = &g_web[i];
    }
    if (slot == NULL) return -1;   /* table full: fail closed */
    if (slot->used) web_entry_free(slot);
    memset(slot, 0, sizeof *slot);
    if (!web_make_entry(&slot->e, bytes, nbytes)) {
        memset(slot, 0, sizeof *slot);
        return -1;
    }
    slot->used = 1;
    slot->hash = h;
    slot->bold = bb;
    slot->italic = it;
    return 0;
}

void tsh_webfont_clear(void) {
    for (int i = 0; i < TSH_WEB_SLOTS; ++i)
        if (g_web[i].used) web_entry_free(&g_web[i]);
}

static tsh_entry *web_find(unsigned h, int bold, int italic) {
    if (h == 0) return NULL;
    for (int i = 0; i < TSH_WEB_SLOTS; ++i) {
        if (g_web[i].used && g_web[i].hash == h
            && g_web[i].bold == (bold ? 1 : 0)
            && g_web[i].italic == (italic ? 1 : 0)
            && g_web[i].e.loaded == 1)
            return &g_web[i].e;
    }
    return NULL;
}

static void entry_free(tsh_entry *e) {
    if (e->loaded != 1) { memset(e, 0, sizeof *e); return; }
    if (e->hbfont != NULL) hb_font_destroy(e->hbfont);
    if (e->hbface != NULL) hb_face_destroy(e->hbface);
    if (e->blob != NULL) hb_blob_destroy(e->blob);
    if (e->cface != NULL) cairo_font_face_destroy(e->cface);
    if (e->ftface != NULL) FT_Done_Face(e->ftface);
    free(e->bytes);
    memset(e, 0, sizeof *e);
}

/* --- Named local families (spec/text_shape.md section 7) --- */

static int ascii_ieq(const char *a, const char *b) {
    for (; *a != '\0' && *b != '\0'; ++a, ++b) {
        char x = (*a >= 'A' && *a <= 'Z') ? (char)(*a + 32) : *a;
        char y = (*b >= 'A' && *b <= 'Z') ? (char)(*b + 32) : *b;
        if (x != y) return 0;
    }
    return *a == '\0' && *b == '\0';
}

int tsh_family_is_generic(const char *name) {
    static const char *const kw[] = {
        "serif", "sans-serif", "monospace", "cursive", "fantasy", "system-ui",
        "emoji", "math", "fangsong",
    };
    if (name == NULL || name[0] == '\0') return 0;
    for (size_t i = 0; i < sizeof kw / sizeof *kw; ++i)
        if (ascii_ieq(name, kw[i])) return 1;
    return (name[0] == 'u' || name[0] == 'U') && (name[1] == 'i' || name[1] == 'I')
           && name[2] == '-';
}

int tsh_pick_from_list(const char *list, tsh_name_resolver resolve, void *ctx,
                       char *out, size_t cap) {
    if (list == NULL || resolve == NULL || out == NULL || cap == 0) return 0;
    const char *p = list;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t' || *p == ',') ++p;
        if (*p == '\0') break;
        const char *st = p;
        while (*p != '\0' && *p != ',') ++p;
        size_t n = (size_t)(p - st);
        while (n > 0 && (st[n - 1] == ' ' || st[n - 1] == '\t')) --n;
        char name[TSH_FAMILY_MAX];
        if (n == 0 || n >= sizeof name) continue;
        memcpy(name, st, n);
        name[n] = '\0';
        if (tsh_family_is_generic(name)) return 0;
        if (resolve(name, out, cap, ctx)) return 1;
    }
    return 0;
}

const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong,
                            size_t n, int (*installed)(const char *name, void *ctx),
                            void *ctx) {
    if (req == NULL || installed == NULL) return NULL;
    if (installed(req, ctx)) return req;
    if (subs == NULL || strong == NULL) return NULL;
    /* subs[0] is the request itself; the run of strong substitutes follows. */
    for (size_t k = 1; k < n && strong[k]; ++k)
        if (subs[k] != NULL && installed(subs[k], ctx)) return subs[k];
    return NULL;
}

/* An exact (case-insensitive) family that fontconfig really has on disk. */
static int fc_installed(const char *name, void *ctx) {
    (void)ctx;
    FcPattern *p = FcPatternCreate();
    if (p == NULL) return 0;
    FcPatternAddString(p, FC_FAMILY, (const FcChar8 *)name);
    FcObjectSet *os = FcObjectSetBuild(FC_FAMILY, (char *)NULL);
    FcFontSet *fs = (os != NULL) ? FcFontList(NULL, p, os) : NULL;
    int ok = fs != NULL && fs->nfont > 0;
    if (fs != NULL) FcFontSetDestroy(fs);
    if (os != NULL) FcObjectSetDestroy(os);
    FcPatternDestroy(p);
    return ok;
}

#define TSH_SUBS_MAX 16

static int fc_resolve(const char *name, char *out, size_t cap, void *ctx) {
    (void)ctx;
    FcPattern *p = FcPatternCreate();
    if (p == NULL) return 0;
    FcPatternAddString(p, FC_FAMILY, (const FcChar8 *)name);
    FcConfigSubstitute(NULL, p, FcMatchPattern);
    const char *subs[TSH_SUBS_MAX];
    int strong[TSH_SUBS_MAX];
    size_t n = 0;
    for (int id = 0; n < TSH_SUBS_MAX; ++id) {
        FcValue v;
        FcValueBinding b;
        if (FcPatternGetWithBinding(p, FC_FAMILY, id, &v, &b) != FcResultMatch) break;
        if (v.type != FcTypeString) continue;
        subs[n] = (const char *)v.u.s;
        strong[n] = (b == FcValueBindingStrong || b == FcValueBindingSame);
        ++n;
    }
    const char *pick = tsh_pick_family(name, subs, strong, n, fc_installed, NULL);
    int ok = 0;
    if (pick != NULL && strlen(pick) < cap) {
        memcpy(out, pick, strlen(pick) + 1);
        ok = 1;
    }
    FcPatternDestroy(p);
    return ok;
}

typedef struct tsh_lfam {
    char      name[TSH_FAMILY_MAX];
    tsh_entry e[4];   /* bold*2 + italic */
    int       tried[4];
} tsh_lfam;

typedef struct tsh_llist {
    char *list;       /* owned copy, the cache key */
    int   fam;        /* index into g_lfam, -1 = resolves to nothing */
} tsh_llist;

static tsh_lfam  g_lfam[TSH_LOCAL_FAMILIES];
static size_t    g_nlfam;
static tsh_llist g_llist[TSH_LOCAL_LISTS];
static size_t    g_nllist;

static void local_clear(void) {
    for (size_t i = 0; i < g_nlfam; ++i)
        for (int k = 0; k < 4; ++k) entry_free(&g_lfam[i].e[k]);
    for (size_t i = 0; i < g_nllist; ++i) free(g_llist[i].list);
    memset(g_lfam, 0, sizeof g_lfam);
    memset(g_llist, 0, sizeof g_llist);
    g_nlfam = 0;
    g_nllist = 0;
}

static int lfam_index(const char *fam) {
    for (size_t i = 0; i < g_nlfam; ++i)
        if (ascii_ieq(g_lfam[i].name, fam)) return (int)i;
    if (g_nlfam >= TSH_LOCAL_FAMILIES || strlen(fam) >= TSH_FAMILY_MAX) return -1;
    memcpy(g_lfam[g_nlfam].name, fam, strlen(fam) + 1);
    return (int)g_nlfam++;
}

int tsh_local_handle(const char *list) {
    if (list == NULL || list[0] == '\0') return 0;
    for (size_t i = 0; i < g_nllist; ++i)
        if (strcmp(g_llist[i].list, list) == 0)
            return g_llist[i].fam >= 0 ? (int)i + 1 : 0;
    if (g_nllist >= TSH_LOCAL_LISTS || !backend_init()) return 0;
    size_t n = strlen(list);
    if (n == (size_t)-1) return 0;
    char *copy = malloc(n + 1);
    if (copy == NULL) return 0;
    memcpy(copy, list, n + 1);
    char fam[TSH_FAMILY_MAX];
    int fi = tsh_pick_from_list(list, fc_resolve, NULL, fam, sizeof fam) ? lfam_index(fam) : -1;
    g_llist[g_nllist].list = copy;
    g_llist[g_nllist].fam = fi;
    ++g_nllist;
    return fi >= 0 ? (int)g_nllist : 0;
}

static tsh_entry *local_entry(int handle, int bold, int italic) {
    if (handle <= 0 || (size_t)handle > g_nllist) return NULL;
    int fi = g_llist[handle - 1].fam;
    if (fi < 0 || (size_t)fi >= g_nlfam) return NULL;
    tsh_lfam *lf = &g_lfam[fi];
    int k = (bold ? 2 : 0) + (italic ? 1 : 0);
    if (lf->e[k].loaded == 1) return &lf->e[k];
    if (lf->tried[k]) return NULL;
    lf->tried[k] = 1;
    if (load_entry_named(&lf->e[k], lf->name, bold, italic)) {
        lf->e[k].loaded = 1;
        return &lf->e[k];
    }
    return NULL;
}

/* Entry for a full font selector: a registered @font-face wins over the local
 * bucket stack; a set-but-unregistered hash falls through to it (the face may
 * belong to another document -- the table is per-document, cleared on
 * navigation -- so missing is routine, never an error). */
static tsh_entry *get_entry_ex(const tsh_font *f) {
    if (f->wfh != 0) {
        tsh_entry *w = web_find(f->wfh, f->bold, f->italic);
        if (w != NULL) return w;
    }
    if (f->local > 0) {
        tsh_entry *l = local_entry(f->local, f->bold, f->italic);
        if (l != NULL) return l;
    }
    return get_entry(f->family, f->bold, f->italic);
}

int tsh_ready(void) {
    /* Backend usable iff the default (sans) face resolves. */
    return get_entry(CSS_FF_SANS, 0, 0) != NULL;
}

tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                     cairo_glyph_t *out, size_t cap, size_t *out_n, double *out_adv) {
    if (f == NULL || out == NULL || out_n == NULL || out_adv == NULL) return TSH_ERR_INPUT;
    if (cap == 0) return TSH_ERR_INPUT;
    if (text == NULL && len != 0) return TSH_ERR_INPUT;
    /* px must be finite and positive; px>1e9 catches +inf, !(px>0) catches NaN/<=0. */
    if (!(px > 0.0) || px > 1.0e9) return TSH_ERR_INPUT;
    if (len > (size_t)TSH_MAX_TEXT) return TSH_ERR_INPUT;

    *out_n = 0;
    *out_adv = 0.0;
    if (len == 0) return TSH_OK;

    tsh_entry *e = get_entry_ex(f);
    if (e == NULL) return TSH_ERR_UNAVAIL;

    int scale = (int)(px * 64.0 + 0.5);
    if (scale < 1) scale = 1;
    hb_font_set_scale(e->hbfont, scale, scale);

    hb_buffer_reset(g_buf);
    hb_buffer_add_utf8(g_buf, text, (int)len, 0, (int)len);
    hb_buffer_guess_segment_properties(g_buf);
    hb_shape(e->hbfont, g_buf, NULL, 0);

    unsigned gn = hb_buffer_get_length(g_buf);
    if ((size_t)gn > cap || gn > TSH_MAX_GLYPHS) return TSH_ERR_OVERFLOW;

    const hb_glyph_info_t     *info = hb_buffer_get_glyph_infos(g_buf, NULL);
    const hb_glyph_position_t  *pos  = hb_buffer_get_glyph_positions(g_buf, NULL);
    if ((gn != 0) && (info == NULL || pos == NULL)) return TSH_ERR_UNAVAIL;

    double penx = 0.0, peny = 0.0;
    for (unsigned i = 0; i < gn; ++i) {
        out[i].index = info[i].codepoint;            /* glyph id (matches cface) */
        out[i].x = penx + (double)pos[i].x_offset / 64.0;
        out[i].y = peny - (double)pos[i].y_offset / 64.0;
        penx += (double)pos[i].x_advance / 64.0;
        peny -= (double)pos[i].y_advance / 64.0;
    }
    *out_n = gn;
    *out_adv = penx;
    return TSH_OK;
}

double tsh_measure(const tsh_font *f, double px, const char *text, size_t len) {
    size_t n = 0;
    double adv = 0.0;
    tsh_status st = tsh_shape(f, px, text, len, g_scratch, TSH_MAX_GLYPHS, &n, &adv);
    return (st == TSH_OK) ? adv : -1.0;
}

tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, double baseline, const char *text, size_t len) {
    if (cr == NULL) return TSH_ERR_INPUT;
    size_t n = 0;
    double adv = 0.0;
    tsh_status st = tsh_shape(f, px, text, len, g_scratch, TSH_MAX_GLYPHS, &n, &adv);
    if (st != TSH_OK) return st;
    if (n == 0) return TSH_OK;

    tsh_entry *e = get_entry_ex(f);
    if (e == NULL) return TSH_ERR_UNAVAIL;

    cairo_set_font_face(cr, e->cface);
    cairo_set_font_size(cr, px);
    for (size_t i = 0; i < n; ++i) {
        g_scratch[i].x += x;
        g_scratch[i].y += baseline;
    }
    cairo_show_glyphs(cr, g_scratch, (int)n);
    return TSH_OK;
}

cairo_font_face_t *tsh_face(const tsh_font *f) {
    if (f == NULL || !backend_init()) return NULL;
    tsh_entry *e = get_entry_ex(f);
    return (e != NULL) ? e->cface : NULL;
}

void tsh_shutdown(void) {
    tsh_webfont_clear();
    for (int i = 0; i < TSH_CACHE_SLOTS; ++i) entry_free(&g_cache[i]);
    local_clear();
    if (g_buf != NULL) { hb_buffer_destroy(g_buf); g_buf = NULL; }
    if (g_backend_ok) FT_Done_FreeType(g_ft);
    g_backend_ok = 0;
    g_init_attempted = 0;
}
