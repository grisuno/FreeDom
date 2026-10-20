# wl_display — descubrimiento del socket Wayland

Problema medido: el binario instalado salia con codigo 1 y SIN mensaje cuando
`WAYLAND_DISPLAY` no estaba definida y el compositor escuchaba en `wayland-1`
(`wl_display_connect(NULL)` solo prueba `wayland-0`).

- Dado un conjunto de nombres de directorio, cuando `wd_pick` los examina, entonces devuelve
  el `wayland-N` valido (N solo digitos) de menor N; `.lock`, otros prefijos y N vacio se ignoran.
- Dado que ninguno es valido, entonces devuelve `WD_NONE` y no escribe en `out`.
- Dado `cap` demasiado chico, entonces `WD_NONE` (fail-closed, sin truncar).
- Orquestador (`wd_resolve_env`): solo actua si `WAYLAND_DISPLAY` esta vacia; nunca pisa
  una variable del usuario. Si no hay compositor, `freedom` imprime un mensaje accionable.
