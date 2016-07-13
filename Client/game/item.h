#ifndef _ITEM_H_
#define _ITEM_H_

struct item
{
  int category;
  int index;
  int price;
};

struct item_in_memory
{
  int index;
  int num;
};

void init_item(void);
struct item* load_item(int);
void add_item(int, int);
void sub_item(int, int);
int have_item(int, int);

#endif