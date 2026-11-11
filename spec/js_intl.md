# spec: js_intl (`ji_`) — formato de numeros, fechas y listas (ECMA-402, locale fijo)

## Problema

QuickJS-ng se compila sin ICU. El `Intl` anterior era un stub que solo evitaba el
`ReferenceError`: `NumberFormat.format` devolvia el numero crudo (`1234567.891`, sin
agrupar), `DateTimeFormat.format` devolvia `Date#toString()` ignorando TODAS las opciones y
`RelativeTimeFormat` devolvia `"3 day"`. Eso es texto que la pagina PINTA: contadores,
precios, fechas ("Jan 5, 2026"), "3 days ago". Firefox y V8 lo formatean; Freedom mostraba
otra cosa.

## Contrato

`int ji_install(js_context *ctx)` — instala `Intl` completo y redefine los metodos
`toLocale*` de `Number`, `BigInt` y `Date` para que deleguen en el. Lo llama `jd_install`.
Devuelve 0 o -1.

**Locale fijo `en-US`, zona fija `UTC`** (Zero Knowledge / anti-fp): cualquier locale pedido
se acepta y se formatea como `en-US`; `resolvedOptions()` responde `en-US`/`latn`/`gregory`/
`UTC`. Una zona horaria pedida distinta de `UTC` se ignora (el worker corre con `TZ=UTC0`):
no se filtra ni se inventa la zona real.

### Dado-Cuando-Entonces (salidas = las de Firefox/V8 para `en-US`)

- **NumberFormat.** `format(1234567.891)` → `1,234,567.891`; por defecto 0–3 decimales con
  redondeo half-expand. Opciones: `minimumFractionDigits`/`maximumFractionDigits`,
  `minimumIntegerDigits`, `minimum/maximumSignificantDigits`, `useGrouping`,
  `style: 'percent'` (`0.256` → `26%`), `style: 'currency'` (`$1,234.50`; simbolos USD/EUR/
  GBP/JPY/..., resto por codigo; `currencyDisplay: 'code'|'name'`), `style: 'unit'`
  (`5 km`, `unitDisplay: 'long'` → `5 kilometers`), `notation: 'compact'` (`1.2K`, `3.4M`,
  `compactDisplay: 'long'` → `1.2 thousand`), `signDisplay`. `NaN` → `NaN`, infinito → `∞`.
  `formatToParts` devuelve partes tipadas cuya concatenacion ES `format()`.
- **DateTimeFormat.** Sin opciones → `1/1/1970`. Componentes `weekday`/`era`/`year`/`month`/
  `day`/`hour`/`minute`/`second`/`fractionalSecondDigits`/`timeZoneName` y `hour12`/
  `hourCycle`; atajos `dateStyle`/`timeStyle`. Ejemplos: `{month:'long',year:'numeric'}` →
  `January 1970`; `{dateStyle:'medium'}` → `Jan 1, 1970`; `{dateStyle:'full'}` →
  `Thursday, January 1, 1970`; `{timeStyle:'short'}` → `12:00 AM`; fecha y hora se unen con
  `, ` (con `dateStyle` `long`/`full`, ` at `). Fecha invalida → `RangeError`.
  `formatToParts`, `formatRange`.
- **`toLocale*`.** `Date#toLocaleString()` → `1/1/1970, 12:00:00 AM`; `toLocaleDateString()`
  → `1/1/1970`; `toLocaleTimeString()` → `12:00:00 AM`; `Number#toLocaleString()` agrupa.
- **RelativeTimeFormat.** `format(-3,'day')` → `3 days ago`; `format(1,'hour')` →
  `in 1 hour`; `numeric:'auto'` → `yesterday`/`tomorrow`/`now`/`last week`...; `style:
  'short'|'narrow'` → `3 days ago` / `3d ago`... (formas de CLDR para `en`).
- **PluralRules.** Cardinal `one`/`other`; `type:'ordinal'` → `one`/`two`/`few`/`other`.
- **ListFormat.** `['a','b','c']` → `a, b, and c`; `type:'disjunction'` → `a, b, or c`;
  `type:'unit'`; `style:'short'|'narrow'`.
- **Collator.** `compare` ordena sin distinguir mayusculas primero (`a` < `B`), `numeric`
  compara tiradas de digitos por valor, `sensitivity:'base'|'accent'` ignora mayusculas.
- `Locale`, `DisplayNames`, `Segmenter`, `getCanonicalLocales`, `supportedLocalesOf`,
  `supportedValuesOf`: como antes (se mudan de `js_dom.c` sin cambio de conducta).

## Garantias

- Codigo puro: sin reloj, sin red, sin zona horaria ni locale del sistema. Misma entrada →
  misma salida en cualquier maquina (identidad normalizada).
- Acotado: los digitos pedidos se recortan a los rangos de ECMA-402 (0–100 fraccion, 1–21
  significativos, 1–21 enteros); fuera de rango → `RangeError`, nunca un bucle largo.

## Fuera de alcance

Otros locales (meses en espanol, separador decimal `,`), calendarios no gregorianos, zonas
horarias reales, `DurationFormat`, notacion cientifica/ingenieria, monedas con nombres en
plural completos.
