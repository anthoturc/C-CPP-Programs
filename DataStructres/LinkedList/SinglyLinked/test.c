#include <stdlib.h>
#include <string.h>

#include "list.h"

int 
main()
{
	list *l = NULL;
	list_init(&l);

	for (int i = 1; i <= 10; ++i) {
		list_append(l, i);
	}

	print_list(l);

	for (int i = 1; i <= 10; ++i) {
		list_prepend(l, i);
	}

	print_list(l);

	return 0;
}
