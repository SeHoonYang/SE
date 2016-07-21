#include <fcntl.h>
#include "usr.h"
#include "direct.h"
#include "../lib/list.h"
#include "../game/map_data.h"

static int _min(int l, int r)
{
  return r < l ? r : l;
}

static int _max(int l, int r)
{
  return r < l ? l : r;
}

/* It would be better with hash */
static struct list user_list;

void release_user_data(int uid)
{
  struct list_elem* e;
  struct list_elem* prev = &user_list.head;
  int mid;

  for(e = list_begin(&user_list); e != list_end(&user_list); e = list_next(e))
  {
    if(((struct user_data*)e->conts)->user_index == uid)
    {
      mid = ((struct user_data*)e->conts)->map_id;
      break;
    }
  }

  rem_user_from_map(mid, uid);

  for(e = list_begin(&user_list); e != list_end(&user_list); e = list_next(e))
  {
    if(((struct user_data*)e->conts)->user_index == uid)
    {
      prev->next = e->next;
      free(e->conts);
      free(e);
      break;
    }
    prev = e;
  }
}

int create_account(char * ID, char * PWD)
{
  chdir("./data/userdata");

  /* ID already exists */
  if(open(ID,O_RDONLY) != -1)
    return 0;

  /* Create an account */
  int fd = open(ID, O_CREAT | O_RDWR);

  /* Write basic user data */
  write(fd, PWD, strlen(PWD));
  write(fd, "\n0", 2);
  write(fd, "\n10 11", 6);
  write(fd, "\n10 5", 5);
  write(fd, "\n", 1);
  
  close(fd);

  return 1;
}

void init_user_data()
{
  init_list(&user_list);
}

int load_user_data(char* ID, int idx, int mid, unsigned pos, unsigned h)
{
  /* Actually, we need to check whether the player has already logged in or not */
  struct list_elem* e;
  for(e = list_begin(&user_list); e != list_end(&user_list); e = list_next(e))
  {
    if(!strcmp(((struct user_data*)e->conts)->id,ID))
      return -1;
  }

  /* Create user data */
  struct user_data *d = (struct user_data *)malloc(sizeof(struct user_data));
  strncpy(d->id, ID, 11);
  d->user_index = idx;
  d->map_id = mid;
  d->x = pos % 65536;
  d->y = pos / 65536;
  d->hp = h % 65536;
  d->mp = h / 65536;

  printf("User data has been loaded : map #%d (%d, %d) hp:%d mp:%d\n", d->map_id, d->x, d->y, d->hp, d->mp);

  /* Add to the list */
  push_list(&user_list, d);

  return 0;
}

void save_user_data(int uid)
{
  /* Save specific user data */
  return;
}

void save_users_data()
{
  /* Save entire user data to the file system */
  return;
}

void clear_user_data()
{
  struct list_elem* e;

  for(e = list_begin(&user_list);e != list_end(&user_list);e = list_next(e))
    free(e->conts);

  clear_list(&user_list);
}

void update_user_location(int idx, char key)
{
  struct list_elem* e;
  for(e = list_begin(&user_list); e != list_end(&user_list); e = list_next(e))
  {
    struct user_data* d = ((struct user_data*)e->conts);

    if(d->user_index == idx)
    {
      switch(key)
      {
        case 75:
          if(movable(d->map_id, d->x-1, d->y))
            d->x--;
          break;
        case 77:
          if(movable(d->map_id, d->x+1, d->y))
            d->x++;
          break;
        case 72:
          if(movable(d->map_id, d->x, d->y-1))
            d->y--;
          break;
        case 80:
          if(movable(d->map_id, d->x, d->y+1))
            d->y++;
          break;
      }

      struct portal* next_map = on_portal(d->map_id, d->x, d->y);

      if(next_map != NULL)
      {
        rem_user_from_map(d->map_id, d->user_index);
        add_user_to_map(next_map->dest_map_id, d->user_index);

        d->map_id = next_map->dest_map_id;
        d->x =  next_map->dest_x_pos;
        d->y =  next_map->dest_y_pos;
      }
      break;
    }
  }
}

int get_user_map_id(int idx)
{
  struct list_elem* e;
  for(e = list_begin(&user_list); e != list_end(&user_list); e = list_next(e))
  {
    if(((struct user_data*)e->conts)->user_index == idx)
    {
      return ((struct user_data*)e->conts)->map_id;
    }
  }

  return -1;
}

struct user_data* get_user_data(int idx)
{
  struct list_elem* e;
  for(e = list_begin(&user_list); e != list_end(&user_list); e = list_next(e))
  {
    if(((struct user_data*)e->conts)->user_index == idx)
    {
      return (struct user_data*)e->conts;
    }
  }

  return NULL;
}