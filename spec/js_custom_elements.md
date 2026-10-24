# js_custom_elements (`jdce_`) — Custom Elements v1 (2026-10-20)

GitHub (Turbo, Primer), lit y casi todo componente web moderno dependen de que
`document.createElement('mi-elemento')` ejecute el constructor de la clase definida y de que
`connectedCallback` se dispare. La versión anterior (`customElements.define` que sólo guardaba la
clase) no construía nada: `Object.getPrototypeOf(createElement('turbo-frame').delegate)` fallaba con
`TypeError: not an object`, el error que GitHub arrojaba en `behaviors.js`.

## Contrato

- `class X extends HTMLElement`: `HTMLElement` es un constructor real. Con `new.target` igual a
  una clase definida devuelve el elemento (creado por `createElement`, o el que se está
  *mejorando*) con su prototipo puesto a `X.prototype`; en cualquier otro caso lanza `TypeError`
  ("Illegal constructor").
- `customElements.define(name, ctor)`: `name` válido (minúsculas, con guion, no reservado) o
  `SyntaxError`; ya definido (nombre o constructor) ⇒ `NotSupportedError`; `ctor` no función ⇒
  `TypeError`. Lee `ctor.observedAttributes`. Tras definir, **mejora** (upgrade) los elementos del
  documento con ese nombre, en orden de documento.
- `document.createElement(name)` con `name` definido ⇒ `new ctor()`; si el constructor lanza, el
  error se informa a la consola y se devuelve un elemento simple (nunca se pierde el nodo).
- Ciclo de vida, sincronizado por `__ceFlush()` (el motor lo llama al terminar cada script, tras
  cada tarea de temporizador y al disparar `load`): `attributeChangedCallback(name, old, new)` para
  los atributos observados (al mejorar, uno por atributo presente), `connectedCallback` cuando el
  elemento pasa a estar en el documento, `disconnectedCallback` cuando deja de estarlo.
- `customElements.get/getName/whenDefined/upgrade`.

## Fuera de alcance (v1)

Elementos personalizados *built-in* (`extends` / `is=`), Shadow DOM encapsulado real,
`adoptedCallback`, `ElementInternals`, formularios asociados. El estado vivo se acota (4096
elementos): el excedente de elementos nunca conectados se descarta, no crece sin tope.

## Dado-Cuando-Entonces

- Dado `class XBox extends HTMLElement { constructor(){ super(); this.delegate = {k:1} } }` definida,
  cuando se hace `document.createElement('x-box')`, entonces el resultado es `instanceof XBox` y
  `delegate.k === 1`.
- Dado un `<x-up>` ya en el documento, cuando se define `x-up`, entonces el elemento existente se
  construye y recibe `attributeChangedCallback` por cada atributo observado que ya tenía.
- Dado un elemento creado y luego añadido y quitado del documento, entonces `connectedCallback` y
  `disconnectedCallback` se llaman una vez cada uno, en ese orden.

## Costo de `define()` (2026-10-24)
`customElements.define(name)` reconcilia SOLO ese nombre (`flush(undefined, name)`): busca en el
documento `name` (no la unión de todos los nombres definidos) y recorre solo los registros vivos de ese
nombre. Antes cada `define` hacía `scan(document)` con un selector de todos los nombres y reconciliaba
todos los elementos vivos: O(define² × DOM). GitHub define cientos; su módulo `github-elements`
(7.7 KB) pasó de 8.3 s a 0.9 s. `__ceFlush`/`__connectedCallback` (tras timers y carga) siguen
reconciliando todo, una vez.
