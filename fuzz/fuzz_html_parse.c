/*
 * libFuzzer harness for html_parse (Hito 2).
 *
 * Goal: arbitrary bytes through the full parse + query + free pipeline must
 * never crash, leak, or trigger UB.
 *
 * Build & run: make fuzz   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "html_parse.h"

#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    hp_config cfg = hp_config_default();
    cfg.strip_scripts = 0; /* keep scripts so the per-script extractor is exercised */
    hp_document *doc = NULL;

    if (hp_parse((const char *)data, size, &cfg, &doc) == HP_OK) {
        size_t len = 0;
        char *text = hp_extract_text(doc, &len);
        hp_free(text);

        char *title = hp_get_title(doc, &len);
        hp_free(title);

        /* Per-script extraction over hostile markup: each script its own buffer,
         * bounded by HP_MAX_SCRIPTS, freed as a unit. Must never crash/leak/UB. */
        size_t nscripts = 0;
        hp_script *scripts = hp_extract_script_list(doc, &nscripts);
        hp_free_scripts(scripts, nscripts);

        (void)hp_element_count(doc);
        (void)hp_script_count(doc);
        (void)hp_event_handler_count(doc);
    }
    hp_document_free(doc);
    return 0;
}
