# spec: box_blur (`bb_`) — desenfoque gaussiano de una máscara A8

## Por qué existe (medido)

`box-shadow` se pintaba como cuatro anillos concéntricos al 30 % de opacidad, sin
importar el alfa del color ni el radio de desenfoque: la sombra sutil de un *design
system* (`0 4px 8px rgba(0,0,0,.04)`, Hugo Stack, GitHub Primer, Tailwind) salía como
un borde gris grueso alrededor de cada tarjeta (medido contra Firefox en
andreagrandi.it). CSS Backgrounds 3 §7.1 define el desenfoque como un gaussiano de
desviación estándar **blur/2**.

## Contrato

```c
int bb_box_sizes(double sigma, int sizes[3]);
int bb_blur_a8(unsigned char *buf, int w, int h, int stride, double sigma);
```

- `bb_box_sizes`: los tres anchos de caja (impares) cuya convolución aproxima un
  gaussiano de `sigma` (W3C/Kovesi: `w_ideal = sqrt(12σ²/3 + 1)`). Devuelve 0 si
  `sigma` no es finito o es `<= 0` (no hay desenfoque).
- `bb_blur_a8`: aplica tres pasadas de caja en cada eje sobre la máscara de 8 bits
  `buf` (`w`×`h`, `stride` bytes por fila), en sitio. Los píxeles fuera del buffer
  valen 0. Devuelve 0 si no hizo nada (σ ≤ 0), 1 si desenfocó, -1 ante argumentos
  inválidos (NULL, dimensiones ≤ 0, `stride < w`, `w·h` mayor que `BB_MAX_PIXELS`).
  Puro, sin I/O; una única asignación de trabajo (una fila/columna), liberada antes
  de volver.

## Dado-Cuando-Entonces

- **Dado** un impulso de 255 en el centro y σ = 2 **entonces** la masa total se
  conserva (±2 % por redondeo), el pico baja y el resultado es simétrico.
- **Dado** σ = 0 **entonces** el buffer queda idéntico.
- **Dado** un buffer uniforme lejos de los bordes **entonces** el interior no cambia.
- **Dado** `w·h > BB_MAX_PIXELS` **entonces** -1 y el buffer intacto (anti-DoS: el
  llamador pinta la sombra sin desenfocar).

## Fuera de alcance

Desenfoque de color/RGBA (las sombras son una máscara × un color), `filter: blur()`
(tiene su propio camino) y el recorte de la sombra (lo hace el pintor).

## Rectangulo con tinta (2026-10-24)
`bb_ink_rect` devuelve la caja de los pixeles con alfa > 0 de una superficie ARGB32, ensanchada por el
alcance del filtro (suma de los tres radios de caja) y acotada a la superficie. Fuera de ella el desenfoque
deja 0, asi que desenfocar solo ese rectangulo es identico a desenfocar todo. El GUI lo usa en
`bui_gaussian_blur_surface`: el grupo con `filter: blur()` crea una superficie del tamano del recorte (hasta
4096 x 4096) y antes pagaba tres pasadas por cada pixel de cada canal aunque el elemento fuera pequeno o
estuviera vacio. Discord (cientos de `blur(30..130px)`): pintado 10.5 s -> ~0.1 s por cuadro; PNG identico.

## Pasadas sin división y por filas (tanda 95)

**Medido** con `tools/guiscroll.py` en la ventana real: el «glow» del hero de GitHub (una caja de
936×528 con `filter: blur(42px)`) costaba **57–116 ms por cuadro** mientras estaba en pantalla, y
la sombra de 1 px de un panel de es.wikipedia 24 ms en su primer cuadro. Microbenchmark sobre el
tamaño real del glow (1080×672, 4 canales, σ = 42): **116 → 15 ms**, con salida idéntica.

- **Sin división por píxel.** `floor((sum + bw/2) / bw)` se calcula como `(n·m) >> 32` con
  `m = floor(2³²/bw) + 1`, exacto para todo `n < 2³²/bw` (Granlund–Montgomery). Aquí
  `n <= 256·bw`, así que basta `bw < BB_BOX_MAX` (4096): un sigma cuya caja llegue a ese ancho
  devuelve -1 (fail-closed; los llamadores ya acotan el radio a 256).
- **Pasada vertical por filas** (una suma por columna, acceso secuencial) en vez de columna a
  columna (un byte por línea de caché). Memoria de trabajo: una copia `w·h` (antes una fila).
- **Una caja de ancho 1 es la identidad** y se salta (σ < ~0,6: `blur: 1px` en una sombra).
- Misma aritmética: `test_blur_matches_reference_byte_for_byte` compara byte a byte contra la
  implementación anterior, copiada en el test como oráculo, sobre máscaras aleatorias, strides
  con relleno y seis sigmas (hasta 130, cajas de ~150 px).
- Se probó y se **descartó** desenfocar a resolución reducida para sigmas grandes (lo que hacen
  Skia/Firefox): con las pasadas ya sin división solo ganaba 1,5× y se apartaba hasta 5/255 de la
  exacta. No compensa una aproximación.
