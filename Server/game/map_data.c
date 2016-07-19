#include "map_data.h"
#include "../lib/lib.h"
#include "../usr/usr.h"

static struct map_data map_data_array[MAX_MAP];

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
}

void rem_user_to_map(int mid, int uid)
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
  struct list_elem* e;

  char num_obj = 0;
  for(e = list_begin(user_list); e != list_end(user_list); e = list_next(e))
  {
    struct user_data* d = get_user_data(*(int *)(e->conts));

    strncpy(buff+1+num_obj*19, d->id, 11);
    memcpy(buff+12+num_obj*19, &d->user_index, 4);
    memcpy(buff+16+num_obj*19, &d->x, 2);
    memcpy(buff+18+num_obj*19, &d->y, 2);

    num_obj = num_obj + 1;
  }
  buff[0] = num_obj;
}