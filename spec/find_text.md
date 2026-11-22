# find_text (`ft_`) — búsqueda en la página (Ctrl+F)

Módulo **puro**, sin I/O ni estado global. Busca una consulta del usuario sobre el texto que el
layout ya pintó y devuelve dónde están las coincidencias, para que el pintor las resalte y la
ventana desplace la actual a la vista.

## Por qué así

- El texto buscado es **el texto renderizado**, no el DOM: lo que el usuario ve. Así un nodo
  `display:none` no "coincide" y el texto de `::before` sí.
- Todo ocurre en el **lado confiable** sobre memoria que el padre ya tiene: la búsqueda no viaja
  al worker, no toca la red, no ejecuta JS y **la página no puede observarla** (no hay evento,
  ni `window.find`, ni cambio de selección expuesto). Zero Knowledge: la consulta no se persiste.
- El layout parte el texto en fragmentos (una palabra suele ser un fragmento y el espacio entre
  palabras es avance de pluma, no un carácter). Por eso la entrada es una secuencia de **piezas**
  con una marca `gap_before`: hay un blanco implícito entre esta pieza y la anterior.

## Entradas

- `ft_piece { const char *text; size_t len; int gap_before; }` — UTF-8 sin validar (contenido
  hostil). `gap_before` = 1 si entre la pieza anterior y esta hay blanco (otra línea, otro
  bloque, o un hueco de pluma).
- Consulta UTF-8 del usuario. `ft_compile` la pliega y colapsa blancos; vacía (o solo blancos)
  ⇒ 0 coincidencias.

## Semántica

- **Plegado** (`ft_fold`): mayúsculas = minúsculas (ASCII, Latin-1, Latin Extended-A, griego
  básico, cirílico básico) y **sin distinguir diacríticos** en latín (`resume` encuentra
  `résumé`, `nino` encuentra `Niño`) — el comportamiento por defecto de Firefox (*Match
  Diacritics* desmarcado). `ß` se queda `ß` (no se expande: un carácter = un carácter).
- **Blancos**: cualquier secuencia de blancos (espacio, tab, LF, CR, FF, NBSP U+00A0) y todo
  `gap_before` cuentan como UN separador. Un blanco de la consulta coincide con un separador;
  la consulta nunca empieza ni termina en blanco (se recorta).
- Byte inválido de UTF-8 ⇒ U+FFFD que **no coincide** con nada de la consulta (avanza 1 byte).
  Nunca lee fuera de `[text, text+len)`.
- Coincidencias **sin solapamiento**, en orden de documento; la siguiente búsqueda empieza al
  final de la anterior. Una coincidencia no empieza en un blanco.
- Topes: consulta `FT_QUERY_MAX` (256) puntos de código; coincidencias hasta el `cap` del
  llamador (`FT_MATCH_MAX` 1000 en la GUI, como Firefox), con `*truncated = 1` si hubo más.

## Salidas

- `ft_match { ft_pos start, end; }`, `ft_pos { size_t piece; size_t off; }`: inicio inclusivo,
  fin exclusivo, `off` en bytes dentro de su pieza (`end.off` puede ser `len` de su pieza).
- `ft_spans`: cada coincidencia en tramos por pieza `{piece, start, end, match}` (una
  coincidencia que cruza piezas da un tramo por pieza tocada) — lo que el pintor resalta.
- `ft_step(cur, n, dir)`: siguiente/anterior con vuelta (Enter / Shift+Enter / F3).

## Errores

| Caso | Resultado |
| :-- | :-- |
| `pieces == NULL` con `n > 0`, `out == NULL` con `cap > 0`, `nout == NULL` | `FT_EINVAL`, salidas sin tocar |
| consulta vacía | `FT_OK`, 0 coincidencias |
| `cap` alcanzado | `FT_OK`, `*truncated = 1` |

## Dado-Cuando-Entonces

- **Dado** las piezas `"Hello"`, `"world"` (gap) **cuando** busco `"hello WORLD"` **entonces**
  una coincidencia de (0,0) a (1,5).
- **Dado** `"Hel"`, `"lo"` (sin gap, `<b>Hel</b>lo`) **cuando** busco `"hello"` **entonces** una
  coincidencia que cruza las dos piezas; y `"hel lo"` no coincide.
- **Dado** `"Niño résumé"` **cuando** busco `"nino resume"` **entonces** coincide.
- **Dado** `"aaaa"` **cuando** busco `"aa"` **entonces** dos coincidencias (sin solapar).
- **Dado** bytes `\xff\xfe` **cuando** busco cualquier cosa **entonces** sin lectura fuera de rango.

## En la GUI (`gui/browser_ui.c`, `gui/bui_chrome.c`)

- `Ctrl+F` abre la barra al pie (geometría en `chrome_layout`: `chl_findbar`), con el texto de la
  última búsqueda seleccionado. Escribir busca al vuelo; `Enter`/`F3` siguiente, `Shift+Enter`/
  `Shift+F3` anterior, `Esc` cierra. Contador «3 of 17», «No matches» en rojo, «More than 1000».
- Se resaltan **todas** las coincidencias visibles; la actual en otro color y se desplaza a la
  vista (a un tercio de la altura) si está fuera.
- Las piezas son los fragmentos de texto del layout principal y de los subárboles fuera de
  flujo (`oof_sub`). Los tramos se buscan por dirección del texto (el fragmento es un trozo del
  texto del bloque), así que el pintor los encuentra en cualquier pasada.
- La barra se cierra al navegar o cambiar de pestaña; las coincidencias se recalculan cuando el
  layout cambia (generación del layout).

## Fuera de alcance (v1)

- *Match case*, *Whole words*, *Match diacritics* (casillas de Firefox).
- Texto de bloques posicionados pintados por el camino `mini` y de controles de formulario.
- Expansiones de plegado de varios caracteres (`ß`→`ss`, ligaduras).
