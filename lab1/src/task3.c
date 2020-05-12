#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
  
const size_t BUFF_SIZE = 1024;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Missing label, exit");
        exit(1);
    }
    char *label = argv[1];
    struct pollfd fds[1];
    int retval, len;
    char buff[BUFF_SIZE] = {0};

    while (1)
    {
        fds[0].fd = STDIN_FILENO;
        fds[0].events = POLLIN;
        retval = poll(fds, 1, 2000);
        if (retval == -1)
        {
            printf("%s, error at select, %s", label, strerror(errno));
            exit(EXIT_FAILURE);
        }
        else if (retval)
        {
            ssize_t readBytes=read(STDIN_FILENO, buff, BUFF_SIZE);

            /* Remove trailing newline character from the input buffer if needed. */
            len = readBytes-1;
            if (buff[len] == '\n')
                buff[len] = '\0';

            printf("%s: '%s'\n", label, buff);
        }
        else
        {
            printf("%s: no data within five seconds.\n", label);
        }
    }
    return 0;
}
