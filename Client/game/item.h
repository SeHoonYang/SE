#ifndef _ITEM_H_
#define _ITEM_H_

struct item
{
  int index;
  int price;
}

// Inventory will be implemented with doubly linked list maybe?

struct item* load_item(char *);
void add_item(int,int);
void sub_item(int,int);
void free_items(void);

#endif