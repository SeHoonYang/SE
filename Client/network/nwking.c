#include "nwking.h"
#include "ysock.h"
#include "packet.h"

#define FREQUENCY 30

static SOCKET client_socket;
static int port;
static char* host;
static char* data;
static int closed;

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
  send(client_socket, (char *)p, BUFFER_SIZE, 0);
  *recv_amount = recv(client_socket, (char *)p, BUFFER_SIZE, 0);
  close_socket(client_socket);  
}

void send_input()
{
  while(!closed)
  {
    Sleep(FREQUENCY);
    connect_client(&client_socket, port, host);
    send(client_socket, data, 2, 0);
    //revc(client_socket, p, p->buffer_size, 0);
    close_socket(client_socket);
    *data = 0;
  }
}

void close_network()
{
  closed = 1;
  end_socket();
}