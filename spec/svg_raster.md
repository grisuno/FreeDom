# svg_raster (`sr_`) — SVG como formato de imagen (2026-10-31, tanda 83)

## 0. Por qué

`<img src="logo.svg">`, `background-image: url(icon.svg)` y los `data:image/svg+xml,...`
son la forma más común de logos e iconos de la Web actual. Hasta la tanda 83 Freedom solo
pintaba el `<svg>` **en línea**: un SVG servido como imagen caía en `IMG_ERR_FORMAT` y se
veía el placeholder (o nada).

## 1. Contrato

```c
int        sr_sniff(const uint8_t *bytes, size_t len);
img_status sr_rasterize(const uint8_t *bytes, size_t len, img_pixels *out);
```

- `sr_sniff`: 1 si, saltando BOM UTF-8, espacios, la declaración `<?xml ...?>`, comentarios
  `<!-- -->` y un `<!DOCTYPE ...>`, el primer elemento es `<svg`. Mira a lo sumo
  `SR_SNIFF_MAX` bytes. Puro.
- `sr_rasterize`: parsea con `sv_parse` (el mismo parser puro y fuzzeado del SVG en línea) y
  pinta las formas con `svp_draw_ex` sobre una superficie Cairo **en memoria** del tamaño
  intrínseco (`width`/`height`, o el `viewBox`, o 300×150), acotado a `SR_MAX_DIM` por lado
  (escala uniforme). Salida: ARGB32 premultiplicado, el mismo `img_pixels` que PNG/JPEG.

## 2. Dónde corre

Dentro del **worker confinado**, como cualquier decodificador de imagen: el padre trae los
bytes y el worker los convierte en píxeles (`img_decode` falla con formato desconocido ⇒
`sr_sniff` ⇒ `sr_rasterize`). Los `data:` de imagen (base64 **o** percent-encoded) se
decodifican también en el worker (`du_decode`); el padre solo valida la forma.

## 3. Garantías de seguridad

- **Cero red, cero archivos:** la gramática de `svg_render` no tiene forma de URL
  (`<image>`, `<use href>`, `url()` no existen), así que la imagen no puede pedir nada.
- **Sin texto:** `<text>` se omite al rasterizar en el worker. Pintar texto con Cairo abre
  fontconfig (archivos del sistema) y el worker no tiene ni debe tener ese acceso. Un SVG de
  imagen con texto pierde el texto; un logo de paths (el caso común) sale entero.
- **Topes:** entrada ≤ `SV_MAX_INPUT`, superficie ≤ `SR_MAX_DIM`² y dentro de
  `img_dimensions_ok`. Fallar cerrado: cualquier error ⇒ `IMG_ERR_*`, sin píxeles parciales.
- Cairo de imagen usa solo memoria (pixman detecta CPU por `cpuid` en x86-64).

## 4. Dado-Cuando-Entonces

- Dado `<svg width="20" height="10"><rect width="20" height="10" fill="red"/></svg>`, cuando
  se rasteriza, entonces 20×10 y el píxel central es rojo opaco.
- Dado `<?xml version="1.0"?><!-- c --><svg viewBox="0 0 40 20">…`, entonces `sr_sniff` es 1 y
  el tamaño es 40×20.
- Dado un PNG o `<html>`, entonces `sr_sniff` es 0.
- Dado `<svg width="100000" height="10">`, entonces se escala para caber en `SR_MAX_DIM`.
- Dado bytes basura o un `<svg>` vacío, entonces `IMG_ERR_DECODE` y `out` en cero.

## 5. Fuera de alcance

Texto, `<image>`, `<use>`, filtros, máscaras y gradientes SVG (lo que `svg_render` no
modela). Rasterizado a la densidad de pantalla (se pinta a 1×, como Firefox a DPR 1).
