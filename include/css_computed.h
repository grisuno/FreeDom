#ifndef FREEDOM_CSS_COMPUTED_H
#define FREEDOM_CSS_COMPUTED_H

#include <stddef.h>

#include "css.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * css_computed -- a resolved css_style as the text getComputedStyle returns.
 * Pure: no I/O, no allocation, reentrant. See spec/js_computed_style.md.
 */

#define CCM_VALUE_MAX 256   /* longest value ccm_get writes, terminator included */

typedef struct ccm_input {
    const css_style *st;
    double           font_px;         /* computed font-size in px (> 0) */
    int              inherited_color; /* 0xRRGGBB from the nearest declaring ancestor, or -1 */
    const char      *tag;             /* lowercase tag name, or NULL: UA default display for it */
} ccm_input;

/* Writes the computed value of the kebab-case property `prop` into out (cap bytes,
 * NUL terminated). Returns its length, or 0 when the property is unknown, in which
 * case out is "". in == NULL or cap == 0 => 0. */
size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap);

/* The properties ccm_get knows, for enumeration (length/item/cssText). */
size_t      ccm_property_count(void);
const char *ccm_property_name(size_t i);

#endif
