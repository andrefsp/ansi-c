#include <libwebsockets.h>

#ifndef SERVER_H
#define SERVER_H

typedef struct Server Server;

struct Server {
    struct lws_context_creation_info *info;

    int (*Start)(Server *s);
    int (*Stop)(Server *s);
};

int Start(Server *s);

int Stop(Server *s);

// Constructor
Server *NewServer();

#endif
