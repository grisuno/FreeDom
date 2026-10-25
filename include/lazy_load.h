#ifndef FREEDOM_LAZY_LOAD_H
#define FREEDOM_LAZY_LOAD_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * lazy_load -- which deferred resources must be fetched now (spec/lazy_load.md).
 * Pure: no I/O, no state. Shared by lazy <img> and CSS background-image so "near the viewport"
 * means ONE thing.
 */

/* 1 when the vertical span [top, top+height] lies within `margin` px of the viewport
 * [view_top, view_top+view_h]; a box that was never placed (height < 0) is "near" so content never
 * stays missing (fail open). All values in the same coordinate space. */
static inline int ll_near_viewport(double top, double height, double view_top, double view_h,
                                   double margin) {
    if (height < 0.0) return 1;
    double lo = view_top - margin, hi = view_top + view_h + margin;
    return !(top + height < lo || top > hi);
}

#endif /* FREEDOM_LAZY_LOAD_H */
