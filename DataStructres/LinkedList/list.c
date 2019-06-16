#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "list.h"

void
init_list(List *list, int memsize, void (*free)(void *))
{
  assert(memsize > 0);
  list->memsize = memsize;
  list->size = 0;
  list->head = list->tail = NULL;
  list->free = free;
}

void
destroy_list(List *list)
{
  Node *curr;
  while (list->head != NULL) {
    curr = list->head;
    list->head = curr->next;

    if (list->free) {
      list->free(curr->data);
    }

    free(curr->data);
    free(curr);
  }
}

void
prepend_list(List *list, void *data)
{
  Node *node;

  if ((node = (Node *)malloc(sizeof(Node))) == NULL) {
    perror("")
}

void
add(List *list, void *data)
{
  Node *new_node;

  if ((new_node = (Node *)malloc(sizeof(Node))) == NULL) {
    perror("list.c: malloc in add @ line 9\n");
  }


}



