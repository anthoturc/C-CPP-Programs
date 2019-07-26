#include <iostream>
#include <vector>

#include "heap.hpp"

int 
main()
{
	Heap h;

	h.insert(3);
	h.insert(-10);
	h.insert(-12);
	h.insert(10);
	h.insert(15);

	std::cout << "Min is: " << h.peek() << std::endl;
	
	std::cout << "Size is: " << h.size() << std::endl;
	h.print_heap();
	h.remove_min();
	h.print_heap();

	std::cout << "Size is: " << h.size() << std::endl;

	std::cout << "Min is: " << h.peek() << std::endl;

	return 0;
}