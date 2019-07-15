#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clist.h"

int
main()
{
	clist *l;
	clist_init((clist **)&l);

	for (int i = 1; i < 10; ++i) {
		clist_ins(l, i);
	}
	print_clist(l);
	clist_destroy(l);
	return 0;
}
