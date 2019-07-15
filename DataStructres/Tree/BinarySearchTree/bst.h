/******************
*			bst.h
******************/

#ifndef _BST_H_
#define _BST_H_

/* `DUPS' and `NDUPS' are used to allow or
 * not allow duplicate elements
 */
#define DUPS 1
#define NDUPS 0

typedef struct _bst_node {
	int 							data;
	struct _bst_node 	*left;
	struct _bst_node 	*right;
} bst_node;

typedef struct _bst {
	int 			allow_dups;
	int				size;
	bst_node	*root;
} bst;

void bst_init(bst **t, int allow_dups);

int bst_insert(bst *t, int data);

int bst_remove(bst *t, int data);

int bst_contains(bst *t, int data);

int bst_min(bst *t);

int bst_max(bst *t);

void bst_destroy(bst *t);

void print_bst(bst *t);

int _bst_insert(bst *t, bst_node *root, bst_node *curr);
int _bst_remove(bst *t, int data);
bst_node *_bst_predecessor(bst_node *node, int data);
bst_node *_bst_find(bst_node *node, int data);
bst_node *_bst_successor(bst_node *node);
bst_node *_bst_min(bst *t);
bst_node *_bst_max(bst *t);
void _print_bst(bst_node *node);

#define bst_size(t) ((t)->size)
#define bst_data(node) ((node)->data)
#define bst_empty(t) ((t)->size == 0)
#define is_leaf(node) ((((node)->left) == NULL) && (((node)->right) == NULL))
#define has_one_child(node) ((((node)->left) == NULL && ((node)->right != NULL)) \
														|| ((((node)->right) == NULL) && (((node)->left) != NULL)))
#endif /* _BST_H_ */

