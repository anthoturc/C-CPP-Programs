/********************
*			queue.h
********************/

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "list.h"

typedef struct _queue {
	list *l;
} queue;

void queue_init(queue **q);

int queue_enqueue(queue *q, int data);

int queue_dequeue(queue *q);

void queue_destroy(queue *q);

void print_queue(queue *q);

#define queue_size(q) (((q)->l)->size);
#define queue_first(q) (((q)->l)->head->data)
#define _queue_head(q) (((q)->l)->head)

#endif /* _QUEUE_H_ */

