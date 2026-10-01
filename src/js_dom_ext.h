#ifndef FREEDOM_JS_DOM_EXT_H
#define FREEDOM_JS_DOM_EXT_H

/* Private to js_dom.c / js_dom_ext.c: installs the DOM Standard extras (tree
 * navigation, compareDocumentPosition, attachShadow, TreeWalker/NodeIterator,
 * importNode/adoptNode, Range) on top of the document facade. Returns 0 or -1. */

#include "quickjs.h"

int jdx_install(JSContext *ctx);

#endif /* FREEDOM_JS_DOM_EXT_H */
