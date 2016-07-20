#ifndef _MAP_H_
#define _MAP_H_

#include "../console/color.h"
#include "../conf.inc"

struct portal
{
  int x_pos;
  int y_pos;
  int dest_map_id;
};

struct monster_spwn
{
  int x_pos;
  int y_pos;
  int monster_id;
};

struct map
{
  int map_id;
  int height;
  int width;
  char* geo;
  color* cgeo;
  int portal_num;
  int monster_num;
  struct portal portals[MAX_PORTALS];
  struct monster_spwn spwn_pts[MAX_MONSTERSPWN];
};

void init_map_list(void);
struct map* load_map(int);
struct map* map_load_data(char *);

#endif