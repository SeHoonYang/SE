#include <stdio.h>
#include "network/packet.h"
#include "network/ysock.h"
#include "usr/usr.h"
#include "game/map_data.h"

SOCKET server_socket;

int main()
{
  /* Get arguments / Make GUI. It depends */

  /* Initializing */
  printf("Initializing data structures\n");
  init_user_data();

  printf("Initializing monster data\n");
  init_mob();

  printf("Loading map data to the memory\n");
  load_maps();

  /* Release monster data */
  clear_mob_data();

  /* Add thread to properly stop the server */
  init_socket(sizeof(struct packet));
  init_server(&server_socket, 2033);
  open_server(server_socket,20);
  printf("Server has been opened\n");

  /* Mob manager */
  _beginthread(mob_manager, 0, NULL);

  /* Networking thread */
  _beginthread(start_server, 0, server_socket);

  while(getch() != 27);

  /* Stop monster manager */
  stop_mob_manager();

  /* Write behind; Write user data to file system */
  save_users_data();

  /* Release user data */
  clear_user_data();

  /* Release map data */
  clear_map_data();

  /* Terminate the server */
  close_socket(server_socket);

  end_socket();

  return 0;
}