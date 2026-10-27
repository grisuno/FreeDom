# include: local_store

include: local_store groups 24 files (c, h) around FREEDOM_LOCAL_STORE_H, LS_KEY_LEN, LS_SALT_LEN, LS_NONCE_LEN, LS_TAG_LEN. cf_set_store: Cache-aware GET.

```mermaid
graph LR
    include["include"]
    src["src"]
    tests["tests"]
    include -- "calls into" --> src
    src -- "calls into" --> include
    tests -- "calls into" --> include
    tests -- "calls into" --> src
```

## include (5.1)

include groups 8 files (h) around FREEDOM_LOCAL_STORE_H, LS_KEY_LEN, LS_SALT_LEN, LS_NONCE_LEN, LS_TAG_LEN. cf_set_store: Cache-aware GET.

## src (5.2)

src groups 8 files (c) around _POSIX_C_SOURCE, trace, cf_set_store, cf_store, cacheable_request. trace: fetcher, and so the same policy, as an uncached request.  #define...

## tests (5.3)

tests groups 8 files (c) around _GNU_SOURCE, NOW, fake_fetch, setup, teardown.

**Files**:

- include/cached_fetch.h
- include/disk_store.h
- include/http_cache.h
- include/local_store.h
- include/pq_seal.h
- include/prefs.h
- include/profile.h
- include/zoom.h
- src/cached_fetch.c
- src/disk_store.c
- src/http_cache.c
- src/local_store.c
- src/pq_seal.c
- src/prefs.c
- src/profile.c
- src/zoom.c
- tests/test_cached_fetch.c
- tests/test_disk_store.c
- tests/test_http_cache.c
- tests/test_local_store.c
- tests/test_pq_seal.c
- tests/test_prefs.c
- tests/test_profile.c
- tests/test_zoom.c
