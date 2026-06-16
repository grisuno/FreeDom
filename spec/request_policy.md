# Especificación: `request_policy`

> Hito 5 — Doctrina anti-vigilancia (bloqueo de terceros). Estado: **SPEC + TEST (rojo)**.
> Metodología: SDD + TDD. Esta spec es el contrato; `tests/test_request_policy.c` debe fallar
> hasta que exista `src/request_policy.c` (estado rojo).

## 1. Propósito

`request_policy` decide si una petición de **subrecurso** (imagen, hoja de estilo, script,
fuente, fetch…) puede salir a la red, dado el origen del documento de nivel superior. Implementa
el Principio 3 del proyecto — **Privacy by Default: bloqueo total de terceros a nivel del motor
de red** — como **lógica pura sin I/O**, directamente auditable.

Es la política que el cargador de páginas consultará **antes** de invocar a `secure_fetch` para
cualquier subrecurso. Aquí no se abre red: solo se decide.

## 2. Modelo: origen, sitio y "tercero"

- **Host:** la autoridad de la URL (`https://HOST[:puerto]/...`), en minúsculas.
- **Sitio (dominio registrable):** el host recortado a su dominio registrable. Es la unidad de
  "primera parte". Ejemplos: `www.example.com` → `example.com`; `a.b.example.co.uk` →
  `example.co.uk`.
- **Tercero (third-party):** una petición cuyo **sitio** difiere del sitio del documento de
  nivel superior. Por defecto se **bloquea**.

Cálculo del dominio registrable: **Public Suffix List completa** (Hito 5). El módulo aplica el
algoritmo oficial de la PSL sobre la lista canónica vendorizada en `third_party/psl/`: reglas
normales, comodín (`*.ck`) y excepción (`!www.ck`); gana la regla de excepción, si no la regla
coincidente más larga, y si ninguna coincide la regla implícita `*` (un solo label). Se incluyen
**ambas** secciones (ICANN y PRIVATE), de modo que p.ej. cada subdominio `*.github.io` es un sitio
registrable distinto (más estricto y correcto para privacidad). La tabla se **genera en tiempo de
compilación** (`tools/gen_psl` → `build/psl_data.c`) como arrays ordenados de solo lectura; la
búsqueda en runtime es pura y en memoria (binary search), **sin** `libpsl`. Fuente única de
verdad: el `.dat`; la tabla es derivada, nunca editada a mano. Fallar cerrado: ante ambigüedad o
URL no parseable, se **bloquea**. Limitación conocida: las reglas IDN se comparan como texto UTF-8
en minúsculas tal cual; la normalización IDNA2008/punycode completa queda fuera de la v1.

## 3. Contrato de la API

Definida en `include/request_policy.h`. Todo es **puro** (sin I/O, sin estado global).

```c
typedef enum rp_decision {
    RP_ALLOW = 0,           /* misma-parte: permitido */
    RP_BLOCK_THIRD_PARTY,   /* subrecurso de tercero: bloqueado por defecto */
    RP_BLOCK_SCHEME,        /* esquema no https */
    RP_BLOCK_INVALID        /* URL ausente / no parseable (falla cerrado) */
} rp_decision;

/* Host en minusculas de una URL absoluta. 0 ok; -1 si no hay host parseable. */
int rp_host_of(const char *url, char *out, size_t out_size);

/* Dominio registrable ("sitio") de un host. 0 ok; -1 si no cabe / host vacio. */
int rp_site_of(const char *host, char *out, size_t out_size);

/* 1 si top_level_url y request_url comparten sitio; 0 si no o si alguna falla. */
int rp_same_site(const char *top_level_url, const char *request_url);

/* Decision para un subrecurso dado el documento de nivel superior. */
rp_decision rp_evaluate(const char *top_level_url, const char *request_url);
```

No hay niveles de política "relajada": permitir terceros por defecto **no es representable**
(Secure by Default). El bloqueo de terceros es la única política.

## 4. Semántica de `rp_evaluate`

En orden, fallando cerrado:
1. `request_url` sin host parseable ⇒ `RP_BLOCK_INVALID`.
2. `request_url` cuyo esquema no es `https://` (case-insensitive) ⇒ `RP_BLOCK_SCHEME`.
3. `top_level_url` sin host parseable o no `https` ⇒ `RP_BLOCK_INVALID` (no se puede situar la
   primera parte ⇒ se rechaza).
4. Si el sitio de `request_url` == sitio de `top_level_url` ⇒ `RP_ALLOW`; si no ⇒
   `RP_BLOCK_THIRD_PARTY`.

`rp_host_of`: localiza `"://"`, toma el host hasta `'/'`, `':'`, `'?'`, `'#'` o fin; lo copia en
minúsculas. Host vacío o ausencia de `"://"` ⇒ `-1`. Buffer insuficiente ⇒ `-1`.

`rp_site_of`: aplica la regla del dominio registrable (§2). Host de una sola etiqueta
(`localhost`) ⇒ se devuelve íntegro.

## 5. Tabla de decisiones (ejemplos)

| top_level | request | resultado |
| :-- | :-- | :-- |
| `https://example.com/` | `https://example.com/a.js` | `RP_ALLOW` |
| `https://www.example.com/` | `https://cdn.example.com/x.css` | `RP_ALLOW` (sitio `example.com`) |
| `https://example.com/` | `https://tracker.net/p.gif` | `RP_BLOCK_THIRD_PARTY` |
| `https://a.example.co.uk/` | `https://b.example.co.uk/x` | `RP_ALLOW` (sitio `example.co.uk`) |
| `https://example.com/` | `http://example.com/x` | `RP_BLOCK_SCHEME` |
| `https://example.com/` | `https:///x` | `RP_BLOCK_INVALID` |
| `http://example.com/` | `https://example.com/x` | `RP_BLOCK_INVALID` (top no https) |

## 6. Garantías

1. **Privacy by Default.** Todo tercero se bloquea sin configuración.
2. **Fail-closed.** URL no parseable, esquema no https o top indeterminable ⇒ bloqueo.
3. **Puro y reentrante.** Sin I/O, sin estado global mutable; misma entrada, misma salida.
   Objetivo: ASan/UBSan limpios.
4. **Sin fugas.** No asigna memoria dinámica; escribe en buffers del llamante con límite.

## 7. Matriz de pruebas

`tests/test_request_policy.c` (cmocka):
- `rp_host_of`: https/http, con puerto/path/query, sin `"://"`, host vacío, overflow de buffer.
- `rp_site_of`: `example.com`, `www.example.com`, `a.b.example.com`, `example.co.uk`,
  `www.example.co.uk`, `localhost`; PSL real: `blog.github.io` (PRIVATE), `*.ck` (comodín),
  `!www.ck` (excepción), `shop.example.dev`.
- `rp_same_site`: mismos/distintos sitios, subdominios, co.uk; `alice.github.io` ≠ `bob.github.io`.
- `rp_evaluate`: cada fila de §5 + `NULL` ⇒ bloqueo.

## 8. Fuera de alcance

- Normalización IDNA2008/punycode de hosts internacionalizados (las reglas IDN se comparan como
  texto; ASCII y hosts ya en punycode funcionan).
- Listas de bloqueo por host/patrón (EasyList-like), cookies de terceros, almacenamiento
  particionado (specs aparte).
- Integración con el cargador de páginas y con `secure_fetch` (cuando exista el orquestador de
  carga de documento + subrecursos).
- WebRTC / fugas de IP (deshabilitado a otro nivel), fingerprinting (canvas/WebGL).
