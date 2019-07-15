#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "queue.h"

void 
queue_init(queue **q)
{
	if ((*q = (queue *)malloc(sizeof(queue))) == NULL) {
		perror("queue.c: malloc in queue_init @ line 11\n");
		return;
	}

	list_init((list **)&((*q)->l));
}

int
queue_enqueue(queue *q, int data)
{
	return list_append(q->l, data);
}

int 
queue_dequeue(queue *q)
{
	return list_rem(q->l, _queue_head(q));
}

void
queue_destroy(queue *q)
{
	list_destroy(q->l);
	free(q);
}

void
print_queue(queue *q)
{
	print_list(q->l);
}

