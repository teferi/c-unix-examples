#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main()
{
    int msgid;
    msgid = msgget(0xABC, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Couldn't create msg queue:");
    }
    return 0;
}
