# include: os_sandbox

*Community 10 | 6 files | cohesion 0.62*

## Definition

This community groups 6 file(s) rooted at `include` with dominant language c (cohesion 0.62). Central symbols: `FREEDOM_OS_SANDBOX_H`, `FREEDOM_RENDERER_H`, `LL_FS_BASE`, `OS_ALLOWED_N`, `OS_SECCOMP_ARCH`, `RD_MAX_FIELD`, `RD_MAX_INPUT`, `_GNU_SOURCE`. Core file: `src/os_sandbox.c` (31 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/os_sandbox.h` | h | utility | 12 | no |
| `include/renderer.h` | h | presentation | 7 | no |
| `src/os_sandbox.c` | c | utility | 31 | no |
| `src/renderer.c` | c | presentation | 6 | no |
| `tests/test_os_sandbox.c` | c | testing | 19 | no |
| `tests/test_renderer.c` | c | testing | 8 | no |

## Key Symbols

- `FREEDOM_OS_SANDBOX_H` (macro, `include/os_sandbox.h:2`) `#define FREEDOM_OS_SANDBOX_H`
- `os_status` (enum, `include/os_sandbox.h:21`)
- `os_violation` (enum, `include/os_sandbox.h:30`) - function (os_policy_allows) that mirrors the installed BPF program.  See spec/os_sandbox.md for the
- `flags` (function, `include/os_sandbox.h:39`) `* permission also depends on the protection flags (see os_prot_allowed / W^X). *`
- `os_policy_size` (function, `include/os_sandbox.h:43`) `size_t os_policy_size(void);` - Nonzero iff syscall_nr is on the strict allowlist (mirrors the BPF program). This is MEMBERSHIP only
- `os_prot_allowed` (function, `include/os_sandbox.h:52`) `int os_prot_allowed(long syscall_nr, unsigned long prot);` - Pure mirror of the BPF program's EFFECTIVE decision for memory syscalls (W^X). Nonzero iff a call to
- `denied` (function, `include/os_sandbox.h:59`) `* request PROT_EXEC are denied (see os_prot_allowed). * Returns OS_ERR_UNSUPPORT`
- `namespace` (function, `include/os_sandbox.h:75`) `* namespace (the unprivileged enabler), network (the worker never needs the * ne`
- `os_namespace_flags` (function, `include/os_sandbox.h:81`) `int os_namespace_flags(void);` - The set of CLONE_* namespace flags the worker isolates into: a new user namespace (the unprivileged
- `os_fs_access` (enum, `include/os_sandbox.h:102`) - the mandatory boundary.  MUST be called from a SINGLE-THREADED context (e.g. straight after fork, be
- `os_fs_rule` (struct, `include/os_sandbox.h:108`)
- `os_landlock_abi` (function, `include/os_sandbox.h:114`) `int os_landlock_abi(void);` - /* What a Landlock rule permits at/below a path. typedef enum os_fs_access { OS_FS_NONE       = 0, /
- `FREEDOM_RENDERER_H` (macro, `include/renderer.h:2`) `#define FREEDOM_RENDERER_H`
- `rd_status` (enum, `include/renderer.h:20`)
- `status` (type_alias, `include/renderer.h:28`) `typedef struct rd_result { rd_status status;`
- `rd_result` (struct, `include/renderer.h:29`)
- `RD_MAX_INPUT` (macro, `include/renderer.h:37`) `#define RD_MAX_INPUT`
- `RD_MAX_FIELD` (macro, `include/renderer.h:38`) `#define RD_MAX_FIELD`
- `rd_result_free` (function, `include/renderer.h:46`) `void rd_result_free(rd_result *out);` - Renders untrusted HTML out-of-process and returns an inert title + text. html == NULL or out == NULL
- `_GNU_SOURCE` (macro, `src/os_sandbox.c:13`) `#define _GNU_SOURCE`
- `OS_ALLOWED_N` (macro, `src/os_sandbox.c:50`) `#define OS_ALLOWED_N`
- `os_policy_allows` (function, `src/os_sandbox.c:52`) `int os_policy_allows(long syscall_nr)`
- `os_policy_size` (function, `src/os_sandbox.c:59`) `size_t os_policy_size(void)`
- `os_prot_allowed` (function, `src/os_sandbox.c:65`) `int os_prot_allowed(long syscall_nr, unsigned long prot)` - W^X mirror: mmap/mprotect keep their membership but lose any request that asks * for executable memo
- `os_no_dump` (function, `src/os_sandbox.c:75`) `os_status os_no_dump(void)` - Anti-dump defense in depth: undumpable + no core file, so neither a crash nor a foreign ptrace can e
- `excluded` (function, `src/os_sandbox.c:89`) `* intentionally excluded (they need /proc remounting and a post-unshare fork). *`
- `os_isolate_namespaces` (function, `src/os_sandbox.c:94`) `os_status os_isolate_namespaces(void)`
- `os_policy_allows` (function, `src/os_sandbox.c:106`) `int os_policy_allows(long syscall_nr)`
- `os_policy_size` (function, `src/os_sandbox.c:107`) `size_t os_policy_size(void)`
- `os_prot_allowed` (function, `src/os_sandbox.c:108`) `int os_prot_allowed(long syscall_nr, unsigned long prot)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 5
- Cross-boundary resolved imports (EXTRACTED): 3

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- [layer strict] `tests/test_renderer.c` (testing) -> `include/renderer.h` (presentation)

## Open Questions

- Why do 6 file(s) lack file-level docs (e.g. `include/os_sandbox.h`)? What purpose do they serve?
- What would break if the most connected file in include: os_sandbox changed?
- Should include: os_sandbox be split, given cohesion 0.62?

## Sources

- `include/os_sandbox.h`
- `include/renderer.h`
- `src/os_sandbox.c`
- `src/renderer.c`
- `tests/test_os_sandbox.c`
- `tests/test_renderer.c`
