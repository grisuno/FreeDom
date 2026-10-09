# Especificación: `js_dom`

> Puente DOM ↔ JS. Estado: **SPEC + TEST verde + ASan/UBSan limpio + fuzz-js verde**.
> Metodología: SDD + TDD.

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

- El *context opaque* del motor (`JS_SetContextOpaque`) apunta a una estructura `jd_opaque`
  controlada por el llamador, que contiene el `dom_index*` y el estado de eventos de click.
  **No** es alcanzable desde JS; las funciones nativas lo recuperan con `JS_GetContextOpaque`.
- Se instala un objeto global `dom` con métodos **no escribibles, no configurables**
  (`JS_PROP_ENUMERABLE` puro) y el propio objeto se sella con `JS_PreventExtensions`. Un script
  no puede sustituir `dom`, ni reemplazar `dom.getElementById`, ni inyectar métodos nuevos.
- El bridge usa una costura mínima de `js_sandbox` (`js_context_raw`) que devuelve el contexto
  del motor como `void*` opaco — sin filtrar tipos `JS*` fuera del módulo, igual que
  `hp_document_root` para `dom`.
- **El `jd_opaque` debe sobrevivir al `js_context`** (vive en el stack/struct del llamador).

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
| `dom.removeAttribute(h, n)` | `undefined` | `dom_remove_attribute` |
| `dom.registerClick(h, fn)` | `undefined` | Registra `fn` como handler de click para el nodo `h` (nativo). |
| `dom.querySelector(root, sel)` | handle \| `null` | `dom_query_selector` (`root=-1` = documento) |
| `dom.querySelectorAll(root, sel)` | array de handles | `dom_query_selector_all` |
| `dom.matches(h, sel)` | booleano | `dom_matches` |
| `dom.closest(h, sel)` | handle \| `null` | `dom_closest` |

**Selectores CSS (`querySelector`/`querySelectorAll`/`matches`/`closest`):** el shim expone
`document.querySelector(sel)`/`querySelectorAll(sel)` (alcance documento, `root=-1`) y, en el
wrapper de elemento, `el.querySelector`/`querySelectorAll` (descendientes estrictos),
`el.matches(sel)` y `el.closest(sel)`. Todos delegan en el **motor de selectores de autor**
(`css_select` vía `css_chain`): el mismo selector matchea igual desde JS que desde una hoja de
estilo (única fuente de verdad). El selector es hostil: parseo acotado, **falla cerrado** (un
selector no soportado —`:not()`, pseudo-elementos— se descarta sin lanzar; un hermano válido de la
lista sobrevive). Subconjunto soportado = el de `css_select` (tipo/`.clase`/`#id`/`*`/`[attr]` +
combinadores descendiente/hijo/hermano + pseudo-clases estructurales/`:link`).

**Eventos de click (Stage 4 dispatcher):** `addEventListener('click', fn)` y `element.onclick = fn`
registran un handler invocable desde C con `jd_fire_click(ctx, node_id)`. El handler recibe un
objeto evento mínimo con `target` (wrapper del nodo) y `preventDefault()`. Si el handler llama
`preventDefault()`, `jd_fire_click` devuelve `0` (el llamante no debe ejecutar la acción por
defecto, p. ej. seguir un enlace); de lo contrario devuelve `1`. El registro vive en un objeto
JS interno (`__clickRegistry`) indexado por handle; no hay JSValue retenido en C, así que no
hay ciclo de vida que administrar.

**Fachada `document` (Hito 20b/20c):** un shim JS inyectado por `jd_install` define `document` sobre la
API de handles para que scripts reales corran. Lectura/escritura: `document.title`,
`getElementById(id)` → wrapper con `textContent` (get/set), `getAttribute`/`setAttribute`/
`removeAttribute`/`hasAttribute`, `tagName`, `id`/`className` (get/set), `src`/`href` (get/set,
reflejan el atributo, `''` si ausente — sin resolver a URL absoluta, sin fuga de base-URL),
`dataset` (Proxy sobre los `data-*`: `el.dataset.fooBar` ↔ `data-foo-bar`, ausente ⇒ `undefined`,
**nunca** lanza), `appendChild`/`removeChild`; `createElement(tag)`; `getElementsByTagName/
ClassName`; `body`/`head`/`documentElement`. Esta **completitud del wrapper** (Hito 24) es lo que
hace correr el JS de arranque de google.com sin lanzar (`b.dataset.ved`, `a.hasAttribute(...)`,
`linkEl.removeAttribute('id')`, `d.src.substring(...)` antes reventaban). Eventos/timers
**sintéticos y acotados**:
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

**`URL` y `URLSearchParams` (identity-safe, WHATWG):** el shim moderno define los constructores
globales `URL` y `URLSearchParams` como **implementación pura en JS** (parseo de strings), sin
tocar la red, el disco ni ninguna API del host — por eso son seguros dentro del sandbox y no
filtran identidad. Motivo: son de los globals más usados de la web moderna; su ausencia era el
**primer** error de JS de Slashdot (`ReferenceError: URL is not defined`, luego
`URLSearchParams is not defined`).

- `new URL(input, base?)` descompone `input` (resolviéndolo contra `base` si es relativo) en
  `href`/`protocol`/`host`/`hostname`/`port`/`pathname`/`search`/`hash`/`origin`/`username`/
  `password` (getters de solo lectura sobre los componentes; un `input` no absoluto sin `base`
  válida **lanza `TypeError`**, como el estándar). `searchParams` devuelve un `URLSearchParams`
  vivo sobre la query. `toString()`/`toJSON()` re-serializan. `Given` una URL absoluta,
  `When` se construye un `URL`, `Then` sus componentes coinciden con `url_split` (misma
  descomposición WHATWG que usa `location`).
- `new URLSearchParams(init)` acepta una query string (con o sin `?` inicial), un objeto, o un
  arreglo de pares `[k,v]`. Métodos: `get`/`getAll`/`has`/`set`/`append`/`delete`/`sort`/`keys`/
  `values`/`entries`/`forEach`/`toString`, con decodificación/codificación **percent** y `+`↔espacio.
  Iterable (`for..of`).

Ambos son **define-guarded** (no pisan un global preexistente) y **acotados** por el presupuesto de
tiempo del intérprete (sin bucles no acotados sobre input hostil). No hay estado global mutable ni
I/O: dos páginas distintas ven implementaciones idénticas y aisladas.

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

**Cerrado 2026-07-11:** el **getter de `innerHTML`** serializa los hijos del nodo
(`dom_get_inner_html`, acotado a `DOM_INNER_HTML_MAX` = 1 MiB, falla cerrado; sobre-tope o handle
inválido ⇒ `""`, un getter jamás mata los scripts de la página). Y los **timers asíncronos son
reales**: `setTimeout`/`setInterval` registran `{fn, due, iv, id}` con su **delay virtual** en ms
(`clearTimeout`/`clearInterval` cancelan por id); el pump de carga (`__fireDeferred`) dispara solo
los de delay 0 (comportamiento histórico); `__tickTimers(elapsed)` avanza el reloj **virtual** y
dispara los vencidos en rondas acotadas (los intervalos se re-arman, mínimo 16 ms anti-loop);
`__nextTimerMs()` reporta el mínimo delay pendiente (o -1). **El reloj solo avanza cuando el padre
confiable lo dice** (`OP_TICK`/`tab_tick` — el worker no tiene reloj real ni canal de push: anti-fp
y un worker comprometido no puede auto-despertarse). La GUI y el headless programan los ticks desde
`tab_page.next_timer_ms`, con tope de ticks por carga.

Lo que **no** existe aún (por diseño): eventos distintos a click (keydown, mousemove, submit,
etc.). Todas las mutaciones son **memory-safe**: remover detacha
(no destruye) → un handle previo nunca cuelga; agregar nodos nunca libera. Un handle inválido
produce `null`/`""`/`false`, **nunca** un fallo del host.

## 4. Contrato de la API (C)

Definida en `include/js_dom.h`.

```c
typedef enum jd_status {
    JD_OK = 0,
    JD_ERR_NULL_ARG,
    JD_ERR_OOM,
    JD_ERR_INTERNAL
} jd_status;

/* Instala el global `dom` y la fachada `document`. opaque debe sobrevivir a ctx y
 * estar inicializado por el llamador (se escribe en la llamada). */
jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque);

/* Click events (Stage 4 dispatcher). state se guarda en opaque->click. */
jd_click_state *jd_click_state_new(void);
void jd_click_state_free(jd_click_state *s);
jd_status jd_install_events(js_context *ctx, jd_click_state *state);
int jd_fire_click(js_context *ctx, dom_node_id node_id);

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
| `JD_OK` | Global `dom` instalado / eventos instalados. |
| `JD_ERR_NULL_ARG` | `ctx == NULL`, `idx == NULL`, `opaque == NULL` o `state == NULL`. |
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
- **Click events (Stage 4):** `addEventListener('click', fn)` y `onclick` ejecutan el handler al
  llamar `jd_fire_click(ctx, h)`; `preventDefault()` hace que `jd_fire_click` devuelva `0`;
  sin handler devuelve `1`; `jd_install_events(NULL, NULL)` falla cerrado.

## 7b. matchMedia real + IntersectionObserver sintético (2026-07-19)

Dos capas de la superficie ambiente dejaron de ser stubs inertes porque su
inercia ROMPÍA el render visual de webs modernas, y ambas se cierran sin fugar
un solo bit real (identity-safe):

- **`matchMedia(q)` evalúa de verdad** contra la MISMA identidad normalizada que
  ya exponen `innerWidth`/`innerHeight` y las viewport units de CSS (desktop
  1920×1080, ver `[[freedom-anti-fp-network-identity]]` y spec/css.md "Viewport
  units"): `min/max-width/height` y `width/height` (unidades `px` y `em`×16),
  `orientation` (landscape), `screen`/`all` (true) vs `print` (false),
  combinadores `and`, listas con coma (OR) y prefijo `not`. Señales de identidad
  SIEMPRE normalizadas: `prefers-color-scheme: light`, `prefers-reduced-motion:
  no-preference`, `hover/any-hover: hover`, `pointer/any-pointer: fine` (la
  identidad Firefox-desktop que ya mandamos por el cable). Todo lo demás ⇒
  `false`, nunca lanza. `addListener`/`addEventListener` aceptan y jamás
  disparan (la identidad normalizada nunca cambia ⇒ cero eventos es correcto y
  determinista). **Dado** un sitio que elige layout con
  `matchMedia('(min-width:768px)')` **cuando** corre su JS **entonces** toma la
  rama desktop, sin conocer la ventana real.
- **`IntersectionObserver` dispara sintéticamente:** `observe(el)` encola vía
  `setTimeout(...,0)` (fase diferida, semántica async real) UNA entrega con
  `[{isIntersecting:true, intersectionRatio:1, target:el, time:0,
  boundingClientRect/intersectionRect: rect 0, rootBounds: 1920×1080}]`. Todos
  los valores son constantes sintéticas — cero geometría real, cero orden de
  scroll, cero timing — pero las librerías de reveal-on-scroll (AOS y familia)
  que dejan el contenido en `opacity:0` hasta que el observer dispara ahora lo
  REVELAN (antes: secciones enteras invisibles para siempre). `disconnect()`
  antes de la fase diferida suprime la entrega; `unobserve()` es no-op v1;
  `takeRecords()` ⇒ `[]`. `MutationObserver`/`ResizeObserver`/
  `PerformanceObserver` siguen sin disparar jamás (sin observación no hay
  fuga, y nada visual depende de ellos).

## 7c. Fachada HTMLMediaElement + `new Audio()` (2026-07-19)

- Todo wrapper de `<video>`/`<audio>` lleva la superficie `HTMLMediaElement`
  **identity-safe y sin red**: `play()` (marca `paused=false`, devuelve
  `Promise.resolve()` — nunca decodifica), `pause()`, `load()` no-op,
  `canPlayType()` (`probably` para mp4/mpegurl/mp2t — lo que el pipeline
  confiable reproduce nativo —, `maybe` para webm/ogg, `''` resto),
  `muted`/`autoplay`/`loop`/`controls`/`playsinline` reflejados al atributo,
  `poster`, `currentSrc` (src propio o del primer `<source>`), `buffered`/
  `played`/`seekable` como TimeRanges vacíos, `videoWidth`/`videoHeight` 0
  (sin metadata cargada: valor real), `readyState`/`networkState` 0,
  constantes `HAVE_*`/`NETWORK_*`, `textTracks` vacío y handlers
  `on<evento>` de media registrados vía `dom.registerEvent` (sintéticos; no
  disparan — no hay reproducción en el worker). Valores fijos ⇒ cero huella.
- `new Audio(src)` global: crea un `<audio>` real vía `document.createElement`
  (recibe la fachada completa por el wrap) y setea su atributo `src`. Crear
  el objeto **jamás** fetchea.
- Dado un script de player **cuando** hace feature-detection y llama
  `v.play()` **entonces** corre sin lanzar y sin tocar la red; la
  decodificación real ocurre solo en el lado confiable
  (`spec/media_decoder.md`), disparada por el click del usuario en la GUI.

## 7d. Propagación de eventos (DOM Standard §2.9) (2026-09-30)

Antes: un handler solo corría si estaba registrado **en el nodo destino**; `click` guardaba
**uno** por nodo (el último `addEventListener` pisaba al anterior); `removeEventListener` y
`dispatchEvent` eran no-op; `document`/`window` solo aceptaban `load`. Toda delegación
(React escucha en la raíz, jQuery `.on(sel)`, `document.addEventListener('click')`) quedaba
sorda.

**Un solo registro de listeners** (`__ls`, en el prelude) para elementos, `document` y `window`.
`dom.registerClick`/`registerSubmit`/`registerEvent` y sus registros desaparecen; los tres
`jd_fire_*` de C conservan su contrato (1 = acción por defecto, 0 = `preventDefault`) y pasan
todos por `__dispatchEvent`.

- **Registro:** `addEventListener(type, fn|{handleEvent}, opts)` con `opts` booleano
  (`capture`) u objeto (`capture`, `once`). El par (tipo, callback, capture) es único: registrar
  dos veces el mismo no duplica. `removeEventListener` lo quita (también de un despacho en curso).
- **`on<evento>`:** el setter ocupa **una** ranura de listener en la posición del primer set y
  la reemplaza en los siguientes; `null` la vacía; el getter devuelve la función.
- **Camino:** destino → `dom.parent` hasta la raíz → `document` → `window`, calculado **antes**
  de despachar (una mutación del DOM durante el despacho no lo cambia). Acotado a
  `JD_EVENT_PATH_MAX` 4096 nodos.
- **Fases:** captura (window → padre del destino, solo `capture`), destino (todos, en orden de
  registro), burbuja (padre → window, solo no-`capture`) **si `bubbles`**.
- **Qué burbujea** en los eventos que genera el motor: `click`, `submit`, `input`, `change`,
  `key*`, `mouse{down,up,over,out,move}`, `wheel`, `focusin`/`focusout`. No burbujean
  `focus`, `blur`, `mouseenter`, `mouseleave`, `scroll` ni `load`. Un evento sintético
  (`new Event`/`CustomEvent`) burbujea solo con `{bubbles:true}`.
- **Objeto evento:** `type`, `target`, `currentTarget`, `eventPhase` (1/2/3, 0 al terminar),
  `bubbles`, `cancelable`, `defaultPrevented`, `isTrusted` (true solo para los del motor),
  `timeStamp` **0** (anti-fp: sin reloj de alta resolución), `detail`, `composedPath()`,
  `stopPropagation`, `stopImmediatePropagation`, `preventDefault` (sin efecto si no es
  `cancelable`).
- **Errores:** una excepción en un listener se registra en la consola (Freebug) y el despacho
  **continúa** con el siguiente (como en todo navegador).
- `el.dispatchEvent(ev)` / `document.dispatchEvent` / `window.dispatchEvent` despachan por el
  mismo camino y devuelven `!defaultPrevented`.

Dado `<div id=main><button id=go>` **cuando** `main` escucha `click` y el usuario hace click en
`go` **entonces** el listener corre con `target === go` y `currentTarget === main`.
Dado un listener de captura en `document`, uno en `go` y uno de burbuja en `main` **entonces** el
orden es captura → destino → burbuja. Dado `stopPropagation()` en el destino **entonces** `main`
no se entera. Dado `focus` **entonces** no burbujea, pero una captura en un ancestro sí lo ve.

**Seguridad:** no cambia la superficie: el camino solo contiene nodos del documento propio,
`document` y `window`; no hay nuevos nativos (al contrario, se eliminan tres). La cota del camino
limita el costo por evento frente a un DOM hostil profundo.

## 7e. `history` real y navegación JS después de la carga (2026-09-30)

**Navegación posterior a la carga (B4a).** Una navegación que un handler, un timer o un
evento pide (`location.href=`/`assign`/`replace`/`reload`) viaja en la respuesta de TODA
operación (`OP_CLICK`/`OP_TICK`/`OP_EVENT`/`OP_MOUSE`), no solo en la de carga, y el padre la
gatea con el mismo `ln_resolve` (función compartida `gate_js_nav`). Antes se descartaba en
silencio: un botón que navega con JS no hacía nada.

**`history` (B4b).** `pushState(state, title, url)` / `replaceState` resuelven `url` con
`url_history_target` (nativo `dom.histTarget`, sin interpolar texto hostil): otro origen ⇒
`SecurityError`. Actualizan `location` en el acto, sin cargar nada, y registran la operación
(`push`/`replace` + URL absoluta) que viaja al padre en la respuesta. `history.state` devuelve
el estado de la entrada actual; `history.length` la cuenta de entradas del documento.
`back()`/`forward()`/`go(n)` registran un delta que el padre aplica con su propio historial.
Al volver a una entrada del mismo documento, el padre manda `OP_POPSTATE(índice)`: el worker
mueve su índice, actualiza `location` y despacha `popstate` (con `state`) en `window`, más
`hashchange` si solo cambió el fragmento. Cotas: `JD_HIST_MAX` 256 entradas por documento
(pasado el tope, `pushState` se comporta como `replaceState`) y el mismo tope de operaciones
por respuesta. El estado vive solo en la memoria del worker (Zero Knowledge: nunca a disco).
Volver a un documento **distinto** lo recarga (sin bfcache): su `history.state` se pierde.

**`window.open` (B4c, solo allow∩js).** Semántica **noopener**: devuelve `null`, no existe
referencia entre ventanas, así que tampoco un canal entre orígenes (`opener`/`postMessage` siguen
ausentes). El destino se **registra** (máx. 4 por operación, sin caracteres de control) y el
padre lo gatea como una navegación (`gate_js_nav`) y lo honra **solo en un gesto del usuario**
(HTML §6.4.2: `click`, `keydown`, `mousedown`/`up`, `pointerdown`/`up`, `touchend`): la carga, un
timer, `focus` o `mousemove` nunca abren ventanas. Cada destino abre una pestaña nueva. Un host
no confiable no tiene `open` (candado `test_eval_no_network_or_cross_origin_api`).

## 7f. `WebSocket` (B5, solo allow∩js, 2026-09-30)

`jd_enable_ws` instala `WebSocket` **solo** para un host allow∩js; un host no confiable no lo
tiene (candado `test_eval_no_network_or_cross_origin_api`). El worker **nunca** toca el
socket: el objeto registra operaciones (`open`/`send`/`close`) que viajan al padre en cada
respuesta, y el padre abre la conexión con `sf_ws_open` (misma política TLS/PQ/realm que un
fetch, más `hostblock`) y empuja los eventos con `OP_WS_EVENT`.

- Constructor: la URL se resuelve contra `location`; solo `wss:` (un `ws:` desde una página
  https es contenido mixto ⇒ `SecurityError`, como en Firefox). Máx. `JD_WS_MAX` 8 sockets
  por página (más ⇒ `SecurityError`).
- `send(data)`: `readyState` debe ser OPEN (si no, `InvalidStateError`). Texto como UTF-8;
  `ArrayBuffer`/vista tipada como binario. Un mensaje > 1 MiB ⇒ `SyntaxError` sin enviar.
- Eventos `open`/`message`/`error`/`close` por `addEventListener` y `on<evento>`; `message`
  entrega texto como string y binario como `ArrayBuffer` (`binaryType` se acepta pero `blob`
  no está soportado). `close` trae `code`/`reason`/`wasClean`.
- Los datos entrantes entran a JS como **valores** (`JS_NewStringLen`/`ArrayBuffer`) llamando a
  una función interna, nunca interpolados en código.
- Cotas: 64 operaciones y 4 MiB por respuesta; excederlas cierra el socket con error.
- Las conexiones pertenecen a la página: se cierran al navegar, recargar o cambiar de pestaña
  (v1: una pestaña en segundo plano pierde sus WebSocket).

## 7g. Superficie DOM Standard (`js_dom_ext`, 2026-09-30)

Medido en github.com: su JS moderno fallaba por APIs ausentes o incorrectas, no por
política. Ahora, sobre los mismos nativos sellados de `dom` (ninguna capacidad nueva):

- **Prototipos reales:** `HTML*Element → HTMLElement → Element → Node → EventTarget`,
  `HTMLDocument → Document → Node`; todo wrapper hereda de `HTMLElement.prototype` y
  `document` de `HTMLDocument.prototype`, así que `instanceof` responde como un navegador.
- **Inserción ordenada:** nativos `dom.insertBefore` (`dom_insert_before`) y `dom.cloneNode`
  (`dom_clone_node`, clona TEXTO y registra los elementos en el índice). `insertBefore`,
  `prepend` y `replaceChild` insertaban al final; ahora respetan el orden. `before`, `after`,
  `replaceWith`, `replaceChildren`, `append`/`prepend` de fragmentos.
- **`js_dom_ext`:** `getRootNode`, `isConnected`, `previousElementSibling`/`previousSibling`,
  `toggleAttribute`, `compareDocumentPosition` (orden real del árbol, no por id),
  `attachShadow` (raíz de fragmento, no se pinta; una por host), `TreeWalker` /
  `NodeIterator` sobre elementos que **siempre terminan en `null`**, `importNode`,
  `adoptNode`, `createRange` (`createContextualFragment` incluido), `elementFromPoint` →
  `null`. `<template>.content` es un `DocumentFragment` estable por plantilla.
- `document.currentScript` se construye con VALORES (el `src` de la página nunca se interpola
  en código) y es `null` mientras corre un módulo.

## 7h. Errores de Freebug en sitios reales: nodos de texto, datos binarios, interfaces (2026-09-30)

Medido recorriendo los sitios allow∩js con `--headless --js=on --dump-console`. Cada fila es
una causa raíz, no un parche por sitio.

| Causa | Síntoma medido | Arreglo |
| :-- | :-- | :-- |
| El JS no veía **nodos de texto**: `childNodes`/`firstChild`/`nextSibling` saltaban el texto y `createTextNode` devolvía un objeto plano no insertable | React no hidrataba (`#418`, crash de Next.js en DuckDuckGo: 17 errores) | Handles perezosos de texto/comentario (`spec/dom.md` §9) + wrapper `Text`/`Comment` (`__wrapChar`): `data`/`nodeValue`/`textContent` escriben al nodo real, `splitText`, `*Data`, `before`/`after`/`replaceWith`, eventos. `append('str')` crea texto. `TreeWalker`/`NodeIterator` respetan `whatToShow` (`1 << (nodeType-1)`). |
| Los listeners de `load`/`DOMContentLoaded` se llamaban **sin evento** | Bootstrap hace `Object.defineProperty(event, …)` → "not an object" (OSM) | Evento real (`target` = document, `currentTarget` = window/document), orden de ciclo de vida (readystatechange, DOMContentLoaded, load), objetos `{handleEvent}`. |
| `console.error(err)` imprimía `{}` (JSON de un Error) | Todo error reportado por un framework era ilegible | Un `Error` se imprime como `Name: message` + stack; un elemento como `<tag#id>`. |
| Faltaban `Blob`/`File`/`FileReader`/`URL.createObjectURL`/`structuredClone`/`MessageChannel`/`BroadcastChannel` | `Blob is not defined` (OSM) | Implementados en página: object URLs opacos (sin fetch de `blob:` todavía), canales asíncronos dentro del propio realm, `structuredClone` con ciclos y `DataCloneError`. |
| `insertAdjacent*` eran no-ops | Contenido que el sitio inserta no aparecía | Nativo `dom_move_children` con las cuatro posiciones; posición inválida ⇒ `SyntaxError`. |
| Los prototipos de interfaz no tenían métodos | Polyfills de Shadow DOM capturan `Node.prototype.appendChild` y obtenían `undefined` (YouTube `webcomponents-sd`) | Métodos/accesores en `EventTarget`/`Node`/`Element`/`HTMLElement.prototype` que delegan al wrapper (`Illegal invocation` si no hay nada que delegar). |
| Interfaces ausentes (`DocumentType`, `CDATASection`, `ProcessingInstruction`, `Window`, `Range`, `Selection`, …) y `window instanceof Window` falso | `ReferenceError` al arrancar Next.js, `CDATASection.prototype` en webcomponents | Constructores con cadena de prototipos real; el global hereda de `Window.prototype`. `Image` sigue indefinido (candado SOP). |
| `<canvas>.getContext` inexistente; API 2D incompleta | web-animations / feature tests | `getContext('2d')` (contexto software, ≤ 1 Mpx), `'webgl'` ⇒ `null`; resto de la API 2D inerte; `measureText` determinista (anti-fp). |
| `Intl` mínimo | formatjs llama `supportedLocalesOf`/`Locale`/`Segmenter` al arrancar | Superficie completa con identidad neutra `en-US`. |
| `fetch` de confianza sin `Request`/`Response` | `Request is not defined` (Reddit) | Clases del Fetch Standard sobre la MISMA llamada gateada; señal abortada ⇒ `AbortError` sin tocar la red. |
| `isEqualNode`/`isSameNode` | `updateHead` de Next.js | Igualdad estructural (atributos sin orden, texto incluido). |
| Un módulo `data:` > 8 KiB se truncaba a su nombre | `SyntaxError` en el módulo de Reddit | El cuerpo sale del atributo; el nombre se acorta a uno sintético solo si no cabe. |

**Resultado** (errores en consola, antes → después): duckduckgo 9 → 1, openstreetmap 5 → 3,
youtube 2 → 0, animate.style 1 → 0, andreagrandi 1 → 0, old.reddit 3 → 0, facebook 47 avisos → 0;
github 1 (sin cambio, `behaviors-*.js:0:0` sin ubicación). Lo que queda: la hidratación de
DuckDuckGo (`#418`, React se recupera renderizando del lado cliente), `Worker` (OSM/MapLibre,
que además exige WebGL) y el `TypeError` sin ubicación de github.

## 7i. `Worker` dedicado (plan B6b, solo allow∩js, 2026-09-30)

`new Worker(url)` corre el script en un **realm propio** (`spec/js_sandbox.md` §7c): su global es
`self` (sin `window` ni `document`, como un `DedicatedWorkerGlobalScope`), con `postMessage`,
`onmessage`/`addEventListener('message')`, `close`, `importScripts`, temporizadores, `console`,
`location`/`navigator` de solo lectura y las APIs de datos de la página (`TextEncoder`/`Decoder`,
`Blob`, `URL`, `atob`/`btoa`, `structuredClone`, `fetch` cuando la página es de confianza).

- **Origen del código:** `blob:` (un object URL de la propia página), `data:` y, solo en página
  de confianza, una URL https por la MISMA llamada gateada del padre (XHR síncrono). Cualquier
  otra cosa ⇒ evento `error` asíncrono en el `Worker` (como en un navegador), nunca una excepción
  que mate al llamante.
- **Mensajes:** asíncronos en ambas direcciones (tarea de temporizador, nunca en línea), clonados
  con `__realmClone` (los objetos llegan al realm del receptor). Un error no capturado en el
  worker dispara `error` en el objeto `Worker` con `message`/`filename`.
- `terminate()` y `self.close()` cortan la entrega en las dos direcciones.
- `type: 'module'` ⇒ evento `error` (fuera de alcance por ahora).
- **Por qué solo allow∩js:** un worker no abre red, pero multiplica la superficie del motor JS;
  sigue la misma frontera de confianza que el resto del runtime de apps (§7d–7h). Para un host no
  confiable `typeof Worker === 'undefined'`, como hoy.

## 7j. `style` write-through + `getComputedStyle` inline + observadores sintéticos (2026-10-09)

Motivo medido: `el.style` era un objeto plano desconectado del DOM — `el.style.color='red'`
no tocaba el atributo `style`, así que el siguiente `pv_build_styled` no lo veía y el
repaint por `OP_TICK`/`OP_EVENT` nunca reflejaba mutaciones de estilo desde JS.
`getComputedStyle` devolvía `''` siempre, lo que quiebra CSS-in-JS que lee el token que
acaba de escribir. `ResizeObserver`/`MutationObserver` nunca disparaban, así que
reveal-on-scroll dependiente de resize quedaba oculto.

- **`style` write-through:** `el.style` lee/escribe el atributo `style` real vía
  `dom.getAttribute`/`dom.setAttribute`. `setProperty(k,v)` / asignación directa
  (`el.style.color='red'`) / `cssText=` actualizan el atributo serializado;
  `getPropertyValue(k)` / lectura directa / `cssText` leen del atributo parseado.
  Conversión camelCase↔kebab-case (`backgroundColor`↔`background-color`).
  Dado `el.style.color='red'` cuando se relee `el.getAttribute('style')`
  entonces contiene `color: red`. Dado `el.setAttribute('style','color: blue')`
  cuando se lee `el.style.color` entonces es `'blue'`.
- **`getComputedStyle(el)` inline (v1):** lee el atributo `style` del elemento y
  devuelve sus declaraciones (kebab y camel). Sin `style` o prop ausente ⇒ `''`.
  `getPropertyValue`/`getPropertyPriority`/`length`/`item()` preservados.
  No resuelve hoja externa (v2); no filtra geometría (solo strings del autor).
  Dado `<div style="color: red; display: none">` cuando `getComputedStyle(div).color`
  entonces `'red'`; y `getPropertyValue('display')` es `'none'`.
- **`ResizeObserver` sintético:** `observe()` encola vía `setTimeout(...,0)` UNA
  entrega `[{target, contentRect: rect 0, borderBoxSize:[{inlineSize:0,blockSize:0}]}]`.
  `disconnect()` suprime; `unobserve()` no-op v1; `takeRecords()` ⇒ `[]`.
  Valores sintéticos constantes, cero geometría real (igual que `IntersectionObserver`).
- **`MutationObserver` sintético (v1):** `observe()` encola UNA entrega vacía
  `[]` vía `setTimeout(...,0)` (desbloquea `await` de librerías, sin records reales).
  `disconnect()` suprime; `takeRecords()` ⇒ `[]`. Records reales fuera de alcance.
- **Seguridad:** solo atributo `style` del propio elemento (misma capacidad que
  `setAttribute`, ya sellada). Sin red, sin geometría real, sin reloj. Presupuesto
  de tiempo del intérprete acota loops.

## 7k. Shadow visible v1: `attachShadow` espeja a light DOM (2026-10-09)

Motivo medido: `attachShadow` devolvía un fragmento JS (`SH[h]`) cuyos hijos son nodos
detached — `pv_build` camina el árbol Lexbor desde `<body>` y nunca los visita, así que
todo contenido shadow (YouTube `webcomponents-sd`, custom elements) quedaba invisible.
Encapsulación real (shadow Oculta light sin slot, proyección en `<slot>`) fuera de alcance.

- **Espejo:** cada mutación del shadow root (`appendChild`/`insertBefore`/`append`/
  `prepend`/`innerHTML=`/`textContent=`) además hace `dom.appendChild/insertBefore/
  setInnerHtml` equivalente sobre el host, así el siguiente `pv_build_styled`
  (vía `OP_TICK`/`OP_EVENT`) lo pinta como light. `innerHTML=` parsea en un `div`
  scratch y mueve hijos (no reemplaza light: append, fail-visible).
  Dado `host.attachShadow({mode:'open'})` + `sr.appendChild(el)` cuando se relee
  `host.firstChild` entonces es `el` (además de `sr.firstChild`).
- **`<slot>` transparente:** `<slot>` vacío no genera caja ni texto (ya es unknown
  inline sin hijos); light ya se emite en su posición original. Sin distribución real.
- **Seguridad:** misma capacidad que `appendChild`/`setInnerHtml` (ya selladas, mismo
  documento). Sin red, sin cross-tree. Cota de moves por op (100k, como `replaceChildren`).

## 8. Fuera de alcance

- Eventos **interactivos** más allá del click (keydown/mousemove/submit; el click del
  usuario → handler → re-render ya funciona vía el dispatcher).
- Navegación con anclas de fragmento (`#id`).
- (Cerrados 2026-07-11, ver §3: timers asíncronos reales vía `OP_TICK` y el getter de
  `innerHTML` — ya **no** están fuera de alcance.)
- Selectores CSS **completos**: `querySelector` cubre el subconjunto de `css_select`
  (tipo/`.clase`/`#id`/`*`/`[attr]` + combinadores + pseudo-clases estructurales/`:link`); quedan
  fuera `:not()`/`:is()`/`:where()`/`:has()`, of-type y pseudo-elementos `::` (fail closed).
