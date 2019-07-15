#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>


#include "bst.h"

int 
main()
{
	srand(time(0));
	bst *t;
	bst_init((bst **)&t, NDUPS);

	for (int i = 1; i < 15; ++i) {
		int n = rand()%100 + 1;
		bst_insert(t, n);
	}
	bst_insert(t, 105);
	print_bst(t);
	
	int i;
	printf("Enter a number to remove: ");
	scanf("%d", &i);
	bst_remove(t, i);
	print_bst(t);

	bst_destroy(t);
	return 0;
}

