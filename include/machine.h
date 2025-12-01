#ifndef MACHINE.H
#define MACHINE.H

#include <netinet/in.h>
#include <netdb.h>
#include "connection.h"


typedef struct machine {

    char *user_name;
    struct sockaddr_in *ipv4;
    struct sockaddr_in6 *ipv6;
    struct addrinfo *address_info;
    void *users;
    struct connection *connection;

    void (*select_machine)(char *user_name);

} machine;

void * machine_select_machine(char *user_name);

struct machine *machine_init(

    machine *self, 
    char *user_name, 
    struct sockaddr_in *ipv4,
    struct sockaddr_in6 *ipv6,
    struct addrinfo *address_info,
    struct connection *connection
);

#endif