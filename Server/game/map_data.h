#ifndef _MAP_DATA_H_
#define _MAP_DATA_H_

#include "../lib/list.h"
#include "map.h"

/*

   Map data structure. It includes

   1. Map data
   2. width/height
   3. User data (linked list/hash)
   4. Monster data (array) and max index 
   5. Monster spawn counter // Not implemented yet(low priority)
   6. Protal data (array) and max index 

   map index is excluded since the array will be indexed by it.

*/

struct map_data
{
  struct map* map;
  struct monster_spwn monster_spawned[MAX_MONSTERSPWN];
  struct list user_data;
};

struct portal* on_portal(int, int, int);
int movable(int, int, int);
void load_maps(void);
void get_map_status(int, char *);
void add_user_to_map(int, int);
void rem_user_from_map(int, int);

#endif