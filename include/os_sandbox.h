#ifndef FREEDOM_OS_SANDBOX_H
#define FREEDOM_OS_SANDBOX_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * os_sandbox — kernel-level syscall confinement (seccomp-bpf on Linux/x86_64).
 *
 * Last Zero-Trust boundary: a fail-closed syscall allowlist so that even a
 * compromised parser / JS engine / bridge cannot open files, open sockets,
 * exec, ptrace, etc. The security policy lives in a pure, directly testable
 * function (os_policy_allows) that mirrors the installed BPF program.
 *
 * See spec/os_sandbox.md for the full contract.
 */

typedef enum os_status {
    OS_OK = 0,
    OS_ERR_UNSUPPORTED, /* not Linux/x86_64, or seccomp-bpf / Landlock / namespaces unavailable */
    OS_ERR_PRCTL,       /* prctl(NO_NEW_PRIVS) or seccomp install failed */
    OS_ERR_LANDLOCK,    /* Landlock ruleset creation / rule / restrict_self failed */
    OS_ERR_NAMESPACE    /* unshare() of the requested namespaces failed */
} os_status;

/* Action taken when a denied syscall is attempted. */
typedef enum os_violation {
    OS_VIOLATION_KILL = 0, /* default: SIGSYS-kill the process (fail closed) */
    OS_VIOLATION_ERRNO     /* deny with EPERM (diagnostic / compatibility) */
} os_violation;

/* --- Pure policy surface (no side effects): the primary test surface. --- */

/* Nonzero iff syscall_nr is on the strict allowlist (mirrors the BPF program).
 * This is MEMBERSHIP only: mmap/mprotect are members, but their effective
 * permission also depends on the protection flags (see os_prot_allowed / W^X). */
int os_policy_allows(long syscall_nr);

/* Number of syscalls on the allowlist. */
size_t os_policy_size(void);

/* Pure mirror of the BPF program's EFFECTIVE decision for memory syscalls (W^X).
 * Nonzero iff a call to syscall_nr with the given memory-protection flags would
 * be permitted. For non-memory syscalls this is just os_policy_allows(syscall_nr);
 * for mmap/mprotect it is additionally false when prot requests PROT_EXEC, because
 * the worker is an interpreter over already-mapped code and never needs to create
 * or flip executable pages. Denying PROT_EXEC removes the last step of native code
 * injection even after a control-flow hijack. No side effects. */
int os_prot_allowed(long syscall_nr, unsigned long prot);

/* --- Enforcement (irreversible). --- */

/* Installs the fail-closed seccomp-bpf allowlist on the calling process.
 * Once installed it cannot be removed or relaxed. Call after initialisation,
 * before touching untrusted content. The filter enforces W^X: mmap/mprotect that
 * request PROT_EXEC are denied (see os_prot_allowed).
 * Returns OS_ERR_UNSUPPORTED on platforms without seccomp-bpf x86_64. */
os_status os_harden(os_violation action);

/* Anti-dump defense in depth: prctl(PR_SET_DUMPABLE, 0) plus setrlimit(RLIMIT_CORE,
 * 0), so a crash leaves no core file and no foreign (non-parent) process can
 * ptrace-attach or read /proc/<pid>/mem. This prevents post-compromise exfiltration
 * of worker secrets (the canvas/audio readback session key, decrypted page bytes).
 * Best-effort like Landlock/namespaces; call BEFORE os_harden (it uses prctl, which
 * the seccomp filter does not allow). Returns OS_OK, or OS_ERR_PRCTL if
 * PR_SET_DUMPABLE failed. OS_ERR_UNSUPPORTED on non-Linux. */
os_status os_no_dump(void);

/* --- Namespace isolation (Linux): defense in depth around the worker. --- */

/* The set of CLONE_* namespace flags the worker isolates into: a new user
 * namespace (the unprivileged enabler), network (the worker never needs the
 * network -- the parent fetches and passes bytes -- so it gets an empty stack),
 * IPC and UTS namespaces. Pure: returns the same constant the enforcer requests,
 * the directly testable mirror of what os_isolate_namespaces applies. 0 on
 * platforms without these namespaces. Mount and PID namespaces are out of scope
 * (they need extra plumbing); see spec/os_sandbox.md. */
int os_namespace_flags(void);

/* Detaches the calling process into fresh namespaces (os_namespace_flags) via
 * unshare(2). This is DEFENSE IN DEPTH layered under seccomp (which already
 * forbids socket/connect): even a kernel-bug bypass of the syscall filter finds
 * no network, no shared IPC and no host identity. Best-effort, exactly like
 * os_landlock_restrict: callers treat a failure as non-fatal because seccomp is
 * the mandatory boundary.
 *
 * MUST be called from a SINGLE-THREADED context (e.g. straight after fork, before
 * any thread or untrusted content): unshare(CLONE_NEWUSER) requires it. Does NOT
 * set up uid/gid maps (the worker only computes; its in-namespace uid is
 * irrelevant) so it performs no /proc writes. Returns OS_OK on success,
 * OS_ERR_UNSUPPORTED where unprivileged user namespaces are disabled, or
 * OS_ERR_NAMESPACE on other unshare failure. Inherited pipe fds keep working
 * across all of these namespaces. */
os_status os_isolate_namespaces(void);

/* --- Landlock filesystem confinement (Linux >= 5.13). --- */

/* What a Landlock rule permits at/below a path. */
typedef enum os_fs_access {
    OS_FS_NONE       = 0, /* no access (not used in rules; documents intent) */
    OS_FS_READ       = 1, /* read files, list dirs, execute */
    OS_FS_READ_WRITE = 2  /* the above plus create/write/remove/truncate */
} os_fs_access;

typedef struct os_fs_rule {
    const char  *path;   /* file or directory (a "beneath" hierarchy) */
    os_fs_access access;  /* what is permitted at/below path */
} os_fs_rule;

/* Kernel Landlock ABI version (>=1), 0 if unsupported, <0 on query error. */
int os_landlock_abi(void);

/* Confines the calling process to the given filesystem rules via Landlock:
 * any filesystem access not covered by a rule is denied. rules == NULL or n == 0
 * denies ALL filesystem access. Irreversible. Must be called BEFORE os_harden
 * (it uses Landlock syscalls and, with rules, open(O_PATH), which seccomp would
 * block). Fail-closed: never leaves a partial confinement.
 * Returns OS_ERR_UNSUPPORTED if the kernel lacks Landlock. */
os_status os_landlock_restrict(const os_fs_rule *rules, size_t n);

#endif /* FREEDOM_OS_SANDBOX_H */
