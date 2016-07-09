#include "packet.h"

struct packet *init_packet(int buffer_size){
  struct packet *pkt = calloc(1, sizeof(struct packet));
  pkt->buffer = malloc(buffer_size);
  pkt->buffer_size = buffer_size;
  return pkt;
}

void marshal_packet(struct packet *pkt, const void *data){
  memcpy(pkt->buffer, data, pkt->buffer_size);
}

void free_packet(struct packet *pkt){
  free(pkt->buffer);
  free(pkt);
}

int pkt_isvalid(struct packet *pkt){
  return 1;
}
