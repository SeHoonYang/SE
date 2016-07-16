#ifndef _PACKET_H_
#define _PACKET_H_

#define BUFFER_SIZE 140

/*
  Packet header

  0 : Error

   // Before the game start //
   1 : Registration request
       -buffer[0-9] : ID
       -buffer[10-19] : Password
   2 : Server quick responce
       -buffer[0] : 1 for success, 0 for failure
   6 : Login request
       -buffer[0-10] : ID
       -buffer[11-21] : Password

   // After the game start //
   3 : User input
       -buffer[0] : char
   4 : Server responce
       -buffer[0] : # of object
       -buffer[1 + i*sizeof_object_data ~ (i+1)*sizeof_object_data]
   
   // object data : coordinate(2),direction(1),HP(4) ...
   5 : Data

*/

struct packet
{
  int header;
  char buffer[BUFFER_SIZE];
  int magic;
};

struct packet* init_packet(int);
void marshal_packet(struct packet *, char *, int, int);
void free_packet(struct packet *);
int pkt_isvalid(struct packet *);

#endif