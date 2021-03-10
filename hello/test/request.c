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

    Response *res = req->Do(req);
    
    assert(("body size", strlen(res->Body) > 0));
}

void test_response_status_header_handler(void) {
    char *statusHeader = "HTTP/1.1 200 OK\r\n";
    char *lastHeader = "\r\n";

    Response *res = NewResponse();

    _responseHeaderHandler(statusHeader, 1, strlen(statusHeader), res);
    _responseHeaderHandler(lastHeader, 1, strlen(lastHeader), res);

    assert(("status code", res->StatusCode == 200));
    assert(("status", strcmp(res->Status, "OK") == 0));    
}


void test_response_header_handler(void) {
    char *statusHeader = "HTTP/1.1 200 OK\r\n";
    char *ctypeHeader = "Content-Type: text/html\r\n";
    char *etagHeader = "ETag: W/\"10-/VnJyQBB0+b7i4NY83P42KKVWsM\"\r\n";
    char *lastHeader = "\r\n";
    Response *res = NewResponse();

    _responseHeaderHandler(statusHeader, 1, strlen(statusHeader), res);
    _responseHeaderHandler(ctypeHeader, 1, strlen(ctypeHeader), res);
    _responseHeaderHandler(etagHeader, 1, strlen(etagHeader), res);
    _responseHeaderHandler(lastHeader, 1, strlen(lastHeader), res);

    assert(("status code", res->StatusCode == 200));
    assert(("status", strcmp(res->Status, "OK") == 0));
    
    char *ctypeh = res->GetHeader(res, "Content-Type");
    assert(("ctype header not nil", ctypeh));
    assert(("ctype header", strcmp(ctypeh, "text/html") == 0));

    char *etagh = res->GetHeader(res, "ETag");
    assert(("custom header not nil", etagh));
    assert(("custom header", strcmp(etagh, "W/\"10-/VnJyQBB0+b7i4NY83P42KKVWsM\"") == 0));
}


void test_request(void) {
    test_new_request();
    test_response_header_handler(); 
    test_response_status_header_handler();
}
