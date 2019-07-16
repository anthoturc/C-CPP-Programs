/*****************
*			heap.hpp
******************/

#ifndef _HEAP_H_
#define _HEAP_H_

#include <vector>
#include <limits>

class Heap
{
public:
	Heap();
	~Heap();

	int peek();
	void insert(int n);
	int remove_max();
	int delete_max();
	int size();
	int increase_key(int oldkey, int newkey);
	int is_empty();
	static Heap heapify(int arr[]);

private:
	std::vector<int> heaparr;
	static int MIN = std::numeric_limits<int>::min();
	int parent(int idx);
	int left_child(int idx);
	int right_child(int idx);
};


#endif /* _HEAP_H_ */