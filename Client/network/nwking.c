#include "nwking.h"
#include "ysock.h"
#include "packet.h"
#include "../console/cons.h"

#define FREQUENCY 30

static user_index;
static SOCKET client_socket;
static int port;
static char* host;
static char* data;
static int closed;

void set_user_index(int i)
{
  user_index = i;
}

void init_network(char* _host, int _port, char* _data)
{
  /* Initialize the socket */
  init_socket(sizeof(struct packet));

  host = _host;
  port = _port;
  data = _data;
  closed = 0;
}

struct packet* send_once(struct packet* p, int* recv_amount)
{
  connect_client(&client_socket, port, host);
  send(client_socket, (char *)p, sizeof(struct packet), 0);
  *recv_amount = recv(client_socket, (char *)p, sizeof(struct packet), 0);
  close_socket(client_socket);  
}

void send_input()
{
  while(!closed)
  {
    /* Keys to send are specified */
    if(*data != 75 && *data != 80 && *data != 72 && *data != 77)
      *data = 0;

    /* Create packet */
    struct packet *p = init_packet(3);
    marshal_packet(p, data, 1, 0);
    marshal_packet(p, (char *)&user_index, 4, 1);

    int recv_amount;
    send_once(p, &recv_amount);

    /* Analyze the server responce */
    if(p->header == 4 && pkt_isvalid(p))
    {
      int obj_num = (int)p->buffer[0];

      /* Not implemented yet */
      for(int i = 0; i < obj_num; ++i)
      {
        if(*(int *)(p->buffer+12+i*19) == user_index)
        {
          unsigned short x = *(unsigned short *)(p->buffer+16+i*19);
          unsigned short y = *(unsigned short *)(p->buffer+18+i*19);

char buf[100];
sprintf(buf, "x : %d, y : %d", x, y);
SetConsoleTitle(buf);
        }
      }
    }

    free(p);
    *data = 0;

    Sleep(FREQUENCY);
  }
}

void close_network()
{
  closed = 1;
  end_socket();
}

void stop_network()
{
  closed = 1;
}

void resume_network()
{
  closed = 0;
}