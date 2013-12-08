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
    * int
    * msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
    * */

    srandom(time(NULL));

    msgbuf.mtype = 1;
    msgbuf.mtext[0] = (char)(random()%26 + 65);
    msgbuf.mtext[1] = (char)(random()%10 + 48);

    printf("About to send message %c%c\n", msgbuf.mtext[0], msgbuf.mtext[1]);

    result = msgsnd(msgid, &msgbuf, sizeof(msgbuf.mtext), 0);

    if (result == -1) {
        perror("Couldn't send a message:");
        return 1;
    }
    return 0;
}

