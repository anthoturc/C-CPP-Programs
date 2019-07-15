#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dlist.h"

void
dlist_init(dlist **l)
{
	if ((*l = (dlist *)malloc(sizeof(dlist))) == NULL) {
		perror("dlist.c: malloc in dlist_init @ line 10\n");
		return;
	}

	(*l)->size = 0;
	(*l)->head = (*l)->tail = NULL;
}

int
dlist_append(dlist *l, int data)
{
	dnode *new_el;
	if ((new_el = (dnode *)malloc(sizeof(dnode))) == NULL) {
		perror("dlist.c: malloc in dlist_append @ line 23\n");
		return -1;
	}

	new_el->data = data;

	if (dlist_size(l) == 0) {
		l->head = new_el;
		l->head->next = NULL;
		l->head->prev = NULL;
		l->tail = new_el;
	} else {
		new_el->prev = l->tail;
		l->tail->next = new_el;
		l->tail = new_el;
		l->tail->next = NULL;
	}

	++l->size;
	return 0;
}

int 
dlist_prepend(dlist *l, int data) 
{
	dnode *new_el;
	if ((new_el = (dnode *)malloc(sizeof(dnode))) == NULL) {
		perror("dlist.c: malloc in dlist_prepend @ line 50\n");
		return -1;
	}

	new_el->data = data;

	if (dlist_size(l) == 0) {
		l->head = new_el;
		l->head->next = NULL;
		l->head->prev = NULL;
		l->tail = new_el;
	} else {
		new_el->next = l->head;
		l->head->prev = new_el;
		l->head = new_el;
		l->head->prev = NULL;
	}

	++l->size;
	return 0;
}

int
dlist_ins_next(dlist *l, dnode *el, int data)
{
	if (el == NULL || dlist_size(l) != 0) {
		return dlist_append(l, data);
	}

	if (el->next == NULL) {
		return dlist_append(l, data);
	}

	dnode *new_el;
	if ((new_el = (dnode *)malloc(sizeof(dnode))) == NULL) {
		perror("dlist.c: malloc in dlist_ins_next @ line 81\n");
		return -1;
	}
	new_el->data = data;

	new_el->next = el->next;
	el->next->prev = new_el;
	el->next = new_el;

	++l->size;
	return 0;
}

int
dlist_ins_prev(dlist *l, dnode *el, int data)
{
	if (el == NULL || dlist_size(l) == 0) {
		return dlist_prepend(l, data);
	}

	if (el->prev == NULL) {
		return dlist_prepend(l, data);
	}

	dnode *new_el;
	if ((new_el = (dnode *)malloc(sizeof(dnode))) == NULL) {
		perror("dlist.c: malloc in dlist_ins_prev @ line 111\n");
		return -1;
	}

	new_el->data = data;
	new_el->next = el;
	el->prev->next = new_el;
	el->prev = new_el;

	++l->size;
	return 0;
}

int
dlist_remove(dlist *l, dnode *el)
{
	if (el == NULL || dlist_size(l) == 0) {
		return -1;
	}

	if (el->prev == NULL) {
		l->head = el->next;
		l->head->prev = NULL;
	} else if (el->next == NULL) {
		l->tail = el->prev;
		l->tail->next = NULL;
	} else {
		el->prev->next = el->next;
		el->next->prev = el->prev;
	}

	el->next = NULL;
	el->prev = NULL;
	free(el);

	return 0;
}

void
dlist_destroy(dlist *l)
{
	while (dlist_size(l) > 0) {
		dlist_remove(l, dlist_head(l));
	}

	memset(l, 0, sizeof(dlist));
}

void
print_dlist(dlist *l)
{
	dnode *curr = l->head;
	while (curr != NULL) {
		printf("%d -> ", curr->data);
		curr = curr->next;
	}
	printf("NULL\n");
}

