# Video Fullscreen Toggle

> Fase F: ALT+ENTER toggles fullscreen video mode; ESC exits.

## Contrato

### Entradas/Salidas

| Función | Entradas | Salidas | Errores |
|---------|----------|---------|---------|
| `toggle_fullscreen(w)` | `browser_window` con `xdg_toplevel` válido | Nada, efecto lateral en ventana | Sin error posible; si el compositor rechaza, la ventana no cambia (fail-closed: el estado `w->fullscreen` se sincroniza en el próximo `toplevel_configure`) |
| `handle_key_press` (ALT+ENTER) | `w`, `sym == XKB_KEY_Return`, `alt && !ctrl` | Llama `toggle_fullscreen(w)` | Nada |
| `handle_key_press` (ESC en fullscreen) | `w`, `sym == XKB_KEY_Escape`, `w->fullscreen` | Llama `toggle_fullscreen(w)` | Nada |

### Garantías de seguridad

- `xdg_toplevel_set_fullscreen(NULL)` — pasa NULL al output para que el compositor elija. No filtra por output, sin fugas de información de monitor.
- `w->fullscreen` se actualiza en cada `toplevel_configure` callback, así un cambio inducido por el compositor (Alt+Tab, workspace switch) se refleja sin desincronización.
- No se guarda estado de fullscreen entre sesiones (no persiste en prefs — cada arranque empieza en ventana normal).
- La tecla ESC siempre sale de fullscreen si se está en él, sin importar qué campo esté enfocado. Esto sigue la convención del navegador.

### Fuera de alcance

- True exclusive fullscreen (only one app on screen) — no se usa; ventana del compositor es suficiente.
- `wl_output` selection para fullscreen — se pasa NULL y el compositor elige el output actual.
- Animación de transición fullscreen — el compositor maneja la transición.
- Ocultar la barra de herramientas/chrome en fullscreen — el compositor lo maneja (estándar Wayland).