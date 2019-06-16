/*
 * list.h
 *
 * Author: Anthony Turcios
 * Date: 03 May 2019
 **/

#ifndef _LIST_H_
#define _LIST_H_

typedef struct node {
  int data; /* void * allows for generic Node */
  struct node *next; /* pointer to the next node */
} Node;

typedef struct list {
  Node *head; /* pointer to the head node */
  Node *tail; /* pointer to the tail node */
  int size; /* the number of elements in the list */
} List;

/*
 * list_init will update the value of the list pointer
 * and set the members of the list data structure
 * 
 * Args:
 *  list - (List *) Pointer to the head of the list
 *  
 * Ret:
 *  1 on success, and -1 on failure.
 **/
int list_init(List *list);

/*
 * list_append will add data to the end of the list
 * 
 * Args:
 *  list - (List *) Pointer to the list
 *  
 *  data - (int) Data
 *
 * Ret:
 *  1 on success and -1 on failure.
 **/
int list_append(List *list, int data);

/*
 * list_prepend will add data to the beginning of the list
 *
 * Args:
 *  list - (List *) Pointer to the list
 *
 *  data - (int) Data
 *
 * Ret:
 *  1 on success and -1 on failure.
 **/
int list_prepend(List *list, int data);

/*
 * list_remove will search for the first instance of data and
 * remove that data
 * 
 * Args:
 *  list - (List *) Pointer to the list
 *
 *  data - (int) Data
 * 
 * Ret:
 *  Value of data if found, bitwise not of data otherwise. 
 **/
int list_remove(List *list, int data);

/*
 * list_find will search the list for the first of data
 * 
 * Args:
 *  list - (List *) Pointer to the list
 *
 *  data - (int) Data
 *
 * Ret:
 *  Value of data, bitwise not of data otherwise.
 **/
int list_find(List *list, int data);

/*
 * list_contains will determine if the data exists in the list
 *
 * Args:
 *  list - (List *) Pointer to the list
 *
 *  data - (int) Data
 *
 * Ret:
 *  1 if data is in list, 0 otherwise.
 **/
int list_contains(List *list, int data);

#endif /* _LIST_H_ */


