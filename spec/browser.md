# Especificación: `browser` — navegador GUI mínimo

> Hito 5+ — Navegador funcional con ventana Wayland: barra de URL, botones
> Atrás/Adelante, y renderizado de páginas vía `tab`/`secure_fetch`.

## 1. Propósito

`browser` es la capa pura de estado y navegación del navegador GUI. Mantiene el
historial de URLs, la posición actual, la URL en edición y el último contenido
renderizado (título + texto). No realiza I/O: la orquesta gráfica de Wayland/Cairo
pide una acción y `browser` responde con el nuevo estado y, opcionalmente, una
petición de carga (fichero local o URL `https://`).

## 2. Estado

```c
typedef struct browser_state {
    char **history;      /* URLs visitadas; history[0] es la primera */
    size_t history_len;
    size_t history_cap;
    size_t history_pos;  /* índice de la página actual; < history_len */

    char   url_bar[1024]; /* URL en edición */
    size_t url_bar_len;
    size_t url_bar_cursor; /* posición del cursor en url_bar */

    char  *page_title;   /* último título renderizado; owned */
    char  *page_text;    /* último texto renderizado; owned */
    int    loading_error; /* último error de carga (0 = éxito) */

    char **exceptions;   /* hosts con override de TLS débil (sesión) */
    size_t exceptions_len;
    size_t exceptions_cap;
} browser_state;
```

## 3. Contrato de navegación

- `browser_init(state)` → inicializa el historial vacío y la URL por defecto
  `about:blank`.
- `browser_navigate(state, url)` —
  - Si `url` empieza con `https://`, la GUI debe usar `secure_fetch` para
    obtener el HTML y luego `tab_load` para renderizar.
  - Si no, la GUI debe tratar `url` como ruta local y leer el fichero.
  - Tras una carga exitosa, se añade `url` al historial **después** de
    `history_pos`, descartando las entradas futuras (comportamiento Atrás/Adelante
    estándar). `page_title` y `page_text` se actualizan.
  - Si falla, `loading_error` se establece y `page_text` muestra un mensaje de
    error seguro (sin contenido remoto parcial).
- `browser_back(state)` → retrocede en el historial si es posible.
- `browser_forward(state)` → avanza en el historial si es posible.
- `browser_set_url_bar(state, url)` → copia `url` a `url_bar` para edición.
- `browser_commit_url_bar(state)` → toma el contenido de `url_bar` y llama a
  `browser_navigate`.
- `browser_add_exception(state, host)` / `browser_is_exception(state, host)` →
  lista de hosts para los que la GUI usará `SF_POLICY_PERMISSIVE` (TLS 1.3 y KE
  híbrido obligatorios, certificados débiles permitidos como override explícito).

- `browser_set_page(state, title, text, error)` → almacena título y texto. El
  contenido procede de un documento hostil y puede venir en codificaciones legadas
  (Latin-1) cuyos bytes altos son **UTF-8 inválido**. Como `cairo_show_text` rechaza
  UTF-8 inválido y deja de pintar el resto del fotograma, `browser_set_page`
  **sanea** título y texto a UTF-8 bien formado, sustituyendo por `?` cualquier byte
  que no forme una secuencia válida (salida nunca más larga que la entrada).
  *(Pendiente: transcodificación real según el charset declarado para mostrar los
  acentos en vez de `?`.)*

## 4. Garantías de seguridad

- Solo se cargan URLs `https://` o ficheros locales; cualquier otro esquema se
  rechaza antes de tocar la red.
- El contenido remoto se parsea/ejecuta solo dentro del worker `tab` confinado.
- Los mensajes de error no incluyen texto plano del contenido remoto.
- El texto a renderizar se normaliza a UTF-8 válido: un documento malformado no
  puede envenenar el renderer ni dejar la ventana en blanco.
- El historial no persiste en disco (Zero Knowledge por defecto).

## 4b. Estado de aviso transitorio (toast)

- `browser_set_status(bs, msg, now_ms)` guarda un aviso breve (p. ej. "blocked: insecure http link"
  cuando se pulsa un enlace inseguro) copiando `msg` (truncado a `BROWSER_STATUS_MAX`) y fijando su
  caducidad en `now_ms + BROWSER_STATUS_DURATION_MS`. `msg` vacío o `NULL` lo limpia.
- `browser_status_text(bs, now_ms)` devuelve el aviso si sigue vigente a `now_ms`, o `NULL`.
- El reloj `now_ms` (milisegundos monótonos) lo aporta el llamante: el módulo no hace llamadas de
  tiempo, así que es puro y testeable. Una navegación real (navigate/back/forward) descarta un aviso
  pendiente para que no sobreviva al cambio de página. El temporizado y la capacidad viven en
  `BROWSER_STATUS_DURATION_MS` / `BROWSER_STATUS_MAX` (sin números mágicos en el código).

## 5. Qué queda fuera de alcance

- Layout de cajas/CSS/imágenes: el renderizado es texto extraído (igual que
  `freedom-view`).
- Pestañas múltiples: una sola pestaña por ventana.
- Favoritos/historial persistente: se mantiene sólo en memoria.
- Indicadores de carga/progreso: síncrono por ahora.

## 6. Pruebas

- Historial vacío: back/forward no hacen nada.
- Navegar tres páginas, retroceder y avanzar.
- Navegar desde el medio del historial descarta el futuro.
- `browser_commit_url_bar` con URL local vs `https://`.
- Rechazo de esquemas no permitidos.
