/* libFuzzer harness for nav_token (spec/nav_token.md): a byte program of new / ref /
 * unref / cancel / foreground / route over a pool of holders. ASan catches any leak,
 * double free or use after free; the routing oracle checks a result is only ever
 * delivered to the active holder or parked at a holder that owns the very token. */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "nav_token.h"

#define POOL 8

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    nt_token *h[POOL] = { 0 };
    for (size_t i = 0; i + 1 < size; i += 2) {
        int op = data[i] % 6, a = data[i + 1] % POOL, b = (data[i + 1] / POOL) % POOL;
        switch (op) {
            case 0: nt_unref(&h[a]); h[a] = nt_new(); break;
            case 1: if (h[b] == NULL) h[b] = nt_ref(h[a]); break;
            case 2: nt_unref(&h[a]); break;
            case 3: nt_cancel(h[a]); break;
            case 4: nt_set_foreground(h[a], b & 1); if (h[a] && nt_foreground(h[a]) != (b & 1)) abort(); break;
            default: {
                int slot = -2;
                nt_route_kind k = nt_route(h[a], h[b], h, POOL, &slot);
                if (k == NT_DELIVER && (h[a] != h[b] || nt_cancelled(h[a]))) abort();
                if (k == NT_PARK && (slot < 0 || slot >= POOL || h[slot] != h[a])) abort();
                if (k != NT_PARK && slot != -1) abort();
                if (h[a] == NULL && k != NT_DROP) abort();
                break;
            }
        }
    }
    for (int i = 0; i < POOL; ++i) nt_unref(&h[i]);
    return 0;
}
