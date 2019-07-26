#ifndef _HEAP_H_
#define _HEAP_H_

#include <vector>

class Heap
{
public:

	Heap();

	int size();
	void insert(int x);
	int remove_min();
	int peek();

	void print_heap();

private:
	std::vector<int> heaparr;

	int parent(unsigned int i);
	int left(int i);
	int right(int i);
	void swap(int i, int j);
};

#endif /* _HEAP_H_ */