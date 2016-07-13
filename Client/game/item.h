#ifndef _ITEM_H_
#define _ITEM_H_

struct item
{
  int index;
  int price;
};

struct item* load_item(char *);
void add_item(int,int);
void sub_item(int,int);

#endif