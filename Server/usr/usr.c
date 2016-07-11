#include <fcntl.h>
#include "usr.h"
#include "direct.h"

int create_account(char * ID, char * PWD)
{
  chdir("./data/userdata");

  /* ID already exists */
  if(open(ID,O_RDONLY) != -1)
    return 0;

  /* Create an account */
  int fd = open(ID, O_CREAT | O_RDWR);

  /* Write basic user data */
  write(fd, PWD, strlen(PWD));
  close(fd);

  return 1;
}