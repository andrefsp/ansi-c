#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "gc.h"
#include "curl/curl.h"
#include "request.h"


void SetTimeout(Request *r, long timeout) {
    curl_easy_setopt(r->curl, CURLOPT_TIMEOUT, timeout);
}

void SetConnectTimeout(Request *r, long timeout) {
    curl_easy_setopt(r->curl, CURLOPT_CONNECTTIMEOUT, timeout);
}

void SetBody(Request *r, char *body) {
    curl_easy_setopt(r->curl, CURLOPT_POSTFIELDS, body);
}

void SetHeader(Request *r, char *name, char *val) {
    char *header = GC_MALLOC((strlen(name)+strlen(val)+4)*sizeof(char));
    header = strcat(header, name);
    header = strcat(header, ": ");
    header = strcat(header, val);

    r->chunk = curl_slist_append(r->chunk, header);
    curl_easy_setopt(r->curl, CURLOPT_HTTPHEADER, r->chunk);
}

static size_t _responseBodyHandler(void *contents, size_t size, size_t nmemb, void *userp) {
    printf("body>> %d, %s\n", strlen(contents), contents);
    return strlen(contents);
}

static size_t _responseHeaderHandler(void *contents, size_t size, size_t nmemb, void *userp) {
    printf("headers>> %d,  %s", strlen(contents), contents);
    return strlen(contents);
}


void Do(Request *r) {
    // TODO(andrefsp): Create response object here and return it!

    curl_easy_setopt(r->curl, CURLOPT_NOPROGRESS, 1L);

    curl_easy_setopt(r->curl, CURLOPT_HEADERFUNCTION, _responseHeaderHandler);
    curl_easy_setopt(r->curl, CURLOPT_WRITEFUNCTION, _responseBodyHandler);
    
    curl_easy_setopt(r->curl, CURLOPT_HEADERDATA, NULL);
    curl_easy_setopt(r->curl, CURLOPT_WRITEDATA, NULL);

    CURLcode response = curl_easy_perform(r->curl);
} 


Request *NewRequest(char *method, char *url) {
    Request *r = GC_MALLOC(sizeof(Request));
    
    r->curl = curl_easy_init();
    r->chunk = NULL;

    // Method
    r->method = method;
    curl_easy_setopt(r->curl, CURLOPT_CUSTOMREQUEST, r->method);

    // Url
    r->url = url;
    curl_easy_setopt(r->curl, CURLOPT_URL, r->url);

    r->SetTimeout = SetTimeout;
    r->SetConnectTimeout = SetConnectTimeout;
    r->SetBody = SetBody;
    r->SetHeader = SetHeader;
    r->Do = Do;

    return r;
}
