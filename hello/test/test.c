// Test includes files
#include "point.c"
#include "server.c"
#include "request.c"
#include "response.c"
#include "hashmap.c"


int main(void) {
    GC_INIT();

    test_hashmap();
    test_point();

    test_server();    
    test_request();
    test_response();
    return 0;
}
