/*
 * dom_debug — see include/dom_debug.h and spec/dom_debug.md.
 *
 * Pure formatter: walks an inert rd_doc and writes a deterministic, line-oriented
 * dump into a caller buffer with a bounded cursor that never overruns. No I/O, no
 * allocation. The only hostile bytes touched (block text/href) are emitted through a
 * truncating, control-byte-escaping field writer so one block stays one line.
 */

#include "dom_debug.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "box_style.h"   /* bx_display */
#include "css.h"         /* css_align, css_border_style */
#include "flex_layout.h" /* fx_justify */
#include "page_view.h"   /* PV_LEN_UNSET, pv_box_def */

/* Bounded write cursor: `pos` bytes are committed to `out` (always leaving room for
 * the terminating NUL); `need` counts every byte that WOULD be written so the caller
 * gets snprintf semantics even when truncated. */
typedef struct dd_cursor {
    char  *out;
    size_t cap;
    size_t pos;
    size_t need;
} dd_cursor;

static void dd_putc(dd_cursor *c, char ch) {
    if (c->out != NULL && c->cap != 0 && c->pos + 1 < c->cap) c->out[c->pos++] = ch;
    c->need++;
}

static void dd_emit(dd_cursor *c, const char *s, size_t len) {
    for (size_t i = 0; i < len; ++i) dd_putc(c, s[i]);
}

static void dd_puts(dd_cursor *c, const char *s) {
    if (s == NULL) return;
    while (*s) dd_putc(c, *s++);
}

/* Formats short fixed fields (ints, hex colours, fixed tokens) only; the variable
 * hostile fields go through dd_field. Keeps `need` exact even on the impossible
 * overflow of the local buffer. */
static void dd_printf(dd_cursor *c, const char *fmt, ...) {
    char tmp[256];
    va_list ap;
    va_start(ap, fmt);
    int k = vsnprintf(tmp, sizeof tmp, fmt, ap);
    va_end(ap);
    if (k <= 0) return;
    size_t kn = (size_t)k;
    if (kn < sizeof tmp) {
        dd_emit(c, tmp, kn);
    } else {
        dd_emit(c, tmp, sizeof tmp - 1);
        c->need += kn - (sizeof tmp - 1);
    }
}

/* Emits a hostile, NUL-terminated string truncated to DD_FIELD_MAX bytes, with
 * control bytes (< 0x20 or 0x7f) rendered as '.', so the dump stays one line per
 * block and cannot be smeared by a malicious document. A trailing ellipsis marks
 * truncation. */
static void dd_field(dd_cursor *c, const char *s) {
    if (s == NULL) return;
    size_t i = 0;
    for (; s[i] != '\0' && i < DD_FIELD_MAX; ++i) {
        unsigned char ch = (unsigned char)s[i];
        dd_putc(c, (ch < 0x20 || ch == 0x7f) ? '.' : (char)ch);
    }
    if (s[i] != '\0') dd_puts(c, "\xE2\x80\xA6"); /* ... (UTF-8 horizontal ellipsis) */
}

/* A border/outline width or radius that is unset (PV_LEN_UNSET) or negative reads as
 * 0 ("no border"); otherwise the value. */
static int dd_w(int v) { return (v == PV_LEN_UNSET || v < 0) ? 0 : v; }

/* "#rrggbb" for a packed colour, "-" when unset (-1). */
static void dd_color(dd_cursor *c, int rgb) {
    if (rgb < 0) dd_puts(c, "-");
    else dd_printf(c, "#%06x", rgb & 0xffffff);
}

static const char *dd_display_name(int d) {
    switch (d) {
        case BX_DISPLAY_FLEX: return "flex";
        case BX_DISPLAY_GRID: return "grid";
        default:              return "block";
    }
}

static const char *dd_justify_name(int j) {
    switch (j) {
        case FX_JUSTIFY_END:           return "end";
        case FX_JUSTIFY_CENTER:        return "center";
        case FX_JUSTIFY_SPACE_BETWEEN: return "space-between";
        case FX_JUSTIFY_SPACE_AROUND:  return "space-around";
        case FX_JUSTIFY_SPACE_EVENLY:  return "space-evenly";
        case FX_JUSTIFY_START:
        default:                       return "start";
    }
}

static const char *dd_align_name(int a) {
    switch (a) {
        case CSS_ALIGN_LEFT:    return "left";
        case CSS_ALIGN_CENTER:  return "center";
        case CSS_ALIGN_RIGHT:   return "right";
        case CSS_ALIGN_JUSTIFY: return "justify";
        default:                return "unset";
    }
}

static const char *dd_position_name(int p) {
    switch (p) {
        case CSS_POS_STATIC:   return "static";
        case CSS_POS_RELATIVE: return "relative";
        case CSS_POS_ABSOLUTE: return "absolute";
        case CSS_POS_FIXED:    return "fixed";
        case CSS_POS_STICKY:   return "sticky";
        default:               return "static";
    }
}

/* A px inset value for the dump: 0 for unset/auto (so the line stays compact). */
static int dd_inset(int v) {
    return (v == PV_LEN_UNSET || v == CSS_LEN_AUTO) ? 0 : v;
}

static const char *dd_border_style_name(int s) {
    switch (s) {
        case CSS_BST_SOLID:  return "solid";
        case CSS_BST_DASHED: return "dashed";
        case CSS_BST_DOTTED: return "dotted";
        case CSS_BST_DOUBLE: return "double";
        case CSS_BST_GROOVE: return "groove";
        case CSS_BST_RIDGE:  return "ridge";
        case CSS_BST_INSET:  return "inset";
        case CSS_BST_OUTSET: return "outset";
        case CSS_BST_HIDDEN: return "hidden";
        case CSS_BST_NONE:   return "none";
        default:             return "none";
    }
}

/* Number of distinct container groups (cont_id >= 0). Document order means a new id
 * only appears the first time it is seen, so counting first-appearances is exact and
 * O(n^2) over a bounded block list (no allocation). */
static size_t dd_count_containers(const rd_doc *doc) {
    size_t n = rd_count(doc), groups = 0;
    for (size_t i = 0; i < n; ++i) {
        int id = rd_at(doc, i)->cont_id;
        if (id < 0) continue;
        int seen = 0;
        for (size_t j = 0; j < i; ++j) {
            if (rd_at(doc, j)->cont_id == id) { seen = 1; break; }
        }
        if (!seen) groups++;
    }
    return groups;
}

static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b) {
    dd_printf(c, "  #%zu parent=%d place(l=%d r=%d w=%d center=%d) bg=",
              id, b->parent_id, b->box_l, b->box_r, b->box_w, b->box_center);
    dd_color(c, b->bg_rgb);
    dd_printf(c, " pad(%d/%d/%d/%d) bord(%d/%d/%d/%d %s) radius=%d shadow=%d outline=%d",
              dd_w(b->pad_t), dd_w(b->pad_r), dd_w(b->pad_b), dd_w(b->pad_l),
              dd_w(b->bord_tw), dd_w(b->bord_rw), dd_w(b->bord_bw), dd_w(b->bord_lw),
              dd_border_style_name(b->bord_ts), dd_w(b->border_radius),
              (b->bsh_color >= 0) ? 1 : 0, dd_w(b->outline_w));
    /* Positioning, only when a real (non-static) position is set, so the common case
     * stays compact. The painter honors relative; absolute/fixed/sticky are carried
     * but deferred (box engine). */
    if (b->position == CSS_POS_RELATIVE || b->position == CSS_POS_ABSOLUTE ||
        b->position == CSS_POS_FIXED || b->position == CSS_POS_STICKY) {
        dd_printf(c, " pos=%s inset(t=%d r=%d b=%d l=%d)", dd_position_name(b->position),
                  dd_inset(b->inset_top), dd_inset(b->inset_right),
                  dd_inset(b->inset_bottom), dd_inset(b->inset_left));
        if (b->z_index != PV_LEN_UNSET) dd_printf(c, " z=%d", b->z_index);
    }
    dd_putc(c, '\n');
}

static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b) {
    dd_printf(c, "  #%zu %s", i, rd_kind_name(b->kind));
    const char *tag = rd_block_tag(b);
    dd_printf(c, " <%s>", (tag != NULL) ? tag : "-");

    if (b->block_break) dd_puts(c, " bb");
    if (b->kind == RD_HEADING && b->heading_level > 0) dd_printf(c, " h%d", b->heading_level);
    if (b->bold)   dd_puts(c, " b");
    if (b->italic) dd_puts(c, " i");
    if (b->indent) dd_printf(c, " indent=%d", b->indent);

    if (b->cont_id >= 0) {
        dd_printf(c, " cont=#%d(%s cols=%d gap=%d %s)",
                  b->cont_id, dd_display_name(b->cont_display), b->cont_cols,
                  b->cont_gap, dd_justify_name(b->cont_justify));
        /* Item identity: runs sharing cont/item are fragments of one flex/grid
         * item and flow together in one cell. */
        if (b->cont_item >= 0) dd_printf(c, " item=%d", b->cont_item);
        /* Stage 3 flex per-item: printed only when the author set one, so the
         * default dump stays byte-identical. dir is the container's. */
        if (b->flex_direction != 0) dd_printf(c, " dir=%d", b->flex_direction);
        if (b->flex_grow >= 0)      dd_printf(c, " grow=%d", b->flex_grow);
        if (b->flex_shrink >= 0)    dd_printf(c, " shrink=%d", b->flex_shrink);
        if (b->flex_basis >= 0)     dd_printf(c, " basis=%d", b->flex_basis);
        if (b->flex_order != CSS_LEN_UNSET) dd_printf(c, " order=%d", b->flex_order);
    }
    if (b->block_id >= 0) dd_printf(c, " box=#%d", b->block_id);

    /* Float layout (spec/float.md): printed only when set, so the default dump stays
     * byte-identical. side 2 = left, 3 = right (css_float values). */
    if (b->float_id >= 0)
        dd_printf(c, " float=%s(#%d)", (b->float_side == CSS_FLOAT_RIGHT) ? "right" : "left",
                  b->float_id);
    if (b->float_clear) dd_printf(c, " clear=%d", b->float_clear);

    if (b->text_align)    dd_printf(c, " align=%s", dd_align_name(b->text_align));
    if (b->font_scale)    dd_printf(c, " fscale=%d", b->font_scale);
    if (b->line_scale)    dd_printf(c, " lscale=%d", b->line_scale);
    if (b->fg_rgb >= 0)   { dd_puts(c, " fg="); dd_color(c, b->fg_rgb); }
    if (b->bg_rgb >= 0)   { dd_puts(c, " bg="); dd_color(c, b->bg_rgb); }
    if (b->box_w)         dd_printf(c, " w=%d", b->box_w);
    if (b->box_l || b->box_r) dd_printf(c, " ins(l=%d r=%d)", b->box_l, b->box_r);
    if (b->box_center)    dd_puts(c, " center");

    if (b->href != NULL && b->href[0] != '\0') { dd_puts(c, " href="); dd_field(c, b->href); }

    dd_puts(c, " \"");
    dd_field(c, b->text);
    dd_puts(c, "\"\n");
}

size_t dd_format(const rd_doc *doc, char *out, size_t cap) {
    dd_cursor c = { out, cap, 0, 0 };

    size_t nblocks = rd_count(doc);
    size_t nboxes  = rd_box_count(doc);
    size_t nconts  = (doc != NULL) ? dd_count_containers(doc) : 0;
    int    imgs    = (doc != NULL) ? (doc->has_images ? 1 : 0) : 0;

    dd_puts(&c, "=== Freedom render tree ===\n");
    dd_printf(&c, "blocks: %zu  boxes: %zu  containers: %zu  has_images: %d\n",
              nblocks, nboxes, nconts, imgs);

    if (nboxes > 0) {
        dd_puts(&c, "[boxes]\n");
        for (size_t i = 0; i < nboxes; ++i) {
            const pv_box_def *b = rd_box_at(doc, i);
            if (b != NULL) dd_box_line(&c, i, b);
        }
    }

    dd_puts(&c, "[blocks]\n");
    for (size_t i = 0; i < nblocks; ++i) {
        const rd_block *b = rd_at(doc, i);
        if (b != NULL) dd_block_line(&c, i, b);
    }

    /* Always NUL-terminate when there is room for it. */
    if (out != NULL && cap != 0) out[(c.pos < cap) ? c.pos : cap - 1] = '\0';
    return c.need;
}
