#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>



const size_t BUFF_SIZE = 1024;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Missing label, exit");
        exit(1);
    }
    char *label = argv[1];
    fd_set rfds;
    struct timeval tv;
    int retval, len;
    char buff[BUFF_SIZE] = {0};

    /* Wait up to five seconds. */
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    while (1)
    {
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        retval = select(1, &rfds, NULL, NULL, &tv);
        if (retval == -1)
        {
            printf("%s, error at select, %s", label, strerror(errno));
            exit(EXIT_FAILURE);
        }
        else if (retval)
        {
            ssize_t readBytes = read(STDIN_FILENO, buff, BUFF_SIZE);
            len = readBytes - 1;
            if (buff[len] == '\n')
            {
                buff[len] = '\0';
            }
            printf("%s: '%s'\n", label, buff);
        }
        else
        {
            printf("%s: no data within five seconds.\n", label);
        }
    }
    return 0;
}
