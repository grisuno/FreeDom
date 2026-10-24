# spec: shm_slots (doble búfer de la ventana, `ss_`)

## Problema (medido)
La ventana usaba UN `wl_buffer` y `buffer_release` no hacía nada. Cada fotograma repinta la página entera sobre
la memoria que el compositor puede estar leyendo, así que se veía a medio pintar: el vídeo de jkanime
parpadeaba. Medido bajo weston con 90 capturas de la zona del vídeo durante la reproducción: **8 cuadros
corruptos** (relleno `246,0,0`) con un solo búfer, **0** con dos.

## Contrato
- Dos ranuras (`SS_COUNT`). Una ranura está OCUPADA desde el `commit` hasta el `release` del compositor.
- `ss_pick`: se pinta en la ranura actual si está libre, si no en la otra; `-1` si el compositor retiene las
  dos. En ese caso el repintado se POSPONE (`redraw_wanted`) y `buffer_release` lo ejecuta al liberarse una:
  nunca se escribe en un búfer retenido.
- `ss_committed` marca la pintada como ocupada y alterna; `ss_released` ignora índices fuera de rango o
  ranuras ya libres.
- Al cambiar el tamaño se destruyen ambos búferes (el compositor conserva su referencia hasta liberarla).
- La ventana de Freebug conserva su búfer único (su `release` es un no-op propio, `fb_buffer_listener`): sus
  datos de usuario no son un `browser_window`.
- Es pura contabilidad (`include/shm_slots.h`, sin E/S ni asignaciones): `tests/test_shm_slots.c`.
