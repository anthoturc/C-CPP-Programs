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
	Heap(std::vector<int> vec);
	~Heap();

	int peek();
	void insert(int n);
	int remove_max();
	int size();
	int increase_key(int oldkey, int newkey);
	bool is_empty();
	static Heap heapify(int arr[], int n);
	static Heap heapify(std::vector<int>& vec);

private:
	std::vector<int> heaparr;
	static const int MIN = std::numeric_limits<int>::min();
	int parent(int idx);
	int left_child(int idx);
	int right_child(int idx);
	void swap(std::vector<int>& vec, int i, int j);
	void swap(int arr[], int n, int i, int j);
	void sift(int idx);
};


#endif /* _HEAP_H_ */