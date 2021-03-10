#include <assert.h>
#include "../src/hello.c"


void test_request_properties() {
    char *url = "http://localhost:7777";
    Request *req = NewRequest("GET", url);
 
    assert(("url", strcmp(req->url, url) == 0));
    assert(("method", strcmp(req->method, "GET") == 0));

    req->SetTimeout(req, 2);
    req->SetHeader(req, "Content-Type", "application/json");
    req->SetBody(req, "{\"a\": 1}");

    char *ctypeh = req->GetHeader(req, "Content-Type");
    assert(("ctype header not nil", ctypeh));
    assert(("ctype header", strcmp(ctypeh, "application/json") == 0));

    assert(("body not nil", req->body));
    assert(("body", strcmp(req->body, "{\"a\": 1}") == 0));
}


void test_request(void) {
    test_request_properties(); 
}
