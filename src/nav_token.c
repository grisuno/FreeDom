/* nav_token -- per-tab navigation identity shared with fetch threads. spec/nav_token.md */
#include "nav_token.h"

#include <stdatomic.h>
#include <stdlib.h>

struct nt_token {
    atomic_int  refs;
    atomic_int  cancelled;
    atomic_int  foreground;
    uint64_t    id;          /* immutable after nt_new */
};

static atomic_uint_fast64_t g_next_id = 1;

nt_token *nt_new(void) {
    nt_token *t = (nt_token *)calloc(1, sizeof *t);
    if (t == NULL) return NULL;
    atomic_init(&t->refs, 1);
    atomic_init(&t->cancelled, 0);
    atomic_init(&t->foreground, 1);
    t->id = (uint64_t)atomic_fetch_add(&g_next_id, 1);
    return t;
}

nt_token *nt_ref(nt_token *t) {
    if (t != NULL) atomic_fetch_add_explicit(&t->refs, 1, memory_order_relaxed);
    return t;
}

void nt_unref(nt_token **tp) {
    if (tp == NULL || *tp == NULL) return;
    nt_token *t = *tp;
    *tp = NULL;
    if (atomic_fetch_sub_explicit(&t->refs, 1, memory_order_acq_rel) == 1) free(t);
}

void nt_cancel(nt_token *t) {
    if (t != NULL) atomic_store_explicit(&t->cancelled, 1, memory_order_release);
}

int nt_cancelled(const nt_token *t) {
    if (t == NULL) return 1;
    return atomic_load_explicit(&((nt_token *)t)->cancelled, memory_order_acquire) != 0;
}

void nt_set_foreground(nt_token *t, int on) {
    if (t != NULL) atomic_store_explicit(&t->foreground, on != 0, memory_order_release);
}

int nt_foreground(const nt_token *t) {
    if (t == NULL) return 0;
    return atomic_load_explicit(&((nt_token *)t)->foreground, memory_order_acquire) != 0;
}

uint64_t nt_id(const nt_token *t) { return (t != NULL) ? t->id : 0; }

nt_route_kind nt_route(const nt_token *job, const nt_token *active, nt_token *const *parked,
                       int n, int *slot) {
    if (slot != NULL) *slot = -1;
    if (job == NULL || nt_cancelled(job)) return NT_DROP;
    if (job == active) return NT_DELIVER;
    if (parked == NULL) return NT_DROP;
    for (int i = 0; i < n; ++i) {
        if (parked[i] == job) {
            if (slot != NULL) *slot = i;
            return NT_PARK;
        }
    }
    return NT_DROP;
}
