# spec: js_native (`jn_`) — la superficie del host se ve nativa

## Problema

La plataforma web de Freedom (DOM, `fetch`, timers, `navigator`...) esta escrita en buena parte
como shims de JavaScript evaluados antes de la pagina. Un navegador real implementa todo eso en
codigo nativo, y una pagina lo puede comprobar sin ninguna API especial:

| Pregunta de la pagina | Firefox | Freedom antes |
| :-- | :-- | :-- |
| `Function.prototype.toString.call(setTimeout)` | `function setTimeout() {\n    [native code]\n}` | el fuente del shim |
| `String(window)` / `String(document)` / `String(navigator)` | `[object Window]` / `[object HTMLDocument]` / `[object Navigator]` | `[object global]` / `[object Object]` |
| `navigator instanceof Navigator` | `true` | `false` |
| `Object.getOwnPropertyNames(navigator).length` | `0` (todo vive en `Navigator.prototype`) | `20` |
| `'userAgent' in Navigator.prototype` | `true` | `false` |
| `navigator.plugins[0].name` (UA Firefox) | `PDF Viewer` | `Chrome PDF Plugin` |
| `CSS.supports('display','grid')` | `true` | `false` |

Cada fila es una **inconsistencia de identidad**: el UA dice Firefox y el entorno dice "motor
desconocido con polyfills". Es exactamente la senal que usan los desafios de "navegador valido"
(y, mas mundano, la que rompe librerias que detectan nativos con `/\[native code\]/`).
No es evasion: es que la identidad anti-fingerprinting (§7.2, *identidad de red = identidad
anti-fp*) sea coherente tambien por dentro. No agrega ninguna capacidad (ni red, ni disco, ni
geometria).

## Contrato

`int jn_seal(js_context *ctx)` — se llama UNA vez, despues de instalar todos los shims y antes
del primer script de pagina. Idempotente. Devuelve 0 o -1 (contexto NULL / fallo del motor).

`JSValue jn_host_eval(JSContext *c, const char *src, size_t len, const char *name)` (interno,
`src/js_native_internal.h`) — evalua codigo DEL HOST como script global. Toda funcion compilada
dentro de esa llamada no conserva su fuente.

### Dado-Cuando-Entonces

- **Fuente oculto.** Dado un shim evaluado con `jn_host_eval`, cuando la pagina llama
  `Function.prototype.toString` sobre cualquiera de sus funciones (incluidas las clausuras que
  cree despues), entonces obtiene `function NAME() {\n    [native code]\n}`. Dado codigo de
  PAGINA (`js_eval*`), entonces `toString` devuelve su fuente exacto, como siempre.
  El mecanismo es del motor (parche `JS_SetHideSource`, `third_party/quickjs/VERSION.md`): no se
  reemplaza `Function.prototype.toString`, asi que no hay envoltorio que detectar ni lista de
  funciones que mantener.
- **Nombres.** Dado un global/metodo del host definido como funcion anonima
  (`g.setTimeout=function(){}`), cuando se sella, entonces su `name` es la clave bajo la que
  esta publicado (`setTimeout`); un getter se llama `get <clave>`. Solo se nombra una funcion sin
  fuente (del host) y sin nombre propio: una funcion de pagina nunca se toca.
- **Etiquetas.** Dada una interfaz del host (`Window`, `HTMLDocument`, `Navigator`,
  `HTMLDivElement`, ...), cuando se sella, entonces su `prototype[Symbol.toStringTag]` es el
  nombre de la interfaz (no enumerable, configurable, como WebIDL). Los intrinsecos de
  ECMAScript no se tocan (`String({})` sigue siendo `[object Object]`).
- **Singletons.** Dado `navigator`/`screen`/`performance`/`history`/`location`/`crypto`...,
  cuando se sella, entonces `x instanceof Interfaz` es verdadero y `String(x)` es
  `[object Interfaz]`.
- **`navigator`.** Sus campos de identidad son getters de `Navigator.prototype`; el objeto no
  tiene propiedades propias. Los valores siguen siendo los de `anti_fp`/`identity`, y asignarlos
  no los cambia (getter sin setter). La lista de plugins y tipos MIME es la de Firefox
  (5 visores PDF, `application/pdf` + `text/pdf`) y `pdfViewerEnabled` es `true`.
- **`CSS.supports`.** `CSS.supports(prop, valor)` y `CSS.supports('(prop: valor)')` responden
  `true` solo si la propiedad es una que el motor implementa (lista cerrada espejo de la cascada)
  y el valor no esta vacio; lo desconocido es `false` (fail-closed: una pagina que cree que algo
  funciona y no funciona se ve peor que una que usa su fallback).

## Garantias de seguridad

- Ninguna capacidad nueva: solo cambia como se DESCRIBE lo que ya existe.
- El flag de ocultar fuente es por runtime y `jn_host_eval` lo restaura siempre (tambien ante
  excepcion): codigo de pagina nunca se compila con el flag puesto, y una pagina no puede
  activarlo (no hay API JS).
- El sellado corre antes que cualquier script remoto; no lee nada que la pagina controle.
- Recorrido acotado (profundidad y numero de objetos) para que el costo de arranque sea fijo.

## Fuera de alcance

- Mensajes de error y formato de `Error.stack` identicos a SpiderMonkey.
- `WebAssembly`, WebGL, `AudioContext`: hitos propios. Un desafio que los exija (hCaptcha,
  reCAPTCHA Enterprise, BotGuard) NO se resuelve con este modulo.
- Funciones que un shim cree en tiempo de ejecucion con `new Function`/`eval` (ninguno lo hace).
