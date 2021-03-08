#include <assert.h>
#include "../src/hello.c"


void test_server_star_stop(void) {
    Server *s = NewServer(9100);
    assert(s != NULL);
    assert(("port is set", s->port == 9100));
    assert(("run server", s->Start(s) == 0));
    assert(("stop server", s->Stop(s) == 0));
}

void test_server_star_listen(void) {
    Server *s = NewServer(9200);
    assert(s != NULL);
    
    assert(("run server", s->Start(s) == 0));
    //assert(("listen server", s->Listen(s) == 0));
    assert(("stop server", s->Stop(s) == 0));
}


void test_server(void) {
    test_server_star_stop();
    test_server_star_listen();
}
