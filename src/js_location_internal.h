#ifndef FREEDOM_JS_LOCATION_INTERNAL_H
#define FREEDOM_JS_LOCATION_INTERNAL_H

/* Private to js_dom.c / js_location.c: the dom.histTarget native lives with the
 * history code but is registered in js_dom's sealed `dom` method table. Engine types
 * stay out of every public header (include/ never sees quickjs.h). */

#include "quickjs.h"

JSValue jl_m_hist_target(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv);

#endif /* FREEDOM_JS_LOCATION_INTERNAL_H */
