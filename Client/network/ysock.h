#ifndef _YSOCK_H_
#define _YSOCK_H_

#include <winsock2.h>

int init_socket(int);
int connect_client(SOCKET*, int, char*);
void close_socket(SOCKET);
void end_socket(void);

#endif