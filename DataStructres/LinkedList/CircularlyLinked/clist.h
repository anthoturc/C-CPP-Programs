#ifndef _C_LIST_H_
#define _C_LIST_H_

typedef struct _cnode {
	int 					data;
	struct _cnode *next;
} cnode;

typedef struct _clist {
	int 					size;
	struct _cnode *head;
} clist;

void clist_init(clist **l);

int clist_ins(clist *l, int data);
int clist_ins_next(clist *l, cnode *el, int data);

int clist_rem(clist *l, cnode *el);

void clist_destroy(clist *l);

void print_clist(clist *l);

#define clist_size(l) ((l)->size)
#define clist_head(l) ((l)->head)
#define clist_data(el) ((el)->data)
#define clist_next(el) ((el)->next)

#endif /* _C_LIST_H_ */

