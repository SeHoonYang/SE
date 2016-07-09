#include "lib.h"

int str3_to_int(char* s)
{
  int sum = 0;

  for(int i = 0; i < 3; ++i)
    sum = sum * 10 + s[i] - '0';

  return sum;
}