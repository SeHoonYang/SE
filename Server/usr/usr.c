#include <fcntl.h>
#include "usr.h"
#include "direct.h"
#include "../lib/list.h"

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

void load_user_data(char* ID, int mid, unsigned pos, unsigned h)
{
  /* Create user data */
  struct user_data *d = (struct user_data *)malloc(sizeof(struct user_data));
  strncpy(d->id, ID, 11);
  d->map_id = mid;
  d->x = pos % 65536;
  d->y = pos / 65536;
  d->hp = h % 65536;
  d->mp = h / 65536;

  printf("User data has been loaded : map #%d (%d, %d) hp:%d mp:%d\n", d->map_id, d->x, d->y, d->hp, d->mp);

  /* Actually, we need to check whether the player has already logged in or not */

  /* Add to the list */
  push_list(&user_list, d);
}

void clear_user_data()
{
  struct list_elem* e;

  for(e = list_begin(&user_list);e != list_end(&user_list);e = list_next(e))
    free(e->conts);

  clear_list(&user_list);
}