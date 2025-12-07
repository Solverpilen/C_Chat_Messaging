#ifndef CONNECTION.H
#define CONNECTION.H
#include <arpa/inet.h>


typedef struct connection {

    struct addrinfo *res;
    int sockfd;

    int (*prepare_socket)(struct addrinfo *res, char * ip);
    int (*connect_to_machine)(struct connection *self_connection, struct machine *self_machine, char * target_ip);

} connection;

static int connection_prepare_socket(struct addrinfo *res, char * target_ip);
int connection_connect_to_machine(struct connection *connection, struct machine *machine, char * target_ip);
connection * connection_init(struct connection *self, char * target_ip);

#endif