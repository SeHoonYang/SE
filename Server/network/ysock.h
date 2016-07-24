#ifndef _YSOCK_H_
#define _YSOCK_H_

#include <winsock2.h>

void stop_data_loop(void);
int init_socket(int);
int init_server(SOCKET*, int);
int connect_client(SOCKET*, int, char*);
void open_server(SOCKET, int);
void start_server(SOCKET);
void close_socket(SOCKET);
void end_socket(void);

#endif