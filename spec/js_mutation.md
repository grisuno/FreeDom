# spec: js_mutation (MutationObserver real)

Vive en `src/js_dom_ext.c` (`JDX_MUTATION_SHIM`) y `src/js_dom.c` (`jd_freeze_mutators`).

## Problema
El `MutationObserver` sintetico nunca observaba nada (llamaba al callback una vez con `[]`).
Frameworks, widgets de consentimiento y cargadores lazy dependen de el.

## Diseno
Todo cambio del documento pasa por 8 nativos sellados de `dom`: `setText`, `appendChild`,
`insertBefore`, `moveChildren`, `removeChild`, `setAttribute`, `removeAttribute`,
`setInnerHtml`. Envolverlos UNA vez es el unico punto de enganche: wrappers, fragmentos,
`innerHTML`, `insertAdjacent*` y custom elements reportan sin tocarse.

**Seguridad:** esos nativos nacen escribibles SOLO durante la instalacion y
`jd_freeze_mutators` los vuelve a sellar (no escribibles, no configurables) incondicionalmente,
incluso si un shim fallo. La pagina nunca puede reemplazar un nativo `dom.*`. Un observer solo
ve mutaciones del propio DOM de la pagina: sin capacidad nueva, sin fuga.

## Contrato
- **Dado** un observer con `childList`/`attributes`/`characterData` (+ `subtree`,
  `attributeFilter`, `attributeOldValue`, `characterDataOldValue`), **cuando** el DOM cambia,
  **entonces** recibe `MutationRecord`s en orden, entregados en UNA microtarea
  (`js_pump_jobs`), con `target`, `addedNodes`, `removedNodes`, `previousSibling`,
  `nextSibling`, `attributeName`, `oldValue` (null salvo que se pida).
- Sin mutaciones no hay callback. `disconnect()` descarta pendientes. `takeRecords()` vacia la cola.
- Mover un nodo entre padres emite el retiro del padre viejo y la insercion en el nuevo.
- `observe` sin `childList`/`attributes`/`characterData` lanza `TypeError`.
- Cotas: 4096 observers vivos, 8192 registros en cola por observer, recorrido de ancestros 100000.
- Sin observers vivos los nativos envueltos son una indireccion (costo ~cero).

## Fuera de alcance
`attributeNamespace`, `MutationRecord` como clase instanciable, observar `shadowRoot` aparte.
