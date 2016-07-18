#include "map_data.h"
#include "../lib/lib.h"

static struct map_data map_data_array[MAX_MAP];

/* Load map datas on the cache */
void load_maps()
{
  for(int i = 0; i < MAX_MAP; ++i)
  {
    char* str = int_to_str(i);
    map_data_array[i].map = map_load_data(str);
    init_list(&map_data_array[i].user_data);
    free(str);
    printf("  Map : #%d has been loaded on the memory\n", i);
  }
}