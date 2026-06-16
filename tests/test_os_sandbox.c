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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
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

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_policy_allows_safe),
        cmocka_unit_test(test_policy_denies_dangerous),
        cmocka_unit_test(test_policy_size),
        cmocka_unit_test(test_harden_kills_denied_syscall),
        cmocka_unit_test(test_harden_allows_permitted_syscall),
        cmocka_unit_test(test_harden_errno_denies_with_eperm),
        cmocka_unit_test(test_landlock_abi_present),
        cmocka_unit_test(test_landlock_deny_all),
        cmocka_unit_test(test_landlock_allow_read),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
