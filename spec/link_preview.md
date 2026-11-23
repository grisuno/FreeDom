# link_preview (`lp_`) — adónde va un clic, antes del clic

## Por qué

Al pasar el puntero sobre un enlace, Freedom mostraba en la barra inferior el `href` **crudo**
del documento: `from?site=hackaday.com` en Hacker News. Eso no dice adónde irá el clic (Firefox
muestra la URL absoluta resuelta), y un `href` hostil llegaba al pintor sin sanear: un
U+202E (RTL override) invierte lo que el usuario lee, un `\n` o un byte de control rompe la
línea, y un `javascript:` se veía como si fuera un enlace normal aunque el clic lo bloquea.

La barra de estado es una superficie **anti-phishing**: tiene que decir la verdad que decide
`ln_resolve`, no lo que el autor escribió.

## Contrato (puro: sin I/O, sin Cairo, sin estado)

```c
lp_status lp_describe(const char *base, const char *href, lp_preview *out);
```

- `LP_EINVAL` si `out` es NULL. Con `href` NULL la decisión es la de `ln_resolve` (bloqueado).
- La decisión es **siempre** la de `ln_resolve(base, href)`: el preview no tiene política propia.
- `out->kind`:
  - `LP_NAVIGATE` — `text` = el destino resuelto (`https://...`, o `file://` + ruta local).
  - `LP_SAME_DOCUMENT` — `text` = la URL de la página (`base`, sin su fragmento) + `#frag`
    si lo hay. Sin base: `#frag`.
  - `LP_BLOCKED` — `text` = `"Blocked (<motivo>): <href crudo saneado>"`, con el motivo de
    `ln_block_reason_text`.
- `out->host_off` / `out->host_len`: el tramo del host dentro de `text` (sin userinfo ni
  puerto) para que el pintor lo resalte, como en el omnibox; `host_len == 0` si no hay host
  (archivo local, bloqueado, fragmento sin base).

### Saneado (todo byte que llega a `text`)

- ASCII imprimible (0x21–0x7E) pasa tal cual; el espacio también.
- Cualquier otro byte (controles, DEL, todo byte ≥ 0x80 —incluidos U+202E y homógrafos de
  otros alfabetos—) se escribe `%XX` en mayúsculas. Es una representación válida de la misma
  URL y hace visible lo invisible: un host con una «а» cirílica se lee `%D0%B0`, no `a`.
- `text` cabe siempre en `LP_TEXT_MAX` (incluido el NUL). Si no cabe, se corta en el **medio
  del camino** con `...` conservando esquema + host enteros y el final del camino; si ni el
  host cabe, se corta al final con `...`. El host nunca se corta por la mitad salvo en ese
  último caso, y entonces `host_len` se acota al tramo visible.

## Garantías

- Ningún byte < 0x20, 0x7F ni ≥ 0x80 aparece en `text`.
- `host_off + host_len <= strlen(text)`.
- El preview y el clic coinciden: `LP_NAVIGATE` ⇔ `ln_resolve` da `LN_NAVIGATE`.

## Fuera de alcance

- Mostrar IDN decodificado (Firefox enseña Unicode para un solo alfabeto y punycode para
  mezclas): aquí todo no-ASCII queda percent-encoded. Más feo, nunca engañoso.
- El ancho en píxeles: el pintor recorta con su propia medida; este módulo solo acota bytes.

## Dado-Cuando-Entonces

- Dado `base = https://news.ycombinator.com/news` y `href = from?site=hackaday.com`, cuando se
  describe, entonces `text = https://news.ycombinator.com/from?site=hackaday.com` y el host es
  `news.ycombinator.com`.
- Dado `href = javascript:alert(1)`, entonces `kind = LP_BLOCKED` y `text` empieza por
  `Blocked (`.
- Dado `href = https://ex\xe2\x80\xaeample.com/`, entonces `text` contiene `%E2%80%AE` y
  ningún byte ≥ 0x80.
- Dado `href = #top` con base `https://a.org/p#old`, entonces `text = https://a.org/p#top`.
- Dado un camino de 7 000 bytes (bajo `URL_MAX_LEN`; más largo, el clic lo bloquea y el preview lo dice), entonces `text` cabe en `LP_TEXT_MAX`, empieza por
  `https://host/`, contiene `...` y el host está entero.
