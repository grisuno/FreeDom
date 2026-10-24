# spec: pq_seal (sellado híbrido ML-KEM-512 + AEAD, `pqs_`)

Cifra datos en reposo que NO son ni credenciales ni preferencias (memoria de redirecciones,
caché HTTP): un blob se sella con una clave de datos que sale de **dos** secretos, así que romper
uno solo no abre el contenido (nunca PQ puro, nunca clásico puro; CLAUDE.md §1.5).

## Contrato
- `pqs_seal(keys, wrap, pt)`: encapsula con ML-KEM-512 (OpenSSL `default` provider, FIPS 203) →
  `ss` (32 B) + `ct` (768 B). Clave de datos = HKDF-SHA256(salt `freedom-pqseal-v1`,
  ikm = `ss ‖ wrap`, info `aead-key`). El cuerpo es un contenedor `local_store` ChaCha20-Poly1305.
  Formato: `"FPQ1" ‖ ct(768) ‖ contenedor`.
- `wrap` es la clave de 32 B del perfil (Argon2id + clave de dispositivo, `profile_ctx.key`). La
  clave privada ML-KEM vive en `pq.key`, sellada bajo `wrap` por `disk_store`.
- **Dado** un blob alterado, `wrap` ajeno o `keys` ajenas, **entonces** `PQS_ERR_AUTH` y ningún
  texto plano. **Dado** un blob de otra versión o truncado, `PQS_ERR_FORMAT`.
- Cada sellado usa una encapsulación nueva: dos sellados del mismo texto difieren.
- Límite de texto plano: el de `local_store` (`LS_MAX_PLAINTEXT`).

## Fuera de alcance
Rotación de claves, firmas (ML-DSA), y cualquier uso en el worker confinado (solo lado confiable).
