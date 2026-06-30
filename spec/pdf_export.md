# spec/pdf_export.md — Helpers puros para "Guardar página como PDF vectorial"

> Módulo `pdf_export` (prefijo `pe_`). Lógica **pura, sin I/O, sin estado global**: a partir del
> título de la página (dato hostil) y el directorio de salida (de confianza), decide **dónde** y con
> **qué nombre** se escribe el PDF (falla cerrado), y reparte las filas del documento en páginas sin
> partir ninguna. No abre archivos ni dibuja píxeles: eso lo hace el orquestador de la GUI con Cairo.
> Metodología: SDD + TDD.

## 0. Por qué existe

Cairo puede redirigir su salida de la pantalla a un `cairo_pdf_surface_t` con una línea: re-dibuja la
display list (la misma de `render_doc`) en un PDF **vectorial**, con texto seleccionable, buscable y
zoom infinito — no una foto de la pantalla. Eso es capacidad nativa del navegador sin extensiones.

Pero "exportar a PDF" toca dos decisiones que **no** deben vivir mezcladas con el código de Cairo,
porque son la superficie auditable:

1. **El nombre de archivo se deriva del título de la página, que es contenido remoto hostil.** Un
   título como `../../.bashrc`, `/etc/passwd`, con bytes de control o NUL **no debe** poder escapar
   del directorio de salida ni nombrar un archivo arbitrario. Esto es Secure by Default / falla
   cerrado, igual que el resto de la doctrina: la configuración insegura no es representable.
2. **La paginación** (repartir filas de altura conocida en páginas de altura fija sin cortar una
   fila) es matemática determinista, testeable sin Cairo.

Ambas son funciones puras: misma entrada → misma salida, sin red ni FS. El orquestador (la GUI) solo
cablea: resuelve el directorio (XDG/`$HOME`), llama a `pe_build_path`, crea el surface PDF, corre el
layout y pinta página por página según `pe_paginate`.

## 1. Constantes y tipos

```c
#define PE_NAME_MAX       128u    /* máx. bytes del basename saneado (sin la extensión) */
#define PE_EXT            ".pdf"
#define PE_EXT_PNG        ".png"  /* export raster (revisión visual): ui_render_png */
#define PE_FALLBACK_NAME  "page"  /* nombre por defecto cuando el título no da nada usable */

typedef enum pe_status {
    PE_OK = 0,
    PE_ERR_NULL_ARG,  /* puntero requerido NULL / outsz == 0 */
    PE_ERR_OVERFLOW   /* el resultado no cabe; out queda vacío (falla cerrado) */
} pe_status;
```

## 2. API (pura, reentrante)

```c
pe_status pe_safe_basename(const char *title, char *out, size_t outsz);
pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,
                            char *out, size_t outsz);
pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz);
size_t    pe_paginate(const double *tops, const double *heights, size_t n,
                      double page_h, int *out_page, double *out_page_y);
```

### `pe_safe_basename`
- Convierte un título hostil en un **basename de archivo seguro** (sin extensión, sin separadores de
  ruta, sin punto inicial). Reglas, por byte:
  - Se conservan tal cual `A-Z a-z 0-9` y `. _ -`.
  - Cualquier otro byte —incluidos `/`, `\`, espacios, bytes de control y **no-ASCII** (≥ 0x80)— se
    mapea a `_`. (ASCII-only es la elección portable; la normalización Unicode del nombre queda fuera
    de alcance.)
  - Se **colapsan** las corridas de `_` en uno solo.
  - Se **recortan** `_`, `.` y `-` al inicio y al final (así no hay archivos ocultos `.x`, ni `..`,
    ni nombres con basura en los bordes).
  - Se **acota** la longitud a `PE_NAME_MAX` (truncado; luego se re-recortan los bordes).
- **Falla cerrado / siempre usable:** si tras sanear no queda nada (título vacío, NULL, todo
  separadores/control), se escribe `PE_FALLBACK_NAME`. El resultado es siempre no vacío y
  NUL-terminado, **salvo**:
  - `out == NULL` u `outsz == 0` → `PE_ERR_NULL_ARG`.
  - `outsz` no alcanza ni para el nombre saneado más corto representable (ni el fallback) →
    `PE_ERR_OVERFLOW`, con `out` dejado como cadena vacía (sin nombre a medias).
- `title == NULL` se trata como título vacío (→ fallback).
- **No** añade la extensión: eso es trabajo de `pe_build_path`.

### `pe_build_path_ext` / `pe_build_path`
- `pe_build_path_ext` construye la ruta completa `dir + "/" + pe_safe_basename(title) + ext` en `out`.
  `pe_build_path` es el wrapper que pasa `PE_EXT` (`.pdf`); el export PNG pasa `PE_EXT_PNG` (`.png`).
  Una sola superficie de saneo/contención de ruta para ambos formatos (DRY).
- `ext` es un literal de **confianza** (lo pasa la app, no la red); `ext == NULL` se trata como `""`
  (sin extensión).
- `dir` es de **confianza** (lo elige la app desde XDG/`$HOME`, no viene de la red); `title` es
  **hostil** y pasa por `pe_safe_basename`. Un `/` final en `dir` se respeta (no se duplica).
- **Falla cerrado:** si la ruta no cabe en `outsz` → `PE_ERR_OVERFLOW` y `out` queda vacío (nunca una
  ruta a medio formar). `dir == NULL` / `out == NULL` / `outsz == 0` → `PE_ERR_NULL_ARG`.
- Como el basename ya no contiene `/`, el resultado **no puede** salir de `dir` (sin traversal): la
  autenticidad del destino se mantiene por construcción, no por confianza en el título.

### `pe_paginate`
- Reparte `n` filas (en orden de documento, con su `tops[i]` absoluto y `heights[i]`) en páginas de
  altura útil `page_h`, **sin partir ninguna fila**. Escribe para cada fila `out_page[i]` (índice de
  página base 0) y `out_page_y[i]` (y dentro de esa página).
- Algoritmo determinista: se mantiene un `offset` (la Y de documento que mapea al tope, y=0, de la
  página actual). Para cada fila, `y = tops[i] - offset`; si `y > 0` y `y + heights[i] > page_h` (no
  cabe y no está ya en el tope de la página), se abre página nueva (`offset = tops[i]`, `y = 0`). Una
  fila **más alta que `page_h`** ocupa su propia página desde `y = 0` y **se desborda** (no se parte:
  partir texto exige cortar glifos, fuera de alcance).
- Devuelve la **cantidad de páginas** (`última página + 1`), o `0` si `n == 0`, `page_h <= 0`, o
  cualquier puntero es NULL (el llamante no pinta nada).
- Preserva el ritmo vertical (gaps entre filas) dentro de cada página, porque `y` conserva la
  distancia relativa al `offset`.

## 3. Garantías

- **Pureza / Zero Trust:** sin I/O, sin estado global, reentrante; el título es dato hostil que se
  sanea, nunca se confía.
- **Secure by Default / falla cerrado:** un nombre de archivo peligroso no es representable (sin
  traversal, sin separadores, sin ocultos); ante cualquier duda, fallback o `PE_ERR_OVERFLOW` con
  `out` vacío. Nunca una ruta a medio formar.
- **Sin asignación dinámica:** buffers de capacidad fija provistos por el llamante.
- **Determinista:** misma entrada → misma salida (testeable, agent-friendly).
- Objetivo de auditoría: `-fsanitize=address,undefined` limpio; fuzzing de `pe_safe_basename` y
  `pe_build_path` con título arbitrario sin crash ni overflow.

## 4. Tabla de estados

| `pe_status` | Condición |
| :-- | :-- |
| `PE_OK` | El nombre/ruta se construyó (no vacío, NUL-terminado). |
| `PE_ERR_NULL_ARG` | Puntero requerido NULL / `outsz == 0`. |
| `PE_ERR_OVERFLOW` | El resultado no cabe en `outsz` (`out` queda vacío). |

`pe_paginate` no usa `pe_status`: devuelve la cuenta de páginas (0 = nada que paginar / argumento
inválido).

## 5. Fuera de alcance

- **La I/O de Cairo:** crear el `cairo_pdf_surface_t`, correr el layout (`layout_doc`) y pintar las
  filas página por página lo hace el orquestador de la GUI (`gui/browser_ui.c`, `export_pdf`), que
  reusa exactamente la misma display list y los mismos helpers de pintado que la pantalla (texto real
  vía `cairo_show_text` ⇒ PDF con texto seleccionable). Es código GUI: compila endurecido y se marca
  **pendiente de verificación visual**, no verificado.
- **Partir una fila entre páginas** (cortar glifos / líneas): una fila más alta que la página se
  desborda, no se parte.
- **Normalización Unicode del nombre de archivo:** se queda en ASCII seguro (los bytes ≥ 0x80 → `_`).
- **Elegir el directorio de salida** (XDG `Downloads` / `$HOME`) y mostrar el toast de resultado: lo
  resuelve el orquestador; aquí `dir` ya viene dado y de confianza.
- **Exportar a PNG / screenshot de página completa:** otro hito (`cairo_image_surface_t`); este
  cubre solo el PDF vectorial.
