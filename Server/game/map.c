#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "../lib/lib.h"

#define MAX_STRLEN 1500

struct map* map_load_data(char *map_id)
{
  /* Change directory */
  chdir("./data/maps");

  /* Parsing buffers */
  char line_buffer[MAX_STRLEN];
  char* geo_temp;
  char* color_temp;
  int portal_index = 0;
  int monster_index = 0;

  /* Open File */
  FILE *map_file = fopen(map_id,"r");

  /* Parsing mode */
  int mode = 0;  

  /* Allocate memory for map data */
  struct map *map = (struct map *)malloc(sizeof(struct map));

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
      geo_temp = map->geo;
    }
    else if(mode == 2)
    {
      /* Mode 2 : geometry of the map */

      memcpy(geo_temp, line_buffer, map->width * 2);
      geo_temp = geo_temp + map->width * 2;
    }
    else if(mode == 3)
    {
      /* Color map will not be parsed on server side */
    }
    else if(mode == 4)
    {
      char* token = strtok(line_buffer, ",");
      map->portals[portal_index].x_pos = strn_to_int(token, 3);
      token = strtok(NULL, ",");
      map->portals[portal_index].y_pos = strn_to_int(token, 3);
      token = strtok(NULL, ",");
      map->portals[portal_index].dest_map_id = strn_to_int(token, 4);
      token = strtok(NULL, ",");
      map->portals[portal_index].dest_x_pos = strn_to_int(token, 3);
      token = strtok(NULL, ",");
      map->portals[portal_index].dest_y_pos = strn_to_int(token, 3);
      portal_index++;
    }
    else if(mode == 5)
    {
      char* token = strtok(line_buffer, ",");
      map->spwn_pts[monster_index].x_pos = strn_to_int(token, 3);
      token = strtok(NULL, ",");
      map->spwn_pts[monster_index].y_pos = strn_to_int(token, 3);
      token = strtok(NULL, ",");
      map->spwn_pts[monster_index].monster_id = strn_to_int(token, 4);
      monster_index++;
    }
  }
  map->portal_num = portal_index;
  map->monster_num = monster_index;

  /* Close map file */
  fclose(map_file);

  /* Change directory */
  chdir("../../");

  return map;
}