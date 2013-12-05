#include <fcntl.h>
#include <stdio.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>


#define PIPE_NAME "foo"

extern int errno;

int main() {
    int fd, count, ok;
    char buf[256] = "Hello fifo";

    // let's check that file exists first
    if (access(PIPE_NAME, F_OK) != 0) {
        printf("No pipe found. Will create one\n");
        mkfifo(PIPE_NAME, 0660);
    }

    //fd = open(PIPE_NAME, O_WRONLY);
    //fd = open(PIPE_NAME, O_WRONLY|O_NONBLOCK);
    printf("About to open pipe\n");
    fd = open(PIPE_NAME, O_WRONLY);
    if (fd == -1) {
        if (errno == ENOENT) {
            printf("Couldn't open file as it doesn't exist\n");
        } else {
            printf("Errno: %d \n", errno);
            perror("Error while opening pipe");
            return 1;
        }
    }
    printf("About to write to pipe, fd: %d\n", fd);
    count = write(fd, buf, 10);
    printf("Wrote %d bytes to pipe\n", count);
    return 0;
}
