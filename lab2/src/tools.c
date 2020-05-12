#include "tools.h"


void printProcessInfo(struct processInfo *s) {
    printf("pid %i\n", s->pid);
    printf("ppid %i\n", s->ppid);
    printf("gid %i\n", s->gid);
    printf("egid %i\n", s->egid);
    printf("sid %i\n", s->sid);
    printf("uid %i\n", s->uid);
    printf("euid %i\n", s->euid);
}

void fprintProcessInfo(FILE *file, struct processInfo *s) {
    fprintf(file, "pid %i\n", s->pid);
    fprintf(file, "ppid %i\n", s->ppid);
    fprintf(file, "gid %i\n", s->gid);
    fprintf(file, "egid %i\n", s->egid);
    fprintf(file, "sid %i\n", s->sid);
    fprintf(file, "uid %i\n", s->uid);
    fprintf(file, "euid %i\n", s->euid);
}

struct processInfo getProcessInfo() {
    struct processInfo info;
    info.pid = getpid();
    info.ppid = getppid();
    info.gid = getgid();
    info.egid = getegid();
    info.sid = getsid(0);
    info.uid = getuid();
    info.euid = geteuid();
    return info;
}
