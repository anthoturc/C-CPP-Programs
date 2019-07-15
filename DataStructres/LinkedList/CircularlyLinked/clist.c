#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "clist.h"

void
clist_init(clist **l)
{
	if ((*l = (clist *)malloc(sizeof(clist))) == NULL) {
		perror("clist.c: malloc in clist_init @ line 10\n");
		return;
	}

	(*l)->size = 0;
	(*l)->head = NULL;
}

int
clist_ins(clist *l, int data)
{
	cnode *new_el;
	if ((new_el = (cnode *)malloc(sizeof(cnode))) == NULL) {
		perror("clist.c: malloc in clist_ins @ line 23\n");
		return -1;
	}

	new_el->data = data;

	if (clist_size(l) == 0) {
		new_el->next = new_el;
		l->head = new_el;
	} else {
		new_el->next = l->head->next;
		l->head->next = new_el;
	}
	
	++l->size;
	return 0;
}

int
clist_ins_next(clist *l, cnode *el, int data)
{
	if (el == NULL || clist_size(l) == 0) {
		return clist_ins(l, data);
	}

	if (el == l->head) {
		return clist_ins(l, data);
	}

	cnode *new_el;
	if ((new_el = (cnode *)malloc(sizeof(cnode))) == NULL) {
		perror("clist.c: malloc in clist_ins_next @ line 55\n");
		return -1;
	}

	new_el->data = data;
	
	new_el->next = el->next;
	el->next = new_el;

	++l->size;
	return 0;
}

int
clist_rem(clist *l, cnode *el)
{
	if (clist_size(l) == 1) {
		l->head = NULL;
		free(el);
		return 0;
	}

	cnode *tmp = el->next;

	while (tmp->next != el) {
		tmp = tmp->next;
	}
	
	tmp->next = el->next;
	if (el == l->head) {
		l->head = el->next;
	}

	--l->size;
	return 0;
}

void 
clist_destroy(clist *l)
{
	cnode *tmp = l->head;
	while (clist_size(l) > 1) {
		l->head = l->head->next;
		free(tmp);
		tmp = l->head;
		--l->size;
	}

	free(l->head);
	free(l);
	memset(l, 0, sizeof(clist));
}

void
print_clist(clist *l)
{
	cnode *tmp = l->head->next;
	while (tmp != l->head) {
		printf("%d -> ", tmp->data);
		tmp = tmp->next;
	}
	printf("%d LOOP \n", l->head->data);
}
