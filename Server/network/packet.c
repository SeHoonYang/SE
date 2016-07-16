#include "packet.h"

struct packet *init_packet(int h){
  struct packet *pkt = (struct packet *)calloc(1, sizeof(struct packet));
  pkt->header = h;
  pkt->magic = 0xaabbcc;
  return pkt;
}

void marshal_packet(struct packet *pkt, char *data, int size, int offset){
  memcpy(pkt->buffer + offset, data, size);
}

void free_packet(struct packet *pkt){
  free(pkt);
}

int pkt_isvalid(struct packet *pkt){
  return pkt->magic == 0xaabbcc;
}