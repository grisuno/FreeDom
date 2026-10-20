#ifndef FREEDOM_JS_CUSTOM_ELEMENTS_H
#define FREEDOM_JS_CUSTOM_ELEMENTS_H

/* Private to js_dom.c: installs Custom Elements v1 (spec/js_custom_elements.md) on top of the
 * document facade. Returns 0 or -1. */

#include "quickjs.h"

int jdce_install(JSContext *ctx);

#endif /* FREEDOM_JS_CUSTOM_ELEMENTS_H */
