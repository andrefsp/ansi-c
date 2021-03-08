#ifndef _HELLO_SERVER_H
#define _HELLO_SERVER_H

#include <sys/socket.h> 
#include <netinet/in.h> 
#include <unistd.h>


typedef struct Server Server;

struct Server {
    int port;
   
    int socket_fd;
    struct sockaddr_in *address;

    int (*Start)(Server *s);
    int (*Stop)(Server *s);
    int (*Listen)(Server *s);
};

int Server_Start(Server *s);

int Server_Stop(Server *s);

int Server_Listen(Server *s);

// Constructor
Server *NewServer(int port);

#endif
