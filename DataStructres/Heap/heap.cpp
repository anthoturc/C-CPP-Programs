#include <vector>
#include <iostream>
#include "heap.hpp"

Heap::Heap() {}

int 
Heap::size()
{
	return heaparr.size();
}

int 
Heap::parent(unsigned int i) 
{
	if (i <= 0 || i >= heaparr.size()) {
		return -1;
	}

	return (i-1)/2;
}

int 
Heap::left(int i)
{
	unsigned int l = 2*i+1;
	if (l >= heaparr.size()) {
		return -1;
	}

	return l;
}

int
Heap::right(int i)
{
	unsigned int r = 2*i+2;
	if (r >= heaparr.size()) {
		return -1;
	}

	return r;
}

void
Heap::insert(int x)
{
	heaparr.push_back(x);

	int i = heaparr.size()-1;
	int p = 0;

	while (true) {
		p = parent(i);
		if (p == -1) break;
		if (heaparr[i] < heaparr[p]) {
			swap(i, p);
			i = p;
		} else {
			break;
		}
	}
}

int
Heap::remove_min()
{
	int last = heaparr.size()-1;

	if (last == -1) return -1;
	if (last == 0) {
		int retval = heaparr[0];
		heaparr.pop_back();
		return retval;
	}

	int oldmin = heaparr[0];
	swap(0, last);
	heaparr.pop_back();
	print_heap();

	int l, r;
	int p = 0;
	while (true) {
		l = left(p);
		r = right(p);

		std::cout <<  "left " << l << std::endl;
		std::cout <<  "right " << r << std::endl;
		
		if (l == -1) break;

		if (heaparr[l] < heaparr[p] &&
			r != -1 && heaparr[r] > heaparr[l]) {
				swap(p, l);
				p = l;
		} else if (r != -1 && heaparr[r] < heaparr[p] &&
			heaparr[l] > heaparr[r]) {
				swap(p, r);
				p = r;
		} else  {
			break;
		}
		
	}

	return oldmin;
}

int
Heap::peek()
{
	if (heaparr.size() == 0) return 10000000;
	return heaparr[0];
}

void
Heap::swap(int i, int j)
{
	int tmp = heaparr[i];
	heaparr[i] = heaparr[j];
	heaparr[j] = tmp;
}

void 
Heap::print_heap()
{
	for (auto p = heaparr.begin(); p != heaparr.end(); ++p) {
		std::cout << *p << " ";
	}
	std::cout << std::endl;
}