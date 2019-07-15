#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "bst.h"

void
bst_init(bst **t, int allow_dups)
{
	if ((*t = (bst *)malloc(sizeof(bst))) == NULL) {
		perror("bst.c: malloc in bst_init @ line 10\n");
		return;
	}

	(*t)->size = 0;
	(*t)->allow_dups = allow_dups;
	(*t)->root = NULL;
}

int
bst_insert(bst *t, int data)
{
	if (t == NULL) {
		return -1;
	}

	bst_node *new_el;
	if ((new_el = (bst_node *)malloc(sizeof(bst_node))) == NULL) {
		perror("bst.c: malloc in bst_insert @ line 28\n");
		return -1;
	}
	new_el->data = data;
	new_el->left = NULL;
	new_el->right = NULL;

	if (bst_empty(t)) {
		t->root = new_el;
	} else {
		if (_bst_insert(t, t->root, new_el) == -1) {
			return -1;
		}
	}

	++t->size;
	return 0;
}

int
bst_remove(bst *t, int data)
{
	if (bst_size(t) == 0) {
		return -1;
	}

	return _bst_remove(t, data);
}

int
bst_contains(bst *t, int data)
{
	return _bst_find(t->root, data) != NULL ? 1 : 0;
}

int 
bst_min(bst *t)
{
	return _bst_min(t)->data;
}

int
bst_max(bst *t)
{
	return _bst_max(t)->data;
}

void
bst_destroy(bst *t)
{
	while (bst_size(t) > 0) {
		bst_node *tmp = _bst_min(t);
		if (tmp == NULL) {
			break;
		}
		bst_remove(t, tmp->data);
	}

	memset(t, 0, sizeof(bst));
	free(t);
}

void
print_bst(bst *t)
{
	_print_bst(t->root);
	printf("\n");
}

void
_print_bst(bst_node *node)
{
	if (node == NULL) {
		return;
	}
	_print_bst(node->left);
	printf("%d ", node->data);
	_print_bst(node->right);
}	

int
_bst_insert(bst *t, bst_node *root, bst_node *curr)
{
	if (t->root == NULL) {
		return -1;
	}

	if (curr->data > root->data) {
		if (root->right == NULL) {
			root->right = curr;
			return 0;
		} 
		return _bst_insert(t, root->right, curr);
	} else if (curr->data < root->data) {
		if (root->left == NULL) {
			root->left = curr;
			return 0;
		}
		return _bst_insert(t, root->left, curr);
	} else {
		if (t->allow_dups == DUPS) {
			return _bst_insert(t, root->right, curr);
		}
		return -1;
	}
}

int
_bst_remove(bst *t, int data)
{
	bst_node *to_rem = _bst_find(t->root, data);
	if (to_rem == NULL) {
		return -1;
	}
	
	bst_node *succ = _bst_successor(to_rem);
	bst_node *pred_succ = NULL;
	if (succ != NULL) {
		pred_succ = _bst_predecessor(t->root, succ->data);
	}

	if (pred_succ != NULL) {
		if (pred_succ != to_rem) {
			pred_succ->left = succ->right;
		}
	}

	if (to_rem == t->root) {
		if (succ == NULL) {
			t->root = t->root->left;
		} else {
			succ->left = t->root->left;
			if (to_rem != pred_succ) {
				succ->right = t->root->right;
			}
			t->root = succ;
		}
	} else { // not root
		bst_node *pred = _bst_predecessor(t->root, to_rem->data);

		if (is_leaf(to_rem)) { // leaf, just remove
			if (pred->left == to_rem) {
				pred->left = NULL;
			} else {
				pred->right = NULL;
			}
		} else if (has_one_child(to_rem)) { // one child
			if (pred->left == to_rem) {
				if (succ == NULL) {
					pred->left = to_rem->left;
				} else {
					pred->left = succ;
					if (pred_succ != to_rem) {
						succ->right = to_rem->right;
					}
				}
			} else {
				if (succ == NULL) {
					pred->right = to_rem->left;
				} else {
					pred->right = succ;
					if (pred_succ != to_rem) {
						succ->right = to_rem->right;
					}
				}
			}
		} else { // two children
			if (pred->left == to_rem) {
				pred->left = succ;
			} else {
				pred->right = succ;
			}
			if (pred_succ != to_rem) {
				succ->left = to_rem->left;
				succ->right = to_rem->right;
			}
		}
	}
	
	to_rem->left = NULL;
	to_rem->right = NULL;

	memset(to_rem, 0, sizeof(bst_node));
	free(to_rem);
	--t->size;
	return 0;
}

bst_node *
_bst_predecessor(bst_node *node, int data)
{ 

	if (((node->left != NULL) && (node->left->data == data)) || 
			((node->right != NULL) && (node->right->data == data))) {
		return node;
	}

	if (node->data > data) {
		return _bst_predecessor(node->left, data);
	}

	if(node->data < data) {
		return _bst_predecessor(node->right, data);
	}

	return NULL;
}

bst_node *
_bst_find(bst_node *node, int data)
{
	if (node == NULL) {
		return NULL;
	}

	if (node->data == data) {
		return node;
	} else if (node->data > data) {
		return _bst_find(node->left, data);
	} else {
		return _bst_find(node->right, data);
	}
}

bst_node *
_bst_successor(bst_node *node)
{
	if (node->right == NULL) {
		return NULL;
	}

	bst_node *tmp = node->right;
	while (tmp->left != NULL) {
		tmp = tmp->left;
	}
	return tmp;
}

bst_node *
_bst_min(bst *t)
{
	if (t == NULL) {
		return NULL;
	}

	if (bst_size(t) == 0) {
		return NULL;
	}
	
	if (t->root == NULL) {
		return NULL;
	}
	bst_node *tmp = t->root;
	while (tmp->left != NULL) {
		tmp = tmp->left;
	}

	return tmp;
}

bst_node *
_bst_max(bst *t)
{
	if (bst_size(t) == 0) {
		return NULL;
	}

	bst_node *tmp = t->root;
	while (tmp->right != NULL) {
		tmp = tmp->right;
	}

	return tmp;
}

