#include "nwking.h"
#include "ysock.h"
#include "packet.h"
#include "../console/cons.h"
#include "../console/color.h"
#include "../lib/list.h"
#include "../game/map.h"

static int _min(int r, int l)
{
  return r < l ? r : l;
}

static int _max(int r, int l)
{
  return r < l ? l : r;
}

#define FREQUENCY 30

static char map_buffer[32*20*2+1];
static color color_buffer[32*20*2*sizeof(color)+1];

static int user_index;
static SOCKET client_socket;
static int port;
static char* host;
static char* data;
static int closed;

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
    /* Keys to send are specified */
    if(*data != 75 && *data != 80 && *data != 72 && *data != 77)
      *data = 0;

    /* Create packet */
    struct packet *p = init_packet(3);
    marshal_packet(p, data, 1, 0);
    marshal_packet(p, (char *)&user_index, 4, 1);

    send(client_socket, (char *)p, sizeof(struct packet), 0);
    recv(client_socket, (char *)p, sizeof(struct packet), 0);

    /* Analyze the server responce */
    if(p->header == 4 && pkt_isvalid(p))
    {
      int map_id = (int)p->buffer[0];
      int obj_num = (int)p->buffer[1];

      int id = 0;
      struct list others;
      init_list(&others);

      /* Not implemented yet */
      for(int i = 0; i < obj_num; ++i)
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

      struct map* map = load_map(map_id);
      int o_x = _min(map->width-32,_max(0,x-15));
      int o_y = _min(map->height-20,_max(0,y-9));

      int delta_x = x - o_x;
      int delta_y = y - o_y;

      for(int n = 0; n < 20; ++n)
        memcpy(map_buffer + n * 64, map->geo + (o_x + (o_y + n) * map->width) * 2, 64);

      for(int n = 0; n < 20; ++n)
        memcpy(color_buffer + n * 64, map->cgeo + (o_x + (o_y + n) * map->width) * 2, 64*2);

      /* Plot others */
      struct list_elem* e;
      for(e = list_begin(&others); e != list_end(&others); e = list_next(e))
      {
        /* If others in the screen */
        if(o_x <= (int)(*(unsigned short *)(p->buffer+17+(*(int *)(e->conts))*19)) && o_x + 32 > (int)(*(unsigned short *)(p->buffer+17+(*(int *)(e->conts))*19)) &&
           o_y <= (int)(*(unsigned short *)(p->buffer+19+(*(int *)(e->conts))*19)) && o_y + 20 > (int)(*(unsigned short *)(p->buffer+19+(*(int *)(e->conts))*19)))
        {
          memcpy(map_buffer + ((int)(*(unsigned short *)(p->buffer+19+(*(int *)(e->conts))*19)) - o_y) * 32 * 2 + ((int)(*(unsigned short *)(p->buffer+17+(*(int *)(e->conts))*19)) - o_x) * 2, "¡ß",2);
        }
      }

      /* Plot user */
      memcpy(map_buffer + delta_y * 32 * 2 + delta_x * 2, "¡Þ",2);

      /* Clear list */
      for(e = list_begin(&others); e != list_end(&others); e = list_next(e))
      {
        free(e->conts);
      }
      clear_list(&others);

      update_screen(map_buffer, color_buffer);
    }

    free(p);
    *data = 0;

    Sleep(FREQUENCY);
  }
}

void close_network()
{
  closed = 1;
  Sleep(FREQUENCY);

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