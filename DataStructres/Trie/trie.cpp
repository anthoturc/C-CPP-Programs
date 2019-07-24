#include <string>
#include "trie.hpp"

Trie::Trie()
{
	isLeaf = false;

	for (int i = 0; i < ALPHA_SZ; ++i) {
		children[i] = nullptr;
	}
}

void
Trie::insert(std::string s)
{
	if (s.empty()) return;

	int sLen = s.length();
	Trie *t = this;

	for (int i = 0; i < sLen; ++i) {
		if (!(t->children[s[i]-'a'])) {
			t->children[s[i]-'a'] = new Trie;
		}

		t = t->children[s[i]-'a'];
	}

	t->isLeaf = true;
}

bool
Trie::search(std::string s)
{
	if (s.empty()) return false;

	int sLen = s.length();
	Trie *t = this;

	for (int i = 0; i < sLen; ++i) {
		t = t->children[s[i]-'a'];

		if (!t) {
			return false;
		}
	}

	return t->isLeaf;
}


bool 
Trie::remove(std::string s)
{
	if (s.empty()) return false;

	return aux_remove((Trie **)this, s);
}


bool
Trie::aux_remove(Trie ** t, std::string s)
{
	if ((*(t))) {
		int sLen = s.length();
		if (sLen) {
			if ((*(t))->children[s[0]-'a'] != nullptr && 
					aux_remove(&((*(t))->children[s[0]-'a']), s.substr(1)) &&
					(*(t))->isLeaf == false) {

				if (!hasChildren((*(t)))) {
					delete (*(t));
					(*(t)) = nullptr;
					return true;
				} else {
					return false;
				}

			}
		}

		if (sLen == 0 && (*(t))->isLeaf) {
			if (!hasChildren((*(t)))) {
				delete (*(t));
				(*(t)) = nullptr;
			} else {
				(*(t))->isLeaf = false;
			}
			return true;
		}
	}
	return false;
}

bool
Trie::hasChildren(Trie const * t)
{
	for (int i = 0; i < ALPHA_SZ; ++i) {
		if (t->children[i]) {
			return true;
		}
	}
	return false;
}