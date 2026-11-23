# smooth_scroll (`sms_`) — desplazamiento suave de la página

## Por qué

Hasta la tanda 102 la rueda y el teclado (`↑`/`↓`, `Espacio`, `RePág`/`AvPág`, `Inicio`/`Fin`)
saltaban de golpe: el ojo pierde la línea que estaba leyendo. Firefox anima cada salto
(~150 ms, curva de salida). Y con el asiento enlazado en la versión 1 de Wayland una
**superficie táctil** mandaba decenas de eventos `axis` por gesto y cada uno avanzaba un paso
entero de rueda (3 líneas): la página volaba.

Este módulo es la cuenta pura de la animación. El lado confiable (GUI) solo la cablea: no
toca contenido remoto, no abre red y no le dice nada a la página (los eventos `wheel`/`scroll`
al JS se despachan igual que antes, al recibir la entrada).

## Contrato

```c
typedef struct { double from, to, pos, t0_ms, dur_ms; int active; } sms_state;
void   sms_init(sms_state *s, double pos);
void   sms_jump(sms_state *s, double pos);
void   sms_retarget(sms_state *s, double target, double now_ms, double dur_ms);
double sms_sample(sms_state *s, double now_ms);
double sms_goal(const sms_state *s);
int    sms_active(const sms_state *s);
```

- `sms_init`/`sms_jump`: posición fija, sin animación (`active = 0`, `from = to = pos`).
- `sms_retarget(target, now, dur)`: anima **desde la posición actual** (`pos`, la última
  muestreada) hasta `target` en `dur` ms. `dur <= 0` (o no finito) ⇒ salto inmediato.
  Un `target` igual a `pos` ⇒ sin animación.
- `sms_sample(now)`: actualiza y devuelve `pos`:
  `s = clamp((now − t0)/dur, 0, 1)`, `pos = from + (to − from)·(1 − (1 − s)³)` (cúbica de
  salida: arranca rápido y frena; derivada nula al llegar). En `s = 1` `pos = to` EXACTO y
  `active = 0`. Un reloj que retrocede (`now < t0`) da `s = 0`.
- `sms_goal`: hacia dónde va (`to` si anima, `pos` si no). Pulsaciones seguidas **acumulan**
  sobre el destino, no sobre la posición intermedia: tres `↓` = tres líneas.
- Una posición, destino o instante no finitos (`NaN`, `±inf`) se ignoran (el estado no
  cambia; `sms_init` cae a 0). Una DURACIÓN no finita es «sin animación». `NULL` es no-op / 0.

## Garantías (propiedades, comprobadas por el fuzzer)

1. `pos` siempre finito y dentro de `[min(from,to), max(from,to)]`: **nunca se pasa** del
   destino (no rebota más allá del final de la página).
2. Monótona en el tiempo dentro de una animación.
3. Continua en posición al re-apuntar: el primer `sms_sample` tras `sms_retarget` en el mismo
   instante devuelve la posición anterior.
4. Termina: para `now ≥ t0 + dur`, `pos == to` y `active == 0`.

## Cableado (gui/browser_ui.c)

- Rueda de ratón (`axis_source` = `wheel`, o desconocido en compositores v1) y teclas de
  desplazamiento: `destino = clamp(sms_goal + delta, 0, máximo)` y `sms_retarget` con
  `FC_SMOOTH_SCROLL_MS`. Un `axis` táctil (`finger`/`continuous`) desplaza su valor en px
  **directamente**, sin animar (el dedo ya es la animación), y cancela la animación en curso.
- El bucle principal muestrea mientras `sms_active` (despierta cada `FC_SMOOTH_SCROLL_FRAME_MS`).
- **Cancelación por observación:** si `w->scroll` ya no es la última posición que escribió la
  animación, otro camino lo movió (buscar, arrastrar la barra, ancla, `scrollTo` del JS,
  recorte al final de la página) y la animación se abandona en esa posición. No hay lista de
  sitios que "deben cancelar".
- `FREEDOM_SMOOTH_SCROLL=0` lo desactiva (saltos instantáneos, como antes). El headless no lo
  usa: sus salidas siguen siendo deterministas para un agente.

## Dado-Cuando-Entonces

- **Dado** `pos 0`, **cuando** `sms_retarget(300, t=1000, 150)`, **entonces** en `t=1000`
  `pos 0`, en `t=1075` `pos = 300·(1−0,5³) = 262,5`, en `t=1150` `pos 300` y no activa.
- **Dado** una animación 0→100 a mitad de camino, **cuando** se re-apunta a `sms_goal + 100`,
  **entonces** el destino es 200 y la posición no salta.
- **Dado** `dur 0`, **entonces** `pos = target` al instante.
- **Dado** `target NaN`, **entonces** el estado no cambia.

## Fuera de alcance

Física de inercia (*fling*) tras soltar el dedo, desplazamiento horizontal, desplazamiento
suave de contenedores `overflow:auto` internos y de `scroll-behavior: smooth` del autor.
