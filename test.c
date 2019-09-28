#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREADSIZE 32
#define MAX 100

int foo(int num);

/* main */
int main()
{       
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
            foo(inputNumber);
        }
    }

    return 0;
}

int foo(int num) {
    int pid = fork();

    if(pid == 0) {
        printf("%d\n", num);
    }
}