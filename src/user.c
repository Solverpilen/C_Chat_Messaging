#include "machine.h"
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

void * user_select_machine(char *user_name, machine *self)
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

struct machine * machine_init(const char * user_name)
{
    machine *u = malloc(sizeof(machine));
    if(!u) return NULL;

    u->user_name = strdup(user_name);
    u->address_info = NULL;
    u->connection = NULL;

    u->select_machine = user_select_machine;
    
    char **user_list = malloc(sizeof(char*) * 4);

    user_list[0] = strdup("SERVER");
    user_list[1] = strdup("James");
    user_list[2] = strdup("Peter");
    user_list[3] = NULL; 

    u->users = user_list;

    return u;
    
}



