#ifndef _HELLO_RESPONSE_H
#define _HELLO_RESPONSE_H


typedef struct Response Response;

struct Response {
    int StatusCode;
    char *Status;

    char *Body;

    void (*SetStatus)(Response *r, char *rstatus);
    void (*SetStatusCode)(Response *r, int statusCode);
    void (*SetHeader)(Response *r, char *name, char *val);
    void (*WriteBody)(Response *r, char *contents);
};

void Response_SetStatus(Response *r, char *rstatus);

void Response_SetStatusCode(Response *r, int statusCode);

void Response_WriteBody(Response *r, char *contents);

void Response_SetHeader(Response *r, char *name, char *val);

// Constructor
Response *NewResponse();

#endif
