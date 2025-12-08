#ifndef MACHINE.H
#define MACHINE.H

#include <netinet/in.h>
#include <netdb.h>
#include "connection.h"


typedef struct machine {

    char *user_name;
    struct addrinfo *address_info;
    void *users;
    struct connection *connection;

    void (*select_machine)(char *user_name, machine *machine);

} machine;

void * machine_select_machine(char *user_name);

struct machine *machine_init(char *user_name);

#endif