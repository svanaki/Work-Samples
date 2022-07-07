/****************************************/
/****************************************/
/****** Soodeh Vanaki *******************/
/****** SID: 075782128 ******************/
/****** Email: svanaki@myseneca.ca ******/
/****************************************/
/****************************************/
/****************************************/

#include <iostream>
#include <iomanip>

/*forward declaration*/
template <class T>
class Queue;

template <class T>
class BST {
	struct Node {
		T data_;
		Node* left_;
		Node* right_;
		Node(const T& data, Node* lt = nullptr, Node* rt = nullptr) {
			data_ = data;
			left_ = lt;
			right_ = rt;
		}
	};
	Node* root_;

	void printPreOrder(Node* subroot)const {
		if (subroot) {
			std::cout << subroot->data_ << " ";
			printPreOrder(subroot->left_);
			printPreOrder(subroot->right_);
		}
	}
	void printInOrder(Node* subroot)const {
		if (subroot) {
			printInOrder(subroot->left_);
			std::cout << subroot->data_ << " ";
			printInOrder(subroot->right_);
		}
	}
	void destroy(Node* subroot) {
		if (subroot) {
			destroy(subroot->left_);
			destroy(subroot->right_);
			delete subroot;
		}
	}

	bool isSame(const Node* left, const Node* right) const;

	/*used by print() to print all nodes at same level*/
	void printLine(Node* data[], int numNodes, int width) const {
		int half = width / 2;
		int firsthalf = width % 2 ? half + 1 : half;

		if (numNodes > 1) {
			for (int i = 0; i < numNodes; i++) {
				if (i % 2 == 0) {
					if (data[i]) {
						std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << "-";
						std::cout << std::left << std::setfill('-') << std::setw(half) << "-";
					}
					else {
						std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
						std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
					}
				}
				else {
					if (data[i]) {
						std::cout << std::right << std::setfill('-') << std::setw(firsthalf) << "-";
						std::cout << std::left << std::setfill(' ') << std::setw(half) << "-";
					}
					else {
						std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
						std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
					}
				}
			}
			std::cout << std::endl;
		}
		for (int i = 0; i < numNodes; i++) {
			if (data[i]) {
				if (i % 2 == 0) {
					std::cout << std::right << std::setw(firsthalf) << "|";
					std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
				}
				else {
					std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
					std::cout << std::left << std::setfill(' ') << std::setw(half) << "|";
				}
			}
			else {
				std::cout << std::left << std::setfill(' ') << std::setw(width) << " ";
			}
		}
		std::cout << std::endl;
		for (int i = 0; i < numNodes; i++) {
			if (data[i]) {
				if (i % 2 == 0) {
					std::cout << std::right << std::setw(firsthalf) << data[i]->data_;
					std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
				}
				else {
					std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
					std::cout << std::left << std::setfill(' ') << std::setw(half) << data[i]->data_;
				}
			}
			else {
				std::cout << std::left << std::setfill(' ') << std::setw(width) << " ";
			}
		}
		std::cout << std::endl;

	}

    // Recursive function to get the depth of each node 
	int getDepthRecursive(Node* node, const T& data, int level)
	{
		if (node != nullptr) {

			if (node->data_ == data)
			{
				return level;
			}

			int downlevel = getDepthRecursive(node->left_, data, level + 1);
			if (downlevel > 0)
				return downlevel;

			downlevel = getDepthRecursive(node->right_, data, level + 1);
			if (downlevel > 0)
				return downlevel;
		}
		return -1;
	}

	// Detaching function: receive a pointer to a node
	// and detach and remove the smallest node in this subtree
	Node* detachInorderSuccessor(Node*& subRoot) {
		if (subRoot->left_ == nullptr)
		{
			Node* rc = subRoot;
			subRoot = subRoot->right_;
			return rc;
		}
		else
			return detachInorderSuccessor(subRoot->left_);
	}

	// Recursive function for remove
	void removeRecursive(const T& data, Node*& subRoot) {
		if (subRoot != nullptr) {
			if (data == subRoot->data_) {
				Node* rm = subRoot;   //make a temp to subRoot so I 
									//don't lose it by accident
				//subroot is a leaf node
				if (subRoot->left_ == nullptr && subRoot->right_ == nullptr) {
					//null out pointer from parent
					subRoot = nullptr;
				}
				else if (subRoot->left_ != nullptr && subRoot->right_ == nullptr) {
					//one child on left
					subRoot = subRoot->left_;
				}
				else if (subRoot->right_ != nullptr && subRoot->left_ == nullptr) {
					//one child on right
					subRoot = subRoot->right_;
				}
				else {
					Node* inorderSuccesor = detachInorderSuccessor(subRoot->right_);
					inorderSuccesor->left_ = subRoot->left_;
					inorderSuccesor->right_ = subRoot->right_;
					subRoot = inorderSuccesor;
				}


				delete rm;
			}
			else if (data < subRoot->data_) {
				removeRecursive(data, subRoot->left_);
			}
			else {
				removeRecursive(data, subRoot->right_);
			}
		}

	}

	// Recursive function to do the deep copy for copy constructor
	Node* copyNode(Node*& currentRoot, Node* cpyRoot)
	{
		if (cpyRoot != nullptr)
		{
			currentRoot = new Node(cpyRoot->data_);
			copyNode(currentRoot->right_, cpyRoot->right_);
			copyNode(currentRoot->left_, cpyRoot->left_);
			return currentRoot;
		}
		else
			return nullptr;
	}


public:
	BST() {
		root_ = nullptr;
	}
	BST(const BST& rhs) {

		root_ = copyNode(root_, rhs.root_);

	}
	void remove(const T& data) {

		removeRecursive(data, root_);

	}

	int depth(const T& data) {

		return getDepthRecursive(root_, data, 0);

	}


	void printPreOrder() const {
		printPreOrder(root_);
		std::cout << std::endl;
	}
	void printInOrder() const {
		printInOrder(root_);
		std::cout << std::endl;
	}


	void insert(const T& data) {
		if (root_ == nullptr) {
			root_ = new Node(data);
		}
		else {

			Node* curr = root_;
			while (curr != nullptr) {
				if (data < curr->data_) {
					//go left
					if (curr->left_) {
						curr = curr->left_;
					}
					else {
						curr->left_ = new Node(data);
						curr = nullptr;
					}
				}
				else {
					//go right
					if (curr->right_) {
						curr = curr->right_;
					}
					else {
						curr->right_ = new Node(data);
						curr = nullptr;
					}
				}
			}

		}

	}

	bool operator==(const BST& rhs) const;
	void print() const {
		struct Output {
			Node* node_;
			int lvl_;
			int position_;
			Output(Node* n = nullptr, int l = 0, int p = 0) {
				node_ = n;
				lvl_ = l;
				position_ = p;
			}
			void set(Node* n = nullptr, int l = 0, int p = 0) {
				node_ = n;
				lvl_ = l;
				position_ = p;
			}
		};
		Queue<Output> theNodes;
		Node* line[16];
		if (root_) {
			for (int i = 0; i < 16; i++) {
				line[i] = nullptr;
			}
			theNodes.enqueue(Output(root_, 0, 0));
			int currline = 0;
			int width = 80;
			int numInLine = 1;
			while (theNodes.isEmpty() == false) {
				Output curr = theNodes.front();
				if (curr.node_->left_)
					theNodes.enqueue(Output(curr.node_->left_, curr.lvl_ + 1, curr.position_ * 2));
				if (curr.node_->right_)
					theNodes.enqueue(Output(curr.node_->right_, curr.lvl_ + 1, curr.position_ * 2 + 1));
				theNodes.dequeue();


				if (curr.lvl_ > currline) {
					printLine(line, numInLine, width);
					width = width / 2;
					numInLine = numInLine * 2;
					for (int i = 0; i < 16; i++) {
						line[i] = nullptr;
					}
					currline++;

				}
				line[curr.position_] = curr.node_;
			}
			printLine(line, numInLine, width);
			std::cout << std::endl;

		}
		else {
			std::cout << "tree is empty" << std::endl;
		}
	}
	~BST() {
		destroy(root_);
	}
};

template <class T>
class Queue {
	T* theQueue_;
	int capacity_;
	int used_;
	int front_;
	int back_;
	void grow() {
		T* tmp = new T[capacity_ * 2];
		int j;
		for (int i = 0, j = front_; i < used_; i++, j = (j + 1) % capacity_) {
			tmp[i] = theQueue_[j];
		}
		delete[] theQueue_;
		theQueue_ = tmp;
		capacity_ = capacity_ * 2;
		front_ = 0;
		back_ = used_;
	}
public:
	Queue() {
		theQueue_ = new T[50];
		capacity_ = 50;
		used_ = 0;
		front_ = 0;
		back_ = 0;
	}
	void enqueue(const T& data) {
		if (used_ == capacity_) {
			grow();
		}
		theQueue_[back_] = data;
		back_ = (back_ + 1) % capacity_;
		used_++;
	}
	void dequeue() {
		if (!isEmpty()) {
			used_--;
			front_ = (front_ + 1) % capacity_;
		}
	}
	T front() const {
		if (!isEmpty()) {
			return theQueue_[front_];
		}
		return T{};

	}
	bool isEmpty() const {
		return used_ == 0;
	}
	~Queue() {
		delete[] theQueue_;
	}
};