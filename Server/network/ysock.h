#ifndef _YSOCK_H_
#define _YSOCK_H_

#include <winsock2.h>

int init_socket(int);
int init_server(SOCKET*, int);
void open_server(SOCKET, int);
void start_server(SOCKET);
void close_socket(SOCKET);
void end_socket(void);

#endif