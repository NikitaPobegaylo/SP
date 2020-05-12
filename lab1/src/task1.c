#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>



const size_t BUFFER_SIZE = 512;
const int NEW_FILE_ATTR = 0644;

struct openFiles
{
    int ifd;
    int ofd;
};

int getFDs(char *ifn, char *ofn, struct openFiles *fds)
{
    fds->ifd = open(ifn, O_RDONLY);
    if (fds->ifd == -1)
    {
        printf("Unable to open input file %s because catch an err %s\n", ifn, strerror(errno));
        return -1;
    }
    fds->ofd = open(ofn, O_CREAT | O_WRONLY | O_APPEND, NEW_FILE_ATTR);
    if (fds->ofd == -1)
    {
        printf("Unable to open/create output file %s,  because catch an err %s\n", ofn, strerror(errno));
        close(fds->ifd);
        return -1;
    }
    return 0;
}

ssize_t processBuffer(char *buff, ssize_t size)
{
    ssize_t changedBytes = 0;
    for (ssize_t i = 0; i <= size; i++)
    {
        if (buff[i] >= 'a' && buff[i] <= 'z')
        {
            buff[i] -= 32;
            changedBytes++;
        }
    }
    return changedBytes;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Missing filenames, exit");
        exit(1);
    }
    char *filenameForRead = argv[1];
    char *filenameForWrite = argv[2];
    struct openFiles openFiles = {};
    printf("Read from %s, write to %s\n", filenameForRead, filenameForWrite);
    if (getFDs(filenameForRead, filenameForWrite, &openFiles) != 0)
    {
        exit(1);
    }
    char buff[BUFFER_SIZE + 1];
    ssize_t bytesRead = 0;
    ssize_t totalRead = 0;
    ssize_t changedBytes = 0;
    do
    {
        bytesRead = read(openFiles.ifd, buff, BUFFER_SIZE);
        totalRead += bytesRead;
        changedBytes += processBuffer(buff, BUFFER_SIZE);
        write(openFiles.ofd, buff, BUFFER_SIZE);
    } while (bytesRead == BUFFER_SIZE);
    printf("Total read %li bytes\n", totalRead);
    printf("Changed %li bytes\n", changedBytes);
    fsync(openFiles.ofd);
    close(openFiles.ofd);
    close(openFiles.ifd);
    return 0;
}
