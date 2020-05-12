#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>


struct processInfo {
    pid_t pid;
    pid_t ppid;
    gid_t gid;
    gid_t egid;
    pid_t sid;
    uid_t uid;
    uid_t euid;
};

void printProcessInfo(struct processInfo *s);

void fprintProcessInfo(FILE * file, struct processInfo *s);

struct processInfo getProcessInfo();
