#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "tools.h"


void processChild() {
    printf("In child process:\n");
    struct processInfo childInfo = getProcessInfo();
    printProcessInfo(&childInfo);
    printf("Child process ended\n");
    exit(EXIT_SUCCESS);
}

int main() {
    pid_t childPid = fork();
    if (childPid == 0) {
        processChild();
    } else {
        printf("In parent process\n");
        struct processInfo parentInfo = getProcessInfo();
        printProcessInfo(&parentInfo);
        printf("child process pid: %i\n", childPid);
        wait(NULL);
        printf("Parent process ended\n");
        exit(EXIT_SUCCESS);
    }

}
