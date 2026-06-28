# Especificación: `js_dom`

> Puente DOM ↔ JS (cierre del cableado del Hito 3). Estado: **SPEC + TEST (rojo)**.
> Metodología: SDD + TDD. Esta spec es el contrato; `tests/test_js_dom.c` debe fallar hasta que
> exista `src/js_dom.c` (estado rojo).

## 1. Propósito

`js_dom` conecta los dos módulos verdes — el índice `dom` (solo lectura) y el motor aislado
`js_sandbox` — exponiendo al script no confiable una **API DOM de solo lectura, mínima y
validada**. Es el "cableado del DOM inerte" que el Hito 3 dejó fuera de alcance.

Diseño Zero Trust: **no se exponen objetos vivos** del motor ni nodos como objetos JS con
prototipos. Los nodos son **handles enteros opacos**; cada llamada valida sus argumentos contra
el índice real. Así la superficie auditada es un puñado de funciones nativas, no un grafo de
objetos. La capa ergonómica (`document`, objetos `Node` con propiedades) puede construirse encima
más adelante, en JS o en C, sin ampliar el núcleo de confianza.

## 2. Decisión de diseño

- El índice `dom` se guarda en el *context opaque* del motor (`JS_SetContextOpaque`), **no**
  alcanzable desde JS. Las funciones nativas lo recuperan con `JS_GetContextOpaque`.
- Se instala un objeto global `dom` con métodos **no escribibles, no configurables**
  (`JS_PROP_ENUMERABLE` puro) y el propio objeto se sella con `JS_PreventExtensions`. Un script
  no puede sustituir `dom`, ni reemplazar `dom.getElementById`, ni inyectar métodos nuevos.
- El bridge usa una costura mínima de `js_sandbox` (`js_context_raw`) que devuelve el contexto
  del motor como `void*` opaco — sin filtrar tipos `JS*` fuera del módulo, igual que
  `hp_document_root` para `dom`.
- **El índice `dom` debe sobrevivir al `js_context`** (se referencia, no se copia).

## 3. Superficie expuesta a JS

Objeto global `dom` (solo lectura). Handles = enteros; "ninguno" = `null`.

| Método JS | Devuelve | Mapea a |
| :-- | :-- | :-- |
| `dom.nodeCount()` | número | `dom_node_count` |
| `dom.getElementById(id)` | handle \| `null` | `dom_get_element_by_id` |
| `dom.getByTag(tag)` | array de handles | `dom_get_by_tag` |
| `dom.getByClass(cls)` | array de handles | `dom_get_by_class` |
| `dom.tagName(h)` | string \| `null` | `dom_tag_name` |
| `dom.getAttribute(h, name)` | string \| `null` | `dom_get_attribute` |
| `dom.parent(h)` | handle \| `null` | `dom_parent` |
| `dom.firstChild(h)` | handle \| `null` | `dom_first_child` |
| `dom.nextSibling(h)` | handle \| `null` | `dom_next_sibling` |
| `dom.precedes(a, b)` | booleano | `dom_precedes` |
| `dom.textContent(h)` | string | `dom_text_content` |
| `dom.setText(h, str)` | `undefined` | `dom_set_text_content` (detach-safe) |
| `dom.getTitle()` / `setTitle(str)` | string / `undefined` | `dom_document_title` / `_set` |
| `dom.createElement(tag)` | handle | `dom_create_element` (índice crece) |
| `dom.appendChild(p, c)` / `removeChild(p, c)` | bool | `dom_append_child` / `_remove` |
| `dom.setAttribute(h, n, v)` | `undefined` | `dom_set_attribute` (re-indexa id/class) |

**Fachada `document` (Hito 20b/20c):** un shim JS inyectado por `jd_install` define `document` sobre la
API de handles para que scripts reales corran. Lectura/escritura: `document.title`,
`getElementById(id)` → wrapper con `textContent` (get/set), `getAttribute`/`setAttribute`, `tagName`,
`id`/`className` (get/set), `appendChild`/`removeChild`; `createElement(tag)`; `getElementsByTagName/
ClassName`; `body`/`head`/`documentElement`. Eventos/timers **sintéticos y acotados**:
`addEventListener('load'|'DOMContentLoaded', fn)` / `window.onload` y `setTimeout`/`setInterval`
**encolan**; el worker llama `__fireDeferred()` una vez tras los scripts (dispara los handlers de carga
y vacía la cola de timers **hasta 64 veces** — no es un event loop real). `window === globalThis`,
`console` no-op. Los wrappers solo guardan el **handle entero validado** — **no** se exponen
objetos-nodo vivos del motor.

**`document.fonts` (stub identity-safe):** el shim define `document.fonts` como un `FontFaceSet`
benigno de valores fijos — `load()`→`Promise.resolve([])`, `check()`→`true`, `ready`→`Promise.resolve()`,
`status:'loaded'`, `size:0`, y `add/delete/clear/forEach/addEventListener/removeEventListener` no-op.
Motivo: scripts de feature-detection llaman `document.fonts.load(...)` muy temprano; sin el stub,
`document.fonts` era `undefined` y la lectura de `.load` lanzaba — la causa **literal** del error de
google.com `cannot read property 'load' of undefined`. No enumera fuentes reales (anti-fingerprinting)
ni toca la red.

**`location` real + navegación por JS (Hito 20e parte 1):** el worker conoce la URL de la página y la
inyecta como `globalThis.__locParts` (objeto de datos construido en C con `url_split`, **sin
interpolar** la URL hostil en JS). El shim define un `location` (y `document.location`/`document.URL`)
de **solo lectura** sobre esos componentes: `href`, `protocol`, `host`, `hostname`, `port`,
`pathname` (vacío ⇒ `/`), `search`, `hash`, `origin`. La **escritura** que navega
(`location.href = x`, `location.assign(x)`, `location.replace(x)`, `location.reload()`,
`window.location = x`) **no ejecuta nada**: solo **registra la string cruda** pedida en
`globalThis.__navReq` (+ `__navReplace`). El worker la lee con `jd_take_nav_request` tras correr los
scripts; **el padre (proceso confiable) la resuelve y gatea** con `ln_resolve(URL_real, cruda)`
(Zero Trust: el worker no resuelve, así un worker comprometido no puede colar `file:///etc/passwd`).
Sin URL (página local/about) `location` cae al stub no-op previo. Última asignación gana.

Lo que **no** existe aún (por diseño): `innerHTML` (getter — serialización), eventos **interactivos**
(clic del usuario), timers **asíncronos** reales (event loop que empuje vistas), scripts externos
(`src`). Todas las mutaciones son **memory-safe**: remover detacha (no destruye) → un handle previo
nunca cuelga; agregar nodos nunca libera. Un handle inválido produce `null`/`""`/`false`, **nunca** un
fallo del host.

## 4. Contrato de la API (C)

Definida en `include/js_dom.h`.

```c
typedef enum jd_status {
    JD_OK = 0,
    JD_ERR_NULL_ARG,
    JD_ERR_OOM,
    JD_ERR_INTERNAL
} jd_status;

/* Instala el global `dom` (con mutadores memory-safe) y la fachada `document` en el
 * sandbox, respaldado por idx (ya no const: expone mutadores). idx debe sobrevivir a
 * ctx. Llamar sobre un contexto recien creado. */
jd_status jd_install(js_context *ctx, dom_index *idx);

/* Hito 20e: instala un `location` real de solo lectura sobre los componentes de la URL
 * de la pagina, y arma la captura de navegacion (location.href=/assign/replace/reload/
 * window.location=). parts puede ser NULL (sin URL https): location cae al stub no-op.
 * href es la URL completa (puede ser file:///about); parts (si no es NULL) la
 * descompone via url_split. No resuelve ni gatea: solo registra la string cruda. */
jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts);

/* Hito 20e: lee (y limpia) el pedido de navegacion que el JS dejo en globalThis.__navReq.
 * Devuelve 1 si habia una string no vacia (copiada acotada en buf, *replace = location.replace),
 * 0 si no hubo pedido. La string es CRUDA (sin resolver): el llamante la gatea con ln_resolve. */
int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace);
```

## 5. Tabla de errores

| Código | Condición |
| :-- | :-- |
| `JD_OK` | Global `dom` instalado. |
| `JD_ERR_NULL_ARG` | `ctx == NULL` o `idx == NULL`. |
| `JD_ERR_OOM` | Fallo de asignación al construir el objeto/funciones. |
| `JD_ERR_INTERNAL` | El contexto del motor no es accesible o la instalación falló. |

## 6. Garantías de seguridad

1. **Solo lectura.** Ningún método muta el árbol; reflejan el índice ya saneado por
   `html_parse`/`dom`.
2. **Superficie mínima validada.** Solo las funciones de §3; cada una valida tipo y rango de sus
   argumentos. Handles fuera de rango o no numéricos ⇒ `null`/`false`.
3. **Métodos infalsificables.** `dom` y sus métodos son no escribibles/no configurables y el
   objeto está sellado: un script no puede secuestrar la API ni inyectar funciones.
4. **Sin fuga de punteros.** El `dom_index` vive en el context opaque del motor, inaccesible
   desde JS; los handles son índices, no direcciones.
5. **Hereda el aislamiento del Hito 3.** Sigue sin I/O y bajo los límites de
   memoria/pila/tiempo del `js_context`.
6. **Robustez.** Entradas arbitrarias desde JS no provocan crash/UB en el host (cubierto por
   pruebas y por la validación de `dom`).

## 7. Matriz de pruebas

`tests/test_js_dom.c` (cmocka), sobre un documento conocido instalado en un contexto:
- `jd_install` con args `NULL` ⇒ `JD_ERR_NULL_ARG`; instalación OK.
- `dom.getElementById('main')` no es `null`; `dom.tagName(...)==='div'`.
- `dom.getByClass('text').length === 2`; `dom.getByTag('p').length === 2`.
- Navegación: `dom.tagName(dom.firstChild(dom.getElementById('main')))==='p'`.
- `dom.getAttribute(main,'class')==='container box'`; atributo ausente ⇒ `null`.
- Handle inválido: `dom.tagName(99999)===null`; `dom.tagName(-1)===null`.
- **Infalsificable:** tras `dom.getElementById = 1`, `typeof dom.getElementById==='function'`;
  reasignar `dom` no cambia su identidad; `dom.nuevo = 1` no añade (objeto sellado).
- Hereda límites: un bucle infinito que usa `dom` sigue dando `JS_ERR_TIMEOUT`.

## 8. Fuera de alcance

- Eventos **interactivos** (clic del usuario → handler → re-render): Hito 20e parte 2.
- Timers **asíncronos** reales (event loop en el worker que empuje vistas nuevas).
- Getter de `innerHTML` (serialización del subárbol).
- Scripts externos (`src`, con política de red) y navegación con anclas de fragmento (`#id`).
- Selectores CSS completos vía `querySelector` (v1 cubre id/tag/class).
