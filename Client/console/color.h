#ifndef _COLOR_H_
#define _COLOR_H_

typedef struct
{
  char bgcolor;
  char textcolor;
} color;

#define ctoi(C) C.bgcolor * 16 + C.textcolor

#endif