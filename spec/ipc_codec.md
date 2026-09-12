# Spec: `ipc_codec` (tab wire drift lock)

## 1. Purpose

`write_view`/`read_view` in `src/tab.c` carry every `pv_run`/`pv_box_def`/
`pv_cont_def` field over pipes. Past failures (4x) came from adding a struct
field without updating both sides, producing silent dead features. This spec
locks the codec against that class.

## 2. Contract

- Wire block widths defined once in `src/tab.c`:
  `TAB_WIRE_HEAD_N=6`, `TAB_WIRE_A_N=38`, `TAB_WIRE_B_N=54`,
  `TAB_WIRE_BOX_F_N=219`, `TAB_WIRE_GRID_N=PV_GRID_TRACKS+1`.
- `_Static_assert(TAB_WIRE_GRID_N == 9)` guards `PV_GRID_TRACKS` drift.
- `_Static_assert(FC_MAX_BOXES == BT_MAX_POSITIONED)` guards box cap coupling.
- `make drift` fails build when array literal width differs from constant.

## 3. Semantics

- Given a new display-list field, when added to struct, then same diff updates
  write block literal, read extraction, setter call, and `TAB_WIRE_*` if width
  changes.
- Given `make drift` red, when CI runs, then build fails before `make test`.
- No tags/versioning: worker is same binary via `/proc/self/exe`, so version
  skew cannot occur. Added complexity would be dead code.

## 4. Security guarantees

- Anti-amplification caps unchanged (`TAB_MAX_RUNS`, `TAB_MAX_INPUT`).
- Fail closed on short read, oversize count, oversize string.
- No network, no filesystem access added.

## 5. Out of scope

- Full TLV/codegen. Current constant+assert+grep gate removes bug class with
  minimal code. Full generator deferred until field churn justifies it.
