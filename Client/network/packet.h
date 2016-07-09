struct packet {
  int *buffer; //contents
  int buffer_size; //size of contents
  int header;  //header
};

extern struct packet *init_packet(int buffer_size);
extern void marshal_packet(struct packet *pkt, const void *data);
extern void free_packet(struct packet *pkt);
extern void pkt_isvalid(struct packet *pkt);
