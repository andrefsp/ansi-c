#include "curl/curl.h"

#ifndef REQUEST_H
#define REQUEST_H

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
    void (*Do)(Request *r);
};


void SetBody(Request *r, char *body);

void SetHeader(Request *r, char *name, char *val);

void SetTimeout(Request *r, long timeout);

void SetConnectTimeout(Request *r, long timeout);


void Do(Request *r); 


// Constructor
Request *NewRequest();


#endif
