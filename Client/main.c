#include <windows.h>
#include <stdio.h>
#include "console/cons.h"

HANDLE printing_thread;
HANDLE networking_thread;

int main()
{
  /* Initialization */
  init_console();

  /* Start printing thread */
  printing_thread = _beginthread(&show_screen,0,NULL);

  /* Start networking thread */
  /* Not implemented yet */

  /* Main thread. Get user input */
  char input = 0;
  while(input != 27)
  {
    input = getch();
  }

  /* Release resources */
  /* Not implemented yet */
  return 0;
}