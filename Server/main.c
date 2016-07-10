#include "network/ysock.h"
#include "network/nwking.h"
#include "usr/usr.h"

int main()
{
  /* Get arguments / Make GUI. It depends */
  SOCKET server_socket;

  int s = init_socket(sizeof(struct packet));
  int d = init_server(&server_socket, 2033);
  open_server(server_socket,3);
  printf("Server opened\n");

  start_server(server_socket);
  close_socket(server_socket);

  end_socket();

  return 0;
}