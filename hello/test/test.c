#include <stdio.h>
#include <assert.h>
#include "../src/point.c"
#include "../src/server.c"

void test_point(void) {
    Point *p1 = NewPoint(10, 11);
    Point *p2 = NewPoint(9, 8);
    assert(("distance", *(p1->Dist(p1, p2)) == 4.0));
}

void test_server_star_stop(void) {
    Server *s = NewServer(9100);
    assert(s != NULL);
    assert(("port is set", s->port == 9100));
    assert(("run server", s->Start(s) == 0));
    assert(("stop server", s->Stop(s) == 0));
}

void test_server_star_listen(void) {
    Server *s = NewServer(9100);
    assert(s != NULL);
    
    assert(("run server", s->Start(s) == 0));
    assert(("listen server", s->Listen(s) == 0));
}


int main(void) {
    GC_INIT();

    test_point();
    test_server_star_stop();
    test_server_star_listen();

    return 0;
}
