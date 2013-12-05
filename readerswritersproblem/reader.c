#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRT 1

int main()
{
    int id, shmid, retval;
    struct sembuf operations[2];
    char *shared;

    id = semget(0xABC, 2, 0666);
    if(id < 0)
    {
       perror("Could not create semaphore, exiting.");
       exit(1);
    }
    shmid = shmget(0xABC, 1, 0);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    shared = shmat(shmid, 0, 0);
    if ((int)shared == -1) {
        perror("shmat");
        exit(1);
    }

    while (1) {

        operations[0].sem_num = WRT;
        operations[0].sem_op = -1;
        operations[0].sem_flg = SEM_UNDO;
        retval = semop(id, operations, 1);
        if (retval != 0) {
            perror("semop");
            exit(1);
        }
        operations[0].sem_num = WRT;
        operations[0].sem_op = 1;
        operations[0].sem_flg = SEM_UNDO;
        operations[1].sem_num = READ;
        operations[1].sem_op = 1;
        operations[1].sem_flg = SEM_UNDO;

        retval = semop(id, operations, 2);
        if (retval != 0) {
            perror("semop");
            exit(1);
        }
        printf("Read '%c' sleeping\n", *shared);
        sleep(2);
        operations[0].sem_num = READ;
        operations[0].sem_op = -1;
        operations[0].sem_flg = SEM_UNDO;
        retval = semop(id, operations, 1);
        if (retval != 0) {
            perror("semop");
            exit(1);
        }
        sleep(5);
    }
}

