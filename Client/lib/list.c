#include <malloc.h>
#include "list.h"

/* Initialize the list */
void init_list(struct list* lst)
{
  lst->head.next = &lst->tail;
}

/* Free all list_elems */
void clear_list(struct list* lst)
{
  struct list_elem* e;
  for(e = list_begin(lst);e != list_end(lst);)
  {
    struct list_elem* temp = list_next(e);
    free(e);
    e = temp;
  }
}

/* Push contents to the list */
void push_list(struct list* lst, void* contents)
{
  return;
}

/* Remove contents from the list */
void remove_list(struct list* lst, void* contents)
{
  return;
}

/* Get contents of the list_elem e */
void* get_contents(struct list_elem* e)
{
  return e->conts;
}

/* Return n'th contents in the list.
   Return NUUL if n > size           */
void* get_contents_n(struct list* lst,int n)
{
  return NULL;
}

/* Return the size of list */
int list_size(struct list* lst)
{
  return 0;
}

/* Return the first element of the list */
struct list_elem* list_begin(struct list* lst)
{
  return lst->head.next;
}

/* Return the tail of the list */
struct list_elem* list_end(struct list* lst)
{
  return &lst->tail;
}

/* Return the next element of the e */
struct list_elem* list_next(struct list_elem* e)
{
  return e->next;
}