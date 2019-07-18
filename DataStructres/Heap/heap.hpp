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
	bool is_empty();
	static Heap heapify(int arr[]);
	static Heap heapify(std::vector<int>& vec);

private:
	std::vector<int> heaparr;
	static int MIN = std::numeric_limits<int>::min();
	int parent(int idx);
	int left_child(int idx);
	int right_child(int idx);
	void swap(std::vector<int>& vec);
	void swap(int arr[]);
};


#endif /* _HEAP_H_ */