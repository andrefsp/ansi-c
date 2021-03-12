// Test includes files
#include "point.c"
#include "server.c"
#include "request.c"
#include "response.c"
#include "hashmap.c"
#include "string_utils.c"
#include "http_client.c"
#include "closure.c"


int main(void) {
    test_hashmap();
    test_string_utils();
    test_point();

    test_server();
    test_response();

    test_request();

    test_http_client();

    test_closure();
    return 0;
}
