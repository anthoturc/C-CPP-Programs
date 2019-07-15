/***************
*			set.h
***************/

#ifndef _SET_H_
#define _SET_H_

#include "bst.h"

typedef struct _set {
	bst *t;
} set;

void set_init(set **s);

int set_add(set *s, int data);

int set_remove(set *s, int data);

int set_contains(set *s, int data);

void set_union(set *s1, set *s2);

void _add_all(set *dest, bst_node *node);

void set_intersect(set **dest, set *s1, set *s2);
int _add_common(set *dest, set *s1, set *s2);

set *set_difference(set *s1, set *s2);

void set_destroy(set *s);

#define set_size(s) (((s)->t)->size)

#endif /* _SET_H_ */

