/*******************************************************************/
/*                                                                 */
/*  A1 Part 2: CacheList starter file                              */
/*                                                                 */
/*  Author Name: Soodeh Vanaki	 	 							   */
/*      - class/function list: everything :)                       */
/*                                                                 */
/*  version 1.1: minor changes to add {} so that it compiles       */
/*               without syntax errors as is with tester           */
/*******************************************************************/

template <typename T>

class CacheList {
	struct Node {
		int access_;
		T data_;		
		Node* next_;		
		Node* prev_;		
		// Struct Constructor
		Node(const T& data = T{}, int acc = 0, Node* nx = nullptr, Node* pr = nullptr) {
			data_ = data;
			access_ = acc;		// set the access to 0
			next_ = nx;
			prev_ = pr;
		}
	};
	Node* front_;		
	Node* back_;
	int size_;		// to access the size of the list

public:
	class const_iterator {
		friend class CacheList;
		Node* curr_;
		const CacheList* owner_;
		const_iterator(Node* n, const CacheList* theList) {
			curr_ = n;
			owner_ = theList;
		}
	public:
		const_iterator() {
			curr_ = nullptr;
			owner_ = nullptr;
		}

		// Advances to next node in list if iterator is not currently at end(). Returns iterator to current node
		const_iterator operator++() {
			//++x
			curr_ = curr_->next_;
			return *this;
		}

		// Advances to next node in list if iterator is not currently at end(). Returns iterator to node before the increment
		const_iterator operator++(int) {
			//x++
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}

		// Goes back to previous node. Returns iterator to current node
		const_iterator operator--() {
			if (owner_) {
				if (curr_) {
					curr_ = curr_->prev_;
				}
				else {
					curr_ = owner_->back_;
				}
			}
			return *this;
		}

		// Goes back to previous node. Returns iterator to node before the decrement
		const_iterator operator--(int) {
			const_iterator old = *this;
			if (owner_) {
				if (curr_) {
					curr_ = curr_->prev_;
				}
				else {
					curr_ = owner_->back_;
				}
			}
			return old;
		}

		// Returns true if rhs and current object refer to the same node
		bool operator==(const_iterator rhs) {
			bool rc = false;
			if (rhs.curr_ == curr_) {
				rc = true;
			}
			return rc;
		}

		// Returns true if rhs and current object does not refer to the same node
		bool operator!=(const_iterator rhs) {
			bool rc = false;
			if (rhs.curr_ != curr_) {
				rc = true;
			}
			return rc;
		}

		// Returns a const reference to data in the node referred to by the iterator.
		const T& operator*()const {
			return this->curr_->data_;
		}
	};
	class iterator :public const_iterator {
		friend class CacheList;
		iterator(Node* n, const CacheList* theList) : const_iterator(n, theList) {}
	public:
		iterator() : const_iterator() {}

		// Advances to next node in list if iterator is not currently at end(). Returns iterator to current node
		iterator operator++() {
			//++x
			this->curr_ = this->curr_->next_;
			return *this;
		}

		// Advances to next node in list if iterator is not currently at end(). Returns iterator to node before the increment
		iterator operator++(int) {
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}

		// Goes back to previous node. Returns iterator to current node
		iterator operator--() {
			if (this->owner_) {
				if (this->curr_) {
					this->curr_ = this->curr_->prev_;
				}
				else {
					this->curr_ = this->owner_->back_;
				}
			}
			return *this;
		}

		// Goes back to previous node. Returns iterator to node before the decrement
		iterator operator--(int) {
			iterator old = *this;
			if (this->owner_) {
				if (this->curr_) {
					this->curr_ = this->curr_->prev_;
				}
				else {
					this->curr_ = this->owner_->back_;
				}
			}
			return old;
		}

		// Returns a reference to data in the node referred to by the iterator.
		T& operator*() {
			return this->curr_->data_;
		}

		// Returns a const reference to data in the node referred to by the iterator.
		const T& operator*()const {
			return this->curr_->data_;
		}
	};
	CacheList();
	~CacheList();
	CacheList(const CacheList& rhs);
	CacheList& operator=(const CacheList& rhs);
	CacheList(CacheList&& rhs);
	CacheList& operator=(CacheList&& rhs);
	
	// Returns the appropriate iterator to the first node (that contains data) in the list
	iterator begin() {
		if (front_->next_ == back_) {
			return end();
		}
		else {
			return iterator(this->front_->next_, this);
		}
	}

	// Returns the appropriate iterator to the node after the last node in the list
	iterator end() {
		return iterator(this->back_, this);
	}

	// Returns the appropriate const_iterator to the first node (that contains data) in the list 
	const_iterator cbegin() const {
		if (front_->next_ == back_) {
			return cend();
		}
		else {
			return const_iterator(front_->next_, this);
		}
	}

	// Returns the appropriate iterator to the node after the last node in the list
	const_iterator cend() const {
		return const_iterator(back_, this);
	}
	void insert(const T& data);
	iterator search(const T& data);
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);
	void merge(CacheList& other);
	bool empty() const;
	int size() const;
};

// Constructor, creates empty CacheList
template <typename T>
CacheList<T>::CacheList() {
	front_ = new Node();
	back_ = new Node();
	front_ -> next_ = back_;
	back_ -> prev_ = front_;
	size_ = 0;
}

// Destructor, deallocate all nodes
template <typename T>
CacheList<T>::~CacheList() {
	Node* current = front_->next_;
	while (current != back_)
	{
		Node* rm = current;
		current = current->next_;
		delete rm;
		--size_;
	}
	front_->next_ = back_;
	back_->prev_ = front_;
}

// Copy Constructor
template <typename T>
CacheList<T>::CacheList(const CacheList& rhs) {
	front_ = new Node();
	back_ = new Node();

	Node* tempRhs = rhs.front_->next_;
	Node* temp = front_;

	if (rhs.front_->next_ == rhs.back_) {
		front_->next_ = back_;
		back_->prev_ = front_;
	}
	else {
		while (tempRhs != rhs.back_) {
			temp->next_ = new Node(tempRhs->data_, tempRhs->access_, nullptr, temp);
			tempRhs = tempRhs->next_;
			temp = temp->next_;
		}
		temp->next_ = back_;
		back_->prev_ = temp;
	}
	size_ = rhs.size_;
}

// Assignment Operator
template <typename T>
CacheList<T>& CacheList<T>::operator=(const CacheList& rhs) {
		
	Node* tempRhs = rhs.front_->next_;
	Node* temp = front_;

	if (this != &rhs) {
		if (rhs.front_->next_ == rhs.back_) {
			front_->next_ = back_;
			back_->prev_ = front_;
			size_ = 0;
		}
		else {
			Node* c = front_->next_;
			while (c != back_) {
				Node* rm = c;
				c = c->next_;
				delete rm;
				--size_;
			}
			while (tempRhs != rhs.back_) {
				temp->next_ = new Node(tempRhs->data_, tempRhs->access_, nullptr, temp);
				tempRhs = tempRhs->next_;
				temp = temp->next_;
				++size_;
			}
			temp->next_ = back_;
			back_->prev_ = temp;
		}
	}
	return *this;
}

// Move Constructor
template <typename T>
CacheList<T>::CacheList(CacheList&& rhs) {
	
	front_ = new Node();
	back_ = new Node();
	
	front_->next_ = back_;
	back_->prev_ = front_;
	size_ == 0;
	
	*this = rhs;
}

// Move Operator
template <typename T>
CacheList<T>& CacheList<T>::operator=(CacheList&& rhs) {

	if (this != &rhs) {
		Node* temp = front_;
		front_ = rhs.front_;
		rhs.front_ = temp;
		temp = back_;
		back_ = rhs.back_;
		rhs.back_ = temp;
		int t = size_;
		size_ = rhs.size_;
		rhs.size_ = t;
	}
	return *this;
}

// Creates new node holding data at the back of the linked list. This new node will have been accessed 0 times.
template <typename T>
void CacheList<T>::insert(const T& data) {
	Node* newNode = new Node(data, 0, back_, back_->prev_);
	back_->prev_->next_ = newNode;
	back_->prev_ = newNode;
	++size_;
}

// Returns an iterator to the node if found, end() if it is not. search accepts as argument a key of the unknown data type T. The function finds and returns an iterator to the node containing a matching key.
template <typename T>
typename CacheList<T>::iterator CacheList<T>::search(const T& data) {
	
	Node* curr = front_->next_;
	while (curr != back_ && curr->data_ != data) {
		curr = curr->next_;
	}

	if (curr != back_) {
		curr->access_ = curr->access_ + 1;
		curr->prev_->next_ = curr->next_;
		curr->next_->prev_ = curr->prev_;
		curr->next_ = nullptr;
		curr->prev_ = nullptr;

		Node* temp = front_->next_;
		while (temp != back_ && temp->access_ > curr->access_) {
			temp = temp->next_;
		}

		temp->prev_->next_ = curr;
		curr->next_ = temp;
		curr->prev_ = temp->prev_;
		temp->prev_ = curr;

	}
	return iterator(curr, this);
}

// This function removes a node referred to by loc. Function returns an iterator to the node that follows the removed node
template <typename T>
typename CacheList<T>::iterator CacheList<T>::erase(iterator it) {
	CacheList<T>::iterator i;
	Node* rm = it.curr_;
	Node* n = it.curr_->next_;
	for(i = this->begin(); i != this->end(); ++i){
		if (i == it) {
			rm->prev_->next_ = n;
			n->prev_ = rm->prev_;
			delete rm;
			--size_;
		}
	}
	return iterator(n, this);
}

// This function removes all nodes from first to last, including the node referred to by first but not the one referred to by last. function returns an iterator to the node that follows the last removed item.
template <typename T>
typename CacheList<T>::iterator CacheList<T>::erase(iterator first, iterator last) {
	CacheList<T>::iterator i;
	for (i = this->begin(); i != this->end(); i++) {
		Node* from = first.curr_;
		Node* to = first.curr_->next_;
		if (i == first && i != last) {
			from->prev_->next_ = to;
			to->prev_ = from->prev_;
			delete from;
			first++;
			--size_;
		}
	}
	return iterator(last.curr_, this);
}

// This function must be implemented by putting existing nodes together (as opposed to inserting the values of other as new nodes into current list).
template <typename T>
void CacheList<T>::merge(CacheList& other) {

	// This function has 2 version, both are working and functional :)
	// version 1
	/*Node* a;
	Node* b;
	a = front_->next_;
	b = other.front_->next_;
	while (a != back_ && b != other.back_) {
		if (b->access_ > a->access_) {

			//saving the next node
			Node* c = b->next_;

			// unlink from other list
			b->prev_->next_ = b->next_;
			b->next_->prev_ = b->prev_;

			// link in current list
			b->next_ = a;
			b->prev_ = a->prev_;
			a->prev_->next_ = b;
			a->prev_ = b;
			b = c;
		}
		else {
			a = a->next_;
		}
	}
	if (b != other.back_) {
		// unlink from other list
		b->prev_->next_ = b->next_;
		b->next_->prev_ = b->prev_;

		// link in curent list
		b->next_ = back_;
		b->prev_ = back_->prev_;
		back_->prev_->next_ = b;

	}

	other.front_->next_ = other.back_;
	other.back_->prev_ = other.front_;
	size_ = this->size_ + other.size_;
	other.size_ = 0;*/


	// version 2
	/*******************/
	Node* curList;
	Node* otherList;
	curList = front_->next_;
	otherList = other.front_->next_;

	if (curList != back_ && otherList != other.back_) {
		for (otherList; otherList != other.back_; otherList = other.front_->next_) {
			while (otherList->access_ <= curList->access_ && curList != back_) {
				curList = curList->next_;
			}
			// unlink from other list
			otherList->prev_->next_ = otherList->next_;
			otherList->next_->prev_ = otherList->prev_;

			// link in current list
			otherList->next_ = curList;
			otherList->prev_ = curList->prev_;
			curList->prev_->next_ = otherList;
			curList->prev_ = otherList;
			//b = b->next_;
			++size_;
		}
	}
	else if (curList == back_) {
		front_->next_ = other.front_->next_;
		curList->prev_ = other.back_->prev_;
		other.back_->prev_->next_ = curList;
		other.front_->next_->prev_ = front_;

		other.front_->next_ = other.back_;
		other.back_->prev_ = other.front_;

		size_ = other.size_;
		other.size_ = 0;
	}
	other.size_ = 0;
}
	

// Returns true if list is empty, false otherwise
template <typename T>
bool CacheList<T>::empty() const {
	if (size() == 0){
		return true;
	}
	else {
		return false;
	}
}

// Returns an int, number of pieces of data stored in the list.
template <typename T>
int CacheList<T>::size() const {
	return size_;
}
