#include "assert.h"
#include "strings.h"
#include "../src/hello.c"

void test_response_status_code() {
    Response *res = NewResponse();
    res->SetStatus(res, "OK");
    res->SetStatusCode(res, 200);
    assert(("status code", res->StatusCode == 200));
    assert(("status", res->Status == "OK"));
}


void test_response_write_body() {
    Response *res = NewResponse();
    res->SetStatusCode(res, 200);
    assert(("status code", res->StatusCode == 200));

    res->WriteBody(res, "this");
    res->WriteBody(res, "_is_\n"); 
    res->WriteBody(res, "data");
    assert(("body", strcmp(res->Body, "this_is_\ndata") == 0));
}


void test_response() {
    test_response_status_code();
    test_response_write_body(); 
}
