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

## 8. Fuera de alcance

- Eventos **interactivos** más allá del click (keydown/mousemove/submit; el click del
  usuario → handler → re-render ya funciona vía el dispatcher).
- Navegación con anclas de fragmento (`#id`).
- (Cerrados 2026-07-11, ver §3: timers asíncronos reales vía `OP_TICK` y el getter de
  `innerHTML` — ya **no** están fuera de alcance.)
- Selectores CSS **completos**: `querySelector` cubre el subconjunto de `css_select`
  (tipo/`.clase`/`#id`/`*`/`[attr]` + combinadores + pseudo-clases estructurales/`:link`); quedan
  fuera `:not()`/`:is()`/`:where()`/`:has()`, of-type y pseudo-elementos `::` (fail closed).
