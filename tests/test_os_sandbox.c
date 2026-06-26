/*
 * TDD suite for os_sandbox (Hito 4 - OS hardening).
 *
 * RED state until src/os_sandbox.c exists: this links and fails on purpose.
 *
 * The pure allowlist is tested directly. Enforcement is tested by forking:
 * os_harden is irreversible and process-wide, so the child applies it, probes
 * with raw syscalls, and reports via exit status; the parent makes the
 * assertions (the hardened child must not run cmocka).
 *
 * Build: make test   ;   ASan: make asan
 */

#define _GNU_SOURCE

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include <errno.h>
#include <fcntl.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <unistd.h>

#include "os_sandbox.h"

/* --- pure policy --- */

static void test_policy_allows_safe(void **state) {
    (void)state;
    assert_true(os_policy_allows(__NR_read));
    assert_true(os_policy_allows(__NR_write));
    assert_true(os_policy_allows(__NR_getpid));
    assert_true(os_policy_allows(__NR_exit_group));
}

static void test_policy_denies_dangerous(void **state) {
    (void)state;
    assert_false(os_policy_allows(__NR_socket));
    assert_false(os_policy_allows(__NR_openat));
    assert_false(os_policy_allows(__NR_execve));
    assert_false(os_policy_allows(__NR_ptrace));
    assert_false(os_policy_allows(__NR_connect));
}

static void test_policy_size(void **state) {
    (void)state;
    assert_true(os_policy_size() > 0);
}

/* --- enforcement (fork-based) --- */

/* KILL: a denied syscall must terminate the child with SIGSYS. */
static void test_harden_kills_denied_syscall(void **state) {
    (void)state;
    pid_t pid = fork();
    assert_true(pid >= 0);
    if (pid == 0) {
        if (os_harden(OS_VIOLATION_KILL) != OS_OK) _exit(98);
        (void)syscall(__NR_getpid); /* allowed: must survive */
        (void)syscall(__NR_socket, AF_INET, SOCK_STREAM, 0); /* denied -> SIGSYS */
        _exit(0); /* reached only if the filter failed to block */
    }
    int st = 0;
    assert_int_equal(waitpid(pid, &st, 0), pid);
    assert_true(WIFSIGNALED(st));
    assert_int_equal(WTERMSIG(st), SIGSYS);
}

/* KILL: an allowed syscall must pass and let the child exit cleanly. */
static void test_harden_allows_permitted_syscall(void **state) {
    (void)state;
    pid_t pid = fork();
    assert_true(pid >= 0);
    if (pid == 0) {
        if (os_harden(OS_VIOLATION_KILL) != OS_OK) _exit(98);
        long p = syscall(__NR_getpid);
        _exit(p > 0 ? 42 : 43);
    }
    int st = 0;
    assert_int_equal(waitpid(pid, &st, 0), pid);
    assert_true(WIFEXITED(st));
    assert_int_equal(WEXITSTATUS(st), 42);
}

/* ERRNO: a denied syscall must return -1/EPERM instead of killing. */
static void test_harden_errno_denies_with_eperm(void **state) {
    (void)state;
    pid_t pid = fork();
    assert_true(pid >= 0);
    if (pid == 0) {
        if (os_harden(OS_VIOLATION_ERRNO) != OS_OK) _exit(98);
        long r = syscall(__NR_socket, AF_INET, SOCK_STREAM, 0);
        _exit((r < 0 && errno == EPERM) ? 7 : 8);
    }
    int st = 0;
    assert_int_equal(waitpid(pid, &st, 0), pid);
    assert_true(WIFEXITED(st));
    assert_int_equal(WEXITSTATUS(st), 7);
}

/* --- W^X: no executable memory (seccomp argument filtering) --- */

/* Pure mirror: mmap/mprotect are members of the allowlist but lose the request
 * when it asks for PROT_EXEC; other syscalls keep their membership decision. */
static void test_prot_allowed_wx(void **state) {
    (void)state;
    assert_true(os_prot_allowed(__NR_mmap, PROT_READ | PROT_WRITE));
    assert_false(os_prot_allowed(__NR_mmap, PROT_READ | PROT_EXEC));
    assert_false(os_prot_allowed(__NR_mprotect, PROT_EXEC));
    assert_true(os_prot_allowed(__NR_read, 0));             /* non-memory: allowed */
    assert_true(os_prot_allowed(__NR_munmap, 0));           /* memory, not prot-filtered */
    assert_false(os_prot_allowed(__NR_socket, PROT_READ));  /* denied stays denied */
}

/* KILL: a PROT_READ|PROT_WRITE mmap survives but a PROT_EXEC mmap is killed. */
static void test_harden_blocks_exec_mmap(void **state) {
    (void)state;
    pid_t pid = fork();
    assert_true(pid >= 0);
    if (pid == 0) {
        if (os_harden(OS_VIOLATION_KILL) != OS_OK) _exit(98);
        long rw = syscall(__NR_mmap, (void *)0, (size_t)4096,
                          PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t)0);
        if (rw == -1) _exit(60); /* a benign RW mapping must still work */
        (void)syscall(__NR_mmap, (void *)0, (size_t)4096,
                      PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t)0);
        _exit(0); /* reached only if the exec mapping was NOT blocked */
    }
    int st = 0;
    assert_int_equal(waitpid(pid, &st, 0), pid);
    assert_true(WIFSIGNALED(st));
    assert_int_equal(WTERMSIG(st), SIGSYS);
}

/* KILL: flipping a writable page to executable via mprotect is killed. */
static void test_harden_blocks_exec_mprotect(void **state) {
    (void)state;
    pid_t pid = fork();
    assert_true(pid >= 0);
    if (pid == 0) {
        if (os_harden(OS_VIOLATION_KILL) != OS_OK) _exit(98);
        long p = syscall(__NR_mmap, (void *)0, (size_t)4096,
                         PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t)0);
        if (p == -1) _exit(60);
        (void)syscall(__NR_mprotect, (void *)p, (size_t)4096, PROT_READ | PROT_EXEC);
        _exit(0); /* reached only if the exec flip was NOT blocked */
    }
    int st = 0;
    assert_int_equal(waitpid(pid, &st, 0), pid);
    assert_true(WIFSIGNALED(st));
    assert_int_equal(WTERMSIG(st), SIGSYS);
}

/* --- anti-dump (no core / no foreign ptrace) --- */

/* Probed BEFORE seccomp so prctl/getrlimit are still reachable: after os_no_dump
 * the process is undumpable and the core-file limit is zero. */
static void test_no_dump_undumpable(void **state) {
    (void)state;
    pid_t pid = fork();
    assert_true(pid >= 0);
    if (pid == 0) {
        if (os_no_dump() != OS_OK) _exit(98);
        if (prctl(PR_GET_DUMPABLE) != 0) _exit(70);
        struct rlimit rl;
        if (getrlimit(RLIMIT_CORE, &rl) != 0) _exit(71);
        _exit(rl.rlim_cur == 0 ? 42 : 72);
    }
    int st = 0;
    assert_int_equal(waitpid(pid, &st, 0), pid);
    assert_true(WIFEXITED(st));
    assert_int_equal(WEXITSTATUS(st), 42);
}

/* --- Landlock filesystem confinement --- */

static void test_landlock_abi_present(void **state) {
    (void)state;
    assert_true(os_landlock_abi() > 0); /* this host supports Landlock */
}

/* deny-all: after restricting with no rules, opening any file must fail EACCES. */
static void test_landlock_deny_all(void **state) {
    (void)state;
    pid_t pid = fork();
    assert_true(pid >= 0);
    if (pid == 0) {
        if (os_landlock_restrict(NULL, 0) != OS_OK) _exit(98);
        int fd = open("/etc/hostname", O_RDONLY);
        if (fd >= 0) { close(fd); _exit(50); } /* should not be reachable */
        _exit(errno == EACCES ? 51 : 52);
    }
    int st = 0;
    assert_int_equal(waitpid(pid, &st, 0), pid);
    assert_true(WIFEXITED(st));
    assert_int_equal(WEXITSTATUS(st), 51);
}

/* allow-read: a read rule on a temp dir lets reads inside through and blocks
 * everything else. */
static void test_landlock_allow_read(void **state) {
    (void)state;
    char dir[] = "/tmp/freedom_ll_XXXXXX";
    assert_non_null(mkdtemp(dir));
    char file[64];
    snprintf(file, sizeof file, "%s/f", dir);
    int wfd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    assert_true(wfd >= 0);
    assert_int_equal(write(wfd, "ok", 2), 2);
    close(wfd);

    pid_t pid = fork();
    assert_true(pid >= 0);
    if (pid == 0) {
        os_fs_rule rules[] = { { dir, OS_FS_READ } };
        if (os_landlock_restrict(rules, 1) != OS_OK) _exit(98);
        int in = open(file, O_RDONLY);          /* inside the rule: allowed */
        if (in < 0) _exit(60);
        close(in);
        int out = open("/etc/hostname", O_RDONLY); /* outside: denied */
        if (out >= 0) { close(out); _exit(61); }
        _exit(errno == EACCES ? 62 : 63);
    }
    int st = 0;
    assert_int_equal(waitpid(pid, &st, 0), pid);

    unlink(file);
    rmdir(dir);

    assert_true(WIFEXITED(st));
    assert_int_equal(WEXITSTATUS(st), 62);
}

/* --- namespace isolation --- */

/* The pure flag set: the worker requests an isolated network (no remote access),
 * a user namespace (the unprivileged enabler), and IPC + UTS isolation. */
static void test_namespace_flags(void **state) {
    (void)state;
    int f = os_namespace_flags();
    assert_true((f & CLONE_NEWNET) != 0);   /* no network: the worker never fetches */
    assert_true((f & CLONE_NEWUSER) != 0);  /* enables the rest unprivileged */
    assert_true((f & CLONE_NEWIPC) != 0);
    assert_true((f & CLONE_NEWUTS) != 0);
}

/* The net-namespace inode of a process. Returns 0 on failure. */
static unsigned long net_ns_inode(void) {
    struct stat sb;
    if (stat("/proc/self/ns/net", &sb) != 0) return 0UL;
    return (unsigned long)sb.st_ino;
}

/* Enforcement (fork-based, like os_harden): the child detaches and must land in a
 * DIFFERENT network namespace than the parent. Where unprivileged user namespaces
 * are disabled the child reports a skip; both outcomes are acceptable for the
 * suite (it is best-effort defense in depth), and on a host that allows them the
 * isolation must actually take effect. */
static void test_namespace_isolate_changes_netns(void **state) {
    (void)state;
    unsigned long parent_ns = net_ns_inode();
    pid_t pid = fork();
    assert_int_not_equal(pid, -1);
    if (pid == 0) {
        os_status rc = os_isolate_namespaces();
        if (rc == OS_ERR_UNSUPPORTED) _exit(80);       /* userns disabled: skip */
        if (rc != OS_OK) _exit(44);                    /* unexpected failure */
        unsigned long child_ns = net_ns_inode();
        if (child_ns == 0UL || parent_ns == 0UL) _exit(45);
        _exit(child_ns != parent_ns ? 42 : 43);        /* 42: isolated */
    }
    int st = 0;
    assert_int_equal(waitpid(pid, &st, 0), pid);
    assert_true(WIFEXITED(st));
    int code = WEXITSTATUS(st);
    assert_true(code == 42 || code == 80); /* isolated, or skipped on a locked host */
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_policy_allows_safe),
        cmocka_unit_test(test_policy_denies_dangerous),
        cmocka_unit_test(test_policy_size),
        cmocka_unit_test(test_harden_kills_denied_syscall),
        cmocka_unit_test(test_harden_allows_permitted_syscall),
        cmocka_unit_test(test_harden_errno_denies_with_eperm),
        cmocka_unit_test(test_prot_allowed_wx),
        cmocka_unit_test(test_harden_blocks_exec_mmap),
        cmocka_unit_test(test_harden_blocks_exec_mprotect),
        cmocka_unit_test(test_no_dump_undumpable),
        cmocka_unit_test(test_landlock_abi_present),
        cmocka_unit_test(test_landlock_deny_all),
        cmocka_unit_test(test_landlock_allow_read),
        cmocka_unit_test(test_namespace_flags),
        cmocka_unit_test(test_namespace_isolate_changes_netns),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
