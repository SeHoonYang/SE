#include <string.h>
#include "map.h"

char *map_load_data(char *map_id)
{
  chdir("./data/mapdata");
  FILE *map_file;
  char buf[1000];
  char output[1000] = "";
  char *separator = "#";
  map_file =fopen(map_id,"r");
  
  /* The map file does not exist */
  if (!map_file){
    printf("Error: %d (%s)\n", errno, strerror(errno));
    getchar();
    return -1;
  }

  /* Reading map file */
  while (fgets(buf,1000, map_file)!=NULL)
    strcat(output, buf);

  fclose(map_file);

  int i = 0;
  char *map_data[ELEM_NUM];

  /* Parsing formatted data */
  char *p = strtok (output, "#");
  while (p != NULL)
  {
    char output[1000] = "";
    strcpy(output, p);

    memmove(&output[0], &output[1], strlen(output));
    output[strlen(output)-1] = 0;

    map_data[i++] = output;
    printf("output = %s\n", output);
    p = strtok (NULL, "#");
  }
  return map_data;
}

