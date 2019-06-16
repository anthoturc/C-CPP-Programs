#include <stdlib.h>
#include <stdio.h>

#include "list.h"

int
list_init(List *list)
{
  if ((list = (List *)malloc(sizeof(list))) == NULL) {
    perror("list: malloc in list_init @ line 9\n");
    return -1;
  }

  list->size = 0;
  list->head = list->tail = NULL;
  list->head->next = list->tail->next = NULL;
  return 1;
}

int
list_append(List *list, int data)
{
  Node *tmp;
  if ((tmp = (Node *)malloc(sizeof(Node))) == NULL) {
    perror("list: malloc in list_append @ line 23\n");
    return -1;
  }
  if (list->head == NULL) {
    list->head = tmp; 
    list->tail = list->head;
    list->head->next = list->tail->next = NULL;
  } else {
    list->tail->next = tmp;
    list->tail = list->tail->next;
    list->tail->next = NULL;
  }
  list->size += 1;

  return 1;
}
