#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREADSIZE 32

void factorize(void *ptr);
int * createNumberList(int num);

/* main */
int main()
{   
    int *numberList = createNumberList(24);

    pthread_t threads[THREADSIZE];

    for(int i = 0; i < THREADSIZE; i++) {
        pthread_create(&threads[i], NULL, (void *) &factorize, &numberList[i]);
    }

    for(int i = 0; i < THREADSIZE; i++) {
         pthread_join(threads[i], NULL);
    }

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

        // If it was not
        else {
            factor++;
        }
    }

    pthread_exit(0); // Leave thread
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