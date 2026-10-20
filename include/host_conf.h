#ifndef FREEDOM_HOST_CONF_H
#define FREEDOM_HOST_CONF_H

#include <stddef.h>

#include "hostblock.h"

/*
 * host_conf -- the ONE place the user's host lists (block.conf, allow.conf, js.conf) are
 * located and loaded. The GUI and the headless mode both go through it, so the page a
 * human sees and the page a benchmark renders are decided by the same lists in the same
 * order. See spec/host_conf.md.
 */

#define HCF_MAX_DIRS       3
#define HCF_PATH_MAX       1024
/* A list file larger than this is ignored whole (never truncated mid-line). */
#define HCF_MAX_FILE_BYTES (16u * 1024u * 1024u)

typedef struct hcf_dirs {
    char   path[HCF_MAX_DIRS][HCF_PATH_MAX];
    size_t n;
} hcf_dirs;

/* Pure. Fills out with, in order: env (when non-empty), home + "/.config/freedom" (when
 * home is non-empty), and "config". A directory already present is not added twice.
 * out == NULL is a no-op. */
void hcf_search_dirs(const char *env, const char *home, hcf_dirs *out);

/* hcf_search_dirs over $FREEDOM_HOSTS_DIR and $HOME. */
void hcf_search_dirs_from_env(hcf_dirs *out);

/* block.conf (BLOCK) + allow.conf (ALLOW) from every directory, cumulative. Missing or
 * unreadable files fail open. NULL only on OOM or dirs == NULL. */
hb_set *hcf_load_filter(const hcf_dirs *dirs);

/* One file (js.conf, allow.conf, ...) from every directory as an ALLOW list. NULL only on
 * OOM or a NULL argument. */
hb_set *hcf_load_allowlist(const hcf_dirs *dirs, const char *fname);

#endif /* FREEDOM_HOST_CONF_H */
