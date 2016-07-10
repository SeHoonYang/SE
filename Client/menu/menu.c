#include <stdio.h>
#include "menu.h"
#include "menu.inc"
#include "../console/cons.h"
#include "../console/color.h"
#include "../conf.inc"
#include "../network/nwking.h"

static int _max(int r, int l)
{
  return r < l ? l : r;
}

static int _min(int r, int l)
{
  return r < l ? r : l;
}

static int valid_ID_char(char c)
{
  return ('a' <= c && 'z' >= c) || ('0' <= c && '9' >= c);
}

static color colormap[(32*20*2+1)*3];

/* Width and height of the game must be
   specified in this context. W = 32, H = 20 */

int show_menu()
{
  /* Show initial_screen */
  colormap_from_string(initial_cstring, colormap);
  update_screen(initial_screen, colormap);

  /* Printing starts from here to prevent synchronization problem */
  resume_printing();

  /* Press enter to start */
  while(getch()!=13);

  char key = 0;
  int menu_index = 0;

  /* Show initial menu */
  while(key != 27)
  {
    switch(key)
    {
      case 72:
        menu_index = _max(0, menu_index - 1);
        break;
      case 80:
        menu_index = _min(2, menu_index + 1);
        break;
    }
    switch(menu_index)
    {
      case 0:
        if(key == 13)
          return show_create_account_menu();
        colormap_from_string(first_cstring, colormap);
        update_screen(first_menu, colormap);
        break;
      case 1:
        if(key == 13)
          return show_login_menu();
        colormap_from_string(second_cstring, colormap);
        update_screen(second_menu, colormap);
        break;
      case 2:
        if(key == 13)
          return 0;
        colormap_from_string(third_cstring, colormap);
        update_screen(third_menu, colormap);
        break;
    }
    key = getch();
  }

  return 0;
}

int show_create_account_menu()
{
  char ID[11] = "\0\0\0\0\0\0\0\0\0\0\0";
  char PWD[11] = "\0\0\0\0\0\0\0\0\0\0\0";
  int ID_index = 0;
  int PWD_index = 0;

  /* Show initial_screen */
  colormap_from_string(first_reg_cstring, colormap);
  update_screen(regist, colormap);
  char key = 0;
  int menu_index = 0;

  /* Show initial menu */

  while(key != 27)
  {
    int arrow_pressed = 0;

    switch(key)
    {
      case 72:
        menu_index = _max(0, menu_index - 1);
        arrow_pressed = 1;
        break;
      case 80:
        menu_index = _min(2, menu_index + 1);
        arrow_pressed = 1;
        break;
    }
    switch(menu_index)
    {
      case 0:
        colormap_from_string(first_reg_cstring, colormap);
        update_screen(NULL, colormap);
        
        if(!arrow_pressed && valid_ID_char(key) && ID_index < 10)
        {
          ID[ID_index] = key;
          ID[++ID_index] = '\0';
        }else if(key == 8 && ID_index > 0)
        {
          ID[--ID_index] = '\0';
        }
        update_screen_string("          ",860);
        update_screen_string(ID,870-ID_index);

        break;
      case 1:
        colormap_from_string(second_reg_cstring, colormap);
        update_screen(NULL, colormap);
        
        if(!arrow_pressed && valid_ID_char(key) && PWD_index < 10)
        {
          PWD[PWD_index] = key;
          PWD[++PWD_index] = '\0';
        }else if(key == 8 && PWD_index > 0)
        {
          PWD[--PWD_index] = '\0';
        }
        update_screen_string("          ",924);
        update_screen_string(PWD,934-PWD_index);
        break;
      case 2:
        if(key == 13)
        {
          /* Send server the register request */
          struct packet* p = init_packet(1);

          /* Marshal data to the packet */
          marshal_packet(p, ID, 10, 0);
          marshal_packet(p, PWD, 10, 10);

          /* Send and receive data from the server */
          send_once(p);

          /* Free the packet structure */
          free_packet(p);

          return show_menu();
        }
        colormap_from_string(third_reg_cstring, colormap);
        update_screen(NULL, colormap);
        break;
    }
    key = getch();
  }

  return 0;
}

static show_login_menu(void)
{
  return 0;
}