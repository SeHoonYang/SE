#ifndef _USR_H_
#define _USR_H_

struct user_data
{
  char id[11];
  int map_id;
  /* x + y * 65536, hp + mp * 65536 */
  unsigned short x;
  unsigned short y;
  unsigned short hp;
  unsigned short mp;
  /* inventroy */
};

int create_account(char *, char *);
void load_user_data(char *, int, unsigned, unsigned);
void init_user_data(void);
void clear_user_data(void);
#endif