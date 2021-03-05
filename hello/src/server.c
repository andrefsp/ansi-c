#include "gc.h"
#include "server.h"


int Stop(Server *s) {
    return 0;
}

int Start(Server *s) {    
    return 0;
}

Server *NewServer() {
    Server *s = GC_MALLOC(sizeof(Server));
    s->Start = Start;
    s->Stop = Stop;
    return s;
}
