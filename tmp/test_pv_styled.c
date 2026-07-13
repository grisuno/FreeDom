#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "html_parse.h"
#include "page_view.h"
int main() {
    FILE *f = fopen("/tmp/jkanime_default.html", "rb");
    if (!f) return 1;
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *html = (char*)malloc((size_t)len + 1);
    fread(html, 1, (size_t)len, f);
    html[len] = '\0';
    fclose(f);
    
    hp_document *doc = NULL;
    hp_config cfg = hp_config_default();
    cfg.strip_scripts = 0;
    hp_status st = hp_parse(html, (size_t)len, &cfg, &doc);
    printf("parse: %d\n", st);
    
    pv_view *v = NULL;
    pv_status pv = pv_build_styled(doc, 1, 0, 0, NULL, 0, &v);
    printf("pv_build_styled: %d, count: %zu\n", pv, v ? pv_count(v) : 0);
    
    pv_free(v);
    hp_document_free(doc);
    free(html);
    return 0;
}
