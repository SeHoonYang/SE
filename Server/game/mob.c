#include <stdio.h>
#include "mob.h"
#include "../lib/list.h"

static struct list mob_list;

void init_mob()
{
  init_list(&mob_list);
}

void clear_mob_data()
{
  struct list_elem* e;

  for(e = list_begin(&mob_list); e != list_end(&mob_list); e = list_next(e))
    free(e->conts);

  clear_list(&mob_list);
}

struct mob* load_mob_data(int mid)
{
  chdir("./../mobs/");

  struct list_elem* e;

  for(e = list_begin(&mob_list); e != list_end(&mob_list); e = list_next(e))
  {
    if(((struct mob *)(e->conts))->id == mid)
      return (struct mob *)(e->conts);
  }

  /* Load mob data from the file system */
  char* file_name = (char *)int_to_str(mid);
  struct mob* m = (struct mob *)malloc(sizeof(struct mob));
  char buffer[20];

  m->id = mid;

  FILE* f = fopen(file_name , "r");

  /* Mob name */
  fgets(buffer, 20, f);
  buffer[strlen(buffer)-1] = 0;
  memcpy(m->name, buffer, 11);

  /* Sprite */
  fgets(buffer, 20, f);
  buffer[strlen(buffer)-1] = 0;
  memcpy(m->sprite, buffer, 2);

  /* Color */
  fgets(buffer, 20, f);
  buffer[strlen(buffer)-1] = 0;
  m->color = (unsigned short)strn_to_int(buffer,20);

  /* HP */
  fgets(buffer, 20, f);
  buffer[strlen(buffer)-1] = 0;
  m->hp = (unsigned short)strn_to_int(buffer,20);

  /* STR */
  fgets(buffer, 20, f);
  buffer[strlen(buffer)-1] = 0;
  m->str = (unsigned short)strn_to_int(buffer,20);

  /* DEF */
  fgets(buffer, 20, f);
  buffer[strlen(buffer)-1] = 0;
  m->def = (unsigned short)strn_to_int(buffer,20);

  fclose(f);

  free(file_name);

  push_list(&mob_list, m);
  chdir("./../maps/");
  return m;
}