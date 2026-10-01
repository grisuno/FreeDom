#ifndef FREEDOM_JS_DOM_INTERNAL_H
#define FREEDOM_JS_DOM_INTERNAL_H

/* Private to the js_dom family (js_dom.c, js_fetch.c, js_events.c, js_embed.c):
 * the context accessors every native needs. Engine types stay out of include/. */

#include "dom.h"
#include "js_dom.h"
#include "quickjs.h"

jd_opaque *jd_opaque_get(JSContext *ctx);
dom_index *jd_idx(JSContext *ctx);
/* Coerces a JS argument to a node handle; -1 with a pending exception if it threw. */
int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out);
JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h);

#endif /* FREEDOM_JS_DOM_INTERNAL_H */
