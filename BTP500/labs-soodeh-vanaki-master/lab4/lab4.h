/*************************/
/***** Lab 4 *************/
/***** Soodeh Vanaki *****/
/***** SID: 075782128 ****/
/*************************/

#include <iostream>

template <typename T>
class DList {
	struct Node {
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr) {
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	DList() {
		front_ = nullptr;
		back_ = nullptr;
	}
	void push_front(const T& data);
	~DList();

	class const_iterator {
		friend class DList;
		Node* curr_;
		const DList* owner_;
		const_iterator(Node* n, const DList* theList) {
			curr_ = n;
			owner_ = theList;
		}
	public:
		const_iterator() {
			curr_ = nullptr;
			owner_ = nullptr;
		}
		const_iterator operator++() {
			//++x
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int) {
			//x++
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
		const_iterator operator--() {
			//--x
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
		const_iterator operator--(int) {
			//x--
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
		bool operator==(const_iterator rhs) {
			bool rc = false;
			if (rhs.curr_ == curr_) {
				rc = true;
			}
			return rc;
		}
		bool operator!=(const_iterator rhs) {
			bool rc = false;
			if (rhs.curr_ != curr_) {
				rc = true;
			}
			return rc;
		}
		const T& operator*()const {
			return curr_->data_;
		}
	};
	class iterator :public const_iterator {
		friend class DList;
		iterator(Node* n, const DList* theList) :const_iterator(n, theList) {}
	public:
		iterator() :const_iterator() {}
		iterator operator++() {
			//++x
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int) {
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
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
		T& operator*() {
			return this->curr_->data_;
		}
		const T& operator*()const {
			return this->curr_->data_;
		}

	};
	const_iterator cbegin() const {
		if (front_ == nullptr) {
			return cend();
		}
		else {
			return const_iterator(front_, this);
		}
	}
	iterator begin() {
		if (front_ == nullptr) {
			return end();
		}
		else {
		return iterator(front_,this);
		}
	}
	const_iterator cend() const {
		return const_iterator(nullptr, this);
	}
	iterator end() {
		return iterator(nullptr, this);
	}
};


template <typename T>
void DList<T>::push_front(const T& data) {
	Node* nn = new Node(data, front_);
	if (front_ != nullptr) {
		front_->prev_ = nn;
	}
	else {
		back_ = nn;
	}
	front_ = nn;
}

template <typename T>
DList<T>::~DList() {
	Node* current = front_;
	while (current)
	{
		Node* rm = current;
		current = current->next_;
		delete rm;
	}
}


template <typename T>
class Sentinel {
	struct Node {
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr) {
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	Sentinel() {
		front_ = new Node();
		back_ = new Node();
		front_->next_ = back_;
		back_->prev_ = front_;
	}
	void push_front(const T& data);
	~Sentinel();

	class const_iterator {
		friend class Sentinel;
		Node* curr_;
		const Sentinel* owner_;
		const_iterator(Node* n, const Sentinel* theList) {
			curr_ = n;
			owner_ = theList;
		}
	public:
		const_iterator() {
			curr_ = nullptr;
			owner_ = nullptr;
		}
		const_iterator operator++() {
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
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
		const_iterator operator--(int) {
			//x--
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
		bool operator==(const_iterator rhs) {
			bool rc = false;
			if (rhs.curr_ == curr_) {
				rc = true;
			}
			return rc;
		}
		bool operator!=(const_iterator rhs) {
			bool rc = false;
			if (rhs.curr_ != curr_) {
				rc = true;
			}
			return rc;
		}
		const T& operator*()const {
			return this->curr_->data_;
		}
	};
	class iterator :public const_iterator {
		friend class Sentinel;
		iterator(Node* n, const Sentinel* theList) :const_iterator(n, theList) {}
	public:
		iterator() :const_iterator() {}
		iterator operator++() {
			//++x
			this->curr_ = this->curr_->next_;
			return *this;		
		}
		iterator operator++(int) {
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
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
		T& operator*() {
			return this->curr_->data_;
		}
		const T& operator*()const {
			return this->curr_->data_;
		}
	};
	const_iterator cbegin() const {
		if (front_->next_ == back_) {
			return cend();
		}
		else {
			return const_iterator(front_->next_, this);
		}
	}
	iterator begin() {
		if (front_->next_ == back_) {
			return end();
		}
		else {
			return iterator(this->front_->next_, this);
		}
	}
	const_iterator cend() const {
		return const_iterator(back_, this);
	}
	iterator end() {
		return iterator(this->back_, this);
	}
};


template <typename T>
void Sentinel<T>::push_front(const T& data) {
	Node* nn = new Node(data, front_->next_, front_);
	front_->next_->prev_ = nn;
	front_->next_ = nn;
}


template <typename T>
Sentinel<T>::~Sentinel() {
	Node* current = front_->next_;
	while (current && current->next_ != nullptr)
	{
		Node* rm = current;
		current = current->next_;
		delete rm;
	}
}
