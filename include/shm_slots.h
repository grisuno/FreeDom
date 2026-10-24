#ifndef FREEDOM_SHM_SLOTS_H
#define FREEDOM_SHM_SLOTS_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * shm_slots -- pure bookkeeping for the window's double buffer (spec/shm_slots.md).
 *
 * The compositor reads a committed wl_buffer until it sends `release`. Painting into a buffer it
 * still holds shows a half-painted frame (the page is cleared and redrawn every frame, so a
 * moving video flickers). With two slots, paint always goes to a slot the compositor has
 * released; a slot is BUSY from commit until release. No I/O, no allocation.
 */

#define SS_COUNT 2

typedef struct ss_state {
    int busy[SS_COUNT];   /* 1 = committed and not yet released by the compositor */
    int back;             /* the slot painted into / about to be */
} ss_state;

static inline void ss_init(ss_state *s) {
    for (int i = 0; i < SS_COUNT; ++i) s->busy[i] = 0;
    s->back = 0;
}

/* Chooses the slot to paint into: the current one if free, else the other free one. Returns its
 * index (also stored in s->back), or -1 when the compositor holds every slot (the caller defers
 * the repaint to the next release). */
static inline int ss_pick(ss_state *s) {
    for (int k = 0; k < SS_COUNT; ++k) {
        int i = (s->back + k) % SS_COUNT;
        if (!s->busy[i]) { s->back = i; return i; }
    }
    return -1;
}

/* The painted slot was attached and committed. */
static inline void ss_committed(ss_state *s, int i) {
    if (i >= 0 && i < SS_COUNT) {
        s->busy[i] = 1;
        s->back = (i + 1) % SS_COUNT;   /* prefer the other one next time: alternate */
    }
}

/* The compositor released slot i. Returns 1 when it was busy. */
static inline int ss_released(ss_state *s, int i) {
    if (i < 0 || i >= SS_COUNT || !s->busy[i]) return 0;
    s->busy[i] = 0;
    return 1;
}

#endif /* FREEDOM_SHM_SLOTS_H */
