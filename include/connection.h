#ifndef CONNECTION.H
#define CONNECTION.H

typedef struct {

    void (*prepare_socket)(struct addrinfo *res);
    void (*connect_to_server)(struct user *user);
    void (*init)(connection *connection);

} connection;

static int connection_prepare_socket(struct addrinfo *res);
static int connection_connect_to_server(connection *connection, user *user);
void connection_init(connection *self);

#endif