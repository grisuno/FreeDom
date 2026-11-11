/*
 * js_intl (ji_) -- ECMA-402 formatting with a fixed locale (en-US) and zone (UTC).
 * Contract: spec/js_intl.md. Pure: no clock, no network, no system locale.
 */
#ifndef FREEDOM_JS_INTL_H
#define FREEDOM_JS_INTL_H

#ifdef __cplusplus
#error "Freedom is pure C11; C++ is not supported."
#endif

#include "js_sandbox.h"

/* Installs `Intl` and the Number/BigInt/Date toLocale* methods that delegate to it.
 * Returns 0, or -1 on a NULL context or an engine failure. */
int ji_install(js_context *ctx);

#endif /* FREEDOM_JS_INTL_H */
