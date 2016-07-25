#include <stdio.h>
#include <time.h>
#include "map_data.h"
#include "../lib/lib.h"
#include "../usr/usr.h"

static struct map_data map_data_array[MAX_MAP];
static int closed;

void stop_mob_manager()
{
  closed = 1;
}

/* Thread that manage monsters */
void mob_manager()
{
  while(!closed)
  {
    Sleep(1000);
    int current_tick = (int)clock();

    for(int i = 0; i < MAX_MAP; ++i)
    {
      int max_mobs = map_data_array[i].map->monster_num;
      for(int j = 0; j < max_mobs; ++j)
      {
        struct monster_spwn* mob = &map_data_array[i].map->spwn_pts[j];

        if(mob->spawned == 1 && rand() % 6 == 0)
        {
          int temp_x = mob->x_pos + (rand() % 3  - 1);
          int temp_y = mob->y_pos + (rand() % 3  - 1);

          if(movable(i,temp_x,temp_y))
          {
            mob->x_pos = (unsigned short)temp_x;
            mob->y_pos = (unsigned short)temp_y;
          }
        }

        if(mob->spawned == 0 && current_tick - mob->timer > 10000)
        {
          /* Spawn mob */
          mob->spawned = 1;
          mob->x_pos = mob->base_x_pos;
          mob->y_pos = mob->base_y_pos;
          mob->current_hp = mob->max_hp;
        }
      }
    }
  }
}

struct portal* on_portal(int mid, int x, int y)
{
  int max_portal = map_data_array[mid].map->portal_num;
  for(int i = 0; i < max_portal; ++i)
  {
    if(map_data_array[mid].map->portals[i].x_pos == x && map_data_array[mid].map->portals[i].y_pos == y)
      return &map_data_array[mid].map->portals[i];
  }

  return NULL;
}

int movable(int mid, int x, int y)
{
  /* Check boundary */
  if(x < 0 || x >= map_data_array[mid].map->width)
    return 0;
  else if(y < 0 || y >= map_data_array[mid].map->height)
    return 0;

  char next_block_1 = (map_data_array[mid].map->geo)[map_data_array[mid].map->width * 2 * y + x * 2];
  char next_block_2 = (map_data_array[mid].map->geo)[map_data_array[mid].map->width * 2 * y + x * 2 + 1];

  char* square = "бр";
  char* square_fill = "бс";

  if(next_block_1 == square[0] && next_block_2 == square[1])
    return 0;
  else if(next_block_1 == square_fill[0] && next_block_2 == square_fill[1])
    return 0;

  return 1;
}

/* Load map datas on the cache */
void load_maps()
{
  for(int i = 0; i < MAX_MAP; ++i)
  {
    char* str = int_to_str(i);
    map_data_array[i].map = map_load_data(str);
    init_list(&map_data_array[i].user_data);
    free(str);
    printf("  Map : #%d has been loaded on the memory\n", i);
  }
}

void add_user_to_map(int mid, int uid)
{
  int* ud = (int *)malloc(4);
  *ud = uid;

  push_list(&map_data_array[mid].user_data, ud);
  printf("%d users are in the map #%d\n", list_size(&map_data_array[mid].user_data), mid);
}

void rem_user_from_map(int mid, int uid)
{
  struct list_elem* e;
  for(e = list_begin(&map_data_array[mid].user_data); e != list_end(&map_data_array[mid].user_data); e = list_next(e))
  {
    if(*(int *)(e->conts) == uid)
    {
      free(e->conts);
      remove_list(&map_data_array[mid].user_data, e->conts);
      return;
    }
  }
}

/* Get map status */
void get_map_status(int mid, char* buff)
{
  struct list* user_list = &map_data_array[mid].user_data;
  int max_mobs = map_data_array[mid].map->monster_num;

  struct list_elem* e;
  char num_obj = 0;

  /* Add users to packet */
  for(e = list_begin(user_list); e != list_end(user_list); e = list_next(e))
  {
    struct user_data* d = get_user_data(*(int *)(e->conts));

    strncpy(buff+2+(int)num_obj*19, d->id, 11);
    memcpy(buff+13+(int)num_obj*19, &d->user_index, 4);
    memcpy(buff+17+(int)num_obj*19, &d->x, 2);
    memcpy(buff+19+(int)num_obj*19, &d->y, 2);

    num_obj = num_obj + 1;
  }

  /* Add monsters to packet */
  for(int i = 0; i < max_mobs; ++i)
  {
    memcpy(buff + 2 + 16 * 19 + i * 8, (char *)&map_data_array[mid].map->spwn_pts[i].id, 4);
    memcpy(buff + 2 + 16 * 19 + 4 + i * 8, (char *)&map_data_array[mid].map->spwn_pts[i].x_pos, 2);
    memcpy(buff + 2 + 16 * 19 + 6 + i * 8, (char *)&map_data_array[mid].map->spwn_pts[i].y_pos, 2);

    num_obj = num_obj + 16;
  }

  buff[0] = (char)mid;
  buff[1] = num_obj;
}

void clear_map_data()
{
  for(int i = 0; i < MAX_MAP; ++i)
  {
    free(map_data_array[i].map);
    struct list_elem* e;

    for(e = list_begin(&map_data_array[i].user_data); e != list_end(&map_data_array[i].user_data); e = list_next(e))
      free(e->conts);

    clear_list(&map_data_array[i].user_data);
  }
}