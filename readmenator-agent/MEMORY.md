# Project Memory

> Cross-session context for agents. Sections 1-6 are regenerated from the source tree with zero LLM tokens: declared rules are quoted verbatim with `file:line`, measured baselines come from the scan. Section 7 is written by agents and humans and is preserved across rebuilds.

Generated from 262 files at commit `606250e9e794`. Read this first, then `readmenator-wiki/index.md`, then `readmenator . ask "<question>"` for anything specific.

## 1. Purpose and domain

- What it is: From the creators of LazyOwn Redteam Framework comes a free and open-source minimal web (`README.md:6`)
- Domain vocabulary (term, files): `null` (137), `one` (110), `max` (108), `not` (103), `include` (103), `size` (101), `out` (98), `free` (95), `freedom` (91), `char` (85), `const` (83), `css` (81), `text` (79), `url` (79), `static` (79)
- Subsystem `src`: 59 files, core `src/tab.c`: write_field: Writes one length-prefixed string field (the write mirror of read_field): a size_t...
- Subsystem `include: browser_ui`: 47 files, core `gui/browser_ui.c`: ui_input_state: Live editable state for one form text control, aliasing a block of the current...
- Subsystem `include: css`: 40 files, core `src/css.c`: css_match: if (!(inherited_px > 0.0)) inherited_px = CL_INITIAL_FONT_SIZE; if (o->font_scale ==...
- Subsystem `include: page_view`: 31 files, core `src/page_view.c`: pv_cont_info: Nearest-container info attached to a run, plus the flex per-item values (Stage 3)...
- Subsystem `include: text_shape`: 20 files, core `src/text_shape.c`: web_magic_ok: True for font programs FreeType parses without new decoders: wOFF/TrueType/...
- Subsystem `include: local_store`: 16 files, core `src/local_store.c`
- Subsystem `gui`: 15 files, core `src/svg_render.c`: svg_render — inline <svg> markup -> a bounded list of geometric shapes.
- Subsystem `include: secure_fetch`: 10 files, core `src/secure_fetch.c`: tls_capture: Snapshot of the negotiated TLS state. curl exposes the live SSL* only while a...
- Business rules that the code cannot show live in section 7: record them there.

## 2. Workflow

Detected commands:
- `python -m pytest -q` (tests/ layout)
- `make all` (Makefile)
- `make install` (Makefile)
- `make test` (Makefile)
- `make itest` (Makefile)
- `make asan` (Makefile)
- `make fuzz` (Makefile)
- `make fuzz-js` (Makefile)
- `make fuzz-imap` (Makefile)
- `make fuzz-wst` (Makefile)
- `make fuzz-geom` (Makefile)
- `make fuzz-jsdom` (Makefile)

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
- Dependency cycles: 1; layer violations: 20 (see `readmenator-agent/GOTCHAS.md`).

## 4. Style norms

Declared:
- none declared in instruction files (add them to AGENTS.md or record them in section 7)

Measured baseline:
- c: 173 files, 4935 symbols; docstrings on 27% of symbols; functions snake_case (99%); types PascalCase (0%); median file 238 lines, max 16301.
- h: 79 files, 1269 symbols; docstrings on 38% of symbols; functions snake_case (98%); types PascalCase (0%); median file 81 lines, max 1164.
- py: 5 files, 31 symbols; docstrings on 23% of symbols; functions snake_case (100%); median file 170 lines, max 328.
- sh: 5 files, 0 symbols; median file 11 lines, max 91.
- Tests: 69 files under tests; follow the existing naming (e.g. `itest_secure_fetch.c`).

## 5. Minimum deliverables

Declared:
- none declared in instruction files (add them to AGENTS.md or record them in section 7)

Measured baseline:
- Tests pass: `python -m pytest -q`.
- Docstring coverage stays at or above 29%.
- No new security findings at medium or above (current: 0).
- No new dependency cycles (current: 1).
- Files stay under 300 lines where possible (`readmenator . lint`).
- Docs refreshed: `readmenator . --rebuild`, and decisions recorded in section 7.

## 6. Risks to respect

- God nodes (changes ripple widely): `gui/browser_ui.c`, `include/css.h`, `src/tab.c`, `src/css.c`, `src/page_view.c`
- Hotspots (complex and central): `gui/browser_ui.c`, `src/tab.c`, `src/css.c`, `src/page_view.c`, `tests/test_css.c`
- Cycle: `include/js_dom.h` -> `include/js_location.h` -> `include/js_dom.h`
- Full blast radius: `readmenator-agent/GOTCHAS.md`; findings: `readmenator-agent/SECURITY.md`.

## 7. Session log (preserved across rebuilds)

Append with `readmenator . remember "<note>" --kind <kind>` (kinds: business, decision, rule, workflow, style, deliverable, gotcha, todo, note) or the MCP tool `readmenator.remember`. Record business rules, decisions and their reasons, workflow changes, and anything the next session must not rediscover.

<!-- readmenator:memory:notes:begin -->
<!-- readmenator:memory:notes:end -->
