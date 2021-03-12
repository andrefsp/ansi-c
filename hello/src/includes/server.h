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
