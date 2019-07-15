#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"
#include "set.h"

void
set_init(set **s)
{
	if ((*s = (set *)malloc(sizeof(set))) == NULL) {
		perror("set.c: malloc in set_init @ line 11 \n");
		return;
	}

	bst_init(s->t, NDUPS);
}

int 
set_add(set *s, int data)
{
	return bst_insert(s->t, data);
}

int
set_remove(set *s, int data)
{
	return bst_remove(s->t, data);
}

int 
set_contains(set *s, int data)
{
	return bst_contains(s->t, data);
}

void
set_union(set *s1, set *s2)
{
	int total = set_size(s1) + set_size(s2);
	_add_all(s1, s2->t->root);
	if (total == set_size(s1)) {
		printf("New set size: %d\n", total);
	} else {
		printf("Set size has not increased!\n");
	}
	set_destroy(s2);
	return new_set;
}

void
_add_all(set *dest, bst_node *node)
{
	if (node == NULL) {
		return;
	} 
	set_add(dest, node->data);
	_add_all(dest, node->left);
	_add_all(dest, node->right);
}

void
set_destroy(set *s)
{
	bst_destroy(s->t);
	memset(s, 0, sizeof(set));
	free(s);
}

