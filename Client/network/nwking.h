#ifndef _NWKING_H_
#define _NWKING_H_

#include "packet.h"

void set_user_index(int);
void init_network(char*, int, char*);
void send_input(void);
void close_network(void);
struct packet* send_once(struct packet *, int *);
void stop_network(void);
void resume_network(void);

#endif