/**********************
*				list.h
**********************/

#ifndef _LIST_H_
#define _LIST_H_

typedef struct _node {
	int 				 	data;
	struct _node	*next;
} node;

typedef struct _list {
	node 	*head;
	node 	*tail;

	int 	size;
} list;

#define list_size(l) ((l)->size)
#define list_head(l) ((l)->head)
#define list_tail(l) ((l)->tail)
#define data(el) ((el)->data)

void list_init(list **l);

int list_append(list *l, int data);
int list_prepend(list *l, int data);
int list_ins_next(list *l, node *el, int data);
int list_ins_prev(list *l, node *el, int data);

int list_rem(list *l, node *el);

void list_destroy(list *l);

void print_list(list *l);

#endif /* _LIST_H_ */

