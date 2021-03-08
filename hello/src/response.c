#ifndef _HELLO_RESPONSE_C
#define _HELLO_RESPONSE_C

#include "gc.h"
#include "strings.h"
#include "response.h"


void Response_SetStatusCode(Response *r, int statusCode) {
    r->StatusCode = statusCode; 
}

void Response_SetStatus(Response *r, char *rstatus) {
    r->Status = rstatus; 
}

void Response_WriteBody(Response *r, char *contents) {
    char *newBody = GC_MALLOC((strlen(contents)+strlen(r->Body))*sizeof(char));
    strcat(newBody, r->Body);
    strcat(newBody, contents);
    
    GC_FREE(r->Body);

    r->Body = newBody;
}

void Response_SetHeader(Response *r, char *name, char *val) {}


Response *NewResponse() {
    Response *res = GC_MALLOC(sizeof(Response));

    res->SetStatus = Response_SetStatus;
    res->SetStatusCode = Response_SetStatusCode;

    res->SetHeader = Response_SetHeader;
    res->WriteBody = Response_WriteBody;

    res->Body = GC_MALLOC(sizeof(char));
    return res;
}

#endif
