#ifndef _MAP_H_
#define _MAP_H_

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
  int height;
  int width;
  char geo[32*20*2+1];
  char cgeo[32*20*2*3+1];
  int portal_num;
  int monster_num;
  struct portal portals[MAX_PORTALS];
  struct monster_spwn spwn_pts[MAX_MONSTERSPWN];
};

struct map* map_load_data(char *map_id);

#endif