#ifndef FREEDOM_FRAME_BROKER_H
#define FREEDOM_FRAME_BROKER_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * frame_broker -- pure frame tree + postMessage routing decisions for the trusted parent.
 * Each iframe is its own confined worker; the parent mediates every message. See
 * spec/frame_broker.md.
 */

#define FBK_MAX_FRAMES 16
#define FBK_MAX_DEPTH  4
#define FBK_MAX_MSG    ((size_t)1048576)
#define FBK_ORIGIN_MAX 300
#define FBK_URL_MAX    2048

typedef enum fbk_rel { FBK_REL_PARENT = 0, FBK_REL_TOP, FBK_REL_CHILD } fbk_rel;

typedef enum fbk_verdict {
    FBK_DELIVER = 0,     /* deliver to dest */
    FBK_DROP_ORIGIN,     /* targetOrigin mismatch: drop silently (HTML postMessage) */
    FBK_ERR_FRAME,       /* unknown/dead frame or non-addressable relation */
    FBK_ERR_SIZE         /* payload over FBK_MAX_MSG */
} fbk_verdict;

typedef struct fbk_frame {
    int  used;
    int  parent;                      /* -1 for the top document */
    int  depth;
    char origin[FBK_ORIGIN_MAX];
} fbk_frame;

typedef struct fbk_table { fbk_frame f[FBK_MAX_FRAMES]; } fbk_table;

/* Serialized origin ("https://host[:port]", lowercase) or "null" for opaque/non-https/unparseable.
 * 0 on success, -1 if out does not fit or args are NULL. */
int fbk_origin_of(const char *url, char *out, size_t cap);

/* Resets t and registers the top document (frame 0) for top_url. 0 / -1. */
int fbk_init(fbk_table *t, const char *top_url);

/* Adds a child of `parent` for url. Writes its id. 0 on success; -1 on a bad parent, depth over
 * FBK_MAX_DEPTH, full table or NULL args (fail closed). */
int fbk_add(fbk_table *t, int parent, const char *url, int *out_id);

/* Removes frame id and its whole subtree. The top (0) cannot be removed. Idempotent. */
void fbk_remove(fbk_table *t, int id);

/* Origin of a live frame or NULL. */
const char *fbk_origin(const fbk_table *t, int id);

/* Routes a postMessage from `from`. For FBK_REL_CHILD `child` must be a direct child of `from`.
 * target_origin is the page-supplied string ("*", "/", or an origin). On FBK_DELIVER *dest is the
 * receiving frame. size is the serialized payload length. */
fbk_verdict fbk_route(const fbk_table *t, int from, fbk_rel rel, int child,
                      const char *target_origin, size_t size, int *dest);

#endif /* FREEDOM_FRAME_BROKER_H */
