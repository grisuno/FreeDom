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
