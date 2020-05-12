#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/errno.h>


struct datum {
    pid_t pid;
    struct tm current_timestamp;
    char str_buff[256];
};

const char *SHM_NAME = "lab3.2";
typedef struct datum datum_t;

int main(void) {
    int fd;
    char str_buff[256];
    datum_t *datum = NULL;
    time_t rawtime;

    /* Create shared memory object */
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (fd == -1) {
        perror("shm_open");
        return -1;
    }

    /* Set shared memory size */
    if (ftruncate(fd, sizeof(struct datum)) != 0) {
        perror("ftruncate");
        printf("Error code: %d\n", errno);
        return -1;
    }

    /* Map shared memory object */
    datum = mmap(NULL, sizeof(struct datum), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (datum == MAP_FAILED) {
        perror("mmap");
        return -1;
    }

    while (1) {
        printf("Wait for input:\n");
        /* 1. Read string from input to str_buff */
        fgets(str_buff, 256, stdin);
        /* 2. Read datum info */
        msync(datum, sizeof(struct datum), MS_SYNC);
        printf("data in datum:\n");
        printf("pid: %d\n", datum->pid);
        printf("time %s\n", asctime(&(datum->current_timestamp)));
        printf("string %s\n", datum->str_buff);

        /* 3. Write to datum */
        datum->pid = getpid();
        time(&rawtime);
        datum->current_timestamp = (*localtime(&rawtime));
        strcpy(datum->str_buff, str_buff);
    }

    /* clear */
//    munmap(datum, sizeof(struct datum));
//    shm_unlink(SHM_NAME);
//    return 0;
}
