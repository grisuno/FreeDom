# include

*Community 13 | 3 files | cohesion 0.50*

## Definition

This community groups 3 file(s) rooted at `include` with dominant language c (cohesion 0.50). Central symbols: `FREEDOM_OS_SANDBOX_H`, `LL_FS_BASE`, `OS_ALLOWED_N`, `OS_SECCOMP_ARCH`, `_GNU_SOURCE`, `denied`, `excluded`, `fields`. Core file: `src/os_sandbox.c` (31 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/os_sandbox.h` | h | utility | 12 | no |
| `src/os_sandbox.c` | c | utility | 31 | no |
| `tests/test_os_sandbox.c` | c | testing | 19 | no |

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
- `os_no_dump` (function, `src/os_sandbox.c:111`) `os_status os_no_dump(void)`
- `os_harden` (function, `src/os_sandbox.c:113`) `os_status os_harden(os_violation action)`
- `os_namespace_flags` (function, `src/os_sandbox.c:115`) `int os_namespace_flags(void)`
- `os_isolate_namespaces` (function, `src/os_sandbox.c:116`) `os_status os_isolate_namespaces(void)`
- `OS_SECCOMP_ARCH` (macro, `src/os_sandbox.c:140`) `#  define OS_SECCOMP_ARCH`
- `OS_SECCOMP_ARCH` (macro, `src/os_sandbox.c:142`) `#  define OS_SECCOMP_ARCH`
- `os_harden` (function, `src/os_sandbox.c:145`) `os_status os_harden(os_violation action)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 2

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- [dataflow DEAD_STORE] `src/os_sandbox.c:154` `os_harden` `n`: `n` assigned at line 154 but never read afterwards.

## Open Questions

- Why do 3 file(s) lack file-level docs (e.g. `include/os_sandbox.h`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.50?

## Sources

- `include/os_sandbox.h`
- `src/os_sandbox.c`
- `tests/test_os_sandbox.c`
