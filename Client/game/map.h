#ifndef _MAP_H_
#define _MAP_H_

#define MAX_PORTALS 20
#define MAX_MONSTERSPWN 10

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
  char geo[32*20*2+1];
  char cgeo[32*20*2*3+1];
  struct portal portals[MAX_PORTALS];
  struct monster_spwn spwn_pts[MAX_MONSTERSPWN];
};

struct map* map_load_data(char *map_id);

#endif