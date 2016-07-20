#include <fcntl.h>
#include "usr.h"
#include "direct.h"
#include "../lib/list.h"

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
    if(((struct user_data*)e->conts)->user_index == idx)
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
    /* Skeleton */
    if(((struct user_data*)e->conts)->user_index == idx)
    {
      switch(key)
      {
        case 75:
          ((struct user_data*)e->conts)->x--;
          break;
        case 77:
          ((struct user_data*)e->conts)->x++;
          break;
        case 72:
          ((struct user_data*)e->conts)->y--;
          break;
        case 80:
          ((struct user_data*)e->conts)->y++;
          break;
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