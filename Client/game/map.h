#ifndef _MAP_H_
#define _MAP_H_

#include "../console/color.h"
#include "../conf.inc"

struct map
{
  int map_id;
  int height;
  int width;
  char* geo;
  color* cgeo;
};

void init_map_list(void);
struct map* load_map(int);
struct map* map_load_data(char *);

#endif