# anchor (`anc_`) — navegar a un fragmento (`#id`) y `scroll-behavior`

> Estado: cerrado (2026-11-23, tandas 103–104). Módulo puro `anchor` (`anc_`), sin I/O ni estado global.
> Consumidores: `src/tab.c` (worker, `OP_ANCHOR`), `gui/browser_ui.c` (ventana).

## 1. Por qué

Hasta la tanda 102 un enlace `href="#historia"` no hacía **nada**: `follow_link` descartaba
`ln_result.fragment` ("para un scroll futuro"), y abrir `https://x/p#seccion` mostraba el
principio de la página. El índice de cada artículo de Wikipedia, las notas al pie y todo
"volver arriba" estaban muertos. `scroll-behavior: smooth` (que el parser ya leía) no tenía
nada que animar.

## 2. Modelo (HTML §7.4.6.4 «indicated part», CSSOM View §7)

1. **Resolver** (worker, tiene el DOM): `anc_resolve(idx, fragment)`:
   - `fragment == ""` ⇒ `ANC_TOP` (principio del documento).
   - elemento **conectado** con `id == fragment` (el primero en orden de árbol) ⇒ `ANC_ELEMENT`;
   - si no, el primer `<a>` conectado con `name == fragment`;
   - si no, lo mismo con el fragmento **decodificado** (`%XX` → byte, `anc_percent_decode`);
   - si no, y el decodificado es `top` sin distinguir mayúsculas ⇒ `ANC_TOP`;
   - si no ⇒ `ANC_NONE` (no se desplaza; la URL y el historial cambian igual, como Firefox).
2. **Recolectar** (worker): `anc_collect(idx, target, out, cap, &nsub)` escribe el destino y su
   subárbol en preorden (`nsub` handles) y, a continuación, los elementos que lo **siguen** en
   orden de árbol, hasta `cap` (≤ `ANC_MAX_HANDLES`). Un destino vacío (`<a name=x></a>`,
   `<span id=x></span>`) no pinta nada: su posición es la del primer contenido que lo sigue.
3. **Ubicar** (ventana, tiene el layout): `anc_target_top(g, h, n, nsub, &top)` sobre la tabla
   de geometría del layout ya retenido (`geom_from_layout`, la MISMA que recibe el JS): el
   mínimo `y` de los rects del subárbol; si el subárbol no pintó nada, el `y` del primer elemento
   posterior que sí. `anc_scroll_for(top, max)` acota a `[0, max]` (alinear el borde superior al
   tope del viewport, `scrollIntoView` `block:start`).
4. **Animar**: si el `scroll-behavior` **computado del elemento raíz** (`<html>`; el de `<body>`
   NO se propaga, CSSOM View §12.1) es `smooth`, el salto se anima con `smooth_scroll`
   (`FC_SMOOTH_SCROLL_ANCHOR_MS`); si no, es instantáneo. `FREEDOM_SMOOTH_SCROLL=0` lo apaga.

## 3. Historial

- Un clic en un fragmento del MISMO documento (mismo URL sin fragmento, o `href="#…"`) es una
  navegación de mismo documento: `browser_push_state` con la URL nueva y sin carga, y se guarda
  el scroll de la entrada que se deja (`browser_set_entry_scroll`). Atrás/Adelante entre
  entradas del mismo documento **restauran el scroll guardado** sin recargar, también con JS
  apagado (antes: recarga completa).
- Mismo fragmento que el actual: se vuelve a desplazar, sin entrada nueva (HTML: *replace*).
- Página con JS: el worker registra la entrada en su `history` (`__histFrag`: actualiza
  `location`, empuja la entrada, despacha `hashchange` con `oldURL`/`newURL`), así los índices de
  `tab_popstate` siguen alineados con los del padre, y responde con la vista re-derivada
  (los oyentes de `hashchange` pueden mutar el DOM).
- Cargar una URL con fragmento: tras el primer layout del documento se desplaza al destino
  (instantáneo: la página aún no se ha visto). Si la ventana aún no tiene superficie (URL de la
  línea de órdenes), se hace en el primer cuadro (`frag_pending`).
- **«Try to scroll to the fragment»** (HTML §7.4.6.4): mientras el documento recién llegado se
  asienta (`FC_ANCHOR_HOLD_MS`, 6 s) y el usuario NO se ha desplazado, un cambio del alto del
  documento (imágenes tardías, scripts) re-aplica el fragmento. Medido en es.wikipedia
  (`/wiki/GNU/Linux#Etimolog%C3%ADa`): sin esto el título quedaba ~70 px por debajo del tope.
- **Clic cancelado**: un oyente que llama `preventDefault()` en el clic de un enlace impide
  seguirlo (`tab_page.default_prevented`): sin eso cada botón `<a href="#">` de una página con JS
  saltaría al principio y añadiría una entrada.
- **Páginas locales**: la `location` de un `file://` se descompone (`url_split_location`,
  origen `null`), y el fragmento viaja al worker RELATIVO (`#x`): la entrada del historial de una
  página local es la ruta llana, su `location` es `file://`. Atrás/Adelante re-resuelven la URL
  absoluta guardada (`url_history_target` acepta la del mismo archivo).

## 3b. Fragmento pedido por un script (tanda 104)

`location.hash = "x"`, `location.href = "#x"`, `location.assign(".../misma-página#x")` y
`location.replace("#x")` son navegaciones de MISMO documento (HTML §7.4.2.3.3 *navigate to a
fragment*), nunca una recarga:

- **Worker** (shim de `location`): si la URL pedida tiene `#` y su parte sin fragmento es la del
  documento, `location` cambia EN EL ACTO (un `location.hash` leído justo después ya es el nuevo),
  se recuerda el `href` anterior para el `hashchange` y la petición viaja RELATIVA (`#x`): así
  `ln_resolve` la clasifica `LN_SAME_DOCUMENT` también en una página local (`file://`) o tras un
  `pushState`, sin depender de que el padre conozca la URL actual del documento. El setter de
  `hash` quita el `#` inicial y, si el fragmento es el actual, no hace nada (WHATWG `hash` setter).
- **Padre** (`gate_js_nav`, Zero Trust): `ln_resolve` sigue siendo el único juez. Una petición con
  `#` produce `tab_page.nav_fragment` (el fragmento, dato); si además es `LN_NAVIGATE`, `nav_url`
  lleva el fragmento (`target#frag`) para que la carga de OTRO documento abra en su ancla.
- **Ventana**: el fragmento es de este documento si `nav_url` es NULL (referencia `#x`) o su URL
  sin fragmento es la de la entrada actual o la de la página (`cur_top`). Entonces se aplica la
  vista que trajo la respuesta y se llama a `navigate_fragment` (entrada nueva, o *replace* con
  `location.replace` y durante la carga —el documento aún no está *completely loaded*—), que le
  pide al worker resolver/ubicar el destino y despachar `hashchange` con el `oldURL` recordado.
  Un oyente de `hashchange` que vuelve a cambiar el hash re-entra acotado por
  `FC_JS_FRAGMENT_DEPTH`; más allá se ignora (igual que `JS_NAV_MAX` para redirecciones).
- Lo que no es mismo documento (otra ruta, otro host) sigue por `do_load` con TODA la política.

## 3c. `:target` (tanda 104)

Tras resolver un fragmento (clic, script, carga con `#x`, Atrás/Adelante entre fragmentos) el
worker fija el destino del documento (`cch_set_target`: el puntero vive en el `user` del
`lxb_dom_document_t`, por documento, sin estado global) y `fill_css_node` le pone el bit
`CSEL_STATE_TARGET`: `:target` es un pseudo de ESTADO más, como `:hover`. Si el destino cambió,
la respuesta a `OP_ANCHOR` trae la vista re-derivada también para una página SIN JS. `ANC_TOP` y
`ANC_NONE` dejan el documento sin destino (`:target` no coincide con nada), como Firefox. Un
elemento quitado del árbol solo se compara por puntero (los mutadores DETACHAN, nunca liberan).

## 3d. Volver a OTRO documento (tanda 104)

Toda navegación nueva desde la ventana (`gui_navigate`: enlace, omnibox, formulario, redirección
de JS) guarda en la entrada que se deja su scroll (`browser_set_entry_scroll`). Atrás/Adelante a
una entrada de otro documento recarga y, cuando el documento llega, restaura ese scroll acotado
al máximo (`restore_pending`), por encima de su fragmento (como Firefox), y lo **sostiene** igual
que un fragmento (§3, `FC_ANCHOR_HOLD_MS`) mientras el alto crece y el usuario no se mueva. Una
navegación nueva descarta la restauración pendiente. El scroll vive solo en RAM, en la entrada
del historial (Zero Knowledge: nada a disco).

## 4. API (C)

```c
#define ANC_MAX_FRAGMENT  256u   /* = LN_MAX_FRAGMENT, bytes con NUL */
#define ANC_MAX_HANDLES  4096u   /* handles por respuesta (cota anti-DoS del IPC) */
typedef enum { ANC_NONE = 0, ANC_TOP = 1, ANC_ELEMENT = 2 } anc_kind;

size_t   anc_percent_decode(const char *in, char *out, size_t cap);
anc_kind anc_resolve(const dom_index *idx, const char *fragment, dom_node_id *out);
size_t   anc_collect(const dom_index *idx, dom_node_id target, dom_node_id *out,
                     size_t cap, size_t *nsub);
int      anc_target_top(const jg_table *g, const dom_node_id *h, size_t n, size_t nsub,
                        double *top);
double   anc_scroll_for(double top, double max_scroll);
```

## 5. Tabla de errores

| Condición | Resultado |
| :-- | :-- |
| `anc_percent_decode`: `in`/`out` NULL, `cap == 0`, no cabe | `(size_t)-1`, `out` = `""` si `cap > 0` |
| `%` sin dos hex detrás | se copia literal (URL §1.3 percent-decode) |
| `anc_resolve`: `idx`/`fragment` NULL | `ANC_NONE` |
| fragmento ≥ `ANC_MAX_FRAGMENT` | `ANC_NONE` (nunca se trunca a un id parcial) |
| decodificado con NUL incrustado (`%00`) | esa rama no encuentra nada |
| `anc_collect`: NULL, `cap == 0`, destino inválido | 0, `*nsub = 0` |
| `anc_target_top`: sin ningún rect | -1, `*top` sin tocar |
| `anc_scroll_for`: `top`/`max` no finitos o `max < 0` | 0 |
| `OP_ANCHOR` con longitud > `ANC_MAX_FRAGMENT` o n > `ANC_MAX_HANDLES` en la respuesta | desync ⇒ worker muerto / `TAB_ERR_IO` (fail closed) |

## 6. Garantías

- Puro y acotado: `anc_collect` hace a lo sumo `cap` pasos de avance más una subida por paso
  acotada por la profundidad del árbol; nada de recursión.
- El fragmento es **dato**: se compara, nunca se interpola en un selector ni en JS
  (`__histFrag` recibe la URL ya resuelta por `dom.histTarget`, mismo origen o nada).
- Un elemento quitado por un script no es destino (`dom_is_connected`).
- El padre no confía en los handles: solo se usan como clave de búsqueda en SU tabla de
  geometría; un handle inventado simplemente no se encuentra.

## 7. Dado-Cuando-Entonces

- **Dado** `<h2 id="b">B</h2>` a 3000 px, **cuando** clic en `<a href="#b">`, **entonces** la
  página queda con el `<h2>` en el tope del viewport y la URL termina en `#b`; **Atrás** vuelve
  al scroll anterior sin recargar.
- **Dado** `<a name="n"></a><p>texto</p>`, **cuando** se navega a `#n`, **entonces** el tope es
  el del `<p>`.
- **Dado** `id="caf%C3%A9"` no existe y `id="café"` sí, **cuando** `#caf%C3%A9`, **entonces**
  destino `café`.
- **Dado** `#top` sin elemento `top`, **entonces** `ANC_TOP`; con `id="top"`, ese elemento.
- **Dado** `html{scroll-behavior:smooth}`, **cuando** se sigue un ancla, **entonces** la posición
  avanza en varios cuadros; con `body{scroll-behavior:smooth}` solo, el salto es instantáneo.

## 8. Fuera de alcance (abierto)

Contenedores `overflow:auto` internos que contienen el destino; `:target-within`; `scroll-snap-*`.
`scrollIntoView`/`scrollTo` y `scroll-margin`/`scroll-padding` viven en `spec/scroll_req.md`.
