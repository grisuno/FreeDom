# Especificación: `renderer`

> Hito 5 — Aislamiento (renderer fuera de proceso por pestaña). Estado: **SPEC + TEST (rojo)**.
> Metodología: SDD + TDD. Esta spec es el contrato; `tests/test_renderer.c` debe fallar hasta que
> exista `src/renderer.c` (estado rojo).

## 1. Propósito

`renderer` ejecuta el parseo de contenido **no confiable** en un **proceso hijo separado y
confinado** (seccomp-bpf), devolviendo al proceso padre solo un resultado **inerte** (título +
texto). Es el modelo multiproceso del aislamiento de pestañas: cada pestaña parsea en su propio
proceso, con su propio espacio de direcciones.

Garantía de aislamiento: el **proceso padre nunca toca los bytes hostiles**. Si el hijo se cuelga,
es explotado o agota su límite de syscalls, muere de forma aislada (`SIGSYS`/exit) y el padre
**sobrevive**, devolviendo `RD_ERR_RENDER`. Un compromiso en una pestaña no alcanza a otras ni al
proceso de UI.

Combina dos módulos verdes: `os_sandbox` (confinamiento) + `html_parse` (parseo inerte). Verificado
que lexbor parsea correctamente bajo la lista blanca de seccomp.

## 2. Arquitectura

```
proceso padre (UI/confianza)        proceso hijo (renderer, confinado)
  rd_render_html(html)                 close(read end)
    pipe(); fork() ----------------->  os_harden(KILL)        <- seccomp activo
    close(write end)                   hp_parse(html)         <- contenido hostil
    read framed result <-----pipe----- write [title][text]
    waitpid()                          _exit(0)
    -> rd_result (inerte)
```

- El hijo aplica `os_harden` **antes** de tocar el HTML: si el parseo intentara una syscall fuera
  de la lista (abrir ficheros, sockets, exec), el kernel lo mata.
- Protocolo padre↔hijo: framed `[title_len][title][text_len][text]` (longitudes `size_t`).
- El padre **valida** las longitudes recibidas contra un tope (`RD_MAX_FIELD`) antes de asignar:
  un hijo comprometido no puede inducir una asignación gigante en el padre.

## 3. Contrato de la API

Definida en `include/renderer.h`.

```c
typedef enum rd_status {
    RD_OK = 0,
    RD_ERR_NULL_ARG,
    RD_ERR_TOO_LARGE,  /* la entrada supera RD_MAX_INPUT */
    RD_ERR_SPAWN,      /* pipe()/fork() fallaron */
    RD_ERR_RENDER,     /* el hijo fallo/murio (aislado): el padre sigue vivo */
    RD_ERR_OOM
} rd_status;

typedef struct rd_result {
    rd_status status;
    char  *title;     size_t title_len;  /* en propiedad; NUL-terminado */
    char  *text;      size_t text_len;
} rd_result;

rd_status rd_render_html(const char *html, size_t len, rd_result *out);
void      rd_result_free(rd_result *out);
```

`RD_MAX_INPUT` por defecto 32 MiB; `RD_MAX_FIELD` (tope por campo de salida) 64 MiB.

## 4. Semántica

- `rd_render_html`: `html`/`out` no nulos (`RD_ERR_NULL_ARG`); `len > RD_MAX_INPUT`
  (`RD_ERR_TOO_LARGE`); fallo de `pipe`/`fork` (`RD_ERR_SPAWN`). En el camino feliz, `*out` lleva
  `title`/`text` inertes y `RD_OK`. Si el hijo no termina con éxito o el resultado no llega
  completo/válido ⇒ `RD_ERR_RENDER` (sin estado parcial fugado). Cada llamada crea un proceso
  hijo nuevo (aislamiento por render/pestaña).
- El hijo, ya confinado, parsea con la política por defecto de `html_parse` (strip de `<script>` y
  `on*`), de modo que `text` nunca contiene cuerpos de script.
- `rd_result_free`: libera `title`/`text` y pone a cero; idempotente, `NULL`-safe.

## 5. Garantías de seguridad

1. **Aislamiento de proceso:** el contenido hostil se parsea en otro espacio de direcciones; el
   padre no lo mapea ni lo ejecuta.
2. **Confinamiento del hijo:** seccomp-bpf fail-closed activo antes de tocar el contenido.
3. **Tolerancia a fallos:** un hijo que muere no derriba al padre; se reporta `RD_ERR_RENDER`.
4. **Anti-amplificación:** longitudes de salida validadas contra tope antes de asignar.
5. **Memoria:** dueño único; `rd_result_free` idempotente. ASan/UBSan limpios.

## 6. Matriz de pruebas

`tests/test_renderer.c` (cmocka):
- Render de un documento conocido ⇒ `RD_OK`, `title`/`text` correctos.
- `<script>`/`onclick` eliminados ⇒ `text` no contiene el cuerpo del script.
- `NULL` ⇒ `RD_ERR_NULL_ARG`; sobre-tamaño ⇒ `RD_ERR_TOO_LARGE`.
- Entrada binaria/malformada ⇒ retorna (RD_OK o RD_ERR_RENDER) **sin** derribar el proceso de
  prueba (demuestra el aislamiento).
- Varias llamadas consecutivas (procesos independientes) ⇒ todas correctas.
- `rd_result_free` con `NULL` y doble llamada.

## 7. Fuera de alcance

- IPC bidireccional / petición-respuesta persistente (un hijo de larga vida por pestaña): v1 es
  one-shot (fork por render). 
- Paso del DOM serializado completo (v1 devuelve título+texto inerte); serializar el árbol es
  trabajo posterior.
- Ejecución de JS en el hijo (se integrará `js_sandbox` en el proceso confinado después).
- `landlock` para el sistema de archivos (refuerzo adicional al seccomp).
