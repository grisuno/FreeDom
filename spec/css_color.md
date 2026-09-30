# spec/css_color.md — Parser puro de colores CSS

> Módulo `css_color` (prefijo `cc_`). Lógica **pura, sin I/O, sin estado global**: convierte un
> token de color CSS (dato hostil con procedencia) en un RGB de 8 bits por canal, o falla cerrado.
> No pinta nada; solo decodifica. Metodología: SDD + TDD.

## 0. Por qué existe

El render quiere mostrar los colores del autor (`color:` en un `style` en línea, `<font color>`),
pero el valor es una cadena arbitraria de un documento remoto. Decodificar un color es lógica pura,
auditable sin Cairo ni red, y se reutiliza en exactamente un sitio probado: `page_view` lo invoca al
extraer el color de un nodo, y el resto del pipeline transporta el resultado ya validado. Falla
cerrado: un token no reconocido **no** produce un color (el llamante usa el color del tema).

## 1. Tipos

```c
typedef struct cc_rgb { unsigned char r, g, b; } cc_rgb;

typedef enum cc_status {
    CC_OK = 0,
    CC_ERR_NULL_ARG,   /* token u out era NULL */
    CC_ERR_SYNTAX      /* el token no es un color reconocido (falla cerrado) */
} cc_status;
```

## 2. API (pura, reentrante)

```c
cc_status cc_parse(const char *token, cc_rgb *out);
int       cc_pack(cc_rgb c);            /* 0x00RRGGBB */
cc_rgb    cc_unpack(int packed);        /* inverso de cc_pack; bits altos ignorados */
```

### `cc_parse`
- `token == NULL` o `out == NULL` → `CC_ERR_NULL_ARG`.
- Se recortan espacios ASCII al principio y al final sobre una copia acotada; un token que no quepa
  en el buffer interno → `CC_ERR_SYNTAX` (nunca se trunca un color a otro).
- Reconoce, **sin distinguir mayúsculas/minúsculas**:
  - **Hex:** `#rgb`, `#rgba`, `#rrggbb`, `#rrggbbaa`. El canal alfa se parsea (validación) pero se
    descarta: Freedom pinta texto opaco. `#rgb` se expande duplicando cada dígito (`#f00` → `ff0000`).
  - **Funcional:** `rgb(r,g,b)` y `rgba(r,g,b,a)`. Cada componente es un entero `0..255` **o** un
    porcentaje `0%..100%` (se redondea al entero más cercano). El alfa de `rgba` se parsea pero se
    descarta. Espacios alrededor de comas y paréntesis permitidos; separación por comas (sintaxis
    CSS clásica). Los componentes se acotan a `[0,255]` / `[0%,100%]`; fuera de rango → `CC_ERR_SYNTAX`.
  - **Funcional moderno (CSS Color 4, espacio + barra):** `rgb(R G B [/ A])`, `rgba(R G B [/ A])`,
    `hsl(H S L [/ A])`, `hsla(H S L [/ A])`, donde los componentes se separan por espacios ASCII
    (uno o más) y el alfa —número o porcentaje— va tras una única `/` top-level. `rgb()` y `rgba()`
    (y `hsl()`/`hsla()`) son alias: la aridad la decide la presencia de alfa, no el nombre. Mezclar
    comas con `/` es inválido (falla cerrado). Motivación medida: `rgb(0 0 0 / 75%)` y
    `rgb(229 233 240 / 50%)` son el idioma de overlays y bordes de las páginas reales (jkanime,
    slashdot); rechazarlos pierde la declaración entera.
    - Dado `rgb(0 0 0 / 75%)`, cuando se parsea, entonces `CC_OK` con `(0,0,0)`.
    - Dado `rgb(229 233 240 / 50%)`, cuando se parsea, entonces `CC_OK` con `(229,233,240)`.
    - Dado `hsl(0 0% 0% / 50%)`, cuando se parsea, entonces `CC_OK` con `(0,0,0)`.
    - Dado `rgb(255 0 0)` (sin alfa), cuando se parsea, entonces `CC_OK` con `(255,0,0)`.
    - Dado `rgb(0, 0, 0 / 50%)` (comas + barra), cuando se parsea, entonces `CC_ERR_SYNTAX`.
    - Dado `rgb(0 0)` o `rgb(0 0 0 /)` o `rgb(0 0 0 / /)`, cuando se parsea, entonces
      `CC_ERR_SYNTAX`.
    - Dado `rgba(10, 20, 30, 0.5)` (legado con comas), cuando se parsea, entonces `CC_OK` con
      `(10,20,30)` — sin cambios.
  - **Nombres:** las palabras clave de color CSS (conjunto extendido) más `transparent`. `transparent`
    no tiene color visible (alfa 0): se rechaza con `CC_ERR_SYNTAX` para que el render use el tema en
    vez de pintar texto invisible (falla cerrado, corrección visual).
- Cualquier otra cosa (`hwb(...)`, `var(...)`, nombre desconocido, basura) →
  `CC_ERR_SYNTAX`. La lista de nombres se consulta por **búsqueda binaria** sobre una tabla ordenada
  (dato de referencia, no números mágicos).
- En `CC_OK`, `*out` queda poblado; en error, `*out` no se toca.

### `cc_pack` / `cc_unpack`
- `cc_pack` empaqueta a un entero `0x00RRGGBB` (no negativo) apto para transporte y para el centinela
  "sin color" `-1` que usa el pipeline. `cc_unpack` recupera el `cc_rgb` (ignora los bits sobre 24).

## 3. Garantías

- **Pureza / Zero Trust:** sin I/O, sin estado global, reentrante; el token es dato hostil.
- **Determinista:** misma entrada → misma salida (testeable, agent-friendly).
- **Falla cerrado:** ante cualquier duda, `CC_ERR_SYNTAX`; nunca un color arbitrario o truncado.
- **Sin asignación dinámica:** opera sobre buffers de pila acotados.
- Objetivo de auditoría: `-fsanitize=address,undefined` limpio.

## 4. Tabla de estados

| `cc_status` | Condición |
| :-- | :-- |
| `CC_OK` | Token reconocido; `*out` es el color opaco. |
| `CC_ERR_NULL_ARG` | `token` u `out` es `NULL`. |
| `CC_ERR_SYNTAX` | Vacío, no cabe, fuera de rango, `transparent`, o sintaxis no soportada. |

## 5. Fuera de alcance

- `hwb()`, `lab()`, `color()`, `color-mix()`, `currentColor`, `var()`, palabras `inherit`/`initial`.
- La palabra `none` como componente (CSS Color 4 la permite; aquí falla cerrado a tema).
- Composición de alfa: Freedom pinta opaco; el alfa se valida pero no se aplica.
- La extracción del token desde el documento (qué declaración `color:` aplica): la hace `page_view`.

## `lab()`, `lch()`, `oklab()`, `oklch()` (CSS Color 4 §8–9, 2026-09-29)

Tailwind v4 escribe toda su paleta en `oklch()`: huggingface.co perdía ~765 declaraciones
de color (fondos de tarjetas incluidos, así que su texto blanco quedaba sobre blanco).

- Solo sintaxis separada por espacios (estas funciones no tienen forma legacy con comas),
  exactamente 3 componentes, `/ alfa` opcional (validado y descartado, como en `rgb()`).
- Componentes: `<number>`, `<percentage>` o `none` (= 0). Referencias del 100 %:
  L = 1 (ok*) / 100 (lab/lch); a, b = 0.4 / 125; C = 0.4 / 150. El tono admite
  `deg`/`grad`/`rad`/`turn` o número (grados); un porcentaje en el tono es inválido.
- `oklab`/`oklch` → sRGB lineal con las matrices de Ottosson (las de la spec);
  `lab`/`lch` son CIE Lab **D50** → XYZ D50 → Bradford a D65 → sRGB lineal.
- Recorte al gamut sRGB **por canal** (clamp). CSS Color 4 §13.2 pide reducción de croma;
  difiere solo en colores que sRGB no puede mostrar (aproximación documentada).
- Referencias verificadas en tests: `oklch(70.7% .022 261.325)` = `#99a1af` (gray-400 de
  Tailwind v4), `oklch(62.8% 0.2577 29.23)` = `lab(54.29 80.8 69.89)` = rojo sRGB.
