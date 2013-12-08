#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MSGSIZE 2

int main()
{
    int msgid, result;
    struct _msgbuf {
        long mtype;
        char mtext[MSGSIZE];
    } msgbuf;

    msgid = msgget(0xABC, 0666);
    if (msgid == -1) {
        perror("Couldn't find msg queue:");
        return 1;
    }

    /*
     * ssize_t
     * msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
     *
     * */

    printf("About to get message \n");

    result = msgrcv(msgid, &msgbuf, MSGSIZE, 1, 0);
    if (result == -1) {
        perror("Couldn't send a message:");
        return 1;
    }
    printf("Got message %c%c\n", msgbuf.mtext[0], msgbuf.mtext[1]);
    return 0;
}


