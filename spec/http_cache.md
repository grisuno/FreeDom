# spec: http_cache (caché HTTP cifrada + memoria de redirecciones, `hc_`)

Hace que los sitios grandes carguen rápido sin construir un archivo de historial legible: la
misma idea que la caché de Firefox (frescura por `Cache-Control`/`Expires`/heurística,
revalidación por `ETag`/`Last-Modified`) con tres diferencias de doctrina.

## Garantías de privacidad
1. **Nada en claro.** Cada entrada es un blob `pq_seal` (ML-KEM-512 + clave del perfil,
   `spec/pq_seal.md`). Un volcado del directorio no revela URL, cabeceras ni cuerpos.
2. **Nombres anonimizados.** El archivo se llama `hex(HMAC-SHA256(k, tipo ‖ partición ‖ url))`
   con `k` derivada de la clave del perfil: sin ella no se puede ni comprobar si una URL está.
3. **Partición por sitio** (doble clave, anti-sondeo de caché): la misma URL pedida desde dos
   sitios de nivel superior distintos son dos entradas; un sitio no puede saber qué vio otro.
4. **Acotada y olvidable:** 8 MiB por entrada, 128 MiB en total (se expulsa lo más antiguo),
   redirecciones 30 días, `hc_clear` borra todo. Solo GET, `https`.

## Contrato (decisiones puras)
- **Almacenable** (`hc_storable`): 200, sin `no-store`, cuerpo <= 8 MiB, y alguna señal de
  reutilización (validador, `max-age`/`Expires`). Otra cosa no se guarda.
- **Frescura** (`hc_lifetime`): `max-age=N` manda; `no-cache` => 0 (siempre revalidar); sin él,
  `Expires - Date`; sin él, heurística 10 % de `Date - Last-Modified` acotada a 1 día; si no, 0.
- **Clasificación** (`hc_classify`): edad < frescura => `HC_FRESH` (servir sin red); si no y hay
  validador => `HC_REVALIDATE` (GET condicional; 304 => servir lo guardado y renovar); sin
  validador => `HC_UNUSABLE` (se vuelve a pedir).
- Un blob alterado, de otra clave o ilegible **se borra y cuenta como fallo** (nunca devuelve
  datos). Clave de perfil distinta => se regeneran las claves ML-KEM y se vacía la caché (es solo
  caché: no hay nada que preservar).
- La revalidación va a la **URL final** guardada, nunca a la solicitada, para no filtrar un
  validador (`ETag` = supercookie) a otro origen de una cadena de redirecciones.

## Memoria de redirecciones
`hc_redirect_put/get`: una 301/308 observada se recuerda 30 días entre sesiones; la siguiente
visita entra directo al destino. Solo destinos `https`. El destino se vuelve a pedir bajo la
política completa (TLS, hostblock, realm): la memoria cambia **a dónde se va primero**, jamás
qué se permite.

## Fuera de alcance
`Vary`, `Range`/206, `stale-while-revalidate`, caché de POST, caché compartida entre perfiles.
