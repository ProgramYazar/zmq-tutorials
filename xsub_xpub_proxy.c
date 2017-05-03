/* 
 * File:   main.c
 * Author: İlter Engin KIZILGÜN
 * Created on May 3, 2017, 12:34 AM
 * N to N proxy example
 * compile and linkage: clang -o nn_proxy xsub_xpub_proxy.c -lzmq
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <zmq.h>



const int PROXY_IN_PORT = 5665;
const int PROXY_OUT_PORT = 5666;

char* get_local_address(int port) {
    char *address = (char*) malloc(sizeof (char) * 100);
    snprintf(address, sizeof (char) *100, "tcp://127.0.0.1:%d", port);
    return address;
}

int main(int argc, char** argv) {
    void *ctx = zmq_ctx_new();
    assert(ctx != 0);

    void *xpub = zmq_socket(ctx, ZMQ_XPUB);
    void *xsub = zmq_socket(ctx, ZMQ_XSUB);

    char *xpub_address = get_local_address(PROXY_OUT_PORT);
    char *xsub_address = get_local_address(PROXY_IN_PORT);
    
    
    printf("in: %s out: %s\n", xsub_address, xpub_address);
    
    zmq_bind(xpub, xpub_address);
    zmq_bind(xsub, xsub_address);
    
    zmq_proxy(xsub, xpub, NULL); // "NULL" parameter for control socket

    
    
    free(xpub_address);
    free(xsub_address);
    
    zmq_close(xpub);
    zmq_close(xsub);
    zmq_ctx_destroy(ctx);

    return (EXIT_SUCCESS);
}

