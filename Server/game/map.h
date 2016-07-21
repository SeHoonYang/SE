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
  int x_pos;
  int y_pos;
  int monster_id;
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