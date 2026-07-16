# Spec: `frame_clock` (`fc_`) — animation frame scheduler

> Phase R1a — Animation & Transition Engine.
> Status: SPEC. Methodology: SDD + TDD.
> Module **pure**: tracks whether a frame clock should be active. The actual timerfd
> lives in the trusted-side GUI. No I/O, no allocation.

## 1. Purpose

When CSS animations or transitions are running, the GUI needs a steady ~60Hz
repaint loop. When all animations are idle, the clock stops to avoid wasting
CPU. `frame_clock` is a minimal pure flag + interval tracker consumed by the GUI's
event loop:

- `fc_set_active(c, 1)` — called when any page has active animations
- `fc_set_active(c, 0)` — called when all animations are done
- `fc_needs_tick(c)` — returns 1 if the timerfd should be armed
- `fc_interval_ms(c)` — the frame interval in ms (default ~16ms = 60fps)

## 2. API

```c
typedef struct fc_clock {
    int active;
    int interval_ms;  /* frame interval, default 16 */
} fc_clock;

/* Initialize with default interval (16ms). */
void fc_init(fc_clock *c);

/* Set animation active state. 1 = running, 0 = idle. */
void fc_set_active(fc_clock *c, int active);

/* Should the trusted-side timerfd be armed? */
int fc_needs_tick(const fc_clock *c);

/* Frame interval in ms. */
int fc_interval_ms(const fc_clock *c);
```

## 3. Semantics (Dado-Cuando-Entonces)

- **Dado** `active=0` → `fc_needs_tick()` ⇒ 0
- **Dado** `active=1` → `fc_needs_tick()` ⇒ 1
- **Dado** `init`, default → interval = 16ms, active = 0
- **Dado** `fc_set_active(c, 1)` → second call `fc_set_active(c, 0)` → `fc_needs_tick()` ⇒ 0
- **Dado** `NULL` pointer → all functions no-op or return 0 (NULL-safe)

## 4. Out of scope

- Timerfd creation/arming (trusted-side GUI concern)
- Variable refresh rate / vsync
- `prefers-reduced-motion` detection
- Multiple concurrent animation groups with independent clocks
