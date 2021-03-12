#include <assert.h>
#include "../src/hello.c"


void test_server_star_stop(void) {
    Server *s = NewServer(9100);
    assert(s != NULL);
    assert(((void)"port is set", s->port == 9100));
    assert(((void)"run server", s->Start(s) == 0));
    assert(((void)"stop server", s->Stop(s) == 0));
}

void test_server_star_listen(void) {
    Server *s = NewServer(9200);
    assert(s != NULL);
    
    assert(((void)"run server", s->Start(s) == 0));
    //assert(((void)"listen server", s->Listen(s) == 0));
    assert(((void)"stop server", s->Stop(s) == 0));
}


void test_server(void) {
    test_server_star_stop();
    test_server_star_listen();
}
