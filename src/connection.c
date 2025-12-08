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

static int connection_prepare_socket(struct addrinfo **res, char * ip)
{
    int status;
    struct addrinfo hints, *p;
    char ipstr[INET6_ADDRSTRLEN];
    int sockfd;

    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

    if ((status = getaddrinfo(ip, 3490, &hints, &res)) != 0) {
        fprintf(stderr, "gai error: %s\n", gai_strerror(status));
        return -1;
    }

    for(p = res; p != NULL; p = p->ai_next) 
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

    sockfd = socket((*res)->ai_family, (*res)->ai_socktype, (*res)->ai_protocol);
    if(sockfd == -1)
    {
        perror("socket");
        freeaddrinfo(*res);
        return -1;
    }

    return sockfd;

}


static int connection_connect_to_machine(struct connection *self, struct machine *machine, const char * target_ip)
{
    int sockfd;

    self->sockfd = connection_prepare_socket(self->res, target_ip);

    if(connect(self->sockfd, self->res->ai_addr, self->res->ai_addrlen) == -1)
    {
        perror("connect");
        close(self->sockfd);
        freeaddrinfo(self->res);
        return -1;
    }
    
    freeaddrinfo(self->res);
    return self->sockfd;
}

//void connection_send_msg()

connection * connection_init(struct machine *machine, char * target_ip)
{
    int connection_status;
    connection *c = malloc(sizeof(connection));
    if(!c) return NULL;

    c->res = NULL;
    c->sockfd = -1;

    c->connect_to_machine = connection_connect_to_machine;
    
    if(c->connect_to_machine(c, machine, target_ip) == -1)
    {
        free(c);
        return NULL;
    }

    printf("CONNECTION: Suceeded \n");
    return c;

    //self->send_msg = connection_send_msg;
}