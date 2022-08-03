#ifndef _LIST_H
#define _LIST_H

#include<iostream>
#include <string>
#include <vector>
#include "List.h"

//Berk Sezer

using namespace std;

template<class Object>
class List;


template<class Object>
class ListItr;



template <class Object>
class ListNode {
	ListNode(const Object & theElement = Object(), ListNode* n = NULL) : element(theElement), next(n) {}

	Object element;
	ListNode* next;

	friend class List<Object>;
	friend class ListItr<Object>;
};


template<class Object>
class ListItr{
public:
	ListItr() : current(NULL) {}

	bool isPastEnd() const {
		return current == NULL;
	}

	void advance () {
		if(!isPastEnd() ) {
			current = current->next;
		}
	}

	const Object & retrieve() const {
		if (!isPastEnd() ) {
			return current->element;
		}
		
	}


private:
	ListNode<Object> *current;
	ListItr(ListNode<Object> *theNode) : current (theNode) {}

	friend class List<Object>;
};



template <class Object>
class List {
public:
	List(); //
	List(const List & rhs);
	~List();

	bool isEmpty() const; //
	void makeEmpty(); //

	ListItr<Object> zeroth() const; //
	ListItr<Object> first() const; //

	void insert(const Object & x, const ListItr<Object> & p); //

	ListItr<Object> find(const Object & x) const; //
	ListItr<Object> findPrevious(const Object & x) const; //

	void remove(const Object & x); //

	const List & operator=(const List & rhs);


private:
	ListNode<Object> *header;


};

template<class Object>
List<Object>::List() {
	header = new ListNode<Object>;
}


template<class Object>
bool List<Object>::isEmpty() const {
	return header->next == NULL;
}


template<class Object>
void List<Object>::insert(const Object & x, const ListItr<Object> & p) {
	if(p.current != NULL) {
		p.current->next = new ListNode<Object>(x, p.current->next);
	}
}

template<class Object>
ListItr<Object> List<Object>::find(const Object & x) const {
	ListNode<Object> *itr = header->next;
	
	while(itr != NULL && itr->element != x) {
		itr = itr->next;
	}

	return ListItr<Object>(itr);

}

template<class Object>
ListItr<Object> List<Object>::findPrevious(const Object & x) const {
	
	ListNode<Object> *itr = header;

	while(itr->next != NULL && itr->next->element != x) {
		itr = itr->next;
	}

	return ListItr<Object>(itr);

}

template<class Object>
void List<Object>::remove(const Object & x) {
	
	ListItr<Object> p = findPrevious(x);

	if(p.current->next != NULL) {
		
		ListNode<Object> *oldNode = p.current->next;
		p.current->next = p.current->next->next;
		delete oldNode;
	}
}

template<class Object>
ListItr<Object> List<Object>::zeroth() const {
	return ListItr<Object>(header);
}

template<class Object>
ListItr<Object> List<Object>::first() const {
	return ListItr<Object>(header->next);
}

template<class Object>
void List<Object>::makeEmpty() {
	
	/*while(!isEmpty()) {
		remove(first().retrieve());
	}*/
	ListNode<Object>* ptr = header->next;
	ListNode<Object>* tail = ptr;
	while(ptr != NULL) {
		tail = ptr;
		ptr = ptr->next;
		delete tail;
	}
}

template<class Object>
const List<Object> & List<Object>::operator=(const List<Object> & rhs) {

	if(this != &rhs) {
		
		makeEmpty();

		ListItr<Object> ritr = rhs.first();

		ListItr<Object> itr = zeroth();

		for(; !ritr.isPastEnd(); ritr.advance(), itr.advance()) {
			insert(ritr.retrieve(), itr);
		}
	}

	return *this;

}

template<class Object>
List<Object>::List(const List<Object> & rhs) {
	
	header = new ListNode<Object>;
	*this = rhs;
	
}

template<class Object>
List<Object>::~List() {
	makeEmpty();
	delete header;
}

#endif