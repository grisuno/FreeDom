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

/* Nonzero iff syscall_nr is on the strict allowlist (mirrors the BPF program). */
int os_policy_allows(long syscall_nr);

/* Number of syscalls on the allowlist. */
size_t os_policy_size(void);

/* --- Enforcement (irreversible). --- */

/* Installs the fail-closed seccomp-bpf allowlist on the calling process.
 * Once installed it cannot be removed or relaxed. Call after initialisation,
 * before touching untrusted content.
 * Returns OS_ERR_UNSUPPORTED on platforms without seccomp-bpf x86_64. */
os_status os_harden(os_violation action);

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
