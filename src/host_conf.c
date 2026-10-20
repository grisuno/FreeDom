#include "host_conf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HCF_USER_SUBDIR "/.config/freedom"
#define HCF_REPO_DIR    "config"

static void add_dir(hcf_dirs *out, const char *path) {
    if (path == NULL || path[0] == '\0' || out->n >= HCF_MAX_DIRS) return;
    size_t len = strlen(path);
    if (len >= HCF_PATH_MAX) return;
    for (size_t i = 0; i < out->n; ++i)
        if (strcmp(out->path[i], path) == 0) return;
    memcpy(out->path[out->n], path, len + 1);
    ++out->n;
}

void hcf_search_dirs(const char *env, const char *home, hcf_dirs *out) {
    if (out == NULL) return;
    out->n = 0;
    add_dir(out, env);
    if (home != NULL && home[0] != '\0') {
        char user[HCF_PATH_MAX];
        int n = snprintf(user, sizeof user, "%s" HCF_USER_SUBDIR, home);
        if (n > 0 && (size_t)n < sizeof user) add_dir(out, user);
    }
    add_dir(out, HCF_REPO_DIR);
}

void hcf_search_dirs_from_env(hcf_dirs *out) {
    hcf_search_dirs(getenv("FREEDOM_HOSTS_DIR"), getenv("HOME"), out);
}

/* Reads dir/name whole, or NULL when it is absent, unreadable or over the cap. */
static char *read_conf(const char *dir, const char *name) {
    char path[HCF_PATH_MAX * 2];
    int n = snprintf(path, sizeof path, "%s/%s", dir, name);
    if (n <= 0 || (size_t)n >= sizeof path) return NULL;
    FILE *f = fopen(path, "rb");
    if (f == NULL) return NULL;
    char *buf = NULL;
    if (fseek(f, 0, SEEK_END) == 0) {
        long sz = ftell(f);
        if (sz >= 0 && (unsigned long)sz <= HCF_MAX_FILE_BYTES && fseek(f, 0, SEEK_SET) == 0) {
            buf = (char *)malloc((size_t)sz + 1);
            if (buf != NULL) {
                size_t got = fread(buf, 1, (size_t)sz, f);
                buf[got] = '\0';
            }
        }
    }
    fclose(f);
    return buf;
}

static void load_into(hb_set *s, const char *dir, const char *name, hb_list list) {
    char *txt = read_conf(dir, name);
    if (txt == NULL) return;
    hb_load(s, txt, list);   /* HB_ERR_OOM only drops extra entries; not fatal */
    free(txt);
}

hb_set *hcf_load_filter(const hcf_dirs *dirs) {
    if (dirs == NULL) return NULL;
    hb_set *s = hb_new();
    if (s == NULL) return NULL;
    for (size_t i = 0; i < dirs->n; ++i) {
        load_into(s, dirs->path[i], "block.conf", HB_LIST_BLOCK);
        load_into(s, dirs->path[i], "allow.conf", HB_LIST_ALLOW);
    }
    return s;
}

hb_set *hcf_load_allowlist(const hcf_dirs *dirs, const char *fname) {
    if (dirs == NULL || fname == NULL) return NULL;
    hb_set *s = hb_new();
    if (s == NULL) return NULL;
    for (size_t i = 0; i < dirs->n; ++i) load_into(s, dirs->path[i], fname, HB_LIST_ALLOW);
    return s;
}
