#include <string>
#include <iostream>

#include "trie.hpp"

int 
main()
{
	Trie *head = new Trie;

	head->insert("boyy");
	head->insert("bobby");
	head->insert("bubby");
	head->insert("lady");
	head->insert("larry");
	head->insert("super");
	head->insert("supra");

	std::cout << "head does " << (head->search("sup") ? "": "not ") << "contain sup" << std::endl;
	std::cout << "head does " << (head->search("bob") ? "": "not ") << "contain bob" << std::endl;
	std::cout << "head does " << (head->search("larry") ? "": "not ") << "contain larry" << std::endl;
	std::cout << "head does " << (head->search("super") ? "": "not ") << "contain super" << std::endl;


	std::cout << "removed super? " << head->remove("super") << std::endl;
	std::cout << "contains supra? " << head->search("supra") << std::endl;

	return 0;
}