/**********************
*				dlist.h
**********************/

#ifndef _D_LIST_H_
#define _D_LIST_H_

typedef struct _dnode {
	int 					data;
	struct _dnode *next;
	struct _dnode *prev;
} dnode;

typedef struct _dlist {
	int 	size;
	dnode	*head;
	dnode *tail;
} dlist;

void dlist_init(dlist **l);

int dlist_append(dlist *l, int data);
int dlist_prepend(dlist *l, int data);

int dlist_ins_next(dlist *l, dnode *el, int data);
int dlist_ins_prev(dlist *l, dnode *el, int data);

int dlist_remove(dlist *l, dnode *el);

void dlist_destroy(dlist *l);

void print_dlist(dlist *l);

#define dlist_size(l) ((l)->size)
#define dlist_head(l) ((l)->head)
#define dlist_tail(l) ((l)->tail)
#define dlist_data(el) ((el)->data)
#define dlist_next(el) ((el)->next)
#define dlist_prev(el) ((el)->prev)

#endif /* _D_LIST_H_ */

