#ifndef _MOB_H_
#define _MOB_H_

/* MOB file structure

#MOB NAME (10 byte, char)
#MOB SPRITE (2 byte, char)
#COLOR (2 byte, int)
#HP (2 byte, int)
#STR (2 byte, int)
#DEF (2 byte, int)
#REWARD (2 byte, int)
#EXP (4 byte, int)

*/

struct mob
{
  int id;
  char name[11];
  char sprite[2];
  unsigned short color;
  unsigned short hp;
  unsigned short str;
  unsigned short def;
  unsigned short reward;
  int exp;
};

void init_mob(void);
void clear_mob_data(void);
struct mob* load_mob_data(int);

#endif