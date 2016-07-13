#ifndef __LIST_H_
#define __LIST_H_

/* list.h 
   Simple implementation of singly linked list

   *list cycle

   init_list => push_list/remove_list => clear_list

   Note that you must free contents in the list_elem before
   call clear_list. clear_list just frees list_elem;

   To iterate, you may use for/while

   ex)
     struct list lst;
     init_list(&lst);

     //push elements

     struct list_elem* e;
     for(e = list_begin(&lst);e != list_end(&lst);e = list_next(e))
     {
       struct foo* bar = (struct foo*)get_contents(e);
       // do something with bar;
     }                                                              */

struct list_elem
{
  struct list_elem *next;
  void* conts;
};

struct list
{
  struct list_elem head;
  struct list_elem tail;
};

void init_list(struct list*);
void clear_list(struct list*);
void push_list(struct list*, void*);
void remove_list(struct list*, void*);
void* get_contents_n(struct list*,int);
int list_size(struct list*);
struct list_elem* list_begin(struct list*);
struct list_elem* list_end(struct list*);
struct list_elem* list_next(struct list_elem*);

#endif