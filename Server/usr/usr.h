#ifndef _USR_H_
#define _USR_H_
#include "../lib/list.h"

struct user_data
{
  char id[11];
  char pwd[11];
  int user_index;
  int map_id;
  /* x + y * 65536, hp + mp * 65536 */
  unsigned short x;
  unsigned short y;
  unsigned short hp;
  unsigned short mp;
  unsigned short max_hp;
  unsigned short max_mp;
  unsigned short str;
  unsigned short def;
  int money;

  struct list inventory;
};

struct enemy_info
{
  unsigned short current_mob_hp;
  int current_mob_id;
};

int create_account(char *, char *);
int load_user_data(char *, char *, int, int, unsigned, unsigned, unsigned, int, unsigned short, unsigned short);
void init_user_data(void);
void save_users_data(void);
void release_user_data(int);
void save_user_data(int);
void clear_user_data(void);
struct enemy_info* update_user_location(int, char);
int get_user_map_id(int);
struct user_data* get_user_data(int);

#endif