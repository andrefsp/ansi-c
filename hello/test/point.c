#include <assert.h>
#include "../src/hello.c"


void test_point(void) {
    Point *p1 = NewPoint(10, 11);
    Point *p2 = NewPoint(9, 8);
    assert(((void)"distance", *(p1->Dist(p1, p2)) == 4.0));
}
