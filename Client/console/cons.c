#include <windows.h>
#include "cons.h"
#include "../conf.inc"

/* Back buffers, double buffering */
static HANDLE buffer1, buffer2;
static HANDLE current_buffer;
static char* last_screen;
static color* last_colormap;
static int printing = 0;

static int init_buffer(HANDLE b)
{
  /* Set console size */
  COORD newSize = {W*2, H+1};
  SetConsoleScreenBufferSize(b, newSize);

  SMALL_RECT newWinSize;
  newWinSize.Left = 0;
  newWinSize.Top = 0;
  newWinSize.Right = W*2-1;
  newWinSize.Bottom = H;
  return SetConsoleWindowInfo(b, TRUE, &newWinSize);
}

int init_console()
{
  /* Set Project title */
  SetConsoleTitle(PROJECT_TITLE);
  char command_buffer[15];

  /* Set buffer size */
  sprintf(command_buffer, "mode %d,%d", W*2, H+1);
  system(command_buffer);

  /* Buffer initialization */
  buffer1=GetStdHandle(STD_OUTPUT_HANDLE);
  buffer2=CreateConsoleScreenBuffer(GENERIC_WRITE,FILE_SHARE_READ,0,CONSOLE_TEXTMODE_BUFFER,NULL);

  /* Initialize initial screen. !Free later! */
  last_colormap = (color *)malloc(W*H*2*sizeof(color) + 1);
  last_screen = (char *)malloc(W*H*2 + 1);

  current_buffer = buffer1;

  return init_buffer(buffer1) && init_buffer(buffer2);
}

static void print_screen(char* screen, color* colormap)
{
  int last_color = ctoi(colormap[0]);
  int last_index = 0;
  for(int i=0;i<=W*H*2;i++)
  {
    if(ctoi(colormap[i]) != last_color)
    {
      SetConsoleTextAttribute(current_buffer, last_color);
      WriteConsole(current_buffer, screen + last_index, i-last_index,NULL,0);

      last_color = ctoi(colormap[i]);
      last_index = i;
    }
  }

  SetConsoleActiveScreenBuffer(current_buffer);
  current_buffer = current_buffer == buffer1 ? buffer2 : buffer1;
}

void update_screen(char* screen, color* colormap)
{
  if(screen != NULL)
    last_screen = screen;
  if(colormap != NULL)
    last_colormap = colormap;
}

void update_screen_string(char* p, int position)
{
  strncpy(last_screen + position, p, strlen(p));
}

void stop_printing()
{
  printing = 0;
}

void resume_printing()
{
  printing = 1;
}

void show_screen()
{
  while(1)
  {
    if(printing)
    {
      print_screen(last_screen,last_colormap);
      Sleep(30);
    }else
      Sleep(30);
  }
}