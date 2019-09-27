// server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHSIZE 100

int main(int argv, char *argv[]){

    int shmid;
    key_t key;
    char *shm;
    char *s

    key = 9876;
    shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);

    shm = shmat(shmid, NULL, 0);
    
    memcyp(shm, "Hello World", 11); //11 characters

    s = shm;
    s += 11;

    *s = 0;

    while(*shm != '*')
        sleep(1);

    return 0;
}