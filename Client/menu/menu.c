#include <stdio.h>
#include <windows.h>
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

static int valid_id_char(char c)
{
  return ('a' <= c && 'z' >= c) || ('0' <= c && '9' >= c);
}

static color colormap[(32*20*2+1)*3];

/* Width and height of the game must be
   specified in this context. W = 32, H = 20 */

int show_menu()
{
  /* Show initial_screen */
  colormap_from_string(32, 20, initial_cstring, colormap);
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
        colormap_from_string(32, 20, first_cstring, colormap);
        update_screen(first_menu, colormap);
        break;
      case 1:
        if(key == 13)
          return show_login_menu();
        colormap_from_string(32, 20, second_cstring, colormap);
        update_screen(second_menu, colormap);
        break;
      case 2:
        if(key == 13)
          return 0;
        colormap_from_string(32, 20, third_cstring, colormap);
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
  colormap_from_string(32, 20, first_reg_cstring, colormap);
  update_screen(regist, colormap);
  update_screen_string("          ",924);

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
        colormap_from_string(32, 20, first_reg_cstring, colormap);
        update_screen(NULL, colormap);
        
        if(!arrow_pressed && valid_id_char(key) && ID_index < 10)
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
        colormap_from_string(32, 20, second_reg_cstring, colormap);
        update_screen(NULL, colormap);
        
        if(!arrow_pressed && valid_id_char(key) && PWD_index < 10)
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
          marshal_packet(p, ID, 11, 0);
          marshal_packet(p, PWD, 11, 11);

          /* Send and receive data from the server */
          int recv_amount;
          send_once(p, &recv_amount);
          
          int account_created = 1;
          if(!pkt_isvalid(p) || p->buffer[0] == '0' || recv_amount == -1)
            account_created = 0;

          /* Free the packet structure */
          free_packet(p);

          /* Show success/fail, according to account_created */
          if(account_created)
            MessageBox(0, "Account created", "Dungeon of Pixels", 0);
          else
            MessageBox(0, "Fail to create an account", "Dungeon of Pixels", 0);

          return show_menu();
        }
        colormap_from_string(32, 20, third_reg_cstring, colormap);
        update_screen(NULL, colormap);
        break;
    }

    key = getch();
  }

  return 0;
}

static show_login_menu(void)
{
  char ID[11] = "\0\0\0\0\0\0\0\0\0\0\0";
  char PWD[11] = "\0\0\0\0\0\0\0\0\0\0\0";
  int ID_index = 0;
  int PWD_index = 0;

  /* Show initial_screen */
  colormap_from_string(32, 20, first_reg_cstring, colormap);
  update_screen(login, colormap);
  update_screen_string("          ",924);

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
        colormap_from_string(32, 20, first_reg_cstring, colormap);
        update_screen(NULL, colormap);
        
        if(!arrow_pressed && valid_id_char(key) && ID_index < 10)
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
        colormap_from_string(32, 20, second_reg_cstring, colormap);
        update_screen(NULL, colormap);
        
        if(!arrow_pressed && valid_id_char(key) && PWD_index < 10)
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
          /* Send server login request */
          struct packet* p = init_packet(6);

          /* Marshal data to the packet */
          marshal_packet(p, ID, 11, 0);
          marshal_packet(p, PWD, 11, 11);

          /* Send and receive data from the server */
          int recv_amount;
          send_once(p, &recv_amount);
          
          int loggedin = 1;
          if(!pkt_isvalid(p) || p->buffer[0] == '0' || recv_amount == -1 || p->header != 7)
            loggedin = 0;

          /* Save user id */
          int uid = *(int *)(p->buffer+1);

          /* Free the packet structure */
          free_packet(p);

          /* Show success/fail, according to loggedin */
          if(loggedin)
          {
            set_user_index(uid);
            return 1;
          }
          else
            MessageBox(0, "Failed to log in", "Dungeon of Pixels", 0);

          return show_menu();
        }
        colormap_from_string(32, 20, third_reg_cstring, colormap);
        update_screen(NULL, colormap);
        break;
    }

    key = getch();
  }

  return 0;
}