#include <fcntl.h>
#include "usr.h"
#include "direct.h"

int create_account(char * ID, char * PWD)
{
  chdir("./data/userdata");

  /* ID already exists */
  if(open(ID,O_RDONLY) != -1)
    return 0;

  
  return 1;
}