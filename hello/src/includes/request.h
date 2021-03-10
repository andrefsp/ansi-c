#ifndef _HELLO_REQUEST_H
#define _HELLO_REQUEST_H

#include "curl/curl.h"

#include "response.h"

typedef struct Request Request;

struct Request {
    CURL *curl;
    struct curl_slist *chunk;

    char *method;
    char *url;

    void (*SetHeader)(Request *r, char *name, char *val);
    void (*SetBody)(Request *r, char *body);
    void (*SetTimeout)(Request *r, long timeout);
    void (*SetConnectTimeout)(Request *r, long timeout);
    Response *(*Do)(Request *r);
};


void Request_SetBody(Request *r, char *body);

void Request_SetHeader(Request *r, char *name, char *val);

void Request_SetTimeout(Request *r, long timeout);

void Request_SetConnectTimeout(Request *r, long timeout);

Response *Request_Do(Request *r); 

// Constructor
Request *NewRequest();

#endif
