#include <stdio.h>
#include <assert.h>
#include "../src/point.c"
#include "./server.c"
#include "./request.c"


void test_point(void) {
    Point *p1 = NewPoint(10, 11);
    Point *p2 = NewPoint(9, 8);
    assert(("distance", *(p1->Dist(p1, p2)) == 4.0));
}


int main(void) {
    GC_INIT();

    test_point();

    test_server();    
    test_request();

    return 0;
}
