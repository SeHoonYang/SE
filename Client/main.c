#include <windows.h>
#include <stdio.h>
#include "console/cons.h"
#include "network/nwking.h"
#include "menu/menu.h"

HANDLE printing_thread;
HANDLE networking_thread;

char input = 0;

int main()
{
  /* Initialization */
  init_console();
  init_network("127.0.0.1", 2033, &input);

  /* Start printing thread */
  printing_thread = _beginthread(&show_screen,0,NULL);

  /* Show initial menu */
  if(show_menu() == 0)
    return 0;

  /* Start networking thread */
  //networking_thread = _beginthread(&send_input,0,NULL);

  /* Main thread. Get user input */
  while(input != 27)
  {
    input = getch();
  }

  /* Release resources */
  close_network();
  
  return 0;
}