/*************************
*				stack.h
*************************/

#ifndef _STACK_H_
#define _STACK_H_

#include "list.h"

typedef struct _stack {
	list* l;
} stack;

void stack_init(stack **s);

int stack_push(stack *s, int data);

int stack_pop(stack *s);

void stack_destroy(stack *s);

void print_stack(stack *s);

#define stack_size(s) (((s)->l)->size)
#define stack_top(s) (((s)->l)->head->data)
#define _stack_head(s) (((s)->l)->head)

#endif /* _STACK_H_ */

