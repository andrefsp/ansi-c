#include <sys/socket.h> 
#include <netinet/in.h> 
#include <unistd.h>


#ifndef SERVER_H
#define SERVER_H

typedef struct Server Server;

struct Server {
    int port;
   
    int socket_fd;
    struct sockaddr_in *address;

    int (*Start)(Server *s);
    int (*Stop)(Server *s);
    int (*Listen)(Server *s);
};

int Start(Server *s);

int Stop(Server *s);

int Listen(Server *s);

// Constructor
Server *NewServer(int port);

#endif
