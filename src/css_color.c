/*
 * css_color — implementation: pure CSS color token parser.
 *
 * No I/O, no global mutable state, no allocation. Operates on bounded stack
 * buffers. Fails closed: an unrecognised, malformed, or out-of-range token never
 * yields a color (the caller falls back to the theme). Named colors are resolved
 * by binary search over a sorted, lowercase reference table.
 */

#include "css_color.h"

#include <stdlib.h>
#include <string.h>

/* Largest CSS color token accepted. The longest named color
 * ("lightgoldenrodyellow") is 20 bytes; functional rgba() with percentages fits
 * well under this. A longer token is not a color and fails closed. */
#define CC_TOKEN_MAX 64u

/* Channel maxima for the rgb() functional form. */
#define CC_CHANNEL_MAX 255
#define CC_PERCENT_MAX 100

typedef struct cc_named {
    const char   *name;
    unsigned char r, g, b;
} cc_named;

/* The CSS extended color keywords, sorted by name for binary search.
 * "transparent" is intentionally absent: it has no visible color and fails
 * closed so the renderer uses the theme color instead of invisible text. */
static const cc_named CC_NAMES[] = {
    { "aliceblue", 0xf0, 0xf8, 0xff }, { "antiquewhite", 0xfa, 0xeb, 0xd7 },
    { "aqua", 0x00, 0xff, 0xff }, { "aquamarine", 0x7f, 0xff, 0xd4 },
    { "azure", 0xf0, 0xff, 0xff }, { "beige", 0xf5, 0xf5, 0xdc },
    { "bisque", 0xff, 0xe4, 0xc4 }, { "black", 0x00, 0x00, 0x00 },
    { "blanchedalmond", 0xff, 0xeb, 0xcd }, { "blue", 0x00, 0x00, 0xff },
    { "blueviolet", 0x8a, 0x2b, 0xe2 }, { "brown", 0xa5, 0x2a, 0x2a },
    { "burlywood", 0xde, 0xb8, 0x87 }, { "cadetblue", 0x5f, 0x9e, 0xa0 },
    { "chartreuse", 0x7f, 0xff, 0x00 }, { "chocolate", 0xd2, 0x69, 0x1e },
    { "coral", 0xff, 0x7f, 0x50 }, { "cornflowerblue", 0x64, 0x95, 0xed },
    { "cornsilk", 0xff, 0xf8, 0xdc }, { "crimson", 0xdc, 0x14, 0x3c },
    { "cyan", 0x00, 0xff, 0xff }, { "darkblue", 0x00, 0x00, 0x8b },
    { "darkcyan", 0x00, 0x8b, 0x8b }, { "darkgoldenrod", 0xb8, 0x86, 0x0b },
    { "darkgray", 0xa9, 0xa9, 0xa9 }, { "darkgreen", 0x00, 0x64, 0x00 },
    { "darkgrey", 0xa9, 0xa9, 0xa9 }, { "darkkhaki", 0xbd, 0xb7, 0x6b },
    { "darkmagenta", 0x8b, 0x00, 0x8b }, { "darkolivegreen", 0x55, 0x6b, 0x2f },
    { "darkorange", 0xff, 0x8c, 0x00 }, { "darkorchid", 0x99, 0x32, 0xcc },
    { "darkred", 0x8b, 0x00, 0x00 }, { "darksalmon", 0xe9, 0x96, 0x7a },
    { "darkseagreen", 0x8f, 0xbc, 0x8f }, { "darkslateblue", 0x48, 0x3d, 0x8b },
    { "darkslategray", 0x2f, 0x4f, 0x4f }, { "darkslategrey", 0x2f, 0x4f, 0x4f },
    { "darkturquoise", 0x00, 0xce, 0xd1 }, { "darkviolet", 0x94, 0x00, 0xd3 },
    { "deeppink", 0xff, 0x14, 0x93 }, { "deepskyblue", 0x00, 0xbf, 0xff },
    { "dimgray", 0x69, 0x69, 0x69 }, { "dimgrey", 0x69, 0x69, 0x69 },
    { "dodgerblue", 0x1e, 0x90, 0xff }, { "firebrick", 0xb2, 0x22, 0x22 },
    { "floralwhite", 0xff, 0xfa, 0xf0 }, { "forestgreen", 0x22, 0x8b, 0x22 },
    { "fuchsia", 0xff, 0x00, 0xff }, { "gainsboro", 0xdc, 0xdc, 0xdc },
    { "ghostwhite", 0xf8, 0xf8, 0xff }, { "gold", 0xff, 0xd7, 0x00 },
    { "goldenrod", 0xda, 0xa5, 0x20 }, { "gray", 0x80, 0x80, 0x80 },
    { "green", 0x00, 0x80, 0x00 }, { "greenyellow", 0xad, 0xff, 0x2f },
    { "grey", 0x80, 0x80, 0x80 }, { "honeydew", 0xf0, 0xff, 0xf0 },
    { "hotpink", 0xff, 0x69, 0xb4 }, { "indianred", 0xcd, 0x5c, 0x5c },
    { "indigo", 0x4b, 0x00, 0x82 }, { "ivory", 0xff, 0xff, 0xf0 },
    { "khaki", 0xf0, 0xe6, 0x8c }, { "lavender", 0xe6, 0xe6, 0xfa },
    { "lavenderblush", 0xff, 0xf0, 0xf5 }, { "lawngreen", 0x7c, 0xfc, 0x00 },
    { "lemonchiffon", 0xff, 0xfa, 0xcd }, { "lightblue", 0xad, 0xd8, 0xe6 },
    { "lightcoral", 0xf0, 0x80, 0x80 }, { "lightcyan", 0xe0, 0xff, 0xff },
    { "lightgoldenrodyellow", 0xfa, 0xfa, 0xd2 }, { "lightgray", 0xd3, 0xd3, 0xd3 },
    { "lightgreen", 0x90, 0xee, 0x90 }, { "lightgrey", 0xd3, 0xd3, 0xd3 },
    { "lightpink", 0xff, 0xb6, 0xc1 }, { "lightsalmon", 0xff, 0xa0, 0x7a },
    { "lightseagreen", 0x20, 0xb2, 0xaa }, { "lightskyblue", 0x87, 0xce, 0xfa },
    { "lightslategray", 0x77, 0x88, 0x99 }, { "lightslategrey", 0x77, 0x88, 0x99 },
    { "lightsteelblue", 0xb0, 0xc4, 0xde }, { "lightyellow", 0xff, 0xff, 0xe0 },
    { "lime", 0x00, 0xff, 0x00 }, { "limegreen", 0x32, 0xcd, 0x32 },
    { "linen", 0xfa, 0xf0, 0xe6 }, { "magenta", 0xff, 0x00, 0xff },
    { "maroon", 0x80, 0x00, 0x00 }, { "mediumaquamarine", 0x66, 0xcd, 0xaa },
    { "mediumblue", 0x00, 0x00, 0xcd }, { "mediumorchid", 0xba, 0x55, 0xd3 },
    { "mediumpurple", 0x93, 0x70, 0xdb }, { "mediumseagreen", 0x3c, 0xb3, 0x71 },
    { "mediumslateblue", 0x7b, 0x68, 0xee }, { "mediumspringgreen", 0x00, 0xfa, 0x9a },
    { "mediumturquoise", 0x48, 0xd1, 0xcc }, { "mediumvioletred", 0xc7, 0x15, 0x85 },
    { "midnightblue", 0x19, 0x19, 0x70 }, { "mintcream", 0xf5, 0xff, 0xfa },
    { "mistyrose", 0xff, 0xe4, 0xe1 }, { "moccasin", 0xff, 0xe4, 0xb5 },
    { "navajowhite", 0xff, 0xde, 0xad }, { "navy", 0x00, 0x00, 0x80 },
    { "oldlace", 0xfd, 0xf5, 0xe6 }, { "olive", 0x80, 0x80, 0x00 },
    { "olivedrab", 0x6b, 0x8e, 0x23 }, { "orange", 0xff, 0xa5, 0x00 },
    { "orangered", 0xff, 0x45, 0x00 }, { "orchid", 0xda, 0x70, 0xd6 },
    { "palegoldenrod", 0xee, 0xe8, 0xaa }, { "palegreen", 0x98, 0xfb, 0x98 },
    { "paleturquoise", 0xaf, 0xee, 0xee }, { "palevioletred", 0xdb, 0x70, 0x93 },
    { "papayawhip", 0xff, 0xef, 0xd5 }, { "peachpuff", 0xff, 0xda, 0xb9 },
    { "peru", 0xcd, 0x85, 0x3f }, { "pink", 0xff, 0xc0, 0xcb },
    { "plum", 0xdd, 0xa0, 0xdd }, { "powderblue", 0xb0, 0xe0, 0xe6 },
    { "purple", 0x80, 0x00, 0x80 }, { "rebeccapurple", 0x66, 0x33, 0x99 },
    { "red", 0xff, 0x00, 0x00 }, { "rosybrown", 0xbc, 0x8f, 0x8f },
    { "royalblue", 0x41, 0x69, 0xe1 }, { "saddlebrown", 0x8b, 0x45, 0x13 },
    { "salmon", 0xfa, 0x80, 0x72 }, { "sandybrown", 0xf4, 0xa4, 0x60 },
    { "seagreen", 0x2e, 0x8b, 0x57 }, { "seashell", 0xff, 0xf5, 0xee },
    { "sienna", 0xa0, 0x52, 0x2d }, { "silver", 0xc0, 0xc0, 0xc0 },
    { "skyblue", 0x87, 0xce, 0xeb }, { "slateblue", 0x6a, 0x5a, 0xcd },
    { "slategray", 0x70, 0x80, 0x90 }, { "slategrey", 0x70, 0x80, 0x90 },
    { "snow", 0xff, 0xfa, 0xfa }, { "springgreen", 0x00, 0xff, 0x7f },
    { "steelblue", 0x46, 0x82, 0xb4 }, { "tan", 0xd2, 0xb4, 0x8c },
    { "teal", 0x00, 0x80, 0x80 }, { "thistle", 0xd8, 0xbf, 0xd8 },
    { "tomato", 0xff, 0x63, 0x47 }, { "turquoise", 0x40, 0xe0, 0xd0 },
    { "violet", 0xee, 0x82, 0xee }, { "wheat", 0xf5, 0xde, 0xb3 },
    { "white", 0xff, 0xff, 0xff }, { "whitesmoke", 0xf5, 0xf5, 0xf5 },
    { "yellow", 0xff, 0xff, 0x00 }, { "yellowgreen", 0x9a, 0xcd, 0x32 },
};

static int ascii_lower(int c) {
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

static int hex_val(int c) {
    c = ascii_lower(c);
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

/* Trims surrounding ASCII spaces and lowercases into out (CC_TOKEN_MAX bytes).
 * Returns 0, or -1 if the trimmed token is empty or does not fit. */
static int normalize(const char *token, char *out) {
    size_t start = 0;
    while (token[start] == ' ' || token[start] == '\t') ++start;
    size_t end = strlen(token);
    while (end > start && (token[end - 1] == ' ' || token[end - 1] == '\t')) --end;

    size_t len = end - start;
    if (len == 0 || len >= CC_TOKEN_MAX) return -1;
    for (size_t i = 0; i < len; ++i) out[i] = (char)ascii_lower((unsigned char)token[start + i]);
    out[len] = '\0';
    return 0;
}

/* Parses the hex body (after '#'), lowercased. Returns 0 / -1. */
static int parse_hex(const char *s, cc_rgb *out) {
    size_t n = strlen(s);
    for (size_t i = 0; i < n; ++i) {
        if (hex_val((unsigned char)s[i]) < 0) return -1;
    }
    if (n == 3 || n == 4) {
        int r = hex_val((unsigned char)s[0]);
        int g = hex_val((unsigned char)s[1]);
        int b = hex_val((unsigned char)s[2]);
        out->r = (unsigned char)(r * 16 + r);
        out->g = (unsigned char)(g * 16 + g);
        out->b = (unsigned char)(b * 16 + b);
        return 0;
    }
    if (n == 6 || n == 8) {
        out->r = (unsigned char)(hex_val((unsigned char)s[0]) * 16 + hex_val((unsigned char)s[1]));
        out->g = (unsigned char)(hex_val((unsigned char)s[2]) * 16 + hex_val((unsigned char)s[3]));
        out->b = (unsigned char)(hex_val((unsigned char)s[4]) * 16 + hex_val((unsigned char)s[5]));
        return 0;
    }
    return -1;
}

/* Parses one rgb() component in [b, e). For a color channel, the value is an
 * integer 0..255 or a percentage 0%..100% (rounded). For the alpha channel
 * (is_alpha), the value is validated as numeric and discarded. Returns 0 / -1. */
static int parse_component(const char *b, const char *e, int is_alpha, int *out) {
    while (b < e && *b == ' ') ++b;
    while (e > b && e[-1] == ' ') --e;
    if (b == e) return -1;

    if (is_alpha) {
        for (const char *p = b; p < e; ++p) {
            if (!((*p >= '0' && *p <= '9') || *p == '.' || *p == '%')) return -1;
        }
        *out = 0;
        return 0;
    }

    int percent = (e[-1] == '%');
    const char *de = percent ? e - 1 : e;
    if (de == b) return -1;

    long v = 0;
    for (const char *p = b; p < de; ++p) {
        if (*p < '0' || *p > '9') return -1;
        v = v * 10 + (*p - '0');
        if (v > 100000) return -1;
    }
    if (percent) {
        if (v > CC_PERCENT_MAX) return -1;
        *out = (int)((v * CC_CHANNEL_MAX + CC_PERCENT_MAX / 2) / CC_PERCENT_MAX);
    } else {
        if (v > CC_CHANNEL_MAX) return -1;
        *out = (int)v;
    }
    return 0;
}

/* Parses one hsl() component: H is integer 0..360, S/L are 0%..100%.
 * Returns 0 / -1. */
static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out) {
    while (b < e && *b == ' ') ++b;
    while (e > b && e[-1] == ' ') --e;
    if (b == e) return -1;
    if (is_hue) {
        if (e[-1] == '%') return -1; /* hue cannot be a percentage */
        long v = 0;
        int neg = 0;
        if (*b == '-') { neg = 1; ++b; }
        if (b == e) return -1;
        for (const char *p = b; p < e; ++p) {
            if (*p < '0' || *p > '9') return -1;
            v = v * 10 + (*p - '0');
            if (v > 1000) return -1;
        }
        if (neg) v = -v;
        /* Normalise hue to 0..359 */
        v = v % 360;
        if (v < 0) v += 360;
        *out = (int)v;
        return 0;
    }
    /* S or L: must be percentage */
    if (e[-1] != '%') return -1;
    long v = 0;
    for (const char *p = b; p < e - 1; ++p) {
        if (*p < '0' || *p > '9') return -1;
        v = v * 10 + (*p - '0');
        if (v > 1000) return -1;
    }
    if (v > 100) return -1;
    *out = (int)v;
    return 0;
}

/* Convert HSL to RGB using integer math. H in 0..359, S and L in 0..100.
 * Precise enough for display (error < 1 in 255). No floating point needed. */
static void hsl_to_rgb(int h, int s, int l, unsigned char *r, unsigned char *g, unsigned char *b) {
    /* Scale S and L to 0..10000 for fixed-point */
    int s2 = s, l2 = l;
    /* Chroma = (1 - |2L - 1|) * S, scaled to 0..255 */
    int l_times_2 = l2 * 2; /* 0..200 */
    int abs_2l_minus_1 = (l_times_2 > 100) ? (l_times_2 - 100) : (100 - l_times_2); /* 0..100 */
    int chroma_times_100 = (100 - abs_2l_minus_1) * s2; /* 0..10000 */
    /* chroma on 0..255 scale: chroma_times_100 * 255 / 10000 */
    int chroma = (chroma_times_100 * 255 + 5000) / 10000;
    /* X = chroma * (1 - |(H/60) mod 2 - 1|) */
    int h_sector = h / 60;       /* 0..5 */
    int h_remainder = h % 60;    /* 0..59 */
    /* x = chroma * min(h_remainder, 60 - h_remainder) / 60 */
    int x = chroma * ((h_remainder < 30) ? h_remainder : (60 - h_remainder)) / 30;
    /* m = L - chroma/2 = (L*255 - chroma*100/2) / 100... simplify:
     * m = (l2 * 255 - chroma * 50) / 100... but l2 is 0..100.
     * Actually: m = L - C/2, where L: 0..100, C: 0..255.
     * To get L on 0..255 scale: l2 * 255 / 100 = l2 * 51 / 20
     * But simpler: work in chroma "units". */
    int r1 = 0, g1 = 0, b1 = 0;
    switch (h_sector) {
        case 0: r1 = chroma; g1 = x;    b1 = 0;     break;
        case 1: r1 = x;     g1 = chroma; b1 = 0;     break;
        case 2: r1 = 0;     g1 = chroma; b1 = x;     break;
        case 3: r1 = 0;     g1 = x;      b1 = chroma; break;
        case 4: r1 = x;     g1 = 0;      b1 = chroma; break;
        case 5: r1 = chroma; g1 = 0;     b1 = x;     break;
    }
    /* m = L * 255/100 - C/2 = (L*255 - C*50) / 100 */
    int m = (l2 * 255 - chroma * 50 + 50) / 100;
    *r = (unsigned char)((r1 + m > 255) ? 255 : (r1 + m < 0 ? 0 : r1 + m));
    *g = (unsigned char)((g1 + m > 255) ? 255 : (g1 + m < 0 ? 0 : g1 + m));
    *b = (unsigned char)((b1 + m > 255) ? 255 : (b1 + m < 0 ? 0 : b1 + m));
}

/* Parses the functional rgb()/rgba()/hsl()/hsla() form (lowercased token).
 * Returns 0 / -1. */
static int parse_func(const char *s, cc_rgb *out) {
    int is_hsl = 0;
    const char *p;
    if (strncmp(s, "rgba(", 5) == 0) p = s + 5;
    else if (strncmp(s, "rgb(", 4) == 0) p = s + 4;
    else if (strncmp(s, "hsla(", 5) == 0) { p = s + 5; is_hsl = 1; }
    else if (strncmp(s, "hsl(", 4) == 0) { p = s + 4; is_hsl = 1; }
    else return -1;

    const char *close = strchr(p, ')');
    if (close == NULL) return -1;
    for (const char *q = close + 1; *q != '\0'; ++q) {
        if (*q != ' ') return -1; /* only trailing spaces after ')' */
    }

    if (is_hsl) {
        int comps[3] = { 0, 0, 0 };
        int nc = 0;
        const char *seg = p;
        for (const char *cur = p; cur <= close; ++cur) {
            if (cur == close || *cur == ',') {
                if (nc >= 4) return -1;
                int is_alpha = (nc == 3);
                int dummy = 0;
                int *slot;
                if (is_alpha) {
                    slot = &dummy;
                } else {
                    slot = &comps[nc];
                }
                if (is_alpha) {
                    for (const char *x = seg; x < cur; ++x) {
                        if (!((*x >= '0' && *x <= '9') || *x == '.' || *x == '%')) return -1;
                    }
                } else {
                    if (parse_hsl_comp(seg, cur, nc == 0, slot) != 0) return -1;
                }
                ++nc;
                seg = cur + 1;
                if (cur == close) break;
            }
        }
        if (nc < 3) return -1;
        hsl_to_rgb(comps[0], comps[1], comps[2], &out->r, &out->g, &out->b);
        return 0;
    }

    int comps[3] = { 0, 0, 0 };
    int nc = 0;
    const char *seg = p;
    for (const char *cur = p; cur <= close; ++cur) {
        if (cur == close || *cur == ',') {
            if (nc >= 4) return -1; /* too many components */
            int is_alpha = (nc == 3);
            int dummy = 0;
            int *slot = is_alpha ? &dummy : &comps[nc];
            if (parse_component(seg, cur, is_alpha, slot) != 0) return -1;
            ++nc;
            seg = cur + 1;
            if (cur == close) break;
        }
    }
    if (nc < 3) return -1; /* too few components */

    out->r = (unsigned char)comps[0];
    out->g = (unsigned char)comps[1];
    out->b = (unsigned char)comps[2];
    return 0;
}

static int named_cmp(const void *key, const void *element) {
    const char *k = (const char *)key;
    const cc_named *n = (const cc_named *)element;
    return strcmp(k, n->name);
}

static int parse_named(const char *s, cc_rgb *out) {
    const cc_named *hit = (const cc_named *)bsearch(
        s, CC_NAMES, sizeof CC_NAMES / sizeof CC_NAMES[0], sizeof CC_NAMES[0], named_cmp);
    if (hit == NULL) return -1;
    out->r = hit->r;
    out->g = hit->g;
    out->b = hit->b;
    return 0;
}

cc_status cc_parse(const char *token, cc_rgb *out) {
    if (token == NULL || out == NULL) return CC_ERR_NULL_ARG;

    char buf[CC_TOKEN_MAX];
    if (normalize(token, buf) != 0) return CC_ERR_SYNTAX;

    cc_rgb tmp;
    int rc;
    if (buf[0] == '#') {
        rc = parse_hex(buf + 1, &tmp);
    } else if (strncmp(buf, "rgb", 3) == 0) {
        rc = parse_func(buf, &tmp);
    } else if (strncmp(buf, "hsl", 3) == 0) {
        rc = parse_func(buf, &tmp);
    } else if (strcmp(buf, "transparent") == 0) {
        tmp.r = 0; tmp.g = 0; tmp.b = 0;
        *out = tmp;
        return CC_TRANSPARENT;
    } else if (strcmp(buf, "currentcolor") == 0) {
        tmp.r = 0; tmp.g = 0; tmp.b = 0;
        *out = tmp;
        return CC_CURRENT_COLOR;
    } else {
        rc = parse_named(buf, &tmp);
    }
    if (rc != 0) return CC_ERR_SYNTAX;

    *out = tmp;
    return CC_OK;
}

int cc_pack(cc_rgb c) {
    return ((int)c.r << 16) | ((int)c.g << 8) | (int)c.b;
}

cc_rgb cc_unpack(int packed) {
    cc_rgb c;
    c.r = (unsigned char)((packed >> 16) & 0xff);
    c.g = (unsigned char)((packed >> 8) & 0xff);
    c.b = (unsigned char)(packed & 0xff);
    return c;
}
