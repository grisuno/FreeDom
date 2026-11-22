# chrome_layout (`chl_`) — geometría del chrome e insignia de identidad

## Por qué

El chrome (barra de título, pestañas, barra de herramientas) vivía como constantes y
cálculos repartidos por `gui/browser_ui.c` (`toolbar_rects`, `window_button_rects`,
`tab_width`, `newtab_x`, `toolbar_button_at`, y tres hit-tests escritos a mano en
`ptr_button`/`ptr_axis`). Pintor y hit-test podían divergir (ya pasó: la rueda del ratón
comparaba contra `UI_TOOLBAR_H`, no contra el borde inferior del chrome), y el chrome no
decía nada sobre la conexión: un navegador cuya misión es la seguridad no mostraba si la
página llegó por intercambio de claves post-cuántico híbrido o por cripto clásica.

Este módulo es la **única fuente de verdad** de la geometría del chrome (pintor y punteros
leen lo mismo) y de la **insignia de identidad** de la conexión. Puro, sin I/O, sin Cairo.

## Disposición (CSD y SSD)

Estilo de los navegadores de primera línea: las pestañas viven en la barra de título.

```
fila 1 (CHL_TABBAR_H): [pestaña][pestaña][+]  ....zona de arrastre....  [_][□][×]
fila 2 (CHL_TOOLBAR_H): (<)(>)(⟳) ( [insignia] url ................ ) (≡)
contenido desde content_top = CHL_TABBAR_H + CHL_TOOLBAR_H
```

- Bajo **CSD** los tres botones de ventana ocupan el extremo derecho de la fila 1 y se
  reserva siempre `CHL_DRAG_MIN` px de zona de arrastre (la ventana se puede mover con
  cualquier cantidad de pestañas). Bajo **SSD** no hay botones de ventana ni reserva.
- Las pestañas reparten el ancho disponible, cada una con ancho en
  `[CHL_TAB_MIN_W, CHL_TAB_MAX_W]`; con demasiadas, el mínimo gana y la tira se desplaza
  (`tab_first`) para que la **activa** sea siempre visible; las que quedan fuera no se
  pintan ni se pueden pulsar (`chl_tab_rect` devuelve 0).
- El botón de cierre de una pestaña existe solo con `tab_count > 1`, y se muestra en toda
  pestaña con ancho ≥ `CHL_TAB_CLOSE_MIN_W` y siempre en la activa.
- Los botones de la barra son círculos de `CHL_BTN` px; la URL es una píldora que va de
  tras recargar hasta antes del menú, con la insignia de identidad dentro a la izquierda.
  No hay botón «Go» (Intro navega; ningún navegador de referencia lo tiene).

## Contrato

- `chl_compute(width, csd, tab_count, active, out)` → `CHL_OK` / `CHL_EINVAL`. `width`
  no finito o < 1 se trata como 1; `tab_count` < 1 ⇒ `CHL_EINVAL`; `active` fuera de rango
  ⇒ `CHL_EINVAL`. Nunca produce rectángulos con ancho negativo.
- `chl_tab_rect(l, i, r)` / `chl_tab_close_rect(l, i, r)` → 1 si existe, 0 si no.
- `chl_hit(l, x, y, &tab)` → la parte bajo el punto (`CHL_PART_*`); `tab` recibe el índice
  para `TAB`/`TAB_CLOSE`, -1 en otro caso. Prioridad: cierre de pestaña antes que pestaña;
  fuera del chrome ⇒ `CHL_PART_CONTENT`; hueco de la fila 1 ⇒ `CHL_PART_DRAG` (CSD) o
  `CHL_PART_NONE` (SSD); hueco de la fila 2 ⇒ `CHL_PART_NONE`.
- `chl_identity_of(url, transport_known, downgrade, operator_insecure)` → `chl_identity`.
- `chl_identity_label(id)` → texto corto en inglés (estático, nunca NULL).

## Insignia de identidad — tabla de decisión (en orden, la primera que aplica)

| Condición | Insignia | Significado |
| :-- | :-- | :-- |
| `url` NULL, vacía, `about:` | `INTERNAL` | página propia del navegador |
| `file:` | `LOCAL` | archivo local, sin red |
| `operator_insecure` y esquema de red | `UNVERIFIED` | `--insecure`: certificado SIN verificar |
| `http:` en `.i2p` | `OVERLAY` | el overlay cifra |
| `http:` en cualquier otro host | `INSECURE` | no debería ocurrir (https-only), falla cerrado |
| `https:` y `!transport_known` | `UNKNOWN` | no sabemos cómo llegó: **ninguna afirmación** |
| `https:` y `downgrade == ALLOWLISTED` | `WEAK` | override de soberanía: fuerza relajada, autenticidad intacta |
| `https:` y `downgrade == CLASSICAL_KE` | `CLASSICAL` | TLS 1.3 sin KE híbrido |
| `https:` en `.onion`/`.i2p` | `OVERLAY` | |
| `https:` y `downgrade == NONE` | `PQ` | TLS 1.3 + X25519MLKEM768 |
| cualquier otro esquema/valor | `UNKNOWN` | falla cerrado: nunca verde por omisión |

**Garantía:** la insignia `PQ` (la única «verde») solo aparece si el transporte es conocido,
el esquema es `https`, no hubo degradación y el operador no desactivó la verificación. Un
`downgrade` fuera del enum es `UNKNOWN`.

`transport_known` lo pone el orquestador **solo** cuando el documento mostrado viene de un
fetch que terminó en este documento (`deliver_fetch_result`); cualquier otro cambio de
documento (`set_cache`) lo apaga. Así una página servida de otro camino nunca hereda la
insignia de la anterior.

## Dado-Cuando-Entonces

- **Dado** ancho 1300 con CSD y 1 pestaña, **cuando** se computa, **entonces** los botones
  de ventana terminan en x = 1300, la pestaña empieza en `CHL_PAD`, no hay cierre de pestaña
  y queda zona de arrastre ≥ `CHL_DRAG_MIN`.
- **Dado** 200 pestañas, **entonces** ninguna mide menos de `CHL_TAB_MIN_W`, `+` y los
  botones de ventana no se solapan con ninguna pestaña visible y la zona de arrastre sigue.
- **Dado** un punto sobre la píldora, **entonces** `chl_hit` da `URL`; sobre la insignia,
  `IDENTITY`; bajo `content_top`, `CONTENT`.
- **Dado** `https://x` con transporte conocido y sin degradación, **entonces** `PQ`; con
  `--insecure`, `UNVERIFIED`; sin transporte conocido, `UNKNOWN`.

## Fuera de alcance

Arrastrar pestañas para reordenarlas, favicons (exigirían un fetch extra por página: se
decidirá en su propio hito por su coste de privacidad), panel de detalles de la conexión.
