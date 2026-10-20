#include "css_mask.h"

#include <ctype.h>
#include <string.h>

#include "css_gradient.h"

#define CM_TOK_MAX 256
#define CM_MAX_TOKS 16

static int ieq(const char *a, const char *b) {
    for (; *a != '\0' && *b != '\0'; ++a, ++b)
        if (tolower((unsigned char)*a) != *b) return 0;
    return *a == '\0' && *b == '\0';
}

int cm_is_mask_prop(const char *prop) {
    if (prop == NULL) return 0;
    return strcmp(prop, "mask") == 0 || strcmp(prop, "mask-image") == 0 ||
           strcmp(prop, "mask-composite") == 0 || strcmp(prop, "mask-clip") == 0 ||
           strcmp(prop, "mask-origin") == 0;
}

void cm_encode_layer(const cm_layer *l, int *meta, int *alphas, int *poss) {
    *meta = 0; *alphas = 0; *poss = 0;
    if (l == NULL || l->kind == 0) return;
    unsigned ua = 0, up = 0;   /* packed unsigned: a byte in the top lane must not overflow int */
    int nst = l->nst < 2 ? 2 : (l->nst > 4 ? 4 : l->nst);
    int ang = ((l->angle % 360) + 360) % 360;
    *meta = 1 | (nst << 4) | (ang << 8);
    for (int k = 0; k < 4; ++k) {
        int a = l->alpha[k] < 0 ? 0 : (l->alpha[k] > 255 ? 255 : l->alpha[k]);
        int p = 255;                                  /* 255 = evenly spaced */
        if (l->pos[k] >= 0) {
            p = (l->pos[k] + 2) / 4;
            if (p > 254) p = 254;
        }
        ua |= (unsigned)a << (8 * k);
        up |= (unsigned)p << (8 * k);
    }
    *alphas = (int)ua;
    *poss = (int)up;
}

void cm_decode_layer(int meta, int alphas, int poss, cm_layer *out) {
    memset(out, 0, sizeof *out);
    for (int k = 0; k < 4; ++k) out->pos[k] = -1;
    if (meta < 0 || (meta & 0xf) != 1) return;
    out->kind = 1;
    out->nst = (meta >> 4) & 0xf;
    if (out->nst < 2) out->nst = 2;
    if (out->nst > 4) out->nst = 4;
    out->angle = (meta >> 8) % 360;
    if (out->angle < 0) out->angle += 360;
    for (int k = 0; k < 4; ++k) {
        out->alpha[k] = (int)(((unsigned)alphas >> (8 * k)) & 0xffu);
        int p = (int)(((unsigned)poss >> (8 * k)) & 0xffu);
        out->pos[k] = (p == 255) ? -1 : (p * 4 > 1000 ? 1000 : p * 4);
    }
}

/* Splits s into depth-0 pieces at `sep` (',' or whitespace). Returns the count, -1 on overflow. */
static int split(const char *s, int comma, char (*out)[CM_TOK_MAX], int max) {
    int n = 0, depth = 0;
    size_t k = 0;
    int in = 0;
    for (const char *p = s;; ++p) {
        char c = *p;
        int sep = (c == '\0') || (depth == 0 && (comma ? c == ',' : isspace((unsigned char)c)));
        if (sep) {
            if (in) {
                if (n >= max) return -1;
                out[n][k] = '\0';
                ++n; k = 0; in = 0;
            } else if (comma && c == ',') {
                return -1;   /* an empty layer */
            }
            if (c == '\0') break;
            continue;
        }
        if (c == '(') ++depth;
        else if (c == ')' && depth > 0) --depth;
        if (n >= max || k + 1 >= CM_TOK_MAX) return -1;   /* never write past out[max-1] */
        out[n][k++] = c;
        in = 1;
    }
    return n;
}

static int composite_word(const char *t, int webkit) {
    if (ieq(t, "add")) return CM_COMP_ADD;
    if (ieq(t, "subtract")) return CM_COMP_SUBTRACT;
    if (ieq(t, "intersect")) return CM_COMP_INTERSECT;
    if (ieq(t, "exclude")) return CM_COMP_EXCLUDE;
    if (webkit) {
        if (ieq(t, "source-over")) return CM_COMP_ADD;
        if (ieq(t, "source-out")) return CM_COMP_SUBTRACT;
        if (ieq(t, "source-in")) return CM_COMP_INTERSECT;
        if (ieq(t, "xor")) return CM_COMP_EXCLUDE;
    }
    return -1;
}

static int clip_word(const char *t) {
    if (ieq(t, "border-box")) return CM_CLIP_BORDER;
    if (ieq(t, "padding-box")) return CM_CLIP_PADDING;
    if (ieq(t, "content-box")) return CM_CLIP_CONTENT;
    return -1;
}

/* One image token -> a layer. 1 = layer set, 2 = `none`, 0 = unsupported/malformed. */
static int image_layer(const char *tok, cm_layer *l) {
    memset(l, 0, sizeof *l);
    if (ieq(tok, "none")) return 2;
    int angle = 180, colors[4] = { -1, -1, -1, -1 }, pos[4] = { -1, -1, -1, -1 };
    int n = cg_parse_linear(tok, &angle, colors, pos);
    if (n < 2) return 0;
    l->kind = 1;
    l->nst = n > 4 ? 4 : n;
    l->angle = angle;
    for (int k = 0; k < 4; ++k) {
        int c = (k < l->nst) ? colors[k] : 0;
        int t = (c >> 24) & 0x7f;                    /* 0 opaque .. 127 clear */
        l->alpha[k] = (127 - t) * 255 / 127;
        l->pos[k] = (k < l->nst) ? pos[k] : -1;
    }
    return 1;
}

static int emit_layers(css_decl *dst, int cap, int shorthand, const char *val) {
    char layers[CM_LAYERS + 1][CM_TOK_MAX];
    int nl = split(val, 1, layers, CM_LAYERS + 1);
    if (nl < 1 || nl > CM_LAYERS) return 0;
    cm_layer L[CM_LAYERS];
    int clips[CM_LAYERS] = { CM_CLIP_BORDER, CM_CLIP_BORDER };
    int comp = CM_COMP_ADD, any = 0;
    for (int i = 0; i < nl; ++i) {
        char toks[CM_MAX_TOKS][CM_TOK_MAX];
        int nt = split(layers[i], 0, toks, CM_MAX_TOKS);
        if (nt < 1) return 0;
        int got_image = 0;
        memset(&L[i], 0, sizeof L[i]);
        for (int t = 0; t < nt; ++t) {
            cm_layer img;
            int r = image_layer(toks[t], &img);
            if (r == 1 || r == 2) {
                got_image = 1;
                if (r == 1) { L[i] = img; any = 1; }
                continue;
            }
            if (!shorthand) return 0;                 /* mask-image takes images only */
            int c = clip_word(toks[t]);
            if (c >= 0) { clips[i] = c; continue; }
            int k = composite_word(toks[t], 0);
            if (k >= 0) { if (i == 0) comp = k; continue; }
            if (strstr(toks[t], "url(") != NULL || strstr(toks[t], "gradient(") != NULL ||
                strstr(toks[t], "image-set(") != NULL)
                return 0;                             /* an image we do not support */
            /* repeat / position / size / mode tokens: accepted, not implemented */
        }
        if (!got_image) return 0;
    }
    int need = 1 + 6 + (shorthand ? 2 : 0);
    if (cap < need) return 0;
    int n = 0;
    dst[n].prop = P_MASK_N; dst[n].ival = any ? nl : 0; ++n;
    for (int i = 0; i < CM_LAYERS; ++i) {
        int m = 0, a = 0, p = 0;
        if (i < nl) cm_encode_layer(&L[i], &m, &a, &p);
        dst[n].prop = (i == 0) ? P_MASK_L0A : P_MASK_L1A; dst[n].ival = m; ++n;
        dst[n].prop = (i == 0) ? P_MASK_L0B : P_MASK_L1B; dst[n].ival = a; ++n;
        dst[n].prop = (i == 0) ? P_MASK_L0C : P_MASK_L1C; dst[n].ival = p; ++n;
    }
    if (shorthand) {
        dst[n].prop = P_MASK_CLIP; dst[n].ival = clips[0] | (clips[1] << 2); ++n;
        dst[n].prop = P_MASK_COMP; dst[n].ival = comp; ++n;
    }
    return n;
}

int cm_expand(const char *prop, const char *val, css_decl *dst, int cap, int webkit_vocab) {
    if (prop == NULL || val == NULL || dst == NULL || cap < 1) return 0;
    while (isspace((unsigned char)*val)) ++val;
    if (*val == '\0') return 0;
    if (strcmp(prop, "mask-composite") == 0) {
        char tok[CM_LAYERS + 1][CM_TOK_MAX];
        int n = split(val, 1, tok, CM_LAYERS + 1);
        if (n < 1) return 0;
        int k = composite_word(tok[0], webkit_vocab);
        if (k < 0) return 0;
        dst[0].prop = P_MASK_COMP; dst[0].ival = k;
        return 1;
    }
    if (strcmp(prop, "mask-clip") == 0 || strcmp(prop, "mask-origin") == 0) {
        char tok[CM_LAYERS + 1][CM_TOK_MAX];
        int n = split(val, 1, tok, CM_LAYERS + 1);
        if (n < 1) return 0;
        int c0 = clip_word(tok[0]);
        int c1 = (n > 1) ? clip_word(tok[1]) : c0;
        if (c0 < 0 || c1 < 0) return 0;
        dst[0].prop = P_MASK_CLIP; dst[0].ival = c0 | (c1 << 2);
        return 1;
    }
    if (strcmp(prop, "mask-image") == 0) return emit_layers(dst, cap, 0, val);
    if (strcmp(prop, "mask") == 0) return emit_layers(dst, cap, 1, val);
    return 0;
}
