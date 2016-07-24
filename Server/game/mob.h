#ifndef _MOB_H_
#define _MOB_H_

struct mob
{
  int id;
  char name[11];
  char sprite[2];
  unsigned short color;
  unsigned short hp;
  unsigned short str;
  unsigned short def;
};

void init_mob(void);
void clear_mob_data(void);
struct mob* load_mob_data(int);

#endif