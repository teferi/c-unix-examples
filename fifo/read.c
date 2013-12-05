#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


int main() {
    int fd, count;
    char buf[256];
    printf("About to open pipe \n");
    fd = open("foo", O_RDONLY);
    printf("Opened pipe. fd: %d\n", fd);
    count = read(fd, buf, 256);
    printf("Read %d bytes from pipe\n", count);
    buf[count] = 0;
    printf("Read from pipe %s\n", buf);
    return 0;
}
