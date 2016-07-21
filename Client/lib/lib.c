#include "lib.h"
#include <stdio.h>

static int _pow(int r, int l)
{
  int rst = 1;

  while(l-- > 0)
    rst *= r;

  return rst;
}

int str3_to_int(char* s)
{
  int sum = 0;

  for(int i = 0; i < 3; ++i)
    sum = sum * 10 + s[i] - '0';

  return sum;
}

int strn_to_int(char* s, int n)
{
  int sum = 0;

  for(int i = 0; i < n; ++i)
  {
    if(s[i] == '\0' || s[i] == '\n')
      break;
    sum = sum * 10 + s[i] - '0';
  }

  return sum;
}

/* 
 * public domain strtok_r() by Charlie Gordon
 *
 *   from comp.lang.c  9/14/2007
 *
 *      http://groups.google.com/group/comp.lang.c/msg/2ab1ecbb86646684
 *
 *     (Declaration that it's public domain):
 *      http://groups.google.com/group/comp.lang.c/msg/7c7b39328fefab9c
 */

char* strtok_r(
    char *str, 
    const char *delim, 
    char **nextp)
{
    char *ret;

    if (str == NULL)
    {
        str = *nextp;
    }

    str += strspn(str, delim);

    if (*str == '\0')
    {
        return NULL;
    }

    ret = str;

    str += strcspn(str, delim);

    if (*str)
    {
        *str++ = '\0';
    }

    *nextp = str;

    return ret;
}

char* int_to_str(int i)
{
  int temp = i;
  int n = 0;
  if(i == 0)
    n = 1;
  else
  {
    while(temp != 0)
    {
      temp /= 10;
      n++;
    }
  }

  char* rst = (char *)malloc(n+1);

  for(int k = 0; k < n; ++k)
  {
    *(rst + k) = '0' + (i / _pow(10,n-k-1) % 10);
  }

  *(rst + n) = 0;

  return rst;
}