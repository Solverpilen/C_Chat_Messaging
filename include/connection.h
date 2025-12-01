#ifndef CONNECTION.H
#define CONNECTION.H

typedef struct connection {

    void (*prepare_socket)(struct addrinfo *res);
    void (*connect_to_machine)(struct user *user, struct machine *machine);

} connection;

static int connection_prepare_socket(struct addrinfo *res);
int connection_connect_to_machine(struct connection *connection, struct machine *machine);
void connection_init(struct connection *self);

#endif