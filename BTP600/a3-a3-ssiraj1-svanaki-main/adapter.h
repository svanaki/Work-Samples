// Soodeh Vanaki
// SID: 075782128
// Email: svanaki@myseneca.ca

//Alvia Siraj
//100427178
//ssiraj1@myseneca.ca


#ifndef ADAPTER_H
#define ADAPTER_H
#include "linkedlist.h"

//the Expected interface for a Queue
class Queue {
public:
	Queue() {}
	virtual void enqueue(const int& o) = 0;
	virtual void dequeue() = 0;
	virtual int front() const = 0;
	virtual bool isEmpty() const = 0;
	virtual int numItems() const = 0;
	virtual ~Queue() {}
};


//class below is not completed... you must structure this as a object adapter
//with appropriate requests and calls inheritance structure etc.
class ObjectAdapter: public Queue {
	DList* doublyList_;
public:
	ObjectAdapter() {
		doublyList_ = new DList();
	}
	void enqueue(const int& o) { 
		doublyList_->push_back(o); 
	}
	void dequeue() { 
		doublyList_->pop_front(); 
	}
	int front() const { 
		return doublyList_->frontData(); 
	}
    bool isEmpty() const { 
		return doublyList_->empty(); 
	}
    int numItems() const { 
		return doublyList_->size(); 
	}
};



//class below is not completed... you must structure this as a class adapter
//with appropriate requests and calls inheritance structure etc.

class ClassAdapter :public Queue, private DList {

public:
	
	ClassAdapter(){};
	
	void enqueue(const int& o) {
		push_back(o);
	}
	void dequeue() {
		pop_front();
	};
	int front() const {
		return frontData();
	}
	bool isEmpty() const {
		return empty();
	};
	int numItems() const {
		return size();
	}
};
#endif
