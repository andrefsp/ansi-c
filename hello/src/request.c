#ifndef _HELLO_REQUEST_C
#define _HELLO_REQUEST_C

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "gc.h"
#include "curl/curl.h"
#include "request.h"

#include "response.c"
#include "string_utils.c"


void Request_SetTimeout(Request *r, long timeout) {
    curl_easy_setopt(r->curl, CURLOPT_TIMEOUT, timeout);
}

void Request_SetConnectTimeout(Request *r, long timeout) {
    curl_easy_setopt(r->curl, CURLOPT_CONNECTTIMEOUT, timeout);
}

void Request_SetBody(Request *r, char *body) {
    curl_easy_setopt(r->curl, CURLOPT_POSTFIELDS, body);
}

void Request_SetHeader(Request *r, char *name, char *val) {
    char *header = GC_MALLOC((strlen(name)+strlen(val)+4)*sizeof(char));
    header = strcat(header, name);
    header = strcat(header, ": ");
    header = strcat(header, val);

    r->chunk = curl_slist_append(r->chunk, header);
    curl_easy_setopt(r->curl, CURLOPT_HTTPHEADER, r->chunk);
}

static size_t _responseBodyHandler(void *contents, size_t size, size_t nmemb, void *userp) {
    Response *res = userp;
    res->WriteBody(res, (char *)contents);
    return nmemb;
}

static size_t _responseHeaderHandler(void *contents, size_t size, size_t nmemb, void *userp) {
    char **parts = GC_MALLOC(0);
    char *header = GC_MALLOC(nmemb*sizeof(char));

    strcpy(header, contents);
    header = str_clean(header);

    if (strlen(header) < 1) {
        goto free;
    }

    Response *res = (Response *)userp;
    if (!res->StatusCode) {
        // TODO(andrefsp): Validate status header.
        // There should be an error in case an invalid status header is sent
        parts = str_tokenize(header, " ");
        res->SetStatusCode(res, atoi(parts[1]));
        res->SetStatus(res, parts[2]);
    } else {
        parts = str_n_tokenize(header, ":", 1);
        
        char *hname = str_strip(parts[0], ' ');
        char *hval = str_strip(parts[1], ' ');

        res->SetHeader(res, hname, hval); 
    }

free:
    GC_FREE(header); 
    GC_FREE(parts);

    return nmemb;
}


Response *Request_Do(Request *r) {
    curl_easy_setopt(r->curl, CURLOPT_NOPROGRESS, 1L);

    curl_easy_setopt(r->curl, CURLOPT_HEADERFUNCTION, _responseHeaderHandler);
    curl_easy_setopt(r->curl, CURLOPT_WRITEFUNCTION, _responseBodyHandler);
   
    Response *res = NewResponse();

    curl_easy_setopt(r->curl, CURLOPT_HEADERDATA, res);
    curl_easy_setopt(r->curl, CURLOPT_WRITEDATA, res);

    CURLcode response = curl_easy_perform(r->curl);

    return res;
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

    r->SetTimeout = Request_SetTimeout;
    r->SetConnectTimeout = Request_SetConnectTimeout;
    r->SetBody = Request_SetBody;
    r->SetHeader = Request_SetHeader;
    r->Do = Request_Do;

    return r;
}


#endif
