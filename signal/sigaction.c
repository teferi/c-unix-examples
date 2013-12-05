#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

// handler function. see man page for argument type info
static void hdl(int sig, siginfo_t *siginfo, void *context)
{
    printf("Sending PID: %ld, UID: %ld\n",
            (long)siginfo->si_pid, (long)siginfo->si_uid);
}

int main (int argc, char *argv[])
{
    struct sigaction act, act_old;
    int dummy;

    memset (&act, '\0', sizeof(act));

    // Use the sa_sigaction field because it handles has additional parameters
    // We could have used exactly the same handler as in signal.c if we used sa_handler.
    act.sa_sigaction = &hdl;

    /// The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not sa_handler.
    act.sa_flags = SA_SIGINFO;

    // let's call sigaction. see man page for prototype
    // here we set a new handler and gather previous handler
    if (sigaction(SIGHUP, &act, &act_old) < 0) {
        printf("sigaction failed\n");
        return 1;
    }

    // Check that it was default
    if (act_old.sa_handler == SIG_DFL){
            printf("Default action was set\n");
    }

    // do exactly the same to find new sa_sigaction where SIG_DFL was
    if (sigaction(SIGHUP, &act, &act_old) < 0) {
        printf("sigaction failed\n");
        return 1;
    }

    if (act_old.sa_sigaction == act.sa_sigaction){
            printf("Found new handler\n");
    }

    printf("my pid is %d.\n", getpid());
    scanf("%d", &dummy); // this is here purely to wait for some user input and halt the program
    printf("Exiting.\n");
    return 0;
}
