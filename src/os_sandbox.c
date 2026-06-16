/*
 * os_sandbox — implementation: fail-closed seccomp-bpf syscall confinement.
 *
 * The allowlist below is the single source of truth: os_policy_allows scans it
 * (pure, directly testable) and os_harden compiles the very same list into the
 * BPF program it installs, so the tested policy is the enforced policy.
 *
 * The filter rejects any architecture other than x86_64 (ABI-confusion
 * defence), allows the listed syscalls, and applies the default action
 * (KILL or ERRNO) to everything else. Raw seccomp via prctl, no libseccomp.
 */

#define _GNU_SOURCE

#include "os_sandbox.h"

#if defined(__linux__)
#include <sys/syscall.h>

/* Allowlist for an already-initialised worker: I/O over already-open fds and
 * computation, never opening new resources. Deliberately excludes open/openat,
 * socket/connect, execve, ptrace, clone/fork, etc. */
static const long os_allowed[] = {
    __NR_read, __NR_write, __NR_readv, __NR_writev, __NR_close, __NR_lseek,
    __NR_fstat,
    __NR_mmap, __NR_munmap, __NR_mremap, __NR_mprotect, __NR_brk, __NR_madvise,
    __NR_rt_sigreturn, __NR_rt_sigaction, __NR_rt_sigprocmask, __NR_sigaltstack,
    __NR_futex, __NR_getpid, __NR_gettid, __NR_getrandom,
    __NR_clock_gettime, __NR_clock_getres, __NR_clock_nanosleep, __NR_nanosleep,
    __NR_gettimeofday, __NR_sched_yield,
    __NR_exit, __NR_exit_group, __NR_restart_syscall,
};

#define OS_ALLOWED_N (sizeof os_allowed / sizeof os_allowed[0])

int os_policy_allows(long syscall_nr) {
    for (size_t i = 0; i < OS_ALLOWED_N; ++i) {
        if (os_allowed[i] == syscall_nr) return 1;
    }
    return 0;
}

size_t os_policy_size(void) {
    return OS_ALLOWED_N;
}

#else /* non-Linux: no seccomp-bpf */

int os_policy_allows(long syscall_nr) { (void)syscall_nr; return 0; }
size_t os_policy_size(void) { return 0; }

os_status os_harden(os_violation action) { (void)action; return OS_ERR_UNSUPPORTED; }

#endif

#if defined(__linux__) && defined(__x86_64__)

#include <errno.h>
#include <stddef.h>
#include <linux/audit.h>
#include <linux/filter.h>
#include <linux/seccomp.h>
#include <sys/prctl.h>

os_status os_harden(os_violation action) {
    const unsigned int deny = (action == OS_VIOLATION_ERRNO)
        ? (SECCOMP_RET_ERRNO | (EPERM & SECCOMP_RET_DATA))
        : SECCOMP_RET_KILL_PROCESS;

    /* 4 header instructions + 2 per allowed syscall + 1 default action. */
    struct sock_filter prog[4 + 2 * OS_ALLOWED_N + 1];
    size_t n = 0;

    /* Reject any ABI other than x86_64 before inspecting the syscall number. */
    prog[n++] = (struct sock_filter)BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
                                             offsetof(struct seccomp_data, arch));
    prog[n++] = (struct sock_filter)BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K,
                                             AUDIT_ARCH_X86_64, 1, 0);
    prog[n++] = (struct sock_filter)BPF_STMT(BPF_RET | BPF_K,
                                             SECCOMP_RET_KILL_PROCESS);
    prog[n++] = (struct sock_filter)BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
                                             offsetof(struct seccomp_data, nr));

    for (size_t i = 0; i < OS_ALLOWED_N; ++i) {
        /* if nr == allowed[i] fall through to ALLOW, else skip it. */
        prog[n++] = (struct sock_filter)BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K,
                                                 (unsigned int)os_allowed[i], 0, 1);
        prog[n++] = (struct sock_filter)BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW);
    }

    prog[n++] = (struct sock_filter)BPF_STMT(BPF_RET | BPF_K, deny);

    struct sock_fprog fprog = { .len = (unsigned short)n, .filter = prog };

    /* Required so an unprivileged process may install a filter, and so the
     * confinement cannot be shed by gaining privileges later. */
    if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) != 0) return OS_ERR_PRCTL;
    if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &fprog, 0, 0) != 0) return OS_ERR_PRCTL;
    return OS_OK;
}

#elif defined(__linux__)

/* Linux on a non-x86_64 architecture: the BPF arch guard above is x86_64-only,
 * so refuse rather than install an incomplete policy (fail closed). */
os_status os_harden(os_violation action) { (void)action; return OS_ERR_UNSUPPORTED; }

#endif

/* --- Landlock filesystem confinement (architecture-independent) --- */

#if defined(__linux__) && defined(__NR_landlock_create_ruleset)

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <linux/landlock.h>
#include <sys/prctl.h>
#include <sys/syscall.h>

static long ll_create_ruleset(const struct landlock_ruleset_attr *attr,
                              size_t size, uint32_t flags) {
    return syscall(__NR_landlock_create_ruleset, attr, size, flags);
}

static long ll_add_rule(int fd, enum landlock_rule_type type,
                        const void *attr, uint32_t flags) {
    return syscall(__NR_landlock_add_rule, fd, type, attr, flags);
}

static long ll_restrict_self(int fd, uint32_t flags) {
    return syscall(__NR_landlock_restrict_self, fd, flags);
}

/* Filesystem rights present since Landlock ABI v1. */
#define LL_FS_BASE ( \
      LANDLOCK_ACCESS_FS_EXECUTE     | LANDLOCK_ACCESS_FS_WRITE_FILE  \
    | LANDLOCK_ACCESS_FS_READ_FILE   | LANDLOCK_ACCESS_FS_READ_DIR    \
    | LANDLOCK_ACCESS_FS_REMOVE_DIR  | LANDLOCK_ACCESS_FS_REMOVE_FILE \
    | LANDLOCK_ACCESS_FS_MAKE_CHAR   | LANDLOCK_ACCESS_FS_MAKE_DIR    \
    | LANDLOCK_ACCESS_FS_MAKE_REG    | LANDLOCK_ACCESS_FS_MAKE_SOCK   \
    | LANDLOCK_ACCESS_FS_MAKE_FIFO   | LANDLOCK_ACCESS_FS_MAKE_BLOCK  \
    | LANDLOCK_ACCESS_FS_MAKE_SYM )

/* The set of FS rights the ruleset handles, masked to what this ABI supports so
 * landlock_create_ruleset does not fail with EINVAL on older kernels. */
static uint64_t ll_handled(int abi) {
    uint64_t h = LL_FS_BASE;
#ifdef LANDLOCK_ACCESS_FS_REFER
    if (abi >= 2) h |= LANDLOCK_ACCESS_FS_REFER;
#endif
#ifdef LANDLOCK_ACCESS_FS_TRUNCATE
    if (abi >= 3) h |= LANDLOCK_ACCESS_FS_TRUNCATE;
#endif
#ifdef LANDLOCK_ACCESS_FS_IOCTL_DEV
    if (abi >= 5) h |= LANDLOCK_ACCESS_FS_IOCTL_DEV;
#endif
    return h;
}

static uint64_t ll_read_access(uint64_t handled) {
    return handled & (LANDLOCK_ACCESS_FS_EXECUTE
                    | LANDLOCK_ACCESS_FS_READ_FILE
                    | LANDLOCK_ACCESS_FS_READ_DIR);
}

int os_landlock_abi(void) {
    long abi = ll_create_ruleset(NULL, 0, LANDLOCK_CREATE_RULESET_VERSION);
    if (abi < 0) return (errno == ENOSYS || errno == EOPNOTSUPP) ? 0 : -1;
    return (int)abi;
}

os_status os_landlock_restrict(const os_fs_rule *rules, size_t n) {
    if (n > 0 && rules == NULL) return OS_ERR_LANDLOCK;

    int abi = os_landlock_abi();
    if (abi <= 0) return OS_ERR_UNSUPPORTED;

    uint64_t handled = ll_handled(abi);

    struct landlock_ruleset_attr attr;
    memset(&attr, 0, sizeof attr);
    attr.handled_access_fs = handled;
    /* sizeof(attr) is safe across ABIs: the kernel accepts a larger struct as
     * long as the unknown trailing fields (net/scoped) are zero, which they are. */
    int rfd = (int)ll_create_ruleset(&attr, sizeof attr, 0);
    if (rfd < 0) return OS_ERR_LANDLOCK;

    for (size_t i = 0; i < n; ++i) {
        if (rules[i].path == NULL) { close(rfd); return OS_ERR_LANDLOCK; }
        int pfd = open(rules[i].path, O_PATH | O_CLOEXEC);
        if (pfd < 0) { close(rfd); return OS_ERR_LANDLOCK; }

        struct landlock_path_beneath_attr pb;
        memset(&pb, 0, sizeof pb);
        pb.allowed_access = (rules[i].access == OS_FS_READ)
                                ? ll_read_access(handled) : handled;
        pb.parent_fd = pfd;
        long rc = ll_add_rule(rfd, LANDLOCK_RULE_PATH_BENEATH, &pb, 0);
        close(pfd);
        if (rc != 0) { close(rfd); return OS_ERR_LANDLOCK; }
    }

    /* No-new-privs is required before restrict_self; it also pins the domain. */
    if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) != 0) { close(rfd); return OS_ERR_LANDLOCK; }
    if (ll_restrict_self(rfd, 0) != 0) { close(rfd); return OS_ERR_LANDLOCK; }
    close(rfd);
    return OS_OK;
}

#else /* non-Linux, or kernel headers without Landlock */

int os_landlock_abi(void) { return 0; }
os_status os_landlock_restrict(const os_fs_rule *rules, size_t n) {
    (void)rules; (void)n; return OS_ERR_UNSUPPORTED;
}

#endif
