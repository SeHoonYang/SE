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
  struct list user_data;
};

void stop_mob_manager(void);
void mob_manager(void);
struct monster_spwn* on_monster(int, int, int);
struct portal* on_portal(int, int, int);
int movable(int, int, int);
void load_maps(void);
void get_map_status(int, char *);
void add_user_to_map(int, int);
void rem_user_from_map(int, int);
void clear_map_data(void);

#endif