/*
 * libFuzzer harness for dom_debug (render-tree dump).
 *
 * Goal: arbitrary bytes parsed to a DOM, walked into a display list, built into an
 * rd_doc (author CSS on, so the box tree is populated), and formatted by dd_format
 * must never crash, leak or trigger UB -- and dd_format must never write past the
 * caller's cap. The first byte chooses a small cap to exercise the truncation path;
 * the measure pass (cap 0) must agree with the would-write return value.
 *
 * Build & run: make fuzz-dd   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "dom_debug.h"
#include "html_parse.h"
#include "page_view.h"
#include "render_doc.h"
#include "render_policy.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    hp_config cfg = hp_config_default();
    hp_document *doc = NULL;
    if (hp_parse((const char *)data, size, &cfg, &doc) != HP_OK) {
        hp_document_free(doc);
        return 0;
    }

    pv_view *v = NULL;
    if (pv_build(doc, &v) == PV_OK) {
        rdp_caps caps = rdp_caps_safe();
        caps.css = true;                 /* populate the box tree */
        rd_doc *rd = NULL;
        if (rd_build(v, caps, "https://example.com/", &rd) == RD_OK) {
            /* Measure pass: the untruncated length. */
            size_t need = dd_format(rd, NULL, 0);

            /* Bounded pass into a guarded buffer with a fuzz-chosen small cap. */
            unsigned char guard[512];
            memset(guard, 0xAA, sizeof guard);
            size_t cap = (size > 0) ? ((size_t)data[0] % 200u) : 0u; /* 0..199 */
            size_t ret = dd_format(rd, (char *)guard, cap);

            /* Invariants: the two passes agree, the cap is never overrun, and the
             * buffer is NUL-terminated when there was room. */
            if (ret != need) __builtin_trap();
            if (cap > 0) {
                int nul = 0;
                for (size_t i = 0; i < cap; ++i) if (guard[i] == '\0') { nul = 1; break; }
                if (!nul) __builtin_trap();
                for (size_t i = cap; i < sizeof guard; ++i)
                    if (guard[i] != 0xAA) __builtin_trap();
            }
            rd_free(rd);
        }
        pv_free(v);
    }
    hp_document_free(doc);
    return 0;
}
