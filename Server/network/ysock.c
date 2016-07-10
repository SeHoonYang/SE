#include "ysock.h"
#include "packet.h"
#include "../usr/usr.h"

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

void start_server(SOCKET s)
{
  SOCKET client;
  struct sockaddr_in client_addr;
  char buffer[buffer_size];
  int c = sizeof(struct sockaddr_in);

  while(1)
  {
    client = accept(s, (struct sockaddr *)&client_addr, &c);

    /* Receive a packet*/

    /* Note that we will use large buffer to
       receive the data in a single loop     */
    recv(client, buffer, buffer_size,0);

    /* Analyze the packet */
    int invalid = pkt_isvalid((struct packet *)buffer);
    int pkt_header = ((struct packet *)buffer)->header;

    /* Create a packet */
    struct packet* to_send;
    
    if(invalid)
    {
      to_send = init_packet(0);
    }
    else
    {
      /* Registration request */
      if(pkt_header == 1)
        to_send = init_packet(2);
    }

    /* Server operation */
    if(!invalid)
    {
      if(pkt_header == 1)
      {
        printf("Account create request : %s\n", ((struct packet *)buffer)->buffer);
        int success = create_account(((struct packet *)buffer)->buffer,((struct packet *)buffer)->buffer+10);
        char send_buffer[1];
        send_buffer[0] = success + '0';
        marshal_packet(to_send,send_buffer,1);
      }
    }

    /* Send state of the server */
    send(client, (char *)to_send, sizeof(struct packet),0);

    /* Free the packet */
    free_packet(to_send);

    close(client);
  }
}

void close_socket(SOCKET s)
{
  closesocket(s);
}

void end_socket()
{
  WSACleanup();
}
