# Especificación: `js_dom`

> Puente DOM ↔ JS (cierre del cableado del Hito 3). Estado: **SPEC + TEST (rojo)**.
> Metodología: SDD + TDD. Esta spec es el contrato; `tests/test_js_dom.c` debe fallar hasta que
> exista `src/js_dom.c` (estado rojo).

## 1. Propósito

`js_dom` conecta los dos módulos verdes — el índice `dom` (solo lectura) y el motor aislado
`js_sandbox` — exponiendo al script no confiable una **API DOM de solo lectura, mínima y
validada**. Es el "cableado del DOM inerte" que el Hito 3 dejó fuera de alcance.

Diseño Zero Trust: **no se exponen objetos vivos** del motor ni nodos como objetos JS con
prototipos. Los nodos son **handles enteros opacos**; cada llamada valida sus argumentos contra
el índice real. Así la superficie auditada es un puñado de funciones nativas, no un grafo de
objetos. La capa ergonómica (`document`, objetos `Node` con propiedades) puede construirse encima
más adelante, en JS o en C, sin ampliar el núcleo de confianza.

## 2. Decisión de diseño

- El índice `dom` se guarda en el *context opaque* del motor (`JS_SetContextOpaque`), **no**
  alcanzable desde JS. Las funciones nativas lo recuperan con `JS_GetContextOpaque`.
- Se instala un objeto global `dom` con métodos **no escribibles, no configurables**
  (`JS_PROP_ENUMERABLE` puro) y el propio objeto se sella con `JS_PreventExtensions`. Un script
  no puede sustituir `dom`, ni reemplazar `dom.getElementById`, ni inyectar métodos nuevos.
- El bridge usa una costura mínima de `js_sandbox` (`js_context_raw`) que devuelve el contexto
  del motor como `void*` opaco — sin filtrar tipos `JS*` fuera del módulo, igual que
  `hp_document_root` para `dom`.
- **El índice `dom` debe sobrevivir al `js_context`** (se referencia, no se copia).

## 3. Superficie expuesta a JS

Objeto global `dom` (solo lectura). Handles = enteros; "ninguno" = `null`.

| Método JS | Devuelve | Mapea a |
| :-- | :-- | :-- |
| `dom.nodeCount()` | número | `dom_node_count` |
| `dom.getElementById(id)` | handle \| `null` | `dom_get_element_by_id` |
| `dom.getByTag(tag)` | array de handles | `dom_get_by_tag` |
| `dom.getByClass(cls)` | array de handles | `dom_get_by_class` |
| `dom.tagName(h)` | string \| `null` | `dom_tag_name` |
| `dom.getAttribute(h, name)` | string \| `null` | `dom_get_attribute` |
| `dom.parent(h)` | handle \| `null` | `dom_parent` |
| `dom.firstChild(h)` | handle \| `null` | `dom_first_child` |
| `dom.nextSibling(h)` | handle \| `null` | `dom_next_sibling` |
| `dom.precedes(a, b)` | booleano | `dom_precedes` |

Lo que **no** existe (por diseño): mutación (`setAttribute`, `appendChild`, `remove`),
acceso a árbol crudo, eventos, `innerHTML`, ni objetos nodo. Un handle inválido o de tipo
incorrecto produce `null`/`false`, **nunca** un fallo del host.

## 4. Contrato de la API (C)

Definida en `include/js_dom.h`.

```c
typedef enum jd_status {
    JD_OK = 0,
    JD_ERR_NULL_ARG,
    JD_ERR_OOM,
    JD_ERR_INTERNAL
} jd_status;

/* Instala el global `dom` (solo lectura) en el sandbox, respaldado por idx.
 * idx debe sobrevivir a ctx. Llamar sobre un contexto recien creado. */
jd_status jd_install(js_context *ctx, const dom_index *idx);
```

## 5. Tabla de errores

| Código | Condición |
| :-- | :-- |
| `JD_OK` | Global `dom` instalado. |
| `JD_ERR_NULL_ARG` | `ctx == NULL` o `idx == NULL`. |
| `JD_ERR_OOM` | Fallo de asignación al construir el objeto/funciones. |
| `JD_ERR_INTERNAL` | El contexto del motor no es accesible o la instalación falló. |

## 6. Garantías de seguridad

1. **Solo lectura.** Ningún método muta el árbol; reflejan el índice ya saneado por
   `html_parse`/`dom`.
2. **Superficie mínima validada.** Solo las funciones de §3; cada una valida tipo y rango de sus
   argumentos. Handles fuera de rango o no numéricos ⇒ `null`/`false`.
3. **Métodos infalsificables.** `dom` y sus métodos son no escribibles/no configurables y el
   objeto está sellado: un script no puede secuestrar la API ni inyectar funciones.
4. **Sin fuga de punteros.** El `dom_index` vive en el context opaque del motor, inaccesible
   desde JS; los handles son índices, no direcciones.
5. **Hereda el aislamiento del Hito 3.** Sigue sin I/O y bajo los límites de
   memoria/pila/tiempo del `js_context`.
6. **Robustez.** Entradas arbitrarias desde JS no provocan crash/UB en el host (cubierto por
   pruebas y por la validación de `dom`).

## 7. Matriz de pruebas

`tests/test_js_dom.c` (cmocka), sobre un documento conocido instalado en un contexto:
- `jd_install` con args `NULL` ⇒ `JD_ERR_NULL_ARG`; instalación OK.
- `dom.getElementById('main')` no es `null`; `dom.tagName(...)==='div'`.
- `dom.getByClass('text').length === 2`; `dom.getByTag('p').length === 2`.
- Navegación: `dom.tagName(dom.firstChild(dom.getElementById('main')))==='p'`.
- `dom.getAttribute(main,'class')==='container box'`; atributo ausente ⇒ `null`.
- Handle inválido: `dom.tagName(99999)===null`; `dom.tagName(-1)===null`.
- **Infalsificable:** tras `dom.getElementById = 1`, `typeof dom.getElementById==='function'`;
  reasignar `dom` no cambia su identidad; `dom.nuevo = 1` no añade (objeto sellado).
- Hereda límites: un bucle infinito que usa `dom` sigue dando `JS_ERR_TIMEOUT`.

## 8. Fuera de alcance

- **Mutación** del DOM desde JS (depende del DOM mutable, hito posterior).
- Objetos `Node`/`document` con prototipos y propiedades (capa ergonómica encima).
- Eventos, `addEventListener`, delegación (necesario para resumability; spec aparte).
- Selectores CSS completos vía `querySelector` (v1 cubre id/tag/class).
