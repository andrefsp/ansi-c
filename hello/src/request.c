#include <string.h>
#include "gc.h"
#include "curl/curl.h"
#include "request.h"


void SetTimeout(Request *r, long timeout) {
    curl_easy_setopt(r->curl, CURLOPT_TIMEOUT, 2L);
}

void SetHeader(Request *r, char *name, char *val) {
    char *header = GC_MALLOC((strlen(name)+strlen(val)+4)*sizeof(char));
    header = strcat(header, name);
    header = strcat(header, ": ");
    header = strcat(header, val);

    r->chunk = curl_slist_append(r->chunk, header);
    curl_easy_setopt(r->curl, CURLOPT_HTTPHEADER, r->chunk);
}

void Do(Request *r) {
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
    r->SetHeader = SetHeader;
    r->Do = Do;

    return r;
}
