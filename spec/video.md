# Video Playback Pipeline

> Fase 0: element `<video>`/`<audio>` reconocido en el DOM, transportado como run/blocks/rows, renderizado como placeholder.

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
