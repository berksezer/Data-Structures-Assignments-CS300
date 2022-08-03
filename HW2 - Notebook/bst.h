#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <string>
#include "bst.h"



using namespace std;


//Berk Sezer


template <class Comparable>
struct BinaryNode {
	Comparable element;
	BinaryNode *left;
	BinaryNode *right;
	string title;

	BinaryNode(const Comparable & theElement, BinaryNode* lt, BinaryNode *rt, string t){
		element = theElement;
		left = lt;
		right = rt;
		title = t;
	
	}

};

template<class Comparable>
class BinarySearchTree {
public:
	explicit BinarySearchTree(); 
	BinarySearchTree(const BinarySearchTree & rhs);
	~BinarySearchTree(); 

	const Comparable & findMin() const; 
	const Comparable & findMax() const; 
	Comparable & find(string name) const; 
	bool isEmpty() const; 
	void printTree() const; 
	void makeEmpty(); 
	void insert(const Comparable & x, string name);  
	void remove(string name); 
	const BinarySearchTree & operator=(const BinarySearchTree & rhs); 
	bool operator< (const BinarySearchTree& rhs); 
	bool operator> (const BinarySearchTree& rhs); 
	bool isThere(string name);

	void changedata(const Comparable &, string name);

	void rootNull();

	template<class Comparabale>
	friend ostream& operator<<(ostream &, const BinarySearchTree<Comparable> &);
	
	
private:

	BinaryNode<Comparable>* root;

	
	Comparable ITEM_NOT_FOUND;
	

	Comparable & elementAt(BinaryNode<Comparable> *t)  const; 

	void remove(string name, BinaryNode<Comparable> * & t) const; 
	BinaryNode<Comparable> * findMin(BinaryNode<Comparable> *t) const; 
	BinaryNode<Comparable> * findMax(BinaryNode<Comparable> *t) const; 
	BinaryNode<Comparable> * find(string name, BinaryNode<Comparable>* t ) const; 
	void makeEmpty(BinaryNode<Comparable> * & t) const; 
	void printTree(BinaryNode<Comparable> *t) const; 


	bool isThere(string name, BinaryNode<Comparable> * t);

};




template<class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(): ITEM_NOT_FOUND(), root(NULL){
	
}

template<class Comparable>
Comparable & BinarySearchTree<Comparable>:: elementAt(BinaryNode<Comparable> *t) const {

	return t->element;
}

template<class Comparable>
bool BinarySearchTree<Comparable>::isThere(string name) {
	BinaryNode<Comparable>* ptr = root;

	while(ptr != NULL) {
		if(name < ptr->title) {
			ptr = ptr->left;
		}

		else if (name > ptr ->title) {
			ptr = ptr->right;
		}

		else {
			return true;
		}

	}

	return false;

}

template <class Comparable>
bool BinarySearchTree<Comparable>::isThere(string name, BinaryNode<Comparable> * t) {
	if(t == NULL) {
		return false;
	}

	else if(name < t->title) {
		return isThere(name, t->left);
	}

	else if (name > t->title) {
		return isThere(name, t->right);
	}

	else {
		return true;
	}
}


template<class Comparable>
Comparable & BinarySearchTree<Comparable>::find(string name) const {
	return elementAt(find(name,root));
} 

template<class Comparable> 
void BinarySearchTree<Comparable>::changedata(const Comparable & x, string name) {
	BinaryNode<Comparable> * ptr = find(name, root);

	ptr->element = x;
}

template<class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::find(string name, BinaryNode<Comparable> * t) const {


	while(t != NULL) {
		if(name < t->title) {
			t = t ->left;
		}

		else if (name > t->title) {
			t = t ->right;
		}

		else {
			return t;
		}

	}
	return NULL;
	
} 

template<class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin() const {
	return elementAt(findMin(root));
}

template<class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable> *t) const {
	if(t == NULL) {
		return NULL;
	}

	if(t->left == NULL) {
		return t;
	}
	return findMin(t->left);
} 

template<class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax() const {
	return elementAt(findMax(root));
}

template<class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::findMax(BinaryNode<Comparable>* t) const {
	if(t != NULL) {
		while(t->right != NULL) {
			t = t->right;
		}
	return t; 
	} 
}



template<class Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x, string name) {
	BinaryNode<Comparable>* newnode = new BinaryNode<Comparable> (x, NULL, NULL, name);

	BinaryNode<Comparable>* ptr = root;
	BinaryNode<Comparable>* temp = nullptr;

	while(ptr != NULL) {
		temp = ptr;

		if(ptr->title > name) {
			ptr = ptr->left;
		}
		else {
			ptr = ptr->right;
		}
	}

	if(temp == NULL) {
		temp = newnode;
		root = temp;
	}

	else if (temp->title > name) {
		temp->left = newnode;
	}

	else {
		temp->right = newnode;
	}



}

template<class Comparable>
void BinarySearchTree<Comparable>::remove (string name) {

	BinaryNode<Comparable> *curr = root;
	BinaryNode<Comparable> *prev = NULL;

	while(curr->title != name) {
		prev = curr;
		if (name < curr->title) {
			curr = curr ->left;
		}
		else {
			curr = curr->right;
		}
	}

	if (curr->left == NULL || curr->right == NULL) {
		BinaryNode<Comparable> *ptr;

		if(curr->left == NULL) {
			ptr = curr->right;
		}
		else {
			ptr = curr->left;
		}

		if(prev == NULL) {
			root = ptr;
		}

		else if(curr == prev->left) {
			prev->left = ptr;
		}

		else {
			prev->right = ptr;
		}

		delete curr;
	}

	else {
		BinaryNode<Comparable>* ptr = NULL;
		BinaryNode<Comparable>* temp;

		temp = curr->right;
		while(temp->left != NULL) {
			ptr = temp;
			temp = temp->left;
		}

		if(ptr != NULL) {
			ptr->left = temp ->right;
		}

		else {
			curr->right = temp->right;
		}

		curr->title = temp->title;
		curr->element = temp->element;

		temp = nullptr;
	
	}
 


}

template<class Comparable>
void BinarySearchTree<Comparable>::remove(string name, BinaryNode<Comparable> *& t) const {
	if(t == NULL) {
		return;
	}
	if(name < t->title) {
		remove(name , t->left);
	}

	else if (t->title < name){
		remove(name, t->right);
	}

	

	else if (t->left != NULL && t->right !=NULL) {
		t->title = findMin(t->right)->title;
		remove(t->title, t->right);
	}

	else {
		BinaryNode<Comparable> *oldnode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldnode;

	}
}

template<class Comparable>
void BinarySearchTree<Comparable>::makeEmpty() {

	makeEmpty(root);

}

template<class Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode<Comparable> *& t) const {
	

	if(t != NULL) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = NULL;



}


template<class Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode<Comparable> *t) const {
	if(t != NULL) {
		printTree(t->left);
		cout << t->title << endl;
		printTree(t->right);
	}
}

template<class Comparable>
void BinarySearchTree<Comparable>::printTree() const {
	if(isEmpty()) {
	}
	else {
		printTree(root);
	}
}

template<class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree() {

	makeEmpty();

}

template<class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree<Comparable> & rhs) {
	*this = rhs;
}


template<class Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const {
	if(root == NULL) {
		return true;
	}

	return false;
}



template<class Comparable>
void BinarySearchTree<Comparable>::rootNull() {
	root = nullptr;
}


template<class Comparable>
const BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree<Comparable> &rhs) {


	if(this!=&rhs)
    {
		

	
		BinaryNode<Comparable>* ptr= rhs.root;
		this->root = ptr;
      

    }
	return *this;
}

template<class Comparable>
bool BinarySearchTree<Comparable>::operator<(const BinarySearchTree<Comparable> &rhs) {
	if(root->element < rhs.root->element) {
		return true;
	}
	else {
		return false;
	}
}


template<class Comparable>
bool BinarySearchTree<Comparable>::operator>(const BinarySearchTree<Comparable> &rhs) {
	if(root->element > rhs.root->element) {
		return true;
	}
	else {
		return false;
	}
}


template <class Comparable>
void writeOS(ostream & os, BinaryNode<Comparable> * t) {
	if(t != NULL) {
		writeOS(os, t->left);
		os << t->element << " ";
		writeOS(os, t->right);
	}

}


template <class Comparable>
ostream & operator << (ostream& os, const BinarySearchTree<Comparable> & rhs) {
	
	writeOS(os , rhs.root);

	return os;

}



#endif