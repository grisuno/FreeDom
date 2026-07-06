# Especificación: `html_parse`

> Hito 2 — Motor de Parsing y Aislamiento. Estado: **SPEC + TEST + FUZZ (sin implementación)**.
> Metodología: SDD + TDD. Esta spec es el contrato; `tests/test_html_parse.c` debe fallar
> hasta que exista `src/html_parse.c` (estado rojo).

## 1. Propósito

`html_parse` convierte HTML **no confiable** (recibido por `secure_fetch`) en un árbol DOM
**inerte** y consultable. Es la primera frontera Zero Trust tras la red: el contenido remoto es
hostil por defecto. El parser **nunca ejecuta scripts** y produce una vista de la que el motor
de renderizado puede fiarse.

## 2. Decisión de stack

Backend de parsing: **Lexbor** (`liblexbor-dev` 3.0.0, C puro). Lexbor implementa el algoritmo
de parsing tolerante de HTML5 y, por diseño, **no ejecuta JavaScript** — es un parser, no un
motor. Eso encaja con el modelo: el aislamiento del JS es problema del Hito 3, aquí solo
garantizamos un árbol inerte.

`liblexbor-dev` no estaba instalado en el host; se instala con
`sudo apt install liblexbor-dev`. El tipo `lxb_*` **no aparece** en `html_parse.h`: el
documento es un tipo opaco (`hp_document`). Encapsulación = Zero Trust hacia la dependencia.

## 3. Garantías de seguridad

1. **Sin ejecución de scripts.** Lexbor no ejecuta JS. Además, por defecto:
   - `strip_scripts` elimina los nodos `<script>` del árbol.
   - `strip_event_handlers` elimina los atributos `on*` en línea (`onclick`, `onload`, …).
2. **Entrada acotada (anti-DoS).** Toda entrada por encima de `max_bytes` se rechaza con
   `HP_ERR_TOO_LARGE` **antes** de parsear.
3. **Robustez ante entrada maliciosa.** Entrada malformada, truncada o binaria produce un árbol
   o un error limpio, **nunca** un fallo de memoria. Verificado con fuzzing (`make fuzz`,
   libFuzzer + ASan/UBSan).
4. **Recorrido sin recursión.** El árbol se recorre de forma iterativa (punteros
   hijo/hermano/padre), no recursiva: HTML profundamente anidado por un atacante no puede
   desbordar la pila.
5. **Memoria.** `hp_document` y los buffers devueltos tienen dueño único; `hp_document_free` y
   `hp_free` son idempotentes / seguros con `NULL`. Objetivo: `valgrind` y ASan/UBSan limpios.

## 4. Contrato de la API

Definida en `include/html_parse.h`.

```c
hp_config hp_config_default(void);

/* Validador puro (sin parsing). */
hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg);

/* Parsea HTML no confiable a un documento inerte. cfg==NULL => defaults. */
hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out);

/* Consultas de solo lectura. */
size_t hp_element_count(const hp_document *doc);
size_t hp_script_count(const hp_document *doc);
size_t hp_event_handler_count(const hp_document *doc);

/* Buffers en propiedad; liberar con hp_free. *out_len excluye el NUL final. */
char *hp_extract_text(const hp_document *doc, size_t *out_len);
char *hp_get_title(const hp_document *doc, size_t *out_len);
/* Lista de los <script> EJECUTABLES en orden de documento, cada uno como su propia
 * entrada. Dos clases (Hito 24 EXT):
 *   - inline:  text != NULL (fuente NUL-terminada), src == NULL.
 *   - externo: src != NULL (el valor CRUDO del atributo src, hostil, sin resolver),
 *              text == NULL. El parser NUNCA fetchea: quien ejecuta (el worker de tab)
 *              decide si puede pedir los bytes al padre confiable bajo política.
 * Un <script> se EJECUTA solo si su `type` está ausente/vacío o es un MIME de
 * JavaScript (contiene "javascript"/"ecmascript"). Todo otro `type` se EXCLUYE
 * (fail-closed, no se ejecuta): bloques de datos JSON/LD, módulos ES (import/export
 * no son evaluables como script clásico), y plantillas (text/x-jquery-tmpl,
 * text/html, text/template), cuyo markup lanzaría un SyntaxError si se evaluara como
 * JS (era el error "#each" de Slashdot). Espeja `ctype_is_javascript` de tab.c (la
 * misma regla para el Content-Type fetcheado del script externo).
 * Un <script src> con cuerpo inline lista SOLO el src (semántica de navegador: si hay
 * src, el contenido se ignora). El worker evalúa CADA entrada por separado: en un
 * navegador cada <script> es un programa independiente, y una excepción no capturada
 * en uno aborta SOLO ese script, no los demás (concatenarlos en un único eval dejaba
 * que el primer fallo matara a todos -- la causa raíz de "no carga nada" en paginas
 * con mucho JS). Acotada por HP_MAX_SCRIPTS (fail-closed, anti-DoS: el exceso se
 * descarta, no se ejecuta). NULL (y *out_count == 0) si no hay scripts ejecutables o
 * en fallo de asignacion. */
typedef struct hp_script { char *text; size_t len; char *src; } hp_script;
hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count);
void hp_free_scripts(hp_script *scripts, size_t count);

void hp_free(char *buf);
void hp_document_free(hp_document *doc);
```

### Configuración por defecto (Secure by Default)
- `max_bytes = HP_DEFAULT_MAX_BYTES` (32 MiB).
- `strip_scripts = 1`.
- `strip_event_handlers = 1`.

## 5. Tabla de errores

| Código | Condición |
| :-- | :-- |
| `HP_OK` | Documento parseado (y saneado según política). |
| `HP_ERR_NULL_ARG` | `html == NULL` o `out == NULL`. |
| `HP_ERR_EMPTY` | `len == 0`. |
| `HP_ERR_TOO_LARGE` | `len > max_bytes`. |
| `HP_ERR_PARSE` | Lexbor no pudo crear/parsear el documento. |
| `HP_ERR_OOM` | Fallo de asignación. |
| `HP_ERR_INTERNAL` | Estado inesperado del backend. |

## 6. Semántica

- `hp_validate_input`: `NULL`⇒`HP_ERR_NULL_ARG`; `len==0`⇒`HP_ERR_EMPTY`; `len>cap`⇒
  `HP_ERR_TOO_LARGE`; si no, `HP_OK`. `cap` = `cfg->max_bytes` o el default si `cfg==NULL`/0.
- `hp_parse`: valida, crea documento Lexbor, parsea, y **muta** el árbol aplicando la política
  (elimina `<script>` y/o atributos `on*`). Los contadores reflejan el árbol **tras** el saneo.
- `hp_script_count`: con `strip_scripts` activo ⇒ `0`. Con `strip_scripts=0` ⇒ nº de `<script>`.
- `hp_event_handler_count`: con `strip_event_handlers` activo ⇒ `0`. Si no ⇒ nº de atributos
  `on*` en el árbol.
- `hp_extract_text`: texto inerte del cuerpo (sin contenido de `<script>` si fue eliminado).
- `hp_get_title`: contenido de `<title>` o cadena vacía.
- `hp_extract_script_list`: devuelve un arreglo en propiedad con cada `<script>`
  ejecutable como su propio `hp_script`, en orden de documento; `*out_count` recibe el
  número. Un script **inline** lleva `text` (NUL-terminado) + `len` y `src == NULL`; un
  script **externo** lleva `src` (el valor crudo del atributo, hostil, sin resolver ni
  fetchear) y `text == NULL`. Un `<script src>` con cuerpo inline lista **solo** el `src`
  (si hay `src`, el contenido se ignora — semántica de navegador). Ejecuta solo si el
  `type` está ausente/vacío o es un MIME de JavaScript; todo otro `type` se excluye
  fail-closed (JSON/LD, módulos ES, y plantillas `text/x-jquery-tmpl`/`text/html`/
  `text/template`), igual que los inline vacíos. Solo significativo si se parseó con `strip_scripts==0`.
  **Browser semantics:** el llamador evalúa cada script por separado, así una excepción no
  capturada en uno **no** aborta los siguientes. Tope `HP_MAX_SCRIPTS` (4096): los scripts
  extra se descartan (fail-closed). `NULL` con `*out_count==0` si no hay o en OOM. Liberar
  con `hp_free_scripts` (libera cada `text`/`src` y el arreglo; idempotente en NULL).
  **El parser jamás abre la red:** exponer `src` es solo transporte de un atributo; la
  decisión de buscar esos bytes vive en el worker de `tab` + el padre confiable
  (`spec/tab.md` §2, Hito 24 EXT).

## 7. Matriz de pruebas

`tests/test_html_parse.c` (cmocka):
- Validador: `NULL`, vacío, sobre-tamaño, OK.
- Config por defecto = segura.
- `hp_parse` de doc simple ⇒ título, texto, `element_count > 0`.
- `<script>` con `strip_scripts` por defecto ⇒ `script_count == 0` y el texto no contiene el
  cuerpo del script.
- `<script>` con `strip_scripts = 0` ⇒ `script_count >= 1`.
- `onclick=...` con `strip_event_handlers` por defecto ⇒ `event_handler_count == 0`.
- Entrada malformada/binaria ⇒ `HP_OK` sin crash.
- `hp_document_free`/`hp_free` con `NULL` y dobles llamadas.

`fuzz/fuzz_html_parse.c` (libFuzzer): bytes arbitrarios → `hp_parse` + consultas + free; el
objetivo es que **nunca** se produzca crash/leak/UB. `make fuzz`.

## 8. Fuera de alcance

- Aplicación de CSS, layout y renderizado (Hito 4).
- Ejecución/aislamiento de JS (Hito 3).
- Política de subrecursos (imágenes, hojas de estilo externas): se define en spec aparte; el
  bloqueo de terceros vive en el motor de red.

## 9. Extracción de hojas de estilo externas (`<link rel=stylesheet>`, Hito 27)

El parser **jamás fetchea**: igual que con los `<script src>` (§6), las hojas externas solo se
**reportan** con su `href` crudo (hostil); decidir si esos bytes pueden buscarse es del worker
`tab`, gateado por el padre (`spec/tab.md` §8).

```c
/* Tope anti-DoS de hojas reportadas (una página real usa <10; el resto se descarta). */
#define HP_MAX_STYLESHEETS ((size_t)64)

/* Devuelve los href crudos de los <link rel=stylesheet> aplicables, en orden de
 * documento, como arreglo propio de strings NUL-terminadas; *out_count recibe la
 * cantidad. NULL (con *out_count == 0) si no hay ninguno o sin memoria. Liberar con
 * hp_free_stylesheet_hrefs. */
char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count);
void hp_free_stylesheet_hrefs(char **hrefs, size_t count);
```

Semántica (Dado-Cuando-Entonces), todo **fail-closed** (ante la duda el `<link>` se salta):

- **Dado** `<link rel=stylesheet href=S>`, **cuando** se extrae, **entonces** S aparece (crudo,
  sin resolver). `rel` se compara por **token** (lista separada por espacios) y **case-insensitive**:
  `rel="STYLESHEET"` aplica; `rel="alternate stylesheet"` **no** (hoja alternativa, no activa).
- **Dado** un `<link>` sin `href` o con `href=""`, **entonces** se salta (no nombra recurso).
- **Dado** un atributo `media`, **entonces** el `<link>` aplica solo si `media` está ausente/vacío
  o contiene `screen` o `all` (substring case-insensitive). `media="print"` se salta. La
  evaluación real de media queries del atributo queda fuera (v1).
- **Dado** más de `HP_MAX_STYLESHEETS` links aplicables, **entonces** los excedentes se descartan.
- **Dado** `doc == NULL`, **entonces** NULL con `*out_count == 0`.

Matriz de pruebas: básico (2 hojas + ruido `rel=icon`/sin-href), `rel` case-insensitive por token,
`alternate` excluido, gate de `media`, tope, documento sin links, args NULL.
