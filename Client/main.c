#include <windows.h>
#include <stdio.h>
#include "lib/lib.h"
#include "console/cons.h"
#include "network/nwking.h"
#include "menu/menu.h"
#include "game/item.h"
#include "game/map.h"

HANDLE printing_thread;
HANDLE networking_thread;

char input = 0;

int main(int argc, char** argv)
{
  /* This program must be executed with 2 parameters */
  if(argc != 3)
  {
    printf("Execute run.bat to start this program\n");
    system("PAUSE");
    return -1;
  }

  /* Initialization */
  init_console();
  init_map_list();
  init_network(argv[1], strn_to_int(argv[2],5), &input);
  init_item();

  /* Start printing thread */
  printing_thread = _beginthread(show_screen,0,NULL);

  /* Show initial menu */
  if(show_menu() == 0)
    return 0;

  /* Start networking thread */
  request_server_make_thread();
  networking_thread = _beginthread(send_input,0,NULL);

  /* Main thread. Get user input */
  while(input != 27)
  {
    input = getch();

    if(input == 13)
    {
      show_game_menu();
      input = 0;
    }
  }

  /* Release resources */
  close_network();
  free_inventory();
  end_console();

  return 0;
}