#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "machine.h"
#include "connection.h"

#define SERVER_ADDR "192.168.1.1"

static int connection_prepare_socket(struct addrinfo *res)
{
    int status;
    struct addrinfo hints, *p;
    char ipstr[INET6_ADDRSTRLEN];
    int s;

    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE; // fill in my IP for me

    if ((status = getaddrinfo(SERVER_ADDR, NULL, &hints, &res)) != 0) {
        fprintf(stderr, "gai error: %s\n", gai_strerror(status));
        exit(1);
    }

    for(p = res; p != NULL; p->ai_next) 
    {
        void *addr;
        char *ipver;
        struct sockaddr_in *ipv4;
        struct sockaddr_in6 *ipv6;

        if(p->ai_family == AF_INET)
        {
            ipv4 = (struct sockaddr_in *) p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }
        else
        {
            ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf(" %s: %s\n", ipver, ipstr);
    }

    s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    return s;

}


static int connection_connect_to_server(struct connection *connection, user *user)
{
    int s;

    s = connection_prepare_socket(user->address_info);
    return connect(s, user->address_info->ai_addr, user->address_info->ai_addrlen);

}

//void connection_send_msg()

void connection_init(connection *self)
{
    self->prepare_socket = connection_prepare_socket;
    self->connect_to_server = connection_connect_to_server;
    //self->send_msg = connection_send_msg;
}