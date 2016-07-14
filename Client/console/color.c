#include "color.h"
#include "../conf.inc"
#include "../lib/lib.h"

void init_colormap(color* colormap)
{
  for(int i =0; i<=W*H*2; i++)
  {
    colormap[i].bgcolor = 0;
    colormap[i].textcolor = 7;
  }

  colormap[W*H*2].textcolor = 0;
}

void colormap_from_string(char* s, color* colormap)
{
  /* Note that string s must formatted as "XXXYYYZZZ ---\n" */

  for(int i = 0; i < 20; ++i)
    for(int j = 0; j < 64; ++j)
      {
        int current_color = str3_to_int(s + (i*64 + j) * 3);
        colormap[i*64 + j].bgcolor = current_color / 16;
        colormap[i*64 + j].textcolor = current_color % 16;
      }
}