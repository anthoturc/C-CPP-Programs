#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dlist.h"

int
main()
{
	dlist *l;
	dlist_init((dlist **)&l);
	for (int i = 1; i <=10; ++i) {
		dlist_append(l, i);
	}
	print_dlist(l);
	
	for (int i = 11; i <= 20; ++i) {
		dlist_prepend(l, i);
	}
	print_dlist(l);

	dlist_destroy(l);
	return 0;
}
