#include "connection.h"
#include <netinet/in.h>

#define USERNAME_SIZE 30

typedef struct user {

    char user_name[USERNAME_SIZE];
    struct sockaddr_in *ipv4;
    struct sockaddrin6 *ipv6;

};




