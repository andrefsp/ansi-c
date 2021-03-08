#include <assert.h>
#include "../src/hello.c"


void test_new_request(void) {
    char *url = "http://localhost:7777";
    Request *req = NewRequest("GET", url);
 
    assert(("url", strcmp(req->url, url) == 0));
    assert(("method", strcmp(req->method, "GET") == 0));

    req->SetTimeout(req, 2);
    req->SetHeader(req, "Authorization", "Bearer sometoken");
    req->SetHeader(req, "Content-type", "application/json");
    req->SetBody(req, "{\"a\": 1}");

    req->Do(req);
}

void test_request(void) {
    test_new_request();
}
