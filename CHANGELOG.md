# Changelog

### Bug Fixes

  * fix: V-002 security vulnerability (ace8416) by orbisai0security
  * fix: V-001 security vulnerability (d67cbb0) by orbisai0security

### Documentation

  * docs: auto-generate knowledge base with readmenator (7be91aa) by readmenator-bot
  * docs: FFmpeg dependency, CLI flags en README + doctrina V-002 en CLAUDE.md (c38d307) by grisun0
  * docs: auto-generate knowledge base with readmenator (b5d0184) by readmenator-bot
  * docs: auto-generate knowledge base with readmenator (2fa1b42) by readmenator-bot
  * docs: auto-generate knowledge base with readmenator (91aa3c5) by readmenator-bot

### Chores

  * some improivements (580bb5d) by grisun0
  * 3d awesome vieew in doc sphere (a97699d) by grisun0
  * Update static.yml (315943d) by Grisuno
  * 3d awesome vieew in doc (a3ba710) by grisun0
  * - webfont_load.h/c nuevo: wf_load_document (extern sheets en orden + inline <style> en orden documento, mismo orden que el worker) con first-wins por (familia,bold,italic), fallback in-list (≤4 URLs), resolución https/data:, ctype allowlist, topes por-cara/total/fetches. fetch==NULL (no trusted) = no-op. - data: se decodifica en el scanner a bytes propios (is_data), porque un data: URL jamás cabe en url[1024] — hallazgo por test rojo (test_data_url_registers falló primero por el drop del scanner y por el skip de URL vacía; ambos verdes ahora). wf_ref_move para transferencia sin doble-free (con test ASan). - Tests: 8/8 loader (stub fetch hermético + DejaVu real cuando existe + first-wins rojo-sin-fix verificado), 13/13 scanner, ASan limpio (0 leaks propios, supresiones del sistema aplicadas), fuzz-wf+data_url 100k runs limpio. - make test 0 fallos, drops/layout-diff/drift verdes. Spec actualizada (contrato loader + diseño data:). (606250e) by grisun0
  * js and css from cdn (e3f691c) by grisun0
  * Merge remote-tracking branch 'origin/main' (835441f) by grisun0
  * - el.style escribe atributo real (src/js_dom.c:739). Antes objeto suelto, repaint nunca veía mutación. - getComputedStyle(el) lee inline (src/js_dom.c:1412). Antes '' siempre. jQuery .css() ya resuelve. - ResizeObserver + MutationObserver sintéticos una entrega (src/js_dom.c:1400). disconnect suprime. Cero geometría real. - Spec spec/js_dom.md:7j. Tests 4 nuevos rojos -> verdes. 155/155 en test_js_dom. - Validado: make test todo verde. ASan test_js_dom verde. make drops OK. make layout-diff byte-idéntico. fuzz-jsdom sin crash (solo timeout). - Prueba viva: el.style.display='none' esconde bloque en --dump-dom. getComputedStyle().color loguea red. (9958e56) by grisun0
  * Merge security-export into main (cf07589) by grisun0
  * Merge docs-export into main (7ce790c) by Grisuno
  * chore(security): export issues + knowledge base + agent docs + network links (02f2dc2) by grisuno security-export bot
  * doc (50e8303) by grisun0
  * doc (03c4701) by grisun0
  * Tanda 41: márgenes auto en columnas flex; un reemplazado sin caja no cierra <body> (9ff0027) by grisun0
  * Tanda 40c: alfa en paradas de degradado; pseudo-clases dentro de :not()/:is() (b2f36ab) by grisun0
  * Tanda 40b: ítems flex sin re-abrir html/body, márgenes de ítem, resets de enlace (ea896db) by grisun0
  * Tanda 40: sitios de allow.conf contra Firefox (f266e51) by grisun0
  * js vendors (4f08ff7) by grisun0
  * doc (1304a42) by grisun0
  * doc (8753e0b) by grisun0
  * Tanda 32: paridad Firefox en sitios allow∩js — lobste.rs 42.60 -> 1.44 (cf44019) by grisun0
  * sin pv_kind nuevo, sin cambio IPC. <iframe src> se emite como PV_LINK reutilizando href ya cableado en write_view/read_view. Display-only, cero fetch (el fetch sigue gateado por net en jd_process_iframes, solo allow∩js). Sin flag de confianza para mostrar; clicar navega por ln_resolve con política completa. (60ef148) by grisun0
  * Readmenator(Doc) Knowleadge base updated and graphs - commit automated by readmenator (pip install readmenator) (258c075) by grisun0
  * - css_unescape_into: decodifica escapes a UTF-8 (FFFD en NUL/sustitutos/>U+10FFFF, escapes = codepoint directo sin remap) - :before/:after legacy + pool CSS_MAX_CONTENT_URLS 256 (400+ reglas reales lo desbordaban en silencio) - Rama hoja-vacía admite content_before sin texto propio (una emisión, camino con-texto intacto) - content:none|normal parsea a vacío explícito (era bad-value en drops) (160e8f1) by grisun0
  * New modules, one contract each: - include/css_decl.h — P_* slots, css_decl struct, css_round_clamp single owner (unified 4 copies). - src/css_values.c (cv_) — color/bg. 5 tests. - src/css_gradient.c (cg_) — gradients/bg-image/background shorthand. 6 tests. - src/css_box.c (cb_) — lengths, box4/2, <length-percentage>, align/font/display/gap/justify, grid tracks, calc. 8 tests. - src/css_text.c (ct_) — font/text/opacity/shadow/spacing/shadow/aspect. 5 tests. - src/css.c 7068 → 5041 lines. Dispatch/cascade/apply only, thin wrappers. (6beb937) by grisun0
  * H3 css split prep: - New include/css_values.h + src/css_values.c. Owns cv_parse_color, cv_interp_color, cv_color_ok, cv_bg_alpha_of, cv_interp_bg. Pure, NULL fail-closed, url() never fetch. - src/css.c now delegates wrappers. Net -60 lines dup logic. No behavior change. - Spec spec/css_values.md. Test tests/test_css_values.c 5/5 pass. Makefile links css_values.o everywhere css.o links, fixes freedom link. - test_css still 237 pass + same 4 preexisting fails. test_tab 81 pass. test_page_view 152 pass. H4 cursor + oof: - Oof leaves-flow already correct per spec/box_engine.md Stage 2e. Verified mode1 .card-body absolute bottom overlay: anchored path holds, no change needed. No security downgrade. - Cursor gap fixed in gui/browser_ui.c cursor_at_point: text-frag hit first, then topmost rc_box border-box fallback with same left+bx->x, origin+bx->top mapping + pointer-events:none respect. Closes border/padding/empty-box miss. Visual identical, hover shape only. - Build build/freedom links clean. (2612b7c) by grisun0
  * whitespace inline en tablas (fd67d84) by grisun0
  * doble cómputo margen en columna pulled (5603e10) by grisun0
  * documentation (a78e82a) by grisun0
  * - float_oid/oside/oml/omr… → el ancestro flotante más externo cruza ahora page_view→render_doc→tab→dom_debug (float_oid, se pliega a -1 cuando el nearest ya es el outer ⇒ camino viejo byte-idéntico). - Columna de flotantes diferidas (defer_split/defer_flush, cotas estáticas), que empaquetan cada founder en su columna contra el contenido anterior (fx_float_pack_m). Las columnas estrechas se trazan primero para que sus exclusiones acorten las historias. Sin nesting ⇒ fail-open, sin cambios. - Tres brechas satélite de paso: <img> en subárbol absoluto sin ancla (caía a flujo), posiciones estáticas de badges/Posted by en columnas flotantes (pintaban en 0,0), y un pv_box_info leído sin inicializar (render no-determinista). (2fbe6c9) by grisun0
  * Pull-up cross-band (9da9244) by grisun0
  * [✓] WPT: verificar red y seleccionar subset estático (overflow/sizing/flex/grid) [✓] WPT: harness tests/wpt/ + target make wpt (reusa pngdiff + perfil parity) [✓] WPT: primera pasada, calibrar umbral, congelar expected.tsv (a3c5f8d) by grisun0
  * display:none ahora también oculta imágenes (76df93c) by grisun0
  * El grid de tarjetas (row-cols-* con un badge position:absolute por tarjeta) colapsaba a una columna por dos bugs distintos de CSS 2.1 §9.7 1. container_box_of leía el sello cont_box_id del primer run (gui/browser_ui.c), que responde por el contenedor más interno. Un contenedor sin caja propia (.row de Bootstrap) adoptaba la caja de su primer ítem como ancho de layout → nada cabía al lado de nada. Ahora resuelve por el padre común de las cajas-raíz de sus ítems; solo la grilla <table> sintetizada conserva el fallback. 2. Un bloque out-of-flow solo se salteaba si no tenía cont_id. Nuevo predicado block_leaves_flow (oof y ancla bt_oof_root >= 0), usado en los tres sitios de salteo (scan de run maximal, segmento por-ítem, bandas). Fail-open: sin ancla queda en flujo. 3. Propina: bt_resolve_positioning_ex gana un bitmap placed[] — un badge absoluto cuyo bloque contenedor nunca se abrió ya no resuelve contra un rect 0×0. (7ec6c99) by grisun0
  * @keyframes deleted css fixed (625cd11) by grisun0
  * - --dump-timings en src/freedom.c: mide con CLOCK_MONOTONIC del lado confiable y vuelca a stdout stage=fetch/ipc/rd_build/paint con n/last/min/max/median. FREEDOM_PERF=1 lo activa también. Opt-in, Zero Knowledge. Spec en spec/freedom.md. - make bench: corre el binario sobre tests/bench/*.html (offline, con --author-css) y reporta tiempos por etapa. - Link: perf_trace.o agregado al binario freedom (faltaba). - Test: test_dump_timings_prints_stages en tests/test_freedom.c (3db653e) by grisun0
  * libcurl changed (4cd3569) by grisun0
  * deleting files (8386e5f) by grisun0
  * src/page_view.c — los márgenes horizontales (margin-right:320px) ahora generan caja de box (CSS 2.1 §10.3.3). Resultado medido: (01f99d5) by grisun0
  *  some new tools (b4ad918) by grisun0
  *  some bug fixing (7f59696) by grisun0
  *  palabras CSS-wide (inherit/initial/unset/revert — reclaman el slot y no escriben), transparent/currentColor (centinelas   negativos que todo test >= 0 rechazaba), width/height:auto, calc() con porcentaje, hsl()/rgb() fraccionarios, background-position negativo (sprites), content (0059596) by grisun0
  *  1. El colapso de márgenes verticales no existía. open_box insertaba max(prev_bottom, th->paragraph_gap) (6cd715f) by grisun0
  * The fix treats a length as what it is — the affine function a + b·font-size. cl_lp carries the derivative; the coefficient is read out of the existing cl_unit_scale table   (probe ctx at font_size 1.0), never a second hand-written one, so a new §6.1 unit gets its coefficient free. calc() propagates it; min/max/clamp are piecewise, not affine, so   they fail closed to derivative 0 (0 corpus cases). It folds in one place, when the element's cascade closes — re-applying the winner through apply_decl rather than a   parallel slot→field switch that would go stale. (6e87f75) by grisun0
  *  claude --resume 4cb76610-9e91-47c3-8e11-8f1d8729ff9a (95b0172) by grisun0
  *  I built and ran make parity against Firefox 140. (5a5e7a1) by grisun0
  *  One canonical <length> resolver — new css_length module (e2b4aff) by grisun0
  *  The root element was outside CSS inheritance. This was the big one. The context walk ended with if (p == base) break; and base is <body> (1c3b499) by grisun0
  *  1. line-height: normal valía 1.2× la caja natural (5168b46) by grisun0
  *   1. @media al ancho de render (197463d) by grisun0
  * rem estaba clavado en 16 px. (10a7970) by grisun0
  * bored work (2755dc5) by grisun0
  * some day we can render a web :_) (c3f43af) by grisun0
  *  Bug 1 — Búsqueda DuckDuckGo salía con cajas de resultado vacías (352e87c) by grisun0
  *   1. src/page_view.c — the whitespace between </td> and <td> (a text node whose parent is <tr>/<tbody>/<table>) was emitted as a stray (85c5691) by grisun0
  * slashdot is readdeable :D (06c2248) by grisun0
  * 1. Flex‑item basis measured replaced elements as raw markup‑text — the dominant bug. measure_item_content_w flowed every flex item through flow_text_block   item's markup string was measured as prose: a 24 px icon asked for a ~268 px flex‑basis. That spread nav icon rows across the whole line and shrank the neighbouring text to   one word per row  New replaced_item_width() measures each replaced element by its real intrinsic size. This is why a simple flex:1 two‑column   layout looked fine but icon/nav rows exploded.   2. SVG single‑axis sizing — an SVG given only height (or only width) now derives the other axis from the viewBox aspect ratio, like <img>, instead of grabbing the raw   viewBox width (which ballooned a 1792‑unit icon to the container).   3. SVG fill from CSS — css.c now parses fill; sv_parse_ex() seeds the SVG root fill so shapes with no fill of their own take the CSS colour. Slashdot's YouTube/Mastodon   icons went from black → correct red/blue; the .social svg{fill:#fff} pattern paints white. Done without a new IPC field (reused fg_rgb), avoiding the documented codec trap.   Regression‑checked: no‑CSS SVGs stay black, currentColor still works. (da2a5f6) by grisun0
  * adsasd (9a5c937) by grisun0
  *  1. Ítem flex con contenido mixto [texto, .row anidado, texto] se decidía por su primer run → el anidado se apilaba. Ahora layout_container particiona el ítem en segmentos y   recursiona por contenedor anidado.   2. Props flex del wrapper (.col{flex:1 0 0%} envolviendo un .row) se perdían — nuevos campos pv_cont_def.item_* capturados en el walk e hilvanados por el códec IPC. Sin esto   el .col no crecía y el header colapsaba.   3. La causa dominante: los runs reemplazados (<input>/<select>/<img>/<svg>) perdían la membresía flex en los tres cruces del códec (emisión en page_view, copia en rd_build   gateada a TEXT/LINK/VIDEO, y read_view bajo if(kind!=PV_INPUT)) → cont_id=-1 rompía la corrida del contenedor y lo fragmentaba en piezas apiladas.   4. emit_replaced_row extraído y compartido por el flujo plano y el de columna flex (antes una <img> en columna era placeholder de ancho 0 y desaparecía — incluyendo el SVG   inline, que ahora pinta bien en columnas).   5. El painter ignoraba x_off/ancho de columna para RC_IMAGE/VIDEO/INPUT (pintaba en x=0) → solape; ahora usa left+x_off y bg_w. (fa33443) by grisun0
  * 1. src/css.c — interp_flex_basis() ahora parsea porcentajes (flex-basis: 75% → codificado como -1000750 en el campo int existente, sin tocar el codec IPC). 2. gui/browser_ui.c — flex_item_basis() resuelve la codificación contra el ancho del contenedor (content_w * per_mille / 1000). 3. tests/test_css.c — actualizado el test que esperaba CSS_LEN_UNSET para flex-basis:10%. (aa6c939) by grisun0
  *   Flex/grid anidado (9dc958c) by grisun0
  * 1. font-size absoluto se aplicaba como multiplicador. h1{font-size:40px} salía a 80px — el porcentaje se multiplicaba por la escala UA del título. Ahora   px/pt/rem/viewport/keywords resuelven contra el root de 16px y reemplazan la escala UA; em/% siguen relativos y encadenan hacia afuera hasta topar con una absoluta   (.card{14px} .card h3{1.2em} → 16.8px). (7eef64a) by grisun0
  * 1. CSS: arrays dinámicos (cero hardcodes) src/css.c: - css_sheet.decls: css_decl[CSS_MAX_DECLS] fijo → css_decl *decls + size_t decls_cap dinámico - css_sheet.rules: array fijo → css_rule *rules + size_t rules_cap dinámico - css_sheet.sels: css_sel[CSS_MAX_SELS] fijo → css_sel *sels + size_t sels_cap dinámico - Crecen con realloc (×2) bajo demanda, como cualquier navegador real - css_free() libera los 3 arrays + el struct → sin memory leaks - Tamaños iniciales chicos (256/512/1024), sin castigo de memoria 2. PNG margin dinámico (no más 24px hardcodeado) - browser_ui.c: write_doc_png usa html_margin_top del documento CSS - page_view.c: lee margin-top de <html> y <body>, incluso margin:0 (0a17870) by grisun0
  * SVG en línea + paridad de render medida contra Firefox (6a14388) by grisun0
  * Nuevas funciones puras bt_oof_anchor/bt_oof_root en box_tree (spec   Stage 2d, 6 tests CMocka, fail-open ante cadenas hostiles), chequeo antes de la rama flex/grid, y la pasada posicionada ahora mide y pinta el subárbol completo. (3a20795) by grisun0
  * P5 partial: form control box pipeline groundwork (b3ee9cf) by grisun0
  * OOF visibility+static position (d96c2ca) by grisun0
  * CLAUDE.md: Stage 2c clip:rect + overflow:hidden+height:0 milestones (f080836) by grisun0
  * P4: overflow:hidden + height:0 clips in-flow content (4e21940) by grisun0
  * Remove test artifacts from repo root; CLAUDE.md clip:rect milestone (36a74a0) by grisun0
  * P3: CSS clip:rect() for positioned boxes (visually-hidden pattern) (ffc1d55) by grisun0
  * bt_box_hidden() — función pura, cycle-bounded, fail-closed — recorre parent_id chain (dcb3964) by grisun0
  * CLAUDE.md: add preserved_view threshold fix doctrine (6d65bc5) by grisun0
  * Fix preserved_view fallback threshold in tab.c (249790a) by grisun0
  * visibility+hstatic+position (5b3ec20) by grisun0
  * Stage 2b: OOF static position + visibility gate (0e9736f) by grisun0
  * padding:0/border:0 (el reset que media web declara) registraba una caja sin decoración por elemento, y el painter rompe línea en cada transición de caja. (77adf25) by grisun0
  * ALT + ENTER to fullscreen video player :D (c23f092) by grisun0
  * 1. Flex no flexeaba. Un ítem sin flex-basis recibía un reparto en partes iguales (content_w/n), y el motor flex solo se usaba si algún ítem declaraba una propiedad flex.   Consecuencia: justify-content era un no-op (columnas iguales no dejan sobrante) y una nav de 3 enlaces ocupaba la página entera. Ahora el basis es el max-content medido (+   padding/borde/margen), y todo contenedor flex pasa por el motor. La medición reusa el flow_text_block real sobre un layout descartable, así no puede divergir del render. (c1cc039) by grisun0
  * 1. Empty decorated elements now paint (src/page_view.c) — a box-generating leaf (css_has_boxdeco + no child elements/text) emits a zero-content placeholder run carrying its   box, so the existing open_box/close_top_box machinery reserves box_h and paints it. Fixes bars, spacers, icons, empty divs.   2. Flex/grid items paint their box (gui/browser_ui.c layout_container) — each item's root box now reserves box_h/min-height, insets content by padding+border, and gets an   rc_box so its background/border/radius/shadow paint. Fixes card decoration and collapsing grid tiles.   3. DRY refactor — extracted rc_box_copy_decoration shared by open_box and the container path (boy-scout). (e6e7391) by grisun0
  * grid-template-rows wiring (b2c0022) by grisun0
  * 1. Grid order support (gui/browser_ui.c) The CSS order property sort was only applied for flex containers. Now it runs for grid items too. Items with explicit order values are stably insertion-sorted into layout slots before grid auto-placement. Previously grid items always rendered in DOM order regardless of order. 2. CSS transition parsing (src/css.c, include/css.h) Added full parsing for transition shorthand + longhands (transition-property, transition-duration, transition-timing-function, transition-delay). Supports none/all/opacity/transform as property values, ms/s durations, and 5 easing functions. Runtime interpolation is deferred. All 4 fields stored in css_style. 3. vertical-align: middle/top/bottom (src/css.c, include/css.h, gui/browser_ui.c) Added CSS_VA_MIDDLE/TOP/BOTTOM to the enum. The painter applies baseline shifts: middle centers within x-height (+0.20×font), top aligns to parent ascent (-0.50×font), bottom aligns to parent descent (+0.50×font). 4. Wayland cursor types (gui/browser_ui.c) Replaced the binary hand-vs-arrow cursor logic with a CSS-cursor-type mapping. Now loads 5 cursors: left_ptr (arrow), pointer/hand2/hand1 (hand), xterm (I-beam), move, watch (spinner), not-allowed. cursor: none hides the cursor. auto resolves to hand over links, arrow elsewhere. (68f45dc) by grisun0
  * bugfoxong in empy divs (5bd52ee) by grisun0
  * bug fixing in audio in video reproductions :D (99f28a0) by grisun0
  * bug fixing in video reproductions :D (80a051f) by grisun0
  * viewport vw hw vmin vmax and some bug fixing :) (203b9b0) by grisun0
  * filter: brightness(), contrast(), sepia(), invert(), saturate(), hue-rotate() (95bba4e) by grisun0
  * 1. Non-solid border rendering (gui/browser_ui.c:5621-5730) border-style: dashed/dotted/double/groove/ridge/inset/outset — all now render visually instead of collapsing to solid. - Uniform (same width/style/color all sides + border-radius): dashed/dotted use cairo_set_dash on the rounded stroke; double draws two concentric rounded strokes at 1/3 and 2/3 of the border width. - Non-uniform (per-side): switched from cairo_fill rects to cairo_stroke lines, using dash patterns for dashed/dotted and parallel strokes for double. - 3D styles (groove/ridge/inset/outset): use color lightness modulation (0.6× darken, 1.4× lighten) per-side following the CSS bevel convention (light top/left, dark right/bottom for outset/ridge; reverse for inset/groove). - Outline also updated with dashed/dotted/double support. 2. Wavy text-decoration (gui/browser_ui.c:5800-5840, 5856-5960) text-decoration-style: wavy — previously fell back to solid. Now draws an approximate sine wave using Cairo cubic beziers with configurable amplitude/wavelength proportional to the line thickness. Double text-decoration also added (two parallel strokes). A shared static helper paint_deco_line() handles all 6 decoration styles (solid/dashed/dotted/double/wavy) for underline, strikethrough, and overline, keeping the logic in one place. 3. Table rowspan height fix (src/box_tree.c:238-255) Added rowspan height redistribution in layout_grid(). Previously, a rowspanning cell's content height only contributed to its starting row; the subsequent spanned rows were unaffected, causing the cell's paint rect to be too short. Now the cell distributes any height deficit across all spanned rows (adding to the last one), and the cell's h is set to the cumulative spanned row height so background/border rects cover the full spanned area. (70aa9d0) by grisun0
  * Update README.md (3f07d86) by Grisuno
  * Now we have video support in pages like jkanime.net :D (0f4c73c) by grisun0
  * Now modify video_read_frame to use blocking reads for frame DATA (after the tag) (0e43a43) by grisun0
  * async js (f26d002) by grisun0
  * position: sticky was fully parsed and stored, and the box tree handled it (70841de) by grisun0
  * src/css.c: Extended @keyframes stop struct with transform_tx/ty/sx/sy/rotate; parser now extracts all P_TRANSFORM_* from keyframe declarations (not just P_OPACITY); css_resolve_anim_keyframes copies transform values (4a6d04d) by grisun0
  * bugfixing (51ed02f) by grisun0
  *  R0 — Instrumentación (perf_trace/pt_, nuevo módulo puro): anillo acotado de spans por etapa (fetch/parse/style/ipc/rd_build/layout/paint/commit/shape), --dump-timings   headless, FREEDOM_PERF=1 en la GUI, make bench con corpus local de 5 páginas. Baseline real capturado en este host: commit (escritura de PNG) y layout dominan en páginas   largas/con imágenes; un fetch trivial a https://example.com mostró fetch=276ms, layout=73ms. (e7d0927) by grisun0
  * Doc(creation documentation) a brand new KNOWLEDGE_BASE.md (449e6c2) by grisun0
  * CSS_MAX_KF_STOPS constant, anim_nkf/anim_kf_pct[]/anim_kf_val[] fields en css_style (eb2e645) by grisun0
  * Update README.md (3072348) by Grisuno
  * Doc(creation documentation) a brand new KNOWLEDGE_BASE.md (78527c0) by grisun0
  * Doc(creation documentation) a brand new KNOWLEDGE_BASE.md (a3b006a) by grisun0
  * some wiring features in background (543e47a) by grisun0
  * some wiring features (fa046cd) by grisun0
  * @font-face parsing + storage (7c7bc80) by grisun0
  * workflows (897f414) by grisun0
  * workflows (a025469) by grisun0
  * workflows (0474906) by grisun0
  * sound (5170785) by grisun0
  * sound (0c6939b) by grisun0
  * Doc(documentation) Update the README (c5dbe40) by grisun0
  *  HTMLCanvasElement (66dbf4d) by grisun0
  * CSS :has() selector (2bcf8c9) by grisun0
  * grid-row: span N (51df945) by grisun0
  * Add animation-iteration-count and timing-function to IPC + GUI (5fd6dd9) by grisun0
  * Update README.md (3cbec09) by Grisuno
  * Doc(documentation) Update the README (b25503c) by grisun0
  * csel_parse — div::before  @keyframes name { 0% { opacity:0 } 100% { opacity:1 } } + from/to + % (24967da) by grisun0
  * Doc(creation documentation) a brand new KNOWLEDGE_BASE.md (340b97e) by grisun0
  * arrayBuffer ::before/::after selector parsing + matching (content paint deferred) (5d1bf8a) by grisun0
  * radial-gradient(#start, #stop1, ...) (7ecb6f5) by grisun0
  * Nested compositor tree  arrayBuffer binary background-position defer scripts customElements  DOM events (975c679) by grisun0
  * background-position — Parse left/center/right/top/bottom/px values. Full pipeline (798e735) by grisun0
  * anim part 3 (da7e466) by grisun0
  * anim part 2 (449865c) by grisun0
  * anim not wire yet (c89e0c1) by grisun0
  * new P_BG_IMAGE_URL slot, per-parse URL pool so css_decl stays int-only (a60cc1e) by grisun0
  * new P_BG_IMAGE_URL slot, per-parse URL pool so css_decl stays int-only (df8e36c) by grisun0
  * css trasnform :D (92a6d73) by grisun0
  * Hito M1.2: CSS transform (2D translate), primera propiedad de transformación (e74e6ca) by grisun0
  * Hito M1.1 (incremento 4/N): opacity in-flow + mix-blend-mode + isolation (4475fd4) by grisun0
  * negative z-index was painting on top of in-flow content instead of behind; fixed in both the screen and headless PNG paths, with a pixel-level (1d1a90a) by grisun0
  * Hito M1.1 (incremento 3/N): opacity de grupo REAL, cableado extremo a extremo (223c7e9) by grisun0
  * Fix: z-index negativo pintaba encima del contenido in-flow, no detrás (ee57d59) by grisun0
  * Hito M1.1 (incremento 2/N): cx_sort cablea bt_resolve_positioning (81f72b8) by grisun0
  * Hito M1.1 (incremento 1/N): fundación pura del compositor (cx_) (b588415) by grisun0
  * Nuevas ui_render_png_images/ui_render_pdf_images: decodifican vía el worker confinado (locales de disco, remotas bajo política) — los bytes hostiles nunca tocan el proceso confiable. (53b1149) by grisun0
  * proto  Codec IPC (0b58319) by grisun0
  * módulo puro wc_ deriva la tabla completa de capacidades de una página (js/css/images/net/cookies + los forward persist/readback/gpu/sw/rtc) desde las señales de confianza, reusando los predicados de   js_policy. Gating por doctrina del owner: leak-free global (toggle o presentation-trust), privacy-sensitive doble-gateado allow.conf ∩ js.conf. Sin cambio de comportamiento — es la unificación que evita reescribir 4   sitios por cada campo nuevo en los milestones siguientes. (400c3c7) by grisun0
  * Merge branch 'main' of https://github.com/grisuno/FreeDom (c9f20a7) by grisun0
  * 1	text-align: justify	✅ Completado — distribuye slack entre espacios en el painter + 3 hit-tests 2	V-001 SIZE_MAX guards	✅ Completado — ~17 guardas añadidas en tab.c, freedom.c, page_view.c, etc. 3	V-002 calloc	✅ Completado — ~10 malloc(n*sizeof) → calloc 4	V-004 snprintf	✅ Completado — ~8 patrones endurecidos contra truncamiento 5	Shared utilities	✅ Completado — include/util.h con write_full/read_full/utf8_seq_len/fnv1a, ~111 líneas dedup de 8 archivos (882d500) by grisun0
  * Merge pull request #37 from grisuno/security-export (1886706) by Grisuno
  * chore(security): export issues, dependabot & codescan alerts (33e39b8) by grisuno security-export bot
  * 1	text-align: justify	✅ Completado — distribuye slack entre espacios en el painter + 3 hit-tests 2	V-001 SIZE_MAX guards	✅ Completado — ~17 guardas añadidas en tab.c, freedom.c, page_view.c, etc. 3	V-002 calloc	✅ Completado — ~10 malloc(n*sizeof) → calloc 4	V-004 snprintf	✅ Completado — ~8 patrones endurecidos contra truncamiento 5	Shared utilities	✅ Completado — include/util.h con write_full/read_full/utf8_seq_len/fnv1a, ~111 líneas dedup de 8 archivos (3b1a5f3) by grisun0
  * Smoth scroll (3dbbc48) by grisun0
  * Doc(creation documentation) a brand new KNOWLEDGE_BASE.md (f07bc99) by grisun0
  * Merge branch 'main' of https://github.com/grisuno/FreeDom (6ee538f) by grisun0
  * a hotfix in prefs.c (df3053f) by grisun0
  * Merge pull request #31 from grisuno/docs-export (1532650) by Grisuno
  * some news properties in js (8d8419a) by grisun0
  * some news properties in js (688dccb) by grisun0
  * Update README.md (301ce74) by Grisuno
  * some news properties css (bd8d9d4) by grisun0
  * some news properties css (24efb7e) by grisun0
  * video is not playable yet but still working (64ad3b3) by grisun0
  * video is not playable yet but still working (a3dac05) by grisun0
  * Doc(creation documentation) a brand new KNOWLEDGE_BASE.md (12920f7) by grisun0
  * hls (00ea4d2) by grisun0
  * pipe line to reproduce videos (abcffbf) by grisun0
  * free  bug control + c to debug :D (8b2104f) by grisun0
  * Update CONTRIBUTING.md (fc4e977) by Grisuno
  * buffer overflow large pages fixed :D (3bc7eee) by grisun0
  * deb package (bc7dc52) by grisun0
  * gitignore tmp/ directory (a7711df) by grisun0
  * Fix pre-script DOM snapshot + clean up debug output (2e09b37) by grisun0
  * Fase 4: Audio decode en media decoder + MD_AUDIO_FRAME protocol (471707b) by grisun0
  * Fix jQuery :visible pseudo-class — getClientRects, offsetWidth/Height (58296ef) by grisun0
  * Fix jQuery/Bootstrap compat: cloneNode deep, boolean attrs, ownerDocument, createDocumentFragment (c62fc57) by grisun0
  * GUI integration: HLS→decoder→frame painting pipeline (f6bdaf6) by grisun0
  * Merge branch 'main' of https://github.com/grisuno/FreeDom (09e51e4) by grisun0
  * Fase 0-1: video pipeline + iframe interceptor + decoder FFmpeg + HLS parser + fix V-002 (ae2830d) by grisun0
  * Merge pull request #33 from orbisai0security/fix-repo-freedom-fix-v-002-browser-ui-buffer-overflow (ba8bf3f) by Grisuno
  * Merge pull request #32 from orbisai0security/fix-repo-freedom-fix-html-parse-dup-bytes-overflow (2ce5a98) by Grisuno
  * new deb package (0d45cd7) by grisun0
  * Security(advisor) fix: add bounds check before memcpy in html_parse.h thanks to orbisai0security, thanks you bro :D (897e4dc) by grisun0
  * Doc(creation documentation) a brand new KNOWLEDGE_BASE.md (1c676fe) by grisun0
  * some impersonates features :D (d43bbcc) by grisun0
  * some js and bot antidetect, but google still not working well (5be4fd1) by grisun0
  * cookies :D on memory (1a882a5) by grisun0
  * some love in js (77ecb87) by grisun0
  * some love (f4fc68f) by grisun0
  * Doc(creation documentation) a brand new KNOWLEDGE_BASE.md (d851013) by grisun0
  * :hover, , focus, active, focus-within, focus-visible :visited (ae79c84) by grisun0
  * Doc(creation documentation) a brand new KNOWLEDGE_BASE.md (69ab729) by grisun0
  *   - Preferencias persistentes — tema (oscuro/sepia), zoom, toggles de imágenes/CSS, política JS, Tor/I2P y modo lectura sobreviven al reinicio. Un env explícito (FREEDOM_JS, etc.) sigue ganando por sesión.   - Marcadores — Ctrl+B marca/desmarca (con checkmark en el menú); se navegan en about:bookmarks (Bookmarks (127a141) by grisun0
  * - src/box_style.c — Added <menu> as BLOCK in UA stylesheet - src/page_view.c — Added LXB_TAG_MENU to is_block_tag; added is_block_like() and causes_block_break() helpers that honor author CSS display values; modified all 4 check points (block detection, float, hbox, boxdeco) to use CSS display overrides - include/css.h — Added CSS_DISP_LIST_ITEM to css_display enum - src/css.c — Added display: list-item handling in interp_display(); added px/em/rem support to interp_lineheight() - tests/test_css.c — Updated test_inline_line_height for the new line-height px/em behavior (f8c2bcb) by grisun0
  * prefetch (d3d7591) by grisun0
  * Merge pull request #26 from grisuno/docs-export (f973b6f) by Grisuno
  * Bug fixing in render_current() (31453b5) by grisun0
  * Bug fixing in render_current() (b1508f7) by grisun0
  * Merge pull request #25 from grisuno/docs-export (db5cff8) by Grisuno
  * Doc(creation documentation) a brand new KNOWLEDGE_BASE.md (a0c7d3f) by grisun0
  * min()/max()/clamp() — como valor completo (width: min(600px, 40em)) y anidadas en calc(); chequeo dimensional, acotadas por CSS_MATHFN_MAX_ARGS (8) y el depth compartido de calc.   - Propiedades lógicas — margin-inline(-start/-end), margin-block, padding-inline/block, inset-inline/block, inline-size/block-size y sus min-/max- → mapeo físico LTR (documentado: la cascada no conoce direction al   interpretar).   - Shorthands — place-items/place-content/place-self, gap: <fila> <columna> (2 valores → row-gap+gap), y font (italic bold 32px/1.5 monospace).   - white-space: break-spaces → pre-wrap. (overflow: clip y text-align: start/end ya estaban soportados.)   - Bug real encontrado de paso: interp_gap parseaba gap: 1em como 1px y aceptaba 50% como 50 — ahora pasa por interp_len (em/rem/calc correctos, junk falla cerrado).   - pointer-events: none — viaja en pv_box_def (como cursor); el GUI lo resuelve por la cadena de cajas y excluye el elemento de hover/click/cursor en los tres hit-tests.   - image-rendering: pixelated/crisp-edges — hereda por runs → filtro CAIRO_FILTER_NEAREST en paint_image_row.   - caret-color — hereda hasta el run del input → tiñe el caret del control enfocado (respeta force-theme).   - content-visibility: hidden — se pliega en visibility del box def (no pinta, reserva espacio; misma simplificación documentada que collapse), sin campo IPC nuevo.   - Refactor boy-scout: pv_set_text_ext pasó de 20 parámetros posicionales a const pv_text_ext * (struct pública); además los runs de imagen/input ahora reciben la ext resuelta (antes se descartaba), y read_view ya no   pierde la ext de los inputs. (4c8c6bc) by grisun0
  * Doc(creation documentation) a brand new KNOWLEDGE_BASE.md (36d7854) by grisun0
  * some love to css and new deb (beb6e02) by grisun0
  * some love to css (22f324f) by grisun0
  * mix-blend-mode object-fit list-style-position font-kerning text-rendering font-stretch resize scroll-behavior touch-action overscroll-behavior backface-visibility (8878ba1) by grisun0
  * background-repeat background-size background-clip  background-origin background-attachment contai  content-visibility image-rendering color-scheme accent-color print-color-adjust forced-color-adjust (209ff6e) by grisun0
  * outline-width/-style/-color border-collapse border-spacing empty-cells table-layout font-variant hyphens user-select caret-color appearance pointer-events (84001ad) by grisun0
  * Nine properties added: min-width, height, min-height, max-height, text-decoration-color, text-decoration-style, direction, outline-offset, tab-size (78449e3) by grisun0
  * Overflow clipping for positioned boxes, Negative z-index two-pass painter (7813de5) by grisun0
  * Merge branch 'main' of https://github.com/grisuno/FreeDom (3f25535) by grisun0
  * - flex-direction: row-reverse — los flex items ahora se invierten visualmente en el eje principal (el primer item va a la derecha, no a la izquierda). - flex-direction: column-reverse — los items en columna se invierten visualmente (último item arriba, primero abajo). Antes caía a orden de documento. - flex-wrap: wrap-reverse — las líneas se invierten en el eje cruzado (primera línea abajo, última arriba). Antes se trataba como wrap normal. (225a3da) by grisun0
  * Update README.md (fa37c4d) by Grisuno
  * full Grid (fr units, span, etc.), position (absolute/fixed/sticky no fully painted), overflow clipping, advanced flex (e39c9f8) by grisun0
  * - ov_box_clips(d) — detecta si un pv_box_def tiene overflow:hidden/scroll/auto - ov_collect_chain(doc, block_id, out, cap) — camina ancestros y colecciona los que clip (outermost-first) - ov_find_box(L, bid) — lookup de rc_box por block_id - ov_content_rect(bx, def, origin, left, ...) — computa el padding-box (content rect) en coordenadas de página - ov_reconcile(cr, stack, depth, doc, bid, L, origin, left) — reconcilia la pila de clips Cairo: pop de clips que ya no aplican, push de los nuevos (common-prefix rule) (8c36fc6) by grisun0
  * now we can loggin successfuly into lazyc2 :D (154dbdd) by grisun0
  * bug fixing in post :D (13e2eac) by grisun0
  * Basic Auth supported :D (1e7e0a1) by grisun0
  * CSS: visibility: visible|hidden|collapse, cursor, text-overflow: ellipsis, word-break/overflow-wrap/word-wrap (391117e) by grisun0
  * Custom properties + var() ,flex-wrap real multi-line packing, align-items/align-self , row-gap (7bfb3f0) by grisun0
  * float (none/left/right) y clear (none/left/right/both), fail-closed; oráculo de fuzz reforzado. (981e1c3) by grisun0
  * La JavaScript de Slashdot pasó de 14 errores de consola a 0 — jQuery ahora carga completo y $ queda definido (dab5746) by grisun0
  * dispatch_click: strdup the href before apply_click_result (2410a9f) by grisun0
  *  bundle URL is 3456 B, over the old 2048 cap, Real querySelector/querySelectorAll/matches/closest through the same author-CSS selector engine, node identity cache, and love (e4a7fd2) by grisun0
  * css box better (75a4c10) by grisun0
  * pseudo-classes now work in css_chain :D (0ef4100) by grisun0
  * Update README.md (e3ddecd) by Grisuno
  * some improves in css selects (cf92b2e) by grisun0
  * now the css is legible :Dhtml_parse: hp_extract_stylesheet_hrefs age_view: pv_build_styled (a1136b1) by grisun0
  * now the colors and links works propertly in hackernews xD (3ac0362) by grisun0
  * some updates (8221974) by grisun0
  * bug fix ci cd workflow (ee7e479) by grisun0
  * bug fix ci cd workflow (09973d7) by grisun0
  * Update ci.yml (b772752) by Grisuno
  * Create static.yml (da01c91) by Grisuno
  * bug fix ci cd workflow (722f5b8) by grisun0
  * bug fix ci cd workflow (85dd2ef) by grisun0
  * Update c-cpp.yml (747f05e) by Grisuno
  * new deb package (f4dcd64) by grisun0
  * new flag --dump-layout: headless mode (2e74858) by grisun0
  * some bug fixing in sf_enforce_policy (90ae7f6) by grisun0
  * some bug fixing (de47545) by grisun0
  * some love We closed the two critical gaps that turn the static document into a live, clickable page: stable node identity (Stage 0 keystone) and a minimal click dispatcher (Stage 4). (5e8a73e) by grisun0
  * some love to reconcile_boxes, flush_line, paint_content_row (639d417) by grisun0
  *  bt_resolve_positioning (3f22fff) by grisun0
  * some love, and dom_debug (d5a13a0) by grisun0
  * some love, and dom_debug (60621b2) by grisun0
  * XMLHttpRequest and fetch now work (3daa7a2) by grisun0
  * hotfixing distraction free (4ef9aae) by grisun0
  * hotfixing (69e6039) by grisun0
  * Gap 1 (parent_id / 1:N): confirmé el bug visualmente (la caja exterior se partía en dos con la interior como hermana) y lo arreglé convirtiendo las cajas en un árbol. Diseño:   - Nuevo pv_box_def {parent_id, hbox, bg, 27 campos de decoración} indexado por block_id → pv_view.boxes/rd_doc.boxes. La decoración se movió fuera de los runs (extinguí la duplicación per-run   del Step A — boy-scout/DRY; los runs solo llevan block_id).   - page_view registra cada bloque-con-caja ancestro y estampa el parent_id; el painter mantiene una pila de cajas abiertas (reconcile_boxes) y compone cada hija dentro del rect de contenido de   su padre, pintando exterior→inner (orden z implícito correcto). Maneja wrappers sin texto (una card cuyo único hijo es un body).   - Resultado visual: la caja exterior ahora envuelve las tres partes con la interior anidada; box-model.html/rich.html byte-idénticos (cero regresión). (fc7094f) by grisun0
  * page_view/IPC/render_doc (Step A): 28 campos de caja hilados css_style → pv_run → IPC → rd_block, gated por caps.css (corregí esto: block_id no es siempre como cont_id — solo sirve para   agrupar la decoración, así que sin author-CSS no agrupa y el layout no cambia). (98fdd4b) by grisun0
  * New module text_shape (tsh_): include/text_shape.h, src/text_shape.c, spec/text_shape.md. Resolves a local font per generic family (fontconfig), parses the same bytes with FreeType (for   Cairo glyphs) and HarfBuzz (for shaping), shapes hostile UTF-8 into cairo_glyph_t.   - Painter integration in gui/browser_ui.c: measure_slice/draw_slice now route through the shaper with a toy-API fallback (byte-identical to the old renderer if no font resolves → no   regression).   - The result: ligatures, GPOS kerning, contextual forms, complex-script direction — visible in the screenshots above (fi/ffi/fl ligated, AV/To/Wa kerned, accents correct). (38cf7af) by grisun0
  * What landed: position (+insets/z-index/box-sizing), full border/-radius/box-shadow/outline, flexbox per-item (flex/-grow/-shrink/-basis/order/align-*/flex-direction/flex-wrap), grid per-item   (grid-template-rows/row-gap/grid-auto-flow/span N) — ~40 new css_style fields, all fail-closed and fuzzed. (542001a) by grisun0
  * new props css (f5e07d3) by grisun0
  * issues (b528636) by grisun0
  * console js FreeBug is now more usable :D (ee3c9cd) by grisun0
  * more fancy css, i resolve one error in js console apear 4 more xD (5645287) by grisun0
  * more fancy css (0ba5aae) by grisun0
  * madurez de selectores y cascada CSS (f8fbede) by grisun0
  * a brand new FreeBug a javascript console is a poc now but here is a huge point to me :D, with love (49ccc4b) by grisun0
  * box model de autor (margin/padding/width/max-width) — el motivo nº1 por el que las webs modernas se veían apretadas. El resultado   headline es la columna de lectura centrada (max-width + margin: 0 auto + padding), verificada visualmente: (139bbef) by grisun0
  *   Cambios (ciclo doctrina):   - Spec — spec/os_sandbox.md: nueva §13 con el fundamento, §3/§10 actualizadas, deny-by-default explicado; spec/threat-model.md: fila   Proceso↔kernel.   - Test — tests/test_os_sandbox.c: test_policy_denies_io_uring (mirror puro de los 3 syscalls) + test_harden_kills_io_uring_setup (fork:   io_uring_setup ⇒ SIGSYS). Candadean la invariante: agregar io_uring al allowlist rompe la suite.   - Code — src/os_sandbox.c: comentario de seguridad junto a os_allowed[] (sin cambio funcional: la propiedad se sostiene por construcción, análogo a   SOP/CORS por construcción).   - Validación — make test (35 suites) y make asan (35 suites, exit 0) limpios; los dos tests nuevos verdes también bajo ASan.   - Fuzzing — N/A (no hay superficie nueva de parseo de contenido remoto).   - Docs — CLAUDE.md §3 reconciliada (io_uring = solo lado confiable, prohibido en el worker) + decisión de doctrina en §7; README.md,   docs/index.html, y memoria nueva freedom-io-uring-forbidden-in-worker.md + puntero en MEMORY.md. (7eedb5e) by grisun0
  * some tests of integration in lazyown (cc80263) by grisun0
  * #1 (CRÍTICO) — TLS PQ regression: FIXED ✅ (412febe) by grisun0
  * hardening claude.md xd (24d5e0f) by grisun0
  * test config/js.conf (705dd35) by grisun0
  * line-height — css_style.line_scale (percent of the natural line box; unitless 1.5→150 or %; normal/absolute px/em → unset; clamped [50,400]). It   inherits and rides the exact font_scale plumbing through every layer: css.c → page_view (resolve_context merge + pv_set_text_style) → tab.c IPC →   render_doc (gated by caps.css) → GUI flush_line (author multiplier replaces theme.line_spacing). (d02e4e0) by grisun0
  *   The cycle, in order:   1. Spec — spec/image_decode.md §0.1 documents the doctrine exception + every libjpeg guard; §4.1 adds Given-When-Then for JPEG.   2. Red — 7 new tests in test_image_decode.c failed for the right reason (undefined IMG_FMT_JPEG/img_decode_jpeg/img_decode).   3. Green — img_sniff recognizes FF D8 FF; img_decode_jpeg (libjpeg); img_decode dispatcher; worker (tab.c) calls the dispatcher.   4. Refactor — single img_decode entry point; IMG_CFLAGS/IMG_LIBS Makefile vars; repointed the obsolete test_sniff_non_png → test_sniff_unsupported   (contract changed); fixed two stale non-PNG GUI comments.   5. Validate — make test 35/35, make asan exit 0, plus a dedicated leak-checked ASan run of the truncated-JPEG longjmp path.   6. Fuzz — make fuzz-img 4.2M execs (libFuzzer discovered FF D8 FF on its own) + a seeded run (CMYK/progressive/grayscale/truncated, 176k execs),   zero crashes/leaks/UB.   7. Docs — CLAUDE.md (§7.1 row + §7.2 milestone + §7.3 roadmap), spec, README, docs/index.html, and memory freedom-jpeg-decode.md + MEMORY.md. (7c92dbe) by grisun0
  * hardening claude.md xd (69f6f50) by grisun0
  * update the readme (fbfd408) by grisun0
  * - Spec — spec/css.md + spec/page_view.md: combinator subset, the new css_element ancestor descriptor, css_resolve_el, specificity = sum, right-to-left matching; sibling/attribute/pseudo stay out (fail closed). - Red — replaced the old test_descendant_selector_unsupported with 6 real combinator tests in test_css.c + 1 integration test in test_page_view.c; confirmed failing (css_resolve_el undefined). - Green —   - src/css.c: css_sel became a compound chain (parts[CSS_MAX_COMPOUNDS=4] + comb[], subject = rightmost). New parse_compound + parse_complex_selector (splits on whitespace/>); complex_matches matches right-to-left over ancestors (child = immediate parent, descendant backtracks); specificity summed. New css_resolve_el(sheet, css_element*, ...); css_resolve is now a parentless wrapper (old behavior preserved).   - src/page_view.c: element_css_style builds the bounded ancestor chain (fill_css_node, cap 32, fail-closed) and calls css_resolve_el, so combinators resolve on the real DOM. - Refactor — single compound-matching surface; DRY; bounded recursion (≤4 deep) → anti-DoS. - Validation — make test (35 suites) and make asan (35, exit 0) clean. - Fuzz — extended fuzz_css to drive css_resolve_el with a synthetic chain: 267k execs clean; fuzz-pv (chain over hostile HTML) 31k execs clean. - Visual review — examples/combinators.html via /visual-review: confirmed in the PNG that .menu > .row lays out a flex row only for the direct child (Delta/Epsilon, a grandchild .row, correctly stack), and aside .ad{display:none} hides only the .ad inside <aside> (the one outside stays). Both combinators and their precision proven. (Author colors are gated by Privacy-by-Default in headless, so the demo uses structural display effects, which always apply.) - Docs — spec, CLAUDE.md (§7.1 row + §7.2 milestone + §7.3 roadmap), docs/index.html, memory freedom-css-combinators.md + MEMORY.md. (edd2409) by grisun0
  * hardening harness and human eval (f82d4c1) by grisun0
  * - fp_origin_key(session_key, registrable_domain) in anti_fp (pure: FNV-1a over the domain, XOR-mixed with the session secret, finalized with the existing splitmix64; NULL/ → one stable namespace). - tab.c worker derives the eTLD+1 from the page URL via the existing request_policy (rp_host_of→rp_site_of, PSL table) and feeds fp_origin_key(...) to je_install_canvas — so two sites in one worker get unlinkable noise. - je_install_canvas param renamed session_key→readback_key (semantics genuinely changed). - Makefile: test_tab now links request_policy.o + the PSL table (it didn't before). (480fe2d) by grisun0
  * hardening claude.md xd (9c719b8) by grisun0
  * unified css render path (99df0f7) by grisun0
  * update install (415b2eb) by grisun0
  * url_split js_dom IPC + Zero Trust (678762e) by grisun0
  * new module to render css and sessions (600b0c5) by grisun0
  * new module to render css (cfbb843) by grisun0
  * zoom :D (b7a1657) by grisun0
  * js fingerprinting (945c057) by grisun0
  * js create element, append child, remove child, append attribute (6d85529) by grisun0
  * writable dom and js mutable (7bf3462) by grisun0
  * js policy (bdc0a52) by grisun0
  * search on the bar, best render html, docs, etc (e6d0d3b) by grisun0
  * you can save de page as PDF instanctly fast. sandbox  hardenizada y reforzada con unamespaces aislados por tab (9ed6851) by grisun0
  * now req are async, the ui doesnt blocked (c5b7b35) by grisun0
  * Update README.md (ceab1f8) by Grisuno
  * Update README.md (23790a2) by Grisuno
  * Update README.md (ee0ff5f) by Grisuno
  * Update README.md (bbc22de) by Grisuno
  * Merge branch 'main' of https://github.com/grisuno/FreeDom (85f4a0f) by grisun0
  * tabs, and love to makefile (4760de2) by grisun0
  * Update README.md (277aff6) by Grisuno
  * Update README.md (c26cfc1) by Grisuno
  * i2p support improved :D (6ee12fb) by grisun0
  * tor support and i2p suppor :D (d3e839c) by grisun0
  * Update README.md (0ad3981) by Grisuno
  * Update README.md (a3c0f71) by Grisuno
  * tor support and i2p suppor :D (924a192) by grisun0
  * blacklist and white list to allow tls 1.2 (7cb2f25) by grisun0
  * update deb package (731e47a) by grisun0
  * sepia mode, box style y flex layout (de0fb68) by grisun0
  * shorcuts, scrollbar, marging and padding, maximize, minimize (1aff3e5) by grisun0
  * better presentation (14e7adc) by grisun0
  * better presentation (1d91b92) by grisun0
  * better presentation (8c39851) by grisun0
  * better presentation (2aca12f) by grisun0
  * better presentation (1071120) by grisun0
  * Update README.md (0d7f6eb) by Grisuno
  * Update README.md (72c6f99) by Grisuno
  * Update README.md (a7cc65f) by Grisuno
  * Update README.md (c845393) by Grisuno
  * update images, darkmode, cursor, hover over links now show the destiny, and clock show when is working :D (03183d7) by grisun0
  * update build_Deb.sh (a9140c7) by grisun0
  * update install (d92fe11) by grisun0
  * Update README.md (23b7119) by Grisuno
  * secure fetch fix (5b1fe4c) by grisun0
  * not images yet but the logic is here... (62c0fac) by grisun0


_Generated by [deploynator](https://github.com/grisuno/deploynator)_