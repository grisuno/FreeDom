# spec: freebug (`fb_`)

Pure, I/O-free **bounded console-log buffer** for the developer console ("Freebug").
It is the directly auditable surface that decides what gets stored when page
JavaScript (or the user's REPL) writes to `console.*`, how much is kept, and how an
overflowing or hostile stream is dropped — fail-closed, never unbounded.

The buffer is shared by two sides:

- **Worker (capture).** `js_dom`'s native `console.{log,info,warn,error,debug}`
  binding appends formatted messages into an `fb_buffer` (held in the QuickJS
  runtime opaque). `tab` also appends an `FB_ERROR` entry for an uncaught exception
  thrown while running the page's scripts. After running scripts / an eval the
  worker drains the buffer over the IPC pipe to the parent.
- **Parent (storage + display).** The GUI keeps the last load's entries plus the
  REPL transcript in `fb_buffer`s and the Freebug window renders them.

Neither side re-implements the caps; both call these pure functions. No QuickJS
type, no Cairo, no Wayland, no global state, reentrant.

## Model

A buffer is an ordered list of entries. Each entry is a `level` (one of the
`fb_level` enum) plus an owned, NUL-terminated `text` copy. The buffer enforces
three independent caps, each fail-closed (the offending push is **dropped**, the
`overflow` flag is raised, and previously stored entries are kept intact):

- `FB_MAX_ENTRIES` — maximum number of stored entries.
- `FB_MAX_ENTRY_BYTES` — a single message longer than this is **truncated** to the
  cap (not dropped): a giant log line still shows, bounded.
- `FB_MAX_TOTAL_BYTES` — maximum sum of stored text bytes; a push that would
  exceed it is dropped whole.

An out-of-range `level` is clamped to `FB_LOG` (never indexes out of bounds). A
`NULL`/empty text is stored as an empty string (a bare `console.log()` is a real
event worth showing). The store copies the bytes, so the caller's buffer need not
outlive the call.

## API

| Function | Behaviour |
| :-- | :-- |
| `void fb_buffer_init(fb_buffer *b)` | Zero-initialises `b` (no allocation). Safe precondition for every other call. |
| `int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)` | Appends `text[0..len)` at `level`. Returns `1` if stored, `0` if dropped (caps) or on allocation failure / `NULL` `b`. Truncates to `FB_MAX_ENTRY_BYTES`; clamps `level`. Raises `b->overflow` when it drops. |
| `void fb_buffer_reset(fb_buffer *b)` | Frees every entry's text and sets `count`/`total_bytes`/`overflow` to 0, **keeping** the entry array allocation for reuse. |
| `void fb_buffer_free(fb_buffer *b)` | Frees the entries and the array; re-zeroes `b`. Idempotent; safe on `NULL` / a zeroed struct. |
| `size_t fb_buffer_count(const fb_buffer *b)` | Number of stored entries (`0` for `NULL`). |
| `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)` | The `i`-th entry, or `NULL` if out of range / `NULL` `b`. |
| `const char *fb_level_name(int level)` | A stable lowercase name (`"log"`/`"info"`/`"warn"`/`"error"`/`"debug"`); out-of-range clamps to `"log"`. Pure, no allocation. |

`fb_entry` exposes `int level; char *text; size_t len;` (text owned by the buffer).

## Behaviour (Given–When–Then)

- **Given** a fresh buffer, **when** a message is pushed, **then** `count` is 1 and
  `fb_buffer_at(b,0)->text` equals the pushed bytes (NUL-terminated, `len` set).
- **Given** a buffer already holding `FB_MAX_ENTRIES`, **when** another push happens,
  **then** it returns 0, `count` is unchanged, and `overflow` is set.
- **Given** a message longer than `FB_MAX_ENTRY_BYTES`, **when** pushed, **then** it
  is stored truncated to exactly `FB_MAX_ENTRY_BYTES` and returns 1.
- **Given** stored bytes near `FB_MAX_TOTAL_BYTES`, **when** a push would exceed the
  total, **then** it is dropped whole (returns 0, `overflow` set) and the prior
  entries remain readable.
- **Given** an out-of-range `level` (negative or huge), **when** pushed, **then** the
  stored entry's level is `FB_LOG` and `fb_level_name` of it is `"log"`.
- **Given** any buffer, **when** `fb_buffer_reset` then a new push, **then** the
  array is reused (no leak) and `overflow` is back to 0.

## Guarantees

- **Bounded.** Stored entry count ≤ `FB_MAX_ENTRIES`; each entry's `len` ≤
  `FB_MAX_ENTRY_BYTES`; total stored text ≤ `FB_MAX_TOTAL_BYTES`. A hostile script
  doing `for(;;)console.log(huge)` cannot exhaust memory: it fills the buffer once
  and every further line is dropped with `overflow` raised.
- **Fail-closed.** Any cap breach drops the offending push and keeps existing state
  consistent; allocation failure returns 0 without corrupting the buffer.
- **No dangling.** Text is copied in; the caller's source need not outlive the call.
  `reset`/`free` are the only owners that release it.
- **Pure.** No I/O, no global state; safe to call from the confined worker.

## Out of scope

- Formatting of JS values (objects → `"[object Object]"` via `toString`): the
  `js_dom` binding does the value→string conversion; this module only stores bytes.
  Structured/`JSON.stringify` rendering of objects is a later refinement.
- Source location (file:line) and timestamps: the v1 entry is level + text only.
- Persistence: the console is per-load / per-session, never written to disk
  (Zero Knowledge).
