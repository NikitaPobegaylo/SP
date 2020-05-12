#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include "tools.h"


struct tm *getDate() {
    time_t rawtime;
    time(&rawtime);
    return localtime(&rawtime);
}


int main(int argc, char **argv) {
    FILE *logFile = fopen("./log.txt", "w");

    fprintf(logFile, "program started %s\n", asctime(getDate()));
    fflush(logFile);
    pid_t childPid = fork();
    if (childPid < 0) {
//        error
        fprintf(stderr, "Error while forking\n");
        exit(EXIT_FAILURE);
    } else if (childPid > 0) {
//        parent
        fprintf(logFile, "create child with PID %i\n", childPid);
        exit(EXIT_SUCCESS);
    } else {
//         child
        pid_t sid = setsid();
        if (sid < 0) {
            fprintf(stderr, "Error while set sid\n");
            exit(EXIT_FAILURE);
        }
        printf("Create new session %i\n", sid);
        if (chdir("/") < 0) {
            fprintf(stderr, "Error while chdir to \"/\"\n");
            exit(EXIT_FAILURE);
        }
        int fdMax = getdtablesize();
        for (int i = 0; i < fdMax; i++) {
            close(i);
        }
        freopen("/dev/null", "r", stdin);
        freopen("/dev/null", "w", stdout);
        freopen("/dev/null", "w", stderr);

        struct processInfo info = getProcessInfo();
        FILE *newLogFile = fopen("./log.txt", "a+t");
        fprintProcessInfo(stdout, &info);
        fprintProcessInfo(newLogFile, &info);
        fflush(newLogFile);
        while (1) {
            sleep(1);
            fprintf(newLogFile, "Lorem ipsum...\n");
            fflush(newLogFile);
        }
        fflush(newLogFile);
        fclose(newLogFile);
        exit(EXIT_SUCCESS);
    }
}
