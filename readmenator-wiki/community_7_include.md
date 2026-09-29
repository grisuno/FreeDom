# include

*Community 7 | 13 files | cohesion 0.68*

## Definition

This community groups 13 file(s) rooted at `include` with dominant language c (cohesion 0.68). Central symbols: `FC_DEFAULT_INTERVAL_MS`, `FREEDOM_FRAME_CLOCK_H`, `FREEDOM_PREFS_H`, `FREEDOM_PROFILE_H`, `FREEDOM_ZOOM_H`, `LLVMFuzzerTestOneInput`, `PREFS_MAGIC`, `PREFS_MAX_BOOKMARKS`. Core file: `src/prefs.c` (26 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_prefs.c` | c | utility | 1 | no |
| `include/frame_clock.h` | h | utility | 7 | no |
| `include/prefs.h` | h | utility | 18 | no |
| `include/profile.h` | h | utility | 9 | no |
| `include/zoom.h` | h | utility | 10 | no |
| `src/frame_clock.c` | c | utility | 4 | no |
| `src/prefs.c` | c | utility | 26 | no |
| `src/profile.c` | c | utility | 9 | no |
| `src/zoom.c` | c | utility | 7 | no |
| `tests/test_frame_clock.c` | c | testing | 4 | no |
| `tests/test_prefs.c` | c | testing | 15 | no |
| `tests/test_profile.c` | c | testing | 17 | no |
| `tests/test_zoom.c` | c | testing | 11 | no |

## Key Symbols

- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_prefs.c:21`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_FRAME_CLOCK_H` (macro, `include/frame_clock.h:2`) `#define FREEDOM_FRAME_CLOCK_H`
- `active` (type_alias, `include/frame_clock.h:14`) `typedef struct fc_clock { int active;` - frame_clock (fc_) — pure animation frame scheduler. Phase R1a. Tracks whether a steady repaint clock
- `fc_clock` (struct, `include/frame_clock.h:15`)
- `fc_init` (function, `include/frame_clock.h:20`) `void fc_init(fc_clock *c);`
- `fc_set_active` (function, `include/frame_clock.h:21`) `void fc_set_active(fc_clock *c, int active);`
- `fc_needs_tick` (function, `include/frame_clock.h:22`) `int fc_needs_tick(const fc_clock *c);`
- `fc_interval_ms` (function, `include/frame_clock.h:23`) `int fc_interval_ms(const fc_clock *c);`
- `FREEDOM_PREFS_H` (macro, `include/prefs.h:2`) `#define FREEDOM_PREFS_H`
- `PREFS_VERSION` (macro, `include/prefs.h:26`) `#define PREFS_VERSION`
- `PREFS_MAX_URL` (macro, `include/prefs.h:27`) `#define PREFS_MAX_URL`
- `PREFS_MAX_TITLE` (macro, `include/prefs.h:28`) `#define PREFS_MAX_TITLE`
- `PREFS_MAX_BOOKMARKS` (macro, `include/prefs.h:29`) `#define PREFS_MAX_BOOKMARKS`
- `PREFS_MAX_HISTORY` (macro, `include/prefs.h:30`) `#define PREFS_MAX_HISTORY`
- `PREFS_MAX_TEXT` (macro, `include/prefs.h:31`) `#define PREFS_MAX_TEXT`
- `PREFS_PAGE_HISTORY` (macro, `include/prefs.h:34`) `#define PREFS_PAGE_HISTORY`
- `prefs_status` (enum, `include/prefs.h:36`)
- `prefs_entry` (struct, `include/prefs.h:45`)
- `theme_mode` (type_alias, `include/prefs.h:49`) `typedef struct prefs_state { int theme_mode;`
- `prefs_state` (struct, `include/prefs.h:50`)
- `prefs_init` (function, `include/prefs.h:65`) `void prefs_init(prefs_state *p);` - Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on). NULL-saf
- `prefs_free` (function, `include/prefs.h:68`) `void prefs_free(prefs_state *p);` - Safe defaults (a virgin session: everything private/off, zoom 100%, * remember_history on). NULL-saf
- `free` (function, `include/prefs.h:71`) `* free(). */ prefs_status prefs_format(const prefs_state *p, char **out, size_t`
- `prefs_bookmark_index` (function, `include/prefs.h:81`) `int prefs_bookmark_index(const prefs_state *p, const char *url);` - Parses text[0..len) over an out ALREADY initialised with prefs_init. Unknown magic/version or len >
- `prefs_suggest` (function, `include/prefs.h:100`) `int prefs_suggest(const prefs_state *p, const char *query, char *out, size_t row` - Omnibox autocomplete: up to max_rows distinct URLs matching query (case- insensitive) written to out
- `anyway` (function, `include/prefs.h:105`) `* page is rendered by the normal confined pipeline anyway (defence in depth). *`
- `FREEDOM_PROFILE_H` (macro, `include/profile.h:2`) `#define FREEDOM_PROFILE_H`
- `PROFILE_KEY_FILE` (macro, `include/profile.h:32`) `#define PROFILE_KEY_FILE`
- `PROFILE_PREFS_FILE` (macro, `include/profile.h:33`) `#define PROFILE_PREFS_FILE`
- `profile_status` (enum, `include/profile.h:35`)

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 13
- Cross-boundary resolved imports (EXTRACTED): 6

## Connections

- [EXTRACTED] depends_on community 2 <-> 7 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/frame_clock.h.
- [EXTRACTED] depends_on community 7 <-> 10 (strength 0.9): Extracted import edge crosses communities: include/profile.h imports include/local_store.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 13 file(s) lack file-level docs (e.g. `fuzz/fuzz_prefs.c`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.68?

## Sources

- `fuzz/fuzz_prefs.c`
- `include/frame_clock.h`
- `include/prefs.h`
- `include/profile.h`
- `include/zoom.h`
- `src/frame_clock.c`
- `src/prefs.c`
- `src/profile.c`
- `src/zoom.c`
- `tests/test_frame_clock.c`
- `tests/test_prefs.c`
- `tests/test_profile.c`
- `tests/test_zoom.c`
