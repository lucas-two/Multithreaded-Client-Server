/* CLIENT */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MAX 100
#define CLEARSCREEN "\e[1;1H\e[2J"

int main()
{  
    const char * name = "shared_memory";
    int shm_fd; //file descriptor of
    int * shelf;
    
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd,sizeof(int));
    shelf = mmap(0,sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf(CLEARSCREEN);
    printf("- - CLIENT started up - -\n");
    
    int queryNo = 1;

    // Application
    while(1) {

        char request[MAX]; // What we ask the server
        int inputNumber; // Number we will factorize

        printf("[%d] Enter Query: ", queryNo);
        gets(request);

        // Exit if quit is called.
        if(strcmp(request, "quit") == 0) {
            break;
        }

        else {
            inputNumber = atoi(request);
            printf("[%d] Query Response: %d\n", queryNo, inputNumber);
            queryNo++;
            // pass back to server.
        }
    }

    // Close and unlink shared memory
    munmap(shelf, sizeof(int));
    close(shm_fd);
    shm_unlink(name);

    return 0;
}