#ifndef _NWKING_H_
#define _NWKING_H_

#include "packet.h"

void init_network(char*, int, char*);
void send_input(void);
void close_network(void);
struct packet* send_once(struct packet *);

#endif