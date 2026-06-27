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
#include <errno.h>
#include <sched.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/resource.h>
#include <sys/syscall.h>

/* Allowlist for an already-initialised worker: I/O over already-open fds and
 * computation, never opening new resources. Deliberately excludes open/openat,
 * socket/connect, execve, ptrace, clone/fork, etc.
 *
 * This is an allowlist (deny-by-default), which is what makes io_uring
 * (io_uring_setup/enter/register) and the other seccomp-bypass primitives
 * (process_vm_readv/writev, bpf, userfaultfd, ...) denied by construction -- a
 * denylist could forget them. io_uring matters most: its IORING_OP_* operations are
 * dispatched by a kernel worker WITHOUT re-entering the syscall entry point this BPF
 * program filters, so a ring would let a compromised worker openat/connect past the
 * filter. It must never be added here "for async I/O" -- the worker only does blocking
 * pipe I/O, and the io_uring doctrine (CLAUDE.md §3) applies to the trusted side only.
 * See spec/os_sandbox.md §13; locked by test_policy_denies_io_uring +
 * test_harden_kills_io_uring_setup. */
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

/* W^X mirror: mmap/mprotect keep their membership but lose any request that asks
 * for executable memory. The single source of truth the BPF prot-check replicates. */
int os_prot_allowed(long syscall_nr, unsigned long prot) {
    if (!os_policy_allows(syscall_nr)) return 0;
    if (syscall_nr == __NR_mmap || syscall_nr == __NR_mprotect)
        return (prot & PROT_EXEC) ? 0 : 1;
    return 1;
}

/* Anti-dump defense in depth: undumpable + no core file, so neither a crash nor a
 * foreign ptrace can exfiltrate worker secrets. Best-effort; call before os_harden
 * (prctl is not on the seccomp allowlist). */
os_status os_no_dump(void) {
    if (prctl(PR_SET_DUMPABLE, 0, 0, 0, 0) != 0) return OS_ERR_PRCTL;
    /* PR_SET_DUMPABLE=0 already disables core dumps and blocks non-parent ptrace;
     * pinning RLIMIT_CORE to 0 is belt-and-suspenders and may legitimately fail
     * under a pre-existing lower hard cap, so its failure is non-fatal. */
    struct rlimit rl = { .rlim_cur = 0, .rlim_max = 0 };
    (void)setrlimit(RLIMIT_CORE, &rl);
    return OS_OK;
}

/* Namespace isolation: defense in depth under seccomp. A new user namespace is the
 * unprivileged enabler for the rest; the worker never touches the network (the
 * parent fetches), so it gets an empty network stack; IPC and UTS isolate it from
 * shared System V/POSIX IPC and the host identity. Mount and PID namespaces are
 * intentionally excluded (they need /proc remounting and a post-unshare fork). */
int os_namespace_flags(void) {
    return CLONE_NEWUSER | CLONE_NEWNET | CLONE_NEWIPC | CLONE_NEWUTS;
}

os_status os_isolate_namespaces(void) {
    if (unshare(os_namespace_flags()) != 0) {
        /* Unprivileged user namespaces disabled (EPERM) or unsupported kernel
         * (EINVAL/ENOSYS): not fatal -- seccomp remains the mandatory boundary. */
        return (errno == EPERM || errno == EINVAL || errno == ENOSYS)
               ? OS_ERR_UNSUPPORTED : OS_ERR_NAMESPACE;
    }
    return OS_OK;
}

#else /* non-Linux: no seccomp-bpf, no Linux namespaces */

int os_policy_allows(long syscall_nr) { (void)syscall_nr; return 0; }
size_t os_policy_size(void) { return 0; }
int os_prot_allowed(long syscall_nr, unsigned long prot) {
    (void)syscall_nr; (void)prot; return 0;
}
os_status os_no_dump(void) { return OS_ERR_UNSUPPORTED; }

os_status os_harden(os_violation action) { (void)action; return OS_ERR_UNSUPPORTED; }

int os_namespace_flags(void) { return 0; }
os_status os_isolate_namespaces(void) { return OS_ERR_UNSUPPORTED; }

#endif

/* seccomp-bpf is supported on x86_64 and little-endian aarch64. Both are
 * little-endian, which the W^X args[2] low-word load relies on (PROT_EXEC lives in
 * the low 32 bits); big-endian aarch64 (__AARCH64EB__) is therefore NOT enabled and
 * falls through to the fail-closed OS_ERR_UNSUPPORTED stub below. The allowlist uses
 * only generic-ABI syscalls, so the __NR_* macros resolve to the correct per-arch
 * numbers automatically. */
#if defined(__linux__) && (defined(__x86_64__) || \
    (defined(__aarch64__) && !defined(__AARCH64EB__)))

#include <errno.h>
#include <stddef.h>
#include <linux/audit.h>
#include <linux/filter.h>
#include <linux/seccomp.h>
#include <sys/mman.h>
#include <sys/prctl.h>

/* The native ABI token the BPF arch guard pins to (rejects x32/i386 on x86_64 and
 * AArch32 on aarch64 -- syscall-ABI-confusion defence). */
#if defined(__x86_64__)
#  define OS_SECCOMP_ARCH AUDIT_ARCH_X86_64
#else
#  define OS_SECCOMP_ARCH AUDIT_ARCH_AARCH64
#endif

os_status os_harden(os_violation action) {
    const unsigned int deny = (action == OS_VIOLATION_ERRNO)
        ? (SECCOMP_RET_ERRNO | (EPERM & SECCOMP_RET_DATA))
        : SECCOMP_RET_KILL_PROCESS;

    /* Header (4) + 2 W^X branch instructions + 2 per generic syscall + RET deny (1)
     * + 5-instruction PROT_EXEC check block. Sized with OS_ALLOWED_N (generic loop
     * emits fewer, since mmap/mprotect are branched out). */
    struct sock_filter prog[4 + 2 + 2 * OS_ALLOWED_N + 1 + 5];
    size_t n = 0;

    /* Reject any ABI other than the one we built for before inspecting the syscall
     * number (x32/i386 on x86_64, AArch32 on aarch64). */
    prog[n++] = (struct sock_filter)BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
                                             offsetof(struct seccomp_data, arch));
    prog[n++] = (struct sock_filter)BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K,
                                             OS_SECCOMP_ARCH, 1, 0);
    prog[n++] = (struct sock_filter)BPF_STMT(BPF_RET | BPF_K,
                                             SECCOMP_RET_KILL_PROCESS);
    prog[n++] = (struct sock_filter)BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
                                             offsetof(struct seccomp_data, nr));

    /* W^X: mmap/mprotect are allowed only when they do NOT request PROT_EXEC. Branch
     * them to the protection-check block (jt patched once its index is known); a
     * non-match falls through (jf=0) to the generic allowlist below. */
    size_t at_mmap = n;
    prog[n++] = (struct sock_filter)BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K,
                                             (unsigned int)__NR_mmap, 0, 0);
    size_t at_mprotect = n;
    prog[n++] = (struct sock_filter)BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K,
                                             (unsigned int)__NR_mprotect, 0, 0);

    /* Generic allowlist, excluding the two W^X syscalls handled above. */
    for (size_t i = 0; i < OS_ALLOWED_N; ++i) {
        if (os_allowed[i] == __NR_mmap || os_allowed[i] == __NR_mprotect) continue;
        /* if nr == allowed[i] fall through to ALLOW, else skip it. */
        prog[n++] = (struct sock_filter)BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K,
                                                 (unsigned int)os_allowed[i], 0, 1);
        prog[n++] = (struct sock_filter)BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW);
    }

    prog[n++] = (struct sock_filter)BPF_STMT(BPF_RET | BPF_K, deny);

    /* PROT_EXEC check block: load the low word of args[2] (prot) and mask PROT_EXEC.
     * Zero => no exec page requested => ALLOW; nonzero => DENY. Both supported arches
     * (x86_64, aarch64 LE) are little-endian -- big-endian is excluded above -- and
     * PROT_EXEC lives in the low 32 bits, so the 32-bit word load of args[2] is
     * sufficient. */
    size_t prot_check = n;
    prog[n++] = (struct sock_filter)BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
                                             offsetof(struct seccomp_data, args[2]));
    prog[n++] = (struct sock_filter)BPF_STMT(BPF_ALU | BPF_AND | BPF_K, PROT_EXEC);
    prog[n++] = (struct sock_filter)BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0, 1, 0);
    prog[n++] = (struct sock_filter)BPF_STMT(BPF_RET | BPF_K, deny);
    prog[n++] = (struct sock_filter)BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW);

    /* Patch the two W^X forward jumps now that the block's index is known. The list
     * is a small compile-time constant, so these offsets fit the u8 jump field with
     * wide headroom (room for ~125 allowed syscalls). */
    prog[at_mmap].jt     = (unsigned char)(prot_check - (at_mmap + 1));
    prog[at_mprotect].jt = (unsigned char)(prot_check - (at_mprotect + 1));

    struct sock_fprog fprog = { .len = (unsigned short)n, .filter = prog };

    /* Required so an unprivileged process may install a filter, and so the
     * confinement cannot be shed by gaining privileges later. */
    if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) != 0) return OS_ERR_PRCTL;
    if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &fprog, 0, 0) != 0) return OS_ERR_PRCTL;
    return OS_OK;
}

#elif defined(__linux__)

/* Linux on an unsupported architecture (not x86_64, not little-endian aarch64): the
 * BPF arch guard and the W^X little-endian assumption do not hold, so refuse rather
 * than install an incomplete or wrong policy (fail closed). */
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
