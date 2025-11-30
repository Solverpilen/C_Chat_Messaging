#include "machine.h"
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

static void * user_select_machine(char *user_name, machine *self)
{
    if(self->users)
    {
        for(int i; i < (sizeof(self->users) / sizeof(self->users[0])); i++) 
        {
            if user_name == self->users[]
        }
    }
}

struct machine * machine_init(

    machine *self, 
    char *user_name, 
    struct sockaddr_in *ipv4,
    struct sockaddr_in6 *ipv6,
    struct addrinfo *address_info,
    struct connection *connection,
)
{
    machine *m = malloc(sizeof(machine));
    m->user_name = strdup(user_name);

    if(ipv4)
    {
        self->ipv6 = NULL;
        self->ipv4 = ipv4;
    }
    else if(ipv4 == NULL)
    {
        self->ipv4 = NULL;
        self->ipv6 = ipv6;
    }
    else
    {    
        self->ipv4 = NULL;
        self->ipv6 = NULL;
        printf("Error: you did not enter a valid IPv4 or IPv6 address");
    }

    self->address_info = address_info;
    self->connection = connection;

    self->select_machine = user_select_machine;

    char *users[20][30] = {
        "SERVER",
        "James",
        "Peter"
    };

    self->users = users;
    return m;
    
}



