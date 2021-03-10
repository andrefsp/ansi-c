// Test includes files
#include "point.c"
#include "server.c"
#include "request.c"
#include "response.c"
#include "hashmap.c"
#include "string_utils.c"

int main(void) {
    test_hashmap();
    test_string_utils();
    test_point();

    test_server();
    test_response();

    test_request(); // Currently failing!
    return 0;
}
