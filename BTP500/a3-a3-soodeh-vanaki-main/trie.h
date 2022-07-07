/************************************/
/**** Assignment 3 ******************/
/**** Soodeh Vanaki *****************/
/**** SID: 075782128 ****************/
/**** Email: svanaki@myseneca.ca ****/
/************************************/
/************************************/
/************************************/

#include <string>

// define number of pointers in each node
#define NUMOFPOINTERS 26

	class Trie {

		struct Node {
			bool terminal_;
			Node* children_[NUMOFPOINTERS];
		};
		
		Node* root_;

		struct Node* createNode(void) {
			Node* newNode = new Node;
			newNode->terminal_ = false;
			for (int i = 0; i < NUMOFPOINTERS; i++) {
				newNode->children_[i] = nullptr;
			}
			return newNode;
		}
		
	public:

		Trie(std::string data[], int sz);
		void addWord(const std::string& newWord);
		bool lookup(const std::string& word) const;
		int suggestionsRec(const Node* root, const std::string& currPartialWord, std::string suggestions[], int count) const;
		int suggest(const std::string& partialWord, std::string suggestions[]) const;
		void removeRecursive(Node* curr);
		~Trie();
				
	};
