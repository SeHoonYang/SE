#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "../lib/lib.h"
#include "../lib/list.h"

#define ELEM_NUM 5
#define MAX_STRLEN 1800
#define MAX_MAP_SIZE 200*200*2*5

static struct list map_list;

struct map* load_map(int mid)
{
  /* Search the list */
  struct list_elem* e;
  for(e = list_begin(&map_list); e != list_end(&map_list); e = list_next(e))
  {
    if(((struct map*)(e->conts))->map_id == mid)
      return (struct map*)(e->conts);
  }

  /* Load map from the file */
  char* mid_str = int_to_str(mid);
  struct map* new_map = map_load_data(mid_str);
  free(mid_str);

  /* Add map to the list */
  push_list(&map_list, new_map);

  return new_map;
}

void init_map_list()
{
  init_list(&map_list);
}

struct map* map_load_data(char *map_id)
{
  /* Change directory */
  chdir("./data/maps");

  /* Parsing buffers */
  char line_buffer[MAX_STRLEN];
  char* geo_temp;
  char* color_temp;
  char* color_last_written;

  /* Open File */
  FILE *map_file = fopen(map_id,"r");

  /* Parsing mode */
  int mode = 0;  

  /* Allocate memory for map data */
  struct map *map = (struct map *)malloc(sizeof(struct map));
  map->map_id = strn_to_int(map_id, 5);

  /* While meet last line of the map */
  while(mode != 6)
  {
    fgets(line_buffer, MAX_STRLEN, map_file);

    /* Meet # sign */
    if(line_buffer[0] == '#')
    {
      mode++;
      continue;
    }

    /* Parsing file */
    if(mode == 1)
    {
      /* Mode 1 : width, height */

      char* w = strtok(line_buffer, " ");
      char* h = strtok(NULL, " ");

      map->width = strn_to_int(w,3);
      map->height = strn_to_int(h,3);

      map->geo = (char *)malloc(map->width * map->height * 2 + 1);
      map->cgeo = (color *)malloc(map->width * map->height * 2 * sizeof(color) + 1);

      geo_temp = map->geo;
      color_temp = (char *)malloc(map->width * map->height * 6 + 1);
      color_last_written = color_temp;
    }
    else if(mode == 2)
    {
      /* Mode 2 : geometry of the map */

      memcpy(geo_temp, line_buffer, map->width * 2);
      geo_temp = geo_temp + map->width * 2;
    }
    else if(mode == 3)
    {
      /* Mode 3 : color of the map */

      memcpy(color_last_written, line_buffer, map->width * 6);
      color_last_written = color_last_written + map->width * 6;
    }
    else if(mode == 4)
    {
      /* Portal does not needs to be parsed on the client side */
    }
    else if(mode == 5)
    {
      /* Monsters does not needs to be parsed on the client side */
    }
  }

  colormap_from_string(map->width, map->height, color_temp, map->cgeo);
  free(color_temp);

  /* Close map file */
  fclose(map_file);

  /* Change directory */
  chdir("../../");

  return map;
}