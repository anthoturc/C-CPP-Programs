#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../LinkedList/SinglyLinked/list.h"
#include "stack.h"

void 
stack_init(stack **s)
{
	if ((*s = (stack *)malloc(sizeof(stack))) == NULL) {
		perror("stack.c: malloc in stack_init @ line 11\n");
		return;
	}

	/* Initialize list using list_init */
	list_init((list **)(&((*s)->l)));
}

int 
stack_push(stack *s, int data)
{
	return list_prepend(s->l, data);
}

int
stack_pop(stack *s)
{
	return list_rem(s->l, _stack_head(s));
}

void
stack_destroy(stack *s)
{
	list_destroy(s->l);
	free(s);
}

void
print_stack(stack *s)
{
	print_list(s->l);
}
