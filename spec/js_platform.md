# spec: js_platform (superficie de plataforma web sin capacidades nuevas)

`JDX_PLATFORM_SHIM` (`src/js_dom_ext.c`, instalado por `jdx_install` tras el MutationObserver).
Cierra huecos de compatibilidad que una pagina moderna usa SIN detectar la funcion (un
`TypeError` aborta su script). Nada de esto abre red, disco, ni lee geometria: Firefox lo tiene
todo, asi que añadirlo acerca la identidad en vez de alejarla. Cada definicion esta guardada: un
nativo o un shim anterior siempre gana.

## Contrato (Dado-Cuando-Entonces)
- **Eventos.** Dado `new KeyboardEvent('keydown',{key:'Enter'})`, cuando se lee, entonces `key`,
  `ctrlKey`, `getModifierState`, `instanceof UIEvent/Event` responden como en un navegador; los
  `MouseEvent/PointerEvent/WheelEvent` traen `clientX/Y`, `pageX/Y` (espejo de client), `button`...
  Cada constructor es una funcion real con `prototype` encadenado (Event > UIEvent > MouseEvent >
  PointerEvent) y los campos del init por defecto de la spec. `__mkEvent` (eventos que fabrica el
  host: clic, popstate) tambien produce instancias de `Event`.
- **Prototipo por etiqueta** (`js_dom.c`, `__elProtoFor`): `<input>` es `HTMLInputElement` (encadenado a
  `HTMLElement`), `<div>` `HTMLDivElement`, etc.; `instanceof` responde bien y los controles de
  formulario pueden llevar metodos propios.
- **Controles de formulario.** `select()`, `setSelectionRange`, `selectionStart/End/Direction`;
  `validity` (`valueMissing`, `typeMismatch` email/url, `patternMismatch`, `rangeUnderflow/Overflow`,
  `badInput`, `customError`), `willValidate`, `validationMessage`, `setCustomValidity`,
  `checkValidity` (dispara `invalid`), `reportValidity`; `form.checkValidity/reportValidity` y
  `form.requestSubmit(submitter)` (valida, dispara `submit` cancelable y recien entonces `submit()`).
  Limite: `tooLong/tooShort/stepMismatch` no se evaluan (la spec los liga a edicion del usuario).
- **Elemento.** `hidden` (refleja el atributo), `outerHTML` (get/set), `scrollTo/scroll/scrollBy`
  (los desplazamientos siguen normalizados: no hay lectura de geometria nueva), `checkVisibility`,
  `getAnimations() -> []`, `animate(keyframes, opts)`: devuelve un objeto Animation con
  `finished/ready/play/pause/finish/cancel/onfinish`; NO anima, pero al terminar (timer de
  `delay + duration*iterations`, tope 600 s, o `finish()`) aplica el ULTIMO fotograma al `style` si
  `fill` es `forwards`/`both`, de modo que el estado final de un fade coincide con el de Firefox.
- **Globales.** `AbortSignal.timeout/any`, `reportError`, `scheduler.postTask/yield`, `visualViewport`
  (lee `innerWidth/Height`, con la misma normalizacion que ellos), `window.name`,
  `document.execCommand` (siempre `false`), `document.timeline`, `DOMPoint`, `DOMMatrix` (4x4,
  `translate/scale/rotate/skew/multiply/inverse/transformPoint/toString`), `ImageData`, `FontFace`
  (`load()` rechaza con `NetworkError`: las fuentes llegan por `@font-face`, no por script),
  `DOMParser` (HTML/XML sobre un contenedor inerte, sin ejecutar scripts) y `XMLSerializer`.
- **`document.styleSheets`.** Una hoja por `<style>` y `<link rel=stylesheet>`. De un `<style>`:
  `cssRules` (`selectorText`, `style.getPropertyValue`, `type`), `insertRule/deleteRule/addRule`
  (reescriben el `textContent`, asi CSS-in-JS en modo rapido sigue funcionando). De un `<link>`:
  `cssRules` lanza `SecurityError`, igual que una hoja de otro origen en un navegador.

## Fuera de alcance (deliberado, anti-fingerprinting / SOP)
`navigator.geolocation/mediaDevices/permissions/clipboard/serviceWorker`, WebGL, `AudioContext`,
`Notification`, `window.postMessage` (SOP por construccion), `SharedWorker`. Pendientes de hito
propio: `indexedDB`, `ReadableStream`/`Response.body`, `WebAssembly`, `EventSource`.
