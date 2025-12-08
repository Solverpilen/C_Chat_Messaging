#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "connection.h"
#include "machine.h"
#include <stdlib.h>

typedef struct users {

    machine *user;
    machine *next;

} users;

void * server_select_machine(machine * self, char *user_name)
{
    if(self->users)
    {
        users *user_list = (users *)self->users;

        for(user_list; user_list->next != NULL; user_list->next)
        {
            if (strcmp(user_name, user_list->user->user_name) == 0)
            {
                return user_name;
            }
        }
    } 
    
    return NULL;
}

struct machine * machine_init(char * user_name)
{
    machine *s = malloc(sizeof(machine));
    if(!s) return NULL;

    s->user_name = strdup(user_name);
    s->address_info = NULL;
    s->connection = NULL;
    s->users = NULL;

    s->select_machine = server_select_machine;

    return s;

}
