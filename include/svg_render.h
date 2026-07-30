#ifndef FREEDOM_SVG_RENDER_H
#define FREEDOM_SVG_RENDER_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * svg_render — inline <svg> markup turned into a bounded list of geometric shapes.
 *
 * PURE: no I/O, no network, no filesystem, no mutable global state. Hostile bytes in,
 * geometry out. The accepted grammar has NO url form at all (<image>, <use>, url())
 * so a parsed SVG structurally cannot fetch anything -- which is why inline SVG
 * renders unconditionally while <img> stays behind the images capability.
 *
 * Every bound below is fixed: a hostile document can never make this module allocate
 * in proportion to what it asks for. Past a bound the shape is dropped, never
 * truncated into something half-valid.
 *
 * See spec/svg_render.md for the full contract.
 */

typedef enum sv_status {
    SV_OK = 0,
    SV_ERR_NULL_ARG,  /* a required pointer argument was NULL */
    SV_ERR_PARSE,     /* no <svg> element, or nothing renderable inside it */
    SV_ERR_LIMIT      /* input longer than SV_MAX_INPUT */
} sv_status;

#define SV_MAX_SHAPES 512
#define SV_MAX_POINTS 4096
#define SV_MAX_SEGS   4096
#define SV_MAX_DEPTH  32
#define SV_TEXT_MAX   128
#define SV_MAX_INPUT  (1024u * 1024u)

/* CSS default replaced-element size, used when the markup declares neither
 * width/height nor a viewBox (CSS 2.1 §10.3.2). */
#define SV_DEFAULT_W 300.0
#define SV_DEFAULT_H 150.0

typedef enum sv_shape_kind {
    SV_RECT = 0,
    SV_CIRCLE,
    SV_ELLIPSE,
    SV_LINE,
    SV_POLYLINE,
    SV_POLYGON,
    SV_PATH,
    SV_TEXT
} sv_shape_kind;

/* A flattened path verb. CUBIC carries two control points plus the end point;
 * MOVE/LINE carry one point; CLOSE carries none. Quadratics and arcs are converted
 * to cubics at parse time, so the painter only ever sees these four. */
typedef enum sv_verb {
    SV_MOVE = 0,
    SV_LINETO,
    SV_CUBIC,
    SV_CLOSE
} sv_verb;

typedef struct sv_seg {
    int    verb;      /* sv_verb */
    double x[3];
    double y[3];
} sv_seg;

/* One paintable shape, already resolved: presentation attributes inherited from the
 * <g> chain, and `m` the flattened affine transform of that chain (a,b,c,d,e,f in
 * Cairo order). Colours are packed 0xRRGGBB, -1 = none, CC_COLOR_CURRENT (-2) =
 * currentColor (the painter substitutes the inherited text colour). */
typedef struct sv_shape {
    int    kind;             /* sv_shape_kind */
    int    fill;             /* 0xRRGGBB, -1 none, -2 currentColor */
    int    stroke;           /* 0xRRGGBB, -1 none, -2 currentColor */
    double stroke_w;         /* px in user space; <= 0 means no stroke */
    int    opacity;          /* 0..100 (group) */
    int    fill_opacity;     /* 0..100 */
    int    stroke_opacity;   /* 0..100 */
    int    fill_even_odd;    /* nonzero: fill-rule: evenodd */
    int    linecap;          /* 0 butt, 1 round, 2 square */
    int    linejoin;         /* 0 miter, 1 round, 2 bevel */
    /* Geometry by kind:
     *   RECT     a=x  b=y  c=width  d=height  (rx/ry rounded corners)
     *   CIRCLE   a=cx b=cy c=r
     *   ELLIPSE  a=cx b=cy c=rx     d=ry
     *   LINE     a=x1 b=y1 c=x2     d=y2
     *   TEXT     a=x  b=y  c=font-size
     *   POLYLINE/POLYGON: [first, first+count) into the point pool
     *   PATH:             [first, first+count) into the segment pool */
    double a, b, c, d;
    double rx, ry;
    size_t first, count;
    double m[6];             /* affine transform: xx, yx, xy, yy, x0, y0 */
    char   text[SV_TEXT_MAX]; /* SV_TEXT only: NUL-terminated, valid UTF-8 */
} sv_shape;

/* A parsed SVG. LARGE (fixed pools): allocate on the HEAP, never on the stack.
 * width/height are the intrinsic pixel dimensions; the viewBox (when present) is the
 * user-space rect those dimensions map to. */
typedef struct sv_image {
    double   width, height;
    double   vb_x, vb_y, vb_w, vb_h;
    int      has_viewbox;
    size_t   nshape;
    sv_shape shapes[SV_MAX_SHAPES];
    size_t   npt;
    double   px[SV_MAX_POINTS];
    double   py[SV_MAX_POINTS];
    size_t   nseg;
    sv_seg   segs[SV_MAX_SEGS];
} sv_image;

/* Parses inline <svg> markup into *out. markup need not be NUL-terminated; len is
 * authoritative. *out is fully zeroed before anything is written, so a failed parse
 * never leaves a half-filled image. Reentrant; allocates nothing. */
sv_status sv_parse(const char *markup, size_t len, sv_image *out);

/* Maps the image's user space onto the destination rect [dx, dy, dw, dh] the way a
 * `preserveAspectRatio="xMidYMid meet"` SVG does: uniform scale, centred. Writes the
 * scale and the translation the painter must apply. Never divides by zero (a
 * degenerate viewBox yields scale 1 and no offset). */
void sv_fit(const sv_image *img, double dw, double dh,
            double *scale, double *off_x, double *off_y);

#endif /* FREEDOM_SVG_RENDER_H */
