# Project Memory

> Cross-session context for agents. Sections 1-6 are regenerated from the source tree with zero LLM tokens: declared rules are quoted verbatim with `file:line`, measured baselines come from the scan. Section 7 is written by agents and humans and is preserved across rebuilds.

Generated from 422 files at commit `b6fdd37a76fc`. Read this first, then `readmenator-wiki/index.md`, then `readmenator . ask "<question>"` for anything specific.

## 1. Purpose and domain

- What it is: From the creators of the LazyOwn Redteam Framework: a free, open-source web browser (`README.md:5`)
- Domain vocabulary (term, files): `null` (198), `one` (198), `max` (167), `include` (158), `not` (154), `spec` (154), `out` (153), `size` (152), `freedom` (143), `char` (138), `const` (134), `free` (131), `its` (126), `text` (119), `css` (117)
- Subsystem `src: tab`: 72 files, core `src/tab.c`: tab_iobuf: Batched pipe I/O for the view codec. write_view/read_view move one int32 block and...
- Subsystem `include: browser_ui`: 65 files, core `gui/browser_ui.c`: ui_input_state: Live editable state for one form text control, aliasing a block of the current...
- Subsystem `include: css`: 58 files, core `src/css.c`: css_cq: @container conditions (spec/css_mq.md): a rule inside one is kept and gated per element....
- Subsystem `src: text_shape`: 55 files, core `src/text_shape.c`: tsh_fb_cp: Per-code-point verdicts of fb_entry.
- Subsystem `include: page_view`: 30 files, core `src/page_view.c`: pv_ptrmap: A small open-addressed map pointer -> int: the per-element verdict on a generated box...
- Subsystem `include: http_cache`: 28 files, core `src/http_cache.c`: days_from_civil: #define HC_MAGIC      "FHC1\n" #define HC_NAME_HEX   64u #define HC_EVICT_EVERY...
- Subsystem `include: secure_fetch`: 24 files, core `src/secure_fetch.c`: tls_capture: Snapshot of the negotiated TLS state. curl exposes the live SSL* only while a...
- Subsystem `include: bui_chrome`: 20 files, core `gui/bui_chrome.c`: tab_path: void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double r) {...
- Business rules that the code cannot show live in section 7: record them there.

## 2. Workflow

Detected commands:
- `python -m pytest -q` (tests/ layout)
- `make all` (Makefile)
- `make install` (Makefile)
- `make test` (Makefile)
- `make fuzz-mkc` (Makefile)
- `make fuzz-bb` (Makefile)
- `make fuzz-ek` (Makefile)
- `make itest` (Makefile)
- `make asan` (Makefile)
- `make asan-run` (Makefile)
- `make fuzz` (Makefile)
- `make fuzz-js` (Makefile)

Session protocol:
1. Start: read this file, then `readmenator . fresh` (exit 1 means run `readmenator . --rebuild`).
2. Orient: `readmenator-wiki/index.md`; for a question use `readmenator . ask "<question>"` (local = entities + sources, `--global` = community reports).
3. Before editing a file: `grep -n '<file>' readmenator-agent/GOTCHAS.md readmenator-agent/SECURITY.md`.
4. After the change: run the tests above, then `readmenator . --rebuild` so the maps, wiki, and this file stay true.
5. End: record decisions, business rules, and gotchas with `readmenator . remember "<note>" --kind decision`.

## 3. Rules and constraints

Declared:
- Pure C11 only. Headers reject C++ via `#error`. (`AGENTS.md:17`)
- Fail closed. Doubt means reject. No convenience downgrade. (`AGENTS.md:18`)
- No new deps without attack-surface reduction argument. Never liboqs/oqsprovider. OpenSSL 3.5+ native only. (`AGENTS.md:19`)
- No `io_uring` inside confined worker (`tab`/renderer). Blocked pipes only. Bypass seccomp otherwise. (`AGENTS.md:20`)
- Every new `pv_run`/`pv_box_def`/`rd_block` field crosses `write_view`/`read_view` in `src/tab.c`. Check `TAB_WIRE_*` constants. Run `make drift`. (`AGENTS.md:21`)
- Shared struct growth requires `make clean` rebuild. Makefile tracks no header deps. (`AGENTS.md:22`)
- `-fvisibility=hidden` invariant. Never remove. HarfBuzz allocator guard. (`AGENTS.md:23`)
- No magic numbers. Policy tunables live in `include/freedom_config.h` as `FC_*` with why-comment. Contract bounds live in module header. (`AGENTS.md:24`)
- No absolute paths. No emojis in code. English identifiers. (`AGENTS.md:25`)
- V-001 malloc(len+1) SIZE_MAX guard. V-002 calloc for arrays + zero-init stack views. V-003 chained fixed blocks for unbounded accumulators. V-004 snprintf truncation check. (`AGENTS.md:26`)
- `make drift` green before `make test`. Drops gate `make drops` green. New bad-value fails build. (`AGENTS.md:27`)
- Plans are hypotheses. Verify every file path and symbol against source before acting. (`AGENTS.md:28`)
- Log mechanism not incident in fix notes. State generalized error category. (`AGENTS.md:29`)

Measured baseline:
- Security findings at medium or above: 0 (see `readmenator-agent/SECURITY.md`); do not add new ones.
- Dependency cycles: 1; layer violations: 26 (see `readmenator-agent/GOTCHAS.md`).

## 4. Style norms

Declared:
- none declared in instruction files (add them to AGENTS.md or record them in section 7)

Measured baseline:
- c: 282 files, 6981 symbols; docstrings on 28% of symbols; functions snake_case (98%); types PascalCase (1%); median file 192 lines, max 22366.
- h: 122 files, 1945 symbols; docstrings on 38% of symbols; functions snake_case (98%); types PascalCase (0%); median file 68 lines, max 1347.
- py: 13 files, 54 symbols; docstrings on 22% of symbols; functions snake_case (100%); median file 123 lines, max 345.
- sh: 5 files, 0 symbols; median file 11 lines, max 90.
- Tests: 110 files under tests; follow the existing naming (e.g. `itest_secure_fetch.c`).

## 5. Minimum deliverables

Declared:
- none declared in instruction files (add them to AGENTS.md or record them in section 7)

Measured baseline:
- Tests pass: `python -m pytest -q`.
- Docstring coverage stays at or above 30%.
- No new security findings at medium or above (current: 0).
- No new dependency cycles (current: 1).
- Files stay under 300 lines where possible (`readmenator . lint`).
- Docs refreshed: `readmenator . --rebuild`, and decisions recorded in section 7.

## 6. Risks to respect

- God nodes (changes ripple widely): `gui/browser_ui.c`, `include/css.h`, `src/tab.c`, `src/page_view.c`, `src/freedom.c`
- Hotspots (complex and central): `gui/browser_ui.c`, `src/tab.c`, `src/page_view.c`, `src/css.c`, `tests/test_css.c`
- Cycle: `include/js_dom.h` -> `include/js_location.h` -> `include/js_dom.h`
- Full blast radius: `readmenator-agent/GOTCHAS.md`; findings: `readmenator-agent/SECURITY.md`.

## 7. Session log (preserved across rebuilds)

Append with `readmenator . remember "<note>" --kind <kind>` (kinds: business, decision, rule, workflow, style, deliverable, gotcha, todo, note) or the MCP tool `readmenator.remember`. Record business rules, decisions and their reasons, workflow changes, and anything the next session must not rediscover.

<!-- readmenator:memory:notes:begin -->
<!-- readmenator:memory:notes:end -->
