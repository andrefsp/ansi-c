#ifndef _HELLO_SERVER_H
#define _HELLO_SERVER_H

#include <sys/socket.h> 
#include <netinet/in.h> 
#include <unistd.h>
#include "uv.h"


uv_tcp_t *Server_uv_server;
uv_loop_t *Server_uv_loop;


typedef struct Server Server;

struct Server {
    int port;
    struct sockaddr_in *address;

    int (*Start)(Server *s, int block);
    int (*Stop)(Server *s);
    void (*Listen)(void *s);
};

int Server_Start(Server *s, int block);

int Server_Stop(Server *s);

void Server_Listen(void *s);

// Constructor
Server *NewServer(int port);

#endif
