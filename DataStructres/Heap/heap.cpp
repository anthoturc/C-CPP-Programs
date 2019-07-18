#include <vector>
#include <limits>

#include "heap.hpp"

Heap::Heap() {}

Heap::Heap(std::vector<int> vec) {
	heaparr = vec;
}

Heap::~Heap() {}

int
Heap::parent(int idx)
{
	if (heaparr.empty()) {
		return MIN
	}

	int size = heaparr.size();

	if (idx < 0 || idx >= size) {
		return MIN;
	} else if (idx == 0) {
		return 0;
	} else {
		return (idx-1)/2;
	}
}

int
Heap::left_child(int idx)
{

	if (heaparr.empty() || idx < 0) {
		return MIN;
	}
	
	int size = heaparr.size();
	int child_idx = 2*idx+1;

	if (child_idx >= size) {
		return MIN;
	}

	return child_idx;
}

int
Heap::right_child(int idx)
{

	if (heaparr.empty() || idx < 0) {
		return MIN;
	}

	int size = heaparr.size();
	int child_idx = 2*idx + 2;

	if (child_idx >= size) {
		return MIN;
	}

	return child_idx;
}

int 
Heap::peek() 
{
	if (heaparr.empty()) {
		return MIN
	}
	
	return heaparr[0];
}

void
Heap::insert(int n)
{
	/* Inserts should take place at the last location in the heap! */
	heaparr.push_back(n);

	int curr = vec.size()-1;
	int curr_parent = parent(curr)
	while (vec[curr] > vec[curr_parent]) {
		swap(vec, curr, curr_parent);	
		curr = curr_parent;
		curr_parent = parent(curr);	
	}
}

void
Heap::swap(std::vector<int>& vec, int i, int j)
{
	int tmp = vec[i];
	vec[i] = vec[j];
	vec[j] = vec[i];
}

static Heap
Heap::heapify(std::vector<int> vec)
{
	int size = vec;
	Heap h;
	for (int i = 0; i < size; ++i) {
		h.insert(vec[i]);
	}

	return h;
}

static Heap
Heap::heapify(int arr[])
{
	int size = sizeof(arr)/sizeof(*a);
	Heap h;
	for (int i = 0; i < size; ++i) {
		h.insert(arr[i]);
	}

	return h;
}

bool
Heap::is_empty()
{
	return heaparr.size() == 0;
}