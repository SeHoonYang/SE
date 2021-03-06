#include <time.h>
#include "nwking.h"
#include "ysock.h"
#include "packet.h"
#include "../console/cons.h"
#include "../console/color.h"
#include "../lib/list.h"
#include "../game/map.h"
#include "../menu/menu.h"
#include "../game/mob.h"

#define PERIOD 40

static int _min(int r, int l)
{
  return r < l ? r : l;
}

static int _max(int r, int l)
{
  return r < l ? l : r;
}

static char map_buffer[32*20*2+1];
static color color_buffer[32*20*2*sizeof(color)+1];
static int user_index;
static SOCKET client_socket;
static int port;
static char* host;
static char* data;
static int closed;
static int timer = -1001;
static int enemy_hp;
static char* enemy_name;
static unsigned short enemy_color;

void set_user_index(int i)
{
  user_index = i;
}

void init_network(char* _host, int _port, char* _data)
{
  /* Initialize the socket */
  init_socket(sizeof(struct packet));

  host = _host;
  port = _port;
  data = _data;
  closed = 0;
}

void request_server_make_thread()
{
  struct packet *p = init_packet(8);

  connect_client(&client_socket, port, host);

  send(client_socket, (char *)p, sizeof(struct packet), 0);
  /* Just for consistency */
  recv(client_socket, (char *)p, sizeof(struct packet), 0);

  free(p);
}

struct packet* send_once(struct packet* p, int* recv_amount)
{
  connect_client(&client_socket, port, host);
  send(client_socket, (char *)p, sizeof(struct packet), 0);
  *recv_amount = recv(client_socket, (char *)p, sizeof(struct packet), 0);
  close_socket(client_socket);
}

void send_input()
{
  while(!closed)
  {
    /* Enter : show menu */
    if(*data == 13)
    {
      struct packet *p = init_packet(9);
      marshal_packet(p, (char *)&user_index, 4, 0);

      send(client_socket, (char *)p, sizeof(struct packet), 0);
      recv(client_socket, (char *)p, sizeof(struct packet), 0);

      if(p->header == 10 && pkt_isvalid(p))
      {
        int hp = (int)*(unsigned short *)(p->buffer);
        int max_hp = (int)*(unsigned short *)(p->buffer+2);
        int mp = (int)*(unsigned short *)(p->buffer+4);
        int max_mp = (int)*(unsigned short *)(p->buffer+6);
        int str = (int)*(unsigned short *)(p->buffer+8);
        int def = (int)*(unsigned short *)(p->buffer+10);
        int money = (int)*(int *)(p->buffer+12);
        int level = (int)*(unsigned short *)(p->buffer+16);
        int exp = (int)*(int *)(p->buffer+18);
        int stat_point = (int)*(unsigned short *)(p->buffer+22);

        set_user_data_menu(hp,max_hp,mp,max_mp,str,def,money,level,exp,stat_point);
      }

      free(p);

      Sleep(PERIOD * 2);
      continue;
    }

    /* Keys to send are specified */
    if(*data != 75 && *data != 80 && *data != 72 && *data != 77)
      *data = 0;

    /* Create packet */
    struct packet *p = init_packet(3);
    marshal_packet(p, data, 1, 0);
    marshal_packet(p, (char *)&user_index, 4, 1);

    send(client_socket, (char *)p, sizeof(struct packet), 0);
    recv(client_socket, (char *)p, sizeof(struct packet), 0);

    /* Analyze the server response */
    if((p->header == 4 || p->header == 5) && pkt_isvalid(p))
    {
      int map_id = (int)p->buffer[0];
      int obj_num = (int)p->buffer[1];

      int user_num = obj_num % 16;
      int mob_num = obj_num / 16;

      int id = 0;
      struct list others;
      init_list(&others);

      /* Split packet by each object */
      for(int i = 0; i < user_num; ++i)
      {
        if(*(int *)(p->buffer+13+i*19) == user_index)
          id = i;
        else
        {
          int* ti = (int *)malloc(4);
          *ti = i;
          push_list(&others,ti);
        }
      }

      int x = (int)(*(unsigned short *)(p->buffer+17+id*19));
      int y = (int)(*(unsigned short *)(p->buffer+19+id*19));

      /* Set camera origin point */
      struct map* map = load_map(map_id);
      int o_x = _min(map->width-32,_max(0,x-15));
      int o_y = _min(map->height-20,_max(0,y-9));

      /* User position on the camera coordinate */
      int delta_x = x - o_x;
      int delta_y = y - o_y;

      /* Control concurrency */
      stop_printing();

      /* Set up background layer */
      for(int n = 0; n < 20; ++n)
        memcpy(map_buffer + n * 64, map->geo + (o_x + (o_y + n) * map->width) * 2, 64);

      for(int n = 0; n < 20; ++n)
        memcpy(color_buffer + n * 64, map->cgeo + (o_x + (o_y + n) * map->width) * 2, 64*2);

      /* Plot others */
      struct list_elem* e;
      for(e = list_begin(&others); e != list_end(&others); e = list_next(e))
      {
        int other_x = (int)(*(unsigned short *)(p->buffer+17+(*(int *)(e->conts))*19));
        int other_y = (int)(*(unsigned short *)(p->buffer+19+(*(int *)(e->conts))*19));

        /* If others in the screen */
        if(o_x <= other_x && o_x + 32 > other_x && o_y <= other_y && o_y + 20 > other_y)
        {
          char* other_name = p->buffer+2+(*(int *)(e->conts))*19;
          int name_len = strlen(other_name);

          /* Display user name */

/* buggy yet;
          for(int i = 0; i < name_len; ++i)
            if(o_x <= other_x -  name_len / 2 + 1 + i && other_x -  name_len / 2 + 1 + i < o_x + 32
            && o_y <= other_y - 1 && o_y + 20 > other_y - 1)
              memcpy(map_buffer + (other_y - 1 - o_y) * 32 * 2 + (other_x - o_x) * 2 - name_len / 2  + 1 + i, other_name + i, 1);
*/
          
          memcpy(map_buffer + (other_y - o_y) * 32 * 2 + (other_x - o_x) * 2, "��", 2);
        }
      }

      /* Plot mobs */

      for(int n = 0; n < mob_num; ++n)
      {
        /* Get mob information */
        int mob_id = *(int *)(p->buffer + 2 + 16 * 19 + n * 8);
        int mob_x = (int)(*(unsigned short *)(p->buffer + 2 + 16 * 19 + 4 + n * 8));
        int mob_y = (int)(*(unsigned short *)(p->buffer + 2 + 16 * 19 + 6 + n * 8));

        if(o_x <= mob_x && o_x + 32 > mob_x && o_y <= mob_y && o_y + 20 > mob_y)
        {
          /* Load map data */
          struct mob* monster = load_mob_data(mob_id);

          memcpy(map_buffer + (mob_y - o_y) * 32 * 2 + (mob_x - o_x) * 2, monster->sprite, 2);
          color_buffer[(mob_y - o_y) * 32 * 2 + (mob_x - o_x) * 2].textcolor = (char)monster->color;
          color_buffer[(mob_y - o_y) * 32 * 2 + (mob_x - o_x) * 2 + 1].textcolor = (char)monster->color;
        }
      }

      /* Plot user */
      memcpy(map_buffer + delta_y * 32 * 2 + delta_x * 2, "��",2);

      /* Clear list */
      for(e = list_begin(&others); e != list_end(&others); e = list_next(e))
      {
        free(e->conts);
      }
      clear_list(&others);

      if(p->header == 5)
      {
        timer = clock();
        enemy_hp = (int)*(unsigned short *)(p->buffer + BUFFER_SIZE - 2);
        int enemy_index = *(int *)(p->buffer + BUFFER_SIZE - 6);
        struct mob* enemy = load_mob_data(enemy_index);
        enemy_name = enemy->name;
        enemy_color = enemy->color;
      }

      if(clock() - timer < 1000)
      {
        /* Display hp bars */
        memcpy(map_buffer      , "��������",14);
        memcpy(map_buffer +  64, "��          ��",14);
        memcpy(map_buffer + 128, "��������",14);
        memcpy(map_buffer + 192, "��HP :      ��",14);
        memcpy(map_buffer + 256, "��������",14);
        memcpy(map_buffer + 66, enemy_name, strlen(enemy_name));

        /* Display hp */
        char* enemy_hp_str = (char *)int_to_str(enemy_hp);
        memcpy(map_buffer + 204 - strlen(enemy_hp_str), enemy_hp_str, strlen(enemy_hp_str));

        /* Change color, frame : white, enemy name : enemy color */
        for(int i = 0; i < 5; ++i)
        {
          for(int j = 0; j < 7; ++j)
          {
            color_buffer[i*64 + j * 2].textcolor = 15;
            color_buffer[i*64 + j * 2 + 1].textcolor = 15;
            if(0 < j && j < 6 && i == 1)
            {
              color_buffer[i*64 + j * 2].textcolor = enemy_color;
              color_buffer[i*64 + j * 2 + 1].textcolor = enemy_color;
            }
          }
        }

        free(enemy_hp_str);
      }

      /* Update screen, actually do nothing except first call of this function */
      update_screen(map_buffer, color_buffer);
      resume_printing();
    }

    free(p);
    *data = 0;

    Sleep(PERIOD);
  }
}

void close_network()
{
  closed = 1;
  Sleep(PERIOD * 2);

  close_socket(client_socket);
  end_socket();
}

void stop_network()
{
  closed = 1;
}

void resume_network()
{
  closed = 0;
}