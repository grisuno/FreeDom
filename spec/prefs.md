# Especificación: `prefs`

> Hito 10 — Persistencia de preferencias, marcadores e historial (lado puro).
> Metodología: SDD + TDD. `tests/test_prefs.c` debe fallar (no enlaza) hasta que exista
> `src/prefs.c`.

## 1. Propósito

`prefs` es la **lógica pura** del perfil del usuario: el modelo en memoria de las
preferencias de sesión (tema, capacidades, zoom, JS, Tor/I2P, modo lectura), los
**marcadores** y el **historial persistente**, junto con su serialización a un texto
versionado y su parseo **fail-closed**. No hace ninguna I/O: leer/escribir el disco (cifrado)
es trabajo del orquestador `profile` (ver `spec/profile.md`).

Doctrina aplicable:

- **Zero Knowledge:** este módulo nunca ve el disco; produce/consume un texto plano que el
  orquestador sella con AEAD. El usuario puede desactivar el recuerdo de historial
  (`remember_history`); al desactivarlo el orquestador/GUI borra el historial retenido.
- **Fail closed:** un texto con magia/versión desconocida se rechaza entero (el llamador se
  queda con los defaults seguros). Una URL con bytes de control no es representable en el
  estado. Los topes (`PREFS_MAX_*`) son inviolables (anti-DoS: el blob viene de disco, pero
  los *títulos* de los marcadores nacieron en contenido remoto hostil).
- **Privacy by Default:** los defaults de `prefs_init` son exactamente los de una sesión
  virgen actual: imágenes/CSS/JS-por-allowlist, tema claro, zoom 100 %, Tor/I2P off,
  lectura off. Persistir no cambia el punto de partida de un perfil nuevo.

## 2. Contrato de la API (C)

Definida en `include/prefs.h`. Prefijo de módulo: `prefs_`.

```c
#define PREFS_VERSION       1u
#define PREFS_MAX_URL       1024u   /* espejo de BROWSER_URL_MAX */
#define PREFS_MAX_TITLE     200u    /* bytes de título retenidos (limpiados) */
#define PREFS_MAX_BOOKMARKS 200u
#define PREFS_MAX_HISTORY   500u
#define PREFS_MAX_TEXT      (2u * 1024u * 1024u)  /* tope del texto serializado/parseado */

typedef enum prefs_status {
    PREFS_OK = 0,
    PREFS_ERR_NULL_ARG,
    PREFS_ERR_FORMAT,   /* magia/version desconocida o texto sobre el tope */
    PREFS_ERR_INVALID,  /* URL no representable (vacia, control bytes, demasiado larga) */
    PREFS_ERR_FULL,     /* tope de marcadores alcanzado */
    PREFS_ERR_OOM
} prefs_status;

typedef struct prefs_entry { char *url; char *title; } prefs_entry;

typedef struct prefs_state {
    int theme_mode;        /* 0 claro, 1 oscuro, 2 sepia (ui_theme_mode) */
    int force_theme;       /* ignorar colores de autor */
    int images, css;       /* capacidades de render (rdp_caps) */
    int reader;            /* modo sin distracciones */
    int js_mode;           /* jsp_mode: 0 off, 1 allowlist, 2 on */
    int tor, i2p, torify;  /* enrutado de red opt-in */
    int zoom_pct;          /* zm_clamp aplica los limites del ladder */
    int remember_history;  /* 1 = persistir visitas (default) */
    prefs_entry *bookmarks; size_t bookmarks_len;  /* orden de insercion */
    char **history;         size_t history_len;    /* mas reciente primero */
} prefs_state;

void prefs_init(prefs_state *p);   /* defaults seguros; NULL-safe */
void prefs_free(prefs_state *p);   /* libera listas; idempotente; NULL-safe */

/* Serializa p a un texto versionado propio (*out, NUL-terminado ademas de *out_len). */
prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len);

/* Parsea text[0..len) sobre un out YA inicializado con prefs_init. Magia/version
 * desconocida o len > PREFS_MAX_TEXT => PREFS_ERR_FORMAT y out queda en defaults.
 * Claves desconocidas y lineas malformadas se IGNORAN (compat hacia adelante);
 * valores fuera de rango se normalizan (clamp / default seguro). */
prefs_status prefs_parse(const char *text, size_t len, prefs_state *out);

/* Indice del marcador con esa URL exacta, o -1. */
int prefs_bookmark_index(const prefs_state *p, const char *url);

/* Agrega (added=1) o quita (added=0) el marcador de url. El titulo (posiblemente
 * hostil/NULL) se LIMPIA: control bytes -> ' ', truncado a PREFS_MAX_TITLE en
 * frontera UTF-8. URL invalida => PREFS_ERR_INVALID; tope => PREFS_ERR_FULL. */
prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,
                                   const char *title, int *added);

/* Registra una visita: dedup (si existe se mueve al frente), tope PREFS_MAX_HISTORY
 * (se descarta la mas vieja). URL invalida => PREFS_ERR_INVALID. */
prefs_status prefs_history_add(prefs_state *p, const char *url);

/* Autocompletado de omnibox: hasta max_rows URLs distintas que casan con query
 * (insensible a mayusculas) en out (filas de row_len bytes, NUL-terminadas).
 * Prioridad: marcadores-prefijo, historial-prefijo, marcadores-subcadena (URL o
 * titulo), historial-subcadena. "Prefijo" tambien casa saltando el esquema y un
 * "www." inicial. query "" casa todo (marcadores primero). Puro, sin I/O. */
int prefs_suggest(const prefs_state *p, const char *query,
                  char *out, size_t row_len, int max_rows);

/* Pagina interna "about:bookmarks": HTML propio con los marcadores y las ultimas
 * PREFS_PAGE_HISTORY visitas como links. TODO texto hostil (titulos, URLs) va
 * escapado (&<>"'). El HTML resultante se renderiza por el pipeline normal
 * (worker confinado), nunca se interpreta en el lado confiable. */
#define PREFS_PAGE_HISTORY 50u
prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len);
```

## 3. Formato serializado v1

Texto línea-a-línea, UTF-8, `\n` como separador:

```
freedom-prefs 1
theme=1
force=0
images=1
css=1
reader=0
js=1
tor=0
i2p=0
torify=0
zoom=125
remhist=1
b\t<url>\t<titulo limpio>
h\t<url>
```

- La primera línea es obligatoria: `freedom-prefs <version>`. Versión ≠ 1 ⇒ `PREFS_ERR_FORMAT`.
- `clave=valor`: clave desconocida se ignora (una versión futura puede añadir claves sin
  romper la vieja). Valores booleanos: `0`/distinto-de-0. Valores fuera de rango se
  normalizan (§4).
- `b<TAB>url<TAB>titulo` y `h<TAB>url`: una entrada por línea. Línea malformada (campos de
  más/de menos, URL inválida) se **descarta** sin abortar el parse. Entradas por encima de
  los topes se descartan.
- El texto completo está acotado por `PREFS_MAX_TEXT` en ambas direcciones.

## 4. Validación y saneado (Dado-Cuando-Entonces)

- **Dado** una URL con bytes < 0x20, 0x7f o `\t`, o vacía, o ≥ `PREFS_MAX_URL` bytes,
  **cuando** se intenta registrarla (marcador o visita), **entonces** se rechaza con
  `PREFS_ERR_INVALID` y el estado no cambia. (El espacio se permite: los paths locales
  pueden llevarlo y no rompe el formato tab-separado.)
- **Dado** un título hostil (control bytes, tabs, saltos de línea, > `PREFS_MAX_TITLE`),
  **cuando** se marca la página, **entonces** el título se retiene **limpio**: bytes de
  control → `' '`, truncado en frontera UTF-8. Un título NULL se retiene como `""`.
  El título jamás bloquea el marcado (siempre es saneable).
- **Dado** `theme=99` o `js=7` en el texto, **cuando** se parsea, **entonces** el valor
  fuera de rango cae al default seguro (tema claro; JS allowlist). `zoom` se pasa por
  `zm_clamp` (única fuente de los límites del ladder). Booleanos: cualquier valor ≠ 0 ⇒ 1.
- **Dado** un texto sin la línea mágica, **cuando** se parsea, **entonces**
  `PREFS_ERR_FORMAT` y el estado queda en defaults (nunca un estado a medias).
- **Dado** un marcador ya existente para la URL, **cuando** se vuelve a marcar,
  **entonces** se elimina (toggle) y `*added == 0`.
- **Dado** una visita a la URL que ya encabeza el historial, **cuando** se registra,
  **entonces** es un no-op (`PREFS_OK`, sin reordenar ni duplicar).
- **Dado** el historial lleno (`PREFS_MAX_HISTORY`), **cuando** entra una visita nueva,
  **entonces** se descarta la más antigua (FIFO por el fondo).
- **Dado** cualquier contenido en el estado, **cuando** se genera la página de marcadores,
  **entonces** `&<>"'` van escapados en atributos y texto: un título
  `<script>alert(1)</script>` aparece como texto, jamás como nodo script. (Defensa en
  profundidad: la página además se renderiza en el worker confinado con JS gateado.)
- **Round-trip:** para todo estado alcanzable por la API, `prefs_parse(prefs_format(p))`
  reproduce exactamente los campos, marcadores (orden de inserción) e historial (orden
  más-reciente-primero).

## 5. Garantías de seguridad

1. **Sin I/O, sin red, sin reloj.** Funciones puras; deterministas para test y fuzzing.
2. **Fail closed** en formato y en URLs; los topes son inviolables.
3. **El HTML interno escapa todo dato hostil.** Y aún si fallara, se renderiza confinado.
4. **Ninguna telemetría:** el texto serializado no contiene identificadores de dispositivo,
   timestamps ni contadores — solo lo que el usuario ve y eligió.

## 6. Matriz de pruebas

`tests/test_prefs.c` (CMocka): defaults; round-trip completo; magia/versión mala; texto
sobre el tope; claves desconocidas ignoradas; clamps (tema/js/zoom/booleanos); URL inválida
(control bytes, vacía, larga, tab); título hostil limpiado y truncado en frontera UTF-8;
toggle add/remove; tope de marcadores (`PREFS_ERR_FULL`); dedup/move-to-front/evict del
historial; `prefs_suggest` (prioridad prefijo-sobre-subcadena, salto de esquema y `www.`,
match por título, dedup, query vacía, filas cortas); escapado de la página de marcadores;
args NULL; `prefs_free` idempotente.

## 7. Fuera de alcance

- La I/O y el cifrado (los hace `profile` con `local_store`/`disk_store`).
- Restaurar el back-stack de navegación entre sesiones (el historial persistente alimenta
  el omnibox y la página interna, no los botones atrás/adelante).
- Sincronización entre dispositivos; import/export (HTML de Netscape); carpetas/etiquetas
  de marcadores.
