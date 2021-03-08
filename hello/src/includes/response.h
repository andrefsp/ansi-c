#ifndef _HELLO_RESPONSE_H
#define _HELLO_RESPONSE_H

typedef struct Response Response;

struct Response {
    void (*SetStatusCode)(int statusCode);
    void (*SetHeader)(Response *r, char *name, char *val);
    void (*SetBody)(Response *r, char *body);
};

void Response_SetStatusCode(int statusCode);

void Response_SetBody(Response *r, char *body);

void Response_SetHeader(Response *r, char *name, char *val);

// Constructor
Response *NewResponse();

#endif
