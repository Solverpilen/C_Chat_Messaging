#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "machine.h"
#include "connection.h"
#include <stdlib.h>

static int connection_prepare_socket(struct addrinfo *res, char * ip)
{
    int status;
    struct addrinfo hints, *p;
    char ipstr[INET6_ADDRSTRLEN];
    int s;

    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE; // fill in my IP for me

    if ((status = getaddrinfo(ip, NULL, &hints, &res)) != 0) {
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


static int connection_connect_to_machine(struct connection *self_connection, struct machine *self_machine, char * target_ip)
{
    int sockfd;

    sockfd = connection_prepare_socket(self_connection->res, target_ip);

    if(connect(sockfd, self_machine->address_info->ai_addr, self_machine->address_info->ai_addrlen) == 0)
    {
        freeaddrinfo(self_connection->res);
        return sockfd;
    }
    else
    {
        perror("connect");
        close(sockfd);
        return -1;
    }

}

//void connection_send_msg()

connection * connection_init(struct machine *self_machine, char * target_ip)
{
    int connection_status;
    connection *c = malloc(sizeof(connection));

    c->connect_to_machine = connection_connect_to_machine;
    connection_status = (int) c->connect_to_machine(&c, &self_machine, target_ip);
    
    if(connection_status != -1)
    {
        c->sockfd = connection_status;
        return c;
    }

    return NULL;

    //self->send_msg = connection_send_msg;
}