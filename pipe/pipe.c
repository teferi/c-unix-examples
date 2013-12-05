#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    pid_t pid;  // pid_t may be int, but let's be cool and use correct type
    int fd[2], w;

    // create a pipe. fd[1] is for writing, fd[0] is for reading
    pipe(fd);

    // fork and exec the child into ls
    pid=fork();
    if (pid==0) {

        printf("i'm the child used for ls \n");
        // STDOUT_FILENO is 1 but using constant is more readable
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        execlp("ls", "ls", "-la", NULL);
    }

    // fork and exec the child into grep
    pid=fork();
    if (pid==0) {
        printf("i'm in the second child, which will be used to run grep\n");
        // STDIN_FILENO is 0 but using constant is more readable
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        execlp("grep", "grep", ".c", NULL);
    }

    wait(&w);  // wait for our processes to stop
    return 0;
}
