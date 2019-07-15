#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "stack.h"

int
main()
{
	stack *s;
	stack_init((stack **)&s);
	for (int i = 0; i < 5; ++i) {
		stack_push(s, i);
	}
	print_stack(s);
	stack_pop(s);
	print_stack(s);

	return 0;
}
