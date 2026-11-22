# nav_token (`nt_`) — carga en paralelo por pestaña

## Por qué

Hasta la tanda 97 había UNA generación de navegación por ventana (`net_gen`): cambiar de
pestaña la incrementaba, así que salir de una pestaña que cargaba **abandonaba** su carga
(transferencia cortada, entrada provisional del historial deshecha). Firefox sigue cargando
la pestaña en segundo plano. Para eso cada navegación de red necesita su propia identidad,
que viaje con la pestaña cuando se aparca y que los hilos de fetch puedan consultar sin
tocar el estado de la ventana.

## Contrato

Un `nt_token` es la identidad de UNA navegación de red de UNA pestaña.

- `nt_new()` → token con una referencia, `foreground = 1`, no cancelado, `id` único y
  creciente (nunca 0). NULL si no hay memoria (el llamador falla cerrado: no lanza el fetch).
- `nt_ref(t)` / `nt_unref(&t)` — conteo atómico; `nt_unref` pone el puntero a NULL
  (liberador idempotente) y libera al llegar a 0. NULL-seguros.
- `nt_cancel(t)` — irreversible. `nt_cancelled(NULL) == 1` (falla cerrado).
- `nt_set_foreground(t, on)` / `nt_foreground(t)` — `NULL` ⇒ 0. Solo una navegación en
  primer plano escribe en el búfer de streaming de la ventana.
- `nt_id(t)` — 0 para NULL. Se compara por id, no por puntero (un token liberado y otro
  nuevo en la misma dirección no se confunden).
- `nt_route(job, active, parked, n, &slot)` — qué hacer con un resultado que llegó:
  | Condición (en orden) | Resultado |
  | :-- | :-- |
  | `job` NULL o cancelado | `NT_DROP` |
  | `job == active` | `NT_DELIVER` (pestaña visible: se pinta ya) |
  | `parked[i] == job` para algún `i` | `NT_PARK`, `*slot = i` (se guarda en esa pestaña y se pinta al volver) |
  | ninguno (la pestaña se cerró) | `NT_DROP` |

Puros salvo los contadores atómicos (C11 `stdatomic`). Sin I/O.

## Garantías

- Un resultado nunca se pinta en una pestaña que no es la suya: la ruta compara identidad
  de token, no posición (las pestañas se reordenan por arrastre).
- Cerrar una pestaña o navegar de nuevo cancela su token: la transferencia se corta en el
  siguiente sondeo de libcurl (`sf_config.cancel_cb`) y el resultado se descarta.
- Salir de una pestaña **no** cancela nada: solo apaga `foreground`.
- Hilos de fetch y GUI comparten el token por referencia: ninguno puede liberar lo que el
  otro todavía lee.

## Dado-Cuando-Entonces

- **Dado** una pestaña A cargando, **cuando** el usuario cambia a B, **entonces** el token de
  A sigue vivo, no cancelado, `foreground = 0`; al llegar el resultado `nt_route` da `PARK`
  en el índice ACTUAL de A (aunque se haya reordenado).
- **Dado** el resultado aparcado, **cuando** el usuario vuelve a A, **entonces** se entrega.
- **Dado** A cerrada, **entonces** su token está cancelado y el resultado es `DROP`.
- **Dado** Detener/Esc o una navegación nueva en A, **entonces** el token viejo se cancela.

## Fuera de alcance

Renderizar la pestaña aparcada en segundo plano (el worker confinado y el pipeline de pintado
son de la pestaña visible): el documento llega por la red en paralelo y se maqueta al
mostrarla. Streaming progresivo de una pestaña oculta.
