# Especificación: `ui`

> Hito 4 — Interfaz gráfica (Cairo + Wayland). Estado: **núcleo puro VERDE (9 tests +
> ASan/UBSan limpio); orquestador Wayland+Cairo compila limpio (`make view`), prueba visual del
> usuario**.
> Metodología: SDD + TDD. La lógica verificable vive en funciones puras
> (`tests/test_ui.c`); el orquestador con I/O (Wayland/Cairo) solo cablea y lo prueba el usuario
> sobre un display real.

## 1. Propósito

`ui` dibuja contenido en una ventana **Wayland** con **Cairo**. Primera entrega: un **visor de
texto desplazable** que renderiza el título y el texto extraído de un documento ya parseado
(`html_parse`/`dom`). Es la base sobre la que crecerá el render de layout (cajas, estilos) en
hitos posteriores.

**Doctrina:** solo Wayland, **nunca X11** (X11 permite keylogging entre ventanas). Sin telemetría
ni dependencias ocultas: `wayland-client`, `cairo`, y el protocolo `xdg-shell` generado con
`wayland-scanner` desde `wayland-protocols`.

## 2. Separación verificable / orquestador

Siguiendo la doctrina del proyecto, la lógica está en **funciones puras sin I/O** y el código
con SO/display solo cablea:

- **Núcleo puro (testeable aquí, `src/ui_layout.c`):** ajuste de línea (word-wrap) en un modelo
  **monoespaciado por columnas** y recorte de scroll. No toca Wayland ni Cairo.
- **Orquestador (`gui/ui_render.c`, prueba visual):** conexión Wayland, `xdg-shell`, buffer
  `wl_shm`, superficie Cairo sobre ese buffer, pintado de las líneas visibles, scroll por rueda,
  redimensionado y cierre. No se puede ejercitar headless; lo prueba el usuario con
  `make view FILE=pagina.html`.

El modelo monoespaciado mantiene el núcleo puro (las columnas no dependen de métricas de fuente);
el orquestador usa una fuente monospace de Cairo, de modo que `max_cols = ancho_px / ancho_celda`
es coherente con el ajuste. El layout de fuentes proporcionales queda para más adelante.

## 3. Contrato de la API

Definida en `include/ui.h`.

```c
typedef enum ui_status {
    UI_OK = 0,
    UI_ERR_NULL_ARG,
    UI_ERR_OOM,
    UI_ERR_DISPLAY,   /* no se pudo conectar al display Wayland */
    UI_ERR_INTERNAL
} ui_status;

/* Una linea = un trozo contiguo [offset, offset+len) del texto original. */
typedef struct ui_line { size_t offset; size_t len; } ui_line;
typedef struct ui_layout { ui_line *lines; size_t count; size_t cap; } ui_layout;

/* --- Nucleo puro (sin I/O): superficie de prueba. --- */
ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out);
void      ui_layout_free(ui_layout *lay);
size_t    ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines);

/* --- Orquestador (I/O, prueba visual). --- */
ui_status ui_run_text_view(const char *title, const char *text, size_t text_len);
```

## 4. Semántica del núcleo puro

- `ui_wrap_text`: divide `text` en líneas de a lo sumo `max_cols` columnas.
  - `max_cols == 0` se trata como `1` (defensivo; sin bucles infinitos).
  - `'\n'` fuerza un salto de línea.
  - Corte preferente en el último espacio que quepa; el espacio de corte se consume (no aparece
    al inicio de la línea siguiente).
  - Una palabra más larga que `max_cols` se parte de forma dura, **siempre en un límite de
    carácter UTF-8** (una columna = un carácter): nunca se parte una secuencia multibyte a la
    mitad, porque una secuencia partida es UTF-8 inválido y el renderer de texto lo rechaza.
    Cada columna cuenta como 1 carácter, así que una línea de `max_cols` columnas ocupa hasta
    `4·max_cols` bytes (el orquestador dimensiona su buffer de línea en consecuencia).
  - `len == 0` ⇒ `count == 0`.
  - Cada `ui_line` es un slice contiguo del texto original (sin copiar): el llamante usa
    `text + offset` con `len`.
  - `out` en propiedad del llamante; liberar con `ui_layout_free` (idempotente, `NULL`-safe).
- `ui_clamp_scroll`: devuelve `desired` recortado a `[0, max(0, total_lines - viewport_lines)]`.
  Si `viewport_lines >= total_lines` ⇒ `0`.

## 5. Tabla de errores

| Código | Condición |
| :-- | :-- |
| `UI_OK` | Operación correcta. |
| `UI_ERR_NULL_ARG` | `text == NULL` u `out == NULL`. |
| `UI_ERR_OOM` | Fallo de asignación del layout. |
| `UI_ERR_DISPLAY` | `ui_run_text_view`: sin `WAYLAND_DISPLAY` o conexión rechazada. |
| `UI_ERR_INTERNAL` | Fallo inesperado del orquestador (registry/shm/surface). |

## 6. Garantías

1. **Solo Wayland.** No se enlaza ni se usa X11. El transporte es el socket Wayland del usuario.
2. **Sin red ni telemetría.** El visor solo dibuja el contenido que se le pasa.
3. **Núcleo robusto.** `ui_wrap_text` con entrada arbitraria no entra en bucle ni desborda;
   `max_cols==0` saneado. Memoria con dueño único; `ui_layout_free` idempotente. Objetivo:
   ASan/UBSan limpios en las pruebas del núcleo.
4. **Fallar cerrado en el display:** sin Wayland disponible, `ui_run_text_view` devuelve
   `UI_ERR_DISPLAY` sin abrir nada.

## 7. Matriz de pruebas

`tests/test_ui.c` (cmocka, solo núcleo puro):
- Vacío ⇒ 0 líneas; `NULL` ⇒ `UI_ERR_NULL_ARG`.
- Texto corto ⇒ 1 línea con el slice correcto.
- Ajuste por espacio en `max_cols`.
- Palabra más larga que `max_cols` ⇒ corte duro.
- `'\n'` ⇒ salto forzado.
- `max_cols == 0` saneado (sin colgarse), produce líneas de 1 columna.
- `ui_clamp_scroll`: por debajo, por encima, y viewport ≥ total.
- `ui_layout_free(NULL)` y doble liberación.

**Prueba visual (usuario):** `make view FILE=pagina.html` abre la ventana, renderiza el texto,
permite scroll con la rueda y cierra con el botón de la ventana.

## 8. Fuera de alcance

- Layout de cajas/estilos CSS y fuentes proporcionales (render real, hitos posteriores).
- Entrada de teclado / foco / IME (xkbcommon): v1 usa rueda + cierre.
- Pestañas, barra de direcciones, navegación (UI de navegador completa).
- Aceleración GPU (`wayland-egl`/Vulkan).
