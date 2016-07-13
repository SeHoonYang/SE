#include "item.h"
#include "../lib/list.h"

static struct list inventory;

void init_item()
{
  init_list(&inventory);
}

struct item* load_item(int item_id)
{
  return 0;
}

void add_item(int id, int d)
{
  /* Inventory iteration */
  struct list_elem* e;
  for(e = list_begin(&inventory); e != list_end(&inventory); e = list_next(e))
  {
    /* Already have item */
    if (((struct item_in_memory*)(e->conts))->index == id)
    {
      ((struct item_in_memory*)(e->conts))->num += d;
      return;
    }
  }

  /* Don't have the item then add new item */
  struct item_in_memory* new_item_inm = (struct item_in_memory*)malloc(sizeof(struct item_in_memory));

  new_item_inm->index = id;
  new_item_inm->num = d;

  push_list(&inventory, new_item_inm);
}

void sub_item(int id, int d)
{
  /* Inventory iteration */
  struct list_elem* e;
  for(e = list_begin(&inventory); e != list_end(&inventory); e = list_next(e))
  {
    /* Have item */
    if (((struct item_in_memory*)(e->conts))->index == id)
    {
      ((struct item_in_memory*)(e->conts))->num -= d;

      /* If item count -> 0, remove from the inventory */
      if(((struct item_in_memory*)(e->conts))->num == 0)
      {
        free(e->conts);
        remove_list(&inventory, e->conts);
      }

      return;
    }
  }
}

int have_item(int id, int d)
{
  /* Inventory iteration */
  struct list_elem* e;
  for(e = list_begin(&inventory); e != list_end(&inventory); e = list_next(e))
  {
    /* Have item */
    if (((struct item_in_memory*)(e->conts))->index == id)
    {
      return ((struct item_in_memory*)(e->conts))->num >= d;
    }
  }

  return 0;
}

void free_inventory()
{
  /* Inventory iteration */
  struct list_elem* e;
  for(e = list_begin(&inventory); e != list_end(&inventory); e = list_next(e))
  {
    /* Free item_in_memory structures */
    free(e->conts);
  }

  clear_list(&inventory);
}