#ifndef _CONS_H_
#define _CONS_H_
#include "color.h"

int init_console(void);
void update_screen(char *, color *);
void show_screen(void);
void stop_printing(void);
void resume_printing(void);
void update_screen_string(char*, int);
void end_console(void);

#endif