/*
 * freedom_config -- the engine's single source of truth for rendering tunables.
 *
 * The project DoD ("no magic numbers, all in its config class") translates to C11
 * as this header: a constant that tunes layout, painting or headless export lives
 * here under a FC_ prefix and is consumed by name, never as a literal scattered
 * through the layout code. A module keeps its own CONTRACT constants (struct
 * limits, protocol bounds) in its own header; this is the shared policy layer.
 *
 * Every value carries its "why" in the comment above it -- a bare number here is
 * exactly the magic it exists to remove.
 */
#ifndef FREEDOM_CONFIG_H
#define FREEDOM_CONFIG_H

/* Width in px of the headless PNG export canvas (--download-png) and of the
 * parity viewport. The harness renders Firefox at this same width so both engines
 * measure the SAME document; the normalised desktop identity (anti-fingerprint)
 * stays 1920 and only this render viewport uses it. */
#define FC_PNG_PAGE_W 1000.0

/* Padding around the PNG export canvas (px): the document's content box is
 * FC_PNG_PAGE_W minus twice this. A page's own <html> margin overrides it. */
#define FC_PNG_MARGIN 24.0

/* Ceiling for a single exported page height in px. 1000 x 30000 x 4B ~= 120 MiB
 * worst-case buffer, which bounds a hostile page's ability to force an unbounded
 * allocation; a taller document is clipped at this height. */
#define FC_PNG_MAX_H 30000

/* Wrap threshold in px used when measuring an item's MAX-CONTENT width: wide
 * enough that no realistic line wraps, small enough to stay far from any overflow
 * in the accumulating pen arithmetic. A measurement device, not a layout value --
 * no rendered geometry is ever placed at this width. */
#define FC_FLEX_MEASURE_W 100000.0

/* The other end of the same measuring stick (px): flowed this narrow, every legal
 * break is taken, so the widest resulting line IS the item's MIN-CONTENT width
 * (CSS Sizing 3 5.1). Like FC_FLEX_MEASURE_W it is a measurement device, not a
 * layout value. */
#define FC_FLEX_MIN_MEASURE_W 1.0

/* Ceiling on the inherited font-size chain the renderer resolves per element.
 * The chain depth is chosen by the attacker, so this is an anti-DoS bound: the
 * walk is iterative and capped here, never recursive. */
#define FC_FONT_CHAIN_MAX 256

/* Ceiling on the per-page box registry. Coupled to the out-of-flow resolver's
 * indexed storage by _Static_assert in page_view.c -- a normal page can exceed a
 * lower value, which is a render bug, not a DoS bound. */
#define FC_MAX_BOXES 1024u

/* Fallback font size in px when a text shape carries no resolved size.
 * Single source for the former scattered 16.0 literals in painters and
 * harnesses; matches the UA root size so fallback text measures like body. */
#define FC_FONT_FALLBACK_PX 16.0

/* Chrome font size in px for the minimal Wayland UI shell. Formerly duplicated
 * as UI_FONT_SIZE in gui/ui_render.c and gui/browser_ui_internal.h. */
#define FC_UI_FONT_SIZE 16.0

#endif /* FREEDOM_CONFIG_H */