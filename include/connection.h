#ifndef CONNECTION.H
#define CONNECTION.H
#include <arpa/inet.h>


typedef struct connection {

    struct addrinfo *res;
    int sockfd;

    int (*connect_to_machine)(struct connection *self, struct machine *machine, const char * target_ip);

} connection;

connection * connection_init(struct connection *self, char * target_ip);

#endif