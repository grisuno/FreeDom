# Especificación: `js_policy`

> Hito 20 — Allowlist de JavaScript por dominio (granular). Estado: **cerrado** (spec + test verde +
> ASan/UBSan + fuzz). Metodología: SDD + TDD.

## 1. Propósito

`js_policy` es la **decisión pura** "¿debe ejecutarse JavaScript para este host?". El JS de la página
es contenido **hostil** (Zero Trust): por defecto está **apagado** y solo se habilita si el usuario
opta por el host (Secure by Default). Combina un **modo global** con la **pertenencia a una
allowlist por host** (la allowlist la resuelve `[[hostblock]]`, que ya cubre subdominios: una entrada
`example.com` cubre `www.example.com`). Sin I/O, sin estado global; toda la lógica de seguridad es
verificable directamente.

La decisión se expone como `rdp_caps.js` y la consume el pipeline de render (el worker). Hoy controla
el render de `<noscript>` (un navegador sin JS muestra el contenido de respaldo); la **ejecución** de
los scripts de páginas allowlisteadas queda apoyada sobre el mismo flag para el hito de DOM-vivo (el
puente DOM actual es de solo lectura, así que ejecutar scripts no podría mutar la página todavía).

## 2. Contrato de la API

```c
typedef enum jsp_mode {
    JSP_OFF = 0,    /* nunca ejecuta JS de página */
    JSP_ALLOWLIST,  /* solo hosts en la allowlist (defecto) */
    JSP_ON          /* todos los hosts (menos seguro; opt-in explícito) */
} jsp_mode;

bool        jsp_enabled(jsp_mode mode, int host_allowlisted);
jsp_mode    jsp_mode_from_str(const char *s);   /* NULL/desconocido => JSP_ALLOWLIST */
const char *jsp_mode_str(jsp_mode mode);        /* "off"/"allowlist"/"on" */
```

## 3. Semántica

- `jsp_enabled`: `JSP_OFF`→`false`; `JSP_ALLOWLIST`→`host_allowlisted != 0`; `JSP_ON`→`true`. Un modo
  fuera de rango → `false` (**falla cerrado**).
- `jsp_mode_from_str` (case-insensitive): `off`/`0`/`no`/`false`/`none`→`JSP_OFF`;
  `on`/`1`/`yes`/`true`/`all`→`JSP_ON`; `allowlist`/`list`/`auto` y **cualquier valor desconocido o
  NULL**→`JSP_ALLOWLIST` (el defecto conservador: solo hosts explícitos ejecutan JS).
- `jsp_mode_str`: nombre canónico en minúscula; valor desconocido → `"off"`. Nunca NULL.

## 4. Garantías

1. **Secure by Default:** el defecto efectivo (allowlist con allowlist vacía) **no ejecuta JS**.
2. **Fail-closed:** un modo inválido nunca habilita JS; un string desconocido no escala a `JSP_ON`.
3. **Pureza / Zero Trust:** sin I/O ni estado global; reentrante; ASan/UBSan limpios.
4. **Una sola fuente de verdad:** la pertenencia por host la decide `hostblock` (subdominios
   incluidos); `js_policy` solo combina modo + pertenencia, sin duplicar el matcher de hosts.

## 5. Matriz de pruebas

`tests/test_js_policy.c` (cmocka): matriz off/allowlist/on × (host listado / no); modo inválido →
`false`; parser de modos (alias, case, NULL, desconocido→allowlist); roundtrip `str→mode→str`.
Fuzz: `jsp_mode_from_str` sobre bytes aleatorios (sin crash; resultado siempre un modo válido).

## 6. Fuera de alcance

- **Ejecución** del JS de la página y mutación del DOM → repintado (hito de DOM-vivo: hoy el puente
  `[[js_dom]]` es de solo lectura). `js_policy` solo decide *si* correría.
- La carga/parseo de la allowlist (`js.conf`): la hace `hostblock`; el orquestador la cablea.
- Política por origen/eTLD+1 más fina que host+subdominio.
