#ifndef _HELLO_SERVER_C
#define _HELLO_SERVER_C

#include "gc.h"
#include "server.h"


int Server_Stop(Server *s) {
    shutdown(s->socket_fd, SHUT_RDWR);
    close(s->socket_fd);
    return 0;
}

int Server_Start(Server *s) {
    int opt = 1;

	s->socket_fd = socket(AF_INET , SOCK_STREAM , 0);
    if (s->socket_fd == -1) {
        return s->socket_fd;
    }
   
    s->address = GC_MALLOC(sizeof(*(s->address)));
    s->address->sin_family = AF_INET;
    s->address->sin_addr.s_addr = INADDR_ANY;
    s->address->sin_port = htons(s->port);
 
    int bindR = bind(
        s->socket_fd, (struct sockaddr *)s->address, sizeof(*(s->address))
    );
    if (bindR < 0) {
        return bindR;
    } 
   
    int lRes = listen(s->socket_fd, 300);
    if (lRes < 0) { 
        return lRes;
    } 

    return 0;
}

int listenLoop(Server *s) {
    
}

int Server_Listen(Server *s) {
    char buffer[1024] = {0};

    int addrlen = sizeof(*(s->address)); 
    while (1) {
        int socket = accept(
            s->socket_fd, (struct sockaddr *)s->address, (socklen_t*)&addrlen
        );
        if (socket < 0) {
            return -1;
        }
        int valread = read(socket , buffer, 1024);
        printf("%s\n", buffer);

        char *message = "HTTP/1.1 200 OK\r\n";
        if (send(socket, message, strlen(message), 0) < 0) {
            printf("Failed to send!");
        }
        close(socket);
    }
    return 0;
}

Server *NewServer(int port) {
    Server *s = GC_MALLOC(sizeof(Server));
    s->port = port;
    s->Start = Server_Start;
    s->Stop = Server_Stop;
    s->Listen = Server_Listen;
    return s;
}

#endif
