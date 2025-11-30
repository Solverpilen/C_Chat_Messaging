#ifndef MACHINE.H
#define MACHINE.H

#include <netinet/in.h>
#include <netdb.h>
#include "connection.h"

#define USERNAME_SIZE 30

typedef struct {

    char user_name[USERNAME_SIZE];
    struct sockaddr_in *ipv4;
    struct sockaddrin6 *ipv6;
    struct addrinfo *address_info;
    void *users;
    connection *connection;

    void (*select_machine)(char *user_name);

} user;

void * user_select_machine(char *user_name);

#endif