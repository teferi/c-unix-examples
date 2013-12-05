#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define READ 0
#define WRT 1


int main()
{
    int id;

    union semun {
        int val;
        struct semid_ds *buf;
        ushort * array;
    } argument;

    argument.val = 0;

    id = semget(0xABC, 2, 0666 | IPC_CREAT);

    if(id < 0) {
        perror("Unable to obtain semaphore.");
        exit(1);
    }

    if( semctl(id, READ, SETVAL, argument) < 0) {
        perror("Cannot set semaphore value.");
        exit(1);
    }
    argument.val = 1;
    if( semctl(id, WRT, SETVAL, argument) < 0) {
        perror("Cannot set semaphore value.");
        exit(1);
    }

    if (shmget(0xABC, 1, 0666 | IPC_CREAT) < 0) {
        perror("shmget");
        exit(1);
    }
    return 0;
}
