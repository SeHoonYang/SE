#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map/map.h"
#define ELEM_NUM 5
#define MAX_STRLEN 1000

int main()
{
  char *map_id = "map_test.txt";
  chdir("./data/mapdata");
  FILE *map_file;
  char buf[MAX_STRLEN];
  char output[MAX_STRLEN] = "";
  char *separator = "#";
  map_file =fopen(map_id,"r");
  
  /* The map file does not exist */
  if (!map_file){
    printf("Error: %d (%s)\n", errno, strerror(errno));
    getchar();
    return -1;
  }

  /* Reading map file */
  while (fgets(buf,MAX_STRLEN, map_file)!=NULL)
    strcat(output, buf);

  fclose(map_file);

  int i = 0;
  char map_data[ELEM_NUM][MAX_STRLEN];

  /* Parsing formatted data */
  char *p = strtok (output, "#");
  while (p != NULL)
  {
    char output[MAX_STRLEN] = "";
    strcpy(output, p);

    memmove(&output[0], &output[1], strlen(output));
    output[strlen(output)-1] = 0;
    strcpy(map_data[i++],output);
    printf("output = %s\n", output);
    p = strtok (NULL, "#");
  }

  struct map *map = (struct map *)calloc(1, sizeof(struct map));
  map->map_id = map_id;
  /* Width and Height */
  char map_elems[2][MAX_STRLEN];
  char *token;
  token = strtok(map_data[0], ",");
  i = 0;
  while(token != NULL)
  {
    printf("token = %s\n", token);
    strcpy(map_elems[i++], token);
    token = strtok(NULL, ",");
  }
  for(i = 0; i< 6; i++)
    printf("map_elem item %d : %s\n", i, map_elems[i]);
  map->width = map_elems[0];
  map->height = map_elems[1];
  /* Geometry of map */
  strcpy(map->geo, map_data[1]);
  /* Colors in map */
  strcpy(map->cgeo, map_data[2]);

  printf("map's geometry is : %s\n", map->geo);
  printf("map's cgeometry is : %s\n", map->cgeo);

  /* Portals */
  struct portal portals[10] = malloc(10 * sizeof(struct portal));
  char *newline_token;
  newline_token = strtok(map_data[3], "\n");
  i = 0;
  while(newline_token != NULL)
  {
    token = strtok(newline_token, ",");
    portals[i].x_pos = token;
    token = strtok(NULL, "\n");
    portals[i].y_pos = token;
    token = strtok(NULL, "\n");
    portals[i].dest_map_id = token;
    newline_token = strtok(NULL, "\n");
    i++;
  }
  map->portals = portals;

  /* Monster Spawn */
  struct monster_spwn spwn_pts[10] = malloc(10 * sizeof(struct monster_spwn));
  newline_token = strtok(map_data[3], "\n");
  i = 0;
  while(newline_token != NULL)
  {
    token = strtok(newline_token, ",");
    spwn_pts[i].x_pos = token;
    token = strtok(NULL, "\n");
    spwn_pts[i].y_pos = token;
    token = strtok(NULL, "\n");
    spwn_pts[i].dest_map_id = token;
    newline_token = strtok(NULL, "\n");
    i++;
  }
  map->spwn_pts = spwn_pts;

  getchar();
  return 0;
}