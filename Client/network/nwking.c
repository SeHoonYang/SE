#include "nwking.h"
#include "ysock.h"
#include "packet.h"

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
    Sleep(FREQUENCY);

    /* Keys to send are specified */
    if(*data != 75 && *data != 80 && *data != 72 && *data != 77)
      *data = 0;

    connect_client(&client_socket, port, host);

    /* Create packet */
    struct packet *p = init_packet(3);
    marshal_packet(p, data, 1, 0);
    
    send(client_socket, (char *)p, sizeof(struct packet), 0);
    recv(client_socket, (char *)p, sizeof(struct packet), 0);

    /* Analyze the server responce */
    if(p->header == 4 && pkt_isvalid(p))
    {
      /* Not implemented yet */
    }

    close_socket(client_socket);

    free(p);
    *data = 0;
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