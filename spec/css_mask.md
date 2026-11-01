# css_mask (`cm_`) — `mask` para degradados de alfa (2026-10-20)

CSS Masking 1: la caja se compone con una máscara de alfa. Es lo que hace casi todo diseño
moderno de "borde degradado" y de desvanecidos: `mask-image: linear-gradient(#fff0, #fff 25%)`
(el degradado del héroe de GitHub, que sin máscara se pintaba a plena intensidad) y la técnica
`mask: linear-gradient(#000 0 0) content-box, linear-gradient(#000 0 0); mask-composite: exclude`
(el borde degradado con esquinas redondeadas).

## Alcance v1 (lo demás falla cerrado: la declaración se descarta y se mide en `--dump-css-drops`)

- Hasta **2 capas**. Cada capa: `linear-gradient(...)` con 2..4 paradas (sólo cuenta el ALFA de
  cada color) o `none`. `url()`, `radial-/conic-gradient`, `image-set` ⇒ la declaración entera se
  descarta.
- `mask`, `mask-image`, `mask-composite`, `mask-clip`, `mask-origin` y sus variantes `-webkit-`.
  `-webkit-mask-composite` usa el vocabulario viejo: `source-over`=add, `source-out`=subtract,
  `source-in`=intersect, `xor`=exclude.
- `mask-clip`/`mask-origin` por caja: `border-box` (defecto), `padding-box`, `content-box`.
- `mask-size`, `mask-position`, `mask-repeat` (tanda 83): misma gramática que el fondo (`expand_bg_size`/
  `expand_bg_position`/`interp_bg_repeat2` renombrados a `P_MASK_GEO*`), colocados por el mismo
  `bx_background_layer`. `mask-mode`, `mask-type`: no implementados.
- `mask-image: url(...)` (tanda 83): la capa 0 es una IMAGEN; su URL va al pool (`P_MASK_URL` →
  `pv_box_def.mask_url`), se resuelve y gatea en `render_doc` exactamente como un `background-image`
  (`gate_box_image_url`), se decodifica en el worker (PNG/JPEG/WebP/GIF o SVG vía `svg_raster`) y el
  pintor (`gui/bui_mask_img.c`) usa su alfa. Mientras no carga, o si está bloqueada, la capa es
  transparente: el elemento no se pinta (como Firefox con una imagen no disponible). En la ventana
  las máscaras `data:` son lazy (se decodifican al acercarse al viewport) y se deduplican por URL.

## Contrato (puro, sin I/O)

`cm_expand(prop, val, dst, cap)` emite declaraciones de la cascada y devuelve cuántas; `0` ⇒
descartar. Las palabras por capa son enteros compactos (`cm_encode_layer`): meta = `1 | nst<<4 |
angle<<8`, alfas = 4 bytes (0..255), posiciones = 4 bytes (`pos/4`, 255 = repartidas). `cm_decode_layer`
las revierte. La composición entre las dos capas es `mask-composite` (add/subtract/intersect/
exclude), de la capa 0 sobre la capa 1.

## Dado-Cuando-Entonces

- Dado `mask-image: linear-gradient(#fff0, #fff 25%)`, entonces 1 capa, 2 paradas, alfas {0,255},
  posiciones {repartida, 250}.
- Dado `-webkit-mask: linear-gradient(#000 0 0) content-box, linear-gradient(#000 0 0)` y
  `mask-composite: exclude`, entonces 2 capas opacas, la primera con clip `content-box`, y la
  composición `exclude` (el anillo entre la caja de contenido y la de borde).
- Dado `mask-image: url(data:image/svg+xml;base64,...)` + `mask-size:contain` sobre un `span`
  con `background-color`, entonces se pinta el icono con ese color (sonda `mask-icons`, 0.32 = Firefox).
- Dado `mask-image: none`, entonces 0 capas (reinicia lo anterior).
