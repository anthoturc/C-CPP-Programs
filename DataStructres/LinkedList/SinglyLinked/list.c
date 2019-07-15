#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "list.h"

void 
list_init(list **l)
{
	if ((*l = (list *)malloc(sizeof(list))) == NULL) {
		perror("list.c: malloc in list_init @ line 9\n");
		return;
	}

	(*l)->size = 0;
	(*l)->head = (*l)->tail = NULL;
}

int 
list_append(list *l, int data)
{
	node *new_el;
	if ((new_el = (node *)malloc(sizeof(node))) == NULL) {
		perror("list.c: malloc in list_append @ line 22\n");
		return -1;
	}
	new_el->data = data;

	if (list_size(l) == 0) {
		l->head = new_el;
		l->head->next = NULL;
		l->tail = new_el;
	} else {
		l->tail->next = new_el;
		l->tail = new_el;
		l->tail->next = NULL;
	}

	++l->size;
	return 0;
}

int 
list_prepend(list *l, int data)
{
	node *new_el;
	if ((new_el = (node *)malloc(sizeof(node))) == NULL) {
		perror("list.c: malloc in list_prepend @ line 46\n");
		return -1;
	}
	new_el->data = data;

	if (list_size(l) == 0) {
		l->head = new_el;
		l->head->next = NULL;
		l->tail = new_el;
	} else {
		new_el->next = l->head;
		l->head = new_el;
	}

	--l->size;
	return 0;
}

int 
list_ins_next(list *l, node *el, int data)
{
	if (el == NULL || list_size(l) == 0) {
		return list_append(l, data);
	}
	node *new_el;

	if ((new_el = (node *)malloc(sizeof(node))) == NULL) {
		perror("list.c: malloc in list_ins_next @ line 73\n");
		return -1;
	}

	new_el->data = data;
	new_el->next = el->next;
	el->next = new_el;

	++l->size;
	return 0;
}

int 
list_ins_prev(list *l, node *el, int data)
{
	if (el == NULL || list_size(l) == 0 || el == l->head) {
		return list_prepend(l, data);
	}

	node *curr = l->head;

	while (curr != NULL) {
		if (curr->next->data == el->data) {
			break;
		}
		curr = curr->next;
	}
	
	if (curr == NULL) {
		return list_prepend(l, data);
	}

	node *new_el;
	if ((new_el = (node *)malloc(sizeof(node))) == NULL) {
		perror("list.c: malloc in list_ins_prev @ line 106\n");
		return -1;
	}
	new_el->data = data;
	
	curr->next = new_el;
	new_el->next = el;

	++l->size;
	return 0;
}

int
list_rem(list *l, node *el)
{
	if (list_size(l) == 0 || el == NULL) {
		return -1;
	}

	if (el == l->head) {
		l->head = l->head->next;
		free(el);
	} else {
		node *curr = l->head;
		while (curr != NULL) {
			if (curr->next->data == el->data) {
				break;
			}
			curr = curr->next;
		}

		if (curr == NULL) {
			return -1;
		}

		curr->next = el->next;
		free(el);
	}
	--l->size;
	return 0;
}

void
list_destroy(list *l)
{
	while (list_size(l) > 0) {
		list_rem(l, list_head(l));
	}
	free(l);
	memset(l, 0, sizeof(list));
}


void
print_list(list *l)
{
	node *curr = l->head;
	while (curr != NULL) {
		printf("%d -> ", curr->data);
		curr = curr->next;
	}

	printf("NULL\n");
}

