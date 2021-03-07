#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "curl/curl.h"
#include "../src/request.c"


void test_new_request(void) {
    Request *req = NewRequest("GET", "http://localhost:7777");
 
    assert(("url", strcmp(req->url, "http://localhost:7777") == 0));
    assert(("method", strcmp(req->method, "GET") == 0));

    req->SetTimeout(req, 2);
    req->SetHeader(req, "Authorization", "Bearer sometoken");
    req->SetHeader(req, "X-Context", "Some context"); 

    req->Do(req);
}

void test_request(void) {
    test_new_request();
}
