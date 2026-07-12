# spec/image_decode.md — Decodificado de imágenes (PNG + JPEG + GIF estático)

> Módulo `image_decode` (prefijo `img_`). Lógica **determinista, sin red y sin acceso a
> ficheros**: recibe los *bytes* crudos de una imagen (dato hostil con procedencia) y los
> convierte en píxeles listos para pintar. No descarga nada; el padre ya trajo los bytes por
> `secure_fetch`. No abre el sistema de ficheros; trabaja solo sobre el buffer recibido.

## 0. Por qué existe y dónde corre

Decodificar una imagen es **parsear bytes hostiles** con una librería de formato (libpng +
zlib), históricamente una de las superficies de CVE más fértiles de un navegador. Por eso el
decodificado **no corre en el proceso padre** (el que tiene la conexión Wayland y todo el
estado del navegador), sino **dentro del worker `tab`**, ya confinado con seccomp-bpf
(allowlist fail-closed) + Landlock (sin FS). El padre solo:

1. decide si la imagen se carga (`render_policy`, ya aplicado en `render_doc`),
2. trae los bytes con `secure_fetch` (TLS 1.3 + KE híbrido PQ, https-only, con tope de tamaño),
3. los pasa al worker, que llama a `img_decode` (despacha por *sniffing* a PNG o JPEG),
4. y pinta los píxeles ARGB que el worker devuelve. **El padre nunca decodifica.**

Este módulo es la pieza que corre en el sandbox: por eso es C puro, sin estado global, y
**falla cerrado** ante cualquier byte que no entienda.

### 0.1 Alcance: PNG **y** JPEG (excepción de doctrina, autorizada por el dueño)

Alcance: **PNG, JPEG** (baseline + progressive) **y GIF estático** (§0.2). El resto (WebP —
autorizado por el dueño pero bloqueado por dependencia, ver §5 — y AVIF, NO autorizado) sigue
rechazado con `IMG_ERR_FORMAT` y el orquestador muestra el placeholder con su razón.

JPEG **rompe la doctrina PNG-only** (`libjpeg-turbo` es una dependencia nueva y código que
parsea bytes hostiles — superficie de CVE histórica). Se admite **solo** porque (a) el dueño lo
autorizó explícitamente, y (b) la superficie se contiene con las mismas barreras que ya protegen
a PNG, más unas específicas de libjpeg. El balance se mantiene **Secure by Default** así:

- **Decodifica solo dentro del worker confinado** (seccomp-bpf allowlist fail-closed + Landlock
  sin-FS + namespaces). Un overflow de libjpeg no alcanza FS (Landlock), ni red (`CLONE_NEWNET`
  da pila vacía + no hay syscall `socket`), y la muerte del worker **no** tumba al padre.
- **Fuente solo en memoria** (`jpeg_mem_src`): nunca se compila la ruta `jpeg_stdio_src`, así
  que no existe camino a un descriptor de fichero.
- **Manejador de error con `longjmp`**: el `error_exit` por defecto de libjpeg llama a `exit()`;
  se reemplaza por uno que hace `longjmp`, de modo que un JPEG malformado devuelve
  `IMG_ERR_DECODE` (falla cerrado) en vez de matar el worker abruptamente. `output_message` se
  silencia (sin ruido a stderr).
- **Tope anti-bomba antes del decode completo**: tras `jpeg_read_header` se acotan las
  dimensiones con `img_dimensions_ok` (mismos límites que PNG) **antes** de
  `jpeg_start_decompress`, así un JPEG diminuto no puede forzar una asignación gigante.
- **Salida forzada a un único formato conocido**: se pide `JCS_RGB` (3 canales, presente en todo
  libjpeg — sin depender de extensiones turbo) y se expande a BGRA con alfa opaco (0xFF). No se
  entregan al padre rutas de salida exóticas (colormap/CMYK/YCCK): un JPEG CMYK/YCCK se **rechaza**
  (`IMG_ERR_DECODE`), no se intenta convertir.
- **Sin dependencia transitiva nueva no auditada**: `libjpeg-turbo` ya está presente en el host
  (verificado: `pkg-config --exists libjpeg`, símbolo `jpeg_mem_src`), se enlaza explícito
  (`-ljpeg`) solo donde se decodifica.
- **Privacy by Default intacto**: las imágenes siguen *opt-in* (`Ctrl+I`); JPEG no auto-carga.
- **Fuzzeado** en la misma malla que PNG (`make fuzz-img` sobre `img_decode`/`img_decode_jpeg`).

### 0.2 GIF estático: decoder PROPIO en C puro (2026-07-11, autorizado por el dueño)

GIF entra **sin dependencia nueva**: un decoder propio (~300 líneas de C11 puro) en vez de
`giflib` (historial de CVEs propio, y sus headers no están en este host). Menos superficie
que auditar, y superficie que **nosotros** fuzzeamos — la dirección que la doctrina prefiere.

- **Alcance:** GIF87a/GIF89a, **primera frame solamente** (un GIF animado muestra su primer
  cuadro, estático — la animación necesita un motor de repintado por tiempo que está fuera
  del alcance del painter v1, como `transition`/`animation`). Paleta global y local,
  entrelazado (Adam-de-4-pasadas GIF), transparencia del Graphic Control Extension.
- **LZW acotado:** diccionario máx. 4096 entradas (12 bits, del estándar), expansión por
  cadena de prefijos con tope de longitud = área de la imagen; un código fuera de rango o
  una cadena que excedería el área devuelven `IMG_ERR_DECODE` (falla cerrado, jamás cuelga).
- **Anti-bomba:** dimensiones del Logical Screen Descriptor acotadas con `img_dimensions_ok`
  **antes** de asignar nada (mismos topes que PNG/JPEG). El frame se recorta al lienzo.
- **Salida:** el mismo ARGB32 premultiplicado que PNG/JPEG; píxel transparente ⇒ 0x00000000,
  el resto alfa opaco. Índice de paleta fuera de la tabla ⇒ `IMG_ERR_DECODE`.
- Corre **solo en el worker confinado**, mismo régimen que PNG/JPEG; fuzzeado por
  `make fuzz-img` (mismo harness, `img_decode` sniffea y rutea).

## 1. Tipos

### `img_format` — formato detectado por *sniffing* de cabecera
```c
typedef enum img_format {
    IMG_FMT_UNKNOWN = 0,
    IMG_FMT_PNG = 1,
    IMG_FMT_JPEG = 2,
    IMG_FMT_GIF = 3
} img_format;
```

### `img_status` — códigos de error
```c
typedef enum img_status {
    IMG_OK = 0,
    IMG_ERR_NULL_ARG,   /* puntero requerido NULL */
    IMG_ERR_FORMAT,     /* los bytes no son un PNG (u otro formato no soportado) */
    IMG_ERR_TRUNCATED,  /* cabecera/IHDR incompleto: no hay bytes suficientes */
    IMG_ERR_DIMENSIONS, /* dimensiones nulas o por encima del tope anti-DoS */
    IMG_ERR_DECODE,     /* libpng/libjpeg rechazó el flujo (corrupto / no soportado / CMYK) */
    IMG_ERR_OOM         /* fallo de asignación */
} img_status;
```

### `img_pixels` — bitmap decodificado, dueño de su buffer
```c
typedef struct img_pixels {
    uint32_t  width;
    uint32_t  height;
    uint32_t  stride;  /* bytes por fila == width*4 (empaquetado, sin padding) */
    uint8_t  *data;    /* width*height*4 bytes; ver formato abajo; lo libera img_pixels_free */
} img_pixels;
```

**Formato de los píxeles:** ARGB32 premultiplicado *nativo de Cairo* en little-endian, es
decir cada píxel es un `uint32_t` `0xAARRGGBB` y en memoria los bytes van **B, G, R, A**; el
color está **premultiplicado por alfa** (lo que `CAIRO_FORMAT_ARGB32` espera). Así el padre
envuelve el buffer en una `cairo_surface_t` y lo pinta sin reconvertir. El módulo **no incluye
`cairo.h`**: solo respeta su layout documentado, para no arrastrar Cairo al sandbox.

## 2. Límites anti-DoS

```c
#define IMG_MAX_DIM     8192u                 /* lado máximo en píxeles */
#define IMG_MAX_PIXELS  (16u * 1024u * 1024u) /* área máxima: 16 Mpx -> 64 MiB ARGB */
```
Una imagen puede declarar dimensiones enormes en un IHDR diminuto (*decompression bomb*).
`img_png_dimensions` lee el IHDR (offset fijo, sin descomprimir nada) y `img_dimensions_ok`
rechaza antes de decodificar todo lo que exceda `IMG_MAX_DIM` por lado o `IMG_MAX_PIXELS` de
área. El cálculo `width*height*4` se hace con comprobación de desbordamiento.

## 3. Funciones (puras salvo `img_decode*`, que solo asignan memoria)

```c
/* Detecta el formato por la firma de cabecera. PNG = 0x89 'PNG'... ; JPEG = FF D8 FF.
 * NULL o longitud insuficiente => UNKNOWN. */
img_format img_sniff(const uint8_t *bytes, size_t len);

/* Lee ancho/alto del IHDR de un PNG sin descomprimir. No valida más allá de la firma + IHDR.
 * bytes/ w/h NULL => IMG_ERR_NULL_ARG; no-PNG => IMG_ERR_FORMAT; corto => IMG_ERR_TRUNCATED. */
img_status img_png_dimensions(const uint8_t *bytes, size_t len,
                              uint32_t *out_w, uint32_t *out_h);

/* 1 si (w,h) es no nulo y cabe en los topes anti-DoS (lado y área, sin overflow); si no, 0. */
int img_dimensions_ok(uint32_t w, uint32_t h);

/* Encaje preservando aspecto: el mayor (dw,dh) <= (box_w,box_h) con dw/dh == iw/ih. Pura.
 * Entradas <= 0 o degeneradas => (0,0). No agranda por encima del original solo si
 * box es mayor: hace 'fit' (puede ampliar o reducir según la caja); ver tests. */
void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,
             double *out_w, double *out_h);

/* Decodifica un PNG a img_pixels (ARGB32 premultiplicado, ver §1). Rechaza no-PNG, truncado,
 * dimensiones fuera de tope (antes de decodificar) y flujos corruptos. En IMG_OK, *out es
 * dueño de data y debe liberarse con img_pixels_free. Reentrante: sin estado global. */
img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out);

/* Decodifica un JPEG (baseline/progressive) a img_pixels (ARGB32, alfa opaco 0xFF). Lee la
 * cabecera, acota dimensiones ANTES del decode (anti-bomba), decodifica a RGB y lo expande a
 * BGRA. Rechaza no-JPEG, dimensiones fuera de tope, CMYK/YCCK y flujos corruptos (IMG_ERR_DECODE
 * vía longjmp; nunca llama exit()). En IMG_OK, *out es dueño de data. Reentrante. */
img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out);

/* Despachador: hace sniff y enruta a img_decode_png / img_decode_jpeg; formato desconocido =>
 * IMG_ERR_FORMAT. Es la única entrada que usa el worker (tab). Falla cerrado. */
img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out);

/* Libera data y pone la estructura a cero. Idempotente; seguro sobre NULL y sobre cero. */
void img_pixels_free(img_pixels *p);

/* Nombre corto y estable en inglés del formato (para salida agent-friendly). Nunca NULL. */
const char *img_format_name(img_format f);
```

## 4. Garantías de seguridad

- **Falla cerrado.** Cualquier duda (firma, IHDR, dimensiones, error de libpng) devuelve un
  `IMG_ERR_*` y **no** produce un bitmap parcial: `out` queda a cero y no se filtra memoria.
- **Sin red, sin FS.** El módulo solo lee del buffer de entrada y asigna memoria de salida; no
  abre sockets ni ficheros, por lo que es compatible con la allowlist seccomp del worker
  (`mmap/munmap/mprotect/brk` permitidos; nada de `open*`/`socket`).
- **Anti-bomba.** Las dimensiones se acotan **antes** de decodificar (PNG: IHDR; JPEG:
  `jpeg_read_header`, antes de `jpeg_start_decompress`), de modo que un fichero comprimido
  diminuto no puede forzar una asignación gigantesca.
- **Reentrante.** Sin estado global mutable; el manejo de errores de libpng usa la API
  simplificada (sin `longjmp`) y el de libjpeg un `jpeg_error_mgr` con `longjmp` **local a la
  llamada** (en la pila de `img_decode_jpeg`). Dos decodificados concurrentes no interfieren.
- **No llama a `exit()`.** El `error_exit` por defecto de libjpeg aborta el proceso; se
  reemplaza por `longjmp`, así un JPEG hostil falla cerrado sin tumbar al worker.
- **Dueño único.** `img_pixels` posee `data`; `img_pixels_free` es el único liberador y es
  idempotente.

### 4.1 Dado-Cuando-Entonces (JPEG)

- **Dado** bytes con firma `FF D8 FF`, **cuando** `img_sniff`, **entonces** `IMG_FMT_JPEG`.
- **Dado** un JPEG válido NxM dentro de los topes, **cuando** `img_decode`/`img_decode_jpeg`,
  **entonces** `IMG_OK`, `width=N`, `height=M`, `stride=N*4`, alfa de todo píxel = 0xFF.
- **Dado** un JPEG que declara dimensiones por encima de `IMG_MAX_*`, **cuando** decode,
  **entonces** `IMG_ERR_DIMENSIONS` **antes** del decode completo, sin asignar el bitmap.
- **Dado** un JPEG truncado/corrupto o CMYK/YCCK, **cuando** decode, **entonces**
  `IMG_ERR_DECODE`, `*out` a cero, sin fugas, sin `exit()`.
- **Dado** un PNG, **cuando** `img_decode` (despachador), **entonces** enruta a la ruta PNG e
  `IMG_OK` (paridad con el comportamiento previo).

### 4.2 Dado-Cuando-Entonces (GIF, §0.2)

- **Dado** un GIF89a válido con paleta global, **cuando** `img_decode_gif`, **entonces**
  `IMG_OK` y los píxeles ARGB coinciden con la paleta (alfa 0xFF).
- **Dado** un GIF con Graphic Control Extension y color transparente, **cuando** decode,
  **entonces** ese índice produce 0x00000000 (transparente premultiplicado).
- **Dado** un GIF entrelazado, **cuando** decode, **entonces** las filas quedan en orden
  visual correcto (des-entrelazado de 4 pasadas).
- **Dado** un GIF que declara dimensiones sobre `IMG_MAX_*`, **cuando** decode, **entonces**
  `IMG_ERR_DIMENSIONS` antes de asignar el bitmap.
- **Dado** un GIF truncado, con código LZW fuera de rango, o con índice de color fuera de la
  paleta, **cuando** decode, **entonces** `IMG_ERR_TRUNCATED`/`IMG_ERR_DECODE`, `*out` a cero,
  sin fugas, sin cuelgues (expansión LZW topada por el área del frame).
- **Dado** un GIF animado (varias Image Descriptors), **cuando** decode, **entonces** `IMG_OK`
  con la PRIMERA frame solamente.

## 5. Fuera de alcance

- WebP (lossless + lossy): **soportado desde 2026-07-11** (`IMG_FMT_WEBP`). Usa `libwebp` vía
  `WebPGetInfo` + `WebPDecodeBGRAInto` (fuente en memoria, dimensiones acotadas antes del
  decode, salida BGRA premultiplicada). Se detecta por la cabecera `RIFF....WEBP`. AVIF/AV1:
  **NO autorizado**, rechazado.
- GIF: animación (solo la primera frame, ver §0.2), disposal methods, loops.
- JPEG CMYK/YCCK (4 canales) y *arithmetic coding*: rechazados (`IMG_ERR_DECODE`); no se
  intenta conversión de espacio de color exótica.
- EXIF (orientación), perfiles ICC y metadatos: ignorados; la imagen se pinta tal cual decodifica.
- PNG animado (APNG), color management/ICC, gamma avanzada: se decodifica el primer frame con
  conversión a RGBA de 8 bits; perfiles se ignoran.
- Reescalado de alta calidad: el escalado de pintado lo hace Cairo en el padre; aquí solo se
  calcula la geometría de encaje (`img_fit`).
- La descarga de los bytes (la hace `secure_fetch` en el padre) y el transporte por IPC (lo
  hace `tab`).
