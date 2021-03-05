#include "gc.h"
#include <libwebsockets.h>
#include "server.h"

struct lws_context *context;


static int callback_http(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
 
    char *requested_uri;
    if (reason != 31) {
        printf("Reason: %d \n", reason);
    }

    switch(reason) {
        case LWS_CALLBACK_HTTP:
            requested_uri = (char *) in;
            printf("%d requested URI: %s\n", len, requested_uri);

            lws_return_http_status(wsi, 200, "thisis abody");
            //lws_write_http(wsi, "this", 200);
            break;
        case LWS_CALLBACK_HTTP_BODY: 
            requested_uri = (char *) in;
            printf("%d requested URI: %s\n", len, requested_uri);
        //    //lws_return_http_status(wsi, 200, "thisis abody");

        //    break;
        default:
            break;
    }
    return 0;
}


static struct lws_protocols protocols[] = {
    /* The first protocol must always be the HTTP handler */
    {
        "http-only",   /* name */
        callback_http, /* callback */
        0,             /* No per session data. */
        0,             /* max frame size / rx buffer */
    },
    { NULL, NULL, 0, 0 } /* terminator */
};


int Stop(Server *s) {
    return 0;
}

int Start(Server *s) {    
    context = lws_create_context(s->info);

    while(!lws_service(context, 0));

    lws_context_destroy(context);
    return 0;
}

Server *NewServer() {
    Server *s = GC_MALLOC(sizeof(Server));
    s->Start = Start;
    s->Stop = Stop;

    s->info = GC_MALLOC(sizeof(struct lws_context_creation_info));
    s->info->port = 8000;
    s->info->protocols = protocols;
    s->info->gid = -1;
    s->info->uid = -1;

    return s;
}
