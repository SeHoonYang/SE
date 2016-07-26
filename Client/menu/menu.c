#include <stdio.h>
#include <windows.h>
#include "menu.h"
#include "menu.inc"
#include "../console/cons.h"
#include "../console/color.h"
#include "../conf.inc"
#include "../network/nwking.h"

static int hp;
static int max_hp;
static int mp;
static int max_mp;
static int str;
static int def;
static int money;
static int level;
static int exp;
static int stat_point;
static char ingame_menu_buffer[32*20*2+1];
static int updated;

void set_user_data_menu(int _hp, int _max_hp, int _mp, int _max_mp, int _str, int _def, int _money, int _level, int _exp, int _stat_point)
{
  hp = _hp;
  max_hp = _max_hp;
  mp = _mp;
  max_mp = _max_mp;
  str = _str;
  def = _def;
  money = _money;
  level = _level;
  exp = _exp;
  stat_point = _stat_point;
  updated = 1;
}

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

int show_game_menu()
{
  int menu_index = 0;
  char* ingame_menu;
  char* ingame_menu_cstring;

  while(1)
  {
    /* Synchronize does not needed since file system does it internally */

    while(!updated);

    ingame_menu = menu_index == 0 ? ingame_menu0 : menu_index == 1 ? ingame_menu1 : ingame_menu2;
    ingame_menu_cstring = menu_index == 0 ? ingame_menu_cstring0 : menu_index == 1 ? ingame_menu_cstring1 : ingame_menu_cstring2;

    /* show menu screen */
    colormap_from_string(32, 20, ingame_menu_cstring, colormap);
    memcpy(ingame_menu_buffer, ingame_menu, 32*20*2);
    update_screen(ingame_menu_buffer, colormap);

    char* hp_str = (char *)int_to_str(hp);
    char* max_hp_str = (char *)int_to_str(max_hp);
    char* mp_str = (char *)int_to_str(mp);
    char* max_mp_str = (char *)int_to_str(max_mp);
    char* money_str = (char *)int_to_str(money);
    char* str_str = (char *)int_to_str(str);
    char* def_str = (char *)int_to_str(def);
    char* level_str = (char *)int_to_str(level);
    char* exp_str = (char *)int_to_str(exp);

    /* Show HP/MP string */
    memcpy(ingame_menu_buffer + 153, hp_str, strlen(hp_str));
    memcpy(ingame_menu_buffer + 187 - strlen(max_hp_str), max_hp_str, strlen(max_hp_str));
    memcpy(ingame_menu_buffer + 217, mp_str, strlen(mp_str));
    memcpy(ingame_menu_buffer + 251 - strlen(max_mp_str), max_mp_str, strlen(max_mp_str));

    /* HP/MP color */
    int n_hp = 18 * hp / max_hp;
    int n_mp = 18 * mp / max_mp;

    for(int i = 0; i < n_hp; ++i)
    {
      colormap[187 - 2 * i].bgcolor = 12;
      colormap[186 - 2 * i].bgcolor = 12;
    }
    for(int i = n_hp; i < 18; ++i)
    {
      colormap[187 - 2 * i].bgcolor = 4;
      colormap[186 - 2 * i].bgcolor = 4;
    }
    for(int i = 0; i < n_mp; ++i)
    {
      colormap[251 - 2 * i].bgcolor = 9;
      colormap[250 - 2 * i].bgcolor = 9;
    }
    for(int i = n_mp; i < 18; ++i)
    {
      colormap[251 - 2 * i].bgcolor = 1;
      colormap[250 - 2 * i].bgcolor = 1;
    }

    /* Show money string */
    memcpy(ingame_menu_buffer + 378 - strlen(money_str), money_str, strlen(money_str));

    /* Show str/def string */
    memcpy(ingame_menu_buffer + 508 - strlen(def_str), def_str, strlen(def_str));
    memcpy(ingame_menu_buffer + 487 - strlen(str_str), str_str, strlen(str_str));

    /* Show level string */
    memcpy(ingame_menu_buffer + 1115 - strlen(level_str), level_str, strlen(level_str));

    /* Show exp string */
    memcpy(ingame_menu_buffer + 1119, exp_str, strlen(exp_str));

    char* max_exp_str = (char *)int_to_str(level * level * 10);    

    memcpy(ingame_menu_buffer + 1147 - strlen(max_exp_str), max_exp_str, strlen(max_exp_str));

    /* Color for exp */
    int n_exp = 15 * exp / (level * level * 10);

    for(int i = 0; i < 15 - n_exp; ++i)
    {
      colormap[1118 + 2 * i].bgcolor = 2;
      colormap[1119 + 2 * i].bgcolor = 2;
    }
    for(int i = 15 - n_exp; i < 15; ++i)
    {
      colormap[1118 + 2 * i].bgcolor = 10;
      colormap[1119 + 2 * i].bgcolor = 10;
    }

    free(hp_str);
    free(max_hp_str);
    free(mp_str);
    free(max_mp_str);
    free(money_str);
    free(str_str);
    free(def_str);
    free(level_str);
    free(exp_str);
    free(max_exp_str);

    char key = getch();
    if(key == 27)
    {
      updated = 0;
      return;
    }
    else if(key == 72)
    {
      menu_index = _max(0, menu_index - 1);
    }
    else if(key == 80)
    {
      menu_index = _min(2, menu_index + 1);
    }
    else if(key == 13)
    {
      if(menu_index == 0)
      {
        /* Inventory */
      }
      else if(menu_index == 1)
      {
        /* Stat */
      }
      else if(menu_index == 2)
      {
        return 1;
      }
    }
  }
}