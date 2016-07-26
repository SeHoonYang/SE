#ifndef _PACKET_H_
#define _PACKET_H_

#define BUFFER_SIZE 413

/*
  Packet header

  0 : Error

   // Before the game start //
   1 : Registration request
       -buffer[0-9] : ID
       -buffer[10-19] : Password
   2 : Server quick response
       -buffer[0] : 1 for success, 0 for failure
   6 : Login request
       -buffer[0-10] : ID
       -buffer[11-21] : Password
   7 : Server login response
       -buffer[0] : 1 for success, 0 for failure
       -bufer[1-4] : user index

   // After the game start //
   3 : User input
       -buffer[0] : char
       -bufer[1-4] : user index
   4 : Server response
       -buffer[0] : map id
       -buffer[1] : # of object
       -buffer[1 + i*sizeof_object_data ~ (i+1)*sizeof_object_data]
       
       user object data : name : 11 index : 4 position : 4 (total 19)
       monster object data : id : 4 position : 4 (total 8)
   
   5 : Monster combat responce
       -Same as 4 + enemy index 4, enemy current hp for last 2 byte

   // After the login //
   8 : New thread creation request

   9 : Menu request
       -buffer[0-3] : user index

   10 : Menu response
        -buffer[0-1] : current hp
        -buffer[2-3] : max hp
        -buffer[4-5] : current mp
        -buffer[6-7] : max mp
        -buffer[8-9] : str
        -buffer[10-11] : def
        -buffer[12-15] : money
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