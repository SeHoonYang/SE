#include "lib.h"
#include <stdio.h>

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
    if(s[i] == '\0')
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