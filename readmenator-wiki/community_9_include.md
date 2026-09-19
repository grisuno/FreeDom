# include

*Community 9 | 3 files | cohesion 0.67*

## Definition

This community groups 3 file(s) rooted at `include` with dominant language c (cohesion 0.67). Central symbols: `FREEDOM_TEXTFIELD_H`, `TF_CAP`, `buf`, `main`, `test_backspace_delete`, `test_full_fails_closed`, `test_init_and_accessors`, `test_insert_sequence`. Core file: `include/textfield.h` (15 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/textfield.h` | h | utility | 15 | no |
| `src/textfield.c` | c | utility | 12 | no |
| `tests/test_textfield.c` | c | testing | 8 | no |

## Key Symbols

- `FREEDOM_TEXTFIELD_H` (macro, `include/textfield.h:2`) `#define FREEDOM_TEXTFIELD_H`
- `TF_CAP` (macro, `include/textfield.h:23`) `#define TF_CAP`
- `buf` (type_alias, `include/textfield.h:24`) `typedef struct tf_field { char buf[TF_CAP];` - textfield — a pure, single-line editable text buffer with a cursor.  No I/O, no global state, no dyn
- `tf_field` (struct, `include/textfield.h:25`)
- `tf_status` (enum, `include/textfield.h:31`)
- `tf_init` (function, `include/textfield.h:38`) `void tf_init(tf_field *f);` - typedef struct tf_field { char   buf[TF_CAP]; /* content, always NUL-terminated at [len] size_t len;
- `tf_clear` (function, `include/textfield.h:45`) `void tf_clear(tf_field *f);` - Replaces the whole content and places the cursor at the end. s == NULL => * TF_ERR_NULL_ARG. strlen(
- `tf_backspace` (function, `include/textfield.h:53`) `void tf_backspace(tf_field *f);` - Inserts one byte at the cursor, shifting the tail right; the cursor advances by one. Returns TF_ERR_
- `tf_delete` (function, `include/textfield.h:56`) `void tf_delete(tf_field *f);` - Inserts one byte at the cursor, shifting the tail right; the cursor advances by one. Returns TF_ERR_
- `tf_move` (function, `include/textfield.h:59`) `void tf_move(tf_field *f, long delta);` - Inserts one byte at the cursor, shifting the tail right; the cursor advances by one. Returns TF_ERR_
- `tf_home` (function, `include/textfield.h:62`) `void tf_home(tf_field *f);` - one. Returns TF_ERR_FULL (field unchanged) when the buffer is full, or * TF_ERR_NULL_ARG when f is N
- `tf_end` (function, `include/textfield.h:63`) `void tf_end(tf_field *f);`
- `tf_text` (function, `include/textfield.h:66`) `const char *tf_text(const tf_field *f);` - /* Deletes the byte before the cursor (no-op at the start). NULL-safe. void tf_backspace(tf_field *f
- `tf_len` (function, `include/textfield.h:67`) `size_t tf_len(const tf_field *f);`
- `tf_cursor` (function, `include/textfield.h:68`) `size_t tf_cursor(const tf_field *f);`
- `whole` (function, `src/textfield.c:6`) `* the buffer is rejected whole (fail closed), never applied partially.  */  #inc`
- `tf_clear` (function, `src/textfield.c:20`) `void tf_clear(tf_field *f)`
- `tf_set` (function, `src/textfield.c:24`) `tf_status tf_set(tf_field *f, const char *s)`
- `tf_insert` (function, `src/textfield.c:35`) `tf_status tf_insert(tf_field *f, char c)`
- `tf_backspace` (function, `src/textfield.c:47`) `void tf_backspace(tf_field *f)`
- `tf_delete` (function, `src/textfield.c:55`) `void tf_delete(tf_field *f)`
- `tf_move` (function, `src/textfield.c:62`) `void tf_move(tf_field *f, long delta)`
- `tf_home` (function, `src/textfield.c:73`) `void tf_home(tf_field *f)`
- `tf_end` (function, `src/textfield.c:78`) `void tf_end(tf_field *f)`
- `tf_text` (function, `src/textfield.c:83`) `const char *tf_text(const tf_field *f)`
- `tf_len` (function, `src/textfield.c:87`) `size_t tf_len(const tf_field *f)`
- `tf_cursor` (function, `src/textfield.c:91`) `size_t tf_cursor(const tf_field *f)`
- `test_init_and_accessors` (function, `tests/test_textfield.c:20`) `static void test_init_and_accessors(void **state)`
- `test_null_safe` (function, `tests/test_textfield.c:29`) `static void test_null_safe(void **state)`
- `test_set` (function, `tests/test_textfield.c:46`) `static void test_set(void **state)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- [EXTRACTED] depends_on community 0 <-> 9 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/textfield.h.
- [INFERRED] shares_context community 1 <-> 9 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (include) and community 9 (include).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 3 file(s) lack file-level docs (e.g. `include/textfield.h`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.67?

## Sources

- `include/textfield.h`
- `src/textfield.c`
- `tests/test_textfield.c`
