#include <stdio.h>
#include <assert.h>
#include "gc.h"
#include <dlfcn.h>
#include "kore/kore.h"
#include "../src/point.c"
#include "../src/server.c"

void test_point(void) {
    Point *p1 = NewPoint(10, 11);
    Point *p2 = NewPoint(9, 8);
    assert(("distance", *(p1->Dist(p1, p2)) == 4.0));
}

void test_server(void) {
    Server *s = NewServer();
    assert(s != NULL);
    assert(("run server", s->Start(s) == 0));
}

/*
void test_kore_module(void) {
    const char* error_message = NULL;

    void* handle = NULL;
    handle = dlopen("/home/andrefsp/development/ansi-c/hello/hello.so", RTLD_LAZY);
    assert(handle != NULL);
    dlerror();

    static void         ( *run_server )(int argc, char *argv[]);

    run_server = dlsym(handle, "kore_server_start");
    
    error_message = dlerror();
    if (error_message) {
        printf("%s \n", error_message);
    }

}
*/

int main(void) {
    GC_INIT();

    test_point();
    test_server();
//    test_kore_module();
    return 0;
}
