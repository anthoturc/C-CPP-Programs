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
		return MIN;
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
		return MIN;
	}
	
	return heaparr[0];
}

void
Heap::sift(int idx)
{
	int curr = idx;
	int curr_parent = parent(curr);
	while (heaparr[curr] > heaparr[curr_parent]) {
		swap(heaparr, curr, curr_parent);	
		curr = curr_parent;
		curr_parent = parent(curr);	
	}
}

void
Heap::insert(int n)
{
	/* Inserts should take place at the last location in the heap! */
	heaparr.push_back(n);
	sift(heaparr.size()-1);
}

void
Heap::swap(std::vector<int>& vec, int i, int j)
{
	int tmp = vec[i];
	vec[i] = vec[j];
	vec[j] = tmp;
}

Heap
Heap::heapify(std::vector<int>& vec)
{
	int size = vec.size();
	Heap h;
	for (int i = 0; i < size; ++i) {
		h.insert(vec[i]);
	}

	return h;
}

Heap
Heap::heapify(int arr[], int n)
{
	int size = n;
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

int 
Heap::size()
{
	return heaparr.size();
}

int
Heap::remove_max()
{
	int size = heaparr.size();

	if (size == 0) {
		return MIN;
	}
	if (size == 1) {
		int res = heaparr[0];
		heaparr.clear();
		return res;
	}

	int old_max = heaparr[0];
	heaparr[0] = heaparr[size-1];
	heaparr.erase(heaparr.end()-1, heaparr.end());

	int curr = 0;
	int lc = left_child(curr);
	int rc = right_child(curr);

	while (heaparr[curr] < heaparr[lc] ||
			heaparr[curr] < heaparr[rc]) {
		
		if (heaparr[curr] < heaparr[lc]) {
			swap(heaparr, curr, lc);
			curr = lc;
			lc = left_child(curr);
		}

		if (heaparr[curr] < heaparr[rc]) {
			swap(heaparr, curr, rc);
			curr = rc;
			rc = right_child(curr);
		}

		if (rc == MIN || lc == MIN) {
			break;
		}
	}

	return old_max;
}

int
Heap::increase_key(int oldkey, int newkey)
{
	int i = 0;
	int size = heaparr.size();
	for (; i < size; ++i) {
		if (heaparr[i] == oldkey) {
			break;
		}
	}

	if (i == 0 && heaparr[0] != oldkey) {
		return MIN;
	}

	heaparr[i] = newkey;
	sift(i);
	return newkey;
}