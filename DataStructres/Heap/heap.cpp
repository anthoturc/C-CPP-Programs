#include <vector>
#include <limits>

#include "heap.hpp"

Heap::Heap() {}

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
	int size = heaparr.size();
	heaparr[size-1] = n;
}