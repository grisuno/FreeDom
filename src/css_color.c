/*
 * css_color — implementation: pure CSS color token parser.
 *
 * No I/O, no global mutable state, no allocation. Operates on bounded stack
 * buffers. Fails closed: an unrecognised, malformed, or out-of-range token never
 * yields a color (the caller falls back to the theme). Named colors are resolved
 * by binary search over a sorted, lowercase reference table.
 */

#include "css_color.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

/* Largest CSS color token accepted. The longest named color
 * ("lightgoldenrodyellow") is 20 bytes; functional rgba() with percentages fits
 * well under this. A longer token is not a color and fails closed. */
#define CC_TOKEN_MAX 64u

/* Channel maxima for the rgb() functional form. */
#define CC_CHANNEL_MAX 255
#define CC_PERCENT_MAX 100
/* Digits accepted on either side of the decimal point in one component. A real
 * value has a handful; the cap is what stops a hostile stylesheet from handing the
 * scanner an unbounded digit run (anti-DoS, fail closed). A preprocessor emitting
 * `91.862745098%` uses 9 fractional digits, so the bound is set well clear of it. */
#define CC_NUMBER_MAX_DIGITS 24
/* Fixed-point scale for hsl() saturation/lightness: hundredths of a percent, so
 * 100% is CC_HSL_SCALE. See parse_hsl_comp. */
#define CC_HSL_SCALE 10000

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
    /* #RGBA / #RRGGBBAA with a zero alpha IS transparent (CSS Color 4 6.1). */
    if (n == 4 && hex_val((unsigned char)s[3]) == 0) return 1;
    if (n == 8 && hex_val((unsigned char)s[6]) == 0 && hex_val((unsigned char)s[7]) == 0)
        return 1;
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

/* Scans a CSS <number> in [b, e) into *out (CSS Syntax 3 section 4.3.12): an
 * optional sign, then digits with an optional fractional part, where EITHER side of
 * the dot may be empty but not both ("1", "1.5", ".5" and "1." are all numbers,
 * "." is not). Returns 0 on success, -1 if the span is not exactly one number.
 *
 * One scanner for every component of every functional colour form. The integer-only
 * loops it replaces rejected any fraction, so `hsl(0,0%,15.83%)` -- the shape a
 * preprocessor emits -- failed, and with it the whole declaration: a page could lose
 * its entire palette to a decimal point. Bounded by construction (it never reads
 * past e) and it does no allocation, so it stays usable on hostile input. */
static int cc_scan_number(const char *b, const char *e, double *out) {
    if (b >= e) return -1;
    int neg = 0;
    if (*b == '+' || *b == '-') { neg = (*b == '-'); ++b; }

    double ip = 0.0;
    int int_digits = 0;
    while (b < e && *b >= '0' && *b <= '9') {
        ip = ip * 10.0 + (double)(*b - '0');
        ++b; ++int_digits;
        if (int_digits > CC_NUMBER_MAX_DIGITS) return -1;  /* anti-DoS, fail closed */
    }

    double fp = 0.0, scale = 1.0;
    int frac_digits = 0;
    if (b < e && *b == '.') {
        ++b;
        while (b < e && *b >= '0' && *b <= '9') {
            scale *= 10.0;
            fp += (double)(*b - '0') / scale;
            ++b; ++frac_digits;
            if (frac_digits > CC_NUMBER_MAX_DIGITS) return -1;
        }
    }
    if (int_digits == 0 && frac_digits == 0) return -1;  /* "." / "+" / "" */
    if (b != e) return -1;                               /* trailing junk */

    double v = ip + fp;
    *out = neg ? -v : v;
    return 0;
}

/* Rounds a non-negative scanned number to the nearest integer. */
static long cc_round(double v) { return (long)(v + 0.5); }

/* Parses one rgb() component in [b, e). For a color channel, the value is an
 * integer 0..255 or a percentage 0%..100% (rounded). For the alpha channel
 * (is_alpha), the value is validated as numeric and discarded. Returns 0 / -1. */
static int parse_component(const char *b, const char *e, int is_alpha, int *out) {
    while (b < e && *b == ' ') ++b;
    while (e > b && e[-1] == ' ') --e;
    if (b == e) return -1;

    if (is_alpha) {
        /* Validated and discarded: the alpha is carried separately (css.c reads it
         * with bg_alpha_of). Scanning it properly means "1.2.3" is rejected here
         * instead of being waved through by a character-class check. */
        const char *ae = (e > b && e[-1] == '%') ? e - 1 : e;
        double a;
        if (cc_scan_number(b, ae, &a) != 0) return -1;
        *out = (a <= 0.0) ? 1 : 0;   /* 1 = the colour is fully transparent */
        return 0;
    }

    int percent = (e[-1] == '%');
    const char *de = percent ? e - 1 : e;
    double num;
    if (cc_scan_number(b, de, &num) != 0) return -1;
    if (num < 0.0) return -1;
    if (percent) {
        if (num > (double)CC_PERCENT_MAX) return -1;
        *out = (int)cc_round(num * (double)CC_CHANNEL_MAX / (double)CC_PERCENT_MAX);
    } else {
        if (num > (double)CC_CHANNEL_MAX) return -1;
        *out = (int)cc_round(num);
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
        if (e[-1] == '%') return -1; /* hue is an <angle>/<number>, never a percentage */
        double num;
        if (cc_scan_number(b, e, &num) != 0) return -1;
        long v = (num < 0.0) ? (long)(num - 0.5) : (long)(num + 0.5);
        v = v % 360;
        if (v < 0) v += 360;
        *out = (int)v;
        return 0;
    }
    /* S or L: a <percentage>, kept in HUNDREDTHS of a percent (0..10000).
     *
     * Rounding to whole percent first is a real loss of colour: 15.8333% of 255 is
     * 40.4, but 16% of 255 is 40.8, so the channel came out one step off every
     * other engine. The extra two digits cost nothing -- the conversion below is
     * fixed-point either way -- and they are exactly what a preprocessor emits. */
    if (e[-1] != '%') return -1;
    double num;
    if (cc_scan_number(b, e - 1, &num) != 0) return -1;
    if (num < 0.0 || num > (double)CC_PERCENT_MAX) return -1;
    *out = (int)cc_round(num * (double)CC_HSL_SCALE / (double)CC_PERCENT_MAX);
    return 0;
}

/* Convert HSL to RGB using integer math. H in 0..359, S and L in 0..100.
 * Precise enough for display (error < 1 in 255). No floating point needed. */
static void hsl_to_rgb(int h, int s, int l, unsigned char *r, unsigned char *g, unsigned char *b) {
    /* H is 0..359 degrees; S and L are hundredths of a percent (0..CC_HSL_SCALE).
     * All fixed-point: the intermediate chroma term reaches CC_HSL_SCALE^2, which
     * overflows int, so the products are done in long. */
    long s2 = s, l2 = l;

    /* Chroma = (1 - |2L - 1|) * S, then scaled onto 0..255. */
    long l_times_2 = l2 * 2;
    long abs_2l_minus_1 = (l_times_2 > CC_HSL_SCALE)
                        ? (l_times_2 - CC_HSL_SCALE) : (CC_HSL_SCALE - l_times_2);
    long chroma_scaled = (CC_HSL_SCALE - abs_2l_minus_1) * s2;   /* 0..CC_HSL_SCALE^2 */
    long denom = (long)CC_HSL_SCALE * (long)CC_HSL_SCALE;
    long chroma = (chroma_scaled * CC_CHANNEL_MAX + denom / 2) / denom;

    /* X = chroma * (1 - |(H/60) mod 2 - 1|). */
    int h_sector = h / 60;       /* 0..5 */
    int h_remainder = h % 60;    /* 0..59 */
    long x = chroma * ((h_remainder < 30) ? h_remainder : (60 - h_remainder)) / 30;

    long r1 = 0, g1 = 0, b1 = 0;
    switch (h_sector) {
        case 0: r1 = chroma; g1 = x;      b1 = 0;      break;
        case 1: r1 = x;      g1 = chroma; b1 = 0;      break;
        case 2: r1 = 0;      g1 = chroma; b1 = x;      break;
        case 3: r1 = 0;      g1 = x;      b1 = chroma; break;
        case 4: r1 = x;      g1 = 0;      b1 = chroma; break;
        case 5: r1 = chroma; g1 = 0;      b1 = x;      break;
        default: break;
    }
    /* m = L*255 - C/2, on the 0..255 scale. */
    long m = (l2 * CC_CHANNEL_MAX - chroma * (CC_HSL_SCALE / 2) + CC_HSL_SCALE / 2)
             / CC_HSL_SCALE;
    long rr = r1 + m, gg = g1 + m, bb = b1 + m;
    *r = (unsigned char)((rr > 255) ? 255 : (rr < 0 ? 0 : rr));
    *g = (unsigned char)((gg > 255) ? 255 : (gg < 0 ? 0 : gg));
    *b = (unsigned char)((bb > 255) ? 255 : (bb < 0 ? 0 : bb));
}

/* Splits the inside [b, e) of rgb()/hsl() into at most 4 component spans
 * (CSS Color 4: legacy comma-separated `f(a, b, c[, d])`, or space-separated
 * `f(a b c [/ d])`). A top-level '/' names the alpha that follows it; mixing
 * commas with '/' is rejected. Writes the span bounds into bs/es, the alpha
 * span (when a slash is present) into ab/ae, and returns the component count,
 * or -1. Bounded: never reads past e, never writes past 4 spans. */
static int cc_split_args(const char *b, const char *e, const char **bs,
                         const char **es, const char **ab, const char **ae,
                         int *comma) {
    const char *slash = NULL;
    int depth = 0;
    for (const char *q = b; q < e; ++q) {
        if (*q == '(') ++depth;
        else if (*q == ')') { if (--depth < 0) return -1; }
        else if (*q == '/' && depth == 0) {
            if (slash != NULL) return -1;  /* second slash */
            slash = q;
        }
    }
    if (depth != 0) return -1;
    const char *left_e = (slash != NULL) ? slash : e;
    if (slash != NULL) {
        const char *x = slash + 1;
        const char *y = e;
        while (x < y && (*x == ' ' || *x == '\t')) ++x;
        while (y > x && (y[-1] == ' ' || y[-1] == '\t')) --y;
        if (x >= y) return -1;  /* dangling slash */
        for (const char *q = x; q < y; ++q)
            if (*q == ' ' || *q == '\t' || *q == ',' || *q == '/') return -1;
        *ab = x;
        *ae = y;
    }
    int has_comma = 0;
    depth = 0;
    for (const char *q = b; q < left_e; ++q) {
        if (*q == '(') ++depth;
        else if (*q == ')') { if (--depth < 0) return -1; }
        else if (*q == ',' && depth == 0) { has_comma = 1; break; }
    }
    if (depth != 0) return -1;
    if (slash != NULL && has_comma) return -1;  /* mixed grammars */
    *comma = has_comma;
    int nc = 0;
    if (has_comma) {
        const char *seg = b;
        for (const char *cur = b; cur <= left_e; ++cur) {
            if (cur == left_e || *cur == ',') {
                if (nc >= 4) return -1;
                bs[nc] = seg;
                es[nc] = cur;
                ++nc;
                seg = cur + 1;
                if (cur == left_e) break;
            }
        }
    } else {
        const char *cur = b;
        while (cur < left_e) {
            while (cur < left_e && (*cur == ' ' || *cur == '\t')) ++cur;
            if (cur >= left_e) break;
            if (nc >= 4) return -1;
            const char *tok = cur;
            while (cur < left_e && *cur != ' ' && *cur != '\t') ++cur;
            bs[nc] = tok;
            es[nc] = cur;
            ++nc;
        }
    }
    return nc;
}

/* Parses the functional rgb()/rgba()/hsl()/hsla() form (lowercased token).
 * CSS Color 4: rgb() and rgba() (hsl() and hsla()) are aliases -- arity comes
 * from the alpha, not the name. The alpha is validated and discarded (Freedom
 * paints opaque; backgrounds read it separately via cv_bg_alpha_of).
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

    const char *bs[4];
    const char *es[4];
    const char *ab = NULL, *ae = NULL;
    int comma = 0;
    int nc = cc_split_args(p, close, bs, es, &ab, &ae, &comma);
    if (nc < 0) return -1;

    int comps[3] = { 0, 0, 0 };
    if (is_hsl) {
        /* Legacy comma form keeps its 4th-component alpha (`hsla(h,s,l,a)`);
         * the space form carries it after the slash instead -- a 4th bare
         * space token is not an alpha (CSS Color 4 requires the slash). */
        if (nc < 3 || nc > 4) return -1;
        if (ab != NULL && nc != 3) return -1;
        if (ab == NULL && nc == 4 && !comma) return -1;
        for (int i = 0; i < 3; ++i)
            if (parse_hsl_comp(bs[i], es[i], i == 0, &comps[i]) != 0) return -1;
        int zero_a = 0;
        if (ab != NULL) {
            if (parse_component(ab, ae, 1, &zero_a) != 0) return -1;
        } else if (nc == 4) {
            if (parse_component(bs[3], es[3], 1, &zero_a) != 0) return -1;
        }
        hsl_to_rgb(comps[0], comps[1], comps[2], &out->r, &out->g, &out->b);
        return zero_a ? 1 : 0;   /* 1: fully transparent */
    }

    if (nc < 3 || nc > 4) return -1;
    if (ab != NULL && nc != 3) return -1;
    if (ab == NULL && nc == 4 && !comma) return -1;
    for (int i = 0; i < 3; ++i)
        if (parse_component(bs[i], es[i], 0, &comps[i]) != 0) return -1;
    int zero_a = 0;
    if (ab != NULL) {
        if (parse_component(ab, ae, 1, &zero_a) != 0) return -1;
    } else if (nc == 4) {
        if (parse_component(bs[3], es[3], 1, &zero_a) != 0) return -1;
    }
    out->r = (unsigned char)comps[0];
    out->g = (unsigned char)comps[1];
    out->b = (unsigned char)comps[2];
    return zero_a ? 1 : 0;   /* 1: fully transparent */
}

/* --- CSS Color 4 sections 8-9: lab(), lch(), oklab(), oklch() -------------------
 * Space-separated syntax only (these functions have no legacy comma form), with an
 * optional `/ alpha` that is validated and discarded like every other alpha here.
 * The result is converted to sRGB and clipped per channel to its gamut: CSS Color 4
 * section 13.2 asks for chroma reduction instead, which differs only for colours
 * sRGB cannot show at all. */

#define CC_PI 3.14159265358979323846

/* One component: a <number>, a <percentage> (scaled so 100% == pct_ref), `none`
 * (0), or -- when is_hue -- an <angle> in deg/grad/rad/turn, returned in degrees. */
static int lab_comp(const char *b, const char *e, double pct_ref, int is_hue, double *out) {
    while (b < e && *b == ' ') ++b;
    while (e > b && e[-1] == ' ') --e;
    if (b == e) return -1;
    if (e - b == 4 && memcmp(b, "none", 4) == 0) { *out = 0.0; return 0; }
    if (e[-1] == '%') {
        double v;
        if (cc_scan_number(b, e - 1, &v) != 0) return -1;
        if (is_hue) return -1;
        *out = v / 100.0 * pct_ref;
        return 0;
    }
    if (is_hue) {
        static const struct { const char *u; double to_deg; } U[] = {
            { "grad", 0.9 }, { "turn", 360.0 }, { "deg", 1.0 }, { "rad", 180.0 / CC_PI } };
        for (size_t k = 0; k < sizeof U / sizeof U[0]; ++k) {
            size_t n = strlen(U[k].u);
            if ((size_t)(e - b) > n && memcmp(e - n, U[k].u, n) == 0) {
                double v;
                if (cc_scan_number(b, e - n, &v) != 0) return -1;
                *out = v * U[k].to_deg;
                return 0;
            }
        }
    }
    return cc_scan_number(b, e, out);
}

static unsigned char srgb_encode(double lin) {
    double v = (lin <= 0.0031308) ? 12.92 * lin : 1.055 * pow(lin, 1.0 / 2.4) - 0.055;
    if (!(v > 0.0)) v = 0.0;          /* also catches NaN */
    if (v > 1.0) v = 1.0;
    return (unsigned char)cc_round(v * 255.0);
}

static void oklab_to_rgb(double L, double a, double b, cc_rgb *out) {
    double l = L + 0.3963377774 * a + 0.2158037573 * b;
    double m = L - 0.1055613458 * a - 0.0638541728 * b;
    double s = L - 0.0894841775 * a - 1.2914855480 * b;
    l = l * l * l; m = m * m * m; s = s * s * s;
    out->r = srgb_encode( 4.0767416621 * l - 3.3077115913 * m + 0.2309699292 * s);
    out->g = srgb_encode(-1.2684380046 * l + 2.6097574011 * m - 0.3413193965 * s);
    out->b = srgb_encode(-0.0041960863 * l - 0.7034186147 * m + 1.7076147010 * s);
}

/* CIE Lab (D50, CSS Color 4 section 9.4) -> XYZ D50 -> Bradford D65 -> linear sRGB. */
static void lab_to_rgb(double L, double a, double b, cc_rgb *out) {
    const double k = 24389.0 / 27.0, e = 216.0 / 24389.0;
    double fy = (L + 16.0) / 116.0, fx = a / 500.0 + fy, fz = fy - b / 200.0;
    double xr = (fx * fx * fx > e) ? fx * fx * fx : (116.0 * fx - 16.0) / k;
    double yr = (L > k * e) ? fy * fy * fy : L / k;
    double zr = (fz * fz * fz > e) ? fz * fz * fz : (116.0 * fz - 16.0) / k;
    double X = xr * 0.3457 / 0.3585, Y = yr, Z = zr * (1.0 - 0.3457 - 0.3585) / 0.3585;
    double X65 =  0.955473421488075 * X - 0.02309845494876471 * Y + 0.06325924320057072 * Z;
    double Y65 = -0.0283697093338637 * X + 1.0099953980813041 * Y + 0.021041441191917323 * Z;
    double Z65 =  0.012314014864481998 * X - 0.020507649298898964 * Y + 1.330365926242124 * Z;
    out->r = srgb_encode( 3.2409699419045226 * X65 - 1.537383177570094 * Y65 - 0.4986107602930034 * Z65);
    out->g = srgb_encode(-0.9692436362808796 * X65 + 1.8759675015077202 * Y65 + 0.04155505740717559 * Z65);
    out->b = srgb_encode( 0.05563007969699366 * X65 - 0.20397695888897652 * Y65 + 1.0569715142428786 * Z65);
}

/* lab()/lch()/oklab()/oklch() on the lowercased token s. Returns 0 / -1. */
static int parse_lab_family(const char *s, cc_rgb *out) {
    int ok = 0, polar = 0;
    const char *p;
    if (strncmp(s, "oklab(", 6) == 0)      { p = s + 6; ok = 1; }
    else if (strncmp(s, "oklch(", 6) == 0) { p = s + 6; ok = 1; polar = 1; }
    else if (strncmp(s, "lab(", 4) == 0)   { p = s + 4; }
    else if (strncmp(s, "lch(", 4) == 0)   { p = s + 4; polar = 1; }
    else return -1;
    const char *close = strchr(p, ')');
    if (close == NULL) return -1;
    for (const char *q = close + 1; *q != '\0'; ++q) if (*q != ' ') return -1;
    const char *bs[4], *es[4], *ab = NULL, *ae = NULL;
    int comma = 0;
    int nc = cc_split_args(p, close, bs, es, &ab, &ae, &comma);
    if (nc != 3 || comma) return -1;
    int zero_a = 0;
    if (ab != NULL && parse_component(ab, ae, 1, &zero_a) != 0) return -1;
    if (zero_a) { out->r = 0; out->g = 0; out->b = 0; return 1; }   /* transparent */
    /* Percentage references (CSS Color 4 sections 8.1, 8.2, 9.2, 9.3). */
    double L, c1, c2;
    double l_ref = ok ? 1.0 : 100.0;
    double ab_ref = ok ? 0.4 : 125.0;
    double c_ref = ok ? 0.4 : 150.0;
    if (lab_comp(bs[0], es[0], l_ref, 0, &L) != 0) return -1;
    if (lab_comp(bs[1], es[1], polar ? c_ref : ab_ref, 0, &c1) != 0) return -1;
    if (lab_comp(bs[2], es[2], ab_ref, polar, &c2) != 0) return -1;
    if (L < 0.0) L = 0.0;
    if (L > l_ref) L = l_ref;
    if (polar) {
        double C = (c1 < 0.0) ? 0.0 : c1, h = c2 * CC_PI / 180.0;
        c1 = C * cos(h);
        c2 = C * sin(h);
    }
    if (ok) oklab_to_rgb(L, c1, c2, out);
    else    lab_to_rgb(L, c1, c2, out);
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
    } else if (strncmp(buf, "lab(", 4) == 0 || strncmp(buf, "lch(", 4) == 0 ||
               strncmp(buf, "oklab(", 6) == 0 || strncmp(buf, "oklch(", 6) == 0) {
        rc = parse_lab_family(buf, &tmp);
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
    /* 1 = parsed, but with a zero alpha: that colour IS `transparent`. */
    if (rc == 1) {
        tmp.r = 0; tmp.g = 0; tmp.b = 0;
        *out = tmp;
        return CC_TRANSPARENT;
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
