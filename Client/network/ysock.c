#include "ysock.h"
#include "packet.h"

static int buffer_size;

int init_socket(int s)
{
  buffer_size = s;
  WSADATA wsa;
  return WSAStartup(MAKEWORD(2,2), &wsa);
}

int init_server(SOCKET* s, int port)
{
  struct sockaddr_in server;

  if((*s = socket(PF_INET, SOCK_STREAM,0)) == INVALID_SOCKET)
    return WSAGetLastError();

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(port);

  if(bind(*s, (struct sockaddr *)&server, sizeof(struct sockaddr)) == SOCKET_ERROR)
    return WSAGetLastError();

  return 0;
}

int connect_client(SOCKET*s, int port, char* host)
{
  struct sockaddr_in client;

  if((*s = socket(PF_INET, SOCK_STREAM,0)) == INVALID_SOCKET)
    return WSAGetLastError();

  client.sin_addr.s_addr = inet_addr(host);
  client.sin_family = AF_INET;
  client.sin_port = htons(port);

  connect(*s, (struct sockaddr *)&client, sizeof(client));

  return 0;
}

void open_server(SOCKET s, int queue)
{
  listen(s, queue);
}

void close_socket(SOCKET s)
{
  closesocket(s);
}

void end_socket()
{
  WSACleanup();
}
