#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void catch_function(int signal) {
    printf("I cought a signal. It's number is %d\n", signal);
}

static void exit_function(int signal) {
    printf("I cought a signal. It's number is %d\n", signal);
    printf("Will exit now\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    int dummy;
    //pointer to a function, not necessary at all
    void (*handler_func)(int) = catch_function;

    // setting a handler
    if (signal(SIGHUP, handler_func) == SIG_ERR) {
        printf("An error occurred while setting a signal handler.\n");
        return EXIT_FAILURE;
    }

    // Ctrl + c sends SIGINT, lets cathc it
    if (signal(SIGINT, exit_function) == SIG_ERR) {
        printf("An error occurred while setting a signal handler.\n");
        return EXIT_FAILURE;
    }

    // setting signal to be ignored
    if (signal(SIGUSR1, SIG_IGN) == SIG_ERR) {
        printf("An error occurred while setting a signal handler.\n");
        return EXIT_FAILURE;
    }

    // resetting default behaviour
    if (signal(SIGUSR2, SIG_DFL) == SIG_ERR) {
        printf("An error occurred while setting a signal handler.\n");
        return EXIT_FAILURE;
    }

    // printing pid, so that we will be able to kill -X this process
    printf("my pid is %d.\n", getpid());

    // if you want to send a signal to yourself: uncomment the next section
    /*
    if (raise(SIGHUP) != 0) {
        printf("Error raising the signal.\n");
        return -1;
    }
    */
    scanf("%d", &dummy); // this is here purely to wait for some user input and halt the program
    printf("Exiting.\n");
    return 0;
}
