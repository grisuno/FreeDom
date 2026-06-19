# spec/image_decode.md — Decodificado de imágenes (PNG)

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
3. los pasa al worker, que llama a `img_decode_png`,
4. y pinta los píxeles ARGB que el worker devuelve. **El padre nunca decodifica.**

Este módulo es la pieza que corre en el sandbox: por eso es C puro, sin estado global, y
**falla cerrado** ante cualquier byte que no entienda.

Alcance de este hito: **solo PNG**. Cualquier otro formato (JPEG/WebP/GIF) se rechaza con
`IMG_ERR_FORMAT` y el orquestador muestra el placeholder con su razón. Añadir más formatos
sería añadir dependencias y superficie de ataque nuevas (contra la doctrina), y queda fuera.

## 1. Tipos

### `img_format` — formato detectado por *sniffing* de cabecera
```c
typedef enum img_format {
    IMG_FMT_UNKNOWN = 0,
    IMG_FMT_PNG = 1
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
    IMG_ERR_DECODE,     /* libpng rechazó el flujo (corrupto / no soportado) */
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

## 3. Funciones (puras salvo `img_decode_png`, que solo asigna memoria)

```c
/* Detecta el formato por la firma de cabecera. NULL o longitud insuficiente => UNKNOWN. */
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
- **Anti-bomba.** Las dimensiones se acotan **antes** de decodificar (IHDR), de modo que un
  PNG comprimido diminuto no puede forzar una asignación gigantesca.
- **Reentrante.** Sin estado global mutable; el manejo de errores de libpng usa `longjmp`
  local a la llamada. Dos decodificados concurrentes no interfieren.
- **Dueño único.** `img_pixels` posee `data`; `img_pixels_free` es el único liberador y es
  idempotente.

## 5. Fuera de alcance

- Otros formatos (JPEG/WebP/GIF/AVIF): rechazados (`IMG_ERR_FORMAT`).
- PNG animado (APNG), color management/ICC, gamma avanzada: se decodifica el primer frame con
  conversión a RGBA de 8 bits; perfiles se ignoran.
- Reescalado de alta calidad: el escalado de pintado lo hace Cairo en el padre; aquí solo se
  calcula la geometría de encaje (`img_fit`).
- La descarga de los bytes (la hace `secure_fetch` en el padre) y el transporte por IPC (lo
  hace `tab`).
