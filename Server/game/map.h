#ifndef _MAP_H_
#define _MAP_H_

#include "../conf.inc"

typedef struct
{
  char bgcolor;
  char textcolor;
} color;

struct portal
{
  int x_pos;
  int y_pos;
  int dest_map_id;
  int dest_x_pos;
  int dest_y_pos;
};

struct monster_spwn
{
  int id;
  int timer;
  char name[11];
  char sprite[2];
  char spawned;
  unsigned short color;
  unsigned short base_x_pos;
  unsigned short base_y_pos;
  unsigned short x_pos;
  unsigned short y_pos;
  unsigned short current_hp;
  unsigned short max_hp;
  unsigned short str;
  unsigned short def;
  unsigned short reward;
  int exp;
};

struct map
{
  int height;
  int width;
  char* geo;
  int portal_num;
  int monster_num;
  struct portal portals[MAX_PORTALS];
  struct monster_spwn spwn_pts[MAX_MONSTERSPWN];
};

struct map* map_load_data(char *);

#endif