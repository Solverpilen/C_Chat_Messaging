#ifndef USER_SERVER.H
#define USER_SERVER.H

int prepare_socket(struct addrinfo *res);
void connect_to_machine(struct user *user);

#endif
