// SERVER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PORT 80
#define SMALL 10
#define MAX 1024
#define LINES 40

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include<sys/utsname.h>
#include <dirent.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>
#include <dirent.h>
#endif

int main(int argc, char *argv[]) {

    /* Create the server socket */
    int serverSocket;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    /* Specifying an address */
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    /* Binding socket to our specific IP and Port */
    bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

    /* Listen for connections */
    listen(serverSocket, 5);

    /* Accepting connection to client */
    int clientSocket;
    clientSocket = accept(serverSocket, NULL, NULL); // These are null since only looking at local machine

    while(1) {
        // Keep running here!
        return; // Temp to avoid infi loop
    }
    /* Close the socket */
    close(serverSocket);

    return 0;
}