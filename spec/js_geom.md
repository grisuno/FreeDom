# js_geom — geometría real de layout para el JS de un host de confianza

> Estado: SDD (2026-09-30). Módulo puro `js_geom` (`jg_`), sin I/O, sin estado global.
> Consumidores: `gui/browser_ui.c` (produce), `src/tab.c` (transporta, `OP_GEOM`),
> `src/js_dom.c` (expone a JS). Hito B3 del plan "Firefox para allow∩js".

## 1. Propósito

Hasta ahora `getBoundingClientRect`, `offset*`, `client*` y `scroll*` devolvían **cero** en
toda página: el worker que ejecuta el JS no maqueta (lo hace el padre, que es quien pinta), y
cero era además la respuesta anti-fingerprinting (la geometría revela métricas de fuente y
tamaño de ventana). Un menú desplegable, un carrusel, un scroll infinito, un tooltip o un
editor miden elementos; con ceros, fallan o se dibujan en (0,0).

La geometría es **información de identidad**, así que se entrega **solo a un host
allow∩js** (decisión del dueño 2026-09-30: el usuario acepta la exposición). Todo otro host
sigue viendo ceros: la tabla nunca se le envía.

## 2. Modelo

- El padre, tras cada layout de `paint_structured`, recorre el layout **final** y registra,
  por elemento, el rectángulo en **coordenadas de documento** (px CSS, origen = esquina
  superior izquierda del documento): cada fragmento de texto (su `node_id`) y cada caja
  pintada (su `pv_box_def.node_id`, campo nuevo que cruza el códec IPC).
- `jg_finish` ordena por nodo y **une** los rects de un mismo nodo (caja envolvente).
- En el worker, `jg_aggregate` propaga cada rect a **todos sus ancestros** (vía `dom_parent`),
  porque la caja de un elemento contiene a la de sus descendientes aunque él no genere
  ninguna caja propia (un `<div>` sin decoración). Acotado a `JG_MAX_DEPTH` 4096 niveles.
- La cabecera lleva `scroll_x/scroll_y`, `view_w/view_h` (viewport real) y `doc_w/doc_h`
  (tamaño del documento).

**Temporalidad (honesta):** los scripts de carga corren **antes** del primer layout y siguen
viendo ceros; la geometría existe desde el primer pintado, así que un listener, un timer o un
`rAF` posterior la ven real. No hay layout síncrono forzado (fuera de alcance, §7).

**Headless (`--js=on`, confianza del operador):** como un navegador maqueta antes de que
disparen los timers, el export headless maqueta **una vez tras la carga y antes de bombear
los timers** (`ui_page_geometry`, mismo layout que `ui_render_png`: ancho `FC_PNG_PAGE_W`,
viewport `FC_HEADLESS_VIEW_H` 768, scroll 0) y entrega la tabla. Un `setTimeout` que mide un
`<div style="width:300px;height:80px">` obtiene 300×80, igual que Firefox.
`tab_set_geometry` no envía nada si la carga no tuvo `net` (sin `--js=on`).

## 3. API (C)

```c
#define JG_MAX_RECTS  65536   /* rects por tabla (cota anti-DoS de memoria/IPC) */
#define JG_MAX_DEPTH   4096   /* ancestros recorridos por rect en jg_aggregate */
#define JG_COORD_MAX  (1<<24) /* |coordenada| y tamaño máximos en px */
#define JG_HEADER_N       6   /* scroll_x, scroll_y, view_w, view_h, doc_w, doc_h */

typedef struct jg_rect  { dom_node_id node; int32_t x, y, w, h; } jg_rect;
typedef struct jg_table { jg_rect *r; size_t n, cap;
                          int32_t scroll_x, scroll_y, view_w, view_h, doc_w, doc_h; } jg_table;

void  jg_init(jg_table *t);
void  jg_free(jg_table *t);                       /* idempotente */
int   jg_add(jg_table *t, dom_node_id node, double x, double y, double w, double h);
int   jg_finish(jg_table *t);                     /* ordena + une por nodo */
const jg_rect *jg_find(const jg_table *t, dom_node_id node);   /* requiere finish */
int   jg_aggregate(jg_table *t, dom_node_id (*parent)(void *, dom_node_id), void *ctx);
size_t jg_wire_len(const jg_table *t);            /* int32 en el cable */
int   jg_encode(const jg_table *t, int32_t *out, size_t cap);
int   jg_decode(const int32_t *in, size_t n, jg_table *out);
uint64_t jg_hash(const jg_table *t);              /* detección de cambios (FNV-1a) */
```

Todas devuelven 0 en éxito y -1 en error. `jg_add` descarta en silencio (devuelve 0) un
`node == DOM_NODE_NONE` o una coordenada no finita, y **recorta** a `±JG_COORD_MAX`; un
ancho/alto negativo se vuelve 0. Pasado `JG_MAX_RECTS` devuelve -1 (la tabla queda válida
con lo que tenía).

## 4. Tabla de errores

| Condición | Resultado |
| :-- | :-- |
| `t == NULL` / `out == NULL` | -1 |
| nodo `DOM_NODE_NONE`, coordenada NaN/Inf | ignorado, 0 |
| tabla llena (`JG_MAX_RECTS`) | -1, contenido previo intacto |
| `jg_decode` con `n < JG_HEADER_N+1`, cuenta que no cierra con `n`, cuenta > `JG_MAX_RECTS`, o valores fuera de rango | -1, `out` vacío |
| `jg_aggregate` con un ciclo en `parent` | se corta a `JG_MAX_DEPTH`; nunca bucle infinito |

## 5. Contrato de exposición a JS (`js_dom`)

Con tabla instalada (`jd_set_geometry`):
- `el.getBoundingClientRect()` = rect del documento − scroll; `{x,y,left,top,right,bottom,
  width,height}` + `toJSON`. `getClientRects()` = `[ese rect]`.
- `offsetWidth/Height` = ancho/alto; `offsetLeft/Top` = coordenadas de documento;
  `clientWidth/Height` y `scrollWidth/Height` = ancho/alto de la caja (sin descontar bordes
  ni scrollbar: aproximación documentada).
- `document.documentElement.clientWidth/Height` = viewport; `scrollHeight/Width` y los de
  `body` = tamaño del documento; `scrollTop` = `scroll_y`.
- `window.innerWidth/innerHeight`, `scrollX/scrollY/pageXOffset/pageYOffset` = reales.
- Un elemento que no está en la tabla (oculto, `display:none`) da ceros, como en Firefox.

Sin tabla: todo exactamente como antes (ceros y viewport normalizado 1920×1080).

## 6. Garantías de seguridad

- **Gate doble:** el padre solo envía `OP_GEOM` si el host es allow∩js, y el worker solo lo
  acepta si su última carga tuvo `net` concedido (el mismo bit de confianza). Fallar cerrado.
- El decodificador valida cabecera, cuenta y rangos antes de tocar memoria; la cuenta está
  acotada por `JG_MAX_RECTS` y la longitud del cable por `TAB_MAX_INPUT`.
- `jg_aggregate` no confía en que `parent` sea acíclico.
- Sin nuevas capacidades de red ni de escritura: solo lectura de números.

## 7. Fuera de alcance

- Layout síncrono forzado (leer `offsetHeight` tras mutar el DOM devuelve el valor del
  último pintado, no el nuevo).
- Bordes/padding/scrollbar en `client*`; `getComputedStyle` real; `elementFromPoint`;
  `ResizeObserver`/`IntersectionObserver` reales (siguen sintéticos).
- Geometría de contenido dentro de cajas `position:absolute|fixed` (solo la caja misma).

## 8. Dado-Cuando-Entonces

- Dado un host allow∩js con un `<div id=a>` de 200×50 en y=100 **cuando** un listener de
  click llama `a.getBoundingClientRect()` con scroll 40 **entonces** obtiene
  `{top:60,height:50,width:200}`.
- Dado un host **no** confiable **cuando** la misma página mide **entonces** obtiene ceros.
- Dado un `<div>` sin caja propia que envuelve dos párrafos **entonces** su rect es la unión
  de ambos.
- Dado un buffer de cable truncado o con cuenta gigante **entonces** `jg_decode` falla
  cerrado.
