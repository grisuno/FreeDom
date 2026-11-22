/* libFuzzer harness for site_panel (spec/site_panel.md): a hostile URL and KE-group text
 * plus hostile geometry. Invariants: every string handed to the painter is printable
 * ASCII and NUL-terminated inside its buffer; the hybrid post-quantum row appears only
 * under a PQ identity; actions only for a network host; rectangles finite, non-negative,
 * actions inside the panel, and every hit lands on a part that exists. */
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "site_panel.h"

static double take_double(const uint8_t **p, size_t *n) {
    double d = 0.0;
    if (*n >= sizeof d) { memcpy(&d, *p, sizeof d); *p += sizeof d; *n -= sizeof d; }
    return d;
}

static void check_text(const char *s, size_t cap) {
    size_t n = 0;
    while (n < cap && s[n] != '\0') ++n;
    if (n == cap) abort();
    for (size_t i = 0; i < n; ++i)
        if ((unsigned char)s[i] < 0x20 || (unsigned char)s[i] >= 0x7f) abort();
}

static void check_rect(chl_rect r) {
    if (!isfinite(r.x) || !isfinite(r.y) || !isfinite(r.w) || !isfinite(r.h)) abort();
    if (r.w < 0.0 || r.h < 0.0) abort();
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 4 || size > 4096) return 0;
    sp_facts f;
    memset(&f, 0, sizeof f);
    f.identity = (chl_identity)(data[0] % 10);
    f.route = (sp_route)(data[1] % 3);
    f.allowlisted = data[2] & 1; f.js_site = (data[2] >> 1) & 1; f.trusted = (data[2] >> 2) & 1; f.listable = (data[2] >> 3) & 1;
    const uint8_t *p = data + 4;
    size_t n = size - 4;
    double ww = take_double(&p, &n), wh = take_double(&p, &n);
    chl_rect anchor = { take_double(&p, &n), take_double(&p, &n), 30.0, 28.0 };
    double hx = take_double(&p, &n), hy = take_double(&p, &n);

    /* The rest splits at the first NUL into url and group. */
    char *buf = (char *)malloc(n + 2);
    if (buf == NULL) return 0;
    memcpy(buf, p, n);
    buf[n] = '\0'; buf[n + 1] = '\0';
    size_t ul = strlen(buf);
    f.url = (data[3] & 1) ? NULL : buf;
    f.group = buf + ul + ((ul < n) ? 1 : 0);
    f.tls_version = (data[3] & 2) ? "TLSv1.3" : NULL;

    sp_panel sp;
    if (sp_build(&f, &sp) != SP_OK) abort();
    check_text(sp.title, sizeof sp.title);
    if (sp.headline == NULL) abort();
    if (sp.row_count < 0 || sp.row_count > SP_MAX_ROWS) abort();
    for (int i = 0; i < sp.row_count; ++i) {
        check_text(sp.rows[i].value, sizeof sp.rows[i].value);
        if (strcmp(sp.rows[i].label, "Key exchange") == 0 && sp.rows[i].tone == SP_TONE_GOOD
            && f.identity != CHL_ID_PQ) abort();
    }
    if (sp.tone == SP_TONE_GOOD && f.identity != CHL_ID_PQ) abort();
    if (sp.action_count < 0 || sp.action_count > SP_MAX_ACTIONS) abort();
    if (sp.action_count > 0 && (f.url == NULL || !f.listable)) abort();

    sp_geom g;
    if (sp_layout(&sp, anchor, ww, wh, &g) != SP_OK) abort();
    check_rect(g.panel);
    if (g.action_count < 0 || g.action_count > sp.action_count) abort();
    for (int i = 0; i < g.action_count; ++i) {
        check_rect(g.action[i]);
        if (g.action[i].x < g.panel.x || g.action[i].y < g.panel.y
            || g.action[i].x + g.action[i].w > g.panel.x + g.panel.w + 1e-6
            || g.action[i].y + g.action[i].h > g.panel.y + g.panel.h + 1e-6) abort();
    }
    int h = sp_hit(&g, hx, hy);
    if (h >= SP_HIT_ACTION0 && h >= g.action_count) abort();
    if (h < SP_HIT_OUTSIDE) abort();
    free(buf);
    return 0;
}
