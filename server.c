/* SERVER */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define THREADSIZE 32

void factorize(void *ptr);
int *createNumberList(int num);

/* main */
int main() {

    // Variables for shared memory
    const char * name = "shared_memory";
    int shm_fd;
    int * shelf;

    // Creating shared memory
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd,sizeof(int));
    shelf = mmap(0,sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // User input
    // ==========================================
    int *numberList = createNumberList(123);
    


    // ==========================================
    pthread_t threads[THREADSIZE];

    // Create threads
    for(int i = 0; i < THREADSIZE; i++) {
        pthread_create(&threads[i], NULL, (void *) &factorize, &numberList[i]);
    }

    // Join threads
    for(int i = 0; i < THREADSIZE; i++) {
         pthread_join(threads[i], NULL);
    }

    // Close and unlink shared memory
    munmap(shelf, sizeof(int));
    close(shm_fd);
    shm_unlink(name);

    return 0;
}

/* Perform trial by division factorisation*/
void factorize(void *ptr) {

    int *num = (int *) ptr;
    int factor = 2; // Base factor

    while(*num > 1) {

        // If it was a factor of the number
        if(*num % factor == 0) {
            printf("%d\n", factor); // Append factor to a list
            *num = *num / factor; // Divide the factor from number
        }

        // If it was not a factor
        else {
            factor++; // Check next factor
        }
    }

    pthread_exit(0); // Exit thread
}


/* Create a set of 32 numbers */
int * createNumberList(int num) {

    static int numList[THREADSIZE];

    for(int i = 0; i < THREADSIZE; i++) {
        num = num >> 1; // Rightwards bit rotation
        numList[i] = num; // Append number to array
    }

    return numList;
}