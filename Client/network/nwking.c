#include "nwking.h"
#include "ysock.h"

#define frequency 30

static SOCKET client_socket;
static int port;
static char* host;
static char* data;
static int closed;

void init_network(char* _host, int _port, char* _data)
{
  /* Initialize the socket */
  init_socket(80);

  host = _host;
  port = _port;
  data = _data;
  closed = 0;
}

void send_input()
{
  while(!closed)
  {
    Sleep(frequency);
    connect_client(&client_socket, port, host);
    send(client_socket, data, 2, 0);
    close_socket(client_socket);
    *data = 0;
  }
}

void close_network()
{
  closed = 1;
  end_socket();
}