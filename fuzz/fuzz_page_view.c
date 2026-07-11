/*
 * libFuzzer harness for page_view (display-list builder).
 *
 * Goal: arbitrary bytes parsed to a DOM and then walked into the inert display
 * list must never crash, leak, or trigger UB. This covers the UTF-8 / Windows-1252
 * transcoder, the inline-emphasis and list-marker logic, and the table-to-grid
 * cell collection -- all reachable only through pv_build, not the parser harness.
 *
 * Build & run: make fuzz-pv   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "html_parse.h"
#include "page_view.h"

#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    hp_config cfg = hp_config_default();
    hp_document *doc = NULL;

    if (hp_parse((const char *)data, size, &cfg, &doc) == HP_OK) {
        pv_view *v = NULL;
        /* The second half of the input doubles as a hostile pre-fetched external
         * stylesheet (Hito 27), exercising the extern+<style> combine and the css
         * cascade over it; the full input is still the parsed HTML. */
        const char *ext = (const char *)data + size / 2;
        size_t ext_len = size - size / 2;
        if (pv_build_styled(doc, 0, 0, 0, ext, ext_len, &v) == PV_OK) {
            size_t n = pv_count(v);
            for (size_t i = 0; i < n; ++i) {
                const pv_run *r = pv_at(v, i);
                /* Touch every owned/derived field so the sanitizers see the reads. */
                volatile int sink = 0;
                if (r->text != NULL) sink ^= (int)r->text[0];
                sink ^= r->kind ^ r->heading ^ r->bold ^ r->italic ^ r->indent
                      ^ r->block_break ^ r->cont_id ^ r->cont_display ^ r->cont_cols
                      ^ r->input_type ^ r->form_id;
                (void)sink;
            }
            pv_free(v);
        }
    }
    hp_document_free(doc);
    return 0;
}
