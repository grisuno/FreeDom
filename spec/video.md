# Video Playback Pipeline

> Fase 0: elemento `<video>`/`<audio>` reconocido en el DOM, transportado como run/blocks/rows, renderizado como placeholder.

## Contrato

### Etapas

1. **page_view** (`PV_VIDEO`): el worker reconoce etiquetas `<video>`/`<audio>` y `<source>` en el DOM, extrae `src`, `poster` (solo video), `width`, `height` y las emite como runs de tipo `PV_VIDEO` en el display list. Por defecto Privacy by Default: el vídeo no se reproduce hasta que el usuario interactúa.

2. **render_doc** (`RD_VIDEO`): el bloque mantiene los metadatos del vídeo (URL, poster, dimensiones). El decision de reproducción se delega al orquestador (GUI).

3. **GUI** (`RC_VIDEO`): pinta un placeholder interactivo. En esta fase (0), un rectángulo gris con el icono ▶ y la URL del video como tooltip.

### Entradas/Salidas

| Función | Entradas | Salidas | Errores |
|---------|----------|---------|---------|
| `pv_append_video(v, heading, block_break, text, src, poster, w, h)` | view, heading, break, alt-text, src, poster, dims | `PV_OK` / `PV_ERR_NULL_ARG` / `PV_ERR_OOM` | src==NULL es error |
| `rd_build` con `PV_VIDEO` | run | `RD_VIDEO` block | OOM |

### Garantías de seguridad

- `src` es la URL raw del host (data with provenance, nunca fetch aquí)
- `poster_src` es la URL raw, tratada como imagen (pasa por `rp_image_decision`)
- Dimensiones acotadas como las imágenes (`PV_MAX_DIM`)
- Privacy by Default: el vídeo no se reproduce sin interacción; ni siquiera se precarga el poster sin `caps.images`
- IPC del worker: el worker solo extrae atributos, nunca ejecuta scripting del video

### Fuera de alcance (Fase 0)

- Reproducción real (Fase 1+)
- MSE / EME
- `play()` / `pause()` desde JS
- iframe anidado (Fase 0d)
- Audio output

## Fase 1a: Iframe shim para sitios con `video[]` array

### Contrato

Un shim JS que se inyecta en el contexto de página DESPUÉS de ejecutar todos los scripts de la página y ANTES de `jd_process_iframes()`. Su función es emular lo que haría un script externo faltante (p.ej. `video_min.js` 404): crear `<iframe>` en el DOM a partir del array `video[]` definido por un script inline de la página.

### Comportamiento

1. Si la variable global `video_data` está definida y no es vacía, la usa directamente como HTML string del iframe (porque la página ya la preparó).
2. Si no, lee `video[1]` (proveedor por defecto, Magi) o `video[0]` (Desu, fallback).
3. Extrae el `src` del iframe parseando el HTML string con una expresión regular simple (`/src\s*=\s*["']([^"']+)["']/`).
4. Si el `src` es relativo (empieza con `/`), lo resuelve contra `location.protocol + "//" + location.hostname`.
5. Crea un elemento `<iframe>` en el DOM mediante `dom.createElement`, le asigna el `src` resuelto, y lo añade al `<body>`.

### Seguridad

- El shim corre en el mismo contexto JS aislado que la página (sin I/O de red, sin acceso a sistema)
- Usa exclusivamente la API `dom.*` del bridge C (handles validados, sin objetos vivos)
- No ejecuta ningún contenido externo; solo crea un nodo DOM que luego `jd_process_iframes()` procesa con su pipeline gateado
- Try/catch alrededor de todo: si algo falla (página sin `video` array, sin `dom`, etc.), el shim es no-op
- Zero Trust: el flujo final del iframe sigue pasando por `jl_process_iframes()` → fetch gateado por el padre → `scan_m3u8_url()` → creación de `<video>` en el DOM

### API

```c
jd_status jd_inject_video_shim(js_context *ctx);
```

Inyecta el shim JS en el contexto. Debe llamarse después de que los scripts de la página hayan ejecutado (para que `video[]` exista) y antes de `jd_process_iframes()`.
