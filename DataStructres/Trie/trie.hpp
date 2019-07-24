/******************
*			trie.hpp
*******************/

// NOTE: assumes that all strings are lowercase
// and that the alphabet is the enlglish one
#ifndef _TRIE_H_

#include <string>

#define ALPHA_SZ 26

class Trie
{
public:
	Trie *children[ALPHA_SZ];
	bool isLeaf;

	Trie();

	void insert(std::string s);
	bool search(std::string s);
	bool remove(std::string s);

private:
	bool aux_remove(Trie **t, std::string s);
	bool hasChildren(Trie const * t);
};

#endif /* _TRIE_H_ */