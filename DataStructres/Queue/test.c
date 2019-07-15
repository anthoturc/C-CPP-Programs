#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "queue.h"

int
main()
{
	queue *q;
	queue_init((queue **)&q);

	for (int i = 1; i <= 6; ++i) {
		queue_enqueue(q, i);
	}
	print_queue(q);
	queue_dequeue(q);
	print_queue(q);
	printf("%d\n", queue_first(q));
	queue_enqueue(q, 30);
	queue_dequeue(q);
	queue_dequeue(q);
	print_queue(q);
	queue_destroy(q);

	return 0;
}

