// std IO needs to be removed after make intial colormap
#include <stdio.h>
#include "menu.h"
#include "menu.inc"
#include "../console/cons.h"
#include "../console/color.h"
#include "../conf.inc"

/* Width and height of the game must be
   specified in this context. W = 32, H = 20 */

int show_menu()
{
  /* Show initial_screen */
  color* colormap = (color *)malloc((W*H*2 + 1)*sizeof(color));
  colormap_from_string(initial_cstring, colormap);
  update_screen(initial_screen, colormap);

  /* Get user input */
  while(1)
    getch();

  return 0;
}