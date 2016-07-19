#include "network/ysock.h"
#include "network/nwking.h"
#include "usr/usr.h"
#include "game/map_data.h"

SOCKET server_socket;

static void _start_server()
{
  start_server(server_socket);
}

int main()
{
  /* Get arguments / Make GUI. It depends */

  /* Initializing */
  printf("Initializing data structures\n");
  init_user_data();

  printf("Loading map data to the memory\n");
  load_maps();

  /* Add thread to properly stop the server */
  init_socket(sizeof(struct packet));
  init_server(&server_socket, 2033);
  open_server(server_socket,20);
  printf("Server has been opened\n");

  /* Networking thread */
  _beginthread(&_start_server,0,NULL);

  while(getch() != 27);

  /* Release user data */
  clear_user_data();

  /* Terminate the server */
  close_socket(server_socket);

  end_socket();

  return 0;
}