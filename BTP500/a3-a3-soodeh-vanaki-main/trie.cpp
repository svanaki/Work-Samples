/************************************/
/**** Assignment 3 ******************/
/**** Soodeh Vanaki *****************/
/**** SID: 075782128 ****************/
/**** Email: svanaki@myseneca.ca ****/
/************************************/
/************************************/
/************************************/

#include "trie.h"

// 2 argument Constructor 
// set the data to the nodes
Trie::Trie(std::string data[], int sz)
{
	root_ = new Node();

	for (int i = 0; i < NUMOFPOINTERS; i++) {
		root_->children_[i] = nullptr;
	}

	for (int i = 0; i < sz; i++) {
		addWord(data[i]);
	}
	
}

// Add newword to the Trie
void Trie::addWord(const std::string& newWord)
{
	Node* curr = root_;
	for (int i = 0; i < newWord.length(); i++) {
		int index = newWord[i] - 'a';
		if (!curr->children_[index]) {
			curr->children_[index] = createNode();
		}
		curr = curr->children_[index];
	}
	curr->terminal_ = true;
}

// Looks up the word in the Trie object. If it is in the Trie object, true is returned.
bool Trie::lookup(const std::string& word) const
{
	Node* curr = root_;
	for (int i = 0; i < word.length(); i++) {
		int index = word[i] - 'a';
		if (!curr->children_[index]) {
        	return false;
		}
		curr = curr->children_[index];
	}
	return (curr != NULL && curr->terminal_);
}

// Recursive suggest function which will be used in suggest function. It will return the number of 
// possible suggestion and store them in a string array alphabetically.
int Trie::suggestionsRec(const Node* root, const std::string& currPartialWord, std::string suggestions[], int count) const
{
	if (root->terminal_) {
		suggestions[count++] = currPartialWord;
	}

	for (int i = 0; i < NUMOFPOINTERS; i++) {
		if (root->children_[i]) {
			count = suggestionsRec(root->children_[i], currPartialWord + (char)(97 + i), suggestions, count);
		}
	}
	return count;
}

// Given a string, this function will find all words that start with the string partialWord within 
// the Trie object and store them into suggestions in alphabetical order. The Function returns number 
// of words stored within suggestions.
int Trie::suggest(const std::string& partialWord, std::string suggestions[]) const
{
	int count = 0;
	Node* curr = root_;

	for (int i = 0; i < partialWord.length(); i++) {
		int index = partialWord[i] - 'a';
		if (!curr->children_[index]) {
			return 0;
		}
		curr = curr->children_[index];
	}
	
	if (curr == NULL) {
		return 0;
	}
	count = suggestionsRec(curr, partialWord, suggestions, 0);

	return count;
}

// Recursive function to delete the Nodes in order. will be used in destructor
void Trie::removeRecursive(Node* curr) {

	for (int i = 0; i < NUMOFPOINTERS; i++) {
		if (curr->children_[i] != nullptr) {
			removeRecursive(curr->children_[i]);
		}
	}
	delete curr;

}

// Destructor
Trie::~Trie()
{
	Node* curr = root_;
	removeRecursive(curr);
}




