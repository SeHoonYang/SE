#include "color.h"
#include "../conf.inc"

void init_colormap(color* colormap)
{
  for(int i =0; i<=W*H*2; i++)
  {
    colormap[i].bgcolor = 0;
    colormap[i].textcolor = 7;
  }
  colormap[W*H*2].textcolor = 0;
}