#include "machine.h"
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

static void * user_select_machine(char *user_name, machine *self)
{
    if(self->users)
    {
        char ** users = (char **) self->users;
        for(int i = 0; users[i] != NULL; i++) 
        {
            if (strcmp(user_name, users[i]) == 0)
            {
                return user_name;
            }
        }
    }
    return NULL;
}

struct machine * machine_init(

    struct addrinfo *address_info,
    struct connection *connection
)
{
    machine *m = malloc(sizeof(machine));

    m->address_info = address_info;
    m->connection = connection;

    m->select_machine = user_select_machine;

    // TODO: Remove *users 

    char *users[] = {
        "SERVER",
        "James",
        "Peter",
        NULL
    };

    m->users = users;
    m->users = (char **) m->users;

    return m;
    
}



