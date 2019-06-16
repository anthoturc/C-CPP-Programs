/*
 * list.h
 *
 * Author: Anthony Turcios
 * Date: 03 May 2019
 **/

#ifndef _LIST_H_
#define _LIST_H_

typedef struct node {
  void *data; /* void * allows for generic Node */
  struct node *node; /* pointer to the next node */
} Node;

typedef struct list {
  Node *head; /* pointer to the head node */
  Node *tail; /* pointer to the tail node */
  int memsize; /* amount of memory taken up by data of each node */
  int size; /* the number of elements in the list */
  void (*free)(void *); /* pointer to function that will free data */
} List;

void init_list(List *list, int memsize, int nmembers, void (*free)(void *));
void destroy_list(List *list);

void prepend_list(List *list, void *data);
void append_list(List *list, void *data);

int size_list(List *list);

void for_each_list(List *list, bool (*iterator)(void *));



#endif /* _LIST_H_ */
