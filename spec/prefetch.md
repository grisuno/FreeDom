# Especificación: `prefetch` (`pf_`)

> Hito 29 — Pipeline no bloqueante del lado confiable: pre-scanner lookahead + pool de
> descarga paralela de subrecursos. Estado: **cerrado** (spec + test verde + ASan + fuzz del
> scanner + E2E con servidor local lento).

## 1. Propósito

Hoy cada subrecurso de una página (hoja `<link rel=stylesheet>`, `<script src>`, imágenes)
se descarga **en serie**: el worker confinado pide uno, el padre lo baja, responde, y recién
entonces el worker pide el siguiente (protocolo `TAG_SUBREQ`, bloqueante por diseño — dos
pipes, sin io_uring, ver `spec/os_sandbox.md` §13). Con N recursos el tiempo es la **suma**
de latencias. Los navegadores modernos lo resuelven con un *preload scanner*: un lector
rápido del HTML que descubre los subrecursos por adelantado y los baja **en paralelo**
mientras el parser principal avanza.

`prefetch` trae ese patrón a Freedom **sin tocar el worker ni el sandbox**: todo ocurre en
el **lado confiable** (donde la doctrina exige I/O asíncrona/no bloqueante), y el protocolo
del worker no cambia ni un byte. Dos piezas:

1. **Scanner lookahead puro** (`pf_scan`): extrae del HTML crudo (hostil) las referencias
   `<link rel=stylesheet href>` y `<script src>`. Sin I/O, acotado, fail-closed.
2. **Pool de descarga** (`pf_pool_*`): baja una lista de URLs en paralelo (pthreads, tope
   `PF_MAX_THREADS`) a través de **el mismo callback de fetch gateado por política** que
   serviría la petición serial (`tab_fetch_fn`). Un *cache-first take* entrega el resultado
   (moviendo la propiedad) cuando el worker pide esa URL; un miss cae al fetch directo.

El worker sigue pidiendo exactamente lo mismo, en el mismo orden, por el mismo pipe; solo
que la respuesta ya está (o está en vuelo) cuando llega la petición: el tiempo total tiende
al **máximo** de las latencias, no a la suma. El mismo pool paraleliza la descarga de
imágenes de la GUI (`load_images`), cuya lista de URLs ya viene **decidida por política**
(`rd_build`/`rdp_image_decision`), así que ahí no interviene el scanner.

## 2. Contrato de la API

```c
typedef enum pf_kind { PF_STYLESHEET = 0, PF_SCRIPT } pf_kind;

typedef struct pf_ref { pf_kind kind; char *url; } pf_ref;   /* url: dueño la lista */

#define PF_MAX_REFS    64          /* tope anti-DoS del scanner y del pool */
#define PF_MAX_THREADS 4           /* descargas simultáneas máximas */

/* Scanner lookahead. html/len es contenido HOSTIL. Rellena out (dueño de las URLs);
 * out->count <= PF_MAX_REFS. Devuelve 0 (incluso con 0 refs); -1 solo con argumentos
 * NULL. Nunca hace I/O. */
int  pf_scan(const char *html, size_t len, pf_list *out);
void pf_list_free(pf_list *l);

/* Callback de fetch: firma idéntica a tab_fetch_fn (tab.h). El pool lo invoca desde
 * sus hilos; debe ser reentrante y aplicar TODA la política (es el mismo callback
 * que serviría la petición serial). */
typedef int (*pf_fetch_fn)(void *ctx, const char *method, const char *url,
                           const char *body, size_t body_len,
                           int *out_status, char **out_body, size_t *out_len,
                           char **out_ctype);

/* Arranca el pool sobre urls[0..nurls) (se copian; duplicados se deduplican). Lanza
 * min(PF_MAX_THREADS, njobs) hilos que van reclamando trabajos. 0 ok / -1 error
 * (sin hilos: el caller sigue con fetch serial, fail-open de rendimiento). */
int  pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                   pf_fetch_fn fetch, void *ctx);

/* Cache-first take: si url coincide con un trabajo NO consumido, ESPERA a que
 * termine y mueve el resultado al caller (rc = lo que devolvió el fetch; en rc==0
 * el caller es dueño de *body/*ctype). Devuelve 1 (hit, resultado movido) o 0
 * (miss: URL desconocida o ya consumida; el caller hace el fetch directo). */
int  pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,
                  char **body, size_t *len, char **ctype);

/* Une los hilos y libera todo resultado no consumido. Idempotente. Bloquea hasta
 * que los fetches en vuelo terminen (acotados por los timeouts de secure_fetch). */
void pf_pool_finish(pf_pool *p);

/* Adaptador cache-first compartido por todos los frontends (DRY): se instala
 * pf_pooled_fetch como tab_fetch_fn con un pf_gated_fetch de contexto. GET con URL
 * en el pool ⇒ resultado del pool (un prefetch fallido propaga el fallo, nunca se
 * re-busca); POST / miss / pool==NULL ⇒ directo al fetcher interno gateado. El
 * pf_gated_fetch debe sobrevivir al tab_load_full; después el caller re-instala el
 * fetcher interno (nada apunta a memoria muerta). */
typedef struct pf_gated_fetch { pf_fetch_fn inner; void *inner_ctx; pf_pool *pool; } pf_gated_fetch;
int pf_pooled_fetch(void *vctx, const char *method, const char *url, ...);
```

## 3. Semántica del scanner (Dado–Cuando–Entonces)

- **Dado** un HTML con `<link rel="stylesheet" href="a.css">` (atributos en cualquier
  orden, comillas dobles/simples/sin comillas, mayúsculas/minúsculas), **cuando** se
  escanea, **entonces** aparece `{PF_STYLESHEET, "a.css"}` con el valor **crudo** del
  atributo (la resolución/validación la hace el fetcher gateado, igual que con la
  petición del worker).
- **Dado** un `<script src="b.js">`, **entonces** `{PF_SCRIPT, "b.js"}`; un `<script>`
  inline no emite nada.
- **Dado** un `<link>` cuyo `rel` no es `stylesheet` (icon, preload, dns-prefetch...),
  **entonces** NO se emite (fail-closed: prefetch jamás amplía lo que la página podría
  pedir).
- **Dado** texto que *parece* una etiqueta dentro de un comentario `<!-- ... -->`, de un
  `<script>...</script>` inline o de un `<style>...</style>`, **entonces** NO se emite
  (anti-overfetch: el worker jamás pediría eso).
- **Dado** más de `PF_MAX_REFS` referencias o una URL más larga que `URL_MAX_LEN`,
  **entonces** se descartan las excedentes (acotado, anti-DoS).
- **Dado** bytes arbitrarios (fuzz), **entonces** nunca crash/leak/UB y nunca I/O.

## 4. Semántica del pool

- Cada URL única se baja **exactamente una vez** (deduplicación en `start`); el método es
  siempre `GET` (un prefetch nunca tiene cuerpo; los POST del worker van directo al
  fetcher).
- `take` con la URL de un trabajo devuelve **ese** resultado (hit) aunque el fetch haya
  fallado (`rc != 0` se propaga: el caller NO reintenta — mismo resultado que el camino
  serial, sin duplicar peticiones). Un segundo `take` de la misma URL es miss (propiedad
  única: un solo dueño, un solo liberador).
- `finish` libera lo no consumido; tras `finish`, `take` es siempre miss. Sin estado
  global; el pool vive en el stack/struct del caller.

## 5. Garantías de seguridad

1. **Cero política nueva:** el pool no decide nada; ejecuta el MISMO `tab_fetch_fn` que
   la petición serial (ln_resolve, hostblock, net_realm fail-closed, TLS-PQ). Si el
   fetcher rechaza, el prefetch rechaza. Quitar el pool no cambia qué se busca, solo
   cuándo.
2. **El caller filtra por grants:** el orquestador solo encola stylesheets si ese load
   tiene `css_allowed`, y scripts si tiene `net_allowed` (los mismos flags de `OP_LOAD`).
   Con ambos grants apagados no se encola nada (idéntico a hoy).
3. **Overfetch acotado y asumido:** un recurso presente en el DOM que el worker luego NO
   pide (p. ej. `<script type=módulo-desconocido>`, gate de MIME) puede haberse
   prefetcheado igual. Es el mismo trade-off del preload scanner de todo navegador:
   acotado (`PF_MAX_REFS`), solo bajo grants explícitos, por el fetcher gateado. Nunca
   ejecuta ni parsea lo que baja.
4. **El worker no cambia:** sin ring, sin fds nuevos, sin protocolo nuevo. La frontera
   Zero-Trust (seccomp/W^X/namespaces) queda intacta por construcción.
5. **Hilos disciplinados:** los hilos del pool solo tocan el job array (bajo mutex) y el
   fetcher; jamás el estado de la ventana/GUI. El caller no muta el estado que el fetcher
   lee mientras el pool corre (igual que con el fetch serial dentro de `tab_load_full`).

## 6. Matriz de pruebas

`tests/test_prefetch.c` (cmocka): scanner (extracción básica, orden de atributos, comillas,
case, rel-no-stylesheet ignorado, comentarios/script/style opacos, tope de refs, NULL/vacío);
pool con fetcher falso determinista (todas las URLs bajadas exactamente una vez; hit mueve el
cuerpo correcto por URL; concurrencia real probada con `pthread_barrier` de N dentro del
fetcher falso — solo pasa si N corren a la vez; miss en URL desconocida; take-consume; rc de
fallo propagado; finish libera lo no consumido — verificado bajo ASan).
Fuzz: `fuzz/fuzz_prefetch.c` sobre `pf_scan` (bytes arbitrarios; sin crash/leak/UB).

## 7. Fuera de alcance

- Parse incremental / streaming del documento principal (requiere rediseño del protocolo
  `OP_LOAD`; hito propio).
- Prioridades/cancelación de descargas en vuelo (v1: `finish` espera; los timeouts de
  `secure_fetch` acotan).
- Prefetch de imágenes desde el scanner: las imágenes se paralelizan con la lista YA
  decidida por política tras `rd_build` (jamás antes de la decisión por-imagen).
- HTTP/2/3 multiplexing (transporte de libcurl; ortogonal al pool).
