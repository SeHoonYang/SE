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
  char map_data[ELEM_NUM][MAX_STRLEN];
  char buf[MAX_STRLEN];
  char output[MAX_MAP_SIZE];

  /* Open File */
  FILE *map_file =fopen(map_id,"r");
  
  /* The map file does not exist */
  if (!map_file){
    printf("Error: %d (%s)\n", errno, strerror(errno));
    return NULL;
  }

  /* Reading map file */
  while (fgets(buf,MAX_STRLEN, map_file)!=NULL)
    strcat(output, buf);

  /* Close the file */
  fclose(map_file);

  /* Parsing formatted data */
  int i = 0;

  char *p = strtok(output, "#");
  while (p != NULL)
  {
    char output[MAX_MAP_SIZE] = "";
    strcpy(output, p);

    memmove(&output[0], &output[1], strlen(output));
    output[strlen(output)-1] = 0;
    strcpy(map_data[i++],output);
    p = strtok (NULL, "#");
  }

  /* Allocate memory for map data */
  struct map *map = (struct map *)malloc(sizeof(struct map));
  map->map_id = strn_to_int(map_id, 4);

  /* Parsing */
  char map_elems[2][4];
  char *token;

  token = strtok(map_data[0], " ");
  i = 0;
  while(token != NULL)
  {
    strcpy(map_elems[i++], token);
    token = strtok(NULL, ",");
  }

  /* Width and height of the map will be less than 1000 */
  map->width = strn_to_int(map_elems[0], 3);
  map->height = strn_to_int(map_elems[1], 3);

  /* Geometry of map */
  i = 0;
  map->geo = (char *)malloc(map->width * map->height * 2 + 1);
  token = strtok(map_data[1], "\n");
  strncpy(map->geo + (i++)*2*(map->width), token, 2*(map->width));
  while(token != NULL)
  {
    token = strtok(NULL, "\n");
    if(token != NULL)
      strncpy(map->geo + (i++)*2*(map->width), token, 2*(map->width));
  }
  map->geo[2*(map->width)*(map->height)] = 0;

  /* Colors in map */
  i = 0;
  char* temp = (char *)malloc(map->width * map->height * 2 * 3 + 1);
  map->cgeo = (color *)malloc(map->width * map->height * 2 * sizeof(color) + 1);

  token = strtok(map_data[2], "\n");
  strncpy(temp + (i++)*6*(map->width), token, 6*(map->width));
  while(token != NULL)
  {
    token = strtok(NULL, "\n");
    if(token != NULL)
      strncpy(temp + (i++)*6*(map->width), token, 6*(map->width));
  }
  temp[6*(map->width)*(map->height)] = 0;
  colormap_from_string(map->width, map->height, temp, map->cgeo);

  free(temp);

  /* Portals */
  char *newline_token;
  char *ptr[2];
  newline_token = strtok_r(map_data[3], "\n", &ptr[0]);
  i = 0;
  while(newline_token != NULL)
  {
    token = strtok_r(newline_token, ",", &ptr[1]);
    map->portals[i].x_pos = strn_to_int(token, 3);
    token = strtok_r(NULL, ",", &ptr[1]);
    map->portals[i].y_pos = strn_to_int(token, 3);
    token = strtok_r(NULL, ",", &ptr[1]);
    map->portals[i].dest_map_id = strn_to_int(token, 4);
    newline_token = strtok_r(NULL, "\n", &ptr[0]);
    i++;
  }
  map->portal_num = i;

  /* Monster spawn */
  newline_token = strtok_r(map_data[4], "\n", &ptr[0]);
  i = 0;
  while(newline_token != NULL)
  {
    token = strtok_r(newline_token, ",", &ptr[1]);
    map->spwn_pts[i].x_pos = strn_to_int(token, 3);
    token = strtok_r(NULL, ",", &ptr[1]);
    map->spwn_pts[i].y_pos = strn_to_int(token, 3);
    token = strtok_r(NULL, ",", &ptr[1]);
    map->spwn_pts[i].monster_id = strn_to_int(token, 4);
    newline_token = strtok_r(NULL, "\n", &ptr[0]);
    i++;
  }
  map->monster_num = i;

  return map;
}