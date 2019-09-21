// CLIENT
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define PORT 80
#define SMALL 10
#define MAX 1024
#define LINES 40
#define CLEARSCREEN "\e[1;1H\e[2J"

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#endif

int main(int argc, char *argv[]) {

    printf(CLEARSCREEN);

    char *serverIP;
    serverIP = argv[1];

    /* Create a socket*/
    int clientSocket;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    /* Specifying an address to connect to */
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_aton(serverIP, &serverAddress.sin_addr.s_addr);

    /* Connecting to the socket */
    int connectionStatus = connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

    //Checking if there was an error with connection
    if(connectionStatus == -1){
        printf("Error making connection");
    }

    while(1) {
        // Keep running here!
        return; // Temp to avoid infi loop

    }
    /* Close the socket */
    close(clientSocket);
    return 0;
}